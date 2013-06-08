
#ifndef _MSOEM_PLAYER_
#define _MSOEM_PLAYER_

#include <swihelper.h>

#define MSF_RESULT int

typedef	const wchar_t*	T_MSF_CSTR;		//const unsigned short string pointer
typedef	unsigned short	T_MSF_ACHAR;

/* 수치형 */
typedef  int            T_MSF_BOOL;

typedef  unsigned char  T_MSF_BYTE;
typedef  unsigned char  T_MSF_UINT8;

typedef  unsigned short T_MSF_UINT16;
typedef  unsigned int   T_MSF_UINT32;
typedef  unsigned int   T_MSF_UINT;
typedef  unsigned long  T_MSF_ULONG;

typedef	 signed char    T_MSF_INT8;
typedef  signed short   T_MSF_INT16;
typedef  signed int     T_MSF_INT;
typedef  signed long    T_MSF_INT32;
typedef  signed long    T_MSF_LONG;

typedef unsigned long   T_MSF_QWORD[2];
typedef	unsigned long long	T_MSF_UINT64;

/* 부동소수점형 */
typedef  float          T_MSF_FLOAT;
typedef  double         T_MSF_DOUBLE;

/* 문자형 */
typedef unsigned short  T_MSF_UCHAR;        // unicode charset

/* 파일 */
typedef T_MSF_UINT32    T_MSF_FILE;         // file handle



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

// Event와 Param은 실마다 변동이 생기므로 MSOEM_Player_Import.h로 이동. by sjmun. 070703

/**************************************************************
*
* Enum 
*
***************************************************************/

//##
/* <Group SI_Common>
	스펙 내부에서 Ringtone type을 나타내는 열거형이다. */
typedef	enum
{
	E_MSFPLAYER_RINGTONE_TYPE_NONE		= 0x00, ///< None
	E_MSFPLAYER_RINGTONE_TYPE_RESTRICTION	= 0x01, ///< Restriction
	E_MSFPLAYER_RINGTONE_TYPE_VOICE		= 0x02, ///< Voice
	E_MSFPLAYER_RINGTONE_TYPE_VIDEO		= 0x04, ///< Video
	E_MSFPLAYER_RINGTONE_TYPE_ALL			= 0x06 ///< All
} E_MSFPLAYER_RINGTONE_TYPE;		

/* <Group SI_Common>
	스펙 내부에서 Streaming type을 나타내는 열거형이다. */
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
	스펙 내부에서 미디어의 type을 나타내는 열거형이다. */
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
	스펙 내부에서 codec의 type을 나타내는 열거형이다. */
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
	스펙 내부에서 Mpeg4의 File Format을 나타내는 열거형이다. */
typedef enum
{
  E_MSFPLAYER_MPEG4_UNKNOWN_FORMAT_TYPE=0, ///< UNKNOWN
  E_MSFPLAYER_MPEG4_STD_FORMAT_TYPE,		///< STD Format
  E_MSFPLAYER_MPEG4_UUID_FORMAT_TYPE		///< UUID Format
} E_MSFPLAYER_MPEG4FileFormatType;
/* <Group SI_Common>
	스펙 내부에서 Mpeg4의 PvxPlaybackControl을 나타내는 열거형이다. */
typedef enum  // 4실
{
     E_MSFPLAYER_NO_PLAYBACK = 0			///< No Playback
    ,E_MSFPLAYER_PLAYBACK_AFTER_DOWNLOAD	///< Download 후 재생
    ,E_MSFPLAYER_PLAYBACK_ASAP			///< ASAP Playback
    ,E_MSFPLAYER_PLAYBACK_RESERVE			/// Playback Reserve
}E_MSFPLAYER_PvxPlaybackControl;// 4실

/* <Group SI_Common>
	Chipset  Type을  나타내는 열거형이다. */
typedef enum
{
	E_MSFPLAYER_DSP_TYPE_BASEBAND, ///< 기본 Chipset 
	E_MSFPLAYER_DSP_TYPE_DSP,		///< 외부 DSP사용한 동영상 재생
	E_MSFPLAYER_DSP_TYPE_DSP_MP3,	///< 외부 DSP 사용한 MP3재생 
	E_MSFPLAYER_DSP_TYPE_MAX		///< 열거형의 끝을 나타내는 값 
}E_MSFPLAYER_DSP_TYPE;

/* <Group SI_Common>
	MSF Player에서 사용하는 내부 API 및 포팅 API의 종류를 나타내는 열거형이다.*/
typedef enum 
{
	E_MSFPLAYER_API_TYPE_NO, ///<알수 없는 Type일 경우
	E_MSFPLAYER_API_TYPE_LOCAL_AUDIO, ///<Local Audio의 경우
	E_MSFPLAYER_API_TYPE_PLAYER  ///<일반적 Player의 경우 ( Streaming, Local Video 등 ) 
} E_MSFPLAYER_API_TYPE;

/* <Group SI_Common>
	DRM의 관련 정보를 얻기 위해 필요한 정보를 저장하는 구조체이다.*/
typedef struct
{
	T_MSF_INT32	nIndex; 		///< DRM오프젝트의 인덱스
	T_MSF_INT32 	nPreview;	///< 미리보기 지원 여부
}T_MSFPLAYER_DRM;

