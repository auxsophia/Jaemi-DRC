#include "CommonDefinition.h"


// This is the definition file

#define	ACC_R_OFFSET	(1995+55)//2186
#define	ACC_P_OFFSET	(2120-200)//2233
#define ACC_R_GAIN		0.014285//0.02727		//deg/digit
#define ACC_P_GAIN		0.014285//0.02651		//deg/digit
#define RF_TILT_R_OFFSET	0
#define RF_TILT_P_OFFSET	0
#define LF_TILT_R_OFFSET	0
#define LF_TILT_P_OFFSET	0

#define	M_GYRO_VEL_CutOff	8//10//15//10	//15	//20		// rad/sec
#define	M_GYRO_THETA_CutOff	1		// Hz
#define	IMU_CUT_OFF			0.03//	0.015//0.02//0.01:is so good.
#define	IMU_CUT_OFF1		0.05//	0.015//0.02//0.01:is so good.
#define	IMU_CUT_OFF2		0.04//	0.015//0.02//0.01:is so good.
#define GYRO_YAW_COF	5
#define FOOT_ACC_COF	4
#define FOOT_ACC_COF1	3
#define FOOT_ACC_COF1	3
#define LFOOT_ACC_COF1	2//3
#define RFOOT_ACC_COF1	2//3
#define FOOT_ACC_HPF_COF	0.1		// HPF cut-off freq.
#define FOOT_VEL_LPF_COF	0.5		// LPF cut-off freq. 

// calibration coeff. for tilt sensor
#define COFF_RF_TILT_P		26.5//38.0
#define COFF_RF_TILT_R		30.8//39.0
#define COFF_LF_TILT_P		33.1//50.2
#define COFF_LF_TILT_R		38.0//32.8
#define SWAY_Y_ADJUST	(-0.1)


// control parameter
#define	ANKLE_GAIN_LR		0.8//1.0//1.0
#define	ANKLE_GAIN_LP		0.8//1.0//1.0 
#define	ANKLE_GAIN_RR		0.8//1.0//1.0 
#define	ANKLE_GAIN_RP		0.8//1.0//1.0
#define	AnkleRollControlGain	0.15//0.20//0.15//0.10//0.15//0.20//0.15//0.12//0.2//0.15
#define	AnklePitchControlGain	0.15//0.20//0.15//0.20//0.2//0.15
#define LANDORIEN_L		1.5//2.0	//1.5
#define LANDORIEN_R		1.5//2.0	//1.5
#define LANDORIEN_PL	-0.4//-0.8//-1.0//-1.5//-2.0	//-1.6
#define LANDORIEN_PR	-0.4//-0.8//-1.0//-1.5//-2.0	//-1.6
#define	VIB_GAIN_RR			0.3//1.0//0.2 //1.0		0.3 : good for notch+lead compensator
#define	VIB_GAIN_LR			0.3//1.0//0.2 //1.0 
#define	VIB_GAIN_RY			0.5//1.0
#define	VIB_GAIN_LY			0.5//1.0
#define	COF_Heel_Landing	1//2
#define	FOOT_REAR			81
#define	FOOT_FRONT			81
#define	FT_COND1			200//400 //294		// criterion for ankle control or landing orientation control
#define ZMP_LP_CUTOFF	5//4	//Hz
#define AnkleControlCutOff	4	//Hz
#define AnkleControlCutOffPitch		6	//Hz
#define ZMP_LP_COF			5	//Hz
#define ZMP_REFY			70	//86
#define SSP_ZMP_GAIN_X		1.0
#define SSP_ZMP_GAIN_Y		1.0 

#define FOOTHEIGHT_START	25	//70 //30
#define FOOTHEIGHT_STEADY	40//60	//100 //50
#define ZeroStrideArmShake	5
#define InitTime_AnkleControl	10	// starting time for ankle contorl ref
#define	DSP_CONDITION		250
#define	UpperMotionRecovertime	300.0	

// kirk variable
#define GAIN_CURVE		0.5
#define ANK_PITCH_ANG   0//5       // 걸음시 발꿈치 각도(down)
#define ANK_PITCH_ANG_UP   10//17//13       // 걸음시 발꿈치 각도(up)
#define ANK_PITCH_ANG_UP2   15   //13       // 걸음시 발꿈치 각도(up) 계단오르기
#define ANK_PITCH_ANG_UP3   13   //14       // 걸음시 발꿈치 각도(dn) 계단내리기
#define ANK_PITCH_ANG_DN   0       // 걸음시 발꿈치 각도(down) 계단오르기
//#define PIT_SUP_ANG_0   0.8    // 걸음시 발을 내딪을때 Dive 현상을 억제하기위한 지지발의 발목각도 보상양
#define PIT_SUP_ANG_1   0       // 걸음시 발을 내딪을때 Dive 현상을 억제하기위한 내딪은발의 발목각도 보상양
#define DAMP_GAIN_R		1.0 //1.2
#define DAMP_GAIN_P		0.6 //1.8
#define LHIP_VIB_GAIN	0.012//0.008//0.01//0.008 
#define RHIP_VIB_GAIN	0.015//0.012//0.025//0.02 
#define UpBody_Tilt_LRHP	0.4//0.5
#define WRIST_FT_FZ_COF		2//4
#define WRIST_FT_M_COF		2//4
#define START_KICK_AMP		6//4
#define AvgZMPAmp			70//70
#define DelMovCoff			1.0//1.0

//#define FING1_A	100
//#define FING1_B	-100
//#define FING2_A	105
//#define FING2_B -105

//Safe finger amplitudes
#define FING1_A	80
#define FING1_B	-80
#define FING2_A	90//85
#define FING2_B -90//-85

