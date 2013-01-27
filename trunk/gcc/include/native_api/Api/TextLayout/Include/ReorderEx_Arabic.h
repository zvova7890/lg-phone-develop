/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ARABIC LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_ARABIC_H_
#define		_LGE_REORDEREX_ARABIC_H_

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
extern A_CHAR	ArabFormTbl[179][4];
extern A_CHAR	ArabLigatureFormTbl[6][4];
extern A_CHAR	ArabLigatureExFormTbl[6];
#endif

//-------------------------------------------------------------------------------------------------
//	Arabic Script code range
#define		ARABIC(C)							(ARAB_CODE(C) || ARAB_OVERRAP(C))
#define		ARAB_CODE(C)						(((0x0621 <= C) && (0x064A >= C)) || ((0x066E <= C) && (0x066F >= C)) || ((0x0671 <= C) && (0x06D3 >= C)))
#define		ARAB_OVERRAP(C)						(((0x0610 <= C) && (0x061A >= C)) || ((0x064B <= C) && (C <= 0x065E)) || (C == 0x0670)|| \
												((0x06D6 <= C) && (C <= 0x06DC)) || ((0x06DF <= C) && (C <= 0x06E4)) || ((0x06E7 <= C) && \
												(C <= 0x06E8)) || ((0x06EA <= C) && (C <= 0x06ED)))
#define		ARAB_CODEEX(C)						(((0xFB50 <= C) && (0xFDFF >= C)) || ((0xFE70 <= C) && (0xFEFF >= C)))

#define		ARAB_HAMZA(C)						(C == 0x0621)
#define		ARAB_SPECIAL(C)						((C == 0x0621) || (C ==0x0622) || (C ==0x0623) || (C ==0x0624) || (C ==0x0625) || (C ==0x0627) || (C ==0x0629) ||\
												(C ==0x062F) || (C ==0x0630) || (C ==0x0631) || (C ==0x0632) || (C ==0x0648) || (C ==0x0649) || (C ==0x0671) ||\
												(C ==0x0672) || (C ==0x0673) || (C ==0x0674) || (C ==0x0675) || (C ==0x0676) || (C ==0x0677) || (C ==0x0678) ||\
												(C ==0x0688) || (C ==0x0689) || (C ==0x068A) || (C ==0x068B) || (C ==0x068C) || (C ==0x068D) || (C ==0x068E) ||\
												(C ==0x068F) || (C ==0x0690) || (C ==0x0691) || (C ==0x0692) || (C ==0x0693) || (C ==0x0694) || (C ==0x0695) ||\
												(C ==0x0696) || (C ==0x0697) || (C ==0x0698) || (C ==0x0699) || (C ==0x06BA) || (C ==0x06C0) || (C ==0x06C4) ||\
												(C ==0x06C5) || (C ==0x06C6) || (C ==0x06C7) || (C ==0x06C8) || (C ==0x06C9) || (C ==0x06CA) || (C ==0x06CB) ||\
												(C ==0x06CD) || (C ==0x06CF) || (C ==0x06D1) || (C ==0x06DC) || (C ==0x06D3))
#define		ARAB_QUESTION_MARK					0x061F

//=================================================================================================
//	Arabic Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define		IS_LIGATURE(pC)						((*(pC) == 0x0644) && ((*(pC+1) == 0x0622) || (*(pC+1) == 0x0623) || (*(pC+1) == 0x0625) || (*(pC+1) == 0x0627)))
#define		IS_OVERLAP(pC)						((((*(pC) >= 0x0621) && (*(pC) <= 0x064A)) || ((*(pC) >= 0x066E) && (*(pC) <= 0x06D3))) && ((*(pC+1) >= 0x064B) && (*(pC+1) <= 0x065E)))
#define		IS_LIGATURE_Ex(pC)					((((*(pC) >= 0x064C) && (*(pC) <= 0x0650)) && (*(pC+1) == 0x0651)) || ((*(pC) == 0x0651) && (*(pC+1) == 0x0670)))
#define		IS_LIGATUREPLUS(pC)					((*(pC) == 0x0644) && ((*(pC+1) == 0x0622) || (*(pC+1) == 0x0623) || (*(pC+1) == 0x0625) || (*(pC+1) == 0x0627))		\
												&& ((((*(pC+2) >= 0x064C) && (*(pC+2) <= 0x0650)) && (*(pC+3) == 0x0651)) || ((*(pC+2) == 0x0651) && (*(pC+3) == 0x0670))))