/* <Group SI_Common>
	Media Plyer에서 재생할 멀티미디어의 타입을 정의하기 위한 열거형이다.*/
typedef enum 
{
 E_MSFPLAYER_TYPE_NORMAL,		///< Local Play , Streaming Play
 E_MSFPLAYER_TYPE_BUFFER_AUDIO,	///< Audio Buffer Play
 E_MSFPLAYER_TYPE_BUFFER_VIDEO,  ///< Video Buffer Play
 E_MSFPLAYER_TYPE_PROGRESSIVE,	///< Progressive Play
 E_MSFPLAYER_TYPE_PSEUDO_STREAM,	///< Pseudo Stream Play
 E_MSFPLAYER_TYPE_ONE_SEQ, ///< Tone Sequence Play for Java, 현재 지원 안함.
 E_MSFPLAYER_TYPE_MIDI_NOTE, ///< MIDI Message Play for Java, 현재 지원 안함.
 E_MSFPLAYER_TYPE_STREAMING
} E_MSFPLAYER_TYPE;

/* <Group SI_Common>
	비디오 프레임을 얻는 종류를 정의하기 위한 열거형이다.*/
typedef enum
{
 E_MSFPLAYER_GETFRAME_FIRST, ///<첫번째 프레임 ( 썸네일 디스플레이를 위해 사용 )
 E_MSFPLAYER_GETFRAME_ORG, ///<원본 프레임 ( 프레임 사이즈 조절 시 사용 ) 
 E_MSFPLAYER_GETFRAME_CURRENT, ///<OSD를 사용해 디스플레이 시 현재 디스플레이 중인 프레임
}E_MSFPLAYER_GETFRAME_TYPE;

/* <Group SI_Common>
	비디오의 디스플레이 방향을 정의하기 위한 열거형이다.*/
typedef enum
{
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_PORTRAIT,   ///< 세로 방향으로 디스플레이 한다.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_LANDSCAPE,   ///< 시계방향으로 90도 회전하여 가로 방향으로 디스플레이 한다.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_MIRROR_X,    ///< 디스플레이의 중심에 위치한 세로 축을 기준으로 미러링하여 디스플레이한다. 
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_MIRROR_Y,    ///< 디스플레이의 중심에 위치한 가로 축을 기준으로 미러링하여 디스플레이한다.
  E_MSFPLAYER_DISPLAY_ORIENTATION_FLAG_QCIF ///< QCIF(Quarter Common Intermediate Format) 형식으로 디스플레이한다.
}E_MSFPLAYER_VIDEO_ORIENTATION;

/* <Group SI_Common>
	비디오를 디스플레이할 LCD의 종류를 정의하기 위한 열거형이다.*/
typedef enum
{
  E_MSFPLAYER_DISPLAY_SUBLCD, ///<보조 디스플레이를 사용하는 경우
  E_MSFPLAYER_DISPLAY_MAINLCD ///<메인 디스플레이를 사용하는 경우
}E_MSFPLAYER_DISPLAY_DIRECTION;

/* <Group SI_Common>
	Player Engine의 상태를 나타내는 열거형이다. */
typedef enum
{
  E_MSFPLAYER_PLAYER_STATE_UNKNOWN = -1,  ///< UNKNOWN
  E_MSFPLAYER_PLAYER_STATE_IDLE = 26,			///< Idle 상태 
  E_MSFPLAYER_PLAYER_STATE_NOT_INITIALIZED,	///< 초기화 되지 않은 상태
  E_MSFPLAYER_PLAYER_STATE_INITIALIZED, 		///< 초기화가 완료된 상태
  E_MSFPLAYER_PLAYER_STATE_PLAYING = 22,		///< 오디오/비디오 재생 중인 상태 
  E_MSFPLAYER_PLAYER_STATE_PAUSED = 23,		///< 오디오/비디오 재생을 잠시 정지한 상태 
  E_MSFPLAYER_PLAYER_STATE_STOPPED = 17,		///< 오디오/비디오 재생을 중단한 상태 
  E_MSFPLAYER_PLAYER_STATE_END_OF_FILE		///< 오디오/비디오를 끝까지 재생해서 정지된 상태
}E_MSFPLAYER_PLAYSTATE; 

/* <Group SI_Common>
	Repeat 유형을 설정하기 위한 열거형이다.*/
typedef enum
{
	E_MSFPLAYER_REPEAT_TYPE_SAVE, ///<구간반복 재생 중 외부인터럽트가 걸려을 때 반복구간 저장을 위해 사용.
	E_MSFPLAYER_REPEAT_TYPE_LOAD,///<E_MSFPLAYER_REPEAT_TYPE_SAVE에 의해 저장된 반복구간 을 다시 재개할 때 사용.
	E_MSFPLAYER_REPEAT_TYPE_DO,///<반복구간 설정 및 해제를 위해 사용.
	E_MSFPLAYER_REPEAT_TYPE_MAX ///< 열거형의 범위를  위한 MAX값
}E_MSFPLAYER_REPEAT_TYPE;

/* <Group SI_Common>
	반복구간 설정 및 해제를 설정하기 위한 열거형이다.*/
