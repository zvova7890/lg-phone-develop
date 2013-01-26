/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT RICH EDIT CONTROL

	Copyright(c) 2003-2004 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_REDITCTRL_H_
#define		_BNSOFT_PEANUT_REDITCTRL_H_

#include	"FrmCtrl.h"
#include	"MacroFunc\REditCtrlM.h"
//#include	"..\..\TextLayout\Include\WLayout.h"
//#include	"..\..\TextLayout\Include\BiDi.h"

//-------------------------------------------------------------------------------------------------
//	EditCtrl Style의 종류 (TBaseCtrl::Style)
#define		REDITSTY_BORDER					FRMSTY_BORDER		//	0x80000000	영역에 테두리를 그림
#define		REDITSTY_TITLE					FRMSTY_TITLE		//	0x40000000	제목을 표시함
#define		REDITSTY_LEFTTITLE				FRMSTY_LEFTTITLE	//	0x20000000	제목을 왼쪽정렬하여 표시함
#define		REDITSTY_TOPTITLE				FRMSTY_LEFTTOPTITLE	//  0x00800000	제목을 왼쪽위쪽정렬하여 표시함
#define		REDITSTY_HSCROLLBAR				FRMSTY_HSCROLLBAR	//	0x10000000	수평 스크롤바를 표시함
#define		REDITSTY_VSCROLLBAR				FRMSTY_VSCROLLBAR	//	0x08000000	수직 스크롤바를 표시함
#define		REDITSTY_ALWAYSSHOWSB			FRMSTY_ALWAYSSHOWSB	//	0x04000000	스크롤바를 항상 보여줌
#define		REDITSTY_FLICKSCROLL 			FRMSTY_FLICKSCROLL
#define		REDITSTY_ADDKEY					0x00010000 			// ADD키 추가 sekyung.choi
#define		REDITSTY_MULTILINE				0x00008000			//	여러줄 편집
#define		REDITSTY_ENDSYMBOL				0x00004000			//	활성화된 경우 줄의 끝에 CR표시를 함
#define		REDITSTY_JUMPHSCROLL			0x00002000			//	HSCROLL시에 WorkArea의 1/4정도 스크롤함
#define		REDITSTY_RIGHT					0x00001000			//	오른쪽에서 입력. (숫자만 입력됨)
#define		REDITSTY_COMMA					0x00000800			//	3자리마다 ','표시
#define		REDITSTY_RICHTEXT				0x00000400			//	각 문자마다 정의한 color대로 출력함 
#define		REDITSTY_BIDI					0x00000200			//	Bidi Algorithm을 이용함
#define		REDITSTY_NOCURSOR				0x00000100			//	커서를 보여주지 않음
#define		REDITSTY_AUTOCURSORMOVE			0x00000080			//	입력 중에 2초 경과후 자동 완성
#define		REDITSTY_HIDDEN					0x00000040			//	'*'로 표시
#define		REDITSTY_READONLY				0x00000020			//	읽기전용
#define		REDITSTY_WORDBREAK				0x00000010			//	한 단어를 가능한 한 붙여서 출력
#define		REDITSTY_AUTOGROWRANGE			0x00000008			//	콘트롤의 영역을 자동으로 늘이고 줄임
#define		REDITSTY_AUTOSHIFTOFF			0x00000004			//	문자 입력시 EditMode가 Abc -> abc, abc -> Abc 자동으로 
															//	변환되는 것을 방지함			 예) URL 입력시 이용
#define		REDITSTY_ADDRESS				0x00000002			// 1번키의 sequence가 @가 가장 먼저 나오도록 함
#define		REDITSTY_LONGPOINTBLOCK			0x00000001			//	롱포인트에 의한 Block을 잡아줌.
//david.choi@lge.com 20100514 - Zoom In cursor 구현 
#define		REDITSTY_ZOOMINCURSOR			0x00040000			//	롱포인트에 의한 Block을 잡아줌.

#define		REDITSTY_DEF					(FRMSTY_DEF | REDITSTY_AUTOCURSORMOVE|REDITSTY_LONGPOINTBLOCK)
//>#define		REDITSTY_DEF					(FRMSTY_DEF | REDITSTY_AUTOCURSORMOVE)

//20101021 david.choi@lge.com - Variable Font Color
#if defined (LGE_FEATURE_FONTCOLOR)
#define		REDITSTY_VFONTCOLOR				0x00020000			//	롱포인트에 의한 Block을 잡아줌.
#endif

//-------------------------------------------------------------------------------------------------
#define		CSM(C)							(((QUAD)(C&0xFF))<<24)									//	Character set mask
#define		DICTIONARY_NONE					0x00100000												//	Multitap Mode
#define		DICTIONARY_T9					0x00200000												//	T9 Mode
#define		LOCAL_NUMBER					0x00400000

//-------------------------------------------------------------------------------------------------
#define		REDITMODE_INIT					REDITMODE_LATIN_abc										//	초기 언어설정(길령환 수정)
#define		REDITMODE_ALL					0xFFFFFFFF

