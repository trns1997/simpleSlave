extern "C"
{
#include "utypes.h"
#include "ecat_slv.h"
}

#include "XMC_SPI.h"
#include "XMC_Timer.h"
#include "LSM6DSM.h"
#include "ForceSensor.h"
#include "xmc_gpio.h"
//#include "xmc4_gpio_map.h

// Application variables
_Rbuffer Rb;
_Wbuffer Wb;
_Cbuffer Cb;

uint8_t *rxpdo = (uint8_t *)&Wb;
uint8_t *txpdo = (uint8_t *)&Rb;

IMUData imuData;
ForceSensorData forceSensorData;

LSM6DSM boardIMU;
ForceSensor forceSensors;

extern "C" void ESC_eep_handler(void);

// Board IMU SPI IRQ Handler (one for transmit and the other for receiver buffer respectively)
extern "C" void USIC1_3_IRQHandler(void) {}
extern "C" void USIC1_2_IRQHandler(void)
{
    boardIMU.irqHandler();       // Read IMU data from SPI
    boardIMU.bufferizeIMUData(); // Fill one of the 2 buffers (Double Buffer)
}

// Force Sensor SPI IRQ Handler (one for transmit and the other for receiver buffer respectively)
extern "C" void USIC0_3_IRQHandler(void) {}
extern "C" void USIC0_2_IRQHandler(void)
{
    forceSensors.irqHandler();               // Read Force Sensor data from SPI
    forceSensors.bufferizeForceSensorData(); // Fill one of the 2 buffers (Double Buffer)
}

// Timer IRQ Handler
extern "C" void CCU40_0_IRQHandler(void)
{
    // Transmit data over respective SPI at every timer tick
    boardIMU.read();
    forceSensors.read();

    static int cnt = 0;
    cnt++;
    if ( cnt > 1000)
    {
        XMC_GPIO_ToggleOutput(P5_9);
        cnt = 0;
    }
}

XMC_SPI_CH_CONFIG_t spi_config =
    {
        .baudrate = 5000000,
        .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE};

// Callback to update ethercat frame when it arrives with slave data
void cb_get_inputs(void)
{
    // Get IMU and Force Sensor Data from locked buffer and switch buffers (Double Buffer)
    imuData = boardIMU.getIMUData();
    forceSensorData = forceSensors.getForceSensorData();

    // Put Data in Respective PDO objects
    Cb.reset_counter++;
    Rb.boardStatus = (uint16_t)ESCvar.Time;

    Rb.ankleIMU.accelerometerX0 = imuData.accelerometer[0];
    Rb.ankleIMU.accelerometerY0 = imuData.accelerometer[1];
    Rb.ankleIMU.accelerometerZ0 = imuData.accelerometer[2];

    Rb.ankleIMU.gyroscopeX0 = imuData.gyroscope[0];
    Rb.ankleIMU.gyroscopeY0 = imuData.gyroscope[1];
    Rb.ankleIMU.gyroscopeZ0 = imuData.gyroscope[2];

    Rb.ankleIMU.temperature0 = imuData.temperatureSensor;

    Rb.forceSensor0 = forceSensorData.f0;
    Rb.forceSensor1 = forceSensorData.f1;
    Rb.forceSensor2 = forceSensorData.f2;
    Rb.forceSensor3 = forceSensorData.f3;
    Rb.forceSensor4 = forceSensorData.f4;
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
            .esc_hw_eep_handler = ESC_eep_handler};

    ecat_slv_init(&config);
}

void initTimer()
{

    XMC_CCU4_SLICE_COMPARE_CONFIG_t sliceConfig;
    sliceConfig.timer_mode = (uint32_t)XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA;
    sliceConfig.monoshot = (uint32_t)XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT;
    sliceConfig.shadow_xfer_clear = false;
    sliceConfig.dither_timer_period = false;
    sliceConfig.dither_duty_cycle = false;
    sliceConfig.prescaler_mode = (uint32_t)XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL;
    sliceConfig.mcm_enable = false;
    sliceConfig.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_256;
    sliceConfig.float_limit = 0;
    sliceConfig.dither_limit = 0;
    sliceConfig.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
    sliceConfig.timer_concatenation = false;

    TIMER_CONFIG timerConfig{
        CCU40,
        XMC_CCU4_CLOCK_SCU,
        XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR,
        0,
        CCU40_CC40,
        sliceConfig,
        XMC_CCU4_SLICE_EVENT_0,
        256,
        2000,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_0,
        XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
        XMC_CCU4_SLICE_SR_ID_0,
        XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
        CCU40_0_IRQn};

    XMC_Timer timer(timerConfig);
}

void initIMU()
{
    XMC_SPI spiIMU;

    PIN_CONFIG IMU_MOSI = {P0_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2};
    PIN_CONFIG IMU_MISO = {P0_4, XMC_GPIO_MODE_INPUT_TRISTATE};
    PIN_CONFIG IMU_SCLK = {P4_0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4};
    PIN_CONFIG IMU_SS = {P0_6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2};

    SPI_CONFIG ImuSpiConfig = {
        XMC_SPI1_CH0,
        spi_config,
        XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED,
        XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK,
        3,
        2,
        USIC1_3_IRQn,
        USIC1_2_IRQn,
        USIC1_C0_DX0_P0_4,
        IMU_MOSI,
        IMU_MISO,
        IMU_SCLK,
        IMU_SS};

    spiIMU.init(ImuSpiConfig);

    boardIMU.setSPI(spiIMU);
    boardIMU.configure();
}

void initForceSensors()
{
    XMC_SPI spiForceSensor;

    PIN_CONFIG FS_MOSI = {P2_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2};
    PIN_CONFIG FS_MISO = {P2_2, XMC_GPIO_MODE_INPUT_TRISTATE};
    PIN_CONFIG FS_SCLK = {P2_4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2};
    PIN_CONFIG FS_SS = {P2_3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2};

    SPI_CONFIG ForceSensorSpiConfig = {
        XMC_SPI0_CH1,
        spi_config,
        XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED,
        XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK,
        3,
        2,
        USIC0_3_IRQn,
        USIC0_2_IRQn,
        USIC0_C1_DX0_P2_2,
        FS_MOSI,
        FS_MISO,
        FS_SCLK,
        FS_SS};

    spiForceSensor.init(ForceSensorSpiConfig);

    forceSensors.setSPI(spiForceSensor);
    forceSensors.configure();
}

int main()
{

    initIMU();

    initForceSensors();

    initTimer();

    soesInit();

    while (1)
    {
        // RUN ETHERCAT SLAVE
        ecat_slv();
    }
    return 0;
}
