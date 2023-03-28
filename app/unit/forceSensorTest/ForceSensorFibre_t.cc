#include "gtest/gtest.h"

#include "ForceSensorFibre.h"

#include "DataModel.h"
#include "Fibre.h"

#include "ForceSensor.h"

bool isReadRequested;
SPI_Slave::State *stateFS;
uint16_t data;

DataItemId forceSensorData[] = {DataItemId::FS_0_ID,
                                DataItemId::FS_1_ID,
                                DataItemId::FS_2_ID,
                                DataItemId::FS_VREF_ID,
                                DataItemId::FS_3_ID};

static ForceSensorFibre forceSensorFibre("ForceSensorFibre", board::SPI_FS, forceSensorData);

extern "C" void SPI_Force_Sensor_TX_Interrupt(void) {}
extern "C" void SPI_Force_Sensor_RX_Interrupt(void)
{
    forceSensorFibre.Interrupt();
}

TEST(ForceSensorTest, test_fs)
{
    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    DataItem fs0DI(DataItemId::FS_0_ID);
    DataItem fs1DI(DataItemId::FS_1_ID);
    DataItem fs2DI(DataItemId::FS_2_ID);
    DataItem fs3DI(DataItemId::FS_3_ID);
    DataItem fsVrefDI(DataItemId::FS_VREF_ID);

    ASSERT_EQ(SPI_Slave::INITIALIZING, *stateFS);
    thread.Init();
    ASSERT_EQ(SPI_Slave::INITIALIZING, *stateFS);

    ASSERT_EQ(false, isReadRequested);
    thread.Run();
    ASSERT_EQ(SPI_Slave::INITIALIZED, *stateFS);
    ASSERT_EQ(false, isReadRequested);

    thread.Run();
    ASSERT_EQ(SPI_Slave::INITIALIZED, *stateFS);
    ASSERT_EQ(false, isReadRequested);

    SPI_Force_Sensor_RX_Interrupt();

    ASSERT_EQ(SPI_Slave::READY, *stateFS);
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
