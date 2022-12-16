#include "GPIO.h"
#include "TIMER.h"

#include "Threads.hpp"

extern "C" void interrupt_1ms(void)
{
    static uint32_t cnt = 0;
    tick_1ms();
    cnt++;
    if ( cnt % 10 == 0 )
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
