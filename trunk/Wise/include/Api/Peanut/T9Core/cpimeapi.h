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
;**     FileName: cpimeapi.h                                                **
;**                                                                           **
;**  Description: Chinese Phrase Text Input IME Interface Header File.        **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPIMEAPI_H
#define T9CPIMEAPI_H

#include "t9cpapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

typedef enum IMEKEY_e {
    KEY_NONE = 0,       /* 00 :                         */
    KEY_ONE,            /* 01 : 1 .-'                   */
    KEY_TWO,            /* 02                           */
    KEY_THREE,          /* 03                           */
    KEY_FOUR,           /* 04                           */
    KEY_FIVE,           /* 05                           */
    KEY_SIX,            /* 06                           */
    KEY_SEVEN,          /* 07                           */
    KEY_EIGHT,          /* 08                           */
    KEY_NINE,           /* 09                           */
    KEY_ZERO,           /* 10                           */
    KEY_STAR,           /* 11  *                        */
    KEY_POUND,          /* 12  #                        */
    KEY_LEFT,           /* 13  <-                       */
    KEY_RIGHT,          /* 14  ->                       */
    KEY_UP,             /* 15  ^                        */
    KEY_DOWN,           /* 16  v                        */
    KEY_OK,             /* 17  OK                       */
    KEY_CLEAR,          /* 18  clr                      */
    KEY_MENU,           /* 19                           */
    KEY_SOFT1,          /* 20  primary soft key         */
    KEY_SOFT2,          /* 21  secondary soft key       */
    /* the tone keys are added for  IME to be able to save the active key sequence */
    KEY_TONE1,          /* 22  the first tone           */
    KEY_TONE2,          /* 23  the second tone          */
    KEY_TONE3,          /* 24  the third tone           */
    KEY_TONE4,          /* 25  the fourth tone          */
    KEY_TONE5           /* 26  no tone                  */
    ,KEY_MAX            /* COUNTER, NOT TO BE USED      */
} IME_KEY;
typedef enum IME_MOVEDIRECTION_e {
    IME_SET,
    IME_MOVE_LAST,
    IME_MOVE_FORWARD,
    IME_MOVE_BACKWARD,
    IME_MOVELINE_FORWARD,
    IME_MOVELINE_BACKWARD,
    IME_MOVE_NONE
} IME_MOVEDIRECTION;

typedef enum T9CPIME_MODE_e {
    T9CPIME_MODE_BPMF,              /*  0 */
    T9CPIME_MODE_PINYIN,            /*  1 */
    T9CPIME_MODE_STROKE,            /*  2 */
    T9CPIME_MODE_reserve,           /*  3 not used */
    T9CPIME_MODE_NUM,               /*  4 */
    T9CPIME_MODE_abc,               /*  5 */
    T9CPIME_MODE_Abc,               /*  6 */
    T9CPIME_MODE_ABC                /*  7 */
} T9CPIMEMode;

typedef enum {
    T9CPIME_STATE_COMPONENT,        /* 0 */
    T9CPIME_STATE_UDBEDIT,          /* 1 */
    T9CPIME_STATE_JIANPIN           /* 2 */
} T9CPIMEState;

/* T9AW shift state */
typedef enum T9CPIME_SHIFT_STATE_e {
    T9CPIME_abc,
    T9CPIME_Abc,
    T9CPIME_ABC
} T9CPIME_SHIFT_STATE;

#define T9CPKEYDELIMITER KEY_POUND      /* the delimiter could be a pound key */

#define T9CPIME_NEW_LINE          (T9SYMB)0x000a

#define T9CPIME_SELECTIONDELIMITER 0
#define T9CPIME_SPELLDELIMITER '|'      /* vertical bar, it can't be the same as the syllable dilimiter */
#define CPIME_TONE_INVALID 0xFF
#define T9CPIME_SYLLABLEDELIMITER T9CPSYLLABLEDELIMITER  /* this has to be different from T9CPIME_SPELLDELIMITER and they can't be in the range of valid spelling letters */

