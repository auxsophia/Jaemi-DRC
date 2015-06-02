#include "math.h"
#include "Function.h"
#include "Define.h"
#include "RTX.h"

char FTN_half_1pcos(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<=temp)
	{
		*result=mag;
		return 0;
	}
	else if((time>=temp)&&(time<temp1))
	{
		*result=mag*(1+(float)cos(PI*(float)(time-temp)/(float)(during-(delay1+delay2))))/2;
		return 1;
	}
	else if(time>=temp1)
	{
		*result=0;
		return 2;
	}
	else return 3;
}

char FTN_half_1pcosFOOTZ(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1,temp2,temp3;
	float	ttt;
	
	temp=start+(long)delay1;		// start time
	temp1=start+(long)(during/2);	//end time of first half
	temp2=start+(long)(during/2);	//start time of second half
	temp3=start+during-(long)delay2;		// end time of second half
	
	if(time<temp)
	{
		*result=mag;
		ttt=0;
		return 0;
	}
	else if((time>=temp)&&(time<temp1))
	{
		ttt=(float)(time-temp);
		*result=(float)(mag*(1+cos(PI/2*(ttt/(temp1-temp))))/2);
		return 1;
	}
	else if((time>=temp1)&&(time<temp2))
	{
		ttt=0.5;
		*result=mag/2;
		return 1;
	}
	else if((time>=temp2)&&(time<temp3))
	{
		ttt=(float)(time-temp2);
		*result=(float)(mag*(1-sin(PI/2*(ttt/(temp3-temp2))))/2);
		return 1;
	}
	else if(time>=temp3)
	{
		ttt=(float)temp3;
		*result=0;
		return 2;
	}
	else
	{
		return 3;
	}
}

char FTN_quarter_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=(float)(mag*(1.-cos(0.5*PI*(float)(time-temp)/(float)(during-(delay1+delay2)))));
		return 1;
	}
	else if(time>temp1)
	{
		*result=mag;
		return 2;
	}
	else return 3;
}

char FTN_quarter_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=mag*((float)sin(0.5*PI*(float)(time-temp)/(float)(during-(delay1+delay2))));
		return 1;
	}
	else if(time>temp1)
	{
		*result=mag;
		return 2;
	}
	else return 3;
}


char FTN_half_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=mag*(1-(float)cos(PI*(float)(time-temp)/(float)(during-(delay1+delay2))))/2;
		return 1;
	}
	else if(time>temp1)
	{
		*result=mag;
		return 2;
	}
	else return 3;
}

char FTN_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<=temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=mag*(1-(float)cos(2*PI*(float)(time-temp)/(float)(during-(delay1+delay2))))/2;
		return 1;
	}
	else if(time>=temp1)
	{
		*result=0;
		return 2;
	}
	else return 3;
}

char FTN_half_1_cos_linear(float mag, long time, long start, long during,
								  int delay, int MAX_D, float *result)
{
	long	temp,temp1;
	float	t;
	if(delay>=0)
	{
		temp=start+delay;
		temp1=start+during-delay;
		
		if(time<=temp)
		{
			*result=0;
			return 0;
		}
		else if((time>=temp)&&(time<temp1))
		{
			*result=mag*(1-(float)cos(PI*(float)(time-temp)/(float)(during-2*delay)))/2;
			return 1;
		}
		else if(time>=temp1)
		{
			*result=mag;
			return 2;
		}
		else return 3;	
	}
	else if(delay<0)
	{
		temp=start;
		temp1=start+during;
		if(time<=temp)
		{
			*result=0;
			return 4;
		}
		else if((time>=temp)&&(time<temp1))
		{
			t=(float)((time-temp)/during);
			*result=(float)(mag*((float)(-delay/MAX_D)*t+((MAX_D+delay)/(MAX_D))*(1-cos(PI*t))/2));
			return 5;
		}
		else if(time>=temp1)
		{
			*result=mag;
			return 6;
		}
		else return 7;
	}
	return 0;
}

char FTN_quater_1_cos_UP(float mag, long time, long start,
									   long during, int delay, float *result)
{
	long	temp,temp1;
	float	t;

	temp=start+delay;
	temp1=start+during;

	t=(float)((time-temp)/(during-delay));
		
	if(time<temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=(float)(mag*(1-cos(PI*t/2)));
		return 1;
	}
	else if(time>temp1)
	{
		*result=mag;
		return 2;
	}
	else return 3;
}

