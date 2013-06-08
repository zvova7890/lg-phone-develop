/********** 1. file discription ***********************************************

          Multimedia Service Framework Player API

File name : 

Description :  

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/  /     SSC T     initial version
07/06/30	  sjmun		Include ����. ���丮 ����. Symphony�� Sync�� ���� InstanceID�� ����. �׷��� ���� ��ƼInstance�� ���������� ����.
07/07/03	  sjmun		Event�� Param�� �Ǹ��� ������ ����Ƿ� MSOEM_Player_Import.h�� �̵�. by sjmun. 070703
07/07/06	  sjmun		�������̽� �ΰ� �߰�. Sync with Nyx. 070706
07/07/11	  sjmun		OEM�ܿ� �ش��ϴ� Enum���� ��� MSF_PlayerDef.h�� �ű�.
*************************************************************************/
#ifndef _MSAPI_PLAYER_H_
#define _MSAPI_PLAYER_H_

// Ÿ��⿡�� �ϴ� ���. ���� �������� �ϴ� ����
#define USE_MSAPI_PLAYER 
//#define USE_TEST_MTM	// temporary for MTM
////

//Define�� ������ 
//#if defined(API_FEATURE_MSAPI)
#ifdef USE_MSAPI_PLAYER
/**************************************************************
*
* include  
*
***************************************************************/
//#include "..\..\..\..\..\WISE\Api\BasicApiLib\Include\Include.h"
//#include "VodApiComDef.h" ���� by sjmun. MSF_Playerdef.h�� ����.

/* Include Header File */
#include "..\..\..\Api\BasicApiLib\Include\Include.h"
#include "MSF_ErrorCode.h" //include dependency with MSAPI Camera
#include "MSF_TypeDef.h" //include dependency with MSAPI Camera
//#include "..\..\..\Api\SndApiLib\Include\SndApiDef.h" //include dependency with Sound API
#include "MSF_PlayerDef.h"
/*******************/

/**************************************************************
*
* define
*
***************************************************************/
// Added by sjmun. for Emulator
#if 0
#ifdef PDK_EMULATOR		ygsong 080416: binary build also needs this --> moved to MSF_PlayerDef.h
	typedef unsigned long int  uint32;      /* Unsigned 32 bit value */
	typedef unsigned short     uint16;      /* Unsigned 16 bit value */
	typedef unsigned char      uint8;       /* Unsigned 8  bit value */
	typedef signed long int    int32;       /* Signed 32 bit value   */
	typedef signed short       int16;       /* Signed 16 bit value   */
	typedef signed char        int8;        /* Signed 8  bit value   */
	typedef	 unsigned __int64	uint64;		/* Unsigned 64 bit value */
	typedef  unsigned char     uint1;        /* Unsigned 8  bit value type. */
	typedef  unsigned short    uint2;        /* Unsigned 16 bit value type. */
	typedef  unsigned long     uint4;        /* Unsigned 32 bit value type. */

	typedef  signed char       int1;         /* Signed 8  bit value type. */
	typedef  signed short      int2;         /* Signed 16 bit value type. */
	typedef  long int          int4;         /* Signed 32 bit value type. */

//  typedef unsigned char      boolean; 
//  typedef char      byte; 
#endif
#endif

#define MSFPLAYER_MAX_LEN_TEXT_FRAME				255

#define MSFPLAYER_MPEG4_MAX_TITLE_BYTES        			50
#define MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES      		50
#define MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES  		128
#define MSFPLAYER_MPEG4_MAX_RATING_BYTES         		128
#define MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES  		256
#define MSFPLAYER_MPEG4_MAX_OWNER_BYTES         		128
#define MSFPLAYER_MPEG4_MAX_VERSION_BYTES         		128
#define MSFPLAYER_MPEG4_MAX_CREATIONDATE_BYTES 	128
#define MSFPLAYER_MPEG4_MAX_DEVICE_NAME_BYTES     	9
#define MSFPLAYER_MPEG4_MAX_MODEL_NAME_BYTES        	9
#define MSFPLAYER_MPEG4_MAX_ENCODER_INFO_BYTES      	9
#define MSFPLAYER_MPEG4_MAX_MUX_INFO_BYTES             	9
#define MSFPLAYER_MPEG4_MAX_GPS_LATITUDE                   	3
#define MSFPLAYER_MPEG4_MAX_GPS_LONGITUDE           	3
#define MSFPLAYER_MPEG4_MAX_GPS_TIME                       	3
#define MSFPLAYER_MPEG4_MAX_GPS_SURVEY_DATA_BYTES          		9
#define MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_METHOD_BYTES  	64
#define MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_NAME_BYTES    		64
#define MSFPLAYER_MPEG4_MAX_GPS_DATE_BYTES          	12
#define MSFPLAYER_MPEG4_MAX_ALBUM_BYTES                  	50 

#define MSFPLAYER_MPEG4_MAX_GENRE_BYTES				128
#define MSFPLAYER_MPEG4_MAX_CLSF_BYTES				128

#define MSFPLAYER_MPEG4_MAX_TRACKNUM_BYTES         	128

#define MSFPLAYER_MAX_LEN_TEXT_FRAME2				800 //GS260 KIMCHANGHOON 20100129 VPS_BASE

#define MSFPLAYER_CALLER_NONE           			0x00
#define MSFPLAYER_CALLER_PLAYER         			0x01
#define MSFPLAYER_CALLER_MMS            			0x02
#define MSFPLAYER_CALLER_CALL           			0x03
#define MSFPLAYER_CALLER_JAVA           			0x04
#define MSFPLAYER_CALLER_WAP            			0x05

// Event�� Param�� �Ǹ��� ������ ����Ƿ� MSOEM_Player_Import.h�� �̵�. by sjmun. 070703

/**************************************************************
*
* Enum 
*
***************************************************************/

//##
/* <Group SI_Common>
	���� ���ο��� Ringtone type�� ��Ÿ���� �������̴�. */
typedef	enum
{
	E_MSFPLAYER_RINGTONE_TYPE_NONE		= 0x00, ///< None
	E_MSFPLAYER_RINGTONE_TYPE_RESTRICTION	= 0x01, ///< Restriction
	E_MSFPLAYER_RINGTONE_TYPE_VOICE		= 0x02, ///< Voice
	E_MSFPLAYER_RINGTONE_TYPE_VIDEO		= 0x04, ///< Video
	E_MSFPLAYER_RINGTONE_TYPE_ALL			= 0x06 ///< All
} E_MSFPLAYER_RINGTONE_TYPE;		