#define T9CPIME_MAXTEXT  256            /* the maximum length of the text buffer */
#define T9CPIME_MAXSPELL 512            /* different database may have different max number of spells */
#define T9CPIME_MAX_NUM_SPELLs 40       /* the max number of spellings, different database may have different max number of spells */
#define T9CPIME_MAXPHRASE T9CPMAXPAGESIZE   /* the max number of characters that can be held in a selection page */
#define T9CPIME_MAXPAGELEN 2 * (T9CPMAXPHRASESIZE + 1) /* the max number of symbol that can be held in page buffer */

#define T9CPIME_ENGLISHMODE()     (IME_IsInMode(T9CPIME_MODE_abc) || IME_IsInMode(T9CPIME_MODE_Abc) || IME_IsInMode(T9CPIME_MODE_ABC))
#define T9CPIME_NONCHINESEMODE()  (T9CPIME_ENGLISHMODE() || IME_IsInMode(T9CPIME_MODE_NUM))

/* the values of the enum indicates the mode in the text editor */
typedef enum {
    CPIME_TEXTEDIT = 0, /* text edit: the focus for the arrow keys and clear key is on the text */
    CPIME_SPELLEDIT,    /* spell edit: the focus is on the spelling/key sequence */
    CPIME_TONE,         /* tone edit: the focus is on the tone information */
    CPIME_SELECT,       /* selection edit: the focus is on selection page */
    CPIME_UDB_OP        /* UDB operation: see T9CPIME_UDB_OP_STATE */
} T9CP_IMEMODE;

typedef enum {
    T9CPIME_UDB_OP_MENU = 0,   /* menu for choosing edit or delete UDB entry */
    T9CPIME_UDB_OP_DEL_PROMPT, /* prompt for deleting UDB entry */
    T9CPIME_UDB_OP_DEL_FAIL    /* failed to delete */
} T9CPIME_UDB_OP_STATE;

int T9FARCALL IsModeActive(T9CP_IMEMODE eTestMode);
/* return true if selection mode is active, false if not */
#define T9CPIME_SELECTION_STATE() IsModeActive(CPIME_SELECT)

/* BoPoMoFo (Zhu Yin) related definitions */
/*
 * One byte BPMF spelling format:
 *  [ BBPMF bit (bit 7) ][ Uppercase bit (bit 6) ][ BPMF Letter ranging from 0 to 36 (bit 5 - 0) ]
 */
#define T9CPIME_BpmfFirstLetter             T9CPBPMFFIRSTLOWERLETTER
#define T9CPIME_BpmfLastLetter              T9CPBPMFLASTLOWERLETTER
#define T9CPIME_BpmfFirstUnicode            T9CPBpmfFirstUnicode /* unicode for letter Bo */
#define T9CPIME_BpmfLastUnicode             T9CPBpmfFirstUnicode + 37 - 1
#define T9CPIME_IsBpmfLowerCase(bLetter)    T9CPIsBpmfLowerCase(bLetter)
#define T9CPIME_IsBpmfUpperCase(bLetter)    T9CPIsBpmfUpperCase(bLetter)
#define T9CPIME_IsBpmfLetter(bLetter)       T9CPIsBpmfLetter(bLetter)
#define T9CPIME_BpmfLetterToUnicode(bLetter) T9CPBpmfLetterToUnicode(bLetter)

