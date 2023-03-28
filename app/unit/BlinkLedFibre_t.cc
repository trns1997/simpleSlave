#include "gtest/gtest.h"

#include "BlinkLedFibre.h"

#include "DataModel.h"
#include "Fibre.h"

#include "GPIO.h"

TEST(BlinkLedTest, test_led)
{
    static BlinkLedFibre blinkLedFibre("BlinkedFiber");

    FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
    DataItem timeDI(DataItemId::TIME_ID, true);
    GPIO gpio{board::LED1};

    timeDI.set(1);
    thread.Run();
    ASSERT_EQ(false, gpio.getPin());

    timeDI.set(999);
    thread.Run();
    ASSERT_EQ(false, gpio.getPin());

    timeDI.set(1000);
    thread.Run();
    ASSERT_EQ(true, gpio.getPin());

    timeDI.set(1999);
    thread.Run();
    ASSERT_EQ(true, gpio.getPin());

    timeDI.set(2000);
    thread.Run();
    ASSERT_EQ(false, gpio.getPin());
}