/* <Group SI_Common>
	���� ���ο��� Streaming type�� ��Ÿ���� �������̴�. */
typedef enum
{
    E_MSFPLAYER_MEDIA_NON_STREAMING = 0, 	///< local clip
    E_MSFPLAYER_MEDIA_STREAMING,     		///< streaming
    E_MSFPLAYER_MEDIA_LIVE_STREAMING, 		///< Live streaming
    //## LGE_UPDATE_S	yjl 2006-10-17
    E_MSFPLAYER_MEDIA_FASTTRACK	///< Fast Track for 4 Lab.
//LGE_UPDATE_E
} E_MSFPLAYER_StreamType;

/* <Group SI_Common>
	���� ���ο��� �̵���� type�� ��Ÿ���� �������̴�. */
typedef enum
{
    E_MSFPLAYER_MEDIA_AUDIO_ONLY=0 	///< Audio Only
   ,E_MSFPLAYER_MEDIA_VIDEO_ONLY		///< Video Only
   ,E_MSFPLAYER_MEDIA_AUDIO_VIDEO	///< Audio + Video
   ,E_MSFPLAYER_MEDIA_VIDEO_STILL_IMAGE	///< Video + Still Image
   ,E_MSFPLAYER_MEDIA_AUDIO_VIDEO_STILL_IMAGE ///< Audio+Video+Still Image
   ,E_MSFPLAYER_MEDIA_VIDEO_TEXT	///< Video + Text
   ,E_MSFPLAYER_MEDIA_AUDIO_TEXT	///< Audio + Text
   ,E_MSFPLAYER_MEDIA_AUDIO_VIDEO_TEXT ///< Audio + Video + Text
   ,E_MSFPLAYER_MEDIA_VIDEO_STILL_IMAGE_TEXT	///< Video + Still Image + Text
   ,E_MSFPLAYER_MEDIA_AUDIO_VIDEO_STILL_IMAGE_TEXT ///< Audio + Video + Still Image + Text
   ,E_MSFPLAYER_MEDIA_VIDEO_MIDI ///< Video + Midi
   ,E_MSFPLAYER_MEDIA_INVALID	///< Invalid
} E_MSFPLAYER_MediaType;

/* <Group SI_Common>
	���� ���ο��� codec�� type�� ��Ÿ���� �������̴�. */
typedef enum
{
   E_MSFPLAYER_CODEC_EVRC=0 		///< EVRC
  ,E_MSFPLAYER_CODEC_QCELP		///< QCELP
  ,E_MSFPLAYER_CODEC_AAC			///< AAC
  ,E_MSFPLAYER_CODEC_AACPLUS		///< AAC+			//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_EAACPLUS		///< Enhanced AAC+		//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_GSM_AMR	///< AMR
  ,E_MSFPLAYER_CODEC_MPEG4		///< MPEG4
  ,E_MSFPLAYER_CODEC_H263 		///< H.263
  ,E_MSFPLAYER_CODEC_STILL_IMAGE	///< Still Image
  ,E_MSFPLAYER_CODEC_TIMED_TEXT	///< Timed Text
  ,E_MSFPLAYER_CODEC_MP3			///< MP3
  ,E_MSFPLAYER_CODEC_H264			///< H.264
  ,E_MSFPLAYER_CODEC_WMA			///< WMA
  ,E_MSFPLAYER_CODEC_WMV			///< common WMV
  ,E_MSFPLAYER_CODEC_WMV1		///< WMV Version 1
  ,E_MSFPLAYER_CODEC_WMV2		///< WMV Version 2
  ,E_MSFPLAYER_CODEC_WMV3		///< WMV Version 3
  ,E_MSFPLAYER_CODEC_AMR_NB		///< AMR NB			//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_AMR_WB		///< AMR WB
  ,E_MSFPLAYER_CODEC_AMR_WB_PLUS	///< AMR WB+
  ,E_MSFPLAYER_CODEC_OGG			///< OGG
  ,E_MSFPLAYER_CODEC_PCM			///< PCM
  ,E_MSFPLAYER_CODEC_REAL			///< REAL				//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_MIDI			///< MIDI				//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_WAV			///< WAV				//ygsong 080401: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_SMAF		///< SMAF				//ygsong 080624: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_XMF			///< XMF					//ygsong 080624: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_IMELODY		///< IMELODY				//ygsong 080624: added according to the MMPlayer spec document
  ,E_MSFPLAYER_CODEC_UNKNOWN 	///< UNKNOWN
} E_MSFPLAYER_CodecType;

/* <Group SI_Common>
	���� ���ο��� Mpeg4�� File Format�� ��Ÿ���� �������̴�. */
typedef enum
{
  E_MSFPLAYER_MPEG4_UNKNOWN_FORMAT_TYPE=0, ///< UNKNOWN
  E_MSFPLAYER_MPEG4_STD_FORMAT_TYPE,		///< STD Format
  E_MSFPLAYER_MPEG4_UUID_FORMAT_TYPE		///< UUID Format
} E_MSFPLAYER_MPEG4FileFormatType;
/* <Group SI_Common>
	���� ���ο��� Mpeg4�� PvxPlaybackControl�� ��Ÿ���� �������̴�. */
typedef enum  // 4��
{
     E_MSFPLAYER_NO_PLAYBACK = 0			///< No Playback
    ,E_MSFPLAYER_PLAYBACK_AFTER_DOWNLOAD	///< Download �� ���
    ,E_MSFPLAYER_PLAYBACK_ASAP			///< ASAP Playback
    ,E_MSFPLAYER_PLAYBACK_RESERVE			/// Playback Reserve
}E_MSFPLAYER_PvxPlaybackControl;// 4��

/* <Group SI_Common>
	Chipset  Type��  ��Ÿ���� �������̴�. */
typedef enum
{
	E_MSFPLAYER_DSP_TYPE_BASEBAND, ///< �⺻ Chipset 
	E_MSFPLAYER_DSP_TYPE_DSP,		///< �ܺ� DSP����� ������ ���
	E_MSFPLAYER_DSP_TYPE_DSP_MP3,	///< �ܺ� DSP ����� MP3��� 
	E_MSFPLAYER_DSP_TYPE_MAX		///< �������� ���� ��Ÿ���� �� 
}E_MSFPLAYER_DSP_TYPE;

/* <Group SI_Common>
	MSF Player���� ����ϴ� ���� API �� ���� API�� ������ ��Ÿ���� �������̴�.*/
