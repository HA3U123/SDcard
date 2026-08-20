//% color=#1E6273 icon="\uf0a0" weight=95
declare namespace SkrepkaSD {
    //% shim=SkrepkaSD::initCard
    function initCard(mosi: number, miso: number, sck: number, cs: number): void;

    //% shim=SkrepkaSD::openGizFile
    function openGizFile(filename: string): boolean;

    //% shim=SkrepkaSD::readToBuffer
    function readToBuffer(): string;

    //% shim=SkrepkaSD::writeToFile
    function writeToFile(filename: string, text: string): boolean;
}
