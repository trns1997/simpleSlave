#include "DataModel.h"
#include "GPIO.h"
#include "Threads.h"

/////////////////////////////////
// Add Application Fibres here //
/////////////////////////////////

//////////////////////////////////
// Add interrupt callbacks here //
//////////////////////////////////

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
