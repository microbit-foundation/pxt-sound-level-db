#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetector.h"
#include "LevelDetectorSPL.h"
#endif

#define MICROPHONE_MIN 52.0f
#define MICROPHONE_MAX 120.0f

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
    LevelDetectorSPL* level = uBit.audio.levelSPL;
    if (NULL == level)
        return 0;
    const int micValue = level->getValue();
    const int scaled = max(MICROPHONE_MIN, min(micValue, MICROPHONE_MAX)) - MICROPHONE_MIN;
    return min(0xff, scaled * 0xff / (MICROPHONE_MAX - MICROPHONE_MIN));
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}
}
