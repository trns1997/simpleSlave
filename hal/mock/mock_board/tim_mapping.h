#ifndef RELAX_TIM_MAPPING_H_
#define RELAX_TIM_MAPPING_H_

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
} tim_conf_t;

static tim_conf_t tim_mapping[] =
{
    {
        TIMER_1
	}
};

}


#endif
