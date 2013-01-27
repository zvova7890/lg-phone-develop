/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	VIETNAMESE LANGUAGE REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	그룹 : TextLayoutLib API
	구분 : 기본모듈
	등급 : 비공개
	버전 : 2.00
	일자 : 2010.05.03

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------	
	2010.05.03		.			v2.00		Create.
	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_REORDEREX_VIETNAMESE_H_
#define		_LGE_REORDEREX_VIETNAMESE_H_


#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport	extern
#else
#define	ReorderDllExport	__declspec(dllexport)
#endif
#endif


#ifdef	BNS_MAIN_VERSION
ReorderDllExport	BYTE		CDBIndexTbl[112];
ReorderDllExport	A_CHAR		CDBTbl[2][5][256];
#endif


//-------------------------------------------------------------------------------------------------
//	Combining Dicritiacl Code
#define		DIACRITICAL_MARK_CODE(C)			((0x0300 <= (C)) && (0x036F >= (C)))



//=================================================================================================
//	Vietnamese Reordering and Rendering Rules
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	Combining Diacritical Marks(0x0300 ~ 0x036F)
#define	IS_CDM(pC)																					\
	(																								\
		DIACRITICAL_MARK_CODE(*((pC) + 1)) &&														\
		CDBIndexTbl[LOW_BYTE(*((pC) + 1))] != 0xFF &&												\
		HIGH_BYTE(*(pC)) < 2 &&																		\
		CDBTbl[HIGH_BYTE(*(pC))][CDBIndexTbl[LOW_BYTE(*((pC) + 1))]][LOW_BYTE(*(pC))]							\
	)

#define	Change_CDM(pSrc, pDst)																		\
	do																								\
	{																								\
		*(pDst)			= CDBTbl[HIGH_BYTE(*(pSrc))][CDBIndexTbl[LOW_BYTE(*((pSrc) + 1))]][LOW_BYTE(*(pSrc))];	\
		*((pDst) + 1)	= ZWC;																\
	} while(0)


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Vietnamese	(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_VIETNAMESE_H_
