#include "EtherCatFibre.h"
#include "DataModel.hpp"
#include "SOES_hooks.h"

void fill_input_buffer(_Rbuffer &buffer)
{
    // TODO: MAKE THIS GENERIC
    static DataItem imuAccelX(DataItemId::IMU_ACCEL_X_ID);
    static DataItem imuAccelY(DataItemId::IMU_ACCEL_Y_ID);
    static DataItem imuAccelZ(DataItemId::IMU_ACCEL_Z_ID);
    static DataItem imuGyroX(DataItemId::IMU_GYRO_X_ID);
    static DataItem imuGyroY(DataItemId::IMU_GYRO_Y_ID);
    static DataItem imuGyroZ(DataItemId::IMU_GYRO_Z_ID);
    static DataItem imuTemp(DataItemId::IMU_TEMP_ID);

    buffer.ankleIMU.accelerometerX = static_cast<int16_t>(imuAccelX.get());
    buffer.ankleIMU.accelerometerY = static_cast<int16_t>(imuAccelY.get());
    buffer.ankleIMU.accelerometerZ = static_cast<int16_t>(imuAccelZ.get());
    buffer.ankleIMU.gyroscopeX = static_cast<int16_t>(imuGyroX.get());
    buffer.ankleIMU.gyroscopeY = static_cast<int16_t>(imuGyroY.get());
    buffer.ankleIMU.gyroscopeZ = static_cast<int16_t>(imuGyroZ.get());
    buffer.ankleIMU.temperature = static_cast<int16_t>(imuTemp.get());

    static DataItem fs0(DataItemId::FS_0_ID);
    static DataItem fs1(DataItemId::FS_1_ID);
    static DataItem fs2(DataItemId::FS_2_ID);
    static DataItem fs3(DataItemId::FS_3_ID);
    static DataItem fsVref(DataItemId::FS_VREF_ID);
    buffer.forceSensor0 = static_cast<uint16_t>(fs0.get());
    buffer.forceSensor1 = static_cast<uint16_t>(fs1.get());
    buffer.forceSensor2 = static_cast<uint16_t>(fs2.get());
    buffer.forceSensor3 = static_cast<uint16_t>(fs3.get());
    buffer.forceSensorVref = static_cast<uint16_t>(fsVref.get());
}

EtherCatFibre::EtherCatFibre(const char *name)
    : Fibre(name)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_POLLED_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

EtherCatFibre::~EtherCatFibre()
{
}

void EtherCatFibre::Init()
{
    soesInit();
}

void EtherCatFibre::Run()
{
    runEtherCAT();
}
