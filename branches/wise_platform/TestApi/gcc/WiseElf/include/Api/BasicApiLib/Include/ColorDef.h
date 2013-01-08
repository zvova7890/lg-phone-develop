/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	COLOR DEFINE

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : BASIC API
	구분 : 그래픽
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.03
	일자 : 2002.10.31
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_COLORDEF_H_
#define		_BNSOFT_COLORDEF_H_

//-------------------------------------------------------------------------------------------------
//	Color Definition
#if defined(GDI_32BIT) && (defined(__ICCARM__) || defined(U8100))  // ktkim ??? for EMP Canvas
#define		WHITE_COLOR					(T_COLOR)0xFFFFFFFF	//	BNSRGB(255,255,255)
#define		BLACK_COLOR					(T_COLOR)0xFF000000	//	BNSRGB(  0,  0,  0)
#else
#define		WHITE_COLOR					(T_COLOR)-1			//	BNSRGB(255,255,255)
#define		BLACK_COLOR					(T_COLOR)0			//	BNSRGB(  0,  0,  0)
#endif

#define		GRAY_COLOR					(T_COLOR)0			//Y 임시 for U900
#define		ALPHABLEND_LEVEL			127					//Y 임시 for U900


#define		LIGHTGRAY_COLOR				BNSRGB(192,192,192)
#define		DARKGRAY_COLOR				BNSRGB(128,128,128)
//-------------------------------------------------------------------------------------------------
//	System Color Definition
#ifndef		TRANSPARENT_COLOR
#define		TRANSPARENT_COLOR			BNSRGB( 36, 255, 0)

#endif
#define		CLEAR_COLOR					WHITE_COLOR

#define		INVERSE_BK_COLOR			BNSRGB(  0,  0,255)
#define		INVERSE_TEXT_COLOR			WHITE_COLOR


#define		TRANSPARENT_COLOR1			0xFF				
#define		TRANSPARENT_COLOR2			0xFF
#define		TRANSPARENT_COLOR8			0x3C			
#define		TRANSPARENT_COLOR12			0x02F0		
#define		TRANSPARENT_COLOR16			0x27E0				
#define		TRANSPARENT_COLOR24			0x24FF00			
#define		TRANSPARENT_COLOR32			0x0024FF00			

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_COLORDEF_H_
