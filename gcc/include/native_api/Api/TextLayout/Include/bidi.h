/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	BiDi LIBRARY

	Copyright(c)    -2004 LG Electronics Inc.

	그룹 : BASIC API
	구분 : Graphic
	등급 : 비공개
	버전 : 1.02
	일자 : 2005.05.30
	성명 : 길령환, 이택길
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   bidi.h

     Description: Bi-directional logic for T9 Demo.


********************************************************************************
********************************************************************************/

#ifndef		_BIDI_H_
#define		_BIDI_H_

#include	"..\..\Peanut\T9Core\T9env.h"
#include	"..\..\BasicApiLib\Include\LnkList.h"
#include	"..\..\BasicApiLib\Include\TypeDef.h"


//-------------------------------------------------------------------------------------------------
#ifndef T9U16
#define T9U16     unsigned T9S16        /* Unsigned 16 bit quantity           */
#endif /* !T9U16 */

#ifndef T9U32
#define T9U32     unsigned T9S32        //	Unsigned 32 bit quantity
#endif /* !T9U32 */


//-------------------------------------------------------------------------------------------------
//	Define a bit of uncompiled commenting.
#ifndef _uninitted
    #define _uninitted
#endif

#ifndef _WINDEF_
    #ifndef BOOL
		#ifndef TYPEDEF_BOOL
		// ??? ktkim Typedef에...
        #define BOOL    T9NUM
		#endif
    #endif

    #ifndef FALSE
        #define FALSE   0
    #endif
    #ifndef TRUE
        #define TRUE    1
    #endif
#endif


//-------------------------------------------------------------------------------------------------
//	We need Unicode characters whether this program has been compiled for single byte "symbols" or not.
#ifndef BISYMB
    #define BISYMB  T9U16
#endif


//-------------------------------------------------------------------------------------------------
typedef enum
{
	LBRK_CT_OP,                                                 // Opening Punctuation
	LBRK_CT_CL,                                                 // Closing Punctuation
	LBRK_CT_QU,                                                 // Ambiguous Quotation
	LBRK_CT_GL,                                                 // Non-breaking ("Glue")
	LBRK_CT_NS,                                                 // Non Starter
	LBRK_CT_EX,                                                 // Exclamation/Interrogation "!", "?" etc.
	LBRK_CT_SY,                                                 // Symbols Allowing Breaks /
	LBRK_CT_IS,                                                 // Infix Separator (Numeric) . ,
	LBRK_CT_PR,                                                 // Prefix (Numeric) $, ? ? etc.
	LBRK_CT_PO,                                                 // Postfix (Numeric) %, ? %, ?                                
	LBRK_CT_NU,                                                 // Numeric                                                      
	LBRK_CT_AL,                                                 // Ordinary Alphabetic and Symbol Characters                    
	LBRK_CT_ID,                                                 // Ideographic                                                  
	LBRK_CT_IN,                                                 // Zero Width Space                                             
	LBRK_CT_HY,                                                 // Hyphen                                                       
	LBRK_CT_BA,                                                 // Break Opportunity After                                      
	LBRK_CT_BB,                                                 // Break Opportunity Before                                     
	LBRK_CT_B2,                                                 // Break Opportunity Before and After                           
	LBRK_CT_ZW,                                                 // Zero Width Space                                             
	LBRK_CT_CM,                                                 // Attached Characters and Combining Marks                      

	LBRK_CT_CR,                                                 // carriage return                                              
	LBRK_CT_LF,                                                 // line feed                                                    
	LBRK_CT_CB,                                                 // Contingent Break Opportunity                                 
	LBRK_CT_SG,                                                 // Surrogates                                                   

	LBRK_CT_AI,                                                 // Ambiguous (Alphabetic or Ideographic)                        
	LBRK_CT_XX,                                                 // Unknown                                                      

	LBRK_CT_SA,                                                 // Complex Context (South East Asian)                           
	LBRK_CT_SP,                                                 // Space                                                        
	LBRK_CT_BK                                                  // mantatory break                                              
} LineBreakCharType;

