#include "Define.h"
/////////////////////////////////
// Added varibal by user from here.

//unsigned char	MotorPos[48][6];	// 48 --> 32:JMC, 16:EJMC
unsigned char	MotorPos[48][8];	// 48 --> 32:JMC, 16:EJMC
float 	PPR[TOTAL_MTR_NUM]; float PLUS_MTR_DIR[TOTAL_MTR_NUM];

unsigned int TIME_AVG00;


////// Shared Memory와 RTX간의 변수 이동용
unsigned char	RTX_Rx_Data[MBSIZE][8];

float	RTX_fREF[TOTAL_MTR_NUM];
float	RTX_fREFOLD[TOTAL_MTR_NUM];
float	RTX_fYaw[2];
float	RTX_fXYZ[12];

int		RTX_RFOOT_Mx0;	int		RTX_RFOOT_My0;	int		RTX_RFOOT_Fz0;
int		RTX_RFOOT_Mx;	int		RTX_RFOOT_My;	int		RTX_RFOOT_Fz;
int		RTX_LFOOT_Mx;	int		RTX_LFOOT_My;	int		RTX_LFOOT_Fz;
int		RTX_RWRIST_Mx;	int		RTX_RWRIST_My;	int		RTX_RWRIST_Fz;
int		RTX_LWRIST_Mx;	int		RTX_LWRIST_My;	int		RTX_LWRIST_Fz;

float	RTX_NM_RFOOT_Mx;  float	RTX_NM_RFOOT_My;  float	RTX_N_RFOOT_Fz;
float	RTX_NM_LFOOT_Mx;  float	RTX_NM_LFOOT_My;  float	RTX_N_LFOOT_Fz;
float	RTX_NM_RWRIST_Mx; float	RTX_NM_RWRIST_My; float	RTX_N_RWRIST_Fz;
float	RTX_NM_LWRIST_Mx; float	RTX_NM_LWRIST_My; float	RTX_N_LWRIST_Fz;

float	RTX_NM_RWRIST_Mx_old; float	RTX_NM_RWRIST_My_old; float	RTX_N_RWRIST_Fz_old;
float	RTX_NM_LWRIST_Mx_old; float	RTX_NM_LWRIST_My_old; float	RTX_N_LWRIST_Fz_old;

float	RTX_NM_RWRIST_Mx_LPF; float	RTX_NM_RWRIST_My_LPF; float	RTX_N_RWRIST_Fz_LPF;
float	RTX_NM_LWRIST_Mx_LPF; float	RTX_NM_LWRIST_My_LPF; float	RTX_N_LWRIST_Fz_LPF;



float	RTX_Xzmp;		  float	RTX_Yzmp;
float	RTX_RXzmp;		  float	RTX_RYzmp;
float	RTX_LXzmp;		  float	RTX_LYzmp;


float	Xzmp_lp, oldXzmp_lp;
float	Yzmp_lp, oldYzmp_lp;

float	RF_DC_MAT[3][3];
float	LF_DC_MAT[3][3];

int		RTX_ACC_R;
int		RTX_ACC_P;		

int		RTX_GYRO_R;		
int		RTX_GYRO_P;
int		RTX_GYRO_Y;

int		RTX_M_Theta_R;
int		RTX_M_Theta_Offset_R;
int		RTX_M_Vel_R;
int		RTX_M_Theta_P;
int		RTX_M_Theta_Offset_P;
int		RTX_M_Vel_P;

short int		RTX_New_Theta_R;
short int		RTX_New_Theta_Offset_R;
short int		RTX_New_Vel_R;
short int		RTX_New_Vel_Offset_R;
short int		RTX_New_Theta_P;
short int		RTX_New_Theta_Offset_P;
short int		RTX_New_Vel_P;
short int		RTX_New_Vel_Offset_P;

short int		RTX_New_Vel_R_old;
short int		RTX_New_Vel_P_old;

