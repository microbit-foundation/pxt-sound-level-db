#include <pxt.h>

#if MICROBIT_CODAL
#include "LevelDetectorSPL.h"
#endif

namespace input {
/**
* IGNORE THIS VERSION.
*/
//%
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


int soundLevelDbF(int value) {
    // From values about 70 db y is accurate, for values below we need to weight it
    if (value > 65) {
        return value;
    }

    const int MIN_DB = 36;
    const int MIN_DB_Y = 52;
    const int MAX_DB = 66;
    const int RANGE_DB = MAX_DB - MIN_DB;
    const int RANGE_DB_Y = MAX_DB - MIN_DB_Y;
    const float EXTRA_DECAY = (float)RANGE_DB / (float)RANGE_DB_Y;

    // Between Y being 64 and 52 we decay three times faster towards 28
    return (int)MAX_DB - ((MAX_DB - value) * EXTRA_DECAY);
}

static LevelDetectorSPL *localLevelSPL = NULL;

#define DEVICE_ID_UNUSED 50


//% blockId=device_get_sound_level_db
int soundLevelDbC() {
#if MICROBIT_CODAL
    if (localLevelSPL == NULL) {
        localLevelSPL = new LevelDetectorSPL(*(uBit.audio.rawSplitter->createChannel()), 200.0, 1.0, 12.0, 50.0, DEVICE_ID_UNUSED, true);
        //localLevelSPL = new LevelDetectorSPL(uBit.audio.processor->output, 200.0, 1.0, 1.0, 30.0, DEVICE_ID_UNUSED, true);
    }
    int detector_db = (int)localLevelSPL->getValue(LEVEL_DETECTOR_SPL_DB);
    return soundLevelDbF(detector_db);
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
    return 0;
#endif
}

}
