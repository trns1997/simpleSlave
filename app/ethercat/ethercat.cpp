#include "Fibre.hpp"
#include "DataItem.hpp"
#include "SOES_hooks.h"


void fill_input_buffer(_Rbuffer& buffer)
{
    static DataItem imuAccelX(IMU_ACCEL_X_ID);
    static DataItem imuAccelY(IMU_ACCEL_Y_ID);
    static DataItem imuAccelZ(IMU_ACCEL_Z_ID);
    static DataItem imuGyroX(IMU_GYRO_X_ID);
    static DataItem imuGyroY(IMU_GYRO_Y_ID);
    static DataItem imuGyroZ(IMU_GYRO_Z_ID);
    static DataItem imuTemp(IMU_TEMP_ID);

    buffer.ankleIMU.accelerometerX0 = static_cast<int16_t>(imuAccelX.get());
    buffer.ankleIMU.accelerometerY0 = static_cast<int16_t>(imuAccelY.get());
    buffer.ankleIMU.accelerometerZ0 = static_cast<int16_t>(imuAccelZ.get());
    buffer.ankleIMU.gyroscopeX0     = static_cast<int16_t>(imuGyroX.get());
    buffer.ankleIMU.gyroscopeY0     = static_cast<int16_t>(imuGyroY.get());
    buffer.ankleIMU.gyroscopeZ0     = static_cast<int16_t>(imuGyroZ.get());
    buffer.ankleIMU.temperature0    = static_cast<int16_t>(imuTemp.get());

    static DataItem fs0(FS_0_ID);
    static DataItem fs1(FS_1_ID);
    static DataItem fs2(FS_2_ID);
    static DataItem fs3(FS_3_ID);
    static DataItem fs4(FS_4_ID);
    buffer.forceSensor0 = static_cast<uint32_t>(fs0.get());
    buffer.forceSensor1 = static_cast<uint32_t>(fs1.get());
    buffer.forceSensor2 = static_cast<uint32_t>(fs2.get());
    buffer.forceSensor3 = static_cast<uint32_t>(fs3.get());
    buffer.forceSensor4 = static_cast<uint32_t>(fs4.get());
}

class EtherCATFibre : public Fibre
{
public:

    EtherCATFibre(): Fibre("EtherCATFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_POLLED_ID);
        thread.Add(std::shared_ptr<Fibre>(this));
    }

    virtual void Init()
    {
        soesInit();
    }

    virtual void Run()
    {
        runEtherCAT();
    }

private:
};

static EtherCATFibre etherCATFibre;
