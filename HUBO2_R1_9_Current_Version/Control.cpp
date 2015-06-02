#include "Control.h"
#include "math.h"
#include "define.h"
#include "CAN.h"
#include "RTX.h"

extern	PSHARED_DATA	pSharedMemory;	// shared memory data

double CTRL_new_compen(float zmp, int zero)
{
	static double x1new,x2new, x1=0., x2=0.;
	const double a[2]={ 0.96443074097695, 0.00982108021084};
	const double b[2]={ 0.00982108021084, 0.00004940180507};
	const double c[2]={-1.14193058854734, 3.16569477323305};
	static double filt,tzmp,delfilt;
	
	
	x1new=a[0]*x1      + b[0]*zmp;
	x2new=a[1]*x1 + x2 + b[1]*zmp;
	
	//	30 = 0.9 x1  x2 + 0.01* 30
	if(zero == 0) {x1new = 0.;x2new = 0.;}
	
	if(x2new>20.0) { x2new=20.0; }
	else if(x2new<-20.0) { x2new=-20.0; }
	
	
	filt=c[0]*x1new + c[1]*x2new;
	/*
	if(filt>30.0)  {		delfilt=filt-30.0;
	filt=30.0;
	tzmp=zmp-1.2*delfilt;
	x1new=a[0]*x1      + b[0]*tzmp;
	x2new=a[1]*x1 + x2 + b[1]*tzmp;
	}
	else if(filt<-30.0) {	delfilt=filt+30.0;
	filt=-30.0;
	tzmp=zmp-1.2*delfilt;
	x1new=a[0]*x1      + b[0]*tzmp;
	x2new=a[1]*x1 + x2 + b[1]*tzmp;
	}
	*/
	x1=x1new;
	x2=x2new;
	
	return filt;
}

double CTRL_new_compenfwd(float zmp, int zero)
{
	static double x1new,x2new, x1=0., x2=0.;
	const double a[2]={ 0.96443074097695, 0.00982108021084};
	const double b[2]={ 0.00982108021084, 0.00004940180507};
	const double c[2]={-1.14193058854734, 3.16569477323305};
	static double filt,tzmp,delfilt;
	
	
	x1new=a[0]*x1      + b[0]*zmp;
	x2new=a[1]*x1 + x2 + b[1]*zmp;
	
	if(zero == 0) {x1new = 0.;x2new = 0.;}
	
	if(x2new>15.0) { x2new=15.0; }
	else if(x2new<-15.0) { x2new=-15.0; }
	
	
	filt=c[0]*x1new + c[1]*x2new;
	
	x1=x1new;
	x2=x2new;
	
	return filt;
}

double CTRL_autotuneankle(float Rfty_Lfty_err,int zero) // Integral controller 
{
	static double deltarh;
	static double sume=0.;
	
	double KI=0.00005;  // with KI 0.0003 KP 0.002 => sustained oscilation
	//double KI=0.0001;  // with KI 0.0003 KP 0.002 => sustained oscilation
	// with KI 0.0003 KP 0.    => satisfactoty
	// with KI 0.0001 => KIRK Setting
	deltarh=(0.*Rfty_Lfty_err+KI*sume);
	sume+=Rfty_Lfty_err;
	
	// temporary windup
	if(sume>5.0/KI) sume=5./KI;
	else if(sume<-5.0/KI) sume=-5./KI;
	
	if(deltarh>5.0) deltarh=5.;
	else if(deltarh<-5.0) deltarh=-5.;
	
	return deltarh;
}

double CTRL_INCL_Hip_Roll(float inclino_err, int zero)
{
	static double deltah;
	static double sume = 0.;
	
	double KI = 0.0004;
	deltah = -(0.1*inclino_err + KI*sume);
	
	sume += inclino_err;
	
	if(sume > 10.0/KI) sume = 10./KI;
	else if(sume < -10.0/KI) sume = -10./KI;
	
	if(deltah > 10.0) deltah = 10.0;
	else if(deltah < -10.0) deltah = -10.0;
	
	if(zero == 0) sume = 0.;
	
	return deltah;
}

double CTRL_INCL_Ank_Pitch(float inclino_err, int zero)
{
	static double deltah;
	static double sume = 0.;
	
	double KI = 0.0004;
	//double KI = 0.0008;
	deltah = -(0.1*inclino_err + KI*sume);
	
	sume += inclino_err;
	
	if(sume > 3.0/KI) sume = 3./KI;
	else if(sume < -3.0/KI) sume = -3./KI;
	
	if(deltah > 3.0) deltah = 3.0;
	else if(deltah < -3.0) deltah = -3.0;
	
	if(zero == 0) sume = 0.;
	
	return deltah;
}

void CTRL_VariableInit00()
{
	CTRL_new_compen(0., 0);
	CTRL_new_compenfwd(0., 0);
	CTRL_autotuneankle(0., 0); // Integral controller
	CTRL_INCL_Hip_Roll(0., 0);
	CTRL_INCL_Ank_Pitch(0., 0);
}

float CTRL_saturation(float data,float limit)
{
	if(data>limit) data=limit;
	else if(data<-limit)data=-limit;
	return data;
}


float CTRL_dsp_compen_p(float zmp,int zero) // same with new_compen_r4
{
	static double x1new,x2new,x3new, x1=0., x2=0.,x3=0.;
	
	static float filt,tzmp,delfilt;
	const float SAT_MM=20.;
	
	const double adm[9]={   0.77212260949428,  -1.89030083059839,  -5.37881650401726,   0.00882947259387,   0.99019291390146,  -0.02805049913090,   0.00004604565208,   0.00996670805815,   0.99990453936134};
	const double bdm[3] ={   0.00882947259387,   0.00004604565208,   0.00000015670122};
	const double cdm[3] ={  -0.62188015405947, -16.60806366969650, -97.18887813896150};
	
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3	 	+ bdm[0]*zmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 		+ bdm[1]*zmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 		+ bdm[2]*zmp;
	
	if(zero==0) { x1new=0.; x2new=0.; x3new=0.; }
	
	filt=(float)(cdm[0]*x1new+cdm[1]*x2new+cdm[2]*x3new);
	
	if(filt>SAT_MM)  {		delfilt=filt-SAT_MM;
	filt=SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	
	}
	else if(filt<-SAT_MM) {	delfilt=filt+SAT_MM;
	filt=-SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	}
	
	
	x1=x1new;	x2=x2new;	x3=x3new;
	
	return filt;
}
float CTRL_dsp_compen_p2(float zmp,int zero) // same with new_compen_r4
{
	static double x1new,x2new,x3new, x1=0., x2=0.,x3=0.;
	
	static float filt,tzmp,delfilt;
	const float SAT_MM=20.;
	
	const double adm[9]={   0.77212260949428,  -1.89030083059839,  -5.37881650401726,   0.00882947259387,   0.99019291390146,  -0.02805049913090,   0.00004604565208,   0.00996670805815,   0.99990453936134};
	const double bdm[3] ={   0.00882947259387,   0.00004604565208,   0.00000015670122};
	const double cdm[3] ={  -0.62188015405947, -16.60806366969650, -97.18887813896150};
	
	
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3	 	+ bdm[0]*zmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 		+ bdm[1]*zmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 		+ bdm[2]*zmp;
	
	if(zero==0) { x1new=0.; x2new=0.; x3new=0.; }
	
	filt=(float)(cdm[0]*x1new+cdm[1]*x2new+cdm[2]*x3new);
	
	if(filt>SAT_MM)  {		delfilt=filt-SAT_MM;
	filt=SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	
	}
	else if(filt<-SAT_MM) {	delfilt=filt+SAT_MM;
	filt=-SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	}
	
	
	x1=x1new;	x2=x2new;	x3=x3new;
	
	return filt;
}
float CTRL_dsp_compen_p_1(float zmp,int zero) // same with new_compen_r4
{
	static double x1new,x2new,x3new, x1=0., x2=0.,x3=0.;
	
	static float filt,delfilt;
	static double tzmp;
	const float SAT_MM=100.;
	
	const double adm[9]={   0.77212260949428,  -1.89030083059839,  -5.37881650401726,   0.00882947259387,   0.99019291390146,  -0.02805049913090,   0.00004604565208,   0.00996670805815,   0.99990453936134};
	const double bdm[3] ={   0.00882947259387,   0.00004604565208,   0.00000015670122};
	const double cdm[3] ={  -0.62188015405947, -16.60806366969650, -97.18887813896150};
	
	
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3	 	+ bdm[0]*zmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 		+ bdm[1]*zmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 		+ bdm[2]*zmp;
	
	if(zero==0) { x1new=0.; x2new=0.; x3new=0.; }
	
	filt=(float)(cdm[0]*x1new+cdm[1]*x2new+cdm[2]*x3new);
	
	if(filt>SAT_MM)  {		delfilt=filt-SAT_MM;
	filt=SAT_MM;
	tzmp=zmp-1.*delfilt;
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	
	}
	else if(filt<-SAT_MM) {	delfilt=filt+SAT_MM;
	filt=-SAT_MM;
	tzmp=zmp-1.*delfilt;
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	}
	
	
	x1=x1new;	x2=x2new;	x3=x3new;
	
	return filt;
}
float CTRL_dsp_compen_p2_1(float zmp,int zero) // same with new_compen_r4
{
	static double x1new,x2new,x3new, x1=0., x2=0.,x3=0.;
	
	static float filt,delfilt;
	static double tzmp;
	const float SAT_MM=100.;
	
	const double adm[9]={   0.77212260949428,  -1.89030083059839,  -5.37881650401726,   0.00882947259387,   0.99019291390146,  -0.02805049913090,   0.00004604565208,   0.00996670805815,   0.99990453936134};
	const double bdm[3] ={   0.00882947259387,   0.00004604565208,   0.00000015670122};
	const double cdm[3] ={  -0.62188015405947, -16.60806366969650, -97.18887813896150};
	
	
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3	 	+ bdm[0]*zmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 		+ bdm[1]*zmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 		+ bdm[2]*zmp;
	
	if(zero==0) { x1new=0.; x2new=0.; x3new=0.; }
	
	filt=(float)(cdm[0]*x1new+cdm[1]*x2new+cdm[2]*x3new);
	
	if(filt>SAT_MM)  {		delfilt=filt-SAT_MM;
	filt=SAT_MM;
	tzmp=zmp-1.*delfilt;
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	
	}
	else if(filt<-SAT_MM) {	delfilt=filt+SAT_MM;
	filt=-SAT_MM;
	tzmp=zmp-1.*delfilt;
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	}
	
	
	x1=x1new;	x2=x2new;	x3=x3new;
	
	return filt;
}
float CTRL_dsp_compen_p_DEMO(float zmp,int zero)
{
	static double x1new,x2new,x3new, x1=0., x2=0.,x3=0.;
	
	static float filt,tzmp,delfilt;
	const float SAT_MM=20.;
	
	const double adm[9] ={   0.77212260949428,  -1.89030083059839,  -5.37881650401726,   0.00882947259387,   0.99019291390146,
							-0.02805049913090,   0.00004604565208,   0.00996670805815,   0.99990453936134};
	const double bdm[3] ={   0.00882947259387,   0.00004604565208,   0.00000015670122};
	const double cdm[3] ={  -0.62188015405947, -16.60806366969650, -97.18887813896150};
	
	
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3	 	+ bdm[0]*zmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 		+ bdm[1]*zmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 		+ bdm[2]*zmp;
	
	if(zero==0) { x1new=0.; x2new=0.; x3new=0.; }
	
	filt=(float)(cdm[0]*x1new+cdm[1]*x2new+cdm[2]*x3new);
	
	if(filt>SAT_MM)  {		delfilt=filt-SAT_MM;
	filt=SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	
	}
	else if(filt<-SAT_MM) {	delfilt=filt+SAT_MM;
	filt=-SAT_MM;
	tzmp=(float)(zmp-1.*delfilt);
	x1new=adm[0]*x1 + adm[1]*x2+ adm[2]*x3 + bdm[0]*tzmp;
	x2new=adm[3]*x1 + adm[4]*x2+ adm[5]*x3 + bdm[1]*tzmp;
	x3new=adm[6]*x1 + adm[7]*x2+ adm[8]*x3 + bdm[2]*tzmp;
	}
	
	
	x1=x1new;	x2=x2new;	x3=x3new;
	
	return filt;
}

