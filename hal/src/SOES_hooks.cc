#include "SOES_hooks.h"

extern "C"
{
#include "ecat_slv.h"
}

extern void callback_inputs();

_Rbuffer Rb;
_Wbuffer Wb;
_Cbuffer Cb;

uint8_t *rxpdo = (uint8_t *)&Wb;
uint8_t *txpdo = (uint8_t *)&Rb;

extern "C" void ESC_eep_handler(void);
extern void fill_input_buffer(_Rbuffer& buffer);

// Callback to update ethercat frame when it arrives with slave data
void cb_get_inputs(void)
{
    // Put Data in Respective PDO objects
    Cb.reset_counter++;
    Rb.boardStatus = (uint16_t)ESCvar.Time;

    fill_input_buffer(Rb);
}

// Callback to get data from the ethercat frame when it arrives
void cb_set_outputs(void)
{
}

uint32_t post_object_download_hook(uint16_t index, uint8_t subindex,
                                   uint16_t flags)
{
    switch (index)
    {
    case 0x8001:
    {
        switch (subindex)
        {
        case 0x01:
        {
            Cb.reset_counter = 0;
            break;
        }
        }
        break;
    }
    }

    return 0;
}

void runEtherCAT()
{
    ecat_slv();
}

// Initialize SEOS EtherCat slave
void soesInit()
{
    /* Setup config hooks */
    static esc_cfg_t config =
    {
        .user_arg = NULL,
        .use_interrupt = 0,
        .watchdog_cnt = 5000,
        .set_defaults_hook = NULL,
        .pre_state_change_hook = NULL,
        .post_state_change_hook = NULL,
        .application_hook = NULL,
        .safeoutput_override = NULL,
        .pre_object_download_hook = NULL,
        .post_object_download_hook = post_object_download_hook,
        .rxpdo_override = NULL,
        .txpdo_override = NULL,
        .esc_hw_interrupt_enable = NULL,
        .esc_hw_interrupt_disable = NULL,
        .esc_hw_eep_handler = ESC_eep_handler
    };

    ecat_slv_init(&config);
}

