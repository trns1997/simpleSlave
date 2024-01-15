#include "GPIO.h"

#include "Threads.h"

#include "BlinkLedFibre.h"
#include "EtherCatFibre.h"
#include "BMI088Fibre.h"
#include "TimerFibre.h"

#include "DataModel.h"

static BlinkLedFibre blinkLedFibre("BlinkedFiber");
static BMI088Fibre imuFibre("IMUFibre",
                            board::SPI_IMU,
                            DataItemId::IMU_GYRO_X_ID,
                            DataItemId::IMU_GYRO_Y_ID,
                            DataItemId::IMU_GYRO_Z_ID,
                            DataItemId::IMU_ACCEL_X_ID,
                            DataItemId::IMU_ACCEL_Y_ID,
                            DataItemId::IMU_ACCEL_Z_ID,
                            DataItemId::IMU_TEMP_ID);
static TimerFibre timeFibre("TimerFibre", board::TIMER_1);
static EtherCatFibre etherCatFibre("EtherCatFibre");

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}

extern "C" void interrupt_1ms(void)
{
    tick_1ms();
}

int main()
{
    initGPIO();

    init_threads();

    while (1)
    {
        tick_polled();
    }
    return 0;
}