char FTN_quater_1_cos_DN(float mag, long time, long start,
									   long during, int delay, float *result)
{
	long	temp,temp1;
	float	t;

	temp=start+delay;
	temp1=start+during;

	t=(float)((time-temp)/(during-delay));
		
	if(time<temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<=temp1))
	{
		*result=(float)(mag*sin(PI*t/2));
		return 1;
	}
	else if(time>temp1)
	{
		*result=mag;
		return 2;
	}
	else return 3;
}

char FTN_cyclUP(float mag, long time, long start, long during, long delay, float SF, float *result)
{
	float	t;
	
	t=(float)(time-(start+delay))/(float)(during-delay);
	
	if(time<start+delay)
	{
		*result=0;
		return 0;
	}
	else if((time>=start+delay)&&(time<=start+during))
	{
		*result=(float)((t-sin(PI*t)/(PI*SF))*mag/2);
		return 1;
	}
	else if(time>start+during)
	{
		*result=mag/2;
		return 2;
	}
	else return 3;
}

char FTN_cyclDN(float mag, long time, long start, long during, long delay, float SF, float *result)
{
	float	t;
	
	t=(float)(time-start)/(float)(during-delay);
	
	if(time<start)
	{
		*result=0;
		return 0;
	}
	else if((time>=start)&&(time<=start+during-delay))
	{
		*result=(float)((t+sin(PI*t)/(PI*SF))*mag/2);
		return 1;
	}
	else if(time>start+during-delay)
	{
		*result=mag/2;
		return 2;
	}
	else return 3;
}

char FTN_cyclUPvel(float mag, long time, long start, long during, long delay, float SF, float *result)
{
	float	t;
	
	t=(float)(time-(start+delay))/(float)(during-delay);
	
	if(time<start+delay)
	{
		*result=0;
		return 0;
	}
	else if((time>=start+delay)&&(time<=start+during))
	{
		*result=(float)((1-cos(PI*t)/SF)*mag/2);
		return 1;
	}
	else if(time>start+during)
	{
		*result=(1+1/SF)*mag/2;
		return 2;
	}
	else return 3;
}

char FTN_cyclDNvel(float mag, long time, long start, long during, long delay, float SF, float *result)
{
	float	t;
	
	t=(float)(time-start)/(float)(during-delay);
	
	if(time<start)
	{
		*result=0;
		return 0;
	}
	else if((time>=start)&&(time<=start+during-delay))
	{
		*result=(float)((1+cos(PI*t)/SF)*mag/2);
		return 1;
	}
	else if(time>start+during-delay)
	{
		*result=(1-1/SF)*mag/2;
		return 2;
	}
	else return 3;
}

char FTN_cyclVel(float mag, long time, long start, long during, long delay, float SF, float *result)
{
	float	t;
	
	t=(float)(time-(start+delay))/(float)(during-2*delay);
	
	if(time<start+delay)
	{
		*result=0;
		return 0;
	}
	else if((time>=start+delay)&&(time<=start+during-delay))
	{
		*result=(float)((1-cos(2*PI*t)*2/SF)*mag);
		return 1;
	}
	else if(time>start+during-delay)
	{
		*result=(1-2/SF)*mag;
		return 2;
	}
	else return 3;
}

