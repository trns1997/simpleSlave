#include "Fibre.h"
#include "TIMER.h"

class TimerFibre : public Fibre
{
public:
    TimerFibre(const char *name, board::tim_identifier tim_name);
    ~TimerFibre() override;

    void Init() override;

    void Run() override;

private:
    TIMER systick_;
    int32_t time_{0};
};
