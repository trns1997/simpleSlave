#include "gtest/gtest.h"

#include "Fibre.hpp"
#include "DataModel.hpp"

#include "SOES_hooks.h"

extern void fill_input_buffer(_Rbuffer& buffer);

bool isConfigured;
uint8_t data;

TEST(EtherCATTest, test_fill_buffer)
{
    DataItem imuAccelX(DataItemId::IMU_ACCEL_X_ID, true);
    DataItem imuAccelY(DataItemId::IMU_ACCEL_Y_ID, true);
    DataItem imuAccelZ(DataItemId::IMU_ACCEL_Z_ID, true);
    DataItem imuGyroX(DataItemId::IMU_GYRO_X_ID, true);
    DataItem imuGyroY(DataItemId::IMU_GYRO_Y_ID, true);
    DataItem imuGyroZ(DataItemId::IMU_GYRO_Z_ID, true);
    DataItem imuTemp(DataItemId::IMU_TEMP_ID, true);
    DataItem fs0DI(DataItemId::FS_0_ID, true);
    DataItem fs1DI(DataItemId::FS_1_ID, true);
    DataItem fs2DI(DataItemId::FS_2_ID, true);
    DataItem fs3DI(DataItemId::FS_3_ID, true);
    DataItem fsVrefDI(DataItemId::FS_VREF_ID, true);

    imuAccelX.set(10);
    imuAccelY.set(11);
    imuAccelZ.set(12);
    imuGyroX.set(20);
    imuGyroY.set(21);
    imuGyroZ.set(22);
    imuTemp.set(30);
    fs0DI.set(40);
    fs1DI.set(41);
    fs2DI.set(42);
    fs3DI.set(43);
    fsVrefDI.set(44);

    _Rbuffer buffer;
    fill_input_buffer(buffer);

    ASSERT_EQ(imuAccelX.get(), buffer.ankleIMU.accelerometerX);
    ASSERT_EQ(imuAccelY.get(), buffer.ankleIMU.accelerometerY);
    ASSERT_EQ(imuAccelZ.get(), buffer.ankleIMU.accelerometerZ);
    ASSERT_EQ(imuGyroX.get(), buffer.ankleIMU.gyroscopeX);
    ASSERT_EQ(imuGyroY.get(), buffer.ankleIMU.gyroscopeY);
    ASSERT_EQ(imuGyroZ.get(), buffer.ankleIMU.gyroscopeZ);
    ASSERT_EQ(imuTemp.get(), buffer.ankleIMU.temperature);

    ASSERT_EQ(fs0DI.get(), buffer.forceSensor0);
    ASSERT_EQ(fs1DI.get(), buffer.forceSensor1);
    ASSERT_EQ(fs2DI.get(), buffer.forceSensor2);
    ASSERT_EQ(fs3DI.get(), buffer.forceSensor3);
    ASSERT_EQ(fsVrefDI.get(), buffer.forceSensorVref);
}

TEST(EtherCATTest, test_fibre)
{
    FibreManager& thread = FibreManager::getInstance(THREAD_POLLED_ID);
    isConfigured = false;
    thread.Init();
    ASSERT_EQ(true, isConfigured);

    data = 0;
    thread.Run();
    ASSERT_EQ(1, data);
}

