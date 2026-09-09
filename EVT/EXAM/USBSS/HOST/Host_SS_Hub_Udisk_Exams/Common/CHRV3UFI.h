/* 2014.09.09
*****************************************
**   Copyright  (C)  W.ch  1999-2019   **
**   Web:      http://wch.cn           **
*****************************************
**  USB?flash File Interface for CHRV3 **
**  KEIL423, gcc 8.20                  **
*****************************************
*/
/* CHRV3 U?disk host file?system interface, support: FAT12/FAT16/FAT32 */
//#include "CHRV3BAS.H"
#ifndef __CHRV3UFI_H__
#define __CHRV3UFI_H__
#define CHRV3_LIB_VER       0x10
//#define DISK_BASE_BUF_LEN     512 /* Default disk data buffer size is 512 bytes (can be set to 2048 or even 4096 for U?disks with large sectors). Set to 0 to skip buffer definition here and assign buffer address via pDISK_BASE_BUF in application */
/* To conserve RAM by reusing the disk data buffer, define DISK_BASE_BUF_LEN as 0 to avoid buffer allocation in this header file. Assign the shared buffer start address to pDISK_BASE_BUF before calling CHRV3LibInit */
//#define NO_DEFAULT_ACCESS_SECTOR      1       /* Disable default disk sector read/write routine, replace it with custom implementation below */
//#define NO_DEFAULT_DISK_CONNECT       1       /* Disable default disk connection detection routine, replace it with custom implementation below */
//#define NO_DEFAULT_FILE_ENUMER        1       /* Disable default filename enumeration callback routine, replace it with custom implementation below */
#define FOR_ROOT_UDISK_ONLY             1
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
#define ERR_CHRV3_ERROR         0x81    /* CHRV3 hardware error, CHRV3 reset may be required */
//#define ERR_DISK_DISCON           0x82    /* Disk not connected, device may have been unplugged */
#define ERR_STATUS_ERR          0x83    /* Disk status error, device is being attached or detached */
#define ERR_HUB_PORT_FREE       0x84    /* USB?HUB is connected but no disk on target port, disk may have been disconnected */
#define ERR_MBR_ERROR           0x91    /* Invalid master boot record on disk, disk may be unpartitioned or unformatted */
#define ERR_TYPE_ERROR          0x92    /* Unsupported partition type, only FAT12/FAT16/BigDOS/FAT32 are supported. Repartition with disk management tool */
#define ERR_BPB_ERROR           0xA1    /* Disk unformatted or invalid BPB parameters, re?format with default Windows parameters */
#define ERR_TOO_LARGE           0xA2    /* Abnormal formatted disk larger than 4GB or 250GB, re?format with default Windows parameters */
#define ERR_FAT_ERROR           0xA3    /* Unsupported file system, only FAT12/FAT16/FAT32 are supported, re?format with default Windows parameters */
#define ERR_DISK_FULL           0xB1    /* Disk full, insufficient free space, perform disk cleanup */
#define ERR_FDT_OVER            0xB2    /* Too many entries inside directory, no free directory items. Root directory of FAT12/FAT16 supports less than 500 files, perform disk cleanup */
#define ERR_MISS_DIR            0xB3    /* Subdirectory on specified path not found, directory name may be incorrect */
#define ERR_FILE_CLOSE          0xB4    /* File already closed, reopen the file for further operations */
#define ERR_OPEN_DIR            0x41    /* Directory on specified path is opened */
#define ERR_MISS_FILE           0x42    /* File on specified path not found, filename may be incorrect */
#define ERR_FOUND_NAME          0x43    /* Wildcard?matched filename found, full path stored in command buffer, open the file to access content */
#endif
/* Code range 0x20?0x2F: USB host communication failure codes, CHRV3 emulates CH375 return values */
/* Code range 0x10?0x1F: USB host operation status codes, CHRV3 emulates CH375 return values */
#ifndef ERR_USB_CONNECT
#define ERR_USB_CONNECT_LS      0x13    /* Low?speed USB device attach event detected */
#define ERR_USB_CONNECT         0x15    /* USB device attach event detected, disk connected */
#define ERR_USB_DISCON          0x16    /* USB device detach event detected, disk disconnected */
#define ERR_USB_BUF_OVER        0x17    /* USB transfer corrupted or data overflowed the receive buffer */
#define ERR_USB_DISK_ERR        0x1F    /* USB mass?storage operation failed. Initialization failure indicates unsupported device; read/write failure indicates damaged or disconnected disk */
#define ERR_USB_TRANSFER        0x20    /* NAK / STALL and other additional error codes occupy 0x20~0x2F */
#endif
/* Disk and file status definitions */
#define DISK_UNKNOWN            0x00    /* Uninitialized, unknown state */
#define DISK_DISCONNECT         0x01    /* Disk not attached or already disconnected */
#define DISK_CONNECT            0x02    /* Physical device attached, uninitialized or unrecognizable file system */
#define DISK_USB_ADDR           0x04    /* USB address assigned, USB configuration and disk initialization pending */
#define DISK_MOUNTED            0x05    /* Disk initialized successfully, file?system parsing incomplete or unsupported */
#define DISK_READY              0x10    /* File?system parsed and supported for access */
#define DISK_OPEN_ROOT          0x12    /* Root directory opened in sector mode, directory content read/write in sector units only. Close after use; FAT12/FAT16 root directory has fixed size */
#define DISK_OPEN_DIR           0x13    /* Subdirectory opened in sector mode, directory content read/write in sector units only */
#define DISK_OPEN_FILE          0x14    /* File opened in sector mode, data access in sector units */
#define DISK_OPEN_FILE_B        0x15    /* File opened in byte mode, random byte?oriented read/write access */
/* FAT file?system type flags */
#ifndef DISK_FAT16
#define DISK_FS_UNKNOWN         0       /* Unknown file system */
#define DISK_FAT12              1       /* FAT12 file system */
#define DISK_FAT16              2       /* FAT16 file system */
#define DISK_FAT32              3       /* FAT32 file system */
#endif
/* File directory entry inside FAT data region */
typedef struct _FAT_DIR_INFO {
    uint8_t DIR_Name[11];               /* Offset 00H, 11?byte short filename, padded with space characters */
    uint8_t DIR_Attr;                   /* Offset 0BH, file attribute, refer to definitions below */
    uint8_t DIR_NTRes;                  /* Offset 0CH */
    uint8_t DIR_CrtTimeTenth;           /* Offset 0DH, file creation timestamp, precision of 0.1 second */
    uint16_t    DIR_CrtTime;            /* Offset 0EH, file creation time */
    uint16_t    DIR_CrtDate;            /* Offset 10H, file creation date */
    uint16_t    DIR_LstAccDate;         /* Offset 12H, last access date */
    uint16_t    DIR_FstClusHI;          /* Offset 14H */
    uint16_t    DIR_WrtTime;            /* Offset 16H, file modification time, use macro MAKE_FILE_TIME */
    uint16_t    DIR_WrtDate;            /* Offset 18H, file modification date, use macro MAKE_FILE_DATE */
    uint16_t    DIR_FstClusLO;          /* Offset 1AH */
    uint32_t    DIR_FileSize;           /* Offset 1CH, file byte size */
} FAT_DIR_INFO;                         /* Total size: 0x20 bytes */
typedef FAT_DIR_INFO *PX_FAT_DIR_INFO;
/* File attribute bits */
#define ATTR_READ_ONLY          0x01    /* Read?only file flag */
#define ATTR_HIDDEN             0x02    /* Hidden file flag */
#define ATTR_SYSTEM             0x04    /* System file flag */
#define ATTR_VOLUME_ID          0x08    /* Volume label entry */
#define ATTR_DIRECTORY          0x10    /* Subdirectory entry */
#define ATTR_ARCHIVE            0x20    /* Archive file flag */
#define ATTR_LONG_NAME          ( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )
/* File attribute byte layout (uint8_t) */
/* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
/* RO  HID SYS VOL DIR ARR RESERVED        */
/* File time encoding (uint16_t) */
/* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )   ( (h<<11) + (m<<5) + (s>>1) )   /* Encode hour/minute/second into FAT time value */
/* File date encoding (uint16_t) */
/* Date = ((Year?1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	/* Encode year/month/day into FAT date value */
/* Filename and path constants */
#define PATH_WILDCARD_CHAR      0x2A        /* Wildcard character '*' for path matching */
#define PATH_SEPAR_CHAR1        0x5C        /* Backslash path separator '\' */
#define PATH_SEPAR_CHAR2        0x2F        /* Slash path separator '/' */
#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN            64          /* Maximum path length including separators, dots and null terminator (00H) */
#endif
/* External command parameter union */
typedef union _CMD_PARAM
{
    struct
    {
        uint8_t mBuffer[ MAX_PATH_LEN ];
    } Other;
    struct
    {
        uint32_t mTotalSector;              /* Return value: total logical sectors of current partition */
        uint32_t mFreeSector;               /* Return value: remaining free logical sectors */
        uint32_t mSaveValue;
    } Query;                                /* CMD_DiskQuery, retrieve disk capacity information */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input parameter: full path string [drive, colon, separator, directory/filename.ext..., null terminator]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
    } Open;                                 /* CMD_FileOpen, open specified file */
