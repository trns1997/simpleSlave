#ifndef MOCK_PIN_MAPPING_H_
#define MOCK_PIN_MAPPING_H_

#include "stdint.h"

namespace board
{

typedef enum
{
	LED1 = 0,
	LED2,
	SPI0_CH1_MOSI,
	SPI0_CH1_MISO,
	SPI0_CH1_CLK,
	SPI0_CH1_CS1,
	SPI2_CH0_MOSI,
	SPI2_CH0_MISO,
	SPI2_CH0_CLK,
	SPI2_CH0_CS1
} pin_identifier;

typedef struct
{
	pin_identifier 		pin_id;
} pin_conf_t;

static pin_conf_t pin_mapping[] =
{
	{LED1},
	{LED2},

	{SPI0_CH1_MOSI},
	{SPI0_CH1_MISO},
	{SPI0_CH1_CLK},
	{SPI0_CH1_CS1},

	{SPI2_CH0_MOSI},
	{SPI2_CH0_MISO},
	{SPI2_CH0_CLK},
	{SPI2_CH0_CS1},
};

}


#endif
