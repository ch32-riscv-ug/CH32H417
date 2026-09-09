/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32h417_udisk.h
* Author             : WCH
* Version            : V1.0
* Date               : 2025/05/30
* Description        : This file contains all the functions prototypes for the
*                      ch32h417_udisk.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __CH32H417_UDSIK_H_
#define __CH32H417_UDSIK_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
//#ifdef BIG_ENDIAN
//#define USB_BO_CBW_SIG              0x55534243                                    /* CBW signature identifier 'USBC' */
//#define USB_BO_CSW_SIG              0x55534253                                    /* CSW signature identifier 'USBS' */
//#else
#define USB_BO_CBW_SIG              0x43425355                                      /* CBW signature identifier 'USBC' */
#define USB_BO_CSW_SIG              0x53425355                                      /* CSW signature identifier 'USBS' */
//#endif
#define USB_BO_CBW_SIZE             0x1F                                            /* Total length of command block CBW */
#define USB_BO_CSW_SIZE             0x0D                                            /* Total length of command status block CSW */
#define USB_BO_DATA_IN              0x80
#define USB_BO_DATA_OUT             0x00
typedef union _BULK_ONLY_CMD
{
    struct
    {
        UINT32 mCBW_Sig;
        UINT32 mCBW_Tag;
        UINT32 mCBW_DataLen;                                                        /* Input: data transfer length */
        UINT8  mCBW_Flag;                                                           /* Input: flags such as transfer direction */
        UINT8  mCBW_LUN;
        UINT8  mCBW_CB_Len;                                                         /* Input: length of command block, valid value ranges from 1 to 16 */
        UINT8  mCBW_CB_Buf[16];                                                     /* Input: command block, the buffer is up to 16 bytes */
    } mCBW;                                                                         /* BulkOnly protocol command block, input CBW structure */
    struct
    {
        UINT32 mCSW_Sig;
        UINT32 mCSW_Tag;
        UINT32 mCSW_Residue;                                                        /* Return: remaining data length */
        UINT8  mCSW_Status;                                                         /* Return: command execution status result */
    } mCSW;                                                                         /* BulkOnly protocol command status block, output CSW structure */
} BULK_ONLY_CMD;
/******************************************************************************/
/* External variable declaration */
extern UINT8  gDiskMaxLun;                                                          /* Maximum logical unit number of the disk */
extern UINT8  gDiskCurLun;                                                          /* Current operated logical unit number of the disk */
extern UINT32 gDiskCapability;                                                      /* Total disk capacity */
extern UINT32 gDiskPerSecSize;                                                      /* Disk sector size */
extern UINT8  gDiskBulkInEp;                                                        /* IN endpoint address of USB mass storage device */
extern UINT8  gDiskBulkOutEp;                                                       /* OUT endpoint address of USB mass storage device */
extern UINT16 gDiskBulkInEpSize;                                                    /* Maximum packet size of IN endpoint for USB mass storage device */
extern UINT16 gDiskBulkOutEpSize;                                                   /* Maximum packet size of OUT endpoint for USB mass storage device */
extern UINT8  gDiskInterfNumber;                                                    /* Interface number of USB mass storage device */
extern BULK_ONLY_CMD    mBOC;                                                       /* BulkOnly transmission structure */
#define DEFAULT_MAX_OPERATE_SIZE        8192                                        /* Default maximum operation packet size */
#define     MAX_DATA_ADDR   0x20030000
extern uint8_t U30HOST_MS_CofDescrAnalyse( uint8_t *pbuf,uint8_t port );
extern UINT8 MS_Init(  UINT8 *pbuf );
extern UINT8 MS_ReadSector( UINT32 StartLba, UINT16 SectCount, PUINT8 DataBuf );
extern UINT8 MS_WriteSector( UINT32 StartLba, UINT8 SectCount, PUINT8 DataBuf );
extern UINT8 CHRV3BulkOnlyCmd( UINT8 *DataBuf );
extern UINT8 U20HOST_Issue_BulkOut( UINT8 *pDatBuf, UINT32 *pSize );
extern UINT8 U20HOST_Issue_BulkIn( UINT8 *pDatBuf, UINT32 *pSize );
extern uint8_t U20HOST_MS_CofDescrAnalyse( uint8_t *pbuf ,uint8_t port);
extern UINT8V U30_TIME_OUT;
extern UINT8 tx_lmp_port;
extern UINT8 Hot_Reset( UINT8 *pdata );
extern UINT8V Hot_ret_flag;
extern UINT8 *pNTFS_BUF;
extern UINT8 gUdisk_flag;
extern UINT8 gUdisk_flag1;
extern UINT16 gUdisk_delay;
extern uint8_t U30HOST_Issue_Bulk( uint8_t EndpNum, uint8_t *SeqNum, uint8_t PacketNum, uint8_t *pDatBuf, UINT32 *pSize, uint8_t Type, uint8_t BrustNum );
#ifdef __cplusplus
}
#endif
#endif
