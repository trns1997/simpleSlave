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
    const char* name;
};

class DataItem
{
public:
    DataItem(DataItemId id);
    DataItem(DataItemId id, bool writable);
    ~DataItem();

    int32_t get();
    Datagram& getDatagram();
    void set(int32_t val);
    void reset();


private:
    Datagram&   data_;
    bool        writable_ {false};
};

#endif
