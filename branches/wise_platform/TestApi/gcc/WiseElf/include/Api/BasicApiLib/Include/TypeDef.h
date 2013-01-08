#ifndef		__TYPEDEF_H__
#define		__TYPEDEF_H__

/* *****************************************************************************

	TYPE DEFINITION

***************************************************************************** */

#ifndef		TYPEDEF_SHORT
#define		TYPEDEF_SHORT
typedef		signed short	SHORT;	//	signed 16 bits
#endif

#ifndef		TYPEDEF_LONG
#define		TYPEDEF_LONG
typedef		signed long	LONG;	//	signed 32 bits
#endif

#ifndef		TYPEDEF_BYTE
#define		TYPEDEF_BYTE
typedef		unsigned char	BYTE;	//	unsigned 8 bits
#endif

#ifndef		TYPEDEF_WORD
#define		TYPEDEF_WORD
typedef		unsigned short	WORD;	//	unsigned 16 bits
#endif

#ifndef		TYPEDEF_QUAD
#define		TYPEDEF_QUAD
typedef		unsigned long	QUAD;	//	unsigned 32 bits
#endif


#ifndef		TYPEDEF_BOOL
#define		TYPEDEF_BOOL
typedef		int		BOOL;	//	boolean
#endif

#ifndef		TYPEDEF_U_CHAR
#define		TYPEDEF_U_CHAR
typedef		unsigned short	U_CHAR;	//	Unicode charset
#endif

#ifndef		TYPEDEF_M_CHAR
#define		TYPEDEF_M_CHAR
typedef		char		M_CHAR;	//	Multibyte charset
#endif

#ifndef		TYPEDEF_M_CODE
#define		TYPEDEF_M_CODE
typedef		unsigned short	M_CODE; //	Multibyte code
#endif

#ifndef		TYPEDEF_A_CHAR
#define		TYPEDEF_A_CHAR
typedef		U_CHAR		A_CHAR;	//	Any Character
#endif

//------------------------------------------------------------------------------
//	Event & Parameter
#ifndef		TYPEDEF_T_EVENT
#define		TYPEDEF_T_EVENT
typedef		unsigned long	T_EVENT; //	event
#endif

#ifndef		TYPEDEF_T_MSG
#define		TYPEDEF_T_MSG
typedef		unsigned long	T_MSG;	//	message
#endif

#ifndef		TYPEDEF_T_PARAM
#define		TYPEDEF_T_PARAM
typedef		unsigned long	T_PARAM; //	Parameter
#endif

//------------------------------------------------------------------------------
//	Enumerator & String
#ifndef		TYPEDEF_T_ENUM
#define		TYPEDEF_T_ENUM
typedef		int		T_ENUM;	//	enumerator
#endif

#ifndef		TYPEDEF_T_CSTR
#define		TYPEDEF_T_CSTR
typedef		const A_CHAR*	T_CSTR;	//	constant string
#endif

#ifndef		TYPEDEF_T_STR
#define		TYPEDEF_T_STR
typedef		A_CHAR*		T_STR;	//	string
#endif

#ifndef		TYPEDEF_M_CSTR
#define		TYPEDEF_M_CSTR
typedef		const M_CHAR*	M_CSTR;	//	constant string
#endif

#ifndef		TYPEDEF_M_STR
#define		TYPEDEF_M_STR
typedef		M_CHAR*		M_STR;	//	Unicode string
#endif

#ifndef		TYPEDEF_U_CSTR
#define		TYPEDEF_U_CSTR
typedef		const U_CHAR*	U_CSTR;	//	constant string
#endif

#ifndef		TYPEDEF_U_STR
#define		TYPEDEF_U_STR
typedef		U_CHAR*		U_STR;	//	Unicode string
#endif

//------------------------------------------------------------------------------
//	ID, Index & Number
#ifndef		TYPEDEF_T_ID
#define		TYPEDEF_T_ID
typedef		unsigned int	T_ID;	//	ID
#endif

#ifndef		TYPEDEF_T_INDEX
#define		TYPEDEF_T_INDEX
typedef		unsigned int	T_INDEX; //	index
#endif

#ifndef		TYPEDEF_T_NUM
#define		TYPEDEF_T_NUM
typedef		unsigned int	T_NUM;	//	number
#endif

//------------------------------------------------------------------------------

#ifndef		TYPEDEF_T_POS
#define		TYPEDEF_T_POS
typedef		signed int	T_POS;	//	position
#endif

#ifndef		TYPEDEF_T_SIZE
#define		TYPEDEF_T_SIZE
typedef		unsigned int	T_SIZE;	//	size
#endif

#ifndef		TYPEDEF_T_OFFSET
#define		TYPEDEF_T_OFFSET
typedef		signed int	T_OFFSET; //	offset
#endif

#ifndef		TYPEDEF_T_COLOR
#define		TYPEDEF_T_COLOR
typedef		unsigned int	T_COLOR; //	color
#endif

//------------------------------------------------------------------------------
#ifndef		TYPEDEF_T_STROKE
#define		TYPEDEF_T_STROKE
typedef		unsigned long	T_STROKE;
#endif

