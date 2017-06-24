/*---------------------------------------------------------------------------/
/  Petit FatFs - FAT file system module include file  R0.03   (C)ChaN, 2014
/----------------------------------------------------------------------------/
/ Petit FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2014, ChaN, all right reserved.
/
/ * The Petit FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------/
* Adapted to M10 Library by PulseRain Technology, LLC 
* (Feb 2017)
/----------------------------------------------------------------------------*/



#ifndef M10SD_H
#define M10SD_H

#include "Arduino.h"


//=======================================================================
// integer.h
//=======================================================================

/* Embedded platform */

/* This type MUST be 8 bit */
typedef uint8_t     BYTE;

/* These types MUST be 16 bit */
typedef int16_t			SHORT;
typedef uint16_t  	WORD;
typedef uint16_t	  WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int16_t				INT;
typedef uint16_t    	UINT;

/* These types MUST be 32 bit */
typedef int32_t			LONG;
typedef uint32_t  	DWORD;

//=======================================================================
// diskio.h
//=======================================================================

/* Status of Disk Functions */
typedef BYTE	DSTATUS;


/* Results of Disk Functions */

#define RES_OK      0    /* 0: Function succeeded */
#define RES_ERROR   1    /* 1: Disk error */
#define RES_NOTRDY  2    /* 2: Not ready */
#define RES_PARERR  3    /* 3: Invalid parameter */

typedef BYTE DRESULT;




//=======================================================================
// pffconf.h
//=======================================================================

#ifndef _PFFCONF
#define _PFFCONF 4004	/* Revision ID */

/*---------------------------------------------------------------------------/
/ Function Configurations
/---------------------------------------------------------------------------*/

#define	_USE_READ	1	/* Enable pf_read() function */
#define	_USE_DIR	0	/* Enable pf_opendir() and pf_readdir() function */
#define	_USE_LSEEK	0	/* Enable pf_lseek() function */
#define	_USE_WRITE	1	/* Enable pf_write() function */

#define _FS_FAT12	0	/* Enable FAT12 */
#define _FS_FAT16	0	/* Enable FAT16 */
#define _FS_FAT32	1	/* Enable FAT32 */


/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

#define _USE_LCC	0	/* Allow lower case characters for path name */

#define	_CODE_PAGE	437
/* The _CODE_PAGE specifies the code page to be used on the target system.
/  SBCS code pages with _USE_LCC == 1 requiers a 128 byte of case conversion
/  table. This might occupy RAM on some platforms, e.g. avr-gcc.
/  When _USE_LCC == 0, _CODE_PAGE has no effect.
/
/   932  - Japanese Shift_JIS (DBCS, OEM, Windows)
/   936  - Simplified Chinese GBK (DBCS, OEM, Windows)
/   949  - Korean (DBCS, OEM, Windows)
/   950  - Traditional Chinese Big5 (DBCS, OEM, Windows)
/   1250 - Central Europe (Windows)
/   1251 - Cyrillic (Windows)
/   1252 - Latin 1 (Windows)
/   1253 - Greek (Windows)
/   1254 - Turkish (Windows)
/   1255 - Hebrew (Windows)
/   1256 - Arabic (Windows)
/   1257 - Baltic (Windows)
/   1258 - Vietnam (OEM, Windows)
/   437  - U.S. (OEM)
/   720  - Arabic (OEM)
/   737  - Greek (OEM)
/   775  - Baltic (OEM)
/   850  - Multilingual Latin 1 (OEM)
/   858  - Multilingual Latin 1 + Euro (OEM)
/   852  - Latin 2 (OEM)
/   855  - Cyrillic (OEM)
/   866  - Russian (OEM)
/   857  - Turkish (OEM)
/   862  - Hebrew (OEM)
/   874  - Thai (OEM, Windows)
*/


/*---------------------------------------------------------------------------/
/ System Configurations
/---------------------------------------------------------------------------*/

