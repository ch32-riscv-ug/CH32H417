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

/* SPI FLASH (SPI1): CS=PA4, SCK=PA5, MISO=PA6, MOSI=PA7, all AF5 */
#define FLASH_CS_PORT GPIOA
#define FLASH_CS_RCC  RCC_HB2Periph_GPIOA
#define FLASH_CS_PIN  (GPIO_Pin_4)

#define LCD_LED_RCC   RCC_HB2Periph_GPIOB
#define LCD_LED_PORT  GPIOB
#define LCD_LED_PIN   (GPIO_Pin_14)

#define LCD_DC_RCC    RCC_HB2Periph_GPIOB
#define LCD_DC_PORT   GPIOB
#define LCD_DC_PIN    (GPIO_Pin_10)

#define LCD_RST_RCC   RCC_HB2Periph_GPIOB
#define LCD_RST_PORT  GPIOB
#define LCD_RST_PIN   (GPIO_Pin_11)

#define LCD_CS_RCC    RCC_HB2Periph_GPIOB
#define LCD_CS_PORT   GPIOB
#define LCD_CS_PIN    (GPIO_Pin_12)

/* LCD SPI2 pins: SCK=PB13(AF5), MOSI=PC1(AF5) */
#define LCD_SCK_RCC   RCC_HB2Periph_GPIOB
#define LCD_SCK_PORT  GPIOB
#define LCD_SCK_PIN   (GPIO_Pin_13)

#define LCD_MOSI_RCC  RCC_HB2Periph_GPIOC
#define LCD_MOSI_PORT GPIOC
#define LCD_MOSI_PIN  (GPIO_Pin_1)

#endif
