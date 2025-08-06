/********************************** (C) COPYRIGHT *******************************
* File Name          : nand_flash.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2025/05/24
* Description        : This file contains the headers of the NANDFLASH.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include"NAND_Flash.h"
#include "string.h"

nand_attriute nand_dev;
u32 WriteEccData[4];
u32 ReadEccData[4];
/*********************************************************************
 * @fn      NAND_Init
 *
 * @brief   Init NANDFLASH
 *
 * @return  none
 */
u8 NAND_Init(void)
{
    FMC_NANDInitTypeDef  FMC_NANDInitStructure={0};
    FMC_NAND_PCCARDTimingInitTypeDef  ComSpaceTiming={0};
    FMC_NAND_PCCARDTimingInitTypeDef  AttSpaceTiming={0};
    GPIO_InitTypeDef  GPIO_InitStructure={0};

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOD | RCC_HB2Periph_GPIOE| RCC_HB2Periph_GPIOF|RCC_HB2Periph_AFIO,ENABLE);
    RCC_HBPeriphClockCmd(RCC_HBPeriph_FMC,ENABLE);

    /*FMC_NWAIT PD6 R/B */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF12);

    /* FMC_NADV */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF12);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF12);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF12);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF12);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF12);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF12);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource3,GPIO_AF12);


    ComSpaceTiming.FMC_SetupTime=2;
    ComSpaceTiming.FMC_WaitSetupTime=3;
    ComSpaceTiming.FMC_HoldSetupTime=2;
    ComSpaceTiming.FMC_HiZSetupTime=1;

    AttSpaceTiming.FMC_SetupTime=2;
    AttSpaceTiming.FMC_WaitSetupTime=3;
    AttSpaceTiming.FMC_HoldSetupTime=2;
    AttSpaceTiming.FMC_HiZSetupTime=1;

    FMC_NANDInitStructure.FMC_Bank = FMC_Bank3_NAND;
    FMC_NANDInitStructure.FMC_Waitfeature = FMC_Waitfeature_Disable;
    FMC_NANDInitStructure.FMC_MemoryDataWidth = FMC_MemoryDataWidth_8b;
    FMC_NANDInitStructure.FMC_ECC = FMC_ECC_Enable;
    FMC_NANDInitStructure.FMC_ECCPageSize = FMC_ECCPageSize_512Bytes;
    FMC_NANDInitStructure.FMC_TCLRSetupTime = 3;
    FMC_NANDInitStructure.FMC_TARSetupTime = 4;
    FMC_NANDInitStructure.FMC_CommonSpaceTimingStruct = &ComSpaceTiming;
    FMC_NANDInitStructure.FMC_AttributeSpaceTimingStruct = &AttSpaceTiming;
    FMC_NANDInit(&FMC_NANDInitStructure);

    FMC_NANDCmd(FMC_Bank3_NAND, ENABLE);

    NAND_Reset();
    Delay_Ms(100);
    nand_dev.id=NAND_ReadID();

    printf("id:%08x\n", nand_dev.id);

    if(nand_dev.id==W29N01HV){
        nand_dev.page_totalsize=2112;
        nand_dev.page_mainsize=2048;
        nand_dev.page_sparesize=64;
        nand_dev.block_pagenum=64;
        nand_dev.plane_blocknum=1024;
        nand_dev.block_totalnum=1024;

    }
    else return 1;

    return 0;
}

/*********************************************************************
 * @fn      NAND_ReadID
 *
 * @brief   Read NANDFLASH ID
 *
 * @return  id - NANDFLASH ID
 */
u32 NAND_ReadID(void)
{
    u8 deviceid[5];
    u32 id;
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_READID;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=0X00;

    /* First 5 bytes: 0xEF ,0xF1, 0x00 ,0x95, 0x00 */
    deviceid[0]=*(vu8*)NAND_ADDRESS;
    deviceid[1]=*(vu8*)NAND_ADDRESS;
    deviceid[2]=*(vu8*)NAND_ADDRESS;
    deviceid[3]=*(vu8*)NAND_ADDRESS;
    deviceid[4]=*(vu8*)NAND_ADDRESS;
    id=((u32)deviceid[1])<<24|((u32)deviceid[2])<<16|((u32)deviceid[3])<<8|deviceid[4];
    return id;
}

