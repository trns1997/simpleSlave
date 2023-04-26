#include "DataModel.h"
#include "DataItem.h"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]{
    /*[WATCHDOG]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "watchdog", .ethercat = {1, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Watchdog counter", 0, NULL}},

    /*[TIME_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time"},

    // FORCE SENSORS
    /*[FS_0_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_0"},
    /*[FS_1_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_1"},
    /*[FS_2_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_2"},
    /*[FS_VREF_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_vref"},
    /*[FS_3_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_3"},

    // FORCE SENSORS 0
    /*[TIME_0]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {2, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_0]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {3, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_0]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {4, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_0]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {5, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 1
    /*[TIME_1]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {6, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_1]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {7, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_1]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {8, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_1]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {9, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 2
    /*[TIME_2]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {10, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_2]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {11, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_2]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {12, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_2]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {13, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 3
    /*[TIME_3]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {14, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_3]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {15, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_3]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {16, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_3]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {17, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 4
    /*[TIME_4]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {18, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_4]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {19, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_4]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {20, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_4]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {21, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 5
    /*[TIME_5]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {22, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_5]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {23, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_5]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {24, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_5]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {25, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 6
    /*[TIME_6]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {26, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_6]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {27, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_6]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {28, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_6]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {29, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 7
    /*[TIME_7]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {30, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_7]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {31, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_7]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {32, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_7]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {33, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 8
    /*[TIME_8]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {34, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_8]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {35, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_8]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {36, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_8]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {37, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

    // FORCE SENSORS 9
    /*[TIME_9]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time", .ethercat = {38, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[FS_1_9]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {39, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_2_9]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {40, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},
    /*[FS_3_9]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs", .ethercat = {41, DTYPE_UNSIGNED16, 16, ATYPE_RO, "fs", 0, NULL}},

};
