#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include "DataItem.h"

enum class DataItemId
{
    WATCHDOG = 0,

    TIME_ID,

    // FORCE SENSOR
    FS_0_ID,
    FS_1_ID,
    FS_2_ID,
    FS_VREF_ID,
    FS_3_ID,

    TIME_0,
    FS_1_0,
    FS_2_0,
    FS_3_0,

    TIME_1,
    FS_1_1,
    FS_2_1,
    FS_3_1,

    TIME_2,
    FS_1_2,
    FS_2_2,
    FS_3_2,

    TIME_3,
    FS_1_3,
    FS_2_3,
    FS_3_3,

    TIME_4,
    FS_1_4,
    FS_2_4,
    FS_3_4,

    TIME_5,
    FS_1_5,
    FS_2_5,
    FS_3_5,

    TIME_6,
    FS_1_6,
    FS_2_6,
    FS_3_6,

    TIME_7,
    FS_1_7,
    FS_2_7,
    FS_3_7,

    TIME_8,
    FS_1_8,
    FS_2_8,
    FS_3_8,

    TIME_9,
    FS_1_9,
    FS_2_9,
    FS_3_9
};

#endif
