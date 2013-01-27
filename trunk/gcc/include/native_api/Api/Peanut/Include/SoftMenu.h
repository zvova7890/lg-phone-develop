/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SOFTMENU MANAGER

	Copyright(c) 1997-2003 BNSoft Corp.
	Copyright(c)     -2005 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_SOFTMENU_H_
#define		_BNSOFT_PEANUT_SOFTMENU_H_

#include	"PeanutInclude.h"

#define		SMSTATE_NORMAL			0
#define		SMSTATE_SELECT			1
#define		SMSTATE_SELECT_OUT		2
#define		SMSTATE_DISABLE			3	
#define		SMSTATE_OVERLAY			4					
#define		SOFTMENU_MAX_MENU		4

typedef enum
{ 	
	SOFTMENUSTY_3MENU =0,
	SOFTMENUSTY_4MENU

} E_SOFTMENUSTYLE;

// SoftMenu Item
#define		SMIMG_SIG		0xA4A7B0B8

typedef struct
{
	QUAD				Sig;
	TImage32*			pNormalImg;
	TImage32*			pPressedImg;
	TImage32*			pOverlayImg;
	TImage32*			pDisableImg;
	T_CSTR				pcszTip;	//Bubble Popup text
}TSoftStateImg;

extern T_POS		SoftMenu_GetAboveY       (void);
extern T_POS		SoftMenu_GetTopY         (void);
extern T_SIZE		SoftMenu_GetHeight       (void);
extern void		SoftMenu_SetFont         (E_FONT enFont);
extern void		SoftMenu_SetOemType      (QUAD OemType);
extern void		SoftMenu_SetStr          (T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu, BOOL bRefresh);
extern void		SoftMenu_Refresh	 (void);
extern void		SoftMenu_Draw            (T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu);
extern void		SoftMenu_DrawEx          (T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu, BOOL bRefresh);
extern BOOL		SoftMenu_SetTransparent  (BOOL bTransparent);
extern int		SoftMenu_Pointing	 (int Action, T_POS X, T_POS Y);
extern int		SoftMenu_GetOemType     (void);

#endif	//	_BNSOFT_PEANUT_SOFTMENU_H_
