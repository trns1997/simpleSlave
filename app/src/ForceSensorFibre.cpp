#include "ForceSensorFibre.h"
#include "DataModel.hpp"

ForceSensorFibre::ForceSensorFibre(const char *name, board::spi_identifier spi_name)
    : Fibre(name), forceSensors_{spi_name}
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
    // TODO: MAKE THIS GENERIC
    static DataItem fs0(DataItemId::FS_0_ID, true);
    static DataItem fs1(DataItemId::FS_1_ID, true);
    static DataItem fs2(DataItemId::FS_2_ID, true);
    static DataItem fs3(DataItemId::FS_3_ID, true);
    static DataItem fsVref(DataItemId::FS_VREF_ID, true);

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
            ForceSensorData forceSensorData = forceSensors_.getForceSensorData();

            fs0.set(forceSensorData.channel0);
            fs1.set(forceSensorData.channel1);
            fs2.set(forceSensorData.channel2);
            fs3.set(forceSensorData.channel4);
            fsVref.set(forceSensorData.channel3);

            forceSensors_.setAvailable();
        }
    }
}