/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2002-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9jldb.h

     Description: Definitions for Japanese T9 core code.


********************************************************************************
********************************************************************************/

#ifndef T9JLDB_H
#define T9JLDB_H

#include "t9.h"
#include "t9jutils.h"
#include "t9jwapi.h"
#include "t9judb.h"
#include "t9jmdb.h"
#include "t9ldb.h"

#ifdef LING_DEBUG
#define TRACE_BUF_SIZE (1024 * 4)
#define MAXCLASS       (1024)
#endif /* LING_DEBUG */

/*------------------------------------------------------------------------
 *
 *                  JT9 API level definitions
 *
 *------------------------------------------------------------------------*/


/*
 * Definitions for operating on the key values.  The lower 5 bits
 * represent the 1-based key value.  The upper 3 bits are flag bits.
 *
 * NOTE:  The key info is exposed in t9jwapi.h.  If the format is
 * changed, update there as well!
 */

#define SPECIALCHARCONVERSIONS

/*------------------------------------------------------------------------
 *
 *                  Database level definitions
 *
 *------------------------------------------------------------------------*/

/* Macro for storing and fetching values using a nibble packed buffer.
 * Pack high nibble, then low nibble. */
#define NIBBLE_PACK(buf, bVal, index)   buf[index/2] = (T9U8) ((index & 0x1) ? ((buf[index/2] & 0xF0) | bVal) : ((buf[index/2] & 0x0F) | (bVal << 4)))
#define NIBBLE_UNPACK(bVal, index)      (T9U8)((index & 0x1) ? (bVal & 0x0F) : ((bVal >> 4) & 0x0F))

/*
 * Supported database settings.
 */
#define JDB_INFLECTED(type)          (type & 0x02)
#define JDB_JAPANESE(type)           (type & 0x04)
                            /* minimum supported types in database to be valid */

#define PRE_PUNC_RULE               0       /* no smart punctuation */
#define POST_PUNC_RULE              0

/* All UDB words are assigned this frequency as if it came from
 * a selection instruction. */
#define UDB_WORD_FREQ           0    /* not the max. leave room for growth... :) */

#define CLASS_MAX_FREQ          15   /* a maximum frequency within a class */

/*
 * Bit field indicating database(s) where object came from. If the object is
 * from the UDB, the lower unused bits contain the yomi index in the UDB.
 * Hope no more than 64 UDB yomis have the same key sequence...
 */
typedef T9U8    DBFlags;
#define DBF_IN_LDB  ((T9U8)0x80)                    /* set if object is from LDB */
#define DBF_IN_UDB  ((T9U8)0x40)                   /* set if object is from UDB */
#define DBF_IN_MDB  ((T9U8)0x20)                    /* set if object is from MDB */
#define UDB_YOMI_INDEX(x)   (x & 0x3F)      /* 6 free lower bits */

#define UDB_YOMI_FLAG       0x8000          /* combined with UDB yomi index
                                             *  to form a new unique selection
                                             *  list index. */
/*
 * Reasons for needing to rebuild the selection objects.  (yomis)
 */
enum JRebuildReasons {
    JRR_DEADEND = 1        /* sel obj info cleared when hit deadend in ldb */
};


    /* Keep this structure word sized so it can fit in the data
     * field in list nodes. Saves memory allocations. */

typedef T9U16 CFPair;
#define CF_TR_INDX(cf)      ((T9U8)(((cf) >> 8) & 0xFF))    /* in-tree index is high byte */
#define CF_FREQ(cf)         ((cf) & 0x00FF)                 /* freq is low byte */
#define MAKE_CF(trIndx, f)  ((T9U16)(((trIndx) << 8) | f))

    /* Structure for building a linked list of Class/Freq info. */
typedef struct {
    T9JW_HANDLE hNext;              /* MUST be first! */
    CFPair  cf;
} CFElt;

/*
 * For processing key sequence.
 *
 * All the possible paths and subpaths for the current key sequence are
 * stored in an array of T9JW_PathGroup structures.  Each path group contains
 * an array of path headers for paths starting with the same 1st key.
 * Each path header contains an array of nodes in the path.
 *
 * Each path tracks which classes in the tree are valid for the path.
 *
 * Each node tracks which instructions are valid in the instruction
 * list to filter out instructions in subsequent nodes which may
 * reference invalid instructions.
 */

/* For working with valid class bitfield in PathHdr structures.
 * pb - pointer to the bitfield buffer
 * c  - 0-based in-tree class index */
#define MAX_CLASSES_PER_TREE    256         /* arbitrary */
#define VALID_CLASS_SIZE        (MAX_CLASSES_PER_TREE / 32) /* dwords */
#define IS_VALID(pb, c)         (pb[c/32] & ((T9U32)1 << (c%32)))
#define SET_VALID(pb, c)        (pb[c/32] |= ((T9U32)1 << (c%32)))

