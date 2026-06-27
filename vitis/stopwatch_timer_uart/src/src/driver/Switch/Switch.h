/*
 * Switch.h
 */

#ifndef SRC_DRIVER_SWITCH_SWITCH_H_
#define SRC_DRIVER_SWITCH_SWITCH_H_

#include "../../HAL/GPIO/GPIO.h"

#define SWITCH_GPIO  GPIOD
#define SWITCH_0_PIN GPIO_PIN_0

void Switch_Init(void);
uint32_t Switch0_IsTurnedOn(void);

#endif /* SRC_DRIVER_SWITCH_SWITCH_H_ */
