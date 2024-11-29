// Auto-generated. Do not edit.
declare namespace input {

    /**
     * IGNORE THIS VERSION.
     */
    //% shim=input::soundLevelDbOriginal
    function soundLevelDbOriginal(): int32;

    /**
     * Reads the loudness through the microphone in decibels (dB).
     */
    //% blockId=device_get_sound_level_db
    //% block="sound level (dB)"
    //% parts="microphone"
    //% weight=13 blockGap=8
    //% advanced=true
    //% group="micro:bit (V2)" shim=input::soundLevelDbC
    function soundLevelDbC(): int32;
}

// Auto-generated. Do not edit. Really.
