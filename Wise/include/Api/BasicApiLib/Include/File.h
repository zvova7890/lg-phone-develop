/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FILE SYSTEM INCLUDE FILE

	Copyright(c) 1997-2002 BNSoft Corp.
	Copyright(c)     -2003 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_FILE_H_
#define		_BNSOFT_FILE_H_

#include	"Include.h"
#include	"ConfigFS.h"

#define  MAX_FILENAME			255
#define  MAX_DIRNAME			255
#define  MAX_FULLPATH			255

#define	MAX_BYTES_FILENAME		MAX_FILENAME*sizeof(A_CHAR) 

#define	DRVID_DEFAULT			0


//	Definition FileType
typedef enum
{
	FILETYPE_DIR_OF_FILE	=	0,
	FILETYPE_FILE,
	FILETYPE_DIRECTORY,
	FILETYPE_MAX
} E_FILETYPE;

//TFileEntry
#define		FILEATTR_SYSTEM				0x8000
#define		FILEATTR_FIXED				0x4000
#define		FILEATTR_EXECUTE			0x2000
#define		FILEATTR_READONLY			0x1000
#define		FILEATTR_HIDDEN				0x0800
#define		FILEATTR_LINEAR				0x0400


#define		SEEK_SET				0
#define		SEEK_CUR				1
#define		SEEK_END				2

#define		FILEMODE_READWRITE			0
#define		FILEMODE_READONLY			1
#define		FILEMODE_WRITEONLY			2
#define		FILEMODE_APPEND				3
#define		FILEMODE_TRUNCATED			4

#define		FILE_HEADER_SIZE			(48)	

#define		NULL_DIR				0		
#define		ROOT_DIR				1	
#define		CURRENT_DIR				0xFFFF
					
#define		DIRID_INVALID				((T_DIRID)(-1))
#define		DRVID_INVALID				((T_DRVID)(-1))

typedef struct
{
	const A_CHAR		cszName[MAX_FILENAME];		
	T_CSTR			pszName;
	WORD			FileID;
	WORD			ParentDirID;
	WORD			Attribute;
	WORD			DriveID;
	QUAD			ClusterID;
	QUAD			CreateTime;
} TFileEntry;


typedef		T_HANDLE	H_SRCHANDLE;
typedef		T_HANDLE	H_FILE;
typedef		void		TFile;

typedef struct 
{
	char d_name[MAX_FILENAME+1]; 
} TDirent;

typedef struct
{
	A_CHAR				szName[MAX_FILENAME+1];
	BOOL				bFile;						//	File(TRUE), Directory(FALSE)
	T_SIZE				Size;						//	File Or Directory Size
	QUAD				CTime;						//	Create Time
	BOOL				BadName;					
	T_SIZE				OccupiedSize;					//	block size * block num
	QUAD				Attr;						//	Attributes
} TFStat;

typedef struct
{
	WORD				ID;
	WORD				ParentDirID;
	T_CSTR				pszName;
} TDirAttr;

//	Sector data structure
typedef struct
{
	QUAD				Attr;
	QUAD				StartAddr;
	QUAD				SectorNum;
	QUAD				SectorSize;
} TSectorInfo;

//	Cluster data structure
typedef struct
{
	QUAD				Attr;
	QUAD				StartAddr;
	QUAD				ClusterNum;
	QUAD				ClusterSize;
} TClusterInfo;

//	Drive data structure
typedef struct
{
	QUAD				ID;			
	T_CSTR				pszName;				
	QUAD				Attribute;				
	QUAD				StartLAddr;			
	QUAD				DriveSize;				
	QUAD				SectorSize;				
	QUAD				ClusterSize;			
	const BYTE*			pFormatData;				
	WORD				FormatDataLen;				
	WORD				SysDirNum;				
} TDriveInfo;
																								//	{{BNS_INTERNALCODE(-)}}
//	Drive data structure
typedef struct
{
	QUAD				ID;					
	T_CSTR				pszName;				
	QUAD				Attribute;				
	QUAD				StartLAddr;				
	QUAD				DriveSize;			
	QUAD				SectorSize;				
	QUAD				ClusterSize;					
	BYTE*				pFormatData;				
	WORD				FormatDataLen;				
	WORD				SysDirNum;				

	TSectorInfo			SectorInfo;
	TClusterInfo		        ClusterInfo;

	void*				pHeadFEObj;
	void*				pHeadDAObj;
	WORD				DirNum;
	WORD				FileNum;
	QUAD				FreeClusterID;
	QUAD				FreeClusterNum;
	QUAD				DelClusterNum;
	void*				pFindFEObj;
	QUAD				FindFEDirID;
	void*				pFindDAObj;
	QUAD				FindDADirID;
	WORD				CurrentDirID;
} TDrive;

