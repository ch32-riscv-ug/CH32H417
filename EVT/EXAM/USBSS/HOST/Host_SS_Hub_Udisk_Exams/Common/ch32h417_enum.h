/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32h417_enum.h
* Author             : WCH
* Version            : V1.0
* Date               : 2025/05/30
* Description        : This file contains all the functions prototypes for the
*                      CH32H417 USB enumeration module.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __CH32H417_ENUM_H__
#define __CH32H417_ENUM_H__
#include "ch32h417_usb.h"
#ifndef TRUE
#define TRUE                    1
#define FALSE                   0
#endif
#ifndef NULL
#define NULL                    0
#endif
#ifndef VOID
#define VOID                    void
#endif
#ifndef CONST
#define CONST                   const
#endif
#ifndef BOOL
typedef unsigned char           BOOL;
#endif
#ifndef BOOLEAN
typedef unsigned char           BOOLEAN;
#endif
#ifndef CHAR
typedef char                    CHAR;
#endif
#ifndef INT8
typedef char                    INT8;
#endif
#ifndef INT16
typedef short                   INT16;
#endif
#ifndef INT32
typedef long                    INT32;
#endif
#ifndef INT64
typedef long long               INT64;
#endif
#ifndef UINT8
typedef unsigned char           UINT8;
#endif
#ifndef UINT16
typedef unsigned short          UINT16;
#endif
#ifndef UINT32
typedef unsigned long           UINT32;
#endif
#ifndef UINT64
typedef unsigned long long      UINT64;
#endif
#ifndef UINT8V
typedef unsigned char volatile  UINT8V;
#endif
#ifndef UINT16V
typedef unsigned short volatile UINT16V;
#endif
#ifndef UINT32V
typedef unsigned long volatile  UINT32V;
#endif
#ifndef UINT64V
typedef unsigned long long volatile  UINT64V;
#endif
#ifndef PVOID
typedef void                    *PVOID;
#endif
#ifndef PCHAR
typedef char                    *PCHAR;
#endif
#ifndef PCHAR
typedef const char              *PCCHAR;
#endif
#ifndef PINT8
typedef char                    *PINT8;
#endif
#ifndef PINT16
typedef short                   *PINT16;
#endif
#ifndef PINT32
typedef long                    *PINT32;
#endif
#ifndef PUINT8
typedef unsigned char           *PUINT8;
#endif
#ifndef PUINT16
typedef unsigned short          *PUINT16;
#endif
#ifndef PUINT32
typedef unsigned long           *PUINT32;
#endif
#ifndef PUINT8V
typedef volatile unsigned char  *PUINT8V;
#endif
#ifndef PUINT16V
typedef volatile unsigned short *PUINT16V;
#endif
#ifndef PUINT32V
typedef volatile unsigned long  *PUINT32V;
#endif
#ifdef __cplusplus
extern "C" {
#endif
#define ERR_SUCCESS             0x14
#define ERR_USB_UNKNOWN         0xFA
#define ERR_USB_TRANSFER        0x20    /* More error codes such as NAK / STALL range from 0x20 ~ 0x2F */
#define ERR_USB_CONNECT         0x15    /* USB device connect event detected, device connected */
#define ERR_USB_DISCON          0x16    /* USB device disconnect event detected, device disconnected */
#define ERR_USB_BUF_OVER        0x17    /* USB transfer data error or buffer overflow */
#define ERR_USB_LENGTH          0x18
#define ERR_USB_DATAERR         0x19
/* Status code 1XH for USB host operation, user?definable values below for CH37x compatibility */
#define ERR_USB_UNKNOWN                         0xFA            /* Unknown error, check hardware or firmware logic */
#ifndef USB_INT_SUCCESS
#define USB_OPERATE_SUCCESS                     0x00            /* USB operation success */
#define USB_OPERATE_ERROR                       0x01            /* USB operation failed */
#define USB_PARAMETER_ERROR                     0x03            /* Invalid parameter or out?of?range value */
#define USB_INT_CONNECT_U20                     0x13            /* USB2.0 device connect event detected */
#define USB_INT_SUCCESS                         0x14            /* USB transaction / transfer completed successfully */
#define USB_INT_CONNECT                         0x15            /* USB device connect event detected */
#define USB_INT_DISCONNECT                      0x16            /* USB device disconnect event detected */
#define USB_INT_BUF_OVER                        0x17            /* Control transfer data exceeds buffer size */
#define USB_INT_DISK_ERR                        0x1F            /* USB mass?storage operation failed */
#define USB_INT_DISK_ERR1                       0x20            /* USB mass?storage operation failed */
#define USB_CH417USBTIMEOUT                     0x28            /* USB device transfer timeout */
#endif
#define USB_CH417USBTIMEOUTVALUE                0x3fffff
#define U30_PID_OUT                         0x00            /* OUT token PID */
#define U30_PID_IN                          0x01            /* IN token PID */
//extern void u2_setup_packet( UINT32 tx_len );
//void u2_get_data( UINT32 endp_num );
//void u2_send_data( UINT32 endp_num, UINT32 tx_len );
//void u2_set_address( UINT32 address );
// USB CONTROL register bits
#define DMA_EN              1<<0
#define USB_ALL_CLR         1<<1
#define USB_FORCE_RST       1<<2
#define INT_BUSY_EN         1<<3
#define DEV_PU_EN           1<<4
#define HOST_MODE           1<<7
// UHOST control bits
#define HOST_TX_EN          1<<14
#define HOST_RX_EN          1<<11
#define SEND_BUS_RESET      (UINT32)(1<<8)
#define SEND_BUS_SUSPEND    (UINT32)(1<<9)
#define SEND_BUS_RESUME     (UINT32)(1<<10)
//#define LINK_READY          (UINT32)(1<<14)
#define SEND_SOF_EN         (UINT32)(1<<15)
// Interrupt enable bits
#define USB2_DETECT_EN      1<<16
#define USB2_ACT_EN         1<<17
#define USB2_SUSP_EN        1<<18
#define USB2_SOF_EN         1<<19
#define USB2_OVER_EN        1<<20
#define USB2_SETUP_EN       1<<21
#define USB2_ISO_EN         1<<22
#define USB2_ATTACH         1<<9
// Interrupt flag bits
#define USB2_DETECT_FLAG    1<<16
#define USB2_ACT_FLAG       1<<17
#define USB2_SUSP_FLAG      1<<18
#define USB2_SOF_FLAG       1<<19
#define USB2_OVER_FLAG      1<<20
#define USB2_SETUP_FLAG     1<<21
#define USB2_ISO_FLAG       1<<22
#define EP_T_RES_MASK       3<<16
#define EP_T_RES_ACK        0<<16
#define EP_T_RES_NYET       1<<16
#define EP_T_RES_NAK        2<<16
#define EP_T_RES_STALL      3<<16
#define EP_T_TOG_0          0<<19
#define EP_T_TOG_1          1<<19
#define EP_R_RES_MASK       3<<24
#define EP_R_RES_ACK        0<<24
#define EP_R_RES_NYET       1<<24
#define EP_R_RES_NAK        2<<24
#define EP_R_RES_STALL      3<<24
#define EP_R_TOG_0          0<<19
#define EP_R_TOG_1          1<<27
#define TOG_MATCH           (UINT32)(1<<30)
// PID encoding: 00?OUT, 01?SOF, 10?IN, 11?SETUP
#define PID_OUT     0
#define PID_SOF     1
#define PID_IN      2
//#define PID_SETUP 3
/* Connected device speed definition */
#define USB_DEV_SPEED_LS        0x01                    /* Low?Speed device */
#define USB_DEV_SPEED_FS        0x00                    /* Full?Speed device */
#define USB_DEV_SPEED_HS        0x02
/* USB PID token definitions */
#ifndef USB_PID_SETUP
#define USB_PID_NULL            0x00    /* Reserved PID */
#define USB_PID_PING            0x04
#define USB_PID_SOF             0x05
#define USB_PID_SETUP           0x0D
#define USB_PID_IN              0x09
#define USB_PID_OUT             0x01
#define USB_PID_ACK             0x02
#define USB_PID_NAK             0x0A
#define USB_PID_STALL           0x0E
#define USB_PID_NYET            0x06
#define USB_PID_DATA0           0x03
#define USB_PID_DATA1           0x0B
#define USB_PID_PRE             0x0C
#define USB_PID_ERR             0x0C
#define USB_PID_SPLIT           0x08
#define USB_PID_DATA0           0x03
#define USB_PID_DATA1           0x0B
#define USB_PID_DATA2           0x07
#define USB_PID_MDATA           0x0F
#endif
/* USB standard device request codes */
#ifndef USB_GET_DESCRIPTOR
#define USB_GET_STATUS          0x00
#define USB_CLEAR_FEATURE       0x01
#define USB_SET_FEATURE         0x03
#define USB_SET_ADDRESS         0x05
#define USB_GET_DESCRIPTOR      0x06
#define USB_SET_DESCRIPTOR      0x07
#define USB_GET_CONFIGURATION   0x08
#define USB_SET_CONFIGURATION   0x09
#define USB_GET_INTERFACE       0x0A
#define USB_SET_INTERFACE       0x0B
#define USB_SYNCH_FRAME         0x0C
#endif
/* USB hub class request codes */
#ifndef HUB_GET_DESCRIPTOR
#define HUB_GET_STATUS          0x00
#define HUB_CLEAR_FEATURE       0x01
#define HUB_GET_STATE           0x02
#define HUB_SET_FEATURE         0x03
#define HUB_GET_DESCRIPTOR      0x06
#define HUB_SET_DESCRIPTOR      0x07
#endif
/* USB HID class request codes */
#ifndef HID_GET_REPORT
#define HID_GET_REPORT          0x01
#define HID_GET_IDLE            0x02
#define HID_GET_PROTOCOL        0x03
#define HID_SET_REPORT          0x09
#define HID_SET_IDLE            0x0A
#define HID_SET_PROTOCOL        0x0B
#endif
/* Bit definitions for USB request type */
#ifndef USB_REQ_TYP_MASK
#define USB_REQ_TYP_IN          0x80            /* Control IN, device to host */
#define USB_REQ_TYP_OUT         0x00            /* Control OUT, host to device */
#define USB_REQ_TYP_READ        0x80            /* Control read transfer */
#define USB_REQ_TYP_WRITE       0x00            /* Control write transfer */
#define USB_REQ_TYP_MASK        0x60            /* Request type bit mask */
#define USB_REQ_TYP_STANDARD    0x00
#define USB_REQ_TYP_CLASS       0x20
#define USB_REQ_TYP_VENDOR      0x40
#define USB_REQ_TYP_RESERVED    0x60
#define USB_REQ_RECIP_MASK      0x1F            /* Recipient bit mask */
#define USB_REQ_RECIP_DEVICE    0x00
#define USB_REQ_RECIP_INTERF    0x01
#define USB_REQ_RECIP_ENDP      0x02
#define USB_REQ_RECIP_OTHER     0x03
#endif
/* Request type for hub?class requests */
#ifndef HUB_GET_HUB_DESCRIPTOR
#define HUB_CLEAR_HUB_FEATURE   0x20
#define HUB_CLEAR_PORT_FEATURE  0x23
#define HUB_GET_BUS_STATE       0xA3
#define HUB_GET_HUB_DESCRIPTOR  0xA0
#define HUB_GET_HUB_STATUS      0xA0
#define HUB_GET_PORT_STATUS     0xA3
#define HUB_SET_HUB_DESCRIPTOR  0x20
#define HUB_SET_HUB_FEATURE     0x20
#define HUB_SET_PORT_FEATURE    0x23
#endif
/* Hub class feature selectors */
#ifndef HUB_PORT_RESET
#define HUB_C_HUB_LOCAL_POWER   0
#define HUB_C_HUB_OVER_CURRENT  1
#define HUB_PORT_CONNECTION     0
#define HUB_PORT_ENABLE         1
#define HUB_PORT_SUSPEND        2
#define HUB_PORT_OVER_CURRENT   3
#define HUB_PORT_RESET          4
#define HUB_PORT_POWER          8
#define HUB_PORT_LOW_SPEED      9
#define HUB_C_PORT_CONNECTION   16
#define HUB_C_PORT_ENABLE       17
#define HUB_C_PORT_SUSPEND      18
#define HUB_C_PORT_OVER_CURRENT 19
#define HUB_C_PORT_RESET        20
#endif
/* USB descriptor type values */
#ifndef USB_DESCR_TYP_DEVICE
#define USB_DESCR_TYP_DEVICE    0x01
#define USB_DESCR_TYP_CONFIG    0x02
#define USB_DESCR_TYP_STRING    0x03
#define USB_DESCR_TYP_INTERF    0x04
#define USB_DESCR_TYP_ENDP      0x05
#define USB_DESCR_TYP_QUALIF    0x06
#define USB_DESCR_TYP_SPEED     0x07
#define USB_DESCR_TYP_OTG       0x09
#define USB_DESCR_TYP_HID       0x21
#define USB_DESCR_TYP_REPORT    0x22
#define USB_DESCR_TYP_PHYSIC    0x23
#define USB_DESCR_TYP_CS_INTF   0x24
#define USB_DESCR_TYP_CS_ENDP   0x25
#define USB_DESCR_TYP_HUB       0x29
#endif
/* USB device class codes */
#ifndef USB_DEV_CLASS_HUB
#define USB_DEV_CLASS_RESERVED  0x00
#define USB_DEV_CLASS_AUDIO     0x01
#define USB_DEV_CLASS_COMMUNIC  0x02
#define USB_DEV_CLASS_HID       0x03
#define USB_DEV_CLASS_MONITOR   0x04
#define USB_DEV_CLASS_PHYSIC_IF 0x05
#define USB_DEV_CLASS_POWER     0x06
#define USB_DEV_CLASS_PRINTER   0x07
#define USB_DEV_CLASS_STORAGE   0x08
#define USB_DEV_CLASS_HUB       0x09
#define USB_DEV_CLASS_VEN_SPEC  0xFF
#endif
/* USB endpoint type and attribute masks */
#ifndef USB_ENDP_TYPE_MASK
#define USB_ENDP_DIR_MASK       0x80
#define USB_ENDP_ADDR_MASK      0x0F
#define USB_ENDP_TYPE_MASK      0x03
#define USB_ENDP_TYPE_CTRL      0x00
#define USB_ENDP_TYPE_ISOCH     0x01
#define USB_ENDP_TYPE_BULK      0x02
#define USB_ENDP_TYPE_INTER     0x03
#endif
#ifndef USBSSsDEVICE_ADDR
#define USB_SSDEVICE_ADDR           0x02    /* Default Super?Speed device address */
#define USB_HSDEVICE_ADDR           0x0A    /* Default High?Speed device address */
#endif
#ifndef DEFAULT_ENDP0_SIZE
#define DEFAULT_ENDP0_SIZE      64      /* Default maximum packet size for endpoint 0 */
#endif
#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE         512     /* Maximum packet size */
#endif
#ifndef USB_BO_CBW_SIZE
#define USB_BO_CBW_SIZE         0x1F    /* Total length of CBW command block */
#define USB_BO_CSW_SIZE         0x0D    /* Total length of CSW command status block */
#endif
#ifndef USB_BO_CBW_SIG0
#define USB_BO_CBW_SIG0         0x55    /* CBW signature byte 'U' */
#define USB_BO_CBW_SIG1         0x53    /* CBW signature byte 'S' */
#define USB_BO_CBW_SIG2         0x42    /* CBW signature byte 'B' */
#define USB_BO_CBW_SIG3         0x43    /* CBW signature byte 'C' */
#define USB_BO_CSW_SIG0         0x55    /* CSW signature byte 'U' */
#define USB_BO_CSW_SIG1         0x53    /* CSW signature byte 'S' */
#define USB_BO_CSW_SIG2         0x42    /* CSW signature byte 'B' */
#define USB_BO_CSW_SIG3         0x53    /* CSW signature byte 'S' */
#endif
#ifndef __PACKED
#define __PACKED        __attribute__((packed))
#endif
#if 0                                       /* Used under special conditions */
typedef struct __PACKED _USB_CONFIG_DESCR {
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 wTotalLength;
    UINT8  bNumInterfaces;
    UINT8  bConfigurationValue;
    UINT8  iConfiguration;
    UINT8  bmAttributes;
    UINT8  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;
typedef struct __PACKED _USB_INTERF_DESCR {
    UINT8 bLength;
    UINT8 bDescriptorType;
    UINT8 bInterfaceNumber;
    UINT8 bAlternateSetting;
    UINT8 bNumEndpoints;
    UINT8 bInterfaceClass;
    UINT8 bInterfaceSubClass;
    UINT8 bInterfaceProtocol;
    UINT8 iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;
typedef struct __PACKED _USB_SETUP_REQ {
    UINT8  bRequestType;
    UINT8  bRequest;
    UINT16 wValue;
    UINT16 wIndex;
    UINT16 wLength;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;
#endif
#if 0
#ifndef USB_SETUP_REQ
typedef struct __PACKED _USB_SETUP_REQ {
    UINT8  bRequestType;
    UINT8  bRequest;
    UINT16 wValue;
    UINT16 wIndex;
    UINT16 wLength;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;
#endif
#ifndef USB_DEV_DESCR
typedef struct __PACKED _USB_DEVICE_DESCR {
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 bcdUSB;
    UINT8  bDeviceClass;
    UINT8  bDeviceSubClass;
    UINT8  bDeviceProtocol;
    UINT8  bMaxPacketSize0;
    UINT16 idVendor;
    UINT16 idProduct;
    UINT16 bcdDevice;
    UINT8  iManufacturer;
    UINT8  iProduct;
    UINT8  iSerialNumber;
    UINT8  bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;
#endif
#ifndef USB_CFG_DESCR
typedef struct __PACKED _USB_CONFIG_DESCR {
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 wTotalLength;
    UINT8  bNumInterfaces;
    UINT8  bConfigurationValue;
    UINT8  iConfiguration;
    UINT8  bmAttributes;
    UINT8  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;
#endif
#ifndef USB_ITF_DESCR
typedef struct __PACKED _USB_INTERF_DESCR {
    UINT8 bLength;
    UINT8 bDescriptorType;
    UINT8 bInterfaceNumber;
    UINT8 bAlternateSetting;
    UINT8 bNumEndpoints;
    UINT8 bInterfaceClass;
    UINT8 bInterfaceSubClass;
    UINT8 bInterfaceProtocol;
    UINT8 iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;
#endif
#ifndef USB_ENDP_DESCR
typedef struct __PACKED _USB_ENDPOINT_DESCR {
    UINT8 bLength;
    UINT8 bDescriptorType;
    UINT8 bEndpointAddress;
    UINT8 bmAttributes;
    UINT8 wMaxPacketSizeL;
    UINT8 wMaxPacketSizeH;
    UINT8 bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;
#endif
#ifndef USB_CFG_DESCR_LONG
typedef struct __PACKED _USB_CONFIG_DESCR_LONG {
    USB_CFG_DESCR   cfg_descr;
    USB_ITF_DESCR   itf_descr;
    USB_ENDP_DESCR  endp_descr[2];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;
#endif
#endif
#ifndef USB_DEV_QUAL_DESCR
typedef struct __PACKED _USB_DEVICE_QUALIFIER_DESCRIPTOR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT8  bcdUSBL;
    UINT8  bcdUSBH;
    UINT8  bDeviceClass;
    UINT8  bDeviceSubClass;
    UINT8  bDeviceProtocol;
    UINT8  bMaxPacketSize0;
    UINT8  bNumConfigurations;
    UINT8  bReserved;
}USB_DEV_QUAL_DESCR, *PUSB_DEV_QUAL_DESCR;
#endif
#ifndef USB_CFG_PWR_DESCR
typedef struct __PACKED _USB_CONFIGURATION_POWER_DESCRIPTOR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT8  SelfPowerConsumedD0[3];
    UINT8  bPowerSummaryId;
    UINT8  bBusPowerSavingD1;
    UINT8  bSelfPowerSavingD1;
    UINT8  bBusPowerSavingD2;
    UINT8  bSelfPowerSavingD2;
    UINT8  bBusPowerSavingD3;
    UINT8  bSelfPowerSavingD3;
    UINT8  TransitionTimeFromD1L;
    UINT8  TransitionTimeFromD1H;
    UINT8  TransitionTimeFromD2L;
    UINT8  TransitionTimeFromD2H;
    UINT8  TransitionTimeFromD3L;
    UINT8  TransitionTimeFromD3H;
}USB_CFG_PWR_DESCR, *PUSB_CFG_PWR_DESCR;
#endif
#ifndef USB_ITF_PWR_DESCR
typedef struct __PACKED _USB_INTERFACE_POWER_DESCRIPTOR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT8  bmCapabilitiesFlags;
    UINT8  bBusPowerSavingD1;
    UINT8  bSelfPowerSavingD1;
    UINT8  bBusPowerSavingD2;
    UINT8  bSelfPowerSavingD2;
    UINT8  bBusPowerSavingD3;
    UINT8  bSelfPowerSavingD3;
    UINT8  TransitionTimeFromD1L;
    UINT8  TransitionTimeFromD1H;
    UINT8  TransitionTimeFromD2L;
    UINT8  TransitionTimeFromD2H;
    UINT8  TransitionTimeFromD3L;
    UINT8  TransitionTimeFromD3H;
}USB_ITF_PWR_DESCR, *PUSB_ITF_PWR_DESCR;
#endif
// #define USB_BO_CBW_SIG              0x43425355                  /* CBW signature magic value 'USBC' */
// #define USB_BO_CSW_SIG              0x53425355                  /* CSW signature magic value 'USBS' */
// typedef struct __PACKED _UDISK_BOC_CBW{
//     UINT32 mCBW_Sig;
//     UINT32 mCBW_Tag;
//     UINT32 mCBW_DataLen;                                            /* Data transfer length */
//     UINT8  mCBW_Flag;                                               /* Transfer direction and control flags */
//     UINT8  mCBW_LUN;
//     UINT8  mCBW_CB_Len;                                             /* Command block length, valid range 1 ~ 16 */
//     UINT8  mCBW_CB_Buf[16];                                         /* Command block buffer, max 16 bytes */
// } UDISK_BOC_CBW, *PUDISK_BOC_CBW;
// typedef struct __PACKED _UDISK_BOC_CSW{
//     UINT32 mCSW_Sig;
//     UINT32 mCSW_Tag;
//     UINT32 mCSW_Residue;                                            /* Remaining un?transferred data length */
//     UINT8  mCSW_Status;                                             /* Command execution result status code */
// } UDISK_BOC_CSW, *PUDISK_BOC_CSW;
#ifndef U30USB_ENDP_DESCR
typedef struct _USB_ENDPOINT_DESCRIPTOR_U30                            /* USB3.0 endpoint descriptor */
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT8  bEndpointAddress;
    UINT8  bmAttributes;
    UINT8  wMaxPacketSizeL;
    UINT8  wMaxPacketSizeH;
    UINT8  bInterval;
    UINT8  bLength1;                                                   /* USB3.0 companion descriptor length */
    UINT8  bDescriptorType1;
    UINT8  bMaxBurst1;
    UINT8  bmAttributes1;
    UINT8  wBytesPerInterval_L;
    UINT8  wBytesPerInterval_H;
}USB_ENDP_DESCR_U30, *PUSB_ENDP_DESCR_U30;
#endif
#ifndef USB_CFG_DESCR_LONG_U30
typedef struct _USB_CONFIG_DESCRIPTOR_LONG_U30
{
    USB_CFG_DESCR  cfg_descr;
    USB_ITF_DESCR  itf_descr;
    USB_ENDP_DESCR_U30 endp_descr[2];
}USB_CFG_DESCR_LONG_U30, *PUSB_CFG_DESCR_LONG_U30;
#endif
/* USB device class codes (duplicate definition for reference) */
#ifndef USB_DEV_CLASS_HUB
#define USB_DEV_CLASS_RESERVED          0x00
#define USB_DEV_CLASS_AUDIO             0x01
#define USB_DEV_CLASS_COMMUNIC          0x02
#define USB_DEV_CLASS_HUMAN_IF          0x03
#define USB_DEV_CLASS_MONITOR           0x04
#define USB_DEV_CLASS_PHYSIC_IF         0x05
#define USB_DEV_CLASS_POWER             0x06
#define USB_DEV_CLASS_PRINTER           0x07
#define USB_DEV_CLASS_STORAGE           0x08
#define USB_DEV_CLASS_HUB               0x09
#define USB_DEV_CLASS_VEN_SPEC          0xFF
#endif
/* USB descriptor type identifiers */
#ifndef USB_DEV_DESCR_TYPE
#define USB_DEV_DESCR_TYPE              0x01
#define USB_CFG_DESCR_TYPE              0x02
#define USB_STR_DESCR_TYPE              0x03
#define USB_ITF_DESCR_TYPE              0x04
#define USB_ENDP_DESCR_TYPE             0x05
#define USB_PWR_DESCR_TYPE              0x06
#define USB_DEV_QUAL_DESCR_TYPE         0x06
#define USB_CFG_PWR_DESCR_TYPE          0x07
#define USB_ITF_PWR_DESCR_TYPE          0x08
#define USB_HID_DESCR_TYPE              0x21
#define USB_REPORT_DESCR_TYPE           0x22
#define USB_PHYSIC_DESCR_TYPE           0x23
#endif
#define USB_U30_SPEED                   0x02
#define USB_U20_SPEED                   0x01
extern UINT8   gDeviceUsbType;                                          /* USB connection type:01?USB2.0/1.1,02?USB3.0 */
#define Usb_Tx_DMAaddr  0x20030000
#define pUsb_Tx_DMAaddr ( ( PUINT8 )0x20030000 )
#define Usb_Rx_DMAaddr  0x20030400
#define pUsb_Rx_DMAaddr ( ( PUINT8 )0x20030400 )
extern void mDelaymS( UINT16 ms );
/* Pointer definition for USB host control transfer SETUP packet structure */
extern USB_SETUP_REQ   *Ctl_Setup;
extern volatile UINT8   gDeviceConnectstatus;                           /* USB device connection state flag */
extern void  CH56X_USB30_LmpInit( void );
extern UINT8 U30HOST_SetConfig( UINT8 cfg );
extern uint8_t U30HSOT_Enumerate( uint8_t *pbuf,uint8_t addr,uint8_t port );
extern UINT8 U30HOST_SetAddress( UINT8 addr );
extern UINT8 U30HOST_ClearEndpStall( UINT8 endp );
extern uint8_t U30HOST_CofDescrAnalyse( uint8_t *pbuf ,uint8_t port);
extern UINT8 U30OST_GetDeviceDescr( UINT8 *buf ,UINT16 *len );
extern UINT8 U30HOST_GetConfigDescr( UINT8 *buf ,UINT16 *len );
extern UINT8 U30HostCtrlTransfer( PUINT8 ReqBuf, PUINT8 DatBuf, PUINT16 RetLen ) ; // Execute control transfer, ReqBuf points to 8?byte setup packet, DatBuf is I/O buffer
extern UINT8 U20OST_GetDeviceDescr( UINT8 *buf ,UINT16 *len );
extern UINT8 U20HOST_GetConfigDescr( UINT8 *buf ,UINT16 *len );
extern UINT8 U20HOST_SetAddress( UINT8 addr );
extern UINT8 U20HOST_SetConfig( UINT8 cfg );
extern UINT8 U20HOST_ClearEndpStall( UINT8 endp );
extern UINT8 U20HostCtrlTransfer(UINT8 *ReqBuf, UINT8 *pbuf, UINT8 *plen );
extern uint8_t U30HSOT_Enumerate( uint8_t *pbuf,uint8_t addr,uint8_t port );
extern uint8_t USBHSH_Transact( uint8_t endp_pid_number, uint16_t endp_tog, uint32_t timeout );
extern uint8_t U20HSOT_Enumerate( uint8_t *pbuf,uint8_t addr,uint8_t port );
extern void USBHSH_CheckRootHubPortStatus( void );
extern uint8_t U30HSOT_Enumerate_Hotrst( uint8_t *pbuf );
extern UINT8 udisk_vidpid_buf[ 4 ] ;                                    /* Buffer for USB device VID and PID values */
extern void H417_RSaveVariable( uint8_t port );
extern void H417_SaveVariable( uint8_t port );
extern uint8_t  gDiskMaxLun;                                            /* Maximum logical unit number of mass?storage device */
extern uint8_t  gDiskCurLun;                                            /* Currently selected logical unit for operation */
extern UINT32 gDiskCapability;                                          /* Total storage capacity of the USB disk */
extern UINT32 gDiskPerSecSize;                                          /* Sector byte size of the USB disk */
extern uint8_t  gDiskBulkInEp;                                          /* IN endpoint address of mass?storage device */
extern uint8_t  gDiskBulkInTog;                                         /* DATA toggle bit for bulk?IN transfers */
extern uint8_t  gDiskBulkInBrust;                                       /* Burst count for bulk?IN operations */
extern uint8_t  gDiskBulkOutEp;                                         /* OUT endpoint address of mass?storage device */
extern uint8_t  gDiskBulkOutTog;                                        /* DATA toggle bit for bulk?OUT transfers */
extern uint8_t  gDiskBulkOutBrust;                                      /* Burst count for bulk?OUT operations */
extern uint16_t gDiskBulkInEpSize;                                      /* Max packet size of bulk?IN endpoint */
extern uint16_t gDiskBulkOutEpSize;                                     /* Max packet size of bulk?OUT endpoint */
extern uint8_t  gDiskInterfNumber;                                      /* Interface index of mass?storage device */
#ifdef __cplusplus
}
#endif

#endif