char FTN_3poly0(float t0, float t, float p1, float dp1, float p2, float dp2, float *result)
{
	// 0<= t <=t0 (3rd order polynomial interpolation function)
	float a[4];
	float t0_temp;

	const float b[4][4] = {{1.0, 0.0, 0.0, 0.0},
							{0.0, 0.0, 1.0, 0.0},
							{-12.0, 12.0, -4.0, -2.0},
							{16.0, -16.0, 4.0, 4.0}};
	float c[4];

	const float dd[6][6] = {{1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
							{0.0, 0.0, 1.0, 0.0, 0.0, 0.0},
							{0.0, 0.0, 0.0, 0.0, 0.5, 0.0},
							{-80.0, 80.0, -24.0, -16.0, -3.0, 1.0},
							{240.0, -240.0, 64.0, 56.0, 6.0, -4.0},
							{-192.0, 192.0, -48.0, -48.0, -4.0, 4.0}};
	float e[6];
	

	t0_temp=-t0*t0*t0; // -t0^3
	
	if((t>=0)&&(t<=t0))
	{
		a[0]=(-2*p1-t0*dp1+2*p2-t0*dp2)/t0_temp;
		a[1]=(3*t0*p1+2*t0*t0*dp1-3*t0*p2+t0*t0*dp2)/t0_temp;
		a[2]=dp1;
		a[3]=p1;
		
		*result=a[0]*t*t*t+a[1]*t*t+a[2]*t+a[3];

		c[0] = b[0][0]*p1 + b[0][1]*p2 + b[0][2]*dp1 + b[0][3]*dp2;
		c[1] = b[1][0]*p1 + b[1][1]*p2 + b[1][2]*dp1 + b[1][3]*dp2;
		c[2] = b[2][0]*p1 + b[2][1]*p2 + b[2][2]*dp1 + b[2][3]*dp2;
		c[3] = b[3][0]*p1 + b[3][1]*p2 + b[3][2]*dp1 + b[3][3]*dp2;

		e[0] = dd[0][0]*p1 + dd[0][1]*p2 + dd[0][2]*dp1 + dd[0][3]*dp2;
		e[1] = dd[1][0]*p1 + dd[1][1]*p2 + dd[1][2]*dp1 + dd[1][3]*dp2;
		e[2] = dd[2][0]*p1 + dd[2][1]*p2 + dd[2][2]*dp1 + dd[2][3]*dp2;
		e[3] = dd[3][0]*p1 + dd[3][1]*p2 + dd[3][2]*dp1 + dd[3][3]*dp2;
		e[4] = dd[4][0]*p1 + dd[4][1]*p2 + dd[4][2]*dp1 + dd[4][3]*dp2;
		e[5] = dd[5][0]*p1 + dd[5][1]*p2 + dd[5][2]*dp1 + dd[5][3]*dp2;

		//pSharedMemory->Hip_test0[0] = (float)(a[0]*t*t*t+a[1]*t*t+a[2]*t+a[3]);
		pSharedMemory->Hip_test3[0] = (float)(c[0] + c[1]*t + c[2]*t*t + c[3]*t*t*t);
		//pSharedMemory->Hip_test5_a[0] = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);


		return 1;
	}
	
	else return 0;
}

char FTN_3poly1(float t0, float t, float p1, float dp1, float p2, float dp2, float *result)
{
	// t0<= t <=1 (3rd order polynomial interpolation function)
	float a[4];
	float t0_temp;
	float t0_1;
	
	const float b[4][4] = {{-4.0, 5.0, -2.0, -1.0},
							{24.0, -24.0, 8.0, 5.0},
							{-36.0, 36.0, -10.0, -8.0},
							{16.0, -16.0, 4.0, 4.0}};
	float c[4];
	
	const float dd[6][6] = {{32.0, -31.0, 8.0, 7.0, 1.0, -0.5},
							{-240.0, 240.0, -64.0, -55.0, -7.0, 4.0},
							{720.0, -720.0, 192.0, 168.0, 19.0, -12.5},
							{-1040.0, 1040.0, -272.0, -248.0, -25.0, 19.0},
							{720.0, -720.0, 184.0, 176.0, 16.0, -14.0},
							{-192.0, 192.0, -48.0, -48.0, -4.0, 4.0}};
	float e[6];
	

	t0_1=t0-1;
	t0_temp=t0_1*t0_1*t0_1; // -(1-t0)^3==(t0-1)^3

	if((t>=t0)&&(t<=1))
	{
		a[0]=(-2*p1+t0_1*dp1+2*p2+t0_1*dp2)/t0_temp;
		a[1]=(3*(t0+1)*p1-(t0+2)*t0_1*dp1-3*(t0+1)*p2-(2*t0+1)*t0_1*dp2)/t0_temp;
		a[2]=(-6*t0*p1+(2*t0+1)*t0_1*dp1+6*t0*p2+t0*(t0+2)*t0_1*dp2)/t0_temp;
		a[3]=((3*t0-1)*p1-t0*t0_1*dp1+t0*t0*(t0-3)*p2-t0*t0*t0_1*dp2)/t0_temp;
		
		*result=a[0]*t*t*t+a[1]*t*t+a[2]*t+a[3];

		c[0] = b[0][0]*p1 + b[0][1]*p2 + b[0][2]*dp1 + b[0][3]*dp2;
		c[1] = b[1][0]*p1 + b[1][1]*p2 + b[1][2]*dp1 + b[1][3]*dp2;
		c[2] = b[2][0]*p1 + b[2][1]*p2 + b[2][2]*dp1 + b[2][3]*dp2;
		c[3] = b[3][0]*p1 + b[3][1]*p2 + b[3][2]*dp1 + b[3][3]*dp2;
		
		e[0] = dd[0][0]*p1 + dd[0][1]*p2 + dd[0][2]*dp1 + dd[0][3]*dp2;
		e[1] = dd[1][0]*p1 + dd[1][1]*p2 + dd[1][2]*dp1 + dd[1][3]*dp2;
		e[2] = dd[2][0]*p1 + dd[2][1]*p2 + dd[2][2]*dp1 + dd[2][3]*dp2;
		e[3] = dd[3][0]*p1 + dd[3][1]*p2 + dd[3][2]*dp1 + dd[3][3]*dp2;
		e[4] = dd[4][0]*p1 + dd[4][1]*p2 + dd[4][2]*dp1 + dd[4][3]*dp2;
		e[5] = dd[5][0]*p1 + dd[5][1]*p2 + dd[5][2]*dp1 + dd[5][3]*dp2;
		
		//pSharedMemory->Hip_test0[1] = (float)(a[0]*t*t*t+a[1]*t*t+a[2]*t+a[3]);
		pSharedMemory->Hip_test3[1] = (float)(c[0] + c[1]*t + c[2]*t*t + c[3]*t*t*t);
		//pSharedMemory->Hip_test5_a[1] = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);

		return 1;
	}

	else	return 0;
}

char FTN_3poly(float t, float p1, float dp1, float p2, float dp2, float *result)
{
	// 0<= t <=1 (3rd order polynomial interpolation function)
	float a[4];
	
	if((t>=0)&&(t<=1))
	{
		a[0]=2*p1+dp1-2*p2+dp2;
		a[1]=-3*p1-2*dp1+3*p2-dp2;
		a[2]=dp1;
		a[3]=p1;
		
		*result=a[0]*t*t*t+a[1]*t*t+a[2]*t+a[3];
		
		return 1;
	}
	else	return 0;
}

char FTN_5poly0(float t0, float t, float p1, float dp1, float p2, float dp2, float ddp1, float ddp2, float *result)
{
	// 0<= t <=t0 (3rd order polynomial interpolation function)
	
	const float d[6][6] = {{1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
							{0.0, 0.0, 1.0, 0.0, 0.0, 0.0},
							{0.0, 0.0, 0.0, 0.0, 0.5, 0.0},
							{-80.0, 80.0, -24.0, -16.0, -3.0, 1.0},
							{240.0, -240.0, 64.0, 56.0, 6.0, -4.0},
							{-192.0, 192.0, -48.0, -48.0, -4.0, 4.0}};
	
	float e[6];
	
	if((t>=0)&&(t<=t0))
	{		
		e[0] = d[0][0]*p1 + d[0][1]*p2 + d[0][2]*dp1 + d[0][3]*dp2 + d[0][4]*ddp1 + d[0][5]*ddp2;
		e[1] = d[1][0]*p1 + d[1][1]*p2 + d[1][2]*dp1 + d[1][3]*dp2 + d[1][4]*ddp1 + d[1][5]*ddp2;
		e[2] = d[2][0]*p1 + d[2][1]*p2 + d[2][2]*dp1 + d[2][3]*dp2 + d[2][4]*ddp1 + d[2][5]*ddp2;
		e[3] = d[3][0]*p1 + d[3][1]*p2 + d[3][2]*dp1 + d[3][3]*dp2 + d[3][4]*ddp1 + d[3][5]*ddp2;
		e[4] = d[4][0]*p1 + d[4][1]*p2 + d[4][2]*dp1 + d[4][3]*dp2 + d[4][4]*ddp1 + d[4][5]*ddp2;
		e[5] = d[5][0]*p1 + d[5][1]*p2 + d[5][2]*dp1 + d[5][3]*dp2 + d[5][4]*ddp1 + d[5][5]*ddp2;
		

		*result = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);
		//pSharedMemory->Hip_test5[0] = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);
		
		pSharedMemory->Hip_test5_a[0] = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);

		return 1;
	}
	
	else return 0;
}