//-------------------------------------------------------------------------------------------------
typedef enum
{
    /***    BIDI_CT_ON MUST be zero, code relies on ON = N = 0                                                                ***/
    /***    ON..AL must be 0..5, actually, too. Code relies on it.                                                            ***/
    BIDI_CT_ON = 0,                                             /* Other Neutral                                                */
    BIDI_CT_L,                                                  /* Left Letter                                                  */
    BIDI_CT_R,                                                  /* Right Letter                                                 */
    BIDI_CT_AN,                                                 /* Arabic Number                                                */
    BIDI_CT_EN,                                                 /* European Number                                              */
    BIDI_CT_AL,                                                 /* Arabic Letter (Right-to-left)                                */

    BIDI_CT_NSM,                                                /* Non-spacing Mark                                             */
    BIDI_CT_CS,                                                 /* Common Separator                                             */
    BIDI_CT_ES,                                                 /* European Separator                                           */
    BIDI_CT_ET,                                                 /* European Terminator (post/prefix e.g. $ and %)               */

    /***    resolved types                                                                                                    ***/
    BIDI_CT_BN,                                                 /* Boundary neutral (RLE... after explicit levels)              */

    /***    input types                                                                                                       ***/
    BIDI_CT_S,                                                  /* Segment Separator (TAB)            used only in L1           */
    BIDI_CT_WS,                                                 /* White space                        used only in L1           */
    BIDI_CT_B,                                                  /* Paragraph Separator (aka as PS)                              */

    /***    types for explicit controls - used only in X1-X9                                                                  ***/
    BIDI_CT_RLO,                                                /* Right to left override                                       */
    BIDI_CT_RLE,                                                /* Right to left embedding                                      */
    BIDI_CT_LRO,                                                /* Left to right override                                       */
    BIDI_CT_LRE,                                                /* Left to right embedding                                      */
    BIDI_CT_PDF,                                                /* Pop directional format                                       */

    BIDI_CT_RLM,                                                /* Right to left mark                                           */
    BIDI_CT_LRM,                                                /* Left to right mark                                           */

    /***    resolved types, also resolved directions                                                                          ***/
    BIDI_CT_N = BIDI_CT_ON,                                     /* alias, where ON, WS and S are treated as same                */
} BidiCharType;

//-------------------------------------------------------------------------------------------------
typedef enum
{
    BidiInfoOp_Probe,                                   /* by character widths or whatever, find length of line in given text   */
    BidiInfoOp_Line,                                    /* re-ordered text, direction, and cursor info (if any) given           */
    BidiInfoOp_Cnt
} BidiInfoOp;

//-------------------------------------------------------------------------------------------------
#define BIDI_AT_RtoL			((T9NUM)  0x80000000)		//	character position attribute: output right to left character
#define BIDI_AT_CHAR_MASK		((T9NUM)  0x00FFFFFF)		//	mask to get the index from a pPositions
//-------------------------------------------------------------------------------------------------
//	추가 정보에 대한 정의
#define	BIDI_PARA_START			((T9NUM)  0x40000000)
#define	BIDI_PARA_END			((T9NUM)  0x20000000)
#define	BIDI_L2R_LINE_START		((T9NUM)  0x10000000)
#define	BIDI_L2R_LINE_END		((T9NUM)  0x08000000)
#define	BIDI_R2L_LINE_START		((T9NUM)  0x04000000)
#define	BIDI_R2L_LINE_END		((T9NUM)  0x02000000)
#define	SYLLABLE_END			((T9NUM)  0x01000000)		// For Indic, Khmer...by Sebastian
//##define	BIDI_PARA_WHOLENUMBER	((T9NUM)  0x01000000)
//-------------------------------------------------------------------------------------------------
//	매크로
#define	POSITIONMASK			0x00FFFFFF
#define	ATTRIBMASK				0xFF000000
#define	BIDI_POS(Q)				(signed int)(Q & POSITIONMASK)
#define	BIDI_ATTR(Q)			(Q & ATTRIBMASK)
#define	BIDI_INVERSE			BIDI_AT_RtoL
//-------------------------------------------------------------------------------------------------
//	Text Mode 정의 (입력모드라고 봐도 되쥐)
#define	INVERSE_TEXT			1
#define	PLAIN_TEXT				0


//-------------------------------------------------------------------------------------------------
//	Information for use by *pCallBack().
typedef struct
{
	void				*p;			//	opaque pointer for arbitrary use by outside code
	const BISYMB		*pTxtBuf;	//	(_Line: reordered) text - *pTxtBuf is bidi logic controlled - contents change inter-callback.
	T9NUM				nBufLen;	//	number of characters in *pTxtBuf
	
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Information filled in for Line op.
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	BOOL				fLtoR;		//	is this _Line text fundamentally left to right (displayed flush/quad left)?

	//	This array, parallel to pTxtBuf, is passed containing the indices into the original
	//	BidiInfo.pTxtBuf array of each of the parallel characters in *pTxtBuf.
	//	For instance, using the testing values of upper-case-r-to-l, lower-l-to-r:
	//	If this were the original T9 text buffer:	"ABC abc DE",
	//	then this would be in *pTxtBuf:			"ED abc CBA",
	//	and  this would be in *pPositions:		"9874563210".
    const T9NUM			*pPositions;
	T9NUM				nBufIndex;
	T9U8				*pTextModes;
	BOOL				bInitTextMode;

	T_NUM				nParaNum;
	BYTE				nBiDiBaseLevel;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
} BidiCBInfo;



