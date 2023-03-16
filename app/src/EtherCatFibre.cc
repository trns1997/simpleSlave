#include "EtherCatFibre.h"
#include "SOES_hooks.h"

EtherCatFibre::EtherCatFibre(const char *name)
    : Fibre(name)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_POLLED_ID);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

EtherCatFibre::~EtherCatFibre()
{
}

void EtherCatFibre::Init()
{
    soesInit();
}

void EtherCatFibre::Run()
{
    runEtherCAT();
}
