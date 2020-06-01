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
    
    /*
    MAP_PRCMPeripheralClkEnable(PRCM_TIMERA0, PRCM_RUN_MODE_CLK); //PWM0/1
    MAP_PRCMPeripheralClkEnable(PRCM_TIMERA1, PRCM_RUN_MODE_CLK); //PWM2/3
    MAP_PRCMPeripheralClkEnable(PRCM_TIMERA2, PRCM_RUN_MODE_CLK); //PWM5
    MAP_PRCMPeripheralClkEnable(PRCM_TIMERA3, PRCM_RUN_MODE_CLK); //PWM6/7
    */

    MAP_PinModeSet(PIN_08, PIN_MODE_0); //Charger connected?
    //MAP_PinTypeADC(PIN_60, 0xFF);  //Battery level ADC?

    MAP_PinModeSet(PIN_58, PIN_MODE_0); //Power SD Pin
    MAP_PinModeSet(PIN_61, PIN_MODE_0); //Power Pin
    MAP_PinModeSet(PIN_62, PIN_MODE_0); //Reset DAC

    //MAP_PinModeSet(PIN_17, PIN_MODE_0); //LED Blue
    //MAP_PinTypeTimer(PIN_19, PIN_MODE_8); //LED Red PWM3? SWD...
    //MAP_PinModeSet(PIN_21, PIN_MODE_0); //LED Green

    //See HardwareSerial.cpp
    //MAP_PinTypeUART(PIN_55, PIN_MODE_3); //TX0 
    //MAP_PinTypeUART(PIN_57, PIN_MODE_3); //RX0

    MAP_PinModeSet(PIN_57, PIN_MODE_0); //BTN1
    MAP_PinModeSet(PIN_59, PIN_MODE_0); //BTN2

    MAP_PinTypeSDHost(PIN_64, PIN_MODE_6); //SDHost_D0
    MAP_PinTypeSDHost(PIN_01, PIN_MODE_6); //SDHost_CLK
    MAP_PinTypeSDHost(PIN_02, PIN_MODE_6); //SDHost_CMD

    MAP_PinTypeI2C(PIN_03, PIN_MODE_5); //I2C_SCL
    MAP_PinTypeI2C(PIN_04, PIN_MODE_5); //I2C_SDA

    MAP_PinTypeSPI(PIN_05, PIN_MODE_7); //GSPI_CLK / TODO: MAP_PinTypeSPI
    MAP_PinTypeSPI(PIN_06, PIN_MODE_7); //GSPI_MISO
    MAP_PinTypeSPI(PIN_07, PIN_MODE_7); //GSPI_MOSI
    MAP_PinModeSet(PIN_18, PIN_MODE_0); //RFID IRQ

    MAP_PinTypeI2S(PIN_50, PIN_MODE_4); //I2S Data0 (DIN)
    MAP_PinTypeI2S(PIN_53, PIN_MODE_2); //I2S ClockO (BCLK)
    MAP_PinTypeI2S(PIN_63, PIN_MODE_7); //I2S Frame Sync (WCLK)
}