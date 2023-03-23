#include "ForceSensorFibre.h"

ForceSensorFibre::ForceSensorFibre(const char *name, board::spi_identifier spi_name, DataItemId *dataItems)
    : Fibre(name),
      forceSensors_{spi_name},
      dataItems_{dataItems}
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

ForceSensorFibre::~ForceSensorFibre()
{
}

void ForceSensorFibre::Init()
{
    forceSensors_.init();
}

void ForceSensorFibre::Run()
{
    if (forceSensors_.isBusy())
        return;

    if (forceSensors_.getState() == SPI_Slave::INITIALIZING)
    {
        forceSensors_.configure();
    }
    else if (forceSensors_.getState() == SPI_Slave::ERROR)
    {
        // TODO: Reset Board or Turn ON Error LED
    }
    else
    {
        forceSensors_.request_read();
    }
    forceSensors_.setBusy();
}

void ForceSensorFibre::Interrupt()
{
    static DataItem items[] = {
        DataItem(dataItems_[0], true),
        DataItem(dataItems_[1], true),
        DataItem(dataItems_[2], true),
        DataItem(dataItems_[3], true),
        DataItem(dataItems_[4], true)};

    if (forceSensors_.getState() == SPI_Slave::INITIALIZING)
    {
        forceSensors_.checkConfiguration();
        forceSensors_.setAvailable();
    }
    else if (forceSensors_.getState() == SPI_Slave::INITIALIZED)
    {
        forceSensors_.setState(SPI_Slave::READY);
        forceSensors_.setAvailable();
    }
    else if (forceSensors_.getState() == SPI_Slave::READY)
    {
        forceSensors_.read();

        if (forceSensors_.isReadingFinished())
        {
            uint16_t *forceSensorData = forceSensors_.getForceSensorData();

            for (uint16_t i = 0; i < sizeof(items) / sizeof(items[0]); ++i)
            {
                items[i].set(forceSensorData[i]);
            }

            forceSensors_.setAvailable();
        }
    }
}