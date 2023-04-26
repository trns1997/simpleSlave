#include "DataModel.h"
#include "DataItem.h"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]{
    /*[WATCHDOG]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "watchdog", .ethercat = {1, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Watchdog counter", 0, NULL}},
    /*[TIME_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time", .ethercat = {2, DTYPE_UNSIGNED32, 32, ATYPE_RO, "time", 0, NULL}},
    /*[TEST_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "test", .ethercat = {3, DTYPE_UNSIGNED16, 16, ATYPE_RO, "test", 0, NULL}},
};
