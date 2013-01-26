/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LANGUAGE COMMON REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	그룹 : TextLayoutLib API
	구분 : 기본모듈
	등급 : 비공개
	버전 : 2.00
	일자 : 2010.05.03

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------	
	2010.05.03		.			v2.00 	Create.
	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef		_REORDEREX_COMMON_H_
#define		_REORDEREX_COMMON_H_


#include	"..\..\BasicApiLib\Include\Include.h"
#include	"..\..\BasicApiLib\Include\LnkList.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport		extern
#else
#define	ReorderDllExport		__declspec( dllexport )
#endif
#endif


//-------------------------------------------------------------------------------------------------
typedef long CharSet;
struct _CharTable
{
	A_CHAR			firstChar;
	A_CHAR			lastChar;
	const CharSet*	charSet;
};
typedef struct _CharTable CharTable;


typedef struct
{
	T_CSTR			pTxtBuf;
	T_STR			pDispBuf;
    QUAD*			pPositions;
	T_POS			StartPos;
	T_POS			EndPos;

	TLnkList*		pReorderExInfoLst;
} TReorderExAttr;


//=================================================================================================
//	Add to Indic & Khmer	by Sebastian
//=================================================================================================
typedef enum
{
	RESERVED				= 0,
	SIGN_ABOVE				= 1,
	SIGN_POST				= 2,
	INDEPENDENT_VOWEL		= 3,
	CONSONANT				= 4,
	CONSONANT_WITH_NUKTA	= 5,
	NUKTA					= 6,
	DEPENDENT_VOWEL			= 7,
	VIRAMA					= 8,
	AL_LAKUNA				= 9,
	CONSONANT2				= 10,
	CONSONANT3				= 11,
	COENG					= 12,
	CONSONANT_SHIFTER		= 13,
	ROBAT					= 14,
	KHMR_SIGN_POST			= 15,
	LENTH					= 16
} CharSetValues;


typedef enum {
	_xx = RESERVED,
	_sa = SIGN_ABOVE,
	_sp = SIGN_POST,
	_iv = INDEPENDENT_VOWEL,
	_ct = CONSONANT,
	_cn = CONSONANT_WITH_NUKTA,
	_nu = NUKTA,
	_dv = DEPENDENT_VOWEL,
	_vr = VIRAMA,
	_al = AL_LAKUNA,
	_c2	= CONSONANT2,
	_c3 = CONSONANT3,
	_co = COENG,
	_cs = CONSONANT_SHIFTER,
	_rb = ROBAT,
	_kp	= KHMR_SIGN_POST,
};


#ifdef	BNS_MAIN_VERSION
ReorderDllExport BYTE*	HighByteTbl[256];
ReorderDllExport BYTE*	NextHighByteTbl[256];

extern BYTE		Tbl_03[256];
extern BYTE		Tbl_06[256];
extern BYTE		Tbl_0E[256];
extern BYTE		Tbl_10[256];
//	ReorderDllExport	BYTE*		LeadByteTbl[256];
#endif



//=================================================================================================
//	Complexed Language
#define		COMPLEX_CODE(C)						(ARAB_CODE(C) || THAI_CODE(C) || DIACRITICAL_MARK_CODE(C) || LAO_CODE(C) || MYANMAR_CODE(C))

//-------------------------------------------------------------------------------------------------
//	Bide Script code range
//-------------------------------------------------------------------------------------------------
//	Arabic				: 0x0600-0x06FF, 0x0750-0x077F (Supplement)
//	Hebrew				: 0x0590-0x05FF
//-------------------------------------------------------------------------------------------------
#define		BIDI_CODE(C)						(((0x0600 <= C) && (0x06FF >= C)) || ((0x0750 <= C) && (0x077F >= C)) || ((0xFB00 <= C) && (0xFDFF >= C)) \
												|| ((0xFE70 <= C) && (0xFEFF >= C)) || ((0x0590 <= C) && (0x05FF >= C)))

//-------------------------------------------------------------------------------------------------
//	Indian Script code range
#define		INDI_CODE(C)						((0x0900 <= C) && (0x0DFF >= C))

//-------------------------------------------------------------------------------------------------
//	Zero Width Character
#define		ZWC									0x0001
#define		ZERO_W_CH(C)						(C == 0x0001)

#define		ZWNJ								0x200C
#define		ZWJ									0x200D

//-------------------------------------------------------------------------------------------------
//	글자 겹침의 예외코드 영역
#define		HIGH_BYTE(C)						(((C) >> 8) & 0xFF)
#define		LOW_BYTE(C)							((C) & 0xFF)
#define		CONTEXTUAL_FORM_FIRST(C)			((HighByteTbl [HIGH_BYTE(C)])		? *(HighByteTbl [HIGH_BYTE(C)] + LOW_BYTE(C)) : 0)
#define		CONTEXTUAL_FORM_NEXT(C)				((NextHighByteTbl[HIGH_BYTE(C)])	? *(NextHighByteTbl[HIGH_BYTE(C)] + LOW_BYTE(C)): 0)
#define		CONTEXTUAL_FORM(pC)					((CONTEXTUAL_FORM_FIRST(*pC)) || (CONTEXTUAL_FORM_NEXT(*(pC + 1))))


//-------------------------------------------------------------------------------------------------
//	Member Functions
extern BOOL		ReorderEx_Common_IsPostSign			(const CharTable *character_table, A_CHAR ch);
extern BOOL		ReorderEx_Common_IsAboveSign		(const CharTable *character_table, A_CHAR ch);
extern BOOL		ReorderEx_Common_IsConsonant		(const CharTable *character_table, A_CHAR ch);
extern CharSet	ReorderEx_Common_GetCharSet			(const CharTable *character_table, A_CHAR ch);
extern long		ReorderEx_Common_SyllableSearch		(const CharTable *character_table, const A_CHAR *chars, long SyllableLen);
extern BOOL		ReorderEx									(T_CSTR pTxtBuf, T_STR pDispBuf, QUAD* pPositions, T_POS StartPos, T_POS EndPos);
//-------------------------------------------------------------------------------------------------
#endif	//	_REORDEREX_COMMON_H_