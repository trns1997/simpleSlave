#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include "DataItem.hpp"

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

    imu ankleIMU;

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

enum class DataItemId
{
    TIME_ID = 0,
};

#endif