//-------------------------------------------------------------------------------------------------
//	Information filled in by outside logic before call to BidiOrderBuff().
typedef struct
{
	const BISYMB			*pTxtBuf;						//	the text to be reordered 
	T9NUM					nStart;							//	BiDi를 수행할 pTxtBuf의 StartPos.	
	T9NUM					nBufLen;						//	how many chars are in *pTxtBuf

	BOOL					fUseTestingValues;				//	Should type types of printable ASCII be the testing types?
	BidiCharType			nDefaultType;					//	BIDI_CT_N or BIDI_CT_L or BIDI_CT_R

	_uninitted T9U8			*pLevels;						//	work area: size >= nBufLen
	_uninitted BidiCharType	*pBidiTypes;					//	work area: size >= nBufLen
	_uninitted BISYMB		*pOutBuf;						//	work area: size >= nBufLen (for the reordered text)
	_uninitted T9NUM		*pPositions;					//	work area: size >= longest line length (direction attribute and reverse char indices)

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	pCallBack :
	//		_Probe	op returns length of text line: 1..nBufLen.
	//		_Line	op returns 0:stop_working		!0:continue.
	T9NUM					(*pCBGetCharNum)         (const BidiCBInfo *pInfo);
	T9NUM					(*pCBDisplay)            (const BidiCBInfo *pInfo);
	T9NUM					(*pCBMultiLine)          (const BidiCBInfo *pInfo);
	void					(*pCBSetNumberAlign)     (void* pSrcCtrl, BOOL bSet);
	void					*p;								//	opaque pointer for arbitrary use by outside code

	T9U8*					pTextModes;
	BOOL					bInitTextMode;

	T_NUM					nParaNum;
	BYTE					nBiDiBaseLevel;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	//-------------------------------------------------------------------------------------------------
	//	(PBTP)
	T9NUM					(*pCBGetNumOfObjectInLine)	(const BidiCBInfo *pInfo, T_POS *StartPos);
} BidiInfo;


#if defined(__cplusplus)
    extern "C" {
#endif



//-------------------------------------------------------------------------------------------------
extern BidiCharType			StrongestBidiType		(BidiCharType first_choice_type, BidiCharType fallback_type);
extern BidiCharType			GetBidiCharType			(BISYMB c, BOOL fUseTestingValues);
extern BidiCharType			GetBidiBuffType			(const BISYMB *pTxtBuf, T9NUM nBufLen, BOOL fUseTestingValues, BidiCharType nDefaultType);
extern void					BuffToBidiTypes			(_uninitted BidiCharType *pBidiTypes, const BISYMB *pTxtBuf, T9NUM nBufLen, BOOL fUseTestingValues);

//-------------------------------------------------------------------------------------------------
//	Put the contents of *pTxtBuf into *pOutBuf, possibly re-ordered according to bi-directional logic and characters.
//	Use *pBidiTypes and *pLevels as work areas.
//	pOutBuf, pBidiTypes, and pLevels must be at least nBufLen long.
//	Return the nBufLen equivalent for *pOutBuf.
extern void					BidiOrderBuff			(BidiInfo *pInfo);
extern T9U8					GetBidiBaseLevel		(const BISYMB *pTxtBuf, T9NUM nBufLen, BOOL fUseTestingValues);		
extern LineBreakCharType	GetLineBreakCharType	(BISYMB c);


//-------------------------------------------------------------------------------------------------
//	(PBTP)
extern void					BiDi_Reorder			(BidiInfo *pInfo);
extern void					BiDi_NoReorder			(BidiInfo *pInfo);
extern BOOL					BiDi_IsBiDiRequired		(BidiInfo *pInfo);
extern BOOL					BiDi_IsBiDiStrongType	(BISYMB ch, BOOL fUseTestingValues);

//-------------------------------------------------------------------------------------------------










#if defined(__cplusplus)
    }
#endif

#endif



/* eof */
