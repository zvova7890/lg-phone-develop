/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ERROR DEFINITION OF FILE SYSTEM

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_ERRORFS_H_
#define		_BNSOFT_ERRORFS_H_

#include	"ErrorDef.h"


typedef enum
{
	ERR_FS_FIRST						= ERR_FILESYS,		//	1500
	ERR_FS_INVALID_FILENAME,
	ERR_FS_CANNOT_CREATE,
	ERR_FS_LACK_OF_HANDLE,
	ERR_FS_NONEXIST_FILE,
	ERR_FS_ALREADY_OPENED,
	ERR_FS_LOWER_ACCESS_LEVEL,
	ERR_FS_INVALID_FP_POS,
	ERR_FS_LINEARFILE,
	ERR_FS_ACCESS_VIOLATION,
	ERR_FS_INVALID_BUFFER,
	ERR_FS_INVALID_HANDLE,
	ERR_FS_INVALID_SIZE,
	ERR_FS_LAST
} E_ERR_FS;

#endif	//	_BNSOFT_ERRORFS_H_
