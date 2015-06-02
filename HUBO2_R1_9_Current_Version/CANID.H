
// This file contains 'CAN-ID' for HUBO2

// 메인 컨트롤러에서(PC) 서브 컨트롤러 및 센서에게 CAN 메세지를 보낼 때 사용되는 CAN ID 및 기본 주소
#define CMD_TXDF				0x01
#define SEND_SENSOR_TXDF		0x02

#define REF_BASE_TXDF			0x10

// 서브 컨트롤러에서 메인 컨트롤러에게(PC) 데이터를 보낼 때 사용되는 CAN ID의 기본 주소
#define ENC_BASE_RXDF			0x60
#define CUR_BASE_RXDF			0x90
#define PM_BASE_RXDF			0x120

// 센서에서 메인 컨트롤러에게(PC) 데이터를 보낼 때 사용되는 CAN ID의 기본 주소
#define SENSOR_FT_BASE_RXDF		0x40
#define SENSOR_AD_BASE_RXDF		0x50
#define DAOFFSET_BASE_RXDF		0x310
#define ADOFFSET_BASE_RXDF		0x320
#define OFFSET_BASE_RXDF		0x330

// 서브 컨트롤러 및 센서에서 메인 컨트롤러에게(PC) 데이터를 보낼 때 사용되는 CAN ID의 기본 주소
#define STAT_BASE_RXDF			0x150
#define NAME_BASE_RXDF			0x190

////////////////////////////////////////////////////////////////////////////////////////////////
// 중요!!                         중요!!                      중요!!                      중요!!
//
// 기본 주소는 프로그램 내에서 직접 사용되지 않으며 기본 주소를 기반으로 
// Offset을 주어 사용한다.
// 예를 들어 JMC3 서브 컨트롤러에게 위치 레퍼런스를 보낼 경우
// REF_BASE_TXDF + 0x03 = REF3_TXDT 와 같이 사용된다.
// 따라서 'REF_BASE_TXDF+0x03'를 직접사용하지 않고 REF3_TXDF를 정의하여 사용한다.
// 참고로 JMC의 번호는 컨트롤러의 딥스위치를 이용하여 결정한다.
// 센서의 경우는 딥스위치가 없기 때문에 프로그램할 때 정의하여야 한다.
//
////////////////////////////////////////////////////////////////////////////////////////////////

// For JMC0 sub-controller
// Right Hip Yaw-Roll
#define JMC0					0x00
#define REF0_TXDF				REF_BASE_TXDF+JMC0
#define ENC0_RXDF				ENC_BASE_RXDF+JMC0
#define CUR0_RXDF				CUR_BASE_RXDF+JMC0
#define PM0_RXDF				PM_BASE_RXDF+JMC0
#define STAT0_RXDF				STAT_BASE_RXDF+JMC0
#define NAME0_RXDF				NAME_BASE_RXDF+JMC0
#define KP0						0x10
#define KI0						0x10
#define KD0						0x10

// For JMC1 sub-controller
// Right Hip Pitch
#define JMC1					0x01
#define REF1_TXDF				REF_BASE_TXDF+JMC1
#define ENC1_RXDF				ENC_BASE_RXDF+JMC1
#define CUR1_RXDF				CUR_BASE_RXDF+JMC1
#define PM1_RXDF				PM_BASE_RXDF+JMC1
#define STAT1_RXDF				STAT_BASE_RXDF+JMC1
#define NAME1_RXDF				NAME_BASE_RXDF+JMC1
#define KP1						0x10
#define KI1						0x10
#define KD1						0x10

// For JMC2 sub-controller
// Right Knee Pitch
#define JMC2					0x02
#define REF2_TXDF				REF_BASE_TXDF+JMC2
#define ENC2_RXDF				ENC_BASE_RXDF+JMC2
#define CUR2_RXDF				CUR_BASE_RXDF+JMC2
#define PM2_RXDF				PM_BASE_RXDF+JMC2
#define STAT2_RXDF				STAT_BASE_RXDF+JMC2
#define NAME2_RXDF				NAME_BASE_RXDF+JMC2
#define KP2						0x10
#define KI2						0x10
#define KD2						0x10

