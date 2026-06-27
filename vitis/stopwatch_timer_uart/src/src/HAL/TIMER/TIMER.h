/*
 * TIMER.h
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#ifndef SRC_SRC_HAL_TIMER_TIMER_H_
#define SRC_SRC_HAL_TIMER_TIMER_H_

#include "xparameters.h"
#include <stdint.h>

typedef struct{
	uint32_t CR;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t CNT;
}TIMER_TypeDef_t;

#define TIMER0_BASEADDR XPAR_TIMER_0_S00_AXI_BASEADDR
#define TMR0	((TIMER_TypeDef_t *)TIMER0_BASEADDR)

#define TIMER_EN_BIT 0
#define TIMER_IE_BIT 1

void TIMER_SetPSC(TIMER_TypeDef_t *tmr, uint32_t psc);
uint32_t TIMER_GetPSC(TIMER_TypeDef_t *tmr);
void TIMER_SetARR(TIMER_TypeDef_t *tmr, uint32_t arr);
uint32_t TIMER_GetARR(TIMER_TypeDef_t *tmr);
void TIMER_SetCNT(TIMER_TypeDef_t *tmr, uint32_t cnt);
uint32_t TIMER_GetCNT(TIMER_TypeDef_t *tmr);
void TIMER_StartTimer(TIMER_TypeDef_t *tmr);
void TIMER_StopTimer(TIMER_TypeDef_t *tmr);
void TIMER_StartInterrupt(TIMER_TypeDef_t *tmr);
void TIMER_StopInterrupt(TIMER_TypeDef_t *tmr);

#endif /* SRC_SRC_HAL_TIMER_TIMER_H_ */
