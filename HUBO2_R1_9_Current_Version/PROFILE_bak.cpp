#include "math.h"
#include "PROFILE.h"
#include "Function.h"
#include "Define.h"
#include "CAN.h"
#include "RTX.h"

//BOOL	oldKineTocken;

BOOL	RStopZ;
BOOL	LStopZ;

int		LFlag;
int		RFlag;

char	DSPFlag;

float	HipYStayFactor;
float	tstar;
float	ttstar;

float	RSwayFactor0;
float	LSwayFactor0;

float	xCurveFactor;
float	yCurveFactor;

float	UpRatio;

float	v_CartPos2;
float	v_CartPos5;

float	v_CartPos2Last;
float	v_CartPos5Last;

float	LPx; float	LPy; float	LPz; // 왼발 위치	Forward Kinematics Output
float	RPx; float	RPy; float	RPz; // 오른발 위치 Forward Kinematics Output

float	v5_CartPos[12];
float	PosInput[12];
float	v_CartOldPos[12];
float	v_CartPos[12];					
float	v_CartVel[12];
float	v_DeltaPos[12];		// 각 발의 위치를 변화 시키기 위한 변수.
float	v_RecoverPos[6];
float	RecoverPosMag[6];
float	RecoverPosMagX[6];
float	v_DeltaPosOLD[12];
float	DeltaPosMag[6];
float	DeltaPosMagOLD[6];				
float	v_CartPosCont[12];
float	v_CartPosCont000[12];
float	v_CartPosCont00[12]; // Initialize 할 경우에 쓰임
float	v_CartPosCont01[12]; // For ZMP Control
float	v_CartPosCont02[12];
float	v_CartPosCont03[12];
float	v_CartPosCont04[12];
float	v_CartPosCont05[12];
float	v_CartPosCont06[12];
float	v_CartPosCont07[12];

float	v_CartVelCont[12];
float	v_CartPRFview[12];
float	YAWAngles[2];
float	PosYaw[2];
float	DelPosYaw[2];
float	PitchKick[2];
float	PitchLand[2];
float	PitchAngBACKUP[2];
float	PitchAngBACKUPDiff[2];
float	PitchAngBACKUP1[2];
float	PitchAngBACKUPDiff1[2];

float	ABSHipPos[3];
float	ABSHipPosOLD[3];
float	ABSHipVel[3];
float	ABSHipPos5[3];
float	ABSHipVel5[3];
float	ABSHipPos5OLD[3];


float	DefalutUpper[TOTAL_MTR_NUM];
float	UpperMovement[TOTAL_MTR_NUM];
float	OLD_UpperMovement[TOTAL_MTR_NUM];
float	Extra_uppermovement[TOTAL_MTR_NUM];
float	Old_Extra_uppermovement[TOTAL_MTR_NUM];

float	PROF_REF[TOTAL_MTR_NUM];
float	AngleInput[TOTAL_MTR_NUM];

float	InvLegAngle[12];

float	v_PAngPos[TOTAL_MTR_NUM];
float	v_PoldAngPos[TOTAL_MTR_NUM];
float	v_PdiffAngPos[TOTAL_MTR_NUM];
		
float	v_AngPos[TOTAL_MTR_NUM];		float	v_oldAngPos[TOTAL_MTR_NUM];
float	v_diffAngPos[TOTAL_MTR_NUM];
float	v_AngVel[TOTAL_MTR_NUM];	

float	MotionHipAngPos[2];
float	MotionAnkleAngPos[2];

float	v_AngPosCont[TOTAL_MTR_NUM];	float	v_oldAngPosCont[TOTAL_MTR_NUM];
float	v_AngVelCont[TOTAL_MTR_NUM];

float	v_AngPosSwt[TOTAL_MTR_NUM];

float	WalkReadyPos[TOTAL_MTR_NUM];
float	JntAng[TOTAL_MTR_NUM];
float	JntAng1[TOTAL_MTR_NUM];


// Added by BeCool
float	v_AngPosEx[6];
float	v_AngArm[4];	// 0:RSP, 1:REB, 2:LSP: 3:LEB
int		HipMoveFlag;
float	HipMove;
float	HipMoveOLD;
float	HipMoveRatio;
float	HipMoveRatioOLD;
float	StrideOLD;
float	KneeBendingMag;
float	v_CTRL_Ankle[2];
float	Heel_Landing[2];
float	Heel_LandingOLD[2];
float	Heel_Landing_LPF[2];
float	Heel_Landing_LPF_OLD[2];
float	v_CTRL_PosHip;
float	v_CTRL_PosHipOLD;
float	Pos_HipPitch;
float	Pos_HipPitchOLD;
float	v_CTRL_HipRoll[2];		// variable hip roll prevent from torso faling down
float	delta_displacement;
float	delta_displacement_a;
	


float	Mag_Landing[6];
float	Mag_LandingX[6];

void InitPROFVar()
{
	char i;
	DSPFlag = 1;

	HipYStayFactor = 1.;

	MotionHipAngPos[0] = 0.;
	MotionHipAngPos[1] = 0.;

	MotionAnkleAngPos[0] = 0.;
	MotionAnkleAngPos[1] = 0.;

	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		PROF_REF[i]=0.;
		AngleInput[i]=0.;
		
		v_AngPos[i]=0.;		v_oldAngPos[i]=0.;
		v_diffAngPos[i]=0.;
		v_AngVel[i]=0.;		
		v_AngPosCont[i]=0.;	v_oldAngPosCont[i]=0.;
		v_AngVelCont[i]=0.;	

		WalkReadyPos[i]=0.;
		JntAng[i]=0.;
		JntAng1[i]=0.;
		v_AngPosSwt[i]=0.;
		UpperMovement[i] = 0.;
		OLD_UpperMovement[i] = 0.;
		Extra_uppermovement[i] = 0.;
		Old_Extra_uppermovement[i] = 0.;
	}
	for(i=0;i<12;i++)
	{
		InvLegAngle[i]=0.;				
		PosInput[i]=0.;				
		v_CartPos[i]=0.;			
		v_CartVel[i]=0.;
		v_DeltaPos[i] = 0.;
		v_DeltaPosOLD[i] = 0.;
		v_CartPosCont[i]=0.;
		v_CartPosCont000[i]=0.;
		v_CartPosCont00[i]=0.;
		v_CartPosCont01[i]=0.;
		v_CartPosCont02[i]=0.;
		v_CartPosCont03[i]=0.;
		v_CartPosCont04[i]=0.;
		v_CartPosCont05[i]=0.;
		v_CartPosCont06[i]=0.;
		v_CartPosCont07[i]=0.;

		v_CartVelCont[i]=0.;
		v_CartPRFview[i]=0.;

		v5_CartPos[i] = 0.;
	}

	for(i=0;i<6;i++)
	{
		v_RecoverPos[i] = (float)0.;
		RecoverPosMag[i] = (float)0.;
	}

	for(i=0;i<3;i++)	
	{
		ABSHipPos[i]=0.;
		ABSHipPosOLD[i] = (float)0.;
		ABSHipVel[i] = (float)0.;

		ABSHipPos5[i]=0.;
		ABSHipPos5OLD[i] = (float)0.;
		ABSHipVel5[i] = (float)0.;
	}

	PitchKick[0] = 0.;	PitchKick[1] = 0.;
	PitchLand[0] = 0.;	PitchLand[1] = 0.;
	PitchAngBACKUP[0] = 0.;
	PitchAngBACKUP[1] = 0.;
	PitchAngBACKUP1[0] = 0.;
	PitchAngBACKUP1[1] = 0.;
	PitchAngBACKUPDiff[0] = 0.;
	PitchAngBACKUPDiff[1] = 0.;
	PitchAngBACKUPDiff1[0] = 0.;
	PitchAngBACKUPDiff1[1] = 0.;

	RStopZ = FALSE;
	LStopZ = FALSE;
	

	LPx=0.;		LPy= L0;	LPz= -(L1+L2);
	RPx=0.;		RPy=-L0;	RPz= -(L1+L2);

	pSharedMemory->fProfXYZ[0]=			 0;
	pSharedMemory->fProfXYZ[1]=			L0;
	pSharedMemory->fProfXYZ[2]=	  -(L1+L2);

	pSharedMemory->fProfXYZ[3]=			 0;
	pSharedMemory->fProfXYZ[4]=		   -L0;
	pSharedMemory->fProfXYZ[5]=	  -(L1+L2);

	v_CartPos[0]=0;
	v_CartPos[1]=(float)(L0 + WLK_RDY_OFFSET);	//75;
	v_CartPos[2]=(float)(-L1-L2+WLK_RDY_DOWN);
	
	v_CartPos[3]=0;
	v_CartPos[4]=-(float)(L0 + WLK_RDY_OFFSET);// -75;
	v_CartPos[5]=(float)(-L1-L2+WLK_RDY_DOWN);
	
	PosInput[0]=0;
	PosInput[1]=(float)(L0 + WLK_RDY_OFFSET);
	PosInput[2]=(float)(-L1-L2+WLK_RDY_DOWN);
	
	PosInput[3]=0;
	PosInput[4]=-(float)(L0 + WLK_RDY_OFFSET);
	PosInput[5]=(float)(-L1-L2+WLK_RDY_DOWN);

	// Added by BeCool
	HipMoveOLD = (float)0.;
	HipMoveRatio = (float)0.;
	HipMoveRatioOLD = (float)0.;
	StrideOLD = (float)0.;
	KneeBendingMag = (float)0.;

	LFlag = 0;
	RFlag = 0;
	
}

void WalkReady(long	Time)
{
	char i;

	if((Time<=READYTIME)&&(Time>=0))
	{
		if(Time==0)
		{
			WalkReadyPos[RHY] =          (float)0.;	// R-Hip Yaw

			// for HUBO2 4cm
			WalkReadyPos[RHR] =  (float)-0.04565;	// R-Hip Roll
			WalkReadyPos[RHP] = (float)-21.10127;	// R-Hip Pitch
			WalkReadyPos[RKN] =  (float)42.10017;	// R-Knee Pitch
			WalkReadyPos[RAP] = (float)-20.9989;	// R-Ankle Pitch
			WalkReadyPos[RAR] =   (float)0.04565;	// R-Ankle Roll

			WalkReadyPos[LHY] =		    (float)0.;	// L-Hip Yaw
			//WalkReadyPos[36] =	 (float)0.4092486;	// L-Hip Roll
			//WalkReadyPos[37] = (float)-21.0356696;	// L-Hip Pitch
			//WalkReadyPos[38] =  (float)42.0713393;	// L-Knee Pitch
			//WalkReadyPos[39] = (float)-21.0356696;	// L-Ankle Pitch
			//WalkReadyPos[40] =  (float)-0.4092486;	// L-Ankle Roll

			// for HUBO 1cm
			//WalkReadyPos[LHR] =	 (float)0.38844;	// L-Hip Roll
			//WalkReadyPos[LHP] = (float)-10.4681897;	// L-Hip Pitch
			//WalkReadyPos[LKN] =  (float)20.9363795;	// L-Knee Pitch
			//WalkReadyPos[LAP] = (float)-10.4681897;	// L-Ankle Pitch
			//WalkReadyPos[LAR] =  (float)-0.38844;	// L-Ankle Roll

			// for HUBO2 4cm
			WalkReadyPos[LHR] =	 (float)0.04565;	// L-Hip Roll
			WalkReadyPos[LHP] = (float)-21.10127;	// L-Hip Pitch
			WalkReadyPos[LKN] =  (float)42.10017;	// L-Knee Pitch
			WalkReadyPos[LAP] = (float)-20.9989;	// L-Ankle Pitch
			WalkReadyPos[LAR] =  (float)-0.04565;	// L-Ankle Roll

			WalkReadyPos[RSP] = (float)(WalkReadyPos[RHP]/1.);	//	R-Shoulder Pitch
			//WalkReadyPos[RSR] = (float)(-WalkReadyPos[RHR]*30.);	//	R-Shoulder Roll
			WalkReadyPos[RSR] = (float)(-WalkReadyPos[RHR]*300.);	//	R-Shoulder Roll
			WalkReadyPos[RSY] = (float)0.;						//	R-Shoulder Yaw
			WalkReadyPos[REB] = (float)(WalkReadyPos[RKN]/2.);	//	R-Elbow Pitch

			WalkReadyPos[LSP] = (float)(WalkReadyPos[LHP]/1.);	//	L-Shoulder Pitch
			//WalkReadyPos[LSR] = (float)(-WalkReadyPos[LHR]*30.);	//	L-Shoulder Roll
			WalkReadyPos[LSR] = (float)(-WalkReadyPos[LHR]*300.);	//	L-Shoulder Roll
			WalkReadyPos[LSY] = (float)0.;						//	L-Shoulder Yaw
			WalkReadyPos[LEB] = (float)(WalkReadyPos[LKN]/2.);	//	L-Elbow Pitch

			WalkReadyPos[WST] = (float)0.;	//	Trunk
			
			for(i=0;i<TOTAL_MTR_NUM;i++)
			{
				v_diffAngPos[i]=WalkReadyPos[i]-PROF_REF[i];
				v_oldAngPos[i]=PROF_REF[i];
			}
		}

		//
		for(i=0;i<TOTAL_MTR_NUM;i++)
		{
			FTN_half_1_cos(v_diffAngPos[i], Time, 0, READYTIME, 0, 0, &JntAng[i]);
			v_AngPos[i]=v_oldAngPos[i]+JntAng[i];
		}
	}
	else if(Time>READYTIME)
	{
		pSharedMemory->Walk_Ready_Flag = FALSE;
		for(i=0;i<TOTAL_MTR_NUM;i++)
		{
			v_oldAngPos[i]=PROF_REF[i];
		}
	}
}

void Home(long	Time)
{
	char i;

	if((Time<=HOMETIME)&&(Time>=0))
	{
		if(Time==0)
		{
			for(i=0;i<=TOTAL_MTR_NUM;i++)
			{
				v_diffAngPos[i]=(float)(0.-PROF_REF[i]);
				v_oldAngPos[i]=PROF_REF[i];
				
				///////////////////////
				v_PdiffAngPos[i]=(float)(0.-PROF_REF[i]);
				v_PoldAngPos[i]=PROF_REF[i];
			}
		}
		
		for(i=0;i<=TOTAL_MTR_NUM;i++)
		{
			FTN_half_1_cos(v_diffAngPos[i], Time, 0, HOMETIME, 0, 0, &JntAng[i]);
			v_AngPos[i]=v_oldAngPos[i]+JntAng[i];

			///////////////////////
			FTN_half_1_cos(v_PdiffAngPos[i], Time, 0, HOMETIME, 0, 0, &JntAng1[i]);
			v_PAngPos[i]=v_PoldAngPos[i]+JntAng1[i];
		}
	}
	else if(Time>HOMETIME)
	{
		pSharedMemory->Home_Flag = FALSE;
		for(i=0;i<=TOTAL_MTR_NUM;i++)
		{
			v_oldAngPos[i]=PROF_REF[i];

			///////////////////////
			v_PoldAngPos[i]=PROF_REF[i];
		}
	}
}

