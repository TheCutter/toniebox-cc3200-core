#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/adc.h"
#include "driverlib/pin.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/prcm.h"

void PinMuxConfig() {
    //
    // Enable Peripheral Clocks 
    // 
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_SDHOST, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_I2CA0, PRCM_RUN_MODE_CLK);

	//MAP_PinModeSet(PIN_01, PIN_MODE_0);

    //See HardwareSerial.cpp
    //MAP_PinTypeUART(PIN_55, PIN_MODE_3); //TX0 
    //MAP_PinTypeUART(PIN_57, PIN_MODE_3); //RX0
    

	MAP_PinTypeSDHost(PIN_64, PIN_MODE_6); //SDHost_D0
	MAP_PinTypeSDHost(PIN_01, PIN_MODE_6); //SDHost_CLK
	MAP_PinTypeSDHost(PIN_02, PIN_MODE_6); //SDHost_CMD

	MAP_PinTypeI2C(PIN_03, PIN_MODE_5); //I2C_SCL
	MAP_PinTypeI2C(PIN_04, PIN_MODE_5); //I2C_SDA
}