char FTN_5poly1(float t0, float t, float p1, float dp1, float p2, float dp2, float ddp1, float ddp2, float *result)
{
	// t0<= t <=1 (3rd order polynomial interpolation function)
	
	const float d[6][6] = {{32.0, -31.0, 8.0, 7.0, 1.0, -0.5},
							{-240.0, 240.0, -64.0, -55.0, -7.0, 4.0},
							{720.0, -720.0, 192.0, 168.0, 19.0, -12.5},
							{-1040.0, 1040.0, -272.0, -248.0, -25.0, 19.0},
							{720.0, -720.0, 184.0, 176.0, 16.0, -14.0},
							{-192.0, 192.0, -48.0, -48.0, -4.0, 4.0}};
	
	
	float e[6];
	
	if((t>=t0)&&(t<=1))
	{		
		e[0] = d[0][0]*p1 + d[0][1]*p2 + d[0][2]*dp1 + d[0][3]*dp2 + d[0][4]*ddp1 + d[0][5]*ddp2;
		e[1] = d[1][0]*p1 + d[1][1]*p2 + d[1][2]*dp1 + d[1][3]*dp2 + d[1][4]*ddp1 + d[1][5]*ddp2;
		e[2] = d[2][0]*p1 + d[2][1]*p2 + d[2][2]*dp1 + d[2][3]*dp2 + d[2][4]*ddp1 + d[2][5]*ddp2;
		e[3] = d[3][0]*p1 + d[3][1]*p2 + d[3][2]*dp1 + d[3][3]*dp2 + d[3][4]*ddp1 + d[3][5]*ddp2;
		e[4] = d[4][0]*p1 + d[4][1]*p2 + d[4][2]*dp1 + d[4][3]*dp2 + d[4][4]*ddp1 + d[4][5]*ddp2;
		e[5] = d[5][0]*p1 + d[5][1]*p2 + d[5][2]*dp1 + d[5][3]*dp2 + d[5][4]*ddp1 + d[5][5]*ddp2;
		
		
		*result = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);
		
		pSharedMemory->Hip_test5_a[1] = (float)(e[0] + e[1]*t + e[2]*t*t + e[3]*t*t*t + e[4]*t*t*t*t + e[5]*t*t*t*t*t);
		
		return 1;
	}
	
	else return 0;
}

