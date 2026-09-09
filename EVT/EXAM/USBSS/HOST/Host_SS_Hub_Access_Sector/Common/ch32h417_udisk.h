/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32h417_udisk.h
* Author             : WCH
* Version            : V1.0
* Date               : 2025/05/30
* Description        : This file contains all the functions prototypes for the
*                      ch32h417_udisk driver.
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
//#define USB_BO_CBW_SIG              0x55534243                                    /* Command Block Wrapper signature 'USBC' */
//#define USB_BO_CSW_SIG              0x55534253                                    /* Command Status Wrapper signature 'USBS' */
//#else
#define USB_BO_CBW_SIG              0x43425355                                    	/* Command Block Wrapper signature 'USBC' */
#define USB_BO_CSW_SIG              0x53425355                                    	/* Command Status Wrapper signature 'USBS' */
//#endif

#define USB_BO_CBW_SIZE             0x1F                                          	/* Total length of CBW (Command Block Wrapper) */
#define USB_BO_CSW_SIZE             0x0D                                          	/* Total length of CSW (Command Status Wrapper) */
#define USB_BO_DATA_IN              0x80
#define USB_BO_DATA_OUT             0x00

typedef union _BULK_ONLY_CMD
{
    struct
    {
        UINT32 mCBW_Sig;
        UINT32 mCBW_Tag;
        UINT32 mCBW_DataLen;                                                       /* Input: expected data transfer length */
        UINT8  mCBW_Flag;                                                          /* Input: transfer direction and control flags */
        UINT8  mCBW_LUN;
        UINT8  mCBW_CB_Len;                                                        /* Input: valid command block length, valid range 1 ~ 16 */
        UINT8  mCBW_CB_Buf[16];                                                    /* Input: SCSI command block buffer, max 16 bytes */
    } mCBW;                                                                        /* CBW structure for Bulk Only transport protocol */

    struct
    {
        UINT32 mCSW_Sig;
        UINT32 mCSW_Tag;
        UINT32 mCSW_Residue;                                                       /* Return: remaining untransferred data length */
        UINT8  mCSW_Status;                                                        /* Return: command execution status code */
    } mCSW;                                                                        /* CSW structure for Bulk Only transport protocol */

} BULK_ONLY_CMD;
/******************************************************************************/
/* External global variables */
extern UINT8  gDiskMaxLun;                                                        /* Maximum logical unit number of the disk */
extern UINT8  gDiskCurLun;                                                        /* Current logical unit number for operation */
extern UINT32 gDiskCapability;                                                    /* Total storage capacity of the disk */
extern UINT32 gDiskPerSecSize;                                                    /* Sector size of the storage device */
extern UINT8  gDiskBulkInEp;                                                      /* Bulk IN endpoint address of USB mass storage device */
extern UINT8  gDiskBulkOutEp;                                                     /* Bulk OUT endpoint address of USB mass storage device */
extern UINT16 gDiskBulkInEpSize;                                                  /* Maximum packet size of Bulk IN endpoint */
extern UINT16 gDiskBulkOutEpSize;                                                 /* Maximum packet size of Bulk OUT endpoint */
extern UINT8  gDiskInterfNumber;                                                  /* Interface number of USB mass storage device */
extern BULK_ONLY_CMD    mBOC;                                                     /* Bulk Only command transfer structure */

#define DEFAULT_MAX_OPERATE_SIZE        8192                                      /* Default maximum transfer size for a single operation */
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
