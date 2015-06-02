#define Init_Xzmp	10//15//(10)//10
#define Init_Yzmp	0

double CTRL_new_compen(float zmp, int zero);			
double CTRL_new_compenfwd(float zmp, int zero);			
double CTRL_autotuneankle(float Rfty_Lfty_err,int zero); // Right Ankle Pitch Balance at ZMP initialization
double CTRL_INCL_Hip_Roll(float inclino_err, int zero);		// Ankle Z-Position Balansing at ZMP initailization
double CTRL_INCL_Ank_Pitch(float inclino_err, int zero);	// Body Balance by left and right ankle joint angle at ZMP initialization
void CTRL_VariableInit00();
float CTRL_saturation(float data,float limit);
float CTRL_dsp_compen_p_DEMO(float zmp,int zero);
float CTRL_dsp_compen_p(float zmp,int zero); // same with new_compen_r4
float CTRL_dsp_compen_p2(float zmp,int zero); // same with new_compen_r4
float CTRL_dsp_compen_p_1(float zmp,int zero); // same with new_compen_r4
float CTRL_dsp_compen_p2_1(float zmp,int zero); // same with new_compen_r4
float CTRL_land_damp_fwd(float theta_ref,float torque,int zero,int test);
float CTRL_land_damp_fwdR(float theta_ref,float torque,int zero,int test);
float CTRL_land_damp_fwdL(float theta_ref,float torque,int zero,int test);
float CTRL_RF_land_damp_roll(float theta_ref,float torque,int zero,int test);	// Right Ankle Landing Orientation Controller [Roll]
float CTRL_LF_land_damp_roll(float theta_ref,float torque,int zero,int test);	// Left Ankle Landing Orientation Controller [Roll]
float CTRL_INCL_Ank_Pitch_Walking(float inclino_err, int zero);
float CTRL_Torq_Zero_LAR(float Torq, float Ref_Torq, int zero);
float CTRL_Torq_Zero_RAR(float Torq, float Ref_Torq, int zero);
float CTRL_new_compenfwd_kirk(float ZMP, float Ref_ZMP, int zero);				// ZMP initialization X-dir
float CTRL_new_compen_kirk(float ZMP, float Ref_ZMP, int zero);					// ZMP initialization Y-dir
float CTRL_SSP_ZMP_CON_Y(float Ref_zmp, float zmp, int zero);
float CTRL_SSP_ZMP_CON_X(float Ref_zmp, float zmp, int zero);
float CTRL_SSP_ZMP_CON_LY(float Ref_zmp, float zmp, int zero);
float CTRL_SSP_ZMP_CON_RY(float Ref_zmp, float zmp, int zero);
float CTRL_SSP_ZMP_CON_LX(float Ref_zmp, float zmp, int zero);
float CTRL_SSP_ZMP_CON_RX(float Ref_zmp, float zmp, int zero);
float CTRL_ZMPAMP(float AvgZMP, float refAMP, int leftright);
float CTRL_INCL_Torso_Roll_Walking(float inclino_err, int zero);
float CTRL_TorsoInclLeftRoll(float Incl, float ref, char activate);
float CTRL_TorsoInclRightRoll(float Incl, float ref, char activate);
float CTRL_TorsoInclLeftPitch(float Incl, float ref, char activate);
float CTRL_TorsoInclRightPitch(float Incl, float ref, char activate);
// becool added function //
float Right_Ankle_Control_Roll(float theta, float vel, float ref);
float Right_Ankle_Control_Pitch(float theta, float vel, float ref);
float Left_Ankle_Control_Roll(float theta, float vel, float ref);
float Left_Ankle_Control_Pitch(float theta, float vel, float ref);
void Hip_Vib_Reduction(float vel);
float Right_Roll_Vib_Reduction(float vel, int no);
float Right_Roll_Vib(float vel, int no);
float Left_Roll_Vib(float vel, int no);
float Left_Roll_Vib_Reduction(float vel, int no);
float Right_SSP_ZMP_Y(float ref, float zmp, float u);
float Left_SSP_ZMP_Y(float ref, float zmp, float u);
float Right_SSP_ZMP_YA(float ref, float zmp);
float DSP_ZMP_Y(float ref, float zmp, int no, float I_gain);
float DSP_ZMP_X(float ref, float zmp, int no, float I_gain);

// kirk`s function
float angle_stiff_ds3(float theta_ref,float torque,int zero,int test);  // 한발지지 왼발목  Roll 방향 자세 제어기 
float angle_stiff_ds4(float theta_ref,float torque,int zero,int test);  // 한발지지 오른발목  Roll 방향 자세 제어기 
float angle_stiff_fwL(float theta_ref,float torque,int zero,int test);  // 한발지지 왼발목  Pitch 방향 자세 제어기 
float angle_stiff_fwR(float theta_ref,float torque,int zero,int test);  // 한발지지 오른발목  Pitch 방향 자세 제어기 
float land_damp_fwd(float theta_ref,float torque,int zero,int test);
float LF_land_damp_roll(float theta_ref,float torque,int zero,int test);
float RF_land_damp_roll(float theta_ref,float torque,int zero,int test);
float SSP_ZMP_CON_Y(float Ref_Yzmp, float Yzmp, int zero);
float SSP_ZMP_CON_X(float Ref_Xzmp, float Xzmp, int zero);
float BC_Y_Amp_Comp_M(float Zmp_Amp, float Ref_Zmp_Amp, int zero);
float BC_Y_Amp_Comp_W(float Zmp_Amp, float Ref_Zmp_Amp, float step_length, int zero);
float BC_Y_Amp_Comp_B(float Zmp_Amp, float Ref_Zmp_Amp, int zero);
float Torsion_mass_spring_damper_Mx(float Mx, int zero);	// shake hands function
float Torsion_mass_spring_damper_My(float My, int zero);	// shake hands function
float Wrist_mass_spring_damper_Fz(float Fz, int zero);		// shake hands function
float SSP_RF_ZMP_CON_Y(float Ref_Yzmp, float Yzmp, int zero);
float SSP_RF_ZMP_CON_X(float Ref_Xzmp, float Xzmp, int zero);