char PRF_RSteady3DSP(float Sway, float RBack, float RFront, float Side, float Rside, unsigned long Time, int start, int during)
{
	float right[3][2];	//right[x-y-z][up-down, forward-backward, left-right]
	float hip[3][2];	//hip[x-y-z][up-down, forward-backward, left-right]
	float RLegABS;
	float HipABS;
	float RLegREL;
	float c0, t0;
	float Stride;
	float t;
	float dp_t0;
	float RSide;
	
	if((Time>=(unsigned long)start)&&(Time<=((unsigned long)(start+during))))
	{	
		Stride=RBack+RFront;
		dp_t0=(float)(BETA*fabs(RFront-RBack));
		
		t=(float)(((float)Time-(float)start)/((float)during)); // Normalized time 0 ~ 1
		// hip - X Profile
		if(RFront>0)
		{
			c0=(float)((2*PI*RBack)/(Stride));
			t0=(float)(acos(1-2*sqrt(1-(c0-PI)*(c0-PI)/(PI*PI)))/(2*PI));
			
			if(RFront<=RBack) t0=1-t0;
			
			if(t<=t0)		FTN_3poly0(t0,t,-RBack/2,(float)(ALPHA*RBack),0,dp_t0,&HipABS);
			else if(t>t0)	FTN_3poly1(t0,t,0,dp_t0,RFront/2,(float)(ALPHA*RFront),&HipABS);
		}
		else if(RFront<=0)
		{
			FTN_3poly(t,-RBack/2,(float)(ALPHA*RBack),RFront/2,0,&HipABS);
		}
		
		/******* Hip Y *******/
		if((FTN_3poly0(0.5,t,0,ALPHA1,Sway/2,0,&hip[1][0])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP-hip[1][0]-Side/2);
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP-hip[1][0]+Side/2);
		}
		if((FTN_3poly1(0.5,t,Sway/2,0,0,-ALPHA1,&hip[1][1])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP-hip[1][1]-Side/2);
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP-hip[1][1]+Side/2);
		}
		FTN_1_cos(Rside,Time,start,during*2,2,2,&RSide);
		
		v_CartVel[4]=RSide/2;
		v_CartVel[1]=-RSide/2;
		/***************************/
		
		// Right Leg - X Profile
		FTN_cyclUP(Stride,Time,start,during/2, 0, 1, &right[0][0]); // Forward Acc.
		FTN_cyclDN(Stride,Time,start+during/2,during/2, 0, 1, &right[0][1]); // Forward DeAcc.
		RLegABS=right[0][0]+right[0][1]-RBack;
		
		RLegREL=RLegABS-HipABS;
		v_CartPos[3]=RLegREL;
		// Left Leg - X Profile
		v_CartPos[0]=-HipABS;
		
		// Left Leg - Z Profile
		// Up-Down Profile Generation
		FTN_half_1_cos(LEG_UP_AMP,Time,start,during/2,during*3/16,0,&right[2][0]); //Up
		FTN_half_1_cos(-LEG_UP_AMP,Time,start+during/2,during/2,0,0,&right[2][1]); //Down
		// Cartesian Position Update
		v_CartPos[5]=-L1-L2+READY_LEG_UP_AMP+right[2][0]+right[2][1];
		
		return 1;
	}
	else return 0;
}

char PRF_R_SSP_Static(float Sway, float Height, unsigned long Time, int start, int during)
{
	float right[3][2]; //right[x-y-z][up-down, forward-backward, left-right]
	float hip[3][2]; //hip[x-y-z][up-down, forward-backward, left-right]
	
	float t;
	
	if((Time>=(unsigned long)start)&&(Time<=((unsigned long)(start+during))))
	{	
		t=(float)(((float)Time-(float)start)/((float)during))/2; // Normalized time 0 ~ 1
		/******* Hip Y *******/
		if((FTN_3poly0(0.5,t,0,0/*ALPHA1*/,Sway/2,0,&hip[1][0])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP-hip[1][0]);
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP-hip[1][0]);
		}
		if((FTN_3poly1(0.5,t,Sway/2,0,0,-ALPHA1,&hip[1][1])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP-hip[1][1]);
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP-hip[1][1]);
		}
		
		// Left Leg - Z Profile
		// Up-Down Profile Generation
		//FTN_half_1_cos(LEG_UP_AMP,Time,start,during,30, 0,&right[2][0]); //Up
		FTN_half_1_cos(LEG_UP_AMP*2,Time,start,during,30*TS, 0,&right[2][0]); //Up
		
		// Cartesian Position Update
		v_CartPos[5]=-L1-L2+READY_LEG_UP_AMP+right[2][0];
		v_CartPos[2]=-L1-L2+READY_LEG_UP_AMP;

		return 1;
	}
	else return 0;
}
char PRF_L_SSP_Static(float Sway, float Height, unsigned long Time, int start, int during)
{
	float left[3][2]; //left[x-y-z][up-down, forward-backward, left-right]
	float hip[3][2]; //hip[x-y-z][up-down, forward-backward, left-right]
	
	float t;
	
	if((Time>=(unsigned long)start)&&(Time<=((unsigned long)(start+during))))
	{	
		t=(float)(((float)Time-(float)start)/((float)during))/2; // Normalized time 0 ~ 1
		/******* Hip Y *******/
		if((FTN_3poly0(0.5,t,0,0/*ALPHA1*/,Sway/2,0,&hip[1][0])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP+hip[1][0]); // right
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP+hip[1][0]); // left
		}
		if((FTN_3poly1(0.5,t,Sway/2,0,0,ALPHA1,&hip[1][1])==1))
		{
			v_CartPos[4]=(float)(-L0-READY_LEG_SIDE_AMP+hip[1][1]); // right
			v_CartPos[1]= (float)(L0+READY_LEG_SIDE_AMP+hip[1][1]); // left
		}
		
		// Right Leg - Z Profile
		// Up-Down Profile Generation
		//FTN_half_1_cos(LEG_UP_AMP,Time,start,during,30, 0,&left[2][0]); //Up
		FTN_half_1_cos(LEG_UP_AMP*2,Time,start,during,30*TS, 0,&left[2][0]); //Up
		
		// Cartesian Position Update
		v_CartPos[2]=-L1-L2+READY_LEG_UP_AMP+left[2][0]; //left
		v_CartPos[5]=-L1-L2+READY_LEG_UP_AMP;
		
		return 1;
	}
	else return 0;
}
char PRF_goLegXYZto(float Lx, float Ly, float Lz, float Rx, float Ry, float Rz, unsigned long time, unsigned int start, unsigned during)
{
	int		i;

	float Diff[6];
	float Result;

	Diff[0]=Lx-v_CartOldPos[0]; Diff[1]=Ly-v_CartOldPos[1]; Diff[2]=Lz-v_CartOldPos[2];
	Diff[3]=Rx-v_CartOldPos[3]; Diff[4]=Ry-v_CartOldPos[4]; Diff[5]=Rz-v_CartOldPos[5];

	FTN_half_1_cos(1,time,start,during,0,0,&Result);

	for(i=0;i<6;i++)
	{
		v_CartPos[i]=Diff[i]*Result + v_CartOldPos[i];
	}
	return 1;
}
char InvKine(float LPx, float LPy, float LPz, float LYaw, float RPx, float RPy, float RPz, float RYaw)
{
	char  i=0;
	float LYaw1;
	float RYaw1;
	float LValid=0.;
	float RValid=0.;
	float temp[4]={0,0,0,0};
	float temp1[4]={0,0,0,0};
	
	/******** Left Leg Inverse Kinematics *********/
	LYaw1=(float)(LYaw*deg2rad);
	LValid=(float)((LPx*LPx+(LPy-L0)*(LPy-L0)+LPz*LPz-(L1*L1)-(L2*L2))/(2*L1*L2));
	if((LValid>1)||(LValid<-1)) return 0;
	
	InvLegAngle[0]=LYaw1; //[Radian] Left Hip Yaw
	InvLegAngle[3]=(float)acos(LValid); //[Radian] Left Knee Angle
	InvLegAngle[1]=(float)atan2(LPz, -LPx*sin(LYaw1)+(LPy-L0)*cos(LYaw1));//[Radian] Left Hip Roll
	
	temp[0]=(float)(-L2*sin(InvLegAngle[3]));
	temp[1]=(float)(L1+L2*cos(InvLegAngle[3]));
	temp[2]=(float)(LPx*cos(LYaw1)+(LPy-L0)*sin(LYaw1));
	temp[3]=(float)(-LPx*sin(LYaw1)*cos(InvLegAngle[1]) + (LPy-L0)*cos(LYaw1)*cos(InvLegAngle[1])+LPz*sin(InvLegAngle[1]));
	
	LValid = (float)((temp[0]*temp[3]-temp[1]*temp[2])/(temp[0]*temp[0]+temp[1]*temp[1]));

	if((LValid>1)||(LValid<-1)) return 0;
	
	InvLegAngle[2]=(float)asin(LValid);
	
	InvLegAngle[1]=(float)(InvLegAngle[1]+PI/2.); // Offset Setting
	
	/******* If Ankle Parallel Condition Applied*******/
	InvLegAngle[4]=-InvLegAngle[3]-InvLegAngle[2]; // Ankle Pitch Angle
	InvLegAngle[5]=-InvLegAngle[1]; // Ankle Roll Angle
	/**************************************************/
	/******** End of Left Leg Inverse Kinematics *********/
	
	/******** Right Leg Inverse Kinematics *********/
	RYaw1=(float)(RYaw*deg2rad);
	RValid=(float)((RPx*RPx+(RPy+L0)*(RPy+L0)+RPz*RPz-(L1*L1)-(L2*L2))/(2*L1*L2));
	if((RValid>1)||(RValid<-1)) return 0;
	
	InvLegAngle[6]=RYaw1; //[Radian] Right Hip Yaw
	InvLegAngle[9]=(float)acos(RValid); //[Radian] Left Knee Angle
	InvLegAngle[7]=(float)atan2(RPz, -RPx*sin(RYaw1)+(L0+RPy)*cos(RYaw1));//[Radian] Right Hip Roll
	
	temp1[0]=(float)(-L2*sin(InvLegAngle[9]));
	temp1[1]=(float)(L1+L2*cos(InvLegAngle[9]));
	temp1[2]=(float)(RPx*cos(RYaw1)+(RPy+L0)*sin(RYaw1));
	temp1[3]=(float)(-RPx*sin(RYaw1)*cos(InvLegAngle[7]) + (RPy+L0)*cos(RYaw1)*cos(InvLegAngle[7])+RPz*sin(InvLegAngle[7]));
	
	RValid = (float)((temp1[0]*temp1[3]-temp1[1]*temp1[2])/(temp1[0]*temp1[0]+temp1[1]*temp1[1]));
	
	if((RValid>1)||(RValid<-1)) return 0;
	
	InvLegAngle[8]=(float)asin(RValid);
	
	InvLegAngle[7]=(float)(InvLegAngle[7]+PI/2.); // Offset Setting
	
	/******* If Ankle Parallel Condition Applied*******/
	InvLegAngle[10]=-InvLegAngle[9]-InvLegAngle[8]; // Ankle Pitch
	InvLegAngle[11]=-InvLegAngle[7]; // Ankle Roll
	/**************************************************/
	/******** End of Right Leg Inverse Kinematics *********/	

	/******* Radian to Degree Conversion **************/
	for(i=0;i<12;i++)
	{
		InvLegAngle[i]=(float)(InvLegAngle[i]*rad2deg);
	}
	/**************************************************/
	return 1;
}

char FrdKine(float LTh1, float LTh2, float LTh3, float LTh4, float LTh5, float LTh6,
			 float RTh1, float RTh2, float RTh3, float RTh4, float RTh5, float RTh6)
{
	float LTh1_; float LTh2_; float LTh3_; float LTh4_; float LTh5_; float LTh6_;
	float RTh1_; float RTh2_; float RTh3_; float RTh4_; float RTh5_; float RTh6_;

	LTh1_=(float)(LTh1*deg2rad);	LTh2_=(float)(LTh2*deg2rad);	LTh3_=(float)(LTh3*deg2rad);
	LTh4_=(float)(LTh4*deg2rad);	LTh5_=(float)(LTh5*deg2rad);	LTh6_=(float)(LTh6*deg2rad);

	RTh1_=(float)(RTh1*deg2rad);	RTh2_=(float)(RTh2*deg2rad);	RTh3_=(float)(RTh3*deg2rad);
	RTh4_=(float)(RTh4*deg2rad);	RTh5_=(float)(RTh5*deg2rad);	RTh6_=(float)(RTh6*deg2rad);

	LPx=(float)(-L1*(sin(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_)+cos(LTh1_)*sin(LTh3_))
				-L2*(cos(LTh1_)*sin(LTh3_+LTh4_)+sin(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_+LTh4_)));

	LPy=(float)(-(-L0+L1*(cos(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_)-sin(LTh1_)*sin(LTh3_))
				+L2*(cos(LTh1_)*cos(LTh2_+PI/2)*cos(LTh3_+LTh4_)-sin(LTh1_)*sin(LTh3_+LTh4_))));

	LPz=(float)(-(L1*sin(LTh2_+PI/2.)*cos(LTh3_)+L2*sin(LTh2_+PI/2.)*cos(LTh3_+LTh4_)));

	
	RPx=(float)(-L1*(sin(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_)+cos(RTh1_)*sin(RTh3_))
				-L2*(cos(RTh1_)*sin(RTh3_+RTh4_)+sin(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_+RTh4_)));
	
	RPy=(float)(-(+L0+L1*(cos(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_)-sin(RTh1_)*sin(RTh3_))
				+L2*(cos(RTh1_)*cos(RTh2_+PI/2)*cos(RTh3_+RTh4_)-sin(RTh1_)*sin(RTh3_+RTh4_))));
	
	RPz=(float)(-(L1*sin(RTh2_+PI/2.)*cos(RTh3_)+L2*sin(RTh2_+PI/2.)*cos(RTh3_+RTh4_)));

	return 1;
}

void AngPosInput(unsigned char mode)
{
	char i=0;
	if(mode == 0)
	{
		for(i=0;i<TOTAL_MTR_NUM;i++)
		{
			AngleInput[i]=v_AngPos[i]+v_AngPosCont[i];
			AngleInput[i]+=(v_AngVel[i]+v_AngVelCont[i]);
		}
	}
	else if(mode == 1)
	{
		for(i=RHY;i<=LAR;i++)
		{
			AngleInput[i]=v_AngPos[i]+v_AngPosCont[i];
			AngleInput[i]+=(v_AngVel[i]+v_AngVelCont[i]);
		}
	}
	else if(mode == 2)
	{
		for(i=RWY;i<=LEB;i++)
		{
			AngleInput[i]=v_AngPos[i]+v_AngPosCont[i];
			AngleInput[i]+=(v_AngVel[i]+v_AngVelCont[i]);
		}
		
	}
}

