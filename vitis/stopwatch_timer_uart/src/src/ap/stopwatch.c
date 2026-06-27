/*
 * stopwatch.c
 *
 *  Created on: 2026. 6. 24.
 *      Author: kccistc
 */

#include "stopwatch.h"
#include "../common/delay/delay.h"
#include "../HAL/uart/uart.h"
#include "../common/Interrupt/Interrupt.h"

#define STOP_STATE_LED 5
#define RUN_STATE_LED 7

#define UART_CMD_RUN_STOP 'T'
#define UART_CMD_CLEAR    'C'

uint32_t	counter;
uint32_t	stopWatchLed;
uint32_t stopWatchStateLed;
void stopwatch_Init(){
	LED_Init();
	FND_Init();
	Button_Init();
	Switch_Init();

	stopWatchState = STOP;
	stopWatchLed=1;
	stopWatchStateLed= 0;
}

void stopwatch_SetCounter(uint32_t value)
{
	counter = value;
}

void stopwatch_Excute(){

	stopwatch_RunTime();
	stopwatch_ControlState();
	stopwatch_ReceiveCommand();
	stopwatch_SendCounterOnSwitch();
	FND_SetNum(counter);

}

void stopwatch_SendCounterOnSwitch()
{
	char tx_data[13];
	char reversedDigits[10];
	uint32_t value;
	uint32_t digitCount = 0;
	uint32_t txIndex = 0;

	if (!Switch0_IsTurnedOn()) {
		return;
	}

	value = counter;
	tx_data[txIndex++] = 'N';

	do {
		reversedDigits[digitCount++] = (char)('0' + (value % 10U));
		value /= 10U;
	} while (value != 0U);

	while (digitCount != 0U) {
		tx_data[txIndex++] = reversedDigits[--digitCount];
	}

	tx_data[txIndex++] = '\n';
	tx_data[txIndex] = '\0';
	UART_SendString(UART, tx_data);
}
void stopwatch_ControlState()
{
	uint32_t runStopState = Button_GetState(&hbtnRunStop);
	uint32_t clearState = Button_GetState(&hbtnClear);
	uint32_t leftState = Button_GetState(&hbtnLeft);
	uint32_t rightState = Button_GetState(&hbtnRight);

	if (leftState == ACT_PUSHED) {
		UART_SendData(UART, UART_CMD_RUN_STOP);
	}

	if (rightState == ACT_PUSHED) {
		UART_SendData(UART, UART_CMD_CLEAR);
	}

	if (clearState == ACT_PUSHED) {
		stopWatchState = CLEAR;
		return;
	}

	switch(stopWatchState){
		case STOP:
			if(runStopState == ACT_PUSHED){
				stopWatchState = RUN;
			}

			break;
		case RUN:
			if(runStopState == ACT_PUSHED){
				stopWatchState = STOP;
			}

			break;
		case CLEAR:
			stopWatchState = STOP;
			counter =0;
			break;
		default:
			stopWatchState=STOP;
			break;
		}
}

void stopwatch_ReceiveCommand()
{
    static uint32_t rxNumber = 0;
    static uint8_t rxNumberMode = 0;

    if (uartRxFlag == 0) {
        return;
    }

    uartRxFlag = 0;

    switch (uartRxData) {
        case UART_CMD_RUN_STOP:
            if (stopWatchState == RUN) {
                stopWatchState = STOP;
            } else {
                stopWatchState = RUN;
            }
            rxNumberMode = 0;
            break;

        case UART_CMD_CLEAR:
            stopWatchState = CLEAR;
            rxNumberMode = 0;
            break;

        case 'N':
            rxNumber = 0;
            rxNumberMode = 1;
            break;

        case '\n':
            if (rxNumberMode) {
                counter = rxNumber;
                rxNumberMode = 0;
            }
            break;

        default:
            if (rxNumberMode && uartRxData >= '0' && uartRxData <= '9') {
                rxNumber = (rxNumber * 10) + (uartRxData - '0');
            }
            break;
    }
}

void stopwatch_RunTime(){

	static uint32_t prevTime =0 ;
	uint32_t curTime = millis();

	if(curTime-prevTime<100) return;
	prevTime=curTime;
	if(stopWatchState == RUN) {
		counter++;
	}
}

void stopwatch_ControlLed(){
	switch(stopWatchState){
	case STOP:
		stopwatch_StopLed();
		break;
	case RUN:
			stopwatch_RunLed();
			break;
	case CLEAR:
		stopwatch_ClearLed();
			break;
	default:
		stopwatch_ClearLed();
		break;
	}
}
void stopwatch_StopLed(){
	stopWatchStateLed |= (1<<STOP_STATE_LED);
	stopWatchStateLed &= ~(1 << RUN_STATE_LED);
	LED_WritePort8(LED_HI_GPIO, stopWatchStateLed);

}

void stopwatch_RunLed(){
	static uint32_t prevTime =0 ;
	uint32_t curTime = millis();

	stopWatchStateLed &= ~(1<<STOP_STATE_LED);
	stopWatchStateLed |= (1 << RUN_STATE_LED);
	LED_WritePort8(LED_HI_GPIO, stopWatchStateLed);

	if(curTime-prevTime<100) return;
	prevTime=curTime;
	stopWatchLed= ((stopWatchLed<<1)|(stopWatchLed>>7));
	LED_WritePort8(LED_LOW_GPIO, stopWatchLed);
}

void stopwatch_ClearLed(){
	stopWatchLed= 0x01;
	LED_WritePort8(LED_LOW_GPIO, stopWatchLed);
}