/*********************************************************************
 * @fn      NAND_ReadStatus
 *
 * @brief   Read NANDFLASH status
 *
 * @return  data -
 *            bit - 0-Pass 1-Fail
 *            bit6 - 0-Busy 1-Ready
 *            bit7 - 0-Protected 1-Not Protected
 */
u8 NAND_ReadStatus(void)
{
    vu8 data=0;
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_READSTA;
    data++;data++;data++;data++;data++;
    data=*(vu8*)NAND_ADDRESS;
    return data;
}

/**********************************************************************
* @fn      FMC_NAND_GetStatus
* @brief   Get the NAND operation status
* 
* @return  New status of the NAND operation. This parameter can be:
*          - NAND_TIMEOUT_ERROR: when the previous operation generate
*          a Timeout error
*          - NAND_READY: when memory is ready for the next operation
*/
u32 FMC_NAND_GetStatus(void)
{
  u32 timeout = 0x1000000, status = NSTA_READY;

  status = NAND_ReadStatus();

  /* Wait for a NAND operation to complete or a TIMEOUT to occur */
  while ((status != NSTA_READY) &&( timeout != 0x00))
  {
     status = NAND_ReadStatus();
     timeout --;
  }

  if(timeout == 0x00)
  {
    status =  NSTA_TIMEOUT;
  }

  /* Return the operation status */
  return (status);
}

/*********************************************************************
 * @fn      NAND_WaitForReady
 *
 * @brief   Wait NANDFLASH ready
 *
 * @return  NSTA_READY - OK
 *          NSTA_TIMEOUT - timeout
 */
u8 NAND_WaitForReady(void)
{
    u8 status=0;
    vu32 time=0;
    while(1)
    {
        status=NAND_ReadStatus();
        if(status&NSTA_READY)break;
        time++;
        if(time>=0X1FFFF)return NSTA_TIMEOUT;
    }
    return NSTA_READY;
}

/*********************************************************************
 * @fn      NAND_Reset
 *
 * @brief   Reset NANDFLASH
 *
 * @return  0 - success
 *          1 - ERR
 */
u8 NAND_Reset(void)
{
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_RESET;
    if(NAND_WaitForReady()==NSTA_READY)return 0;
    else return 1;
}

/*********************************************************************
 * @fn      NAND_WaitRB
 *
 * @brief   Wait RB signal valid
 *
 * @param   rb -
 *            0- Low level active
 *            1- High level active
 *
 * @return  0 - success
 *          1 - ERR
 */
u8 NAND_WaitRB(vu8 rb)
{
    vu16 time=0;
    while(time<10000)
    {
        time++;
        GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_6);
    }
    return 1;
}

/*********************************************************************
 * @fn      NAND_Delay
 *
 * @brief   Delay function
 *
 * @param   i - delay time
 *
 * @return  none
 */
void NAND_Delay(vu32 i)
{
    while(i>0)i--;
}

/*********************************************************************
 * @fn      NAND_ReadPage
 *
 * @brief   Read the data of the specified page and column of NAND flash
 *
 * @param   PageNum - page number
 *          ColNum - column number
 *          pBuffer - data
 *          NumByteToRead - data number
 *
 * @return  0 - success
 *          1 - ERR
 */
u8 NAND_ReadPage(u32 PageNum,u16 ColNum,u8 *pBuffer,u16 NumByteToRead)
{
    vu16 i=0;
    u8 errsta=0;
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_A;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)ColNum;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(ColNum>>8);
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);

    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_TRUE1;
    Delay_Ms(10);
    FMC_NANDECCCmd(FMC_Bank3_NAND, DISABLE);
    for(i=0; i<NumByteToRead; i++)
    {
        *(vu8*)pBuffer++ = *(vu8*)NAND_ADDRESS;
    }
    while(FMC_GetFlagStatus( FMC_FLAG_FEMPT)==RESET);
    if(NAND_WaitForReady()!=NSTA_READY)errsta=NSTA_ERROR;

    return errsta;
}

