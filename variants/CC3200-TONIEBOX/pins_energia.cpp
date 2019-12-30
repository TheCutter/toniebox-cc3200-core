#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//#include "inc/hw_gpio.h"
//#include "driverlib/adc.h"
#include "driverlib/pin.h"
//#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
//#include "driverlib/gpio.h"
#include "driverlib/prcm.h"

void PinMuxConfig() {
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_SDHOST, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_I2CA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI, PRCM_RUN_MODE_CLK);

    MAP_PinModeSet(PIN_61, PIN_MODE_0); //Power Pin
    MAP_PinModeSet(PIN_62, PIN_MODE_0); //Reset DAC

    //See HardwareSerial.cpp
    //MAP_PinTypeUART(PIN_55, PIN_MODE_3); //TX0 
    //MAP_PinTypeUART(PIN_57, PIN_MODE_3); //RX0

    MAP_PinTypeSDHost(PIN_64, PIN_MODE_6); //SDHost_D0
    MAP_PinTypeSDHost(PIN_01, PIN_MODE_6); //SDHost_CLK
    MAP_PinTypeSDHost(PIN_02, PIN_MODE_6); //SDHost_CMD

    MAP_PinTypeI2C(PIN_03, PIN_MODE_5); //I2C_SCL
    MAP_PinTypeI2C(PIN_04, PIN_MODE_5); //I2C_SDA

    MAP_PinTypeSPI(PIN_05, PIN_MODE_7); //GSPI_CLK / TODO: MAP_PinTypeSPI
    MAP_PinTypeSPI(PIN_06, PIN_MODE_7); //GSPI_MISO
    MAP_PinTypeSPI(PIN_07, PIN_MODE_7); //GSPI_MOSI
    MAP_PinModeSet(PIN_18, PIN_MODE_0); //RFID IRQ

    MAP_PinTypeI2S(PIN_50, PIN_MODE_6); //I2S Data1 (DIN)
    MAP_PinTypeI2S(PIN_53, PIN_MODE_2); //I2S ClockO (BCLK)
    MAP_PinTypeI2S(PIN_63, PIN_MODE_7); //I2S Frame Sync (WCLK)
}