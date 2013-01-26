/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT RADIO CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_RDOCTRL_H_
#define		_BNSOFT__PEANUT_RDOCTRL_H_

#include	"..\RdoCtrl.h"

typedef H_CTRL			(*T_pfnRdoCtrl_Create)      (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText, H_CTRL hGrpRC);
typedef BOOL			(*T_pfnRdoCtrl_Destroy)     (H_CTRL hRC);
typedef BOOL			(*T_pfnRdoCtrl_ModifyStyle) (H_CTRL hRC, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnRdoCtrl_SetStatus)   (H_CTRL hRC, E_RDOSTATUS enStatus);
typedef BOOL			(*T_pfnRdoCtrl_SetCheck)    (H_CTRL hRC, BOOL bCheck);
typedef H_CTRL			(*T_pfnRdoCtrl_GetChecked)  (H_CTRL hRC);
typedef BOOL			(*T_pfnRdoCtrl_UncheckAll)  (H_CTRL hRC);

typedef struct
{
	T_pfnRdoCtrl_Create				pfnCreate;
	T_pfnRdoCtrl_Destroy				pfnDestroy;
	T_pfnRdoCtrl_ModifyStyle			pfnModifyStyle;
	T_pfnRdoCtrl_SetStatus				pfnSetStatus;
	T_pfnRdoCtrl_SetCheck				pfnSetCheck;
	T_pfnRdoCtrl_GetChecked				pfnGetChecked;
	T_pfnRdoCtrl_UncheckAll				pfnUncheckAll;
} TApiGrp_RdoCtrl;

#define	RdoCtrl_Create(p1,p2,p3,p4,p5,p6,p7)		__ApiLink7(RdoCtrl,Create,p1,p2,p3,p4,p5,p6,p7)
#define	RdoCtrl_Destroy(p1)				__ApiLink1(RdoCtrl,Destroy,p1)
#define	RdoCtrl_ModifyStyle(p1,p2,p3)			__ApiLink3(RdoCtrl,ModifyStyle,p1,p2,p3)
#define	RdoCtrl_SetStatus(p1,p2)			__ApiLink2(RdoCtrl,SetStatus,p1,p2)
#define	RdoCtrl_SetCheck(p1,p2)				__ApiLink2(RdoCtrl,SetCheck,p1,p2)
#define	RdoCtrl_GetChecked(p1)				__ApiLink1(RdoCtrl,GetChecked,p1)
#define	RdoCtrl_UncheckAll(p1)				__ApiLink1(RdoCtrl,UncheckAll,p1)


#endif	//	_BNSOFT__PEANUT_RDOCTRL_H_
