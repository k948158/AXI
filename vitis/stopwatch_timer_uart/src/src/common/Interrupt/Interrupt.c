/*
 * Interrupt.c
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#include "interrupt.h"
#include "xparameters.h"
#include "xintc.h"
#include "xil_exception.h"
#include "../delay/delay.h"
#include "../../HAL/uart/uart.h"
#include "../../driver/FND/FND.h"

XIntc	IntrController;
volatile uint8_t uartRxData;
volatile uint32_t uartRxFlag;

void TMR_ISR(void *CallbackRef) //TIMER
{
	FND_Excute();
	incTick();
}

void UART_ISR(void *CallbackRef)
{
	(void)CallbackRef;

	if (UART_IsRxValid(UART)) {
		uartRxData = UART_ReceiveData(UART);
		uartRxFlag = 1;
	}
}

int SetupInterruptSystem()
{
	int status;
	//****1. 인터럽트 컨트롤러 초기화 (변경 없음)

	status = XIntc_Initialize(&IntrController, INTC_DEV_ID);
	if(status != XST_SUCCESS){
		return XST_FAILURE;
	}
	//2-1/ TMR_ISR 함수를 Intc와 연결
	status = XIntc_Connect(&IntrController, TMR_VEC_ID, (XInterruptHandler)TMR_ISR, (void *)0);
	if(status != XST_SUCCESS){
		return XST_FAILURE;
	}

	status = XIntc_Connect(&IntrController, UART_VEC_ID, (XInterruptHandler)UART_ISR, (void *)0);
	if(status != XST_SUCCESS){
		return XST_FAILURE;
	}

	//*****3. Interrupt COntroller 시작 (Hardware Mode) (변경 없음)
	status = XIntc_Start(&IntrController, XIN_REAL_MODE);
	if(status != XST_SUCCESS){
			return XST_FAILURE;
		}

	//4. 각각의 인터럽트 채널 활성화
	UART_Init(UART);
	XIntc_Enable(&IntrController, TMR_VEC_ID);
	XIntc_Enable(&IntrController, UART_VEC_ID);

	//*******5. Microblazedml Exception 초기화 및 활성화 (변경 없음)
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &IntrController);
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}
