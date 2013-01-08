/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	API LINK DEFINITION

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APILINK_APILINKDEF_H_
#define		_BNSOFT_APILINK_APILINKDEF_H_

//-------------------------------------------------------------------------------------------------
#define		__ApiLinkV(G,F)												(*g_pApiLink->p##G->pfn##F)
#define		__ApiLink0(G,F)												(*g_pApiLink->p##G->pfn##F)()
#define		__ApiLink1(G,F,p1)											(*g_pApiLink->p##G->pfn##F)(p1)
#define		__ApiLink2(G,F,p1,p2)										(*g_pApiLink->p##G->pfn##F)(p1,p2)
#define		__ApiLink3(G,F,p1,p2,p3)									(*g_pApiLink->p##G->pfn##F)(p1,p2,p3)
#define		__ApiLink4(G,F,p1,p2,p3,p4)									(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4)
#define		__ApiLink5(G,F,p1,p2,p3,p4,p5)								(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5)
#define		__ApiLink6(G,F,p1,p2,p3,p4,p5,p6)							(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6)
#define		__ApiLink7(G,F,p1,p2,p3,p4,p5,p6,p7)						(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7)
#define		__ApiLink8(G,F,p1,p2,p3,p4,p5,p6,p7,p8)						(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8)
#define		__ApiLink9(G,F,p1,p2,p3,p4,p5,p6,p7,p8,p9)					(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8,p9)
#define		__ApiLinkA(G,F,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)				(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)
#define		__ApiLinkB(G,F,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB)			(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB)
#define		__ApiLinkC(G,F,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB,pC)			(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB,pC)
#define		__ApiLinkE(G,F,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB,pC,pD,pE)	(*g_pApiLink->p##G->pfn##F)(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA,pB,pC,pD,pE)
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_APILINK_APILINKDEF_H_
