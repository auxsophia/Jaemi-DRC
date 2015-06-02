

char FTN_half_1pcos(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_half_1pcosFOOTZ(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_quarter_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_quarter_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_half_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_1_cos(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_half_1_cos_linear(float mag, long time, long start, long during, int delay, int MAX_D, float *result);
char FTN_quater_1_cos_UP(float mag, long time, long start, long during, int delay, float *result);
char FTN_quater_1_cos_DN(float mag, long time, long start, long during, int delay, float *result);
char FTN_cyclUP(float mag, long time, long start, long during, long delay, float SF, float *result);
char FTN_cyclDN(float mag, long time, long start, long during, long delay, float SF, float *result);
char FTN_cyclUPvel(float mag, long time, long start, long during, long delay, float SF, float *result);
char FTN_cyclDNvel(float mag, long time, long start, long during, long delay, float SF, float *result);
char FTN_cyclVel(float mag, long time, long start, long during, long delay, float SF, float *result);
char FTN_3poly0(float t0, float t, float p1, float dp1, float p2, float dp2, float *result);
char FTN_3poly1(float t0, float t, float p1, float dp1, float p2, float dp2, float *result);
char FTN_3poly(float t, float p1, float dp1, float p2, float dp2, float *result);
char FTN_5poly0(float t0, float t, float p1, float dp1, float p2, float dp2, float ddp1, float ddp2, float *result);
char FTN_5poly1(float t0, float t, float p1, float dp1, float p2, float dp2, float ddp1, float ddp2, float *result);
char FTN_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_half_sin(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_sinPI_half(float mag, long time, long start, long during, int delay1, int delay2, float *result);
char FTN_sign(float input);

// kirk`s function
unsigned char PROF_ftn_1_cos(											// 1-Cos ÇÔ¼ö Generator
							 unsigned long TIMEindex,unsigned long TIMEstart,
							 unsigned long TIMEduring,unsigned long TIMEstop,
							 unsigned char TIMEselect,unsigned long TIMEdelay,
							 unsigned char PROFhold, float *PROFresult);
int half_cyclUP(float *value,unsigned long time,unsigned long from,unsigned long during);
int half_cyclDN(float *value,unsigned long time,unsigned long from,unsigned long during); // 10ms unit (during>0)
int delayhalf1_cosdelay(long delay,float *value,float mag,unsigned long time,unsigned long from,unsigned long during);