#include "soes_hooks.h"

#include "GPIO.h"
#include "TIMER.h"

#include "LSM6DSM.h"
#include "ForceSensor.h"

LSM6DSM boardIMU(board::SPI2_CH0);
extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    boardIMU.read();
}

ForceSensor forceSensors(board::SPI0_CH1);
extern "C" void SPI_Force_Sensor_TX_Interrupt() {}
extern "C" void SPI_Force_Sensor_RX_Interrupt()
{
    forceSensors.read();
}

void fill_input_buffer(_Rbuffer& buffer)
{
    IMUData imuData = boardIMU.getIMUData();
    buffer.ankleIMU.accelerometerX0 = imuData.accelerometer[0];
    buffer.ankleIMU.accelerometerY0 = imuData.accelerometer[1];
    buffer.ankleIMU.accelerometerZ0 = imuData.accelerometer[2];
    buffer.ankleIMU.gyroscopeX0     = imuData.gyroscope[0];
    buffer.ankleIMU.gyroscopeY0     = imuData.gyroscope[1];
    buffer.ankleIMU.gyroscopeZ0     = imuData.gyroscope[2];
    buffer.ankleIMU.temperature0    = imuData.temperatureSensor;

    ForceSensorData forceSensorData = forceSensors.getForceSensorData();
    buffer.forceSensor0 = forceSensorData.f0;
    buffer.forceSensor1 = forceSensorData.f1;
    buffer.forceSensor2 = forceSensorData.f2;
    buffer.forceSensor3 = forceSensorData.f3;
    buffer.forceSensor4 = forceSensorData.f4;
}

extern "C" void interrupt_1ms(void)
{
    // Transmit data over respective SPI at every timer tick
    boardIMU.request_read();
    forceSensors.request_read();
    static GPIO gpio_led(board::LED1);
    static int cnt = 0;

    cnt++;
    if (cnt > 1000)
    {
        gpio_led.togglePin();
        cnt = 0;
    }
}

void initTimer()
{
    TIMER timer(board::TIMER_1);
    timer.init();
}

void initIMU()
{
    boardIMU.init();
    boardIMU.configure();
}

void initForceSensors()
{
    forceSensors.init();
    forceSensors.configure();
}

int main()
{
    initGPIO();
    initIMU();
    initForceSensors();
    initTimer();
    soesInit();

    while (1)
    {
        // RUN ETHERCAT SLAVE
        runEtherCAT();
    }
    return 0;
}
