#include "gtest/gtest.h"

#include "IMUFibre.h"

#include "DataModel.h"
#include "Fibre.h"

#include "LSM6DSM.h"

bool isReadRequested;
SPI_Slave::State *stateIMU;
int16_t data;

DataItemId imuData[] = {DataItemId::IMU_GYRO_X_ID,
                        DataItemId::IMU_GYRO_Y_ID,
                        DataItemId::IMU_GYRO_Z_ID,
                        DataItemId::IMU_ACCEL_X_ID,
                        DataItemId::IMU_ACCEL_Y_ID,
                        DataItemId::IMU_ACCEL_Z_ID,
                        DataItemId::IMU_TEMP_ID};

static IMUFibre imuFibre("IMUFibre", board::SPI_IMU, imuData);

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}

TEST(IMUTest, test_imu)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    DataItem gyrXDI(DataItemId::IMU_GYRO_X_ID);
    DataItem gyrYDI(DataItemId::IMU_GYRO_Y_ID);
    DataItem gyrZDI(DataItemId::IMU_GYRO_Z_ID);
    DataItem accXDI(DataItemId::IMU_ACCEL_X_ID);
    DataItem accYDI(DataItemId::IMU_ACCEL_Y_ID);
    DataItem accZDI(DataItemId::IMU_ACCEL_Z_ID);
    DataItem tempDI(DataItemId::IMU_TEMP_ID);

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
    ASSERT_EQ(10, gyrXDI.get());
    ASSERT_EQ(11, gyrYDI.get());
    ASSERT_EQ(12, gyrZDI.get());
    ASSERT_EQ(20, accXDI.get());
    ASSERT_EQ(21, accYDI.get());
    ASSERT_EQ(22, accZDI.get());
    ASSERT_EQ(30, tempDI.get());
}
