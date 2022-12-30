#include "gtest/gtest.h"

#include "Fibre.hpp"
#include "DataModel.hpp"

#include "LSM6DSM.h"

bool isReadRequested;
SPI_Slave::State *stateIMU;
uint8_t data;

extern "C" void SPI_IMU_RX_Interrupt();

TEST(IMUTest, test_imu)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    DataItem accXDI(DataItemId::IMU_ACCEL_X_ID, true);
    DataItem accYDI(DataItemId::IMU_ACCEL_Y_ID, true);
    DataItem accZDI(DataItemId::IMU_ACCEL_Z_ID, true);
    DataItem gyrXDI(DataItemId::IMU_GYRO_X_ID, true);
    DataItem gyrYDI(DataItemId::IMU_GYRO_Y_ID, true);
    DataItem gyrZDI(DataItemId::IMU_GYRO_Z_ID, true);
    DataItem tempDI(DataItemId::IMU_TEMP_ID, true);

    ASSERT_EQ(SPI_Slave::INITIALIZING, *stateIMU);
    thread.Init();
    ASSERT_EQ(SPI_Slave::INITIALIZING, *stateIMU);

    ASSERT_EQ(false, isReadRequested);
    thread.Run();
    ASSERT_EQ(SPI_Slave::INITIALIZING, *stateIMU);
    ASSERT_EQ(false, isReadRequested);

    thread.Run();
    SPI_IMU_RX_Interrupt();
    ASSERT_EQ(SPI_Slave::INITIALIZED, *stateIMU);
    ASSERT_EQ(false, isReadRequested);

    SPI_IMU_RX_Interrupt();

    ASSERT_EQ(SPI_Slave::READY, *stateIMU);
    ASSERT_EQ(false, isReadRequested);

    thread.Run();
    ASSERT_EQ(true, isReadRequested);
    data = 10;
    SPI_IMU_RX_Interrupt();
    ASSERT_EQ(false, isReadRequested);
    ASSERT_EQ(10, accXDI.get());
    ASSERT_EQ(11, accYDI.get());
    ASSERT_EQ(12, accZDI.get());
    ASSERT_EQ(20, gyrXDI.get());
    ASSERT_EQ(21, gyrYDI.get());
    ASSERT_EQ(22, gyrZDI.get());
    ASSERT_EQ(30, tempDI.get());
}
