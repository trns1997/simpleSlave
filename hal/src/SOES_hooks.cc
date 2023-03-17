#include "SOES_hooks.h"
#include "DataModel.h"
#include "EthercatObjects.h"
#include <cstring>
#include <vector>

extern "C"
{
#include "ecat_slv.h"
}

extern void callback_inputs();

uint8_t input[MAX_TXPDO_SIZE];
uint8_t output[MAX_RXPDO_SIZE];

uint8_t *rxpdo = (uint8_t *)&output;
uint8_t *txpdo = (uint8_t *)&input;

_objectlist SDOobjects[MAX_TXPDO_SIZE];

extern "C" void ESC_eep_handler(void);

// Callback to update ethercat frame when it arrives with slave data
void cb_get_inputs(void)
{
    uint16_t pos = 0;
    std::size_t size = 0;

    for (uint16_t i = 0; i < MAX_DATA_ITEMS; ++i)
    {
        static DataItem item(static_cast<DataItemId>(i));
        Datagram datagram = item.getDatagram(static_cast<DataItemId>(i));

        switch (datagram.ethercat.datatype)
        {
        case DTYPE_BIT1:
        case DTYPE_BIT2:
        case DTYPE_BIT3:
        case DTYPE_BIT4:
        case DTYPE_BIT5:
        case DTYPE_BIT6:
        case DTYPE_BIT7:
        case DTYPE_BIT8:
        case DTYPE_BOOLEAN:
        case DTYPE_UNSIGNED8:
        case DTYPE_INTEGER8:
        case DTYPE_BITARR8:
        {
            size = sizeof(uint8_t);
            uint8_t data = static_cast<uint8_t>(datagram.value);
            std::memcpy(input + pos, &data, size);
            break;
        }

        case DTYPE_UNSIGNED16:
        case DTYPE_INTEGER16:
        case DTYPE_BITARR16:
        {
            size = sizeof(uint16_t);
            uint16_t data = static_cast<uint16_t>(datagram.value);
            std::memcpy(input + pos, &data, size);
            break;
        }

        case DTYPE_REAL32:
        case DTYPE_UNSIGNED32:
        case DTYPE_INTEGER32:
        case DTYPE_BITARR32:
        {
            size = sizeof(uint32_t);
            uint32_t data = static_cast<uint32_t>(datagram.value);
            std::memcpy(input + pos, &data, size);
            break;
        }

        case DTYPE_REAL64:
        case DTYPE_UNSIGNED64:
        case DTYPE_INTEGER64:
        {
            size = sizeof(uint64_t);
            uint64_t data = static_cast<uint64_t>(datagram.value);
            std::memcpy(input + pos, &data, size);
            break;
        }
        }
        pos += size;
    }
}

// Callback to get data from the ethercat frame when it arrives
void cb_set_outputs(void)
{
    static DataItem watchDogCounter(DataItemId::WATCHDOG, true);
    uint16_t rxWatchDogCounter = output;

    watchDogCounter.set(rxWatchDogCounter);
}

void runEtherCAT()
{
    ecat_slv();
}

void initPDOMapping()
{
    for (uint16_t i = 0; i < MAX_DATA_ITEMS; ++i)
    {
        static DataItem item(static_cast<DataItemId>(i));
        Datagram datagram = item.getDatagram(static_cast<DataItemId>(i));
        if (datagram.ethercat.datatype != NULL)
        {
            SDO6000.push_back(datagram.ethercat);
            SDO1A00.push_back({datagram.ethercat.subindex, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], (0x60000000 + datagram.ethercat.bitlength + (256 * datagram.ethercat.subindex)), NULL});
        }
    }

    SDO6000[0].value = SDO6000.size() - 1;
    SDO1A00[0].value = SDO1A00.size() - 1;

    std::vector<_objectlist> baseSDOobjects{{0x1000, OTYPE_VAR, 0, 0, &acName1000[0], &SDO1000[0]},
                                            {0x1008, OTYPE_VAR, 0, 0, &acName1008[0], &SDO1008[0]},
                                            {0x1009, OTYPE_VAR, 0, 0, &acName1009[0], &SDO1009[0]},
                                            {0x100A, OTYPE_VAR, 0, 0, &acName100A[0], &SDO100A[0]},
                                            {0x1018, OTYPE_RECORD, 4, 0, &acName1018[0], &SDO1018[0]},
                                            {0x1600, OTYPE_RECORD, 1, 0, &acName1600[0], &SDO1600[0]},
                                            {0x1A00, OTYPE_RECORD, SDO6000[0].value, 0, &acName1A00[0], SDO1A00.data()},
                                            {0x1C00, OTYPE_ARRAY, 4, 0, &acName1C00[0], &SDO1C00[0]},
                                            {0x1C10, OTYPE_ARRAY, 0, 0, &acName1C10[0], &SDO1C10[0]},
                                            {0x1C11, OTYPE_ARRAY, 0, 0, &acName1C11[0], &SDO1C11[0]},
                                            {0x1C12, OTYPE_ARRAY, 1, 0, &acName1C12[0], &SDO1C12[0]},
                                            {0x1C13, OTYPE_ARRAY, 1, 0, &acName1C13[0], &SDO1C13[0]},
                                            {0x6000, OTYPE_ARRAY, SDO1A00[0].value, 0, &acName6000[0], SDO6000.data()},
                                            {0x7000, OTYPE_ARRAY, 1, 0, &acName7000[0], &SDO7000[0]},
                                            {0xffff, 0xff, 0xff, 0xff, NULL, NULL}};

    std::copy(baseSDOobjects.begin(), baseSDOobjects.end(), SDOobjects);
}

// Initialize SEOS EtherCat slave
void soesInit()
{
    initPDOMapping();

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
            .post_object_download_hook = NULL,
            .rxpdo_override = NULL,
            .txpdo_override = NULL,
            .esc_hw_interrupt_enable = NULL,
            .esc_hw_interrupt_disable = NULL,
            .esc_hw_eep_handler = ESC_eep_handler};

    ecat_slv_init(&config);
}
