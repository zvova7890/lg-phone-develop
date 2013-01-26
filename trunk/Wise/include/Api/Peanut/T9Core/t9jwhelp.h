/*******************************************************************************
********************************************************************************

                  COPYRIGHT 1998-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9jwhelp.h

     Description: This file contains the definitions specific to any
                  particular T9 embedded environment.

********************************************************************************
********************************************************************************/

#ifndef _T9JWHELP_H
#define _T9JWHELP_H 1

#define COPY  (T9UINT) 0
#define BUILD (T9UINT) 1

/* Each key is modified by an amount to indicate a diacritic. */
#define DIACRITIC_ADDER     ((T9AuxType) 10)
#define JKEY_INDEX(key)     ((T9AuxType)(T9JWKEYVAL(key) - 1))

#define COMPLETE   (T9UINT) 1
#define INCOMPLETE (T9UINT) 0

typedef enum {J_EXPL_INSERT, J_EXPL_OVERWRITE} JExplAction;

void     T9FARCALL T9JW_SetVirtualFunctions(T9JWFieldInfo *pJWFieldInfo);
void     T9FARCALL T9JW_ResetJWordSetup(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_TimeOutFunc(T9JWFieldInfo *pJWFieldInfo);
T9AuxType T9FARCALL T9JW_RetrieveKeyForSymbolAndNumber(T9JWFieldInfo *pJWFieldInfo, T9SYMB sSym);
T9AuxType T9FARCALL T9JW_RetrieveKeyForSymbol(T9JWFieldInfo *pJWFieldInfo, T9SYMB sSym);
T9STATUS T9FARCALL T9JW_AddKeyFunc(T9JWFieldInfo *pJWFieldInfo, T9KEY eKeyID);
T9STATUS T9FARCALL T9JW_AddExplicitFunc(T9JWFieldInfo *pJWFieldInfo, T9SYMB mKeyID);
T9STATUS T9FARCALL T9JW_GetNextCandidate(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_GetPrevCandidate(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_ExecuteClear(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_MoveLeft(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_MoveRight(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_ExecuteDiacKey(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_BuildWordWithCurrentText(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlBegin(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlEnd(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlSetExtSpell(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlCrlExtSpell(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlCrlCodeVersion(T9U8 *pbDest);
T9STATUS T9FARCALL T9JW_CtrlCrlLDBVersion(T9JWFieldInfo *pJWFieldInfo, T9U8 *pbDest);
T9STATUS T9FARCALL T9JW_CtrlDelWord(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlWordLeft(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_CtrlWordRight(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_FlushFunc(T9JWFieldInfo *pJWFieldInfo, T9MINOR mFlushType);
T9STATUS T9FARCALL T9JW_GetKeyForSymFunc(T9JWFieldInfo *pJWFieldInfo, T9SYMB sSymID, T9AuxType *paKey);
T9STATUS T9FARCALL T9JW_GetKeysForSymsFunc(T9JWFieldInfo *pJWFieldInfo, T9SYMB* sSymID, T9AuxType *paKey);

T9STATUS T9FARCALL T9JW_ExplicifyCharacter(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JW_EnterExplicitSymbol(T9JWFieldInfo *pJWFieldInfo, T9SYMB sSym, JExplAction eAddType);
T9STATUS T9FARCALL T9JW_GetCurrentCompoundOrWord(T9JWFieldInfo *pJWFieldInfo, T9UINT nUpdate, T9UINT nCopyOrBuild);

#endif
