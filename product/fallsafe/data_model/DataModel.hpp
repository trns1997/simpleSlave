#ifndef ARC_DATAACCESSOR_HPP
#define ARC_DATAACCESSOR_HPP

#include <stdint.h>

enum DataItemId
{
    // Measurements
    TIME_ID             = 0,

    // IMU
    IMU_ACCEL_0_ID,
    IMU_ACCEL_1_ID,
    IMU_ACCEL_2_ID,
    IMU_GYRO_0_ID,
    IMU_GYRO_1_ID,
    IMU_GYRO_2_ID,
    IMU_TEMP_ID,
};

struct Datagram
{
    int32_t value;
    int32_t reset;
    int32_t min;
    int32_t max;
    int32_t div;
    const char* name;
};

static Datagram DataItems[] =
{
// Measurements
[TIME_ID]          =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1000,    .name = "time"},

// IMU
[IMU_ACCEL_0_ID]    =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_accel_0"},
[IMU_ACCEL_1_ID]    =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_accel_1"},
[IMU_ACCEL_2_ID]    =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_accel_2"},
[IMU_GYRO_0_ID]     =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_gyro_0"},
[IMU_GYRO_1_ID]     =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_gyro_1"},
[IMU_GYRO_2_ID]     =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_gyro_2"},
[IMU_TEMP_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "imu_temp"},

};

#endif