//=================================================================================================
//	Type of REditCtrl Input Mode (TREditCtrl::EditMode, TREditCtrl::EditableMode)
//=================================================================================================
#define		REDITMODE_NUMBER				0x00000001												//	European Number
#define		REDITMODE_SYMBOL				0x00000002												//	Symbol
#define		REDITMODE_IMOTICON				0x00000004												//	Imoticon
#define		REDITMODE_PHRASE				0x00000008												//	A Idiomatic Phrase
#define		REDITMODE_TOOL1					0x00000010												//	Tools
#define		REDITMODE_ENGLISH				REDITMODE_LATIN_ALL
#define		REDITMODE_SMALLENG				REDITMODE_LATIN_abc
#define		REDITMODE_LARGEENG				REDITMODE_LATIN_ABC
#define		REDITMODE_NUM					REDITMODE_NUMBER
#ifdef LGE_REGION_CHINA  //zhaopengfei add for china edit
#define		REDITMODE_EMO					0x08000000			//	zhaopengfei add for china edit
#define		REDITMODE_CHN_EDITOR_ALL				0x04000000			//	guoyongcan add for china edit
#endif

//=================================================================================================
//	EUROPEAN ALPHABETS
//=================================================================================================
#define		REDITMODE_LATIN_abc				0x00000010												//	European Small letter
#define		REDITMODE_LATIN_ABC				0x00000020												//	European Capital letter
#define		REDITMODE_LATIN_Abc				0x00000040												//	European Shift Abc
#define		REDITMODE_LATIN_T9_abc			0x00000080												//	European Small letter of T9 Mode
#define		REDITMODE_LATIN_T9_ABC			0x00000100												//	European Capital letter of T9 Mode
#define		REDITMODE_LATIN_T9_Abc			0x00000200												//	European Shift Abc of T9 Mode

#define		REDITMODE_LATIN					REDITMODE_LATIN_Abc										//	Basic European Mode
#define		REDITMODE_LATIN_ALL				(REDITMODE_LATIN_abc | REDITMODE_LATIN_ABC | REDITMODE_LATIN_Abc | \
											 REDITMODE_LATIN_T9_ABC | REDITMODE_LATIN_T9_Abc | REDITMODE_LATIN_T9_abc)

//=================================================================================================
//	EAST ASIAN SCRIPTS(CJK)
//=================================================================================================
//	Edit mode for Korean
#define		REDITMODE_KOREAN				(CSM(CHARSET_KOREAN) | DICTIONARY_NONE)					//	Korean Multitap Mode
//	Edit mode for Chinese
#define		REDITMODE_BOPOMOPO				0x00000400			//	Chinese bopomopo for Traditional only
#define		REDITMODE_PINYIN				0x00000800			//	Chinese PinYin for Simplied only
#define		REDITMODE_STROKE_TRAD			0x00001000			//	Chinese traditional stroke for traditinal only
#define		REDITMODE_STROKE_SIMP			0x00002000			//	Chinese simplied stroke for simplied only
//- - - - - For the compatibility for old version "DO NOT USE FUTURE"  - - - - - - - - - - - - - -
#define		REDITMODE_CHINESE_T9_BoPoMoFo	REDITMODE_BOPOMOPO
#define		REDITMODE_CHINESE_T9_PINYIN		REDITMODE_PINYIN
#define		REDITMODE_CHINESE_T9_T_STROKE	REDITMODE_STROKE_TRAD
#define		REDITMODE_CHINESE_T9_S_STROKE	REDITMODE_STROKE_SIMP
#define		REDITMODE_TRADITIONAL_CHINESE	REDITMODE_CHINESE_T9_T_STROKE
#define		REDITMODE_SIMPLIFIED_CHINESE	REDITMODE_CHINESE_T9_S_STROKE

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		REDITMODE_CHINESE_TRAD			(REDITMODE_STROKE_TRAD | REDITMODE_BOPOMOPO)
#define		REDITMODE_CHINESE_SIMP			(REDITMODE_STROKE_SIMP | REDITMODE_PINYIN)
#define		REDITMODE_CHINESE_ALL			(REDITMODE_CHINESE_TRAD | REDITMODE_CHINESE_SIMP)
#define		IS_REDITMODE_CHINESE(E)			(E & REDITMODE_CHINESE_ALL)

	
//=================================================================================================
//	MIDDLE EASTERN SCRIPTS
//=================================================================================================
//	Edit mode for Hebrew
#define		REDITMODE_HEBREW				(CSM(CHARSET_HEBREW) | DICTIONARY_NONE)					//	Hebrew Multitap Mode
#define		REDITMODE_HEBREW_T9				(CSM(CHARSET_HEBREW) | DICTIONARY_T9)					//	Hebrew T9 Mode

//	Edit mode for Arabic
#define		REDITMODE_ARABIC				(CSM(CHARSET_ARABIC) | DICTIONARY_NONE)					//	Arabic Multitap Mode
#define		REDITMODE_ARABIC_T9				(CSM(CHARSET_ARABIC) | DICTIONARY_T9)					//	Arabic T9 Mode
#define		REDITMODE_ARABIC_NUMBER			(CSM(CHARSET_ARABIC) | LOCAL_NUMBER)						//	Arabic Number Mode

//	Edit mode for Farsian
#define		REDITMODE_FARSI					(CSM(CHARSET_FARSI) | DICTIONARY_NONE)					//	Farsi Multitap Mode



//=================================================================================================
//	SOUTH EAST ASIAN SCRIPTS
//=================================================================================================
//	Edit mode for Thai
#define		REDITMODE_THAI					(CSM(CHARSET_THAI) | DICTIONARY_NONE)					//	Thai Multitap Mode
#define		REDITMODE_THAI_T9				(CSM(CHARSET_THAI) | DICTIONARY_T9)						//	Thai T9 Mode

