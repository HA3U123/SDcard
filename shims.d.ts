declare namespace SkrepkaSD {
    function initCard(mosi: number, miso: number, sck: number, cs: number): void;
    function openGizFile(filename: string): boolean;
    function readToBuffer(): string;
    function writeToFile(filename: string, text: string): boolean;
}
