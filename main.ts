//% color="#1E88E5" icon="\uf0c6" block="SkrepkaSD"
namespace customsd {

    /**
     * Подключить модуль SD-карты к пинам micro:bit V2
     * @param mosi пин MOSI, eg: DigitalPin.P15
     * @param miso пин MISO, eg: DigitalPin.P14
     * @param sclk пин CLK, eg: DigitalPin.P13
     * @param cs пин CS, eg: DigitalPin.P16
     */
    //% block="Инициализировать SD-карту | MOSI %mosi | MISO %miso | CLK %sclk | CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sclk.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    export function initSD(mosi: DigitalPin, miso: DigitalPin, sclk: DigitalPin, cs: DigitalPin): void {
        if (pxt.getConfigData("target") == "microbit") {
            c_init(mosi, miso, sclk, cs);
        }
    }

    /**
     * Записать строку в файл (если файла нет, он создастся автоматически)
     */
    //% block="Записать строку %text в файл %filename"
    //% text.defl="125,Avav,Aprold" filename.defl="data.txt"
    export function writeLine(text: string, filename: string): void {
        if (pxt.getConfigData("target") == "microbit") {
            c_write(text, filename);
        }
    }

    /**
     * Прочитать конкретную строку по её номеру (начиная с 0)
     */
    //% block="Прочитать строку № %lineIndex из файла %filename"
    //% lineIndex.defl=0 filename.defl="data.txt"
    export function readLine(lineIndex: number, filename: string): string {
        if (pxt.getConfigData("target") == "microbit") {
            return c_read_line(filename, lineIndex);
        }
        return "125,Avav,Aprold"; // Заглушка для симулятора в браузере
    }

    /**
     * Узнать, сколько всего строк записано в файле
     */
    //% block="Количество строк в файле %filename"
    //% filename.defl="data.txt"
    export function countLines(filename: string): number {
        if (pxt.getConfigData("target") == "microbit") {
            return c_count_lines(filename);
        }
        return 1; // Заглушка для симулятора
    }

    /**
     * Проверить, существует ли файл на SD-карте
     */
    //% block="Файл %filename существует?"
    //% filename.defl="data.txt"
    export function fileExists(filename: string): boolean {
        if (pxt.getConfigData("target") == "microbit") {
            return c_exists(filename);
        }
        return true; // Заглушка для симулятора
    }

    /**
     * Полностью удалить файл с SD-карты
     */
    //% block="Удалить файл %filename с SD-карты"
    //% filename.defl="data.txt"
    export function deleteFile(filename: string): void {
        if (pxt.getConfigData("target") == "microbit") {
            c_delete(filename);
        }
    }
}
