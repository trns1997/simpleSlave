#ifndef ARC_DATAACCESSOR_HPP
#define ARC_DATAACCESSOR_HPP

#include <stdint.h>

enum DataItemId
{
    // Measurements
    TIME_ID = 0,

    // IMU
    IMU_ACCEL_X_ID,
    IMU_ACCEL_Y_ID,
    IMU_ACCEL_Z_ID,
    IMU_GYRO_X_ID,
    IMU_GYRO_Y_ID,
    IMU_GYRO_Z_ID,
    IMU_TEMP_ID,

    // FORCE SENSOR
    FS_0_ID,
    FS_1_ID,
    FS_2_ID,
    FS_3_ID,
    FS_4_ID

};

struct Datagram
{
    int32_t value;
    int32_t reset;
    int32_t min;
    int32_t max;
    int32_t div;
    const char *name;
};

static Datagram DataItems[] =
    {
        // Measurements
        [TIME_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time"},

        // IMU
        [IMU_ACCEL_X_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_x"},
        [IMU_ACCEL_Y_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_y"},
        [IMU_ACCEL_Z_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_z"},
        [IMU_GYRO_X_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_x"},
        [IMU_GYRO_Y_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_y"},
        [IMU_GYRO_Z_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_z"},
        [IMU_TEMP_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_temp"},

        // FORCE SENSORS
        [FS_0_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_0"},
        [FS_1_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_1"},
        [FS_2_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_2"},
        [FS_3_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_3"},
        [FS_4_ID] = {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_4"},

};

#endif
