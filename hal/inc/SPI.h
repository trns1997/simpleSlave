#ifndef HAL_INC_SPI_H_
#define HAL_INC_SPI_H_

#include "spi_mapping.h"
#include <stdint.h>

class SPI
{

public:
	SPI(board::spi_identifier spi_name): spi_conf_(board::spi_mapping[spi_name])
	{}
	~SPI() {}

	void init();

	void sendData(uint8_t* txData, uint32_t size);
	void readData(uint8_t* rxData, uint32_t& size);


private:

	board::spi_conf_t spi_conf_;
	bool transferComplete_ {false};

};


static void initSPI()
{
    for (int i = 0; i < (sizeof(board::spi_mapping)/sizeof(board::spi_conf_t)); i++)
    {
        SPI spi(static_cast<board::spi_identifier>(i));
        spi.init();
    }
}


#endif /* HAL_INC_SPI_H_ */