typedef enum 
{
	E_MSFPLAYER_API_TYPE_NO, ///<�˼� ���� Type�� ���
	E_MSFPLAYER_API_TYPE_LOCAL_AUDIO, ///<Local Audio�� ���
	E_MSFPLAYER_API_TYPE_PLAYER  ///<�Ϲ��� Player�� ��� ( Streaming, Local Video �� ) 
} E_MSFPLAYER_API_TYPE;

/* <Group SI_Common>
	DRM�� ���� ������ ��� ���� �ʿ��� ������ �����ϴ� ����ü�̴�.*/
typedef struct
{
	T_MSF_INT32	nIndex; 		///< DRM������Ʈ�� �ε���
	T_MSF_INT32 	nPreview;	///< �̸����� ���� ����
}T_MSFPLAYER_DRM;

/* <Group SI_Common>
	Media Plyer���� ����� ��Ƽ�̵���� Ÿ���� �����ϱ� ���� �������̴�.*/
typedef enum 
{
 E_MSFPLAYER_TYPE_NORMAL,		///< Local Play , Streaming Play
 E_MSFPLAYER_TYPE_BUFFER_AUDIO,	///< Audio Buffer Play
 E_MSFPLAYER_TYPE_BUFFER_VIDEO,  ///< Video Buffer Play
 E_MSFPLAYER_TYPE_PROGRESSIVE,	///< Progressive Play
 E_MSFPLAYER_TYPE_PSEUDO_STREAM,	///< Pseudo Stream Play
 E_MSFPLAYER_TYPE_ONE_SEQ, ///< Tone Sequence Play for Java, ���� ���� ����.
 E_MSFPLAYER_TYPE_MIDI_NOTE, ///< MIDI Message Play for Java, ���� ���� ����.
 E_MSFPLAYER_TYPE_STREAMING
} E_MSFPLAYER_TYPE;

/* <Group SI_Common>
	���� �������� ��� ������ �����ϱ� ���� �������̴�.*/
typedef enum
{
 E_MSFPLAYER_GETFRAME_FIRST, ///<ù��° ������ ( ����� ���÷��̸� ���� ��� )
 E_MSFPLAYER_GETFRAME_ORG, ///<���� ������ ( ������ ������ ���� �� ��� ) 
 E_MSFPLAYER_GETFRAME_CURRENT, ///<OSD�� ����� ���÷��� �� ���� ���÷��� ���� ������
}E_MSFPLAYER_GETFRAME_TYPE;

/* <Group SI_Common>
	������ ���÷��� ������ �����ϱ� ���� �������̴�.*/
typedef enum
{
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_PORTRAIT,   ///< ���� �������� ���÷��� �Ѵ�.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_LANDSCAPE,   ///< �ð�������� 90�� ȸ���Ͽ� ���� �������� ���÷��� �Ѵ�.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_MIRROR_X,    ///< ���÷����� �߽ɿ� ��ġ�� ���� ���� �������� �̷����Ͽ� ���÷����Ѵ�. 
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_MIRROR_Y,    ///< ���÷����� �߽ɿ� ��ġ�� ���� ���� �������� �̷����Ͽ� ���÷����Ѵ�.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_QCIF ///< QCIF(Quarter Common Intermediate Format) �������� ���÷����Ѵ�.
}E_MSFPLAYER_VIDEO_ORIENTATION;

/* <Group SI_Common>
	������ ���÷����� LCD�� ������ �����ϱ� ���� �������̴�.*/
typedef enum
{
  E_MSFPLAYER_DISPLAY_SUBLCD, ///<���� ���÷��̸� ����ϴ� ���
  E_MSFPLAYER_DISPLAY_MAINLCD ///<���� ���÷��̸� ����ϴ� ���
}E_MSFPLAYER_DISPLAY_DIRECTION;

/* <Group SI_Common>
	Player Engine�� ���¸� ��Ÿ���� �������̴�. */
typedef enum
{
  E_MSFPLAYER_PLAYER_STATE_UNKNOWN = -1,  ///< UNKNOWN
  E_MSFPLAYER_PLAYER_STATE_IDLE = 26,			///< Idle ���� 
  E_MSFPLAYER_PLAYER_STATE_NOT_INITIALIZED,	///< �ʱ�ȭ ���� ���� ����
  E_MSFPLAYER_PLAYER_STATE_INITIALIZED, 		///< �ʱ�ȭ�� �Ϸ�� ����
  E_MSFPLAYER_PLAYER_STATE_PLAYING = 22,		///< �����/���� ��� ���� ���� 
  E_MSFPLAYER_PLAYER_STATE_PAUSED = 23,		///< �����/���� ����� ��� ������ ���� 
  E_MSFPLAYER_PLAYER_STATE_STOPPED = 17,		///< �����/���� ����� �ߴ��� ���� 
  E_MSFPLAYER_PLAYER_STATE_END_OF_FILE		///< �����/������ ������ ����ؼ� ������ ����
}E_MSFPLAYER_PLAYSTATE; 

/* <Group SI_Common>
	Repeat ������ �����ϱ� ���� �������̴�.*/
typedef enum
{
	E_MSFPLAYER_REPEAT_TYPE_SAVE, ///<�����ݺ� ��� �� �ܺ����ͷ�Ʈ�� �ɷ��� �� �ݺ����� ������ ���� ���.
	E_MSFPLAYER_REPEAT_TYPE_LOAD,///<E_MSFPLAYER_REPEAT_TYPE_SAVE�� ���� ����� �ݺ����� �� �ٽ� �簳�� �� ���.
	E_MSFPLAYER_REPEAT_TYPE_DO,///<�ݺ����� ���� �� ������ ���� ���.
	E_MSFPLAYER_REPEAT_TYPE_MAX ///< �������� ������  ���� MAX��
}E_MSFPLAYER_REPEAT_TYPE;

/* <Group SI_Common>
	�ݺ����� ���� �� ������ �����ϱ� ���� �������̴�.*/
typedef enum
{	
	E_MSFPLAYER_REPEAT_STATE_NONE, ///<������ �ݺ������� �����ϱ� ���� ���.
	E_MSFPLAYER_REPEAT_STATE_A, ///<�ݺ������� ������ġ ����.
	E_MSFPLAYER_REPEAT_STATE_B, ///<�ݺ������� ����ġ ����. 
	E_MSFPLAYER_REPEAT_STATE_MAX ///< �������� ������  ���� MAX��
}E_MSFPLAYER_REPEAT_STATE ;

/* <Group SI_Common>
	MSAPI_Player_Seek���� � Mode�� �������� ��Ÿ���� ���� �������̴�.*/
