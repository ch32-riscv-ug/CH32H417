/********************************** (C) COPYRIGHT *******************************
* File Name          : hub.h
* Author             : WCH
* Version            : V1.0
* Date               : 2025/05/30
* Description        : This file contains all the functions prototypes for the
*                      ch32h417 operation of hub.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __HUB_H
#define __HUB_H

#define HUB_ERR_SCUESS                0x02
#define HUB_ERR_CONNECT               0x01
#define HUB_ERR_DISCONNECT            0x00
#define HUB_CS_NAK                    0x2a
#define HUB_DEVICE_DISCONNECT         0x00           // 0-disconnect  1-connect  2-config
#define HUB_DEVICE_CONNECT            0x01
#define HUB_DEVICE_CONFIG             0x02
#define HUB_DEVICE_CONFIG_SUCESS      0x03
#define C_PORT_CONNECT_ST            (1<<0)          // Device attach event
#define C_PORT_OVC_ST                (1<<3)          // Port over?current event
#define C_PORT_RESET_ST              (1<<4)          // HOT?RESET event
#define C_PORT_BHRESET_ST            (1<<5)          // WRAM?RESET event
#define C_PORT_LINK_STATE_ST         (1<<6)          // Link state change event
#define C_PORT_CFG_ERR_ST            (1<<7)          // Port configuration error event
#define PORT_CONNECT_ST              (1<<0)
#define PORT_ENABLE_ST               (1<<1)
#define PORT_OVC_ST                  (1<<3)
#define PORT_RESET_ST                (1<<4)
#define PORT_PWR_ST                  (1<<9)
#define LINK_HUB_STATE_MASK          (0xF<<5)
#define PORT_LINK_U0                 (0x0<<5)
#define PORT_LINK_U1                 (0x1<<5)
#define PORT_LINK_U2                 (0x2<<5)
#define PORT_LINK_U3                 (0x3<<5)
#define PORT_LINK_DISABLED           (0x4<<5)
#define PORT_LINK_RXDET              (0x5<<5)
#define PORT_LINK_INACTIVE           (0x6<<5)
#define PORT_LINK_POLLING            (0x7<<5)
#define PORT_LINK_RECOVERY           (0x8<<5)
#define PORT_LINK_HOTRST             (0x9<<5)
#define PORT_LINK_COMPLIANCE         (0xA<<5)
#define PORT_LINK_LOOPBACK           (0xB<<5)
#define C_PORT_CONNECTION            16
#define C_PORT_ENABLE                17
#define C_PORT_SUSPEND               18
#define C_PORT_OVER_CURRENT          19
#define C_PORT_RESET                 20
#define PORT_TEST_MODE               21
#define PORT_INDI                    22
#define C_PORT_L1                    23
#define C_PORT_LINK_STATE            25
#define C_PORT_CFG_ERR               26
#define C_BH_PORT_RESET              29
#define HUB_DEVICE                   0x09
#define UDISK_DEVICE                 0x08
#define HID_DEVICE                   0x03
//0?Full?Speed, 1?High?Speed, 2?Low?Speed ,3 --Super?Speed
#define FULL_SPEED                   0x00
#define HIGH_SPEED                   0X01
#define LOW_SPEED                    0x02
typedef struct  __attribute__((packed)) _HUB_Endp_Info {
    UINT8 Num;                          // Endpoint number
    UINT8 EndpType;                     // Endpoint type: 1?ISO, 2?BULK, 3?INTERRUPT
    UINT8 tog;
    UINT8 HighTransNum;                 // Number of transactions per microframe (<=3)
    UINT8 Brust;
    UINT16 Endp_Size;                   // Endpoint maximum packet size
} HUB_Endp_Info, *PHUB_Enpd_Info;
typedef struct  __attribute__((packed)) _HUB_Port_Info {
    UINT8 Status;
    UINT8 Speed;                        // [8]?S, 0?Low?Speed, 1?Full?Speed;
    UINT8 Num;                          // Port number
    UINT8 Addr;                         // Device address under this HUB port
    UINT8 DeviceType;                   // Connected device type
    UINT8 EndpNum;                      // Number of endpoints
    UINT8 PortpChangeField;             // Port state change bitmap
    HUB_Endp_Info portEndp[8];          // 8 endpoint descriptors
} HUB_Port_Info, *PHUB_Port_Info;
typedef struct  __attribute__((packed)) _USB_HUB_Info {
    UINT8 Status;                       // 0?disconnect  1?connect  2?config
    UINT8 Speed;                        // 0?Full?Speed, 1?High?Speed, 2?Low?Speed ,3 --Super?Speed
    UINT8 IntEndpnum;
    UINT8 DevAddr;
    UINT8 EndpSize;
    UINT8 Numofport;
    HUB_Port_Info portD[4];
} USB_HUB_Info, *PUSB_HUB_Info;
typedef struct  __attribute__((packed)) _USB_HUB_SaveData {
    UINT8 Depth;
    UINT8 UpLevelPort;
    UINT8 CurrentPort;
    UINT8 Device_Type;                          // 09 represents HUB device
    USB_HUB_Info HUB_Info;
} USB_HUB_SaveData;
extern uint8_t DATA_BUFFER[ 34*1024 ];
extern  USB_HUB_SaveData SS_HUB_SaveData;       // Super?Speed device context
extern USB_HUB_SaveData HS_HUB_SaveData;        // High?Speed / Full?Speed device context
extern USB_HUB_Info HubInfo[8];
extern uint8_t U30OST_GetHUBDevDescr( uint8_t *buf ,uint16_t *len );
extern uint8_t U30OST_GetHUBDevStatus( uint8_t *buf ,uint16_t *len );
extern uint8_t U30OST_SetHUBDevDepth( uint8_t depth );
extern uint8_t U30OST_GetHubStatus( uint8_t *buf ,uint16_t *len );
extern uint8_t U30OST_GetHubPortStatus( uint8_t port ,uint8_t *buf );
extern void U30HOST_SetSelfAddress( uint8_t addr );
extern uint8_t  U30HOST_ConnectDevice( void );
extern uint8_t U30HOST_HUB_DEV_Enumerate( uint8_t i );
extern void  U30HOST_HUBSaveVari( uint8_t port,uint8_t index  );
extern void U30HOST_HUB_DEV_MainProcess( void );
extern uint8_t  U30HOST_CheckDeviceStatus( uint8_t port );
/*
    USB2.0 function prototypes
*/
extern uint8_t  U20HOST_ConnectDevice( void );
extern void U20HOST_HUB_DEV_MainProcess( void );
extern uint8_t  U20HOST_CheckDeviceStatus( uint8_t port );
extern uint8_t FAT_Init( uint8_t port );
#endif