//	Edit mode for Khmer
#define		REDITMODE_KHMER					(CSM(CHARSET_KHMER) | DICTIONARY_NONE)					//	Khmer Multitap Mode
//=================================================================================================
//	INDIAN SCRIPTS
//=================================================================================================
//	Edit mode for Hindi
#define		REDITMODE_HINDI					(CSM(CHARSET_HINDI) | DICTIONARY_NONE)					//	Hindi Multitap Mode
#define		REDITMODE_HINDI_T9				(CSM(CHARSET_HINDI) | DICTIONARY_T9)						//	Hindi T9 Mode

//	Edit mode for Marathi
#define		REDITMODE_MARATHI				(CSM(CHARSET_MARATHI) | DICTIONARY_NONE)					//	Matathi Multitap Mode
#define		REDITMODE_MARATHI_T9			(CSM(CHARSET_MARATHI) | DICTIONARY_T9)						//	Marathi T9 Mode
//	Edit mode for Bengali
#define		REDITMODE_BENGALI				(CSM(CHARSET_BENGALI) | DICTIONARY_NONE)					//	Bengali Multitap Mode
#define		REDITMODE_BENGALI_T9			(CSM(CHARSET_BENGALI) | DICTIONARY_T9)						//	Bengali T9 Mode
//	Edit mode for Tamil
#define		REDITMODE_TAMIL					(CSM(CHARSET_TAMIL) | DICTIONARY_NONE)					//	Tamil Multitap Mode
#define		REDITMODE_TAMIL_T9				(CSM(CHARSET_TAMIL) | DICTIONARY_T9)					//	Tamil T9 Mode //Nanda

//	Edit mode for Urdu
#define		REDITMODE_URDU					(CSM(CHARSET_URDU) | DICTIONARY_NONE)					//	Urdu Multitap Mode
#define		REDITMODE_URDU_T9				(CSM(CHARSET_URDU) | DICTIONARY_T9)						//	Urdu Multitap Mode

//	Edit mode for Telugu
#define		REDITMODE_TELUGU				(CSM(CHARSET_TELUGU) | DICTIONARY_NONE)					//	Telugu Multitap Mode
#define		REDITMODE_TELUGU_T9				(CSM(CHARSET_TELUGU) | DICTIONARY_T9)					//	Telugu T9 Mode //Nanda

//	Edit mode for Gurmukhi
#define		REDITMODE_GURMUKHI				(CSM(CHARSET_GURMUKHI) | DICTIONARY_NONE)				//	Gurmukhi Multitap Mode

#define		REDITMODE_PUNJABI				(CSM(CHARSET_PANJABI) | DICTIONARY_NONE)				//	Punjabi Multitap Mode //Nanda
#define		REDITMODE_PUNJABI_T9			(CSM(CHARSET_PANJABI) | DICTIONARY_T9)					//	Punjabi T9 Mode 
#define		REDITMODE_PANJABI				REDITMODE_PUNJABI
#define		REDITMODE_PANJABI_T9			REDITMODE_PUNJABI_T9

//	Edit mode for Sinhala
#define		REDITMODE_SINHALA				(CSM(CHARSET_SINHALA) | DICTIONARY_NONE)					//	Sinhala Multitap Mode

//	Edit mode for Gujarati
#define		REDITMODE_GUJARATI				(CSM(CHARSET_GUJARATI) | DICTIONARY_NONE)				//	Gujarati Multitap Mode
#define		REDITMODE_GUJARATI_T9			(CSM(CHARSET_GUJARATI) | DICTIONARY_T9)					//	Gujarati T9 Mode
#define		REDITMODE_GUJARATHI				REDITMODE_GUJARATI
#define		REDITMODE_GUJARATHI_T9			REDITMODE_GUJARATI_T9

//	Edit mode for Kannada
#define		REDITMODE_KANNADA				(CSM(CHARSET_KANNADA) | DICTIONARY_NONE)				//	Kannada Multitap Mode
#define		REDITMODE_KANNADA_T9			(CSM(CHARSET_KANNADA) | DICTIONARY_T9)					//	Kannada T9 Mode //Nanda

//	Edit mode for Malayalam
#define		REDITMODE_MALAYALAM				(CSM(CHARSET_MALAYALAM) | DICTIONARY_NONE)				//	Malayalam Multitap Mode
#define		REDITMODE_MALAYALAM_T9			(CSM(CHARSET_MALAYALAM) | DICTIONARY_T9)				//	Malayalam T9 Mode 
//	Edit mode for Oriya
#define		REDITMODE_ORIYA					(CSM(CHARSET_ORIYA) | DICTIONARY_NONE)					//	Oriya Multitap Mode
#define		REDITMODE_ORIYA_T9				(CSM(CHARSET_ORIYA) | DICTIONARY_T9)					//	Oriya T9 Mode

//	Edit mode for Assamese
#define		REDITMODE_ASSAMESE				(CSM(CHARSET_ASSAMESE) | DICTIONARY_NONE)				//	Assamese Multitap Mode
#define		REDITMODE_ASSAMESE_T9			(CSM(CHARSET_ASSAMESE) | DICTIONARY_T9)					//	Assamese T9 Mode

//-------------------------------------------------------------------------------------------------

#define		INVERSE_CSM(C)					((C >> 24) & 0xFF)
#define		IS_T9_SUPPORTING_EDITMODE(E)	((E & REDITMODE_LATIN_ALL) || (INVERSE_CSM(E) != 0) && \
											(INVERSE_CSM(E) != CHARSET_FARSI) && (INVERSE_CSM(E) != CHARSET_KOREAN))

