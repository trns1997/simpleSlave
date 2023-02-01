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

    // FORCE SENSOR
    FS_0_ID,
    FS_1_ID,
    FS_2_ID,
    FS_3_ID,
    FS_VREF_ID
};

struct imu
{
    // current IMU data
    int16_t accelerometerX; // raw data
    int16_t accelerometerY;
    int16_t accelerometerZ;

    int16_t gyroscopeX; // raw data.
    int16_t gyroscopeY;
    int16_t gyroscopeZ;

    int16_t temperature; // Celsius degrees
} __attribute__((packed));

struct readBuffer
{
    uint16_t watchdogCounter;

    imu footIMU;

    uint16_t forceSensor0;
    uint16_t forceSensor1;
    uint16_t forceSensor2;
    uint16_t forceSensor3;
    uint16_t forceSensorVref;

    uint16_t boardStatus;
} __attribute__((packed));

struct writeBuffer
{
    uint16_t watchdogCounter;
} __attribute__((packed));

struct counterBuffer
{
    uint32_t reset_counter;
} __attribute__((packed));

#endif
