#include "Fibre.hpp"
#include "DataModel.hpp"

class TimeFibre : public Fibre
{
public:

    TimeFibre(): Fibre("TimeFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
    }

    virtual void Init()
    {
        time_ = 0;
    }

    virtual void Run()
    {
        static DataItem timeDI(DataItemId::TIME_ID, true);
        time_++;
        timeDI.set(time_);
    }

private:
    int32_t time_ {0};
};

static TimeFibre timeFibre;
