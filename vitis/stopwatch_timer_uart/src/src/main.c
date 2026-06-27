#include <stdint.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xuartlite_l.h"
#include "ap/stopwatch.h"
#include "common/delay/delay.h"
#include "common/Interrupt/interrupt.h"
#include "HAL/TIMER/TIMER.h"



int main()
{

	stopwatch_Init();
	TIMER_SetPSC(TMR0, 100-1);
			TIMER_SetARR(TMR0, 1000-1);
			TIMER_StartInterrupt(TMR0);
			TIMER_StartTimer(TMR0);
					SetupInterruptSystem();

	xil_printf("terminal ready\r\n");

	while(1)
	{

		stopwatch_Excute();
							stopwatch_ControlLed();
		/***************polling service routine***********************/

	}
	return 0;
}
