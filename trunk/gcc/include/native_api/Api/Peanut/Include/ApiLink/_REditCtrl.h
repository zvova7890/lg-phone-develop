/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT REDIT CONTROL APILINK

	Copyright(c) 2003-2004 BNSoft Corp.

	그룹 : PEANUT
	구분 : APILINK
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.02
	일자 : 2004.09.15
	성명 : 박상호, 이택길
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_REDITCTRL_H_
#define		_BNSOFT__PEANUT_REDITCTRL_H_

#include	"..\REditCtrl.h"

//-------------------------------------------------------------------------------------------------
typedef H_CTRL			(*T_pfnREditCtrl_Create)              (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
typedef H_CTRL			(*T_pfnREditCtrl_CreateEx)            (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
typedef BOOL			(*T_pfnREditCtrl_Destroy)             (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_AssignBuf)           (H_CTRL hREC, T_CSTR pBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnREditCtrl_SetStr)              (H_CTRL hREC, T_CSTR pcszStr);
typedef BOOL			(*T_pfnREditCtrl_InsertStr)           (H_CTRL hREC, T_CSTR pcszStr);
typedef BOOL			(*T_pfnREditCtrl_InsertStrI)          (H_CTRL hREC, TREditBuf* pREditBuf);
typedef BOOL			(*T_pfnREditCtrl_InsertStrEx)         (H_CTRL hREC, T_POS Pos, T_CSTR pcszStr);
typedef BOOL			(*T_pfnREditCtrl_InsertStrExI)        (H_CTRL hREC, T_POS Pos, TREditBuf* pREditBuf);
typedef	BOOL			(*T_pfnREditCtrl_InsertObj)           (H_CTRL hREC, BYTE ObjType, BYTE ObjOrdNum);
typedef BOOL			(*T_pfnREditCtrl_InsertObjEx)         (H_CTRL hREC, T_POS Pos, BYTE ObjType, BYTE ObjOrdNum);
typedef BOOL			(*T_pfnREditCtrl_RemoveStr)           (H_CTRL hREC, T_NUM RemoveCharNum);
typedef BOOL			(*T_pfnREditCtrl_RemoveStrEx)         (H_CTRL hREC, T_POS Pos, T_NUM RemoveCharNum);
typedef BOOL			(*T_pfnREditCtrl_SelectStr)           (H_CTRL hREC, T_POS Pos, T_SIZE Size);
typedef BOOL			(*T_pfnREditCtrl_CutStr)              (H_CTRL hREC, T_STR pszBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnREditCtrl_CutStrI)             (H_CTRL hREC, TREditBuf* pREditBuf);
typedef BOOL			(*T_pfnREditCtrl_CopyStr)             (H_CTRL hREC, T_STR pszBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnREditCtrl_CopyStrI)            (H_CTRL hREC, TREditBuf* pREditBuf);
typedef BOOL			(*T_pfnREditCtrl_PasteStr)            (H_CTRL hREC, T_CSTR pcszStr);
typedef BOOL			(*T_pfnREditCtrl_PasteStrI)           (H_CTRL hREC, TREditBuf* pREditBuf);
typedef BOOL			(*T_pfnREditCtrl_SetMaxChar)          (H_CTRL hREC, T_NUM MaxChar);
typedef BOOL			(*T_pfnREditCtrl_SetEditableMode)     (H_CTRL hREC, QUAD Modes);
typedef BOOL			(*T_pfnREditCtrl_SetEditMode)         (H_CTRL hREC, QUAD Mode);
typedef T_POS			(*T_pfnREditCtrl_SetCursorPos)        (H_CTRL hREC, T_POS CursorPos);
typedef BOOL			(*T_pfnREditCtrl_SetMultiLine)        (H_CTRL hREC, BOOL bMode, int LineGap, int Separator);
typedef int				(*T_pfnREditCtrl_GetMultiLine)        (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_SetInputEnter)       (H_CTRL hREC, BOOL bInputEnter);
typedef BOOL			(*T_pfnREditCtrl_SetAlign)            (H_CTRL hREC, QUAD AlignType);
typedef BOOL			(*T_pfnREditCtrl_SetMinHeight)        (H_CTRL hREC, T_SIZE MinHeight);
typedef T_CSTR			(*T_pfnREditCtrl_GetStr)              (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_GetAttribute)        (H_CTRL hREC, T_POS Index, TObjAttr* pObjAttr);
typedef T_POS			(*T_pfnREditCtrl_GetSelPos)           (H_CTRL hREC);
typedef T_SIZE			(*T_pfnREditCtrl_GetSelStrLen)        (H_CTRL hREC);
typedef T_CSTR			(*T_pfnREditCtrl_GetSelStr)           (H_CTRL hREC);
typedef T_NUM			(*T_pfnREditCtrl_GetMaxChar)          (H_CTRL hREC);
typedef QUAD			(*T_pfnREditCtrl_GetEditableMode)     (H_CTRL hREC);
typedef QUAD			(*T_pfnREditCtrl_GetEditMode)         (H_CTRL hREC);
typedef E_REDITSTATE	(*T_pfnREditCtrl_GetEditState)        (H_CTRL hREC);
typedef T_POS			(*T_pfnREditCtrl_GetCursorPos)        (H_CTRL hREC);
typedef T_POS			(*T_pfnREditCtrl_GetDispCursorPos)    (H_CTRL hREC);
typedef T_POS			(*T_pfnREditCtrl_CalcCursorPos)       (H_CTRL hREC, T_NUM LineNum, T_POS XPos);
typedef BOOL			(*T_pfnREditCtrl_GetCursorLoc)        (H_CTRL hREC, T_NUM* pLineNum, T_POS* pXPos, T_POS CursorPos);
typedef BOOL			(*T_pfnREditCtrl_IsEndPos)            (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_IsTopLine)           (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_IsEndLine)           (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_EnsureCursorVisible) (H_CTRL hREC, T_POS CursorPos);
typedef BOOL			(*T_pfnREditCtrl_GetInputEnter)       (H_CTRL hREC);
typedef QUAD			(*T_pfnREditCtrl_GetAlign)            (H_CTRL hREC);
typedef int				(*T_pfnREditCtrl_GetStrLen)           (H_CTRL hREC);
typedef int				(*T_pfnREditCtrl_GetLineNum)          (H_CTRL hREC);
typedef int				(*T_pfnREditCtrl_GetTopLine)          (H_CTRL hREC);
typedef T_SIZE			(*T_pfnREditCtrl_GetMinHeight)        (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_ScrollUp)            (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_ScrollDown)          (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_ShowCursor)          (H_CTRL hREC, BOOL bShow);
typedef BOOL			(*T_pfnREditCtrl_SetCursorType)       (H_CTRL hREC, int Type, BOOL bBlink);
typedef void			(*T_pfnREditCtrl_SkipCursorBlink)     (void);
typedef BOOL			(*T_pfnREditCtrl_CompleteChar)        (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_LongKeyProcess)      (H_CTRL hREC, KEY Key, BOOL bRefresh);
typedef E_FONT			(*T_pfnREditCtrl_SetDefCharFont)      (H_CTRL hREC, E_FONT enFont);
typedef BOOL			(*T_pfnREditCtrl_SetFontEx)           (H_CTRL hREC, E_FONT enFont, T_NUM StartIndex, T_NUM Cnt);
typedef BOOL			(*T_pfnREditCtrl_SetFontExI)          (H_CTRL hREC, E_FONT enFont, T_NUM DispStartIndex, T_NUM Cnt);
typedef QUAD			(*T_pfnREditCtrl_SetDefCharEffect)    (H_CTRL hREC, QUAD Effect);
typedef BOOL			(*T_pfnREditCtrl_SetEffectEx)         (H_CTRL hREC, QUAD Effect, T_NUM StartIndex, T_NUM Cnt);
typedef BOOL			(*T_pfnREditCtrl_SetEffectExI)        (H_CTRL hREC, QUAD Effect, T_NUM DispStartIndex, T_NUM Cnt);
typedef BOOL			(*T_pfnREditCtrl_SetEffectColorEx)	  (H_CTRL hREC, int Effect, T_COLOR Color, T_NUM DispStartIndex, T_NUM Cnt);
typedef T_COLOR			(*T_pfnREditCtrl_SetDefCharColor)     (H_CTRL hREC, T_COLOR Color);
typedef BOOL			(*T_pfnREditCtrl_SetColorEx)          (H_CTRL hREC, T_COLOR Color, T_NUM StartIndex, T_NUM Cnt);
typedef BOOL			(*T_pfnREditCtrl_SetColorExI)         (H_CTRL hREC, T_COLOR Color, T_NUM DispStartIndex, T_NUM Cnt);
typedef BOOL			(*T_pfnREditCtrl_SetDefSty)           (H_CTRL hREC, TCharStyle CharSty);
typedef E_FONT			(*T_pfnREditCtrl_GetDefCharFont)      (H_CTRL hREC);
typedef QUAD			(*T_pfnREditCtrl_GetDefCharEffect)    (H_CTRL hREC);
typedef T_COLOR			(*T_pfnREditCtrl_GetDefCharColor)     (H_CTRL hREC);
typedef TCharStyle	   	(*T_pfnREditCtrl_GetDefSty)           (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_AttachInfoProc)      (H_CTRL hREC, int ObjType, TObjInfoProc* pObjInfoProc);
typedef BOOL			(*T_pfnREditCtrl_DettachInfoProc)     (H_CTRL hREC, int ObjType);
typedef BOOL			(*T_pfnREditCtrl_SetDictionaryType)   (H_CTRL hREC, E_CHARSET eCharSet);
typedef E_CHARSET		(*T_pfnREditCtrl_GetDictionaryType)   (H_CTRL hREC);
typedef BOOL					(*T_pfnREditCtrl_SetEditModeSequence)   (H_CTRL hREC, E_REDITMODE_SEQUENCE_ID eSeqID);
typedef E_REDITMODE_SEQUENCE_ID	(*T_pfnREditCtrl_GetEditModeSequence)   (H_CTRL hREC);
typedef QUAD			(*T_pfnREditCtrl_CoreHandleEvent)     (H_CTRL hREC, void* pEvent);
typedef T_SIZE			(*T_pfnREditCtrl_GetHeightToCursor)   (H_CTRL hREC, T_POS CursorPos);
typedef T_SIZE			(*T_pfnREditCtrl_GetCurLineHeight)    (H_CTRL hREC, T_POS CursorPos);
typedef TLineInfo*		(*T_pfnREditCtrl_FindLineWithPos)	  (H_CTRL hREC, T_POS Pos);
typedef TLineInfo*		(*T_pfnREditCtrl_FindLineWithLineNum) (H_CTRL hREC, T_NUM LineNum);
typedef BOOL			(*T_pfnREditCtrl_SetQuickSym)		  (H_CTRL hREC, BOOL bOn);
typedef BOOL			(*T_pfnREditCtrl_SetQuickSymType)	  (H_CTRL hREC, T_CSTR TypeStrID);	  
typedef BOOL			(*T_pfnREditCtrl_SetWordList)		  (H_CTRL hREC, BOOL bOn);
typedef BOOL			(*T_pfnREditCtrl_IsBlock)			  (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_SetBlockOn)		  (H_CTRL hREC, BOOL bOn);
typedef BOOL			(*T_pfnREditCtrl_SetKeypadLanguage)   (H_CTRL hREC, E_CHARSET eCharSet);
typedef E_CHARSET		(*T_pfnREditCtrl_GetKeypadLanguage)   (H_CTRL hREC);
typedef BOOL			(*T_pfnREditCtrl_SetOemTool)		  (H_CTRL hREC, QUAD OemToolID, T_PARAM bOn);
typedef BOOL			(*T_pfnREditCtrl_IsOemToolOn)		  (H_CTRL hREC, QUAD OemToolID);

typedef BOOL			(*T_pfnREditCtrl_IsAutogrowrange)	  (H_CTRL hREC, BOOL bOn);
//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnREditCtrl_Create				pfnCreate;
	T_pfnREditCtrl_CreateEx				pfnCreateEx;
	T_pfnREditCtrl_Destroy				pfnDestroy;
	T_pfnREditCtrl_AssignBuf			pfnAssignBuf;
	T_pfnREditCtrl_SetStr				pfnSetStr;
	T_pfnREditCtrl_InsertStr			pfnInsertStr;
	T_pfnREditCtrl_InsertStrI			pfnInsertStrI;
	T_pfnREditCtrl_InsertStrEx			pfnInsertStrEx;
	T_pfnREditCtrl_InsertStrExI			pfnInsertStrExI;
	T_pfnREditCtrl_InsertObj			pfnInsertObj;
	T_pfnREditCtrl_InsertObjEx			pfnInsertObjEx;
	T_pfnREditCtrl_RemoveStr			pfnRemoveStr;
	T_pfnREditCtrl_RemoveStrEx			pfnRemoveStrEx;
	T_pfnREditCtrl_SelectStr			pfnSelectStr;
	T_pfnREditCtrl_CutStr				pfnCutStr;
	T_pfnREditCtrl_CutStrI				pfnCutStrI;
	T_pfnREditCtrl_CopyStr				pfnCopyStr;
	T_pfnREditCtrl_CopyStrI				pfnCopyStrI;
	T_pfnREditCtrl_PasteStr				pfnPasteStr;
	T_pfnREditCtrl_PasteStrI			pfnPasteStrI;
	T_pfnREditCtrl_SetMaxChar			pfnSetMaxChar;
	T_pfnREditCtrl_SetEditableMode		pfnSetEditableMode;
	T_pfnREditCtrl_SetEditMode			pfnSetEditMode;
	T_pfnREditCtrl_SetCursorPos			pfnSetCursorPos;
	T_pfnREditCtrl_SetMultiLine			pfnSetMultiLine;
	T_pfnREditCtrl_SetInputEnter		pfnSetInputEnter;
	T_pfnREditCtrl_SetAlign				pfnSetAlign;
	T_pfnREditCtrl_SetMinHeight			pfnSetMinHeight;
	T_pfnREditCtrl_GetStr				pfnGetStr;
	T_pfnREditCtrl_GetAttribute			pfnGetAttribute;
	T_pfnREditCtrl_GetSelPos			pfnGetSelPos;
	T_pfnREditCtrl_GetSelStrLen			pfnGetSelStrLen;
	T_pfnREditCtrl_GetSelStr			pfnGetSelStr;
	T_pfnREditCtrl_GetMaxChar			pfnGetMaxChar;
	T_pfnREditCtrl_GetEditableMode		pfnGetEditableMode;
	T_pfnREditCtrl_GetEditMode			pfnGetEditMode;
	T_pfnREditCtrl_GetEditState			pfnGetEditState;
	T_pfnREditCtrl_GetCursorPos			pfnGetCursorPos;
	T_pfnREditCtrl_GetDispCursorPos		pfnGetDispCursorPos;
	T_pfnREditCtrl_CalcCursorPos		pfnCalcCursorPos;
	T_pfnREditCtrl_GetCursorLoc			pfnGetCursorLoc;
	T_pfnREditCtrl_IsEndPos				pfnIsEndPos;
	T_pfnREditCtrl_IsTopLine			pfnIsTopLine;
	T_pfnREditCtrl_IsEndLine			pfnIsEndLine;
	T_pfnREditCtrl_EnsureCursorVisible	pfnEnsureCursorVisible;
	T_pfnREditCtrl_GetInputEnter		pfnGetInputEnter;
	T_pfnREditCtrl_GetAlign				pfnGetAlign;
	T_pfnREditCtrl_GetStrLen			pfnGetStrLen;
	T_pfnREditCtrl_GetLineNum			pfnGetLineNum;
	T_pfnREditCtrl_GetTopLine			pfnGetTopLine;
	T_pfnREditCtrl_GetMinHeight			pfnGetMinHeight;
	T_pfnREditCtrl_ScrollUp				pfnScrollUp;
	T_pfnREditCtrl_ScrollDown			pfnScrollDown;
	T_pfnREditCtrl_ShowCursor			pfnShowCursor;
	T_pfnREditCtrl_SetCursorType		pfnSetCursorType;
	T_pfnREditCtrl_SkipCursorBlink		pfnSkipCursorBlink;
	T_pfnREditCtrl_CompleteChar			pfnCompleteChar;
	T_pfnREditCtrl_LongKeyProcess		pfnLongKeyProcess;
	T_pfnREditCtrl_SetDefCharFont		pfnSetDefCharFont;
	T_pfnREditCtrl_SetFontEx			pfnSetFontEx;
	T_pfnREditCtrl_SetFontExI			pfnSetFontExI;
	T_pfnREditCtrl_SetDefCharEffect		pfnSetDefCharEffect;
	T_pfnREditCtrl_SetEffectEx			pfnSetEffectEx;
	T_pfnREditCtrl_SetEffectExI			pfnSetEffectExI;
	T_pfnREditCtrl_SetEffectColorEx		pfnSetEffectColorEx;
	T_pfnREditCtrl_SetDefCharColor		pfnSetDefCharColor;
	T_pfnREditCtrl_SetColorEx			pfnSetColorEx;
	T_pfnREditCtrl_SetColorExI			pfnSetColorExI;
	T_pfnREditCtrl_SetDefSty			pfnSetDefSty;
	T_pfnREditCtrl_GetDefCharFont		pfnGetDefCharFont;
	T_pfnREditCtrl_GetDefCharEffect		pfnGetDefCharEffect;
	T_pfnREditCtrl_GetDefCharColor		pfnGetDefCharColor;
	T_pfnREditCtrl_GetDefSty			pfnGetDefSty;
	T_pfnREditCtrl_AttachInfoProc		pfnAttachInfoProc;
	T_pfnREditCtrl_DettachInfoProc		pfnDettachInfoProc;
	T_pfnREditCtrl_SetDictionaryType	pfnSetDictionaryType;
	T_pfnREditCtrl_GetDictionaryType	pfnGetDictionaryType;
	T_pfnREditCtrl_SetEditModeSequence	pfnSetEditModeSequence;
	T_pfnREditCtrl_GetEditModeSequence	pfnGetEditModeSequence;
	T_pfnREditCtrl_CoreHandleEvent		pfnCoreHandleEvent;
	T_pfnREditCtrl_GetHeightToCursor	pfnGetHeightToCursor;
	T_pfnREditCtrl_GetCurLineHeight		pfnGetCurLineHeight;
	T_pfnREditCtrl_FindLineWithPos		pfnFindLineWithPos;
	T_pfnREditCtrl_FindLineWithLineNum  pfnFindLineWithLineNum;
	T_pfnREditCtrl_SetQuickSym			pfnSetQuickSym;
	T_pfnREditCtrl_SetQuickSymType		pfnSetQuickSymType;
	T_pfnREditCtrl_GetMultiLine			pfnGetMultiLine;
	T_pfnREditCtrl_SetWordList			pfnSetWordList;
	T_pfnREditCtrl_IsBlock				pfnIsBlock;
	T_pfnREditCtrl_SetBlockOn			pfnSetBlockOn;
	T_pfnREditCtrl_SetKeypadLanguage	pfnSetKeypadLanguage;
	T_pfnREditCtrl_GetKeypadLanguage	pfnGetKeypadLanguage;
	T_pfnREditCtrl_SetOemTool			pfnSetOemTool;
	T_pfnREditCtrl_IsOemToolOn			pfnIsOemToolOn;
	T_pfnREditCtrl_IsAutogrowrange		pfnIsAutogrowrange;
} TApiGrp_REditCtrl;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		REditCtrl_Create(p1,p2,p3,p4,p5,p6)			__ApiLink6(REditCtrl,Create,p1,p2,p3,p4,p5,p6)
	#define		REditCtrl_CreateEx(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(REditCtrl,CreateEx,p1,p2,p3,p4,p5,p6,p7)
	#define		REditCtrl_Destroy(p1)						__ApiLink1(REditCtrl,Destroy,p1)
	#define		REditCtrl_AssignBuf(p1,p2,p3)				__ApiLink3(REditCtrl,AssignBuf,p1,p2,p3)
	#define		REditCtrl_SetStr(p1,p2)						__ApiLink2(REditCtrl,SetStr,p1,p2)
	#define		REditCtrl_InsertStr(p1,p2)					__ApiLink2(REditCtrl,InsertStr,p1,p2)
	#define		REditCtrl_InsertStrI(p1,p2)					__ApiLink2(REditCtrl,InsertStrI,p1,p2)
	#define		REditCtrl_InsertStrEx(p1,p2,p3)				__ApiLink3(REditCtrl,InsertStrEx,p1,p2,p3)
	#define		REditCtrl_InsertStrExI(p1,p2,p3)			__ApiLink3(REditCtrl,InsertStrExI,p1,p2,p3)
	#define		REditCtrl_InsertObj(p1,p2,p3)           	__ApiLink3(REditCtrl,InsertObj,p1,p2,p3)
	#define		REditCtrl_InsertObjEx(p1,p2,p3,p4)			__ApiLink4(REditCtrl,InsertObjEx,p1,p2,p3,p4)
	#define		REditCtrl_RemoveStr(p1,p2)					__ApiLink2(REditCtrl,RemoveStr,p1,p2)
	#define		REditCtrl_RemoveStrEx(p1,p2,p3)				__ApiLink3(REditCtrl,RemoveStrEx,p1,p2,p3)
	#define		REditCtrl_SelectStr(p1,p2,p3)				__ApiLink3(REditCtrl,SelectStr,p1,p2,p3)
	#define		REditCtrl_CutStr(p1,p2,p3)					__ApiLink3(REditCtrl,CutStr,p1,p2,p3)
	#define		REditCtrl_CutStrI(p1,p2)					__ApiLink2(REditCtrl,CutStrI,p1,p2)
	#define		REditCtrl_CopyStr(p1,p2,p3)					__ApiLink3(REditCtrl,CopyStr,p1,p2,p3)
	#define		REditCtrl_CopyStrI(p1,p2)					__ApiLink2(REditCtrl,CopyStrI,p1,p2)
	#define		REditCtrl_PasteStr(p1,p2)					__ApiLink2(REditCtrl,PasteStr,p1,p2)
	#define		REditCtrl_PasteStrI(p1,p2)					__ApiLink2(REditCtrl,PasteStrI,p1,p2)
	#define		REditCtrl_SetMaxChar(p1,p2)					__ApiLink2(REditCtrl,SetMaxChar,p1,p2)
	#define		REditCtrl_SetEditableMode(p1,p2)			__ApiLink2(REditCtrl,SetEditableMode,p1,p2)
	#define		REditCtrl_SetEditMode(p1,p2)				__ApiLink2(REditCtrl,SetEditMode,p1,p2)
	#define		REditCtrl_SetCursorPos(p1,p2)				__ApiLink2(REditCtrl,SetCursorPos,p1,p2)
	#define		REditCtrl_SetMultiLine(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetMultiLine,p1,p2,p3,p4)
	#define		REditCtrl_GetMultiLine(p1)					__ApiLink1(REditCtrl,GetMultiLine,p1)
	#define		REditCtrl_SetInputEnter(p1,p2)				__ApiLink2(REditCtrl,SetInputEnter,p1,p2)
	#define		REditCtrl_SetAlign(p1,p2)					__ApiLink2(REditCtrl,SetAlign,p1,p2)
	#define		REditCtrl_SetMinHeight(p1,p2)				__ApiLink2(REditCtrl,SetMinHeight,p1,p2)
	#define		REditCtrl_GetStr(p1)						__ApiLink1(REditCtrl,GetStr,p1)
	#define		REditCtrl_GetAttribute(p1,p2,p3)			__ApiLink3(REditCtrl,GetAttribute,p1,p2,p3)
	#define		REditCtrl_GetSelPos(p1)						__ApiLink1(REditCtrl,GetSelPos,p1)
	#define		REditCtrl_GetSelStrLen(p1)					__ApiLink1(REditCtrl,GetSelStrLen,p1)
	#define		REditCtrl_GetSelStr(p1)						__ApiLink1(REditCtrl,GetSelStr,p1)
	#define		REditCtrl_GetMaxChar(p1)					__ApiLink1(REditCtrl,GetMaxChar,p1)
	#define		REditCtrl_GetEditableMode(p1)				__ApiLink1(REditCtrl,GetEditableMode,p1)
	#define		REditCtrl_GetEditMode(p1)					__ApiLink1(REditCtrl,GetEditMode,p1)
	#define		REditCtrl_GetEditState(p1)					__ApiLink1(REditCtrl,GetEditState,p1)
	#define		REditCtrl_GetCursorPos(p1)					__ApiLink1(REditCtrl,GetCursorPos,p1)
	#define		REditCtrl_GetDispCursorPos(p1)				__ApiLink1(REditCtrl,GetDispCursorPos,p1)
	#define		REditCtrl_CalcCursorPos(p1,p2,p3)			__ApiLink3(REditCtrl,CalcCursorPos,p1,p2,p3)
	#define		REditCtrl_GetCursorLoc(p1,p2,p3,p4)			__ApiLink4(REditCtrl,GetCursorLoc,p1,p2,p3,p4)
	#define		REditCtrl_IsEndPos(p1)						__ApiLink1(REditCtrl,IsEndPos,p1)
	#define		REditCtrl_IsTopLine(p1)						__ApiLink1(REditCtrl,IsTopLine,p1)
	#define		REditCtrl_IsEndLine(p1)						__ApiLink1(REditCtrl,IsEndLine,p1)
	#define		REditCtrl_EnsureCursorVisible(p1,p2)		__ApiLink2(REditCtrl,EnsureCursorVisible,p1,p2)
	#define		REditCtrl_GetInputEnter(p1)					__ApiLink1(REditCtrl,GetInputEnter,p1)
	#define		REditCtrl_GetAlign(p1)						__ApiLink1(REditCtrl,GetAlign,p1)
	#define		REditCtrl_GetStrLen(p1)						__ApiLink1(REditCtrl,GetStrLen,p1)
	#define		REditCtrl_GetLineNum(p1)					__ApiLink1(REditCtrl,GetLineNum,p1)
	#define		REditCtrl_GetTopLine(p1)					__ApiLink1(REditCtrl,GetTopLine,p1)
	#define		REditCtrl_GetMinHeight(p1)					__ApiLink1(REditCtrl,GetMinHeight,p1)
	#define		REditCtrl_ScrollUp(p1)						__ApiLink1(REditCtrl,ScrollUp,p1)
	#define		REditCtrl_ScrollDown(p1)					__ApiLink1(REditCtrl,ScrollDown,p1)
	#define		REditCtrl_ShowCursor(p1,p2)					__ApiLink2(REditCtrl,ShowCursor,p1,p2)
	#define		REditCtrl_SetCursorType(p1,p2,p3)			__ApiLink3(REditCtrl,SetCursorType,p1,p2,p3)
	#define		REditCtrl_SkipCursorBlink()					__ApiLink0(REditCtrl,SkipCursorBlink)
	#define		REditCtrl_CompleteChar(p1)					__ApiLink1(REditCtrl,CompleteChar,p1)
	#define		REditCtrl_LongKeyProcess(p1,p2,p3)			__ApiLink3(REditCtrl,LongKeyProcess,p1,p2,p3)
	#define		REditCtrl_SetDefCharFont(p1,p2)				__ApiLink2(REditCtrl,SetDefCharFont,p1,p2)
	#define		REditCtrl_SetFontEx(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetFontEx,p1,p2,p3,p4)
	#define		REditCtrl_SetFontExI(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetFontExI,p1,p2,p3,p4)
	#define		REditCtrl_SetDefCharEffect(p1,p2)			__ApiLink2(REditCtrl,SetDefCharEffect,p1,p2)
	#define		REditCtrl_SetEffectEx(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetEffectEx,p1,p2,p3,p4)
	#define		REditCtrl_SetEffectExI(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetEffectExI,p1,p2,p3,p4)
	#define		REditCtrl_SetEffectColorEx(p1,p2,p3,p4,p5)	__ApiLink5(REditCtrl,SetEffectColorEx,p1,p2,p3,p4,p5)
	#define		REditCtrl_SetDefCharColor(p1,p2)			__ApiLink2(REditCtrl,SetDefCharColor,p1,p2)
	#define		REditCtrl_SetColorEx(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetColorEx,p1,p2,p3,p4)
	#define		REditCtrl_SetColorExI(p1,p2,p3,p4)			__ApiLink4(REditCtrl,SetColorExI,p1,p2,p3,p4)
	#define		REditCtrl_SetDefSty(p1,p2)					__ApiLink2(REditCtrl,SetDefSty,p1,p2)
	#define		REditCtrl_GetDefCharFont(p1)				__ApiLink1(REditCtrl,GetDefCharFont,p1)
	#define		REditCtrl_GetDefCharEffect(p1)				__ApiLink1(REditCtrl,GetDefCharEffect,p1)
	#define		REditCtrl_GetDefCharColor(p1)				__ApiLink1(REditCtrl,GetDefCharColor,p1)
	#define		REditCtrl_GetDefSty(p1)						__ApiLink1(REditCtrl,GetDefSty,p1)
	#define		REditCtrl_AttachInfoProc(p1,p2,p3)			__ApiLink3(REditCtrl,AttachInfoProc,p1,p2,p3)
	#define		REditCtrl_DettachInfoProc(p1,p2)			__ApiLink2(REditCtrl,DettachInfoProc,p1,p2)
	#define		REditCtrl_SetDictionaryType(p1,p2)			__ApiLink2(REditCtrl,SetDictionaryType,p1,p2)
	#define		REditCtrl_GetDictionaryType(p1)				__ApiLink1(REditCtrl,GetDictionaryType,p1)
	#define		REditCtrl_SetEditModeSequence(p1,p2)		__ApiLink2(REditCtrl,SetEditModeSequence,p1,p2)
	#define		REditCtrl_GetEditModeSequence(p1)			__ApiLink1(REditCtrl,GetEditModeSequence,p1)
	#define		REditCtrl_CoreHandleEvent(p1,p2)			__ApiLink2(REditCtrl,CoreHandleEvent,p1,p2)
	#define		REditCtrl_GetHeightToCursor(p1,p2)			__ApiLink2(REditCtrl,GetHeightToCursor,p1,p2)
	#define		REditCtrl_GetCurLineHeight(p1,p2)			__ApiLink2(REditCtrl,GetCurLineHeight,p1,p2)
	#define		REditCtrl_FindLineWithPos(p1,p2)			__ApiLink2(REditCtrl,FindLineWithPos,p1,p2)
	#define		REditCtrl_FindLineWithLineNum(p1,p2)		__ApiLink2(REditCtrl,FindLineWithLineNum,p1,p2)
	#define		REditCtrl_SetQuickSym(p1,p2)				__ApiLink2(REditCtrl,SetQuickSym,p1,p2)
	#define		REditCtrl_SetQuickSymType(p1,p2)			__ApiLink2(REditCtrl,SetQuickSymType,p1,p2)
	#define		REditCtrl_SetWordList(p1,p2)				__ApiLink2(REditCtrl,SetWordList,p1,p2)
	#define		REditCtrl_IsBlock(p1)						__ApiLink1(REditCtrl,IsBlock,p1)
	#define		REditCtrl_SetBlockOn(p1,p2)					__ApiLink2(REditCtrl,SetBlockOn,p1,p2)
	#define		REditCtrl_SetKeypadLanguage(p1,p2)			__ApiLink2(REditCtrl,SetKeypadLanguage,p1,p2)
	#define		REditCtrl_GetKeypadLanguage(p1)				__ApiLink1(REditCtrl,GetKeypadLanguage,p1)
	#define		REditCtrl_SetOemTool(p1,p2,p3)				__ApiLink3(REditCtrl,SetOemTool,p1,p2,p3)
	#define		REditCtrl_IsOemToolOn(p1,p2)				__ApiLink2(REditCtrl,IsOemToolOn,p1,p2)

	#define		REditCtrl_IsAutogrowrange(p1,p2)			__ApiLink2(REditCtrl,IsAutogrowrange,p1,p2)

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__PEANUT_REDITCTRL_H_