/* IME API */
/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_Init
 *
 *  Description     : UI layer has to call this function before calling any other function in this interface
 *
 *  Pass            : SelectionCanFit, a call back function that tests if the symbol string can be fit 
 *                                      into the selection page display area
 *                                  pass in:psSelectionPage, a pointer pointing to the symbol string
 *                                          nSelectionPageLen, the number of symbol in the string
 *                                  return: 1 if the string can fit
 *                                          0 if the string doesn't fit
 *                    ScrollText, a callback function that sets the start and end of the text window according
 *                                  to the cursor movement passed in
 *                                  pass in: psTxtBuf, pointing to the beginning of the text buffer
 *                                           nTxtBufLen, the length of the text buffer
 *                                           eMove, indicating the movement of the cursor
 *                                           nOldCursor, where the cursor is before the movement
 *                                  return: the new cursor position
 *                    ScrollSpell, a callback function that adjust the spell display window and the current active spell
 *                                  pass in: pbSpellBuf, the spell buffer
 *                                           nSpellBufLen, the length of the spell buffer
 *                                           eMove, the moving direction of the active spell
 *                                           bOldActiveSpell, the active spel position before the move
 *                                  return:  1 if the active spell changes
 *                                           0 if the active spell does not change
 *                                           -1 if already at one end of the spell list, can't scroll anymore.
 *                    SetKeyRepeatable, callback function that sets which keys are repeatable
 *                                  pass in: eKey, the repeatable key
 *                                  return:  None
 *                    T9ReadLdbData, a call back function that is going to used to read PTI database
 *                                  pass in:     
 *                                  return:
 *                    MultitapHandleRequest, a required call back function (empty) for calling T9AWInitialize()
 *                                  pass in: void
 *                                  return: void
 *
 *  Return          : error code indicating if the initialization is successful
 *                    0 means no error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_Init(int T9FARCALL (*SelectionCanFit)(T9SYMB *psSelectionPage, T9UINT nLen),
                         T9UINT T9FARCALL (*ScrollText)(T9SYMB* psTxtBuf, T9UINT nTxtBufLen, IME_MOVEDIRECTION eMove, T9UINT nOldCursor),
                         int T9FARCALL (*ScrollSpell)(T9U8* pbSpellBuf, T9UINT nSpellBufLen, IME_MOVEDIRECTION eMove, T9U8 bOldActiveSpell),
                         void (*SetKeyRepeatable)(IME_KEY eKey),
                         T9ReadLdbData_f T9ReadLdbData,
                         T9HandleRequest_f MultitapHandleRequest);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_SetLanguage
 *
 *  Description     : Set language and reset state as needed.
 *
 *  Pass            : nLdbNum - ldb number
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_SetLanguage(T9UINT nLdbNum);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetChineseLdbNum
 *
 *  Description     : Get the Chinese LDB number
 *
 *  Pass            : none
 *
 *  Return          : nLdbNum - ldb number
 *
 *  note: if 0 is returned, Chinese LDB is not initialized.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL IME_GetChineseLdbNum();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_SetInputMode
 *
 *  Description     : Set the input mode
 *
 *  Pass            : eMode - the desired mode
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_SetInputMode(T9CPIMEMode eMode);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetInputMode
 *
 *  Description     : Get the IME input mode
 *
 *  Pass            : none
 *
 *  Return          : IME input mode
 *
 *---------------------------------------------------------------------------*/
T9CPIMEMode T9FARCALL IME_GetInputMode();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_SetPrevInputMode
 *
 *  Description     : Set the previous input mode
 *
 *  Pass            : eMode - the desired mode
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_SetPrevInputMode(T9CPIMEMode eMode);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetPrevInputMode
 *
 *  Description     : Get the previous IME input mode
 *
 *  Pass            : none
 *
 *  Return          : previous IME input mode
 *
 *---------------------------------------------------------------------------*/
T9CPIMEMode T9FARCALL IME_GetPrevInputMode();


/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_MultitapTimeOut
 *
 *  Description     : Flush multitap key and reset multitap text buffer when timer expires.
 *
 *  Pass            : none
 *
 *  Return          : none
 *
 *---------------------------------------------------------------------------*/
void T9FARCALL IME_MultitapTimeOut();


/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_MultitapInsertMode
 *
 *  Description     : test if T9 multitap is in active insert mode.
 *
 *  Pass            : none
 *
 *  Return          : non-zero if Multitap Insert Mode is true, otherwise 0.
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL IME_MultitapInsertMode();


/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_InsertSymbol
 *
 *  Description     : Insert Symbol to the text buffer from symbol mode
 *
 *  Pass            : symbol to be inserted
 *
 *  Return          : whether the insertion succeed or not
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_InsertSymbol(T9SYMB symb);


/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_IsInMode
 *
 *  Description     : test if the input mode is as passed in
 *
 *  Pass            : eMode - the test mode
 *
 *  Return          : 0 if the mode is not the same as passed in
 *
 *---------------------------------------------------------------------------*/
T9U8     T9FARCALL IME_IsInMode(T9CPIMEMode eMode);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_IsStateActive
 *
 *  Description     : test if the input state is as passed in
 *
 *  Pass            : eState - the test state
 *
 *  Return          : 0 if the state is not the same as passed in
 *
 *---------------------------------------------------------------------------*/
