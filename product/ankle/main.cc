#include "GPIO.h"

#include "Threads.h"

#include "EtherCatFibre.h"
#include "ForceSensorFibre.h"
#include "IMUFibre.h"
#include "TimerFibre.h"

static TimerFibre timeFibre("TimerFibre", board::TIMER_1);
static EtherCatFibre etherCatFibre("EtherCatFibre");
static IMUFibre imuFibre("IMUFibre", board::SPI_IMU);
static ForceSensorFibre forceSensorFibre("ForceSensorFibre", board::SPI_FS);

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

    while (1)
    {
        tick_polled();
    }
    return 0;
}