float CTRL_land_damp_fwd(float theta_ref,float torque,int zero,int test)
{
	
	static float x1new, x1=0.,y;
	static float stiffnessMKS=0.;
	static float pa=(float)0., pc=(float)0.015;
	static int offcontrolflag=0;
	
	pa=pc*stiffnessMKS;
	
	
	if(offcontrolflag==0)
	{
		if(torque<-0.1) torque+=(float)0.1;
		else if(torque<0.1) torque=0.;  // dead zone
		else torque-=(float)0.1;
		
		x1new=(float)((1.-pa*0.01)*x1 + (pc)*0.01*torque);
		if(x1new>0.1) x1new=(float)0.1;
		else if(x1new<-0.1) x1new=(float)-0.1;
		y=(float)(+57.295779513*x1new); // positive feedback
		
		x1=x1new;
	}
	
	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;	
}
float CTRL_land_damp_fwdR(float theta_ref,float torque,int zero,int test)
{
	
	static float x1new, x1=0.,y;
	static float stiffnessMKS=0.;
	static float pa=(float)0., pc=(float)0.008;//0.015;
	static int offcontrolflag=0;
	
	pa=pc*stiffnessMKS;
	
	
	if(offcontrolflag==0)
	{
		if(torque<-0.5) torque+=(float)0.5;
		else if(torque<0.5) torque=0.;  // dead zone
		else torque-=(float)0.5;
		
		x1new=(float)((1.-pa*DELTA_T)*x1 + (pc)*DELTA_T*torque);
		if(x1new>0.1) x1new=(float)0.1;
		else if(x1new<-0.1) x1new=(float)-0.1;
		y=(float)(+57.295779513*x1new); // positive feedback
		
		x1=x1new;
	}
	
	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;	
}
float CTRL_land_damp_fwdL(float theta_ref,float torque,int zero,int test)
{
	
	static float x1new, x1=0.,y;
	static float stiffnessMKS=0.;
	static float pa=(float)0., pc=(float)0.008;//0.015;
	static int offcontrolflag=0;
	
	pa=pc*stiffnessMKS;
	
	
	if(offcontrolflag==0)
	{
		if(torque<-0.5) torque+=(float)0.5;
		else if(torque<0.5) torque=0.;  // dead zone
		else torque-=(float)0.5;
		
		x1new=(float)((1.-pa*DELTA_T)*x1 + (pc)*DELTA_T*torque);
		if(x1new>0.1) x1new=(float)0.1;
		else if(x1new<-0.1) x1new=(float)-0.1;
		y=(float)(+57.295779513*x1new); // positive feedback
		
		x1=x1new;
	}
	
	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;	
}
float CTRL_RF_land_damp_roll(float theta_ref,float torque,int zero,int test)
{
	static float x1new, x1=0.,y;
	static float stiffnessMKS=0.;
	static float pa=(float)0., pc=(float)0.008;//0.015;
	
	static int offcontrolflag=0;
	
	pa=pc*stiffnessMKS;
	
	
	if(offcontrolflag==0)
	{
		if(torque<-0.5) torque+=(float)0.5;
		else if(torque<0.5) torque=0.;  // dead zone
		else torque-=(float)0.5;
		
		x1new=(float)((1.-pa*DELTA_T)*x1 + (pc)*DELTA_T*torque);
		if(x1new>0.1) x1new=(float)0.1;
		else if(x1new<-0.1) x1new=(float)-0.1;
		y=(float)(+57.295779513*x1new); // positive feedback
		
		x1=x1new;
	}
	
	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;
}

float CTRL_LF_land_damp_roll(float theta_ref,float torque,int zero,int test)
{	
	static float x1new, x1=0.,y;
	static float stiffnessMKS=0.;
	static float pa=(float)0., pc=(float)0.008;//0.015;	
	static int offcontrolflag=0;
	
	pa=pc*stiffnessMKS;
		
	if(offcontrolflag==0)
	{
		if(torque<-0.5) torque+=(float)0.5;
		else if(torque<0.5) torque=0.;  // dead zone
		else torque-=(float)0.5;
		
		x1new=(float)((1.-pa*DELTA_T)*x1 + (pc)*DELTA_T*torque);
		if(x1new>0.1) x1new=(float)0.1;
		else if(x1new<-0.1) x1new=(float)-0.1;
		y=(float)(+57.295779513*x1new); // positive feedback
		
		x1=x1new;
	}
	
	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;
}

float CTRL_INCL_Ank_Pitch_Walking(float inclino_err, int zero)
{
	static float deltah;
	static float sume = 0.;
	
	float KI = (float)0.001;
	deltah = (float)(-(0.2*inclino_err + KI*sume));
	
	sume += inclino_err;
	
	if(sume > 6.0/KI) sume = (float)(6./KI);
	else if(sume < -6.0/KI) sume = (float)(-6./KI);
	
	if(deltah > 6.0) deltah = 6.0;
	else if(deltah < -6.0) deltah = -6.0;
	
	if(zero == 0) sume = 0.;
	
	return deltah;
}


float CTRL_INCL_Torso_Roll_Walking(float inclino_err, int zero)
{
	static float deltah;
	static float sume = 0.;
	
	float KI = (float)0.003;
	deltah = (float)(-(1.5*inclino_err + KI*sume));
	
	sume += inclino_err;
	
	if(sume > 6.0/KI) sume = (float)(6./KI);
	else if(sume < -6.0/KI) sume = (float)(-6./KI);
	
	if(deltah > 6.0) deltah = 6.0;
	else if(deltah < -6.0) deltah = -6.0;
	
	if(zero == 0) sume = 0.;
	
	return deltah;
}


float CTRL_Torq_Zero_LAR(float Torq, float Ref_Torq, int zero)
{
	static float y;
	static float sume = 0.;
	float KI = (float)(0.5*0.02/TS);
	
	
	y = -KI*sume;
	
	sume += Ref_Torq - Torq;
	
	if(sume > 5.0/KI) sume = (float)(5./KI);
	else if(sume < -5.0/KI) sume = (float)(-5./KI);
	
	if(y > 5.0) y = 5.0;
	else if(y < -5.0) y = -5.0;
	
	if(zero == 0) sume = 0.;
	
	return y;
}

float CTRL_Torq_Zero_RAR(float Torq, float Ref_Torq, int zero)
{
	static float y;
	static float sume = 0.;
	float KI = (float)(0.5*0.02/TS);
	
	
	y = -KI*sume;
	
	sume += Ref_Torq - Torq;
	
	if(sume > 5.0/KI) sume = (float)(5./KI);
	else if(sume < -5.0/KI) sume = (float)(-5./KI);
	
	if(y > 5.0) y = 5.0;
	else if(y < -5.0) y = -5.0;
	
	if(zero == 0) sume = 0.;
	
	return y;
}

float CTRL_new_compenfwd_kirk(float ZMP, float Ref_ZMP, int zero)
{
	static float y;
	static float sume = 0.;
	float KI = (float)(0.3*(0.002/TS));
	
	
	y = KI*sume;
	
	sume += Ref_ZMP - ZMP;
	
	if(sume > 30.0/KI) sume = (float)(30./KI);
	else if(sume < -30.0/KI) sume = (float)(-30./KI);
	
	if(y > 30.0) y = 30.0;
	else if(y < -30.0) y = -30.0;
	
	if(zero == 0) sume = 0.;
	
	return y;
}

float CTRL_new_compen_kirk(float ZMP, float Ref_ZMP, int zero)
{
	static float y;
	static float sume = 0.;
	float KI = (float)(0.2*(0.002/TS));
	
	
	y = KI*sume;
	
	sume += Ref_ZMP - ZMP;
	
	if(sume > 30.0/KI) sume = (float)(30./KI);
	else if(sume < -30.0/KI) sume = (float)(-30./KI);
	
	if(y > 30.0) y = 30.0;
	else if(y < -30.0) y = -30.0;
	
	if(zero == 0) sume = 0.;
	
	return y;
}


