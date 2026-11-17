/*********************************************************************
 * File Name          : config.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/8/15
 * Description        : file for Config.
 *********************************************************************************
* Copyright (c) 2023 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/* LCD screen and touch panel GPIO definition (CH32H417QEU) */
#define LCD_LED_RCC       RCC_HB2Periph_GPIOB
#define LCD_LED_PORT      GPIOB
#define LCD_LED_PIN       (GPIO_Pin_0)

#define LCD_DC_RCC        RCC_HB2Periph_GPIOB
#define LCD_DC_PORT       GPIOB
#define LCD_DC_PIN        (GPIO_Pin_10)

#define LCD_RST_RCC       RCC_HB2Periph_GPIOB
#define LCD_RST_PORT      GPIOB
#define LCD_RST_PIN       (GPIO_Pin_11)

#define LCD_CS_RCC        RCC_HB2Periph_GPIOB
#define LCD_CS_PORT       GPIOB
#define LCD_CS_PIN        (GPIO_Pin_12)

#define TOUCH_RST_RCC     RCC_HB2Periph_GPIOB
#define TOUCH_RST_PORT    GPIOB
#define TOUCH_RST_PIN     (GPIO_Pin_5)

#define TOUCH_INT_RCC     RCC_HB2Periph_GPIOB
#define TOUCH_INT_PORT    GPIOB
#define TOUCH_INT_PIN     (GPIO_Pin_4)

#define TOUCH_IIC_RCC     RCC_HB2Periph_GPIOB
#define TOUCH_SCL_PORT    GPIOB
#define TOUCH_SCL_PIN     (GPIO_Pin_6)
#define TOUCH_SDA_PORT    GPIOB
#define TOUCH_SDA_PIN     (GPIO_Pin_7)

#endif
