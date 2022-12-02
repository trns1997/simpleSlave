/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

/** \file
 * \brief
 * ESC hardware layer functions.
 *
 * Function to read and write commands to the ESC. Used to read/write ESC
 * registers and memory.
 */
#include "esc_hw.h"
#include "esc.h"
#include "esc_hw_eep.h"
#include "esc_eep.h"

#include "xmc_gpio.h"
#include "xmc_ecat.h"

#ifdef XMC4800_F144x2048
/* ESC to PHY interconnect setup */
/* PHY management interface signal definitions*/
#define ECAT_MDO P0_12
#define ECAT_MCLK P3_3

#define ENABLE_ECAT_RESET_REQ 0U
#define ECAT_PORT_CTRL_LATCHIN0 XMC_ECAT_PORT_CTRL_LATCHIN0_P14_5
#define ECAT_PORT_CTRL_LATCHIN1 XMC_ECAT_PORT_CTRL_LATCHIN1_P14_4
#define ECAT_PHYADDR_OFFSET 1

/* EtherCAT slave physical layer pin configurations */
#define ECAT_CLK25 P1_13
#define ECAT_PHY_RESET P0_0
#define ECAT_LED_RUN P0_8
#define ECAT_LED_ERR P0_7

/* EtherCAT slave physical layer Port 0 pin configurations */
#define ECAT_P0_LINK_STATUS P1_15
#define ECAT_P0_LED_LINK_ACT P1_12
#define ECAT_P0_RXD3 P1_11
#define ECAT_P0_RXD2 P1_10
#define ECAT_P0_RXD1 P1_5
#define ECAT_P0_RXD0 P1_4
#define ECAT_P0_RX_DV P1_9
#define ECAT_P0_RX_CLK P1_1
#define ECAT_P0_RX_ERR P2_6
#define ECAT_P0_TXD3 P1_2
#define ECAT_P0_TXD2 P1_8
#define ECAT_P0_TXD1 P1_7
#define ECAT_P0_TXD0 P1_6
#define ECAT_P0_TX_EN P1_3
#define ECAT_P0_TX_CLK P1_0

/* EtherCAT slave physical layer Port 1 pin configurations */
#define ECAT_P1_LINK_STATUS P15_3
/* Maximum Sync Managers supported */
#define MAX_SYNC_MAN (8U)

#endif

#define ESCADDR(x) (((uint8_t *)ECAT0_BASE) + x)

static const XMC_ECAT_PORT_CTRL_t port_control = {
    .common = {
        .enable_rstreq = ENABLE_ECAT_RESET_REQ,
        .latch_input0 = XMC_ECAT_PORT_CTRL_LATCHIN0_P14_5,
        .latch_input1 = XMC_ECAT_PORT_CTRL_LATCHIN1_P14_4,
        .phyaddr_offset = ECAT_PHYADDR_OFFSET,
        .mdio = XMC_ECAT_PORT_CTRL_MDIO_P0_12},
    .port0 = {.rxd0 = XMC_ECAT_PORT0_CTRL_RXD0_P1_4, .rxd1 = XMC_ECAT_PORT0_CTRL_RXD1_P1_5, .rxd2 = XMC_ECAT_PORT0_CTRL_RXD2_P1_10, .rxd3 = XMC_ECAT_PORT0_CTRL_RXD3_P1_11, .rx_clk = XMC_ECAT_PORT0_CTRL_RX_CLK_P1_1, .rx_dv = XMC_ECAT_PORT0_CTRL_RX_DV_P1_9, .rx_err = XMC_ECAT_PORT0_CTRL_RX_ERR_P2_6, .link = XMC_ECAT_PORT0_CTRL_LINK_P1_15, .tx_clk = XMC_ECAT_PORT0_CTRL_TX_CLK_P1_0, .tx_shift = XMC_ECAT_PORT0_CTRL_TX_SHIFT_0NS},
    .port1 = {.rxd0 = 3, .rxd1 = 3, .rxd2 = 3, .rxd3 = 3, .rx_clk = 3, .rx_dv = 3, .rx_err = 3, .link = XMC_ECAT_PORT1_CTRL_LINK_P15_3, .tx_clk = 3, .tx_shift = XMC_ECAT_PORT1_CTRL_TX_SHIFT_0NS}};

static const XMC_GPIO_CONFIG_t gpio_config_input = {
    .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
    .output_level = 0,
    .output_strength = 0};

static void init_input(XMC_GPIO_PORT_t *const port, const uint8_t pin)
{
  XMC_GPIO_Init(port, pin, &gpio_config_input);
}

static void init_output(XMC_GPIO_PORT_t *const port, const uint8_t pin,
                        uint32_t function, XMC_GPIO_OUTPUT_STRENGTH_t strength)
{
  XMC_GPIO_CONFIG_t config;

  config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | function);
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = strength;

  XMC_GPIO_Init(port, pin, &config);
}

#define init_output_sharp(pin, function) init_output(pin, function, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE);
#define init_output_soft(pin, function) init_output(pin, function, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE);

/** ESC read function used by the Slave stack.
 *
 * @param[in]   address     = address of ESC register to read
 * @param[out]  buf         = pointer to buffer to read in
 * @param[in]   len         = number of bytes to read
 */
void ESC_read(uint16_t address, void *buf, uint16_t len)
{
  ESCvar.ALevent = etohs((uint16_t)ECAT0->AL_EVENT_REQ);
  memcpy(buf, ESCADDR(address), len);
}

/** ESC write function used by the Slave stack.
 *
 * @param[in]   address     = address of ESC register to write
 * @param[out]  buf         = pointer to buffer to write from
 * @param[in]   len         = number of bytes to write
 */