float CTRL_SSP_ZMP_CON_Y(float Ref_zmp, float zmp, int zero)
{
	static float x1new,x2new,x3new,x4new,x5new, x1=0., x2=0., x3=0., x4=0., x5=0.;
	
	const float a[25]={(float)0.00003605223886,  (float)-0.00206946260718,  (float)-0.03777924515070,  (float)-0.35325745247171,  (float)-1.04356976974768,
		(float)0.00000065489684,   (float)0.00008846059811,   (float)-0.00021497918289,  (float)-0.00203943341973,  (float)-0.00606479109435,
		(float)0.00000000380599,   (float)0.00000095947231,   (float)0.00009923808025,   (float)-0.00000727434304,  (float)-0.00002169486330,
		(float)0.00000000001361,   (float)0.00000000489551 ,  (float)0.00000099802533,   (float)0.00009998107833,   (float)-0.00000005652441,
		(float)0.00000000000004,   (float)0.00000000001645 ,  (float)0.00000000499596,   (float)0.00000099996115 ,  (float)0.00009999988383};
	
	const float b[5] = {(float)0.00654896840949,
		(float)0.00003805986570,
		(float)0.00000013614708,
		(float)0.00000000035472,
		(float)0.00000000000073};
	
	const float c[5] = {(float)-0.00034968495443,  (float)-0.01396027841576,  (float)-0.18287463740397,  (float)-1.85137609754101,  (float)-6.07515095605203};
	
	const float p =   (float)-0.58967218893899;
	
	const float scail_a = 10000.;
	
	const float scail_c = 100000.;
	
	static float filt,tzmp,delfilt;
	
	float Err_zmp;
	
	Err_zmp = Ref_zmp - zmp;
	
	x1new=scail_a*(a[0]*x1 + a[1]*x2 + a[2]*x3 + a[3]*x4 + a[4]*x5) + b[0]*Err_zmp;
	x2new=scail_a*(a[5]*x1 + a[6]*x2 + a[7]*x3 + a[8]*x4 + a[9]*x5) + b[1]*Err_zmp;
	x3new=scail_a*(a[10]*x1 + a[11]*x2 + a[12]*x3 + a[13]*x4 + a[14]*x5) + b[2]*Err_zmp;
	x4new=scail_a*(a[15]*x1 + a[16]*x2 + a[17]*x3 + a[18]*x4 + a[19]*x5) + b[3]*Err_zmp;
	x5new=scail_a*(a[20]*x1 + a[21]*x2 + a[22]*x3 + a[23]*x4 + a[24]*x5) + b[4]*Err_zmp;
	
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.; x5new = 0.;}
	
	filt = scail_c*(c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new + c[4]*x5new); 
	
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;
	x5=x5new;
	
	return filt;
}

float CTRL_SSP_ZMP_CON_X(float Ref_zmp, float zmp, int zero)
{
	
	static float x1new,x2new,x3new,x4new,x5new, x1=0., x2=0., x3=0., x4=0., x5=0.;
	
	const float a[25]={ (float)0.00041947455348,  (float)-0.01719952377315,  (float)-0.29263080854907,  (float)-2.64267647502850,  (float)-7.71520583867285,
		(float)0.00000690010232,   (float)0.00090553907551,  (float)-0.00163555363518,  (float)-0.01496801542078,  (float)-0.04397509379505,
		(float)0.00000003932917,   (float)0.00000967057058,   (float)0.00099425051899,  (float)-0.00005293255850,  (float)-0.00015594956348,
		(float)0.00000000013947,   (float)0.00000004915413,   (float)0.00000998516936,   (float)0.00099986299289,  (float)-0.00000040429749,
		(float)0.00000000000036,   (float)0.00000000016494,   (float)0.00000004996972,   (float)0.00000999971964,  (float)0.00099999917181};
	
	const float b[5] = {  (float)0.00690010231574,
		(float)0.00003932917059,
		(float)0.00000013947365,
		(float)0.00000000036158,
		(float)0.00000000000074};
	
	const float c[5] = {(float)-0.00006206491571,  (float)-0.00302077676130,  (float)-0.03567352461336,  (float)-0.35556554646454,  (float)-1.19603333911370};
	
	const float p = (float)-0.59805909460840;
	
	const float scail_a = (float)1000.;
	
	const float scail_c = (float)1000000.;
	
	static float filt,tzmp,delfilt;
	
	float Err_zmp;
	
	Err_zmp = Ref_zmp - zmp;
	
	x1new=scail_a*(a[0]*x1 + a[1]*x2 + a[2]*x3 + a[3]*x4 + a[4]*x5) + b[0]*Err_zmp;
	x2new=scail_a*(a[5]*x1 + a[6]*x2 + a[7]*x3 + a[8]*x4 + a[9]*x5) + b[1]*Err_zmp;
	x3new=scail_a*(a[10]*x1 + a[11]*x2 + a[12]*x3 + a[13]*x4 + a[14]*x5) + b[2]*Err_zmp;
	x4new=scail_a*(a[15]*x1 + a[16]*x2 + a[17]*x3 + a[18]*x4 + a[19]*x5) + b[3]*Err_zmp;
	x5new=scail_a*(a[20]*x1 + a[21]*x2 + a[22]*x3 + a[23]*x4 + a[24]*x5) + b[4]*Err_zmp;
	
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.; x5new = 0.;}
	
	filt = scail_c*(c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new + c[4]*x5new); 
	
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;
	x5=x5new;
	
	return filt;
}

float CTRL_SSP_ZMP_CON_LY(float Ref_zmp, float zmp, int zero)
{
	static float x1new,x2new,x3new,x4new, x1=0., x2=0., x3=0., x4=0.;

	const float a[16]={
		(float)0.608752264168,   (float)-9.872343095122,  (float)-169.149869566708,   (float)-698.443990686020,
		(float)0.007987402034,   (float)0.948387260031,   (float)-0.907436045320,     (float)-3.777298466896,
		(float)0.000043197167,   (float)0.009824203218,   (float)0.996870932461,      (float)-0.013074338996,
		(float)0.000000149518,   (float)0.000049554875,   (float)0.009992019443,      (float)0.999966580908};
	
	const float b[4] = {
			(float)0.00798740203371,
			(float)0.00004319716664,
			(float)0.00000014951808,
			(float)0.00000000038218};
	
	const float c[4] = {
		(float)0.96189880516,   (float)34.55899911440,   (float)517.89887218092,   (float)5251.32695879049};
		
	static float filt,tzmp,delfilt;
	
	float Err_zmp;
	
	Err_zmp = Ref_zmp - zmp;
	
	x1new=(a[0]*x1	+ a[1]*x2	+ a[2]*x3	+ a[3]*x4)	+ b[0]*Err_zmp;
	x2new=(a[4]*x1	+ a[5]*x2	+ a[6]*x3	+ a[7]*x4)	+ b[1]*Err_zmp;
	x3new=(a[8]*x1	+ a[9]*x2	+ a[10]*x3	+ a[11]*x4) + b[2]*Err_zmp;
	x4new=(a[12]*x1 + a[13]*x2	+ a[14]*x3	+ a[15]*x4) + b[3]*Err_zmp;
	
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.;}
	
	filt = (c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new); 
	
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;
	
	return filt;
}
float CTRL_SSP_ZMP_CON_RY(float Ref_zmp, float zmp, int zero)
{
	static float x1new,x2new,x3new,x4new, x1=0., x2=0., x3=0., x4=0.;
	
	const float a[16]={
			(float)0.596354354256,   (float)-10.199708632156,  (float)-170.000453778310,   (float)-709.858998276509,
			(float)0.007918037833,   (float)0.946472526458,   (float)-0.914669326584,     (float)-3.850811728751,
			(float)0.000042953422,   (float)0.009817343424,   (float)0.996841597424,      (float)-0.013348089710,
			(float)0.000000148890,   (float)0.000049536995,   (float)0.009991938010,      (float)0.999965852146};
		
	const float b[4] = {
			(float)0.00791803783337,
			(float)0.00004295342178,
			(float)0.00000014888968,
			(float)0.00000000038090};
			
	const float c[4] = {
			(float)0.89120734311,   (float)30.05543686569,   (float)428.77698288805,   (float)4733.90369201485};
				
	static float filt,tzmp,delfilt;
				
	float Err_zmp;
				
	Err_zmp = Ref_zmp - zmp;
				
	x1new=(a[0]*x1	+ a[1]*x2	+ a[2]*x3	+ a[3]*x4)	+ b[0]*Err_zmp;
	x2new=(a[4]*x1	+ a[5]*x2	+ a[6]*x3	+ a[7]*x4)	+ b[1]*Err_zmp;
	x3new=(a[8]*x1	+ a[9]*x2	+ a[10]*x3	+ a[11]*x4) + b[2]*Err_zmp;
	x4new=(a[12]*x1 + a[13]*x2	+ a[14]*x3	+ a[15]*x4) + b[3]*Err_zmp;
				
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.;}
				
	filt = (c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new); 
				
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;
				
	return filt;
}

float CTRL_SSP_ZMP_CON_LX(float Ref_zmp, float zmp, int zero)
{
	static float x1new,x2new,x3new,x4new,x5new, x1=0., x2=0., x3=0., x4=0.;
	
	const float a[16]={ 
		(float)0.551668372453096,		(float)-13.497911307226,		(float)-186.947538907555,		(float)-580.05116776014,
		(float)0.0076877999900101,		(float)0.927998793311265,		(float)-1.01926071660603,		(float)-3.18228061520447,
		(float)4.21768599764199e-005,	(float)0.00975242647431348,		(float)0.996459250053005,		(float)-0.011086521439833,
		(float)1.46936967205002e-007,   (float)4.93696655618587e-005,   (float)0.00999093099771149,		(float)0.999971556534211};
		
	const float b[4] = {
		(float)0.0076877999900101,
		(float)4.21768599764199e-005,
		(float)1.46936967205002e-007,
		(float)3.76979977216967e-010};
			
	const float c[4] = {(float)4.1733414281115,  (float)137.60826073673,  (float)1739.64597582691,  (float)12062.5790219493};
			
	static float filt,tzmp,delfilt;
			
	float Err_zmp;
			
	Err_zmp = Ref_zmp - zmp;
			
	x1new=(a[0]*x1	+ a[1]*x2	+ a[2]*x3	+ a[3]*x4)	+ b[0]*Err_zmp;
	x2new=(a[4]*x1	+ a[5]*x2	+ a[6]*x3	+ a[7]*x4)	+ b[1]*Err_zmp;
	x3new=(a[8]*x1	+ a[9]*x2	+ a[10]*x3	+ a[11]*x4) + b[2]*Err_zmp;
	x4new=(a[12]*x1 + a[13]*x2	+ a[14]*x3	+ a[15]*x4) + b[3]*Err_zmp;
			
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.;}
	
	filt = (c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new);
			
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;

	return filt;
}

