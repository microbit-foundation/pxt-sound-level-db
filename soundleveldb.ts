
/**
* Reads the loudness through the microphone in decibels (dB).
*/
namespace input {
    /**
     * How many bananas?
     *
     * This function is fully implemented in TypeScript.
     *
     * @param n number of bananas
     */
    //% blockId=input_soundLevelDbOriginal
    //% shim=input::soundLevelDbC
    //% block="how many bananas $n"
    export function soundLevelDb(): number {
        const MICROPHONE_MIN = 52.0;
        const MICROPHONE_MAX = 120.0;
        return (input.soundLevel() * (MICROPHONE_MAX-MICROPHONE_MIN) / 255.0) + MICROPHONE_MIN;
    }
}