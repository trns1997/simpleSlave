#include "DataModel.hpp"
#include "DataItem.hpp"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*[TIME_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time"},

    // IMU
    /*[IMU_ACCEL_X_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_x"},
    /*[IMU_ACCEL_Y_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_y"},
    /*[IMU_ACCEL_Z_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_z"},
    /*[IMU_GYRO_X_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_x"},
    /*[IMU_GYRO_Y_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_y"},
    /*[IMU_GYRO_Z_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_z"},
    /*[IMU_TEMP_ID]*/    {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_temp"},

};

