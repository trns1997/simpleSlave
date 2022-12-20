#include "Fibre.hpp"
#include "DataModel.hpp"

#include "GPIO.h"

class BlinkLedFibre : public Fibre
{
public:

    BlinkLedFibre(): Fibre("BlinkLedFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
    }
    ~BlinkLedFibre() override {}

    void Init() override
    {}

    void Run() override
    {
        static DataItem timeDI(DataItemId::TIME_ID);

        if (timeDI.get() % 1000 == 0)
        {
            gpio_led_.togglePin();
        }
    }

private:

    GPIO gpio_led_ {board::LED1};
};

static BlinkLedFibre blinkLedFibre;
