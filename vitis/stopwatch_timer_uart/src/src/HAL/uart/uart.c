/*
 * UART.c
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#include "uart.h"

uint32_t UART_IsTxReady(UART_TypeDef *uart)
{
	return (uart->SR & UART_SR_TX_READY_Msk) != 0;
}

uint32_t UART_IsRxValid(UART_TypeDef *uart)
{
	return (uart->SR & UART_SR_RX_VALID_Msk) != 0;
}

void UART_ClearRxValid(UART_TypeDef *uart)
{
	uart->SR = UART_SR_RX_VALID_Msk;
}

void UART_EnableRxInterrupt(UART_TypeDef *uart)
{
	uart->IER = UART_IER_RX_EN_Msk;
}

void UART_DisableRxInterrupt(UART_TypeDef *uart)
{
	uart->IER = 0;
}

void UART_Init(UART_TypeDef *uart)
{
	UART_ClearRxValid(uart);
	UART_EnableRxInterrupt(uart);
}

void UART_SendData(UART_TypeDef *uart, uint8_t data)
{
	while (!UART_IsTxReady(uart));

	uart->TX = UART_TX_DATA(data) | UART_TX_START_Msk;

	while (!UART_IsTxReady(uart));
}

void UART_SendString(UART_TypeDef *uart, const char *data)
{
	while (*data != '\0') {
		UART_SendData(uart, (uint8_t)*data);
		data++;
	}
}

uint8_t UART_ReceiveData(UART_TypeDef *uart)
{
	uint8_t data = (uint8_t)((uart->RX & UART_RX_DATA_Msk) >> UART_RX_DATA_Pos);
	UART_ClearRxValid(uart);
	return data;
}
