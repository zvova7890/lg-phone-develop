/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	WISE TEXT LAYOUT

	Copyright(c) 2007 -	 LGE Inc.

	그룹 : TextLayout
	구분 : LAYOUT
	등급 : 공개/비공개																						
	버전 : 2.00

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef		_LGE_WLAYOUT_H_
#define		_LGE_WLAYOUT_H_

#include	"bidi.h"
#include	"AdaptWLayout.h"
#include	"..\..\BasicApiLib\Include\Include.h"
#include	"..\..\BasicApiLib\Include\LnkList.h"
#include	"..\..\BasicApiLib\Include\SysHeap.h"
#include	"..\..\BasicApiLib\Include\UnicodeLib.h"
#include	"..\..\BasicApiLib\Include\AdaptSys.h"
#include	"..\..\BasicApiLib\Include\GrDevInfo.h"
#include	"..\..\BasicApiLib\Include\FileSys.h"


//-------------------------------------------------------------------------------------------------
typedef	void (*pfnCallback) (QUAD, T_POS, T_POS);
//-------------------------------------------------------------------------------------------------
#define		WLAYOUTRGB(R,G,B)				WLayout_RGBColor(R,G,B)
#define		WLAYOUT_OPAQUE					0
#define		WLAYOUT_TRANSPARENT				1
#define		WLAYOUT_SWAP(TYPE,A,B)			{ TYPE C = A; A = B; B = C; }

//-------------------------------------------------------------------------------------------------
#define		LAYOUT_ASSERT(pCtrl,RET)										\
	do																		\
	{																		\
		if ((pCtrl) == NULL)												\
		{																	\
			return (RET);													\
		}																	\
	} while(0)
//-------------------------------------------------------------------------------------------------

#define		LAYOUT_SAFE_FREE(pMem)											\
	do																		\
	{																		\
		if (pMem)															\
		{																	\
			WLayout_Heap_Free(pMem);										\
			(pMem) = NULL;													\
		}																	\
	}	while(0)															 

#define		WLAYOUT_CURSORUP			0x00000001
#define		WLAYOUT_CURSORDOWN			0x00000002
#define		WLAYOUT_CURSORLEFT			0x00000003
#define		WLAYOUT_CURSORRIGHT			0x00000004

#define		WLAYOUT_LEFTDIR				0x00000000
#define		WLAYOUT_RIGHTDIR			0x00000001

//-------------------------------------------------------------
#define		WLAYOUT_FOCUSED				0x00000001
#define		WLAYOUT_UNFOCUSED			0x00000000
#define		WLAYOUT_THEMECOLOR			0x00000002

//-------------------------------------------------------------
#define		LAYOUTCSR_NONE				0x00000000
#define		LAYOUTCSR_VERTICAL			0x00000001
#define		LAYOUTCSR_FULLBOX			0x00000002
#define		LAYOUTCSR_HALFBOX			0x00000003
#define		LAYOUTCSR_MINIBOX			0x00000004
#define		LAYOUTCSR_CHARBLINKING		0x00000080

//-------------------------------------------------------------
#define		CURSOR_UP					0x00000001
#define		CURSOR_DOWN					0x00000002
#define		CURSOR_LEFT					0x00000003
#define		CURSOR_RIGHT				0x00000004

//-------------------------------------------------------------------------------------------------
//	EditCtrl의 SeparatorType 종류
#define		LAYOUTSEP_NONE				0x00000000
#define		LAYOUTSEP_LINE				0xFFFFFFFF
#define		LAYOUTSEP_DASHLINE			0xEEEEEEEE
#define		LAYOUTSEP_DOTLINE			0xAAAAAAAA

//-------------------------------------------------------------------------------------------------
#define		LAYOUT_CHAR					0x00000000
#define		LAYOUT_OBJECT				0x00000001

#define		TEXT_ENDSYMBOL				0x001C

#define		SELECTED					0x00000001
#define		UNSELECTED					0x00000000
		
//-------------------------------------------------------------------------------------------------
#define		LAYOUT_FONT_NOMAL			0x00000000
#define		LAYOUT_FONT_INVERSE			0x80000000			//	텍스트를 반전시켜서 출력시킨다.
#define		LAYOUT_FONT_BOLD			0x40000000
#define		LAYOUT_FONT_UNDERLINE		0x20000000
#define		LAYOUT_FONT_ITALIC			0x10000000
#define		LAYOUT_FONT_BOLDITALIC		LAYOUT_FONT_BOLD | LAYOUT_FONT_ITALIC
#define		LAYOUT_FONT_OUTLINE			0x08000000
#define		LAYOUT_FONT_STRIKEOUT		0x04000000

