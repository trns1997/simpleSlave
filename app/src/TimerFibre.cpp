#include "TimerFibre.h"
#include "DataModel.hpp"

TimerFibre::TimerFibre(const char *name)
    : Fibre(name)
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
}

void TimerFibre::Run()
{
    static DataItem timeDI(DataItemId::TIME_ID, true);
    time_++;
    timeDI.set(time_);
}