void CartPosInput(unsigned char mode)
{
	char	i=0;

	if(mode == 0)
	{
		for(i=0;i<12;i++)
		{
			if(i==2)
			{
				if(LStopZ == TRUE)	PosInput[2]=v_CartPos2+v_CartPosCont[2]+v_CartPosCont000[2]+v_CartPosCont00[2]
												+v_CartPosCont01[2]+v_CartPosCont02[2]+v_CartPosCont03[2]+v_CartPosCont04[2]+v_CartPosCont05[2]
												+v_CartPosCont06[2]+v_CartPosCont07[2];//+v_CartPosContPROF[2];
				else	PosInput[2]=v_CartPos[2]+v_CartPosCont[2]+v_CartPosCont000[2]+v_CartPosCont00[2]
									+v_CartPosCont01[2]+v_CartPosCont02[2]+v_CartPosCont03[2]+v_CartPosCont04[2]+v_CartPosCont05[2]
									+v_CartPosCont06[2]+v_CartPosCont07[2];//+v_CartPosContPROF[2];
			}
			else if(i==5)
			{
				if(RStopZ == TRUE)	PosInput[5]=v_CartPos5+v_CartPosCont[5]+v_CartPosCont000[5]+v_CartPosCont00[5]
												+v_CartPosCont01[5]+v_CartPosCont02[5]+v_CartPosCont03[5]+v_CartPosCont04[5]+v_CartPosCont05[5]
												+v_CartPosCont06[5]+v_CartPosCont07[5];//+v_CartPosContPROF[5];
				else	PosInput[5]=v_CartPos[5]+v_CartPosCont[5]+v_CartPosCont000[5]+v_CartPosCont00[5]
									+v_CartPosCont01[5]+v_CartPosCont02[5]+v_CartPosCont03[5]+v_CartPosCont04[5]+v_CartPosCont05[5]
									+v_CartPosCont06[5]+v_CartPosCont07[5];//+v_CartPosContPROF[5];
			}
			else
				PosInput[i]=v_CartPos[i]+v_CartPosCont[i]+v_CartPosCont000[i]+v_CartPosCont00[i]
							+v_CartPosCont01[i]+v_CartPosCont02[i]+v_CartPosCont03[i]+v_CartPosCont04[i]+v_CartPosCont05[i]
							+v_CartPosCont06[i]+v_CartPosCont07[i];//+v_CartPosContPROF[i];

			PosInput[i]=PosInput[i]+(v_CartVel[i]+v_CartVelCont[i]);

			v_CartPRFview[i] = v_CartPos[i];//+v_CartPosContPROF[i];
			v_CartPRFview[i] += v_CartVel[i];
		}
		YAWAngles[0] = PosYaw[0];
		YAWAngles[1] = PosYaw[1];
	}
	else if(mode == 1)
	{
		for(i=0;i<6;i++)
		{
			if(i==2)
			{
				if(LStopZ == TRUE)	PosInput[2]=v_CartPos2+v_CartPosCont[2]+v_CartPosCont000[2]+v_CartPosCont00[2]
												+v_CartPosCont01[2]+v_CartPosCont02[2]+v_CartPosCont03[2]+v_CartPosCont04[2]+v_CartPosCont05[2]
												+v_CartPosCont06[2]+v_CartPosCont07[2];//+v_CartPosContPROF[2];
				else if(LStopZ == FALSE)	PosInput[2]=v_CartPos[2]+v_CartPosCont[2]+v_CartPosCont000[2]+v_CartPosCont00[2]
														+v_CartPosCont01[2]+v_CartPosCont02[2]+v_CartPosCont03[2]+v_CartPosCont04[2]+v_CartPosCont05[2]
														+v_CartPosCont06[2]+v_CartPosCont07[2];//+v_CartPosContPROF[2];
			}
			else if(i==5)
			{
				if(RStopZ == TRUE)	PosInput[5]=v_CartPos5+v_CartPosCont[5]+v_CartPosCont000[5]+v_CartPosCont00[5]
												+v_CartPosCont01[5]+v_CartPosCont02[5]+v_CartPosCont03[5]+v_CartPosCont04[5]+v_CartPosCont05[5]
												+v_CartPosCont06[5]+v_CartPosCont07[5];//+v_CartPosContPROF[5];
				else if(RStopZ == FALSE) PosInput[5]=v_CartPos[5]+v_CartPosCont[5]+v_CartPosCont000[5]+v_CartPosCont00[5]
												+v_CartPosCont01[5]+v_CartPosCont02[5]+v_CartPosCont03[5]+v_CartPosCont04[5]+v_CartPosCont05[5]
												+v_CartPosCont06[5]+v_CartPosCont07[5];//+v_CartPosContPROF[5];
			}
			else
				PosInput[i]=v_CartPos[i]+v_CartPosCont[i]+v_CartPosCont000[i]+v_CartPosCont00[i]
							+v_CartPosCont01[i]+v_CartPosCont02[i]+v_CartPosCont03[i]+v_CartPosCont04[i]+v_CartPosCont05[i]
							+v_CartPosCont06[i]+v_CartPosCont07[i];//+v_CartPosContPROF[i];

			//PosInput[i]=PosInput[i]+(v_CartVel[i]+v_CartVelCont[i]);
			PosInput[i]=PosInput[i]+(v_CartVel[i]+v_CartVelCont[i]+v_DeltaPos[i]);

			v_CartPRFview[i] = v_CartPos[i];//+v_CartPosContPROF[i];
			v_CartPRFview[i] += v_CartVel[i];
		}
		YAWAngles[0] = PosYaw[0];
		YAWAngles[1] = PosYaw[1];
	}
}

void v_CartBackUP()
{
//	char PRF_goLegXYZto(float Lx, float Ly, float Lz, float Rx, float Ry, float Rz, unsigned long time, unsigned int start, unsigned during)
//	위 함수를 사용할 시 직전 단계에서 백업을 한다.
	unsigned char i;
	for(i=0;i<12;i++)
	{
		v_CartOldPos[i]=v_CartPos[i];
	}
}

void RCurveFactors(int during, float X_step, float Y_step)
{
	float	X;
	float	Y;

	X=X_step;
	Y=Y_step;

	/*
	if(during == 95)
		xCurveFactor = (float)1.; // 1.0
	else if(during == 80)
		xCurveFactor = (float)(1.50/ALPHA); //1.50
	else if(during == 70)
		xCurveFactor = (float)((pSharedMemory->X_ShapeFactor)/ALPHA); // for tunning
	*/

	xCurveFactor = (float)((pSharedMemory->X_ShapeFactor_mod)/ALPHA); // for tunning

	if(Y==0)
	{
		//yCurveFactor = (float)1.;
		//if(during == 70)	HipYStayFactor = (float)0.9;
		//else HipYStayFactor = (float)1.0;

		yCurveFactor = pSharedMemory->Y_ShapeFactor;
		HipYStayFactor = (float)1.0;
	}
	else if(Y>0) //recover part
	{
		//yCurveFactor = (float)1.;
		//yCurveFactor = pSharedMemory->Y_ShapeFactor;
		yCurveFactor = pSharedMemory->Y_ShapeFactorRecover;
		HipYStayFactor = (float)pSharedMemory->SwayDelayRecover;//2.2;//2.0;//2.5;
	}
	else //open stance part
	{
		//yCurveFactor = pSharedMemory->Y_ShapeFactor;
		yCurveFactor = pSharedMemory->Y_ShapeFactorOpen;
		HipYStayFactor = (float)pSharedMemory->SwayDelayOpen;//2.0;//2.0;//2.5;
	}
}

void LCurveFactors(int during, float X_step, float Y_step)
{
	float	X;
	float	Y;
	
	X=X_step;
	Y=Y_step;
	
	/*
	if(during == 95)
		xCurveFactor = (float)1.; // 1.0
	else if(during == 80)
		xCurveFactor = (float)(1.50/ALPHA); //1.50
	else if(during == 70)
		xCurveFactor = (float)((pSharedMemory->X_ShapeFactor)/ALPHA); // for tunning
	*/
	
	xCurveFactor = (float)((pSharedMemory->X_ShapeFactor_mod)/ALPHA); // for tunning

	if(Y==0)
	{
		//yCurveFactor = (float)1.;
		//if(during == 70)	HipYStayFactor = (float)0.9;
		//else HipYStayFactor = (float)1.;

		yCurveFactor = pSharedMemory->Y_ShapeFactor;
		HipYStayFactor = (float)1.0;
	}
	else if(Y<0) //recover part
	{
		//yCurveFactor = (float)1.;
		//yCurveFactor = pSharedMemory->Y_ShapeFactor;
		yCurveFactor = pSharedMemory->Y_ShapeFactorRecover;
		HipYStayFactor = (float)pSharedMemory->SwayDelayRecover;//2.2;//2.0;//2.5;
	}
	else //open stance part
	{
		//yCurveFactor = pSharedMemory->Y_ShapeFactor;
		yCurveFactor = pSharedMemory->Y_ShapeFactorOpen;
		HipYStayFactor = (float)pSharedMemory->SwayDelayOpen;//2.0;//2.0;//2.5;
	}
}


void RSwayFactor(int during, float Rforward, float RSide)
{
	int StepTime;
	float RStepLength;
	float RSideLength;

	StepTime = during;
	RStepLength = Rforward;
	RSideLength = RSide;

	if(RSideLength < 0)
	{
		RSwayFactor0 = pSharedMemory->YSway_Factor;
		pSharedMemory->RollOrienGainFactor = (float)0.5;
		pSharedMemory->RollVibGainFactor = (float)1.0;//0.0;
	}
	else
	{
		RSwayFactor0 = (float)1.0;
		pSharedMemory->RollOrienGainFactor = (float)1.0;
		pSharedMemory->RollVibGainFactor = (float)1.0;
	}
}

void LSwayFactor(int during, float Lforward, float LSide)
{
	int StepTime;
	float LStepLength;
	float LSideLength;
	
	StepTime = during;
	LStepLength = Lforward;
	LSideLength = LSide;

	if(LSideLength > 0)
	{
		LSwayFactor0 = pSharedMemory->YSway_Factor;
		pSharedMemory->RollOrienGainFactor = (float)0.5;
		pSharedMemory->RollVibGainFactor = (float)1.0;//0.0;
	}
	else
	{
		LSwayFactor0 = (float)1.0;
		pSharedMemory->RollOrienGainFactor = (float)1.0;
		pSharedMemory->RollVibGainFactor = (float)1.0;
	}
}

/*
void RAnkKick(float MAX, long time, long start, long during)
{
	float result1;
	float result2;
	
	FTN_half_1_cos(MAX,time,start,(long)during/2,0,0,&result1);
	FTN_half_1_cos(-MAX,time,(long)during/2,(long)during/2,0,0,&result2);
	
	PitchKick[1] = result1+result2;
}
*/
void RAnkKick2(float MAX, long time, long start, int during, int delay1, int delay2)
{
	float ankPKick;
	static float OldAnkle = 0.;
	static float DelAnkle = 0.;
	
	if(time<start)	ankPKick = 0.;
	else if((time>=start)&&(time<=start+during/2-DSPTIME*2))
	{
		FTN_half_1_cos(MAX,time,start,during/2,DSPTIME,DSPTIME,&ankPKick);
		PitchKick[1] = ankPKick;
		OldAnkle = PitchKick[1];
		DelAnkle = 0 - PitchKick[1];
	}
	else if((time>start+during/2-DSPTIME*2)&&(time<=start+during-DSPTIME*2))
	{
		PitchKick[1] = PRF_C1_cosRecover(OldAnkle, DelAnkle, time,start+during/2-DSPTIME*2,during/2);
	}
	else
	{
		PitchKick[1] = 0.;
		OldAnkle = 0.;
		DelAnkle = 0.;
		ankPKick = 0.;
	}
	
}
void RAnkKick1(float MAX, float RZpos, long time, long start, int during, int delay1, int delay2)
{
	float maxR;
	float ankPKick;
	static float OldAnkle = 0.;
	static float DelAnkle = 0.;

	if(MAX>=21)
		maxR = 21;
	else maxR = MAX;
	
	if((time>=start)&&(time<=start+during/2))
	{
		if(RZpos <= 0.)	ankPKick = 0.;
		else if(((RZpos+ANK2BASE)/ANK2TOE) < 1) ankPKick = (float)(rad2deg*(asin((RZpos+ANK2BASE)/ANK2TOE))-ANK2TOEANGLE);
		
		if(ankPKick >= maxR)	ankPKick = maxR;

		PitchKick[1] = ankPKick;
		OldAnkle = PitchKick[1];
		DelAnkle = 0 - PitchKick[1];
	}
	else if((time>start+during/2)&&(time<=start+during))
	{
		PitchKick[1] = PRF_C1_cosRecover(OldAnkle, DelAnkle, time,start+during/2,during/2);
	}
	else
	{
		PitchKick[1] = 0.;
		OldAnkle = 0.;
		DelAnkle = 0.;
		ankPKick = 0.;
	}
}

void RAnkLand(float Ang, long time, long start, long during, char reset)
{
	static float ank=0.;
	float result1;
	static float old_ank;
	static float diff_ank;

	PitchLand[0] = PRF_C1_cosRecover(PitchAngBACKUP[0],PitchAngBACKUPDiff[0],time,start,(long)during/2-10);

	FTN_half_1_cos(Ang,time,start+(long)during/2,(long)during/2-10,0,0,&result1);
	PitchLand[1] = result1;

	PitchAngBACKUP[1] = PitchLand[1];
	PitchAngBACKUPDiff[1] = (float)(0-PitchAngBACKUP[1]);
}

void RAnkLandSTOP(long time, long start, long during)
{
	if((time>=start)&&(time<=start+(long)during/2-10)) // recover stage
	{
		PitchLand[1] = PRF_C1_cosRecover(PitchAngBACKUP[1],PitchAngBACKUPDiff[1],time,start,(long)during/2-10);
	}
}

/*
void LAnkKick(float MAX, long time, long start, long during)
{
	float result1;
	float result2;
	float tmpAMG;

	FTN_half_1_cos(MAX,time,start,(long)during/2,0,0,&result1);
	FTN_half_1_cos(-MAX,time,(long)during/2,(long)during/2,0,0,&result2);

	PitchKick[0] = result1+result2;
	tmpAMG = (float)(PitchKick[0]*deg2rad);
}
*/

void LAnkKick2(float MAX, long time, long start, int during, int delay1, int delay2)
{
	float ankPKick;
	static float OldAnkle = 0.;
	static float DelAnkle = 0.;
	
	if(time<start)	ankPKick = 0.;
	else if((time>=start)&&(time<=start+during/2-DSPTIME*2))
	{
		FTN_half_1_cos(MAX,time,start,during/2,DSPTIME,DSPTIME,&ankPKick);
		PitchKick[0] = ankPKick;
		OldAnkle = PitchKick[0];
		DelAnkle = 0 - PitchKick[0];
	}
	else if((time>start+during/2-DSPTIME*2)&&(time<=start+during-DSPTIME*2))
	{
		PitchKick[0] = PRF_C1_cosRecover(OldAnkle, DelAnkle, time,start+during/2-DSPTIME*2,during/2);
	}
	else
	{
		PitchKick[0] = 0.;
		OldAnkle = 0.;
		DelAnkle = 0.;
		ankPKick = 0.;
	}
}
void LAnkKick1(float MAX, float LZpos, long time, long start, int during, int delay1, int delay2)
{
	float maxL;
	float ankPKick;
	static float OldAnkle = 0.;
	static float DelAnkle = 0.;
	
	if(MAX>=21)
		maxL = 21;
	else maxL = MAX;
	
	if((time>=start)&&(time<=start+during/2))
	{
		if(LZpos <= 0.)	ankPKick = 0.;
		else if(((LZpos+ANK2BASE)/ANK2TOE) < 1) ankPKick = (float)(rad2deg*(asin((LZpos+ANK2BASE)/ANK2TOE))-ANK2TOEANGLE);
		
		if(ankPKick >= maxL)	ankPKick = maxL;
		
		PitchKick[0] = ankPKick;
		OldAnkle = PitchKick[0];
		DelAnkle = 0 - PitchKick[0];
	}
	else if((time>start+during/2)&&(time<=start+during))
	{
		PitchKick[0] = PRF_C1_cosRecover(OldAnkle, DelAnkle, time,start+during/2,during/2);
	}
	else
	{
		PitchKick[0] = 0.;
		OldAnkle = 0.;
		DelAnkle = 0.;
		ankPKick = 0.;
	}
}
void LAnkLand(float Ang, long time, long start, long during, char reset)
{
	static float ank=0.;
	float result1;
	static float old_ank;
	static float diff_ank;

	PitchLand[1] = PRF_C1_cosRecover(PitchAngBACKUP[1],PitchAngBACKUPDiff[1],time,start,(long)during/2-10);
	
	FTN_half_1_cos(Ang,time,start+(long)during/2,(long)during/2-10,0,0,&result1);
	PitchLand[0] = result1;
	
	PitchAngBACKUP[0] = PitchLand[0];
	PitchAngBACKUPDiff[0] = (float)(0-PitchAngBACKUP[0]);
}

void LAnkLandSTOP(long time, long start, long during)
{
	if((time>=start)&&(time<=start+(long)during/2-10)) // recover stage
	{
		PitchLand[0] = PRF_C1_cosRecover(PitchAngBACKUP[0],PitchAngBACKUPDiff[0],time,start,(long)during/2-10);
	}
}

float	PRF_C1_cosRecover(float oldData, float diffData, unsigned int Time, unsigned int start, unsigned int during)
{
	float Recover,prf;
	
	if((Time>start)&&(Time<start+during))
	{
		FTN_half_1_cos(diffData,Time,start,during,0,0,&prf);
		Recover = oldData+prf;
	}
	else if(Time<=start)
	{
		Recover = oldData;
	}
	else if(Time>=start+during)
	{
		Recover = oldData + diffData;
	}
	return Recover;
}