// Mode Change Sequence Type
typedef enum{
	REDITMODE_SEQUENCE_INVALID			= -1,
	REDITMODE_SEQUENCE_ABC 				= 0,
	REDITMODE_SEQUENCE_T9,
	REDITMODE_SEQUENCE_MAX
}E_REDITMODE_SEQUENCE_ID;

//	REditCtrl의 입력상태 종류 (TREditCtrl::enEditState)
typedef enum
{
	REDITSTATE_ERROR					= -1,
	REDITSTATE_WAIT						= 0,					//	새로운 문자의 입력을 기다리는 중
	REDITSTATE_INPUT											//	문자를 만들고 있는 중
} E_REDITSTATE;

//-------------------------------------------------------------------------------------------------
//	커서의 종류
#define		REDITCSR_NONE				0
#define		REDITCSR_VERTICAL			1
#define		REDITCSR_FULLBOX			2
#define		REDITCSR_HALFBOX			3
#define		REDITCSR_MINIBOX			4
#define		REDITCSR_CHARBLINKING		0x80

//-------------------------------------------------------------------------------------------------
//	EditCtrl의 SeparatorType 종류
#define		REDITSEP_NONE				0x00000000
#define		REDITSEP_LINE				0xFFFFFFFF
#define		REDITSEP_DASHLINE			0xEEEEEEEE
#define		REDITSEP_DOTLINE			0xAAAAAAAA

//-------------------------------------------------------------------------------------------------
//	EditCtrl Notify Event의 종류 (TBaseCtrl::NotiMask)
#define		REDITNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND		//	0x80000000	컨트롤의 배경을 그리는 경우에 발생
#define		REDITNOTI_POSTDRAW			NOTIMASK_POSTDRAW		//	0x40000000	컨트롤을 그린 후 그래픽버퍼로 출력하기 전에 발생
#define		REDITNOTI_PREKEY			NOTIMASK_PREKEY			//	0x20000000	컨트롤의 키 처리 이전에 키를 받음
#define		REDITNOTI_POSTKEY			NOTIMASK_POSTKEY		//	0x10000000	컨트롤의 키 처리 이후 키를 받음
#define		REDITNOTI_TITLEDRAW			NOTIMASK_TITLEDRAW		//  0x01000000	컨트롤의 title을 그리는 경우에 발생(값주의)
#define		REDITNOTI_HASVSCROLL		NOTIMASK_HASVSCROLL		//	0x00000001	컨트롤의 vertical scrollbar이 생기거나 없어질때 발생
#define		REDITNOTI_STRCHANGED		0x08000000				//	문자열이 바뀌었음
#define		REDITNOTI_EDITMODECHANGED	0x04000000				//	EditMode 변경시 오듈에 변경을 알림
#define		REDITNOTI_OEMNOTIFY			0x02000000
#define		REDITNOTI_T9ONOFF			0x01000000				//	T9 On/Off시에 발생함.
#define		REDITNOTI_PREPOINTNG		0x00800000				//	0x00800000	컨트롤 포인팅 처리 전에 포인팅이벤트 받음 //20060721_황수환
#define		REDITNOTI_POSTPOINTNG		0x00400000				//	0x00400000	컨트롤 포인팅 처리 후에 포인팅이벤트 받음 //20060721_황수환
#define		REDITNOTI_POINTING			0x00200000				//	포인팅이 되면 발생
#define		REDITNOTI_CURSORPOS			0x00100000				//	read only이고 커서가 없는 경우 
#define		REDITNOTI_FLICK				FRMNOTI_FLICK			//	0x00080000
#define		REDITNOTI_INPUTCOMPLETE		0x00040000				//	EditState 입력을 완성했을 때 발생 (MULTITAB에서 WAIT 또는 다른키 입력시 발생)
#define		REDITNOTI_AUTOGROWRANGE		0x00020000				//	Editctrl 의 크기가 변경되었을때 발생
#define		REDITNOTI_ZOOMINCURSOR		0x00010000				//	Zoomincursor가 on/off 시에 발생함.

#define		REDITNOTI_CURSORZERO		0x00008000				//	Back Key (Clear 동작)시에  CursorPos가 0임을 flash에 Noti
#define		REDITNOTI_CHANGELANG		0x00004000				//	Language Change 되었음을 Flash에 Noti