#define _WORD_ACCESS	0
/* The _WORD_ACCESS option is an only platform dependent option. It defines
/  which access method is used to the word data on the FAT volume.
/
/   0: Byte-by-byte access. Always compatible with all platforms.
/   1: Word access. Do not choose this unless under both the following conditions.
/
/  * Address misaligned memory access is always allowed for ALL instructions.
/  * Byte order on the memory is little-endian.
/
/  If it is the case, _WORD_ACCESS can also be set to 1 to improve performance and
/  reduce code size. Following table shows an example of some processor types.
/
/   ARM7TDMI    0           ColdFire    0           V850E       0
/   Cortex-M3   0           Z80         0/1         V850ES      0/1
/   Cortex-M0   0           RX600(LE)   0/1         TLCS-870    0/1
/   AVR         0/1         RX600(BE)   0           TLCS-900    0/1
/   AVR32       0           RL78        0           R32C        0
/   PIC18       0/1         SH-2        0           M16C        0/1
/   PIC24       0           H8S         0           MSP430      0
/   PIC32       0           H8/300H     0           x86         0/1
*/








/*---------------------------------------*/
/* Prototypes for disk control functions */

//extern DSTATUS disk_initialize (void);
//extern DRESULT disk_readp (BYTE* buff, DWORD sector, UINT offser, UINT count);
//extern DRESULT disk_writep (const BYTE* buff, DWORD sc);

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */



#endif /* _PFFCONF */




//=======================================================================
// pff.h
//=======================================================================


#ifndef _PFATFS
#define _PFATFS	4004	/* Revision ID */

#if _PFATFS != _PFFCONF
#error Wrong configuration file (pffconf.h).
#endif

#if _FS_FAT32
typedef DWORD CLUST;
#else
typedef WORD CLUST;
#endif


/* File system object structure */

typedef struct {
	BYTE	fs_type;	/* FAT sub type */
	BYTE	flag;		/* File status flags */
	BYTE	csize;		/* Number of sectors per cluster */
	BYTE	pad1;
	WORD	n_rootdir;	/* Number of root directory entries (0 on FAT32) */
	CLUST	n_fatent;	/* Number of FAT entries (= number of clusters + 2) */
	DWORD	fatbase;	/* FAT start sector */
	DWORD	dirbase;	/* Root directory start sector (Cluster# on FAT32) */
	DWORD	database;	/* Data start sector */
	DWORD	fptr;		/* File R/W pointer */
	DWORD	fsize;		/* File size */
	CLUST	org_clust;	/* File start cluster */
	CLUST	curr_clust;	/* File current cluster */
	DWORD	dsect;		/* File current data sector */
} FATFS;


/* Directory object structure */

typedef struct {
	WORD	index;		/* Current read/write index number */
	BYTE*	fn;			/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]} */
	CLUST	sclust;		/* Table start cluster (0:Static table) */
	CLUST	clust;		/* Current cluster */
	DWORD	sect;		/* Current sector */
} DIR;

/* File status structure */

typedef struct {
	DWORD	fsize;		/* File size */
	WORD	fdate;		/* Last modified date */
	WORD	ftime;		/* Last modified time */
	BYTE	fattrib;	/* Attribute */
	char	fname[13];	/* File name */
} FILINFO;



/* File function return code (FRESULT) */
typedef uint8_t FRESULT;

#define FR_OK             0		  /* 0 */
#define FR_DISK_ERR       1		  /* 1 */
#define FR_NOT_READY      2	 	  /* 2 */
#define FR_NO_FILE        3	  	/* 3 */
#define FR_NOT_OPENED     4    	/* 4 */
#define FR_NOT_ENABLED    5  		/* 5 */
#define FR_NO_FILESYSTEM	6     /* 6 */


/*--------------------------------------------------------------*/
/* Petit FatFs module application interface                     */