//-------------------------------------------------------------------------------------------------
//	Layout Style
#define		LAYOUTSTY_MULTILINE			0x00008000			//	여러줄 편집
#define		LAYOUTSTY_ENDSYMBOL			0x00004000			//	활성화된 경우 줄의 끝에 CR표시를 함
#define		LAYOUTSTY_RIGHT				0x00001000			//	오른쪽에서 입력. (숫자만 입력됨)
#define		LAYOUTSTY_COMMA				0x00000800			//	3자리마다 ','표시
#define		LAYOUTSTY_RICHTEXT			0x00000400			//	각 문자마다 정의한 color대로 출력함 
#define		LAYOUTSTY_BIDI				0x00000200			//	Bidi Algorithm을 이용함
#define		LAYOUTSTY_HIDDEN			0x00000040			//	'*'로 표시
#define		LAYOUTSTY_WORDBREAK			0x00000010			//	한 단어를 가능한 한 붙여서 출력
#define		LAYOUTSTY_NORMAL			0x00000000
#define		LAYOUTSTY_NOCURSOR			0x00000100			//	커서를 보여주지 않음 (Cursor Blinking으로 인하여 bShowCursor 판단과 다름)	

#define		LAYOUT_ENDSYMBOL			0x001C
#define		LEFFECT_NORMAL				0x00000000
#define		LEFFECT_INVERSE				0x80000000			//	텍스트를 반전시켜서 출력시킨다.
#define		LEFFECT_BOLD				0x40000000			//	텍스트를 볼드체로 출력한다.
#define		LEFFECT_UNDERLINE			0x20000000			//	텍스트를 출력한 후 밑줄을 긋는다.
#define		LEFFECT_ITALIC				0x10000000			//	텍스트를 이텔릭체로 출력한다.
#define		LEFFECT_OUTLINE				0x08000000			//	외곽선 폰트로 출력한다.
#define		LEFFECT_STRIKETHROUGH		0x04000000			//	텍스트에 취소선을 그린다(REditCtrl에만 적용).
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	아래정의는 얼라인의 중복을 막기위해 비트 마스킹을 사용하지 않는다.
//	REditCtrl의 문자외의 Object의 Layout의 종류 (TObjAttr의 Effect에 저장된다 최대값 255)
#define		LEFFECT_ALIGN_DEFAULT		0x00000000			//	Object를 일반문자와같이 문자옆에 그려준다.
#define		LEFFECT_ALIGN_LEFT			0x00000001			//	Object를 문자와 달리 독립된 형태로 Left Align속성을 주어 그린다.
#define		LEFFECT_ALIGN_CENTER		0x00000002			//	Object를 문자와 달리 독립된 형태로 Center Align속성을 주어 그린다.
#define		LEFFECT_ALIGN_RIGHT			0x00000004			//	Object를 문자와 달리 독립된 형태로 Right Align속성을 주어 그린다.
#define		LEFFECT_ALIGN_TOP			0x00000008
#define		LEFFECT_ALIGN_MIDDLE		0x00000010
#define		LEFFECT_ALIGN_BOTTOM		0x00000020
#define		LEFFECT_ALIGN_NONE			0x00000040

typedef enum
{
	LAYOUTCOLOR_TEXT					= 0,
	LAYOUTCOLOR_MULTILINE,
	LAYOUTCOLOR_BLOCK,
	LAYOUTCOLOR_BLOCKFONT,
	LAYOUTCOLOR_STRIKE,
	LAYOUTCOLOR_UNDERLINE,
	LAYOUTCOLOR_PREDICTION
} EItem;

//-------------------------------------------------------------------------------------------------
//	Get FontStyle시 FontEffect/Size/Color등을 구분하기 위해서 사용.
typedef	enum
{												
	GETMODE_FONTEFFECT					= 0,
	GETMODE_FONTSIZE,
	GETMODE_FONTCOLOR	
} E_GETMODE;

//-------------------------------------------------------------------------------------------------
enum
{
	L2R		= 0,
	R2L
};

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_POS				DispCursorPos;
	T_POS				CursorPos;							//	Real 커서의 위치
	T_POS				CursorX;							//	커서의 X 위치. (픽셀단위)
	T_POS				CursorY;							//	커서의 Y 위치. (라인단위)
	T_POS				CursorBX;							//	커서의 기본 X 위치. (픽셀단위)
	T_POS				DrawCursorPos;
	BOOL				bForeCursor;						//	커서를 문자의 앞에 표시하는지, 뒤에 표시하는지의 여부
	int					CursorType;
	BOOL				bShowCursor;						//	커서가 보이는 지의 여부
	TRect				CursorRect;
	BOOL				bCharBlinking;
	BOOL				bInverse;
	TRect				rcCursorDrawRgn;
	TPoint				ptOriginOfCursor;
} TCursor;


typedef	struct TParaInfo TParaInfo;

