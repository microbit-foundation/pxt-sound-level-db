
/**
* Reads the loudness through the microphone in decibels (dB).
*/
namespace input {
    /**
     * Reads the loudness through the microphone in decibels (dB).
     */
    //% blockId=input_soundLevelDb
    //% shim=input::soundLevelDbC
    //% block="sound level (dB)"
    //% parts="microphone"
    //% weight=13 blockGap=8
    //% advanced=true
    //% group="micro:bit (V2)"
    export function soundLevelDb(): number {
        // The input.soundLevel() 8-bit range conversion goes from 52 to 100 dB,
        // but the input.soundLevelDb() function can return values from 35 to around 100ish.
        // So, the mapping between the simulator 8-bit-value-to-dB-value vs on-device won't be
        // the same, but this is only noticeable when looking at both value side by side.
        // It is preferable to get a more realistic dB range in the simulator data than the
        // dB-to-8-bit conversion accuracy.
        const MICROPHONE_MIN = 35.0;
        const MICROPHONE_MAX = 100.0;
        return Math.floor(input.soundLevel() * (MICROPHONE_MAX-MICROPHONE_MIN) / 255.0) + MICROPHONE_MIN;
    }
}
