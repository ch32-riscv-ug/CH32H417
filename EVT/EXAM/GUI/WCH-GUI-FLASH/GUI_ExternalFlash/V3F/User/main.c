/********************************** (C) COPYRIGHT *******************************
 * File Name          : main_v3f.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/03/01
 * Description        : Main program body for V3F.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 A demo for wui
  pins: 
    FLASH_CS   -- PA4
    FLASH_DO   -- PA6
    FLASH_DI   -- PA7
    FLASH_CLK  -- PA5
    
    LCD_BLK    -- PB14
    LCD_DC     -- PB10
    LCD_RST    -- PB11
    LCD_CS     -- PB12
    LCD_SCK    -- PB13
    LCD_SDA    -- PC1

    ENC_A      -- PB4  (TIM3_CH1, AF2)
    ENC_B      -- PB5  (TIM3_CH2, AF2)
    ENC_KEY    -- PB0
*/
/*********************************IMPORTANT!******************************
  Set WUI_INTERNAL_FLASH (images.h) to select resource 
 location: 0 = external SPI flash, 1 = internal flash.
 *********************************IMPORTANT!******************************/

#include <math.h>
#include "debug.h"
#include "string.h"
#include "lcd.h"
#include "flash.h"
#include "config.h"
#include "wui.h"
#include "wui_port.h"
#include "wui_user/wui_page.h"

/* UI time base: TIM4 counts at 8 kHz (125 us), 8 counts = 1 ms */
#define TIM_PCK (8000ul)

#define ENC_KEY_PORT GPIOB
#define ENC_KEY_PIN  (GPIO_Pin_0)
#define ENC_KEY()    ((ENC_KEY_PORT->INDR & ENC_KEY_PIN) == 0)

static uint32_t key3_state = 0;
static uint8_t  wui_heap_buffer[4 * 1024];

/*********************************************************************
 * @fn      TIM4_init
 *
 * @brief   Initialize TIM4 as the WCHGUI UI time base
 *
 * @return  none.
 */
void TIM4_init(void)
{
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    TIM_Cmd(TIM4, DISABLE);

    TIM_TimeBaseInitStructure.TIM_Period        = 0xffff;
    TIM_TimeBaseInitStructure.TIM_Prescaler     = ((SystemCoreClock) / TIM_PCK) - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ARRPreloadConfig(TIM4, DISABLE);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);

    TIM_Cmd(TIM4, ENABLE);
}

/*********************************************************************
 * @fn      TIM3_Encoder_Init
 *
 * @brief   Initialize TIM3 encoder interface: PB4=TIM3_CH1, PB5=TIM3_CH2 (AF2)
 *
 * @return  none.
 */
void TIM3_Encoder_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef       TIM_ICInitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure = {0};

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOB | RCC_HB2Periph_AFIO, ENABLE);
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_TIM3, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF2);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler     = 0x0;
    TIM_TimeBaseStructure.TIM_Period        = 160;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInitStructure.TIM_Channel  = TIM_Channel_1;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel  = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE);
}

/*********************************************************************
 * @fn      iabs
 *
 * @brief   Compute the absolute value of a signed 32-bit integer.
 *
 * @return  Absolute value of a
 */
uint32_t static inline iabs(int32_t a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

/*********************************************************************
 * @fn      check_direction
 *
 * @brief   Detect the rotation direction of the encoder
 *
 * @return  direction The direction of the encoder's rotation
 */
int32_t check_direction(int current_value)
{
    static int last_value = 0;

    if (current_value == last_value)
    {
        return 0;
    }

    int diff = current_value - last_value;
    if (iabs(diff) < 4)
    {
        return 0;
    }

    int32_t direction;

    if (iabs(diff) < 80)
    {
        direction = (diff > 0) ? 1 : -1;
    }
    else
    {
        direction = (diff > 0) ? -1 : 1;
    }

    last_value = current_value;
    return direction;
}

/*********************************************************************
 * @fn      Key_GPIOInit
 *
 * @brief   Initialize the encoder key pin
 *
 * @return  none.
 */
void Key_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = ENC_KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENC_KEY_PORT, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	SystemInit();
	SystemAndCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	Delay_Ms(1000);

	printf("SystemClk:%d\r\n", SystemClock);
	printf("V3F SystemCoreClk:%d\r\n", SystemCoreClock);

	SPI_FLASH_Init();
	printf("flash_id %x\r\n", SPI_Flash_ReadJedecDeviceID());

	LCD_Init();

	TIM3_Encoder_Init();
	TIM4_init();
	Key_GPIOInit();

	wui_init_data_t data = {
	    .page_count = WUI_PAGE_COUNT,
	    .width      = LCD_WIDTH,
	    .height     = LCD_HEIGHT,
	    .heap_addr  = wui_heap_buffer,
	    .heap_size  = sizeof(wui_heap_buffer),
	};

	wui_init(&data);
	wui_register_hal(wui_get_hal());
	wui_page_switch(WUI_START_PAGE);

	while (1)
	{
		uint16_t now = TIM4->CNT;
		if (now > 16)
		{
			now       = now / 8;
			TIM4->CNT = 0;

			wui_page_ui_tick(now);
		}

		wui_page_ui_update();

		uint32_t tcnt = TIM3->CNT;
		int32_t  dir  = check_direction(tcnt);

		if (dir > 0)
		{
			HW_Key_event('a');
		}
		else if (dir < 0)
		{
			HW_Key_event('d');
		}

		uint32_t k3 = ENC_KEY();
		if (k3)
		{
			if (!key3_state)
			{
				key3_state = 1;
				HW_Key_event('b');
			}
		}
		else
		{
			key3_state = 0;
		}
	}
}