float CTRL_SSP_ZMP_CON_RX(float Ref_zmp, float zmp, int zero)
{
	static float x1new,x2new,x3new,x4new,x5new, x1=0., x2=0., x3=0., x4=0.;
	
	const float a[16]={ 
		(float)0.534100069824468,		(float)-15.295757655903,		(float)-220.273223948066,		(float)-687.101543935971,
		(float)0.00760161459404354,		(float)0.918152162450455,		(float)-1.20631004480821,		(float)-3.78672699952483,
		(float)4.18937193160041e-005,	(float)0.00971818737896273,		(float)0.995801371869629,		(float)-0.0132181790388271,
		(float)1.46236758707665e-007,	(float)4.92819567102713e-005,   (float)0.00998923442102698,		(float)0.999966050731741};
		
	const float b[4] = {
		(float)0.00760161459404354,
		(float)4.18937193160041e-005,
		(float)1.46236758707665e-007,
		(float)3.75591141264735e-010};
			
	const float c[4] = {(float)3.17865765965759,  (float)99.0095064672044,  (float)1451.47758484481,  (float)13823.1962738162};
			
	static float filt,tzmp,delfilt;
	
	float Err_zmp;
			
	Err_zmp = Ref_zmp - zmp;
			
	x1new=(a[0]*x1	+ a[1]*x2	+ a[2]*x3	+ a[3]*x4)	+ b[0]*Err_zmp;
	x2new=(a[4]*x1	+ a[5]*x2	+ a[6]*x3	+ a[7]*x4)	+ b[1]*Err_zmp;
	x3new=(a[8]*x1	+ a[9]*x2	+ a[10]*x3	+ a[11]*x4) + b[2]*Err_zmp;
	x4new=(a[12]*x1 + a[13]*x2	+ a[14]*x3	+ a[15]*x4) + b[3]*Err_zmp;
			
	if(zero == 0) {x1new = 0.; x2new = 0.; x3new = 0.; x4new = 0.;}
			
	filt = (c[0]*x1new + c[1]*x2new + c[2]*x3new + c[3]*x4new);
			
	x1=x1new;
	x2=x2new;
	x3=x3new;
	x4=x4new;
			
	return filt;
}

float CTRL_ZMPAMP(float AvgZMP, float refAMP, int leftright)
{
	const float K[2] = {(float)0.001, (float)0.001};
	float	result;

	if(leftright == 0)	result = (float)(K[leftright]*(refAMP-AvgZMP));
	else				result = (float)(K[leftright]*(refAMP+AvgZMP));

	return result;
}

float CTRL_TorsoInclLeftRoll(float Incl, float ref, char activate)
{
/*
	Controller Poles : 
	-3.00000000000000 + 4.00000000000000i
	-3.00000000000000 - 4.00000000000000i
	-1.50000000000000  
	
	Controller Zeros :
	-60
*/

	const float a[9] = {
							(float)0.92612058448711,   (float)-0.32920525067363,  (float)-0.36107732699954,
							(float)0.00962872871999,   (float)0.99833604988702,   (float)-0.00182847419404,
							(float)0.00004875931184,   (float)0.00999442355880,   (float)0.99999386648961
						};
	const float b[3] = {
							(float)0.00962872871999,
							(float)0.00004875931184,
							(float)0.00000016356028
						};
	const float c[3] = {(float)0,     (float)1,    (float)60};
	
	const float d = (float)0.;
	
	static float x1 = 0.;
	static float x2 = 0.;
	static float x3 = 0.;
	
	static float x1new;
	static float x2new;
	static float x3new;
	
	float input;
	float output;
	
	if(activate == 1)
	{
		input = ref-Incl;
		
		x1new = a[0]*x1 + a[1]*x2 + a[2]*x2 + b[0]*input;
		x2new = a[3]*x1 + a[4]*x2 + a[5]*x2 + b[1]*input;
		x3new = a[6]*x1 + a[7]*x2 + a[8]*x2 + b[2]*input;
		
		output = c[0]*x1new + c[1]*x2new + c[2]*x3new + d*input;
		
		x1 = x1new;
		x2 = x2new;
		x3 = x3new;
		
		if(output >= 2.) output = 2;
		else if(output <= -2.) output = -2;
	}
	else if(activate == 0)
	{
		input = 0.;
		x1new = 0.;
		x2new = 0.;
		x3new = 0.;
		x1 = 0.;
		x2 = 0.;
		x3 = 0.;
		output = 0;
	}
	
	return output;
}

float CTRL_TorsoInclRightRoll(float Incl, float ref, char activate)
{
/*
	Controller Poles : 
	-3.00000000000000 + 4.00000000000000i
	-3.00000000000000 - 4.00000000000000i
	-1.50000000000000  
	
	Controller Zeros :
	-60
*/

	const float a[9] = {
							(float)0.92612058448711,   (float)-0.32920525067363,  (float)-0.36107732699954,
							(float)0.00962872871999,   (float)0.99833604988702,   (float)-0.00182847419404,
							(float)0.00004875931184,   (float)0.00999442355880,   (float)0.99999386648961
						};

	const float b[3] = {
							(float)0.00962872871999,
							(float)0.00004875931184,
							(float)0.00000016356028
						};
	
	const float c[3] = {(float)0,     (float)1,    (float)60};

	const float d = (float)0.;

	static float x1 = 0.;
	static float x2 = 0.;
	static float x3 = 0.;
	
	static float x1new;
	static float x2new;
	static float x3new;
	
	float input;
	float output;
	
	if(activate == 1)
	{
		input = ref-Incl;
		
		x1new = a[0]*x1 + a[1]*x2 + a[2]*x2 + b[0]*input;
		x2new = a[3]*x1 + a[4]*x2 + a[5]*x2 + b[1]*input;
		x3new = a[6]*x1 + a[7]*x2 + a[8]*x2 + b[2]*input;
		
		output = c[0]*x1new + c[1]*x2new + c[2]*x3new + d*input;
		
		x1 = x1new;
		x2 = x2new;
		x3 = x3new;
		
		if(output >= 2.) output = 2;
		else if(output <= -2.) output = -2;
	}
	else if(activate == 0)
	{
		input = 0.;
		x1new = 0.;
		x2new = 0.;
		x3new = 0.;
		x1 = 0.;
		x2 = 0.;
		x3 = 0.;
		output = 0;
	}
	
	return output;
}

float CTRL_TorsoInclLeftPitch(float Incl, float ref, char activate)
{
/*
	Controller Poles : 
	-10.00000000000000                    
	-8.00000000000000 + 6.00000000000000i
	-8.00000000000000 - 6.00000000000000i
	
	Controller Zeros :
   -60
*/
	const float a[9] = {
			(float)0.86522902151819,   (float)-0.84811613897248,  (float)-1.86349787374386,
			(float)0.00931748936872,   (float)0.99567387268026,   (float)-0.00954209578775,
			(float)0.00004771047894,   (float)0.00998543607386,   (float)0.99996781578475
	};
	
	const float b[3] = {
			(float)0.00931748936872,
			(float)0.00004771047894,
			(float)0.00000016092108
	};
	
	const float c[3] = {(float)0,     (float)1,    (float)60};
	
	const float d = (float)0.;

	static float x1 = 0.;
	static float x2 = 0.;
	static float x3 = 0.;
	
	static float x1new;
	static float x2new;
	static float x3new;
	
	float input;
	float output;
	
	if(activate == 1)
	{
		input = ref-Incl;
		
		x1new = a[0]*x1 + a[1]*x2 + a[2]*x2 + b[0]*input;
		x2new = a[3]*x1 + a[4]*x2 + a[5]*x2 + b[1]*input;
		x3new = a[6]*x1 + a[7]*x2 + a[8]*x2 + b[2]*input;
		
		output = c[0]*x1new + c[1]*x2new + c[2]*x3new + d*input;
		
		x1 = x1new;
		x2 = x2new;
		x3 = x3new;
		
		if(output >= 2.) output = 2;
		else if(output <= -2.) output = -2;
	}
	else if(activate == 0)
	{
		input = 0.;
		x1new = 0.;
		x2new = 0.;
		x3new = 0.;
		x1 = 0.;
		x2 = 0.;
		x3 = 0.;
		output = 0;
	}
	
	return output;
}
float CTRL_TorsoInclRightPitch(float Incl, float ref, char activate)
{
/*
	Controller Poles : 
	-10.00000000000000                    
	-8.00000000000000 + 6.00000000000000i
	-8.00000000000000 - 6.00000000000000i
	
	Controller Zeros :
   -60
*/
	const float a[9] = {
			(float)0.86522902151819,   (float)-0.84811613897248,  (float)-1.86349787374386,
			(float)0.00931748936872,   (float)0.99567387268026,   (float)-0.00954209578775,
			(float)0.00004771047894,   (float)0.00998543607386,   (float)0.99996781578475
	};
	
	const float b[3] = {
			(float)0.00931748936872,
			(float)0.00004771047894,
			(float)0.00000016092108
	};
	
	const float c[3] = {(float)0,     (float)1,    (float)60};
	
	const float d = (float)0.;

	static float x1 = 0.;
	static float x2 = 0.;
	static float x3 = 0.;
	
	static float x1new;
	static float x2new;
	static float x3new;
	
	float input;
	float output;
	
	if(activate == 1)
	{
		input = ref-Incl;
		
		x1new = a[0]*x1 + a[1]*x2 + a[2]*x2 + b[0]*input;
		x2new = a[3]*x1 + a[4]*x2 + a[5]*x2 + b[1]*input;
		x3new = a[6]*x1 + a[7]*x2 + a[8]*x2 + b[2]*input;
		
		output = c[0]*x1new + c[1]*x2new + c[2]*x3new + d*input;
		
		x1 = x1new;
		x2 = x2new;
		x3 = x3new;
		
		if(output >= 2.) output = 2;
		else if(output <= -2.) output = -2;
	}
	else if(activate == 0)
	{
		input = 0.;
		x1new = 0.;
		x2new = 0.;
		x3new = 0.;
		x1 = 0.;
		x2 = 0.;
		x3 = 0.;
		output = 0;
	}
	
	return output;
}

