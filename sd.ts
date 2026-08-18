//% color=#1E90FF icon="\uf07b" block="SkrepkaSD"
namespace SkrepkaSD {

    /**
     * Включить карту памяти через SPI пины.
     */
    //% blockId=skrepka_sd_init
    //% block="включить SD карту MOSI %mosi MISO %miso SCK %sck CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sck.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    export function init(mosi: DigitalPin, miso: DigitalPin, sck: DigitalPin, cs: DigitalPin): void {
        // Передаем внутренний численный ID пина micro:bit в C++
        initCard(mosi, miso, sck, cs);
    }

    /**
     * Открыть файл программы .giz с флешки.
     * @param filename имя файла, eg: "main.giz"
     */
    //% blockId=skrepka_sd_open
    //% block="открыть файл %filename"
    //% filename.defl="main.giz"
    export function openFile(filename: string): boolean {
        return openGizFile(filename);
    }

    /**
     * Считать следующую строчку кода. Если файл кончился, вернет "EOF".
     */
    //% blockId=skrepka_sd_read
    //% block="считать строку кода"
    export function readLine(): string {
        return readToBuffer();
    }
}