#define		IS_LIGATUREPOINT(pC)				((*(pC) == 0x0644) && ((*(pC+1) == 0x0622) || (*(pC+1) == 0x0623) || (*(pC+1) == 0x0625) || (*(pC+1) == 0x0627))		\
												&& ((*(pC+2) >= 0x064B) && (*(pC+2) <= 0x065E)))
#define		IS_BASELIGATURE_EX(pC)				((((*(pC) >= 0x0621) && (*(pC) <= 0x064A)) || ((*(pC) >= 0x066E) && (*(pC) <= 0x06D3))) && ((((*(pC+1) >= 0x064C) && (*(pC+1) <= 0x0650)) && (*(pC+2) == 0x0651)) || ((*(pC+1) == 0x0651) && (*(pC+2) == 0x0670))))
#define		IS_OVERLAP2(pC)						((((*(pC) >= 0x0621) && (*(pC) <= 0x064A)) || ((*(pC) >= 0x066E) && (*(pC) <= 0x06D3))) && ((*(pC+1) >= 0x064B) && (*(pC+1) <= 0x065E)) && ((*(pC+2) >= 0x064B) && (*(pC+2) <= 0x065E)))
#define		IS_LIGATUREPOINT2(pC)				((*(pC) == 0x0644) && ((*(pC+1) == 0x0622) || (*(pC+1) == 0x0623) || (*(pC+1) == 0x0625) || (*(pC+1) == 0x0627))		\
												&& ((*(pC+2) >= 0x064B) && (*(pC+2) <= 0x065E)) && ((*(pC+3) >= 0x064B) && (*(pC+3) <= 0x065E)))
//	Arabic Ligature Macro
#define	IS_ARAB_LIGATURE(pC)					((*(pC) == 0x0644) && ((*(pC+1) == 0x0622) || (*(pC+1) == 0x0623) || (*(pC+1) == 0x0625) || (*(pC+1) == 0x0627)))
#define	Change_ARAB_LIGATURE_ISOL(pSrc, pDst)	{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ArabLigatureFormTbl[*(pSrc+1) - 0x0622][0];						\
												}
#define	Change_ARAB_LIGATURE_INIT(pSrc, pDst)	{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ArabLigatureFormTbl[*(pSrc+1) - 0x0622][2];						\
												}
#define	Change_ARAB_LIGATURE_MEDI(pSrc, pDst)	{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ArabLigatureFormTbl[*(pSrc+1) - 0x0622][3];						\
												}
#define	Change_ARAB_LIGATURE_FINL(pSrc, pDst)	{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ArabLigatureFormTbl[*(pSrc+1) - 0x0622][1];						\
												}
//-------------------------------------------------------------------------------------------------
//	Arabic Presentation form Macro
#define	Change_ARAB_ISOL(pSrc, pDst)			*(pDst)		= ArabFormTbl[*(pSrc) - 0x0621][0]
#define	Change_ARAB_INIT(pSrc, pDst)			*(pDst)		= ArabFormTbl[*(pSrc) - 0x0621][2]
#define	Change_ARAB_MEDI(pSrc, pDst)			*(pDst)		= ArabFormTbl[*(pSrc) - 0x0621][3]
#define	Change_ARAB_FINL(pSrc, pDst)			*(pDst)		= ArabFormTbl[*(pSrc) - 0x0621][1]
//-------------------------------------------------------------------------------------------------
#define	IS_ARAB_OVERRAP(pC)						ARAB_OVERRAP(*(pC))
#define	IS_ARAB_CODE(pC)						ARAB_CODE(*(pC))
//-------------------------------------------------------------------------------------------------
//	Points form ISO 8859-6 Ligature						2007.11.09		by Sebastian
#define	IS_ARAB_LIGATURE_Ex(pC)					((((*(pC) >= 0x064C) && (*(pC) <= 0x0650)) && (*(pC+1) == 0x0651)) ||				\
												((*(pC) == 0x0651) && (*(pC+1) == 0x0670)))
#define	Change_ARAB_LigatureExForm(pSrc, pDst)	{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ArabLigatureExFormTbl[*(pSrc) - 0x064C];							\
												}
//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Arabic				(TReorderExAttr* pAttr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_ARABIC_H_
