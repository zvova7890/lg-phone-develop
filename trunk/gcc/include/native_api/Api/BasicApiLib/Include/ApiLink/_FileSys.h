/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__FILESYS_H_
#define		_BNSOFT__FILESYS_H_

#include	"../FileSys.h"

typedef E_GC_STATUS		(*T_pfnFileSys_GarbageCollection) (BOOL bAllDrive, BOOL bFullRegion);
typedef BOOL			(*T_pfnFileSys_IsExist)           (T_CSTR pcszFileName);
typedef BOOL			(*T_pfnFileSys_IsOpen)            (H_FILE hFile);
typedef H_FILE			(*T_pfnFileSys_Create)            (T_CSTR pcszFileName, WORD wAttr, T_SIZE Size);
typedef H_FILE			(*T_pfnFileSys_Open)              (T_CSTR pcszFileName, int nMode);
typedef BOOL			(*T_pfnFileSys_Close)             (H_FILE hFile);
typedef T_POS			(*T_pfnFileSys_Seek)              (H_FILE hFile, long lPos, int nFlag);
typedef T_NUM			(*T_pfnFileSys_Read)              (H_FILE hFile, BYTE* pBuf, T_SIZE Size);
typedef T_NUM			(*T_pfnFileSys_Write)             (H_FILE hFile, BYTE* pBuf, T_SIZE Size);
typedef BOOL			(*T_pfnFileSys_Truncate)          (H_FILE hFile, T_SIZE	Size);
typedef T_SIZE			(*T_pfnFileSys_GetSize)           (H_FILE hFile);
typedef T_POS			(*T_pfnFileSys_GetPos)            (H_FILE hFile);
typedef TFileEntry*		(*T_pfnFileSys_GetEntry)          (H_FILE hFile);
typedef T_CSTR			(*T_pfnFileSys_GetName)           (H_FILE hFile);
typedef T_CSTR			(*T_pfnFileSys_GetExtension)      (H_FILE hFile);
typedef BOOL			(*T_pfnFileSys_GetPath)           (H_FILE hFile, T_STR pBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnFileSys_MoveFile)          (T_CSTR pcszFileName, T_CSTR pcszNewFileName);
typedef BOOL			(*T_pfnFileSys_CopyFile)          (T_CSTR pcszFileName, T_CSTR pcszNewFileName);
typedef	BOOL			(*T_pfnFileSys_RemoveFile)        (T_CSTR pcszFileName);
typedef	BOOL			(*T_pfnFileSys_RemoveAllFiles)    (T_CSTR DirPath);
typedef BOOL			(*T_pfnFileSys_SearchFile)        (T_CSTR pcszFileName);
typedef TFileEntry*		(*T_pfnFileSys_GetFileEntry)      (T_CSTR pcszFileName);
typedef T_SIZE			(*T_pfnFileSys_GetFileSize)       (T_CSTR pcszFileName);
typedef T_ADDR			(*T_pfnFileSys_GetFileAddress)    (T_CSTR pcszFileName);
typedef T_CSTR			(*T_pfnFileSys_GetFileName)       (T_CSTR pcszFileName);
typedef T_CSTR			(*T_pfnFileSys_GetFileExtension)  (T_CSTR pcszFileName);
typedef BOOL			(*T_pfnFileSys_GetFilePath)       (T_CSTR pcszFileName, T_STR pBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnFileSys_CreateDir)         (T_CSTR pcszDirName);
typedef BOOL			(*T_pfnFileSys_ChangeDir)         (T_CSTR DirPath);
typedef BOOL			(*T_pfnFileSys_MoveDir)           (T_CSTR pcszDirName, T_CSTR pcszNewDirName);
typedef BOOL			(*T_pfnFileSys_CopyDir)           (T_CSTR pcszDirName, T_CSTR pcszNewDirName);
typedef int			(*T_pfnFileSys_RemoveDir)         (T_CSTR pcszDirName);
typedef int			(*T_pfnFileSys_SearchDir)         (T_CSTR pcszDirName);
typedef BOOL			(*T_pfnFileSys_Stat)              (T_CSTR pcszFileName, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FStat)             (H_FILE hFile, TFStat* FStat);
typedef T_ADDR			(*T_pfnFileSys_GetAddr)			  (H_FILE hFile);
typedef QUAD			(*T_pfnFileSys_FindFreeSpace)	  (T_CSTR pcszPath, QUAD nSize, BOOL bLinear);

