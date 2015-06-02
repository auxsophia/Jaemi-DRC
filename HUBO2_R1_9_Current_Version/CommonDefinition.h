
// This file is using both project same.

#define	PI				3.14
#define rad2deg			(180./PI)
#define deg2rad			(PI/180.)
#define LEFT			0
#define RIGHT			1



#define		TOTAL_MTR_NUM   51	// 10ea is reserved
#define		TOTAL_JMC_NUM	12
#define		TOTAL_EJMC_NUM   6
#define		TOTAL_SEN_NUM   7//5	//4	//3
#define		TOTAL_BOARD_NUM	20

#define		NumTimer				30
#define		NumOfMotions			90		// dan change from 43
#define		NumOfMotionJoint		27

#define		SaveData_COL	80
#define		SaveData_ROW	10000

#define		RWY		0	// right wrist yaw
#define		RW1		1	// right wrist 1
#define		RW2		2	// right wrist 2
#define		LWY		3	// left wrist yaw
#define		LW1		4	// left wrist 1
#define		LW2		5	// left wrist 2
#define		NKY		6	// neck yaw
#define		NK1		7	// neck 1
#define		NK2		8	// neck 2
#define		RF1		9			//	Right Finger	엄지
#define		RF2		10			//	Right Finger	검지
#define		RF3		11			//	Right Finger	중지
#define		RF4		12			//	Right Finger	약지
#define		RF5		13			//	Right Finger	새끼
#define		LF1		14			//	Left Finger		엄지
#define		LF2		15			//	Left Finger		검지
#define		LF3		16			//	Left Finger		중지
#define		LF4		17			//	Left Finger		약지
#define		LF5		18			//	Left Finger		새끼



#define		RSP				30			//	Right Shoulder Pitch
#define		RSR				31			//	Right Shoulder Pitch
#define		RSY				32			//	Right Shoulder Roll
#define		REB				33			//	Right Elbow Pitch

#define		LSP				34			//	Left Shoulder Pitch
#define		LSR				35			//	Left Shoulder Yaw
#define		LSY				36			//	Left Shoulder Roll
#define		LEB				37			//	Left Elbow Pitch
#define		WST				38			//	Trunk Yaw

// motor no 19 ~ 29 is reserved

#define		RHY				39				//	Right Hip Yaw
#define		RHR				40				//	Right Hip Roll
#define		RHP				41				//	Right Hip Pitch
#define		RKN				42				//	Right Knee Pitch
#define		RAP				43				//	Right Ankle Pitch
#define		RAR				44				//	Right Ankle Roll

#define		LHY				45				//	Left Hip Yaw
#define		LHR				46				//	Left Hip Roll
#define		LHP				47				//	Left Hip Pitch
#define		LKN				48				//	Left Knee Pitch
#define		LAP				49				//	Left Ankle Pitch
#define		LAR				50				//	Left Ankle Roll

////// KHR-3 Parameters ///////
#define		L0				88.5	//(78.5)	//71
#define		L1				300
#define		L2				300
#define		WLK_RDY_DOWN	40	//10	//40 
#define		WLK_RDY_OFFSET	0
#define		MAX_STEP_NUM	500
#define		WLK_RDY_LRSY	10
#define		WLK_RDY_LRSP    20
#define		WLK_RDY_LREB	40
#define		WLKING_LRSP		8
#define		WLKING_LREB		8
#define		WLKING_WST		0
#define		WLKING_LRSY		5
//#define		DAMP_GAIN_R		1.5
//#define		DAMP_GAIN_P		1.5
#define		SH_HIP_ANG      10
///////////////////////////////

////// related to interrupt frequency
#define INT_TIME	10//5			// value for sending sub-board(msec)
#define	INT_TIME1	10			// 10msec for upper body
#define DELTA_T		(INT_TIME/1000.)		// 0.002 sec

#define TS				1//2		// Time scale for Interrupt 
								// original is TS = 1 for 10msec
								// TS = 5 for 2 msec
#define	SEC1			(200*TS)	// 2 sec for calculation gyro offset
/////////////

#define	ENC_FAIL		0x10
#define MOTOR_JAM		0x20
#define FOLLOWER_FAIL	0x40
