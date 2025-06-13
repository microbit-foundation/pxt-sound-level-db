#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetectorSPL.h"
#endif

namespace input {

#if (!defined(CODAL_VERSION_MAJOR) || !defined(CODAL_VERSION_MINOR)) || (CODAL_VERSION_MAJOR < 1 && CODAL_VERSION_MINOR < 3)
    // #warning "COMPILING PRE_REFACTOR"
    #define CODAL_PRE_SOUND_REFACTOR 1
#else
    // #warning "COMPILING REFACTORED"
    #define CODAL_PRE_SOUND_REFACTOR 0
#endif

int preRefactorScaleLowerDbValues(int value) {
    // From values about 65-70 db y is accurate, for values below we need to weight it
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

/** The C++ function that returns sound level in decibels  */
//% blockId=device_get_sound_level_db
int soundLevelDbC() {
#if MICROBIT_CODAL
    #if CODAL_PRE_SOUND_REFACTOR == 1
        // CODAL had a couple of issues in the Level Detector SPL:
        // - Min dB value was set to 52 dB (too high, it is capable to measure 30ish dB)
        // - The dB values returned were not accurate compared with external tools and older CODAL versions
        static LevelDetectorSPL *localLevelSPL = NULL;
        const int DEVICE_ID_UNUSED = 50;
        if (localLevelSPL == NULL) {
            // Lower gain and lower min value than default uBit.audio.levelSPL
            localLevelSPL = new LevelDetectorSPL(*(uBit.audio.rawSplitter->createChannel()), 200.0, 1.0, 12.0, 50.0, DEVICE_ID_UNUSED, true);
        }
        int localLevelValue = localLevelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
        return preRefactorScaleLowerDbValues(localLevelValue);
    #else
        // The CODAL refactor from v0.3.0 fixes these issues
        return uBit.audio.levelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
    #endif
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}

}
