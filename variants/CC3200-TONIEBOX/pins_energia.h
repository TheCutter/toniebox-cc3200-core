/*
 ************************************************************************
 *	pins_energia.h
 *
 *	Energia core files for CC3200
 *		Copyright (c) 2014 Robert Wessels. All right reserved.
 *
 ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
 */

#ifndef Pins_Energia_h
#define Pins_Energia_h

#define TARGET_IS_CC3101 1

#ifndef BV
#define BV(x) (1 << (x)) 
#endif 
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/pin.h"

static const uint8_t LED_RED = 19;
static const uint8_t LED_GREEN = 21;
static const uint8_t LED_BLUE = 17;

static const uint8_t PUSH1 = 55;
static const uint8_t PUSH2 = 57;
/*
static const uint8_t A0 = 23;
static const uint8_t A1 = 2;
static const uint8_t A2 = 6;
static const uint8_t A3 = 24;*/
#ifdef ARDUINO_MAIN
const uint32_t port_to_base[] = {
	NOT_A_PORT,
	(uint32_t) GPIOA0_BASE,
	(uint32_t) GPIOA1_BASE,
	(uint32_t) GPIOA2_BASE,
	(uint32_t) GPIOA3_BASE,
};

const uint16_t digital_pin_to_pin_num[] = {
	NOT_A_PIN, /* dummy */
	PIN_01, /* 01 - GPIO10 */
	PIN_02, /* 02 - GPIO11 */
	PIN_03, /* 03 - GPIO12 */
	PIN_04, /* 04 - GPIO13 */
	PIN_05, /* 05 - GPIO14 */
	PIN_06, /* 06 - GPIO15 */
	PIN_07, /* 07 - GPIO16 */
	PIN_08, /* 08 - GPIO17 */
	PIN_09, /* 09 - VDD_DIG1 */
	PIN_10, /* 10 - VINIO1 */
	PIN_11, /* 11 - FLASH_SPI_CLK */
	PIN_12, /* 12 - FLASH_SPI_DOUT */
	PIN_13, /* 13 - FLASH_SPI_DIN */
	PIN_14, /* 14 - FLASH_SPI_CS */
	PIN_15, /* 15 - GPIO22 */
	PIN_16, /* 16 - TDI (GPIO23) */
	PIN_17, /* 17 - TDO (GPIO24) */
	PIN_18, /* 18 - GPIO28 */
	PIN_19, /* 19 - TCK */
	PIN_20, /* 20 - TMS (GPIO29) */
	PIN_21, /* 21 - SOP2 (GPIO25) */
	PIN_22, /* 22 - WLAN_XTAL_N */
	PIN_23, /* 23 - WLAN_XTAL_P */
	PIN_24, /* 24 - VDD_PLL */
	PIN_25, /* 25 - LDO_IN2 */
	PIN_26, /* 26 - NC */
	PIN_27, /* 27 - NC */
	PIN_28, /* 28 - NC */
	PIN_29, /* 29 - ANTSEL1 */
	PIN_30, /* 30 - ANTSEL2 */
	PIN_31, /* 31 - RF_BG */
	PIN_32, /* 32 - nRESET */
	PIN_33, /* 33 - VDD_PA_IN */
	PIN_34, /* 34 - SOP1 */
	PIN_35, /* 35 - SOP0 */
	PIN_36, /* 36 - LDO_IN1 */
	PIN_37, /* 37 - VIN_DCDC_ANA */
	PIN_38, /* 38 - DCDC_ANA_SW */
	PIN_39, /* 39 - VIN_DCDC_PA */
	PIN_40, /* 40 - DCDC_PA_SW_P */
	PIN_41, /* 41 - DCDC_PA_SW_N */
	PIN_42, /* 42 - DCDC_PA_OUT */
	PIN_43, /* 43 - DCDC_DIG_SW */
	PIN_44, /* 44 - VIN_DCDC_DIG */
	PIN_45, /* 45 - DCDC_ANA2_SW_P (GPIO31) */
	PIN_46, /* 46 - DCDC_ANA2_SW_N  */
	PIN_47, /* 47 - VDD_ANA2  */
	PIN_48, /* 48 - VDD_ABA1  */
	PIN_49, /* 49 - VDD_RAM */
	PIN_50, /* 50 - GPIO00 */
	PIN_51, /* 51 - RTC_XTAL_P */
	PIN_52, /* 52 - RTC_XTAL_N (GPIO32) */
	PIN_53, /* 53 - GPIO30 */
	PIN_54, /* 54 - VIN_IO2 */
	PIN_55, /* 55 - GPIO01 */
	PIN_56, /* 56 - VDD_DIG2  */
	PIN_57, /* 57 - GPIO02 */
	PIN_58, /* 58 - GPIO03 */
	PIN_59, /* 59 - GPIO04 */
	PIN_60, /* 60 - GPIO05 */
	PIN_61, /* 61 - GPIO06 */
	PIN_62, /* 62 - GPIO07 */
	PIN_63, /* 63 - GPIO08 */
	PIN_64  /* 64 - GPIO09 */
};