void ESC_write(uint16_t address, void *buf, uint16_t len)
{
  ESCvar.ALevent = etohs((uint16_t)ECAT0->AL_EVENT_REQ);
  memcpy(ESCADDR(address), buf, len);
}

/** ESC emulated EEPROM handler
 */
void ESC_eep_handler(void)
{
  EEP_process();
  EEP_hw_process();
}

void ESC_reset(void)
{
  /* disable ESC to force reset */
  XMC_ECAT_Disable();

  /* initialize EEPROM emulation */
  EEP_init();
}

void ESC_init(const esc_cfg_t *cfg)
{
  XMC_ECAT_CONFIG_t ecat_config;
  XMC_ECAT_PORT_CTRL_t port_control;
  port_control.common.raw = 0;
  port_control.port0.raw = 0;
  port_control.port1.raw = 0;

  XMC_GPIO_CONFIG_t gpio_config;

  ESC_reset();

  /* EtherCAT slave physical layer pin settings */
  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(ECAT_P0_LINK_STATUS, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD3, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD2, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD1, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD0, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_DV, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_CLK, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_ERR, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_TX_CLK, &gpio_config);

  /* If an ESC MII interface is not used, LINK_MII has to be tied to the logic value high which indicates no link */
  gpio_config.mode = XMC_GPIO_MODE_INPUT_PULL_UP;
  XMC_GPIO_Init(ECAT_P1_LINK_STATUS, &gpio_config);
  port_control.common.enable_rstreq = false;
  port_control.common.mdio = XMC_ECAT_PORT_CTRL_MDIO_P0_12;
  port_control.common.phyaddr_offset = 1;
  port_control.common.latch_input0 = XMC_ECAT_PORT_CTRL_LATCHIN0_P14_5;
  port_control.common.latch_input1 = XMC_ECAT_PORT_CTRL_LATCHIN1_P14_4;
  port_control.port0.rxd0 = XMC_ECAT_PORT0_CTRL_RXD0_P1_4;
  port_control.port0.rxd1 = XMC_ECAT_PORT0_CTRL_RXD1_P1_5;
  port_control.port0.rxd2 = XMC_ECAT_PORT0_CTRL_RXD2_P1_10;
  port_control.port0.rxd3 = XMC_ECAT_PORT0_CTRL_RXD3_P1_11;
  port_control.port0.rx_clk = XMC_ECAT_PORT0_CTRL_RX_CLK_P1_1;
  port_control.port0.rx_dv = XMC_ECAT_PORT0_CTRL_RX_DV_P1_9;
  port_control.port0.rx_err = XMC_ECAT_PORT0_CTRL_RX_ERR_P2_6;
  port_control.port0.link = XMC_ECAT_PORT0_CTRL_LINK_P1_15;
  port_control.port0.tx_clk = XMC_ECAT_PORT0_CTRL_TX_CLK_P1_0;
  port_control.port0.tx_shift = XMC_ECAT_PORT0_CTRL_TX_SHIFT_0NS;
  /* If an ESC MII interface is not used, RX_CLK, RXD, RX_ER, and especially RX_DV have to be tied to GND.                   For this purpose you can select a input position in register ECAT0_CONPx of these signals which are not connected to a pin on the XMC4800 */
  port_control.port1.rxd0 = 3;
  port_control.port1.rxd1 = 3;
  port_control.port1.rxd2 = 3;
  port_control.port1.rxd3 = 3;
  port_control.port1.rx_clk = 3;
  port_control.port1.rx_dv = 3;
  port_control.port1.rx_err = 3;
  port_control.port1.link = XMC_ECAT_PORT1_CTRL_LINK_P15_3;
  port_control.port1.tx_clk = 3;
  port_control.port1.tx_shift = XMC_ECAT_PORT1_CTRL_TX_SHIFT_0NS;
  XMC_ECAT_SetPortControl(port_control);

  XMC_ECAT_SetPortControl(port_control);

  /* read config from emulated EEPROM */
  memset(&ecat_config, 0, sizeof(XMC_ECAT_CONFIG_t));
  EEP_read(0, (uint8_t *)&ecat_config, sizeof(XMC_ECAT_CONFIG_t));
  XMC_ECAT_Init(&ecat_config);

  /* EtherCAT slave physical layer pin configurations */
  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE;
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_P0_TXD3, &gpio_config);
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_P0_TXD2, &gpio_config);
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_P0_TXD1, &gpio_config);
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_P0_TXD0, &gpio_config);
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_P0_TX_EN, &gpio_config);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
  XMC_GPIO_Init(ECAT_CLK25, &gpio_config);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
  XMC_GPIO_Init(ECAT_MCLK, &gpio_config);
  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(ECAT_MDO, &gpio_config);
  XMC_GPIO_SetHardwareControl(ECAT_MDO, XMC_GPIO_HWCTRL_PERIPHERAL1);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
  XMC_GPIO_Init(ECAT_P0_LED_LINK_ACT, &gpio_config);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3;
  XMC_GPIO_Init(ECAT_LED_RUN, &gpio_config);
  XMC_GPIO_SetHardwareControl(ECAT_LED_RUN, XMC_GPIO_HWCTRL_DISABLED);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3;
  XMC_GPIO_Init(ECAT_LED_ERR, &gpio_config);
  XMC_GPIO_SetHardwareControl(ECAT_LED_ERR, XMC_GPIO_HWCTRL_DISABLED);

  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
  XMC_GPIO_Init(ECAT_PHY_RESET, &gpio_config);
}