char FTN_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<=temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<temp1))
	{
		*result=mag*(float)sin(2*PI*(float)(time-temp)/(float)(during-(delay1+delay2)));
		return 1;
	}
	else if(time>=temp1)
	{
		*result=0;
		return 2;
	}
	else return 3;
}

char FTN_half_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<=temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<temp1))
	{
		*result=mag*(float)sin(PI*(float)(time-temp)/(float)(during-(delay1+delay2)));
		return 1;
	}
	else if(time>=temp1)
	{
		*result=0;
		return 2;
	}
	else return 3;
}

char FTN_sinPI_half(float mag, long time, long start, long during, int delay1, int delay2, float *result)
{
	long	temp,temp1;
	temp=start+delay1;
	temp1=start+during-delay2;
	
	if(time<=temp)
	{
		*result=0;
		return 0;
	}
	else if((time>=temp)&&(time<temp1))
	{
		*result=(float)(mag*(PI/2)*(float)sin(PI*(float)(time-temp)/(float)(during-(delay1+delay2))));
		return 1;
	}
	else if(time>=temp1)
	{
		*result=0;
		return 2;
	}
	else return 3;
}

char FTN_sign(float input)
{
	if(input>0)			return 1;
	else if(input<0)	return -1;
	else				return 0;
}


