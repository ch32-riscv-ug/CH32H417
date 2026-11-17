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

#if 0


/* Global typedef */
typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

/* Global define */
#define TxSize  (size(TxBuffer))
#define size(a) (sizeof(a) / sizeof(*(a)))

/* Global Variable */
u8         TxBuffer[]       = "Buffer Send from USART2 to USART3 by polling!";
u8         RxBuffer[TxSize] = {0};
u8         TxCnt = 0, RxCnt = 0;
TestStatus TransferStatus = FAILED;

/*********************************************************************
 * @fn      Buffercmp
 *
 * @brief   Compares two buffers
 *
 * @param   Buf1,Buf2 - buffers to be compared
 *          BufferLength - buffer's length
 *
 * @return  PASSED - Buf1 identical to Buf
 *          FAILED - Buf1 differs from Buf2
 */
TestStatus Buffercmp(uint8_t *Buf1, uint8_t *Buf2, uint16_t BufLength)
{
    while (BufLength--)
    {
        if (*Buf1 != *Buf2)
        {
            return FAILED;
        }
        Buf1++;
        Buf2++;
    }
    return PASSED;
}

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_HB1PeriphClockCmd(RCC_HB1Periph_USART2 | RCC_HB1Periph_USART3, ENABLE);
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOD | RCC_HB2Periph_GPIOB, ENABLE);

    // USART2_RX PD6(AF7)
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF7);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // USART2_TX PD5(AF7)
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF7);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // USART3_RX PB11(AF7)
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF7);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // USART3_TX PB10(AF7)
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF7);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
}

/*********************************************************************
 * @fn      Hardware
 *
 * @brief   Resets the CRC Data register (DR).
 *
 * @return  none
 */
#define LCD_SELFTEST (1)

printf("SPI2 CR1=%08x SR=%08x\r\n",
           (unsigned)SPI2->CTLR1, (unsigned)SPI2->STATR);
    printf("GPIOB CFGLR=%08x CFGHR=%08x OUT=%08x\r\n",
           (unsigned)GPIOB->CFGLR, (unsigned)GPIOB->CFGHR, (unsigned)GPIOB->OUTDR);

    SPI2_Write(0xA5u);
    printf("SPI2 SR after tx=%08x\r\n", (unsigned)SPI2->STATR);

#if LCD_SELFTEST
static void lcd_selftest(void)
{
    static uint16_t line[PANEL_W];
    const uint16_t colors[3] = {0xF800, 0x07E0, 0x001F};
    uint16_t i;
    uint16_t y;
    uint8_t c;

    for (c = 0; c < 3u; c++)
    {
        for (i = 0; i < PANEL_W; i++)
        {
            line[i] = colors[c];
        }

        SPI2_SetDataSize(SPI_DataSize_16b);
        LCD_SetWindows(0, 0, PANEL_W - 1, PANEL_H - 1);

        for (y = 0; y < PANEL_H; y++)
        {
            SPI2_Write_DMA16(line, PANEL_W);
        }

        SPI2_SetDataSize(SPI_DataSize_8b);
        Delay_Ms(600);
    }
}
#endif

void Hardware(void)
{
    printf("USART Polling TEST\r\n");
    USARTx_CFG(); /* USART2 & USART3 INIT */

    while (TxCnt < TxSize)
    {
        USART_SendData(USART2, TxBuffer[TxCnt++]);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        {
            /* waiting for sending finish */
        }
        while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {
            /* waiting for receiving finish */
        }
        RxBuffer[RxCnt++] = (USART_ReceiveData(USART3));
    }

    TransferStatus = Buffercmp(TxBuffer, RxBuffer, TxSize);

    if (TransferStatus)
    {
        printf("send success!\r\n");
        printf("TXBuffer: %s \r\n", TxBuffer);
        printf("RxBuffer: %s \r\n", RxBuffer);
    }
    else
    {
        printf("send fail!\r\n");
        printf("TXBuffer: %s \r\n", TxBuffer);
        printf("RxBuffer: %s \r\n", RxBuffer);
    }
    while (1)
        ;
}
#endif

#include "lcd.h"
#include "GT9xx.h"
#include "wvui.h"
#include "wvui_port_display.h"
#include "wvui_port_input.h"
#include "wvui_app.h"

#define PANEL_W (320)
#define PANEL_H (240)
#define TIM_PCK (8000ul)

