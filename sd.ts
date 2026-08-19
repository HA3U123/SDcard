    /**
     * Инициализирует SD-карту с указанием пинов подключения SPI.
     * @param mosi Pin для передачи данных, eg: DigitalPin.P15
     * @param miso Pin для приема данных, eg: DigitalPin.P14
     * @param sck Pin тактового сигнала, eg: DigitalPin.P13
     * @param cs Pin выбора чипа, eg: DigitalPin.P16
     */
    //% blockId="skrepka_sd_init_block" 
    //% block="Инициализировать SD-карту| MOSI %mosi| MISO %miso| SCK %sck| CS %cs"
    //% mosi.defl=DigitalPin.P15 miso.defl=DigitalPin.P14 sck.defl=DigitalPin.P13 cs.defl=DigitalPin.P16
    //% weight=100
    export function initialize(mosi: DigitalPin, miso: DigitalPin, sck: DigitalPin, cs: DigitalPin): void {
        initCard(mosi, miso, sck, cs);
    }
    
    /**
     * Считывает следующую строку из ранее открытого файла.
     * Если достигнут конец файла (EOF), автоматически закрывает его и возвращает "EOF".
     */
    //% blockId="skrepka_sd_read_block" 
    //% block="Прочитать строку из файла"
    //% weight=80
    export function readLine(): string {
        return readToBuffer();
    }

    /**
     * Проверяет, осталась ли еще информация в файле (не равен ли результат "EOF").
     * Полезно для циклов "пока не конец файла".
     * @param line Переменная строки, полученная из файла
     */
    //% blockId="skrepka_sd_is_eof" 
    //% block="строка %line является концом файла (EOF)?"
    //% line.shadow="text"
    //% weight=75
    export function isEOF(line: string): boolean {
        return line == "EOF";
    }

    /**
     * Дописывает текстовую строку в конец указанного файла (режим Append).
     * Если файл не существовал, он будет создан автоматически.
     * Каждая запись автоматически завершается переносом строки (\n).
     * @param filename Имя файла, eg: "log.txt"
     * @param text Текст для записи, eg: "Привет, мир!"
     */
    //% blockId="skrepka_sd_write_block" 
    //% block="В файл %filename записать строку %text"
    //% filename.shadow="text" text.shadow="text"
    //% weight=70
    export function writeLine(filename: string, text: string): boolean {
        return writeToFile(filename, text);
    }
}
