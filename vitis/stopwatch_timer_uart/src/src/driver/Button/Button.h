/*
 * Button.h
 *
 *  Created on: 2026. 6. 24.
 *      Author: kccistc
 */

#ifndef SRC_DRIVER_BUTTON_BUTTON_H_
#define SRC_DRIVER_BUTTON_BUTTON_H_

#include "../../HAL/GPIO/GPIO.h"
typedef enum{
	NO_ACT=0,
	ACT_PUSHED,
	ACT_RELEASED
}Button_status_e;

typedef enum{
	RELEASED=0,
	PUSHED
}button_state_e;

typedef struct{
	GPIO_TYPEDEF *GPIOx;
	uint32_t gpio_pin;
	button_state_e prevState;
}hbutton;

extern hbutton hbtnRunStop, hbtnClear;
extern hbutton hbtnLeft, hbtnRight;

void Button_Init();
void Button_SetInit(hbutton *hbtn, GPIO_TYPEDEF *GPIOx, uint32_t gpio_pin);
uint32_t Button_GetState(hbutton *hbtn);

#endif /* SRC_DRIVER_BUTTON_BUTTON_H_ */
