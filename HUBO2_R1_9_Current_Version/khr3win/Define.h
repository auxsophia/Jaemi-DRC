#include "..\CommonDefinition.h"

// Timer Frequency for Display
#define DISP_TIMER	100
/////////////////////////////////////////////////////////////////////////////////////
// button

//khr3winDlg
#define Enc_SHOW					1000
#define Enc_HIDE					1001
#define Enc_CLOSE					1002
#define Enc_CREATE					1003

#define CAN_ON						1100
#define CAN_OFF						1101
	
#define RTX_ON						1200
#define RTX_OFF						1201

#define FT_SHOW						1300
#define FT_HIDE						1301
#define FT_CLOSE					1302
#define FT_CREATE					1303

#define TILT_SHOW					1400
#define TILT_HIDE					1401
#define TILT_CLOSE					1402
#define TILT_CREATE					1403

#define TILT_CUTOFF_RESET			1404
#define TILT_STOP					1405
#define TILT_START					1406

#define TILT_GRAPH_ON				1407
#define TILT_GRAPH_HOLD				1408

#define OL_SHOW						1500
#define OL_HIDE						1501
#define OL_CLOSE					1503
#define OL_CREATE					1504

#define POS_SHOW					1600
#define POS_HIDE					1601
#define POS_CLOSE					1603
#define POS_CREATE					1604

#define WALK_SHOW					1700
#define WALK_HIDE					1701
#define WALK_CLOSE					1702
#define WALK_CREATE					1703
#define WALK_GRAPH_START			1704
#define WALK_GRAPH_HOLD				1705

#define WALKING_EXP_SHOW			1800
#define WALKING_EXP_HIDE			1801
#define WALKING_EXP_CLOSE			1802
#define WALKING_EXP_CREATE			1803
#define WALKING_EXP_GRAPH_START		1804
#define WALKING_EXP_GRAPH_HOLD		1805

#define KIRK_WALKING_EXP_SHOW			1900
#define KIRK_WALKING_EXP_HIDE			1901
#define KIRK_WALKING_EXP_CLOSE			1902
#define KIRK_WALKING_EXP_CREATE			1903
#define KIRK_WALKING_EXP_GRAPH_START	1904
#define KIRK_WALKING_EXP_GRAPH_HOLD		1905


//F/TReadDlg
#define FTDLG_FT_GRAPH_ON			2004
#define FTDLG_FT_GRAPH_HOLD			2005

// Parameters setting
#define PARAMETER_SETTING_SHOW		2100
#define	PARAMETER_SETTING_HIDE		2101
#define	PARAMETER_SETTING_CLOSE		2102
#define	PARAMETER_SETTING_CREATE	2103																				   

// Gain setting
#define GAIN_SETTING_SHOW			2200
#define GAIN_SETTING_HIDE			2201
#define GAIN_SETTING_CLOSE			2202
#define GAIN_SETTING_CREATE			2203

// Motor state
#define MOTOR_STATE_SHOW			2300
#define MOTOR_STATE_HIDE			2301
#define MOTOR_STATE_CLOSE			2302
#define MOTOR_STATE_CREATE			2303
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// CBoard CenterPoint

#define CENTERPOINT_MIDDLE			3000
#define CENTERPOINT_LEFTDOWN		3001
#define CENTERPOINT_LEFTTOP			3002
#define CENTERPOINT_LEFTMIDDLE		3003
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// Variable Type Definition
typedef  unsigned char     Byte;
typedef    signed char     sByte;
typedef  unsigned short    Word;
typedef    signed short    sWord;
typedef  unsigned long     LWord;
typedef    signed long     sLWord;
//
/////////////////////////////////////////////////////////////////////////////////////

#define SIZE   5000

#define		ENABLE			1
#define		DISABLE			0
#define		HIGH			1
#define		LOW				0
#define		BUSY			1
#define		IDLE			0
#define		CCW				1
#define		CW				0
		//***** Motor Values

typedef	struct _MOTOR_{
		sLWord	Ref[SIZE];		// Reference Command
		sLWord	OldRef;
		sLWord	CurrPos;			// Current Encoder Position
		
		Word	Current;			// Motor Current value
		Word	Pressure;			// Motor Pressure value
		float   CURRvol;       // Current in voltage
		
		Word	PM;				// Potentiometer value in digit
		float   PMvol;         // Potentiometer value in voltage
		
		Byte    EncoMul;			// Multiple of Encoder Logic (x1, x2, x4)
		Byte    PWMCarrier;	 	// PWM Carry Frequency
		float	PWMDuty;			// PWM Duty Cycle
		
		Word		KP;		 	   // P gain of Position controller
		Word		KI;		 	   // I gain
		Word		KD;		 	   // D gain
		
		Word		Home;			// Potentiometer value for Home Position
		Word		Upper;		 	// Potentiometer value for Upper Out-of-range
		Word		Lower;		 	// Potentiometer value for Lower Out-of-range
		
		Byte		Mn;			 	// Motor ID number
		char		Name[7];			// Name of motor
	} MOTOR;
	
//***** Status byte for each motor
typedef	volatile union {
	struct _mSTAT_ {
			unsigned    RXDAT:1;	 	// 1= Receving Reference Position/Current Data
			unsigned    :3;         // Not used
			unsigned 	OC:1;			// 1= Over current detected
			unsigned 	HP:1;			// 1= Home position detected
			unsigned 	OOR:1;		// 1= Out of range detected
			unsigned 	DIR:1;		// Motor Direction (1= CCW, 0= CW)
		} _BITS;
		unsigned char _BYTE;
	} mSTAT;

//***** Control byte for each motor
typedef volatile union {
   struct _mCTL_{
		unsigned    RUN:1;		// 1= Update Reference command
		unsigned    MAN:1;		// 1= Manual mode ON
		unsigned    HOME:1;	   // 1= Home positioning mode
		unsigned    FREE:1;	   // 1= Set Free Mode, 0= Disable Free Mode
		unsigned    CNTL:1;	   // 1= Current control mode, 0= Position control mode
		unsigned    DIS:1;		// 1= Enable HIP4081A, 0= Disable HIP4081A
     	unsigned    :1;         // Not used
     	unsigned 	STOP:1;		// 1= Stop motor (PWM duty = 0, Brake mode)
   } _BITS;
   unsigned char _BYTE;
} mCTL;

//***** Status byte of Joint Motor Controller
typedef volatile union {
	struct _jSTAT_{
    	unsigned 	TxEnco:1;	// 1= Transmitting Encoder data
     	unsigned 	TxPres:1;	// 1= Transmitting pressure data 
     	unsigned 	TxPM:1;		// 1= Transmitting Potentiometer data
     	unsigned 	PWM:1;		// 1= PWM Test mode
     	unsigned    :3;         // Not used
        unsigned    Ready:1;	   // 1= system Ready to start motion control
	} _BITS;
	unsigned char _BYTE;
} jSTAT;
		