//-------------------------------------------------------------------------------------------------
//	REditCtrl Effect의 종류 (NORMAL ~ OUTLINE는  GrSys의 Text effect와 값을 일치 시킨다)
//	상위 3바이트는 텍스트 출력에대한 Effect를 나타내며 하위 1바이트는 Object일경우의 Align을 정의 한다.
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		REFFECT_NORMAL				0x00000000
#define		REFFECT_INVERSE				0x80000000				//	텍스트를 반전시켜서 출력시킨다.
#define		REFFECT_BOLD				0x40000000				//	텍스트를 볼드체로 출력한다.
#define		REFFECT_UNDERLINE			0x20000000				//	텍스트를 출력한 후 밑줄을 긋는다.
#define		REFFECT_ITALIC				0x10000000				//	텍스트를 이텔릭체로 출력한다.
#define		REFFECT_OUTLINE				0x08000000				//	외곽선 폰트로 출력한다.
#define		REFFECT_STRIKETHROUGH		0x04000000				//	텍스트에 취소선을 그린다(REditCtrl에만 적용).
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	아래정의는 얼라인의 중복을 막기위해 비트 마스킹을 사용하지 않는다.
//	REditCtrl의 문자외의 Object의 Layout의 종류 (TObjAttr의 Effect에 저장된다 최대값 255)
#define		REFFECT_ALIGN_DEFAULT		0x00000000				//	Object를 일반문자와같이 문자옆에 그려준다.
#define		REFFECT_ALIGN_LEFT			0x00000001				//	Object를 문자와 달리 독립된 형태로 Left Align속성을 주어 그린다.
#define		REFFECT_ALIGN_CENTER		0x00000002				//	Object를 문자와 달리 독립된 형태로 Center Align속성을 주어 그린다.
#define		REFFECT_ALIGN_RIGHT			0x00000004				//	Object를 문자와 달리 독립된 형태로 Right Align속성을 주어 그린다.
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//-------------------------------------------------------------------------------------------------
//	EditCtrl 색상 정의
typedef enum
{
	REDITCOL_BACKGROUND					= FRMCOL_BACKGROUND,
	REDITCOL_FOREGROUND					= FRMCOL_FOREGROUND,
	REDITCOL_BORDER_LT					= FRMCOL_BORDER_LT,
	REDITCOL_BORDER_RB					= FRMCOL_BORDER_RB,
	REDITCOL_TITLE_BACKGROUND			= FRMCOL_TITLE_BACKGROUND,
	REDITCOL_TITLE_TEXT					= FRMCOL_TITLE_TEXT,
	REDITCOL_TITLE_UNDERLINE			= FRMCOL_TITLE_UNDERLINE,
	REDITCOL_SEPARATOR,
	REDITCOL_NUM
} E_REDITCOL;
//-------------------------------------------------------------------------------------------------
//  REDITCtrl Object type.	2부터는 UserDefine 타입을 정의 하면됨.

#define		REDITCTRL_CHARACTER			0
#define		REDITCTRL_CONTROL			1

//-------------------------------------------------------------------------------------------------
//	REditCtrl GetInfo, Process.

#define		REOINFO_WIDTH				0
#define		REOINFO_HEIGHT				1
#define		REOINFO_ASCENT				2
#define		REOINFO_DESCENT				3

#define		REOCMD_KEYDOWN				4
#define		REOCMD_TIMER				5
#define		REOCMD_PAINT				6
#define		REOCMD_SETFOCUS				7
#define		REOCMD_KILLFOCUS			8
#define		REOINFO_WIDTHEX				9	
#define		REOCMD_PAINTEX				10

//-------------------------------------------------------------------------------------------------
#define		NOMETHOD					0
#define		MAXMETHOD					256

//-------------------------------------------------------------------------------------------------
//	콜백함수 타입, 구조체 정의
typedef int				(*T_pfnGetWidthEx)				  (QUAD PreObj, QUAD ObjAttr, QUAD* pFontData, int* KerningX);
typedef int				(*T_pfnGetWidth)                  (QUAD Data);
typedef int				(*T_pfnGetHeight)                 (QUAD Data);
typedef	int				(*T_pfnGetAscent)                 (QUAD Data);
typedef int				(*T_pfnGetDescent)                (QUAD Data);
typedef int				(*T_pfnKeyDown)                   (QUAD Data, KEY Key);
typedef int				(*T_pfnTimer)                     (T_ID ID, QUAD Data);
typedef void			(*T_pfnPaint)                     (QUAD Data, T_POS X, T_POS Y);
typedef void			(*T_pfnPaintEx)                   (QUAD ObjAttr, T_POS X, T_POS Y, BYTE* pFontData);
typedef int				(*T_pfnSetFocus)                  (QUAD Data);
typedef int				(*T_pfnKillFocus)                 (QUAD Data);

//-------------------------------------------------------------------------------------------------
//	콜백함수 등록할 구조체 정의
typedef struct 
{
	void*				pfnGetWidthCB;
	void*				pfnGetHeightCB;
	void*				pfnGetAscentCB;
	void*				pfnGetDescentCB;
	void*				pfnKeyDownCB;
	void*				pfnTimerCB;
	void*				pfnPaintCB;
	void*				pfnSetFocusCB;
	void*				pfnKillFocusCB;
	void*				pfnGetWidthExCB;
	void*				pfnPaintExCB;
} TObjInfoProc;

typedef	struct
{
	BYTE				Type;
	BYTE				Data;								//	문자 : font,	문자외의 Object	: ordnum
	QUAD				Effect;
	T_COLOR				Color;
} TObjAttr;

//-------------------------------------------------------------------------------------------------
//	Charactor Object Default Style 구조체 정의
typedef struct
{
	E_FONT				Font;
	QUAD				Effect;
	T_COLOR				Color;
} TCharStyle;

//-------------------------------------------------------------------------------------------------
//	Object Attribute, Color buffer copy, paste 시에 사용.
typedef struct
{
	T_STR				pszStrBuf;
	TObjAttr*			pAttrBuf;
	T_SIZE				BufSize;
} TREditBuf;

