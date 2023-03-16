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
    GPIO gpio_led_{board::LED1};
};
