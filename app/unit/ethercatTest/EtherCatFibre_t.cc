#include "gtest/gtest.h"

#include "EtherCatFibre.h"

#include "DataModel.h"
#include "Fibre.h"

bool isConfigured;
uint8_t data;

TEST(EtherCATTest, test_fibre)
{
    static EtherCatFibre etherCatFibre("EtherCatFibre");
    
    FibreManager &thread = FibreManager::getInstance(THREAD_POLLED_ID);
    isConfigured = false;
    thread.Init();
    ASSERT_EQ(true, isConfigured);

    data = 0;
    thread.Run();
    ASSERT_EQ(1, data);
}