//-------------------------------------------------------------------------------------------------
//	EditCtrl 구조체 정의
typedef struct
{
	TFrmCtrl			Frame;
//	BOOL				bAssignedBuf;
//	T_SIZE				BufSize;							//	편집문자열 버퍼의 크기 (NULL포함길이)
	QUAD				EditableMode;
	QUAD				EditMode;
	E_REDITMODE_SEQUENCE_ID enEditModeSeqID;				//Edit Mode sequence ID
	E_REDITSTATE		enEditState;
	
	BOOL				bShowCursor;						//	커서가 보이는 지의 여부
	BOOL				bCursorBlink;						//	커서를 깜박이게 할지 여부

	TPoint				Scroll;								//	스크롤의 양(X-픽셀단위, Y-줄단위)
	BOOL				bInputEnter;						//	Enter 키의 입력을 받아들일 지의 여부
	KEY					RepeatKey;
	int					RepeatCnt;
	BOOL				bVScrlBar;							//	VScrollBar Style일 경우 라인 정보구성시 고려 유무
	T_POS				ScrollPos;

	int*				Method;								//	Call 함수 등록할 배열.  <= QUAD형이었슴.
	TObjInfoProc		ObjInfoProc;						//  Character 콜백함수 구조체.
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	ADDED BY LG ELECTRONICS FOR EUROPE MODEL
	T_HANDLE			hT9Info;
	T_HANDLE			hLangDll;

	E_CHARSET			DictionaryType;
	T_SIZE				WorkWidth;
	T_SIZE				MinHeight;							//	Minimum Height

	TLayout*			pLayout;
	BOOL				bIsLtoR;
	QUAD				DicChange;							//Y Dictionary On/Off/Number setting
	E_CHARSET			KeypadLang;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	For DOP
	void*				pOemREditCtrl;

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	For Quick Symbol Input
#if (FEATURE_USE_QUICKSYMBOL_INPUT == 1)
	BOOL				bOnQuickSym;						//	Quick Symbol Input 창을 띄울 것인지 여부
	T_CSTR				pQuickSymTypeID;					//	Quick Symbol Type의 ID --> String으로 지정 (ex, L"COMMON") 
#endif
	BOOL				bOnWordList;
	//	For Qwerty Only.
	QUAD				OldEditMode;						//	Shift/Symbol 키에 의해 돌아가기 위한 Mode
	QUAD				OrgTextMode;
	QUAD				CtrlKey;							//	Ctrl Key가 눌린 경우 해당 값을 저장한다.
//	BOOL				ShiftKey;							// Symbol 및 ShiftMode관련 설정을 한다.
	QUAD				CurDev;								//	현재 Device의 상태를 봄 (E_OEMREDITDEV 참고)
	E_REDITMODE_SEQUENCE_ID	PrevDevSeq;
	//	For Block Function.
	BOOL				bBlockEnable;						// Block을 사용할지 여부를 결정한다. Default는 TRUE
	BOOL				bBlockOn;							// Block상태 On/Off
	BOOL				bBlockPending;						// 2011.02.15 david.choi@lge.com - Block상태 Pending State. Block 설정을 위한 timer 세팅 시에 True가 된다. 
	BOOL				bHScrollMove;
	BOOL				bCapsLock;
	T_POS				ScrollOffset;
	BOOL				bIsAutoGrowRange;
	BOOL				bShift;								//	20100527, hyunsoo.maeng@lge.com, add shift strate for hard QWERTY
	LONG				AltState;							//	20100527, hyunsoo.maeng@lge.com, add alt state for hard QWERTY
} TREditCtrl;