/* from SWRU367A Table 5-14. GPIO Mapping */ 
const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN, /* dummy */
	S1, /* 01 - GPIO10 */
	S1, /* 02 - GPIO11 */
	S1, /* 03 - GPIO12 */
	S1, /* 04 - GPIO13 */
	S1, /* 05 - GPIO14 */
	S1, /* 06 - GPIO15 */
	S2, /* 07 - GPIO16 */
	S2, /* 08 - GPIO17 */
	NOT_A_PIN, /* 09 - VDD_DIG1 */
	NOT_A_PIN, /* 10 - VINIO1 */
	NOT_A_PIN, /* 11 - FLASH_SPI_CLK */
	NOT_A_PIN, /* 12 - FLASH_SPI_DOUT */
	NOT_A_PIN, /* 13 - FLASH_SPI_DIN */
	NOT_A_PIN, /* 14 - FLASH_SPI_CS */
	S2, /* 15 - GPIO22 */
	S2, /* 16 - TDI (GPIO23) */
	S3, /* 17 - TDO (GPIO24) */
	S3, /* 18 - GPIO28 */
	NOT_A_PIN, /* 19 - TCK */
	S3, /* 20 - TMS (GPIO29) */
	S3, /* 21 - SOP2 (GPIO25) */
	NOT_A_PIN, /* 22 - WLAN_XTAL_N */
	NOT_A_PIN, /* 23 - WLAN_XTAL_P */
	NOT_A_PIN, /* 24 - VDD_PLL */
	NOT_A_PIN, /* 25 - LDO_IN2 */
	NOT_A_PIN, /* 26 - NC */
	NOT_A_PIN, /* 27 - NC */
	NOT_A_PIN, /* 28 - NC */
	NOT_A_PIN, /* 29 - ANTSEL1 */
	NOT_A_PIN, /* 30 - ANTSEL2 */
	NOT_A_PIN, /* 31 - RF_BG */
	NOT_A_PIN, /* 32 - nRESET */
	NOT_A_PIN, /* 33 - VDD_PA_IN */
	NOT_A_PIN, /* 34 - SOP1 */
	NOT_A_PIN, /* 35 - SOP0 */
	NOT_A_PIN, /* 36 - LDO_IN1 */
	NOT_A_PIN, /* 37 - VIN_DCDC_ANA */
	NOT_A_PIN, /* 38 - DCDC_ANA_SW */
	NOT_A_PIN, /* 39 - VIN_DCDC_PA */
	NOT_A_PIN, /* 40 - DCDC_PA_SW_P */
	NOT_A_PIN, /* 41 - DCDC_PA_SW_N */
	NOT_A_PIN, /* 42 - DCDC_PA_OUT */
	NOT_A_PIN, /* 43 - DCDC_DIG_SW */
	NOT_A_PIN, /* 44 - VIN_DCDC_DIG */
	S3, /* 45 - DCDC_ANA2_SW_P (GPIO31) */
	NOT_A_PIN, /* 46 - DCDC_ANA2_SW_N  */
	NOT_A_PIN, /* 47 - VDD_ANA2  */
	NOT_A_PIN, /* 48 - VDD_ABA1  */
	NOT_A_PIN, /* 49 - VDD_RAM */
	S0, /* 50 - GPIO00 */
	NOT_A_PIN, /* 51 - RTC_XTAL_P */
	NOT_A_PIN, /* 52 - RTC_XTAL_N (GPIO32) S4?! */
	S3, /* 53 - GPIO30 */
	NOT_A_PIN, /* 54 - VIN_IO2 */
	S0, /* 55 - GPIO01 */
	NOT_A_PIN, /* 56 - VDD_DIG2  */
	S0, /* 57 - GPIO02 */
	S0, /* 58 - GPIO03 */
	S0, /* 59 - GPIO04 */
	S0, /* 60 - GPIO05 */
	S0, /* 61 - GPIO06 */
	S0, /* 62 - GPIO07 */
	S1, /* 63 - GPIO08 */
	S1  /* 64 - GPIO09 */
};

