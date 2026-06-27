#include "GPIO.h"


void GPIO_SetMode(GPIO_TYPEDEF *GPIOx, int mode)
{
	GPIOx->CR = mode;
}

void GPIO_WritePort(GPIO_TYPEDEF *GPIOx, uint32_t data)
{
	GPIOx->ODR = data;
}

void GPIO_WritePin(GPIO_TYPEDEF *GPIOx, uint32_t gpio_pin, uint32_t gpio_pin_state)
{
	if(gpio_pin_state == GPIO_SET){
		GPIOx->ODR |=gpio_pin;
	}
	else {
		GPIOx->ODR &= ~gpio_pin;
	}
}

uint32_t GPIO_ReadPort(GPIO_TYPEDEF *GPIOx)
{
	return GPIOx->IDR;
}

uint32_t GPIO_ReadPin(GPIO_TYPEDEF *GPIOx, uint32_t gpio_pin)
{
	return (GPIOx->IDR & gpio_pin) ? 1:0;
}

uint32_t GPIO_GetODR(GPIO_TYPEDEF *GPIOx)
{
	return GPIOx->ODR;
}

uint32_t GPIO_GetCR(GPIO_TYPEDEF *GPIOx)
{
	return GPIOx->CR;
}
