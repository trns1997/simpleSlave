#include "IMUFibre.h"
#include "DataModel.h"

IMUFibre::IMUFibre(const char *name, board::spi_identifier spi_name)
    : Fibre(name), boardIMU_{spi_name}
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

IMUFibre::~IMUFibre()
{
}

void IMUFibre::Init()
{
    boardIMU_.init();
}

void IMUFibre::Run()
{
    if (boardIMU_.isBusy())
        return;

    if (boardIMU_.getState() == SPI_Slave::INITIALIZING)
    {
        boardIMU_.configure();
    }
    else if (boardIMU_.getState() == SPI_Slave::ERROR)
    {
        // TODO: Reset Board or Turn ON Error LED
    }
    else
    {
        boardIMU_.request_read();
    }
    boardIMU_.setBusy();
}

void IMUFibre::Interrupt()
{
    // TODO: MAKE THIS GENERIC
    static DataItem imuAccelX(DataItemId::IMU_ACCEL_X_ID, true);
    static DataItem imuAccelY(DataItemId::IMU_ACCEL_Y_ID, true);
    static DataItem imuAccelZ(DataItemId::IMU_ACCEL_Z_ID, true);
    static DataItem imuGyroX(DataItemId::IMU_GYRO_X_ID, true);
    static DataItem imuGyroY(DataItemId::IMU_GYRO_Y_ID, true);
    static DataItem imuGyroZ(DataItemId::IMU_GYRO_Z_ID, true);
    static DataItem imuTemp(DataItemId::IMU_TEMP_ID, true);

    if (boardIMU_.getState() == SPI_Slave::INITIALIZING)
    {
        boardIMU_.checkConfiguration();
    }
    else if (boardIMU_.getState() == SPI_Slave::INITIALIZED)
    {
        boardIMU_.setState(SPI_Slave::READY);
    }
    else if (boardIMU_.getState() == SPI_Slave::READY)
    {
        boardIMU_.read();
        IMUData imuData = boardIMU_.getIMUData();

        imuAccelX.set(imuData.accelerometer[0]);
        imuAccelY.set(imuData.accelerometer[1]);
        imuAccelZ.set(imuData.accelerometer[2]);
        imuGyroX.set(imuData.gyroscope[0]);
        imuGyroY.set(imuData.gyroscope[1]);
        imuGyroZ.set(imuData.gyroscope[2]);
        imuTemp.set(imuData.temperatureSensor);
    }
    boardIMU_.setAvailable();
}