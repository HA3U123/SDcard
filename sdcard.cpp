#include "pxt-core.h"
#include "FATFileSystem.h"
#include "SDBlockDevice.h"

using namespace pxt;

namespace SkrepkaSD {
    mbed::SDBlockDevice* sd = nullptr;
    mbed::FATFileSystem* fs = nullptr;
    FILE* activeFile = nullptr;

    // Внутренняя функция для безопасного закрытия файла
    void closeActiveFile() {
        if (activeFile != nullptr) {
            fclose(activeFile);
            activeFile = nullptr;
        }
    }

        //% blockId="skrepka_sd_init" block="Инициализировать SD-карту: MOSI %mosi| MISO %miso| SCK %sck| CS %cs"
    //% weight=100
    void initCard(int mosi, int miso, int sck, int cs) {
        if (sd != nullptr) return; 

        // Получаем CODAL-объекты пинов по их ID из MakeCode
        MicroBitPin* p_mosi = pxt::getPin(mosi);
        MicroBitPin* p_miso = pxt::getPin(miso);
        MicroBitPin* p_sck  = pxt::getPin(sck);
        MicroBitPin* p_cs   = pxt::getPin(cs);

        if (!p_mosi || !p_miso || !p_sck || !p_cs) return;

        // ИСПРАВЛЕНО: Явное приведение типов uint16_t (из CODAL) к PinName (для mbed OS)
        PinName mosi_p = (PinName)p_mosi->name;
        PinName miso_p = (PinName)p_miso->name;
        PinName sck_p  = (PinName)p_sck->name;
        PinName cs_p   = (PinName)p_cs->name;

        sd = new mbed::SDBlockDevice(mosi_p, miso_p, sck_p, cs_p);
        fs = new mbed::FATFileSystem("sd");
        
        int err = fs->mount(sd);
        if (err != 0) {
            delete fs; fs = nullptr;
            delete sd; sd = nullptr;
        }
    }

    //% blockId="skrepka_sd_open" block="Открыть файл %filename для чтения"
    //% weight=90
    bool openGizFile(StringData* filename) {
        if (!fs || filename == nullptr) return false; 
        closeActiveFile(); 
        
        String name(filename);
        // ИСПРАВЛЕНО: Буфер увеличен до 128 байт для безопасной работы с путями
        char path[128];
        snprintf(path, sizeof(path), "/sd/%s", name.data());
        
        activeFile = fopen(path, "r");
        return (activeFile != nullptr);
    }

    //% blockId="skrepka_sd_read" block="Прочитать строку из файла"
    //% weight=80
    StringData* readToBuffer() {
        if (activeFile == nullptr) {
            return pxt::mkString("EOF");
        }
        
        char lineBuffer[128]; // Буфер для одной строки (можно увеличить при необходимости)
        int index = 0;
        int c;
        
        // Оставляем 1 байт под терминальный нуль
        while (index < (sizeof(lineBuffer) - 1)) {
            c = fgetc(activeFile);
            
            if (c == EOF) {
                closeActiveFile(); 
                if (index == 0) {
                    return pxt::mkString("EOF");
                }
                break;
            }
            
            if (c == '\r') {
                int next = fgetc(activeFile);
                if (next != '\n' && next != EOF) {
                    // ИСПРАВЛЕНО: Вместо fseek используем стандартный ungetc
                    ungetc(next, activeFile);
                }
                break; 
            }
            if (c == '\n') {
                break; 
            }
            
            lineBuffer[index++] = (char)c;
        }
        
        lineBuffer[index] = '\0'; 
        return pxt::mkString(lineBuffer);
    }

    //% blockId="skrepka_sd_write" block="Записать в файл %filename текст %text"
    //% weight=70
    bool writeToFile(StringData* filename, StringData* text) {
        if (!fs || filename == nullptr || text == nullptr) return false;

        closeActiveFile(); 

        String name(filename);
        String content(text);
        
        // ИСПРАВЛЕНО: Буфер увеличен до 128 байт
        char path[128];
        snprintf(path, sizeof(path), "/sd/%s", name.data());

        FILE* f = fopen(path, "a");
        if (f == nullptr) return false;

        fprintf(f, "%s\n", content.data());
        fflush(f); 
        fclose(f);
        return true;
    }
}
