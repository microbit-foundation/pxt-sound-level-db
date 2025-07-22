#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetectorSPL.h"
#endif

namespace input {

// CODAL v0.3.0 has a working sound level in DB, but has the following issue:
// https://github.com/lancaster-university/codal-microbit-v2/issues/489
// It has been deployed to MakeCode live on the 16th of July 2025.
// The fix should be released with CODAL v0.3.2.
// Until that is released, this extension will continue to use the workaround.
#if (!defined(CODAL_VERSION_MAJOR) || !defined(CODAL_VERSION_MINOR)) || (CODAL_VERSION_MAJOR < 1 && CODAL_VERSION_MINOR < 3)
    // #warning "COMPILING PRE_REFACTOR"
    #define CODAL_PRE_SOUND_REFACTOR 1
#else
    // #warning "COMPILING REFACTORED"
    #define CODAL_PRE_SOUND_REFACTOR 0

    // There is a specific workaround for v0.3.0+.
    // https://github.com/lancaster-university/codal-microbit-v2/issues/503
    // Once fixed it should be updated to only apply it to the right CODAL version range.
    #define CODAL_0_3_X_SOUNDLEVEL_WORKAROUND 1
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
        // CODAL v0.2.x had a couple of issues in the Level Detector SPL:
        // - Min dB value was set to 52 dB (too high, it is capable to measure 30ish dB)
        // - The dB values returned were not accurate compared with external tools and older CODAL versions
        static LevelDetectorSPL *localLevelSPL = NULL;
        const int DEVICE_ID_UNUSED = 50;
        if (localLevelSPL == NULL) {
            // Lower gain and lower min value than default uBit.audio.levelSPL
            #if CODAL_PRE_SOUND_REFACTOR == 1
                localLevelSPL = new LevelDetectorSPL(*(uBit.audio.rawSplitter->createChannel()), 200.0, 1.0, 12.0, 50.0, DEVICE_ID_UNUSED, true);
            #else
                localLevelSPL = new LevelDetectorSPL(*(uBit.audio.rawSplitter->createChannel()), 200.0, 1.0, 12.0, 30.0, DEVICE_ID_UNUSED);
            #endif
        }

        #if CODAL_0_3_X_SOUNDLEVEL_WORKAROUND == 1
            // UGLY WORKAROUND FOR CODAL v0.3.0 deployed to MakeCode live.
            // A LevelDetectorSPL can lock up waiting for data, but calling it multiple
            // times in a row will eventually return values.
            // So, launch a few fibers, they all yield to each other until they all finish.
            static bool workaroundInitialised = false;
            if (!workaroundInitialised) {
                static volatile int fibersDone = 0;
                const int totalFibers = 10;
                for (int i = 0; i < totalFibers; i++) {
                    create_fiber([](void *param) {
                        uBit.sleep(1);
                        uBit.audio.levelSPL->getValue(LEVEL_DETECTOR_SPL_8BIT);
                        fibersDone++;
                        uBit.sleep(1);
                        //uBit.serial.printf("Fiber done (%d).\n", fibersDone);
                    }, (void *)fibersDone, release_fiber);
                    uBit.sleep(1);
                }
                while (fibersDone < totalFibers) {
                    uBit.sleep(10);
                }
                workaroundInitialised = true;
            }
        #endif

        int localLevelValue = localLevelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
        return preRefactorScaleLowerDbValues(localLevelValue);

        // In the future, CODAL >= v0.3.1 can just call this instead
        // return uBit.audio.levelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}

} // namespace input