T9U8     T9FARCALL IME_IsStateActive(T9CPIMEState eState);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_IsInputKey
 *
 *  Description     : test if a key is an ambiguous input key in current input mode.
 *
 *  Input           : bKey = the key to be tested
 *
 *  Return          : 1 if true, 0 otherwise
 *
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_IsInputKey(T9U8 bKey);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetCodeVersion
 *
 *  Description     : Wrapper function for getting code version from PTI core,
 *
 *  Pass            : pbCodeVersion - the buffer for storing result
 *                    result length: T9MAXLDBWORDSIZE without null terminator
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_GetCodeVersion(T9U8 *pbCodeVersion);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetLdbVersion
 *
 *  Description     : Wrapper function for getting ldb version from PTI core,
 *
 *  Pass            : pbLdbVersion - the buffer for storing result
 *                    result length: T9MAXLDBWORDSIZE without null terminator
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_GetLdbVersion(T9U8 *pbLdbVersion);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_ValidateLdb
 *
 *  Description     : Validate the language database for the specified language
 *
 *  Pass            : nLdbNum - ldb number
 *
 *  Return          : error codes returned from the PTI core
 *                    T9STATNONE means no error.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_ValidateLdb(T9UINT nLdbNum);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_HandleLogicalKey
 *
 *  Description     : It handles all the short key presses according to the IME internal state
 *
 *  Pass            : bKey - the key code
 *
 *  Return          : T9STATNONE if there is no error
 *                    T9STATERROR if PTI core generic error or invalid key press
 *                    others are the error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_HandleLogicalKey(IME_KEY eKey);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : HandlePressHoldLogicalKey
 *
 *  Description     : It handles all the long key presses (selection or shortcuts)
 *
 *  Pass            : bKey - the key code
 *
 *  Return          : T9STATNONE if there is no error
 *                    T9STATERROR if PTI core generic error or invalid key press
 *                    others are the error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_HandlePressHoldLogicalKey(IME_KEY eKey);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetTextBuf
 *
 *  Description     : Returns the text buffer pointer
 *
 *  Pass            : None
 *
 *  Return          : the text buffer pointer
 *
 *---------------------------------------------------------------------------*/
T9SYMB* T9FARCALL IME_GetTextBuf();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetTextBufLen
 *
 *  Description     : return how many symbol there are in the text buffer
 *
 *  Pass            : None
 *
 *  Return          : the number of symbols in the text buffer
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL IME_GetTextBufLen();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetCursor
 *
 *  Description     : returns the cursor position relative to the start of the text buffer, 
 *                      range 0~GetTextBufLen()
 *
 *  Pass            : None
 *
 *  Return          : the current cursor postion
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL IME_GetCursor();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetActiveSpellIndex
 *
 *  Description     : returns 0-based index of the current active spell
 *
 *  Pass            : None
 *
 *  Return          : 0-based index of the current active spell
 *
 *---------------------------------------------------------------------------*/
T9U8      T9FARCALL IME_GetActiveSpellIndex();

/*-----------------------------------------------------------------------------
 *  Function name   : IME_GetSpellBuf
 *
 *  Description     : Get a pointer to the spell buffer.
 *                    Caller should not write to the buffer.
 *
 *  Output          : ppbSpell - a pointer to the spell buffer
 *
 *  Return          : the length of the spell buffer
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL IME_GetSpellBuf(T9U8** ppbSpell);
T9UINT T9FARCALL IME_GetSpellCount();
T9STATUS T9FARCALL IME_GetNthSpell(T9UINT nIndex, T9CPSpellInfo *psSpell);

/*-----------------------------------------------------------------------------
 *  Function name   : IME_SetMohuPairs
 *
 *  Description     : set the mohu pairs.  Clear the key buffer if phonetic mode is active and
 *                      there is something in the key buffer
 *
 *  Pass            : wMohuPairs - the mohu pair bits
 *
 *  Return          : None
 *
 *---------------------------------------------------------------------------*/
void T9FARCALL IME_SetMohuPairs(T9U16 wMohuPairs);

