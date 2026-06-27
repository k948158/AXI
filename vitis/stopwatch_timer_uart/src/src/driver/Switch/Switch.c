/*
 * Switch.c
 */

#include "Switch.h"

static uint32_t switch0PrevState;

void Switch_Init(void)
{
	uint32_t gpioMode = GPIO_GetCR(SWITCH_GPIO);

	gpioMode &= ~SWITCH_0_PIN;
	GPIO_SetMode(SWITCH_GPIO, gpioMode);
	switch0PrevState = GPIO_ReadPin(SWITCH_GPIO, SWITCH_0_PIN);
}

uint32_t Switch0_IsTurnedOn(void)
{
	uint32_t currentState = GPIO_ReadPin(SWITCH_GPIO, SWITCH_0_PIN);
	uint32_t turnedOn = (switch0PrevState == 0U) && (currentState != 0U);

	switch0PrevState = currentState;
	return turnedOn;
}
