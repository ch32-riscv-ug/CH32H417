/********************************** (C) COPYRIGHT  *******************************
* File Name          : hardware.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2025/03/01
* Description        : This file provides all the hardware firmware functions.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "hardware.h"

/* Global typedef */

/* Global define */

/* Global Variable */




/* main is just one of the threads, in addition to tshell,idle
 *    main is just an LED blinking, the main thread is registered in rtthread_startup,
 *    tshell uses the serial port to receive interrupts, and the interrupt stack and thread stack are
 *    used separately.Note that when entering an interrupt, the 16caller register needs to be pushed 
 *    into the thread stack
 */

/*********************************************************************
 * @fn      Hardware
 *
 * @brief   Resets the CRC Data register (DR).
 *
 * @return  none
 */
void Hardware(void)
{
    

}


