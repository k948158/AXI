/*
 * TIMER.c
 *
 *  Created on: 2026. 6. 26.
 *      Author: kccistc
 */

#include "TIMER.h"

void TIMER_SetPSC(TIMER_TypeDef_t *tmr, uint32_t psc)
{
	tmr->PSC = psc;
}

uint32_t TIMER_GetPSC(TIMER_TypeDef_t *tmr)
{
	return tmr->PSC;
}

void TIMER_SetARR(TIMER_TypeDef_t *tmr, uint32_t arr)
{
	tmr->ARR = arr;
}


uint32_t TIMER_GetARR(TIMER_TypeDef_t *tmr)
{
	return tmr->ARR;
}

void TIMER_SetCNT(TIMER_TypeDef_t *tmr, uint32_t cnt)
{
	tmr->CNT = cnt;
}


uint32_t TIMER_GetCNT(TIMER_TypeDef_t *tmr)
{
	return tmr->CNT;
}

void TIMER_StartTimer(TIMER_TypeDef_t *tmr)
{
	tmr->CR |= (1<<TIMER_EN_BIT);
}

void TIMER_StopTimer(TIMER_TypeDef_t *tmr)
{
	tmr->CR &= ~(1<<TIMER_EN_BIT);
}

void TIMER_StartInterrupt(TIMER_TypeDef_t *tmr)
{
	tmr->CR |=1<<TIMER_IE_BIT;
}

void TIMER_StopInterrupt(TIMER_TypeDef_t *tmr)
{
	tmr->CR &= ~(1<<TIMER_IE_BIT);
}