// For JMC3 sub-controller
// Right Ankle Pitch-Roll
#define JMC3					0x03
#define REF3_TXDF				REF_BASE_TXDF+JMC3
#define ENC3_RXDF				ENC_BASE_RXDF+JMC3
#define CUR3_RXDF				CUR_BASE_RXDF+JMC3
#define PM3_RXDF				PM_BASE_RXDF+JMC3
#define STAT3_RXDF				STAT_BASE_RXDF+JMC3
#define NAME3_RXDF				NAME_BASE_RXDF+JMC3
#define KP3						0x10
#define KI3						0x10
#define KD3						0x10

// For JMC4 sub-controller
// Left Hip Yaw-Roll
#define JMC4					0x04
#define REF4_TXDF				REF_BASE_TXDF+JMC4
#define ENC4_RXDF				ENC_BASE_RXDF+JMC4
#define CUR4_RXDF				CUR_BASE_RXDF+JMC4
#define PM4_RXDF				PM_BASE_RXDF+JMC4
#define STAT4_RXDF				STAT_BASE_RXDF+JMC4
#define NAME4_RXDF				NAME_BASE_RXDF+JMC4
#define KP4						0x10
#define KI4						0x10
#define KD4						0x10

// For JMC5 sub-controller
// Left Hip Pitch
#define JMC5					0x05
#define REF5_TXDF				REF_BASE_TXDF+JMC5
#define ENC5_RXDF				ENC_BASE_RXDF+JMC5
#define CUR5_RXDF				CUR_BASE_RXDF+JMC5
#define PM5_RXDF				PM_BASE_RXDF+JMC5
#define STAT5_RXDF				STAT_BASE_RXDF+JMC5
#define NAME5_RXDF				NAME_BASE_RXDF+JMC5
#define KP5						0x10
#define KI5						0x10
#define KD5						0x10

// For JMC6 sub-controller
// Left Knee Pitch
#define JMC6					0x06
#define REF6_TXDF				REF_BASE_TXDF+JMC6
#define ENC6_RXDF				ENC_BASE_RXDF+JMC6
#define CUR6_RXDF				CUR_BASE_RXDF+JMC6
#define PM6_RXDF				PM_BASE_RXDF+JMC6
#define STAT6_RXDF				STAT_BASE_RXDF+JMC6
#define NAME6_RXDF				NAME_BASE_RXDF+JMC6
#define KP6						0x10
#define KI6						0x10
#define KD6						0x10

// For JMC7 sub-controller
// Left Ankle Pitch-Roll
#define JMC7					0x07
#define REF7_TXDF				REF_BASE_TXDF+JMC7
#define ENC7_RXDF				ENC_BASE_RXDF+JMC7
#define CUR7_RXDF				CUR_BASE_RXDF+JMC7
#define PM7_RXDF				PM_BASE_RXDF+JMC7
#define STAT7_RXDF				STAT_BASE_RXDF+JMC7
#define NAME7_RXDF				NAME_BASE_RXDF+JMC7
#define KP7						0x10
#define KI7						0x10
#define KD7						0x10

// For JMC8 sub-controller
// Right Shoulder Pitch & Roll
#define JMC8					0x08
#define REF8_TXDF				REF_BASE_TXDF+JMC8
#define ENC8_RXDF				ENC_BASE_RXDF+JMC8
#define CUR8_RXDF				CUR_BASE_RXDF+JMC8
#define PM8_RXDF				PM_BASE_RXDF+JMC8
#define STAT8_RXDF				STAT_BASE_RXDF+JMC8
#define NAME8_RXDF				NAME_BASE_RXDF+JMC8
#define KP8						0x10
#define KI8						0x10
#define KD8						0x10

