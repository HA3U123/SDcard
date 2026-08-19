//% color=#1E6273 icon="\uf0a0" block="Skrepka SD" weight=95
export namespace SkrepkaSD {

    //% blockId="skrepka_sd_init_block" 
    //% block="Инициализировать SD-карту| MOSI %mosi| MISO %miso| SCK %sck| CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sck.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    //% weight=100
    export function initialize(mosi: DigitalPin, miso: DigitalPin, sck: DigitalPin, cs: DigitalPin): void {
        // ИСПРАВЛЕНО: Явно приводим enum DigitalPin к типу number через унарный плюс или принудительное приведение
        let mosi_num: number = mosi;
        let miso_num: number = miso;
        let sck_num: number = sck;
        let cs_num: number = cs;
        
        SkrepkaSD.initCard(mosi_num, miso_num, sck_num, cs_num);
    }

    //% blockId="skrepka_sd_open_block" 
    //% block="Открыть файл %filename для чтения"
    //% filename.shadow="text"
    //% weight=90
    export function openFile(filename: string): boolean {
        return SkrepkaSD.openGizFile(filename);
    }

    //% blockId="skrepka_sd_read_block" 
    //% block="Прочитать строку из файла"
    //% weight=80
    export function readLine(): string {
        return SkrepkaSD.readToBuffer();
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
        return SkrepkaSD.writeToFile(filename, text);
    }
}