float Right_Ankle_Control_Roll(float theta, float vel, float ref)
{
	static float y1 = (float)0.;
	static float y2 = (float)0.;
	static float oldtheta = pSharedMemory->M_Theta_R;
	float y;
	
	y = (float)0.;
	//if( fabs(theta-oldtheta) < 5.0 )
	//{
		//y2 = (float)(-0.15*(1.*theta + 1.*vel));
		//y2 = (float)(-0.15*(1.*theta + 1.*vel));
		//y2 = (float)(-0.2*(1.*theta + 1.*vel));
		//y2 = (float)(-AnkleRollControlGain*(1.*(theta) + 1.*vel));
		y2 = (float)(-AnkleRollControlGain*(1.*(theta) + 0.8*vel));
		//pSharedMemory->temp[1] = (float)(-AnkleRollControlGain*(1.*(theta-ref) + 1.*vel));
		//y2 = (float)(-0.2*(1.*(pSharedMemory->Pos_Roll_Ref - theta) + 1.*vel));
		//y2 = (float)(-AnkleRollControlGain*(1.*(pSharedMemory->Pos_Roll_Ref - theta) + 1.*vel));
	//}
	//else ;
		

	if(y2 > (float)2.0) y2 = (float)2.0;
	else if(y2 < (float)-2.0) y2 = (float)-2.0;

	pSharedMemory->tp_coff1[0] = y2;
	pSharedMemory->tp_coff1[1] = y1;
	pSharedMemory->tp_coff1[2] = y;

	y = (float)((1. - 2.*PI*AnkleControlCutOff*DELTA_T)*y1 + 2.*PI*AnkleControlCutOff*DELTA_T*y2);
	y1 = y;
	//pSharedMemory->temp[1] = -y;

	//return y2;
	return y;
}

float Right_Ankle_Control_Pitch(float theta, float vel, float ref)
{
	static float y1 = (float)0.;
	static float y2 = (float)0.;
	static float oldtheta = pSharedMemory->M_Theta_P;
	float y;

	y = (float)0.;

	//if( fabs(theta-oldtheta) < 5.0 )
	//{
		//y2 = (float)(-0.2*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 1.*vel));
		//y2 = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 1.*vel));
		y2 = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 0.8*vel));
		//pSharedMemory->temp[3] = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta+ref) + 1.*vel));
		//y2 = (float)(-0.15*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 1.*vel));
	//}
	//else ;
	
	if(y2 > (float)2.0) y2 = (float)2.0;
	else if(y2 < (float)-2.0) y2 = (float)-2.0;
	
	pSharedMemory->tp_coff1[3] = y2;
	pSharedMemory->tp_coff1[4] = y1;
	pSharedMemory->tp_coff1[5] = y;

	y = (float)((1. - 2.*PI*AnkleControlCutOffPitch*DELTA_T)*y1 + 2.*PI*AnkleControlCutOffPitch*DELTA_T*y2);
	y1 = y;
	//pSharedMemory->temp[3] = -y;

	//return y2;
	return y;
}

float Left_Ankle_Control_Roll(float theta, float vel, float ref)
{
	static float y1 = (float)0.;
	static float y2 = (float)0.;
	static float oldtheta = pSharedMemory->M_Theta_R;
	float y;
	y = (float)0.;

	//if( fabs(theta-oldtheta) < 5.0 )
	//{
		//y2 = (float)(-0.15*(1.*theta + 1.*vel));
		//y2 = (float)(-0.15*(1.*theta + 1.*vel));
		//y2 = (float)(-0.2*(1.*theta + 1.*vel));
		//y2 = (float)(-AnkleRollControlGain*(1.*theta + 1.*vel));
		y2 = (float)(-AnkleRollControlGain*(1.*theta + 0.8*vel));
		//pSharedMemory->temp[0] = (float)(-AnkleRollControlGain*(1.*(theta - ref) + 1.*vel));
		//y2 = (float)(-0.2*(1.*(pSharedMemory->Pos_Roll_Ref - theta) + 1.*vel));
		//y2 = (float)(-AnkleRollControlGain*(1.*(pSharedMemory->Pos_Roll_Ref - theta) + 1.*vel));
	//}
	//else ;
	
	if(y2 > (float)2.0) y2 = (float)2.0;
	else if(y2 < (float)-2.0) y2 = (float)-2.0;

	pSharedMemory->tp_coff0[0] = y2;
	pSharedMemory->tp_coff0[1] = y1;
	pSharedMemory->tp_coff0[2] = y;

	y = (float)((1. - 2.*PI*AnkleControlCutOff*DELTA_T)*y1 + 2.*PI*AnkleControlCutOff*DELTA_T*y2);
	y1 = y;
	//pSharedMemory->temp[0] = -y;
	
	//return y2;
	return y;
}

float Left_Ankle_Control_Pitch(float theta, float vel, float ref)
{
	static float y1 = (float)0.;
	static float y2 = (float)0.;
	static float oldtheta = pSharedMemory->M_Theta_P;
	float y;
	y = (float)0.;

	//if( fabs(theta-oldtheta) < 5.0 )
	//{
		//y2 = (float)(-0.2*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 1.*vel));
		//y2 = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 1.*vel));
		y2 = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta) + 0.8*vel));
		//pSharedMemory->temp[2] = (float)(-AnklePitchControlGain*(1.*(pSharedMemory->Pos_Pitch_Ref-theta+ref) + 1.*vel));
	//}
	//else ;
	
	if(y2 > (float)2.0) y2 = (float)2.0;
	else if(y2 < (float)-2.0) y2 = (float)-2.0;
	
	pSharedMemory->tp_coff0[3] = y2;
	pSharedMemory->tp_coff0[4] = y1;
	pSharedMemory->tp_coff0[5] = y;

	y = (float)((1. - 2.*PI*AnkleControlCutOffPitch*DELTA_T)*y1 + 2.*PI*AnkleControlCutOffPitch*DELTA_T*y2);
	y1 = y;
	//pSharedMemory->temp[2] = -y;

	//return y2;
	return y;
}

void Hip_Vib_Reduction(float vel)
{
	static float y1 = (float)0.;
	static float y2 = (float)0.;
	static float u1 = (float)0.;
	static float u2 = (float)0.;
	
	//y2 = (float)((1.-3.*0.01)*y1 + 0.1*0.07*3*(u2 + (1.*0.01 - 1.)*u1));

	

	//y2 = (float)((1.-0.01/0.054)*y1 + 0.0231*0.076/(0.054)*vel + 0.0231/(0.054)*(0.01 - 0.076)*u1);
	y2 = (float)((1.-0.01/0.054)*y1 + 0.04*0.076/(0.054)*vel + 0.04/(0.054)*(0.01 - 0.076)*u1);

	if(y2>1.0) y2=(float)1.0;
	else if(y2<-1.0) y2=(float)-1.0;

	u1 = u2;
	y1 = y2;
	
	//pSharedMemory->Hip_Compen[0] = (float)(-1.*y2);
}

float Right_Roll_Vib_Reduction(float vel, int no)
{
	
	static float x1 = (float)0.;
	static float x2 = (float)0.;
	static float x3 = (float)0.;
	
	static float y = (float)0.;
	
	static float x1new,x2new,x3new;
	
	const float a[3][3] = {{(float)-131.44, (float)-5759, (float)-84106},
	{(float)1.0, (float)0., (float)0.},
	{(float)0., (float)1.0, (float)0.}};
	
	const float b[3] = {(float)1.0, (float)0., (float)0.};
	//const float c[3] = {(float)-2.3919, (float)-134.33, (float)-2182.};
	//const float d = (float)0.071843;
	const float c[3] = {(float)-4.6129, (float)-188.52, (float)-671.39};
	const float d = (float)0.053883;
	
	x1new = (float)((1.+DELTA_T*a[0][0])*x1 + (DELTA_T*a[0][1])*x2 + (DELTA_T*a[0][2])*x3 + DELTA_T*(b[0]*vel));
	x2new = (float)((DELTA_T*a[1][0])*x1 + (1.+DELTA_T*a[1][1])*x2 + (DELTA_T*a[1][2])*x3 + DELTA_T*(b[1]*vel));
	x3new = (float)((DELTA_T*a[2][0])*x1 + (DELTA_T*a[2][1])*x2 + (1.+DELTA_T*a[2][2])*x3 + DELTA_T*(b[2]*vel));
	
	x1 = x1new;
	x2 = x2new;
	x3 = x3new;
	
	y = (float)((c[0]*x1 + c[1]*x2 + c[2]*x3) + d*vel);
	
	if(y>(float)2.0) y=(float)2.0;
	else if(y<(float)-2.0) y=(float)-2.0;
	
	return y;
	
}

float Right_Roll_Vib(float vel, int no)
{
	static float x1 = (float)0.;
	static float x2 = (float)0.;
	static float x3 = (float)0.;

	static float y = (float)0.;
	
	static float x1new,x2new,x3new;
	
	const float a[3][3] = {{(float)-131.44, (float)-5759, (float)-84106},
							{(float)1.0, (float)0., (float)0.},
							{(float)0., (float)1.0, (float)0.}};
	
	const float b[3] = {(float)1.0, (float)0., (float)0.};
	//const float c[3] = {(float)-2.3919, (float)-134.33, (float)-2182.};
	//const float d = (float)0.071843;
	const float c[3] = {(float)-4.6129, (float)-188.52, (float)-671.39};
	const float d = (float)0.053883;

	x1new = (float)((1.+DELTA_T*a[0][0])*x1 + (DELTA_T*a[0][1])*x2 + (DELTA_T*a[0][2])*x3 + DELTA_T*(b[0]*vel));
	x2new = (float)((DELTA_T*a[1][0])*x1 + (1.+DELTA_T*a[1][1])*x2 + (DELTA_T*a[1][2])*x3 + DELTA_T*(b[1]*vel));
	x3new = (float)((DELTA_T*a[2][0])*x1 + (DELTA_T*a[2][1])*x2 + (1.+DELTA_T*a[2][2])*x3 + DELTA_T*(b[2]*vel));
	
	x1 = x1new;
	x2 = x2new;
	x3 = x3new;

	y = (float)((c[0]*x1 + c[1]*x2 + c[2]*x3) + d*vel);

	if(y>(float)2.0) y=(float)2.0;
	else if(y<(float)-2.0) y=(float)-2.0;

	return y;
}