// For JMC9 sub-controller
// Right Shoulder Yaw-Elbow
#define JMC9					0x09
#define REF9_TXDF				REF_BASE_TXDF+JMC9
#define ENC9_RXDF				ENC_BASE_RXDF+JMC9
#define CUR9_RXDF				CUR_BASE_RXDF+JMC9
#define PM9_RXDF				PM_BASE_RXDF+JMC9
#define STAT9_RXDF				STAT_BASE_RXDF+JMC9
#define NAME9_RXDF				NAME_BASE_RXDF+JMC9
#define KP9						0x10
#define KI9						0x10
#define KD9						0x10

// For JMC10 sub-controller
// Left Shoulder Pitch & Roll
#define JMC10					0x0A
#define REF10_TXDF				REF_BASE_TXDF+JMC10
#define ENC10_RXDF				ENC_BASE_RXDF+JMC10
#define CUR10_RXDF				CUR_BASE_RXDF+JMC10
#define PM10_RXDF				PM_BASE_RXDF+JMC10
#define STAT10_RXDF				STAT_BASE_RXDF+JMC10
#define NAME10_RXDF				NAME_BASE_RXDF+JMC10
#define KP10					0x10
#define KI10					0x10
#define KD10					0x10

// For JMC11 sub-controller
// Left Shoulder Yaw-Elbow
#define JMC11					0x0B
#define REF11_TXDF				REF_BASE_TXDF+JMC11
#define ENC11_RXDF				ENC_BASE_RXDF+JMC11
#define CUR11_RXDF				CUR_BASE_RXDF+JMC11
#define PM11_RXDF				PM_BASE_RXDF+JMC11
#define STAT11_RXDF				STAT_BASE_RXDF+JMC11
#define NAME11_RXDF				NAME_BASE_RXDF+JMC11
#define KP11					0x10
#define KI11					0x10
#define KD11					0x10


// For EJMC0 sub-controller
// Right Wrist
#define EJMC0					0x20
#define REF32_TXDF				REF_BASE_TXDF+EJMC0
#define ENC32_RXDF				ENC_BASE_RXDF+EJMC0
#define CUR32_RXDF				CUR_BASE_RXDF+EJMC0
#define PM32_RXDF				PM_BASE_RXDF+EJMC0
#define STAT32_RXDF				STAT_BASE_RXDF+EJMC0
#define NAME32_RXDF				NAME_BASE_RXDF+EJMC0
#define KP32					0x10
#define KI32					0x10
#define KD32					0x10

// For EJMC1 sub-controller
// Left Wrist
#define EJMC1					0x21
#define REF33_TXDF				REF_BASE_TXDF+EJMC1
#define ENC33_RXDF				ENC_BASE_RXDF+EJMC1
#define CUR33_RXDF				CUR_BASE_RXDF+EJMC1
#define PM33_RXDF				PM_BASE_RXDF+EJMC1
#define STAT33_RXDF				STAT_BASE_RXDF+EJMC1
#define NAME33_RXDF				NAME_BASE_RXDF+EJMC1
#define KP33					0x10
#define KI33					0x10
#define KD33					0x10

// For EJMC2 sub-controller
// Neck
#define EJMC2					0x22
#define REF34_TXDF				REF_BASE_TXDF+EJMC2
#define ENC34_RXDF				ENC_BASE_RXDF+EJMC2
#define CUR34_RXDF				CUR_BASE_RXDF+EJMC2
#define PM34_RXDF				PM_BASE_RXDF+EJMC2
#define STAT34_RXDF				STAT_BASE_RXDF+EJMC2
#define NAME34_RXDF				NAME_BASE_RXDF+EJMC2
#define KP34					0x10
#define KI34					0x10
#define KD34					0x10


// For EJMC3 sub-controller
// Waist
#define EJMC3					0x23	//0x23
#define REF35_TXDF				REF_BASE_TXDF+EJMC3
#define ENC35_RXDF				ENC_BASE_RXDF+EJMC3
#define CUR35_RXDF				CUR_BASE_RXDF+EJMC3
#define PM35_RXDF				PM_BASE_RXDF+EJMC3
#define STAT35_RXDF				STAT_BASE_RXDF+EJMC3
#define NAME35_RXDF				NAME_BASE_RXDF+EJMC3
#define KP35					0x10
#define KI35					0x10
#define KD35					0x10


