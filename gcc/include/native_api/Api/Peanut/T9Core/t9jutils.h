/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9jutils.h

     Description: Utilities for Japanese core code.  Heap manager, memory
                  manager, linked list utility, etc.


********************************************************************************
********************************************************************************/

#ifndef T9JUTILS_H
#define T9JUTILS_H

/*------------------------------------------------------------------------
 *
 *                  Memory Manager And Heap Definitions
 *
 *------------------------------------------------------------------------*/

/* A null handle to indicate no memory. */
#define JNULL ((T9JW_HANDLE)0)

/* Results of performing a heap operation. */
typedef enum {
    HR_ERROR,              /* critical failure of heap operation */
    HR_SUCCESS,            /* successful heap operation */
    HR_DUPLICATE,          /* add operation failed:
                              item is already in the heap in the heap */
    HR_FULL                /* add operation failed: heap is full */
} HeapResult;


/* Macro to convert heap index into a heap element index. */
#define JHINDX(index) (hpMgr->wElts - (index))

#define HASH_MODULUS 31  /* hash value % this -> hash table index */

/*
 * Structure of elements in the hash table.
 */

typedef struct {
    T9U16   wHpIndex;           /* index of element in heap */
    T9JW_HANDLE hNext;              /* next element in hash chain */
} HashElt;

/*
 * Each blob of memory has a header listing the size of the blob and
 * the next blob in memory.  Allocated data begins after the blob header.
 */

typedef struct {
    T9U16   wSize;              /* size of memory blob */
    T9JW_HANDLE hNext;              /* next blob of free memory */
} JMHdr;

#define JMHDR_SIZE  4 /* make this a constant to avoid zillions of calls to sizeof(JMHdr) */

#define WORD_ALIGN(n)   if ((n) & 0x1) {(n)++;}
/*
 * Description: Convert n to a multiple of 2.
 */
#define JMDeref(memmgr, han) ((void *)((memmgr).pbMemBase + (han) - JMHDR_SIZE))
/*
 * Description: Dereference a memory handle to an address pointer.
 *              As a macro, for now, to save function call overhead...
 *              Note shift of JMHDR_SIZE to avoid valid handles being zero
 */

#ifdef T9JW_DEBUGON
/* Format of information provided by JMDump. */
typedef struct {
    T9U8    *pbMemAddr;         /* address of memory block */
    T9U8    *pbHeap;            /* start of heap array */
    T9U16   wMemSize;           /* size of memory block */
    T9U16   wTotalFree;         /* total amount of free memory, including headers */
    T9U16   wFreeListSize;      /* number of entries in the free list */
    T9JW_HANDLE wFirstFree;         /* handle of first node in free list */
    T9U16   wHdrsWritten;       /* number of headers in freeList array */
    JMHdr   freeList[1];        /* array of headers of blobs in free list */

} JMDumpS;
extern T9U16 T9FARCALL JMDump(T9JW_MemMgr *pMemMgr, T9U8 *pbOutput, T9U16 wBufSize);
/*
 * Description: Provide information on usage of memory block.
 *              Enables checking to see if free area is fragmented,
 *              and to see how much of the memory block is actually
 *              being used.
 *
 * Pass:        pMemMgr      - memory manager
 *              pbOutput    - buffer to store data
 *              wBufSize    - size of output buffer
 *
 * Return:      size of data written to output buffer
 */
#endif /* T9JW_DEBUGON */

#define JHCount(memmgr) ((memmgr).hpMgr.wElts)
/*
 * Description:     Count the number of elements in the heap.
 *
 * Pass:            memmgr  - memory manager
 */

/*-------------------------------------
 *
 *      Linked List/Queue routines
 *
 *------------------------------------*/

#define JLAdd(memmgr, hHead, hNew) *((T9JW_HANDLE *)JMDeref(memmgr, (hNew))) = hHead;
/*
 * Description: Prepend the new item as a node at the head of the list.
 *
 * Pass:        pMemMgr   - memory manager
 *              hHead    - handle of current first node in the list
 *              hNew     - handle of new list node
 */

#define JLNext(n) (n)->hNext
/*
 * Description: Get the data from the next node in the list.
 *              Element is not removed from the list.
 *
 * Params:      n = pointer to list node
 */

#define JQInit(q) (q).hHead = (q).hTail = JNULL;
/*
 * Description: Initializes an empty queue.
 *
 * Params:        qHdr - header of the queue
 *
 */

#define JQHead(qHdr) (qHdr).hHead
/*
 * Description: Get the first node in the queue without removing it.
 *
 * Params:      qHdr - pointer to the queue header
 */

#define JQTail(qHdr) (qHdr).hTail
/*
 * Description: Get the last node in the queue without removing it.
 *
 * Params:     qHdr  - pointer to the queue header
 */

#endif /* T9JUTILS_H */

/*---------------------------------- eof ---------------------------------*/