//-------------------------------------------------------------------------------------------------
//	TLineInfo
typedef	struct
{
	TDLnkObj			DLnkObj;
	T_POS				StartPos;							//	startIndex;v
	T_POS				EndPos;								//	endIndex;v
	T_SIZE				Width;								//	라인의 스트링 길이AdvanceBox.X2;v 라인의 width
	T_SIZE				Height;								//	AdvanceBox.Y2;v
	int					Ascent;								//	BaseLine;x
	BOOL				bLtoR;								//	LtoR, RtoL 라인지 구분;x
	BOOL				bLayout;							//	문자가 아닌 Object로만 이루어져 Layout을 적용할 것인지 구분x
	int					LineFlags;
	BYTE				nBiDiBaseLevel;
	TRect				BoundingBox;
	TPoint				LineOrigin;

	//	(PBTP)
	TParaInfo*			pParaInfo;							//	Parent ParaInfo Node.
	BOOL				bBiDiValid;							//	BiDi Reodering 결과가 Valid 한지를 표시.
} TLineInfo;


//-------------------------------------------------------------------------------------------------
//	TParaInfo - Paragraph단위로 관리하기 위한 구조체이다.
struct TParaInfo
{
	TDLnkObj			DLnkObj;

	TLineInfo*			pStartLine;
	TLineInfo*			pEndLine;

	BOOL				bIsBiDiRequired;					//	BiDi Reordering을 필요로 하는 Paragraph인지를 표시 (L2R 문자들로만 구성 => 필요없음)
	BYTE				nBiDiBaseLevel;
	
	T_POS				BiDiStartPos;						//	BiDi Algorithm이 적용되어야 하는 영역에 StartPos & EndPos.
	T_POS				BiDiEndPos;
} ;


//-------------------------------------------------------------------------------------------------
//	Layout Color List의 정의 
typedef struct
{
	T_COLOR				TextColor;
	T_COLOR				MultiLineColor;
	T_COLOR				BlockColor;
	T_COLOR				BlockFontColor;
	T_COLOR				StrikeColor;
	T_COLOR				UnderlineColor;
	T_COLOR				PredictionColor;					// Standard UI 시나리오 적용
} TLayoutColor;

//-------------------------------------------------------------------------------------------------
//	TMultiLine
typedef struct
{
	BOOL				IsUse;
	int					LineGap;							//	여러줄 모드의 줄간 간격
	T_COLOR				LineColor;
	int					LineType;
	int					Thickness;
	T_SIZE				Indent;
} TMultiline;

//-------------------------------------------------------------------------------------------------
//	Charactor Object Default Style 구조체 정의
//	Face, Size, Style(Bold, Normal, Italic), Underline, Strike 정보를 가지고 있음.
typedef struct
{
	int					FaceID;								//	폰트의 종류
	int					Size;								//	폰트의 크기
	QUAD				Effect;								//	Bold, Normal, Italic, Underline, Strike
	T_COLOR				TextColor;							//	글자의 색
	T_COLOR				BkColor;							//	Outline 폰트를 그릴때의 배경색
	T_COLOR				UnderlineColor;						//	밑줄을 그릴 Effect가 있으면 이때 그릴 색정보
	T_COLOR				StrikeColor;						//	취소선을 그릴 Effect가 있으면 이때 그릴 색정보
	T_COLOR				InverseColor;						//	글자또는 Object가 선택될때, 반전될 색
} TFontParams;

//--------------------------------------
typedef struct
{
	int					Align;								//	Object를 왼쪽, 중간, 오른쪽 에 정렬을 원할때 사용한다. (Text의 Align과는 다르다.)
	T_INDEX				ImageID;							//	Object의 종류에 따라서 Callback에서 구분 지을수 있는 ID 값이다.
	int					Effect;
	int					Left;								//	Object를 지정된 위치에 그릴때 사용할 Left 변수 (현재는 사용하지 않음)
	int					Top;								//	Object를 지정된 위치에 그릴때 사용할 Top 변수  (현재는 사용하지 않음)
	int					Width;								//	Object의 Width
	int					Height;								//	Object의 Height
	pfnCallback			pfnDrawObj;							//	Object를 그릴때, 사용할 Callback 함수
	T_COLOR				UnderlineColor;						//	밑줄을 그릴 Effect가 있으면 이때 그릴 색정보
	T_COLOR				StrikeColor;						//	취소선을 그릴 Effect가 있으면 이때 그릴 색정보
	T_COLOR				InverseColor;						//	글자또는 Object가 선택될때, 반전될 색
} TObjParams;

//--------------------------------------
typedef	union
{
	TFontParams			Font;
	TObjParams			Image;
} unObj ;

//---------------------------------------
typedef	struct
{
	BYTE				Type;
	unObj				Attr;
} TObjAttr2;

//-------------------------------------------------------------------------------------------------
//	Text의 Font / Object 정보를 필요로 할때, 읽어 갈수 있도록 제공
typedef struct
{
	int					nType;
	A_CHAR				Obj;					
	T_SIZE				Width;
	T_SIZE				Height;
	T_SIZE				xAdvance;
	T_SIZE				Ascender;
	T_SIZE				Descender;
	T_SIZE				KerningX;
} TObjInfo;

