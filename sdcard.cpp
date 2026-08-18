#include "pxt-core.h"
#include "FATFileSystem.h"
#include "SDBlockDevice.h"

using namespace pxt;

namespace SkrepkaSD {
    mbed::SDBlockDevice* sd = nullptr;
    mbed::FATFileSystem* fs = nullptr;
    FILE* activeFile = nullptr;

    // %shim=SkrepkaSD::initCard
    void initCard(int mosi, int miso, int sck, int cs) {
        if (sd != nullptr) return; 
        sd = new mbed::SDBlockDevice((PinName)mosi, (PinName)miso, (PinName)sck, (PinName)cs);
        fs = new mbed::FATFileSystem("sd");
        int err = fs->mount(sd);
        if (err != 0) {
            delete fs; fs = nullptr;
            delete sd; sd = nullptr;
        }
    }

    // %shim=SkrepkaSD::openGizFile
    bool openGizFile(String filename) {
        if (!fs) return false; 
        if (activeFile != nullptr) {
            fclose(activeFile);
            activeFile = nullptr;
        }
        if (!filename || filename->getUTF8Data() == nullptr) return false;
        char path[64];
        snprintf(path, sizeof(path), "/sd/%s", filename->getUTF8Data());
        activeFile = fopen(path, "r");
        return (activeFile != nullptr);
    }

    // %shim=SkrepkaSD::readToBuffer
    String readToBuffer() {
        if (activeFile == nullptr) return pxt::mkString("EOF");
        char lineBuffer[32]; 
        int index = 0;
        int c;
        while (index < 31) {
            c = fgetc(activeFile);
            if (c == EOF) {
                if (index == 0) return pxt::mkString("EOF");
                break;
            }
            if (c == '\n' || c == '\r') {
                if (index == 0) continue; 
                break;
            }
            lineBuffer[index++] = (char)c;
        }
        lineBuffer[index] = '\0'; 
        return pxt::mkString(lineBuffer);
    }

    // Исправленный супер-блок записи
    // %shim=SkrepkaSD::writeToFile
    bool writeToFile(String filename, String text) {
        if (!fs) return false;
        if (!filename || filename->getUTF8Data() == nullptr) return false;
        if (!text || text->getUTF8Data() == nullptr) return false;

        // Безопасность: Если этот файл сейчас открыт на чтение через activeFile, 
        // его необходимо закрыть перед записью, чтобы избежать HardFault микроконтроллера!
        if (activeFile != nullptr) {
            fclose(activeFile);
            activeFile = nullptr;
        }

        char path[64];
        snprintf(path, sizeof(path), "/sd/%s", filename->getUTF8Data());

        FILE* f = fopen(path, "a");
        if (f == nullptr) return false;

        // Записываем текст и добавляем символ переноса строки \n
        fprintf(f, "%s\n", text->getUTF8Data());
        
        // Принудительно выталкиваем данные из кэша RAM непосредственно на физическую SD-карту
        fflush(f); 
        fclose(f);
        
        return true;
    }
}
