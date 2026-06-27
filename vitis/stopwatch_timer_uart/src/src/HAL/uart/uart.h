/*
 * UART.h
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#ifndef SRC_HAL_UART_UART_H_
#define SRC_HAL_UART_UART_H_

#include "xparameters.h"
#include <stdint.h>

#define UART_BASEADDR XPAR_UART_0_S00_AXI_BASEADDR

typedef struct {
	volatile uint32_t TX;   // slv_reg0, 0x00
	volatile uint32_t SR;   // slv_reg1, 0x04
	volatile uint32_t RX;   // slv_reg2, 0x08
	volatile uint32_t IER;  // slv_reg3, 0x0C
} UART_TypeDef;

#define UART ((UART_TypeDef *)UART_BASEADDR)

/* slv_reg0 */
#define UART_TX_START_Pos      0
#define UART_TX_START_Msk      (1U << UART_TX_START_Pos)

#define UART_TX_DATA_Pos       8
#define UART_TX_DATA_Msk       (0xFFU << UART_TX_DATA_Pos)
#define UART_TX_DATA(x)        (((uint32_t)(x) << UART_TX_DATA_Pos) & UART_TX_DATA_Msk)

/* slv_reg1 */
#define UART_SR_TX_READY_Pos   0
#define UART_SR_TX_READY_Msk   (1U << UART_SR_TX_READY_Pos)

#define UART_SR_RX_VALID_Pos   1
#define UART_SR_RX_VALID_Msk   (1U << UART_SR_RX_VALID_Pos)

/* slv_reg2 */
#define UART_RX_DATA_Pos       0
#define UART_RX_DATA_Msk       (0xFFU << UART_RX_DATA_Pos)

/* slv_reg3 */
#define UART_IER_RX_EN_Pos     0
#define UART_IER_RX_EN_Msk     (1U << UART_IER_RX_EN_Pos)

void UART_Init(UART_TypeDef *uart);
void UART_SendData(UART_TypeDef *uart, uint8_t data);
void UART_SendString(UART_TypeDef *uart, const char *data);
uint8_t UART_ReceiveData(UART_TypeDef *uart);
void UART_ClearRxValid(UART_TypeDef *uart);
uint32_t UART_IsTxReady(UART_TypeDef *uart);
uint32_t UART_IsRxValid(UART_TypeDef *uart);
void UART_EnableRxInterrupt(UART_TypeDef *uart);
void UART_DisableRxInterrupt(UART_TypeDef *uart);

#endif /* SRC_HAL_UART_UART_H_ */
