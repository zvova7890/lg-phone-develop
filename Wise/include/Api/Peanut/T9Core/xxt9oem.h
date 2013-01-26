/*******************************************************************************
********************************************************************************

                  COPYRIGHT 1998-2005 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   xxt9oem.h

     Description: This file contains the definitions specific to any
                  particular T9 embedded environment.
               

     Version:	  7.4                                                       
********************************************************************************
********************************************************************************/

#ifndef T9OEM_H
#define T9OEM_H

/* Don't mangle function names if compiled under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define T9 Edition
 *----------------------------------------------------------------------------*/
#define	T9ALPHABETIC
//#ifdef CA_CHINA
	#define T9CHINESE
#define T9CHINESEPTI
//#endif
//#define T9JAPANESE

/*----------------------------------------------------------------------------
 *  Define OEMID -- LG Electronics OEM ID
 *----------------------------------------------------------------------------*/
#define T9OEMID 30020

/*----------------------------------------------------------------------------
 *  Define number of bytes in each T9 data element
	For Customer vesrion, these should be defined.
 *----------------------------------------------------------------------------*/
#define T9SYMBOLWIDTH	2
#define T9MINORWIDTH	2
#define T9NUMBERWIDTH	4

/*----------------------------------------------------------------------------
 *  Define function and data prefixes for special memory models
 *----------------------------------------------------------------------------*/
/* #define _64K_LIMIT_ */
/* #define T9FARDATA  __far	*/		/* data out side the segment */
/* #define T9FARCALL  __far */		/* function out side of segment */
/* #define T9NEARCALL __near */		/* function within the same segment */
/* #define T9NEARDATA __near */ 	/* data within the same segment */


/*----------------------------------------------------------------------------
 *  Define maximum udb word size
 *  NOTE:  This should not be set to less than 32 or more than 64.
 *----------------------------------------------------------------------------*/

#define T9MAXUDBWORDSIZE    64  /* Max udb word length supported by T9 system */


/*----------------------------------------------------------------------------
 *  Define maximum mdb word size
 *  NOTE: The maximum MDB word size isn't necessarily the same as the maximum
 *       UDB word size.
 *  NOTE:  This should not be set to less than 32 or more than 256.
 *----------------------------------------------------------------------------*/

#define T9MAXMDBWORDSIZE    64



/*----------------------------------------------------------------------------
 *  Define maximum cdb matches
 *----------------------------------------------------------------------------*/
#define T9MAXCDBMATCHES     0x06


/*----------------------------------------------------------------------------
 *	For our external demo, we need latin1 all the time.
 ----------------------------------------------------------------------------*/
#define T9CSLatin1
// #define T9CSGSM

/*----------------------------------------------------------------------------
 *	Turn on all the Collating sequences that are not keypad dependent.
 ----------------------------------------------------------------------------*/
#define T9CSGeneralPunctuation		/* Farsi needs zero-width space */
#define T9CSCurrencySymbols			/* Mostly to get the Euro. */

#define T9CSLatinA				/* 128 extended characters */
#define T9CSLatinB				/* Next 128 extended characters for Vietnamese */
#define T9CSDiacritics			/* Combining diacritic marks, for Vietnamese */

#define T9CSHebrew					/* Collating sequence for Hebrew */
// #define T9CSHebrewAlt3 

// #define T9CSArabic				/* Arabic characters */
 #define T9CSArabicAlternate 
// #define T9CSArabicAlt3 

//#define T9CSCyrillic				/* Cyrillic characters */
#define T9CSCyrillicEven			/* Cyrillic characters */

// #define T9CSDevanagari			/* Devanagari (i.e. Hindi) characters */
// #define T9CSDevanagariAlternate 

// #define T9CSBengali				/* Bengali characters */
// #define T9CSTamil				/* Tamil characters */

// #define T9CSGreek				/* Greek characters in the U+0380 range */
#define T9CSGreekAlphabetic 

// #define T9CSThai					/* Thai characters */
// #define T9CSThaiAIS 
 #define T9CSThaiHutchison 
// #define T9CSThaiAlternate 

/*----------------------------------------------------------------------------
 *	Korean
 ----------------------------------------------------------------------------*/
#if defined(T9KOREAN)
#define T9CSKoreanChun
#endif

/*----------------------------------------------------------------------------
 *	Chinese
 ----------------------------------------------------------------------------*/
#if defined(T9CHINESE)
#define T9CCSPELLBUFMAXSIZE         128 /* Size of Chinese spell buffer   */
#define T9CCKEYBUFMAXSIZE           55  /* Size of Chinese key buffer     */
#define T9CCSELECTPAGEMAXSIZE       8   /* Size of Chinese selection page */
#endif

/*----------------------------------------------------------------------------
 *	Japanese
 ----------------------------------------------------------------------------*/
#if defined(T9JAPANESE)
#define T9JWYOMIREORDERCOUNT         3 /*	The number of yomi to reorder */
#endif

