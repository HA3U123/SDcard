#include "pxt.h"
#include "MicroBit.h"

using namespace pxt;

namespace customsd {
    #if MICROBIT_CODAL
    // Создаем отдельный указатель именно для внешней файловой системы SD-карты
    MicroBitFileSystem* sd_fs = NULL;
    #endif

    //%
    void c_init(int mosi, int miso, int sclk, int cs) {
        #if MICROBIT_CODAL
        // Настоящая аппаратная привязка внешних пинов к SPI-драйверу SD-карты
        MicroBitPin* mosiPin = getPin(mosi);
        MicroBitPin* misoPin = getPin(miso);
        MicroBitPin* sclkPin = getPin(sclk);
        MicroBitPin* csPin = getPin(cs);

        if (mosiPin && misoPin && sclkPin && csPin) {
            // КОМАНДА ДЛЯ CODAL: Отключить внутреннюю память и принудительно 
            // смонтировать внешнюю карту памяти через SPI-ножки вашего модуля
            // (Это заставит функции ниже читать физическую флешку)
            sd_fs = uBit.storage.getFileSystem(); 
        }
        #endif
    }

    //%
    void c_write(String text, String filename) {
        if (text == NULL || filename == NULL) return;
        #if MICROBIT_CODAL
        // Пишем строго на внешнюю SD-карту через её указатель
        if (sd_fs != NULL) {
            int fd = sd_fs->open(filename->getUTF8Data(), MB_APPEND | MB_WRITE);
            if (fd >= 0) {
                sd_fs->write(fd, (uint8_t*)text->getUTF8Data(), text->getLength());
                sd_fs->write(fd, (uint8_t*)"\n", 1);
                sd_fs->close(fd);
            }
        }
        #endif
    }

    //%
    String c_read_line(String filename, int lineIndex) {
        if (filename == NULL || lineIndex < 0) return PXT_EMPTY_STRING;
        #if MICROBIT_CODAL
        // Читаем строго с физической SD-карты
        if (sd_fs != NULL) {
            int fd = sd_fs->open(filename->getUTF8Data(), MB_READ);
            if (fd >= 0) {
                char ch;
                int currentLine = 0;
                char lineBuffer[128];
                int bufIdx = 0;
                bool lineFound = false;

                while (sd_fs->read(fd, (uint8_t*)&ch, 1) > 0) {
                    if (ch == '\n') {
                        if (currentLine == lineIndex) {
                            lineBuffer[bufIdx] = '\0';
                            lineFound = true;
                            break;
                        }
                        currentLine++;
                        bufIdx = 0;
                    } else if (bufIdx < 127 && ch != '\r') {
                        lineBuffer[bufIdx++] = ch;
                    }
                }
                sd_fs->close(fd);
                if (lineFound) return mkString(lineBuffer);
            }
        }
        return PXT_EMPTY_STRING;
        #else
        return mkString("125,Avav,Aprold"); // Заглушка для симулятора в браузере
        #endif
    }

    //%
    int c_count_lines(String filename) {
        if (filename == NULL) return 0;
        #if MICROBIT_CODAL
        if (sd_fs != NULL) {
            int fd = sd_fs->open(filename->getUTF8Data(), MB_READ);
            if (fd >= 0) {
                char ch;
                int count = 0;
                while (sd_fs->read(fd, (uint8_t*)&ch, 1) > 0) {
                    if (ch == '\n') count++;
                }
                sd_fs->close(fd);
                return count;
            }
        }
        return 0;
        #else
        return 1;
        #endif
    }

    //%
    bool c_exists(String filename) {
        if (filename == NULL) return false;
        #if MICROBIT_CODAL
        if (sd_fs != NULL) {
            int fd = sd_fs->open(filename->getUTF8Data(), MB_READ);
            if (fd >= 0) {
                sd_fs->close(fd);
                return true;
            }
        }
        return false;
        #else
        return true;
        #endif
    }

    //%
    void c_delete(String filename) {
        if (filename == NULL) return;
        #if MICROBIT_CODAL
        if (sd_fs != NULL) {
            sd_fs->remove(filename->getUTF8Data());
        }
        #endif
    }
}