float	RTX_M_Tilt_Theta_R;
float	RTX_M_Tilt_Theta_ROLD;
float	RTX_M_Tilt_Vel_R;

float	RTX_M_Tilt_Theta_P;
float	RTX_M_Tilt_Theta_POLD;
float	RTX_M_Tilt_Vel_P;

float	RTX_M_Tilt_Theta_R_LPF;
float	RTX_M_Tilt_Theta_P_LPF;

float	RTX_M_Tilt_Thetaold_R;
float	RTX_M_Tilt_Thetaold_P;

float	RTX_M_Tilt_Velold_R;
float	RTX_M_Tilt_Vel_R_LPF;

float	RTX_M_Tilt_Velold_P;
float	RTX_M_Tilt_Vel_P_LPF;

float	RTX_New_Tilt_Theta_R;
float	RTX_New_Tilt_Theta_ROLD;
float	RTX_New_Tilt_Vel_R;
float	RTX_New_Tilt_Vel_ROLD;

float	RTX_New_Tilt_Theta_P;
float	RTX_New_Tilt_Theta_POLD;
float	RTX_New_Tilt_Vel_P;
float	RTX_New_Tilt_Vel_POLD;

int		Gyro_P_Offset; int		Gyro_R_Offset; int		Gyro_Y_Offset;

float	GyroR0;		// gyro - gyro_offset
float	GyroP0;
float	GyroY0;

float	GyroP_deg;
float	GyroR_deg;
float	GyroY_deg;

float	AccR_deg;
float	AccP_deg;

float	LPF_GYRO_Y1;
float	LPF_GYRO_Y1_OLD;

float	HPF_M_ThetaR; float HPF_M_ThetaR_old;
float	HPF_M_ThetaP; float HPF_M_ThetaP_old;

float	HPF_New_ThetaR; float HPF_New_ThetaR_old;
float	HPF_New_ThetaP; float HPF_New_ThetaP_old;

float	HPF2_New_ThetaR; float HPF2_New_ThetaR_old; float HPF2_New_ThetaR_old2;
float	HPF2_New_ThetaP; float HPF2_New_ThetaP_old; float HPF2_New_ThetaP_old2;

float	LPF_New_VelR; float LPF_New_VelR_old;
float	LPF_New_VelP; float LPF_New_VelP_old;

float	LPF_AccR; float LPF_AccR_old;
float	LPF_AccP; float LPF_AccP_old;

float	LPF_New_AccR; float LPF_New_AccR_old;
float	LPF_New_AccP; float LPF_New_AccP_old;

float	RTX_CompenTheta_R;
float	RTX_CompenTheta_P;

float	RTX_New_CompenTheta_R;
float	RTX_New_CompenTheta_P;

int		RTX_RF_INCL_R;			int		RTX_RF_INCL_P;			int		RTX_LF_INCL_R0;	int		RTX_LF_INCL_P0;
int		RTX_RF_Tilt_R_Offset;	int		RTX_RF_Tilt_P_Offset;
int		RTX_LF_Tilt_R_Offset;	int		RTX_LF_Tilt_P_Offset;

int		FootTilt[4];

float	RF_ACC_R_lp;  float	RF_ACC_P_lp;
float	LF_ACC_R_lp;  float	LF_ACC_P_lp;

float	RF_ACC_R_lp0;  float	RF_ACC_P_lp0;
float	LF_ACC_R_lp0;  float	LF_ACC_P_lp0;

float	RF_TILT_R;    float	RF_TILT_P;
float	LF_TILT_R;    float	LF_TILT_P;

float	RF_TILT_R_old;    float	RF_TILT_P_old;
float	LF_TILT_R_old;    float	LF_TILT_P_old;

float	RF_TILT_R_HPF;    float	RF_TILT_P_HPF;
float	LF_TILT_R_HPF;    float	LF_TILT_P_HPF;