//-------------------------------------------------------------------------------------------------
//	Object Attribute, Color buffer copy, paste 시에 사용.
typedef struct
{
	T_STR				pszStrBuf;
	TObjAttr2*			pAttrBuf;							//	동일한 특성을 갖는 폰트가 삽입된다.
	T_SIZE				BufSize;
} TEditBuf;

//-------------------------------------------------------------------------------------------------
//	For Bidirectional CallBack Info
typedef	struct
{
	void*				pLayout;
	TLineInfo*			pPrevLineInfo;
	TLineInfo			LineInfo;
	BOOL				bNumAlignRight;						//	BIDI 스타일에서 모두 숫자인 문자열의 Right Align 여부
} TCBInfo_Rich;


//-------------------------------------------------------------------------------------------------
typedef	enum
{												
	TEXTMODI_NONE		= 0,
	TEXTMODI_INSERT,
	TEXTMODI_DELETE
} E_TEXTMODITYPE;

//20101110 dooyoung.hwang@lge.com(torch) Underline Selection 지원 [START]
typedef enum
{
	SELECTIONDRAW_RECT = 0,	
	SELECTIONDRAW_UNDERLINE,
	SELECTIONDRAW_ROUNDRECT
} E_SELECTIONDRAW;
//20101110 dooyoung.hwang@lge.com(torch) [END]

//-------------------------------------------------------------------------------------------------
typedef	struct
{
	E_TEXTMODITYPE		ModiType;							//	Text의 Modifying Type을 표시.
	
	T_POS				StartPos;							//	Real Buffer에 변경된 String의 시작과 끝. xxx[Start] ~ xxx[End]
	T_POS				EndPos;

	T_POS				ShiftPos;
	T_NUM				nShiftLen;							//	Shift 할 길이.
	BOOL				bShiftRight;						//	Right or Left Shift Type을 지정.
} TTextModifyInfo;


//-------------------------------------------------------------------------------------------------
//	EditCtrl 구조체 정의
typedef struct
{
	T_CSTR				pcszStr;							//	편집문자열 버퍼 포인터. (NULL일 수도 있다.)
	TObjAttr2*			pObjAttr;							//	Object Attribute 버퍼
	T_NUM				MaxChar;							//	편집할 수 있는 문자열의 길이 (NULL을 제외한 크기)
	T_POS				SelPos;
	T_SIZE				SelSize;
	BOOL				bAssignedBuf;
	T_SIZE				BufSize;
	int					Direction;
	int					Language;
	TFontParams			DefFontParam;						//	전체에 적용될 Default 설정값.(Rich의 경우에도 각각의 따로 설정 하지 않으면 Default를 따라 간다.)
	
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	For bidi
	BOOL				bBidiStyle;							//	BIDI Style 셋팅함.
	BYTE*				pSelect;							//	BIDI Style일 경우 Select위치를 Display 기준으로 세팅한다.
	T_CSTR				pDispStr;							//	Display String 버퍼.
	QUAD*				pDispAttr;							//	Display Attribute 버퍼(Original ObjAttr을 Display 순서에 맞게 버퍼에 유지)
	T_POS				DispCursorPos;						//	Display 커서의 위치, Bidi를 사용하지 않을때 CursorPos와 같다.
	QUAD*				pPositions;							//	BIDI Reordering 이후, 재 배치된 Real Buffer 상의 Character들에 Index 값.
	BYTE*				pLevels;							//	BIDI Reordering 이후, 각 Character에 대한 BIDI Algorithm 상에 Level 값.
	BidiInfo			BidiInfo;
	TCBInfo_Rich		CBInfo;
	//---------------------------------------------------------------------------------------------
	//	For T9 Prediction Gray Display									2009.06.27	by Sebastian
	T_POS				PendingStartPos;
	T_POS				PendingEndPos;
	T_SIZE				PendingSize;
	BOOL				bPendingSelBorder;					//	A Class Touch 2.n 시나리오 -- 2010.04.26 by bean
	E_SELECTIONDRAW		SelectionDrawType;
} TText;


//-------------------------------------------------------------------------------------------------
//	Layout 구조체 정의
typedef struct
{
	TText*				pText;
	TRect				Range;								// 	라인의 실제 영역너비.
	QUAD				Style;								//	Rich 인지, Bidi
	int					State;
	QUAD				AlignType;
	BOOL				TextDirection;
	TLnkList*			pParaInfoLst;						//	Para Info List
	TLnkList*			pLineInfoLst;						//	Line Info List (Bidi를 사용하는 경우 Display 버퍼에 적용된다
	TMultiline			Multiline;
	BOOL				bShowSelection;
	TCursor				Cursor;
	TLayoutColor		LayoutColor;
	
	TRect				Scroll;								//	x scroll or y scroll이 발생시에 그려야 하는 문자열의 시작점까지의 위치
	int					CurrDirection;						// 현재 문장의 진행방향을 설정한다.
	T_POS				QuesMarkPos;						// Question Mark Pos.
	BOOL				bLeftQuesMark;						// EditMode방향과, 문장의 마지막에 ? 올때 예외처리를 위함.
	BOOL				bShowEndSymbol;

	//20110106 dooyoung.hwang@lge.com(torch) MultiLine Editor의 경우 기본적으로 Partial Draw이지만
	//이 Flag가 FALSE일 시 WriteLine에서 Partial Draw를 수행하지 않는다.
	BOOL				bLineDrawPartial;					
									
	TTextModifyInfo		TextModifyInfo;
} TLayout;

