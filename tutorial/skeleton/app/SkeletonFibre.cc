#include "SkeletonFibre.h"
#include "DataModel.h"

SkeletonFibre::SkeletonFibre(const char *name)
    : Fibre(name)
{
    ////////////////////////////////////////////
    // Tell Fibre Manager when this task runs //
    ////////////////////////////////////////////

    FibreManager &thread = FibreManager::getInstance(/*WHEN DO I RUN*/);
    thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
}

SkeletonFibre::~SkeletonFibre()
{
}

void SkeletonFibre::Init()
{
}

void SkeletonFibre::Run()
{
    ////////////////////////////////////////////////////
    // What does this fibre do when it the time comes //
    ////////////////////////////////////////////////////
}
