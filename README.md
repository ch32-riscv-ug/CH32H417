# CH32H417

<!-- This file is generated from ch32-riscv-ug/ch32-device-data (index/ + evidence/ + tools/build_readme.py). Edit there, not here. -->

*Generated from the mirror at commit [`5078e3b`](https://github.com/ch32-riscv-ug/CH32H417/tree/5078e3b966647e96938cf0b814a52f5120030b23) (2026-08-29). Newer PDFs may exist upstream; see Documents below.*

[Choose a part](#product-comparison) &middot; [Pin viewer](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415) &middot; [Pin maps](#pin-maps--alternate-functions) &middot; [Errata](#errata) &middot; [Examples](#evt-examples) &middot; [Documents](#documents) &middot; [Address map](#address-map)

## Quick start

### Debug / serial defaults

Where these land **without writing a remap register**. SWD is live at reset; the UART pads are not -- the pin must still be put into alternate-function mode. See `route` in evidence/README.ja.md.

| Series | SWDIO | SWCLK | UART TX | UART RX |
|---|---|---|---|---|
| CH32H415 | PB9 | PB8 | none by default[^af] | none by default[^af] |
| CH32H416 | PB9 | PB8 | none by default[^af] | none by default[^af] |
| CH32H417 | PB9 | PB8 | none by default[^af] | none by default[^af] |

[^af]: This series selects every pin function through `AFIO->GPIOx_AFLR/AFHR` rather than through AFIO remap, so no USART is routed out until software picks one -- the pads it **can** go on are listed under Pin definitions. The reset value of `GPIOx_AFLR/AFHR` is 0, which selects AF0 (a real function, not "none"), and a pad only drives its alternate function once its GPIO mode is set to alternate.

## Series

| Series | Core | ISA | Flash | SRAM | Main clock | VDD | Packages | Products | Official |
|---|---|---|---|---|---|---|---|---|---|
| **CH32H415** | QingKe V5F + QingKe V3F | RV32IMABCF + RV32IMAFCB | 960K | 896K | 160/200 MHz\* | - | QFN60X6 | 1 | [en](https://www.wch-ic.com/products/CH32H415.html) / [zh](https://www.wch.cn/products/CH32H415.html) |
| **CH32H416** | QingKe V5F + QingKe V3F | RV32IMABCF + RV32IMAFCB | 480K | 896K | 160/200 MHz\* | - | QFN60X6 | 1 | [en](https://www.wch-ic.com/products/CH32H416.html) / [zh](https://www.wch.cn/products/CH32H416.html) |
| **CH32H417** | QingKe V5F + QingKe V3F | RV32IMABCF + RV32IMAFCB | 960K | 896K | 160/200 MHz\* | - | QFN128,QFN68,QFN88 | 3 | [en](https://www.wch-ic.com/products/CH32H417.html) / [zh](https://www.wch.cn/products/CH32H417.html) |

\* the datasheet states no nominal system main frequency for this series, so the figure is the electrical maximum (HCLK) from the characteristics table -- a limit, not a rating.

## Product comparison

### CH32H417 product comparison

Only the 15 rows that differ between these 3 products; the other 32 are the same for all of them.

| | [CH32H417&#8203;MEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417MEU6)&#8203;(QFN88) | [CH32H417&#8203;QEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417QEU6)&#8203;(QFN128) | [CH32H417&#8203;WEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417WEU6)&#8203;(QFN68) |
|---|---|---|---|
| **GPIO** | 65 | 95 | 50 |
| ADC/TKey Channels | 9+2 | 16+2 | 7+2 |
| HSADC Channels | 4 | 7 | 4 |
| DAC (Unit) | 2 | 2 | 1 (DAC2) |
| OPA | 2 (OPA1/3) | 3 | 2 (OPA1/3) |
| USART | 8 | 8 | 7 |
| SPI/I2S | 4/2 | 4/2 | 3/2 |
| QSPI | 1 (QSPI2) | 2 | 1 (QSPI2) |
| UHSIF | 1 | 1 | 1(1) |
| SDIO | - | 1 | - |
| USBFS/OTG_FS | 1 | 1 | - |
| USBPD Type-C | 1 | 1 | - |
| FSMC | 1(2) | 1 | 1(2) |
| SerDes(4) | 1 | 1 | - |
| SDRAM | 1 | 1 | 1(3) |

<details><summary>All 47 rows</summary>

| | [CH32H417&#8203;MEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417MEU6)&#8203;(QFN88) | [CH32H417&#8203;QEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417QEU6)&#8203;(QFN128) | [CH32H417&#8203;WEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417WEU6)&#8203;(QFN68) |
|---|---|---|---|
| **Flash** | 960K | 960K | 960K |
| **SRAM** | 896K | 896K | 896K |
| **GPIO** | 65 | 95 | 50 |
| **Temperature** | -40..85C | -40..85C | -40..85C |
| Core 1 HS ITCM | 128KB | 128KB | 128KB |
| Core 1 HS DTCM | 256KB | 256KB | 256KB |
| SRAM Shared code and data area | 512KB | 512KB | 512KB |
| ADTM (16-bit) | 2 | 2 | 2 |
| GPTM (16-bit) | 4 | 4 | 4 |
| GPTM (32-bit) | 4 | 4 | 4 |
| Basic (16-bit) | 2 | 2 | 2 |
| LPTIM | 2 | 2 | 2 |
| Timer Watchdog | WWDG+IWDG | WWDG+IWDG | WWDG+IWDG |
| SysTick 32-bit | 2 | 2 | 2 |
| RTC | √ | √ | √ |
| ADC/TKey Units | 2 | 2 | 2 |
| ADC/TKey Channels | 9+2 | 16+2 | 7+2 |
| HSADC Units | 1 | 1 | 1 |
| HSADC Channels | 4 | 7 | 4 |
| DAC (Unit) | 2 | 2 | 1 (DAC2) |
| OPA | 2 (OPA1/3) | 3 | 2 (OPA1/3) |
| CMP | 1 | 1 | 1 |
| DFSDM | 1 | 1 | 1 |
| RNG | 1 | 1 | 1 |
| LTDC | 1 | 1 | 1 |
| GPHA | 1 | 1 | 1 |
| DVP | 1 | 1 | 1 |
| USART | 8 | 8 | 7 |
| SPI/I2S | 4/2 | 4/2 | 3/2 |
| QSPI | 1 (QSPI2) | 2 | 1 (QSPI2) |
| I2C | 4 | 4 | 4 |
| I3C | 1 | 1 | 1 |
| UHSIF | 1 | 1 | 1(1) |
| CAN(5) | 3 | 3 | 3 |
| SDMMC | 1 | 1 | 1 |
| SDIO | - | 1 | - |
| SAI | 1 | 1 | 1 |
| SWPMI | 1 | 1 | 1 |
| USBFS/OTG_FS | 1 | 1 | - |
| USBHS (USB 2.0) | 1 | 1 | 1 |
| USBSS (USB 3.0) | 1 | 1 | 1 |
| Ethernet(5) | MAC+10/100M PHY | MAC+10/100M PHY | MAC+10/100M PHY |
| USBPD Type-C | 1 | 1 | - |
| FSMC | 1(2) | 1 | 1(2) |
| SerDes(4) | 1 | 1 | - |
| SDRAM | 1 | 1 | 1(3) |
| PIOC | 1 | 1 | 1 |

</details>

## Packages & pinout drawings

Pinout drawings are in the datasheet (chapter *Pinouts*):

| Package | Products | Datasheet | Outline |
|---|---|---|---|
| QFN60X6 | CH32H415REU6 | [en](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) / [zh](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) | [drawing](https://raw.githubusercontent.com/ch32-riscv-ug/WCH-common/main/image/package_QFN60X6.png) |
| QFN60X6 | CH32H416RDU6 | [en](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) / [zh](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) | [drawing](https://raw.githubusercontent.com/ch32-riscv-ug/WCH-common/main/image/package_QFN60X6.png) |
| QFN88 | CH32H417MEU6 | [en](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) / [zh](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) | [drawing](https://raw.githubusercontent.com/ch32-riscv-ug/WCH-common/main/image/package_QFN88.png) |
| QFN128 | CH32H417QEU6 | [en](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) / [zh](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) | [drawing](https://raw.githubusercontent.com/ch32-riscv-ug/WCH-common/main/image/package_QFN128.png) |
| QFN68 | CH32H417WEU6 | [en](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) / [zh](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) | [drawing](https://raw.githubusercontent.com/ch32-riscv-ug/WCH-common/main/image/package_QFN68.png) |

## Pin maps & alternate functions

> [!NOTE]
> These are the **pin-table superset**: the datasheet prints one pad table for every product that shares a pinout, so a pad row does not mean this part has the peripheral. Use the product comparison table above for what a given part number contains.

### CH32H415 pin map

Pin functions (filterable): [ALL](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415) [ADC](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=ADC) [I2C](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=I2C) [SPI](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=SPI) [SYS](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=SYS) [TIM](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=TIM) [UART](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=UART) [USB](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415&features=USB)

<details><summary><b>CH32H415 pin map</b> (61 pads x 1 products)</summary>

| Pin name | Type | [CH32H415&#8203;REU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H415REU6)&#8203;(QFN60X6) | Notes |
|---|---|---|---|
| PA0 | I/O/A | 14 |  |
| PA1 | I/O/A | 15 |  |
| PA2 | I/O/A | 16 |  |
| PA3 | I/O/A | 17 |  |
| PA4 | I/O/A | 18 |  |
| PA5 | I/O/A | 19 |  |
| PA6 | I/O/A | 20 |  |
| PA7 | I/O/A | 21 |  |
| PA9 | I/O/A | 40 |  |
| PA10 | I/O/A | 41 |  |
| PA11 | I/O/A | 42 |  |
| PA12 | I/O/A | 43 |  |
| PA13 | I/O | 44 |  |
| PA14 | I/O | 45 |  |
| PA15 | I/O | 46 |  |
| PB0 | I/O/A | 23 |  |
| PB1 | I/O/A | 24 |  |
| PB3 | I/O | 55 |  |
| PB4 | I/O | 56 |  |
| PB6 | I/O | 57 |  |
| PB7 | I/O | 58 |  |
| PB8 | I/O/A | 59 | SWCLK |
| PB9 | I/O/A | 60 | SWDIO |
| PB10 | I/O | 29 |  |
| PB11 | I/O | 30 |  |
| PB12 | I/O | 32 |  |
| PB13 | I/O | 33 |  |
| PB14 | I/O | 34 |  |
| PB15 | I/O | 35 |  |
| PC0 | I/O/A | 9 |  |
| PC1 | I/O/A | 10 |  |
| PC2 | I/O/A | 11 |  |
| PC3 | I/O/A | 12 |  |
| PC4 | I/O/A | 22 |  |
| PC6 | I/O | 36 |  |
| PC7 | I/O | 37 |  |
| PC8 | I/O | 38 |  |
| PC9 | I/O | 39 |  |
| PC10 | I/O | 47 |  |
| PC11 | I/O | 48 |  |
| PC12 | I/O | 49 |  |
| PD3 | I/O | 50 |  |
| PE0 | I/O | 54 |  |
| PE3 | I/O | 1 |  |
| PE4 | I/O | 2 |  |
| PE5 | I/O | 3 |  |
| PE6 | I/O | 4 |  |
| PE11 | I/O | 25 |  |
| PE12 | I/O | 26 |  |
| PE13 | I/O | 27 |  |
| PE14 | I/O | 28 |  |
| PE15 | I/O | 29 |  |
| PF3 | I/O | 51 |  |
| PF4 | I/O | 52 |  |
| PF5 | I/O | 53 |  |
| VDD33 | P | 6/31 |  |
| VDD33A | P | 13 |  |
| VDDK | P | 5 |  |
| VSS | P | EP |  |
| XI | I/A | 7 |  |
| XO | O/A | 8 |  |

</details>

<details><summary><b>CH32H415 alternate functions</b></summary>

| Pad | default | (no route stated) | af-0 | af-1 | af-10 | af-11 | af-12 | af-13 | af-14 | af-15 | af-2 | af-3 | af-4 | af-5 | af-6 | af-7 | af-8 | af-9 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| PA0 | ADC_IN0, OPA3_OUT0 | ADC_IN0, OPA3_OUT0 | - | TIM2_CH1_ETR | - | - | - | - | LTDC_R0 | - | TIM5_CH1 | TIM8_ETR | QSPI2_SIOX2 | PIOC_IO0 | TIM9_CH1 | USART2_CTS | USART6_TX | SDIO_CMD |
| PA1 | ADC_IN1 | ADC_IN1 | - | TIM2_CH2 | - | - | - | - | LTDC_R2 | - | TIM5_CH2 | - | QSPI2_SIOX3 | - | TIM9_CH2 | USART2_RTS | USART6_RX | QSPI1_SIO3 |
| PA2 | ADC_IN2, OPA3_P1 | ADC_IN2, OPA3_P1 | - | TIM2_CH3 | - | - | - | - | LTDC_R1 | - | TIM5_CH3 | USART6_CK | TIM9_CH3 | - | - | USART2_TX | - | - |
| PA3 | ADC_IN3, OPA3_N1 | ADC_IN3, OPA3_N1 | - | TIM2_CH4 | - | - | - | - | LTDC_B5 | - | TIM5_CH4 | - | TIM9_CH4 | - | - | USART2_RX | TIM10_CH3 | LTDC_B2 |
| PA4 | ADC_IN4, DAC1_OUT, OPA3_OUT1 | ADC_IN4, DAC1_OUT, OPA3_OUT1 | - | - | - | - | - | DVP_HSYNC | LTDC_VSYNC | - | TIM5_ETR | - | TIM9_ETR | SPI1_NSS | I2S3_WS, SPI3_NSS | USART2_CK | - | TIM10_CH4 |
| PA5 | ADC_IN5, DAC2_OUT, OPA1_OUT1 | ADC_IN5, DAC2_OUT, OPA1_OUT1 | - | TIM2_CH1_ETR | - | DVP_VSYNC | - | - | LTDC_R4 | - | TIM1_BKIN2 | TIM8_CH1N | - | SPI1_SCK | - | - | - | TIM10_ETR |
| PA6 | ADC_IN6, OPA1_P1 | ADC_IN6, OPA1_P1 | - | TIM1_BKIN | CMP_OUT | LTDC_HSYNC | - | DVP_PCLK | LTDC_G2 | - | TIM3_CH1 | TIM8_BKIN | - | SPI1_MISO | - | - | - | TIM10_CH1 |
| PA7 | ADC_IN7, OPA1_N1 | ADC_IN7, OPA1_N1 | - | TIM1_CH1N | - | - | - | - | LTDC_VSYNC | - | TIM3_CH2 | TIM8_CH1N | - | SPI1_MOSI | - | - | - | TIM10_CH2 |
| PA9 | OTG_VBUS | OTG_VBUS | - | TIM1_CH2 | - | - | - | DVP_D0 | LTDC_R5 | - | - | - | I2C3_SMBA | I2S2_CK, SPI2_SCK | - | USART1_TX | - | - |
| PA10 | OTG_ID | OTG_ID | - | TIM1_CH3 | - | - | LTDC_B4 | DVP_D1 | LTDC_B1 | - | - | - | - | - | USART6_CK | USART1_RX | - | - |
| PA11 | OTG_DM | OTG_DM | - | TIM1_CH4 | - | - | - | - | LTDC_R4 | - | - | - | USART3_CK | I2S2_WS, SPI2_NSS | USART6_RX | USART1_CTS | - | CAN1_RX |
| PA12 | OTG_DP | OTG_DP | - | TIM1_ETR | - | - | TIM1_BKIN2 | - | LTDC_R5 | - | - | - | USART3_RTS | I2S2_CK, SPI2_SCK | USART6_TX | USART1_RTS | - | CAN1_TX |
| PA13 | - | - | - | I2S3_SD, SPI3_MOSI | - | - | - | SAI_SD_B | - | - | - | - | USART3_TX | CAN_RX | - | I2C3_SDA | LTDC_B2 | - |
| PA14 | - | - | - | I2S3_CK, SPI3_SCK | - | USART8_CK | - | SAI_SCK_B | LTDC_B6 | LTDC_R0 | - | - | USART3_RX | CAN_TX | - | I2C3_SCL | - | - |
| PA15 | - | - | - | TIM2_CH1_ETR | LTDC_B4 | USART8_TX | - | SAI_FS_B | LTDC_B6 | LTDC_CLK | - | - | USART3_CTS | SPI1_NSS | I2S3_WS, SPI3_NSS | I2C3_SMBA | USART6_RTS | LTDC_R3 |
| PB0 | ADC_IN8, CMP_P0, OPA1_P0 | ADC_IN8, CMP_P0, OPA1_P0 | MCO | TIM1_CH2N | - | - | - | TIM12_ETR | LTDC_G1 | - | TIM3_CH3 | TIM8_CH2N | TIM5_CH4 | - | DFSDM_CKOUT | - | USART6_CTS | LTDC_R3 |
| PB1 | ADC_IN9, CMP_N0, OPA1_N0 | ADC_IN9, CMP_N0, OPA1_N0 | - | TIM1_CH3N | - | - | - | - | LTDC_G0 | - | TIM3_CH4 | TIM8_CH3N | - | TIM12_CH1 | DFSDM_DATIN1 | - | - | LTDC_R6 |
| PB3 | - | - | - | TIM2_CH2 | - | USART8_RX | - | DVP_D5 | TIM12_ETR | - | - | - | CC1 | SPI1_SCK | I2S3_CK, SPI3_SCK | - | - | SDIO_D2 |
| PB4 | - | - | - | - | TIM4_ETR | USART8_TX | - | - | USART7_CK | - | TIM3_CH1 | - | CC2 | SPI1_MISO | SPI3_MISO | I2S2_WS, SPI2_NSS | - | SDIO_D3 |
| PB6 | - | - | TIM10_CH1 | - | QSPI1_SCSN | - | - | DVP_D5 | USART7_TX | - | TIM4_CH1 | CAN1_RX | I2C1_SCL | I2S3_MCK | I2C4_SCL | USART1_TX | - | CAN2_TX |
| PB7 | - | - | TIM10_CH2 | - | USART8_CK | - | - | DVP_VSYNC | - | - | TIM4_CH2 | CAN1_TX | I2C1_SDA | - | I2C4_SDA | USART1_RX | - | - |
| PB8 | SWCLK, USBHS_DP | SWCLK, USBHS_DP | - | TIM10_CH3 | SDIO_D4 | - | - | DVP_D6 | LTDC_B6 | - | TIM4_CH3 | - | I2C1_SCL | PIOC_IO0 | I2C4_SCL | - | USART6_RX | CAN1_RX |
| PB9 | SWDIO, SWIO, USBHS_DM | SWDIO, SWIO, USBHS_DM | - | TIM10_CH4 | SDIO_D5 | I2C4_SMBA | - | DVP_D7 | LTDC_B7 | - | TIM4_CH4 | - | I2C1_SDA | I2S2_WS, SPI2_NSS | I2C4_SDA | PIOC_IO1 | USART6_TX | CAN1_TX |
| PB10 | - | - | - | TIM2_CH3 | - | QSPI2_SCSXN | - | - | LTDC_G4 | - | TIM9_CH2 | LPTIM2_CH1 | I2C2_SCL | I2S2_CK, SPI2_SCK | - | USART3_TX | SDIO_CMD | USART6_CK |
| PB11 | - | - | - | TIM2_CH4 | - | QSPI2_SIOX0 | - | - | LTDC_G5 | - | - | LPTIM2_ETR | I2C2_SDA | - | - | USART3_RX | SDIO_CK | TIM9_CH4 |
| PB12 | - | - | - | TIM1_BKIN | LTDC_VSYNC | QSPI2_SIOX1 | - | CMP_OUT | USART7_RX | DVP_PCLK | TIM8_BKIN | - | I2C2_SMBA | I2S2_WS, SPI2_NSS | DFSDM_DATIN1 | USART3_CK | TIM9_CH3 | CAN2_RX |
| PB13 | - | - | - | TIM1_CH1N | - | QSPI2_SIOX0 | - | DVP_D2 | USART7_TX | - | TIM8_BKIN2 | LPTIM2_OC | TIM9_ETR | I2S2_CK, SPI2_SCK | DFSDM_CKIN1 | USART3_CTS | DVP_HSYNC | CAN2_TX |
| PB14 | - | - | - | TIM1_CH2N | - | QSPI2_SIOX1 | - | USART7_CK | LTDC_CLK | DVP_VSYNC | TIM9_CH1 | TIM8_CH2N | USART1_TX | SPI2_MISO | LTDC_G0 | USART3_RTS | USART6_RTS | SDIO_D0 |
| PB15 | - | - | - | TIM1_CH3N | - | - | - | - | LTDC_G7 | - | TIM9_CH2 | TIM8_CH3N | USART1_RX | I2S2_SD, SPI2_MOSI | - | - | USART6_CTS | SDIO_D1 |
| PC0 | ADC_IN10, HSADC_IN0 | ADC_IN10, HSADC_IN0 | TIM8_BKIN | - | QSPI2_SIO3 | LTDC_G2 | - | - | LTDC_R5 | - | - | DFSDM_CKIN0 | - | PIOC_IO1 | - | SAI_MCLK_A | - | I2C2_SCL |
| PC1 | ADC_IN11, HSADC_IN1 | ADC_IN11, HSADC_IN1 | TIM8_CH1N | - | QSPI2_SCSXN | SDIO_CK | - | - | LTDC_G5 | - | TIM5_CH1 | DFSDM_DATIN0 | - | I2S2_SD, SPI2_MOSI | - | PIOC_IO0, SAI_SD_A | - | I2C2_SDA |
| PC2 | ADC_IN12, HSADC_IN2, OPA3_P0 | ADC_IN12, HSADC_IN2, OPA3_P0 | TIM8_CH2N | - | QSPI2_SIOX0 | - | - | - | - | - | TIM5_CH2 | DFSDM_CKIN1 | - | SPI2_MISO | DFSDM_CKOUT | SAI_SCK_A | PIOC_IO1 | I2C2_SMBA |
| PC3 | ADC_IN13, HSADC_IN3, OPA3_N0 | ADC_IN13, HSADC_IN3, OPA3_N0 | TIM8_CH3N | - | QSPI2_SIOX1 | - | - | - | - | - | TIM5_CH3 | DFSDM_DATIN1 | - | I2S2_SD, SPI2_MOSI | - | SAI_FS_A | - | - |
| PC4 | ADC_IN14, CMP_N1, OPA1_OUT0 | ADC_IN14, CMP_N1, OPA1_OUT0 | - | - | - | - | - | - | LTDC_R7 | - | - | - | - | - | CAN3_RX | I3C_SCL | - | - |
| PC6 | - | - | - | - | - | SWPMI_IO | - | DVP_D0 | LTDC_HSYNC | - | TIM3_CH1 | TIM8_CH1 | - | I2S2_MCK | - | USART4_TX | - | SDIO_D6 |
| PC7 | - | - | - | - | - | SWPMI_TX | - | DVP_D1 | LTDC_G6 | - | TIM3_CH2 | TIM8_CH2 | - | - | I2S3_MCK | USART4_RX | - | SDIO_D7 |
| PC8 | - | - | - | - | - | SWPMI_RX | - | DVP_D2 | LTDC_G4 | - | TIM3_CH3 | TIM8_CH3 | - | - | TIM9_ETR | USART4_CK | USART7_RTS | - |
| PC9 | - | - | - | - | LTDC_G3 | SWPMI_SUP | - | DVP_D3 | LTDC_B2 | SAI_MCLK_B | TIM3_CH4 | TIM8_CH4 | I2C3_SDA | SPI3_MISO | TIM9_CH1 | - | USART7_CTS | QSPI1_SIO0 |
| PC10 | - | - | - | - | LTDC_B1 | SWPMI_RX | - | DVP_D8 | LTDC_R2 | LTDC_HSYNC | TIM9_CH2 | - | - | - | I2S3_CK, SPI3_SCK | USART3_TX | USART6_TX | QSPI1_SIO1 |
| PC11 | - | - | - | - | - | - | - | DVP_D4 | LTDC_B4 | LTDC_VSYNC | TIM9_CH4 | - | - | - | SPI3_MISO | USART3_RX | USART6_RX | QSPI1_SCSXN |
| PC12 | - | - | - | - | - | - | - | DVP_D9 | LTDC_R6 | LTDC_DE | TIM9_CH3 | - | - | - | I2S3_SD, SPI3_MOSI | USART3_CK | USART7_TX | - |
| PD3 | - | - | - | - | - | - | - | DVP_D5 | LTDC_G7 | LTDC_R6 | TIM11_CH1 | DFSDM_CKOUT | - | I2S2_CK, SPI2_SCK | - | USART2_CTS | USART6_CK | TIM3_CH1 |
| PE0 | - | - | - | LPTIM1_CH1 | - | DVP_D0 | - | TIM11_CH1 | LTDC_B1 | LTDC_B3 | - | - | USART5_TX | - | - | USART4_RTS | - | LTDC_B4 |
| PE3 | - | - | TIM8_CH1 | - | - | USART5_TX | - | DVP_D3 | - | - | TIM4_CH1 | TIM12_CH1 | - | PIOC_IO0 | SAI_SD_B | - | - | - |
| PE4 | - | - | TIM8_CH2 | - | - | - | - | DVP_D4 | LTDC_B0 | - | TIM4_CH2 | TIM12_CH2 | PIOC_IO1 | SPI4_NSS | SAI_FS_A | - | - | - |
| PE5 | - | - | TIM8_CH3 | - | - | - | - | DVP_D6 | LTDC_G0 | - | TIM4_CH3 | TIM12_CH3 | TIM9_CH3 | SPI4_MISO | SAI_SCK_A | - | - | - |
| PE6 | - | - | TIM8_CH4 | TIM1_BKIN2 | - | CMP_OUT | - | DVP_D7 | LTDC_G1 | - | TIM4_CH4 | TIM12_CH4 | TIM9_CH4 | SPI4_MOSI | SAI_SD_A | - | USART8_CK | - |
| PE11 | - | - | - | TIM1_CH2 | - | - | - | - | LTDC_G3 | - | - | - | - | SPI4_NSS | - | QSPI2_SCSN | SDIO_D3 | - |
| PE12 | - | - | - | TIM1_CH3N | - | - | - | CMP_OUT | LTDC_B4 | - | - | - | - | SPI4_SCK | - | QSPI2_SIO0 | SDIO_D4 | - |
| PE13 | - | - | - | TIM1_CH3 | - | - | - | - | LTDC_DE | - | TIM12_CH2 | - | - | SPI4_MISO | - | QSPI2_SIO1 | SDIO_D5 | - |
| PE14 | - | - | - | TIM1_CH4 | - | - | - | LTDC_CLK | - | - | TIM12_CH3 | I3C_SCL | - | SPI4_MOSI | - | QSPI2_SIO2 | SDIO_D6 | - |
| PE15 | - | - | - | TIM1_BKIN | - | USART5_CK | - | CMP_OUT | LTDC_R7 | - | TIM12_CH4 | I3C_SDA | - | - | - | QSPI2_SIO3 | SDIO_D7 | - |
| PF3 | - | - | - | - | - | DVP_D9 | - | DVP_VSYNC | LTDC_B0 | LTDC_G5 | CAN3_TX | - | - | SPI1_MISO | - | USART4_RX | - | QSPI1_SIOX2 |
| PF4 | - | - | - | LPTIM1_ETR | - | DVP_D8 | - | DVP_D2 | LTDC_B2 | LTDC_G6 | CAN3_RX | - | - | SPI1_NSS | - | USART4_TX | - | LTDC_G3 |
| PF5 | - | - | - | LPTIM1_CH2 | - | - | - | DVP_D3 | LTDC_B3 | LTDC_G7 | - | - | USART5_RX | SPI1_SCK | - | - | - | QSPI1_SIOX3 |

</details>

### CH32H416 pin map

Pin functions (filterable): [ALL](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416) [ADC](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=ADC) [I2C](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=I2C) [SPI](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=SPI) [SYS](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=SYS) [TIM](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=TIM) [UART](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=UART) [USB](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416&features=USB)

<details><summary><b>CH32H416 pin map</b> (60 pads x 1 products)</summary>

| Pin name | Type | [CH32H416&#8203;RDU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H416RDU6)&#8203;(QFN60X6) | Notes |
|---|---|---|---|
| PA0 | I/O/A | 16 |  |
| PA1 | I/O/A | 17 |  |
| PA2 | I/O/A | 18 |  |
| PA3 | I/O/A | 19 |  |
| PA4 | I/O/A | 20 |  |
| PA5 | I/O/A | 21 |  |
| PA6 | I/O/A | 22 |  |
| PA7 | I/O/A | 23 |  |
| PA11 | I/O/A | 39 |  |
| PA12 | I/O/A | 40 |  |
| PA13 | I/O | 41 |  |
| PA14 | I/O | 42 |  |
| PA15 | I/O | 43 |  |
| PB0 | I/O/A | 26 |  |
| PB1 | I/O/A | 27 |  |
| PB3 | I/O | 49 |  |
| PB4 | I/O | 50 |  |
| PB5 | I/O | 51 |  |
| PB6 | I/O | 52 |  |
| PB7 | I/O | 53 |  |
| PB8 | I/O/A | 54 | SWCLK |
| PB9 | I/O/A | 55 | SWDIO |
| PC0 | I/O/A | 10 |  |
| PC1 | I/O/A | 11 |  |
| PC2 | I/O/A | 12 |  |
| PC3 | I/O/A | 13 |  |
| PC4 | I/O/A | 24 |  |
| PC5 | I/O/A | 25 |  |
| PC6 | I/O | 35 |  |
| PC7 | I/O | 36 |  |
| PC8 | I/O | 37 |  |
| PC9 | I/O | 38 |  |
| PC10 | I/O | 44 |  |
| PC11 | I/O | 45 |  |
| PC12 | I/O | 46 |  |
| PD2 | I/O | 47 |  |
| PD3 | I/O | 48 |  |
| PD9 | I/O | 33 |  |
| PD10 | I/O | 34 |  |
| PE9 | I/O/A | 30 |  |
| PE15 | I/O | 31 |  |
| PF6 | I/O | 3 |  |
| PF7 | I/O | 4 |  |
| PF8 | I/O | 5 |  |
| PF9 | I/O/A | 6 |  |
| PF10 | I/O/A | 7 |  |
| PF12 | I/O/A | 28 |  |
| PF13 | I/O | 29 |  |
| SSRXA | USB3.0 | 60 |  |
| SSRXB | USB3.0 | 59 |  |
| SSTXA | USB3.0 | 57 |  |
| SSTXB | USB3.0 | 56 |  |
| VDD12A | P | 58 |  |
| VDD33 | P | 2/32 |  |
| VDD33A | P | 15 |  |
| VDDK | P | 1 |  |
| VREFP | P | 14 |  |
| VSS | P | EP |  |
| XI | I/A | 8 |  |
| XO | O/A | 9 |  |

</details>

<details><summary><b>CH32H416 alternate functions</b></summary>

| Pad | default | af-0 | af-1 | af-10 | af-11 | af-12 | af-13 | af-14 | af-15 | af-2 | af-3 | af-4 | af-5 | af-6 | af-7 | af-8 | af-9 | remap-1 | remap-2 | remap-3 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| PA0 | ADC_IN0, OPA3_OUT0 | - | TIM2_CH1_ETR | - | - | - | - | LTDC_R0 | - | TIM5_CH1 | TIM8_ETR | QSPI2_SIOX2 | PIOC_IO0 | TIM9_CH1 | USART2_CTS | USART6_TX | SDIO_CMD | - | - | - |
| PA1 | ADC_IN1 | - | TIM2_CH2 | - | - | - | - | LTDC_R2 | - | TIM5_CH2 | - | QSPI2_SIOX3 | - | TIM9_CH2 | USART2_RTS | USART6_RX | QSPI1_SIO3 | - | - | - |
| PA2 | ADC_IN2, OPA3_P1 | - | TIM2_CH3 | - | - | - | - | LTDC_R1 | - | TIM5_CH3 | USART6_CK | TIM9_CH3 | - | - | USART2_TX | - | - | - | - | - |
| PA3 | ADC_IN3, OPA3_N1 | - | TIM2_CH4 | - | - | - | - | LTDC_B5 | - | TIM5_CH4 | - | TIM9_CH4 | - | - | USART2_RX | TIM10_CH3 | LTDC_B2 | - | - | - |
| PA4 | ADC_IN4, DAC1_OUT, OPA3_OUT1 | - | - | - | - | - | DVP_HSYNC | LTDC_VSYNC | - | TIM5_ETR | - | TIM9_ETR | SPI1_NSS | I2S3_WS, SPI3_NSS | USART2_CK | - | TIM10_CH4 | - | - | - |
| PA5 | ADC_IN5, DAC2_OUT, OPA1_OUT1 | - | TIM2_CH1_ETR | - | DVP_VSYNC | - | - | LTDC_R4 | - | TIM1_BKIN2 | TIM8_CH1N | - | SPI1_SCK | - | - | - | TIM10_ETR | - | - | - |
| PA6 | ADC_IN6, OPA1_P1 | - | TIM1_BKIN | CMP_OUT | LTDC_HSYNC | - | DVP_PCLK | LTDC_G2 | - | TIM3_CH1 | TIM8_BKIN | - | SPI1_MISO | - | - | - | TIM10_CH1 | - | - | - |
| PA7 | ADC_IN7, OPA1_N1 | - | TIM1_CH1N | - | - | - | - | LTDC_VSYNC | - | TIM3_CH2 | TIM8_CH1N | - | SPI1_MOSI | - | - | - | TIM10_CH2 | - | - | - |
| PA11 | OTG_DM | - | TIM1_CH4 | - | - | - | - | LTDC_R4 | - | - | - | USART3_CK | I2S2_WS, SPI2_NSS | USART6_RX | USART1_CTS | - | CAN1_RX | - | - | - |
| PA12 | OTG_DP | - | TIM1_ETR | - | - | TIM1_BKIN2 | - | LTDC_R5 | - | - | - | USART3_RTS | I2S2_CK, SPI2_SCK | USART6_TX | USART1_RTS | - | CAN1_TX | - | - | - |
| PA13 | - | - | I2S3_SD, SPI3_MOSI | - | - | - | SAI_SD_B | - | - | - | - | USART3_TX | CAN_RX | - | I2C3_SDA | LTDC_B2 | - | - | - | - |
| PA14 | SDMMC_D4 | - | I2S3_CK, SPI3_SCK | - | USART8_CK | - | SAI_SCK_B | LTDC_B6 | LTDC_R0 | - | - | USART3_RX | CAN_TX | - | I2C3_SCL | - | - | SDMMC_D4 | - | - |
| PA15 | SDMMC_D5 | - | TIM2_CH1_ETR | LTDC_B4 | USART8_TX | - | SAI_FS_B | LTDC_B6 | LTDC_CLK | - | - | USART3_CTS | SPI1_NSS | I2S3_WS, SPI3_NSS | I2C3_SMBA | USART6_RTS | LTDC_R3 | SDMMC_D5 | - | - |
| PB0 | ADC_IN8, CMP_P0, OPA1_P0 | MCO | TIM1_CH2N | - | - | - | TIM12_ETR | LTDC_G1 | - | TIM3_CH3 | TIM8_CH2N | TIM5_CH4 | - | DFSDM_CKOUT | - | USART6_CTS | LTDC_R3 | - | - | - |
| PB1 | ADC_IN9, CMP_N0, OPA1_N0, OPA2_OUT1 | - | TIM1_CH3N | - | - | - | - | LTDC_G0 | - | TIM3_CH4 | TIM8_CH3N | - | TIM12_CH1 | DFSDM_DATIN1 | - | - | LTDC_R6 | - | - | - |
| PB3 | - | - | TIM2_CH2 | - | USART8_RX | - | DVP_D5 | TIM12_ETR | - | - | - | CC1 | SPI1_SCK | I2S3_CK, SPI3_SCK | - | - | SDIO_D2 | - | - | - |
| PB4 | - | - | - | TIM4_ETR | USART8_TX | - | - | USART7_CK | - | TIM3_CH1 | - | CC2 | SPI1_MISO | SPI3_MISO | I2S2_WS, SPI2_NSS | - | SDIO_D3 | - | - | - |
| PB5 | - | TIM10_ETR | - | - | - | - | DVP_D10 | USART7_RX | - | TIM3_CH2 | LTDC_B5 | I2C1_SMBA | SPI1_MOSI | I2C4_SMBA | I2S3_SD, SPI3_MOSI | I2S2_MCK | CAN2_RX | - | - | - |
| PB6 | - | TIM10_CH1 | FSMC_A5 | QSPI1_SCSN | - | - | DVP_D5 | USART7_TX | - | TIM4_CH1 | CAN1_RX | I2C1_SCL | I2S3_MCK | I2C4_SCL | USART1_TX | - | CAN2_TX | - | - | - |
| PB7 | - | TIM10_CH2 | - | USART8_CK | - | - | DVP_VSYNC | - | - | TIM4_CH2 | CAN1_TX | I2C1_SDA | - | I2C4_SDA | USART1_RX | - | - | - | - | - |
| PB8 | SWCLK, USBHS_DP | - | TIM10_CH3 | SDIO_D4 | - | - | DVP_D6 | LTDC_B6 | - | TIM4_CH3 | - | I2C1_SCL | PIOC_IO0 | I2C4_SCL | - | USART6_RX | CAN1_RX | - | - | - |
| PB9 | SWDIO, SWIO, USBHS_DM | - | TIM10_CH4 | SDIO_D5 | I2C4_SMBA | - | DVP_D7 | LTDC_B7 | - | TIM4_CH4 | - | I2C1_SDA | I2S2_WS, SPI2_NSS | I2C4_SDA | PIOC_IO1 | USART6_TX | CAN1_TX | - | - | - |
| PC0 | ADC_IN10, HSADC_IN0 | TIM8_BKIN | - | QSPI2_SIO3 | LTDC_G2 | - | - | LTDC_R5 | - | - | DFSDM_CKIN0 | - | PIOC_IO1 | - | SAI_MCLK_A | - | I2C2_SCL | - | - | - |
| PC1 | ADC_IN11, HSADC_IN1 | TIM8_CH1N | - | QSPI2_SCSXN | SDIO_CK | - | - | LTDC_G5 | - | TIM5_CH1 | DFSDM_DATIN0 | - | I2S2_SD, SPI2_MOSI | - | PIOC_IO0, SAI_SD_A | - | I2C2_SDA | - | - | - |
| PC2 | ADC_IN12, HSADC_IN2, OPA3_P0 | TIM8_CH2N | - | QSPI2_SIOX0 | - | - | - | - | - | TIM5_CH2 | DFSDM_CKIN1 | - | SPI2_MISO | DFSDM_CKOUT | SAI_SCK_A | PIOC_IO1 | I2C2_SMBA | - | - | - |
| PC3 | ADC_IN13, HSADC_IN3, OPA3_N0 | TIM8_CH3N | - | QSPI2_SIOX1 | - | - | - | - | - | TIM5_CH3 | DFSDM_DATIN1 | - | I2S2_SD, SPI2_MOSI | - | SAI_FS_A | - | - | - | - | - |
| PC4 | ADC_IN14, CMP_N1, OPA1_OUT0 | - | - | - | - | - | - | LTDC_R7 | - | - | - | - | - | CAN3_RX | I3C_SCL | - | - | - | - | - |
| PC5 | ADC_IN15 | - | - | - | - | - | CMP_OUT | LTDC_DE | - | - | - | - | - | CAN3_TX | I3C_SDA | - | - | - | - | - |
| PC6 | SDMMC_D6 | - | - | - | SWPMI_IO | - | DVP_D0 | LTDC_HSYNC | - | TIM3_CH1 | TIM8_CH1 | - | I2S2_MCK | - | USART4_TX | - | SDIO_D6 | SDMMC_D6 | - | - |
| PC7 | SDMMC_D7 | - | - | - | SWPMI_TX | - | DVP_D1 | LTDC_G6 | - | TIM3_CH2 | TIM8_CH2 | - | - | I2S3_MCK | USART4_RX | - | SDIO_D7 | SDMMC_D7 | - | - |
| PC8 | SDMMC_D0 | - | - | - | SWPMI_RX | - | DVP_D2 | LTDC_G4 | - | TIM3_CH3 | TIM8_CH3 | - | - | TIM9_ETR | USART4_CK | USART7_RTS | - | - | - | - |
| PC9 | SDMMC_D1 | - | - | LTDC_G3 | SWPMI_SUP | - | DVP_D3 | LTDC_B2 | SAI_MCLK_B | TIM3_CH4 | TIM8_CH4 | I2C3_SDA | SPI3_MISO | TIM9_CH1 | - | USART7_CTS | QSPI1_SIO0 | SDMMC_D1 | - | - |
| PC10 | SDMMC_D2 | - | - | LTDC_B1 | SWPMI_RX | - | DVP_D8 | LTDC_R2 | LTDC_HSYNC | TIM9_CH2 | - | - | - | I2S3_CK, SPI3_SCK | USART3_TX | USART6_TX | QSPI1_SIO1 | - | SDMMC_CMD, SDMMC_STS | SDMMC_CMD, SDMMC_STS |
| PC11 | SDMMC_D3 | - | - | - | - | - | DVP_D4 | LTDC_B4 | LTDC_VSYNC | TIM9_CH4 | - | - | - | SPI3_MISO | USART3_RX | USART6_RX | QSPI1_SCSXN | - | SDMMC_STR | SDMMC_STR |
| PC12 | SDMMC_SDCK, SDMMC_SLVCK | - | - | - | - | - | DVP_D9 | LTDC_R6 | LTDC_DE | TIM9_CH3 | - | - | - | I2S3_SD, SPI3_MOSI | USART3_CK | USART7_TX | - | - | SDMMC_SDCK, SDMMC_SLVCK | SDMMC_SDCK, SDMMC_SLVCK |
| PD2 | SDMMC_CMD, SDMMC_STS | - | - | - | - | - | DVP_D11 | LTDC_B2 | LTDC_R5 | TIM3_ETR | - | - | - | - | - | USART7_RX | LTDC_B7 | - | SDMMC_D2 | SDMMC_D2 |
| PD3 | SDMMC_STR | - | - | - | - | - | DVP_D5 | LTDC_G7 | LTDC_R6 | TIM11_CH1 | DFSDM_CKOUT | - | I2S2_CK, SPI2_SCK | - | USART2_CTS | USART6_CK | TIM3_CH1 | - | SDMMC_D3 | SDMMC_D3 |
| PD9 | - | - | - | - | - | - | - | - | - | - | - | - | I3C_SCL | - | USART3_RX | - | - | - | - | - |
| PD10 | - | - | - | - | - | - | - | LTDC_B3 | - | - | DFSDM_CKOUT | LPTIM2_ETR | I3C_SDA | - | USART3_CK | - | - | SDMMC_STR | - | - |
| PE9 | OPA2_P0 | - | TIM1_CH1 | QSPI1_SIOX2 | - | - | - | - | - | - | DFSDM_CKOUT | - | - | - | - | SDIO_D1 | - | - | - | - |
| PE15 | - | - | TIM1_BKIN | - | USART5_CK | - | CMP_OUT | LTDC_R7 | - | TIM12_CH4 | I3C_SDA | - | - | - | QSPI2_SIO3 | SDIO_D7 | - | - | - | - |
| PF6 | - | - | - | QSPI1_SIO3 | - | - | TIM11_CH1 | - | - | CAN3_RX | SPI1_NSS | QSPI2_SCK | I3C_SCL | SAI_SD_B | USART8_RX | - | TIM10_CH3 | - | - | - |
| PF7 | - | - | - | QSPI1_SIO2 | - | - | TIM11_CH2 | - | - | CAN3_TX | SPI1_SCK | QSPI2_SCSN | I3C_SDA | SAI_MCLK_B | USART8_TX | - | TIM10_CH4 | - | - | - |
| PF8 | HSADC_IN4 | - | - | QSPI1_SIO0 | - | - | TIM11_CH3 | - | - | - | SPI1_MOSI | QSPI2_SIO0 | - | SAI_SCK_B | USART8_RTS | QSPI2_SIO0 | TIM10_CH1 | - | - | - |
| PF9 | HSADC_IN5 | - | - | QSPI1_SIO1 | USART8_RTS | - | TIM11_CH4 | - | - | - | SPI1_MISO | QSPI2_SIO1 | - | SAI_FS_B | USART8_CTS | - | TIM10_CH2 | - | - | - |
| PF10 | HSADC_IN6 | - | - | - | USART8_CTS | - | DVP_D11 | LTDC_DE | - | - | - | QSPI2_SIO2 | - | - | USART8_CK | TIM10_ETR | - | - | - | - |
| PF12 | OPA2_N1 | - | - | - | - | - | TIM12_CH3 | - | - | I2C4_SCL | PIOC_IO0 | - | - | - | - | - | - | - | - | - |
| PF13 | - | - | - | - | DVP_PCLK | - | TIM12_CH4 | - | - | I2C4_SDA | - | - | PIOC_IO1 | - | - | - | - | - | - | - |

</details>

### CH32H417 pin map

Pin functions (filterable): [ALL](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417) [ADC](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=ADC) [I2C](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=I2C) [SPI](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=SPI) [SYS](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=SYS) [TIM](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=TIM) [UART](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=UART) [USB](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417&features=USB)

<details><summary><b>CH32H417 pin map</b> (116 pads x 3 products)</summary>

| Pin name | Type | [CH32H417&#8203;MEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417MEU6)&#8203;(QFN88) | [CH32H417&#8203;QEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417QEU6)&#8203;(QFN128) | [CH32H417&#8203;WEU6](https://ch32-riscv-ug.github.io/ch32-device-data/pins.html?chip=CH32H417WEU6)&#8203;(QFN68) | Notes |
|---|---|---|---|---|---|
| PA0 | I/O/A | 21 | 34 | - |  |
| PA1 | I/O/A | - | 35 | - |  |
| PA2 | I/O/A | - | 36 | - |  |
| PA3 | I/O/A | - | 37 | - |  |
| PA4 | I/O/A | 22 | 39 | - |  |
| PA5 | I/O/A | 23 | 40 | 20 |  |
| PA6 | I/O/A | - | 41 | - |  |
| PA7 | I/O/A | - | 42 | - |  |
| PA8 | I/O | - | 87 | - |  |
| PA9 | I/O/A | 54 | 88 | - |  |
| PA10 | I/O/A | 55 | 89 | - |  |
| PA11 | I/O/A | 56 | 90 | - |  |
| PA12 | I/O/A | 57 | 91 | - |  |
| PA13 | I/O | 58 | 92 | 46 |  |
| PA14 | I/O | 60 | 94 | 47 |  |
| PA15 | I/O | 61 | 95 | 48 |  |
| PB0 | I/O/A | 24 | 45 | 21 |  |
| PB1 | I/O/A | 25 | 46 | 22 |  |
| PB2 | I/O/A | - | 47 | - |  |
| PB3 | I/O | 80 | 115 | - |  |
| PB4 | I/O | 81 | 116 | - |  |
| PB5 | I/O | - | 117 | - |  |
| PB6 | I/O | - | 118 | - |  |
| PB7 | I/O | - | 119 | - |  |
| PB8 | I/O/A | 82 | 120 | 67 | SWCLK |
| PB9 | I/O/A | 83 | 121 | 68 | SWDIO |
| PB10 | I/O | 32 | 61 | 26 |  |
| PB11 | I/O | 33 | 62 | 27 |  |
| PB12 | I/O | 36 | 65 | 30 |  |
| PB13 | I/O | 37 | 66 | 31 |  |
| PB14 | I/O | 38 | 67 | 32 |  |
| PB15 | I/O | - | 68 | - |  |
| PC0 | I/O/A | 15 | 26 | 15 |  |
| PC1 | I/O/A | 16 | 27 | 16 |  |
| PC2 | I/O/A | 17 | 28 | 17 |  |
| PC3 | I/O/A | 18 | 29 | 18 |  |
| PC4 | I/O/A | - | 43 | - |  |
| PC5 | I/O/A | - | 44 | - |  |
| PC6 | I/O | 50 | 83 | 42 |  |
| PC7 | I/O | 51 | 84 | 43 |  |
| PC8 | I/O | 52 | 85 | 44 |  |
| PC9 | I/O | 53 | 86 | 45 |  |
| PC10 | I/O | 62 | 96 | 49 |  |
| PC11 | I/O | 63 | 97 | 50 |  |
| PC12 | I/O | 64 | 98 | 51 |  |
| PD0 | I/O | 65 | 99 | 52 |  |
| PD1 | I/O | 66 | 100 | 53 |  |
| PD2 | I/O | 67 | 101 | 54 |  |
| PD3 | I/O | 68 | 102 | 55 |  |
| PD4 | I/O | 69 | 103 | 56 |  |
| PD5 | I/O | 70 | 104 | 57 |  |
| PD6 | I/O | 71 | 106 | 58 |  |
| PD7 | I/O | 72 | 107 | 59 |  |
| PD8 | I/O | - | 69 | - |  |
| PD9 | I/O | - | 70 | - |  |
| PD10 | I/O | 39 | 71 | 33 |  |
| PD11 | I/O | 40 | 72 | 34 |  |
| PD12 | I/O | 41 | 73 | 35 |  |
| PD13 | I/O | 42 | 74 | 36 |  |
| PD14 | I/O | 43 | 75 | 37 |  |
| PD15 | I/O | 44 | 76 | 38 |  |
| PE0 | I/O | 76 | 111 | 63 |  |
| PE1 | I/O | 77 | 112 | 64 |  |
| PE2 | I/O | - | 1 | - |  |
| PE3 | I/O/SDP | 2 | 2 | - |  |
| PE4 | I/O/SDP | 3 | 3 | - |  |
| PE5 | I/O/SDP | 4 | 4 | - |  |
| PE6 | I/O/SDP | 5 | 5 | - |  |
| PE7 | I/O/A | - | 52 | - |  |
| PE8 | I/O/A | - | 53 | - |  |
| PE9 | I/O/A | - | 54 | - |  |
| PE10 | I/O | 26 | 55 | - |  |
| PE11 | I/O | 27 | 56 | - |  |
| PE12 | I/O | 28 | 57 | - |  |
| PE13 | I/O | 29 | 58 | 23 |  |
| PE14 | I/O | 30 | 59 | 24 |  |
| PE15 | I/O | 31 | 60 | 25 |  |
| PF0 | I/O | 45 | 77 | 39 |  |
| PF1 | I/O | 46 | 78 | 40 |  |
| PF2 | I/O | 47 | 79 | 41 |  |
| PF3 | I/O | 73 | 108 | 60 |  |
| PF4 | I/O | 74 | 109 | 61 |  |
| PF5 | I/O | 75 | 110 | 62 |  |
| PF6 | I/O | - | 17 | - |  |
| PF7 | I/O | - | 18 | - |  |
| PF8 | I/O | - | 19 | - |  |
| PF9 | I/O/A | - | 20 | - |  |
| PF10 | I/O/A | - | 21 | - |  |
| PF11 | I/O/A | - | 48 | - |  |
| PF12 | I/O/A | - | 49 | - |  |
| PF13 | I/O | - | 50 | - |  |
| PF14 | I/O | 78 | 113 | 65 |  |
| MDIRN | ETH | 7 | 12 | 8 |  |
| MDIRP | ETH | 8 | 13 | 9 |  |
| MDITN | ETH | 9 | 14 | 10 |  |
| MDITP | ETH | 10 | 15 | 11 |  |
| NRST | I | 14 | 25 | - |  |
| PC13-RTC | I/O | - | 8 | - |  |
| PC14-OSC32_IN | I/O/A | - | 9 | - |  |
| PC15-OSC32_OUT | I/O/A | - | 10 | - |  |
| SSRXA | USB3.0 | 88 | 127 | 5 |  |
| SSRXB | USB3.0 | 87 | 126 | 4 |  |
| SSTXA | USB3.0 | 85 | 124 | 2 |  |
| SSTXB | USB3.0 | 84 | 123 | 1 |  |
| VBAT | P | - | 7 | - |  |
| VDD12A | P | 86 | 125 | 3 |  |
| VDD33 | P | 1/11/59 | 16/93/128 | 6/12 |  |
| VDD33A | P | 20 | 33 | 19 |  |
| VDDIO | P | 19/35 | 6/30/38/51/64/82/114 | 29 |  |
| VDDK | P | 6/48 | 11/80 | 7 |  |
| VIO18 | P | 34/49/79 | 63/81/105 | 28/66 |  |
| VREFP | P | - | 32 | - |  |
| VSS | P | EP | 22/122/EP | EP |  |
| VSSA | P | - | 31 | - |  |
| XI | I/A | 12 | 23 | 13 |  |
| XO | O/A | 13 | 24 | 14 |  |

</details>

<details><summary><b>CH32H417 alternate functions</b></summary>

| Pad | default | af-0 | af-1 | af-10 | af-11 | af-12 | af-13 | af-14 | af-15 | af-2 | af-3 | af-4 | af-5 | af-6 | af-7 | af-8 | af-9 | remap-1 | remap-2 | remap-3 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| PA0 | ADC_IN0, OPA3_OUT0 | - | TIM2_CH1_ETR | - | - | FSMC_D23, SDRAM_D23 | - | LTDC_R0 | SDRAM_DQM2 | TIM5_CH1 | TIM8_ETR | QSPI2_SIOX2 | PIOC_IO0 | TIM9_CH1 | USART2_CTS | USART6_TX | SDIO_CMD | - | - | - |
| PA1 | ADC_IN1 | - | TIM2_CH2 | - | - | FSMC_D24, SDRAM_D24 | - | LTDC_R2 | - | TIM5_CH2 | - | QSPI2_SIOX3 | - | TIM9_CH2 | USART2_RTS | USART6_RX | QSPI1_SIO3 | - | - | - |
| PA2 | ADC_IN2, OPA3_P1 | - | TIM2_CH3 | - | - | FSMC_D25, SDRAM_D25 | - | LTDC_R1 | - | TIM5_CH3 | USART6_CK | TIM9_CH3 | - | - | USART2_TX | - | - | - | - | - |
| PA3 | ADC_IN3, OPA3_N1 | - | TIM2_CH4 | - | - | FSMC_D26, SDRAM_D26 | - | LTDC_B5 | - | TIM5_CH4 | - | TIM9_CH4 | - | - | USART2_RX | TIM10_CH3 | LTDC_B2 | - | - | - |
| PA4 | ADC_IN4, DAC1_OUT, OPA3_OUT1 | - | - | - | - | FSMC_D27, SDRAM_D27 | DVP_HSYNC | LTDC_VSYNC | - | TIM5_ETR | - | TIM9_ETR | SPI1_NSS | I2S3_WS, SPI3_NSS | USART2_CK | - | TIM10_CH4 | - | - | - |
| PA5 | ADC_IN5, DAC2_OUT, OPA1_OUT1 | - | TIM2_CH1_ETR | - | DVP_VSYNC | FSMC_D28, SDRAM_D28 | - | LTDC_R4 | - | TIM1_BKIN2 | TIM8_CH1N | - | SPI1_SCK | - | - | - | TIM10_ETR | - | - | - |
| PA6 | ADC_IN6, OPA1_P1 | - | TIM1_BKIN | CMP_OUT | LTDC_HSYNC | - | DVP_PCLK | LTDC_G2 | - | TIM3_CH1 | TIM8_BKIN | - | SPI1_MISO | SDRAM_DQM2 | - | - | TIM10_CH1 | - | - | - |
| PA7 | ADC_IN7, OPA1_N1 | - | TIM1_CH1N | - | - | SDRAM_WE_N | - | LTDC_VSYNC | - | TIM3_CH2 | TIM8_CH1N | - | SPI1_MOSI | - | - | - | TIM10_CH2 | - | - | - |
| PA8 | - | - | TIM1_CH1 | - | USART8_RX | CMP_OUT | LTDC_B3 | LTDC_R6 | - | - | TIM8_BKIN2 | I2C3_SCL | - | SDRAM_DQM3 | USART1_CK | - | - | - | - | - |
| PA9 | OTG_VBUS | SDRAM_D10 | TIM1_CH2 | - | - | - | DVP_D0 | LTDC_R5 | - | - | - | I2C3_SMBA | I2S2_CK, SPI2_SCK | - | USART1_TX | SDRAM_D20 | - | - | - | - |
| PA10 | OTG_ID | SDRAM_D11 | TIM1_CH3 | FSMC_A6, SDRAM_A6 | - | LTDC_B4 | DVP_D1 | LTDC_B1 | - | - | - | - | - | USART6_CK | USART1_RX | SDRAM_D21 | - | - | - | - |
| PA11 | OTG_DM | SDRAM_D12 | TIM1_CH4 | FSMC_A7, SDRAM_A7 | - | - | - | LTDC_R4 | - | - | - | USART3_CK | I2S2_WS, SPI2_NSS | USART6_RX | USART1_CTS | SDRAM_D22 | CAN1_RX | - | - | - |
| PA12 | OTG_DP | SDRAM_D13 | TIM1_ETR | FSMC_A8, SDRAM_A8 | - | TIM1_BKIN2 | - | LTDC_R5 | - | - | - | USART3_RTS | I2S2_CK, SPI2_SCK | USART6_TX | USART1_RTS | SDRAM_D23 | CAN1_TX | - | - | - |
| PA13 | UHSIF_PORT29 | SDRAM_D14 | I2S3_SD, SPI3_MOSI | FSMC_A9, SDRAM_A9 | - | - | SAI_SD_B | - | - | - | SDRAM_BA1 | USART3_TX | CAN_RX | - | I2C3_SDA | LTDC_B2 | - | - | - | - |
| PA14 | SDMMC_D4, UHSIF_PORT30 | SDRAM_D15 | I2S3_CK, SPI3_SCK | - | USART8_CK | RGMII_RXDV | SAI_SCK_B | LTDC_B6 | LTDC_R0 | - | SDRAM_A0 | USART3_RX | CAN_TX | - | I2C3_SCL | - | - | SDMMC_D4 | - | - |
| PA15 | SDMMC_D5, UHSIF_PORT31 | FSMC_NBL3, SDRAM_DQM3 | TIM2_CH1_ETR | LTDC_B4 | USART8_TX | SDRAM_A1 | SAI_FS_B | LTDC_B6 | LTDC_CLK | - | RGMII_RXC | USART3_CTS | SPI1_NSS | I2S3_WS, SPI3_NSS | I2C3_SMBA | USART6_RTS | LTDC_R3 | SDMMC_D5 | - | - |
| PB0 | ADC_IN8, CMP_P0, OPA1_P0 | MCO | TIM1_CH2N | - | - | FSMC_D29, SDRAM_D29 | TIM12_ETR | LTDC_G1 | - | TIM3_CH3 | TIM8_CH2N | TIM5_CH4 | - | DFSDM_CKOUT | SDRAM_DQM3 | USART6_CTS | LTDC_R3 | UHSIF_PORT6 | UHSIF_PORT3 | UHSIF_PORT3 |
| PB1 | ADC_IN9, CMP_N0, OPA1_N0, OPA2_OUT1 | - | TIM1_CH3N | - | - | FSMC_D30, SDRAM_D30 | - | LTDC_G0 | - | TIM3_CH4 | TIM8_CH3N | - | TIM12_CH1 | DFSDM_DATIN1 | SDRAM_BA0 | - | LTDC_R6 | UHSIF_PORT7 | UHSIF_PORT4 | UHSIF_PORT4 |
| PB2 | CMP_P1 | - | - | - | - | FSMC_D31, SDRAM_D31 | TIM11_ETR | - | - | - | - | DFSDM_CKIN1 | TIM12_CH2 | SAI_SD_A | I2S3_SD, SPI3_MOSI | - | QSPI1_SCK | - | - | - |
| PB3 | - | - | TIM2_CH2 | - | USART8_RX | FSMC_A1, SDRAM_A1 | DVP_D5 | TIM12_ETR | - | - | - | CC1 | SPI1_SCK | I2S3_CK, SPI3_SCK | - | - | SDIO_D2 | - | - | - |
| PB4 | - | - | - | TIM4_ETR | USART8_TX | FSMC_A2, SDRAM_A2 | - | USART7_CK | - | TIM3_CH1 | - | CC2 | SPI1_MISO | SPI3_MISO | I2S2_WS, SPI2_NSS | - | SDIO_D3 | - | - | - |
| PB5 | - | TIM10_ETR | - | - | FSMC_D17, SDRAM_D17 | SDRAM_CKE1 | DVP_D10 | USART7_RX | - | TIM3_CH2 | LTDC_B5 | I2C1_SMBA | SPI1_MOSI | I2C4_SMBA | I2S3_SD, SPI3_MOSI | I2S2_MCK | CAN2_RX | - | - | - |
| PB6 | - | TIM10_CH1 | FSMC_A5 | QSPI1_SCSN | SDRAM_A5 | SDRAM_CS_N1 | DVP_D5 | USART7_TX | - | TIM4_CH1 | CAN1_RX | I2C1_SCL | I2S3_MCK | I2C4_SCL | USART1_TX | - | CAN2_TX | - | - | - |
| PB7 | - | TIM10_CH2 | - | USART8_CK | - | FSMC_NADV | DVP_VSYNC | - | - | TIM4_CH2 | CAN1_TX | I2C1_SDA | - | I2C4_SDA | USART1_RX | - | - | - | - | - |
| PB8 | SWCLK, USBHS_DP | - | TIM10_CH3 | SDIO_D4 | - | FSMC_A3, SDRAM_A3 | DVP_D6 | LTDC_B6 | - | TIM4_CH3 | - | I2C1_SCL | PIOC_IO0 | I2C4_SCL | - | USART6_RX | CAN1_RX | - | - | - |
| PB9 | SWDIO, SWIO, USBHS_DM | - | TIM10_CH4 | SDIO_D5 | I2C4_SMBA | FSMC_A4, SDRAM_A4 | DVP_D7 | LTDC_B7 | - | TIM4_CH4 | SDRAM_DQM2 | I2C1_SDA | I2S2_WS, SPI2_NSS | I2C4_SDA | PIOC_IO1 | USART6_TX | CAN1_TX | - | - | - |
| PB10 | UHSIF_PORT11 | SDRAM_A5 | TIM2_CH3 | - | QSPI2_SCSXN | FSMC_A10, SDRAM_A10 | - | LTDC_G4 | - | TIM9_CH2 | LPTIM2_CH1 | I2C2_SCL | I2S2_CK, SPI2_SCK | FSMC_A19 | USART3_TX | SDIO_CMD | USART6_CK | SDMMC_D2 | - | - |
| PB11 | UHSIF_PORT12 | SDRAM_A6 | TIM2_CH4 | - | QSPI2_SIOX0 | FSMC_A11, SDRAM_A11 | - | LTDC_G5 | - | FSMC_A20 | LPTIM2_ETR | I2C2_SDA | - | - | USART3_RX | SDIO_CK | TIM9_CH4 | SDMMC_D3 | - | - |
| PB12 | UHSIF_PORT13 | SDRAM_A7 | TIM1_BKIN | LTDC_VSYNC | QSPI2_SIOX1 | FSMC_A12, SDRAM_A12 | CMP_OUT | USART7_RX | DVP_PCLK | TIM8_BKIN | FSMC_A21 | I2C2_SMBA | I2S2_WS, SPI2_NSS | DFSDM_DATIN1 | USART3_CK | TIM9_CH3 | CAN2_RX | - | - | - |
| PB13 | UHSIF_PORT14 | SDRAM_A8 | TIM1_CH1N | ETH_PHY_LED3 | QSPI2_SIOX0 | FSMC_A13 | DVP_D2 | USART7_TX | FSMC_A22 | TIM8_BKIN2 | LPTIM2_OC | TIM9_ETR | I2S2_CK, SPI2_SCK | DFSDM_CKIN1 | USART3_CTS | DVP_HSYNC | CAN2_TX | SDMMC_D0 | - | - |
| PB14 | UHSIF_PORT15 | FSMC_A23, SDRAM_A9 | TIM1_CH2N | ETH_PHY_LED4 | QSPI2_SIOX1 | FSMC_A14, SDRAM_BA0 | USART7_CK | LTDC_CLK | DVP_VSYNC | TIM9_CH1 | TIM8_CH2N | USART1_TX | SPI2_MISO | LTDC_G0 | USART3_RTS | USART6_RTS | SDIO_D0 | - | - | - |
| PB15 | - | - | TIM1_CH3N | - | - | FSMC_A15, SDRAM_BA1 | - | LTDC_G7 | - | TIM9_CH2 | TIM8_CH3N | USART1_RX | I2S2_SD, SPI2_MOSI | - | - | USART6_CTS | SDIO_D1 | - | - | - |
| PC0 | ADC_IN10, HSADC_IN0 | TIM8_BKIN | ETH_MDC | QSPI2_SIO3 | LTDC_G2 | SDRAM_WE_N | - | LTDC_R5 | SDRAM_CAS_N | - | DFSDM_CKIN0 | FSMC_D4 | PIOC_IO1 | - | SAI_MCLK_A | - | I2C2_SCL | UHSIF_CLK | - | - |
| PC1 | ADC_IN11, HSADC_IN1 | TIM8_CH1N | ETH_MDIO | QSPI2_SCSXN | SDIO_CK | - | - | LTDC_G5 | SDRAM_WE_N | TIM5_CH1 | DFSDM_DATIN0 | FSMC_D5 | I2S2_SD, SPI2_MOSI | - | PIOC_IO0, SAI_SD_A | - | I2C2_SDA | UHSIF_PORT3 | UHSIF_PORT0 | UHSIF_PORT0 |
| PC2 | ADC_IN12, HSADC_IN2, OPA3_P0 | TIM8_CH2N | ETH_PPS | QSPI2_SIOX0 | - | SDRAM_CS_NO | - | - | SDRAM_DQM0 | TIM5_CH2 | DFSDM_CKIN1 | FSMC_D6 | SPI2_MISO | DFSDM_CKOUT | SAI_SCK_A | PIOC_IO1 | I2C2_SMBA | UHSIF_PORT4 | UHSIF_PORT1 | UHSIF_PORT1 |
| PC3 | ADC_IN13, HSADC_IN3, OPA3_N0 | TIM8_CH3N | - | QSPI2_SIOX1 | FSMC_D16, SDRAM_D16 | SDRAM_CKE0 | - | - | SDRAM_DQM1 | TIM5_CH3 | DFSDM_DATIN1 | FSMC_D7 | I2S2_SD, SPI2_MOSI | - | SAI_FS_A | - | - | UHSIF_PORT5 | UHSIF_PORT2 | UHSIF_PORT2 |
| PC4 | ADC_IN14, CMP_N1, OPA1_OUT0 | - | - | - | - | SDRAM_CS_N0 | - | LTDC_R7 | - | - | - | - | - | CAN3_RX | I3C_SCL | - | - | - | - | - |
| PC5 | ADC_IN15 | - | - | - | - | SDRAM_CKE0 | CMP_OUT | LTDC_DE | - | - | - | - | - | CAN3_TX | I3C_SDA | - | - | - | - | - |
| PC6 | SDMMC_D6, UHSIF_PORT25 | SDRAM_D6 | - | - | SWPMI_IO | RGMII_RXD3 | DVP_D0 | LTDC_HSYNC | - | TIM3_CH1 | TIM8_CH1 | FSMC_D8 | I2S2_MCK, SPI2_MCK | - | USART4_TX | - | SDIO_D6 | SDMMC_D6 | - | - |
| PC7 | SDMMC_D7, UHSIF_PORT26 | SDRAM_D7 | - | - | SWPMI_TX | RGMII_RXD2 | DVP_D1 | LTDC_G6 | - | TIM3_CH2 | TIM8_CH2 | FSMC_D9 | - | I2S3_MCK | USART4_RX | - | SDIO_D7 | SDMMC_D7 | - | - |
| PC8 | SDMMC_D0, UHSIF_PORT27 | SDRAM_D8 | - | - | SWPMI_RX | RGMII_RXD1 | DVP_D2 | LTDC_G4 | - | TIM3_CH3 | TIM8_CH3 | FSMC_D13 | - | TIM9_ETR | USART4_CK | USART7_RTS | - | - | - | - |
| PC9 | SDMMC_D1, UHSIF_PORT28 | SDRAM_D9 | - | LTDC_G3 | SWPMI_SUP | RGMII_RXD0 | DVP_D3 | LTDC_B2 | SAI_MCLK_B | TIM3_CH4 | TIM8_CH4 | I2C3_SDA | SPI3_MISO | TIM9_CH1 | FSMC_D14 | USART7_CTS | QSPI1_SIO0 | SDMMC_D1 | - | - |
| PC10 | SDMMC_D2, UHSIF_PORT32 | FSMC_NBL2, SDRAM_DQM2 | SDRAM_RAS_N | LTDC_B1 | SWPMI_RX | - | DVP_D8 | LTDC_R2 | LTDC_HSYNC | TIM9_CH2 | SDRAM_D24 | - | - | I2S3_CK, SPI3_SCK | USART3_TX | USART6_TX | QSPI1_SIO1 | - | SDMMC_CMD, SDMMC_STS, UHSIF_PORT32 | SDMMC_CMD, SDMMC_STS, UHSIF_PORT32 |
| PC11 | SDMMC_D3, UHSIF_PORT33 | FSMC_NBL1, SDRAM_DQM1 | - | - | - | - | DVP_D4 | LTDC_B4 | LTDC_VSYNC | TIM9_CH4 | SDRAM_D25 | - | - | SPI3_MISO | USART3_RX | USART6_RX | QSPI1_SCSXN | - | SDMMC_STR, UHSIF_PORT33 | SDMMC_STR, UHSIF_PORT33 |
| PC12 | SDMMC_SDCK, SDMMC_SLVCK, UHSIF_PORT34 | FSMC_NBL0, SDRAM_DQM0 | - | - | - | - | DVP_D9 | LTDC_R6 | LTDC_DE | TIM9_CH3 | SDRAM_D26 | - | - | I2S3_SD, SPI3_MOSI | USART3_CK | USART7_TX | - | - | SDMMC_SDCK, SDMMC_SLVCK, UHSIF_PORT34 | SDMMC_SDCK, SDMMC_SLVCK, UHSIF_PORT34 |
| PD0 | UHSIF_PORT35 | - | SDRAM_D10 | - | - | FSMC_D2, SDRAM_D2 | - | LTDC_B1 | LTDC_R3 | - | - | - | - | - | - | USART6_RX | CAN1_RX | - | SDMMC_D0, UHSIF_PORT35 | SDMMC_D0, UHSIF_PORT35 |
| PD1 | UHSIF_PORT36 | - | SDRAM_D11 | - | - | FSMC_D3, SDRAM_D3 | - | - | LTDC_R4 | - | - | - | - | - | - | USART6_TX | CAN1_TX | - | SDMMC_D1, UHSIF_PORT36 | SDMMC_D1, UHSIF_PORT36 |
| PD2 | SDMMC_CMD, SDMMC_STS, UHSIF_PORT37 | - | SDRAM_D12 | - | FSMC_A25 | - | DVP_D11 | LTDC_B2 | LTDC_R5 | TIM3_ETR | - | - | - | - | - | USART7_RX | LTDC_B7 | - | SDMMC_D2, UHSIF_PORT37 | SDMMC_D2, UHSIF_PORT37 |
| PD3 | SDMMC_STR, UHSIF_PORT38 | - | SDRAM_D13 | - | - | FSMC_CLK | DVP_D5 | LTDC_G7 | LTDC_R6 | TIM11_CH1 | DFSDM_CKOUT | - | I2S2_CK, SPI2_SCK | - | USART2_CTS | USART6_CK | TIM3_CH1 | - | SDMMC_D3, UHSIF_PORT38 | SDMMC_D3, UHSIF_PORT38 |
| PD4 | UHSIF_PORT39 | - | SDRAM_D14 | - | - | FSMC_NOE | - | LTDC_B4 | LTDC_R7 | TIM11_CH2 | - | - | - | - | USART2_RTS | USART7_CK | TIM3_CH2 | - | SDMMC_D4, UHSIF_PORT39 | SDMMC_D4, UHSIF_PORT39 |
| PD5 | UHSIF_PORT40 | - | SDRAM_D15 | - | - | FSMC_NWE | TIM11_ETR | LTDC_B5 | LTDC_G2 | TIM11_CH3 | - | - | - | - | USART2_TX | - | TIM3_CH3 | - | SDMMC_D5, UHSIF_PORT40 | SDMMC_D5, UHSIF_PORT40 |
| PD6 | UHSIF_PORT41 | - | - | - | USART5_CK | FSMC_NWAIT | DVP_D10 | LTDC_B2 | LTDC_G3 | TIM11_CH4 | SDRAM_CS_N0 | DFSDM_DATIN1 | I2S3_SD, SPI3_MOSI | SAI_SD_A | USART2_RX | - | TIM3_CH4 | - | SDMMC_D6, UHSIF_PORT41 | SDMMC_D6, UHSIF_PORT41 |
| PD7 | UHSIF_PORT42 | - | - | - | - | FSMC_NE1 | TIM11_CH3 | LTDC_B3 | LTDC_G4 | - | SDRAM_CS_N1 | USART5_RTS | SPI1_MOSI | DFSDM_CKIN1 | USART2_CK | - | - | - | SDMMC_D7, UHSIF_PORT42 | SDMMC_D7, UHSIF_PORT42 |
| PD8 | - | - | - | - | - | FSMC_D13, SDRAM_D13 | - | LTDC_B7 | - | - | - | - | - | - | USART3_TX | - | - | - | - | - |
| PD9 | - | SDRAM_A9 | - | - | - | FSMC_D14, SDRAM_D14 | - | - | - | - | - | - | I3C_SCL | - | USART3_RX | - | - | - | - | UHSIF_CLK |
| PD10 | UHSIF_PORT16 | SDRAM_A10 | - | RGMII_TXD3 | - | FSMC_D15, SDRAM_D15 | - | LTDC_B3 | - | - | DFSDM_CKOUT | LPTIM2_ETR | I3C_SDA | - | USART3_CK | - | - | SDMMC_STR | - | - |
| PD11 | UHSIF_PORT17 | SDRAM_A11 | LPTIM1_ETR | RGMII_TXD2 | LTDC_R4 | FSMC_A16 | - | USART1_CK | - | - | LPTIM2_CH2 | I2C4_SMBA | - | TIM5_ETR | USART3_CTS | - | QSPI1_SIO0 | SDMMC_SDCK, SDMMC_SLVCK | - | - |
| PD12 | UHSIF_PORT18 | SDRAM_A12 | LPTIM1_CH1 | RGMII_TXD1 | LTDC_R3 | FSMC_A17 | DVP_D4 | USART1_RX | - | TIM4_CH1 | LPTIM2_CH1 | I2C4_SCL | CAN3_RX | TIM5_CH1 | USART3_RTS | - | QSPI1_SIO1 | SDMMC_CMD, SDMMC_STS | - | - |
| PD13 | UHSIF_PORT19 | SDRAM_D0 | LPTIM1_OC | RGMII_TXD0 | - | FSMC_A18 | DVP_D5 | USART1_TX | - | TIM4_CH2 | LTDC_R2 | I2C4_SDA | CAN3_TX | TIM5_CH2 | - | - | QSPI1_SIO3 | - | - | - |
| PD14 | UHSIF_PORT20 | SDRAM_D1 | LPTIM1_CH2 | RGMII_TXEN | - | FSMC_D0, SDRAM_D0 | DVP_D6 | USART1_RTS | - | TIM4_CH3 | - | - | - | TIM5_CH3 | - | LTDC_B1 | QSPI1_SIO2 | - | - | - |
| PD15 | UHSIF_PORT21 | SDRAM_D2 | - | RGMII_GTXC | - | FSMC_D1, SDRAM_D1 | DVP_D7 | USART1_CTS | - | TIM4_CH4 | - | - | - | TIM5_CH4 | LTDC_G2 | - | - | - | - | - |
| PE0 | UHSIF_PORT46 | SDRAM_A3 | LPTIM1_CH1 | - | DVP_D0 | FSMC_NE4 | TIM11_CH1 | LTDC_B1 | LTDC_B3 | - | SDRAM_D30 | USART5_TX | - | - | USART4_RTS | - | LTDC_B4 | - | UHSIF_PORT46 | UHSIF_PORT46 |
| PE1 | UHSIF_PORT47 | SDRAM_A4 | LPTIM1_OC | - | DVP_D1 | FSMC_A24 | TIM11_CH2 | LTDC_R0 | LTDC_B4 | - | SDRAM_D31 | USART5_CTS | - | - | USART4_CTS | - | - | - | UHSIF_PORT47 | UHSIF_PORT47 |
| PE2 | - | - | - | - | - | FSMC_A23 | DVP_D2 | LTDC_R6 | - | - | - | USART5_RX | SPI4_SCK | SAI_MCLK_A | - | USART6_CK | SDRAM_CLK | - | - | - |
| PE3 | SERDES_TXP | TIM8_CH1 | SDRAM_DQM1 | - | USART5_TX | FSMC_A19 | DVP_D3 | - | - | TIM4_CH1 | TIM12_CH1 | - | PIOC_IO0 | SAI_SD_B | - | - | SDRAM_CS_N0 | - | - | - |
| PE4 | SERDES_TXN | TIM8_CH2 | - | - | - | FSMC_A20 | DVP_D4 | LTDC_B0 | - | TIM4_CH2 | TIM12_CH2 | PIOC_IO1 | SPI4_NSS | SAI_FS_A | - | - | SDRAM_CS_N1 | - | - | - |
| PE5 | SERDES_RXP | TIM8_CH3 | - | SDRAM_D27 | - | FSMC_A21 | DVP_D6 | LTDC_G0 | - | TIM4_CH3 | TIM12_CH3 | TIM9_CH3 | SPI4_MISO | SAI_SCK_A | - | - | SDRAM_CKE0, SDRAM_RAS_N | - | - | - |
| PE6 | SERDES_RXN | TIM8_CH4 | TIM1_BKIN2 | SDRAM_D28 | CMP_OUT | FSMC_A22 | DVP_D7 | LTDC_G1 | - | TIM4_CH4 | TIM12_CH4 | TIM9_CH4 | SPI4_MOSI | SAI_SD_A | SDRAM_CKE1 | USART8_CK | - | - | - | - |
| PE7 | OPA2_OUT0, UHSIF_PORT2 | - | TIM1_ETR | QSPI1_SIOX0 | - | FSMC_D4, SDRAM_D4 | - | - | - | - | - | - | - | - | USART8_RX | - | - | UHSIF_PORT2 | - | - |
| PE8 | OPA2_N0, UHSIF_PORT3 | - | TIM1_CH1N | QSPI1_SIOX1 | - | FSMC_D5, SDRAM_D5 | - | - | - | - | - | - | - | - | USART8_TX | SDIO_D0 | - | - | - | - |
| PE9 | OPA2_P0, UHSIF_PORT4 | - | TIM1_CH1 | QSPI1_SIOX2 | - | FSMC_D6, SDRAM_D6 | - | - | - | - | DFSDM_CKOUT | - | - | - | - | SDIO_D1 | - | - | - | - |
| PE10 | UHSIF_PORT5 | - | TIM1_CH2N | QSPI1_SIOX3 | - | FSMC_D7, SDRAM_D7 | - | - | SDRAM_BA1 | - | SDRAM_D17 | - | - | - | QSPI2_SCK | SDIO_D2 | - | - | UHSIF_PORT5 | UHSIF_PORT5 |
| PE11 | UHSIF_PORT6 | - | TIM1_CH2 | - | - | FSMC_D8, SDRAM_D8 | - | LTDC_G3 | SDRAM_A0 | - | SDRAM_D18 | - | SPI4_NSS | - | QSPI2_SCSN | SDIO_D3 | - | - | UHSIF_PORT6 | UHSIF_PORT6 |
| PE12 | UHSIF_PORT7 | - | TIM1_CH3N | - | - | FSMC_D9, SDRAM_D9 | CMP_OUT | LTDC_B4 | SDRAM_A1 | - | SDRAM_D19 | - | SPI4_SCK | - | QSPI2_SIO0 | SDIO_D4 | - | - | UHSIF_PORT7 | UHSIF_PORT7 |
| PE13 | UHSIF_PORT8 | - | TIM1_CH3 | - | - | FSMC_D10, SDRAM_D10 | - | LTDC_DE | SDRAM_A2 | TIM12_CH2 | - | - | SPI4_MISO | - | QSPI2_SIO1 | SDIO_D5 | - | - | - | - |
| PE14 | UHSIF_PORT9 | - | TIM1_CH4 | - | - | FSMC_D11, SDRAM_D11 | LTDC_CLK | SDRAM_A3 | - | TIM12_CH3 | I3C_SCL | - | SPI4_MOSI | - | QSPI2_SIO2 | SDIO_D6 | - | - | - | - |
| PE15 | UHSIF_PORT10 | - | TIM1_BKIN | - | USART5_CK | FSMC_D12, SDRAM_D12 | CMP_OUT | LTDC_R7 | SDRAM_A4 | TIM12_CH4 | I3C_SDA | - | - | - | QSPI2_SIO3 | SDIO_D7 | - | - | - | - |
| PF0 | UHSIF_PORT22 | - | - | ETH_PHY_LED0 | LTDC_R1 | DVP_D11 | - | LTDC_R7 | - | SDRAM_D3 | - | SDRAM_CS_N1 | QSPI2_SCK | - | USART4_CTS | - | - | - | - | - |
| PF1 | UHSIF_PORT23 | - | - | ETH_PHY_LED1 | - | FSMC_INT2 | - | LTDC_CLK | - | SDRAM_D4 | - | - | QSPI2_SCSN | SAI_MCLK_A | USART4_CK | LTDC_B0 | - | - | - | - |
| PF2 | UHSIF_PORT24 | - | - | ETH_PHY_LED2 | - | SDRAM_CLK | - | LTDC_G7 | - | SDRAM_D5 | TIM8_ETR | - | QSPI2_SIO0 | - | USART4_RTS | - | - | - | - | - |
| PF3 | UHSIF_PORT43 | - | - | - | DVP_D9 | FSMC_NCE2, FSMC_NE2 | DVP_VSYNC | LTDC_B0 | LTDC_G5 | CAN3_TX | SDRAM_RAS_N | SDRAM_CKE0 | SPI1_MISO | - | USART4_RX | - | QSPI1_SIOX2 | - | UHSIF_PORT43 | UHSIF_PORT43 |
| PF4 | UHSIF_PORT44 | - | LPTIM1_ETR | - | DVP_D8 | FSMC_NE3 | DVP_D2 | LTDC_B2 | LTDC_G6 | CAN3_RX | - | SDRAM_CKE1 | SPI1_NSS | - | USART4_TX | - | LTDC_G3 | - | UHSIF_PORT44 | UHSIF_PORT44 |
| PF5 | UHSIF_PORT45 | - | LPTIM1_CH2 | - | - | FSMC_A0, SDRAM_A0 | DVP_D3 | LTDC_B3 | LTDC_G7 | - | SDRAM_D29 | USART5_RX | SPI1_SCK | - | - | - | QSPI1_SIOX3 | - | UHSIF_PORT45 | UHSIF_PORT45 |
| PF6 | - | - | - | QSPI1_SIO3 | - | FSMC_D18, SDRAM_D18 | TIM11_CH1 | - | - | CAN3_RX | SPI1_NSS | QSPI2_SCK | I3C_SCL | SAI_SD_B | USART8_RX | - | TIM10_CH3 | - | - | - |
| PF7 | - | - | - | QSPI1_SIO2 | - | FSMC_D19, SDRAM_D19 | TIM11_CH2 | - | - | CAN3_TX | SPI1_SCK | QSPI2_SCSN | I3C_SDA | SAI_MCLK_B | USART8_TX | - | TIM10_CH4 | - | - | - |
| PF8 | HSADC_IN4 | - | - | QSPI1_SIO0 | - | FSMC_D20, SDRAM_D20 | TIM11_CH3 | - | - | - | SPI1_MOSI | QSPI2_SIO0 | - | SAI_SCK_B | USART8_RTS | QSPI2_SIO0 | TIM10_CH1 | - | - | - |
| PF9 | HSADC_IN5 | - | - | QSPI1_SIO1 | USART8_RTS | FSMC_D21, SDRAM_D21 | TIM11_CH4 | - | - | - | SPI1_MISO | QSPI2_SIO1 | - | SAI_FS_B | USART8_CTS | - | TIM10_CH2 | - | - | - |
| PF10 | HSADC_IN6 | - | - | - | USART8_CTS | FSMC_D22, SDRAM_D22 | DVP_D11 | LTDC_DE | - | - | - | QSPI2_SIO2 | - | - | USART8_CK | TIM10_ETR | - | - | - | - |
| PF11 | OPA2_P1, UHSIF_CLK | - | - | - | - | SDRAM_RAS_N | - | - | - | I2C4_SMBA | - | - | - | - | - | - | - | - | - | - |
| PF12 | OPA2_N1, UHSIF_PORT0 | - | - | - | - | SDRAM_CAS_N | TIM12_CH3 | - | - | I2C4_SCL | PIOC_IO0 | - | - | - | - | - | - | UHSIF_PORT0 | - | - |
| PF13 | UHSIF_PORT1 | - | - | - | DVP_PCLK | - | TIM12_CH4 | - | - | I2C4_SDA | - | - | PIOC_IO1 | - | - | - | - | UHSIF_PORT1 | - | - |
| PF14 | - | - | SDRAM_CLK | - | DVP_D5 | FSMC_NADV | - | - | LTDC_B5 | - | - | - | PIOC_IO1 | - | - | - | - | - | UHSIF_CLK | - |
| PC13-RTC | - | - | RTC | - | - | FSMC_A5, SDRAM_A5 | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| PC14-OSC32_IN | OSC32_IN | - | - | - | - | FSMC_D16, SDRAM_D16 | - | - | - | - | - | - | - | - | - | - | SDRAM_CKE1 | - | - | - |
| PC15-OSC32_OUT | OSC32_OUT | - | - | - | - | FSMC_D17, SDRAM_D17 | - | - | - | - | - | - | - | - | - | - | SDRAM_RAS_N | - | - | - |

</details>

<details><summary><b>Remap selectors (AFIO)</b></summary>

| Series | Field | Register | Bits | Values | Reset |
|---|---|---|---|---|---|
| CH32H416 | SDMMC_REMAP | PCFR1 | PCFR1:10;PCFR1:11 | 0;1;2;3 | 0 |
| CH32H417 | SDMMC_REMAP | PCFR1 | PCFR1:10;PCFR1:11 | 0;1;2;3 | 0 |
| CH32H417 | UHSIF_CLK_REMAP | PCFR1 | PCFR1:6;PCFR1:7 | 0;1;2;3 | 0 |
| CH32H417 | UHSIF_PORT_REMAP | PCFR1 | PCFR1:8;PCFR1:9 | 0;1;2;3 | 0 |

</details>

## Block diagrams

### CH32H415
<img src="image/architecture_CH32H415.png" alt="CH32H415 block diagram" />

### CH32H416
<img src="image/architecture_CH32H416.png" alt="CH32H416 block diagram" />

### CH32H417
<img src="image/architecture_CH32H417.png" alt="CH32H417 block diagram" />

## Errata

- The blue-marked sections of the clock tree diagram in the datasheet are not applicable (they only apply to chips whose 5th lot-number digit is greater than 0). *(applies: CH32H415, CH32H416, CH32H417; 5th digit of lot number = 0)*
- GPHA, Ethernet, SerDes and CAN functions are not provided. *(applies: CH32H415, CH32H416, CH32H417; 5th digit of lot number = 0)*

## EVT examples

233 routines in [EVT/EXAM](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM):

[ADC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/ADC) 14 · [APPLICATION](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/APPLICATION) 3 · [CAN](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/CAN) 3 · [CPU](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/CPU) 19 · [CRC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/CRC) 1 · [DAC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/DAC) 6 · [DFSDM](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/DFSDM) 11 · [DMA](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/DMA) 4 · [DVP](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/DVP) 3 · [ECDC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/ECDC) 2 · [ETH](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/ETH) 15 · [EXTI](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/EXTI) 1 · [FLASH](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/FLASH) 2 · [FMC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/FMC) 9 · [GPHA](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/GPHA) 2 · [GPIO](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/GPIO) 1 · [HSADC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/HSADC) 1 · [I2C](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/I2C) 6 · [I2S](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/I2S) 3 · [I3C](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/I3C) 3 · [IAP](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/IAP) 1 · [IWDG](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/IWDG) 1 · [LPTIM](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/LPTIM) 2 · [LTDC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/LTDC) 1 · [OPA](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/OPA) 2 · [PIOC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/PIOC) 18 · [PWR](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/PWR) 6 · [QSPI](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/QSPI) 3 · [RCC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/RCC) 3 · [RNG](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/RNG) 1 · [RTC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/RTC) 2 · [SAI](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SAI) 1 · [SDIO](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SDIO) 2 · [SDMMC](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SDMMC) 4 · [SPI](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SPI) 5 · [SWPMI](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SWPMI) 2 · [SerDes](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/SerDes) 2 · [TIM](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/TIM) 15 · [TKey](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/TKey) 3 · [UHSIF](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/UHSIF) 1 · [USART](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/USART) 7 · [USB](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/USB) 39 · [USBPD](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/USBPD) 2 · [WWDG](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT/EXAM/WWDG) 1

## Documents

| Document | Kind | English | 中文 |
|---|---|---|---|
| CH32H417DS0.PDF | datasheet | [page](https://www.wch-ic.com/downloads/CH32H417DS0_PDF.html) [mirror](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417DS0.PDF) v1.8 | [page](https://www.wch.cn/downloads/CH32H417DS0_PDF.html) [mirror](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417DS0.PDF) v1.8 |
| CH32H417RM.PDF | reference-manual | [page](https://www.wch-ic.com/downloads/CH32H417RM_PDF.html) [mirror](https://ch32-riscv-ug.github.io/CH32H417/datasheet_en/CH32H417RM.PDF) v1.7 | [page](https://www.wch.cn/downloads/CH32H417RM_PDF.html) [mirror](https://ch32-riscv-ug.github.io/CH32H417/datasheet_zh/CH32H417RM.PDF) v1.7 |
| CH32H417EVT.ZIP | evt | [page](https://www.wch-ic.com/downloads/CH32H417EVT_ZIP.html) [mirror](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT) v1.3 | [page](https://www.wch.cn/downloads/CH32H417EVT_ZIP.html) [mirror](https://github.com/ch32-riscv-ug/CH32H417/tree/main/EVT) v1.5 |

### Evaluation boards

- board-manual:en: [CH32H417 Evaluation Board Reference-EN.pdf](https://github.com/ch32-riscv-ug/CH32H417/blob/main/EVT/PUB/CH32H417%20Evaluation%20Board%20Reference-EN.pdf)
- board-manual:zh: [CH32H417评估板说明书.pdf](https://github.com/ch32-riscv-ug/CH32H417/blob/main/EVT/PUB/CH32H417%E8%AF%84%E4%BC%B0%E6%9D%BF%E8%AF%B4%E6%98%8E%E4%B9%A6.pdf)
- schematic-pdf: [CH32H417SCH.pdf](https://github.com/ch32-riscv-ug/CH32H417/blob/main/EVT/PUB/CH32H417SCH.pdf)

7 board schematics under `EVT/PUB/SCHPCB/`: `CH32H415REU6-R0`, `CH32H416RDU6-R0`, `CH32H417MEU6-R0`, `CH32H417MEU6-UHSIF-R0`, `CH32H417QEU-R1`, `CH32H417QEU6-R0`, `CH32H417WEU6-R0`

## Reference

### Address map

| Region | Base | Kind |
|---|---|---|
| HBPERIPH | `0x40000000` | bus |
| PERIPH | `0x40000000` | bus |
| FLASH (V3F) | `0x00000000` | link-origin |
| FLASH (V5F) | `0x00010000` | link-origin |
| RAM (V5F) | `0x200c0300` | link-origin |
| RAM (V3F) | `0x20110100` | link-origin |
| FLASH | `0x08000000` | memory |
| OB | `0x1ffff800` | memory |
| SRAM | `0x20100000` | memory |

`link-origin` is what the EVT linker scripts use; the `memory` row for FLASH is the address the device header states. Both windows are real -- CH32V307 answers at `0x08000000` and at `0x00000000`.

Peripheral base addresses are in [memory_map.csv](https://github.com/ch32-riscv-ug/ch32-device-data/blob/main/evidence/memory_map.csv); interrupt numbers in [interrupts.csv](https://github.com/ch32-riscv-ug/ch32-device-data/blob/main/evidence/interrupts.csv).

---
Data: [ch32-device-data](https://github.com/ch32-riscv-ug/ch32-device-data) (evidence/ and index/ -- each value carries its evidence and confidence there).
