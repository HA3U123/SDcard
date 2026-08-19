#include "pxt-core.h"
#include "FATFileSystem.h"
#include "SDBlockDevice.h"

using namespace pxt;

namespace SkrepkaSD {
    mbed::SDBlockDevice* sd = nullptr;
    mbed::FATFileSystem* fs = nullptr;
    FILE* activeFile = nullptr;

    void closeActiveFile() {
        if (activeFile != nullptr) {
            fclose(activeFile);
            activeFile = nullptr;
        }
    }

    void initCard(int mosi, int miso, int sck, int cs) {
        if (sd != nullptr) return; 

        MicroBitPin* p_mosi = pxt::getPin(mosi);
        MicroBitPin* p_miso = pxt::getPin(miso);
        MicroBitPin* p_sck  = pxt::getPin(sck);
        MicroBitPin* p_cs   = pxt::getPin(cs);

        if (!p_mosi || !p_miso || !p_sck || !p_cs) return;

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

    bool openGizFile(StringData* filename) {
        if (!fs || filename == nullptr) return false; 
        closeActiveFile(); 
        
        String name(filename);
        char path[128];
        snprintf(path, sizeof(path), "/sd/%s", name.data());
        
        activeFile = fopen(path, "r");
        return (activeFile != nullptr);
    }

    StringData* readToBuffer() {
        if (activeFile == nullptr) {
            return pxt::mkString("EOF");
        }
        
        char lineBuffer[128]; 
        int index = 0;
        int c;
        
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

    bool writeToFile(StringData* filename, StringData* text) {
        if (!fs || filename == nullptr || text == nullptr) return false;

        closeActiveFile(); 

        String name(filename);
        String content(text);
        
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