typedef TDirAttr*		(*T_pfnFileSys_GetDirAttr)        (T_CSTR pcszDirName);
typedef T_DIRID			(*T_pfnFileSys_GetDirID)          (T_CSTR pcszDirName);
typedef T_CSTR			(*T_pfnFileSys_GetDirName)        (T_DIRID DirID);
typedef BOOL			(*T_pfnFileSys_GetDirPath)        (T_DIRID DirID, T_STR pBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnFileSys_SetCurrentDirID)   (T_DIRID DirID);
typedef T_DIRID			(*T_pfnFileSys_GetCurrentDirID)   (void);
typedef T_DIRID			(*T_pfnFileSys_GetParentDirID)    (T_DIRID DirID);
typedef T_DRVID			(*T_pfnFileSys_ChangeDrive)       (T_DRVID DrvID);
typedef T_DRVID			(*T_pfnFileSys_GetCurrDriveID)    (void);
typedef TDrive*			(*T_pfnFileSys_GetCurrDriveInfo)  (void);
typedef BOOL			(*T_pfnFileSys_FindFirstFile)     (T_CSTR DirPath, long* Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindNextFile)      (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindPrevFile)      (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindFirstDir)      (T_CSTR DirPath, long* Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindNextDir)       (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindPrevDir)       (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindFirstDirFile)  (T_CSTR DirPath, long* Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindNextDirFile)   (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindPrevDirFile)   (long Iterator, TFStat* FStat);
typedef BOOL			(*T_pfnFileSys_FindClose)         (long Iterator);
typedef TDrive*			(*T_pfnFileSys_FindFirstDrive)    (void);
typedef TDrive*			(*T_pfnFileSys_FindNextDrive)     (void);
typedef BOOL			(*T_pfnFileSys_GetSearchHandle)   (TSrchFS* pSrchFS);
typedef BOOL			(*T_pfnFileSys_SetSearchHandle)   (TSrchFS* pSrchFS);
typedef T_NUM			(*T_pfnFileSys_GetFileCount)      (T_CSTR pcszDirName);
typedef T_NUM			(*T_pfnFileSys_GetDirCount)       (T_CSTR pcszDirName);
typedef T_NUM			(*T_pfnFileSys_GetDriveCount)     (void);
typedef T_NUM			(*T_pfnFileSys_GetFileCountEx)    (T_DIRID ParentDirID);
typedef T_NUM			(*T_pfnFileSys_GetDirCountEx)     (T_DIRID ParentDirID);
typedef	UINT64			(*T_pfnFileSys_GetFreeSpace)      (T_CSTR Mount);

typedef	UINT64			(*T_pfnFileSys_GetTotalSpace)      (T_CSTR Mount);
typedef T_SIZE			(*T_pfnFileSys_GetDriveSpace)     (T_DRVID DrvID, E_DRVSPACE enDrvSpaceType);
typedef BOOL			(*T_pfnFileSys_SetFileLevel)      (T_CSTR pcszFileName, E_FILELEVEL enFileLevel);
typedef E_FILELEVEL		(*T_pfnFileSys_GetFileLevel)      (T_CSTR pcszFileName);
typedef BOOL			(*T_pfnFileSys_SetDirLevel)       (T_CSTR pcszDirName, int nDirLevel);
typedef int				(*T_pfnFileSys_GetDirLevel)       (T_CSTR pcszDirName);
typedef void			(*T_pfnFileSys_SaveFlashMem)      (T_CSTR pcszFileName);
typedef QUAD			(*T_pfnFileSys_GetCreateTime)     (T_CSTR FilePath, BYTE* pHour, BYTE* pMinute, BYTE* pSecond);
typedef QUAD			(*T_pfnFileSys_GetCreateDate)     (T_CSTR FilePath, int* pYear, int* pMonth, int* pDay);
typedef BOOL			(*T_pfnFileSys_DisableGC)         (BOOL bEnable);
typedef BOOL			(*T_pfnFileSys_GetCurrentDir)     (T_STR Buffer, T_SIZE Size);
typedef BOOL			(*T_pfnFileSys_Rename)			  (T_CSTR old_pcszFileName, T_CSTR new_pcszFileName);
typedef QUAD			(*T_pfnFileSys_GetDirNum)		  (T_CSTR pcszDirName);
typedef QUAD			(*T_pfnFileSys_GetFileNum)		  (T_CSTR pcszDirName);

