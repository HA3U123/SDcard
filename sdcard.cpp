#include "pxt-core.h"
#include "FATFileSystem.h"
#include "SDBlockDevice.h"

// Используем пространства имен CODAL и PXT
using namespace pxt;

namespace SkrepkaSD {
    // Указатели инициализируем в nullptr
    mbed::SDBlockDevice* sd = nullptr;
    mbed::FATFileSystem* fs = nullptr;
    FILE* activeFile = nullptr;

    // %shim=SkrepkaSD::initCard
    void initCard(int mosi, int miso, int sck, int cs) {
        // Если уже инициализировано — выходим
        if (sd != nullptr) return; 

        // В micro:bit PXT id пинов конвертируются в PinName через специальный макрос или приведение
        PinName p_mosi = (PinName)mosi;
        PinName p_miso = (PinName)miso;
        PinName p_sck  = (PinName)sck;
        PinName p_cs   = (PinName)cs;

        // Создаем объекты в куче (heap)
        sd = new mbed::SDBlockDevice(p_mosi, p_miso, p_sck, p_cs);
        fs = new mbed::FATFileSystem("sd");

        // Пытаемся смонтировать файловую систему
        int err = fs->mount(sd);
        if (err != 0) {
            // Если ошибка (например, нет карты), очищаем память во избежание HardFault
            delete fs; fs = nullptr;
            delete sd; sd = nullptr;
        }
    }

    // %shim=SkrepkaSD::openGizFile
    bool openGizFile(String filename) {
        // Если карта памяти не смонтирована удачно, файл открыть нельзя
        if (!fs) return false; 

        // Закрываем предыдущий файл, если он был открыт
        if (activeFile != nullptr) {
            fclose(activeFile);
            activeFile = nullptr;
        }
        
        // Проверка на пустую строку
        if (!filename || filename->getUTF8Data() == nullptr) return false;

        // Буфер для пути (64 байта достаточно для micro:bit, защищает от переполнения)
        char path[64];
        snprintf(path, sizeof(path), "/sd/%s", filename->getUTF8Data());
        
        // Открываем файл на чтение
        activeFile = fopen(path, "r");
        return (activeFile != nullptr);
    }

    // %shim=SkrepkaSD::readToBuffer
    String readToBuffer() {
        // Если файл не открыт — сразу возвращаем PXT-строку "EOF"
        if (activeFile == nullptr) return pxt::mkString("EOF");

        char lineBuffer[32]; 
        int index = 0;
        int c;

        while (index < 31) {
            c = fgetc(activeFile);
            
            if (c == EOF) {
                // Если файл кончился и мы ничего не успели прочитать
                if (index == 0) return pxt::mkString("EOF");
                break;
            }
            
            // Обработка символов новой строки
            if (c == '\n' || c == '\r') {
                // Пропускаем пустые байты в начале строки (например, если \r\n идет подряд)
                if (index == 0) continue; 
                break;
            }
            
            lineBuffer[index++] = (char)c;
        }
        
        // Обязательный терминальный ноль для C-строки
        lineBuffer[index] = '\0'; 

        // Возвращаем строку, корректно обернутую в pxt::mkString для MakeCode Garbage Collector
        return pxt::mkString(lineBuffer);
    }
}