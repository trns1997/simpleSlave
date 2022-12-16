#ifndef RELAX_TIM_MAPPING_H_
#define RELAX_TIM_MAPPING_H_

#include "xmc_ccu4.h"
#include "stdint.h"

#define interrupt_1ms CCU40_0_IRQHandler

namespace board
{

typedef enum
{
	TIMER_1 = 0
} tim_identifier;

typedef struct
{
    tim_identifier  name;
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
} tim_conf_t;

static tim_conf_t tim_mapping[] =
{
    {
        TIMER_1,
        CCU40,
        XMC_CCU4_CLOCK_SCU,
        XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR,
        0,
        CCU40_CC40,
        XMC_CCU4_SLICE_COMPARE_CONFIG_t(),
        XMC_CCU4_SLICE_EVENT_0,
        256,
        2000,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_0,
        XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
        XMC_CCU4_SLICE_SR_ID_0,
        XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
        CCU40_0_IRQn
	}
};

}


#endif /* RELAX_PIN_MAPPING_H_ */