/*********************************************************************
 * @fn      NAND_ReadPageWithEcc
 *
 * @brief   Read the data of the specified page and column of NAND flash with ECC
 *
 * @param   PageNum - page number
 *          ColNum - column number
 *          pBuffer - data
 *          NumByteToRead - data number
 *
 * @return  0 - success
 *          1 - ERR
 */

u8 NAND_ReadPageWithEcc(u32 PageNum,u16 ColNum,u8 *pBuffer,u16 NumByteToRead)
{
    vu16 i=0,j=0;
    u8 n=0;
    u8 errsta=0;
    u32 Eccdata,data;
    u16 EccColNum=0;
    u8 SpareBuf[4];
    n=NumByteToRead/512;
    switch (ColNum)
    {
        case 0:
            EccColNum=2048;
            break;
        case 512:
            EccColNum=2064;
            break;
        case 1024:
            EccColNum=2080;
            break;
        case 1536:
            EccColNum=2096;
            break;
        default:
            break;
    }

    for(i=0;i<n;i++)
      {
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_A;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)ColNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(ColNum>>8);
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_TRUE1;
        FMC_NANDECCCmd(FMC_Bank3_NAND, DISABLE);
        Delay_Ms(10);
        FMC_NANDECCCmd(FMC_Bank3_NAND, ENABLE);
        for(j=0; j<512; j++)
        {
            *(vu8*)pBuffer++ = *(vu8*)NAND_ADDRESS;
        }
        while(FMC_GetFlagStatus( FMC_FLAG_FEMPT)==RESET);
        ReadEccData[i]=FMC_GetECC(FMC_Bank3_NAND);
        FMC_NANDECCCmd(FMC_Bank3_NAND, DISABLE);
        if(NAND_WaitForReady()!=NSTA_READY)errsta=NSTA_ERROR;
        ColNum+=512;
      }


    for(int k=0;k<n;k++)
    {
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_A;
           *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)EccColNum;
           *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(EccColNum>>8);
           *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
           *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);
           *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_AREA_TRUE1;
           Delay_Ms(10);
           for (int p= 0;  p < 4; p++)
           {
               SpareBuf[p] = *(vu8*)(NAND_ADDRESS+2*i);

        }
           Eccdata=SpareBuf[0]+(SpareBuf[1]<<8)+(SpareBuf[2]<<16)+(SpareBuf[3]<<24);
           data=Eccdata^ReadEccData[k];
           if(data==0)
           {
               printf("no errors-%d\r\n",k);
           }
           else
           {
               CheckEcc(data);
           }
           while(FMC_GetFlagStatus( FMC_FLAG_FEMPT)==RESET);
           if(NAND_WaitForReady()!=NSTA_READY)errsta=NSTA_ERROR;
           EccColNum+=16;
    }
    return errsta;
}

/*********************************************************************
 * @fn      NAND_WritePage
 *
 * @brief   Write the data of the specified page and column of NAND flash
 *
 * @param   PageNum - page number
 *          ColNum - column number
 *          pBuffer - data
 *          NumByteToRead - data number
 *
 * @return  0 - success
 *          1 - ERR
 */

u8 NAND_WritePage(u32 PageNum,u16 ColNum,u8 *pBuffer,u16 NumByteToWrite)
{
    int j=0;
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE0;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)ColNum;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(ColNum>>8);
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);

    NAND_Delay(30);
    FMC_NANDECCCmd(FMC_Bank3_NAND, DISABLE);

    for(j=0;j<NumByteToWrite;j++)
    {
        *(vu8*)NAND_ADDRESS=*(vu8*)pBuffer++;
    }
    while(FMC_GetFlagStatus( FMC_FLAG_FEMPT)==RESET);

    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE_TURE1;
    if(NAND_WaitForReady()!=NSTA_READY)return NSTA_ERROR;

    return 0;
}

