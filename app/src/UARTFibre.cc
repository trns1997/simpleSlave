#include "UARTFibre.h"
#include "DataModel.h"
#include <string.h>

UARTFibre::UARTFibre(const char *name)
    : Fibre(name)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

UARTFibre::~UARTFibre()
{
}

void UARTFibre::Init()
{
    uart_.init();
}

void UARTFibre::Run()
{
    static DataItem gyroX(DataItemId::IMU_GYRO_X_ID);
    static DataItem gyroY(DataItemId::IMU_GYRO_Y_ID);
    static DataItem gyroZ(DataItemId::IMU_GYRO_Z_ID);
    static DataItem accelX(DataItemId::IMU_ACCEL_X_ID);
    static DataItem accelY(DataItemId::IMU_ACCEL_Y_ID);
    static DataItem accelZ(DataItemId::IMU_ACCEL_Z_ID);
    static DataItem temp(DataItemId::IMU_TEMP_ID);

    static std::string teleplot = "";

    teleplot += ">GX:" + std::to_string(gyroX.get()) + "\n";
    teleplot += ">GY:" + std::to_string(gyroY.get()) + "\n";
    teleplot += ">GZ:" + std::to_string(gyroZ.get()) + "\n";
    teleplot += ">AX:" + std::to_string(accelX.get()) + "\n";
    teleplot += ">AY:" + std::to_string(accelY.get()) + "\n";
    teleplot += ">AZ:" + std::to_string(accelZ.get()) + "\n";
    teleplot += ">Temp:" + std::to_string(temp.get()) + "\n";

    uart_.sendData(teleplot.c_str(), teleplot.length());

    teleplot.clear();
}