//  struct
//  {
//      uint8_t mPathName[ MAX_PATH_LEN ];  /* Input parameter: path string with wildcard characters [drive, colon, separator, filename pattern..., null terminator]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILE*",00H */
//  } Open;                                 /* CMD_FileOpen, enumerate files. Set MSB of CHRV3vFileSize to invoke xFileNameEnumer callback; clear MSB to return filename at specified index */
    struct
    {
        uint8_t mUpdateLen;                 /* Input parameter: enable file?size modification: 0 = disable, 1 = enable */
    } Close;                                /* CMD_FileClose, close currently opened file */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input parameter: full path string [drive, colon, separator, directory/filename.ext..., null terminator]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
    } Create;                               /* CMD_FileCreate, create and open file; delete existing file before creation */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input parameter: full path string [drive, colon, separator, directory/filename.ext..., null terminator]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
    } Erase;                                /* CMD_FileErase, delete and close target file */
    struct
    {
        uint32_t mFileSize;                 /* Input parameter: new target file size; 0xFFFFFFFF keeps original value. Return value: previous file size */
        uint16_t mFileDate;                 /* Input parameter: new file date stamp; 0xFFFF keeps original value. Return value: previous date stamp */
        uint16_t mFileTime;                 /* Input parameter: new file time stamp; 0xFFFF keeps original value. Return value: previous time stamp */
        uint8_t  mFileAttr;                 /* Input parameter: new file attribute flags; 0xFF keeps original value. Return value: previous attribute flags */
    } Modify;                               /* CMD_FileQuery, read current file metadata; CMD_FileModify, read or update file metadata */
    struct
    {
        uint32_t mSaveCurrClus;
        uint32_t mSaveLastClus;
    } Alloc;                                /* CMD_FileAlloc, allocate or release disk clusters to match target file size */
    struct
    {
        uint32_t mSectorOffset;             /* Input parameter: sector?based file pointer offset. Value 0 seeks to file start; 0xFFFFFFFF seeks to file end. Return value: absolute linear LBA address of new file pointer; 0xFFFFFFFF indicates end?of?file */
        uint32_t mLastOffset;
    } Locate;                               /* CMD_FileLocate, reposition file pointer in sector granularity */
    struct
    {
        uint8_t mSectorCount;               /* Input parameter: requested read sector count. Return value: actual sectors successfully read */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mRemainCnt;
        uint8_t *mDataBuffer;               /* Input parameter: destination buffer start address. Return value: updated buffer pointer after transfer */
        uint32_t mLbaStart;
    } Read;                                 /* CMD_FileRead, read data starting from current file pointer */
    struct
    {
        uint8_t mSectorCount;               /* Input parameter: requested write sector count. Return value: actual sectors successfully written */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mAllocCnt;
        uint8_t *mDataBuffer;               /* Input parameter: source data buffer start address. Return value: updated buffer pointer after transfer */
        uint32_t mLbaStart;
        uint32_t mSaveValue;
    } Write;                                /* CMD_FileWrite, write data starting from current file pointer */
    struct
    {
        uint32_t mDiskSizeSec;              /* Return value: total physical disk sectors, valid only on the first call */
    } DiskReady;                            /* CMD_DiskReady, check disk readiness status */
    struct
    {
        uint32_t mByteOffset;               /* Input parameter: byte?based seek offset for file pointer. Return value: absolute linear LBA address of new file pointer; 0xFFFFFFFF indicates end?of?file */
        uint32_t mLastOffset;
    } ByteLocate;                           /* CMD_ByteLocate, reposition file pointer in byte granularity */
    struct
    {
        uint16_t mByteCount;                /* Input parameter: requested read byte count. Return value: actual bytes successfully read */
        uint8_t *mByteBuffer;               /* Input parameter: destination buffer for received data block */
        uint16_t mActCnt;
    } ByteRead;                             /* CMD_ByteRead, read byte?oriented data block from current file pointer */
    struct
    {
        uint16_t mByteCount;                /* Input parameter: requested write byte count. Return value: actual bytes successfully written */
        uint8_t *mByteBuffer;               /* Input parameter: source buffer containing data block to transmit */
        uint16_t mActCnt;
    } ByteWrite;                            /* CMD_ByteWrite, write byte?oriented data block at current file pointer */
    struct
    {
        uint8_t mSaveVariable;              /* Input parameter: set to 0 to restore single?disk context; set to 0x80 to restore multi?disk context; other values trigger backup / save operation */
        uint8_t mReserved[3];
        uint8_t *mBuffer;                   /* Input parameter: backup buffer for library state variables, minimum length 80 bytes */
    } SaveVariable;                         /* CMD_SaveVariable, backup / save / restore library runtime context for multi?device switching */
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
#define DISK_BASE_BUF_LEN       512         /* Default disk data buffer size is 512 bytes. 2048 or 4096 recommended for large?sector U?disks. Set to 0 to skip buffer definition here and assign buffer address via pDISK_BASE_BUF in application */
#endif
/* Global runtime variables exported by library */
extern  volatile uint8_t CHRV3IntStatus;    /* Interrupt status code for last CHRV3 operation */
extern  volatile uint8_t CHRV3DiskStatus;   /* Overall disk and file?system state flag */
extern  uint8_t  CHRV3vDiskFat;             /* Partition FAT type flag:1=FAT12,2=FAT16,3=FAT32 */
extern  uint8_t  CHRV3vSecPerClus;          /* Sectors per cluster for current logical partition */
extern  uint8_t  CHRV3vSectorSizeB;         /* Log2 value of physical sector size */
extern  uint32_t CHRV3vStartLba;            /* Starting absolute LBA address of current logical partition */
extern  uint32_t CHRV3vDiskRoot;            /* FAT16: root?directory sector count; FAT32: root?directory starting cluster number */
extern  uint32_t CHRV3vDataStart;           /* Starting LBA address of partition data region */
extern  uint32_t CHRV3vStartCluster;        /* Starting cluster index of currently opened file or directory */
extern  uint32_t CHRV3vFileSize;            /* Byte length of currently opened file */
extern  uint32_t CHRV3vCurrentOffset;       /* Byte offset of active file read/write pointer */
extern  uint32_t CHRV3vFdtLba;              /* LBA address of the current directory entry sector */
extern  uint32_t CHRV3vLbaCurrent;          /* Starting disk LBA for ongoing read/write operation */
extern  uint16_t CHRV3vFdtOffset;           /* Byte offset of directory entry inside its sector */
extern  uint16_t CHRV3vSectorSize;          /* Physical disk sector byte size */
extern  uint8_t  CHRV3vCurrentLun;          /* Logical unit number selected for disk operations */
extern  uint8_t  CHRV3vSubClassIs6;         /* Flag set when USB mass?storage subclass code equals 6 */
extern  uint8_t  *pDISK_BASE_BUF;           /* Pointer to external RAM disk data buffer, buffer size >= CHRV3vSectorSize, initialized by application */
extern  uint8_t  *pDISK_FAT_BUF;            /* Pointer to external RAM FAT table buffer, buffer size >= CHRV3vSectorSize, initialized by application */
extern  uint16_t CHRV3vPacketSize;          /* Max USB bulk packet length:64 for Full?Speed,512 for High?Speed / Super?Speed, assigned by application after device enumeration */
extern  uint32_t *pTX_DMA_A_REG;            /* Pointer to transmit DMA address register, initialized by application */
extern  uint32_t *pRX_DMA_A_REG;            /* Pointer to receive DMA address register, initialized by application */
extern  uint16_t *pTX_LEN_REG;              /* Pointer to transmit length register, initialized by application */
extern  uint16_t *pRX_LEN_REG;              /* Pointer to receive length register, initialized by application */
extern  CMD_PARAM_I mCmdParam;              /* Global command parameter union */
extern  __attribute__ ((aligned(4)))   uint8_t  RxBuffer[ ];  // IN transfer buffer, must be even?aligned address
extern  __attribute__ ((aligned(4)))   uint8_t  TxBuffer[ ];  // OUT transfer buffer, must be even?aligned address
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
extern  uint8_t DISK_BASE_BUF[ DISK_BASE_BUF_LEN ]; /* Disk data buffer allocated in external RAM, buffer length equals one physical sector */
#endif
extern  uint8_t CHRV3ReadSector( uint8_t SectCount, uint8_t * DataBuf );    /* Read multiple consecutive disk sectors into target buffer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3WriteSector( uint8_t SectCount, uint8_t * DataBuf );   /* Write multiple consecutive sectors from source buffer to physical disk */
#endif
extern  uint8_t CHRV3DiskConnect( void );   /* Detect disk hot?plug state and update CHRV3DiskStatus */
extern  void    xFileNameEnumer( void );    /* External callback function triggered during file enumeration */
extern  uint8_t CHRV3LibInit( void );       /* Initialize CHRV3 runtime library, returns 0 on successful initialization */
/* Library exported API functions */
/* File?operation APIs (CHRV3File*) and disk query API (CHRV3DiskQuery) will occupy pDISK_BASE_BUF for temporary file?system metadata.
Avoid overwriting pDISK_BASE_BUF with unrelated data during file access.
If RAM is constrained and temporary reuse of pDISK_BASE_BUF is required, call CHRV3DirtyBuffer to invalidate cached disk data after external usage */
extern  uint8_t CHRV3GetVer( void );        /* Return runtime library version code */
extern  void    CHRV3DirtyBuffer( void );   /* Invalidate and clear cached disk buffer content */
extern  uint8_t CHRV3BulkOnlyCmd( uint8_t * DataBuf );  /* Execute USB Mass?Storage Bulk?Only protocol transaction */
extern  uint8_t CHRV3DiskReady( void );                 /* Verify that the disk is ready for I/O operations */
extern  uint8_t CHRV3AnalyzeError( uint8_t iMode );     /* Parse USB transfer failure and update CHRV3IntStatus with resolved error code */
extern  uint8_t CHRV3FileOpen( void );      /* Open a target file or trigger directory file enumeration */
extern  uint8_t CHRV3FileClose( void );     /* Close the currently opened file handle */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileErase( void );     /* Delete and close the specified file */
extern  uint8_t CHRV3FileCreate( void );    /* Create a new empty file and open the handle; overwrite existing file */
extern  uint8_t CHRV3FileAlloc( void );     /* Adjust allocated FAT clusters to match the target file size */
#endif
extern  uint8_t CHRV3FileModify( void );    /* Read or update metadata properties of the currently opened file */
extern  uint8_t CHRV3FileQuery( void );     /* Read metadata properties of the currently opened file */
extern  uint8_t CHRV3FileLocate( void );    /* Reposition the sector?aligned file read/write pointer */
extern  uint8_t CHRV3FileRead( void );      /* Read sector?aligned data block starting at current file pointer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileWrite( void );     /* Write sector?aligned data block starting at current file pointer */
#endif
extern  uint8_t CHRV3ByteLocate( void );    /* Reposition the byte?granularity file read/write pointer */
extern  uint8_t CHRV3ByteRead( void );      /* Read arbitrary byte?length data block starting at current file pointer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3ByteWrite( void );     /* Write arbitrary byte?length data block starting at current file pointer */
#endif
extern  uint8_t CHRV3DiskQuery( void );     /* Query partition capacity and remaining free sectors */
extern  void    CHRV3SaveVariable( void );  /* Backup / save / restore library runtime context for switching between multiple USB devices */
extern  void    mDelayuS( uint16_t n );     // Microsecond delay function
extern  void    mDelaymS( uint16_t n );     // Millisecond delay function
extern  uint8_t USBHostTransact( uint8_t endp_pid, uint8_t tog, uint32_t timeout );     // CHRV3 USB host transaction handler. Input: endpoint address / token PID, data toggle flag, NAK retry timeout. Return 0 for success, retry on timeout or transfer error
extern  uint8_t HostCtrlTransfer( uint8_t * DataBuf, uint8_t * RetLen );                // Execute USB control transfer. 8?byte setup packet stored in pSetupReq, DataBuf is optional IN/OUT data buffer, actual transfer length written to RetLen
extern  void    CopySetupReqPkg( const char * pReqPkt );                                // Copy pre?defined control?transfer setup packet
extern  uint8_t CtrlGetDeviceDescrTB( void );       // Retrieve USB device descriptor, result stored inside TxBuffer
extern  uint8_t CtrlGetConfigDescrTB( void );       // Retrieve USB configuration descriptor, result stored inside TxBuffer
extern  uint8_t CtrlSetUsbAddress( uint8_t addr );  // Assign new USB device address
extern  uint8_t CtrlSetUsbConfig( uint8_t cfg );    // Activate target USB configuration index
extern  uint8_t CtrlClearEndpStall( uint8_t endp ); // Clear endpoint STALL handshake status
#ifndef FOR_ROOT_UDISK_ONLY
//extern    uint8_t CtrlGetHubDescr( void );  // Retrieve USB?HUB descriptor, result stored inside TxBuffer
extern  uint8_t HubGetPortStatus( uint8_t HubPortIndex );  // Query USB?HUB port status register, result stored inside TxBuffer
//extern    uint8_t HubSetPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Set specified USB?HUB port feature
extern  uint8_t HubClearPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Clear specified USB?HUB port feature
#endif
#ifdef __cplusplus
}

#endif

#endif
