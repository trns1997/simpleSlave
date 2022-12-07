#include "TIMER.h"

using namespace board;

void TIMER::init()
{
    XMC_CCU4_SLICE_COMPARE_CONFIG_t sliceConfig;
    sliceConfig.timer_mode = (uint32_t)XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA;
    sliceConfig.monoshot = (uint32_t)XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT;
    sliceConfig.shadow_xfer_clear = false;
    sliceConfig.dither_timer_period = false;
    sliceConfig.dither_duty_cycle = false;
    sliceConfig.prescaler_mode = (uint32_t)XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL;
    sliceConfig.mcm_enable = false;
    sliceConfig.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_256;
    sliceConfig.float_limit = 0;
    sliceConfig.dither_limit = 0;
    sliceConfig.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
    sliceConfig.timer_concatenation = false;
    tim_conf_.sliceConfig = sliceConfig;

    // CCU4 Initialization
    /* Select module clock as clock source */
    XMC_CCU4_SetModuleClock(tim_conf_.module, tim_conf_.clock);

    /* Init CCU4 */
    XMC_CCU4_Init(tim_conf_.module, tim_conf_.sliceAction);

    /* Start Prescaler */
    XMC_CCU4_StartPrescaler(tim_conf_.module);

    /* Get the slice out of idle mode */
    XMC_CCU4_EnableClock(tim_conf_.module, tim_conf_.clockMask);

    /* Mapping Event-0 to count function */
    XMC_CCU4_SLICE_CountConfig(tim_conf_.slice, tim_conf_.sliceEvent);

    /* Configure Event-0 and map it to Input */
    XMC_CCU4_SLICE_CompareInit(tim_conf_.slice, &tim_conf_.sliceConfig);

    uint32_t timePeriod = 144000000 / tim_conf_.prescalar / tim_conf_.frequency;
    /* Program maximum Period value */
    XMC_CCU4_SLICE_SetTimerPeriodMatch(tim_conf_.slice, timePeriod);

    /* Enable shadow transfer */
    XMC_CCU4_EnableShadowTransfer(tim_conf_.module, tim_conf_.shadowTransferMask);

    /* Enable Compare Match while counting up interrupt event */
    XMC_CCU4_SLICE_EnableEvent(tim_conf_.slice, tim_conf_.interruptEvent);

    /* Connect compare match event to SR0 */
    XMC_CCU4_SLICE_SetInterruptNode(tim_conf_.slice, tim_conf_.interruptEvent, tim_conf_.isrId);

    XMC_CCU4_SLICE_SetTimerRepeatMode(tim_conf_.slice, tim_conf_.sliceRepeatMode);

    /* Configure interrupt node */
    NVIC_SetPriority(tim_conf_.timerIRQ, 10U);
    NVIC_EnableIRQ(tim_conf_.timerIRQ);

    /* Start Timer */
    XMC_CCU4_SLICE_StartTimer(tim_conf_.slice);
}
