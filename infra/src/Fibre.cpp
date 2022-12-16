#include "Fibre.hpp"

FibreManager::FibreManager()
{}

FibreManager::~FibreManager()
{
    fibres_.clear();
}

FibreManager& FibreManager::getInstance(ThreadID id)
{
    static FibreManager thread_polled;
    static FibreManager thread_1ms;
    static FibreManager thread_10ms;

    switch (id)
    {
    default:
    case THREAD_POLLED_ID:
        return thread_polled;
        break;
    case THREAD_1MS_ID:
        return thread_1ms;
        break;
    case THREAD_10MS_ID:
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