float Left_Roll_Vib(float vel, int no)
{
	static float x1 = (float)0.;
	static float x2 = (float)0.;
	static float x3 = (float)0.;

	static float y = (float)0.;
	
	static float x1new,x2new,x3new;
	
	const float a[3][3] = {{(float)-131.44, (float)-5759, (float)-84106},
							{(float)1.0, (float)0., (float)0.},
							{(float)0., (float)1.0, (float)0.}};
	
	const float b[3] = {(float)1.0, (float)0., (float)0.};
	//const float c[3] = {(float)-2.3919, (float)-134.33, (float)-2182.};
	//const float d = (float)0.071843;
	const float c[3] = {(float)-4.6129, (float)-188.52, (float)-671.39};
	const float d = (float)0.053883;
	
	x1new = (float)((1.+DELTA_T*a[0][0])*x1 + (DELTA_T*a[0][1])*x2 + (DELTA_T*a[0][2])*x3 + DELTA_T*(b[0]*vel));
	x2new = (float)((DELTA_T*a[1][0])*x1 + (1.+DELTA_T*a[1][1])*x2 + (DELTA_T*a[1][2])*x3 + DELTA_T*(b[1]*vel));
	x3new = (float)((DELTA_T*a[2][0])*x1 + (DELTA_T*a[2][1])*x2 + (1.+DELTA_T*a[2][2])*x3 + DELTA_T*(b[2]*vel));
	
	x1 = x1new;
	x2 = x2new;
	x3 = x3new;
	
	y = (float)((c[0]*x1 + c[1]*x2 + c[2]*x3) + d*vel);
	
	if(y>(float)2.0) y=(float)2.0;
	else if(y<(float)-2.0) y=(float)-2.0;
	
	return y;
}


float Left_Roll_Vib_Reduction(float vel, int no)
{
	
	static float x1 = (float)0.;
	static float x2 = (float)0.;
	static float x3 = (float)0.;
	
	static float y = (float)0.;
	
	static float x1new,x2new,x3new;
	
	const float a[3][3] = {{(float)-131.44, (float)-5759, (float)-84106},
	{(float)1.0, (float)0., (float)0.},
	{(float)0., (float)1.0, (float)0.}};
	
	const float b[3] = {(float)1.0, (float)0., (float)0.};
	//const float c[3] = {(float)-2.3919, (float)-134.33, (float)-2182.};
	//const float d = (float)0.071843;
	const float c[3] = {(float)-4.6129, (float)-188.52, (float)-671.39};
	const float d = (float)0.053883;
	
	x1new = (float)((1.+DELTA_T*a[0][0])*x1 + (DELTA_T*a[0][1])*x2 + (DELTA_T*a[0][2])*x3 + DELTA_T*(b[0]*vel));
	x2new = (float)((DELTA_T*a[1][0])*x1 + (1.+DELTA_T*a[1][1])*x2 + (DELTA_T*a[1][2])*x3 + DELTA_T*(b[1]*vel));
	x3new = (float)((DELTA_T*a[2][0])*x1 + (DELTA_T*a[2][1])*x2 + (1.+DELTA_T*a[2][2])*x3 + DELTA_T*(b[2]*vel));
	
	x1 = x1new;
	x2 = x2new;
	x3 = x3new;
	
	y = (float)((c[0]*x1 + c[1]*x2 + c[2]*x3) + d*vel);
	
	if(y>(float)2.0) y=(float)2.0;
	else if(y<(float)-2.0) y=(float)-2.0;
	
	return y;
	
}

float Right_SSP_ZMP_Y(float ref, float zmp, float u)
{
	const float a[2][2] = {{(float)-7.6027, (float)-47.769},
							{(float)1., (float)0.}};
	const float b[2] = {(float)1., (float)0.};
	const float c[2] = {(float)-456.89, (float)-3352.1};
	const float d = (float)58.173;
	
	
	static float x1 = (float)0.;
	static float x1new = (float)0.;
	static float x2 = (float)0.;
	static float x2new = (float)0.;
	static float y = (float)0.;
	//static float yhat = (float)0.;
	static float yhat = (float)zmp;

	// desired pole 4+-4i, 3 times faster observer poles.
	//const float Kp[2] = {(float)0.39735, (float)-15.769};
	//const float Ke[2] = {(float)-0.077921, (float)0.0057289};
	
	// desired pole 4+-4i, 3 times faster observer poles.
	const float Kp[2] = {(float)1.3973, (float)-7.2689};
	const float Ke[2] = {(float)-0.10358, (float)0.0083319};
	
	
	yhat = (float)(c[0]*x1 + c[1]*x2 + d*u);
	
	x1new = (float)(x1 + (a[0][0]*x1 + a[0][1]*x2 + b[0]*u + Ke[0]*(zmp - yhat))*0.01);
	x2new = (float)(x2 + (a[1][0]*x1 + a[1][1]*x2 + b[1]*u + Ke[1]*(zmp - yhat))*0.01);
	
	x1 = x1new;
	x2 = x2new;

	y = (float)(-1.*(Kp[0]*x1 + Kp[1]*x2));
	if(y > 1.5) y = (float)1.5;
	else if(y < -1.5) y = (float)-1.5;

	return y;
}

float Left_SSP_ZMP_Y(float ref, float zmp, float u)
{
	const float a[2][2] = {{(float)-7.6027, (float)-47.769},
	{(float)1., (float)0.}};
	const float b[2] = {(float)1., (float)0.};
	const float c[2] = {(float)-456.89, (float)-3352.1};
	const float d = (float)58.173;
	
	
	static float x1 = (float)0.;
	static float x1new = (float)0.;
	static float x2 = (float)0.;
	static float x2new = (float)0.;
	static float y = (float)0.;
	//static float yhat = (float)0.;
	static float yhat = (float)zmp;
	
	// desired pole 4+-4i, 3 times faster observer poles.
	//const float Kp[2] = {(float)0.39735, (float)-15.769};
	//const float Ke[2] = {(float)-0.077921, (float)0.0057289};
	
	// desired pole 4+-4i, 3 times faster observer poles.
	const float Kp[2] = {(float)1.3973, (float)-7.2689};
	const float Ke[2] = {(float)-0.10358, (float)0.0083319};
	
	
	yhat = (float)(c[0]*x1 + c[1]*x2 + d*u);
	
	x1new = (float)(x1 + (a[0][0]*x1 + a[0][1]*x2 + b[0]*u + Ke[0]*(zmp - yhat))*0.01);
	x2new = (float)(x2 + (a[1][0]*x1 + a[1][1]*x2 + b[1]*u + Ke[1]*(zmp - yhat))*0.01);
	
	x1 = x1new;
	x2 = x2new;
	
	y = (float)(-1.*(Kp[0]*x1 + Kp[1]*x2));
	if(y > 1.5) y = (float)1.5;
	else if(y < -1.5) y = (float)-1.5;
	
	return y;
}

float Right_SSP_ZMP_YA(float ref, float zmp)
{
	const float a[2][2] = {{(float)-2.2011, (float)-0.089221},
							{(float)1.0, (float)0.}};
	const float b[2] = {(float)1.0, (float)0.};
	const float c[2] = {(float)-0.054867, (float)-0.51253};
	const float d = (float)-0.011486;

	static float x1 = (float)0.;
	static float x1new = (float)0.;
	static float x2 = (float)0.;
	static float x2new = (float)0.;
	static float u = (float)0.;
	static float y = (float)0.;
	static float LPF_y = (float)0.;
	static float LPF_y_old = (float)0.;

	u = ref - zmp;

	x1new = (float)(x1 + (a[0][0]*x1 + a[0][1]*x2 + b[0]*u)*0.01);
	x2new = (float)(x2 + (a[1][0]*x1 + a[1][1]*x2 + b[1]*u)*0.01);
	x1 = x1new;
	x2 = x2new;

	y = c[0]*x1 + c[1]*x2 + d*u;
	
	//pSharedMemory->temp_data[0] = y;
	
	if(y>1.5) y=1.5;
	else if(y<-1.5) y = -1.5;
	
	//pSharedMemory->temp_data[1] = y;

	LPF_y = (float)((1. - 2*PI*1.*0.01)*LPF_y_old + 2.*PI*1.*0.01*y);
	LPF_y_old = LPF_y;

	return LPF_y;
}

float DSP_ZMP_Y(float ref, float zmp, int no, float I_gain)
{
	const float a[2][2] = {{(float)-13.210, (float)-30.702},
							{(float)1.0, (float)0.}};
	const float b[2] = {(float)1.0, (float)0.};
	const float c[2] = {(float)0.02, (float)0.196};
	const float d = (float)0.;

	static float x1 = (float)0.;
	static float x1new = (float)0.;
	static float x2 = (float)0.;
	static float x2new = (float)0.;
	static float inp = (float)0.;
	static float y = (float)0.;
	static float yi = (float)0.;
	static float yi_old = (float)0.;

	inp = ref - zmp;

	x1new = (float)(x1 + (a[0][0]*x1 + a[0][1]*x2 + b[0]*inp)*DELTA_T);
	x2new = (float)(x2 + (a[1][0]*x1 + a[1][1]*x2 + b[1]*inp)*DELTA_T);
	x1 = x1new;
	x2 = x2new;

	y = c[0]*x1 + c[1]*x2 + d*inp;

	yi = (float)(yi_old + I_gain*DELTA_T*inp);
	yi = CTRL_saturation(yi, 2.0);
	yi_old = yi;

	y = (float)(y + yi);
	
	y=CTRL_saturation(y, 2.0);

	if(no == 0)	// controller reset!
	{
		y = (float)0.;
		x1 = (float)0.;
		x2 = (float)0.;
		yi = (float)0.;
		yi_old = (float)0.;
	}

	return y;
}