/*-----------------------------------------------------------------------------
 *  Function name   : IME_AddExplPhoneticSym
 *
 *  Description     : Add an explicit phonetic symbol
 *
 *  Pass            : bSym = the explicit phonetic symbol to be added
 *
 *  Return          : T9STATNONE on success, error otherwise.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_AddExplPhoneticSym(T9U8 bSym);

/*-----------------------------------------------------------------------------
 *  Function name   : IME_GetSelectedComponent
 *
 *  Description     : test if a component is active
 *
 *  Pass            : nothing
 *
 *  Return          : the unicode value of the selected component or 0 if there is not any
 *
 *---------------------------------------------------------------------------*/
T9SYMB T9FARCALL IME_GetSelectedComponent();

/*-----------------------------------------------------------------------------
 *  Function name   : IME_EnableComponent
 *
 *  Description     : Enable/Disable component feature
 *
 *  Pass            : int 0 to disable component, non-zero to enable component
 *
 *  Return          : 0 means success, 1 failure.
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL IME_EnableComponent(int fEnable);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetValidTones
 *
 *  Description     : Get the valid tones for the current key sequence.  This function is also 
 *                    used to test if tone or selection page should be displayed.
 *
 *  Pass            : None
 *
 *  Return          : if CPIME_TONE_INVALID, IME is not in tone mode
 *                    if not, a byte for a bit map of valid tones is returned.
 *                    The tone bit mast is defined as following:
 *                      x      x       x       x       x       x       x       x
 *                                           tone 5   tone 4  tone 3  tone 2  tone 1
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL IME_GetValidTones();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetSelectionPage
 *
 *  Description     : Calculates and returns the selection page buffer and related parameters
 *
 *  Pass            : piLen, a pointer to the length of the selection page
 *                    piSelectionPageHasNext, a pointer to a flag if there is a next page
 *                    piSelectionPageHasPrev, a pointer to a flag if there is a previous page
 *
 *  Return          : T9SYMB pointer pointing to the selection page symbol string
 *                    *piLen, number of symbols in the returned string
 *                    *piSelectionPageHasNext, if there is a next page
 *                    *piSelectionPageHasPrev, if there is a previous page
 *
 *---------------------------------------------------------------------------*/
T9SYMB*  T9FARCALL IME_GetSelectionPage(int* piLen, int* piSelectionPageHasNext, int* piSelectionPageHasPrev);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetCurrSelectionPos
 *
 *  Description     : Get the current selection position
 *
 *  Pass            : None
 *
 *  Return          : current selection position
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL IME_GetCurrSelectionPos();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetNthSelection
 *
 *  Description     : Get the Nth selection
 *
 *  Input           : n = 0-based selection index
 *
 *  Return          : the Nth selection phrase
 *
 *---------------------------------------------------------------------------*/
T9CPPhraseInfo* T9FARCALL IME_GetNthSelection(int n);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : GetKeyLabel
 *
 *  Description     : Return the current key label for the given key ID.
 *
 *  Pass            : eKey, the key ID
 *
 *  Return          : T9SYMB pointer pointing to a null terminated string with the key label.
 *                    A null pointer indicates the key has no active label.
 *
 *---------------------------------------------------------------------------*/
T9SYMB*  T9FARCALL IME_GetKeyLabel(IME_KEY eKey);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : ClearInputs
 *
 *  Description     : clear inputs stored in IME layer
 *
 *  Pass            : bClearContext = 1 : clear context, 0 : keep context
 *
 *  Return          : PTI core error code
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_ClearInputs(T9U8 bClearContext);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_ClearTextBuffer
 *
 *  Description     : clear the text buffer in IME, clear active key sequence and context in PTI core
 *
 *  Pass            : None
 *
 *  Return          : PTI core error code
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_ClearTextBuffer();

#ifndef T9CPNORDB
/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_UdbActivate
 *
 *  Description     : Activate a given UDB so that it becomes the active UDB of
 *                    this thread.  Reset it if the UDB has not been initialized
 *                    or has been corrupted.
 *
 *  Pass            : pUdb = pointer to the UDB
 *                    wDataSize = size of the whole UDB in bytes
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_UdbActivate(T9CPUdbInfo T9FARUDBPOINTER *pUdb,
                                   T9U16 wDataSize);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_UdbReset
 *
 *  Description     : Reset the UDB to its empty state.
 *
 *  Pass            : none
 *
 *  Return          : error codes returned from the PTI core
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL IME_UdbReset();

#endif /* END use RDB */