float	RF_TILT_R_HPF_old;    float	RF_TILT_P_HPF_old;
float	LF_TILT_R_HPF_old;    float	LF_TILT_P_HPF_old;

float	RF_TILT_R_Vel;		float LF_TILT_R_Vel;
float	RF_TILT_R_Vel_old;	float LF_TILT_R_Vel_old;

float	RF_TILT_P_Vel;		float LF_TILT_P_Vel;
float	RF_TILT_P_Vel_old;	float LF_TILT_P_Vel_old;



// variable for walking pattern using stage & operation00
char	STATUS[2];
char	oldSTATUS[2];
char	Status[10];
char	oldStatus[10];

unsigned int	DURING1;
unsigned int	DURING2;
unsigned int	DURING3;

float	OP_DistLftRht[2];
float	OP_DistFwdBwd;
float	OP_DistFwdBwd1;
float	OP_DistFwdBwd1old;
float	OP_AngTurn;

float	DirDist[2][9];
float	RL_DirDist[2][9];
char	Button[3];

unsigned int NumStep;

float	RTXSWAYcompen1;
float	RTXSWAYcompen2;
float	RTXSWAYcompen3;

float	ZMPrefAdd[2];

BOOL	ZLandingCTRLFlag;
char	FiveKG_R_Flag; 
char	FiveKG_L_Flag;

char	LandLOK_Flag; 
char	LandROK_Flag;

float			Init_Heel_Angle[2];
float			Final_Heel_Angle[2];	
int				Heel_InitFlag[2];		// 
int				Heel_Timer[2];			// Timer for Heel ankle recover
float			tp_delta_Heel;


extern	float	v_CartPos2;
float	v_oldCartPos2;
float	v_delCartPos2;
extern	float	v_CartPos5;
float	v_oldCartPos5;
float	v_delCartPos5;

extern	float	v_CartPos2Last;
extern	float	v_CartPos5Last;

// variable for control
float	AddDiff;
float	RTX_HeightDiff[2];
float	AnkAdjust[2];

float	ZMPref[2];

float	RTX_BodyCenter[3];		// 0: X-Axis, 1: Y-Axis, 2: Z-Axis
float	RTX_DeltaMove[3];		// 0: X-Axis, 1: Y-Axis, 2: Z-Axis
float	RTX_DeltaMove0[3];		// 0: X-Axis, 1: Y-Axis, 2: Z-Axis	, 왼발 서기, 오른발 서기 동작
float   OL_y, OR_y, OL_x, OR_x;

float	RTX_R_AnkleP;
float	RTX_Adj_AnkleP;
float	RTX_CTRL_Ankle[4];

float	RTX_COMPEN_Ankle_Roll[2][3];	// 0:left, 1:right,		control by M-INF gyro feedback
float	RTX_COMPEN_Ankle_Pitch[2][3];	// 0:left, 1:right
float	RTX_oldCOMPEN_Ankle_Roll[2][3];
float	RTX_oldCOMPEN_Ankle_Pitch[2][3];
float	RTX_delCOMPEN_Ankle_Roll[2][3];
float	RTX_delCOMPEN_Ankle_Pitch[2][3];

float	RTX_COMPEN_Vib_Roll[2];		// 0:left, 1:right,	Vibration reduction
float	RTX_oldCOMPEN_Vib_Roll[2];
float	RTX_delCOMPEN_Vib_Roll[2];

float	RTX_COMPEN_Vib_Yaw[2];	// 0:left, 1:right
float	RTX_oldCOMPEN_Vib_Yaw[2];
float	RTX_delCOMPEN_Vib_Yaw[2];

float	INItemp[10];
int	RSteadyFlag;
int	LSteadyFlag;

float	InitialRoll[2];
float	InitialPitch[2];
float	temp_roll_ref[2];
float	temp_pitch_ref[2];
float	AnkleRollRef[2];
float	AnklePitchRef[2];

