#ifndef HAL_INC_TIMER_H_
#define HAL_INC_TIMER_H_

#include "tim_mapping.h"

class TIMER
{

public:
    TIMER(board::tim_identifier tim_name): tim_conf_(board::tim_mapping[tim_name])
	{}
	~TIMER() {}

	void init();

private:

	board::tim_conf_t tim_conf_;

};

#endif /* HAL_INC_SPI_H_ */