// For EJMC4 sub-controller
// Right Finger
#define EJMC4					0x24
#define REF36_TXDF				REF_BASE_TXDF+EJMC4
#define ENC36_RXDF				ENC_BASE_RXDF+EJMC4
#define CUR36_RXDF				CUR_BASE_RXDF+EJMC4
#define PM36_RXDF				PM_BASE_RXDF+EJMC4
#define STAT36_RXDF				STAT_BASE_RXDF+EJMC4
#define NAME36_RXDF				NAME_BASE_RXDF+EJMC4
#define KP36					0x10
#define KI36					0x10
#define KD36					0x10

// For EJMC5 sub-controller
// Right Finger
#define EJMC5					0x25
#define REF37_TXDF				REF_BASE_TXDF+EJMC5
#define ENC37_RXDF				ENC_BASE_RXDF+EJMC5
#define CUR37_RXDF				CUR_BASE_RXDF+EJMC5
#define PM37_RXDF				PM_BASE_RXDF+EJMC5
#define STAT37_RXDF				STAT_BASE_RXDF+EJMC5
#define NAME37_RXDF				NAME_BASE_RXDF+EJMC5
#define KP37					0x10
#define KI37					0x10
#define KD37					0x10


// Sensors
// For FT1 sub-controller Right
#define FT1						0x30		// Board Number
#define SENSOR_RECEIVE1			0x01
#define SENSOR_FT1_RXDF			SENSOR_FT_BASE_RXDF+SENSOR_RECEIVE1
#define SENSOR_AD1_RXDF			SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE1
#define DAOFFSET1_RXDF			DAOFFSET_BASE_RXDF+SENSOR_RECEIVE1
#define ADOFFSET1_RXDF			ADOFFSET_BASE_RXDF+SENSOR_RECEIVE1
#define OFFSET1_RXDF			OFFSET_BASE_RXDF+SENSOR_RECEIVE1
#define STAT_FT1_RXDF			STAT_BASE_RXDF+FT1
#define NAME_FT1_RXDF			NAME_BASE_RXDF+FT1

// For FT2 sub-controller Left
#define FT2						0x31
#define SENSOR_RECEIVE2			0x02
#define SENSOR_FT2_RXDF			SENSOR_FT_BASE_RXDF+SENSOR_RECEIVE2
#define SENSOR_AD2_RXDF			SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE2
#define DAOFFSET2_RXDF			DAOFFSET_BASE_RXDF+SENSOR_RECEIVE2
#define ADOFFSET2_RXDF			ADOFFSET_BASE_RXDF+SENSOR_RECEIVE2
#define OFFSET2_RXDF			OFFSET_BASE_RXDF+SENSOR_RECEIVE2
#define STAT_FT2_RXDF			STAT_BASE_RXDF+FT2
#define NAME_FT2_RXDF			NAME_BASE_RXDF+FT2

// For IMU1 sub-controller
#define IMU1					0x32
#define SENSOR_RECEIVE3			0x03
#define SENSOR_IMU1_RXDF		SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE3
#define STAT_IMU1_RXDF			STAT_BASE_RXDF+IMU1
#define NAME_IMU1_RXDF			NAME_BASE_RXDF+IMU1

// For IMU2 sub-controller
#define IMU2					0x33
#define SENSOR_RECEIVE4			0x04
#define SENSOR_IMU2_RXDF		SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE4
#define STAT_IMU2_RXDF			STAT_BASE_RXDF+IMU2
#define NAME_IMU2_RXDF			NAME_BASE_RXDF+IMU2

// For IMU3 sub-controller
#define IMU3					0x34
#define SENSOR_RECEIVE5			0x05
#define SENSOR_IMU3_RXDF		SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE5
#define STAT_IMU3_RXDF			STAT_BASE_RXDF+IMU3
#define NAME_IMU3_RXDF			NAME_BASE_RXDF+IMU3