//-------------------------------------------------------------------------------------------------	{{BNS_INTERNALCODE(+)}}
//	EditCtrl Internal Member Functions
#ifdef		BNS_MAIN_VERSION

	extern BOOL				REditCtrl_CreateBody          (TREditCtrl* pREC, void* pOwner, E_CTRLTYPE enType, QUAD Style, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
	extern BOOL				REditCtrl_DestroyBody         (TREditCtrl* pREC);
	extern BOOL				REditCtrl_TestWordBreak       (TREditCtrl* pREC, T_NUM ObjNum, T_SIZE Width);

	extern BOOL				REditCtrl_InitLineInfoLst     (TREditCtrl* pREC);
	extern BOOL				REditCtrl_ResetLineInfoLst    (TREditCtrl* pREC);
	extern BOOL				REditCtrl_DestroyLineInfoLst  (TREditCtrl* pREC);
	extern T_NUM			REditCtrl_FillLineInfo        (TREditCtrl* pREC, TLineInfo* pLineInfo, int StartPos);
	extern T_NUM			REditCtrl_FillLineInfoRvrs    (TREditCtrl* pREC, TLineInfo* pLineInfo, int EndPos);

	extern void				REditCtrl_MakeDisplayAttrBuf  (TREditCtrl* pREC);
	extern T_POS			REditCtrl_ToDisplayPos        (TREditCtrl* pREC, T_POS RealPos);
	extern T_POS			REditCtrl_ToRealPos           (TREditCtrl* pREC, T_POS DisplayPos);
	extern BOOL				REditCtrl_SetSelectBuff       (TREditCtrl* pREC, T_POS SelPos, T_SIZE Size, BOOL bDisplayPos);
	extern BOOL				REditCtrl_GetSelPositions     (TREditCtrl* pREC, T_POS* pMinPos, T_POS* pMaxPos, T_POS SelPos, T_POS Size, BOOL bRetDisp);
	extern BOOL				REditCtrl_IsHScrollCondition	(H_CTRL	hREC);

#endif	//	BNS_MAIN_VERSION																	//	{{BNS_INTERNALCODE(-)}}
//-------------------------------------------------------------------------------------------------
//	EditCtrl Member Functions
#ifdef		BNS_MAIN_VERSION

	extern H_CTRL			REditCtrl_Create              (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
	extern H_CTRL			REditCtrl_CreateEx            (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
	extern BOOL				REditCtrl_Destroy             (H_CTRL hREC);
	extern BOOL				REditCtrl_AssignBuf           (H_CTRL hREC, T_CSTR pBuf, T_SIZE BufSize);
	extern BOOL				REditCtrl_SetStr              (H_CTRL hREC, T_CSTR pcszStr);
	extern BOOL				REditCtrl_InsertStr           (H_CTRL hREC, T_CSTR pcszStr);
	extern BOOL				REditCtrl_InsertStrI          (H_CTRL hREC, TREditBuf* pREditBuf);
	extern BOOL				REditCtrl_InsertStrEx         (H_CTRL hREC, T_POS Pos, T_CSTR pcszStr);
	extern BOOL				REditCtrl_InsertStrExI        (H_CTRL hREC, T_POS Pos, TREditBuf* pREditBuf);
	extern BOOL				REditCtrl_InsertObj           (H_CTRL hREC, BYTE ObjType, BYTE ObjOrdNum);
	extern BOOL				REditCtrl_InsertObjEx         (H_CTRL hREC, T_POS Pos, BYTE ObjType, BYTE ObjOrdNum);
	extern BOOL				REditCtrl_RemoveStr           (H_CTRL hREC, T_NUM RemoveCharNum);
	extern BOOL				REditCtrl_RemoveStrEx         (H_CTRL hREC, T_POS Pos, T_NUM RemoveCharNum);
	extern BOOL				REditCtrl_SelectStr           (H_CTRL hREC, T_POS Pos, T_SIZE Size);
	extern BOOL				REditCtrl_CutStr              (H_CTRL hREC, T_STR pszBuf, T_SIZE BufSize);
	extern BOOL				REditCtrl_CutStrI             (H_CTRL hREC, TREditBuf* pREditBuf);
	extern BOOL				REditCtrl_CopyStr             (H_CTRL hREC, T_STR pszBuf, T_SIZE BufSize);
	extern BOOL				REditCtrl_CopyStrI            (H_CTRL hREC, TREditBuf* pREditBuf);
	extern BOOL				REditCtrl_PasteStr            (H_CTRL hREC, T_CSTR pcszStr);
	extern BOOL				REditCtrl_PasteStrI           (H_CTRL hREC, TREditBuf* pREditBuf);
	extern BOOL				REditCtrl_SetMaxChar          (H_CTRL hREC, T_NUM MaxChar);
	extern BOOL				REditCtrl_SetEditableMode     (H_CTRL hREC, QUAD Modes);
	extern BOOL				REditCtrl_SetEditMode         (H_CTRL hREC, QUAD Mode);
	extern T_POS			REditCtrl_SetCursorPos        (H_CTRL hREC, T_POS CursorPos);
	extern BOOL				REditCtrl_SetMultiLine        (H_CTRL hREC, BOOL bMode, int LineGap, int Separator);
	extern int				REditCtrl_GetMultiLine        (H_CTRL hREC);
	extern BOOL				REditCtrl_SetInputEnter       (H_CTRL hREC, BOOL bInputEnter);
	extern BOOL				REditCtrl_SetAlign            (H_CTRL hREC, QUAD AlignType);
	extern BOOL				REditCtrl_SetMinHeight        (H_CTRL hREC, T_SIZE MinHeight);

	extern T_CSTR			REditCtrl_GetStr              (H_CTRL hREC);
	extern T_POS			REditCtrl_GetSelPos           (H_CTRL hREC);
	extern T_SIZE			REditCtrl_GetSelStrLen        (H_CTRL hREC);
	extern T_CSTR			REditCtrl_GetSelStr           (H_CTRL hREC);
	extern T_NUM			REditCtrl_GetMaxChar          (H_CTRL hREC);
	extern QUAD				REditCtrl_GetEditableMode     (H_CTRL hREC);
	extern QUAD				REditCtrl_GetEditMode         (H_CTRL hREC);
	extern E_REDITSTATE		REditCtrl_GetEditState        (H_CTRL hREC);
	extern T_POS			REditCtrl_GetCursorPos        (H_CTRL hREC);
	extern T_POS			REditCtrl_GetDispCursorPos    (H_CTRL hREC);
	extern T_POS			REditCtrl_CalcCursorPos       (H_CTRL hREC, T_NUM LineNum, T_POS XPos);
	extern BOOL				REditCtrl_GetCursorLoc        (H_CTRL hREC, T_NUM* pLineNum, T_POS* pXPos, T_POS CursorPos);
	extern BOOL				REditCtrl_IsEndPos            (H_CTRL hREC);
	extern BOOL				REditCtrl_IsTopLine           (H_CTRL hREC);
	extern BOOL				REditCtrl_IsEndLine           (H_CTRL hREC);
	extern BOOL				REditCtrl_EnsureCursorVisible (H_CTRL hREC, T_POS CursorPos);
	extern BOOL				REditCtrl_GetInputEnter       (H_CTRL hREC);
	extern QUAD				REditCtrl_GetAlign            (H_CTRL hREC);
	extern int				REditCtrl_GetStrLen           (H_CTRL hREC);
	extern int				REditCtrl_GetLineNum          (H_CTRL hREC);
	extern int				REditCtrl_GetTopLine          (H_CTRL hREC);
	extern BOOL				REditCtrl_GetAttribute        (H_CTRL hREC, T_POS Index, TObjAttr* pObjAttr);
	extern T_SIZE			REditCtrl_GetMinHeight        (H_CTRL hREC);

	extern BOOL				REditCtrl_ScrollUp            (H_CTRL hREC);
	extern BOOL				REditCtrl_ScrollDown          (H_CTRL hREC);

	extern BOOL				REditCtrl_ShowCursor          (H_CTRL hREC, BOOL bShow);
	extern BOOL				REditCtrl_SetCursorType       (H_CTRL hREC, int Type, BOOL bBlink);
	extern void				REditCtrl_SkipCursorBlink     (void);
	extern BOOL				REditCtrl_CompleteChar        (H_CTRL hREC);

	extern BOOL				REditCtrl_LongKeyProcess      (H_CTRL hREC, KEY Key, BOOL bRefresh);
	extern BOOL				REditCtrl_SetDictionaryType   (H_CTRL hREC, E_CHARSET eCharSet);
	extern E_CHARSET		REditCtrl_GetDictionaryType   (H_CTRL hREC);

	extern BOOL						REditCtrl_SetEditModeSequence(H_CTRL hREC, E_REDITMODE_SEQUENCE_ID eSeqID);
	extern E_REDITMODE_SEQUENCE_ID	REditCtrl_GetEditModeSequence(H_CTRL hREC);
	
	extern QUAD				REditCtrl_CoreHandleEvent     (H_CTRL hEC, void* pEvent);

	extern E_FONT			REditCtrl_SetDefCharFont      (H_CTRL hREC, E_FONT enFont);
	extern BOOL				REditCtrl_SetFontEx	          (H_CTRL hREC, E_FONT enFont, T_NUM StartIndex, T_NUM Cnt);
	extern BOOL				REditCtrl_SetFontExI          (H_CTRL hREC, E_FONT enFont, T_NUM DispStartIndex, T_NUM Cnt);
	extern QUAD				REditCtrl_SetDefCharEffect    (H_CTRL hREC, QUAD Effect);
	extern BOOL				REditCtrl_SetEffectEx         (H_CTRL hREC, QUAD Effect, T_NUM StartIndex, T_NUM Cnt);
	extern BOOL				REditCtrl_SetEffectExI        (H_CTRL hREC, QUAD Effect, T_NUM DispStartIndex, T_NUM Cnt);
	extern BOOL				REditCtrl_SetEffectColorEx	  (H_CTRL hREC, int Effect, T_COLOR Color, T_NUM DispStartIndex, T_NUM Cnt);
	extern T_COLOR			REditCtrl_SetDefCharColor     (H_CTRL hREC, T_COLOR Color);
	extern BOOL				REditCtrl_SetColorEx          (H_CTRL hREC, T_COLOR Color, T_NUM StartIndex, T_NUM Cnt);
	extern BOOL				REditCtrl_SetColorExI         (H_CTRL hREC, T_COLOR Color, T_NUM DispStartIndex, T_NUM Cnt);
	extern BOOL				REditCtrl_SetDefSty           (H_CTRL hREC, TCharStyle CharSty);

	extern E_FONT			REditCtrl_GetDefCharFont      (H_CTRL hREC);
	extern QUAD				REditCtrl_GetDefCharEffect    (H_CTRL hREC);
	extern T_COLOR			REditCtrl_GetDefCharColor     (H_CTRL hREC);
	extern TCharStyle		REditCtrl_GetDefSty           (H_CTRL hREC);
	
	extern BOOL				REditCtrl_AttachInfoProc      (H_CTRL hREC, int ObjType, TObjInfoProc* pObjInfoProc);
	extern BOOL				REditCtrl_DettachInfoProc     (H_CTRL hREC, int ObjType);

	extern T_SIZE			REditCtrl_GetHeightToCursor   (H_CTRL hREC, T_POS CursorPos);
	extern T_SIZE			REditCtrl_GetCurLineHeight    (H_CTRL hREC, T_POS CursorPos);
	extern TLineInfo*		REditCtrl_FindLineWithPos	  (H_CTRL hREC, T_POS Pos);
	extern TLineInfo*		REditCtrl_FindLineWithLineNum (H_CTRL hREC, T_NUM LineNum);

	extern BOOL				REditCtrl_SetQuickSym		  (H_CTRL hREC, BOOL bOn);
	extern BOOL				REditCtrl_SetQuickSymType	  (H_CTRL hREC, T_CSTR TypeStrID);

	//	@maenghs[2008-06-17] 다른 콘트롤에서 dll을 사용하기 위하여 interface를 추가함.
	//	모듈에서는 사용하지 않으므로 APILink로 추가하지 않음
	extern BOOL				REditCtrl_GetSymbolTbl        (H_CTRL hREC, QUAD* pSymTbl, T_NUM* pSymCnt);
	extern BOOL				REditCtrl_IsT9Mode            (H_CTRL hREC);

	extern BOOL				REditCtrl_SetWordList		  (H_CTRL hREC, BOOL bOn);
	extern BOOL				REditCtrl_IsBlock             (H_CTRL hREC);
	extern BOOL				REditCtrl_SetBlockOn		  (H_CTRL hREC, BOOL bOn);

	extern BOOL				REditCtrl_SetKeypadLanguage	  (H_CTRL hREC, E_CHARSET eCharSet);
	extern E_CHARSET		REditCtrl_GetKeypadLanguage   (H_CTRL hREC);
	extern void				REditCtrl_OnMaxText			  (H_CTRL hREC, T_PARAM Component);
	extern BOOL				REditCtrl_SetOemTool		  (H_CTRL hREC, QUAD OemToolID, T_PARAM bOn);
	extern BOOL				REditCtrl_IsOemToolOn		  (H_CTRL hREC, QUAD OemToolID);
	extern BOOL				REditCtrl_IsAutogrowrange	  (H_CTRL hREC, BOOL bOn);
#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_REDITCLTRL_H_
