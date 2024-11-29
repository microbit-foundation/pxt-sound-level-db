
/**
* Reads the loudness through the microphone in decibels (dB).
*/
namespace input {
    /**
     * Reads the loudness through the microphone in decibels (dB).
     */
    //% blockId=input_soundLevelDbOriginal
    //% shim=input::soundLevelDbC
    //% block="sound level (dB)"
    //% parts="microphone"
    //% weight=13 blockGap=8
    //% advanced=true
    //% group="micro:bit (V2)"
    export function soundLevelDb(): number {
        const MICROPHONE_MIN = 52.0;
        const MICROPHONE_MAX = 120.0;
        return Math.floor(input.soundLevel() * (MICROPHONE_MAX-MICROPHONE_MIN) / 255.0) + MICROPHONE_MIN;
    }
}
