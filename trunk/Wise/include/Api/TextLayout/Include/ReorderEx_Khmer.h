/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	KHMER LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_KHMER_H_
#define		_LGE_REORDEREX_KHMER_H_


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
extern A_CHAR	KHMR_COENG01_Tbl[52];
extern A_CHAR	KHMR_COENG02_Tbl[52];
extern A_CHAR	KHMR_COENG03_Tbl[52];	
extern A_CHAR	KHMR_PRE_Tbl[52];
extern A_CHAR	KHMR_CONSONANT_AA_Tbl[35];
extern A_CHAR	KHMR_CONSONANT_AU_Tbl[35];
#endif


//-------------------------------------------------------------------------------------------------
//	Khmer Code Range
#define		KHMER_CODE(C)						((0x1780 <= C) && (0x17DF >= C))



//=================================================================================================
//	Khmer Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define	KHMR_CONSONANT(C)					((0x1780 <= C) && (C <= 0x17B3))
#define	KHMR_CONSONANT_01(C)				(((0x1780 <= C) && (C <= 0x1782)) || ((0x1784 <= C) && (C <= 0x1787)) ||				\
											((0x1789 <= C) && (C <= 0x178C)) || ((0x178E <= C) && (C <= 0x1793)) ||					\
											((0x1795 <= C) && (C <= 0x1798)) || ((0x179B <= C) && (C <= 0x179D)) ||					\
											(0x179A0 <= C) || ((0x179A2 <= C) && (C <= 0x17B3)))
#define	KHMR_CONSONANT_02(C)				(C == 0x179A)
#define	KHMR_CONSONANT_03(C)				((C == 0x1783) || (C == 0x1788) || (C == 0x178D) || (C == 0x1794) || (C == 0x1799) ||	\
											(C == 0x179E) || (C == 0x179F) || (C == 0x17A1))

#define	KHMR_CONSONANT_BELOW(C)				((C == 0x17A1) || (C == 0x17A6) || ((0x17AB <= C) && (C <= 0x17AE)) || (C == 0x17B0))
#define	KHMR_CONSONANT_ABOVE(C)				((C == 0x17A8) || (C == 0x17AA) || (C == 0x17B1) || (C == 0x17B3))
#define	KHMR_CONSONANT_NYO(C)				(C == 0x1789)
#define	KHMR_CONSONANT_RO(C)				((C == 0xED7D) || (C == 0xEDB1) || (C == 0xEDE8))

#define	KHMR_VOWEL(C)						((0x17B4 <= C) && (C <= 0x17C5))
#define	KHMR_VOWEL_ABOVE(C)					((0x17B7 <= C) && (C <= 0x17BA))
#define	KHMR_VOWEL_BELOW(C)					((0x17BB <= C) && (C <= 0x17BD))
#define	KHMR_VOWEL_PREFIX(C)				(C == 0x17C1)

#define	KHMR_COENG(C)						(C == 0x17D2)
#define	KHMR_ROBAT(C)						(C == 0x17CC)
#define	KHMR_CONSONANT_SHIFTER(C)			((C == 0x17C9) || (C == 0x17CA))

#define	KHMR_AA_TRUE(C)						(((0xEE02 <= C) && (C <= 0xEE39)) || ((0xEE6D <= C) && (C <= 0xEEE2)) ||				\
											(C == 0xEE69) || (C == 0xED48))

#define	KHMR_AA_FALSE(C)					(((0xED56 <= C) && (C <= 0xED5E)) || ((0xED60 <= C) && (C <= 0xED61)) ||				\
											((0xED63 <= C) && (C <= 0xED7C)) || ((0xED7E <= C) && (C <= 0xEDB0)) ||					\
											((0xEDB2 <= C) && (C <= 0xEDCA)) || ((0xEDCE <= C) && (C <= 0xEDE7)) ||					\
											((0xEDE9 <= C) && (C <= 0xEE01)) || ((0xEE4B <= C) && (C <= 0xEE68)) ||					\
											((0xEE6A <= C) && (C <= 0xEE6C)) ||	(C == 0xED53) || (C == 0xEDCC) || (C == 0x0001))