/*
 * Structure of new trees added to the heap for sorting.
 */
typedef struct {
    T9U32   dwValidCls[VALID_CLASS_SIZE];
                            /* bit field indicating valid classes in tree */
    T9U8    bTree;          /* index of tree */
} NewTree;


typedef struct {
    T9JW_HANDLE hPath;          /* handle to the array of path nodes */
    T9U8    bTree;          /* which tree the path is in, 0 for main tree */
    T9U8    bLastKey;       /* last valid key in this path (0-based).
                             * This includes the node that is created for
                                the next key that needs processing. */
    T9U8    bNumNodes;      /* number of path nodes in the array */
    T9U8    bSearched;      /* number of nodes searched for selection
                                instructions. */
    T9U8    bSize;          /* size of valid class filter */
    T9U32   dwValidCls[VALID_CLASS_SIZE];   /* bit field indicating valid classes
                                being constructed from this path.
                                Size of array must be fixed as this structure
                                is allocated as an array of path headers. */
} PathHdr;

typedef struct {
    T9U32   dwNodePtr;      /* nibble offset to node */
    T9U32   dwSILPtr;       /* nibble offset to desired selection instruction
                                list for key represented by this node.
                                0 indicates a dead end. */

    T9U16   wSelIndx;       /* # selection instructions before this key's SIL */
        /* add wSelIndx to index of selection instruction to get index of
         * selection instruction within entire node. Use that index to locate
         * the conversion instruction list. */

    T9U16   wSILObj;        /* index in key's selection instruction list
                             * of instruction used for yomi
                             * Add to wSelIndx to compute index of sel instr
                             * within entire node. */
} PathNode;


/*
 * For building objects.
 */

    /* Each object may be formed from one or more parts.  This
     * info is needed to keep track of how the object was constructed,
     * and to compute the frequency of this particular construction.
     * A series of trace info's trace the makeup of a complete
     * object.
     */
typedef struct {
    T9U16   wAIC;           /* absolute inflection class - easier
                                to have this for checking follow class
                                and for computing frequency than to
                                convert from tree number and in-tree index */
    T9U8    bFreq;           /* frequency from class/frequency pair */
    T9U8    bLen;            /* length of this part */
} TraceInfo;

    /* Structure for putting TraceInfo in a list. */
typedef struct {
    T9JW_HANDLE hNext;          /* next pointer, MUST be first! */
    TraceInfo ti[1];        /* array of trace infos */
} TraceInfoElt;

    /* Accounting info to sort out which trace info structures in
     * the trace info array make up a single trace. */
typedef struct {
    T9U8    bNTraces;        /* number of separate traces */
    T9U8    bNTI;            /* number of trace info structures in
                                the trace info array */
    T9U8    bTILens[1];      /* length of each trace */
} TraceInfoAcctg;

    /* Part of a selection object.  One or more parts are combined to form
     * a complete selection object. */
typedef struct {
    T9JW_HANDLE     hNext;      /* handle to next part.  MUST be first field! */
    T9JW_HANDLE     hTIAcctg;   /* handle to accounting for trace info array */
                            /* JNULL if no traces */
    T9JW_HANDLE     hTraceInfo; /* handle to trace info array */
                            /* JNULL if no traces */
    T9U8        bLen;       /* length of word part */
    T9U8        bSyms[1];   /* nibble packed symbol buffer */
} JSelPart;


/*
 * For completed objects.
 */

    /* All completed objects are sorted into a table.  If not all
     * items are sorted, the additional items are still in the heap. */
typedef struct {
    T9U16   wObjCnt;            /* total number of selection objects */
    T9U16   wNumSorted;         /* number of sorted objects */
    T9JW_HANDLE hObjs[1];           /* handles to the objects */
} JObjTable;

    /* A completed selection object. */
typedef struct {
    T9U32       dwFreq;             /* computed frequency */
    T9U8        bWordLen;           /* needed because there is no
                                        access to pJWFieldInfo in callbacks! */
    T9U8        bBaseLen;           /* longest first component */

    T9JW_HANDLE     hTIAcctg;           /* handle to accounting for trace info array */
                                    /* JNULL if no traces */
    T9JW_HANDLE     hTraceInfo;         /* handle to trace info array */
                                    /* JNULL if no traces */

    DBFlags     bDBFlags;           /* DB(s) containing the object */
    T9U8        bSyms[1];           /* nibble packed symbol buffer */
} JSelObject;
#endif /* T9JLDB_H */

/*---------------------------------- eof ---------------------------------*/
