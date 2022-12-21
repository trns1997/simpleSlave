#include "DataModel.hpp"
#include "DataItem.hpp"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*IMU_ACCEL_X_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "accX"},
    /*IMU_ACCEL_Y_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "accY"},
    /*IMU_ACCEL_Y_ID */ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "accZ"},
    /*IMU_GYRO_X_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "gyrX"},
    /*IMU_GYRO_Y_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "gyrY"},
    /*IMU_GYRO_Z_ID */  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "gyrZ"},
    /*IMU_TEMP_ID */    {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "temp"},
};
