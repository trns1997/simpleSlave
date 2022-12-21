#include "DataModel.hpp"
#include "DataItem.hpp"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*TIME_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "time"},
};
