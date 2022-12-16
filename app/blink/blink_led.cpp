#include "Fibre.hpp"
#include "DataItem.hpp"

#include "GPIO.h"

class BlinkLedFibre : public Fibre
{
public:

    BlinkLedFibre(): Fibre("BlinkLedFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(this));
    }

    virtual void Init()
    {}

    virtual void Run()
    {
        static GPIO gpio_led(board::LED1);
        static DataItem timeDI(TIME_ID);

        if (timeDI.get() % 1000 == 0)
        {
            gpio_led.togglePin();
        }
    }

private:
};

static BlinkLedFibre blinkLedFibre;
