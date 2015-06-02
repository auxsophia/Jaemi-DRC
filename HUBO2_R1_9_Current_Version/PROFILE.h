#define		SWAY1				45//50	//50 //(750msec) //114(950msec and 850msec)
#define		LEG_UP_AMP			50 //35
#define		READY_LEG_UP_AMP	40	//10	//40, changed for straight walking
#define		READY_LEG_SIDE_AMP	4
#define		ALPHA				1.7
#define		ALPHA00				0
#define		ALPHA01				0
#define		ALPHA1				(SWAY1*2)
#define		BETA				0.5
#define		BETA00				0
#define		DELAY_Y				0
#define		DELAY_Y1			5*TS

#define		EITA				(0)//Must Be ZERO
#define		HIP_DELAY			0.2//(0.2)

#define		FOOTHEIGHT			30

#define		ANK2FRONT			153
#define		ANK2BACK			81
#define		ANK2BASE			83
#define		ANK2TOE				(174.1) // sqrt(ANK2FRONT*ANK2FRONT+ANK2BASE*ANK2BASE)
#define		ANK2TOEANGLE		28.5	// Deg

#define		KICKAng				12		//300mm 15 Degree      //5 Degree --> ankle angle
#define		LANDAng				-90	// scale of ankle angle

#define		UP07FACTOR			2*TS
#define		UP07TIME_FACTOR		-3*TS
#define		UP07TIME_FACTOR1	1*TS

#define	READYTIME	100*TS // 2 sec
#define	HOMETIME	200*TS // 2 sec
#define DSPTIME		3*TS//6
#define SUPPHEIGHT	0//4//2
#define ARM_CUTOFF	0.7


char PRF_RSteady3DSP(float Sway, float RBack, float RFront, float Side, float Rside, unsigned long Time, int start, int during);

char PRF_R_SSP_Static(float Sway, float Height, unsigned long Time, int start, int during);
char PRF_L_SSP_Static(float Sway, float Height, unsigned long Time, int start, int during);

char PRF_goLegXYZto(float Lx, float Ly, float Lz, float Rx, float Ry, float Rz, unsigned long time, unsigned int start, unsigned during);

char InvKine(float LPx, float LPy, float LPz, float LYaw, float RPx, float RPy, float RPz, float RYaw);
	// LegAngle[0~11] 조인트 각도 (전역 변수)
char FrdKine(float LTh1, float LTh2, float LTh3, float LTh4, float LTh5, float LTh6,
			 float RTh1, float RTh2, float RTh3, float RTh4, float RTh5, float RTh6);
	// LPx, LPy, LPz, RPx, RPy, RPz 위치 (전역 변수)
void AngPosInput(unsigned char mode);
void CartPosInput(unsigned char mode);

void InitPROFVar();
void WalkReady(long	Time);
void Home(long	Time);

void v_CartBackUP();

void RCurveFactors(int during, float X_step, float Y_step);
void LCurveFactors(int during, float X_step, float Y_step);

void RSwayFactor(int during, float Rforward, float RSide);
void LSwayFactor(int during, float Lforward, float LSide);

void RAnkKick(float MAX, long time, long start, long during);
void RAnkKick1(float MAX, float RZpos, long time, long start, int during, int delay1, int delay2);
void RAnkKick2(float MAX, long time, long start, int during, int delay1, int delay2);

void LAnkKick(float MAX, long time, long start, long during);
void LAnkKick1(float MAX, float LZpos, long time, long start, int during, int delay1, int delay2);
void LAnkKick2(float MAX, long time, long start, int during, int delay1, int delay2);

float PRF_C1_cosRecover(float oldData, float diffData, unsigned int Time, unsigned int start, unsigned int during);
void LAnkLand(float Ang, long time, long start, long during, char reset);
void RAnkLand(float Ang, long time, long start, long during, char reset);
void RAnkLandSTOP(long time, long start, long during);
void LAnkLandSTOP(long time, long start, long during);