// double support zmp stabilization control variable
float	ZMP_DSP_Angle[2];
float	ZMP_DSP_Angle_old[2];
float	tp_ZMP_DSP_Angle[2];
float	DSP_ZMPRef[2];
BOOL	Read_ZMP_Flag;
float	Init_DSP_ZMP[2];
/////////////////////////////////////

float	InitDeltaFoot[6];

float	SumZMP[2][2]; //[]left,right, []x,y
float	AvgZMP[2][2];	//[]left,right, []x,y
float	BodyEstimateTimer[2];	//[]left,right
float	SumRoll[2];		//[]left,right
float	SumPitch[2];	//[]left,right
float	AvgRoll[2];		//
float	AvgPitch[2];
float	SumGyroRoll[2];
float	SumGyroPitch[2];
float	AvgGyroRoll[2];
float	AvgGyroPitch[2];
int		BodyEstimateUpdateFlag[2];//	[]left,right

float	TotalSumZMP[2][2]; //[]left,right, []x,y
float	TotalAvgZMP[2][2];	//[]left,right, []x,y
float	TotalBodyEstimateTimer[2];	//[]left,right
float	TotalSumRoll[2];		//[]left,right
float	TotalSumPitch[2];	//[]left,right
float	TotalAvgRoll[2];		//
float	TotalAvgPitch[2];
float	TotalSumGyroRoll[2];
float	TotalSumGyroPitch[2];
float	TotalAvgGyroRoll[2];
float	TotalAvgGyroPitch[2];
int		TotalBodyEstimateUpdateFlag[2];//	[]left,right

unsigned long	TIMERecover[10];

float	RTX_DeltaMove2[3];

/// variable for profile
BOOL	InvFlag;
long	UpperBodyTime[50];
extern	BOOL	RStopZ;
extern	BOOL	LStopZ;

unsigned char	stage;
unsigned char	nextstage;
unsigned char	stage00;
unsigned char	nextstage00;
unsigned char	stretchedFlag;
unsigned char	Rstretched;
unsigned char	Lstretched;

float	LZ;	// for up-down test
float	RZ;

// extern variable
extern	float	PROF_REF[TOTAL_MTR_NUM];
extern	float	PosInput[12];
extern	float	v_CartPos[12];
extern	float	v5_cartPos[12];
extern	float	AngleInput[TOTAL_MTR_NUM];
extern	float	YAWAngles[2];
extern	float	InvLegAngle[12];								 // Inverse Kinematics Output
extern	float	LPx; extern	float	LPy; extern	float	LPz; // 왼발 위치	Forward Kinematics Output
extern	float	RPx; extern	float	RPy; extern	float	RPz; // 오른발 위치 Forward Kinematics Output
extern	float	tstar;
extern	float	ttstar;
extern	float	UpRatio;
extern	float	ABSHipPos[3];
extern	float	ABSHipVel[3];
extern	float	ABSHipPos5[3];
extern	float	ABSHipVel5[3];
extern	float	v5_CartPos[12];

extern	float	v_CartPosCont00[12];
extern	float	v_CartPosCont000[12];
extern	float	v_CartPosCont02[12];

extern float	Pos_HipPitch;
extern float	Pos_HipPitchOLD;

extern float	v_AngPosEx[6];
//extern float	v_AngArm[4];	// 0:RSP, 1:REB, 2:LSP: 3:LEB
extern float	v_AngArm[8];	// 0:RSP, 1:RSR, 2:RSY, 3:REB, 4:LSP: 5:LSR, 6:LSY, 7:LEB
extern float	v_CTRL_Ankle[2];
extern float	Heel_Landing[2];
extern float	Heel_LandingOLD[2];
extern float	Heel_Landing_LPF[2];
extern float	Heel_Landing_LPF_OLD[2];
extern float	HipMove;
extern int		HipMoveFlag;
extern float	v_CTRL_PosHip;
extern float	v_CTRL_PosHipOLD;
extern float	UpperMovement[TOTAL_MTR_NUM];
extern float	OLD_UpperMovement[TOTAL_MTR_NUM];
extern float	Extra_uppermovement[TOTAL_MTR_NUM];
extern float	Old_Extra_uppermovement[TOTAL_MTR_NUM];
extern float	MotionHipAngPos[2];
extern float	MotionAnkleAngPos[2];