typedef struct
{
	T_pfnFileSys_GarbageCollection		pfnGarbageCollection; /* NULL */
	T_pfnFileSys_IsExist			pfnIsExist;
	T_pfnFileSys_IsOpen			pfnIsOpen;
	T_pfnFileSys_Create			pfnCreate;
	T_pfnFileSys_Open			pfnOpen;
	T_pfnFileSys_Close			pfnClose;
	T_pfnFileSys_Seek			pfnSeek;
	T_pfnFileSys_Read			pfnRead;
	T_pfnFileSys_Write			pfnWrite;
	T_pfnFileSys_Truncate			pfnTruncate;
	T_pfnFileSys_GetSize			pfnGetSize;
	T_pfnFileSys_GetPos			pfnGetPos;
	T_pfnFileSys_GetEntry			pfnGetEntry; /* NULL */
	T_pfnFileSys_GetName			pfnGetName; /* NULL */
	T_pfnFileSys_GetExtension		pfnGetExtension; /* NULL */
	T_pfnFileSys_GetPath			pfnGetPath; /* NULL */
	T_pfnFileSys_MoveFile			pfnMoveFile; /* NULL */
	T_pfnFileSys_CopyFile			pfnCopyFile;
	T_pfnFileSys_RemoveFile			pfnRemoveFile;
	T_pfnFileSys_RemoveAllFiles		pfnRemoveAllFiles;
	T_pfnFileSys_SearchFile			pfnSearchFile;
	T_pfnFileSys_GetFileEntry		pfnGetFileEntry; /* NULL */
	T_pfnFileSys_GetFileSize		pfnGetFileSize;
	T_pfnFileSys_GetFileAddress		pfnGetFileAddress; /* NULL */
	T_pfnFileSys_GetFileName		pfnGetFileName; /* NULL */
	T_pfnFileSys_GetFileExtension		pfnGetFileExtension;
	T_pfnFileSys_GetFilePath		pfnGetFilePath; /* NULL */
	T_pfnFileSys_CreateDir			pfnCreateDir;
	T_pfnFileSys_ChangeDir			pfnChangeDir;
	T_pfnFileSys_MoveDir			pfnMoveDir; /* NULL */
	T_pfnFileSys_CopyDir			pfnCopyDir; /* NULL */
	T_pfnFileSys_RemoveDir			pfnRemoveDir;
	T_pfnFileSys_SearchDir			pfnSearchDir;
	T_pfnFileSys_Stat			pfnStat;
	T_pfnFileSys_FStat			pfnFStat;
	T_pfnFileSys_GetAddr			pfnGetAddr;
	T_pfnFileSys_FindFreeSpace		pfn_FindFreeSpace;
	T_pfnFileSys_GetDirAttr			pfnGetDirAttr; /* NULL */
	T_pfnFileSys_GetDirID			pfnGetDirID; /* NULL */
	T_pfnFileSys_GetDirName			pfnGetDirName; /* NULL */
	T_pfnFileSys_GetDirPath			pfnGetDirPath; /* NULL */
	T_pfnFileSys_SetCurrentDirID		pfnSetCurrentDirID; /* NULL */
	T_pfnFileSys_GetCurrentDirID		pfnGetCurrentDirID; /* NULL */
	T_pfnFileSys_GetParentDirID		pfnGetParentDirID; /* NULL */
	T_pfnFileSys_ChangeDrive		pfnChangeDrive; /* NULL */
	T_pfnFileSys_GetCurrDriveID		pfnGetCurrDriveID; /* NULL */
	T_pfnFileSys_GetCurrDriveInfo		pfnGetCurrDriveInfo; /* NULL */
	T_pfnFileSys_FindFirstFile		pfnFindFirstFile;
	T_pfnFileSys_FindNextFile		pfnFindNextFile;
	T_pfnFileSys_FindPrevFile		pfnFindPrevFile; /* NULL */
	T_pfnFileSys_FindFirstDir		pfnFindFirstDir;
	T_pfnFileSys_FindNextDir		pfnFindNextDir;
	T_pfnFileSys_FindPrevDir		pfnFindPrevDir; /* NULL */
	T_pfnFileSys_FindFirstDirFile		pfnFindFirstDirFile;
	T_pfnFileSys_FindNextDirFile		pfnFindNextDirFile;
	T_pfnFileSys_FindPrevDirFile		pfnFindPrevDirFile; /* NULL */
	T_pfnFileSys_FindClose  		pfnFindClose;
	T_pfnFileSys_FindFirstDrive		pfnFindFirstDrive; /* NULL */
	T_pfnFileSys_FindNextDrive		pfnFindNextDrive; /* NULL */
	T_pfnFileSys_GetSearchHandle		pfnGetSearchHandle; /* NULL */
	T_pfnFileSys_SetSearchHandle		pfnSetSearchHandle; /* NULL */
	T_pfnFileSys_GetFileCount		pfnGetFileCount; /* NULL */
	T_pfnFileSys_GetDirCount		pfnGetDirCount; /* NULL */
	T_pfnFileSys_GetDriveCount		pfnGetDriveCount; /* NULL */
	T_pfnFileSys_GetFileCountEx		pfnGetFileCountEx; /* NULL */
	T_pfnFileSys_GetDirCountEx		pfnGetDirCountEx; /* NULL */
	T_pfnFileSys_GetFreeSpace		pfnGetFreeSpace; /* NULL */
	T_pfnFileSys_GetTotalSpace		pfnGetTotalSpace;
	T_pfnFileSys_GetDriveSpace		pfnGetDriveSpace;
	T_pfnFileSys_SetFileLevel		pfnSetFileLevel; /* NULL */
	T_pfnFileSys_GetFileLevel		pfnGetFileLevel; /* NULL */
	T_pfnFileSys_SetDirLevel		pfnSetDirLevel; /* NULL */
	T_pfnFileSys_GetDirLevel		pfnGetDirLevel; /* NULL */
	T_pfnFileSys_SaveFlashMem		pfnSaveFlashMem; /* NULL */
	T_pfnFileSys_GetCreateTime              pfnGetCreateTime; /* NULL */
	T_pfnFileSys_GetCreateDate              pfnGetCreateDate;
	T_pfnFileSys_DisableGC			pfnDisableGC;
	T_pfnFileSys_GetCurrentDir		pfnGetCurrentDir;  /* NULL */
	T_pfnFileSys_Rename			pfnRename;
	T_pfnFileSys_GetDirNum			pfnGetDirNum;
	T_pfnFileSys_GetFileNum			pfnGetFileNum;
} TApiGrp_FileSys;


