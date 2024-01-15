#include "DataModel.h"
#include "DataItem.h"

Datagram DataItem::s_integer[MAX_DATA_ITEMS]{
    /*[WATCHDOG]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "watchdog", .ethercat = {1, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Watchdog counter", 0, NULL}},

    /*[TIME_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1000, .name = "time"},

    // IMU
    /*[IMU_ACCEL_X_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_x", .ethercat = {2, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_accel_x", 0, NULL}},
    /*[IMU_ACCEL_Y_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_y", .ethercat = {3, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_accel_y", 0, NULL}},
    /*[IMU_ACCEL_Z_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_accel_z", .ethercat = {4, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_accel_z", 0, NULL}},
    /*[IMU_GYRO_X_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_x", .ethercat = {5, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_gyro_x", 0, NULL}},
    /*[IMU_GYRO_Y_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_y", .ethercat = {6, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_gyro_y", 0, NULL}},
    /*[IMU_GYRO_Z_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_gyro_z", .ethercat = {7, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_gyro_z", 0, NULL}},
    /*[IMU_TEMP_ID]*/ {.value = 0, .reset = 0, .min = INT32_MIN, .max = INT32_MAX, .div = 1, .name = "imu_temp", .ethercat = {8, DTYPE_INTEGER16, 16, ATYPE_RO, "imu_temp", 0, NULL}}};
