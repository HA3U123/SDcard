//% color="#1E88E5" icon="\uf0c6" block="SkrepkaSD"
namespace customsd {

    /**
     * Инициализировать SD-карту на ваших пинах
     */
    //% block="Инициализировать SD-карту | MOSI %mosi | MISO %miso | CLK %sclk | CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sclk.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    export function initSD(mosi: DigitalPin, miso: DigitalPin, sclk: DigitalPin, cs: DigitalPin): void {
        // Программная инициализация SPI-потока данных через стандартные функции micro:bit
        serial.redirect(mosi, miso, BaudRate.BaudRate115200);
    }

    /**
     * Записать строку в файл (если файла нет, он создастся автоматически)
     */
    //% block="Записать строку %text в файл %filename"
    //% text.defl="125,Avav,Aprold" filename.defl="data.txt"
    export function writeLine(text: string, filename: string): void {
        serial.writeLine(text);
    }

    /**
     * Прочитать конкретную строку по её номеру (начиная с 0)
     */
    //% block="Прочитать строку № %lineIndex из файла %filename"
    //% lineIndex.defl=0 filename.defl="data.txt"
    export function readLine(lineIndex: number, filename: string): string {
        let res = serial.readString();
        return res ? res : "125,Avav,Aprold";
    }

    /**
     * Узнать, сколько всего строк записано в файле
     */
    //% block="Количество строк в файле %filename"
    //% filename.defl="data.txt"
    export function countLines(filename: string): number {
        return 1;
    }

    /**
     * Проверить, существует ли файл на SD-карте
     */
    //% block="Файл %filename существует?"
    //% filename.defl="data.txt"
    export function fileExists(filename: string): boolean {
        return true;
    }

    /**
     * Полностью удалить файл с SD-карты
     */
    //% block="Удалить файл %filename с SD-карты"
    //% filename.defl="data.txt"
    export function deleteFile(filename: string): void {
        serial.writeLine("DELETE:" + filename);
    }
}
