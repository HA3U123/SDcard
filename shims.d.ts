//% color=#1E6273 icon="\uf0a0" block="Skrepka SD" weight=95
namespace SkrepkaSD {
    //% shim=SkrepkaSD::initCard
    export function initCard(mosi: number, miso: number, sck: number, cs: number): void;

    //% shim=SkrepkaSD::openGizFile
    export function openGizFile(filename: string): boolean;

    //% shim=SkrepkaSD::readToBuffer
    export function readToBuffer(): string;

    //% shim=SkrepkaSD::writeToFile
    export function writeToFile(filename: string, text: string): boolean;
}