#ifndef T9CPNOUDB
/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_IsUdbOpState
 *
 *  Description     : check if UDB operation is in the expected state
 *
 *  Pass            : eTestState = expected state
 *
 *  Return          : non-zero if IME is in UDB operation mode and
 *                             UDB operation is in the expected state
 *                    0 otherwise
 *
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_IsUdbOpState(T9CPIME_UDB_OP_STATE eTestState);

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetUDBPhraseBuf
 *
 *  Description     : Returns the UDB editing phrase buffer pointer
 *
 *  Pass            : None
 *
 *  Return          : the UDB editing phrase buffer pointer
 *
 *---------------------------------------------------------------------------*/
T9SYMB* IME_GetUDBPhraseBuf();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetUDBPhraseBufLen
 *
 *  Description     : return how many characters in the UDB phrase editing buffer.
 *
 *  Pass            : None
 *
 *  Return          : the number of characters in the UDB phrase editing buffer.
 *
 *---------------------------------------------------------------------------*/
T9U8 IME_GetUDBPhraseBufLen();

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_GetUdbEditorCursor
 *
 *  Description     : returns the cursor position relative to the start of the UDB Editor
 *                    text buffer, ranging from 0 to IME_GetUDBPhraseBufLen().
 *
 *  Pass            : None
 *
 *  Return          : the current cursor postion in UDB Editor
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL IME_GetUdbEditorCursor();

/*---------------------------------------------------------------------------
 *
 *  Function: IME_StartCPUdbEdit
 *                                 
 *  Synopsis: Enters the PTI UDB editing mode.
 *                                           
 *     Input:
 *
 *    Output:
 *
 *    Return: T9STATNONE on success, otherwise return T9 error code.
 *                                                                            
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_StartCPUdbEdit();

/*---------------------------------------------------------------------------
 *
 *  Function: IME_CancelCPUdbEdit
 *                                 
 *  Synopsis: Exits from the PTI UDB editing mode without saving the UDB object.
 *                                           
 *     Input: 
 *
 *    Output:
 *
 *    Return: T9STATNONE on success, otherwise return T9 error code.
 *                                                                            
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_CancelCPUdbEdit();

/*---------------------------------------------------------------------------
 *
 *  Function: IME_SaveCPUdbEntry
 *                                 
 *  Synopsis: Save the UDB object and exits from the UDB editing mode.
 *                                           
 *     Input: 
 *
 *    Output:
 *
 *    Return: T9STATNONE on success, otherwise return T9 error code.
 *                                                                            
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_SaveCPUdbEntry();

#endif /* END use UDB */

/*-----------------------------------------------------------------------------
 *
 *  Function name   : IME_IsNameInputActive
 *
 *  Description     : check if NameInput feature is active
 *
 *  Pass            : none
 *
 *  Return          : non-zero if IME is in NameInput operation mode
 *                    0 otherwise
 *
 *---------------------------------------------------------------------------*/
int T9FARCALL IME_IsNameInputActive();

/***************************************************************************************
 *  Function name   : IME_SetNameInput
 *
 *  Description     : set the NameInput feature.
 *
 *  Pass            : None
 *
 *  Return          : T9STATNONE on success, error otherwise.
 *
 *****************************************************************************************/
T9STATUS T9FARCALL IME_SetNameInput();

/***************************************************************************************
 *  Function name   : IME_ClearNameInput
 *
 *  Description     : turn off the NameInput feature.
 *
 *  Pass            : None
 *
 *  Return          : T9STATNONE on success, error otherwise.
 *
 *****************************************************************************************/
T9STATUS T9FARCALL IME_ClearNameInput();

T9STATUS T9FARCALL IME_SetSpellType(T9CPSpellType eType);
T9STATUS T9FARCALL IME_ClrSpellType(T9CPSpellType eType);

T9SYMB IME_GetFirstComponent();
T9SYMB IME_GetLastComponent();    

#ifdef T9ALPHABETIC
T9STATUS IME_AWUdbActivate(T9U8 T9FARDATA * pUdb, T9U16 wDataSize);
#endif

/* end of IME api */

#ifdef T9_DEBUG
T9CPSpellInfo * T9FARCALL IME_GetCurrentSpell();
#endif

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* #ifndef T9CPIMEAPI_H */