//	Drive Attribute Type
#define		DRVATTR_VALID			0x80000000	
#define		DRVATTR_READONLY		0x40000000
#define		DRVATTR_HASLINEARFILE		0x20000000	
#define		DRVATTR_RECORD			0x10000000	
#define		DRVATTR_RAMDRIVE		0x08000000
#define		DRVATTR_RENAMABLE		0x04000000
#define		DRVATTR_BLOCKDEVICE		0x02000000

//	Drive format directives
#define		DRVFMT_NORMALDRIVE		0	
#define		DRVFMT_READONLYDRIVE		1
#define		DRVFMT_DIRLIST			2
#define		DRVFMT_READONLYDIRLIST		3
																								//	{{BNS_INTERNALCODE(-)}}
typedef struct
{
	void*				pFindFEObj;
	QUAD				FindFEDirID;
	void*				pFindDAObj;
	QUAD				FindDADirID;
} TSrchFS;

typedef enum
{
	DRVSPACE_TOTAL						= 0,
	DRVSPACE_FREE,
	DRVSPACE_USED,
	DRVSPACE_GARBAGE,
	DRVSPACE_LARGESTBLOCK
} E_DRVSPACE;

typedef enum
{
	RGNSPACE_TOTAL						= 0,
	RGNSPACE_FREE,
	RGNSPACE_USED,
	RGNSPACE_RSVD,
	RGNSPACE_GARBAGE,
	RGNSPACE_LARGESTBLOCK
} E_RGNSPACE;

//	Access Level Definition
#ifndef		ACCESSLEVEL_DEFINED
#define		ACCESSLEVEL_DEFINED
typedef enum
{
	ACCESSLEVEL_PUBLIC					= 0,
	ACCESSLEVEL_DEVELOPER,
	ACCESSLEVEL_SYSTEM
} E_ACCESSLEVEL;
#endif	//	ACCESSLEVEL_DEFINED

typedef enum
{
        FILELEVEL_NONO						= 0,		//	DEVELOPER None,      PUBLIC None
	FILELEVEL_NOWO,								//	DEVELOPER None,	     PUBLIC WriteOnly
	FILELEVEL_NORO,								//	DEVELOPER None,	     PUBLIC ReadOnly
	FILELEVEL_NORW,								//	DEVELOPER None,	     PUBLIC ReadWrite
	FILELEVEL_WONO,								//	DEVELOPER WriteOnly, PUBLIC None
	FILELEVEL_WOWO,								//	DEVELOPER WriteOnly, PUBLIC WriteOnly
	FILELEVEL_WORO,								//	DEVELOPER WriteOnly, PUBLIC ReadOnly
	FILELEVEL_WORW,								//	DEVELOPER WriteOnly, PUBLIC ReadWrite
	FILELEVEL_RONO,								//	DEVELOPER ReadOnly,  PUBLIC None
	FILELEVEL_ROWO,								//	DEVELOPER ReadOnly,  PUBLIC WriteOnly
	FILELEVEL_RORO,								//	DEVELOPER ReadOnly,  PUBLIC ReadOnly
	FILELEVEL_RORW,								//	DEVELOPER ReadOnly,  PUBLIC ReadWrite
	FILELEVEL_RWNO,								//	DEVELOPER ReadWrite, PUBLIC None
	FILELEVEL_RWWO,								//	DEVELOPER ReadWrite, PUBLIC WriteOnly
	FILELEVEL_RWRO,								//	DEVELOPER ReadWrite, PUBLIC ReadOnly
	FILELEVEL_RWRW,								//	DEVELOPER ReadWrite, PUBLIC ReadWrite
	FILELEVEL_MAX
} E_FILELEVEL;

//	GarbageCollection Status
typedef int		E_GC_STATUS;

enum
{
	GC_FAIL								= 0,		//	GarbageCollection Failed
	GC_NEEDMOREBLOCK,								//	GarbageCollection done but more block need GC
	GC_COMPLETE									//	All block cleaded. GC Completed
};


#endif	//	_BNSOFT_FILE_H_
