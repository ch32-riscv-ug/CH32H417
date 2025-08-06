/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/03/01
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 Complementary output and deadband insertion mode routines:
 TIM8_CH1(PC6),TIM8_CH1N(PA5)
 This example demonstrates three complementary output modes with dead zone of TIM1: complementary output
 with dead zone insertion, dead zone waveform delay Greater than the negative pulse, the dead zone waveform
  delay is greater than the positive pulse.
 
*/

#include "debug.h"
#include "hardware.h"

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

	SystemAndCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	printf("V5F SystemCoreClk:%d\r\n", SystemCoreClock);

	Delay_Ms(500);

#if (Run_Core == Run_Core_V3FandV5F)
	HSEM_FastTake(HSEM_ID0);
	HSEM_ReleaseOneSem(HSEM_ID0, 0);


#elif (Run_Core == Run_Core_V3F)
	

#elif (Run_Core == Run_Core_V5F)

    Hardware();
	
#endif


	while(1)
	{

	}
}