float	tp_cnt[7];
long	int_time1;
long	int_time2;
long	int_time3;

// Kirk Variable
float BC_Walk_Mov_Y[MAX_STEP_NUM], LF_Walk_Mov_Z[MAX_STEP_NUM], RF_Walk_Mov_Z[MAX_STEP_NUM], temp_BC_Walk_Mov_Y;
float temp_LF_Walk_Mov_Z, temp_RF_Walk_Mov_Z;
float DelMov_LF_Walk_Z, DelMov_RF_Walk_Z, DelMov_LF_Walk_Z_ref, DelMov_RF_Walk_Z_ref;
float DelMov_LF_Walk_Z_del, DelMov_RF_Walk_Z_del, DelMov_LF_Walk_Z_old, DelMov_RF_Walk_Z_old;
float DelMov_LAR, DelMov_RAR;
float abs_footLx_ref, abs_footRx_ref, abs_footLx_del, abs_footRx_del, abs_footLx_old2, abs_footRx_old2;
float abs_hipx , abs_footRx , abs_footLx, abs_footLx_old, temp_abs_footLx_1, temp_abs_footLx_2, temp_abs_footLx_3, temp_abs_footLx_4;
float abs_footRx_old, temp_abs_footRx_1, temp_abs_footRx_2, temp_abs_footRx_3, temp_abs_footRx_4;
float abs_hipy , abs_footRy , abs_footLy, abs_footLy_old, temp_abs_footLy_1, temp_abs_footLy_2;
float abs_footRy_old, temp_abs_footRy_1, temp_abs_footRy_2;
float abs_hipx_old, temp_abs_hipx, abs_hipy_old, temp_abs_hipy;
float rel_footRx, rel_footLx,  rel_footRy, rel_footLy;
float temp_LRHY_1_RT, temp_LRHY_2_RT, temp_LRHY_1_LT, temp_LRHY_2_LT, Gesture_Pelvis_1;
float LF_More_Strech_old, LF_More_Strech, RF_More_Strech_old, RF_More_Strech;
float Temp_Step_Length_0, Temp_Step_Length_1, Temp_Step_Length_2;
float Land_OnOff_RAP, Land_OnOff_LAP,Land_OnOff_RAP_2, Land_OnOff_LAP_2, Land_On_Height, Land_Off_Height, Land_On_Fwd_Disp, Land_Off_Fwd_Disp; 
float temp_theta_1, temp_theta_2, temp_theta_3, temp_theta_4, temp_theta_5, temp_theta_6, temp_theta_7, temp_theta_8;
float temp_theta_9, temp_theta_10, temp_theta_11, temp_theta_12, temp_LRHY_1, temp_LRHY_2;
float BC_equi_com_y_con_input, DelMov_LAR_TOC, DelMov_RAR_TOC, DelMov_BC_y_TOC, DelMov_LHR_TOC, DelMov_RHR_TOC ;

float temp_hip_x;
long hip_Adj;

unsigned char LRHY_status, LF_half_1_cos_Status, RF_half_1_cos_Status, LRHY_status_LT, LRHY_status_RT;
unsigned char Land_OnOff_RAP_Status, Land_OnOff_LAP_Status;
unsigned int RAP_Landing_OnOff_CNT, LAP_Landing_OnOff_CNT;
unsigned int LRHY_CNT_RT, LRHY_CNT_LT;
unsigned int landRF_CNT,landRF_r_CNT, landLF_CNT, landLF_r_CNT, abs_footLx_CNT, abs_footRx_CNT, abs_hipx_CNT;
unsigned int abs_footLy_CNT, abs_footRy_CNT, abs_hipy_CNT, LRHY_CNT , DeltaMov_y_Tilt_CNT, DeltaMov_x_Tilt_CNT;

