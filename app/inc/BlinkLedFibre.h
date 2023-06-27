#include "Fibre.h"
#include "GPIO.h"

class BlinkLedFibre : public Fibre
{
public:
    BlinkLedFibre(const char *name);
    ~BlinkLedFibre() override;

    void Init() override;

    void Run() override;

private:
    GPIO gpio_led1_{board::LED1};
    GPIO gpio_led2_{board::LED2};
    uint16_t counter_{0};
};
