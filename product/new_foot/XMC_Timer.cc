#include "XMC_Timer.h"

XMC_Timer::XMC_Timer(TIMER_CONFIG timerConfig)
{
    // CCU4 Initialization
    /* Select module clock as clock source */
    XMC_CCU4_SetModuleClock(timerConfig.module, timerConfig.clock);

    /* Init CCU4 */
    XMC_CCU4_Init(timerConfig.module, timerConfig.sliceAction);

    /* Start Prescaler */
    XMC_CCU4_StartPrescaler(timerConfig.module);

    /* Get the slice out of idle mode */
    XMC_CCU4_EnableClock(timerConfig.module, timerConfig.clockMask);

    /* Mapping Event-0 to count function */
    XMC_CCU4_SLICE_CountConfig(timerConfig.slice, timerConfig.sliceEvent);

    /* Configure Event-0 and map it to Input */
    XMC_CCU4_SLICE_CompareInit(timerConfig.slice, &timerConfig.sliceConfig);

    uint32_t timePeriod = 144000000 / timerConfig.prescalar / timerConfig.frequency;
    /* Program maximum Period value */
    XMC_CCU4_SLICE_SetTimerPeriodMatch(timerConfig.slice, timePeriod);

    /* Enable shadow transfer */
    XMC_CCU4_EnableShadowTransfer(timerConfig.module, timerConfig.shadowTransferMask);

    /* Enable Compare Match while counting up interrupt event */
    XMC_CCU4_SLICE_EnableEvent(timerConfig.slice, timerConfig.interruptEvent);

    /* Connect compare match event to SR0 */
    XMC_CCU4_SLICE_SetInterruptNode(timerConfig.slice, timerConfig.interruptEvent, timerConfig.isrId);

    XMC_CCU4_SLICE_SetTimerRepeatMode(timerConfig.slice, timerConfig.sliceRepeatMode);

    /* Configure interrupt node */
    NVIC_SetPriority(timerConfig.timerIRQ, 10U);
    NVIC_EnableIRQ(timerConfig.timerIRQ);

    /* Start Timer */
    XMC_CCU4_SLICE_StartTimer(timerConfig.slice);
}