typedef enum
{
	E_MSFPLAYER_SEEKMODE_TIME,	///<�ð�(ms)�� ���ڷ� ����ϴ� ���
	E_MSFPLAYER_SEEKMODE_ISSEEK, ///<1�� ��������� Seek ���۸� ���Ұ�� (ms����)
	E_MSFPLAYER_SEEKMODE_MAX ///< �������� ������  ���� MAX��
}E_MSFPLAYER_SEEKMODE;

/* <Group SI_Common>
	�̵���� Class ID��  ��Ÿ���� �������̴�. */
typedef enum {
   E_MSFPLAYER_CLSID_MEDIABASE	   = 0,	///< Base, 
   E_MSFPLAYER_CLSID_MEDIAMIDI	   = (E_MSFPLAYER_CLSID_MEDIABASE+  1),	///<MIDI
   E_MSFPLAYER_CLSID_MEDIAMP3 	   = (E_MSFPLAYER_CLSID_MEDIABASE+  2),	///< MP3
   E_MSFPLAYER_CLSID_MEDIAQCP 	   = (E_MSFPLAYER_CLSID_MEDIABASE+  3),	///<QCELP
   E_MSFPLAYER_CLSID_MEDIAPMD 	   = (E_MSFPLAYER_CLSID_MEDIABASE+  4),	///<PMD
   E_MSFPLAYER_CLSID_MEDIAMIDIOUTMSG = (E_MSFPLAYER_CLSID_MEDIABASE+  5),	///< MIDI out message
   E_MSFPLAYER_CLSID_MEDIAMIDIOUTQCP = (E_MSFPLAYER_CLSID_MEDIABASE+  6),	///< MIDI out QCP
   E_MSFPLAYER_CLSID_MEDIAMPEG4	   = (E_MSFPLAYER_CLSID_MEDIABASE+  7),	///< Mpeg4
   E_MSFPLAYER_CLSID_MEDIAMMF 	   = (E_MSFPLAYER_CLSID_MEDIABASE+  8),	///< MMF
   E_MSFPLAYER_CLSID_MEDIAPHR 	   = (E_MSFPLAYER_CLSID_MEDIABASE+  9),	///< PHR
   E_MSFPLAYER_CLSID_MEDIAADPCM	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 10),	///< ADPCM
   E_MSFPLAYER_CLSID_MEDIAAAC 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 11),	///< AAC
   E_MSFPLAYER_CLSID_MEDIAIMELODY    = (E_MSFPLAYER_CLSID_MEDIABASE+ 12),	///< IMelody
   E_MSFPLAYER_CLSID_MEDIAUTIL	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 13),	///<UTIL
   E_MSFPLAYER_CLSID_MEDIAAMR 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 14),	///< AMR
   E_MSFPLAYER_CLSID_MEDIAHVS 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 15),	///< HVS
   E_MSFPLAYER_CLSID_MEDIASAF 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 16),	///< SAF
   E_MSFPLAYER_CLSID_MEDIAWAV 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 17),	///< WAV
   E_MSFPLAYER_CLSID_MEDIA3GP 	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 18),	///< 3gp
   E_MSFPLAYER_CLSID_MEDIARA   	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 19),	///< RA
   E_MSFPLAYER_CLSID_MEDIAWMA   	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 20),	///< WMA
   E_MSFPLAYER_CLSID_MEDIAXMF   	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 21),	///< XMF
 #if defined(WISE_ON_MTK)// WISE_PORTING_KIMHONGSEOK_20090211 :  
   E_MSFPLAYER_CLSID_MEDIAOGG   	   = (E_MSFPLAYER_CLSID_MEDIABASE+ 22),	///< XMF
   E_MSFPLAYER_CLSID_MULTIMEDIA_LAST = (E_MSFPLAYER_CLSID_MEDIABASE+ 23), ///< �������� �� 
  #else
   E_MSFPLAYER_CLSID_MULTIMEDIA_LAST = (E_MSFPLAYER_CLSID_MEDIABASE+ 22) ///< �������� �� 
 #endif
}E_MSFPLAYER_MEDIA_TYPE;
/**************************************************************
*
* Structure 
*
***************************************************************/

//## 

//GS260 KIMCHANGHOON 20100129 VPS_BASE [START]
typedef struct T_MSFPLAYER_MediaASFStdSpec		
{
	T_MSF_UINT16              szTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];
	T_MSF_UINT16              szAuthor[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES];
	T_MSF_UINT16              szCopyright[MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES];
	T_MSF_UINT16              szRating[MSFPLAYER_MPEG4_MAX_RATING_BYTES];
	T_MSF_UINT16              szDescription[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES];
	T_MSF_UINT16              szOwner[MSFPLAYER_MPEG4_MAX_OWNER_BYTES];
	T_MSF_UINT16              szArtist[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES];
	T_MSF_UINT16              szSTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];
	T_MSF_UINT16              szAlbum[MSFPLAYER_MPEG4_MAX_ALBUM_BYTES];
	T_MSF_UINT16              szInfo[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES];
	T_MSF_UINT16              szGenre[MSFPLAYER_MPEG4_MAX_RATING_BYTES];
	T_MSF_UINT16		  szYear[MSFPLAYER_MPEG4_MAX_RATING_BYTES];
	T_MSF_UINT16		  szTrackNumber[MSFPLAYER_MPEG4_MAX_RATING_BYTES];	
	T_MSF_UINT32		  Bitrate;
	T_MSF_UINT32		  SampleRate;
	T_MSF_UINT16		  Channels;
	T_MSF_UINT16              cbAlbumImg;
	T_MSF_UINT8               *pbAlbumImg;
}T_MSFPLAYER_MediaASFStdSpec;

