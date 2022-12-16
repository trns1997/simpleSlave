#include "Fibre.hpp"
#include "DataItem.hpp"
#include "SOES_hooks.h"

void fill_input_buffer(_Rbuffer &buffer)
{
    static DataItem<int16_t> imuAccelX(IMU_ACCEL_X_ID);
    static DataItem<int16_t> imuAccelY(IMU_ACCEL_Y_ID);
    static DataItem<int16_t> imuAccelZ(IMU_ACCEL_Z_ID);
    static DataItem<int16_t> imuGyroX(IMU_GYRO_X_ID);
    static DataItem<int16_t> imuGyroY(IMU_GYRO_Y_ID);
    static DataItem<int16_t> imuGyroZ(IMU_GYRO_Z_ID);
    static DataItem<int16_t> imuTemp(IMU_TEMP_ID);

    buffer.ankleIMU.accelerometerX0 = imuAccelX.get();
    buffer.ankleIMU.accelerometerY0 = imuAccelY.get();
    buffer.ankleIMU.accelerometerZ0 = imuAccelZ.get();
    buffer.ankleIMU.gyroscopeX0 = imuGyroX.get();
    buffer.ankleIMU.gyroscopeY0 = imuGyroY.get();
    buffer.ankleIMU.gyroscopeZ0 = imuGyroZ.get();
    buffer.ankleIMU.temperature0 = imuTemp.get();

    static DataItem<uint32_t> fs0(FS_0_ID);
    static DataItem<uint32_t> fs1(FS_1_ID);
    static DataItem<uint32_t> fs2(FS_2_ID);
    static DataItem<uint32_t> fs3(FS_3_ID);
    static DataItem<uint32_t> fs4(FS_4_ID);
    buffer.forceSensor0 = fs0.get();
    buffer.forceSensor1 = fs1.get();
    buffer.forceSensor2 = fs2.get();
    buffer.forceSensor3 = fs3.get();
    buffer.forceSensor4 = fs4.get();
}

class EtherCATFibre : public Fibre
{
public:
    EtherCATFibre() : Fibre("EtherCATFibre")
    {
        FibreManager &thread = FibreManager::getInstance(THREAD_POLLED_ID);
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
