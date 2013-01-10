/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FILE SYSTEM

	Copyright(c) 1997-2003 BNSoft Corp.
	Copyright(c)     -2003 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_FILESYS_H_
#define		_BNSOFT_FILESYS_H_

#include	"File.h"


//	FileSys Member Functions

extern E_GC_STATUS	FileSys_GarbageCollection (BOOL bAllDrive, BOOL bFullRegion);
extern BOOL		FileSys_IsExist           (T_CSTR pszFileName);
extern BOOL		FileSys_IsOpen            (H_FILE hFile);								//@
extern H_FILE		FileSys_Create            (T_CSTR pcszFileName, WORD wAttr, T_SIZE Size);
extern H_FILE		FileSys_Open              (T_CSTR pszFileName, int nMode);
extern BOOL		FileSys_Close             (H_FILE hFile);
extern T_POS		FileSys_Seek              (H_FILE hFile, long lPos, int nFlag);
extern T_NUM		FileSys_Read              (H_FILE hFile, BYTE* pBuf, T_SIZE Size);
extern T_NUM		FileSys_Write             (H_FILE hFile, BYTE* pBuf, T_SIZE Size);
extern BOOL		FileSys_Truncate          (H_FILE hFile, T_SIZE	Size);
extern T_SIZE		FileSys_GetSize           (H_FILE hFile);
extern T_POS		FileSys_GetPos            (H_FILE hFile);
extern T_ADDR		FileSys_GetAddr           (H_FILE hFile);
extern TFileEntry*	FileSys_GetEntry          (H_FILE hFile);
extern T_CSTR		FileSys_GetName           (H_FILE hFile);
extern T_CSTR		FileSys_GetExtension      (H_FILE hFile);
extern BOOL		FileSys_GetPath		 (H_FILE hFile, T_STR pBuf, T_SIZE BufSize);

extern BOOL		FileSys_MoveFile          (T_CSTR pszFileName, T_CSTR pszNewFileName);
extern BOOL		FileSys_CopyFile          (T_CSTR pszFileName, T_CSTR pszNewFileName);
extern BOOL		FileSys_RemoveFile        (T_CSTR pszFileName);
extern BOOL		FileSys_RemoveAllFiles	  (T_CSTR DirPath);
extern BOOL		FileSys_SearchFile        (T_CSTR pcszFileName);
extern TFileEntry*	FileSys_GetFileEntry      (T_CSTR pszFileName);
extern T_SIZE		FileSys_GetFileSize       (T_CSTR pszFileName);
extern T_ADDR		FileSys_GetFileAddress    (T_CSTR pszFileName);
extern T_CSTR		FileSys_GetFileName       (T_CSTR pszFileName);
extern T_CSTR		FileSys_GetFileExtension  (T_CSTR pszFileName);
extern BOOL		FileSys_GetFilePath       (T_CSTR pszFileName, T_STR pBuf, T_SIZE BufSize);

extern BOOL		FileSys_CreateDir         (T_CSTR pcszDirName);
extern BOOL		FileSys_ChangeDir         (T_CSTR pszDirName);
extern BOOL		FileSys_MoveDir           (T_CSTR pszDirName, T_CSTR pszNewDirName);
extern BOOL		FileSys_CopyDir           (T_CSTR pszDirName, T_CSTR pszNewDirName);
extern BOOL		FileSys_RemoveDir         (T_CSTR pcszDirName);
extern BOOL		FileSys_SearchDir         (T_CSTR pcszDirName);
extern BOOL		FileSys_Stat              (T_CSTR pcszFileName, TFStat* FStat);
extern BOOL		FileSys_FStat             (H_FILE hFile, TFStat* FStat);
extern T_ADDR		FileSys_GetAddr			  (H_FILE hFile);
extern QUAD		FileSys_FindFreeSpace	  (T_CSTR pcszPath, QUAD nSize, BOOL bLinear);

