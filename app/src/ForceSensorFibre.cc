#include "ForceSensorFibre.h"

ForceSensorFibre::ForceSensorFibre(const char *name,
                                   board::spi_identifier spi_name,
                                   DataItemId FS0,
                                   DataItemId FS1,
                                   DataItemId FS2,
                                   DataItemId FSVref,
                                   DataItemId FS3)
    : Fibre(name),
      forceSensors_{spi_name},
      FS0_{DataItem(FS0, true)},
      FS1_{DataItem(FS1, true)},
      FS2_{DataItem(FS2, true)},
      FSVref_{DataItem(FSVref, true)},
      FS3_{DataItem(FS3, true)}
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

            FS0_.set(forceSensorData[0]);
            FS1_.set(forceSensorData[1]);
            FS2_.set(forceSensorData[2]);
            FSVref_.set(forceSensorData[3]);
            FS3_.set(forceSensorData[4]);

            forceSensors_.setAvailable();
        }
    }
}