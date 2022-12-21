#include "gtest/gtest.h"

#include "Fibre.hpp"
#include "DataModel.hpp"

bool isConfigured;
bool isReadRequested;
uint8_t data;

extern "C" void SPI_Force_Sensor_RX_Interrupt();

TEST(ForceSensorTest, test_fs)
{
    FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
    DataItem fs0DI(DataItemId::FS_0_ID, true);
    DataItem fs1DI(DataItemId::FS_1_ID, true);
    DataItem fs2DI(DataItemId::FS_2_ID, true);
    DataItem fs3DI(DataItemId::FS_3_ID, true);
    DataItem fsVrefDI(DataItemId::FS_VREF_ID, true);

    ASSERT_EQ(false, isConfigured);
    thread.Init();
    ASSERT_EQ(true, isConfigured);

    ASSERT_EQ(false, isReadRequested);
    thread.Run();
    ASSERT_EQ(true, isReadRequested);

    data = 10;
    SPI_Force_Sensor_RX_Interrupt();
    ASSERT_EQ(false, isReadRequested);
    ASSERT_EQ(10, fs0DI.get());
    ASSERT_EQ(11, fs1DI.get());
    ASSERT_EQ(12, fs2DI.get());
    ASSERT_EQ(13, fsVrefDI.get());
    ASSERT_EQ(14, fs3DI.get());
}