typedef enum
{	
	E_MSFPLAYER_REPEAT_STATE_NONE, ///<설정된 반복구간을 해제하기 위해 사용.
	E_MSFPLAYER_REPEAT_STATE_A, ///<반복구간의 시작위치 설정.
	E_MSFPLAYER_REPEAT_STATE_B, ///<반복구간의 끝위치 설정. 
	E_MSFPLAYER_REPEAT_STATE_MAX ///< 열거형의 범위를  위한 MAX값
}E_MSFPLAYER_REPEAT_STATE ;

/* <Group SI_Common>
	MSAPI_Player_Seek에서 어떤 Mode로 수행할지 나타내기 위한 열거형이다.*/
typedef enum
{
	E_MSFPLAYER_SEEKMODE_TIME,	///<시간(ms)을 인자로 사용하는 경우
	E_MSFPLAYER_SEEKMODE_ISSEEK, ///<1실 오디오에서 Seek 동작만 원할경우 (ms단위)
	E_MSFPLAYER_SEEKMODE_MAX ///< 열거형의 범위를  위한 MAX값
}E_MSFPLAYER_SEEKMODE;

/* <Group SI_Common>
	미디어의 Class ID를  나타내는 열거형이다. */
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
   E_MSFPLAYER_CLSID_MULTIMEDIA_LAST = (E_MSFPLAYER_CLSID_MEDIABASE+ 23), ///< 열거형의 끝 
  #else
   E_MSFPLAYER_CLSID_MULTIMEDIA_LAST = (E_MSFPLAYER_CLSID_MEDIABASE+ 22) ///< 열거형의 끝 
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
	Mpeg4 내부 스펙을 나타내는 구조체 중 하나이다. */
