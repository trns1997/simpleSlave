#include "Fibre.h"
#include "GPIO.h"

class IMUTriggerFibre : public Fibre
{
public:
    IMUTriggerFibre(const char *name);
    ~IMUTriggerFibre() override;

    void Init() override;

    void Run() override;

private:
    GPIO gpio_led_{board::LED1};
};
