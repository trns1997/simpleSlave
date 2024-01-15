#include "BMI323Fibre.h"

BMI323Fibre::BMI323Fibre(const char *name,
                   board::spi_identifier spi_name,
                   DataItemId imuGyroX,
                   DataItemId imuGyroY,
                   DataItemId imuGyroZ,
                   DataItemId imuAccelX,
                   DataItemId imuAccelY,
                   DataItemId imuAccelZ,
                   DataItemId imuTemp)
    : Fibre(name),
      boardIMU_{spi_name},
      imuGyroX_{DataItem(imuGyroX, true)},
      imuGyroY_{DataItem(imuGyroY, true)},
      imuGyroZ_{DataItem(imuGyroZ, true)},
      imuAccelX_{DataItem(imuAccelX, true)},
      imuAccelY_{DataItem(imuAccelY, true)},
      imuAccelZ_{DataItem(imuAccelZ, true)},
      imuTemp_{DataItem(imuTemp, true)}
{

    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

BMI323Fibre::~BMI323Fibre()
{
}

void BMI323Fibre::Init()
{
    boardIMU_.init();
}

void BMI323Fibre::Run()
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

void BMI323Fibre::Interrupt()
{
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
        int16_t *imuData = boardIMU_.getIMUData();

        imuGyroX_.set(imuData[0]);
        imuGyroY_.set(imuData[1]);
        imuGyroZ_.set(imuData[2]);
        imuAccelX_.set(imuData[3]);
        imuAccelY_.set(imuData[4]);
        imuAccelZ_.set(imuData[5]);
        imuTemp_.set(imuData[6]);
    }
    boardIMU_.setAvailable();
}