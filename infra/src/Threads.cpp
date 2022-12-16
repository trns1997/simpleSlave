#include "Threads.hpp"
#include "Fibre.hpp"

void init_threads()
{
	FibreManager& thread_polled = FibreManager::getInstance(THREAD_POLLED_ID);
	thread_polled.Init();

	FibreManager& thread_1ms = FibreManager::getInstance(THREAD_1MS_ID);
	thread_1ms.Init();

	FibreManager& thread_10ms = FibreManager::getInstance(THREAD_10MS_ID);
	thread_10ms.Init();
}

void tick_polled()
{
    static FibreManager& thread_polled = FibreManager::getInstance(THREAD_POLLED_ID);
    thread_polled.Run();
}

void tick_1ms()
{
    static FibreManager& thread_1ms = FibreManager::getInstance(THREAD_1MS_ID);
    thread_1ms.Run();
}

void tick_10ms()
{
    static FibreManager& thread_10ms = FibreManager::getInstance(THREAD_10MS_ID);
    thread_10ms.Run();
}

