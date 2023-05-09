#include "GPIO.h"

#include "Threads.h"

#include "EtherCatFibre.h"
#include "IMUFibre.h"
#include "TimerFibre.h"
#include "IMUTriggerFibre.h"

#include "DataModel.h"

static IMUFibre imuFibre("IMUFibre",
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
static IMUTriggerFibre IMUTriggerFibre("IMUTriggerFibre");

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

    // GPIO gpio_led{board::LED1};

    // DataItem accelZ(DataItemId::IMU_ACCEL_Z_ID);

    while (1)
    {
        tick_polled();
        // if (accelZ.get() > 6000)
        // {
        //     gpio_led.togglePin();
        // }
    }
    return 0;
}
