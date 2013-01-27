/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 2004-2007 TEGIC COMMUNICATIONS               **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: t9cpime.h                                                   **
;**                                                                           **
;**  Description: Chinese Phrase Text Input IME Interface Header File.        **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPIME_H
#define T9CPIME_H

#include "t9cpapi.h"
#include "cpimeapi.h"
#include "t9awapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/****************** ime definitions *************/

/* T9CPIME_MAXSELECTIONPAGENEXT is the max number of pages that the text editor can next.  T9CPIME_SELECTIONPAGE::bPhrasesPerPage 
 * is used to save the number of phrases per selection page.
 * The reason is that the selection page can contain phrases with various number of characters.  Saving 
 * the number of phrases per page is a way to make sure when the user goes to the next page and then 
 * the previous page, the same page would be displayed.  For example, if the screen can display 
 * 5 characters at most,
 * the first page:      A B C D E
 * the second page:     F G H I
 * the third page:      JK L M N
 * if the users is at the second page and "JK" can't be shown because the screen can hold only 5 chars
 * the next page would be the third page.  If the user wants to show the previous page, which is the second
 * page, at this time, we would retrieve "E F G H I" to fill up the selection page if we did not have the 
 * number of phrases per page information
 */
#define T9CPIME_MAXSELECTIONPAGENEXT 40

/* assume the current phrase is always the one after the current page */
#define T9CPIME_SELECTIONPAGEPREV 0
#define T9CPIME_SELECTIONPAGENEXT 1
#define IME_SYMBOL_SPACE 0x20

typedef struct T9CPIME_SELECTIONPAGE_s {
    T9CPPhraseInfo  psPage[T9CPIME_MAXPHRASE + 1];         /* the selection page in array */
    T9SYMB  pPage[T9CPIME_MAXPAGELEN];      /* the selection page in string */
    T9UINT  nPageLen;                       /* the length of the selection page */
    T9U8    bHasNextPage;                   /* indicating if the current selection page has a next page */
    T9U8    bCurrentPage;                   /* the 0-based index of the current selection page */
    T9U8    bCurrentSelection;              /* the 0-based index of the currect selection */
    T9U8    bPhrasesPerPage[T9CPIME_MAXSELECTIONPAGENEXT]; /* saves the number of phrases for every selection page */
    T9U8    bSelectionPageMove;             /* a flag indicating if last selection page move is next or previous */
    int T9FARCALL (*SelectionCanFit)(T9SYMB *psSelectionPage, T9UINT uiLen); /* the call back function */
} T9CPIME_SELECTIONPAGE;


/* the values of the enum indicates the 
 * soft key related 
 * soft key labels */
typedef enum {
    IME_LABEL_NONE = 0,
#ifndef T9CPNOUDB
    IME_LABEL_SAVE,
    IME_LABEL_DELETE,
    IME_LABEL_UDB_OP_MENU,
#endif
    IME_LABEL_BACK
} IME_LABEL;

typedef struct IME_SOFTKEY_s {
    IME_LABEL iLabel; /* the index of the label */
    int T9FARCALL (*PressSoftKey)();
} IME_SOFTKEY;

typedef struct T9CP_IME_s {
    T9U8    pbSpell[T9CPIME_MAXSPELL]; /* the spell buffer */
    T9UINT  nSpellLen;              /* current length of the spell buffer */
    T9U8    bActiveSpell;           /* 0-based index of the active spell */
    T9U8    bDefaultSpell;          /* 0-based index of the core's default active spell */
    T9U8    bSpellCount;            /* spell count in the spell buffer */
    T9CP_IMEMODE eMode;
    IME_SOFTKEY sSoftKey1;
    IME_SOFTKEY sSoftKey2;
    T9U8    bValidTones;            /* the valid tone, for tone cycling */
    T9CPFieldInfo   sCPFieldInfo;   /* field info for PTI chinese */
    T9AWFieldInfo   sAWFieldInfo;   /* field info for english mode */
    T9SYMB  psTxtBuf[T9CPIME_MAXTEXT];   /* The text buffer */
    T9AuxType paAuxBuf[T9CPIME_MAXTEXT]; /* The aux buffer for AW core */
#ifndef T9ALPHABETIC
    T9UINT nCursor;
    T9UINT nTxtBufLen;
#endif
    T9CPIME_SELECTIONPAGE sSelectionPage;
    T9UINT T9FARCALL (*ScrollText)(T9SYMB* psTxtBuf, T9UINT nTxtBufLen, IME_MOVEDIRECTION eMove, T9UINT nOldCursor);  /* call back function, nCursor should be the value after the move */
    int T9FARCALL (*ScrollSpell)(T9U8* pbSpellBuf, T9UINT nSpellBufLen, IME_MOVEDIRECTION eMove, T9U8 bOldActiveSpell); /* call back function, returning if the active spell changes */
    void (*SetKeyRepeatable)(IME_KEY eKey);
    T9SYMB  sComp;                  /* the selected component if non-zero */
    T9CPSpellInfo sStemSpell;       /* stem spell for stem holding */
    T9U8 pbSpellIndex[T9CPIME_MAX_NUM_SPELLs];  /* the 0 based spell index in core */
#ifndef T9CPNOUDB
    T9CPIME_UDB_OP_STATE eUdbOpState; /* state within UDB operations */
    T9UINT  nUdbEditorCursor;       /* The position of the cursor in the UDB Editor, value from 0 to bUdbPhraseLen */
    T9SYMB  pUdbPhrase[T9CPMAXUDBPHRASESIZE]; 
    T9U8    bUdbPhraseLen;
    T9U8    pUdbSpell[T9CPIME_MAXSPELL]; 
    T9U8    bUdbSpellLen;
#endif

#ifdef T9_DEBUG
    T9CPSpellInfo sCurrentSpell;
#endif
    T9CPIMEMode bInputMode;         /* current input mode */
    T9CPIMEMode bPrevMode;          /* for symbol mode poping previously used mode */
} T9CP_IME;

/****************** Macro definitions ******************/
#define IME_AWGetState()    (sCPIME.sAWFieldInfo.G.dwStateBits)

/****************** function prototypes ****************/
T9STATUS T9FARCALL HandleTxtInputKey(IME_KEY eKey);

T9STATUS T9FARCALL SetActiveMode(T9CP_IMEMODE eSetMode);

T9STATUS T9FARCALL MoveSelectionPage(IME_KEY eKey);
T9STATUS T9FARCALL InsertSelection(T9U8 bSelectionIndex); /* insert the 0-based selected item to text buffer */
T9STATUS T9FARCALL MoveCursor(IME_KEY eKey);
T9STATUS T9FARCALL MoveActiveSpell(T9U8 *pbSpellBuf, T9UINT nSpellBufLen,
                                   IME_KEY eKey);
T9STATUS T9FARCALL ResetSelection();
T9STATUS T9FARCALL InsertSymbol(T9SYMB symb);
T9STATUS T9FARCALL RemoveSymbol();
T9STATUS T9FARCALL SetSpellBuffer();
T9STATUS T9FARCALL SetActiveSpell(T9U8 bActiveSpell, int fStemHold);
T9UINT T9FARCALL ToggleAWCPSpells();

int T9FARCALL IME_PromptForDeleteUdbEntry();
int T9FARCALL IME_CancelDeleteUdbEntry();
int T9FARCALL IME_DeleteCPUdbEntry();

int T9FARCALL IsComponent(T9U16 wUnicode);

T9FieldInfo* T9FARCALL IME_GetAWG();

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* #ifndef T9CPIME_H */
