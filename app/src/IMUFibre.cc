#include "IMUFibre.h"

IMUFibre::IMUFibre(const char *name, board::spi_identifier spi_name, DataItemId *dataItems)
    : Fibre(name),
      boardIMU_{spi_name},
      dataItems_{dataItems}
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
    static DataItem items[] = {
        DataItem(dataItems_[0], true),
        DataItem(dataItems_[1], true),
        DataItem(dataItems_[2], true),
        DataItem(dataItems_[3], true),
        DataItem(dataItems_[4], true),
        DataItem(dataItems_[5], true),
        DataItem(dataItems_[6], true)};

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
        for (uint16_t i = 0; i < sizeof(items) / sizeof(items[0]); ++i)
        {
            items[i].set(imuData[i]);
        }
    }
    boardIMU_.setAvailable();
}