static wvui_color_t s_pfb[(uint32_t)PANEL_W * WVUI_CFG_PFB_LINES];
static uintptr_t s_arena_persist_mem[1536];
static wvui_arena_t s_arena_persist;
static uintptr_t s_arena_transient_mem[64];
static wvui_arena_t s_arena_transient;

#define LCD_BRINGUP (0)

static void lcd_bringup(void)
{
    static uint16_t line[PANEL_W];
    uint16_t i;
    uint16_t y;

    for (i = 0; i < 6u; i++)
    {
        LCD_LED_CLR();
        Delay_Ms(200);
        LCD_LED_SET();
        Delay_Ms(200);
    }

    for (i = 0; i < PANEL_W; i++)
    {
        line[i] = 0xF800;
    }

    LCD_SetWindows(0, 0, PANEL_W - 1, PANEL_H - 1);
    SPI2_SetDataSize(SPI_DataSize_16b);

    LCD_CS_CLR();
    LCD_DC_SET();

    for (y = 0; y < PANEL_H; y++)
    {
        SPI2_Write_DMA16(line, PANEL_W);
        while (SPI2_DMA_TX_CH->CNTR > 0)
            ;
    }

    LCD_CS_SET();
    SPI2_SetDataSize(SPI_DataSize_8b);
}

#define LCD_SELFTEST (1)

#if LCD_SELFTEST
static void lcd_selftest(void)
{
    static uint16_t line[PANEL_W];
    const uint16_t colors[3] = {0xF800, 0x07E0, 0x001F};
    uint16_t i;
    uint16_t y;
    uint8_t c;

    for (c = 0; c < 3u; c++)
    {
        for (i = 0; i < PANEL_W; i++)
        {
            line[i] = colors[c];
        }

        SPI2_SetDataSize(SPI_DataSize_16b);
        LCD_SetWindows(0, 0, PANEL_W - 1, PANEL_H - 1);

        for (y = 0; y < PANEL_H; y++)
        {
            SPI2_Write_DMA16(line, PANEL_W);
        }

        SPI2_SetDataSize(SPI_DataSize_8b);
        Delay_Ms(600);
    }
}
#endif

static void TIM4_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_HB1PeriphClockCmd(RCC_HB1Periph_TIM4, ENABLE);

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

void Hardware(void)
{
    wvui_cfg_t cfg = {0};
    int rc;

    TIM4_init();

    if (lcd_init() != 0)
    {
        printf("FAIL: lcd_init()\r\n");
        return;
    }

#if LCD_BRINGUP
    printf("bringup: fill red\r\n");
    lcd_bringup();
    printf("bringup: done, hold\r\n");

    while (1)
    {
        Delay_Ms(1000);
    }
#endif

#if 0
    printf("LCD selftest: R/G/B\r\n");
    lcd_selftest();
    printf("LCD selftest done\r\n");
#endif

    if (Touch_Init() != 0)
    {
        printf("WARN: touch init failed\r\n");
    }
    else
    {
        printf("touch panel %ux%u\r\n",
               (unsigned)touchChipInfo.width, (unsigned)touchChipInfo.height);
    }

    wvui_port_display_configure(1u);

    cfg.w = PANEL_W;
    cfg.h = PANEL_H;
    cfg.bg = WVUI_RGB565(245, 247, 250);
    cfg.pfb = s_pfb;
    cfg.pfb_pixels = (uint32_t)PANEL_W * WVUI_CFG_PFB_LINES;
    cfg.double_buffer = 1u;

    rc = wvui_init(wvui_port_display(), &cfg);
    if (rc != WVUI_OK)
    {
        printf("FAIL: wvui_init rc=%d\r\n", rc);
        return;
    }

    printf("wvui: %dx%d db=%u rows=%u\r\n", (int)wvui_info()->w, (int)wvui_info()->h,
           (unsigned)wvui_info()->double_buffer, (unsigned)wvui_info()->chunk_rows);

    wvui_arena_init(&s_arena_persist, s_arena_persist_mem,
                    (uint32_t)sizeof(s_arena_persist_mem));
    wvui_arena_init(&s_arena_transient, s_arena_transient_mem,
                    (uint32_t)sizeof(s_arena_transient_mem));
    wvui_driver_bind_arena(&s_arena_persist, &s_arena_transient);
    wvui_driver_bind_input(wvui_port_input());

    if (app_init() != 0)
    {
        printf("FAIL: app init\r\n");
        return;
    }

    printf("OK: wvui ready\r\n");

    while (1)
    {
        wvui_app_tick();
    }
}
