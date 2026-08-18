// Этот файл автоматически связывает TS и C++ (shims.d.ts)
declare namespace SkrepkaSD {
    //% shim=SkrepkaSD::initCard
    function initCard(mosi: number, miso: number, sck: number, cs: number): void;

    //% shim=SkrepkaSD::openGizFile
    function openGizFile(filename: string): boolean;

    //% shim=SkrepkaSD::readToBuffer
    function readToBuffer(): string;

    // Сигнатура для блока записи
    //% shim=SkrepkaSD::writeToFile
    function writeToFile(filename: string, text: string): boolean;
    //% shim=String_::charAt
function charAt(pos: number): string;

//% shim=String_::toNumber
function toNumber(text: string): number;
}