unsigned char WLK_RDY_MODE;
unsigned int Path_Local_CNT;
unsigned char PROF_Status, RF_half_cyclUP_Status, RF_half_cyclDN_Status, LF_half_cyclUP_Status, LF_half_cyclDN_Status, abs_hipx_status, abs_hipy_status;
unsigned char CTRL_mode;
unsigned long temp_Path_Area_CNT;
int Walk_Motion_Mode;
unsigned char Delay_LO_Control_Flag;
unsigned char RF_Landing_PosCon_Flag, LF_Landing_PosCon_Flag;
unsigned int RF_Landing_PosCon_CNT, LF_Landing_PosCon_CNT;
float L_theta_compen_r, L_theta_compen_p, R_theta_compen_r, R_theta_compen_p;
float L_theta_compen_r_old, L_theta_compen_r_del, L_theta_compen_p_old, L_theta_compen_p_del;
float R_theta_compen_r_old, R_theta_compen_r_del, R_theta_compen_p_old, R_theta_compen_p_del;
unsigned int R_theta_compen_CNT, L_theta_compen_CNT, zmp_CNT_1, zmp_CNT_2;
float DeltaMov_x_ini, DeltaMov_y_ini;
float landRF, landLF, landRF_r, landLF_r, landRF_old, landRF_r_old, landLF_old, landLF_r_old, landRF_del, landRF_r_del, landLF_del, landLF_r_del;
float DeltaMov_x, DeltaMov_y;
float DeltaMov_x_dsp, DeltaMov_y_dsp;
float DeltaMov_x_dsp_old, DeltaMov_y_dsp_old;
float DeltaMov_x_ssp, DeltaMov_y_ssp;
float DeltaMov_x_ssp_old, DeltaMov_y_ssp_old;
float Err_Xzmp, Err_Yzmp;
float Ref_Yzmp_Con, old_Ref_Yzmp_Con, BC_y_ZMP_CON, BC_x_ZMP_CON, Ref_Xzmp_Con, old_Ref_Xzmp_Con, Ref_Xzmp_Con_0;
float old_BC_y_ZMP_CON, old_BC_x_ZMP_CON;
unsigned char BC_x_ZMP_CON_CNT, BC_y_ZMP_CON_CNT;
float Start_Kick_BC_Y_Comp;
float Del_Mov_RHip_r , Del_Mov_LHip_r; 
float Equi_Adj_LRAP_Walking;
float Pit_y_a_1_Hspd, Pit_y_a_0_Hspd;
float DelMov_LRAP_OL;
unsigned char DelMov_LRAP_OL_CNT;
float temp_Plus_Yzmp_avg, temp_Minus_Yzmp_avg;
float Amp_BC_Y_Amp_Compen_M, Amp_BC_Y_Amp_Compen_W, Amp_BC_Y_Amp_Compen_B;
float BC_Y_Amp_Compen;
float Temp_Inc_Sum, Inc_Avg, DelMov_BCA;
unsigned char Temp_Inc_Sum_CNT;
float DSP_temp_1, DSP_temp_2, DSP_temp_3, DSP_temp_4, temp_DeltaMov_x, temp_DeltaMov_y, SSP_temp_1, SSP_temp_2, SSP_temp_3, SSP_temp_4, SSP_temp_5;
float g_temp_theta_1, g_temp_theta_2, g_temp_theta_3, g_temp_theta_4, g_temp_theta_5, g_temp_theta_6, g_temp_theta_7, g_temp_theta_8; // for gesture
float g_temp_theta_9, g_temp_theta_10, g_temp_theta_11, g_temp_theta_12, g_temp_theta_13, g_temp_theta_14, g_temp_theta_15, g_temp_theta_16; // for gestures
float Gesture_Pelvis_2;

