#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include "DataItem.hpp"

enum class DataItemId
{
    TIME_ID = 0,

    // IMU
    IMU_ACCEL_X_ID,
    IMU_ACCEL_Y_ID,
    IMU_ACCEL_Z_ID,
    IMU_GYRO_X_ID,
    IMU_GYRO_Y_ID,
    IMU_GYRO_Z_ID,
    IMU_TEMP_ID,
};

#endif
