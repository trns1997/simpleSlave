#include "DataModel.hpp"
#include "DataItem.hpp"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*IMU_ACCEL_X_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs0"},
    /*IMU_ACCEL_Y_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs1"},
    /*IMU_ACCEL_Y_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs2"},
    /*IMU_GYRO_X_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs3"},
    /*IMU_GYRO_Y_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs4"},
    /*IMU_GYRO_Z_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs4"},
    /*IMU_TEMP_ID */    {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs4"},
};
