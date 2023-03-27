#include "SOES_hooks.h"
#include <cstdint>

extern bool isConfigured;
extern uint8_t data;

// Callback to update ethercat frame when it arrives with slave data
void cb_get_inputs(void)
{
}

// Callback to get data from the ethercat frame when it arrives
void cb_set_outputs(void)
{
}

uint32_t post_object_download_hook(uint16_t index, uint8_t subindex,
                                   uint16_t flags)
{
    return 0;
}

void runEtherCAT()
{
    data++;
}

// Initialize SEOS EtherCat slave
void soesInit()
{
    isConfigured = true;
}