typedef struct
{
  T_MSF_UINT16              szTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES]; ///< 타이틀 
  T_MSF_UINT16              szAuthor[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< Author
  T_MSF_UINT16              szCopyright[MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES];///< 저작권자 
  T_MSF_UINT16              szRating[MSFPLAYER_MPEG4_MAX_RATING_BYTES]; ///< Rating
  T_MSF_UINT16              szDescription[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< 설명 
  T_MSF_UINT16              szOwner[MSFPLAYER_MPEG4_MAX_OWNER_BYTES]; ///< 소유자 
  T_MSF_UINT16              szVersion[MSFPLAYER_MPEG4_MAX_VERSION_BYTES];  ///< 버전 
  T_MSF_UINT16              szCreationDate[MSFPLAYER_MPEG4_MAX_CREATIONDATE_BYTES]; ///< 생성일시
  T_MSF_UINT16              szArtist[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< 아티스트 
  T_MSF_UINT16              szSTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];		///< 서브 타이틀
  T_MSF_UINT16              szAlbum[MSFPLAYER_MPEG4_MAX_ALBUM_BYTES];	///<  앨범 제목 
  T_MSF_UINT16              szInfo[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< 정보
//LGE_UPDATE_S for extra info by yjl on 2006-07-27
  T_MSF_UINT16              szGenre[MSFPLAYER_MPEG4_MAX_GENRE_BYTES]; ///< 장르 
  T_MSF_UINT16		        szTrackNumber[MSFPLAYER_MPEG4_MAX_RATING_BYTES];
  T_MSF_UINT16              szClassification[MSFPLAYER_MPEG4_MAX_CLSF_BYTES]; ///< 등급 
  T_MSF_UINT32              cbAlbumImg;	///< 앨범아트 크기  //GS260 KIMCHANGHOON 20100129 VPS_BASE
  T_MSF_UINT8               *pbAlbumImg;  ///< 앨범 아트 데이터  //GS260 KIMCHANGHOON 20100129 VPS_BASE  
//LGE_UPDATE_E
} T_MSFPLAYER_MPEG4StdSpec; 

/* <Group SI_Common>
	Mpeg4 내부 스펙을 나타내는 구조체 중 하나이다. */
typedef struct
{
  T_MSF_UINT32              dwCopyProhibitionFlag; ///< 복사 금지 플래그 
  T_MSF_UINT32              dwValidityEffectiveDate; ///< 유효 날짜 
  T_MSF_UINT32              dwValidityPeriod; 		///< 유효 기간 
  T_MSF_UINT32              dwNumberOfAllowedPlayBacks;  ///< 재생 가능한 횟수 

  T_MSF_UINT16              szTitle[MSFPLAYER_MPEG4_MAX_TITLE_BYTES];  ///< 타이틀 
  T_MSF_UINT16              szCopyright[MSFPLAYER_MPEG4_MAX_COPYRIGHT_BYTES]; ///< 저작권자 
  T_MSF_UINT16              szAuthor[MSFPLAYER_MPEG4_MAX_AUTHOR_BYTES]; ///< Author
  T_MSF_UINT16              szMemo[MSFPLAYER_MPEG4_MAX_DESCRIPTION_BYTES]; ///< 메모 
  T_MSF_UINT32              dwGenerationDLLVersion; ///< DLL 버전 

  T_MSF_UINT32              dwEditFlags;  ///< Edit 플래그 
  T_MSF_UINT32              dwRecordingMode;  ///< 레코딩 모드 
  T_MSF_UINT32              dwRecordingDate; 	///< 레코딩 날짜 

  T_MSF_UINT16              szDeviceName[MSFPLAYER_MPEG4_MAX_DEVICE_NAME_BYTES]; ///< device 이름 
  T_MSF_UINT16              szModelName[MSFPLAYER_MPEG4_MAX_MODEL_NAME_BYTES]; ///< 모델 이름 
  T_MSF_UINT16              szEncoderInformation[MSFPLAYER_MPEG4_MAX_ENCODER_INFO_BYTES]; ///< encoder 정보 
  T_MSF_UINT16              szMuxInformation[MSFPLAYER_MPEG4_MAX_MUX_INFO_BYTES]; ///< Mux 정보 

  T_MSF_UINT16              wGPSByteOrder;  ///< GPS 관련 정보 
  T_MSF_UINT32              dwGPSVersionID;///< GPS 관련 정보 
  T_MSF_UINT32              dwGPSLatitudeRef;///< GPS 관련 정보 
  T_MSF_UINT32              dwGPSLongitudeRef;///< GPS 관련 정보 
  T_MSF_UINT32              dwGPSAltitudeRef;///< GPS 관련 정보 
  T_MSF_UINT64              GPSLatitudeArray[MSFPLAYER_MPEG4_MAX_GPS_LATITUDE];///< GPS 관련 정보 
  T_MSF_UINT64              GPSLongitudeArray[MSFPLAYER_MPEG4_MAX_GPS_LONGITUDE];///< GPS 관련 정보 
  T_MSF_UINT64              dwGPSAltitude;///< GPS 관련 정보 
  T_MSF_UINT64              GPSTimeArray[MSFPLAYER_MPEG4_MAX_GPS_TIME];///< GPS 관련 정보 
  T_MSF_UINT64              ddwGPSExtensionMapScaleInfo;///< GPS 관련 정보 
  T_MSF_UINT16              szGPSSurveyData[MSFPLAYER_MPEG4_MAX_GPS_SURVEY_DATA_BYTES];///< GPS 관련 정보 
  T_MSF_UINT16              szGPSPositioningMethod[MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_METHOD_BYTES];///< GPS 관련 정보 
  T_MSF_UINT16              szGPSPositioningName[MSFPLAYER_MPEG4_MAX_GPS_POSITIONING_NAME_BYTES];///< GPS 관련 정보 
  T_MSF_UINT16              szGPSDate[MSFPLAYER_MPEG4_MAX_GPS_DATE_BYTES];///< GPS 관련 정보 
} T_MSFPLAYER_MPEG4UUIDSpec;


/* <Group SI_Common>
	Mpeg4 내부 스펙을 나타내는 구조체 중 하나이다. */
typedef struct 
{
    T_MSFPLAYER_MPEG4StdSpec       	StdSpec;		///< 표준 Mpeg4 스펙 
    T_MSF_BOOL                   		bPurgeDowloadedFile; ///< download 파일 삭제 여부 
    T_MSF_BOOL                    		bAllowUserPlayback; ///< User Playback 여부 
    E_MSFPLAYER_PvxPlaybackControl 	downloadPlaybackControl;  ///< PVX 재생 control 
} T_MSFPLAYER_MPEG4PvxSpec; // 4실

/* <Group SI_Common>
	Mpeg4 내부 스펙을 나타내는 구조체 중 하나이다. */
typedef union
{
  T_MSFPLAYER_MPEG4StdSpec        	StdSpec;	///< 표준 Mpeg4 스펙 
  T_MSFPLAYER_MPEG4UUIDSpec       	UUIDSpec;  ///< UUID 스펙 
  T_MSFPLAYER_MPEG4PvxSpec        	PvxSpec;	///< PVX 스펙 
  T_MSFPLAYER_MediaASFStdSpec		ASFSpec; //GS260 KIMCHANGHOON 20100129 VPS_BASE
  T_MSFPLAYER_ID3TAG				ID3Tag;		///< MP3 AAC의 ID3 Tag  //GS260 KIMCHANGHOON 20100129 VPS_BASE  
} T_MSFPLAYER_MPEG4SpecEx;

/* <Group SI_Common>
	미디어의 스펙을 저장하기 위한 구조체이다.*/
typedef struct
{
  T_MSF_UINT32                      dwDuration; 				///<  미디어의 total time (msec)
  T_MSF_UINT32                      dwSize;     					///< 파일의 크기
  E_MSFPLAYER_StreamType               streamtype; 					///< 스트리밍 타입 (스트리밍에만 적용 가능)
  E_MSFPLAYER_MediaType                mediaType;  					///< 컨텐츠 타입 
  E_MSFPLAYER_CodecType				mediaFileType;
  
  E_MSFPLAYER_CodecType                audioType;  					///< 오디오 코덱 타입
  E_MSFPLAYER_CodecType                videoType;  					///< 비디오 코덱 타입

  T_MSF_BOOL                     bRepositioningAllowed;///< Repositioning 허용 여부
  T_MSF_BOOL                     bAudioOnlyPlaybackAllowed;///< 오디오만 재생 가능한지 여부
  T_MSF_BOOL                     bVideoOnlyPlaybackAllowed;///< 비디오만 재생 가능한지 여부
  T_MSF_UINT32                      dwHeight; 					///<  비디오 프레임의 높이
  T_MSF_UINT32                      dwWidth;  					///<  비디오 프레임의 너비

#if defined(LGE_VOD_COM)
  T_MSF_UINT32                      dwTotalFrame;///< 전체 프레임의 수(1실 전용) 
  T_MSF_UINT32                      dwFrameRate;			///<  프레임 레이트(1실 전용) 
  T_MSF_UINT32                      dwTotalBitRate;			///<  전체 비트 레이트(1실 전용) 
  T_MSF_UINT32                      audioSampFreq;			///<  오디오 샘플링 빈도수(1실 전용) 
  T_MSF_BYTE                        soundMode;                    ///<  사운드 모드  0:mono, 1:stereo (1실 전용) 
  T_MSF_UINT32                      dwPreroll;                    ///<  Only applicable to streaming clips (1실 전용) 
  T_MSF_BOOL                    bMidiPresent;///< 미디 존재 여부, Only applicable to streaming clips(1실 전용) 
  T_MSF_BOOL                    bLinkDataPresent;///< 링크 데이터 존재 여부, Only applicable to streaming clips(1실 전용) 
  T_MSF_UINT32                      dwAudioEncodedBitRate;///< 오디오 비트 레이트(1실 전용) 
#endif

  T_MSF_UINT32                      audioSampFreq;	//build error hym 0202
  T_MSF_UINT32			     				dwNumAudioChannels; ///< 오디오 채널의 번호  (4실 전용) 
  T_MSF_UINT32							dwMaxBitrate;		///<  max bitrate (video only) (4실 전용) 
  T_MSF_UINT32							dwFramerate;			///<  frame count per second (4실 전용) 
  E_MSFPLAYER_RINGTONE_TYPE			eRingtoneType;		///<  ringtone type (4실 전용) 


  E_MSFPLAYER_MPEG4FileFormatType      eFormatType;///< 파일 포맷
  T_MSFPLAYER_MPEG4SpecEx              ExtendedInfo;///< 부가 정보
} T_MSFPLAYER_MEDIA_SPEC;

/* <Group SI_Common>
 각종 미디어의 파일 종류와 시간, 해당 미디어의 포맷을 저장하기 위한 구조체이다.*/ 
typedef struct {
	T_MSF_INT32 eFileType;		///< 미디어의 Class ID 
	T_MSF_INT32 dwTotalTime;	///< 미디어의 총 시간 ( ms 단위 ) 
	
	void		*pSpec;		///< 해당 미디어 데이터 포멧의 스펙에 대한 포인터 

} T_MSFPLAYER_MEDIA_SPEC_EX;

/* <Group SI_Common>
	초기화를 위해 필요한 정보를 저장하기 위한 구조체이다.*/
typedef struct 
{
 T_MSF_INT8*    			pFileBuffer; ///<파일 이름 및 스트리밍 URN의 포인터 혹은 버퍼의 주소 포인터
 T_MSF_UINT32    			dwBuffSize;///<버퍼의 주소 포인터를 쓸 경우, 해당 버퍼의 크기
 E_MSFPLAYER_TYPE 		ePlayType;///<재생할 멀티미디어의 타입
 T_MSFPLAYER_DRM 			stDRMParam;///<DRM 키를 얻기위한 파라미터
 #if defined(WISE_ON_MTK)
 E_MSFPLAYER_CodecType	codecType;
 #endif
} T_MSFPLAYER_INIT;

/* <Group SI_Common>
	프레임의 Rendering 위치 및 크기를 나타내는 구조체이다.*/
typedef struct 
{
 T_MSF_INT32	X; ///<프레임의 Rendering 시작 위치의 X 좌표
 T_MSF_INT32	Y;///<프레임의 Rendering 시작 위치의 Y좌표
 T_MSF_INT32	Width;///<프레임의 Rendering X방향 크기
 T_MSF_INT32	Height;///<프레임의 Rendering Y방향 크기 
} T_MSFPLAYER_CAPTURE_RECT;

/* <Group SI_Common>
	사각형을 나타내기 위한 두 좌표를 가리키는 구조체이다.*/
typedef struct 
{
 T_MSF_INT32	X1;	///< 첫번째 좌표의 x 값 
 T_MSF_INT32	Y1;	///< 첫번째 좌표의 y 값 
 T_MSF_INT32	X2;	///< 두번째 좌표의 x 값 
 T_MSF_INT32	Y2;	///< 두번째 좌표의 y 값 
} T_MSFPLAYER_RECT;

typedef enum
{
    E_MSFPLAYER_META_NONE			= 0x00000000
    ,E_MSFPLAYER_META_TITLE		= 0x00000001
    ,E_MSFPLAYER_META_ALBUM		= 0x00000002
    ,E_MSFPLAYER_META_ARTIST		= 0x00000004
    ,E_MSFPLAYER_META_COPYRIGHT	= 0x00000008
    ,E_MSFPLAYER_META_AUTHOR		= 0x00000010
    ,E_MSFPLAYER_META_DESCRIPTION	= 0x00000020
    ,E_MSFPLAYER_META_GENRE		= 0x00000040
    ,E_MSFPLAYER_META_YEAR			= 0x00000080
    ,E_MSFPLAYER_META_TRACKNUM		= 0x00000100
    ,E_MSFPLAYER_META_CLSF			= 0x00000200
    ,E_MSFPLAYER_META_FILEINFO		= 0x000003FF
    ,E_MSFPLAYER_META_APIC			= 0x00000400
       #if defined (WISE_ON_MTK)
        ,E_MSFPLAYER_META_RATING  = 0x00000800
        ,E_MSFPLAYER_META_PCOUNT  = 0x00001000
       #endif
#if defined (LGE_FEATURE_MUSIC_BROWSER_WIDGET)
    ,E_MSFPLAYER_META_WIDGET_APIC	= 0x0002000
    ,E_MSFPLAYER_META_PLAYER		= 0x00003FFF
    ,E_MSFPLAYER_META_MAX			= 0x00003FFF	///< ¿­°ÅÇüÀÇ  ³¡
#else
    ,E_MSFPLAYER_META_PLAYER		= 0x000007FF
    ,E_MSFPLAYER_META_MAX			= 0x000007FF	///< ¿­°ÅÇüÀÇ  ³¡
#endif
} E_MSFPLAYER_META_TYPE;


/* <Group SI_Common>
	프레임의 Rendering 위치를 나타내는 구조체이다.*/
typedef	struct
{	
	E_MSFPLAYER_META_TYPE	eMetaType;///<객체가 갖고 있는 MetaData 목록 (bitwisely recorded)
	T_MSF_ACHAR			aszTitle[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1]; ///<컨텐츠 제목
	T_MSF_ACHAR			aszCopyright[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<컨텐츠 저작권
	T_MSF_ACHAR    		aszArtist[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<아티스트 이름
	T_MSF_ACHAR    		aszAlbum[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///< 앨범 이름
	T_MSF_ACHAR 			aszAuthor[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<컨텐츠 제작자
	T_MSF_ACHAR			aszDescription[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<컨텐츠에 관한 설명
	T_MSF_ACHAR			aszGenre[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<컨텐츠 장르
	T_MSF_ACHAR			aszYrrc[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///< Year of Record
	T_MSF_ACHAR			aszTrackNum[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<Track Number
	T_MSF_ACHAR			aszClsf[MSFPLAYER_MAX_LEN_TEXT_FRAME + 1];///<Classification
// for 4 Lab. metadata start
	void *			pImgHandle;///<이미지 핸들(4실 전용)
	T_MSF_UINT8 *	pAttachedPic;///<오디오 재생시 디스플레이되는 이미지의 포인터
	T_MSF_UINT32		unAPicWidth;///<오디오 재생시 디스플레이되는 이미지의  너비
	T_MSF_UINT32		unAPicHeight;///<오디오 재생시 디스플레이되는 이미지의 높이
	T_MSF_INT32		FormatId;	///<파일 포맷 아이디(4실 전용)
       #if defined (WISE_ON_MTK)
        T_MSF_UINT8  nRating; /// Rating (POPM: rr pp pp pp pp)
        T_MSF_UINT32  nPCNT;  /// Play Counter
       #endif
// for 4 Lab. metadata end
// for 1 Lab. mp3 getinfo start
	T_MSF_INT32			valid;///<(1실 전용)
	T_MSF_ACHAR			aszLength[20];				///<파일 길이, in format of "hh:mm:ss" (1실 전용)
	T_MSF_ACHAR			aszSize[20];					///< 파일 사이즈, in byte (from 0 to 99MB).(1실 전용)
	T_MSF_ACHAR			aszBitrate[20];				///< 비트레이트, in bps; in example, "128000".(1실 전용)
	T_MSF_ACHAR			aszSamplingRate[20];			///< 샘플링레이트, in Hz; in example, "44100".(1실 전용)
	T_MSF_ACHAR			aszCodecType[10];			///< 코덱타입, in example, "mp3" or "aac".(1실 전용)
	T_MSF_ACHAR			aszValidDate[15];				///< 유효날짜, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1실 전용)
	T_MSF_ACHAR			aszStartDay[15];				///< 시작날짜, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1실 전용)
	T_MSF_ACHAR			aszEndDay[15];				///< 종료날짜, with format like "YYYYMMDDHHMMSSZ+09"; but, discard "Z+09".(1실 전용)
	T_MSF_UINT8	  		mp3_filetype;				///< 파일타입, "일반 MP3" : MP3_FILE_TYPE(0), "벨소리" : MP3_BELL_TYPE(1), (1실 전용)
										// "일체형 Caption" : MP3_CAPTION_UNION_TYPE(2).
										// "분리형 Caption" : MP3_CAPTION_SEPARATE_TYPE(3).
	T_MSF_ACHAR    		aszEncodingType[64];///<엔코딩타입(1실 전용)
	T_MSF_ACHAR    		aszSoundMode[64];///<사운드모드(1실 전용)
// for 1 Lab. mp3 getinfo end
} T_MSFPLAYER_META_INFO;

/* <Group SI_Common>
 스트리밍 비디오의 녹화 정보를 저장하기 위한 구조체이다.
 
 Remarks 
 - mode and duration may be ignored by the Qtv player. 
 - Refer to Qtv player API for more details.
*/
typedef struct /* AEEStreamRecordInfo */
{
  T_MSF_INT8* 		pcFilename; ///< 녹화 내용을 저장할 파일의 이름 (경로 포함)
  T_MSF_BOOL 		bOverwrite; ///<  파일 겹쳐쓰기 여부 (TRUE, FALSE)
  T_MSF_UINT8 		byMode; ///<녹화할 트랙을 선택하기 위한 비트 마스트
  T_MSF_UINT32 	unDuration; ///< 녹화할 기간 ( 0, If no limit is enforced )

} T_MSFPLAYER_RECORD_INFO;

/* <Group SI_Common>
	MSF Player의 확장형 스펙을  위한 구조체이다.
	 T_MSFPLAYER_MEDIA_SPEC_EX 와 같은 역할을 한다.
*/
typedef struct {
	T_MSF_INT32 eFileType;		///< 미디어의 Class ID 
	T_MSF_INT32 dwTotalTime;	///< 미디어의 총 시간 ( ms 단위 ) 
	
	void		*pSpec;		///< 해당 미디어 데이터 포멧의 스펙에 대한 포인터 

} T_MSFPLAYER_MMP_MEDIA_SPEC;

/* <Group SI_Common>
	비디오 프레임의 정보를 저장하기 위한 구조체이다.*/
typedef struct
{
	T_MSF_BYTE* pBuff;  ///<한 프레임을 저장한 버퍼의 포인터
	T_MSF_INT32 width; ///< 프레임의 너비
	T_MSF_INT32 height; ///< 프레임의 높이
}T_MSFPLAYER_FRAME_INFO;
	
/* <Group SI_Common>
	등록할 Frame Callback 함수의 형
	프레임의 width, height 와 buffer pointer 등을 받아서 처리할 수 있다. */
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
}E_MSFPLAYER_STATE; //MSAPI 고정부 state 





#define MSFPLAYER_PARAM_SET_BASE	10000 + 100
#define MSFPLAYER_PARAM_SET_VOLUME	( MSFPLAYER_PARAM_SET_BASE + 3 )




#define MSFPLAYER_PARAM_GET_BASE	10000 + 200
#define MSFPLAYER_PARAM_MP3_BASE	10000 + 300

#define MSFPLAYER_PARAM_CHECK_RECORD_SPACE		( MSFPLAYER_PARAM_GET_BASE + 1 )
#define MSFPLAYER_PARAM_IS_PAUSED				( MSFPLAYER_PARAM_GET_BASE + 2 )
#define MSFPLAYER_PARAM_IS_PLAYING				( MSFPLAYER_PARAM_GET_BASE + 3 )
#define MSFPLAYER_PARAM_GET_VOLUME				( MSFPLAYER_PARAM_GET_BASE + 4 )
#define MSFPLAYER_PARAM_GET_ELAPSED_TIME		( MSFPLAYER_PARAM_GET_BASE + 5 )
#define MSFPLAYER_PARAM_GET_TOTAL_TIME 		( MSFPLAYER_PARAM_GET_BASE + 6 )
#define MSFPLAYER_PARAM_GET_PLAY_POS			( MSFPLAYER_PARAM_GET_BASE + 7 )
#define MSFPLAYER_PARAM_GET_SOUND_MODE 		( MSFPLAYER_PARAM_GET_BASE + 8 )
#define MSFPLAYER_PARAM_GET_MEDIA_SPEC 		( MSFPLAYER_PARAM_GET_BASE + 9 )
#define MSFPLAYER_PARAM_QUERY_END_OF_STREAM	( MSFPLAYER_PARAM_GET_BASE + 10 )
#define MSFPLAYER_PARAM_GET_TIMED_TEXT 		( MSFPLAYER_PARAM_GET_BASE + 11 )
#define MSFPLAYER_PARAM_GET_LINK_DATA			( MSFPLAYER_PARAM_GET_BASE + 12 )
#define MSFPLAYER_PARAM_GET_KEY_LINK_DATA 	( MSFPLAYER_PARAM_GET_BASE + 13 )
#define MSFPLAYER_PARAM_GET_EXT_RTSP_PARM 	( MSFPLAYER_PARAM_GET_BASE + 14 )
#define MSFPLAYER_PARAM_GET_EXT_RTSP_LINK_URL	( MSFPLAYER_PARAM_GET_BASE + 15 )
#define MSFPLAYER_PARAM_CHECK_FILE				( MSFPLAYER_PARAM_GET_BASE + 16 )
#define MSFPLAYER_PARAM_GET_API_TYPE				( MSFPLAYER_PARAM_GET_BASE + 17 )
#define MSFPLAYER_PARAM_GET_OSD_BUFFER 		( MSFPLAYER_PARAM_GET_BASE + 18 )
#define MSFPLAYER_PARAM_GET_DISP_BUFFER			( MSFPLAYER_PARAM_GET_BASE + 19 )
#define MSFPLAYER_PARAM_GET_DSP_TYPE			( MSFPLAYER_PARAM_GET_BASE + 20 )

//#define MSFPLAYER_PARAM_GET_CALLERID			MSFPLAYER_PARAM_CALLERID 	--> Common paramÀž·Î ÅëÇÕ

// [WISEonUTA] ygsong 080114 : added PARAM_GET
#define MSFPLAYER_PARAM_GET_STATUS				( MSFPLAYER_PARAM_GET_BASE + 22 ) //LGMM_PARAM_GETSTATUS
#define MSFPLAYER_PARAM_GET_STREAM_MEDIA_SPEC	( MSFPLAYER_PARAM_GET_BASE + 23 ) //LGMM_PARAM_GET_STREAM_MEDIA_SPEC
#define MSFPLAYER_PARAM_GET_BGM_STATE			( MSFPLAYER_PARAM_GET_BASE + 24 ) //LGMM_PARAM_BGM_STATE
#define MSFPLAYER_PARAM_IS_AVAILABLEPROGRESSIVE	( MSFPLAYER_PARAM_GET_BASE + 25 ) //LGMM_PARAM_ISAVAILABLEPROGRESSIVE
#define MSFPLAYER_PARAM_GET_FRAME_RATE			( MSFPLAYER_PARAM_GET_BASE + 26 ) //LGMM_PARAM_FRAME_RATE
#define MSFPLAYER_PARAM_CHECK_VIDEO_SPEC		( MSFPLAYER_PARAM_GET_BASE + 27 ) //LGMM_PARAM_CHECK_VIDEO_SPEC
#define MSFPLAYER_PARAM_IS_SVGZ					( MSFPLAYER_PARAM_GET_BASE + 28 ) //LGMM_PARAM_ISSVGZ
#define MSFPLAYER_PARAM_GET_OP_MCC				( MSFPLAYER_PARAM_GET_BASE + 29 ) //LGMM_PARAM_OP_MCC
#define MSFPLAYER_PARAM_IS_RT_STREAMING			( MSFPLAYER_PARAM_GET_BASE + 30 ) //LGMM_PARAM_IS_RT_STREAMING
#define MSFPLAYER_PARAM_IS_OPENED				( MSFPLAYER_PARAM_GET_BASE + 33 )	//ygsong 080610: 2œÇ žðµš ¿äÃ»Àž·Î Ãß°¡
#define MSFPLAYER_PARAM_GET_PLAYER_TYPE			( MSFPLAYER_PARAM_GET_BASE + 32 )
#define MSFPLAYER_PARAM_GET_ERROR_CODE			( MSFPLAYER_PARAM_GET_BASE + 34 )
#define MSFPLAYER_PARAM_GET_SESSION_NAME 		( MSFPLAYER_PARAM_GET_BASE + 35 )		//VideoStreaming
#define MSFPLAYER_PARAM_IS_SEEKING			    ( MSFPLAYER_PARAM_GET_BASE + 36 )//donghyub 110303 seeking check



#define __decl __attribute__((used)) static

#ifndef __cplusplus
extern "C" {

#endif


__decl MSF_RESULT (*MSOEM_Player_Init)( T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam) =
        (int(*)(T_MSF_CSTR, T_MSFPLAYER_INIT*))(0x4715DEFC+1);

__decl MSF_RESULT (*MSOEM_Player_Start)( uint32_t  nStartPos) =
        (int(*)(uint32_t))(0x4715DFE4+1);
//__decl MSF_RESULT (*MSOEM_Player_Play)( T_MSF_CSTR pFile, int32_t nStartPosMS) = (void*)0x4715E16A+1;
__decl MSF_RESULT (*MSOEM_Player_Stop)(void) = (int(*)(void))(0x4715E21A+1);
__decl MSF_RESULT (*MSOEM_Player_Close)(void) = (int(*)(void))(0x4715E2DC+1);

__decl MSF_RESULT (*MSOEM_Player_Pause)(char bRelease) = (int(*)(char))(0x4715E374+1);
__decl MSF_RESULT (*MSOEM_Player_Resume)(char bRestore) = (int(*)(char))(0x4715E374+1);

__decl MSF_RESULT (*MSOEM_Player_Seek)( E_MSFPLAYER_SEEKMODE eSeekMode, int32_t nSeekTime) =
        (int(*)(E_MSFPLAYER_SEEKMODE, int32_t))(0x4715E374+1);

__decl MSF_RESULT (*MSOEM_Player_StartRecord)( T_MSFPLAYER_RECORD_INFO* pstRecInfo ) =
        (int(*)(T_MSFPLAYER_RECORD_INFO*))(0x4715E86A+1);
__decl MSF_RESULT (*MSOEM_Player_StopRecord)( char bAbort ) =
        (int(*)(char))( 0x4715E88E +1 );



__decl MSF_RESULT (*MSOEM_Player_GetParam)( int32_t nParmID, int32_t* p1, int32_t* p2 ) =
        (int(*)(int32_t, int32_t *, int32_t *))(0x47160AB2+1);
__decl MSF_RESULT (*MSOEM_Player_SetParam)( int32_t nParmID, int32_t p1, int32_t p2) =
        (int(*)(int32_t, int32_t, int32_t))(0x471605F2+1);

__decl MSF_RESULT (*MSOEM_Player_GetMetaData)(T_MSF_CSTR pFileName,  T_MSFPLAYER_INIT  *pstInitParam,
                        T_MSFPLAYER_META_INFO *pstMetaInfo) =
        (int(*)(T_MSF_CSTR, T_MSFPLAYER_INIT*, T_MSFPLAYER_META_INFO*))(0x4715FE4C+1);

__decl MSF_RESULT (*MSOEM_Player_GetMediaSpec)(T_MSF_CSTR pFileName, T_MSFPLAYER_INIT *pstInitParam,
                            T_MSFPLAYER_MEDIA_SPEC *pstMediaSpec, T_MSF_BOOL bForced) =
        (int (*)(T_MSF_CSTR, T_MSFPLAYER_INIT*, T_MSFPLAYER_MEDIA_SPEC*, T_MSF_BOOL))(0x4715EFCA+1);





#ifndef __cplusplus
}
#endif

#endif