unsigned char PROF_ftn_1_cos(
							 unsigned long TIMEindex,unsigned long TIMEstart,
							 unsigned long TIMEduring,unsigned long TIMEstop,
							 unsigned char TIMEselect,unsigned long TIMEdelay,
							 unsigned char PROFhold, float *PROFresult)
{
	static int PROFst;
	static int CYCLEhalf=0;
	static long TIMElocal;
	
	if(TIMEselect==0) TIMEstop=TIMEstart+TIMEduring;
	else if(TIMEselect==1) TIMEduring=TIMEstop-TIMEstart;
	else if(TIMEselect==2)
	{
		TIMEstart=TIMEstop-TIMEduring;
	}
	TIMElocal=TIMEindex-TIMEstart;
	CYCLEhalf=(TIMEduring-TIMEdelay);
	////////////////////////////
	// Generate Profile Here!!!
	////////////////////////////
	if(PROFhold==0)
	{
		if(TIMEindex<TIMEstart)
			*PROFresult=0;
		else if((TIMEindex>=TIMEstart)&&(TIMEindex<=TIMEstop-TIMEdelay))
			*PROFresult= (float)((1-cos(PI*TIMElocal/CYCLEhalf))/2.);
		else if((TIMEindex>TIMEstop-TIMEdelay)&&(TIMEindex<=TIMEstop))
			*PROFresult=*PROFresult;
		else *PROFresult=*PROFresult;
	}
	else if(PROFhold==1)
		*PROFresult=*PROFresult;
	////////////////////////////
	
	if(TIMElocal<0) PROFst=0;
	else if((TIMElocal>=0)&&(TIMElocal<=TIMEduring))
	{
		if(TIMElocal==0)	PROFst=1; // Just Started Status
		else				PROFst=2; // Running Status
	}
	else 
	{
		PROFst=4;
	}
	return PROFst;
}

int half_cyclUP(float *value,unsigned long time,unsigned long from,unsigned long during)
{ // from 0~0.5    below y=x curve
	static float t;
	
	t=((float)(time-from)) / ((float)during) ;
	
	if( (time>=from)&&(time<=(from+during)) )
	{
		*value=(float)(0.5*(t-sin(3.141592*t)/3.141592 )) ;
		return 1;
	}
	else if(time < from){
		return 0;
	}
	else if(time > (from + during)){
		return 2;
	}
}

int half_cyclDN(float *value,unsigned long time,unsigned long from,unsigned long during) // 10ms unit (during>0)
{ // from 0.5~1	upper y=x curve
	// CAUTION time index !!! (from-1)
	static float t;
	
	//	t=((float)(time-(from-1)))/((float)during);
	t=((float)(time-from))/((float)during);
	
	if( (time>=from)&&(time<=(from+during)) )
	{
		*value=(float)(0.5*(t+sin(3.141592*t)/3.141592));  // plus
		return 1;
	}
	else if(time < from){
		return 0;
	}
	else if(time > (from + during)){
		return 2;
	}
	
}

int delayhalf1_cosdelay(long delay,float *value,float mag,unsigned long time,unsigned long from,unsigned long during)
{ // if(delay>0) return from 000,0~1, 111
	// else between 1_cos (at delay=0) and line(at delay=-10)
	static float value1,value2;
	
	if(delay>0)
	{
		if( (time>=from)&&(time<=(from+during)) )
		{
			if(time<from+delay) *value=0.;
			else if(time>from+during-delay) *value=1.;
			else *value=(float)(0.5*mag*(1.-cos( PI*((float)(time-from-delay)) / ((float)(during-2*delay)) ))) ;
			return 1;
		}
		else if(time < from){
			return 0;
		}
		else if(time > (from + during)){
			return 2;
		}
	}
	else // between  1_cos and line
	{
		if(delay<-10) delay=-10;
		
		if( (time>=from)&&(time<=(from+during)) )
		{
			value1=(float)(0.5*mag*(1.-cos( PI*((float)(time-from)) / ((float)during) )));
			value2=mag*((float)(time-from)) / ((float)during) ;
			*value=(float)(value2+(float)(delay+10)/10.*(value1-value2));
			
			return 1;
		}
		else if(time < from){
			return 0;
		}
		else if(time > (from + during)){
			return 2;
		}
		
	}

}
