#include "DataModel.h"
#include "DataItem.h"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*TEST_DATA_ID*/ {.value = 0, .reset = 10, .min = -10, .max = 20, .div = 1000, .name = "time"},
};

