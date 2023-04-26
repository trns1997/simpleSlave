#include "GPIO.h"

#include "Threads.h"

#include "EtherCatFibre.h"
#include "ForceSensorFibre.h"
#include "TimerFibre.h"

#include "DataModel.h"

DataItemId forceSensorData[] = {DataItemId::FS_0_ID,
                                DataItemId::FS_1_ID,
                                DataItemId::FS_2_ID,
                                DataItemId::FS_VREF_ID,
                                DataItemId::FS_3_ID};

static ForceSensorFibre forceSensorFibre("ForceSensorFibre", board::SPI_FS, forceSensorData);

static EtherCatFibre etherCatFibre("EtherCatFibre");

static TimerFibre timeFibre("TimerFibre", board::TIMER_1);

static DataItem items[] = {
    DataItem(DataItemId::TIME_0, true),
    DataItem(DataItemId::FS_1_0, true),
    DataItem(DataItemId::FS_2_0, true),
    DataItem(DataItemId::FS_3_0, true),

    DataItem(DataItemId::TIME_1, true),
    DataItem(DataItemId::FS_1_1, true),
    DataItem(DataItemId::FS_2_1, true),
    DataItem(DataItemId::FS_3_1, true),

    DataItem(DataItemId::TIME_2, true),
    DataItem(DataItemId::FS_1_2, true),
    DataItem(DataItemId::FS_2_2, true),
    DataItem(DataItemId::FS_3_2, true),

    DataItem(DataItemId::TIME_3, true),
    DataItem(DataItemId::FS_1_3, true),
    DataItem(DataItemId::FS_2_3, true),
    DataItem(DataItemId::FS_3_3, true),

    DataItem(DataItemId::TIME_4, true),
    DataItem(DataItemId::FS_1_4, true),
    DataItem(DataItemId::FS_2_4, true),
    DataItem(DataItemId::FS_3_4, true),

    DataItem(DataItemId::TIME_5, true),
    DataItem(DataItemId::FS_1_5, true),
    DataItem(DataItemId::FS_2_5, true),
    DataItem(DataItemId::FS_3_5, true),

    DataItem(DataItemId::TIME_6, true),
    DataItem(DataItemId::FS_1_6, true),
    DataItem(DataItemId::FS_2_6, true),
    DataItem(DataItemId::FS_3_6, true),

    DataItem(DataItemId::TIME_7, true),
    DataItem(DataItemId::FS_1_7, true),
    DataItem(DataItemId::FS_2_7, true),
    DataItem(DataItemId::FS_3_7, true),

    DataItem(DataItemId::TIME_8, true),
    DataItem(DataItemId::FS_1_8, true),
    DataItem(DataItemId::FS_2_8, true),
    DataItem(DataItemId::FS_3_8, true),

    DataItem(DataItemId::TIME_9, true),
    DataItem(DataItemId::FS_1_9, true),
    DataItem(DataItemId::FS_2_9, true),
    DataItem(DataItemId::FS_3_9, true)
    };

extern "C" void SPI_Force_Sensor_TX_Interrupt(void) {}
extern "C" void SPI_Force_Sensor_RX_Interrupt(void)
{
    forceSensorFibre.Interrupt();
}

extern "C" void interrupt_1ms(void)
{
    tick_1ms();

    static DataItem time(DataItemId::TIME_ID);
    static DataItem fs1(DataItemId::FS_1_ID);
    static DataItem fs2(DataItemId::FS_2_ID);
    static DataItem fs3(DataItemId::FS_3_ID);

    static uint16_t itemCounter = 0;

    items[itemCounter].set(time.get());
    itemCounter++;
    items[itemCounter].set(fs1.get());
    itemCounter++;
    items[itemCounter].set(fs2.get());
    itemCounter++;
    items[itemCounter].set(fs3.get());
    itemCounter++;

    if (itemCounter >= 40)
    {
        itemCounter = 0;
    }
}

int main()
{
    initGPIO();

    init_threads();

    while (1)
    {
        tick_polled();
    }
    return 0;
}
