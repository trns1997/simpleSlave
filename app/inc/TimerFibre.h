#include "Fibre.hpp"
#include "GPIO.h"

class TimerFibre : public Fibre
{
public:
    TimerFibre(const char *name);
    ~TimerFibre() override;

    void Init() override;

    void Run() override;

private:
    int32_t time_{0};
};