/* from SWRU367A Table 5-14. GPIO Mapping */ 
const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* dummy */
	BV(2), /* 01 - GPIO10 */
	BV(3), /* 02 - GPIO11 */
	BV(4), /* 03 - GPIO12 */
	BV(5), /* 04 - GPIO13 */
	BV(6), /* 05 - GPIO14 */
	BV(7), /* 06 - GPIO15 */
	BV(0), /* 07 - GPIO16 */
	BV(1), /* 08 - GPIO17 */
	NOT_A_PIN, /* 09 - VDD_DIG1 */
	NOT_A_PIN, /* 10 - VINIO1 */
	NOT_A_PIN, /* 11 - FLASH_SPI_CLK */
	NOT_A_PIN, /* 12 - FLASH_SPI_DOUT */
	NOT_A_PIN, /* 13 - FLASH_SPI_DIN */
	NOT_A_PIN, /* 14 - FLASH_SPI_CS */
	BV(6), /* 15 - GPIO22 */
	BV(7), /* 16 - TDI (GPIO23) */
	BV(0), /* 17 - TDO (GPIO24) */
	BV(4), /* 18 - GPIO28 */
	NOT_A_PIN, /* 19 - TCK */
	BV(5), /* 20 - TMS (GPIO29) */
	BV(1), /* 21 - SOP2 (GPIO25) */
	NOT_A_PIN, /* 22 - WLAN_XTAL_N */
	NOT_A_PIN, /* 23 - WLAN_XTAL_P */
	NOT_A_PIN, /* 24 - VDD_PLL */
	NOT_A_PIN, /* 25 - LDO_IN2 */
	NOT_A_PIN, /* 26 - NC */
	NOT_A_PIN, /* 27 - NC */
	NOT_A_PIN, /* 28 - NC */
	NOT_A_PIN, /* 29 - ANTSEL1 */
	NOT_A_PIN, /* 30 - ANTSEL2 */
	NOT_A_PIN, /* 31 - RF_BG */
	NOT_A_PIN, /* 32 - nRESET */
	NOT_A_PIN, /* 33 - VDD_PA_IN */
	NOT_A_PIN, /* 34 - SOP1 */
	NOT_A_PIN, /* 35 - SOP0 */
	NOT_A_PIN, /* 36 - LDO_IN1 */
	NOT_A_PIN, /* 37 - VIN_DCDC_ANA */
	NOT_A_PIN, /* 38 - DCDC_ANA_SW */
	NOT_A_PIN, /* 39 - VIN_DCDC_PA */
	NOT_A_PIN, /* 40 - DCDC_PA_SW_P */
	NOT_A_PIN, /* 41 - DCDC_PA_SW_N */
	NOT_A_PIN, /* 42 - DCDC_PA_OUT */
	NOT_A_PIN, /* 43 - DCDC_DIG_SW */
	NOT_A_PIN, /* 44 - VIN_DCDC_DIG */
	BV(7), /* 45 - DCDC_ANA2_SW_P (GPIO31) */
	NOT_A_PIN, /* 46 - DCDC_ANA2_SW_N  */
	NOT_A_PIN, /* 47 - VDD_ANA2  */
	NOT_A_PIN, /* 48 - VDD_ABA1  */
	NOT_A_PIN, /* 49 - VDD_RAM */
	BV(0), /* 50 - GPIO00 */
	NOT_A_PIN, /* 51 - RTC_XTAL_P */
	NOT_A_PIN, /* 52 - RTC_XTAL_N (GPIO32) S4?! */
	BV(6), /* 53 - GPIO30 */
	NOT_A_PIN, /* 54 - VIN_IO2 */
	BV(1), /* 55 - GPIO01 */
	NOT_A_PIN, /* 56 - VDD_DIG2  */
	BV(2), /* 57 - GPIO02 */
	BV(3), /* 58 - GPIO03 */
	BV(4), /* 59 - GPIO04 */
	BV(5), /* 60 - GPIO05 */
	BV(6), /* 61 - GPIO06 */
	BV(7), /* 62 - GPIO07 */
	BV(8), /* 63 - GPIO08 */
	BV(9)  /* 64 - GPIO09 */
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /* dummy */
	TIMERA3A, /* 01 - GPIO10 */
	TIMERA3B, /* 02 - GPIO11 */
	NOT_ON_TIMER, /* 03 - GPIO12 */
	NOT_ON_TIMER, /* 04 - GPIO13 */
	NOT_ON_TIMER, /* 05 - GPIO14 */
	NOT_ON_TIMER, /* 06 - GPIO15 */
	NOT_ON_TIMER, /* 07 - GPIO16 */
	NOT_ON_TIMER, /* 08 - GPIO17 */
	NOT_ON_TIMER, /* 09 - VDD_DIG1 */
	NOT_ON_TIMER, /* 10 - VINIO1 */
	NOT_ON_TIMER, /* 11 - FLASH_SPI_CLK */
	NOT_ON_TIMER, /* 12 - FLASH_SPI_DOUT */
	NOT_ON_TIMER, /* 13 - FLASH_SPI_DIN */
	NOT_ON_TIMER, /* 14 - FLASH_SPI_CS */
	NOT_ON_TIMER, /* 15 - GPIO22 */
	NOT_ON_TIMER, /* 16 - TDI (GPIO23) */
	TIMERA0A, /* 17 - TDO (GPIO24) */
	NOT_ON_TIMER, /* 18 - GPIO28 */
	NOT_ON_TIMER, /* 19 - TCK */
	NOT_ON_TIMER, /* 20 - TMS (GPIO29) */
	TIMERA1A, /* 21 - SOP2 (GPIO25) */
	NOT_ON_TIMER, /* 22 - WLAN_XTAL_N */
	NOT_ON_TIMER, /* 23 - WLAN_XTAL_P */
	NOT_ON_TIMER, /* 24 - VDD_PLL */
	NOT_ON_TIMER, /* 25 - LDO_IN2 */
	NOT_ON_TIMER, /* 26 - NC */
	NOT_ON_TIMER, /* 27 - NC */
	NOT_ON_TIMER, /* 28 - NC */
	NOT_ON_TIMER, /* 29 - ANTSEL1 */
	NOT_ON_TIMER, /* 30 - ANTSEL2 */
	NOT_ON_TIMER, /* 31 - RF_BG */
	NOT_ON_TIMER, /* 32 - nRESET */
	NOT_ON_TIMER, /* 33 - VDD_PA_IN */
	NOT_ON_TIMER, /* 34 - SOP1 */
	NOT_ON_TIMER, /* 35 - SOP0 */
	NOT_ON_TIMER, /* 36 - LDO_IN1 */
	NOT_ON_TIMER, /* 37 - VIN_DCDC_ANA */
	NOT_ON_TIMER, /* 38 - DCDC_ANA_SW */
	NOT_ON_TIMER, /* 39 - VIN_DCDC_PA */
	NOT_ON_TIMER, /* 40 - DCDC_PA_SW_P */
	NOT_ON_TIMER, /* 41 - DCDC_PA_SW_N */
	NOT_ON_TIMER, /* 42 - DCDC_PA_OUT */
	NOT_ON_TIMER, /* 43 - DCDC_DIG_SW */
	NOT_ON_TIMER, /* 44 - VIN_DCDC_DIG */
	NOT_ON_TIMER, /* 45 - DCDC_ANA2_SW_P (GPIO31) */
	NOT_ON_TIMER, /* 46 - DCDC_ANA2_SW_N  */
	NOT_ON_TIMER, /* 47 - VDD_ANA2  */
	NOT_ON_TIMER, /* 48 - VDD_ABA1  */
	NOT_ON_TIMER, /* 49 - VDD_RAM */
	NOT_ON_TIMER, /* 50 - GPIO00 */
	NOT_ON_TIMER, /* 51 - RTC_XTAL_P */
	NOT_ON_TIMER, /* 52 - RTC_XTAL_N (GPIO32) S4?! */
	NOT_ON_TIMER, /* 53 - GPIO30 */
	NOT_ON_TIMER, /* 54 - VIN_IO2 */
	NOT_ON_TIMER, /* 55 - GPIO01 */
	NOT_ON_TIMER, /* 56 - VDD_DIG2  */
	NOT_ON_TIMER, /* 57 - GPIO02 */
	NOT_ON_TIMER, /* 58 - GPIO03 */
	NOT_ON_TIMER, /* 59 - GPIO04 */
	NOT_ON_TIMER, /* 60 - GPIO05 */
	NOT_ON_TIMER, /* 61 - GPIO06 */
	NOT_ON_TIMER, /* 62 - GPIO07 */
	NOT_ON_TIMER, /* 63 - GPIO08 */
	TIMERA2B /* 64 - GPIO09 */
};

#endif
#endif
