/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ERROR DEFINITION

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_ERRDEF_H_
#define		_BNSOFT_PEANUT_ERRDEF_H_

//	Definition of Peanut Error
typedef enum
{
	PN_ERR_FIRST				= 20000,
	PN_ERR_ERROR,
	PN_ERR_MEMORY_FULL,
	PN_ERR_INVALID_PARAM,
	PN_ERR_OUT_OF_RANGE,
	PN_ERR_INVALID_CTRL_ID,
	PN_ERR_NO_ACTIVE_CTRL,
	PN_ERR_NO_ITEM,
	PN_ERR_ILLIGAL_FORMAT,
	PN_ERR_T9_INITIAL_FAILURE,
	PN_ERR_LAST
} E_PN_ERR;


#endif	//	_BNSOFT_PEANUT_ERRDEF_H_
