#include "GPIO.h"
#include "TIMER.h"

#include "Threads.hpp"

#include "EtherCatFibre.h"
#include "ForceSensorFibre.h"
#include "IMUFibre.h"
#include "TimerFibre.h"

static TimerFibre timeFibre("TimerFibre");
static EtherCatFibre etherCatFibre("EtherCatFibre");
static IMUFibre imuFibre("IMUFibre");
static ForceSensorFibre forceSensorFibre("ForceSensorFibre");

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}

extern "C" void SPI_Force_Sensor_TX_Interrupt() {}
extern "C" void SPI_Force_Sensor_RX_Interrupt()
{
    forceSensorFibre.Interrupt();
}

extern "C" void interrupt_1ms(void)
{
    static uint32_t cnt = 0;
    tick_1ms();
    cnt++;
    if (cnt % 10 == 0)
    {
        tick_10ms();
        cnt = 0;
    }
}

int main()
{
    initGPIO();

    init_threads();

    TIMER systick(board::TIMER_1);
    systick.init();

    while (1)
    {
        tick_polled();
    }
    return 0;
}
