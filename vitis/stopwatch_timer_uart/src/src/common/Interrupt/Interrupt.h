/*
 * Interrupt.h
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#ifndef SRC_SRC_COMMON_INTERRUPT_INTERRUPT_H_
#define SRC_SRC_COMMON_INTERRUPT_INTERRUPT_H_

#include "xparameters.h"
#include "xintc.h"
#include "xil_exception.h"
#include <stdint.h>

//#define INTC_DEV_ID	XPAR_INTC_0_DEVICE_ID
//#define TMR_DEV_ID	XPAR_TIMER_0_DEVICE_ID

#define INTC_DEV_ID	XPAR_INTC_0_DEVICE_ID
#define TMR_VEC_ID	XPAR_INTC_0_TIMER_0_VEC_ID
#define UART_VEC_ID	XPAR_INTC_0_UART_0_VEC_ID

extern volatile uint8_t uartRxData;
extern volatile uint32_t uartRxFlag;

void TMR_ISR(void *CallbackRef);
void UART_ISR(void *CallbackRef);
int SetupInterruptSystem();

#endif /* SRC_SRC_COMMON_INTERRUPT_INTERRUPT_H_ */
