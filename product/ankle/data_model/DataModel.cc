#include "DataModel.h"
#include "DataItem.h"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]
{
    /*[TIME_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time", .ethercat = false},

    // IMU
    /*[IMU_ACCEL_X_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_x", .ethercat = true},
    /*[IMU_ACCEL_Y_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_y", .ethercat = true},
    /*[IMU_ACCEL_Z_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_z", .ethercat = true},
    /*[IMU_GYRO_X_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_x", .ethercat = true},
    /*[IMU_GYRO_Y_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_y", .ethercat = true},
    /*[IMU_GYRO_Z_ID]*/  {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_z", .ethercat = true},
    /*[IMU_TEMP_ID]*/    {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_temp", .ethercat = true},

    // FORCE SENSORS
    /*[FS_0_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_0", .ethercat = true},
    /*[FS_1_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_1", .ethercat = true},
    /*[FS_2_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_2", .ethercat = true},
    /*[FS_3_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_3", .ethercat = true},
    /*[FS_VREF_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "fs_vref", .ethercat = true},

};
