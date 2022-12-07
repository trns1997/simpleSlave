extern "C"
{
#include "utypes.h"
#include "ecat_slv.h"
}

#include "GPIO.h"

#include "spi_mapping.h"
#include "LSM6DSM.h"
#include "ForceSensor.h"

#include "XMC_Timer.h"

LSM6DSM boardIMU(board::SPI2_CH0);
void SPI2_CH0_Interrupt(void)
{
    boardIMU.read();
}

ForceSensor forceSensors(board::SPI0_CH1);
void SPI0_CH1_Interrupt()
{
    forceSensors.read();
}

extern "C" void USIC2_3_IRQHandler(void) {}
extern "C" void USIC2_2_IRQHandler(void)
{
    SPI2_CH0_Interrupt();
}

extern "C" void USIC0_3_IRQHandler(void) {}
extern "C" void USIC0_2_IRQHandler(void)
{
    SPI0_CH1_Interrupt();
}

_Rbuffer Rb;
_Wbuffer Wb;
_Cbuffer Cb;

uint8_t *rxpdo = (uint8_t *)&Wb;
uint8_t *txpdo = (uint8_t *)&Rb;

extern "C" void ESC_eep_handler(void);

// Timer IRQ Handler
extern "C" void CCU40_0_IRQHandler(void)
{
    // Transmit data over respective SPI at every timer tick
    boardIMU.request_read();
    forceSensors.request_read();
	static GPIO gpio_led(board::LED1);
    static int cnt = 0;

    cnt++;
    if ( cnt > 1000)
    {
    	gpio_led.togglePin();
        cnt = 0;
    }
}

// Callback to update ethercat frame when it arrives with slave data
void cb_get_inputs(void)
{
    // Put Data in Respective PDO objects
    Cb.reset_counter++;
    Rb.boardStatus = (uint16_t)ESCvar.Time;

    IMUData imuData = boardIMU.getIMUData();
    Rb.ankleIMU.accelerometerX0 = imuData.accelerometer[0];
    Rb.ankleIMU.accelerometerY0 = imuData.accelerometer[1];
    Rb.ankleIMU.accelerometerZ0 = imuData.accelerometer[2];
    Rb.ankleIMU.gyroscopeX0     = imuData.gyroscope[0];
    Rb.ankleIMU.gyroscopeY0     = imuData.gyroscope[1];
    Rb.ankleIMU.gyroscopeZ0     = imuData.gyroscope[2];
    Rb.ankleIMU.temperature0    = imuData.temperatureSensor;

    ForceSensorData forceSensorData = forceSensors.getForceSensorData();
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
		.esc_hw_eep_handler = ESC_eep_handler
	};

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
    boardIMU.init();
    boardIMU.configure();
}

void initForceSensors()
{
    forceSensors.init();
    forceSensors.configure();
}

int main()
{
	initGPIO();

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
