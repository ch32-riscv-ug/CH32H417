/********************************** (C) COPYRIGHT  *******************************
* File Name          : hardware.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2025/03/01
* Description        : This file provides all the CRC firmware functions.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "hardware.h"

/* Global define */
#define Buf_Size 32

/* Global define */
#define Num    7
u16 DAC_Value[Num] = {64, 128, 256, 512, 1024, 2048, 4095};

/*********************************************************************
 * @fn      Dac_Init
 *
 * @brief   Initializes DAC collection.
 *
 * @return  none
 */
void Dac_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    DAC_InitTypeDef  DAC_InitType = {0};

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOA, ENABLE);
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_DAC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    DAC_InitType.DAC_Trigger = DAC_Trigger_None;
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1, &DAC_InitType);
    DAC_Cmd(DAC_Channel_1, ENABLE);

    DAC_SetChannel1Data(DAC_Align_12b_R, 0);
}

/*********************************************************************
 * @fn      DAC1_Nosie_Gen_Test
 *
 * @brief   Noise wava generation test.
 *
 * @return  none
 */
void DAC1_Nosie_Gen_Test(void)
{
    DAC->SWTR |= 0x01; /* Set by software, Reset by hardware */
    __asm volatile("nop");
    #if 0
    printf("DOR1=0x%04x\r\n", DAC->DOR1); /* Value will be 0x0AAA,0x0D55,0x0EAA ... */
    #endif
}

/*********************************************************************
 * @fn      Hardware
 *
 * @brief   DAC channel 0 (PA4) output.
 *
 * @return  none
 */
void Hardware(void)
{
    u8 i = 0;

    printf("Noise Wava Generation Test\r\n");
    Dac_Init();

    while(1)
    {
            for(i = 0; i < Num; i++)
        {
            DAC_SetChannel1Data(DAC_Align_12b_R, DAC_Value[i]);
            Delay_Ms(1000);
        }
    }
}
