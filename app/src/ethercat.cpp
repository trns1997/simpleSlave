#include "Fibre.hpp"
#include "DataItem.hpp"
#include "SOES_hooks.h"


void fill_input_buffer(_Rbuffer& buffer)
{
    static DataItem imuAccel0(IMU_ACCEL_0_ID);
    static DataItem imuAccel1(IMU_ACCEL_1_ID);
    static DataItem imuAccel2(IMU_ACCEL_2_ID);
    static DataItem imuGyro0(IMU_GYRO_0_ID);
    static DataItem imuGyro1(IMU_GYRO_1_ID);
    static DataItem imuGyro2(IMU_GYRO_2_ID);
    static DataItem imuTemp(IMU_TEMP_ID);

    buffer.ankleIMU.accelerometerX0 = static_cast<int16_t>(imuAccel0.get());
    buffer.ankleIMU.accelerometerY0 = static_cast<int16_t>(imuAccel1.get());
    buffer.ankleIMU.accelerometerZ0 = static_cast<int16_t>(imuAccel2.get());
    buffer.ankleIMU.gyroscopeX0     = static_cast<int16_t>(imuGyro0.get());
    buffer.ankleIMU.gyroscopeY0     = static_cast<int16_t>(imuGyro1.get());
    buffer.ankleIMU.gyroscopeZ0     = static_cast<int16_t>(imuGyro2.get());
    buffer.ankleIMU.temperature0    = static_cast<int16_t>(imuTemp.get());

    static DataItem fs0(FS_0_ID);
    static DataItem fs1(FS_1_ID);
    static DataItem fs2(FS_2_ID);
    static DataItem fs3(FS_3_ID);
    static DataItem fs4(FS_4_ID);
    buffer.forceSensor0 = static_cast<int16_t>(fs0.get());
    buffer.forceSensor1 = static_cast<int16_t>(fs1.get());
    buffer.forceSensor2 = static_cast<int16_t>(fs2.get());
    buffer.forceSensor3 = static_cast<int16_t>(fs3.get());
    buffer.forceSensor4 = static_cast<int16_t>(fs4.get());
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