/*********************************************************************
 * @fn      NAND_WritePagewithEcc
 *
 * @brief   Write the data of the specified page and column of NAND flash with ECC
 *
 * @param   PageNum - page number
 *          ColNum - column number
 *          pBuffer - data
 *          NumByteToRead - data number
 *
 * @return  0 - success
 *          1 - ERR
 */

u8 NAND_WritePagewithEcc(u32 PageNum,u16 ColNum,u8 *pBuffer,u16 NumByteToWrite)
{
    int i=0,j=0;
    u8 buf[16];
    u8 n=0;
    u16 EccColNum=0;
    n=NumByteToWrite/512;
    switch (ColNum) {
        case 0:
            EccColNum=2048;
            break;
        case 512:
            EccColNum=2064;
            break;
        case 1024:
            EccColNum=2080;
            break;
        case 1536:
            EccColNum=2096;
            break;
        default:
            break;
    }
// save data
    for(i=0;i<n;i++)
    {
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE0;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)ColNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(ColNum>>8);
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);
        NAND_Delay(30);
        FMC_NANDECCCmd(FMC_Bank3_NAND, ENABLE);
        for(j=0;j<512;j++)
        {
            *(vu8*)NAND_ADDRESS=*(vu8*)pBuffer++;
        }
        while(FMC_GetFlagStatus(FMC_FLAG_FEMPT)==RESET);
        WriteEccData[i]=FMC_GetECC(FMC_Bank3_NAND);
        FMC_NANDECCCmd(FMC_Bank3_NAND, DISABLE);

        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE_TURE1;
        if(NAND_WaitForReady()!=NSTA_READY)return NSTA_ERROR;
        ColNum+=512;
    }

// write Ecc data
    for(int k=0;k<n;k++)
    {
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE0;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)EccColNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(EccColNum>>8);
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)PageNum;
        *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(PageNum>>8);
        NAND_Delay(30);
        buf[0]=WriteEccData[k]&0xFF;
        buf[1]=(WriteEccData[k]>>8)&0xFF;
        buf[2]=(WriteEccData[k]>>16)&0xFF;
        buf[3]=(WriteEccData[k]>>24)&0xFF;
        for(int p=0;p<4;p++)
        {
            *(vu8*)(NAND_ADDRESS+2*i)=buf[p];
        }
        while(FMC_GetFlagStatus( FMC_FLAG_FEMPT)==RESET);
        *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_WRITE_TURE1;
        if(NAND_WaitForReady()!=NSTA_READY)return NSTA_ERROR;
        EccColNum+=16;
    }
    return 0;
}

/*********************************************************************
 * @fn      NAND_EraseBlock
 *
 * @brief   Erase NANDFLASH block
 *
 * @param   BlockNum - Block Number
 *
 * @return  none
 */
u8  NAND_EraseBlock(u32 BlockNum)
{
    if(nand_dev.id==W29N01HV)BlockNum<<=6;

    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_ERASE0;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)BlockNum;
    *(vu8*)(NAND_ADDRESS|NAND_ADDR)=(u8)(BlockNum>>8);
    *(vu8*)(NAND_ADDRESS|NAND_CMD)=NAND_ERASE1;
    if(NAND_WaitForReady()!=NSTA_READY)return NSTA_ERROR;

    return 0;
}

/*********************************************************************
 * @fn      CheckEcc
 *
 * @brief   Check ECC result
 *
 * @param   data - ECC XOR calculation results for reading and writing
 *
 * @return  error location
 */

u32 CheckEcc( u32  data)
{
  u32 temp;
  int i;
  u8 eccdata;
  u32 location=0;
  for(int p=0;p<4;p++)
  {
      temp=data&0xffffff;
      for(i=0;i<24/2;i++)
      {
          eccdata=(temp>>(i*2))&0x3;
          if(eccdata==0x01)
          {
              //01
              }
          else if(eccdata==0x02)
          {
              // 10
              location|=(1<<i);
          }
          else {
              return 0;
          }
          printf("Error location: %d\r\n",location);
      }
  }
  return location;
}








