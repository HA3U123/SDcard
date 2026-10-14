//% color="#1E88E5" icon="\uf0c6" block="SkrepkaSD"
namespace customsd {

    /**
     * Подключить модуль SD-карты к пинам micro:bit V2
     */
    //% block="Инициализировать SD-карту | MOSI %mosi | MISO %miso | CLK %sclk | CS %cs"
    //% mosi.defl=DigitalPin.P14 miso.defl=DigitalPin.P13 sclk.defl=DigitalPin.P15 cs.defl=DigitalPin.P16
    export function initSD(mosi: DigitalPin, miso: DigitalPin, sclk: DigitalPin, cs: DigitalPin): void {
        c_init(mosi, miso, sclk, cs);
    }

    /**
     * Записать строку в файл (если файла нет, он создастся автоматически)
     */
    //% block="Записать строку %text в файл %filename"
    //% text.defl="125,Avav,Aprold" filename.defl="data.txt"
    export function writeLine(text: string, filename: string): void {
        c_write(text, filename);
    }

    /**
     * Прочитать конкретную строку по её номеру (начиная с 0)
     */
    //% block="Прочитать строку № %lineIndex из файла %filename"
    //% lineIndex.defl=0 filename.defl="data.txt"
    export function readLine(lineIndex: number, filename: string): string {
        return c_read_line(filename, lineIndex);
    }

    /**
     * Узнать, сколько всего строк записано в файле
     */
    //% block="Количество строк в файле %filename"
    //% filename.defl="data.txt"
    export function countLines(filename: string): number {
        return c_count_lines(filename);
    }

    /**
     * Проверить, существует ли файл на SD-карте
     */
    //% block="Файл %filename существует?"
    //% filename.defl="data.txt"
    export function fileExists(filename: string): boolean {
        return c_exists(filename);
    }

    /**
     * Полностью удалить файл с SD-карты
     */
    //% block="Удалить файл %filename с SD-карты"
    //% filename.defl="data.txt"
    export function deleteFile(filename: string): void {
        c_delete(filename);
    }
}