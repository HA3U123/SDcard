declare namespace customsd {
    //% shim=customsd::c_init
    function c_init(mosi: number, miso: number, sclk: number, cs: number): void;

    //% shim=customsd::c_write
    function c_write(text: string, filename: string): void;

    //% shim=customsd::c_read_line
    function c_read_line(filename: string, lineIndex: number): string;

    //% shim=customsd::c_count_lines
    function c_count_lines(filename: string): number;

    //% shim=customsd::c_exists
    function c_exists(filename: string): boolean;

    //% shim=customsd::c_delete
    function c_delete(filename: string): void;
}