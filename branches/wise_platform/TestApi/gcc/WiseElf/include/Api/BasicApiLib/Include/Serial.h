/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SERIAL COMMUNICATION MANAGER

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SERIAL_H_
#define		_BNSOFT_SERIAL_H_

#include	"Include.h"
#include	"ConfigSR.h"

#define		SERIAL_DATA_RECEIVED		0
#define		SERIAL_DATA_SENT		1

typedef enum
{
	SERIAL_PARITY_NONE			= 0,
	SERIAL_PARITY_ODD,
	SERIAL_PARITY_EVEN
} E_SERIAL_PARITY;

typedef enum
{
	SERIAL_FLOWCTRL_NONE			= 0,
	SERIAL_FLOWCTRL_XONOFF,
	SERIAL_FLOWCTRL_HARDWARE
} E_SERIAL_FLOWCTRL;

//-------------------------------------------------------------------------------------------------
//	E_COMPORT 타입을 지정한다.
#ifndef		TYPEDEF_E_COMPORT
#define		TYPEDEF_E_COMPORT
typedef		unsigned int			E_COMPORT;
#endif

//	Definition of H_SERIAL
typedef		T_HANDLE			H_SERIAL;

typedef struct
{
	int					Baudrate;
	int					DataBit;
	E_SERIAL_PARITY		enParity;
	int					StopBit;
	E_SERIAL_FLOWCTRL	enFlowCtrl;
} TSerialSetup;


typedef struct
{
		E_COMPORT			enComPort;
		TSerialSetup		Setup;
		T_NUM				SentBytes;
		T_NUM				ReadBytes;
		T_HANDLE			hOwner;
} TSerial;

typedef enum
{
		SERIAL_NOTIFY_DATA_RECEIVED		= 0,
		SERIAL_NOTIFY_DATA_SENT
} E_SERIAL_NOTIFY;



extern H_SERIAL		Serial_Open    (E_COMPORT enComPort, int Baudrate);
extern H_SERIAL		Serial_OpenEx  (E_COMPORT enComPort, TSerialSetup* pSetup);
extern BOOL		Serial_Close   (H_SERIAL hSerial);
extern T_NUM		Serial_Send    (H_SERIAL hSerial, BYTE* pData, T_SIZE Len);
extern T_NUM		Serial_Read    (H_SERIAL hSerial, BYTE* pBuf, T_SIZE BufSize);
extern BOOL		Serial_Empty   (H_SERIAL hSerial);
extern BOOL		Serial_IsEmpty (H_SERIAL hSerial);


#endif	//	_BNSOFT_SERIAL_H_
