#include "DataAccessor.hpp"


Datagram DataItems[] =
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

// FORCE SENSORS
[FS_0_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "fs_0"},
[FS_1_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "fs_1"},
[FS_2_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "fs_2"},
[FS_3_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "fs_3"},
[FS_4_ID]       =    {.value = 0,    .reset = 0,  .min = INT32_MIN,  .max = INT32_MAX,  .div = 1,    .name = "fs_4"},

};

DataItem::DataItem(DataItemId id)
        :   data_(DataItems[id]),
            writable_(false)
{}

DataItem::DataItem(DataItemId id, bool writable)
        :   data_(DataItems[id]),
            writable_(writable)
{}

DataItem::~DataItem()
{}

int32_t DataItem::get()
{
    return data_.value;
}

Datagram& DataItem::getDatagram()
{
    return data_;
}


void DataItem::set(int32_t val)
{
    if (writable_)
    {
        if (val >= data_.min and val <= data_.max)
        {
            data_.value = val;
        }
    }
}

void DataItem::reset()
{
    set(data_.reset);
}
