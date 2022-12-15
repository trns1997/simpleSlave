#include "Fibre.hpp"
#include "DataAccessor.hpp"

#include "ForceSensor.h"

class FootSensorFibre : public Fibre
{
public:

    FootSensorFibre(): Fibre("FootSensorFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(this));
    }

    virtual void Init()
    {
        forceSensors.init();
        forceSensors.configure();
    }

    virtual void Run()
    {
        forceSensors.request_read();
    }

    void Interrupt()
    {
        static DataItem fs0(FS_0_ID, true);
        static DataItem fs1(FS_1_ID, true);
        static DataItem fs2(FS_2_ID, true);
        static DataItem fs3(FS_3_ID, true);
        static DataItem fs4(FS_4_ID, true);

        forceSensors.read();
        ForceSensorData forceSensorData = forceSensors.getForceSensorData();

        fs0.set(forceSensorData.f0);
        fs1.set(forceSensorData.f1);
        fs2.set(forceSensorData.f2);
        fs3.set(forceSensorData.f3);
        fs4.set(forceSensorData.f4);
    }

private:
    ForceSensor forceSensors{board::SPI0_CH1};
};

static FootSensorFibre footSensorFibre;

extern "C" void SPI_Force_Sensor_TX_Interrupt() {}
extern "C" void SPI_Force_Sensor_RX_Interrupt()
{
    footSensorFibre.Interrupt();
}