extern TDirAttr*	FileSys_GetDirAttr        (T_CSTR pszDirName);
extern T_DIRID		FileSys_GetDirID          (T_CSTR pszDirName);
extern T_CSTR		FileSys_GetDirName        (T_DIRID DirID);
extern BOOL		FileSys_GetDirPath        (T_DIRID DirID, T_STR pBuf, T_SIZE BufSize);
extern BOOL		FileSys_SetCurrentDirID   (T_DIRID DirID);
extern T_DIRID		FileSys_GetCurrentDirID   (void);
extern T_DIRID		FileSys_GetParentDirID    (T_DIRID DirID);

extern T_DRVID		FileSys_ChangeDrive       (T_DRVID DrvID);
extern T_DRVID		FileSys_GetCurrDriveID    (void);
extern TDrive*		FileSys_GetCurrDriveInfo  (void);

extern BOOL		FileSys_FindFirstFile     (T_CSTR DirPath, long* Iterator, TFStat* FStat);
extern BOOL		FileSys_FindNextFile      (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindPrevFile      (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindFirstDir      (T_CSTR DirPath, long* Iterator, TFStat* FStat);
extern BOOL		FileSys_FindNextDir       (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindPrevDir       (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindFirstDirFile  (T_CSTR DirPath, long* Iterator, TFStat* FStat);
extern BOOL		FileSys_FindNextDirFile   (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindPrevDirFile   (long Iterator, TFStat* FStat);
extern BOOL		FileSys_FindClose         (long Iterator);
extern TDrive*		FileSys_FindFirstDrive    (void);
extern TDrive*		FileSys_FindNextDrive     (void);
extern BOOL		FileSys_GetSearchHandle   (TSrchFS* pSrchFS);
extern BOOL		FileSys_SetSearchHandle   (TSrchFS* pSrchFS);

extern T_NUM		FileSys_GetFileCount      (T_CSTR pszDirName);
extern T_NUM		FileSys_GetDirCount       (T_CSTR pszDirName);
extern T_NUM		FileSys_GetDriveCount     (void);

extern T_NUM		FileSys_GetFileCountEx    (T_DIRID ParentDirID);
extern T_NUM		FileSys_GetDirCountEx     (T_DIRID ParentDirID);

extern UINT64		FileSys_GetFreeSpace      (T_CSTR Mount);
extern UINT64		FileSys_GetTotalSpace      (T_CSTR Mount);
extern T_SIZE		FileSys_GetDriveSpace     (T_DRVID DrvID, E_DRVSPACE enDrvSpaceType);

extern BOOL		FileSys_SetFileLevel      (T_CSTR pszFileName, E_FILELEVEL enFileLevel);
extern E_FILELEVEL	FileSys_GetFileLevel      (T_CSTR pszFileName);
extern BOOL		FileSys_SetDirLevel       (T_CSTR pszDirName, int nDirLevel);
extern int		FileSys_GetDirLevel       (T_CSTR pszDirName);

extern void		FileSys_SaveFlashMem      (T_CSTR pcszFileName);
extern QUAD	        FileSys_GetCreateTime     (T_CSTR pszFileName, BYTE* pHour, BYTE* pMinute, BYTE* pSecond);
extern QUAD	        FileSys_GetCreateDate     (T_CSTR pszFileName, int* pYear, int* pMonth, int* pDay);
extern BOOL		FileSys_DisableGC         (BOOL bEnable);
extern BOOL		FileSys_GetCurrentDir     (T_STR Buffer, T_SIZE Size);
extern BOOL		FileSys_Rename			  (T_CSTR old_pcszFileName,T_CSTR new_pcszFileName); 
extern QUAD 		FileSys_GetFileNum		(T_CSTR DirPath);
extern QUAD 		FileSys_GetDirNum		(T_CSTR DirPath);

extern BOOL		FileSys_GetCurrentDir(T_STR Buffer, T_SIZE Size);
extern void		FileSys_SetLastError(int ErrCode, M_CSTR pcszFile, T_NUM Line, M_CSTR pcszFunc);



#endif	//	_BNSOFT_FILESYS_H_

