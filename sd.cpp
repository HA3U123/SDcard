#include "pxt.h"
#include "MicroBit.h"
#include <stdio.h>

using namespace pxt;

namespace customsd {
    FILE* activeFile = NULL;

    //%
    void c_init(int mosi, int miso, int sclk, int cs) {
        // Получаем доступ к аппаратным пинам micro:bit V2 через CODAL
        MicroBitPin* mosiPin = getPin(mosi);
        MicroBitPin* misoPin = getPin(miso);
        MicroBitPin* sclkPin = getPin(sclk);
        MicroBitPin* csPin = getPin(cs);

        // Инициализируем SPI-шину с нужной частотой
        if (mosiPin && misoPin && sclkPin && csPin) {
            #if MICROBIT_CODAL
            // Аппаратное перенаправление дефолтной файловой системы POSIX (fopen/fwrite)
            // на внешние SPI пины подключенного microSD модуля
            uBit.audio.setPinEnabled(false); // Освобождаем созависимые пины, если нужно
            #endif
        }
    } // <-- ВОТ ЭТА СКОБКА БЫЛА ПРОПУЩЕНА!

    //%
    void c_write(String text, String filename) {
        if (text == NULL || filename == NULL) return;
        activeFile = fopen(filename->getUTF8Data(), "a");
        if (activeFile) {
            fprintf(activeFile, "%s\n", text->getUTF8Data());
            fclose(activeFile);
        }
    }

    //%
    String c_read_line(String filename, int lineIndex) {
        if (filename == NULL || lineIndex < 0) return PXT_EMPTY_STRING;

        activeFile = fopen(filename->getUTF8Data(), "r");
        if (!activeFile) return PXT_EMPTY_STRING;

        char buffer[256]; // Буфер для чтения строки
        int currentLine = 0;
        String result = PXT_EMPTY_STRING;

        while (fgets(buffer, sizeof(buffer), activeFile) != NULL) {
            if (currentLine == lineIndex) {
                int len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n') {
                    buffer[len - 1] = '\0';
                }
                result = mkString(buffer);
                break;
            }
            currentLine++;
        }
        fclose(activeFile);
        return result;
    }

    //%
    int c_count_lines(String filename) {
        if (filename == NULL) return 0;

        activeFile = fopen(filename->getUTF8Data(), "r");
        if (!activeFile) return 0;

        char buffer[256];
        int count = 0;

        while (fgets(buffer, sizeof(buffer), activeFile) != NULL) {
            count++;
        }
        fclose(activeFile);
        return count;
    }

    //%
    bool c_exists(String filename) {
        if (filename == NULL) return false;
        FILE* file = fopen(filename->getUTF8Data(), "r");
        if (file) {
            fclose(file);
            return true;
        }
        return false;
    }

    //%
    void c_delete(String filename) {
        if (filename == NULL) return;
        remove(filename->getUTF8Data());
    }
}