//% color=#007ACC icon="\uf0a0" block="Skrepka SD"
namespace SkrepkaSD {
    //% block="Инициализировать карту MOSI %mosi MISO %miso SCK %sck CS %cs"
    //% shim=SkrepkaSD::initCard
    function initCard(mosi: number, miso: number, sck: number, cs: number): void;

    //% block="Открыть файл %filename для чтения"
    //% shim=SkrepkaSD::openGizFile
    function openGizFile(filename: string): boolean;

    //% block="Прочитать строку в буфер"
    //% shim=SkrepkaSD::readToBuffer
    function readToBuffer(): string;

    //% block="Записать в файл %filename текст %text"
    //% shim=SkrepkaSD::writeToFile
    function writeToFile(filename: string, text: string): boolean;
}