float DSP_ZMP_X(float ref, float zmp, int no, float I_gain)
{
	const float a[2][2] = {{(float)-13.000, (float)-40.928},
							{(float)1.0, (float)0.}};
	const float b[2] = {(float)1.0, (float)0.};
	const float c[2] = {(float)0.0828, (float)1.0019};
	const float d = (float)0.;

	static float x1 = (float)0.;
	static float x1new = (float)0.;
	static float x2 = (float)0.;
	static float x2new = (float)0.;
	static float inp = (float)0.;
	static float y = (float)0.;
	static float yi = (float)0.;
	static float yi_old = (float)0.;

	inp = ref + zmp;	// positive feedback

	x1new = (float)(x1 + (a[0][0]*x1 + a[0][1]*x2 + b[0]*inp)*DELTA_T);
	x2new = (float)(x2 + (a[1][0]*x1 + a[1][1]*x2 + b[1]*inp)*DELTA_T);
	x1 = x1new;
	x2 = x2new;

	y = c[0]*x1 + c[1]*x2 + d*inp;

	yi = (float)(yi_old + I_gain*DELTA_T*inp);
	yi = (float)0.;
	yi = CTRL_saturation(yi, 2.0);
	yi_old = yi;

	y = (float)(y + yi);
	
	y=CTRL_saturation(y, 2.0);

	if(no == 0)	// controller reset!
	{
		y = (float)0.;
		x1 = (float)0.;
		x2 = (float)0.;
		yi = (float)0.;
		yi_old = (float)0.;
	}

	return y;
}

float angle_stiff_ds3(float theta_ref,float torque,int zero,int test)
{
	static float x1new, x1=0., y;
	static float notch=0.;
	
	//	static float	pa=3.357,pb=-1.299,pc=0.0006912562 ; // ch=1.000 wn=  5.0 Lo=  5.0
	// This gain is only "pd" torque feedback gain
	//static float 	 pa=3.653,pb=-2.274,pc=0.0005427701 ; // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.213
	
	static float 	 pa=3.939f,pb=-4.333f,pc=0.0007566526f ; // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.213
	
	torque=CTRL_saturation(torque,25.);
	x1new=(float)((1.-pa*0.01)*x1 + (pb-pa)*0.01*torque);
	y=(float)(-57.295779513*pc*(x1new+torque)); // negative feedback
	// Just add this term to the reference
	x1=x1new;
	if(zero==0)  { x1=0.; }
	return y;
}

float angle_stiff_ds4(float theta_ref,float torque,int zero,int test)
{
	static float x1new, x1=0., y;
	static float notch=0.;
	
	//	static float	pa=3.357,pb=-1.299,pc=0.0006912562 ; // ch=1.000 wn=  5.0 Lo=  5.0
	// This gain is only "pd" torque feedback gain
	//static float 	 pa=3.653,pb=-2.274,pc=0.0005427701 ; // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.213
	
	static float 	 pa=3.939f,pb=-4.333f,pc=0.0007566526f ; // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.213
	
	torque=CTRL_saturation(torque,25.);
	x1new=(float)((1.-pa*0.01)*x1 + (pb-pa)*0.01*torque);
	y=(float)(-57.295779513*pc*(x1new+torque)); // negative feedback
	// Just add this term to the reference
	x1=x1new;
	if(zero==0)  { x1=0.; }
	return y;
}

float angle_stiff_fwL(float theta_ref,float torque,int zero,int test)
{
	// Usage : 	 AnkleRoll=angle_stiff_fw1(0.,(Lft.y-512)*NM,1,gainnumberf);
	static float x1new, x1=0.,y;
	//static float pa=3.831, pb=-6.200, pc=0.0002558993;  // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.179
	
	static float pa =4.238f, pb=-5.712f, pc=0.0006317315f;
	// from gcheckf01.m
	x1new=(float)((1.-pa*0.01)*x1 + (pb-pa)*0.01*torque);
	y=(float)(-57.295779513*pc*(x1new+torque)); // negative feedback
	// Just add this term to the reference
	x1=x1new;
	if(zero==0)  { x1=0.; }
	return y;
	
}

float angle_stiff_fwR(float theta_ref,float torque,int zero,int test)
{
	static float x1new, x1=0.,y;
	//static float pa=3.831, pb=-6.200, pc=0.0002558993;  // ch=0.707 wn=  6.0 Lo=  6.0 kd=0.179
	
	//static float pa =5.408, pb=-5.712, pc=0.0014938529;
	static float pa =4.238f, pb=-5.712f, pc=0.0006317315f;
	
	
	// from gcheckf01.m
	x1new=(float)((1.-pa*0.01)*x1 + (pb-pa)*0.01*torque);
	y=(float)(-57.295779513*pc*(x1new+torque)); // negative feedback
	// Just add this term to the reference
	x1=x1new;
	if(zero==0)  { x1=0.; }
	return y;
	
}

float land_damp_fwd(float theta_ref,float torque,int zero,int test)
{
/*	static float x1new,x2new, x1=0., x2=0.;
	static float filt;

	const float a[4] = {0.91904399910015,  -0.39477189065497,
   0.00959295694292,   0.99799837723115};

	const float b[2] = {0.00959295694292,
   0.00004863943328};

	const float c[2] = {0,   0.04115226337449};


	x1new = a[0]*x1 + a[1]*x2 + b[0]*torque;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*torque;

	if(zero == 0) {x1new = 0.; x2new = 0.;}

	filt = c[0]*x1new + c[1]*x2new ;

	if(filt > 10.0) filt = 10.0;
	else if(filt < -10.0) filt = -10.0;

	x1=x1new;
	x2=x2new;

	return filt;
*/
  
	static float x1new, x1=0.,y;
//	static float stiffnessMKS=200.;
	static float stiffnessMKS=0.;
	static float pa=0.0f, pc=0.015f; // pc<=0.03 optimal ok : when this gain is used you should turn off stiff_fw
								  // pc<=0.015(limit) can be mixed with land_stiff

	static int offcontrolflag=0;

	pa=pc*stiffnessMKS;


	if(offcontrolflag==0)
	{
	//if(torque<-1.0) torque+=1.0;
	//else if(torque<1.0) torque=0.;  // dead zone
	//else torque-=1.0;
	if(torque<-0.1) torque+=(float)(0.1);
	else if(torque<0.1) torque=0.;  // dead zone
	else torque-=(float)(0.1);

	x1new=(float)((1.-pa*0.01)*x1 + (pc)*0.01*torque);
	if(x1new>0.1) x1new=(float)(0.1);
	else if(x1new<-0.1) x1new=(float)(-0.1);
	y=(float)(+57.295779513*x1new); // positive feedback

	x1=x1new;
	}

	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;

}

float LF_land_damp_roll(float theta_ref,float torque,int zero,int test)
{
	/*
	static float x1new,x2new, x1=0., x2=0.;
	static float filt;

	const float a[4] = {0.93816401227048,  -0.39880503521043,
   0.00969096235561,   0.99798476755204};

	const float b[2] = {0.00969096235561,
   0.00004897014849};

	const float c[2] = {0,   0.04115226337449};


	x1new = a[0]*x1 + a[1]*x2 + b[0]*torque;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*torque;

	if(zero == 0) {x1new = 0.; x2new = 0.;}

	filt = c[0]*x1new + c[1]*x2new ;

	if(filt > 5.0) filt = 5.0;
	else if(filt < -5.0) filt = -5.0;

	x1=x1new;
	x2=x2new;

	return filt;
*/

	static float x1new, x1=0.,y;
//	static float stiffnessMKS=200.;
	static float stiffnessMKS=0.;
	static float pa=0.0f, pc=0.015f; // pc<=0.03 optimal ok : when this gain is used you should turn off stiff_fw
								  // pc<=0.015(limit) can be mixed with land_stiff

	static int offcontrolflag=0;

	pa=pc*stiffnessMKS;


	if(offcontrolflag==0)
	{
	//if(torque<-1.0) torque+=1.0;
	//else if(torque<1.0) torque=0.;  // dead zone
	//else torque-=1.0;
	if(torque<-0.1) torque+=(float)(0.1);
	else if(torque<0.1) torque=0.;  // dead zone
	else torque-=(float)(0.1);

	x1new=(float)((1.-pa*0.01)*x1 + (pc)*0.01*torque);
	if(x1new>0.1) x1new=(float)(0.1);
	else if(x1new<-0.1) x1new=(float)(-0.1);
	y=(float)(+57.295779513*x1new); // positive feedback

	x1=x1new;
	}

	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;

}

float RF_land_damp_roll(float theta_ref,float torque,int zero,int test)
{
	/*
	static float x1new,x2new, x1=0., x2=0.;
	static float filt;

	const float a[4] = {0.93816401227048,  -0.39880503521043,
   0.00969096235561,   0.99798476755204};

	const float b[2] = {0.00969096235561,
   0.00004897014849};

	const float c[2] = {0,   0.04115226337449};


	x1new = a[0]*x1 + a[1]*x2 + b[0]*torque;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*torque;

	if(zero == 0) {x1new = 0.; x2new = 0.;}

	filt = c[0]*x1new + c[1]*x2new ;

	if(filt > 5.0) filt = 5.0;
	else if(filt < -5.0) filt = -5.0;

	x1=x1new;
	x2=x2new;

	return filt;
	*/

	static float x1new, x1=0.,y;
//	static float stiffnessMKS=200.;
	static float stiffnessMKS=0.;
	static float pa=0.0f, pc=0.015f; // pc<=0.03 optimal ok : when this gain is used you should turn off stiff_fw
								  // pc<=0.015(limit) can be mixed with land_stiff

	static int offcontrolflag=0;

	pa=pc*stiffnessMKS;


	if(offcontrolflag==0)
	{
	//if(torque<-1.0) torque+=1.0;
	//else if(torque<1.0) torque=0.;  // dead zone
	//else torque-=1.0;
	if(torque<-0.1) torque+=(float)(0.1);
	else if(torque<0.1) torque=0.;  // dead zone
	else torque-=(float)(0.1);

	x1new=(float)((1.-pa*0.01)*x1 + (pc)*0.01*torque);
	if(x1new>0.1) x1new=(float)(0.1);
	else if(x1new<-0.1) x1new=(float)(-0.1);
	y=(float)(+57.295779513*x1new); // positive feedback

	x1=x1new;
	}

	if(zero==0)  { x1=0.; offcontrolflag=0;}
	return y;

}