//FRESULT pf_mount (FATFS* fs) __reentrant;								/* Mount/Unmount a logical drive */
//FRESULT pf_open (const uint8_t* path) __reentrant;							/* Open a file */
//FRESULT pf_read (BYTE* buff, UINT btr, UINT* br) __reentrant;			/* Read data from the open file */
//FRESULT pf_write (const BYTE* buff, UINT btw, UINT* bw) __reentrant;	/* Write data to the open file */
//FRESULT pf_lseek (DWORD ofs) __reentrant;								/* Move file pointer of the open file */
//FRESULT pf_opendir (DIR* dj, const char* path) __reentrant;				/* Open a directory */
//FRESULT pf_readdir (DIR* dj, FILINFO* fno) __reentrant;					/* Read a directory item from the open directory */



/*--------------------------------------------------------------*/
/* Flags and offset address                                     */

/* File status flag (FATFS.flag) */

#define	FA_OPENED	0x01
#define	FA_WPRT		0x02
#define	FA__WIP		0x40


/* FAT sub type (FATFS.fs_type) */

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* File attribute bits for directory entry */

#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define	AM_VOL	0x08	/* Volume label */
#define AM_LFN	0x0F	/* LFN entry */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */
#define AM_MASK	0x3F	/* Mask of defined bits */


/*--------------------------------*/
/* Multi-byte word access macros  */


//== #if _WORD_ACCESS == 1	/* Enable word access to the FAT structure */
//== #define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
//== #define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))
//== #define	ST_WORD(ptr,val)	*(WORD*)(BYTE*)(ptr)=(WORD)(val)
//== #define	ST_DWORD(ptr,val)	*(DWORD*)(BYTE*)(ptr)=(DWORD)(val)
//== #else					/* Use byte-by-byte access to the FAT structure */
//== #define	LD_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr)+1)<<8)|(WORD)*(BYTE*)(ptr))
//== #define	LD_DWORD(ptr)		(DWORD)(((DWORD)(*((BYTE*)(ptr)+3))<<24)|((DWORD)*((BYTE*)(ptr)+2)<<16)|((DWORD)*((BYTE*)(ptr)+1)<<8)|(DWORD)*(BYTE*)(ptr))

//== #define	ST_WORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8)
//== #define	ST_DWORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(ptr)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(ptr)+3)=(BYTE)((DWORD)(val)>>24)
//== #endif




#endif /* _PFATFS */



//=======================================================================
// MicroSD Card Library
//=======================================================================

#define SD_CSR_RESET         1
#define SD_CSR_START         (1 << 1)
#define SD_CSR_INC_ADDR      (1 << 2)
#define SD_CSR_R1_R1B        0
#define SD_CSR_R2            (1 << 3)
#define SD_CSR_R3_R7         (2 << 3)
#define SD_SCLK_SLOW         0
#define SD_SCLK_FAST         (1 << 5)

#define SD_R1_IDLE_STATE     1
#define SD_R1_ERASE_RESET    (1 << 1)
#define SD_R1_ILLEGAL_CMD    (1 << 2)
#define SD_R1_CRC_ERROR      (1 << 3)
#define SD_R1_ERASE_SEQ_ERR  (1 << 4)
#define SD_R1_ADDRESS_ERROR  (1 << 5)
#define SD_R1_PARAMETER_ERR  (1 << 6)


#define SD_TYPE_SDC_V1     1
#define SD_TYPE_SDC_V2     2
#define SD_TYPE_SDHC_SDXC  0xc


#define SD_RET_OK         3
#define SD_RET_TIME_OUT   1
#define SD_RET_CRC_FAIL   2

 
typedef struct {

  uint8_t (*begin)();

  uint8_t (*fopen)(const uint8_t* path) __reentrant;
  uint8_t (*fread)(uint8_t* buff, uint16_t btr, uint16_t* br) __reentrant;
  uint8_t (*fwrite)(const uint8_t* buff, uint16_t btw, uint16_t* bw) __reentrant;
}M10SD_STRUCT;

extern const M10SD_STRUCT SD;

#endif

