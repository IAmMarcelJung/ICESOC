#include <stdint.h>

#include <defs.h>
#include <global_defs.h>
#include <gpio_config_io.h>
#include <helpers.h>
#include <stub.h>

#define TEST_WORD 0xBADCAFFE

int main() {
  // NOTE: these config values are taken from the wb_test_icesoc firmware
  // Connect the housekeeping SPI to the SPI master
  // so that the CSB line is not left floating.  This allows
  // all of the GPIO pins to be used for user functions.

  reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

  // Configure lower 8-IOs as user output
  // Observe counter value in the testbench
  reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_1 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_6 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_7 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;

  reg_mprj_io_8 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_9 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
  reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;

  /* Apply configuration */
  reg_mprj_xfer = 1;
  while (reg_mprj_xfer == 1)
    ;

  reg_gpio_mode1 = 1;
  reg_gpio_mode0 = 0;
  reg_gpio_ien = 1;
  reg_gpio_oe = 1;
  reg_gpio_out = 1;
  reg_wb_enable = 1;
  reg_hkspi_disable = 1;

  reg_gpio_out = 0;

  // Set LA bits 0-3 as outputs
  reg_la0_oenb = reg_la0_oenb & ~0xF;
  //
  // Set Ibex control bits to zero
  reg_la0_data = 0u;

  volatile uint32_t *sram1 = (uint32_t *)&reg_mprj_slave;

  uint8_t fail;

  reg_mprj_datah = 0x1;

  // This can be used both for the on-chip test and the simulation
  while (1) {
    sram1[0] = TEST_WORD;
    if (sram1[0] == TEST_WORD) {
      fail = 0;
    } else {
      fail = 1;
    }
    if (fail) {
      reg_mprj_datah = 0x2;
      blink(3, 500000);
    } else {
      reg_mprj_datah = 0x3;
      blink(3, 100000);
    }
    delay(1000000);
  }

  return 0;
}
