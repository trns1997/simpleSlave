#include "DataModel.hpp"
#include "DataItem.hpp"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*FS_0_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs0"},
    /*FS_1_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs1"},
    /*FS_2_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs2"},
    /*FS_3_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs3"},
    /*FS_4_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs4"},
};
