/* 2014.09.09
*****************************************
**   Copyright  (C)  W.ch  1999-2019   **
**   Web:       http://wch.cn          **
*****************************************
**  USB flash File Interface for CHRV3 **
**  KEIL423, gcc 8.20                  **
*****************************************
*/
/* CHRV3 Host file system interface for USB flash drive, support: FAT12/FAT16/FAT32 */
//#include "CHRV3BAS.H"
#ifndef __CHRV3UFI_H__
#define __CHRV3UFI_H__
#define CHRV3_LIB_VER        0x10
//#define DISK_BASE_BUF_LEN    512 /* Default disk sector buffer size 512 bytes (can be 2048/4096 for large sector USB drives). Set to 0 to disable internal buffer and assign pDISK_BASE_BUF from application */
/* To save RAM by sharing sector buffer with other modules, define DISK_BASE_BUF_LEN=0, assign shared buffer address to pDISK_BASE_BUF before calling CHRV3LibInit */
//#define NO_DEFAULT_ACCESS_SECTOR     1       /* Disable default sector read/write wrapper for custom low level implementation */
//#define NO_DEFAULT_DISK_CONNECT      1       /* Disable default plug in detection wrapper for custom implementation */
//#define NO_DEFAULT_FILE_ENUMER       1       /* Disable default filename enumeration callback for custom implementation */
#define FOR_ROOT_UDISK_ONLY          1
#ifdef __cplusplus
extern "C" {
#endif
/* ********************************************************************************************************************* */
/* FILE: CHRV3UF.H */
/* Status / Error Codes */
#ifndef ERR_SUCCESS
// #define ERR_SUCCESS              0x00    /* Operation completed successfully */
#endif
#ifndef ERR_DISK_DISCON
#define ERR_CHRV3_ERROR         0x81    /* CHRV3 hardware fault, CHRV3 reset may be required */
//#define ERR_DISK_DISCON           0x82    /* Media not present, device may have been unplugged */
#define ERR_STATUS_ERR          0x83    /* Disk state invalid, hot plug / unplug in progress */
#define ERR_HUB_PORT_FREE       0x84    /* USB HUB connected but no storage device on the target port */
#define ERR_MBR_ERROR           0x91    /* Invalid master boot record, drive unpartitioned or unformatted */
#define ERR_TYPE_ERROR          0x92    /* Unsupported partition type, only FAT12/FAT16/BigDOS/FAT32 are supported, re partition with disk tool */
#define ERR_BPB_ERROR           0xA1    /* Drive unformatted or BPB parameters corrupted, re format with Windows default settings */
#define ERR_TOO_LARGE           0xA2    /* Abnormal formatting with capacity >4GB or >250GB, re format with Windows default settings */
#define ERR_FAT_ERROR           0xA3    /* Unsupported filesystem, only FAT12/FAT16/FAT32 are supported, re format with Windows default settings */
#define ERR_DISK_FULL           0xB1    /* No free space remaining on volume, run disk cleanup */
#define ERR_FDT_OVER            0xB2    /* Directory entry overflow; root directory on FAT12/FAT16 limited to ~500 entries, run disk cleanup */
#define ERR_MISS_DIR            0xB3    /* Sub directory not found, verify directory name */
#define ERR_FILE_CLOSE          0xB4    /* File handle already closed, re open for further operations */
#define ERR_OPEN_DIR            0x41    /* Target path is an opened directory */
#define ERR_MISS_FILE           0x42    /* Specified file not found, verify filename */
#define ERR_FOUND_NAME          0x43    /* Wildcard match found, matched path stored in command buffer; open the file to proceed */
#endif
/* Code range 0x20 0x2F: USB host transfer failures emulated from CH375 */
/* Code range 0x10 0x1F: USB host operation status emulated from CH375 */
#ifndef ERR_USB_CONNECT
#define ERR_USB_CONNECT_LS      0x13    /* Low speed USB device attach event detected */
#define ERR_USB_CONNECT         0x15    /* USB device attach event detected, storage media connected */
#define ERR_USB_DISCON          0x16    /* USB device detach event detected, storage media removed */
#define ERR_USB_BUF_OVER        0x17    /* USB transfer corruption or buffer overflow */
#define ERR_USB_DISK_ERR        0x1F    /* Mass storage command failed; unsupported device, media damage or sudden removal */
#define ERR_USB_TRANSFER        0x20    /* NAK / STALL and other transfer errors occupy 0x20~0x2F */
#endif
/* Disk and file state definitions */
#define DISK_UNKNOWN            0x00    /* Uninitialized, unknown state */
#define DISK_DISCONNECT         0x01    /* Storage device absent or unplugged */
#define DISK_CONNECT            0x02    /* Device physically connected but not initialized or unrecognizable */
#define DISK_USB_ADDR           0x04    /* USB address assigned, pending configuration and media init */
#define DISK_MOUNTED            0x05    /* Media initialized, pending filesystem analysis or unsupported FS */
#define DISK_READY              0x10    /* Filesystem parsed and supported */
#define DISK_OPEN_ROOT          0x12    /* Root directory opened in sector mode; directory content accessed by sector, handle must be closed. FAT12/FAT16 root has fixed size */
#define DISK_OPEN_DIR           0x13    /* Sub directory opened in sector mode; directory content accessed by sector */
#define DISK_OPEN_FILE          0x14    /* File opened in sector mode, read/write aligned to sector boundaries */
#define DISK_OPEN_FILE_B        0x15    /* File opened in byte mode, arbitrary byte offset read/write supported */
/* FAT filesystem type flags */
#ifndef DISK_FAT16
#define DISK_FS_UNKNOWN         0       /* Undetermined filesystem */
#define DISK_FAT12              1       /* FAT12 filesystem */
#define DISK_FAT16              2       /* FAT16 filesystem */
#define DISK_FAT32              3       /* FAT32 filesystem */
#endif
/* FAT directory entry structure */
typedef struct _FAT_DIR_INFO {
    uint8_t DIR_Name[11];               /* 00H, 8.3 filename padded with space characters */
    uint8_t DIR_Attr;                   /* 0BH, file attribute bits defined below */
    uint8_t DIR_NTRes;                  /* 0CH, reserved NT flag */
    uint8_t DIR_CrtTimeTenth;           /* 0DH, file creation time fraction in 0.1 second units */
    uint16_t    DIR_CrtTime;            /* 0EH, file creation time stamp */
    uint16_t    DIR_CrtDate;            /* 10H, file creation date stamp */
    uint16_t    DIR_LstAccDate;         /* 12H, last access date stamp */
    uint16_t    DIR_FstClusHI;          /* 14H, high word of starting cluster number */
    uint16_t    DIR_WrtTime;            /* 16H, last modification time, use macro MAKE_FILE_TIME */
    uint16_t    DIR_WrtDate;            /* 18H, last modification date, use macro MAKE_FILE_DATE */
    uint16_t    DIR_FstClusLO;          /* 1AH, low word of starting cluster number */
    uint32_t    DIR_FileSize;           /* 1CH, file length in bytes */
} FAT_DIR_INFO;                         /* Entry occupies 32 bytes (0x20) */
typedef FAT_DIR_INFO *PX_FAT_DIR_INFO;
/* File attribute bitmask */
#define ATTR_READ_ONLY          0x01    /* Read only file */
#define ATTR_HIDDEN             0x02    /* Hidden entry */
#define ATTR_SYSTEM             0x04    /* System entry */
#define ATTR_VOLUME_ID          0x08    /* Volume label entry */
#define ATTR_DIRECTORY          0x10    /* Sub directory entry */
#define ATTR_ARCHIVE            0x20    /* Archive flag for modified files */
#define ATTR_LONG_NAME          ( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )
/* Attribute byte layout (uint8_t) */
/* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
/* RO   HID  SYS  VOL  DIR  ARC  Reserved */
/* Time encoding for directory entry (uint16_t) */
/* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )   ( (h<<11) + (m<<5) + (s>>1) )   /* Encode hour/minute/second into FAT time field */
/* Date encoding for directory entry (uint16_t) */
/* Date = ((Year-1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )   ( ((y-1980)<<9) + (m<<5) + d )  /* Encode year/month/day into FAT date field */
/* Path name constants */
#define PATH_WILDCARD_CHAR      0x2A    /* Wildcard character '*' */
#define PATH_SEPAR_CHAR1        0x5C    /* Path separator backslash '\' */
#define PATH_SEPAR_CHAR2        0x2F    /* Path separator forward slash '/' */
#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN            64      /* Maximum full path length including separators and null terminator */
#endif
/* Unified command parameter union */
typedef union _CMD_PARAM
{
    struct
    {
        uint8_t mBuffer[ MAX_PATH_LEN ];
    } Other;
    struct
    {
        uint32_t mTotalSector;          /* Output: total logical sectors of the volume */
        uint32_t mFreeSector;           /* Output: remaining free sectors on the volume */
        uint32_t mSaveValue;
    } Query;                            /* CMD_DiskQuery, volume information query */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input path string: [drive, colon, separator, dir/filename..., null terminator]. Drive letter and colon are optional, example: "C:\DIR1.EXT\DIR2\FILENAME.EXT",0x00 */
    } Open;                             /* CMD_FileOpen, open a specified file */
//  struct
//  {
//      uint8_t mPathName[ MAX_PATH_LEN ];  /* Input wildcard path string, null terminated. If CHRV3vFileSize MSB is set, xFileNameEnumer callback fires for each match; otherwise returns entry by index */
//  } Open;                             /* CMD_FileOpen, file enumeration mode */
    struct
    {
        uint8_t mUpdateLen;             /* Input: enable file size update on close: 0 = disable, 1 = enable */
    } Close;                            /* CMD_FileClose, close the currently opened file */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input path for new file, null terminated. Overwrite existing file if present */
    } Create;                           /* CMD_FileCreate, create and open file; delete existing file first */
    struct
    {
        uint8_t mPathName[ MAX_PATH_LEN ];  /* Input path of file to delete, null terminated */
    } Erase;                            /* CMD_FileErase, delete and close target file */
    struct
    {
        uint32_t mFileSize;             /* Input: new target file size, 0xFFFFFFFF = keep unchanged; Output: original size */
        uint16_t mFileDate;             /* Input: new modification date, 0xFFFF = keep unchanged; Output: original date */
        uint16_t mFileTime;             /* Input: new modification time, 0xFFFF = keep unchanged; Output: original time */
        uint8_t  mFileAttr;             /* Input: new attribute byte, 0xFF = keep unchanged; Output: original attributes */
    } Modify;                           /* CMD_FileQuery / CMD_FileModify, read only or modify metadata */
    struct
    {
        uint32_t mSaveCurrClus;
        uint32_t mSaveLastClus;
    } Alloc;                            /* CMD_FileAlloc, extend/shrink cluster allocation to match file size */
    struct
    {
        uint32_t mSectorOffset;         /* Input: sector based seek offset; 0 = file start, 0xFFFFFFFF = file end; Output: absolute LBA of current pointer, 0xFFFFFFFF for EOF */
        uint32_t mLastOffset;
    } Locate;                           /* CMD_FileLocate, sector aligned file seek */
    struct
    {
        uint8_t mSectorCount;           /* Input: requested sector count for read; Output: actual sectors transferred */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mRemainCnt;
        uint8_t *mDataBuffer;           /* Input: read buffer base pointer; Output: updated buffer pointer after transfer */
        uint32_t mLbaStart;
    } Read;                             /* CMD_FileRead, sector mode file read */
    struct
    {
        uint8_t mSectorCount;           /* Input: requested sector count for write; Output: actual sectors transferred */
        uint8_t mActCnt;
        uint8_t mLbaCount;
        uint8_t mAllocCnt;
        uint8_t *mDataBuffer;           /* Input: write buffer base pointer; Output: updated buffer pointer after transfer */
        uint32_t mLbaStart;
        uint32_t mSaveValue;
    } Write;                            /* CMD_FileWrite, sector mode file write */
    struct
    {
        uint32_t mDiskSizeSec;          /* Output: total physical disk sectors, valid only on first successful call */
    } DiskReady;                        /* CMD_DiskReady, check media readiness */
    struct
    {
        uint32_t mByteOffset;           /* Input: byte based seek offset; Output: absolute LBA of current pointer, 0xFFFFFFFF for EOF */
        uint32_t mLastOffset;
    } ByteLocate;                       /* CMD_ByteLocate, arbitrary byte offset seek */
    struct
    {
        uint16_t mByteCount;            /* Input: requested byte count for read; Output: actual bytes read */
        uint8_t *mByteBuffer;           /* Input: destination buffer for byte read */
        uint16_t mActCnt;
    } ByteRead;                         /* CMD_ByteRead, byte mode block read */
    struct
    {
        uint16_t mByteCount;            /* Input: requested byte count for write; Output: actual bytes written */
        uint8_t *mByteBuffer;           /* Input: source buffer for byte write */
        uint16_t mActCnt;
    } ByteWrite;                        /* CMD_ByteWrite, byte mode block write */
    struct
    {
        uint8_t mSaveVariable;          /* Control code: 0 = restore single drive context, 0x80 = restore multi drive context, other values for save/backup */
        uint8_t mReserved[3];
        uint8_t *mBuffer;               /* Context backup buffer with minimum size of 80 bytes */
    } SaveVariable;                     /* CMD_SaveVariable, save / restore library context for multi device switching */
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
#define DISK_BASE_BUF_LEN       512     /* Default sector buffer length 512 bytes, recommend 2048/4096 for large sector USB drives. Set to 0 to omit buffer definition in header and assign pDISK_BASE_BUF from application */
#endif
/* Global library variables */
extern  volatile uint8_t CHRV3IntStatus;    /* Interrupt driven operation status code */
extern  volatile uint8_t CHRV3DiskStatus;   /* Media and file system state machine value */
extern  uint8_t  CHRV3vDiskFat;             /* Volume FAT type:1=FAT12,2=FAT16,3=FAT32 */
extern  uint8_t  CHRV3vSecPerClus;          /* Sectors per allocation cluster on the volume */
extern  uint8_t  CHRV3vSectorSizeB;         /* log2(CHRV3vSectorSize), sector shift value */
extern  uint32_t CHRV3vStartLba;            /* Starting LBA address of the logical partition */
extern  uint32_t CHRV3vDiskRoot;            /* For FAT16: root directory sector count; For FAT32: starting cluster number of root directory */
extern  uint32_t CHRV3vDataStart;           /* Starting LBA of the volume data region */
extern  uint32_t CHRV3vStartCluster;        /* Starting cluster number of the currently opened file/directory */
extern  uint32_t CHRV3vFileSize;            /* Byte length of currently opened file */
extern  uint32_t CHRV3vCurrentOffset;       /* Byte offset file pointer for active handle */
extern  uint32_t CHRV3vFdtLba;              /* LBA address of current FAT directory entry sector */
extern  uint32_t CHRV3vLbaCurrent;          /* Starting LBA for ongoing disk read/write operation */
extern  uint16_t CHRV3vFdtOffset;           /* Byte offset of directory entry inside its sector */
extern  uint16_t CHRV3vSectorSize;          /* Physical media sector size in bytes */
extern  uint8_t  CHRV3vCurrentLun;          /* Current logical unit number for mass storage access */
extern  uint8_t  CHRV3vSubClassIs6;         /* USB storage subclass flag: non zero indicates SCSI transparent command set */
extern  uint8_t  *pDISK_BASE_BUF;           /* Pointer to sector data buffer, buffer size >= CHRV3vSectorSize, initialized by application */
extern  uint8_t  *pDISK_FAT_BUF;            /* Pointer to FAT table cache buffer, buffer size >= CHRV3vSectorSize, initialized by application */
extern  uint16_t CHRV3vPacketSize;          /* Max bulk endpoint packet size:64 for FS,512 for HS/SS, assigned after device enumeration */
extern  uint32_t *pTX_DMA_A_REG;            /* Transmit DMA address register pointer, assigned by application */
extern  uint32_t *pRX_DMA_A_REG;            /* Receive DMA address register pointer, assigned by application */
extern  uint16_t *pTX_LEN_REG;              /* Transmit transfer length register pointer, assigned by application */
extern  uint16_t *pRX_LEN_REG;              /* Receive transfer length register pointer, assigned by application */
extern  CMD_PARAM_I mCmdParam;              /* Global command parameter union */
extern  __attribute__ ((aligned(4)))   uint8_t  RxBuffer[ ];  // IN transfer buffer, must be even address aligned
extern  __attribute__ ((aligned(4)))   uint8_t  TxBuffer[ ];  // OUT transfer buffer, must be even address aligned
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
extern  uint8_t DISK_BASE_BUF[ DISK_BASE_BUF_LEN ];                         /* Sector buffer in external RAM, length equals one physical sector */
#endif
extern  uint8_t CHRV3ReadSector( uint8_t SectCount, uint8_t * DataBuf );    /* Read multiple consecutive sectors from media into data buffer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3WriteSector( uint8_t SectCount, uint8_t * DataBuf );   /* Write multiple consecutive sectors from buffer to media */
#endif
extern  uint8_t CHRV3DiskConnect( void );   /* Detect device hot plug status and update CHRV3DiskStatus */
extern  void    xFileNameEnumer( void );    /* External filename enumeration callback function */
extern  uint8_t CHRV3LibInit( void );       /* Initialize CHRV3 library, returns 0 on success */
/* Public library APIs */
/* File operation and disk query functions may modify pDISK_BASE_BUF cache.
If the buffer is temporarily reused for other purposes with limited RAM,
call CHRV3DirtyBuffer to invalidate the cached disk content before filesystem operations resume */
extern  uint8_t CHRV3GetVer( void );        /* Retrieve library version byte */
extern  void    CHRV3DirtyBuffer( void );   /* Mark sector cache as invalid, discard cached disk data */
extern  uint8_t CHRV3BulkOnlyCmd( uint8_t * DataBuf );  /* Execute USB Mass Storage Bulk Only transport command */
extern  uint8_t CHRV3DiskReady( void );     /* Poll media readiness status */
extern  uint8_t CHRV3AnalyzeError( uint8_t iMode ); /* Parse USB transaction failure and translate to high level error code */
extern  uint8_t CHRV3FileOpen( void );      /* Open file handle or trigger wildcard enumeration */
extern  uint8_t CHRV3FileClose( void );     /* Close active file handle, flush pending writes if required */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileErase( void );     /* Delete target file and close handle */
extern  uint8_t CHRV3FileCreate( void );    /* Create new file handle, overwrite existing entry */
extern  uint8_t CHRV3FileAlloc( void );     /* Adjust FAT cluster allocation to match target file size */
#endif
extern  uint8_t CHRV3FileModify( void );    /* Read or modify metadata of active file handle */
extern  uint8_t CHRV3FileQuery( void );     /* Read only metadata query on active file handle */
extern  uint8_t CHRV3FileLocate( void );    /* Sector aligned seek on active file handle */
extern  uint8_t CHRV3FileRead( void );      /* Sector mode read from current file pointer */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3FileWrite( void );     /* Sector mode write at current file pointer */
#endif
extern  uint8_t CHRV3ByteLocate( void );    /* Byte granularity seek on active file handle */
extern  uint8_t CHRV3ByteRead( void );      /* Byte mode arbitrary offset block read */
#ifdef  EN_DISK_WRITE
extern  uint8_t CHRV3ByteWrite( void );     /* Byte mode arbitrary offset block write */
#endif
extern  uint8_t CHRV3DiskQuery( void );     /* Query total and free sector count of mounted volume */
extern  void    CHRV3SaveVariable( void );  /* Save or restore full library runtime context for multi device switching */
extern  void    mDelayuS( uint16_t n );     // Microsecond delay wrapper
extern  void    mDelaymS( uint16_t n );     // Millisecond delay wrapper
extern  uint8_t USBHostTransact( uint8_t endp_pid, uint8_t tog, uint32_t timeout ); // Low level USB host transaction: endpoint/PID, data toggle, NAK retry timeout, return 0 for success
extern  uint8_t HostCtrlTransfer( uint8_t * DataBuf, uint8_t * RetLen );            // USB control transfer, setup packet pre filled inside pSetupReq; DataBuf for optional IN/OUT payload, actual transfer length stored at RetLen
extern  void    CopySetupReqPkg( const char * pReqPkt );    // Copy pre defined 8 byte setup request into TxBuffer
extern  uint8_t CtrlGetDeviceDescrTB( void );               // Retrieve USB device descriptor into TxBuffer
extern  uint8_t CtrlGetConfigDescrTB( void );               // Retrieve USB full configuration descriptor into TxBuffer
extern  uint8_t CtrlSetUsbAddress( uint8_t addr );          // Send SET_ADDRESS control request
extern  uint8_t CtrlSetUsbConfig( uint8_t cfg );            // Send SET_CONFIGURATION control request
extern  uint8_t CtrlClearEndpStall( uint8_t endp );         // Send CLEAR_FEATURE endpoint halt request
#ifndef FOR_ROOT_UDISK_ONLY
//extern    uint8_t CtrlGetHubDescr( void );  // Retrieve HUB descriptor into TxBuffer
extern  uint8_t HubGetPortStatus( uint8_t HubPortIndex );  // Fetch USB HUB port status into TxBuffer
//extern    uint8_t HubSetPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Set HUB port feature flag
extern  uint8_t HubClearPortFeature( uint8_t HubPortIndex, uint8_t FeatureSelt );  // Clear HUB port feature flag
#endif
#ifdef __cplusplus
}
#endif
#endif
