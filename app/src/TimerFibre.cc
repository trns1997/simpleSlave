#include "TimerFibre.h"
#include "DataModel.h"

TimerFibre::TimerFibre(const char *name, board::tim_identifier tim_name)
    : Fibre(name), systick_{tim_name}
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

TimerFibre::~TimerFibre()
{
}

void TimerFibre::Init()
{
    time_ = 0;
    systick_.init();
}

void TimerFibre::Run()
{
    static DataItem timeDI(DataItemId::TIME_ID, true);
    time_++;
    timeDI.set(time_);
}
