//% color=#1E6273 icon="\uf0a0" block="Skrepka SD" weight=95
export namespace SkrepkaSD {

    //% blockId="skrepka_sd_init_block" 
    //% block="Инициализировать SD-карту| MOSI %mosi| MISO %miso| SCK %sck| CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sck.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    //% weight=100
    export function initialize(mosi: DigitalPin, miso: DigitalPin, sck: DigitalPin, cs: DigitalPin): void {
        initCard(mosi, miso, sck, cs);
    }

    //% blockId="skrepka_sd_open_block" 
    //% block="Открыть файл %filename для чтения"
    //% filename.shadow="text"
    //% weight=90
    export function openFile(filename: string): boolean {
        return openGizFile(filename);
    }

    //% blockId="skrepka_sd_read_block" 
    //% block="Прочитать строку из файла"
    //% weight=80
    export function readLine(): string {
        return readToBuffer();
    }

    //% blockId="skrepka_sd_is_eof" 
    //% block="строка %line является концом файла (EOF)?"
    //% line.shadow="text"
    //% weight=75
    export function isEOF(line: string): boolean {
        return line == "EOF";
    }

    //% blockId="skrepka_sd_write_block" 
    //% block="В файл %filename записать строку %text"
    //% filename.shadow="text" text.shadow="text"
    //% weight=70
    export function writeLine(filename: string, text: string): boolean {
        return writeToFile(filename, text);
    }
}
