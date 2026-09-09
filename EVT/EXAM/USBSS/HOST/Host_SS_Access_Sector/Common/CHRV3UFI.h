/* 2026.09.09
*****************************************
**   Copyright  (C)  W.ch  1999-2019   **
**   Web:        https://wch.cn         **
*****************************************
**  USB?flash File Interface for CHRV3 **
**  KEIL423, gcc 8.20                   **
*****************************************
*/
/* CHRV3 USB?Host file?system interface for U?disk, support: FAT12/FAT16/FAT32 */
//#include "CHRV3BAS.H"
#ifndef __CHRV3UFI_H__
#define __CHRV3UFI_H__
#define CHRV3_LIB_VER       0x10
//#define DISK_BASE_BUF_LEN     512 /* Default disk data buffer size is 512 bytes (can be set to 2048 or even 4096 to support U?disks with large sectors). Set to 0 to disable buffer definition in this file and specify the buffer address via pDISK_BASE_BUF in application */
/* If you want to reuse the disk data buffer to save RAM, define DISK_BASE_BUF_LEN as 0 to skip buffer definition here, then assign the shared buffer start address to variable pDISK_BASE_BUF before calling CHRV3LibInit */
//#define NO_DEFAULT_ACCESS_SECTOR      1       /* Disable default disk sector read/write routine, replace it with self?implemented code below */
//#define NO_DEFAULT_DISK_CONNECT       1       /* Disable default disk connection check routine, replace it with self?implemented code below */
//#define NO_DEFAULT_FILE_ENUMER        1       /* Disable default file name enumeration callback, replace it with self?implemented code below */
#define FOR_ROOT_UDISK_ONLY           1
#ifdef __cplusplus
extern "C" {
#endif
/* ********************************************************************************************************************* */
/* FILE: CHRV3UF.H */
/* Error codes */
#ifndef ERR_SUCCESS
// #define ERR_SUCCESS              0x00    /* Operation succeeded */
#endif
#ifndef ERR_DISK_DISCON
#define ERR_CHRV3_ERROR         0x81    /* CHRV3 hardware error, CHRV3 may need a reset */
//#define ERR_DISK_DISCON           0x82    /* Disk not connected, device may have been unplugged */
#define ERR_STATUS_ERR          0x83    /* Disk status abnormal, device is being attached or detached */
#define ERR_HUB_PORT_FREE       0x84    /* USB?HUB is connected but no disk on the port, disk may have been removed */
#define ERR_MBR_ERROR           0x91    /* Invalid master boot record, disk is unpartitioned or unformatted */
#define ERR_TYPE_ERROR          0x92    /* Unsupported partition type, only FAT12/FAT16/BigDOS/FAT32 are supported, re?partition with disk management tool */
#define ERR_BPB_ERROR           0xA1    /* Disk unformatted or invalid BPB parameters, re?format with Windows default settings */
#define ERR_TOO_LARGE           0xA2    /* Abnormal formatted disk larger than 4GB or over 250GB, re?format with Windows default settings */
#define ERR_FAT_ERROR           0xA3    /* Unsupported file system, only FAT12/FAT16/FAT32 are supported, re?format with Windows default settings */
#define ERR_DISK_FULL           0xB1    /* Disk full, insufficient free space, defragmentation required */
#define ERR_FDT_OVER            0xB2    /* Too many entries inside directory, no free directory items. Root directory of FAT12/FAT16 is limited to less than 500 files, defragmentation required */
#define ERR_MISS_DIR            0xB3    /* Sub?directory in given path not found, possible directory name mistake */
#define ERR_FILE_CLOSE          0xB4    /* File already closed, reopen the file for further operations */
#define ERR_OPEN_DIR            0x41    /* Target path is an opened directory */
#define ERR_MISS_FILE           0x42    /* Specified file not found, possible filename mistake */
#define ERR_FOUND_NAME          0x43    /* Wildcard matched filename found, full path stored in command buffer, open the file to use it */
#endif
/* Code range 0x20?0x2F: USB host communication failure codes, CHRV3 emulates CH375 return values */
/* Code range 0x10?0x1F: USB host operation status codes, CHRV3 emulates CH375 return values */
#ifndef ERR_USB_CONNECT
#define ERR_USB_CONNECT_LS      0x13    /* Low?speed USB device attach event detected */
#define ERR_USB_CONNECT         0x15    /* USB device attach event detected, disk connected */
#define ERR_USB_DISCON          0x16    /* USB device detach event detected, disk disconnected */
#define ERR_USB_BUF_OVER        0x17    /* USB transfer error or buffer overflow caused by oversized payload */
#define ERR_USB_DISK_ERR        0x1F    /* USB mass?storage operation failed. During initialization the device may be unsupported; during read/write the disk may be damaged or unplugged */
#define ERR_USB_TRANSFER        0x20    /* NAK / STALL and other detailed error codes range from 0x20 ~ 0x2F */
#endif
/* Disk & file state definitions */
#define DISK_UNKNOWN            0x00    /* Not initialized, unknown state */
#define DISK_DISCONNECT         0x01    /* Disk not present or already disconnected */
#define DISK_CONNECT            0x02    /* Physical device attached, not initialized or unrecognizable file system */
#define DISK_USB_ADDR           0x04    /* USB address assigned, USB configuration and disk initialization pending */
#define DISK_MOUNTED            0x05    /* Disk initialized successfully, file?system analysis pending or unsupported */
#define DISK_READY              0x10    /* File?system parsed and supported */
#define DISK_OPEN_ROOT          0x12    /* Root directory opened in sector mode, directory content can only be accessed sector?wise. Must be closed after use. FAT12/FAT16 root directory has fixed size */
#define DISK_OPEN_DIR           0x13    /* Sub?directory opened in sector mode, directory content can only be accessed sector?wise */
#define DISK_OPEN_FILE          0x14    /* File opened in sector mode, read/write in sector units */
#define DISK_OPEN_FILE_B        0x15    /* File opened in byte mode, read/write in byte units */
/* FAT file?system type flags */
#ifndef DISK_FAT16
#define DISK_FS_UNKNOWN         0       /* Unknown file system */
#define DISK_FAT12              1       /* FAT12 file system */
#define DISK_FAT16              2       /* FAT16 file system */
#define DISK_FAT32              3       /* FAT32 file system */
#endif
/* File directory entry structure in FAT data region */
typedef struct _FAT_DIR_INFO {
    uint8_t DIR_Name[11];               /* 00H, short filename (11 bytes), padded with space characters */
    uint8_t DIR_Attr;                   /* 0BH, file attribute, refer to definitions below */
    uint8_t DIR_NTRes;                  /* 0CH */
    uint8_t DIR_CrtTimeTenth;           /* 0DH, file creation time, unit: 0.1 second */
    uint16_t    DIR_CrtTime;            /* 0EH, file creation time */
    uint16_t    DIR_CrtDate;            /* 10H, file creation date */
    uint16_t    DIR_LstAccDate;         /* 12H, last access date */
    uint16_t    DIR_FstClusHI;          /* 14H */
    uint16_t    DIR_WrtTime;            /* 16H, file modification time, refer to macro MAKE_FILE_TIME */
    uint16_t    DIR_WrtDate;            /* 18H, file modification date, refer to macro MAKE_FILE_DATE */
    uint16_t    DIR_FstClusLO;          /* 1AH */
    uint32_t    DIR_FileSize;           /* 1CH, file size in bytes */
} FAT_DIR_INFO;                         /* Total size: 0x20 bytes */
typedef FAT_DIR_INFO *PX_FAT_DIR_INFO;
/* File attribute bits */
#define ATTR_READ_ONLY          0x01    /* Read?only file */
#define ATTR_HIDDEN             0x02    /* Hidden file */
#define ATTR_SYSTEM             0x04    /* System file */
#define ATTR_VOLUME_ID          0x08    /* Volume label entry */
#define ATTR_DIRECTORY          0x10    /* Sub?directory entry */
#define ATTR_ARCHIVE            0x20    /* Archive file flag */
#define ATTR_LONG_NAME          ( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )
/* File attribute bitmap (uint8_t) */
/* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
/* RO   HID  SYS  VOL  DIR  ARCH Reserved */
/* File time encoding (uint16_t) */
/* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )   ( (h<<11) + (m<<5) + (s>>1) )   /* Encode hour/minute/second into FAT time value */
/* File date encoding (uint16_t) */
/* Date = ((Year?1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	/* Encode year/month/day into FAT date value */
/* Path and filename constants */
#define PATH_WILDCARD_CHAR      0x2A        /* Wildcard character '*' for filename search */
#define PATH_SEPAR_CHAR1        0x5C        /* Path separator backslash '\' */
#define PATH_SEPAR_CHAR2        0x2F        /* Path separator slash '/' */
#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN            64          /* Maximum path length including separators, dots and null terminator 0x00 */
#endif
/* Union for external command parameters */
typedef union _CMD_PARAM
{
    struct
    {
        uint8_t mBuffer[ MAX_PATH_LEN ];
    } Other;
    struct
    {
        uint32_t mTotalSector;              /* Return value: total sector count of current logical drive */
        uint32_t mFreeSector;               /* Return value: free sector count of current logical drive */
        uint32_t mSaveValue;
    } Query;                                /* CMD_DiskQuery, query disk information */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input: full path string [drive, colon, separator, directory/filename..., null?terminated]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",0x00 */
    } Open;                                 /* CMD_FileOpen, open a specified file */
//  struct
//  {
//      uint8_t mPathName[ MAX_PATH_LEN ];  /* Input: path with wildcard [drive, colon, separator, filename with '*'..., null?terminated]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILE*",0x00 */
//  } Open;                                 /* CMD_FileOpen, enumerate files. If highest bit of CHRV3vFileSize equals 1, callback xFileNameEnumer will be invoked; if 0, return filename with specified index */
    struct
    {
        uint8_t mUpdateLen;                 /* Input: enable file?size auto?update flag: 0?disable, 1?enable */
    } Close;                                /* CMD_FileClose, close current opened file */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input: full path string [drive, colon, separator, directory/filename..., null?terminated]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",0x00 */
    } Create;                               /* CMD_FileCreate, create and open file. If file already exists, erase it before creation */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input: full path string [drive, colon, separator, directory/filename..., null?terminated]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",0x00 */
    } Erase;                                /* CMD_FileErase, delete and close target file */
    struct
    {
        uint32_t mFileSize;                 /* Input: new target file size, set to 0xFFFFFFFF to skip modification; Return: original file size */
        uint16_t mFileDate;                 /* Input: new file date, set to 0xFFFF to skip modification; Return: original date */
        uint16_t mFileTime;                 /* Input: new file time, set to 0xFFFF to skip modification; Return: original time */
        uint8_t  mFileAttr;                 /* Input: new file attribute, set to 0xFF to skip modification; Return: original attribute */
    } Modify;                               /* CMD_FileQuery: read current file metadata; CMD_FileModify: read or update current file metadata */
    struct
    {
        uint32_t mSaveCurrClus;
        uint32_t mSaveLastClus;
    } Alloc;                                /* CMD_FileAlloc, adjust allocated disk clusters according to target file size */
    struct
    {
        uint32_t mSectorOffset;             /* Input: sector?based file pointer offset, 0 for file start, 0xFFFFFFFF for file end; Return: absolute LBA address of new pointer, 0xFFFFFFFF when reaching end?of?file */
        uint32_t mLastOffset;
    } Locate;                               /* CMD_FileLocate, reposition current file pointer in sector granularity */
    struct
    {
        uint8_t mSectorCount;               /* Input: requested read sector count; Return: actual sectors read */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mRemainCnt;
        uint8_t *mDataBuffer;               /* Input: starting address of data buffer; Return: current buffer pointer after operation */
        uint32_t mLbaStart;
    } Read;                                 /* CMD_FileRead, read data from current file position */
    struct
    {
        uint8_t mSectorCount;               /* Input: requested write sector count; Return: actual sectors written */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mAllocCnt;
        uint8_t *mDataBuffer;               /* Input: starting address of data buffer; Return: current buffer pointer after operation */
        uint32_t mLbaStart;
        uint32_t mSaveValue;
    } Write;                                /* CMD_FileWrite, write data to current file position */
    struct
    {
        uint32_t mDiskSizeSec;              /* Return: total physical disk sector count, valid only on the first call */
    } DiskReady;                            /* CMD_DiskReady, check disk ready status */
    struct
    {
        uint32_t mByteOffset;               /* Input: byte?based file pointer offset; Return: absolute LBA address of new pointer, 0xFFFFFFFF when reaching end?of?file */
        uint32_t mLastOffset;
    } ByteLocate;                           /* CMD_ByteLocate, reposition current file pointer in byte granularity */
    struct
    {
        uint16_t mByteCount;                /* Input: requested read byte count; Return: actual bytes read */
        uint8_t *mByteBuffer;               /* Input: destination buffer address for received data */
        uint16_t mActCnt;
    } ByteRead;                             /* CMD_ByteRead, read a byte?aligned data block from current file position */
    struct
    {
        uint16_t mByteCount;                /* Input: requested write byte count; Return: actual bytes written */
        uint8_t *mByteBuffer;               /* Input: source buffer address for transmit data */
        uint16_t mActCnt;
    } ByteWrite;                            /* CMD_ByteWrite, write a byte?aligned data block to current file position */
    struct
    {
        uint8_t mSaveVariable;              /* Input: control flag: 0 = restore single?disk variables, 0x80 = restore multi?disk variables, other values = save / backup variables */
        uint8_t mReserved[3];
        uint8_t *mBuffer;                   /* Input: backup buffer for library state variables, buffer length ¡Ý 80 bytes */
    } SaveVariable;                         /* CMD_SaveVariable, backup / save / restore library runtime variables for multi?device switching */
} CMD_PARAM;
typedef CMD_PARAM CMD_PARAM_I;
//typedef CMD_PARAM *P_CMD_PARAM;
/* SCSI command opcodes */
#ifndef SPC_CMD_INQUIRY
#define SPC_CMD_INQUIRY         0x12
#define SPC_CMD_READ_CAPACITY   0x25
#define SPC_CMD_READ10          0x28
#define SPC_CMD_WRITE10         0x2A
#define SPC_CMD_TEST_READY      0x00
#define SPC_CMD_REQUEST_SENSE   0x03
#define SPC_CMD_MODESENSE6      0x1A
#define SPC_CMD_MODESENSE10     0x5A
#define SPC_CMD_START_STOP      0x1B
#endif
/* FILE: CHRV3UFI.C */
#define EN_DISK_WRITE           1
#ifndef DISK_BASE_BUF_LEN
#define DISK_BASE_BUF_LEN       512         /* Default disk data buffer size is 512 bytes. Recommended 2048 or 4096 for large?sector U?disks. Set to 0 so the application assigns pDISK_BASE_BUF externally */
#endif
/* Global variables exported by library */
extern  volatile uint8_t CHRV3IntStatus;    /* Interrupt / operation status of CHRV3 functions */
extern  volatile uint8_t CHRV3DiskStatus;   /* Global disk and file state flag */
extern  uint8_t  CHRV3vDiskFat;             /* Logical drive FAT type flag:1=FAT12,2=FAT16,3=FAT32 */
extern  uint8_t  CHRV3vSecPerClus;          /* Sectors per cluster on current logical drive */
extern  uint8_t  CHRV3vSectorSizeB;         /* log2 value of physical sector size */
extern  uint32_t CHRV3vStartLba;            /* Starting absolute LBA of current logical partition */
extern  uint32_t CHRV3vDiskRoot;            /* For FAT16: root?directory sector count; For FAT32: starting cluster number of root directory */
extern  uint32_t CHRV3vDataStart;           /* Starting LBA address of drive data region */
extern  uint32_t CHRV3vStartCluster;        /* Starting cluster number of currently opened file or directory */
extern  uint32_t CHRV3vFileSize;            /* Byte?size of currently opened file */
extern  uint32_t CHRV3vCurrentOffset;       /* Current byte?offset file read/write pointer */
extern  uint32_t CHRV3vFdtLba;              /* LBA address of the current FAT directory entry sector */
extern  uint32_t CHRV3vLbaCurrent;          /* Starting LBA for the ongoing disk read/write operation */
extern  uint16_t CHRV3vFdtOffset;           /* Byte offset of directory entry within its sector */
extern  uint16_t CHRV3vSectorSize;          /* Physical disk sector byte?size */
extern  uint8_t  CHRV3vCurrentLun;          /* Current logical unit number for mass?storage operation */
extern  uint8_t  CHRV3vSubClassIs6;         /* Flag indicates USB?MSC subclass code equals 6 */
extern  uint8_t  *pDISK_BASE_BUF;           /* Pointer to disk data buffer in external RAM, buffer size ¡Ý CHRV3vSectorSize, initialized by application */
extern  uint8_t  *pDISK_FAT_BUF;            /* Pointer to FAT table working buffer in external RAM, buffer size ¡Ý CHRV3vSectorSize, initialized by application */
extern  uint16_t CHRV3vPacketSize;          /* Max endpoint packet size for USB mass?storage device:64 for FS,512 for HS/SS, configured after device enumeration */
extern  uint32_t *pTX_DMA_A_REG;            /* Pointer to transmit DMA address register, assigned by application */
extern  uint32_t *pRX_DMA_A_REG;            /* Pointer to receive DMA address register, assigned by application */
extern  uint16_t *pTX_LEN_REG;              /* Pointer to transmit length register, assigned by application */
extern  uint16_t *pRX_LEN_REG;              /* Pointer to receive length register, assigned by application */
extern  CMD_PARAM_I mCmdParam;              /* Global command?parameter union */
extern  __attribute__ ((aligned(4)))   uint8_t  RxBuffer[ ];  // IN transfer buffer, must be even?address aligned
extern  __attribute__ ((aligned(4)))   uint8_t  TxBuffer[ ];  // OUT transfer buffer, must be even?address aligned
//#define       PXUDISK_BOC_CBW PUDISK_BOC_CBW
//#define       PXUDISK_BOC_CSW PUDISK_BOC_CSW
#ifndef pSetupReq
#define pSetupReq   ((PUSB_SETUP_REQ)TxBuffer)
#endif
#ifndef pCBW
#define pCBW        ((PXUDISK_BOC_CBW)TxBuffer)
#define pCSW        ((PXUDISK_BOC_CSW)RxBuffer)
#endif
#ifndef pBOC_buf
#define pBOC_buf    (TxBuffer+((USB_BO_CBW_SIZE+4)&0xFE))
#endif
#if     DISK_BASE_BUF_LEN > 0
extern  uint8_t DISK_BASE_BUF[ DISK_BASE_BUF_LEN ];                         /* Disk data buffer in external RAM, one sector long */
#endif
extern  uint8_t CHRV3ReadSector( uint8_t SectCount, uint8_t * DataBuf );    /* Read multiple consecutive sectors from disk into buffer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3WriteSector( uint8_t SectCount, uint8_t * DataBuf );   /* Write multiple consecutive sectors from buffer to disk */
#endif
extern  uint8_t CHRV3DiskConnect( void );   /* Detect disk hot?plug state and update global disk status */
extern  void    xFileNameEnumer( void );    /* User?defined callback for filename enumeration during directory scan */
extern  uint8_t CHRV3LibInit( void );       /* Initialize CHRV3 library, returns 0 on success */
/* Library API functions */
/* Note: File?operation APIs (CHRV3File*) and CHRV3DiskQuery use the shared pDISK_BASE_BUF working buffer which may contain cached disk metadata.
If RAM resources are limited and you need to reuse this buffer temporarily for other tasks, you must call CHRV3DirtyBuffer to invalidate cached content before reuse. */
extern  uint8_t CHRV3GetVer( void );        /* Get current library version code */
extern  void    CHRV3DirtyBuffer( void );   /* Mark disk buffer as dirty / invalidate cached sector data */
extern  uint8_t CHRV3BulkOnlyCmd( uint8_t * DataBuf );  /* Execute USB MSC Bulk?Only transport command */
extern  uint8_t CHRV3DiskReady( void );     /* Check whether the mounted disk is ready for I/O */
extern  uint8_t CHRV3AnalyzeError( uint8_t iMode ); /* Parse USB transaction failure and fill CHRV3IntStatus with error code */
extern  uint8_t CHRV3FileOpen( void );      /* Open a target file or trigger wildcard directory enumeration */
extern  uint8_t CHRV3FileClose( void );     /* Close the currently opened file handle */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileErase( void );     /* Delete target file and close its handle */
extern  uint8_t CHRV3FileCreate( void );    /* Create a new file and open it; overwrite existing file */
extern  uint8_t CHRV3FileAlloc( void );     /* Expand or shrink allocated FAT clusters to match target file size */
#endif
extern  uint8_t CHRV3FileModify( void );    /* Read or modify metadata of currently opened file */
extern  uint8_t CHRV3FileQuery( void );     /* Read metadata of currently opened file */
extern  uint8_t CHRV3FileLocate( void );    /* Reposition sector?granularity file pointer */
extern  uint8_t CHRV3FileRead( void );      /* Read sector?aligned data block from current file position */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileWrite( void );     /* Write sector?aligned data block to current file position */
#endif
extern  uint8_t CHRV3ByteLocate( void );    /* Reposition byte?granularity file pointer */
extern  uint8_t CHRV3ByteRead( void );      /* Read arbitrary byte?length data block from current file position */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3ByteWrite( void );     /* Write arbitrary byte?length data block to current file position */
#endif
extern  uint8_t CHRV3DiskQuery( void );     /* Query total and free space information of mounted logical drive */
extern  void    CHRV3SaveVariable( void );  /* Backup / restore runtime library state variables for multi?chip or multi?disk switching scenarios */
extern  void    mDelayuS( uint16_t n );     // Microsecond delay helper routine
extern  void    mDelaymS( uint16_t n );     // Millisecond delay helper routine
extern  uint8_t USBHostTransact( uint8_t endp_pid, uint8_t tog, uint32_t timeout ); // CHRV3 USB host transaction: token PID, toggle flag, NAK retry timeout. Return 0 on success, retry on timeout or error
extern  uint8_t HostCtrlTransfer( uint8_t * DataBuf, uint8_t * RetLen );    // Execute USB control transfer. 8?byte setup packet stored in pSetupReq; DataBuf is optional I/O buffer; actual transfer length written back to RetLen
extern  void    CopySetupReqPkg( const char * pReqPkt );                    // Copy custom setup request packet into TxBuffer
extern  uint8_t CtrlGetDeviceDescrTB( void );                               // Retrieve USB device descriptor into TxBuffer
extern  uint8_t CtrlGetConfigDescrTB( void );                               // Retrieve USB configuration descriptor into TxBuffer
extern  uint8_t CtrlSetUsbAddress( uint8_t addr );                          // Assign new USB device address
extern  uint8_t CtrlSetUsbConfig( uint8_t cfg );                            // Activate selected USB configuration
extern  uint8_t CtrlClearEndpStall( uint8_t endp );                         // Clear endpoint STALL handshake status
#ifndef FOR_ROOT_UDISK_ONLY
//extern    uint8_t CtrlGetHubDescr( void );  // Retrieve HUB descriptor into TxBuffer
extern  uint8_t HubGetPortStatus( uint8_t HubPortIndex );  // Query HUB port status, result stored in TxBuffer
//extern    uint8_t HubSetPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Set HUB port feature
extern  uint8_t HubClearPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Clear HUB port feature
#endif
#ifdef __cplusplus
}
#endif
#endif
