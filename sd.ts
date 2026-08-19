//% color=#4c97ff icon="\uf0a0" block="Skrepka SD"
namespace SkrepkaSD {

    /**
     * Инициализация SD карты с выбором пинов.
     */
    //% block="Инициализировать карту: MOSI %mosi| MISO %miso| SCK %sck| CS %cs"
    //% mosi.shadow="digitalioPins"
    //% miso.shadow="digitalioPins"
    //% sck.shadow="digitalioPins"
    //% cs.shadow="digitalioPins"
    export function init(mosi: number, miso: number, sck: number, cs: number): void {
        // Вызываем функцию из C++ через shim
        initCard(mosi, miso, sck, cs);
    }

    /**
     * Открыть файл для чтения.
     */
    //% block="Открыть файл %filename для чтения"
    export function openFile(filename: string): boolean {
        return openGizFile(filename);
    }

    /**
     * Прочитать одну строку из открытого файла.
     */
    //% block="Прочитать строку"
    export function readLine(): string {
        return readToBuffer();
    }

    /**
     * Записать текст в файл.
     */
    //% block="Записать в файл %filename текст %text"
    export function write(filename: string, text: string): boolean {
        return writeToFile(filename, text);
    }
}