#ifndef		TYPEDEF_T_FONT
#define		TYPEDEF_T_FONT
typedef		T_ENUM		T_FONT;
#endif

#ifndef		TYPEDEF_T_FONTEFFECT
#define		TYPEDEF_T_FONTEFFECT
typedef		T_ENUM		T_FONTEFFECT;
#endif

//------------------------------------------------------------------------------
#ifndef		TYPEDEF_T_DRVID
#define		TYPEDEF_T_DRVID
typedef		unsigned long	T_DRVID;
#endif

#ifndef		TYPEDEF_T_DIRID
#define		TYPEDEF_T_DIRID
typedef		unsigned short	T_DIRID;
#endif

#ifndef		TYPEDEF_T_ADDR
#define		TYPEDEF_T_ADDR
typedef		unsigned long	T_ADDR;
#endif

//------------------------------------------------------------------------------

#ifndef		TYPEDEF_T_HANDLE
#define		TYPEDEF_T_HANDLE
typedef		void*		T_HANDLE; //	handle
#endif


#ifndef		H_INVALID
#define		H_INVALID	(T_HANDLE)0
#endif

#ifndef		T_PTR
#define		T_PTR		T_HANDLE
#endif

#ifndef		H_CTRL
#define		H_CTRL		T_HANDLE
#endif

#ifndef		H_NONE
#define		H_NONE		(T_HANDLE)0
#endif

#ifndef		H_OVERFLOW
#define		H_OVERFLOW	(T_HANDLE)-2
#endif


 /*  INT8    :   8 bit signed integer    */
#ifndef		TYPEDEF_T_INT8
#define		TYPEDEF_T_INT8
 typedef char     	      INT8;	
#endif 

/*  UINT8   :   8 bit unsigned integer    */
#ifndef UINT8
  typedef unsigned char   UINT8;
#endif

/*  INT16   :   16 bit signed integer     */
typedef signed short    INT16;

#ifndef UINT16
/*  UINT16  :   16 bit unsigned integer   */
  typedef unsigned short  UINT16;
#endif

typedef signed long     INT32;

#ifndef UINT32
/*  UINT32  :   32 bit unsigned integer   */
 typedef unsigned long   UINT32;  
#endif 


//------------------------------------------------------------------------------
#ifndef		LOCAL
#define		LOCAL	static
#endif

#ifndef		CALLBACK
#define		CALLBACK LOCAL
#endif

#ifndef		GLOBAL
#define		GLOBAL
#endif

#ifndef		INTERNAL
#define		INTERNAL
#endif

#ifndef		PROTECTED
#define		PROTECTED
#endif

#ifndef		INHERITED
#define		INHERITED
#endif

#ifndef		BNS_ADAPT
#define		BNS_ADAPT
#endif

#ifndef		DEV_ADAPT
#define		DEV_ADAPT
#endif

#ifndef		TRUE
#define		TRUE			1
#endif

#ifndef		FALSE
#define		FALSE			0
#endif

#ifndef		NOTUSED
#define		NOTUSED			0
#endif

#ifndef		NOT_USED
#define		NOT_USED		0
#endif

#ifndef		min
#define		min(X,Y)		((X) < (Y) ? (X) : (Y))
#endif

 
#ifndef		max
#define		max(X,Y)		((X) > (Y) ? (X) : (Y))
#endif


#ifndef		MK_WORD
#define		MK_WORD(H,L)		((WORD)(((WORD)(H))*256 + ((WORD)(L))))
#endif

#ifndef		MK_QUAD
#define		MK_QUAD(A,B,C,D)	((QUAD)(((QUAD)MK_WORD(A,B))*256*256 + (QUAD)MK_WORD(C,D)))
#endif

#ifndef		TOLOWER
#define		TOLOWER(c)		((c) >= 'A' && (c) <= 'Z' ? (c) -'A'+'a' : (c))
#endif

#ifndef		TOUPPER
#define		TOUPPER(c)		((c) >= 'a' && (c) <= 'z' ? (c) -'a'+'A' : (c))
#endif
 
#ifndef		BNS_SWAP
#define		BNS_SWAP(TYPE,A,B)	{ TYPE C = A; A = B; B = C; }
#endif

//------------------------------------------------------------------------------

#ifndef		TYPEDEF_TPoint
#define		TYPEDEF_TPoint
typedef struct
{
	T_POS 		X;
	T_POS 		Y;
} TPoint;
#endif

#ifndef		TYPEDEF_TRect
#define		TYPEDEF_TRect
typedef struct
{
	T_POS 		Left;
	T_POS 		Top;
	T_POS 		Right;
	T_POS 		Bottom;
} TRect;
#endif

//------------------------------------------------------------------------------
//	Align type (combination of following values)
#define		ALIGN_LEFT				0x00
#define		ALIGN_CENTER				0x08
#define		ALIGN_RIGHT				0x04
#define		ALIGN_TOP				0x00
#define		ALIGN_MIDDLE				0x02
#define		ALIGN_BOTTOM				0x01
#define		ALIGN_NONE				0x80 // GrSysWriteStr()
//------------------------------------------------------------------------------


#endif	//	__TYPEDEF_H__