float SSP_ZMP_CON_Y(float Ref_Yzmp, float Yzmp, int zero)
{	
	static float y;
	static float sume = 0.;
	float KI = 0.0;
	//float KI = 0.006; //static
	//float KI = 0.002; // dynamic
	
	//y = -0.03*(Ref_Yzmp - Yzmp) + KI*sume; 
	y =(float)( -0.05*(Ref_Yzmp - Yzmp) + KI*sume); 
	
	sume += Ref_Yzmp - Yzmp;
	
	//	if(sume > 10.0/KI) sume = 10./KI;
	//	else if(sume < -10.0/KI) sume = -10./KI;
	
	if(y > 10.0) y = 10.0;
	else if(y < -10.0) y = -10.0;
	
	if(zero == 0) sume = 0.;
	
	return y;
}

float SSP_ZMP_CON_X(float Ref_Xzmp, float Xzmp, int zero)
{
	static float y;
	static float sume = 0.;
	float KI = 0.0;
	//float KI = 0.01; // static
	//float KI = 0.005; // dynamic
	
	y =(float)( -0.05*(Ref_Xzmp - Xzmp) + KI*sume);
	//y = -0.075*(Ref_Xzmp - Xzmp) + KI*sume;
	
	sume += Ref_Xzmp - Xzmp;
	
	//	if(sume > 10.0/KI) sume = 10./KI;
	//	else if(sume < -10.0/KI) sume = -10./KI;
	
	if(y > 10.0) y = 10.0;
	else if(y < -10.0) y = -10.0;	
	
	if(zero == 0) sume = 0.;
	
	return y;
}

float BC_Y_Amp_Comp_M(float Zmp_Amp, float Ref_Zmp_Amp, int zero)
{
	static float amp;
	static float sume = 0.;
	float KI = (float)0.03;
	
	amp = (float)(0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume);
	
	sume += Ref_Zmp_Amp - Zmp_Amp;
	
	if(sume > 3.0/KI) sume = (float)(3./KI);
	else if(sume < -3.0/KI) sume = (float)(-3./KI);
	
	if(amp > 3.0) amp = 3.0;
	else if(amp < -3.0) amp = -3.0;
	
	if(zero == 0) sume = 0.;
	
	return amp;
}

float BC_Y_Amp_Comp_W(float Zmp_Amp, float Ref_Zmp_Amp, float step_length, int zero)
{
	static float amp;
	static float sume_0 = 0., sume_1 = 0., sume_2 = 0., sume_3 = 0.;
	float KI = (float)0.03;
	
	if(step_length <= 175){
		amp = (float)(0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume_0);
		
		sume_0 += Ref_Zmp_Amp - Zmp_Amp;
		
		if(sume_0 > 3.0/KI) sume_0 = (float)(3./KI);
		else if(sume_0 < -3.0/KI) sume_0 = (float)(-3./KI);
	}
	else if(step_length >= 175 && step_length < 225){
		amp = (float)(0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume_1);
		
		sume_1 += Ref_Zmp_Amp - Zmp_Amp;
		
		if(sume_1 > 3.0/KI) sume_1 = (float)(3./KI);
		else if(sume_1 < -3.0/KI) sume_1 = (float)(-3./KI);
	}
	else if(step_length >= 225 && step_length < 275){
		amp = (float)(0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume_2);
		
		sume_2 += Ref_Zmp_Amp - Zmp_Amp;
		
		if(sume_2 > 3.0/KI) sume_2 = (float)(3./KI);
		else if(sume_2 < -3.0/KI) sume_2 = (float)(-3./KI);
	}
	else if(step_length >= 275){
		amp =(float)( 0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume_3);
		
		sume_3 += Ref_Zmp_Amp - Zmp_Amp;
		
		if(sume_3 > 3.0/KI) sume_3 =(float)(3./KI);
		else if(sume_3 < -3.0/KI) sume_3 = (float)(-3./KI);
	}
	
	
	if(amp > 3.0) amp = 3.0;
	else if(amp < -3.0) amp = -3.0;
	
	if(zero == 0) {sume_0 = 0.; sume_1 = 0.; sume_2 = 0.; sume_3 = 0.;}
	
	return amp;
}

float BC_Y_Amp_Comp_B(float Zmp_Amp, float Ref_Zmp_Amp, int zero)
{
	static float amp;
	static float sume = 0.;
	float KI = 0.03f;
	
	amp = (float)(0.1*(Ref_Zmp_Amp - Zmp_Amp) + KI*sume);
	
	sume += Ref_Zmp_Amp - Zmp_Amp;
	
	if(sume > 3.0/KI) sume = (float)(3./KI);
	else if(sume < -3.0/KI) sume = (float)(-3./KI);
	
	if(amp > 3.0) amp = 3.0;
	else if(amp < -3.0) amp = -3.0;
	
	if(zero == 0) sume = 0.;
	
	return amp;
}

float Torsion_mass_spring_damper_Mx(float Mx, int zero)
{
	static float x1new,x2new, x1=0., x2=0.;
	static float filt;
	
	/*
	const float a[4] = {(float)0.92461509587868,  (float)-0.32069771753193,
						(float)0.00962093152596,   (float)0.99837557091103};
	
	const float b[2] = {(float)0.00962093152596, (float)0.00004873287267};
	const float c[2] = { (float)0.0,  (float)65.0};
	*/
	/*
	const float a[4] = {(float)0.97015145404280,  (float)-0.13134819764971,
						(float)0.00985111482373,   (float)0.99933994240940};
	
	const float b[2] = {(float)0.00985111482373,	(float)0.00004950431930};
	
	const float c[2] = {(float)0.0,  (float)14.81481481481481};
	*/

	const float a[4] = {(float)0.97765796618688,  (float)-0.07324804804199,
						(float)0.00988848648567,   (float)0.99963238059948};
	
	const float b[2] = {(float)0.00988848648567,	(float)0.00004962861907};
	
	const float c[2] = {(float)0.0,  (float)14.81481481481481};

	
	x1new = a[0]*x1 + a[1]*x2 + b[0]*Mx;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*Mx;
	
	if(zero == 0) {x1new = 0.; x2new = 0.; filt = 0.;}
	
	//filt = c[0]*x1new + c[1]*x2new;

	filt = (float)(filt + 0.1*Mx); 
	
	if(filt > 10.0) filt = 10.0;
	else if(filt < -30.0) filt = -30.0;
	
	x1=x1new;
	x2=x2new;
	
	return filt;
}

float Torsion_mass_spring_damper_My(float My, int zero)
{
	static float x1new,x2new, x1=0., x2=0.;
	static float filt;
	
	const float a[4] = {(float)0.97015145404280,  (float)-0.13134819764971,
						(float)0.00985111482373,   (float)0.99933994240940};
	
	const float b[2] = {(float)0.00985111482373,	(float)0.00004950431930};
	
	const float c[2] = {(float)0.0,  (float)14.81481481481481};
	
	x1new = a[0]*x1 + a[1]*x2 + b[0]*My;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*My;
	
	if(zero == 0) {x1new = 0.; x2new = 0.; filt = 0.;}
	
	//filt = c[0]*x1new + c[1]*x2new;

	filt = (float)(filt + 0.05*My); 
	
	if(filt > 10.0) filt = 10.0;
	else if(filt < -10.0) filt = -10.0;
	
	x1=x1new;
	x2=x2new;
	
	return filt;
}

float Wrist_mass_spring_damper_Fz(float Fz, int zero)
{
	static float x1new,x2new, x1=0., x2=0.;
	static float filt;
	
	const float a[4] = {(float)0.94503939283972,  (float)-0.29175327263157,
						(float)0.00972510908772,   (float)0.99852749282218};
	
	const float b[2] = {(float)0.00972510908772,	(float)0.00004908357259};
	
	const float c[2] = {(float)0.0,    (float)10.0};
	
	
	x1new = a[0]*x1 + a[1]*x2 + b[0]*Fz;
	x2new = a[2]*x1 + a[3]*x2 + b[1]*Fz;
	
	if(zero == 0) {x1new = 0.; x2new = 0.;}
	
	filt = c[0]*x1new + c[1]*x2new ;
	
	if(filt > 30.0) filt = 30.0;
	else if(filt < -30.0) filt = -30.0;
	
	x1=x1new;
	x2=x2new;
	
	return filt;
}


float SSP_RF_ZMP_CON_Y(float Ref_Yzmp, float Yzmp, int zero){

	static float y;
	static float sume = 0.;
	float KI = 0.003; // chicago
	//float KI = 0.006;
	

	//y = 0.02*(Ref_Yzmp - Yzmp) + KI*sume;
	y = 0.03*(Ref_Yzmp - Yzmp) + KI*sume;
	
	sume += Ref_Yzmp - Yzmp;

	if(sume > 50.0/KI) sume = 50./KI;
	else if(sume < -50.0/KI) sume = -50./KI;

	if(y > 50.0) y = 50.0;
	else if(y < -50.0) y = -50.0;

	if(zero == 0) sume = 0.;

	return y;
}

float SSP_RF_ZMP_CON_X(float Ref_Xzmp, float Xzmp, int zero){

	static float y;
	static float sume = 0.;
	float KI = 0.006;
	
	//y = 0.02*(Ref_Xzmp - Xzmp) + KI*sume;
	y = 0.05*(Ref_Xzmp - Xzmp) + KI*sume;
	
	sume += Ref_Xzmp - Xzmp;

	if(sume > 50.0/KI) sume = 50./KI;
	else if(sume < -50.0/KI) sume = -50./KI;

	if(y > 50.0) y = 50.0;
	else if(y < -50.0) y = -50.0;

	if(zero == 0) sume = 0.;

	return y;
}





