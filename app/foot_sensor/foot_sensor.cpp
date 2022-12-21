#include "Fibre.hpp"
#include "DataModel.hpp"

#include "ForceSensor.h"

class FootSensorFibre : public Fibre
{
public:

    FootSensorFibre(): Fibre("FootSensorFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
    }

    ~FootSensorFibre() override {}

    void Init() override
    {
        forceSensors_.init();
        forceSensors_.configure();
    }

    void Run() override
    {
        forceSensors_.request_read();
    }

    void Interrupt()
    {
        static DataItem fs0(DataItemId::FS_0_ID, true);
        static DataItem fs1(DataItemId::FS_1_ID, true);
        static DataItem fs2(DataItemId::FS_2_ID, true);
        static DataItem fs3(DataItemId::FS_3_ID, true);
        static DataItem fsVref(DataItemId::FS_VREF_ID, true);

        forceSensors_.read();
        ForceSensorData forceSensorData = forceSensors_.getForceSensorData();

        fs0.set(forceSensorData.channel0);
        fs1.set(forceSensorData.channel1);
        fs2.set(forceSensorData.channel2);
        fs3.set(forceSensorData.channel4);
        fsVref.set(forceSensorData.channel3);
    }

private:
    ForceSensor forceSensors_{board::SPI0_CH1};
};

static FootSensorFibre footSensorFibre;

extern "C" void SPI_Force_Sensor_TX_Interrupt() {}
extern "C" void SPI_Force_Sensor_RX_Interrupt()
{
    footSensorFibre.Interrupt();
}