// For FT3 sub-controller Left for right wrist
#define FT3						0x35
#define SENSOR_RECEIVE6			0x06
#define SENSOR_FT3_RXDF			SENSOR_FT_BASE_RXDF+SENSOR_RECEIVE6
#define SENSOR_AD3_RXDF			SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE6
#define DAOFFSET3_RXDF			DAOFFSET_BASE_RXDF+SENSOR_RECEIVE6
#define ADOFFSET3_RXDF			ADOFFSET_BASE_RXDF+SENSOR_RECEIVE6
#define OFFSET3_RXDF			OFFSET_BASE_RXDF+SENSOR_RECEIVE6
#define STAT_FT3_RXDF			STAT_BASE_RXDF+FT3
#define NAME_FT3_RXDF			NAME_BASE_RXDF+FT3

// For FT4 sub-controller Left for right wrist
#define FT4						0x36
#define SENSOR_RECEIVE7			0x07
#define SENSOR_FT4_RXDF			SENSOR_FT_BASE_RXDF+SENSOR_RECEIVE7
#define SENSOR_AD4_RXDF			SENSOR_AD_BASE_RXDF+SENSOR_RECEIVE7
#define DAOFFSET4_RXDF			DAOFFSET_BASE_RXDF+SENSOR_RECEIVE7
#define ADOFFSET4_RXDF			ADOFFSET_BASE_RXDF+SENSOR_RECEIVE7
#define OFFSET4_RXDF			OFFSET_BASE_RXDF+SENSOR_RECEIVE7
#define STAT_FT4_RXDF			STAT_BASE_RXDF+FT4
#define NAME_FT4_RXDF			NAME_BASE_RXDF+FT4

// Command(Not CAN ID)
#define AllController			0x20		// 모든 컨트롤러에게 메세지를 전달 하고자 할때 사용. 이외에는 개별적인 모듈네임을 이용. 예)JMC0, FT1 등등
#define NameInfo				0x01		// 컨트롤러의 이름을 물어본다.
#define BoardStatus				0x02		// 컨트롤러의 상태를 물어본다.
#define SendEncoder				0x03		// 엔코더 값을 물어본다.
#define SendCurrent				0x04		// 전류값을 물어본다.
#define SendPM					0x05		// PM 값을 물어본다.
#define EncZero					0x06		// 엔코더 값을 영으로 설정한다.
#define SetPosGainA				0x07		// 모터제어기 첫번째 채널의 위치제어기 게인을 설정한다.
#define SetPosGainB				0x08		// 모터제어기 두번째 채널의 위치제어기 게인을 설정한다.
#define SetTorqueGainA			0x09		// 모터제어기 첫번째 채널의 토크제어기 게인을 설정한다.
#define SetTorqueGainB			0x0A		// 모터제어기 두번째 채널의 토크제어기 게인을 설정한다.
#define HipEnable				0x0B		// 힙을 활성화 시킨다.
#define GoHome					0x0C		// 'Home' 위치로 이동한다.
#define PwmCMD					0x0D		// 'PWM'을 내보낸다.
#define RunCMD					0x0E		// 작동을 명령한다.
#define StopCMD					0x0F		// 작동을 멈춘다.
#define ControlMode				0x10		// 위치제어 모드인지 전류제어 모드인지 설정한다.
#define GoLimitPos				0x11		// 리밋스위치 위치까지 이동한다.
#define TorqueLimit				0x12		// 전류 제어 모드일때 전류의 상한값을 설정한다.

#define NullCMD					0x81		// 센서를 널링한다.
#define SetPeriod				0x82		// 
#define SetSample				0x83		//
#define ADRead					0x84		//
#define DAOut					0x85		//
#define DataTypeCMD				0x86		//
#define DAOffsetCMD				0x87		//
#define ADOffsetCMD				0x88		//
#define OffsetCMD				0x89		//


					