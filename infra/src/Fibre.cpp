#include "Fibre.hpp"

FibreManager::FibreManager()
{
}

FibreManager::~FibreManager()
{
}

FibreManager& FibreManager::getInstance(ThreadID id)
{
    switch (id)
    {
    default:
    case THREAD_POLLED_ID:
        static FibreManager thread_polled;
        return thread_polled;
        break;
    case THREAD_1MS_ID:
        static FibreManager thread_1ms;
        return thread_1ms;
        break;
    case THREAD_10MS_ID:
        static FibreManager thread_10ms;
        return thread_10ms;
        break;
    }
}

void FibreManager::Init()
{
    for( const auto f : fibres_)
    {
        f->Init();
    }
}

void FibreManager::Run()
{
    for( const auto f : fibres_)
    {
        f->Run();
    }
}

void FibreManager::Add(std::shared_ptr<Fibre> f)
{
    fibres_.push_back(f);
}
