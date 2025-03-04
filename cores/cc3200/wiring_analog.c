/*
 ************************************************************************
 *	wiring_analog.c
 *
 *	Energia core files for MSP430
 *	Copyright (c) 2014 Robert Wessels. All right reserved.
 *
 *
 ***********************************************************************
  Derived from:
  wiring_analog.c - analog input and output
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

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

#include "wiring_private.h"
#include <driverlib/prcm.h>
#include <driverlib/rom_map.h>
#include <driverlib/pin.h>
#include <driverlib/timer.h>
#include <driverlib/adc.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gprcm.h>
#include <inc/hw_adc.h>

#define TIMER_INTERVAL_RELOAD   40035//255*157
#define DUTYCYCLE_GRANULARITY   157

static int _readResolution = 12;

void PWMPrepare(uint8_t pin) {
	uint8_t timer = digitalPinToTimer(pin);
	MAP_PRCMPeripheralClkEnable(PRCM_TIMERA0 + (timer/2), PRCM_RUN_MODE_CLK);

	uint32_t base = TIMERA0_BASE + ((timer/2) << 12);
	uint16_t pnum = digitalPinToPinNum(pin);

	switch(timer) {
	/* PWM0/1 */
	case TIMERA0A:
	case TIMERA0B:
		MAP_PinTypeTimer(pnum, PIN_MODE_5);
		break;
	/* PWM2/3 */
	case TIMERA1A:
		MAP_PinTypeTimer(pnum, PIN_MODE_9);
		break;
	case TIMERA1B:
		MAP_PinTypeTimer(pnum, PIN_MODE_8);
		break;
	/* PWM4/5 */
	case TIMERA2A:
	case TIMERA2B:
		MAP_PinTypeTimer(pnum, PIN_MODE_3);
		break;
	/* PWM6/7 */
	case TIMERA3A:
	case TIMERA3B:
		MAP_PinTypeTimer(pnum, PIN_MODE_3);
		break;
	}
	MAP_TimerConfigure(base, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);
}

void PWMWrite(uint8_t pin, uint32_t analog_res, uint32_t duty, uint32_t freq)
{
	analog_res = analog_res * 1000;
	freq;

	uint32_t load = (F_CPU / freq) * 1000;
	uint32_t match = load / (analog_res / duty);

	match = match;
	load = load / 1000;

	uint16_t prescaler = load >> 16;
	uint16_t prescaler_match = match >> 16;

	uint8_t timer = digitalPinToTimer(pin);

	if(timer == NOT_ON_TIMER)
		return;

	uint32_t base = TIMERA0_BASE + ((timer/2) << 12);

	uint16_t timerab = timer % 2 ? TIMER_B : TIMER_A;
	MAP_TimerPrescaleSet(base, timerab, prescaler);
	MAP_TimerPrescaleMatchSet(base, timerab, prescaler_match);

	MAP_TimerControlLevel(base, timerab, 1);

	MAP_TimerLoadSet(base, timerab, load);

	MAP_TimerMatchSet(base, timerab, match);

	MAP_TimerEnable(base, timerab);
}

void analogWrite(uint8_t pin, int val) {
	/* duty cycle(%) = val / 255;
	 * Frequency of 490Hz specified by Arduino API */
	uint8_t timer = digitalPinToTimer(pin);

	if(timer == NOT_ON_TIMER)
		return;

	if (val == 0) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		return;
	}

	if (val >= 255) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
		return;
	}

	PWMWrite(pin, 255, val, 490);
}

void analogReadResolution(int res) {
    _readResolution = res;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
    if (from == to)
        return value;
    if (from > to)
        return value >> (from-to);
    else
        return value << (to-from);
}

#define MAX_NO_OF_SAMPLES 256
uint16_t pulAdcSamples[MAX_NO_OF_SAMPLES];
uint16_t analogReadAvg(uint8_t pin, uint8_t samplesCount) {
    uint16_t channel;
    uint16_t pinNum = digitalPinToPinNum(pin);
	uint8_t uiIndex = 0;
	volatile uint32_t averageSample = 0;

    switch(pinNum) {
        /* case PIN_57: {channel = ADC_CH_0;}break; */
        case PIN_58: {channel = ADC_CH_1;}break;
        case PIN_59: {channel = ADC_CH_2;}break;
        case PIN_60: {channel = ADC_CH_3;}break;
        default: return 0;
    }

    MAP_PinTypeADC(pinNum, PIN_MODE_255);
	MAP_ADCTimerConfig(ADC_BASE, 0x1FFFF); // Configure ADC timer which is used to timestamp the ADC data samples
	MAP_ADCTimerEnable(ADC_BASE); // Enable ADC timer which is used to timestamp the ADC data samples
	MAP_ADCEnable(ADC_BASE); // Enable ADC module
	MAP_ADCChannelEnable(ADC_BASE, channel); // Enable ADC channel

	while(MAP_ADCFIFOLvlGet(ADC_BASE, channel)) { // flush the channel's FIFO if not empty
        MAP_ADCFIFORead(ADC_BASE, channel);
    }

	while (uiIndex < samplesCount) {
		if (MAP_ADCFIFOLvlGet(ADC_BASE, channel)) {
			pulAdcSamples[uiIndex++] = MAP_ADCFIFORead(ADC_BASE, channel) & 0x3FFF;
			averageSample += pulAdcSamples[uiIndex-1];
		}
	}

    MAP_ADCDisable(ADC_BASE);
    MAP_ADCChannelDisable(ADC_BASE, channel);
    MAP_ADCTimerDisable(ADC_BASE);

	averageSample = averageSample/samplesCount;
	return averageSample;

	
	/*
	MAP_PinTypeADC(pinNum, PIN_MODE_255);
	
	while(ADCFIFOLvlGet(ADC_BASE, channel)) { // flush the channel's FIFO if not empty
        ADCFIFORead(ADC_BASE, channel);
    }

    ADCChannelEnable(ADC_BASE, channel);
    ADCTimerConfig(ADC_BASE,0x1ffff);
    ADCTimerEnable(ADC_BASE);
    ADCEnable(ADC_BASE);

    while(!ADCFIFOLvlGet(ADC_BASE, channel));
    val = ADCFIFORead(ADC_BASE, channel) & 0x3FFF;

    ADCDisable(ADC_BASE);
    ADCChannelDisable(ADC_BASE, channel);
    ADCTimerDisable(ADC_BASE);

    val = val >> 2;
    return mapResolution(val, 12, _readResolution);*/
}

uint16_t analogRead(uint8_t pin) {
	return analogReadAvg(pin, 1);
}

