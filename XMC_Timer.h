#ifndef XMC_Timer_H_
#define XMC_Timer_H_

extern "C"
{
#include <xmc_ccu4.h>
}

struct TIMER_CONFIG
{
    XMC_CCU4_MODULE_t *module;
    XMC_CCU4_CLOCK_t clock;
    XMC_CCU4_SLICE_MCMS_ACTION_t sliceAction;
    uint8_t clockMask;
    XMC_CCU4_SLICE_t *slice;
    XMC_CCU4_SLICE_COMPARE_CONFIG_t sliceConfig;
    XMC_CCU4_SLICE_EVENT_t sliceEvent;
    uint32_t prescalar;
    uint32_t frequency;
    uint32_t shadowTransferMask;
    XMC_CCU4_SLICE_IRQ_ID_t interruptEvent;
    XMC_CCU4_SLICE_SR_ID_t isrId;
    XMC_CCU4_SLICE_TIMER_REPEAT_MODE_t sliceRepeatMode;
    IRQn_Type timerIRQ;
};

class XMC_Timer
{
public:
    XMC_Timer(TIMER_CONFIG timerConfig);
    ~XMC_Timer() = default;
};

#endif
