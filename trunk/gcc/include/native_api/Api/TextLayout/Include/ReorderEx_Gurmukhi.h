/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GURMUKHI LANGUAGE REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	그룹 : TextLayoutLib API
	구분 : 기본모듈
	등급 : 비공개
	버전 : 2.00
	일자 : 2010.05.03

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------	
	2010.05.03		.			v2.00	Create.
	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_REORDEREX_GURMUKHI_H_
#define		_LGE_REORDEREX_GURMUKHI_H_


#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport		extern
#else
#define	ReorderDllExport		__declspec(dllexport)
#endif
#endif


#ifdef	BNS_MAIN_VERSION
//	For Punjabi
extern A_CHAR	GURU_IVWN_Tbl[16];
extern A_CHAR	GURU_CWN_Tbl[37];
#endif



//-------------------------------------------------------------------------------------------------
//	Gurmukhi Code Range
#define		GURU_CODE(C)						((0x0A00 <= C) && (0x0A74 >= C))



//=================================================================================================
//	Punjabi Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define GURU_ALL_CONSONANT(C)				(((0x0A15 <= C) && (0x0A39 >= C)) || ((0x0A59 <= C) && (0x0A5E >= C)))
#define GURU_CONSONANT(C)					((0x0A15 <= C) && (0x0A39 >= C))
#define GURU_ADD_CONSONANT(C)				((0x0A59 <= C) && (0x0A5E >= C))
#define GURU_NUKTA_CONSONANT(C)				((C == 0x0A33) || (C == 0x0A36) ||((0x0A59 <= C) && (0x0A5E >= C)))
#define	GURU_BELOW_CONSONANT(C)				((C == 0x0A30) || (C == 0x0A35) || (C == 0x0A39))
#define GURU_SIGN(C)						(((0x0A01 <= C) && (C <= 0x0A03)) || ((0x0A70 <= C) && (C <= 0x0A71)))
#define GURU_INDEPENDENTVOWEL(C)			((0x0A05 <= C) && (C <= 0x0A14))
#define GURU_DEPENDENTVOWEL(C)				((0x0A3E <= C) && (C <= 0x0A4C))
#define GURU_PREFIX(C)						(C == 0x0A3F)
#define GURU_VIRAMA(C)						(C == 0x0A4D)
#define GURU_NUKTA(C)						(C == 0x0A3C)
#define GURU_YA(C)							(C == 0x0A2F)			//	Post Consonant
#define GURU_RA(C)							(C == 0x0A30)			//	Vattu
#define GURU_VA(C)							(C == 0x0A35)			//	Below Consonant
#define GURU_HA(C)							(C == 0x0A39)			//	Below Consonant
#define	GURU_BELOW_VOWEL(C)					((0x0A41 <= C) && (C <= 0x0A42))

//-------------------------------------------------------------------------------------------------
#define	IS_GURU_IVWN(pC)					(GURU_INDEPENDENTVOWEL(*pC) && GURU_NUKTA(*(pC+1)))
#define	Change_GURU_IVWN(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= GURU_IVWN_Tbl[*(pSrc) - 0x0A05];										\
											}
#define	IS_GURU_CWN(pC)						((GURU_CONSONANT(*pC) && GURU_NUKTA(*(pC+1))) && !GURU_NUKTA_CONSONANT(*pC))
#define	Change_GURU_CWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= GURU_CWN_Tbl[*(pSrc) - 0x0A15];										\
											}

#define	Change_GURU_BELOW_DVS(pSrc, pDst)	*pDst	= ((*(pSrc)) == 0x0A41 ? 0x0A76 : 0x0A77);

#define	IS_GURU_POST(pC)					(GURU_ALL_CONSONANT(*pC) && GURU_VIRAMA(*(pC+1)) && GURU_YA(*(pC+2)))
#define	IS_GURU_ADD_NUKTA_POST(pC)			((GURU_CONSONANT(*pC) && GURU_NUKTA(*(pC+1)) && GURU_VIRAMA(*(pC+2)) &&					\
											GURU_YA(*(pC+3))) && !GURU_NUKTA_CONSONANT(*pC))

#define	IS_GURU_BELOW(pC)					(GURU_ALL_CONSONANT(*pC) && GURU_VIRAMA(*(pC+1)) && GURU_BELOW_CONSONANT(*(pC+2)))
#define	IS_GURU_ADD_NUKTA_BELOW(pC)			((GURU_CONSONANT(*pC) && GURU_NUKTA(*(pC+1)) && GURU_VIRAMA(*(pC+2)) &&					\
											GURU_BELOW_CONSONANT(*(pC+3))) && !GURU_NUKTA_CONSONANT(*pC))

#define	Change_GURU_POST(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0x0A65;																\
											}
#define	Change_GURU_BELOW(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ((*(pSrc) == 0x0A30 || *(pSrc) == 0x0A4D) ? 0x0A62 : ((*(pSrc)) == 0x0A35 ? 0x0A63 : 0x0A64));\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Gurmukhi			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_GURMUKHI_H_