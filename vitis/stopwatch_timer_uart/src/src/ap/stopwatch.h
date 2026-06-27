/*
 * stopwatch.h
 *
 *  Created on: 2026. 6. 24.
 *      Author: kccistc
 */

#ifndef SRC_AP_STOPWATCH_H_
#define SRC_AP_STOPWATCH_H_

#include "../HAL/GPIO/GPIO.h"
#include "../DRIVER/FND/FND.h"
#include "../DRIVER/Button/Button.h"
#include "../DRIVER/LED/LED.h"
#include "../DRIVER/Switch/Switch.h"
typedef enum{
	STOP=0,
	RUN,
	CLEAR
}stopWatch_e;

stopWatch_e stopWatchState;
void stopwatch_Init();
void stopwatch_SetCounter(uint32_t value);
void stopwatch_Excute();
void stopwatch_ControlState();
void stopwatch_ReceiveCommand();
void stopwatch_SendCounterOnSwitch();
void stopwatch_RunTime();
void stopwatch_ControlLed();
void stopwatch_StopLed();
void stopwatch_RunLed();
void stopwatch_ClearLed();

#endif /* SRC_AP_STOPWATCH_H_ */