typedef	struct T_MSFPLAYER_ID3TAG
{
	T_MSF_UCHAR	aszTitle[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszAlbum[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszArtist[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszCopyright[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszFiletype[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszTracknumber[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszGenre[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszYear[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszSize[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszUser[MSFPLAYER_MAX_LEN_TEXT_FRAME2 + 1];
	T_MSF_UCHAR	aszAuthor[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszDescription[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_UCHAR	aszComment[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];
	T_MSF_BYTE*	pImgBuf;
	unsigned long	qImgSize;
} T_MSFPLAYER_ID3TAG; //(T_MMP_ID3 => T_MMP_MetaInfo)
//GS260 KIMCHANGHOON 20100129 VPS_BASE [END]

/* <Group SI_Common>
	Mpeg4 ���� ������ ��Ÿ���� ����ü �� �ϳ��̴�. */
typedef struct
{
  T_MSF_UINT16              szTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES]; ///< Ÿ��Ʋ 
  T_MSF_UINT16              szAuthor[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< Author
  T_MSF_UINT16              szCopyright[MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES];///< ���۱��� 
  T_MSF_UINT16              szRating[MSFPLAYER_MPEG4_MAX_RATING_BYTES]; ///< Rating
  T_MSF_UINT16              szDescription[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< ���� 
  T_MSF_UINT16              szOwner[MSFPLAYER_MPEG4_MAX_OWNER_BYTES]; ///< ������ 
  T_MSF_UINT16              szVersion[MSFPLAYER_MPEG4_MAX_VERSION_BYTES];  ///< ���� 
  T_MSF_UINT16              szCreationDate[MSFPLAYER_MPEG4_MAX_CREATIONDATE_BYTES]; ///< �����Ͻ�
  T_MSF_UINT16              szArtist[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< ��Ƽ��Ʈ 
  T_MSF_UINT16              szSTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];		///< ���� Ÿ��Ʋ
  T_MSF_UINT16              szAlbum[MSFPLAYER_MPEG4_MAX_ALBUM_BYTES];	///<  �ٹ� ���� 
  T_MSF_UINT16              szInfo[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< ����
//LGE_UPDATE_S for extra info by yjl on 2006-07-27
  T_MSF_UINT16              szGenre[MSFPLAYER_MPEG4_MAX_GENRE_BYTES]; ///< �帣 
  T_MSF_UINT16		        szTrackNumber[MSFPLAYER_MPEG4_MAX_RATING_BYTES];
  T_MSF_UINT16              szClassification[MSFPLAYER_MPEG4_MAX_CLSF_BYTES]; ///< ��� 
  T_MSF_UINT32              cbAlbumImg;	///< �ٹ���Ʈ ũ��  //GS260 KIMCHANGHOON 20100129 VPS_BASE
  T_MSF_UINT8               *pbAlbumImg;  ///< �ٹ� ��Ʈ ������  //GS260 KIMCHANGHOON 20100129 VPS_BASE  
//LGE_UPDATE_E
} T_MSFPLAYER_MPEG4StdSpec; 

/* <Group SI_Common>
	Mpeg4 ���� ������ ��Ÿ���� ����ü �� �ϳ��̴�. */
typedef struct
{
  T_MSF_UINT32              dwCopyProhibitionFlag; ///< ���� ���� �÷��� 
  T_MSF_UINT32              dwValidityEffectiveDate; ///< ��ȿ ��¥ 
  T_MSF_UINT32              dwValidityPeriod; 		///< ��ȿ �Ⱓ 
  T_MSF_UINT32              dwNumberOfAllowedPlayBacks;  ///< ��� ������ Ƚ�� 

  T_MSF_UINT16              szTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];  ///< Ÿ��Ʋ 
  T_MSF_UINT16              szCopyright[MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES]; ///< ���۱��� 
  T_MSF_UINT16              szAuthor[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< Author
  T_MSF_UINT16              szMemo[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< �޸� 
  T_MSF_UINT32              dwGenerationDLLVersion; ///< DLL ���� 

  T_MSF_UINT32              dwEditFlags;  ///< Edit �÷��� 
  T_MSF_UINT32              dwRecordingMode;  ///< ���ڵ� ��� 
  T_MSF_UINT32              dwRecordingDate; 	///< ���ڵ� ��¥ 

  T_MSF_UINT16              szDeviceName[MSFPLAYER_MPEG4_MAX_DEVICE_NAME_BYTES]; ///< device �̸� 
  T_MSF_UINT16              szModelName[MSFPLAYER_MPEG4_MAX_MODEL_NAME_BYTES]; ///< �� �̸� 
  T_MSF_UINT16              szEncoderInformation[MSFPLAYER_MPEG4_MAX_ENCODER_INFO_BYTES]; ///< encoder ���� 
  T_MSF_UINT16              szMuxInformation[MSFPLAYER_MPEG4_MAX_MUX_INFO_BYTES]; ///< Mux ���� 

  T_MSF_UINT16              wGPSByteOrder;  ///< GPS ���� ���� 
  T_MSF_UINT32              dwGPSVersionID;///< GPS ���� ���� 
  T_MSF_UINT32              dwGPSLatitudeRef;///< GPS ���� ���� 
  T_MSF_UINT32              dwGPSLongitudeRef;///< GPS ���� ���� 
  T_MSF_UINT32              dwGPSAltitudeRef;///< GPS ���� ���� 
  T_MSF_UINT64              GPSLatitudeArray[MSFPLAYER_MPEG4_MAX_GPS_LATITUDE];///< GPS ���� ���� 
  T_MSF_UINT64              GPSLongitudeArray[MSFPLAYER_MPEG4_MAX_GPS_LONGITUDE];///< GPS ���� ���� 
  T_MSF_UINT64              dwGPSAltitude;///< GPS ���� ���� 
  T_MSF_UINT64              GPSTimeArray[MSFPLAYER_MPEG4_MAX_GPS_TIME];///< GPS ���� ���� 
  T_MSF_UINT64              ddwGPSExtensionMapScaleInfo;///< GPS ���� ���� 
  T_MSF_UINT16              szGPSSurveyData[MSFPLAYER_MPEG4_MAX_GPS_SURVEY_DATA_BYTES];///< GPS ���� ���� 
  T_MSF_UINT16              szGPSPositioningMethod[MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_METHOD_BYTES];///< GPS ���� ���� 
  T_MSF_UINT16              szGPSPositioningName[MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_NAME_BYTES];///< GPS ���� ���� 
  T_MSF_UINT16              szGPSDate[MSFPLAYER_MPEG4_MAX_GPS_DATE_BYTES];///< GPS ���� ���� 
} T_MSFPLAYER_MPEG4UUIDSpec;


/* <Group SI_Common>
	Mpeg4 ���� ������ ��Ÿ���� ����ü �� �ϳ��̴�. */
typedef struct 
{
    T_MSFPLAYER_MPEG4StdSpec       	StdSpec;		///< ǥ�� Mpeg4 ���� 
    T_MSF_BOOL                   		bPurgeDowloadedFile; ///< download ���� ���� ���� 
    T_MSF_BOOL                    		bAllowUserPlayback; ///< User Playback ���� 
    E_MSFPLAYER_PvxPlaybackControl 	downloadPlaybackControl;  ///< PVX ��� control 
} T_MSFPLAYER_MPEG4PvxSpec; // 4��

/* <Group SI_Common>
	Mpeg4 ���� ������ ��Ÿ���� ����ü �� �ϳ��̴�. */
typedef union
{
  T_MSFPLAYER_MPEG4StdSpec        	StdSpec;	///< ǥ�� Mpeg4 ���� 
  T_MSFPLAYER_MPEG4UUIDSpec       	UUIDSpec;  ///< UUID ���� 
  T_MSFPLAYER_MPEG4PvxSpec        	PvxSpec;	///< PVX ���� 
  T_MSFPLAYER_MediaASFStdSpec		ASFSpec; //GS260 KIMCHANGHOON 20100129 VPS_BASE
  T_MSFPLAYER_ID3TAG				ID3Tag;		///< MP3 AAC�� ID3 Tag  //GS260 KIMCHANGHOON 20100129 VPS_BASE  
} T_MSFPLAYER_MPEG4SpecEx;

/* <Group SI_Common>
	�̵���� ������ �����ϱ� ���� ����ü�̴�.*/
typedef struct
{
  T_MSF_UINT32                      dwDuration; 				///<  �̵���� total time (msec)
  T_MSF_UINT32                      dwSize;     					///< ������ ũ��
  E_MSFPLAYER_StreamType               streamtype; 					///< ��Ʈ���� Ÿ�� (��Ʈ���ֿ��� ���� ����)
  E_MSFPLAYER_MediaType                mediaType;  					///< ������ Ÿ�� 
  E_MSFPLAYER_CodecType				mediaFileType;
  
  E_MSFPLAYER_CodecType                audioType;  					///< ����� �ڵ� Ÿ��
  E_MSFPLAYER_CodecType                videoType;  					///< ���� �ڵ� Ÿ��

  T_MSF_BOOL                     bRepositioningAllowed;///< Repositioning ��� ����
  T_MSF_BOOL                     bAudioOnlyPlaybackAllowed;///< ������� ��� �������� ����
  T_MSF_BOOL                     bVideoOnlyPlaybackAllowed;///< ������ ��� �������� ����
  T_MSF_UINT32                      dwHeight; 					///<  ���� �������� ����
  T_MSF_UINT32                      dwWidth;  					///<  ���� �������� �ʺ�

#if defined(LGE_VOD_COM)
  T_MSF_UINT32                      dwTotalFrame;///< ��ü �������� ��(1�� ����) 
  T_MSF_UINT32                      dwFrameRate;			///<  ������ ����Ʈ(1�� ����) 
  T_MSF_UINT32                      dwTotalBitRate;			///<  ��ü ��Ʈ ����Ʈ(1�� ����) 
  T_MSF_UINT32                      audioSampFreq;			///<  ����� ���ø� �󵵼�(1�� ����) 
  T_MSF_BYTE                        soundMode;                    ///<  ���� ���  0:mono, 1:stereo (1�� ����) 
  T_MSF_UINT32                      dwPreroll;                    ///<  Only applicable to streaming clips (1�� ����) 
  T_MSF_BOOL                    bMidiPresent;///< �̵� ���� ����, Only applicable to streaming clips(1�� ����) 
  T_MSF_BOOL                    bLinkDataPresent;///< ��ũ ������ ���� ����, Only applicable to streaming clips(1�� ����) 
  T_MSF_UINT32                      dwAudioEncodedBitRate;///< ����� ��Ʈ ����Ʈ(1�� ����) 
#endif

  T_MSF_UINT32                      audioSampFreq;	//build error hym 0202
  T_MSF_UINT32			     				dwNumAudioChannels; ///< ����� ä���� ��ȣ  (4�� ����) 
  T_MSF_UINT32							dwMaxBitrate;		///<  max bitrate (video only) (4�� ����) 
  T_MSF_UINT32							dwFramerate;			///<  frame count per second (4�� ����) 
  E_MSFPLAYER_RINGTONE_TYPE			eRingtoneType;		///<  ringtone type (4�� ����) 


  E_MSFPLAYER_MPEG4FileFormatType      eFormatType;///< ���� ����
  T_MSFPLAYER_MPEG4SpecEx              ExtendedInfo;///< �ΰ� ����
} T_MSFPLAYER_MEDIA_SPEC;

/* <Group SI_Common>
 ���� �̵���� ���� ������ �ð�, �ش� �̵���� ������ �����ϱ� ���� ����ü�̴�.*/ 
typedef struct {
	T_MSF_INT32 eFileType;		///< �̵���� Class ID 
	T_MSF_INT32 dwTotalTime;	///< �̵���� �� �ð� ( ms ���� ) 
	
	void		*pSpec;		///< �ش� �̵�� ������ ������ ���忡 ���� ������ 

} T_MSFPLAYER_MEDIA_SPEC_EX;

/* <Group SI_Common>
	�ʱ�ȭ�� ���� �ʿ��� ������ �����ϱ� ���� ����ü�̴�.*/
typedef struct 
{
 T_MSF_INT8*    			pFileBuffer; ///<���� �̸� �� ��Ʈ���� URN�� ������ Ȥ�� ������ �ּ� ������
 T_MSF_UINT32    			dwBuffSize;///<������ �ּ� �����͸� �� ���, �ش� ������ ũ��
 E_MSFPLAYER_TYPE 		ePlayType;///<����� ��Ƽ�̵���� Ÿ��
 T_MSFPLAYER_DRM 			stDRMParam;///<DRM Ű�� ������� �Ķ����
 #if defined(WISE_ON_MTK)
 E_MSFPLAYER_CodecType	codecType;
 #endif
} T_MSFPLAYER_INIT;

/* <Group SI_Common>
	�������� Rendering ��ġ �� ũ�⸦ ��Ÿ���� ����ü�̴�.*/
typedef struct 
{
 T_MSF_INT32	X; ///<�������� Rendering ���� ��ġ�� X ��ǥ
 T_MSF_INT32	Y;///<�������� Rendering ���� ��ġ�� Y��ǥ
 T_MSF_INT32	Width;///<�������� Rendering X���� ũ��
 T_MSF_INT32	Height;///<�������� Rendering Y���� ũ�� 
} T_MSFPLAYER_CAPTURE_RECT;

/* <Group SI_Common>
	�簢���� ��Ÿ���� ���� �� ��ǥ�� ����Ű�� ����ü�̴�.*/
typedef struct 
{
 T_MSF_INT32	X1;	///< ù��° ��ǥ�� x �� 
 T_MSF_INT32	Y1;	///< ù��° ��ǥ�� y �� 
 T_MSF_INT32	X2;	///< �ι�° ��ǥ�� x �� 
 T_MSF_INT32	Y2;	///< �ι�° ��ǥ�� y �� 
} T_MSFPLAYER_RECT;

#if defined(WISE_ON_MTK) //for oaep
 typedef struct
{
	T_MSF_UINT8		effect_type;	//OAEP_Effect_type
	T_MSF_UINT8		out_type;		//OAEP_Audio_Out_type
	T_MSF_UINT8		dummy1;
	T_MSF_UINT16 	max_volume;	// max_AMPgain
	T_MSF_UINT16	cur_volume;	// AMPgain
} T_MSFPLAYER_OAEP_CMD;
#endif

/* <Group SI_Common>
	�������� Rendering ��ġ�� ��Ÿ���� ����ü�̴�.*/
typedef	struct
{	
	E_MSFPLAYER_META_TYPE	eMetaType;///<��ü�� ���� �ִ� MetaData ��� (bitwisely recorded)
	T_MSF_ACHAR			aszTitle[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1]; ///<������ ����
	T_MSF_ACHAR			aszCopyright[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<������ ���۱�
	T_MSF_ACHAR    		aszArtist[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<��Ƽ��Ʈ �̸�
	T_MSF_ACHAR    		aszAlbum[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///< �ٹ� �̸�
	T_MSF_ACHAR 			aszAuthor[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<������ ������
	T_MSF_ACHAR			aszDescription[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<�������� ���� ����
	T_MSF_ACHAR			aszGenre[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<������ �帣
	T_MSF_ACHAR			aszYrrc[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///< Year of Record
	T_MSF_ACHAR			aszTrackNum[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<Track Number
	T_MSF_ACHAR			aszClsf[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<Classification
// for 4 Lab. metadata start
	void *			pImgHandle;///<�̹��� �ڵ�(4�� ����)
	T_MSF_UINT8 *	pAttachedPic;///<����� ����� ���÷��̵Ǵ� �̹����� ������
	T_MSF_UINT32		unAPicWidth;///<����� ����� ���÷��̵Ǵ� �̹�����  �ʺ�
	T_MSF_UINT32		unAPicHeight;///<����� ����� ���÷��̵Ǵ� �̹����� ����
	T_MSF_INT32		FormatId;	///<���� ���� ���̵�(4�� ����)
       #if defined (WISE_ON_MTK)
        T_MSF_UINT8  nRating; /// Rating (POPM: rr pp pp pp pp)
        T_MSF_UINT32  nPCNT;  /// Play Counter
       #endif
// for 4 Lab. metadata end
// for 1 Lab. mp3 getinfo start
	T_MSF_INT32			valid;///<(1�� ����)
	T_MSF_ACHAR			aszLength[20];				///<���� ����, in format of "hh:mm:ss" (1�� ����)
	T_MSF_ACHAR			aszSize[20];					///< ���� ������, in byte (from 0 to 99MB).(1�� ����)
	T_MSF_ACHAR			aszBitrate[20];				///< ��Ʈ����Ʈ, in bps; in example, "128000".(1�� ����)
	T_MSF_ACHAR			aszSamplingRate[20];			///< ���ø�����Ʈ, in Hz; in example, "44100".(1�� ����)
	T_MSF_ACHAR			aszCodecType[10];			///< �ڵ�Ÿ��, in example, "mp3" or "aac".(1�� ����)
	T_MSF_ACHAR			aszValidDate[15];				///< ��ȿ��¥, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1�� ����)
	T_MSF_ACHAR			aszStartDay[15];				///< ���۳�¥, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1�� ����)
	T_MSF_ACHAR			aszEndDay[15];				///< ���ᳯ¥, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1�� ����)
	T_MSF_UINT8	  		mp3_filetype;				///< ����Ÿ��, "�Ϲ� MP3" : MP3_FILE_TYPE(0), "���Ҹ�" : MP3_BELL_TYPE(1), (1�� ����)
										// "��ü�� Caption" : MP3_CAPTION_UNION_TYPE(2).
										// "�и��� Caption" : MP3_CAPTION_SEPARATE_TYPE(3).
	T_MSF_ACHAR    		aszEncodingType[64];///<���ڵ�Ÿ��(1�� ����)
	T_MSF_ACHAR    		aszSoundMode[64];///<������(1�� ����)
// for 1 Lab. mp3 getinfo end
} T_MSFPLAYER_META_INFO;

/* <Group SI_Common>
 ��Ʈ���� ������ ��ȭ ������ �����ϱ� ���� ����ü�̴�.
 
 Remarks 
 - mode and duration may be ignored by the Qtv player. 
 - Refer to Qtv player API for more details.
*/
typedef struct /* AEEStreamRecordInfo */
{
  T_MSF_INT8* 		pcFilename; ///< ��ȭ ������ ������ ������ �̸� (��� ����)
  T_MSF_BOOL 		bOverwrite; ///<  ���� ���ľ��� ���� (TRUE, FALSE)
  T_MSF_UINT8 		byMode; ///<��ȭ�� Ʈ���� �����ϱ� ���� ��Ʈ ����Ʈ
  T_MSF_UINT32 	unDuration; ///< ��ȭ�� �Ⱓ ( 0, If no limit is enforced )

} T_MSFPLAYER_RECORD_INFO;

/* <Group SI_Common>
	MSF Player�� Ȯ���� ������  ���� ����ü�̴�.
	 T_MSFPLAYER_MEDIA_SPEC_EX �� ���� ������ �Ѵ�.
*/
typedef struct {
	T_MSF_INT32 eFileType;		///< �̵���� Class ID 
	T_MSF_INT32 dwTotalTime;	///< �̵���� �� �ð� ( ms ���� ) 
	
	void		*pSpec;		///< �ش� �̵�� ������ ������ ���忡 ���� ������ 

} T_MSFPLAYER_MMP_MEDIA_SPEC;

/* <Group SI_Common>
	���� �������� ������ �����ϱ� ���� ����ü�̴�.*/
typedef struct
{
	T_MSF_BYTE* pBuff;  ///<�� �������� ������ ������ ������
	T_MSF_INT32 width; ///< �������� �ʺ�
	T_MSF_INT32 height; ///< �������� ����
}T_MSFPLAYER_FRAME_INFO;
	
/* <Group SI_Common>
	����� Frame Callback �Լ��� ��
	�������� width, height �� buffer pointer ���� �޾Ƽ� ó���� �� �ִ�. */
typedef void (*MSFPLAYER_DrawFrameFuncType)(T_MSF_INT32 frm_width, T_MSF_INT32 frm_height, T_MSF_UINT8* frm_data, void* misc_data);


typedef enum 
{
  	E_MSFPLAYER_STATE_IDLE = 0 ,		// 0
	E_MSFPLAYER_STATE_PRE_STOP,	// 1
	E_MSFPLAYER_STATE_STOP,		// 2
	E_MSFPLAYER_STATE_INIT,			// 3
	E_MSFPLAYER_STATE_CONNECT,	// 4
	E_MSFPLAYER_STATE_READY,		// 5
	E_MSFPLAYER_STATE_BUFFER,		// 6
	E_MSFPLAYER_STATE_PRE_PLAY,	// 7
	E_MSFPLAYER_STATE_PLAY,			// 8
	E_MSFPLAYER_STATE_PRE_PAUSE,	// 9
	E_MSFPLAYER_STATE_PAUSE,		// 10
	E_MSFPLAYER_STATE_PRE_RESUME,// 11
	E_MSFPLAYER_STATE_PRE_SEEK,	// 12
	E_MSFPLAYER_STATE_ERROR,		// 13
	
	E_MSFPLAYER_STATE_MAX			// 14
}E_MSFPLAYER_STATE; //MSAPI ������ state 


/**************************************************************
*
* MSAPI Function 
*
***************************************************************/

// ##

extern MSF_RESULT MSAPI_Player_Init(T_MSF_INT32 nInstanceID, T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam);
extern MSF_RESULT MSAPI_Player_Start(T_MSF_INT32 nInstanceID, T_MSF_UINT32  startPos);
extern MSF_RESULT MSAPI_Player_Stop(T_MSF_INT32 nInstanceID);
extern MSF_RESULT MSAPI_Player_Close(T_MSF_INT32 nInstanceID);
extern MSF_RESULT MSAPI_Player_Pause(T_MSF_INT32 nInstanceID, T_MSF_BOOL bRelease);
extern MSF_RESULT MSAPI_Player_Resume(T_MSF_INT32 nInstanceID, T_MSF_BOOL bRestore);
extern MSF_RESULT MSAPI_Player_Seek(T_MSF_INT32 nInstanceID, E_MSFPLAYER_SEEKMODE eSeekMode, T_MSF_INT32 nSeekTime);
extern MSF_RESULT MSAPI_Player_Play(T_MSF_INT32 nInstanceID, T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam, T_MSF_UINT32 nStartPos);
extern MSF_RESULT MSAPI_Player_StartRecord(T_MSF_INT32 nInstanceID, T_MSFPLAYER_RECORD_INFO* pstRecInfo );
extern MSF_RESULT MSAPI_Player_StopRecord(T_MSF_INT32 nInstanceID, T_MSF_BOOL bDelete );
extern MSF_RESULT MSAPI_Player_GetFrame(T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam, 
							E_MSFPLAYER_GETFRAME_TYPE eGetFrameType, T_MSFPLAYER_FRAME_INFO **pFrame);
extern MSF_RESULT MSAPI_Player_GetMediaSpec(T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam,   
							T_MSFPLAYER_MEDIA_SPEC *pstMediaSpec, T_MSF_BOOL bForced);
extern MSF_RESULT MSAPI_Player_GetMetaData(T_MSF_CSTR pFileName,  T_MSFPLAYER_INIT  *pstInitParam,
							T_MSFPLAYER_META_INFO *pstMetaInfo);
extern MSF_RESULT MSAPI_Player_SetMetaData(T_MSF_CSTR pFileName,  T_MSFPLAYER_INIT  *pstInitParam,
							T_MSFPLAYER_META_INFO *pstMetaInfo);
extern MSF_RESULT MSAPI_Player_SetRenderArea(T_MSF_INT32 nInstanceID, T_MSFPLAYER_CAPTURE_RECT tRect, E_MSFPLAYER_VIDEO_ORIENTATION Orientation, 
							E_MSFPLAYER_DISPLAY_DIRECTION LCDDirection);
extern MSF_RESULT MSAPI_Player_SetParam(T_MSF_INT32 nInstanceID, T_MSF_INT32 nParmID, T_MSF_INT32 p1, T_MSF_INT32 p2);
extern MSF_RESULT MSAPI_Player_GetParam(T_MSF_INT32 nInstanceID, T_MSF_INT32 nParmID, T_MSF_INT32* p1, T_MSF_INT32* p2 );
extern MSF_RESULT MSAPI_Player_RegFrameCB(T_MSF_INT32 nInstanceID, MSFPLAYER_DrawFrameFuncType pfnDrawFrameCB, T_MSF_INT32 nColorFormat);
extern MSF_RESULT MSAPI_Player_ScaleFrame(T_MSF_INT32 nInstanceID, T_MSF_INT32 nScaling );
extern MSF_RESULT MSAPI_Player_RepeatAB(T_MSF_INT32 nInstanceID, E_MSFPLAYER_REPEAT_TYPE eRepeatType, E_MSFPLAYER_REPEAT_STATE* pRepeatState);
extern MSF_RESULT MSAPI_Player_GetInstanceID (T_MSF_CSTR pFileName, T_MSF_INT32* pnInstanceID);	//## added by sjmun. 070630
//## Added. Sync with Nyx. 070706
extern MSF_RESULT MSAPI_Player_SetVolume( T_MSF_INT32 nInstanceID, T_MSF_INT32 nVolume );
extern MSF_RESULT MSAPI_Player_GetVolume( T_MSF_INT32 nInstanceID, T_MSF_INT32* pVolume );
extern MSF_RESULT MSAPI_Player_SetAudioPath( T_MSF_INT32 nInstanceID, T_MSF_BOOL bOn, T_MSF_INT32 eState );

#ifdef USE_TEST_MTM	// temporary for MTM
extern void MSAPI_Player_SetApiState(E_MSFPLAYER_STATE state);	// temporary for MTM
extern E_MSFPLAYER_STATE MSAPI_Player_GetApiState(void);	// temporary for MTM
#endif // temporary for MTM

//20100706, jungyeal@lge.com, MUSIC_DB_BG program by norix.noh@lge.com
extern MSF_RESULT MSAPI_Player_GetMusicMetaData(T_MSF_CSTR pFileName,T_MSFPLAYER_META_INFO *pstMetaInfo);
							
#endif // USE_MSAPI_PLAYER

#endif /* _MSAPI_PLAYER_H_ */
