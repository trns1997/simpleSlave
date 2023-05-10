#ifndef RELAX_SPI_MAPPING_H_
#define RELAX_SPI_MAPPING_H_

#include "stdint.h"

////////////////////////////////////////////////////
// Include SPI HAL from Manufacturer or your own ///
////////////////////////////////////////////////////

/////////////////////////////////////////////////
// Remap SPI interrupt callbacks here (if any) //
/////////////////////////////////////////////////

namespace board
{
    enum spi_identifier
    {
        ///////////////////////////////
        // Fill Pin Identifier Enums //
        ///////////////////////////////
    };

    struct spi_conf_t
    {
        ///////////////////////////////////////////////////////////////////////
        // Board Specific spi configs (channel, cph, cpole, source and etc.) //
        ///////////////////////////////////////////////////////////////////////
    };

    static spi_conf_t spi_mapping[] =
        {
            ///////////////////////////
            // SPI configuration Map //
            ///////////////////////////
    };

}

#endif
