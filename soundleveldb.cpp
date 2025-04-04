#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetectorSPL.h"
#endif

namespace input {
/**
* IGNORE THIS VERSION, only used for testing.
*/
// <-- During testing you can add the % sign here to export it to TS
int soundLevelDbOriginal() {
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


int scaleLowerDbValues(int value) {
    // From values about 70 db y is accurate, for values below we need to weight it
    if (value > 65) {
        return value;
    }

    const int MAX_DB = 65;
    const int MIN_DB = 30;
    const int MIN_VALUE = 51;
    const int RANGE_VALUE = MAX_DB - MIN_VALUE;
    const int RANGE_DB = MAX_DB - MIN_DB;

    // Original linear decay
    // return (int)MAX_DB - ((MAX_DB - value) * EXTRA_DECAY);

    float fraction = (float)(value - MIN_VALUE) / (float)RANGE_VALUE;
    float nonLinearFraction = sqrtf(fraction);
    return MIN_DB + (int)(RANGE_DB * nonLinearFraction);
}

/** The C++ function that return sound level in decibels  */
//% blockId=device_get_sound_level_db
int soundLevelDbC() {
#if MICROBIT_CODAL
    static LevelDetectorSPL *localLevelSPL = NULL;
    const int DEVICE_ID_UNUSED = 50;
    if (localLevelSPL == NULL) {
        // Lower gain and lower min value than default uBit.audio.levelSPL
        localLevelSPL = new LevelDetectorSPL(*(uBit.audio.rawSplitter->createChannel()), 200.0, 1.0, 12.0, 50.0, DEVICE_ID_UNUSED, true);
    }
    int localLevelValue = localLevelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
    return scaleLowerDbValues(localLevelValue);
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}

}
