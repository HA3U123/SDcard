//% color=#2693ab icon="\uf0a0" block="Skrepka SD"
namespace SkrepkaSD {
    /**
     * Инициализирует SD карту через указанные пины.
     */
    //% shim=SkrepkaSD::initCard
    function initCard(mosi: number, miso: number, sck: number, cs: number): void;

    /**
     * Открывает файл на чтение. Возвращает true при успехе.
     */
    //% shim=SkrepkaSD::openGizFile
    function openGizFile(filename: string): boolean;

    /**
     * Читает одну строку из открытого файла. Возвращает "EOF", если файл закончился.
     */
    //% shim=SkrepkaSD::readToBuffer
    function readToBuffer(): string;

    /**
     * Дописывает строку в файл. Автоматически переносит строку в конце.
     */
    //% shim=SkrepkaSD::writeToFile
    function writeToFile(filename: string, text: string): boolean;
}
