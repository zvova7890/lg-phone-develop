/*******************************************************************************
********************************************************************************

                    COPYRIGHT 1999-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9judb.h

     Description: Header file for Japanese User Database module


********************************************************************************
********************************************************************************/

#ifndef T9JUDB_H
#define T9JUDB_H
/* Flags for T9JUdbSubHeader's bFlags field. */
#define YOMI_ALREADY_IN_JLDB_MASK   ((T9U8)0x80)
#define UDB_WORD_CAN_INFLECT_MASK   ((T9U8)0x40)
#define MARKED_FOR_DELETION_MASK    ((T9U8)0x01)

/* Maximum number of Japanese UDB entries. Arbitrary...*/
#define MAX_JUDB_ENTRIES            255

typedef struct T9JUdbSubHeader_s {
   T9U8  bFlags;
   T9U8  bTimeStamp;
   T9SYMB  sYCount;     /* size of Yomi */
}T9JUdbSubHeader;

typedef struct T9JYomiReorderSubHeader_s {
   T9U16 wTimestamp; /* Time Stamp for each reorder entry                   */
   T9U8  bSelLen;    /* length of key sequence                              */
   T9U8  bData[1];   /* position of first byte of data                      */
   /* Data area is used as following                                        */
   /*   T9U8 bOrder[T9JWYOMIREORDERCOUNT];                                    */
   /* Value must be between 1 and T9JWYOMIREORDERCOUNT. '0' means no data.    */
   /*   T9U8 bKeys[n];                                                      */
   /*   T9U8 bSyms[T9JWYOMIREORDERCOUNT][n];                                  */
   /* n = bSelLen / 2 + bSelLen % 1                                         */
   /* keys encoded 1-9, A=0, B=1+diacr, C=2+diacr, D=3+diacr, E=4+diacr,    */
   /*                F=6+1diacr, 0=6+2diacr                                 */
}T9JYomiReorderSubHeader;


#define NextJUdbRecordPtr(pHdr)    \
  ((T9JUdbSubHeader *)((T9U8 *)pHdr + sizeof(T9JUdbSubHeader) + (pHdr->sYCount * T9SYMBOLWIDTH)))

/* Body size (in bytes) for a yomi-reorder entry. */
#define YomiReorderBodyBytes(len)  \
  (T9JWYOMIREORDERCOUNT + (((len) + 1) / 2) * (T9JWYOMIREORDERCOUNT + 1))

/* Total size (in symbols) for a yomi-reorder entry, given the byte county. */
/* (Note that -1 is because T9JYomiReorderSubHeader has 1 byte of data in decl.) */
#define YomiReorderSize(len)  \
  ((sizeof(T9JYomiReorderSubHeader) - 1 + YomiReorderBodyBytes(len) + \
    T9SYMBOLWIDTH - 1) / T9SYMBOLWIDTH)

#define NextJYomiReorderRecordPtr(pHdr) \
{ pHdr = (T9JYomiReorderSubHeader *)((T9SYMB *)pHdr + YomiReorderSize(pHdr->bSelLen));   \
  T9JW_DEBUGFILTER(assert(((T9U32)pHdr & (T9U32)0x1) == 0);) /* check word alignment */      \
}
  
#define GETCLASSBIT(i) (((i)&0x80)>>4)
#define SETCLASSBIT(i) \
{ i = (T9U8)((i)|0x80);}

#define GETORDERBIT(i) ((i) & 0x7F)

#define INCREASEORDER(i) \
{ i++;}

#define SETORDER(i) \
{ i=1;}

#define RESETORDER(i) \
{	T9U8 temp = i&0x80;\
	i=0;\
	if (temp) SETCLASSBIT(i);\
}

#define IS_UDB1(pUdb, pJWFieldInfo)	(pUdb == pJWFieldInfo->pUdbInfo)
#define IS_UDB2(pUdb, pJWFieldInfo)	(pUdb == pJWFieldInfo->pAutoUdbInfo)

/* Helpful macros. */
/* The Udb data area pointer */
#define JWUdbData(udb) ((T9U8 T9FARUDBPOINTER*)udb->sDataArea)
/* Macro to get actual number of bytes in the udb header area */
#define JWUdbHeaderBytes(udb)    \
            ((T9UINT)(JWUdbData(udb) - (T9U8 T9FARUDBPOINTER*)udb))
/* Macro to get actual number of bytes in the udb data area */
#define JWUdbDataAreaBytes(udb)    \
            ((T9UINT)(udb->wDataSize - JWUdbHeaderBytes(udb)))
/* Macro to get actual number of symbols in the udb data area */
#define JWUdbDataAreaSymbols(udb)   \
            ((T9UINT)(JWUdbDataAreaBytes(udb) >> (T9SYMBOLWIDTH - 1)))

#endif /* T9JUDB_H */

/*---------------------------------- eof ---------------------------------*/