//20101125 dooyoung.hwang@lge.com(torch) These chars have biditype of BIDI_CT_B. Used for LineBreak or paragraph separation.
#define		IS_NEWLINECHAR(c)				((c == 0x0085) || (c == 0x000a) || (c == 0x000d) || (c == 0x001d) || (c == 0x001e) || (c == 0x2029))

//-------------------------------------------------------------------------------------------------
//	ListCtrl Internal Member Functions
#ifdef		BNS_MAIN_VERSION
	extern	TText*			WLayout_TextCreate				(TLayout* pLayout,  T_NUM MaxChar);
	extern	BOOL			WLayout_TextDestroy				(TLayout* pLayout);
	extern	BOOL			WLayout_ResetLineInfoLst		(TLayout* pLayout);
	extern	QUAD			WLayout_GetLineObjectNum		(const BidiCBInfo* pCBInfo);
	extern  T_POS			WLayout_GetLayoutXPos			(TLayout* pLayout, TLineInfo* pLineInfo);
#endif	//	BNS_MAIN_VERSION

//-------------------------------------------------------------------------------------------------
//	WLayout Member Functions
#ifdef		BNS_MAIN_VERSION

	extern	TLayout*		WLayout_Create					(T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
	extern	BOOL			WLayout_Destroy					(TLayout* pLayout);
	extern	BOOL			WLayout_SetRange				(TLayout* pLayout, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);

	extern	BOOL			WLayout_BidiStyleChanged		(TLayout* pLayout, QUAD RemoveStyle, QUAD AddStyle);
	extern	T_POS			WLayout_CalcCursorPos			(TLayout* pLayout, T_NUM LineNum, T_POS XPos);
	extern	BOOL			WLayout_CalCursorLoc			(TLayout* pLayout, BOOL bChangeBX);
	extern	BOOL			WLayout_ClearAttr				(TLayout* pLayout, int ChangeStrLen, int OldStrLen, T_POS OldCursorPos);
	extern	BOOL			WLayout_CopyStr					(TLayout* pLayout, T_STR pszBuf, T_SIZE BufSize);
	extern	BOOL			WLayout_CopyStrI				(TLayout* pLayout, TEditBuf* pREditBuf);
	extern	T_NUM			WLayout_CountLineNum			(TLayout* pLayout);
	//extern	T_NUM			WLayout_CountParagraphNum		(TLayout* pLayout);

	extern	void			WLayout_CurrTextDirection		(TLayout* pLayout, int Dir);
	extern	BOOL			WLayout_CursorMove				(TLayout* pLayout, int Direction);
	extern	BOOL			WLayout_CursorReset				(TLayout* pLayout);
	extern	BOOL			WLayout_CutStr					(TLayout* pLayout, T_STR pszBuf, T_SIZE BufSize);
	extern	BOOL			WLayout_CutStrI					(TLayout* pLayout, TEditBuf* pREditBuf);

	extern	void			WLayout_DoBidiOp				(TLayout* pLayout, BOOL bInitTextMode);

	//Start of Modification -torch(For Cursor & LineBreak) -------------------------------------------------------------------------------
	//@	extern	void			WLayout_DrawCursor				(TLayout* pLayout, int X, int Y, int W, int H, BOOL bLtoR);
	extern	BOOL		WLayout_IsLineBreakOK			(A_CHAR ch1, A_CHAR ch2);
	extern	BOOL			WLayout_DrawCursor				(TLayout* pLayout, TRect* pUpdatedRange);
	extern  BOOL			WLayout_GetCursorDrawRange(TLayout* pLayout, TRect* pCursorRange);
	extern	BOOL			WLayout_WriteCursorLine		(TLayout* pLayout);
	extern	BOOL			WLayout_SetCursorOrigin		(TLayout* pLayout, T_POS OrgX, T_POS OrgY);
	extern	BOOL			WLayout_GetCursorOrigin		(TLayout* pLayout, TPoint* pPtOrigin);
	extern	TLineInfo*		WLayout_FindLineAndYPos_WithLineNum	(TLayout* pLayout, T_NUM LineNum, T_POS* pYPosFromOrigin);
	extern	BOOL			WLayout_GetHorizontalTextBound(TLayout* pLayout, TLineInfo*	pLineToGetBound, T_POS* pLeftX, T_POS* pRightX);	
	//torch : add 4th parameter - height of lines that are scrolled vertically and nonvisible. 
	//extern	void			WLayout_SetScroll				(TLayout* pLayout, T_POS X, T_POS Y, T_POS Y2);
	extern	void			WLayout_SetScroll					(TLayout* pLayout, T_POS X, T_POS Y, T_POS Y2, T_POS nNonVisibleLineHeight);
	//End of Modification -torch(For Cursor & LineBreak) -------------------------------------------------------------------------------------------

	extern	void			WLayout_DrawInputCursor			(TLayout* pLayout);
	extern	void			WLayout_DrawText				(TLayout* pLayout, int StartLine);
	extern	TLineInfo*		WLayout_EndLineInfo				(TLayout* pLayout);
	extern	T_NUM			WLayout_FindLineNumWithY		(TLayout* pLayout, T_POS Y);
	extern	TLineInfo*		WLayout_FindLineWithLineNum		(TLayout* pLayout, T_NUM LineNum);
	extern	TLineInfo*		WLayout_FindLineWithPos			(TLayout* pLayout, T_POS Pos);
	extern	TLineInfo*		WLayout_FirstLineInfo			(TLayout* pLayout);
	extern	QUAD			WLayout_GetAlign				(TLayout* pLayout);
	extern	TObjAttr2*		WLayout_GetAttr					(TLayout* pLayout);
	extern	A_CHAR			WLayout_GetChar					(TLayout* pLayout, int nIndex);
	extern	BOOL			WLayout_GetCharBlinking			(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetCurLineHeight		(TLayout* pLayout, T_POS CursorPos);
	extern	BOOL			WLayout_GetCursorInfo			(TLayout* pLayout, TCursor* Info);
	extern	BOOL			WLayout_GetCursorLoc			(TLayout* pLayout, T_NUM* pLineNum, T_POS* pXPos, T_POS CursorPos);
	extern	T_POS			WLayout_GetCursorPos			(TLayout* pLayout);
	extern	QUAD*			WLayout_GetDispAttr				(TLayout* pLayout, T_POS Pos);
	extern	T_POS			WLayout_GetDispCursorPos		(TLayout* pLayout);
	extern	T_CSTR			WLayout_GetDispStr				(TLayout* pLayout);
	extern	BOOL			WLayout_GetGlyphInfo			(TLayout* pLayout, int GlyphIndex, TGlyphInfo* pGlyphInfo);
	extern	T_SIZE			WLayout_GetHeightToPos			(TLayout* pLayout, T_POS Pos);
	extern	void			WLayout_GetLastCursorRect		(TLayout* pLayout, TRect* pRect);
	extern	T_SIZE			WLayout_GetLineHeight			(TLayout* pLayout, int LineNum);
	extern	T_SIZE			WLayout_GetLineHeightWithPos	(TLayout* pLayout, T_POS CursorPos);
	extern	T_NUM			WLayout_GetLineInfo				(TLayout* pLayout, int LineNum, TLineInfo* pLineInfo);
	extern	T_SIZE			WLayout_GetLineWidth			(TLayout* pLayout, int LineNum);
	extern	T_NUM			WLayout_GetMaxChar				(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetMultiLineGap			(TLayout* pLayout);
	extern	BOOL			WLayout_GetObjectInfo			(TLayout* pLayout, TLineInfo* pLineInfo, int nIndex, TObjInfo* pObjInfo);
	//extern	TParaInfo*		WLayout_GetParagraphInfo		(TLayout* pLayout, T_NUM ParaNum);
	//extern	T_NUM			WLayout_GetParagraphNumWithPos	(TLayout* pLayout, T_POS Pos);
	extern	T_POS			WLayout_GetSelPos				(TLayout* pLayout);
	extern	BOOL			WLayout_GetSelPositions			(TLayout* pLayout, T_POS* pMinPos, T_POS* pMaxPos, T_POS SelPos, T_POS Size, BOOL bRetDisp);
	extern	T_CSTR			WLayout_GetSelStr				(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetSelStrLen			(TLayout* pLayout);
	extern	T_CSTR			WLayout_GetStr					(TLayout* pLayout);
	extern	int				WLayout_GetStrLen				(TLayout* pLayout);
	extern	QUAD			WLayout_GetStyle				(TLayout* pLayout, QUAD Style);
	extern	int				WLayout_GetTextColor			(TLayout* pLayout);
	extern	int				WLayout_GetTextEffect			(TLayout* pLayout);
	extern	int				WLayout_GetTextFace				(TLayout* pLayout);
	extern	int				WLayout_GetTextSize				(TLayout* pLayout);
	extern	TFontParams*	WLayout_GetTextStyEx			(TLayout* pLayout, T_POS Pos, E_GETMODE GetMode , T_NUM *StartIndex, T_NUM *EndIndex);
//S	extern	int				WLayout_GetTextStyle			(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetTotalHeight			(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetTotalLineHeight		(TLayout* pLayout);
	extern	T_SIZE			WLayout_GetTotalLineWidth		(TLayout* pLayout);

	extern	void			WLayout_InsertAttr				(TLayout* pLayout, int ChangeStrLen, int OldStrLen, T_POS OldCursorPos, BYTE TextMode);
	extern	BOOL			WLayout_InsertChar				(TLayout* pLayout, A_CHAR ch);
	extern	BOOL			WLayout_InsertObjEx				(TLayout* pLayout, T_POS Pos, BYTE ObjType, void* pData);
	extern	BOOL			WLayout_InsertStr				(TLayout* pLayout, T_POS Pos, T_CSTR pInsStr, int InsLen);
	extern	BOOL			WLayout_InsertStrEx				(TLayout* pLayout, T_POS Pos, T_CSTR pcszStr);
	extern	BOOL			WLayout_InsertStrExI			(TLayout* pLayout, T_POS Pos, TEditBuf* pInBuf);
	extern	BOOL			WLayout_InsertStrI				(TLayout* pLayout, T_POS Pos, TEditBuf* pREditBuf);
	
	extern	BOOL			WLayout_IsEndSymbol				(TLayout* pLayout);
	extern	BOOL			WLayout_IsMultiLine				(TLayout* pLayout);
	extern	BOOL			WLayout_IsNumAlignRight			(TLayout* pLayout);
	extern	BOOL			WLayout_IsOutsetPos				(TLayout* pLayout);
	extern	void			WLayout_MakeDisplayAttrBuf		(TLayout* pLayout);
	extern	void			WLayout_MakeRightStyleLineLst	(TLayout* pLayout);
	extern	BOOL			WLayout_ModifyStyle				(TLayout* pLayout, QUAD RemoveStyle, QUAD AddStyle);
	extern	BOOL			WLayout_PasteStr				(TLayout* pLayout, T_CSTR pcszStr);
	extern	BOOL			WLayout_PasteStrI				(TLayout* pLayout, TEditBuf* pREditBuf);
	extern	BOOL			WLayout_RemoveStr				(TLayout* pLayout, T_POS Pos, T_NUM RemoveCharNum);
	extern	BOOL			WLayout_RemoveStrEx				(TLayout* pLayout, T_POS Pos, T_NUM RemoveCharNum);
	extern	BOOL			WLayout_SelectStr				(TLayout* pLayout, T_POS Pos, T_SIZE Size, BOOL bDisp);

	extern	BOOL			WLayout_SetAlign				(TLayout* pLayout, QUAD AlignType);
	extern	BOOL			WLayout_SetAssignBuf			(TLayout* pLayout, T_CSTR pBuf, T_SIZE BufSize);
	//extern	BOOL			WLayout_SetBidiStyle			(TLayout* pLayout, int Bidi);
	extern	BOOL			WLayout_SetCharBlink			(TLayout* pLayout, BOOL bBlink);
	extern	BOOL			WLayout_SetCharBlinking			(TLayout* pLayout, BOOL bBlink);
	extern	T_POS			WLayout_SetCursorPos			(TLayout* pLayout, T_POS CursorPos);
	extern	BOOL			WLayout_SetCursorType			(TLayout* pLayout, int Type);
	extern	BOOL			WLayout_SetDispCursorPos		(TLayout* pLayout, int Pos);

	extern	BOOL			WLayout_SetIndent				(TLayout* pLayout, int Indent);
	extern	BOOL			WLayout_SetLayoutColor			(TLayout* pLayout, EItem item, T_COLOR Color);
	extern	BOOL			WLayout_SetMaxChar				(TLayout* pLayout, int MaxChar);
	extern	BOOL			WLayout_SetMultiLine			(TLayout* pLayout, BOOL bMode, int LineGap, int LineType);
	extern	void			WLayout_SetNumberAlign			(void* pLayout, BOOL bRight);
	extern	void			WLayout_SetQuestionMarkPos		(TLayout* pLayout, T_POS Pos);
	extern	BOOL			WLayout_SetSelectBuff			(TLayout* pLayout, T_POS SelPos, T_SIZE Size, BOOL bDisplayPos);
	extern	BOOL			WLayout_SetSelSize				(TLayout* pLayout, T_SIZE Size);
	extern	BOOL			WLayout_SetStr					(TLayout* pLayout, T_CSTR pcszStr);
	extern	BOOL			WLayout_SetTextColor			(TLayout* pLayout, int color);
	extern	BOOL			WLayout_SetTextColor2			(TLayout* pLayout, int cl, T_POS pos, int cnt);
	extern	BOOL			WLayout_SetTextEffect			(TLayout* pLayout, int Effect);
	extern	BOOL			WLayout_SetTextEffect2			(TLayout* pLayout, int Effect, T_POS pos, int cnt);
	extern	BOOL			WLayout_SetTextFace				(TLayout* pLayout, int faceID);
	extern	BOOL			WLayout_SetTextSize				(TLayout* pLayout, int size);
	extern	BOOL			WLayout_SetTextSize2			(TLayout* pLayout, int size, T_POS pos, int cnt);
//S	extern	BOOL			WLayout_SetTextStyle			(TLayout* pLayout, int sytle);
	extern	BOOL			WLayout_SetTextStyle2			(TLayout* pLayout, int Sytle, T_POS pos, int cnt);
	extern	BOOL			WLayout_SetWordBreak			(TLayout* pLayout, BOOL bBreak);
	
	extern	BOOL			WLayout_ShowCursor				(TLayout* pLayout, BOOL bShow);
	extern	BOOL			WLayout_ShowEndSymbol			(TLayout* pLayout, BOOL bShow);
	extern	T_POS			WLayout_ToDisplayPos			(TLayout* pLayout, T_POS RealPos);
	extern	T_POS			WLayout_ToRealPos				(TLayout* pLayout, T_POS DisplayPos);
	
	extern	void			WLayout_WriteCenter				(TLayout* pLayout, TLineInfo* pLineInfo, T_POS Y);
	extern	void			WLayout_WriteCenterRvrs			(TLayout* pLayout, TLineInfo* pLineInfo, T_POS Y);
	extern	void			WLayout_WriteFromLeft			(TLayout* pLayout, TLineInfo* pLineInfo, T_POS Y);
	extern	void			WLayout_WriteFromRight			(TLayout* pLayout, TLineInfo* pLineInfo, T_POS Y);
	extern	void			WLayout_WriteFromRightRvrs		(TLayout* pLayout, TLineInfo* pLineInfo, T_POS Y);
	extern	void			WLayout_WriteLine				(TLayout* pLayout, TLineInfo* pLineInfo, T_POS X, T_POS Y, T_POS CursorOrgX);

	extern	BOOL			WLayout_SetStrikeoutColor		(TLayout* pLayout, T_NUM DispStartIndex, T_NUM Cnt, T_COLOR Color);
	extern	BOOL			WLayout_SetUnderlineColor		(TLayout* pLayout, T_NUM DispStartIndex, T_NUM Cnt, T_COLOR Color);
	extern	BOOL			WLayout_TestWordBreak					(TLayout* pLayout, TLineInfo* pLineInfo, T_NUM ObjNum, T_SIZE Width);

	//---------------------------------------------------------------------------------------------
	extern	BOOL			WLayout_SetTextModifyInfo		(TLayout* pLayout, E_TEXTMODITYPE Type, T_POS X1, T_POS X2, T_POS SPos, T_NUM nSLen, BOOL bSRight);
	extern	BOOL			WLayout_InitInfoLst				(TLayout* pLayout);
	extern	BOOL			WLayout_DestroyInfoLst			(TLayout* pLayout);
	extern	BOOL			WLayout_ResetInfoLst			(TLayout* pLayout);
	extern	BOOL			WLayout_ResetBuffers			(TLayout* pLayout);
	extern	BOOL			WLayout_DoBiDiReorderAtDrawTime	(TLayout* pLayout, T_POS StartLine);
	extern	TLineInfo*		WLayout_DoBiDiReorderByLineInfo	(TLayout* pLayout, TLineInfo* pLineInfo);
	extern	BOOL			WLayout_ModifyInfoLst			(TLayout* pLayout);


	extern	BOOL			WLayout_bForeCursor				(TLayout* pLayout, BOOL bFore);
	//20110107 dooyoung.hwang@lge.com(torch) [START]
	extern	void			WLayout_SetPartialLineDraw	(TLayout* pLayout, BOOL bPartial);
	extern	T_POS			WLayout_GetLastLineDrawX();
//	extern  void			WLayout_WriteIconStr (T_CSTR pcszStr, T_POS X1, T_POS X2, T_POS Y1, T_POS Y2, T_SIZE iconWidth, T_SIZE iconHeight, int nIconID, T_POS iconPos, int nFontSize, TTextStyle* pTS, pfnCallback pfnDrawFn);
	extern  void			WLayout_WriteIconStr(T_CSTR pcszStr, T_POS X1, T_POS X2, T_POS Y1, T_POS Y2, T_SIZE iconWidth, T_SIZE iconHeight, int nIconID, T_POS iconPos, int nFontSize, QUAD AlignType, TTextStyle* pTS, pfnCallback pfnDrawFn);
	//20110107 dooyoung.hwang@lge.com(torch) [END]
	
	extern	BOOL			WLayout_GetDisplayStr(T_CSTR pcszStr, T_STR pOutBuf, int nBufSize);		//20110412 dooyoung.hwang@lge.com(torch)
#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif		//	_LGE_WLAYOUT_H_

