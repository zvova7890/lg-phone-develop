/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9jword.h

     Description: Utilities for Japanese core code.  Heap manager, memory
                  manager, linked list utility, etc.


********************************************************************************
********************************************************************************/

#ifndef T9JWORD_H
#define T9JWORD_H
#define GETSIZEOFAUTOWORDHEAD (sizeof(T9U16) * (2 + T9JW_AUTOWORDOFFSETS * 2))
typedef enum { NONMATCH = 0, CHARMATCH, KEYMATCH, EXACTMATCH } MATCH;
#define AutoWordCandidateSize(nKey, nMidaLen) ((sizeof(T9U8) * 2) + (sizeof(T9U8) * nKey)     + (sizeof(T9SYMB) * nMidaLen))
#define AutoWordNodeSize(cur)                 ((sizeof(T9U8) * 2) + (sizeof(T9U8) * (*(cur))) + (sizeof(T9SYMB) * (*(cur+1))))
#define NextAutoWordNode(cur)                 (cur + AutoWordNodeSize(cur))
#define KeyLenght(cur)                        (*(cur))
#define MidaLenght(cur)                       (*(cur + 1))
#define AutoWordDataPtr(cur)                  (cur + 2)
#define GetBlockNum(c)                        ((T9U8)((((c & 0xF0) >> 4) - 1) % T9JW_AUTOWORDOFFSETS))
#endif

