#include "BlinkLedFibre.h"
#include "DataModel.hpp"

BlinkLedFibre::BlinkLedFibre(const char *name)
    : Fibre(name)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

BlinkLedFibre::~BlinkLedFibre()
{
}

void BlinkLedFibre::Init()
{
}

void BlinkLedFibre::Run()
{
    static DataItem timeDI(DataItemId::TIME_ID);

    if (timeDI.get() % 1000 == 0)
    {
        gpio_led_.togglePin();
    }
}
