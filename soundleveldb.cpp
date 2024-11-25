#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetector.h"
#include "LevelDetectorSPL.h"
#endif

namespace input {
/**
* Reads the loudness through the microphone in decibels (dB).
*/
//% blockId=device_get_sound_level_db block="sound level (dB)"
//% parts="microphone"
//% weight=34 blockGap=8
//% advanced=true
//% group="micro:bit (V2)"
int soundLevelDb() {
#if MICROBIT_CODAL
    int originalUnit = uBit.audio.levelSPL->unit;
    float soundDb = uBit.audio.levelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
    uBit.audio.levelSPL->unit = originalUnit;
    return (int)soundDb;
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}
}
