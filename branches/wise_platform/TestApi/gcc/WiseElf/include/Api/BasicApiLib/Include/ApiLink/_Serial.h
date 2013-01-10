/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__SERIAL_H_
#define		_BNSOFT__SERIAL_H_

#include	"..\Serial.h"

typedef H_SERIAL		(*T_pfnSerial_Open)    (E_COMPORT enComPort, int Baudrate);
typedef H_SERIAL		(*T_pfnSerial_OpenEx)  (E_COMPORT enComPort, TSerialSetup* pSetup);
typedef BOOL			(*T_pfnSerial_Close)   (H_SERIAL hSerial);
typedef T_NUM			(*T_pfnSerial_Send)    (H_SERIAL hSerial, BYTE* pData, T_SIZE Len);
typedef T_NUM			(*T_pfnSerial_Read)    (H_SERIAL hSerial, BYTE* pBuf, T_SIZE BufSize);
typedef BOOL			(*T_pfnSerial_Empty)   (H_SERIAL hSerial);
typedef BOOL			(*T_pfnSerial_IsEmpty) (H_SERIAL hSerial);

typedef struct
{
	T_pfnSerial_Open				pfnOpen;
	T_pfnSerial_OpenEx				pfnOpenEx;
	T_pfnSerial_Close				pfnClose;
	T_pfnSerial_Send				pfnSend;
	T_pfnSerial_Read				pfnRead;
	T_pfnSerial_Empty				pfnEmpty;
	T_pfnSerial_IsEmpty				pfnIsEmpty;
} TApiGrp_Serial;


#define		Serial_Open(p1,p2)			__ApiLink2(Serial,Open,p1,p2)
#define		Serial_OpenEx(p1,p2)			__ApiLink2(Serial,OpenEx,p1,p2)
#define		Serial_Close(p1)			__ApiLink1(Serial,Close,p1)
#define		Serial_Send(p1,p2,p3)			__ApiLink3(Serial,Send,p1,p2,p3)
#define		Serial_Read(p1,p2,p3)			__ApiLink3(Serial,Read,p1,p2,p3)
#define		Serial_Empty(p1)			__ApiLink1(Serial,Empty,p1)
#define		Serial_IsEmpty(p1)			__ApiLink1(Serial,IsEmpty,p1)


#endif	//	_BNSOFT__SERIAL_H_