void	PROF_ArmShake(long Time, int mode, int start, int during, float stride)
{
	// mode : 0 --> RStart
	// mode : 1 --> LSteady
	// mode : 2 --> RSteady
	// mode : 3 --> LStop
	// mode : 4 --> RStop
	float tp_out1;
	float tp_out2;
	float mag_arm;
	int ij=0;

	mag_arm = (float)(0.015*stride + ZeroStrideArmShake);

	tp_out1 = 0;
	tp_out2 = 0;
	
	if(mode == 0)
	{
		FTN_half_1_cos(mag_arm, Time, start, during/2, 5*TS, 0, &tp_out1);
		FTN_quarter_1_cos(-mag_arm, Time, start+during/2, during/2, 0, 0, &tp_out2);
		//FTN_half_1_cos(-mag_arm, Time, start+during/2, during/2, 0, 0, &tp_out2);

		v_AngArm[0] = -tp_out1 - tp_out2;
		v_AngArm[1] = (float)(0.2*(-tp_out1 - tp_out2));
		v_AngArm[2] = -v_AngArm[0];
		v_AngArm[3] = -v_AngArm[1];

	}
	else if(mode == 1)
	{
		FTN_half_sin(mag_arm, Time, start, during, 0, 0, &tp_out1);

		v_AngArm[0] = tp_out1;
		v_AngArm[1] = (float)(0.2*tp_out1);
		v_AngArm[2] = -v_AngArm[0];
		v_AngArm[3] = -v_AngArm[1];

	}
	else if(mode == 2)
	{
		FTN_half_sin(mag_arm, Time, start, during, 0, 0, &tp_out1);

		v_AngArm[0] = -tp_out1;
		v_AngArm[1] = (float)(-0.2*tp_out1);
		v_AngArm[2] = -v_AngArm[0];
		v_AngArm[3] = -v_AngArm[1];
	}
	else if(mode == 3)
	{
		//FTN_half_1_cos(mag_arm, Time, start, during/2, 0, 0, &tp_out1);
		FTN_quarter_sin(mag_arm, Time, start, during/2, 0, 0, &tp_out1);
		FTN_half_1_cos(-mag_arm, Time, start+during/2, during/2, 0, 2, &tp_out2);

		v_AngArm[0] = tp_out1 + tp_out2;
		v_AngArm[1] = (float)(0.2*(tp_out1 + tp_out2));
		v_AngArm[2] = -v_AngArm[0];
		v_AngArm[3] = -v_AngArm[1];
	}
	else if(mode == 4)
	{
		//FTN_half_1_cos(mag_arm, Time, start, during/2, 0, 0, &tp_out1);
		FTN_quarter_sin(mag_arm, Time, start, during/2, 0, 0, &tp_out1);
		FTN_half_1_cos(-mag_arm, Time, start+during/2, during/2, 0, 2, &tp_out2);
		
		v_AngArm[0] = -tp_out1 - tp_out2;
		v_AngArm[1] = (float)(0.2*(-tp_out1 - tp_out2));
		v_AngArm[2] = -v_AngArm[0];
		v_AngArm[3] = -v_AngArm[1];
	}
	else
	{
		v_AngArm[0] = (float)0.;
		v_AngArm[1] = (float)0.;
		v_AngArm[2] = (float)0.;
		v_AngArm[3] = (float)0.;

		for(ij=RSP;ij<=LEB;ij++) DefalutUpper[ij] = v_AngPos[ij];
	}

	//pSharedMemory->temp[0] = tp_out1;
	//pSharedMemory->temp[1] = tp_out2;
	//pSharedMemory->temp[2] = Time;
	//pSharedMemory->temp[3] = mode;
	//pSharedMemory->temp[4] = during;
	//pSharedMemory->temp[5] = start;
	//pSharedMemory->temp[6] = stride;
}

float	PROF_ArmShake_Walk(long Time,unsigned char Flag)
{
	int		i;
	float	time;
	static float oldJntAng1[TOTAL_MTR_NUM];
	static float JntAng1[TOTAL_MTR_NUM];
	
	float result1[TOTAL_MTR_NUM];
	/*
	/////////////// Arm & Torso //////////////
		v_AngPos[20];	// R-Shoulder Pitch	
		v_AngPos[21];	// R-Shoulder Roll	
		v_AngPos[22];	// R-Shoulder Yaw
		v_AngPos[23];	// R-Elbow	Pitch
		
		v_AngPos[24];	// L-Shoulder Pitch
		v_AngPos[25];	// L-Shoulder Roll
		v_AngPos[26];	// L-Shoulder Yaw
		v_AngPos[27];	// L-Elbow	Pitch		
		
		v_AngPos[28];	// Trunk

  
	/////////////// Leg //////////////
		InvLegAngle[8];		// R-Hip Pitch
		InvLegAngle[9];		// R-Knee Pitch
	
		InvLegAngle[2];		// L-Hip Pitch
		InvLegAngle[3];		// L-Knee Pitch
	*/
	if(Flag == 1)
	{		
		oldJntAng1[RSP] = v_AngPos[RSP];
		oldJntAng1[REB] = v_AngPos[REB];
		oldJntAng1[LSP] = v_AngPos[LSP];
		oldJntAng1[LEB] = v_AngPos[LEB];
		
		
		v_AngPos[RSP] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[RSP]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[2]));
		v_AngPos[REB] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[REB]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[3]));
		
		v_AngPos[LSP] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[LSP]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[8]));
		v_AngPos[LEB] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[LEB]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[9]));
		
		/*
		v_AngPos[RSP] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[RSP]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[2] - WalkReadyPos[RSP]));
		v_AngPos[REB] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[REB]+2.*PI*ARM_CUTOFF*DELTA_T*(0.5*InvLegAngle[3]));
		
		v_AngPos[LSP] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[LSP]+2.*PI*ARM_CUTOFF*DELTA_T*(InvLegAngle[8] - WalkReadyPos[LSP]));
		v_AngPos[LEB] = (float)((1-2.*PI*ARM_CUTOFF*DELTA_T)*oldJntAng1[LEB]+2.*PI*ARM_CUTOFF*DELTA_T*(0.5*InvLegAngle[9]));
		*/
		JntAng1[RSP] = v_AngPos[RSP];
		JntAng1[REB] = v_AngPos[REB];
		JntAng1[LSP] = v_AngPos[LSP];
		JntAng1[LEB] = v_AngPos[LEB];


		return 1;
	}
	else if(Flag == 0)
	{
		if(Time<=(50*TS))	time = (float)((float)Time/(50.*TS));
		else time = 1.0;
		
		FTN_3poly(time,JntAng1[RSP],(JntAng1[RSP]-oldJntAng1[RSP])*50,WalkReadyPos[RSP],0,&result1[RSP]);
		v_AngPos[RSP]=result1[RSP];

		FTN_3poly(time,JntAng1[REB],(JntAng1[REB]-oldJntAng1[REB])*50,WalkReadyPos[REB],0,&result1[REB]);
		v_AngPos[REB]=result1[REB];
		
		FTN_3poly(time,JntAng1[LSP],(JntAng1[LSP]-oldJntAng1[LSP])*50,WalkReadyPos[LSP],0,&result1[LSP]);
		v_AngPos[LSP]=result1[LSP];

		FTN_3poly(time,JntAng1[LEB],(JntAng1[LEB]-oldJntAng1[LEB])*50,WalkReadyPos[LEB],0,&result1[LEB]);
		v_AngPos[LEB]=result1[LEB];

		if(time>=1)
		{
			for(i=0;i<TOTAL_MTR_NUM;i++)
				DefalutUpper[i] = v_AngPos[i];
		}
		return 0;
	}
	return 2;
}
 

void	PROF_Wrist_Shake(long time)
{
	v_AngPos[RWY] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
	v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
	v_AngPos[RW2] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
}