#define	KHMR_COENG_CONSONANT(pC)			(KHMR_CONSONANT(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT(*(pC+2)))
#define	Change_KHMR_COENG(pSrc, pDst)		{																						\
												*pDst		= KHMR_CONSONANT_NYO(*pSrc) ? 0xEDCB : *pSrc;							\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= KHMR_CONSONANT_BELOW(*pSrc) ?											\
												KHMR_COENG02_Tbl[*(pSrc+2) - 0x1780] : KHMR_COENG01_Tbl[*(pSrc+2) - 0x1780];		\
											}

#define	KHMR_NYO_NYO(pC)					(KHMR_CONSONANT_NYO(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT_NYO(*(pC+2)))
#define	Change_KHMR_NYO_NYO(pSrc, pDst)		{																						\
												*pDst		= 0xEDCB;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0xEDCC;																\
											}
#define	KHMR_COENG_CON02(pC)				(KHMR_CONSONANT(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT_02(*(pC+2)))
#define	Change_KHMR_COENG_CON02(pSrc, pDst)	{																						\
												*pDst		= 0xED7D;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= *pSrc;																\
											}

#define	KHMR_COENG_COENG_CONSONANT(pC)		(KHMR_CONSONANT(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT(*(pC+2)) &&				\
											KHMR_COENG(*(pC+3)) && KHMR_CONSONANT(*(pC+4)))
#define	Change_KHMR_COENG_COENG(pSrc, pDst)	{																						\
												*pDst		= KHMR_CONSONANT_NYO(*pSrc) ? 0xEDCB : *pSrc;							\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= KHMR_CONSONANT_BELOW(*pSrc) ?											\
												KHMR_COENG02_Tbl[*(pSrc+2) - 0x1780] : KHMR_COENG01_Tbl[*(pSrc+2) - 0x1780];		\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= KHMR_CONSONANT_BELOW(*pSrc) ?											\
												KHMR_COENG03_Tbl[*(pSrc+4) - 0x1780] : KHMR_COENG02_Tbl[*(pSrc+4) - 0x1780];		\
											}
#define	KHMR_COENG_COENG_NYO(pC)			(KHMR_CONSONANT_NYO(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT_NYO(*(pC+2)) &&		\
											KHMR_COENG(*(pC+3)) && KHMR_CONSONANT(*(pC+4)))
#define	Change_KHMR_COENG_02_NYO(pSrc, pDst){																						\
												*pDst		= 0xEDCB;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0xEDCC;																\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= KHMR_COENG02_Tbl[*(pSrc+4) - 0x1780];									\
											}

#define	KHMR_COENG_COENG_CON02(pC)			(KHMR_CONSONANT(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT_01(*(pC+2)) &&			\
											KHMR_COENG(*(pC+3)) && KHMR_CONSONANT_02(*(pC+4)))
#define	Change_KHMR_COENG_02_CON02(pSrc, pDst){																						\
												*pDst		= 0xEDB1;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= *pSrc;																\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= KHMR_CONSONANT_BELOW(*pSrc) ?											\
												KHMR_COENG02_Tbl[*(pSrc+2) - 0x1780] : KHMR_COENG01_Tbl[*(pSrc+2) - 0x1780];		\
											}
#define	KHMR_COENG_CON02_COENG(pC)			(KHMR_CONSONANT(*pC) && KHMR_COENG(*(pC+1)) && KHMR_CONSONANT_02(*(pC+2)) &&			\
											KHMR_COENG(*(pC+3)) && KHMR_CONSONANT(*(pC+4)))
#define	Change_KHMR_COENG_02_COENG(pSrc, pDst){																						\
												*pDst		= 0xED7D;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= *pSrc;																\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= KHMR_CONSONANT_BELOW(*pSrc) ?											\
												KHMR_COENG02_Tbl[*(pSrc+4) - 0x1780] : KHMR_COENG01_Tbl[*(pSrc+4) - 0x1780];		\
											}

//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Khmer				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_KHMER_H_