#define	FileSys_GarbageCollection(p1,p2)	__ApiLink2(FileSys,GarbageCollection,p1,p2)
#define	FileSys_IsExist(p1)			__ApiLink1(FileSys,IsExist,p1)
#define	FileSys_IsOpen(p1)			__ApiLink1(FileSys,IsOpen,p1)
#define	FileSys_Create(p1,p2,p3)		__ApiLink3(FileSys,Create,p1,p2,p3)
#define	FileSys_Open(p1,p2)			__ApiLink2(FileSys,Open,p1,p2)
#define	FileSys_Close(p1)			__ApiLink1(FileSys,Close,p1)
#define	FileSys_Seek(p1,p2,p3)			__ApiLink3(FileSys,Seek,p1,p2,p3)
#define	FileSys_Read(p1,p2,p3)			__ApiLink3(FileSys,Read,p1,p2,p3)
#define	FileSys_Write(p1,p2,p3)			__ApiLink3(FileSys,Write,p1,p2,p3)
#define	FileSys_Truncate(p1,p2)			__ApiLink2(FileSys,Truncate,p1,p2)
#define	FileSys_GetSize(p1)			__ApiLink1(FileSys,GetSize,p1)
#define	FileSys_GetPos(p1)			__ApiLink1(FileSys,GetPos,p1)
#define	FileSys_GetEntry(p1)			__ApiLink1(FileSys,GetEntry,p1)
#define	FileSys_GetName(p1)			__ApiLink1(FileSys,GetName,p1)
#define	FileSys_GetExtension(p1)		__ApiLink1(FileSys,GetExtension,p1)
#define	FileSys_GetPath(p1,p2,p3)		__ApiLink3(FileSys,GetPath,p1,p2,p3)
#define	FileSys_MoveFile(p1,p2)			__ApiLink2(FileSys,MoveFile,p1,p2)
#define	FileSys_CopyFile(p1,p2)			__ApiLink2(FileSys,CopyFile,p1,p2)
#define FileSys_RemoveFile(p1)			__ApiLink1(FileSys,RemoveFile,p1)
#define FileSys_RemoveAllFiles(p1)		__ApiLink1(FileSys,RemoveAllFiles,p1)
#define	FileSys_SearchFile(p1)			__ApiLink1(FileSys,SearchFile,p1)
#define	FileSys_GetFileEntry(p1)		__ApiLink1(FileSys,GetFileEntry,p1)
#define	FileSys_GetFileSize(p1)			__ApiLink1(FileSys,GetFileSize,p1)
#define	FileSys_GetFileAddress(p1)		__ApiLink1(FileSys,GetFileAddress,p1)
#define	FileSys_GetFileName(p1)			__ApiLink1(FileSys,GetFileName,p1)
#define	FileSys_GetFileExtension(p1)		__ApiLink1(FileSys,GetFileExtension,p1)
#define	FileSys_GetFilePath(p1,p2,p3)		__ApiLink3(FileSys,GetFilePath,p1,p2,p3)
#define	FileSys_CreateDir(p1)			__ApiLink1(FileSys,CreateDir,p1)
#define	FileSys_ChangeDir(p1)			__ApiLink1(FileSys,ChangeDir,p1)
#define	FileSys_MoveDir(p1,p2)			__ApiLink2(FileSys,MoveDir,p1,p2)
#define	FileSys_CopyDir(p1,p2)			__ApiLink2(FileSys,CopyDir,p1,p2)
#define	FileSys_RemoveDir(p1)			__ApiLink1(FileSys,RemoveDir,p1)
#define	FileSys_SearchDir(p1)			__ApiLink1(FileSys,SearchDir,p1)
#define	FileSys_Stat(p1,p2)			__ApiLink2(FileSys,Stat,p1,p2)
#define	FileSys_FStat(p1,p2)			__ApiLink2(FileSys,FStat,p1,p2)
#define	FileSys_GetAddr(p1)			__ApiLink1(FileSys,GetAddr,p1)
#define	FileSys_FindFreeSpace(p1, p2, p3)	__ApiLink3(FileSys,FindFreeSpace,p1,p2,p3)
#define	FileSys_GetDirAttr(p1)			__ApiLink1(FileSys,GetDirAttr,p1)
#define	FileSys_GetDirID(p1)			__ApiLink1(FileSys,GetDirID,p1)
#define	FileSys_GetDirName(p1)			__ApiLink1(FileSys,GetDirName,p1)
#define	FileSys_GetDirPath(p1,p2,p3)		__ApiLink3(FileSys,GetDirPath,p1,p2,p3)
#define	FileSys_SetCurrentDirID(p1)		__ApiLink1(FileSys,SetCurrentDirID,p1)
#define	FileSys_GetCurrentDirID()		__ApiLink0(FileSys,GetCurrentDirID)
#define	FileSys_GetParentDirID(p1)		__ApiLink1(FileSys,GetParentDirID,p1)
#define	FileSys_ChangeDrive(p1)			__ApiLink1(FileSys,ChangeDrive,p1)
#define	FileSys_GetCurrDriveID()		__ApiLink0(FileSys,GetCurrDriveID)
#define	FileSys_GetCurrDriveInfo()		__ApiLink0(FileSys,GetCurrDriveInfo)
#define	FileSys_FindFirstFile(p1,p2,p3)		__ApiLink3(FileSys,FindFirstFile,p1,p2,p3)
#define	FileSys_FindNextFile(p1,p2)		__ApiLink2(FileSys,FindNextFile,p1,p2)
#define	FileSys_FindPrevFile(p1,p2)		__ApiLink2(FileSys,FindPrevFile,p1,p2)
#define	FileSys_FindFirstDir(p1,p2,p3)		__ApiLink3(FileSys,FindFirstDir,p1,p2,p3)
#define	FileSys_FindNextDir(p1,p2)		__ApiLink2(FileSys,FindNextDir,p1,p2)
#define	FileSys_FindPrevDir(p1,p2)		__ApiLink2(FileSys,FindPrevDir,p1,p2)
#define	FileSys_FindFirstDirFile(p1,p2,p3)	__ApiLink3(FileSys,FindFirstDirFile,p1,p2,p3)
#define	FileSys_FindNextDirFile(p1,p2)		__ApiLink2(FileSys,FindNextDirFile,p1,p2)
#define	FileSys_FindPrevDirFile(p1,p2)		__ApiLink2(FileSys,FindPrevDirFile,p1,p2)
#define	FileSys_FindClose(p1)   		__ApiLink1(FileSys,FindClose,p1)
#define	FileSys_FindFirstDrive()		__ApiLink0(FileSys,FindFirstDrive)
#define	FileSys_FindNextDrive()			__ApiLink0(FileSys,FindNextDrive)
#define	FileSys_GetSearchHandle(p1)		__ApiLink1(FileSys,GetSearchHandle,p1)
#define	FileSys_SetSearchHandle(p1)		__ApiLink1(FileSys,SetSearchHandle,p1)
#define	FileSys_GetFileCount(p1)		__ApiLink1(FileSys,GetFileCount,p1)
#define	FileSys_GetDirCount(p1)			__ApiLink1(FileSys,GetDirCount,p1)
#define	FileSys_GetDriveCount()			__ApiLink0(FileSys,GetDriveCount)
#define	FileSys_GetFileCountEx(p1)		__ApiLink1(FileSys,GetFileCountEx,p1)
#define	FileSys_GetDirCountEx(p1)		__ApiLink1(FileSys,GetDirCountEx,p1)
#define	FileSys_GetFreeSpace(p1)		__ApiLink1(FileSys,GetFreeSpace,p1)
#define	FileSys_GetTotalSpace(p1)		__ApiLink1(FileSys,GetTotalSpace,p1)
#define	FileSys_GetDriveSpace(p1,p2)		__ApiLink2(FileSys,GetDriveSpace,p1,p2)
#define	FileSys_SetFileLevel(p1,p2)		__ApiLink2(FileSys,SetFileLevel,p1,p2)
#define	FileSys_GetFileLevel(p1)		__ApiLink1(FileSys,GetFileLevel,p1)
#define	FileSys_SetDirLevel(p1,p2)		__ApiLink2(FileSys,SetDirLevel,p1,p2)
#define	FileSys_GetDirLevel(p1)			__ApiLink1(FileSys,GetDirLevel,p1)
#define	FileSys_SaveFlashMem(p1)		__ApiLink1(FileSys,SaveFlashMem,p1)
#define FileSys_GetCreateTime(p1,p2,p3,p4)      __ApiLink4(FileSys,GetCreateTime,p1,p2,p3,p4)
#define FileSys_GetCreateDate(p1,p2,p3,p4)      __ApiLink4(FileSys,GetCreateDate,p1,p2,p3,p4)
#define	FileSys_DisableGC(p1)			__ApiLink1(FileSys,DisableGC,p1)
#define	FileSys_GetCurrentDir(p1,p2)		__ApiLink2(FileSys,ChangeDir,p1,p2)
#define	FileSys_Rename(p1,p2)			__ApiLink2(FileSys,Rename,p1,p2)
#define	FileSys_GetFileNum(p1)			__ApiLink1(FileSys,GetFileNum,p1)
#define	FileSys_GetDirNum(p1)			__ApiLink1(FileSys,GetDirNum,p1)


#define FileSys_FindFirst(p1,p2,p3)	__ApiLink3(FileSys,FindFirstDirFile,p1,p2,p3)
#define FileSys_FindNext(p1,p2)		__ApiLink2(FileSys,FindNextDirFile,p1,p2)
#define FileSys_FindPrev(p1,p2)		__ApiLink2(FileSys,FindPrevDirFile,p1,p2)

#endif	//	_BNSOFT__FILESYS_H_