void	PROF_ArmShake(long Time, int mode, int start, int during, float stride);
float	PROF_ArmShake_Walk(long Time,unsigned char Flag);
void	PROF_MotionPlay1(int T, char MotionStop);
void	PROF_MotionPlay2(int T, char MotionStop);
void	PROF_MotionPlay3(int T, char MotionStop);
void	PROF_MotionPlay4(int T, char MotionStop);	// short taichi
void	PROF_MotionPlay5(int T, char MotionStop);	// 첫인사
void	PROF_MotionPlay6(int T, char MotionStop);
void	PROF_MotionPlay7(int T, char MotionStop);
void	PROF_MotionPlay8(int T, char MotionStop);
void	PROF_MotionPlay9(int T, char MotionStop);
void	PROF_MotionPlay10(int T, char MotionStop);		// grip off flower
void	PROF_MotionPlay11(int T, char MotionStop);
void	PROF_MotionPlay12(int T, char MotionStop);
void	PROF_MotionPlay13(int T, char MotionStop);
void	PROF_MotionPlay14(int T, char MotionStop);
void	PROF_MotionPlay15(int T, char MotionStop);
void	PROF_MotionPlay16(int T, char MotionStop);		// say hello
void	PROF_MotionPlay17(int T, char MotionStop);		// M1
void	PROF_MotionPlay18(int T, char MotionStop);		// M2
void	PROF_MotionPlay19(int T, char MotionStop);		// M3
void	PROF_MotionPlay20(int T, char MotionStop);		// M4
void	PROF_MotionPlay21(int T, char MotionStop);		// M5
void	PROF_MotionPlay22(int T, char MotionStop);		// M6
void	PROF_MotionPlay23(int T, char MotionStop);		// M7
void	PROF_MotionPlay24(int T, char MotionStop);		// M8
void	PROF_MotionPlay25(int T, char MotionStop);		// M9
void	PROF_MotionPlay26(int T, char MotionStop);		// M10
void	PROF_MotionPlay27(int T, char MotionStop);		// M11
void	PROF_MotionPlay28(int T, char MotionStop);		// M12
void	PROF_MotionPlay29(int T, char MotionStop);		// M13
void	PROF_Wrist_Shake(long time);
void	PROF_Shoulder_Shake(long time, int mode);
void	PROF_Hand_Shake(long time);
void	PROF_Wrist_Shake(long time, int mode);
void	PROF_Wrist_Shake1(long time, int mode);
void	PROF_Wrist_Shake2(long time, int mode);
void	PROF_WristConfigure1(long time);
void	PROF_WristConfigure2(long time);
// Function primitives for PTM Demo gestures
void 	Motion_RaiseRightHand(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_RaiseRightArm(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_RightArmCircle(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_RaiseLeftHand(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_RaiseLeftArm(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_LeftArmCircle(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_TouchHead(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_TouchNose(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_RubStomach(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_ChooChoo(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_TipHat(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_ClapHands(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_FlapArms(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_HandsOnHips(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_PointRight(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_PointLeft(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_PointBothLeftRight(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_Aux_Bend_Right_Elbow(int T, char MotionStop,unsigned int MotionNo);
void 	Motion_Aux_UNLV(int T, char MotionStop,unsigned int MotionNo);
void	Motion_Hello_World(int T, char MotionStop,unsigned int MotionNo);


// Finer motion function
void	PROF_LFingerMotion1(long start_time, long stop_time);
void	PROF_LFingerMotion2_A(long start_time, long stop_time);	// grip all fingers
void	PROF_LFingerMotion2_B(long start_time, long stop_time);	// recover 2 pose
void	PROF_LFingerMotion3_A(long start_time, long stop_time);	// grip all fingers in sweep motion, starting with thumb
void	PROF_LFingerMotion3_B(long start_time, long stop_time);	// recover 3 pose
void	PROF_LFingerMotion4_A(long start_time, long stop_time);	// extend all fingers
void	PROF_LFingerMotion4_B(long start_time, long stop_time);	// recover 4 pose
void	PROF_LFingerMotion5_A(long start_time, long stop_time);	// extend index finger & thumb (close others)
void	PROF_LFingerMotion5_B(long start_time, long stop_time);	// recover 5 pose
void	PROF_LFingerMotion6_A(long start_time, long stop_time);	// "devil horns"
void	PROF_LFingerMotion6_B(long start_time, long stop_time);	// recover 6 pose
void	PROF_LFingerMotion7_A(long start_time, long stop_time);	// point with just index finger
void	PROF_LFingerMotion7_B(long start_time, long stop_time);	// recover 7 pose
void	PROF_RFingerMotion1(long start_time, long stop_time);
void	PROF_RFingerMotion2_A(long start_time, long stop_time);	// grip pose
void	PROF_RFingerMotion2_B(long start_time, long stop_time);	// recover 2 pose
void	PROF_RFingerMotion3_A(long start_time, long stop_time);	// grip pose 각각 
void	PROF_RFingerMotion3_B(long start_time, long stop_time);	// recover 3 pose
void	PROF_RFingerMotion4_A(long start_time, long stop_time);	// 손 펴기 
void	PROF_RFingerMotion4_B(long start_time, long stop_time);	// recover 4 pose
void	PROF_RFingerMotion5_A(long start_time, long stop_time);	// 가위 pose 
void	PROF_RFingerMotion5_B(long start_time, long stop_time);	// recover 5 pose
void	PROF_RFingerMotion6_A(long start_time, long stop_time);	// 수화 pose 엄지,중지,약지 쥐고, 검지, 새끼 펴기 
void	PROF_RFingerMotion6_B(long start_time, long stop_time);	// recover 6 pose
void	PROF_RFingerMotion7_A(long start_time, long stop_time);	// 검지만 펴는 pose 
void	PROF_RFingerMotion7_B(long start_time, long stop_time);	// recover 7 pose

//Rob's modified finger motions

void	LeftHand_Neutral(long start_time, long stop_time,long time);
void	LeftHand_GripAll(long start_time, long stop_time, long time, bool direction);
void	LeftHand_Sweep(long start_time, long stop_time, long time, bool direction);
void	LeftHand_ExtendFingers(long start_time, long stop_time,long time, bool direction);
void	LeftHand_ThumbIndex(long start_time, long stop_time, long time, bool direction);
void	LeftHand_DevilHorns(long start_time, long stop_time, long time, bool direction);
void	LeftHand_Index(long start_time, long stop_time, long time, bool direction);
void	RightHand_Neutral(long start_time, long stop_time,long time);
void	RightHand_GripAll(long start_time, long stop_time, long time, bool direction);
void	RightHand_Sweep(long start_time, long stop_time, long time, bool direction);
void	RightHand_ExtendFingers(long start_time, long stop_time,long time, bool direction);
void	RightHand_ThumbIndex(long start_time, long stop_time, long time, bool direction);
void	RightHand_DevilHorns(long start_time, long stop_time, long time, bool direction);
void	RightHand_Index(long start_time, long stop_time, long time, bool direction);
