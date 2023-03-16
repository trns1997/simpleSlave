#ifndef INC_CRC_HPP_
#define INC_CRC_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum{
    CHECKSUM_ERROR = 0X04
};

uint8_t SF04_CheckCrc (uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum);
uint8_t SF04_CalcCrc (uint8_t data[], uint8_t nbrOfBytes);

#ifdef __cplusplus
}
#endif

#endif /* INC_CRC_HPP_ */
