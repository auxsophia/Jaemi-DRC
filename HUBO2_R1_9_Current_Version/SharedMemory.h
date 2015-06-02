#include "CommonDefinition.h"

typedef struct _SHARED_DATA_
{
	BOOL	bExitFlag;
	
	// CAN Message를 주고 받을때 사용되는 변수
	// 보내고자 하는 데이터를 아래의 변수에 할당 한 후 사용.
	BOOL				Tx_Flag;
	BOOL				Tx1_Flag;
	BOOL				Rx_Flag;
	BOOL				INT_Flag;
	unsigned short		Tx_ID;
	unsigned char		Tx_Data[8];
	unsigned char		Tx_DLC;
	unsigned short		Tx1_ID;
	unsigned char		Tx1_Data[8];
	unsigned char		Tx1_DLC;
	unsigned char		Rx_Data[352][8];		// MBSIZE와 같은 값을 사용할 것

	// Flag variable
	BOOL			GYRO_RESET;
	BOOL			StartReadTheta;
	BOOL			FootAccReset;

	BOOL			Read_Enc_Flag;
	BOOL			Read_FTS_Flag;
	BOOL			Read_TILT_Flag;
	BOOL			POS_CTRL_Flag;
	BOOL			Ini_ZMP_Zero_Flag;
	BOOL			CUT_OFF;
	BOOL			Move_Flag[TOTAL_MTR_NUM];
	BOOL			DataSaveFlag;
	
	BOOL			TestModeFlag;
	char			MOTION_Stop;
	char			MotionFlagALL;
	BOOL			Arm_Motion;
	BOOL			ZMPSysIDFlag;
	BOOL			Walk_Ready_Flag;
	BOOL			Home_Flag;
	BOOL			Walk01Test_Flag;
	BOOL			DSP_Pose_Set_Flag;
	BOOL			DSP_Pose_Reset_Flag;
	BOOL			DSP_Pose_CTRL_Off_Flag;
	BOOL			DSP_Pose_CTRL_On_Flag;
	BOOL			SSP_Pose_Set_Flag;
	BOOL			SSP_Pose_Reset_Flag;
	BOOL			SSP_Pose_CTRL_Off_Flag;
	BOOL			SSP_Pose_CTRL_On_Flag;
	BOOL			SSP_OL_L_Pose_Flag;
	BOOL			SSP_OL_R_Pose_Flag;
	BOOL			SSP_Tick_Roll_Save_Flag;
	BOOL			SSP_Tick_Pitch_Save_Flag;
	BOOL			SSP_OL_Save_Flag;
	BOOL			SSPCTRLOn;
	BOOL			SSPCTRLOff;
	BOOL			TorsoCTRLOnOff;
	BOOL			ZMP_Zero_Set_Flag;
	BOOL			RollAnkleTestFlag;
	BOOL			RollAnkleTestStopFlag;
	BOOL			PitchAnkleTestFlag;
	BOOL			PitchAnkleTestStopFlag;
	BOOL			WalkingExp00_Flag;
	BOOL			GoStop_Flag;
	BOOL			SET_Flag;
	BOOL			KeepGoing;
	BOOL			SwayAdjToggle;
	BOOL			MotionFlag[NumOfMotions];
	BOOL			Foot_Displacement_Flag;
	BOOL			EncFlag;
	BOOL			HipYawVibFlag;
	BOOL			InitialPositionSettingFlag;
	BOOL			LoadParameterFlag;

	long			Offset_Pulse[TOTAL_MTR_NUM];
	long			Offset_Rev[TOTAL_MTR_NUM];
	long			Limit_Rev[TOTAL_MTR_NUM];
	float			PPR[TOTAL_MTR_NUM];
	float			PLUS_MTR_DIR[TOTAL_MTR_NUM];
	long			Kp0[TOTAL_MTR_NUM];
	long			Kp1[TOTAL_MTR_NUM];
	long			Kd0[TOTAL_MTR_NUM];
	long			Kd1[TOTAL_MTR_NUM];
	long			Ki0[TOTAL_MTR_NUM];
	long			Ki1[TOTAL_MTR_NUM];
	long			Z_Ref[TOTAL_MTR_NUM];
	float			temp[12];
	
				
	int				MotionLength[NumOfMotions];
	
	unsigned long	PROFTime[NumTimer];
	unsigned long	RTX_Index;
	unsigned long	Move_CNT[TOTAL_MTR_NUM];
	unsigned long	Tfinal[TOTAL_MTR_NUM];
	
	float			Realtheta[TOTAL_MTR_NUM];
	float			theta[TOTAL_MTR_NUM];
	float			Oldtheta[TOTAL_MTR_NUM];
	float			Deltheta[TOTAL_MTR_NUM];
	float			Reftheta[TOTAL_MTR_NUM];
	float			XYZreal[12];
	float			XYZDelta[12];
	float			XYZref[12];
	float			RefVel[TOTAL_MTR_NUM];
	float			UpBody_MTN_CAP_Data[24000][NumOfMotionJoint];

	float			fProfXYZ[12];
	float			LeftAnkPos[3];
	float			RightAnkPos[3];

	float			DistLftRht;
	float			DistFwdBwd;
	float			AngTurn;
	char			DirButton[3];
	float			OFFSETAdj[3];

	float			SWAYcompen;

	int				ShakeHandsFlag;	

	// Sensor variable
	int				RFOOT_Mx;
	int				RFOOT_My;
	int				RFOOT_Fz;
	int				LFOOT_Mx;
	int				LFOOT_My;
	int				LFOOT_Fz;
	int				RWRIST_Mx;
	int				RWRIST_My;
	int				RWRIST_Fz;
	int				LWRIST_Mx;
	int				LWRIST_My;
	int				LWRIST_Fz;

	float			NM_RFOOT_Mx;
	float			NM_RFOOT_My;
	float			N_RFOOT_Fz;
    float			NM_LFOOT_Mx;
	float			NM_LFOOT_My;
	float			N_LFOOT_Fz;
	float			NM_RWRIST_Mx;
	float			NM_RWRIST_My;
	float			N_RWRIST_Fz;
    float			NM_LWRIST_Mx;
	float			NM_LWRIST_My;
	float			N_LWRIST_Fz;

	float			Xzmp;
	float			Yzmp;

	float			RXzmp;
	float			RYzmp;
	
	float			LXzmp;
	float			LYzmp;
	
	
	int				ACC_R;
	int				ACC_P;
	
	int				GYRO_R;
	int				GYRO_P;
	int				GYRO_Y;
	
	int				RF_INCL_R;
	int				RF_INCL_P;
	int				LF_INCL_R;
	int				LF_INCL_P;
	
	int				RF_Tilt_R_Offset;
	int				RF_Tilt_P_Offset;
	int				LF_Tilt_R_Offset;
	int				LF_Tilt_P_Offset;

	float			M_Theta_R;
	float			M_Theta_P;
	float			M_Vel_R;
	float			M_Vel_P;

	float			New_Theta_R;
	float			New_Theta_P;
	float			New_Vel_R;
	float			New_Vel_P;

	float			Incl_P;
	float			Incl_R;

	float			LF_TILT_R;
	float			LF_TILT_P;
	float			RF_TILT_R;
	float			RF_TILT_P;
	
	float			Compen_Theta_R;
	float			Compen_Theta_P;

	int				Incl_Roll_Offset;
	int				Incl_Pitch_Offset;

	/// variables relted to control
	float			VibGainR;
	float			VibGainY;

	float			ZMPInitAdjust[3];
	float			ZMPSysID[3];
	unsigned int	NumShake;
	//float			ZMPYOveral;
	//float			ZMPXOveral;

	float			WalkSway;
	float			OLAnkComp;

	float			tp_WalkSway;
	float			tp_OLAnkComp;

	float			PushUpAMP;
	float			PushUpHz;
	BOOL			PushUpFlag;

	float			WristAmp;
	float			WristHz;
	int				WristMotionFlag;
	int				WristMotionMode;
	int				WristConfigureFlag;

	float			ShoulderPitchAmp;
	float			ShoulderRollAmp;
	float			ElbowAmp;
	float			ShoulderPitchHz;
	float			ShoulderRollHz;
	int				ShoulderMotionFlag;
	
	int				HandMotionFlag;
	float			HandAmp;
	float			HandFreq;

	unsigned int	SHWalkingPeriod;
	unsigned int	SHnewWalkingPeriod;

	float			YSway_Factor;
	float			Y_ShapeFactor;
	float			Y_ShapeFactorOpen;
	float			Y_ShapeFactorRecover;
	float			X_ShapeFactor;
	float			X_ShapeFactor_mod;
	float			X_mod;
	float			ZMPref_AMP[2];

	float			TorsoCTRLGainR[2];
	float			TorsoCTRLGainP[2];

	float			Zmp_Zero_Offset;
	
	
	long			ENC_POS[47][2];
	long			Ex_ENC_POS[TOTAL_EJMC_NUM][5];

	float			AnkleAmplitude;
	float			AnkleFreq;

	float			DelAnkleRoll[2]; // "0" Left, "1" Right
	float			InitAnkleRoll[2];// "0" Left, "1" Right

	float			RHipRollCompenMag;
	float			LHipRollCompenMag;

	float			RollVibGainFactor;
	float			RollOrienGainFactor;

	float			UPRATIO;
	float			UpRightPoseOffset;
	
	float			SwayDelayOpen;
	float			SwayDelayRecover;
	
	int				DSP_During;
	float			DSP_SideAmplitude;
	float			DSP_SwayAmplitude;

	float			Acc_Roll_Offset_Ini;
	float			Acc_Pitch_Offset_Ini;
	
	float			pHipMoveRatio;
	float			HipPitchAngle;
	float			FootPlacementGain;
	float			Roll_Ref_Gain;
	float			Pitch_Ref_Gain;
	float			Pos_Pitch_Ref;
	float			Pos_Roll_Ref;
	float			Hip_test0[2];
	float			Hip_test3[2];
	float			Hip_test5_a[2];

	int				AnkleControlFlag[2];
	float			tp_coff0[7];
	float			tp_coff1[7];
	
	int				ZMP_DSP_CTRL_Flag;
	float			ZMP_DSP_X_Gain;
	float			ZMP_DSP_Y_Gain;
	float			ZMP_DSP_Y_IntegralGain;
	BOOL			DSP_ZMP_Recover_Flag;
	float			StartInitVelCoff;
	float			ZMPAddCoff;
	float			Delta_Foot_Position[6];	// Initial delta foot position
	float			AvgXZmp[2];
	float			AvgYZmp[2];
	float			AvgRoll[2];
	float			AvgPitch[2];
	float			AvgGyroRoll[2];
	float			AvgGyroPitch[2];
	float			TotalAvgXZmp[2];
	float			TotalAvgYZmp[2];
	float			TotalAvgRoll[2];
	float			TotalAvgPitch[2];
	float			TotalAvgGyroRoll[2];
	float			TotalAvgGyroPitch[2];
	float			LandingPitchGain;
	float			LandingRollGain;
	float			X_ShapeFactorGain;
	float			ToeOffGain;
	float			AnkleRollGain;
	float			temp_data[10];
	
	int				SearchBoardNo;
	int				Motor_State[TOTAL_MTR_NUM];

	// kirk variable
	BOOL	Kirk_WalkingFlag;
	unsigned long	Int_CNT;
	unsigned char Mark_Time_Flag;
	unsigned char Walking_Stop_Flag;
	unsigned char Walking_Stop_Flag_2;
	unsigned char Walk_FWD_Flag;
	unsigned char Walk_BWD_Flag;
	unsigned char FWD_Turning_Flag_1_LT;
	unsigned char FWD_Turning_Flag_2_LT;
	unsigned char FWD_Turning_Flag_1_RT;
	unsigned char FWD_Turning_Flag_2_RT;
	unsigned char Gesture_Flag;
	unsigned char Walking_Test_Flag;
	unsigned char Walking_Gesture_Flag;
	unsigned char Walk_R_Side_Flag;
	unsigned char Walk_L_Side_Flag;
	unsigned char Walk_CW_Turn_Flag;
	unsigned char Walk_CCW_Turn_Flag;
	unsigned char FSM;      // Fitst Step Mode  -> 0:  Left Foot Starting  ,  1: Right Foot Starting
	int Motion_State;  // 0 : Marking, 1 : FWD Walking, -1 : BWD Walking, 2 : R-Side Walking, 3 : L-Side Walking, 4 : CW Turning, 5 : CCW Turning, 6 : Stop, 7 : UP, 8 : DN
	unsigned long Path_Area_CNT;
	float dsp_ratio;
	unsigned int Up_time;
	unsigned int Upstart_time;
	unsigned int Peak_time;
	unsigned int Delay_time;
	unsigned int Step_time;
	float Walk_Foot_Zdir_Amp;
	float Walk_BC_Ydir_Amp;
	float Amp_ankleR;
	float Amp_ankleL;
	float Step_Length;
	float Side_Step_Length;
	float FWD_Turning_Angle;
	float PIT_SUP_ANG_0;
	float Turning_Angle;
	float Equi_Adj_Rfoot_Z;
	float Equi_Adj_Lfoot_Z;
	float Gain_LO_Con_p;
	float Gain_LO_Con_r;

	float BC_x;
	float BC_y;
	float BC_z;
	float R_px;
	float R_py;
	float R_pz;
	float L_px;
	float L_py;
	float L_pz;

	float	gain_temp1;
	float	gain_temp2;
	float	amp_temp1;
	float	Plus_Yzmp_avg;
	float	Minus_Yzmp_avg;
	unsigned char SSP_CTRL_MODE;	// 1:damping, 2:posture
	unsigned char Demo_4_Flag;		// DSP control
	unsigned char Demo_4_Off_Flag;
	unsigned char Demo_5_Flag;		// SSP control flag
	unsigned char Demo_5_Off_Flag;
	unsigned char Demo_6_Flag;		// SSP maintain balance
	unsigned int  Test_CNT_0;			// Local Counter 0
	unsigned int  Test_CNT_1;			//local Counter 1
	unsigned int  Test_CNT_2;			//local Counter 2
	unsigned char DSPS_Con_Flag;
	unsigned char SSPS_Con_Flag;
	
	float			SaveData[SaveData_ROW][SaveData_COL];
	int JaemiSaysMotionSpeed; 	//0=slow 1=medium 2 = fast

	//Data for Rob's scripting engine
	int ScriptLoaded;
	int CurrentScript;
	int ScriptIndex;
	
} SHARED_DATA, *PSHARED_DATA;