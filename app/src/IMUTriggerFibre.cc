#include "IMUTriggerFibre.h"
#include "DataModel.h"

IMUTriggerFibre::IMUTriggerFibre(const char *name)
    : Fibre(name)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_POLLED_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

IMUTriggerFibre::~IMUTriggerFibre()
{
}

void IMUTriggerFibre::Init()
{
}

void IMUTriggerFibre::Run()
{
    static DataItem accelZ(DataItemId::IMU_ACCEL_Z_ID);

    if (accelZ.get() > 6000)
    {
        gpio_led_.togglePin();
    }
}