void	PROF_Wrist_Shake(long time, int mode)
{
	if(mode == 1)
	{
		v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if((mode == 2) || (mode == 3))
	{
		v_AngPos[RWY] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(-pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		v_AngPos[RW2] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 4) 
	{
		v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI+PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 5)
	{
		v_AngPos[RWY] = (float)0.;
		v_AngPos[RW1] = (float)0.;
		v_AngPos[RW2] = (float)0.;
	}
	
}

void	PROF_Wrist_Shake1(long time, int mode)	// 180deg phase
{
	if(mode == 1)
	{
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if((mode == 2) || (mode == 3))
	{
		//v_AngPos[RWY] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		v_AngPos[RW1] = (float)(-pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		v_AngPos[RW2] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 4) 
	{
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI+PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 5)
	{
		v_AngPos[RWY] = (float)0.;
		v_AngPos[RW1] = (float)0.;
		v_AngPos[RW2] = (float)0.;
	}
	
}

void	PROF_Wrist_Shake2(long time, int mode)	// 1-axis
{
	if(mode == 1)
	{
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if((mode == 2) || (mode == 3))
	{
		//v_AngPos[RWY] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(cos(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW1] = (float)(-pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
		//v_AngPos[RW2] = (float)(pSharedMemory->WristAmp*(sin(2.*PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 4) 
	{
		//v_AngPos[RW1] = (float)(pSharedMemory->WristAmp*0.5*(1. - cos(PI+PI*pSharedMemory->WristHz*time*DELTA_T)));
	}
	else if(mode == 5)
	{
		v_AngPos[RWY] = (float)0.;
		v_AngPos[RW1] = (float)0.;
		v_AngPos[RW2] = (float)0.;
	}
	
}

void	PROF_WristConfigure1(long time)
{
	float temp;
	temp = (float)(0.5*(1. - cos(PI*time*DELTA_T)));

	UpperMovement[RSP] = (float)(20.*temp);
	UpperMovement[REB] = (float)(50.*temp);
}

void	PROF_WristConfigure2(long time)
{
	float temp;
	temp = (float)(0.5*(1. - cos(PI*time*DELTA_T)));
	
	UpperMovement[RSP] = (float)(20.*(1. - temp));
	UpperMovement[REB] = (float)(50.*(1. - temp));
}


void	PROF_Shoulder_Shake(long time, int mode)
{
	float temp1;
	float temp2;
	float temp3;
	float temp4;
	
	temp1 = (float)(0.5*(1. - cos(PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T)));
	temp2 = (float)(cos(2.*PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T));
	temp3 = (float)(sin(2.*PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T));
	temp4 = (float)(0.5*(1. - cos(2.*PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T)));
	
	if(mode == 1)
	{
		UpperMovement[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*temp1);
		UpperMovement[LSP] = (float)(-pSharedMemory->ShoulderPitchAmp*temp1);

		//v_AngPos[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*temp1);
		//v_AngPos[LSP] = (float)(-pSharedMemory->ShoulderPitchAmp*temp1);
	}
	else if((mode == 2) || (mode == 3))
	{
		UpperMovement[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*temp2);
		UpperMovement[LSP] = (float)(-pSharedMemory->ShoulderPitchAmp*temp2);

		UpperMovement[RSR] = (float)(pSharedMemory->ShoulderRollAmp*temp4);
		UpperMovement[LSR] = (float)(-pSharedMemory->ShoulderRollAmp*temp4);

		UpperMovement[REB] = (float)(pSharedMemory->ElbowAmp*temp4);
		UpperMovement[LEB] = (float)(pSharedMemory->ElbowAmp*temp4);

		//v_AngPos[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*temp2);
		//v_AngPos[LSP] = (float)(-pSharedMemory->ShoulderPitchAmp*temp2);
		
		//v_AngPos[RSR] = (float)(pSharedMemory->ShoulderRollAmp*temp4);
		//v_AngPos[LSR] = (float)(-pSharedMemory->ShoulderRollAmp*temp4);
	}
	else if(mode == 4)
	{
		//v_AngPos[RSP] = (float)(-pSharedMemory->ShoulderPitchAmp*temp1);
		//v_AngPos[LSP] = (float)(pSharedMemory->ShoulderPitchAmp*temp1);
		//v_AngPos[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*(1.-temp1));
		//v_AngPos[LSP] = (float)(pSharedMemory->ShoulderPitchAmp*(-1.+temp1));

		UpperMovement[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*(1.-temp1));
		UpperMovement[LSP] = (float)(pSharedMemory->ShoulderPitchAmp*(-1.+temp1));
	}
	else
	{
		UpperMovement[RSP] = (float)0.;
		UpperMovement[LSP] = (float)0.;

		UpperMovement[RSR] = (float)0.;
		UpperMovement[LSR] = (float)0.;

		UpperMovement[REB] = (float)0.;
		UpperMovement[LEB] = (float)0.;

		//v_AngPos[RSP] = (float)0.;
		//v_AngPos[LSP] = (float)0.;
		
		//v_AngPos[RSR] = (float)0.;
		//v_AngPos[LSR] = (float)0.;
	}

	/*
	v_AngPos[RSP] = (float)(pSharedMemory->ShoulderPitchAmp*0.5*(1. - cos(2.*PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T)));
	v_AngPos[RSR] = -(float)(pSharedMemory->ShoulderRollAmp*0.5*(1. - cos(2.*PI*pSharedMemory->ShoulderRollHz*time*DELTA_T)));

	v_AngPos[LSP] = -(float)(pSharedMemory->ShoulderPitchAmp*0.5*(1. - cos(2.*PI*pSharedMemory->ShoulderPitchHz*time*DELTA_T)));
	v_AngPos[LSR] = (float)(pSharedMemory->ShoulderRollAmp*0.5*(1. - cos(2.*PI*pSharedMemory->ShoulderRollHz*time*DELTA_T)));
	*/
}

void	PROF_Hand_Shake(long time)
{
	float tp1;

	tp1 = (float)(pSharedMemory->HandAmp*0.5*(1. - cos(2.*PI*pSharedMemory->HandFreq*time*DELTA_T)));
	
	v_AngPos[RF1] = tp1;
	v_AngPos[RF2] = tp1;
	v_AngPos[RF3] = tp1;
	v_AngPos[RF4] = tp1;
	v_AngPos[RF5] = tp1;

	v_AngPos[LF1] = tp1;
	v_AngPos[LF2] = tp1;
	v_AngPos[LF3] = tp1;
	v_AngPos[LF4] = tp1;
	v_AngPos[LF5] = tp1;
}

void	PROF_LFingerMotion1(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;
	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + FING2_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING2_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING2_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING2_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion2_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	// set local time to 0 at first initialization
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion2_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion3_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(80.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(80.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion3_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(80.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(80.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion4_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING2_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING2_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING2_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion4_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING2_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING2_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING2_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion5_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion5_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion6_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion6_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion7_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_B*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_A*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_A*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_LFingerMotion7_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1_A*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1_B*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1_B*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[LF1] = v_AngPos[LF1];
			v_oldAngPos[LF2] = v_AngPos[LF2];
			v_oldAngPos[LF3] = v_AngPos[LF3];
			v_oldAngPos[LF4] = v_AngPos[LF4];
			v_oldAngPos[LF5] = v_AngPos[LF5];
		}
	}
}

void	PROF_RFingerMotion1(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;
	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + FING2_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING2_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING2_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING2_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion2_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion2_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion3_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(80.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(80.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion3_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(80.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(80.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion4_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING2_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING2_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING2_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion4_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING2_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING2_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING2_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion5_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion5_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion6_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion6_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}


void	PROF_RFingerMotion7_A(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);
	
	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_A*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_B*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_A*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_A*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_A*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}

void	PROF_RFingerMotion7_B(long start_time, long stop_time)	
{
	static long local_time;
	static int local_flag = 0;
	float tmp_res[5];
	long local_during;
	float tp_portion;

	local_during = stop_time - start_time;

	tp_portion = (float)(local_during/100.);

	if(local_flag == 0)
	{
		local_time = 0;
		local_flag = 1;
	}

	if(local_flag == 1)
	{
		local_time++;
		FTN_half_1_cos(1., local_time, 0, local_during, 0, (int)(50.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos(1., local_time, 0, local_during, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1_B*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1_A*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1_B*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1_B*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1_B*tmp_res[4]);

		if(local_time >= local_during) 
		{
			local_flag = 0;

			v_oldAngPos[RF1] = v_AngPos[RF1];
			v_oldAngPos[RF2] = v_AngPos[RF2];
			v_oldAngPos[RF3] = v_AngPos[RF3];
			v_oldAngPos[RF4] = v_AngPos[RF4];
			v_oldAngPos[RF5] = v_AngPos[RF5];
		}
	}
}


void	PROF_MotionPlay1(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[1] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			//////////
			//for(i=20;i<29;i++)
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			//LOCALoldJntAng[31] = MotionHipAngPos[1];
			//LOCALoldJntAng[37] = MotionHipAngPos[0];

			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			/*
			FTN_half_1_cos( Adjust[0],time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-Adjust[0],time,T-100,100,0,0,&result2[0]);
			result[0] = result1[0]+result2[0];


			FTN_half_1_cos( Adjust[3],time,    0,100,0,0,&result1[3]);
			FTN_half_1_cos(-Adjust[3],time,T-100,100,0,0,&result2[3]);
			result[3] = result1[3]+result2[3];
			
			FTN_half_1_cos( Adjust[4],time,    0,100,0,0,&result1[4]);
			FTN_half_1_cos(-Adjust[4],time,T-100,100,0,0,&result2[4]);
			result[4] = result1[4]+result2[4];
			
			FTN_half_1_cos( Adjust[5],time,    0,100,0,0,&result1[5]);
			FTN_half_1_cos(-Adjust[5],time,T-100,100,0,0,&result2[5]);
			result[5] = result1[5]+result2[5];
			
			FTN_half_1_cos( Adjust[6],time,    0,100,0,0,&result1[6]);
			FTN_half_1_cos(-Adjust[6],time,T-100,100,0,0,&result2[6]);
			result[6] = result1[6]+result2[6];
			
			FTN_half_1_cos( Adjust[9],time,    0,100,0,0,&result1[9]);
			FTN_half_1_cos(-Adjust[9],time,T-100,100,0,0,&result2[9]);
			result[9] = result1[9]+result2[9];
			
			FTN_half_1_cos( Adjust[10],time,    0,100,0,0,&result1[10]);
			FTN_half_1_cos(-Adjust[10],time,T-100,100,0,0,&result2[10]);
			result[10] = result1[10]+result2[10];
			
			FTN_half_1_cos( Adjust[11],time,    0,100,0,0,&result1[11]);
			FTN_half_1_cos(-Adjust[11],time,T-100,100,0,0,&result2[11]);
			result[11] = result1[11]+result2[11];
			
			FTN_half_1_cos( Adjust[12],time,    0,100,0,0,&result1[12]);
			FTN_half_1_cos(-Adjust[12],time,T-100,100,0,0,&result2[12]);
			result[12] = result1[12]+result2[12];
			
			

			FTN_half_1_cos( Adjust[15],time,    0,100,0,0,&result1[15]);
			FTN_half_1_cos(-Adjust[15],time,T-100,100,0,0,&result2[15]);
			result[15] = result1[15]+result2[15];
			*/
			/*
			v_AngPos[RSP] = DefalutUpper[RSP] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];// + result[ 9];	// R-Shoulder Pitch	
			v_AngPos[RSR] = DefalutUpper[RSR] + pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			v_AngPos[RSY] = DefalutUpper[RSY] + pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			v_AngPos[REB] = DefalutUpper[REB] + pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			v_AngPos[LSP] = DefalutUpper[LSP] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];// + result[ 3];	// L-Shoulder Pitch
			v_AngPos[LSR] = DefalutUpper[LSR] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			v_AngPos[LSY] = DefalutUpper[LSY] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			v_AngPos[LEB] = DefalutUpper[LEB] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			v_AngPos[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			*/

			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];// + result[ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];// + result[ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			MotionHipAngPos[0] = MotionHipAngPos[1] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime,DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime,0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime,0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[1] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}	
	}
}
void	PROF_MotionPlay2(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 2;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			/*
			FTN_half_1_cos( Adjust[0],time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-Adjust[0],time,T-100,100,0,0,&result2[0]);
			result[0] = result1[0]+result2[0];

			FTN_half_1_cos( Adjust[15],time,    0,100,0,0,&result1[15]);
			FTN_half_1_cos(-Adjust[15],time,T-100,100,0,0,&result2[15]);
			result[15] = result1[15]+result2[15];
			*/
			
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];// + result[ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];// + result[ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk

			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];

			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];
			
			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];

			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}
void	PROF_MotionPlay3(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 3;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));
			
			pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][30]=(float)result[0];
			pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)result[1];
			pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)time;
			
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10] + result[0];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[ 0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4] - result[ 0];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];

			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay4(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 4;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
		
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

			FTN_half_1_cos( 1.0f,time, 1700,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time, 2300,100,0,0,&result2[1]);
			result[1] = (float)(20.*(result1[1]+result2[1]));

			// Finger Motion //
			if((time >= 5) && (time <80)) {PROF_RFingerMotion4_A(5, 80); PROF_LFingerMotion4_A(5, 80);}
			if((time >= 500) && (time <585)) {PROF_RFingerMotion4_B(500, 585); PROF_LFingerMotion4_B(500, 585);}

			if((time >= 590) && (time <650)) {PROF_RFingerMotion2_A(590, 650); PROF_LFingerMotion2_A(590, 650);}
			if((time >= 800) && (time <870)) {PROF_RFingerMotion2_B(800, 870); PROF_LFingerMotion2_B(800, 870);}

			if((time >= 875) && (time <950)) {PROF_RFingerMotion4_A(875, 950); PROF_LFingerMotion4_A(875, 950);}
			if((time >= 1350) && (time <1430)) {PROF_RFingerMotion4_B(1350, 1430); PROF_LFingerMotion4_B(1350, 1430);}
			
			if((time >= 1675) && (time <1820)) {PROF_RFingerMotion3_A(1675, 1820);}
			if((time >= 1825) && (time <1900)) {PROF_RFingerMotion3_B(1825, 1900);}

			if((time >= 2340) && (time <2425)) {PROF_RFingerMotion4_A(2340, 2425); PROF_LFingerMotion4_A(2340, 2425);}
			if((time >= 3300) && (time <3375)) {PROF_RFingerMotion4_B(3300, 3375); PROF_LFingerMotion4_B(3300, 3375);}

			if((time >= 3400) && (time <3600)) {PROF_RFingerMotion3_A(3400, 3600);}
			if((time >= 3625) && (time <3750)) {PROF_RFingerMotion3_B(3625, 3750);}

			if((time >= 3790) && (time <3875)) {PROF_RFingerMotion4_A(3790, 3875); PROF_LFingerMotion4_A(3790, 3875);}
			if((time >= 4160) && (time <4235)) {PROF_RFingerMotion4_B(4160, 4235); PROF_LFingerMotion4_B(4160, 4235);}

			if((time >= 4250) && (time <4365)) {PROF_RFingerMotion2_A(4250, 4365); PROF_LFingerMotion2_A(4250, 4365);}
			if((time >= 4585) && (time <4650)) {PROF_RFingerMotion2_B(4585, 4650); PROF_LFingerMotion2_B(4585, 4650);}

						
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0] + result[1];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10] + result[0];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0] + result[1];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4] - result[0];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];

			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay5(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 5;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			/*
			FTN_half_1_cos( Adjust[0],time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-Adjust[0],time,T-100,100,0,0,&result2[0]);
			result[0] = result1[0]+result2[0];

			FTN_half_1_cos( Adjust[15],time,    0,100,0,0,&result1[15]);
			FTN_half_1_cos(-Adjust[15],time,T-100,100,0,0,&result2[15]);
			result[15] = result1[15]+result2[15];
			*/

			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));
			
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];// + result[ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];// + result[ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			/*
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];
			*/
			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];

			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay6(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 6;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			/*
			FTN_half_1_cos( Adjust[0],time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-Adjust[0],time,T-100,100,0,0,&result2[0]);
			result[0] = result1[0]+result2[0];

			FTN_half_1_cos( Adjust[15],time,    0,100,0,0,&result1[15]);
			FTN_half_1_cos(-Adjust[15],time,T-100,100,0,0,&result2[15]);
			result[15] = result1[15]+result2[15];
			*/
			
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];// + result[ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];// + result[ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];
			
			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];

			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay7(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];
	
	MotionNo = 7;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			// user modified code /////////////////////////////////////////////////////////
			
			/*
			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,100,100,0,0,&result2[0]);
			res[0] = (float)(20.*(result1[0]+result2[0]));
			
			FTN_half_1_cos(1.0f,time,    200,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time,300,100,0,0,&result2[1]);
			res[1] = (float)(-20.*(result1[1]+result2[1]));
			*/

			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,300,100,0,0,&result2[0]);
			res[0] = (float)(20.*(result1[0]+result2[0]));

			
			FTN_1_cos(1.0f, time, 100,200,0,0,&result1[1]);
			res[1] = (float)(-40.*result1[1]);
			

			///End of the user modified code ////////////////////////////////////////////

			UpperMovement[RSP] = (float)0.;	// R-Shoulder Pitch	
			UpperMovement[RSR] = (float)0.;// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = (float)0.;// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = (float)0.;	// L-Shoulder Pitch
			UpperMovement[LSR] = (float)0.;// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = (float)0.;// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = (float)0.;// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = (float)0.;// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = (float)0.;
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = (float)0.;

			UpperMovement[NKY] = res[0] + res[1];
			UpperMovement[NK1] = (float)0.;
			UpperMovement[NK2] = (float)0.;
			
			MotionHipAngPos[0] = (float)0.;// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay8(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 8;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay9(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 9;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay10(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 10;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			// ---------=====[ Start edit ]====-----------

			// Define angles and variables

			float res_buff[3];	

			// start worked fine for end salute
			/*
					// Buffer for results
			float RSP_Angle0 = 110.;	// define right sholder pitch angle
			float RSY_Angle0 = 50.;		// define right sholder yaw angle
			float REB_Angle0 = 100.;	// define right elbow bend angle
			float RSR_Angle0 = 30.;		// right sholder angle start

			float RSP_Angle1 = 110.;	// right sholder pitch part 2
			float RSY_Angle1 = 50.;		// right sholder yaw part 2
			float REB_Angle1 = 60.;		// right elbo bend part 2
			float RSR_Angle1 = 10.;		// right sholder roll part 2
			*/  
			// end worked fine for end salute

			float RSP_Angle0 = 130.;	// right sholder pitch part 1
			float RSY_Angle0 = 50.;		// right sholder yaw part 1
			float REB_Angle0 = 75.;		// right elbo bend part 1
			float RSR_Angle0 = 10.;		// right sholder roll part 1

			float RSP_Angle1 = 110.;	// right sholder pitch part 2
			float RSY_Angle1 = 50.;		// right sholder yaw part 2
			float REB_Angle1 = 30.;		// right elbo bend part 2
			float RSR_Angle1 = 10.;		// right sholder roll part 2


			long salute_start0 = 50;		// salute start time
			long salute_rise_time = 20;		// how fast hubo salutes
			long salute_hold_time = 200;	// how long hubo holds salute out
			long salute_finish_time = 70;	// finish rise period

			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			if(time == 10)		// Open all fingers and closes thumb
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (5 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (5 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (5 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (5 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (5 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			
/*
			FTN_half_1_cos(-1, time,(salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[0]);		// raise right sholder pitch
			//FTN_half_1_cos(-1, time, 150, 30, 0, 0, &res_buff[1]);
			//res[RSP] = (float)((90.0*res_buff[0])+(90.0*res_buff[1]));
			res[RSP] = (float)(RSP_Angle0+(RSP_Angle0*res_buff[0]));
			*/
			FTN_half_1_cos(-1, time, salute_start0, salute_rise_time, 0, 0, &res_buff[0]);		// right sholder pitch
			FTN_half_1_cos(-1, time, (salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[RSP] = (float)((RSP_Angle0+(RSP_Angle0-RSP_Angle1)*res_buff[0])+RSP_Angle1*res_buff[1]);
			/*
			FTN_half_1_cos(-1, time,(salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[0]);		// yaw sholder
			res[RSY] = (float)(RSY_Angle0+RSY_Angle0*res_buff[0]);
*/
			FTN_half_1_cos(-1, time, salute_start0, salute_rise_time, 0, 0, &res_buff[0]);		// yaw sholder
			FTN_half_1_cos(-1, time, (salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[RSY] = (float)((RSY_Angle0+(RSY_Angle0-RSY_Angle1)*res_buff[0])+RSY_Angle1*res_buff[1]);

			FTN_half_1_cos(-1, time, salute_start0, salute_rise_time, 0, 0, &res_buff[0]);		// bend elbow
			FTN_half_1_cos(-1, time, (salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[REB] = (float)((REB_Angle0+(REB_Angle0-REB_Angle1)*res_buff[0])+REB_Angle1*res_buff[1]);

			FTN_half_1_cos(-1, time, salute_start0, salute_rise_time, 0, 0, &res_buff[0]);		// Right sholder roll
			FTN_half_1_cos(-1, time, (salute_start0+salute_rise_time+salute_hold_time), salute_finish_time, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 135, 15, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[RSR] = (float)((RSR_Angle0+(RSR_Angle0-RSR_Angle1)*res_buff[0])+RSR_Angle1*res_buff[1]);


			UpperMovement[RSP] = res[RSP];
			UpperMovement[RSR] = res[RSR];
			UpperMovement[RSY] = res[RSY];
			UpperMovement[REB] = res[REB];
			UpperMovement[LSP] = (float)0.0;
			UpperMovement[LSR] = (float)0.0;
			UpperMovement[LSY] = (float)0.0;
			UpperMovement[LEB] = (float)0.0;
			UpperMovement[WST] = (float)0.0;
			UpperMovement[RWY] = (float)0.0;
			UpperMovement[RW1] = (float)0.0;
			UpperMovement[RW2] = (float)0.0;
			UpperMovement[LWY] = (float)0.0;
			UpperMovement[LW1] = (float)0.0;
			UpperMovement[LW2] = (float)0.0;

			MotionHipAngPos[0] = (float)0.0;
			MotionHipAngPos[1] = MotionHipAngPos[0];

			// ---------=====[ End edit ]====-----------
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay11(int T, char MotionStop)
{
		static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 11;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			// ---------=====[ Start edit ]====-----------
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
					

			FTN_half_1_cos( 1.0f,time,    0,15,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time, 15,15,0,0,&result2[0]);
			res[0] = (float)(10.*(result1[0]+result2[0]));
			//res[1] = (float)(10.*(result1[0]+result2[0]));
		
/*
			FTN_half_1_cos(1.0f,time,    300,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time,700,100,0,0,&result2[1]);
			res[1] = (float)(90.*(result1[1]+result2[1]));*/
/*
			if(time == 1)		
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (3 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 100)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (3 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 200)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (3 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 300)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (3 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 400)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (3 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 500)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 600)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (3 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 700)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (3 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 800)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (3 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 900)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (3 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 1000)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (3 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 1100)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
*/
			

			UpperMovement[RSP] = (float)45;//res[0];//res[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = (float)0.;// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = res[0];//(float)0.;//res[0] + res[2];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = (float)0;//res[1];//(float)0.;	// L-Shoulder Pitch
			UpperMovement[LSR] = (float)0.;// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = (float)0.;// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = (float)0.;// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = (float)0.; // res[1];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = (float)0.; //-UpperMovement[RW1];
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = (float)0.; //-UpperMovement[RW1];

			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			// ---------=====[ End edit ]====-----------
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}

}

void	PROF_MotionPlay12(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 12;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay13(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 13;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay14(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 14;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay15(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 15;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,200,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-200,200,0,0,&result2[0]);
			result[0] = (float)(10.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9] + result[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + result[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay16(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	result[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 16;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					result[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,150,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,160,150,0,0,&result2[0]);
			result[0] = (float)(-20.*(result1[0]+result2[0]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15] + result[0];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay17(int T, char MotionStop)
{
	
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];
	
	MotionNo = 17;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			// user modified code /////////////////////////////////////////////////////////
			
			/*
			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,100,100,0,0,&result2[0]);
			res[0] = (float)(20.*(result1[0]+result2[0]));
			
			FTN_half_1_cos(1.0f,time,    200,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time,300,100,0,0,&result2[1]);
			res[1] = (float)(-20.*(result1[1]+result2[1]));
			*/

			FTN_half_1_cos( 1.0f,time,    100,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,    200,100,0,0,&result2[0]);
			FTN_half_1_cos( 1.0f,time,    400,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time,    500,100,0,0,&result2[1]);
			res[0] = (float)(90.*(result1[0]+result2[0]+result1[1]+result2[1]));

			
			FTN_half_1_cos(-1.0f,time,    100,100,0,0,&result1[2]);
			FTN_half_1_cos( 1.0f,time,    200,100,0,0,&result2[2]);
			FTN_half_1_cos(-1.0f,time,    400,100,0,0,&result1[3]);
			FTN_half_1_cos( 1.0f,time,    500,100,0,0,&result2[3]);
			res[1] = (float)(90.*(result1[2]+result2[2]+result1[3]+result2[3]));

			///End of the user modified code ////////////////////////////////////////////

			UpperMovement[RSP] = (float)0.;	// R-Shoulder Pitch	
			UpperMovement[RSR] = res[0];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = (float)0.;// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = (float)0.;	// L-Shoulder Pitch
			UpperMovement[LSR] = res[1];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = (float)0.;// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = (float)0.;// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = (float)0.;// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = (float)0.;
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = (float)0.;

			UpperMovement[NKY] = (float)0.;
			UpperMovement[NK1] = (float)0.;
			UpperMovement[NK2] = (float)0.;
			
			MotionHipAngPos[0] = (float)0.;// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}


void	PROF_MotionPlay18(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 18;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			if(time == 1)		
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (3 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 100)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (3 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 100)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (3 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 200)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (3 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 300)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (3 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 400)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (3 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 500)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 600)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (3 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 700)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (3 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 800)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (3 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 900)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (3 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 1000)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (3 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 1100)	
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}

			

			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay19(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 19;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			if(time == 130)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (5 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (1 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (1 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (1 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (1 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 150)	// 
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (2 & 0x0F);
				Local_TxData[4]=0x10 | (7 & 0x0F);
				Local_TxData[5]=0x10 | (4 & 0x0F);
				Local_TxData[6]=0x10 | (4 & 0x0F);
				Local_TxData[7]=0x10 | (7 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 250)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-150)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (2 & 0x0F);
				Local_TxData[4]=0x00 | (7 & 0x0F);
				Local_TxData[5]=0x00 | (4 & 0x0F);
				Local_TxData[6]=0x00 | (4 & 0x0F);
				Local_TxData[7]=0x00 | (7 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-100)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (3 & 0x0F);
				Local_TxData[4]=0x00 | (5 & 0x0F);
				Local_TxData[5]=0x00 | (3 & 0x0F);
				Local_TxData[6]=0x00 | (3 & 0x0F);
				Local_TxData[7]=0x00 | (5 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-20)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
	

		
			UpperMovement[RSP] = (float)0.;//pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = (float)0.;//pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;//pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = (float)0.;//pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = -UpperMovement[LW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay20(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 20;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			
			FTN_half_1_cos( 1.0f,time,    0,150,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-150,150,0,0,&result2[0]);
			res[0] = (float)(-10.*(result1[0] + result2[0]));
			res[1] = (float)(-30.*(result1[0] + result2[0]));

			FTN_1_cos(1.0f,time,    200,100,0,0,&result1[1]);
			FTN_1_cos(1.0f,time,300,100,0,0,&result2[1]);
			FTN_1_cos(1.0f,time,400,100,0,0,&result1[2]);
			res[2] = (float)(13.*(result1[1] + result2[1] + result1[2]));
					
		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0] + res[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			UpperMovement[NKY] = res[1];
			UpperMovement[NK1] = res[2];
			UpperMovement[NK2] = -res[2];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}


void	PROF_MotionPlay21(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];

	MotionNo = 21;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,110,150,0,0,&result2[0]);
			FTN_half_1_cos( 1.0f,time,    270,100,0,0,&result1[1]);
			res[0] = (float)(20.*(result1[0] + 2.*result2[0] + result1[1]));

		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0] + res[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			UpperMovement[NKY] = res[0];
			UpperMovement[NK1] = (float)0.;
			UpperMovement[NK2] = (float)0.;

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay22(int T, char MotionStop)
{
		static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 22;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			// ---------=====[ Start edit ]====-----------

			// Define angles and variables

			float res_buff[3];			// Buffer for results

			//Working values but hand too low
			/* 
		
			float RSP_Angle0 = 110.;		// define right sholder pitch angle
			float RSY_Angle0 = 50.;		// define right sholder yaw angle
			float REB_Angle0 = 100.;		// define right elbow bend angle
			float RSR_Angle0 = 30.;		// define right sholder roll angle
			*/  // end working with hand too low

			float RSP_Angle0 = 130.;	// right sholder pitch part 2
			float RSY_Angle0 = 50.;		// right sholder yaw part 2
			float REB_Angle0 = 75.;		// right elbo bend part 2
			float RSR_Angle0 = 10.;		// right sholder roll part 2

			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];

			// start Hand move
			/*
			
			if(time == 10)		// Open all fingers and closes thumb
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (5 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (5 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (5 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (5 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (5 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			*/
			// end hand move

			FTN_half_1_cos(1, time, 50, 100, 0, 0, &res_buff[0]);		// raise right sholder pitch
			//FTN_half_1_cos(-1, time, 150, 30, 0, 0, &res_buff[1]);
			//res[RSP] = (float)((90.0*res_buff[0])+(90.0*res_buff[1]));
			res[RSP] = (float)((RSP_Angle0*res_buff[0]));

			FTN_half_1_cos(1, time, 50, 100, 0, 0, &res_buff[0]);		// yaw sholder
			res[RSY] = (float)(RSY_Angle0*res_buff[0]);

			FTN_half_1_cos(1, time, 50, 100, 0, 0, &res_buff[0]);		// bend elbow
			//FTN_half_1_cos(-1, time, 135, 15, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[REB] = (float)((REB_Angle0*res_buff[0]));

			FTN_half_1_cos(1, time, 50, 100, 0, 0, &res_buff[0]);		// Sholder roll
			//FTN_half_1_cos(-1, time, 135, 15, 0, 0, &res_buff[1]);
			//FTN_half_1_cos(-1, time, 150, 15, 0, 0, &res_buff[2]);
			//res[REB] = (float)((90.0*res_buff[0])+(45.0*res_buff[1])+(45.0*res_buff[2]));
			res[RSR] = (float)((RSR_Angle0*res_buff[0]));


			UpperMovement[RSP] = res[RSP];
			UpperMovement[RSR] = res[RSR];
			UpperMovement[RSY] = res[RSY];
			UpperMovement[REB] = res[REB];
			UpperMovement[LSP] = (float)0.0;
			UpperMovement[LSR] = (float)0.0;
			UpperMovement[LSY] = (float)0.0;
			UpperMovement[LEB] = (float)0.0;
			UpperMovement[WST] = (float)0.0;
			UpperMovement[RWY] = (float)0.0;
			UpperMovement[RW1] = (float)0.0;
			UpperMovement[RW2] = (float)0.0;
			UpperMovement[LWY] = (float)0.0;
			UpperMovement[LW1] = (float)0.0;
			UpperMovement[LW2] = (float)0.0;

			MotionHipAngPos[0] = (float)0.0;
			MotionHipAngPos[1] = MotionHipAngPos[0];

			// ---------=====[ End edit ]====-----------
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}

}

void	PROF_MotionPlay23(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 23;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			if(time == 20)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (4 & 0x0F);		// 1st
				Local_TxData[4]=0x00 | (1 & 0x0F);		// 5th
				Local_TxData[5]=0x00 | (1 & 0x0F);		// 4th
				Local_TxData[6]=0x00 | (1 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (1 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 50)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (6 & 0x0F);
				Local_TxData[4]=0x00 | (1 & 0x0F);
				Local_TxData[5]=0x00 | (1 & 0x0F);
				Local_TxData[6]=0x00 | (1 & 0x0F);
				Local_TxData[7]=0x10 | (6 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 100)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (7 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 130)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-150)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (6 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-110)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (5 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (5 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-50)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (2 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (2 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-20)
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			
		
			FTN_half_1_cos( 1.0f,time,    0,150,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,T-150,150,0,0,&result2[0]);
			res[0] = (float)(30.*(result1[0] + result2[0]));
		
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3] + res[0];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6] + res[0];// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay24(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	//unsigned char Local_TxData[8];

	MotionNo = 24;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			/*
			if(time == 130)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (5 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (1 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (1 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (1 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (1 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 150)	// 
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (2 & 0x0F);
				Local_TxData[4]=0x10 | (7 & 0x0F);
				Local_TxData[5]=0x10 | (4 & 0x0F);
				Local_TxData[6]=0x10 | (4 & 0x0F);
				Local_TxData[7]=0x10 | (7 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 250)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-200)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (2 & 0x0F);
				Local_TxData[4]=0x00 | (7 & 0x0F);
				Local_TxData[5]=0x00 | (4 & 0x0F);
				Local_TxData[6]=0x00 | (4 & 0x0F);
				Local_TxData[7]=0x00 | (7 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-150)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (3 & 0x0F);
				Local_TxData[4]=0x00 | (5 & 0x0F);
				Local_TxData[5]=0x00 | (3 & 0x0F);
				Local_TxData[6]=0x00 | (3 & 0x0F);
				Local_TxData[7]=0x00 | (5 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == T-70)	// stop to grip on
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (0 & 0x0F);
				Local_TxData[4]=0x00 | (0 & 0x0F);
				Local_TxData[5]=0x00 | (0 & 0x0F);
				Local_TxData[6]=0x00 | (0 & 0x0F);
				Local_TxData[7]=0x00 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			*/

			// Finger Motion //
			if((time >= 100) && (time <200)) {PROF_RFingerMotion4_A(100, 200);}
			if((time >= (T-150)) && (time < (T-50))) {PROF_RFingerMotion4_B(T-150, T-50);}


			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[LSR] = -pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[RSP] = (float)0.;
			UpperMovement[RSR] = (float)0.;
			UpperMovement[RSY] = (float)0.;
			UpperMovement[REB] = (float)0.;
		/*
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
		*/	
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = 0.;
			UpperMovement[RW1] = 0.;
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = 0.;
			UpperMovement[LW1] = 0.;
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay25(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 25;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			if(time == 1)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (3 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 100)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (3 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 300)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (3 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 400)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (3 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 500)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (3 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 600)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 700)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x00 | (3 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 800)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x00 | (3 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 900)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x00 | (3 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 1000)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x00 | (3 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 1100)		// grip on fingers in order to make scissor pose
			{
				Local_TxData[0]=EJMC5;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);		// 1st
				Local_TxData[4]=0x10 | (0 & 0x0F);		// 5th
				Local_TxData[5]=0x10 | (0 & 0x0F);		// 4th
				Local_TxData[6]=0x10 | (0 & 0x0F);		// 3rd
				Local_TxData[7]=0x10 | (0 & 0x0F);		// 2nd
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
	
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay26(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 26;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			if(time == 20)		// grip on fingers except the thumb
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (3 & 0x0F);
				Local_TxData[4]=0x00 | (3 & 0x0F);
				Local_TxData[5]=0x00 | (2 & 0x0F);
				Local_TxData[6]=0x00 | (2 & 0x0F);
				Local_TxData[7]=0x00 | (3 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 300)	// stop to grip on
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x00 | (1 & 0x0F);
				Local_TxData[4]=0x00 | (1 & 0x0F);
				Local_TxData[5]=0x00 | (1 & 0x0F);
				Local_TxData[6]=0x00 | (1 & 0x0F);
				Local_TxData[7]=0x00 | (1 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			

			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay27(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 27;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			
			if(time == 20)		// grip off a thumb
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (5 & 0x0F);
				Local_TxData[4]=0x10 | (5 & 0x0F);
				Local_TxData[5]=0x10 | (3 & 0x0F);
				Local_TxData[6]=0x10 | (3 & 0x0F);
				Local_TxData[7]=0x10 | (5 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			if(time == 75)		// grip off a thumb
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (6 & 0x0F);
				Local_TxData[5]=0x10 | (6 & 0x0F);
				Local_TxData[6]=0x10 | (6 & 0x0F);
				Local_TxData[7]=0x10 | (6 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			else if(time == 90)	// stop to grip off
			{
				Local_TxData[0]=EJMC4;
				Local_TxData[1]=PwmCMD;
				Local_TxData[2]=0x01;
	
				Local_TxData[3]=0x10 | (0 & 0x0F);
				Local_TxData[4]=0x10 | (0 & 0x0F);
				Local_TxData[5]=0x10 | (0 & 0x0F);
				Local_TxData[6]=0x10 | (0 & 0x0F);
				Local_TxData[7]=0x10 | (0 & 0x0F);
				CanSendMsg(1, CMD_TXDF, Local_TxData, 8, 0);
			}
			

			/*
			UpperMovement[RSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 9];	// R-Shoulder Pitch	
			UpperMovement[RSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][10];// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][11];// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = pSharedMemory->UpBody_MTN_CAP_Data[time][12];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 3];	// L-Shoulder Pitch
			UpperMovement[LSR] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 4];// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 5];// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 6];// + result[ 6];	// L-Elbow	Pitch		
			
			//UpperMovement[WST] = DefalutUpper[WST] + pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			UpperMovement[WST] = pSharedMemory->UpBody_MTN_CAP_Data[time][ 0];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][13];
			UpperMovement[RW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][14];
			UpperMovement[RW2] = -UpperMovement[RW1];
			
			UpperMovement[LWY] = pSharedMemory->UpBody_MTN_CAP_Data[time][7];
			UpperMovement[LW1] = pSharedMemory->UpBody_MTN_CAP_Data[time][8];
			UpperMovement[LW2] = -UpperMovement[RW1];

			MotionHipAngPos[0] = pSharedMemory->UpBody_MTN_CAP_Data[time][15];// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			*/
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay28(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];
	
	MotionNo = 28;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
		
			// user modified code /////////////////////////////////////////////////////////
			
			/*
			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			FTN_half_1_cos(-1.0f,time,100,100,0,0,&result2[0]);
			res[0] = (float)(20.*(result1[0]+result2[0]));
			
			FTN_half_1_cos(1.0f,time,    200,100,0,0,&result1[1]);
			FTN_half_1_cos(-1.0f,time,300,100,0,0,&result2[1]);
			res[1] = (float)(-20.*(result1[1]+result2[1]));
			*/

			FTN_half_1_cos( 1.0f,time,    0,100,0,0,&result1[0]);
			//FTN_half_1_cos(-1.0f,time, 500,100,0,0,&result2[0]);
			res[0] = (float)(45.*(result1[0]));
			

			///End of the user modified code ////////////////////////////////////////////

			UpperMovement[RSP] = res[0];//(float)0.;	// R-Shoulder Pitch	
			UpperMovement[RSR] = (float)0.;// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = (float)0.;// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = (float)0.;	// L-Shoulder Pitch
			UpperMovement[LSR] = (float)0.;// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = (float)0.;// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = (float)0.;// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = (float)0.;// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = (float)0.;
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = (float)0.;

			UpperMovement[NKY] = (float)0;//res[0] + res[1];
			UpperMovement[NK1] = (float)0.;
			UpperMovement[NK2] = (float)0.;
			
			MotionHipAngPos[0] = (float)0.;// + result[15]; // Hip Pitch
			MotionHipAngPos[1] = MotionHipAngPos[0];
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime)	time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	PROF_MotionPlay29(int T, char MotionStop)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	unsigned int MotionNo;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	MotionNo = 29;	// user should change

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			// ---------=====[ Start edit ]====-----------
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			float thedeg;
			thedeg = 45.;

			FTN_half_1_cos( -1.0f,time,    0,100,0,0,&result1[0]);
			//FTN_half_1_cos(-1.0f,time, 500,100,0,0,&result2[0]);
			res[0] = (float)(thedeg*(result1[0]))+thedeg;
			//res[1] = (float)(10.*(result1[0]+result2[0]));
		

			//FTN_half_1_cos(1.0f,time,    300,100,0,0,&result1[1]);
			//FTN_half_1_cos(-1.0f,time,700,100,0,0,&result2[1]);
			//res[1] = (float)(90.*(result1[1]+result2[1]));
			

			UpperMovement[RSP] = res[0];//res[0];	// R-Shoulder Pitch	
			UpperMovement[RSR] = (float)0.;// + result[10];	// R-Shoulder Roll	
			UpperMovement[RSY] = (float)0.;// + result[11];	// R-Shoulder Yaw
			UpperMovement[REB] = (float)0.;//res[0] + res[2];// + result[12];	// R-Elbow	Pitch
			
			UpperMovement[LSP] = (float)0.;	// L-Shoulder Pitch
			UpperMovement[LSR] = (float)0.;// + result[ 4];	// L-Shoulder Roll
			UpperMovement[LSY] = (float)0.;// + result[ 5];	// L-Shoulder Yaw
			UpperMovement[LEB] = (float)0.;// + result[ 6];	// L-Elbow	Pitch		
			
			UpperMovement[WST] = (float)0.; // res[1];// + result[ 0];	// Trunk
			
			UpperMovement[RWY] = (float)0.;
			UpperMovement[RW1] = (float)0.;
			UpperMovement[RW2] = (float)0.; //-UpperMovement[RW1];
			
			UpperMovement[LWY] = (float)0.;
			UpperMovement[LW1] = (float)0.;
			UpperMovement[LW2] = (float)0.; //-UpperMovement[RW1];

			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			// ---------=====[ End edit ]====-----------
			//////////
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

//####################################### PTM DEMO gesture motions start here ###################################################################33

// General purpose functions used to simplify math
float ArraySum(float array1[],int l)
{
	float arrsum=0;
	for(int n=0;n<l;n++)
	{
		arrsum+=array1[n];
	}
	return arrsum;
}


void	Motion_RaiseRightHand(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {130,10,15,30,-80,0,0,0,0,0,0,0,0,0};  //14 element array of motion amplitudes
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output1[2];
			float Result1;
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 125,76, 0, 0, &Output1[1]);
					RightHand_ExtendFingers(5, 75,time,1);
					RightHand_ExtendFingers(125, 76,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,65, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 85,65, 0, 0, &Output1[1]);
					RightHand_ExtendFingers(5, 65,time,1);
					RightHand_ExtendFingers(85, 65,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[1]);
					//if((time >= 5) && (time < 100)) {PROF_RFingerMotion2_A(5, 100);}
					//if((time >= 200) && (time < 295)) {PROF_RFingerMotion2_B(200, 295);}
					RightHand_ExtendFingers(5, 100,time,1);
					RightHand_ExtendFingers(200, 100,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result1=Amplitudes1[n]*(Output1[0]+Output1[1]); //find paths for each step (sum
				UpperMovement[k]=Result1;  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
} 

void	Motion_RaiseRightArm(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {20,65,20,-5,35,0,0,0,0,0,0,0,0,0};  //14 element array of motion amplitudes
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output1[2];
			float Result1;
			
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 125,76, 0, 0, &Output1[1]);
					RightHand_GripAll(5,70,time,1);
					RightHand_GripAll(125,70,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,50, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 70,50, 0, 0, &Output1[1]);
					RightHand_GripAll(5,50,time,1);
					RightHand_GripAll(70,45,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[1]);
					RightHand_GripAll(5,95,time,1);
					RightHand_GripAll(200,95,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result1=Amplitudes1[n]*(Output1[0]+Output1[1]); //find paths for each step (sum
				UpperMovement[k]=Result1;  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_RightArmCircle(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {20,45,20,-5,35,0,0,0,0,0,0,0,0,0};  //lift arm forward
			float Amplitudes2[] = {-40, 0,0,0,0,0,0,0,0,0,0,0,0,0};  //arm rotates up 
			float Amplitudes3[] = {  0,40,0,0,0,0,0,0,0,0,0,0,0,0};  //arm rotates back
			//updated to increase amplitude of circle and make it center properly
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output1[10];
			float Result[10];
			
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 75,50, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 125,50, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 175,50, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 225,50, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 100,50, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 150,50, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 200,50, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 250,50, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 300,60, 0, 0, &Output1[9]);
					RightHand_ExtendFingers(5,75,time,1);
					RightHand_ExtendFingers(300,55,time,-1);
					break;					
				case 2:
					FTN_half_1_cos(1.0f, time, 0,50, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 50,30, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 80,30, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 110,30, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 140,30, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 65,30, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 95,30, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 125,30, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 155,30, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 185,55, 0, 0, &Output1[9]);
					RightHand_ExtendFingers(5,45,time,1);
					RightHand_ExtendFingers(185,50,time,-1);
					break;	
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 100,100, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 300,100, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 400,100, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 150,100, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 250,100, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 350,100, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 450,100, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 550,110, 0, 0, &Output1[9]);
					RightHand_ExtendFingers(5,95,time,1);
					RightHand_ExtendFingers(550,100,time,-1);
					break;	
			}
			
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output1[0]);
				Result[1]=Amplitudes2[n]*(Output1[1]);
				Result[2]=Amplitudes2[n]*(Output1[2]);
				Result[3]=Amplitudes2[n]*(Output1[3]);
				Result[4]=Amplitudes2[n]*(Output1[4]);
				Result[5]=Amplitudes3[n]*(Output1[5]);
				Result[6]=Amplitudes3[n]*(Output1[6]);
				Result[7]=Amplitudes3[n]*(Output1[7]);
				Result[8]=Amplitudes3[n]*(Output1[8]);
				Result[9]=Amplitudes1[n]*(Output1[9]);

				UpperMovement[k]=ArraySum(Result,10);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

// Left arm gestures
void	Motion_RaiseLeftHand(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {0,0,0,0,0,0,0,120,-8,30,25,45,0,-6};  //14 element array of motion amplitudes
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output1[2];
			float Result1;
			
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 125,76, 0, 0, &Output1[1]);
					LeftHand_ExtendFingers(5,70,time,1);
					LeftHand_ExtendFingers(125,70,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,65, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 85,65, 0, 0, &Output1[1]);
					LeftHand_ExtendFingers(5,60,time,1);
					LeftHand_ExtendFingers(85,60,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[1]);
					LeftHand_ExtendFingers(5,95,time,1);
					LeftHand_ExtendFingers(200,95,time,-1);
					break;	
			}
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result1=Amplitudes1[n]*(Output1[0]+Output1[1]); //find paths for each step (sum
				UpperMovement[k]=Result1;  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
} 

void	Motion_RaiseLeftArm(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {0,0,0,0,0,0,0,30,-75,30,-10,45,0,-6};  //14 element array of motion amplitudes
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output1[2];
			float Result1;
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 125,76, 0, 0, &Output1[1]);
					LeftHand_GripAll(5,70,time,1);
					LeftHand_GripAll(125,70,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,50, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 70,50, 0, 0, &Output1[1]);
					LeftHand_GripAll(5,45,time,1);
					LeftHand_GripAll(70,45,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[1]);
					LeftHand_GripAll(5,95,time,1);
					LeftHand_GripAll(200,95,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result1=Amplitudes1[n]*(Output1[0]+Output1[1]); //find paths for each step (sum
				UpperMovement[k]=Result1;  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_LeftArmCircle(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {0,0,0,0,0,0,0, 20,-45,30,-10,45,0,-6};  //lift arm forward
			float Amplitudes2[] = {0,0,0,0,0,0,0,-40,  0, 0,  0, 0,0, 0};  //arm rotates up 
			float Amplitudes3[] = {0,0,0,0,0,0,0,  0,-40, 0,  0, 0,0, 0};  //arm rotates back
			//updated to increase amplitude of circle and make it center properly
			
			float Output1[10];
			float Result[10];
			
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,75, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 75,50, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 125,50, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 175,50, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 225,50, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 100,50, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 150,50, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 200,50, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 250,50, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 300,60, 0, 0, &Output1[9]);
					LeftHand_GripAll(5,70,time,1);
					LeftHand_GripAll(300,55,time,-1);
					break;					
				case 2:
					FTN_half_1_cos(1.0f, time, 0,50, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 50,30, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 80,30, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 110,30, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 140,30, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 65,30, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 95,30, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 125,30, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 155,30, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 185,55, 0, 0, &Output1[9]);
					LeftHand_GripAll(5,45,time,1);
					LeftHand_GripAll(185,50,time,-1);
					break;	
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output1[0]);
					//X cycle
					FTN_half_1_cos(1.0f, time, 100,100, 0, 0, &Output1[1]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output1[2]);
					FTN_half_1_cos(1.0f, time, 300,100, 0, 0, &Output1[3]);
					FTN_half_1_cos(-1.0f, time, 400,100, 0, 0, &Output1[4]);
					//Y cycle
					FTN_half_1_cos(1.0f, time, 150,100, 0, 0, &Output1[5]);
					FTN_half_1_cos(-1.0f, time, 250,100, 0, 0, &Output1[6]);
					FTN_half_1_cos(1.0f, time, 350,100, 0, 0, &Output1[7]);
					FTN_half_1_cos(-1.0f, time, 450,100, 0, 0, &Output1[8]);
					
					FTN_half_1_cos(-1.0f, time, 550,110, 0, 0, &Output1[9]);
					LeftHand_GripAll(5,95,time,1);
					LeftHand_GripAll(550,105,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output1[0]);
				Result[1]=Amplitudes2[n]*(Output1[1]);
				Result[2]=Amplitudes2[n]*(Output1[2]);
				Result[3]=Amplitudes2[n]*(Output1[3]);
				Result[4]=Amplitudes2[n]*(Output1[4]);
				Result[5]=Amplitudes3[n]*(Output1[5]);
				Result[6]=Amplitudes3[n]*(Output1[6]);
				Result[7]=Amplitudes3[n]*(Output1[7]);
				Result[8]=Amplitudes3[n]*(Output1[8]);
				Result[9]=Amplitudes1[n]*(Output1[9]);

				UpperMovement[k]=ArraySum(Result,10);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

//Gestures for right arm only

void	Motion_TouchHead(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];

	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable
			//FIX THIS...redo from poser
			float Amplitudes1[] = {130,19,40,78,40,5,-5,0,0,0,0,0,0,0};
			float Amplitudes2[] = {  0, 0, 0, 6, 4,0,-5,0,0,0,0,0,0,0};
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output[6];
			float Result[6];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,90, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 90,25, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 115,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 145,25, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 170,30, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output[5]);
					LeftHand_ExtendFingers(5,85,time,1);
					LeftHand_ExtendFingers(200,95,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,70, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 70,20, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 90,25, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 115,20, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 135,25, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 160,71, 0, 0, &Output[5]);
					LeftHand_ExtendFingers(5,65,time,1);
					LeftHand_ExtendFingers(160,70,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,120, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 120,30, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 150,40, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 190,30, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 220,40, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 260,121, 0, 0, &Output[5]);
					LeftHand_ExtendFingers(5,115,time,1);
					LeftHand_ExtendFingers(260,115,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]);
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes2[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes1[n]*(Output[5]);
				UpperMovement[k]=ArraySum(Result,6);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_TouchNose(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {140,24,60,85,50,0,3,0,0,0,0,0,0,0};
			float Amplitudes2[] = {0,0,0,0,0,0,-5,0,0,0,0,0,0,0};
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			float Output[6];
			float Result[6];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,90, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 90,25, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 115,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 145,25, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 170,30, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 200,100, 0, 0, &Output[5]);
					RightHand_Index(0,85,time,1);
					RightHand_Index(200,95,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,70, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 70,20, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 90,25, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 115,20, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 135,25, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 160,71, 0, 0, &Output[5]);
					RightHand_Index(0,65,time,1);
					RightHand_Index(160,65,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,120, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 120,30, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 150,40, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 190,30, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 220,40, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 260,121, 0, 0, &Output[5]);
					RightHand_Index(0,115,time,1);
					RightHand_Index(260,115,time,-1);
					break;	
			}
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]);
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes2[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes1[n]*(Output[5]);
				UpperMovement[k]=ArraySum(Result,6);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}
void	Motion_TipHat(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //14 element array of motion amplitudes
			float Amplitudes2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //14 element array of motion amplitudes
			float Amplitudes3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //14 element array of motion amplitudes
			// Define additional amplitudes INCREMENTALLY, so you can just add it all together at the end
			
			float Output[6];
			float Result[6];
			/*
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					
					
					break;
				case 2:
					
					
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,50, 0, 0, &Output[1]);
					FTN_half_1_cos(1.0f, time, 150,50, 0, 0, &Output[2]);
					FTN_half_1_cos(-1.0f, time, 200,50, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 250,50, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 300,100, 0, 0, &Output[5]);
					break;	
			}
			*/
			FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,50, 0, 0, &Output[1]);
					FTN_half_1_cos(1.0f, time, 150,50, 0, 0, &Output[2]);
					FTN_half_1_cos(-1.0f, time, 200,50, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 250,50, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 300,100, 0, 0, &Output[5]);
			//define additional steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); //find paths for each step (sum
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes3[n]*(Output[2]);
				Result[3]=Amplitudes3[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes1[n]*(Output[5]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,6);  //sum all results to get actual movement
			}
			

			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_RubStomach(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = { 50, 30, 80, 45,20,0,-5,0,0,0,0,0,0,0};
			float Amplitudes2[] = {  7,-25,  0, 20, 0,0,0,0,0,0,0,0,0,0};
			float Amplitudes3[] = { 20,-24,  5,-16, 5,0,0,0,0,0,0,0,0,0};
			float Amplitudes4[] = {  3, 14,-10, 15, 0,0,0,0,0,0,0,0,0,0};
			float Amplitudes5[] = {-30, 35,  5,-19,-5,0,0,0,0,0,0,0,0,0};
			//added pitch offset of about 20 degrees, since the position control seems to mess it up by that much
			
			float Output[6];
			float Result[6];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,70, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 70,50, 0, 0, &Output[1]);
					FTN_half_1_cos(1.0f, time, 110,50, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 150,50, 0, 0, &Output[3]);
					FTN_half_1_cos(1.0f, time, 190,50, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 240,69, 0, 0, &Output[5]);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,50, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 50,30, 0, 0, &Output[1]);
					FTN_half_1_cos(1.0f, time, 75,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 100,30, 0, 0, &Output[3]);
					FTN_half_1_cos(1.0f, time, 125,30, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 150,51, 0, 0, &Output[5]);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,60, 0, 0, &Output[1]);
					FTN_half_1_cos(1.0f, time, 150,60, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 200,60, 0, 0, &Output[3]);
					FTN_half_1_cos(1.0f, time, 250,50, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 300,99, 0, 0, &Output[5]);
					break;	
			}
			
			//define additional steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); //find paths for each step (sum
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes3[n]*(Output[2]);
				Result[3]=Amplitudes4[n]*(Output[3]);
				Result[4]=Amplitudes5[n]*(Output[4]);
				Result[5]=Amplitudes1[n]*(Output[5]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,6);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_ChooChoo(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = { 90,31,  0,75,20,1,0,0,0,0,0,0,0,0};
			float Amplitudes2[] = {-50, -7,-40, 7, 5,0,0,0,0,0,0,0,0,0};  //updated to not contract elbow as much
			
			float Output[6];
			float Result[6];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,85, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 85,40, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 130,40, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 165,40, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 200,40, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 235,71, 0, 0, &Output[5]);
					RightHand_GripAll(0,80,time,1);
					RightHand_GripAll(235,65,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,70, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 70,30, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 100,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 130,30, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 160,30, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 190,71, 0, 0, &Output[5]);
					RightHand_GripAll(0,65,time,1);
					RightHand_GripAll(190,65,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,50, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 150,50, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 200,50, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 250,50, 0, 0, &Output[4]);
					FTN_half_1_cos(-1.0f, time, 300,99, 0, 0, &Output[5]);
					RightHand_GripAll(0,95,time,1);
					RightHand_GripAll(300,95,time,-1);
					break;	
			}
			
			//define additonal steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); 
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes2[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes1[n]*(Output[5]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,6);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}



// Gestures involving both hands/arms
void	Motion_ClapHands(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {36,-10, 30, 40, 20,0,0,36,10,30,60,30,0,0};
			float Amplitudes2[] = { 7, -2, 17,  3,  0,0,0, 5, 2,14,-10,0,0,0};
			//updated to bring hands closer, fixed hanging problem (had the wrong amplitudes reffed)
			
			float Output[8];
			float Result[8];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,40, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 40,20, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 60,20, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 80,20, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 100,20, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 120,20, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 140,20, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 160,41, 0, 0, &Output[7]);
					RightHand_ExtendFingers(5,40,time,1);
					RightHand_ExtendFingers(160,40,time,-1);
					LeftHand_ExtendFingers(5,40,time,1);
					LeftHand_ExtendFingers(160,40,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,60, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 60,30, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 85,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 110,30, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 135,30, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 160,30, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 195,30, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 210,60, 0, 0, &Output[7]);
					RightHand_ExtendFingers(5,60,time,1);
					RightHand_ExtendFingers(210,60,time,-1);
					LeftHand_ExtendFingers(5,60,time,1);
					LeftHand_ExtendFingers(210,60,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,40, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 133,40, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 166,40, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 200,40, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 233,40, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 266,33, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 300,99, 0, 0, &Output[7]);
					RightHand_ExtendFingers(5,95,time,1);
					RightHand_ExtendFingers(300,95,time,-1);
					LeftHand_ExtendFingers(5,95,time,1);
					LeftHand_ExtendFingers(300,95,time,-1);
					break;	
			}
			
			//define additional steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); //find paths for each step (sum
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes2[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes2[n]*(Output[5]);
				Result[6]=Amplitudes2[n]*(Output[6]);
				Result[7]=Amplitudes1[n]*(Output[7]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,8);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_FlapArms(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			//float Amplitudes1[] = {25,70,35,95,0,0,0,25,-70,35,95,0,0,0};
			//reduce elbow swing, also look into shoulder yaw
			float Amplitudes1[] = {25,70,35,70,0,0,0,25,-70,35,70,0,0,0};
			float Amplitudes2[] = {0,-40,8,-5,0,0,0,0,40,8,-5,0,0,0};
			//Updated with higher initial height to clear bodywork, less elbow bend
			
			float Output[8];
			float Result[8];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,40, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 40,20, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 60,20, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 80,20, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 100,20, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 120,20, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 140,20, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 160,41, 0, 0, &Output[7]);
					RightHand_GripAll(0,40,time,1);
					RightHand_GripAll(160,40,time,-1);
					LeftHand_GripAll(0,40,time,1);
					LeftHand_GripAll(160,40,time,-1);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,60, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 60,30, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 85,30, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 110,30, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 135,30, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 160,30, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 195,30, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 210,60, 0, 0, &Output[7]);
					RightHand_GripAll(0,60,time,1);
					RightHand_GripAll(210,60,time,-1);
					LeftHand_GripAll(0,60,time,1);
					LeftHand_GripAll(210,60,time,-1);
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,100, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,40, 0, 0, &Output[1]);
					FTN_half_1_cos(-1.0f, time, 133,40, 0, 0, &Output[2]);
					FTN_half_1_cos(1.0f, time, 166,40, 0, 0, &Output[3]);
					FTN_half_1_cos(-1.0f, time, 200,40, 0, 0, &Output[4]);
					FTN_half_1_cos(1.0f, time, 233,40, 0, 0, &Output[5]);
					FTN_half_1_cos(-1.0f, time, 266,33, 0, 0, &Output[6]);
					FTN_half_1_cos(-1.0f, time, 300,99, 0, 0, &Output[7]);	
					RightHand_GripAll(0,100,time,1);
					RightHand_GripAll(300,95,time,-1);
					LeftHand_GripAll(0,100,time,1);
					LeftHand_GripAll(300,95,time,-1);
					break;	
			}
			//define additional steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); //find paths for each step (sum
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes2[n]*(Output[3]);
				Result[4]=Amplitudes2[n]*(Output[4]);
				Result[5]=Amplitudes2[n]*(Output[5]);
				Result[6]=Amplitudes2[n]*(Output[6]);
				Result[7]=Amplitudes1[n]*(Output[7]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,8);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

void	Motion_HandsOnHips(int T, char MotionStop,unsigned int MotionNo)
{
	static int time = 0;
	static int time1 = 0;
	static float ftime = 0.;

	unsigned int i;
	float	Adjust[NumOfMotionJoint];
	float	LOCALresultMTRAng[TOTAL_MTR_NUM];
	float	res[NumOfMotionJoint];
	float	result1[NumOfMotionJoint];
	float	result2[NumOfMotionJoint];
	
	static float LOCALoldJntAng[TOTAL_MTR_NUM];
	static float LOCALJntAng[TOTAL_MTR_NUM];
	unsigned char Local_TxData[8];

	if(MotionStop == 0)
	{
		if(time>=T)
		{
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			time=0;
		}
		else if((time>=0)&&(time<=T))
		{
			time1 = 0;
			ftime = 0.;
			
			if(time==0)
			{
				for(i=0;i<NumOfMotionJoint;i++)
				{
					Adjust[i]  = 0.;
					res[i]  = 0.;
					result1[i] = 0.;
					result2[i] = 0.;
				}
				Adjust[3]  = 10.;
				Adjust[4]  = 10.;
			}
			
			for(i=RSP;i<LEB;i++)
			{
				LOCALoldJntAng[i] = v_AngPos[i];
			}
			LOCALoldJntAng[RHP] = MotionHipAngPos[1];
			LOCALoldJntAng[LHP] = MotionHipAngPos[0];
			
			
			//############### Begin motion definition here ########################
			// Standard addresses, simply loop through each of 14 Joint Locations to assign
			int JointLocations[]={RSP,RSR,RSY,REB,RWY,RW1,RW2,LSP,LSR,LSY,LEB,LWY,LW1,LW2};
			int k=0; //internal increment variable

			float Amplitudes1[] = {20,0,0,0,0,0,0,20,0,0,0,0,0,0};  //14 element array of motion amplitudes
			float Amplitudes2[] = {-25,40,70,65,45,0,10,-25,-40,70,65,-45,10,0};  //14 element array of motion amplitudes
			//added a bit of roll axis offset to lift arms and clear bodywork
			
			float Output[4];
			float Result[4];
			switch(pSharedMemory->JaemiSaysMotionSpeed)
			{
				case 1:
					FTN_half_1_cos(1.0f, time, 0,60, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 40,80, 0, 0, &Output[1]);
					//short pause
					FTN_half_1_cos(-1.0f, time, 160,80, 0, 0, &Output[2]);
					FTN_half_1_cos(-1.0f, time, 240,60, 0, 0, &Output[3]);
					break;
				case 2:
					FTN_half_1_cos(1.0f, time, 0,30, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 30,50, 0, 0, &Output[1]);
					//short pause
					FTN_half_1_cos(-1.0f, time, 100,50, 0, 0, &Output[2]);
					FTN_half_1_cos(-1.0f, time, 150,30, 0, 0, &Output[3]);
					
					break;
				case 0:
				default:
					FTN_half_1_cos(1.0f, time, 0,110, 0, 0, &Output[0]);
					FTN_half_1_cos(1.0f, time, 100,100, 0, 0, &Output[1]);

					FTN_half_1_cos(-1.0f, time, 300,110, 0, 0, &Output[2]);
					FTN_half_1_cos(-1.0f, time, 400,101, 0, 0, &Output[3]);
					break;	
			}
			//define additonal steps here
			
			for (int n=0;n<=13;n++)
			{
				k=JointLocations[n];  //Assign current index to temporary variable
				Result[0]=Amplitudes1[n]*(Output[0]); //find paths for each step (sum
				Result[1]=Amplitudes2[n]*(Output[1]);
				Result[2]=Amplitudes2[n]*(Output[2]);
				Result[3]=Amplitudes1[n]*(Output[3]);
				//specify additional steps here
				UpperMovement[k]=ArraySum(Result,4);  //sum all results to get actual movement
			}
			
			//############### End User Motion Code ########################
			
			
			MotionHipAngPos[0] = (float)0.;
			MotionHipAngPos[1] = MotionHipAngPos[0];
			for(i=RSP;i<LEB;i++)
			{
				LOCALJntAng[i] = v_AngPos[i];
			}
			LOCALJntAng[RHP] = MotionHipAngPos[1];
			LOCALJntAng[LHP] = MotionHipAngPos[0];
			time++;
		}
	}
	else if(MotionStop == 1)
	{
		ftime = (float)(time1/UpperMotionRecovertime);
		
		for(i=RSP;i<LEB;i++)
		{
			FTN_3poly(ftime,LOCALJntAng[i],(float)((LOCALJntAng[i]-LOCALoldJntAng[i])*UpperMotionRecovertime),DefalutUpper[i],0,&LOCALresultMTRAng[i]);
			v_AngPos[i]=LOCALresultMTRAng[i];
		}
		FTN_3poly(ftime,LOCALJntAng[RHP],(float)((LOCALJntAng[RHP]-LOCALoldJntAng[RHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[RHP]);
		MotionHipAngPos[1] = LOCALresultMTRAng[RHP];

		FTN_3poly(ftime,LOCALJntAng[LHP],(float)((LOCALJntAng[LHP]-LOCALoldJntAng[LHP])*UpperMotionRecovertime),0,0,&LOCALresultMTRAng[LHP]);
		MotionHipAngPos[0] = LOCALresultMTRAng[LHP];

		time = 0;
		if(time1<=UpperMotionRecovertime) time1++;
		else if(time1>=UpperMotionRecovertime)
		{
			pSharedMemory->MotionFlag[MotionNo] = FALSE;
			pSharedMemory->MotionFlagALL = 0;
			MotionHipAngPos[0] = 0.;
			MotionHipAngPos[1] = 0.;
			time=0;
			time1=0;
			ftime = 0.;
		}
	}
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Rob's experimental finger motions here $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void	LeftHand_Neutral(long start_time, long duration,long time,short direction)	
{
	// Neutral hand position (partially curled)
	long local_time=time-start_time;
	float tmp_res[5];
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[0]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[1]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[2]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[3]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + FING2*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING2*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING2*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING2*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		//update local positions
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}

void	LeftHand_GripAll(long start_time, long duration, long time, short direction)	
{
	// Close all fingers
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{

		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}

void	LeftHand_Sweep(long start_time, long duration, long time, short direction)	
{
	//Sweep open/closed fingers leading with the thumb
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(80.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(80.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}

void	LeftHand_ExtendFingers(long start_time, long duration,long time, short direction)	
{
	//Extend all fingers to flatten hand
	long local_time=time-start_time;
	float tmp_res[5]={0,0,0,0,0};
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	//Experimental reverse delay function
	//bool index=0-(bool)direction;
	//int delay[2];
	//delay[index]=
	//delay[index+1]=

	if(local_time>=0 && local_time<duration)
	{
		if(direction>0)
		{
			FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[0]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[1]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[2]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[3]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[4]);
		}
		else if(direction<0)
		{
			//reverse delays
			FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[0]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
			FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		}
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING2*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING2*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING2*tmp_res[4]);

	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}


void	LeftHand_ThumbIndex(long start_time, long duration, long time, short direction)	
{
	//Extend index and thumb, close others
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{

		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING2*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING2*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}

void	LeftHand_DevilHorns(long start_time, long duration, long time, short direction)	
{
	//extend index and pinky fingers
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}


void	LeftHand_Index(long start_time, long duration, long time, short direction)	
{
	//Extend index finger only
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[LF1] = (float)(v_oldAngPos[LF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[LF2] = (float)(v_oldAngPos[LF2] + FING1*tmp_res[1]);
		v_AngPos[LF3] = (float)(v_oldAngPos[LF3] + FING1*tmp_res[2]);
		v_AngPos[LF4] = (float)(v_oldAngPos[LF4] + FING1*tmp_res[3]);
		v_AngPos[LF5] = (float)(v_oldAngPos[LF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[LF1] = v_AngPos[LF1];
		v_oldAngPos[LF2] = v_AngPos[LF2];
		v_oldAngPos[LF3] = v_AngPos[LF3];
		v_oldAngPos[LF4] = v_AngPos[LF4];
		v_oldAngPos[LF5] = v_AngPos[LF5];
	}
}

//########################### - Right Hand - ##################################

void	RightHand_Neutral(long start_time, long duration,long time,short direction)	
{
	// Neutral hand position (partially curled)
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[0]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[1]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[2]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[3]);
		FTN_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + FING2*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING2*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING2*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING2*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		//update local positions
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}

void	RightHand_GripAll(long start_time, long duration, long time, short direction)	
{
	// Close all fingers
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{

		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}

void	RightHand_Sweep(long start_time, long duration, long time, short direction)	
{
	//Sweep open/closed fingers leading with the thumb
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(80.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), (int)(60.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(40.*tp_portion), (int)(40.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(60.*tp_portion), (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(80.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}

void	RightHand_ExtendFingers(long start_time, long duration,long time, short direction)	
{
	//Extend all fingers to flatten hand
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(20.*tp_portion), 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING2*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING2*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING2*tmp_res[4]);

	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}

void	RightHand_ThumbIndex(long start_time, long duration, long time, short direction)	
{
	//Extend index and thumb, close others
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{

		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, 0, &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING2*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING2*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}

void	RightHand_DevilHorns(long start_time, long duration, long time, short direction)	
{
	//extend index and pinky fingers
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}


void	RightHand_Index(long start_time, long duration, long time, short direction)	
{
	//Extend index finger only
	long local_time=time-start_time;
	float tmp_res[5];
	
	float tp_portion;
	tp_portion = (float)(duration/100.);
	
	if(local_time>=0 && local_time<duration)
	{
		FTN_half_1_cos((float)direction, local_time, 0, duration, (int)(50.*tp_portion), 0, &tmp_res[0]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[1]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[2]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[3]);
		FTN_half_1_cos((float)direction, local_time, 0, duration, 0, (int)(20.*tp_portion), &tmp_res[4]);
		
		v_AngPos[RF1] = (float)(v_oldAngPos[RF1] + 0.5*FING1*tmp_res[0]);
		v_AngPos[RF2] = (float)(v_oldAngPos[RF2] + FING1*tmp_res[1]);
		v_AngPos[RF3] = (float)(v_oldAngPos[RF3] + FING1*tmp_res[2]);
		v_AngPos[RF4] = (float)(v_oldAngPos[RF4] + FING1*tmp_res[3]);
		v_AngPos[RF5] = (float)(v_oldAngPos[RF5] + FING1*tmp_res[4]);
	}
	else if(local_time == duration) 
	{
		v_oldAngPos[RF1] = v_AngPos[RF1];
		v_oldAngPos[RF2] = v_AngPos[RF2];
		v_oldAngPos[RF3] = v_AngPos[RF3];
		v_oldAngPos[RF4] = v_AngPos[RF4];
		v_oldAngPos[RF5] = v_AngPos[RF5];
	}
}