/*----------------------------------------------------------------------------
 *	T9 EVENT & WORD API DEFINE : Implemented as EVENTAPI
 ----------------------------------------------------------------------------*/
#define		T9EVENTAPI
//#define		T9WORDAPI

/*----------------------------------------------------------------------------
 * T9 LDB OEM DEFINE : LDB used by OEM
 ----------------------------------------------------------------------------*/
	#define			T9LANG_English
	#define			T9LANG_Chinese
	#define			T9LANG_Malay
	#define			T9LANG_ChineseSimplifiedPTI
	#define			T9LANG_ChineseTraditionalPTI
	#define			T9LANG_Indonesian
	#define			T9LANG_Arabic					
	#define			T9LANG_Bulgarian		
	#define			T9LANG_Czech		
	#define			T9LANG_Danish
	#define			T9LANG_Dutch
	#define			T9LANG_Finnish		
	#define			T9LANG_French		
	#define			T9LANG_German		
	#define			T9LANG_Greek		
	#define			T9LANG_Hebrew		
	#define			T9LANG_Hungarian
	#define			T9LANG_Indonesian	
	#define			T9LANG_Italian		
	#define			T9LANG_Japanese	
	#define			T9LANG_Norwegian		
	#define			T9LANG_Polish		
	#define			T9LANG_Portuguese		
	#define			T9LANG_Romanian		
	#define			T9LANG_Russian		
	#define			T9LANG_SerboCroat		
	#define			T9LANG_Slovak		
	#define			T9LANG_Slovenian
	#define			T9LANG_Spanish		
	#define			T9LANG_Swedish		
	#define			T9LANG_Thai		
	#define			T9LANG_Turkish		
	#define			T9LANG_Ukrainian		
	#define			T9LANG_Vietnamese		
	#define			T9LANG_Hindi		
	#define			T9LANG_Malay
	#define			T9LANG_Estonian
	#define			T9LANG_Lithuanian
	#define			T9LANG_Latvian

/*----------------------------------------------------------------------------
 *	T9 UDB OEM DEFINE : UDB Configuration
 ----------------------------------------------------------------------------*/
#define		UDB_MAX_SIZE			1024*4
#define		CDB_MAX_SIZE			1600*T9SYMBOLWIDTH

//#define		JUDB_MAX_SIZE			1024*4
//#define		JACDB_MAX_SIZE			1024*16
#define		UDB_FENCE				1



 /*	Chinese defaults.
 ----------------------------------------------------------------------------*/
#if defined(T9CHINESE)
#define T9CCSPELLBUFMAXSIZE         128 /* Size of Chinese spell buffer   */
#define T9CCKEYBUFMAXSIZE           55  /* Size of Chinese key buffer     */
#define T9CCSELECTPAGEMAXSIZE       8   /* Size of Chinese selection page */
#endif

/*----------------------------------------------------------------------------
 *	T9 CUDB OEM DEFINE : CUDB Configuration		030514 yhjeon
 ----------------------------------------------------------------------------*/
#define		CUDB_MAX_SIZE			(CUDB_DATA_SIZE + 8)	//	sizeof(T9U16) * 4
#define		CUDB_DATA_SIZE			T9CCUDBMINSIZE			//	512 (t9ccapi.h) : WORD SIZE
#define		CUDB_FENCE				1

/*----------------------------------------------------------------------------
 *	T9 CAUDB OEM DEFINE : CAUDB Configuration	030514 yhjeon
 ----------------------------------------------------------------------------*/
#define		CAUDB_MAX_SIZE			(CAUDB_DATA_SIZE + 12)	//	sizeof(T9U16) * 5 : data외의 field는 10byte이지만 padding byte 포함해서 12byte로 한다.
#define		CAUDB_DATA_SIZE			128
#define		CAUDB_FENCE				1


/*----------------------------------------------------------------------------
 *	T9 EVENT & WORD API DEFINE : Implemented as EVENTAPI
 ----------------------------------------------------------------------------*/
//#define		T9WORDAPI

//#define T9MDBCALLBACK

#ifdef T9CHINESEPTI
#define T9CPMAXPAGESIZE             8//9   /* max number of characters/phrases on a selection page */
#define T9KEY_STROKE_WILDCARD       T9KEYAMBIG6 /* wild card key, has to be one of T9KEY values */
#define	CPUDB_MAX_SIZE			T9CPUDBMINSIZE
#endif
/*----------------------------------------------------------------------------
 *	T9 UDB OEM DEFINE : UDB Configuration
 ----------------------------------------------------------------------------*/
//>#if defined (CA_LATIN)
//>	#define		T9_NO_CDB_IN_BUILD//T9CDB_IN_BUILD
//>#elif defined (CA_CHINA)
//>	#define		T9_NO_CDB_IN_BUILD			// don't use CDB not yet[20051206]
//>#else
	#define		T9CDB_IN_BUILD
//>#endif

#if defined(__cplusplus)
}
#endif

#endif /* T9OEM_H */

/*---------------------------------- eof ---------------------------------*/
