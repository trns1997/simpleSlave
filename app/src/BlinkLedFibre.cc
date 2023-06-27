#include "BlinkLedFibre.h"
#include "DataModel.h"

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

    if (timeDI.get() % 500 == 0)
    {
        switch (counter_)
        {
        case 0:
        {
            gpio_led1_.setPin();
            gpio_led2_.resetPin();
            ++counter_;
            break;
        }
        case 1:
        {
            gpio_led1_.resetPin();
            gpio_led2_.setPin();
            ++counter_;
            break;
        }
        case 2:
        {
            gpio_led1_.setPin();
            gpio_led2_.setPin();
            ++counter_;
            break;
        }
        default:
        {
            gpio_led1_.resetPin();
            gpio_led2_.resetPin();
            counter_ = 0;
            break;
        }
        }
    }
}
