#include "GPIO.h"
#include "Threads.hpp"

#include "BlinkLedFibre.h"
#include "TimerFibre.h"

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

    static TimerFibre timeFibre("TimerFibre", board::TIMER_1);
    static BlinkLedFibre blinkLedFibre("BlinkedFiber");

    init_threads();

    while (1)
    {
        tick_polled();
    }
    return 0;
}
