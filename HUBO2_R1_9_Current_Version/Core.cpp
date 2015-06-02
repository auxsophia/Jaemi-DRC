////////////////////////////////////////////////////////////
//
//	Main control program for HUBO2
//	Designed by Kim Min su
//	Humanoid Robot Research Center
//
////////////////////////////////////////////////////////////


#include "RTX.h"
#include "CAN.h"
#include "HUBOVar.h"
#include "Profile.h"
#include "FUNCTION.h"
#include "MotorParameter.h"
#include "fstream.h"
#include "math.h"
#include "Control.h"

PSHARED_DATA pSharedMemory;	// shared memory data
HANDLE hSharedMemory;		// shared memory handler
HANDLE hTimer;				// 2 msec(500 Hz) timer handle
HANDLE hTimer2;				// 10 msec(100 Hz) timer handle

MYCAN CAN[2];
MYMB MB[MBSIZE];

UCHAR TxData[8];

void LoadParameter();
void ALLTILTRead();
void ALLFTRead();
void ALLEncRead();
void ALLPOSCTRL();
void FootAccReset();
void SharedMEMUpdate();
void InitParameters();
void ReadSensor(void);
void RequestSensor(unsigned char mode);
void RTFCNDCL TimerHandler(PVOID context);
void RTFCNDCL TimerHandler2(PVOID context);
void RTxMoveAng(unsigned char moID,float angle);
void UpperBody_RTxMoveAng(unsigned char moID, float angle);
//UINT SignFunc(long value);
unsigned long SignFunc(long value);
unsigned long HandSignFunc(long value);
void RefPosCmd();
void LegKine(BOOL Tocken);
void DataSave();
void DataSave1();
void DataSave2();
void DataSave3();
void AnkleCompensationRoll();
void ControlVarReset();
float C1_cosRecover(float oldData, float diffData, unsigned int Time, unsigned int start, unsigned int during);
void WalkAnkVarReset();
void GYRO_Reset(char RotAXIS);
void KeepGoing();
void InitCTRL();
void InitCTRLVar();
void InitVarSet(unsigned char mode);
void SSP_OL_L_Pose();
void SSP_OL_R_Pose();
void AnkleRollCompenBackUP();
void UpperMove();
// Kirk`s walking function
void Walking_On_Spot();
void Forward_Walking();
void Backward_Walking();
void Left_Side_Walking();
void Right_Side_Walking();
void Left_Turn_Walking();
void Right_Turn_Walking();
void Damping_control_init();
void Landing_control_init();
void WristMotion();
void ShoulderTestMotion();
void WristConfigureMotion();	// Elbow up to show wrist motion
void ShakeHands();				// shake hands using wrist F/T sensor
void JMC_STATE();


void BCDataCont();		// ZMP initialization
void BCDataCont0();		// for single supprt pose
void BCDataCont2();		// For SwayAdjustment


void main(void)
{
	RtxInit();
	//LoadParameter();
	InitPROFVar();	// variable initialization in profile.cpp
	InitParameters();
	StartCAN();
	
	while((pSharedMemory->bExitFlag)==FALSE)
	{		
		RtSleep(5);

		if(pSharedMemory->LoadParameterFlag == TRUE) LoadParameter();
	
		if(pSharedMemory->Tx_Flag == TRUE)
		{
			CanSendMsg(0, pSharedMemory->Tx_ID, pSharedMemory->Tx_Data, pSharedMemory->Tx_DLC, 0);
			pSharedMemory->Tx_Flag = FALSE;
			//RtWprintf(L"\n No : %x \t CMD : %x \t data : %x",pSharedMemory->Tx_Data[0], pSharedMemory->Tx_Data[1], pSharedMemory->Tx_Data[2]);
		}

		if(pSharedMemory->Tx1_Flag == TRUE)
		{
			CanSendMsg(1, pSharedMemory->Tx1_ID, pSharedMemory->Tx1_Data, pSharedMemory->Tx1_DLC, 0);
			pSharedMemory->Tx1_Flag = FALSE;
		}

		//if(pSharedMemory->Rx_Flag == TRUE)
		{
			CanReceiveMsg(0);		// 1st channel
			CanReceiveMsg(1);		// 2nd channel

			JMC_STATE();
		}
		
	}
	
	RtxEnd();
}

void JMC_STATE()
{
	int ii;
	int buff_no;

	int ch1[TOTAL_JMC_NUM];
	int ch2[TOTAL_JMC_NUM];

	int ch1_ex[TOTAL_EJMC_NUM];
	int ch2_ex[TOTAL_EJMC_NUM];
	int ch3_ex[TOTAL_EJMC_NUM];
	
	buff_no = 288;

	for(ii=0;ii<TOTAL_JMC_NUM;ii++)
	{
		ch1[ii] = pSharedMemory->Rx_Data[buff_no+ii][5] & 0x70;
		ch2[ii] = pSharedMemory->Rx_Data[buff_no+ii][6] & 0x70;

		switch(ii)
		{
		case JMC0:
			pSharedMemory->Motor_State[RHY] = ch1[ii];
			pSharedMemory->Motor_State[RHR] = ch2[ii];
			break;
		case JMC1:
			pSharedMemory->Motor_State[RHP] = ch1[ii];
			break;
		case JMC2:
			pSharedMemory->Motor_State[RKN] = ch1[ii];
			break;
		case JMC3:
			pSharedMemory->Motor_State[RAP] = ch1[ii];
			pSharedMemory->Motor_State[RAR] = ch2[ii];
			break;
		case JMC4:
			pSharedMemory->Motor_State[LHY] = ch1[ii];
			pSharedMemory->Motor_State[LHR] = ch2[ii];
			break;
		case JMC5:
			pSharedMemory->Motor_State[LHP] = ch1[ii];
			break;
		case JMC6:
			pSharedMemory->Motor_State[LKN] = ch1[ii];
			break;
		case JMC7:
			pSharedMemory->Motor_State[LAP] = ch1[ii];
			pSharedMemory->Motor_State[LAR] = ch2[ii];
			break;
		case JMC8:
			pSharedMemory->Motor_State[RSP] = ch1[ii];
			pSharedMemory->Motor_State[RSR] = ch2[ii];
			break;
		case JMC9:
			pSharedMemory->Motor_State[RSY] = ch1[ii];
			pSharedMemory->Motor_State[REB] = ch2[ii];
			break;
		case JMC10:
			pSharedMemory->Motor_State[LSP] = ch1[ii];
			pSharedMemory->Motor_State[LSR] = ch2[ii];
			break;
		case JMC11:
			pSharedMemory->Motor_State[LSY] = ch1[ii];
			pSharedMemory->Motor_State[LEB] = ch2[ii];
			break;
		}	
	}

	for(ii=0;ii<TOTAL_EJMC_NUM;ii++)
	{
		ch1_ex[ii] = pSharedMemory->Rx_Data[buff_no+ii][5] & 0x70;
		ch2_ex[ii] = pSharedMemory->Rx_Data[buff_no+ii][6] & 0x70;
		ch3_ex[ii] = pSharedMemory->Rx_Data[buff_no+ii][7] & 0x70;

		switch(ii+EJMC0)
		{
		case EJMC0:
			pSharedMemory->Motor_State[RWY] = ch1_ex[ii];
			pSharedMemory->Motor_State[RW1] = ch2_ex[ii];
			pSharedMemory->Motor_State[RW2] = ch3_ex[ii];
			break;
		case EJMC1:
			pSharedMemory->Motor_State[LWY] = ch1_ex[ii];
			pSharedMemory->Motor_State[LW1] = ch2_ex[ii];
			pSharedMemory->Motor_State[LW2] = ch3_ex[ii];
			break;
		case EJMC2:
			pSharedMemory->Motor_State[NKY] = ch1_ex[ii];
			pSharedMemory->Motor_State[NK1] = ch2_ex[ii];
			pSharedMemory->Motor_State[NK2] = ch3_ex[ii];
			break;
		case WST:
			pSharedMemory->Motor_State[WST] = ch1_ex[ii];
			break;
		}
	}



}

void ReadSensor(void)
{

	int temp_count = 0;
	int ck_no = 200;
	
	while(CanReceiveMsg(0, SENSOR_FT1_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[0] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_FT2_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[1] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_AD1_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[2] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_AD2_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[3] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	/*
	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_IMU1_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[4] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	// IMU2 is uses temporary.
	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_IMU2_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[5] = (float)temp_count;
		if(temp_count > ck_no) break;
	}*/

	temp_count = 0;
	while(CanReceiveMsg(0, SENSOR_IMU3_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[6] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

	temp_count = 0;
	while(CanReceiveMsg(1, SENSOR_FT3_RXDF)==ERR_NODATA)
	{
		temp_count++;
		tp_cnt[6] = (float)temp_count;
		if(temp_count > ck_no) break;
	}

}
void RequestSensor(unsigned char mode)
{
	unsigned char data = mode;
	CanSendMsg(0, SEND_SENSOR_TXDF, &mode, 1, 0);
	CanSendMsg(1, SEND_SENSOR_TXDF, &mode, 1, 0);
	
}



// 500 Hz timer interrupt
void RTFCNDCL TimerHandler(PVOID context)
{	
	int i;
	unsigned char data[6] = {0,0,0,0,0,0};


	/*
	LARGE_INTEGER testtime1;
	LARGE_INTEGER testtime2;
	
	RtGetClockTime(CLOCK_2,&testtime1);
	*/

	SharedMEMUpdate();
	if(pSharedMemory->INT_Flag == TRUE)
	{
		RequestSensor(0x00);

		// To do /////////////////////////////
		
		if(pSharedMemory->DataSaveFlag == TRUE) DataSave3();
		
		if(pSharedMemory->Read_TILT_Flag == TRUE)
		{
			ALLTILTRead();
		}
				  
		if(pSharedMemory->Read_FTS_Flag == TRUE)
		{
			ALLFTRead();
		}

		if(pSharedMemory->POS_CTRL_Flag == TRUE)
		{
			ALLPOSCTRL();
			pSharedMemory->RTX_Index++;
		}

		// walk ready position
		if(pSharedMemory->Walk_Ready_Flag == TRUE)
		{
			WalkReady(pSharedMemory->PROFTime[0]);
			pSharedMemory->PROFTime[0]++;
			
			if(pSharedMemory->PROFTime[0] > READYTIME+2)
			{
				LegKine(0);

			}
			else
			{
				
				LegKine(1); // Inverse 우선 모드 "0", Forward 우선 모드 "1"
				UpperMove();

				RTX_COMPEN_Ankle_Roll[LEFT][0] = 0.;
				RTX_COMPEN_Ankle_Roll[RIGHT][0] = 0.;
			}
			
			RefPosCmd();
	
		}

		////// Home Position
		if(pSharedMemory->Home_Flag == TRUE) // Homing 프로파일 (각도 제어 모드)
		{
			Home(pSharedMemory->PROFTime[1]);
			pSharedMemory->PROFTime[1]++;
			//
			LegKine(1); // Inverse 우선 모드 "0", Forward 우선 모드 "1"
			UpperMove();

			RefPosCmd();
		}

		////// Walk test mode
		if(pSharedMemory->Walk01Test_Flag == TRUE)
		{
			
			LegKine(0);
			pSharedMemory->PROFTime[2]++;
			
			RefPosCmd();
			
			if(pSharedMemory->PROFTime[2]>=1000*TS)
			{
				pSharedMemory->Walk01Test_Flag = FALSE;
			}
		}

		////// Initialize with balance
		if(pSharedMemory->Ini_ZMP_Zero_Flag == TRUE) // 초기 ZMP세팅 시 작동 
		{
			OL_y = L0 + WLK_RDY_OFFSET;
			OR_y = -L0 - WLK_RDY_OFFSET;
			OL_x = 0.;
			OR_x = 0.;
			
			if(pSharedMemory->ZMP_Zero_Set_Flag == FALSE)
			{
				// Initialize: Variables and Functions for ZMP zero setting Here !!
				// This routine starts at walk ready mode..
				CTRL_VariableInit00();		// control variable which is used in ZMP initialization is reset
				InitCTRLVar();
				CTRL_new_compen(0,0);
				//InitOnOffAnkleRoll(1); // Ankle Roll On
			}
			else if(pSharedMemory->ZMP_Zero_Set_Flag == TRUE)
			{
				// Initialize ZMP Zero Start
				InitCTRL();
				//BCDataCont();
				LegKine(0); // Inverse 우선 모드 "0", Forward 우선 모드 "1"
				RefPosCmd();
			}
		}
		else if(pSharedMemory->Ini_ZMP_Zero_Flag == FALSE)
		{	
			if(pSharedMemory->ZMP_Zero_Set_Flag == TRUE)
			{ 
				InitVarSet(0);
			}
			else if(pSharedMemory->ZMP_Zero_Set_Flag == FALSE)
			{
				InitVarSet(1);
				//InitOnOffAnkleRoll(1);		
				RefPosCmd();
				InitVarSet(2);
			}
		}

		if(pSharedMemory->SSP_OL_L_Pose_Flag == TRUE) // R Foot Support
		{
			SSP_OL_L_Pose();
		}

		if(pSharedMemory->SSP_OL_R_Pose_Flag == TRUE) // L Foot Support
		{
			SSP_OL_R_Pose();
		}

		/*
		if((pSharedMemory->WristConfigureFlag == 1) || (pSharedMemory->WristConfigureFlag == 2))
		{
			if(pSharedMemory->WristConfigureFlag == 1) 
			{
				UpperBodyTime[5] = 0;
				pSharedMemory->WristConfigureFlag = 2;
			}

			PROF_WristConfigure1(UpperBodyTime[5]);

			if(UpperBodyTime[5] > 100*TS) pSharedMemory->WristConfigureFlag = 0;

			UpperMove();
			RefPosCmd();
		}
		*/
		
		// Wrist motion	///////////////////////////////////////////////////////////////////////////////
		if(pSharedMemory->Kirk_WalkingFlag == FALSE) 
		{
			WristMotion();
			//UpperMove();
			//RefPosCmd();
		}
		
		// Shoulder test motion //////////////////////////////////////////////////////////////////////
		if(pSharedMemory->Kirk_WalkingFlag == FALSE) 
		{
			ShoulderTestMotion();
			//UpperMove();
			//RefPosCmd();
		}

		// Elbow up to show wrist motion
		if(pSharedMemory->Kirk_WalkingFlag == FALSE) 
		{
			WristConfigureMotion();
			//UpperMove();
			//RefPosCmd();
		}

		if((pSharedMemory->HandMotionFlag == 1) || (pSharedMemory->HandMotionFlag == 2))	// Finger motion
		{
			UpperBodyTime[4]++;
			
			if(UpperBodyTime[4] >= ((1/DELTA_T)/(pSharedMemory->HandFreq))) UpperBodyTime[4] = 0;
			
			PROF_Hand_Shake(UpperBodyTime[4]);
			
			if((pSharedMemory->HandMotionFlag == 2) && (UpperBodyTime[4] == 0)) pSharedMemory->HandMotionFlag = 0;
			
			UpperMove();
			RefPosCmd();
			
		}
		else if(pSharedMemory->HandMotionFlag == 0)
		{
			UpperBodyTime[4] = 0;
		}		
			

		// ZMP CTRL Test in DSP
		if(pSharedMemory->TestModeFlag == TRUE)
		{
			if(pSharedMemory->ZMP_DSP_CTRL_Flag == 1)
			{	
				if(Read_ZMP_Flag == FALSE)
				{
					Init_DSP_ZMP[0] = (Xzmp_lp - Init_Xzmp);
					Init_DSP_ZMP[1] = Yzmp_lp;
					Read_ZMP_Flag = TRUE;
					pSharedMemory->PROFTime[22] = 0;
					
					ZMP_DSP_Angle[1] = (float)(pSharedMemory->ZMP_DSP_Y_Gain*DSP_ZMP_Y(DSP_ZMPRef[1], Yzmp_lp, 0, pSharedMemory->ZMP_DSP_Y_IntegralGain));
					ZMP_DSP_Angle[0] = (float)(pSharedMemory->ZMP_DSP_X_Gain*DSP_ZMP_X(DSP_ZMPRef[0], (Xzmp_lp - Init_Xzmp), 0, pSharedMemory->ZMP_DSP_Y_IntegralGain));
				}
				
				pSharedMemory->PROFTime[22]++;
				
				if(pSharedMemory->PROFTime[22] < (10*TS)) 
				{
					DSP_ZMPRef[1] = (float)(Init_DSP_ZMP[1]*(1. - (pSharedMemory->PROFTime[22]/(10.*TS))));
					DSP_ZMPRef[0] = (float)(Init_DSP_ZMP[0]*(1. - (pSharedMemory->PROFTime[22]/(10.*TS))));
				}
				else DSP_ZMPRef[1] = (float)0.;
				
				ZMP_DSP_Angle[1] = (float)(pSharedMemory->ZMP_DSP_Y_Gain*DSP_ZMP_Y(DSP_ZMPRef[1], Yzmp_lp, 1, pSharedMemory->ZMP_DSP_Y_IntegralGain));
				ZMP_DSP_Angle[0] = (float)(pSharedMemory->ZMP_DSP_X_Gain*DSP_ZMP_X(DSP_ZMPRef[0], (Xzmp_lp - Init_Xzmp), 1, pSharedMemory->ZMP_DSP_Y_IntegralGain));
								
				LegKine(0);
				RefPosCmd();
			}
			else if(pSharedMemory->ZMP_DSP_CTRL_Flag == 2)
			{
				ZMP_DSP_Angle_old[1] = ZMP_DSP_Angle[1];
				ZMP_DSP_Angle_old[0] = ZMP_DSP_Angle[0];
				pSharedMemory->ZMP_DSP_CTRL_Flag = 3;
				pSharedMemory->PROFTime[22] = 0;
				Read_ZMP_Flag = FALSE;
			}
			else if(pSharedMemory->ZMP_DSP_CTRL_Flag == 3)
			{
				if(pSharedMemory->PROFTime[22] == (100*TS)) pSharedMemory->ZMP_DSP_CTRL_Flag = 0;
				
				FTN_half_1_cos(-ZMP_DSP_Angle_old[1], pSharedMemory->PROFTime[22], 0, (long)(100*TS), 0, 0, &tp_ZMP_DSP_Angle[1]);
				ZMP_DSP_Angle[1] = ZMP_DSP_Angle_old[1] + tp_ZMP_DSP_Angle[1];
				
				FTN_half_1_cos(-ZMP_DSP_Angle_old[0], pSharedMemory->PROFTime[22], 0, (long)(100*TS), 0, 0, &tp_ZMP_DSP_Angle[0]);
				ZMP_DSP_Angle[0] = ZMP_DSP_Angle_old[0] + tp_ZMP_DSP_Angle[0];
				
				pSharedMemory->PROFTime[22]++;
				
				LegKine(0);
				RefPosCmd();
			}
			else
			{
				ZMP_DSP_Angle[0] = (float)0.;
				ZMP_DSP_Angle[1] = (float)0.;
				//Read_ZMP = FALSE;
			}
		}
		

		/////// Walking Experiment00 Routine Starts here
		//if(pSharedMemory->WalkingExp00_Flag == TRUE)
		if(pSharedMemory->Kirk_WalkingFlag == TRUE)
		{	
			//if(pSharedMemory->Mark_Time_Flag && WLK_RDY_MODE == 1 && pSharedMemory->FSM == 0) // 제자리걸음 , Left Foot Starting
			//if(pSharedMemory->Mark_Time_Flag == TRUE && pSharedMemory->Walk_Ready_Flag == TRUE && pSharedMemory->FSM == 0) // 제자리걸음 , Left Foot Starting
			if(pSharedMemory->Mark_Time_Flag == TRUE && pSharedMemory->FSM == FALSE) // 제자리걸음 , Left Foot Starting
			{
				Walking_On_Spot();
				LegKine(0);
				//UpperMove();
				//RefPosCmd();
			}
			//else if(pSharedMemory->Walk_FWD_Flag && pSharedMemory->Walk_Ready_Flag == TRUE && pSharedMemory->FSM == 0)
			else if(pSharedMemory->Walk_FWD_Flag && pSharedMemory->FSM == 0)
			{
				Forward_Walking();
				LegKine(0);
			}
			else if(pSharedMemory->Walk_BWD_Flag && pSharedMemory->FSM == 1) // Go Forward with Right Foot Starting
			{
				Backward_Walking();
				LegKine(0);
			}
			else if(pSharedMemory->Walk_L_Side_Flag == TRUE) // Walk Foward with Left Foot Starting
			{
				Left_Side_Walking();
				LegKine(0);
			}
			else if(pSharedMemory->Walk_R_Side_Flag) // Go Forward with Right Foot Starting
			{
				Right_Side_Walking();
				LegKine(0);
			}
			else if(pSharedMemory->Walk_CCW_Turn_Flag)
			{
				Left_Turn_Walking();
				LegKine(0);
			}
			else if(pSharedMemory->Walk_CW_Turn_Flag)
			{
				Right_Turn_Walking();
				LegKine(0);
			}

			pSharedMemory->Int_CNT = pSharedMemory->Int_CNT + 1; 
			
		// upperbody motion //
		if((InvFlag == TRUE)&&(pSharedMemory->TestModeFlag == FALSE))
		{
			if((pSharedMemory->Walk_Ready_Flag == FALSE)&&(pSharedMemory->Home_Flag == FALSE))
			{
				////// Shake arms during walking ////	
				if(pSharedMemory->Arm_Motion == TRUE)
				{
					UpperBodyTime[1] = 0;
				}
				else if((pSharedMemory->Arm_Motion == FALSE)&&(pSharedMemory->MotionFlagALL == 0))
				{
					UpperBodyTime[1]++;
					//pSharedMemory->SaveData[pSharedMemory->PROFTime[19]][0]++;
				}
				/////////////////////////////////////
				
				if(pSharedMemory->Gesture_Flag == TRUE)
				{
					if(pSharedMemory->MotionFlag[1] == TRUE)
					{
						PROF_MotionPlay1(pSharedMemory->MotionLength[1],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[2] == TRUE)
					{	
						PROF_MotionPlay2(pSharedMemory->MotionLength[2],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[3] == TRUE)
					{	
						PROF_MotionPlay3(pSharedMemory->MotionLength[3],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[4] == TRUE)
					{	
						PROF_MotionPlay4(pSharedMemory->MotionLength[4],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[5] == TRUE)
					{	
						PROF_MotionPlay5(pSharedMemory->MotionLength[5],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[6] == TRUE)
					{	
						PROF_MotionPlay6(pSharedMemory->MotionLength[6],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[7] == TRUE)
					{	
						PROF_MotionPlay7(pSharedMemory->MotionLength[7],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[8] == TRUE)
					{	
						PROF_MotionPlay8(pSharedMemory->MotionLength[8],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[9] == TRUE)
					{	
						PROF_MotionPlay9(pSharedMemory->MotionLength[9],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[10] == TRUE)
					{	
						PROF_MotionPlay10(pSharedMemory->MotionLength[10],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[11] == TRUE)
					{	
						PROF_MotionPlay11(pSharedMemory->MotionLength[11],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[12] == TRUE)
					{	
						PROF_MotionPlay12(pSharedMemory->MotionLength[12],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[13] == TRUE)
					{	
						PROF_MotionPlay13(pSharedMemory->MotionLength[13],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[14] == TRUE)
					{	
						PROF_MotionPlay14(pSharedMemory->MotionLength[14],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[15] == TRUE)
					{	
						PROF_MotionPlay15(pSharedMemory->MotionLength[15],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[16] == TRUE)
					{	
						PROF_MotionPlay16(pSharedMemory->MotionLength[16],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[17] == TRUE)
					{	
						PROF_MotionPlay17(pSharedMemory->MotionLength[17],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[18] == TRUE)
					{	
						PROF_MotionPlay18(pSharedMemory->MotionLength[18],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[19] == TRUE)
					{	
						PROF_MotionPlay19(pSharedMemory->MotionLength[19],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[20] == TRUE)
					{	
						PROF_MotionPlay20(pSharedMemory->MotionLength[20],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[21] == TRUE)
					{	
						PROF_MotionPlay21(pSharedMemory->MotionLength[21],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[22] == TRUE)
					{	
						PROF_MotionPlay22(pSharedMemory->MotionLength[22],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[23] == TRUE)
					{	
						PROF_MotionPlay23(pSharedMemory->MotionLength[23],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[24] == TRUE)
					{	
						PROF_MotionPlay24(pSharedMemory->MotionLength[24],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[25] == TRUE)
					{	
						PROF_MotionPlay25(pSharedMemory->MotionLength[25],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[26] == TRUE)
					{	
						PROF_MotionPlay26(pSharedMemory->MotionLength[26],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[27] == TRUE)
					{	
						PROF_MotionPlay27(pSharedMemory->MotionLength[27],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[28] == TRUE)
					{	
						PROF_MotionPlay28(pSharedMemory->MotionLength[28],pSharedMemory->MOTION_Stop);
					}
					else if(pSharedMemory->MotionFlag[29] == TRUE)
					{	
						PROF_MotionPlay29(pSharedMemory->MotionLength[29],pSharedMemory->MOTION_Stop);
					}
					// Custom Gestures begin here

					//Gestures for Either arm (Right)
					else if(pSharedMemory->MotionFlag[30] == TRUE)
					{	
						Motion_RaiseRightHand(pSharedMemory->MotionLength[30],pSharedMemory->MOTION_Stop,30);
					}
					else if(pSharedMemory->MotionFlag[31] == TRUE)
					{	
						Motion_RaiseRightArm(pSharedMemory->MotionLength[31],pSharedMemory->MOTION_Stop,31);
					}
					else if(pSharedMemory->MotionFlag[32] == TRUE)
					{	
						Motion_RightArmCircle(pSharedMemory->MotionLength[32],pSharedMemory->MOTION_Stop,32);
					}

					//Gestures for Either arm (Left
					else if(pSharedMemory->MotionFlag[33] == TRUE)
					{	
						Motion_RaiseLeftHand(pSharedMemory->MotionLength[33],pSharedMemory->MOTION_Stop,33);
					}
					else if(pSharedMemory->MotionFlag[34] == TRUE)
					{	
						Motion_RaiseLeftArm(pSharedMemory->MotionLength[34],pSharedMemory->MOTION_Stop,34);
					}
					else if(pSharedMemory->MotionFlag[35] == TRUE)
					{	
						Motion_LeftArmCircle(pSharedMemory->MotionLength[35],pSharedMemory->MOTION_Stop,35);
					}
					
					//Gestures for Right Arm ONLY
					else if(pSharedMemory->MotionFlag[36] == TRUE)
					{	
						Motion_TouchHead(pSharedMemory->MotionLength[36],pSharedMemory->MOTION_Stop,36);
					}
					else if(pSharedMemory->MotionFlag[37] == TRUE)
					{	
						Motion_TouchNose(pSharedMemory->MotionLength[37],pSharedMemory->MOTION_Stop,37);
					}
					else if(pSharedMemory->MotionFlag[38] == TRUE)
					{	
						Motion_TipHat(pSharedMemory->MotionLength[38],pSharedMemory->MOTION_Stop,38);
					}
					else if(pSharedMemory->MotionFlag[40] == TRUE)
					{	
						Motion_ChooChoo(pSharedMemory->MotionLength[40],pSharedMemory->MOTION_Stop,40);
					}
					else if(pSharedMemory->MotionFlag[39] == TRUE)
					{	
						Motion_RubStomach(pSharedMemory->MotionLength[39],pSharedMemory->MOTION_Stop,39);
					}
					// Gestures using both arms simultaneously
					else if(pSharedMemory->MotionFlag[41] == TRUE)
					{	
						Motion_ClapHands(pSharedMemory->MotionLength[41],pSharedMemory->MOTION_Stop,41);
					}
					else if(pSharedMemory->MotionFlag[42] == TRUE)
					{	
						Motion_FlapArms(pSharedMemory->MotionLength[42],pSharedMemory->MOTION_Stop,42);
					}
					else if(pSharedMemory->MotionFlag[43] == TRUE)
					{	
						Motion_HandsOnHips(pSharedMemory->MotionLength[43],pSharedMemory->MOTION_Stop,43);
					}
					else if(pSharedMemory->MotionFlag[44] == TRUE)
					{
						Motion_PointRight(pSharedMemory->MotionLength[44], pSharedMemory->MOTION_Stop, 44);
					}
					else if(pSharedMemory->MotionFlag[45] == TRUE)
					{
						Motion_PointLeft(pSharedMemory->MotionLength[45], pSharedMemory->MOTION_Stop, 45);
					}
					else if(pSharedMemory->MotionFlag[46] == TRUE)
					{
						Motion_PointBothLeftRight(pSharedMemory->MotionLength[46], pSharedMemory->MOTION_Stop, 46);
					}
					else if(pSharedMemory->MotionFlag[47] == TRUE)
					{
						Motion_Aux_Bend_Right_Elbow(pSharedMemory->MotionLength[47], pSharedMemory->MOTION_Stop, 47);
					}
					else if(pSharedMemory->MotionFlag[48] == TRUE)
					{
						Motion_Aux_UNLV(pSharedMemory->MotionLength[48], pSharedMemory->MOTION_Stop, 48);
					}
					else if(pSharedMemory->MotionFlag[49] == TRUE)
					{
						Motion_Hello_World(pSharedMemory->MotionLength[49], pSharedMemory->MOTION_Stop, 49);
					}
				}
				//#################################### Scripting section ###############################################
				
				//this is a hack here, but hard-code the script until we figure out a better way
				static int Script1[]={30,33,31,34,36,40,41,42,30,33,33,32,43,31,30,33,30,34};
				static int Script2[]={33,39,36,30,36,33,43,42,41,31,34,30,34};
				static int ScriptLength1=18; //corresponds to above!
				static int ScriptLength2=13; //corresponds to above!
				static int MotionNo=0;

				if(pSharedMemory->MotionFlagALL==FALSE)
				{
					//If a script is loaded and a motion is completed
					switch(pSharedMemory->ScriptLoaded)
					{
					case 1:
						if(pSharedMemory->ScriptIndex < ScriptLength1)
						{
							MotionNo=Script1[pSharedMemory->ScriptIndex];
							pSharedMemory->MotionFlagALL = TRUE;
							pSharedMemory->MotionFlag[MotionNo] = TRUE;
							pSharedMemory->MOTION_Stop = 0;
							pSharedMemory->ScriptIndex++; //increment gesture command
						}
						break;
					case 2:
						if(pSharedMemory->ScriptIndex < ScriptLength2)
						{
							MotionNo=Script2[pSharedMemory->ScriptIndex];
							pSharedMemory->MotionFlagALL = TRUE;
							pSharedMemory->MotionFlag[MotionNo] = TRUE;
							pSharedMemory->MOTION_Stop = 0;
							pSharedMemory->ScriptIndex++; //increment gesture command
						}
						break;
					case 0:
					default:
						//do nothing, no script loaded
						break;
					}
					if(pSharedMemory->ScriptIndex >= ScriptLength2)
						{
							pSharedMemory->ScriptLoaded=FALSE;
							pSharedMemory->ScriptIndex=0;
						}
				}
				// End of gesture choices
			}
			

			// DSP CONTROL ///////////////////////////////////////////////////////
			if(pSharedMemory->Demo_4_Flag == 1)
			{
				
				if(pSharedMemory->Test_CNT_0 == 0) 
				{
					CTRL_new_compen(0,0); CTRL_new_compenfwd(0,0); angle_stiff_ds4(0,0,0,0); angle_stiff_fwR(0,0,0,0); 
					CTRL_dsp_compen_p(0,0);
					CTRL_dsp_compen_p2(0,0);
				} 

				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,0,80,0,0,0,0,&g_temp_theta_1);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,30,50,0,0,0,0,&g_temp_theta_2);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,80,80,0,0,0,0,&g_temp_theta_3);
	
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_1,0,80,0,0,0,0,&g_temp_theta_5);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_1,80,50,0,0,0,0,&g_temp_theta_6);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_1,100,50,0,0,0,0,&g_temp_theta_7);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_1,120,50,0,0,0,0,&g_temp_theta_8);
		
				DSP_temp_1 = 85.0*g_temp_theta_1 - 85.0*g_temp_theta_3 + 117.0*g_temp_theta_5 - 117.0*g_temp_theta_8; 
				DSP_temp_2 = 25.0*g_temp_theta_2 - 25.0*g_temp_theta_3 + 25.0*g_temp_theta_6 - 25.0*g_temp_theta_8;
				DSP_temp_3 = 35.0*g_temp_theta_3 - 35.0*g_temp_theta_7;
				DSP_temp_4 = 35.0*g_temp_theta_3 - 35.0*g_temp_theta_8;

				if(pSharedMemory->DSPS_Con_Flag)
				{
					DeltaMov_y_dsp = temp_DeltaMov_y + 0.8*CTRL_new_compen(Err_Yzmp,1); // PI
					DeltaMov_x_dsp = temp_DeltaMov_x + 0.6*CTRL_new_compenfwd(Err_Xzmp-Init_Xzmp,1); // P

					DeltaMov_x_dsp_old = DeltaMov_x_dsp;
					DeltaMov_y_dsp_old = DeltaMov_y_dsp;
				}
			
				if(pSharedMemory->Test_CNT_0 > 120 && pSharedMemory->Test_CNT_0 < 300)
				{
					OL_y = L0 + WLK_RDY_OFFSET + 35.0;
					OR_y = -L0 - WLK_RDY_OFFSET - 35.0;

					DeltaMov_y_dsp = (float)(0.8*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
					DeltaMov_x_dsp = (float)(0.8*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
					temp_DeltaMov_y = DeltaMov_y_dsp;
					temp_DeltaMov_x = DeltaMov_x_dsp;

					DeltaMov_x_dsp_old = DeltaMov_x_dsp;
					DeltaMov_y_dsp_old = DeltaMov_y_dsp;
				}
				else if(pSharedMemory->Test_CNT_0 < 100)
				{
					R_theta_compen_r = (DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0);
					R_theta_compen_p = -1.*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0);
				}
		
				if(pSharedMemory->Test_CNT_0 < 310) pSharedMemory->Test_CNT_0++;

				if(pSharedMemory->Demo_4_Off_Flag == 1)
				{
					DeltaMov_x_dsp = (float)(DeltaMov_x_dsp_old*(1 - g_temp_theta_5));
					DeltaMov_y_dsp = (float)(DeltaMov_y_dsp_old*(1 - g_temp_theta_5));


					if(pSharedMemory->Test_CNT_1 == 170)
					{
						pSharedMemory->Demo_4_Flag = 0;
						pSharedMemory->Demo_4_Off_Flag = 0;
						pSharedMemory->DSPS_Con_Flag = 0;
			
						angle_stiff_ds4(0,0,0,0);   
						angle_stiff_fwR(0,0,0,0);
						CTRL_new_compen(0,0); 
						CTRL_new_compenfwd(0,0);

						CTRL_dsp_compen_p(0,0);
						CTRL_dsp_compen_p2(0,0);
					
						OL_y = L0 + WLK_RDY_OFFSET ;
						OR_y = -L0 - WLK_RDY_OFFSET;

						DSP_temp_1 = DSP_temp_2 = DSP_temp_3 = DSP_temp_4 = 0.; 
						//pSharedMemory->bAction_Flag = FALSE;
					}
	
					if(pSharedMemory->Test_CNT_1 > 100 && pSharedMemory->Test_CNT_1 < 150)
					{
						R_theta_compen_r = (DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0);
						R_theta_compen_p = -1.0*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0);
					}

					if(pSharedMemory->Test_CNT_1 < 200) pSharedMemory->Test_CNT_1++;
				}
			}	// End of DSP control
			else if(pSharedMemory->Demo_5_Flag == 1)	// SSP control
			{
				if(pSharedMemory->Test_CNT_0 == 0) 
				{
					angle_stiff_ds4(0,0,0,0); angle_stiff_fwR(0,0,0,0); g_temp_theta_10 = g_temp_theta_11 = 0.;
					//SSP_RF_ZMP_CON_Y(0,0,0); SSP_RF_ZMP_CON_X(0,0,0);
					CTRL_new_compen(0.,0);
					CTRL_new_compenfwd(0, 0);
				} 

				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,0,80,0,0,0,0,&g_temp_theta_1);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,30,50,0,0,0,0,&g_temp_theta_2);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_1,0,80,0,0,0,0,&g_temp_theta_3);
						
				SSP_temp_1 = -80.0*g_temp_theta_1 + g_temp_theta_10 + (80.0 - g_temp_theta_10)*g_temp_theta_3 ;
				SSP_temp_2 = 35.0*g_temp_theta_2 - 35.0*g_temp_theta_3;
				SSP_temp_3 = -2.5*g_temp_theta_1 + 2.5*g_temp_theta_3;
				SSP_temp_5 = g_temp_theta_11 - g_temp_theta_11*g_temp_theta_3;
			
				if(pSharedMemory->Test_CNT_0 > 80 && pSharedMemory->Test_CNT_0 < 400)
				{ 
					g_temp_theta_10 = 0.5*CTRL_new_compen(Err_Yzmp-80.,1); // PI
					g_temp_theta_11 = 0.8*CTRL_new_compenfwd(Err_Xzmp,1); // P

				}

				if(pSharedMemory->SSPS_Con_Flag)
				{
					R_theta_compen_r = (DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0);
					R_theta_compen_p = -1.0*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0);

					//g_temp_theta_10 = 0.5*CTRL_new_compen(Err_Yzmp-80.,1); // PI
					//g_temp_theta_11 = 0.8*CTRL_new_compenfwd(Err_Xzmp,1); // P
					
				}

				if(pSharedMemory->Test_CNT_0 < 400) 
				{
					pSharedMemory->Test_CNT_0++;
					R_theta_compen_r = (DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0);
					R_theta_compen_p = -1.0*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0);
				}

				if(pSharedMemory->Demo_5_Off_Flag == 1)
				{
					DeltaMov_y = (float)(0.8*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
					DeltaMov_x = (float)(0.8*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P

					//DeltaMov_x_ssp = (float)(DeltaMov_x_ssp_old*(1. - g_temp_theta_3));

					if(pSharedMemory->Test_CNT_1 < 80) pSharedMemory->Test_CNT_1++;
					else
					{
						pSharedMemory->Demo_5_Flag = 0;
						pSharedMemory->Demo_5_Off_Flag = 0;
						pSharedMemory->SSPS_Con_Flag = 0;

						angle_stiff_ds4(0,0,0,0);   
						angle_stiff_fwR(0,0,0,0);

						R_theta_compen_r = 0;
						R_theta_compen_p = 0;

						SSP_temp_1 = SSP_temp_2 = 0.;
					}
				}			
			}	// End of SSP control
			else if(pSharedMemory->Demo_6_Flag == 1)
			{ // 한발 균형 잡기
				if(pSharedMemory->Test_CNT_0 == 0) 
				{
					angle_stiff_ds4(0,0,0,0); angle_stiff_fwR(0,0,0,0); 
					SSP_RF_ZMP_CON_Y(0,0,0); SSP_RF_ZMP_CON_X(0,0,0); 
					g_temp_theta_4 = 0.; Gesture_Pelvis_2 = g_temp_theta_13 = 0.;
					CTRL_new_compen(0,0);
					CTRL_new_compenfwd(0,0);
				}
			
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,0,100,0,0,0,0,&g_temp_theta_1); // 몸통 이동
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,50,50,0,0,0,0,&g_temp_theta_2); // 왼다리 lift
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,0,200,0,0,0,0,&g_temp_theta_5);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,200,200,0,0,0,0,&g_temp_theta_6);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,400,200,0,0,0,0,&g_temp_theta_7);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,600,200,0,0,0,0,&g_temp_theta_8);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,800,200,0,0,0,0,&g_temp_theta_9);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,1000,200,0,0,0,0,&g_temp_theta_10);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,1200,200,0,0,0,0,&g_temp_theta_11);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,1400,200,0,0,0,0,&g_temp_theta_12);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,1600,300,0,0,0,0,&g_temp_theta_14);
				PROF_ftn_1_cos(pSharedMemory->Test_CNT_0,2000,80,0,0,0,0,&g_temp_theta_3); // 제자리로

				if(pSharedMemory->Test_CNT_0 > 100 && pSharedMemory->Test_CNT_0 < 2000)	
				{ 
					//g_temp_theta_4 = 0.6*CTRL_new_compen(Err_Yzmp-80.,1); // PI
					//g_temp_theta_13 = 0.8*CTRL_new_compenfwd(Err_Xzmp,1); // P
					g_temp_theta_4 = SSP_RF_ZMP_CON_Y(-80, RTX_Yzmp,1);
					g_temp_theta_13 = SSP_RF_ZMP_CON_X(10, RTX_Xzmp, 1);
				}

				if(pSharedMemory->Test_CNT_0 > 50 && pSharedMemory->Test_CNT_0 < 120)	
				{
					Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); //발떨림 제거					
				}
				else if(pSharedMemory->Test_CNT_0 == 121) Del_Mov_LHip_r = 0.;

				SSP_temp_1 = -80.0*g_temp_theta_1 + g_temp_theta_4 + (80.0 - g_temp_theta_4)*g_temp_theta_3;
				SSP_temp_2 = 35.0*g_temp_theta_2 - 35.0*g_temp_theta_3;	
				SSP_temp_3 = -2.5*g_temp_theta_1 + 2.5*g_temp_theta_3;	
				SSP_temp_4 = -30.*g_temp_theta_8 + 30.*g_temp_theta_14;
				SSP_temp_5 = g_temp_theta_13 - g_temp_theta_13*g_temp_theta_3;
			
				R_theta_compen_r = (DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0);
				R_theta_compen_p = -1.0*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0);

				UpperMovement[RSR] = (float)(60*g_temp_theta_5 - 10*g_temp_theta_6 + 20*g_temp_theta_7 - 20*g_temp_theta_8 + 20*g_temp_theta_9 - 20*g_temp_theta_10 + 20*g_temp_theta_11 - 10*g_temp_theta_12 -60*g_temp_theta_14);
				UpperMovement[LSR] = (float)(-60*g_temp_theta_5 - 10*g_temp_theta_6 + 20*g_temp_theta_7 - 20*g_temp_theta_8 + 20*g_temp_theta_9 - 20*g_temp_theta_10 + 20*g_temp_theta_11 - 10*g_temp_theta_12 + 60*g_temp_theta_14);
			
				UpperMovement[REB] = (float)-20*g_temp_theta_5 + 20*g_temp_theta_14; 
				UpperMovement[LEB] = (float)-20*g_temp_theta_5 + 20*g_temp_theta_14;

				Gesture_Pelvis_2 = -20.*g_temp_theta_8 + 40.*g_temp_theta_9 - 40.*g_temp_theta_10 + 40.*g_temp_theta_11 - 40.*g_temp_theta_12 + 20.*g_temp_theta_14;

				pSharedMemory->Test_CNT_0++;

				if(pSharedMemory->Test_CNT_0 == 2080)
				{
					pSharedMemory->Demo_6_Flag = 0; 
					SSP_temp_1 = SSP_temp_2 = SSP_temp_3 = SSP_temp_4 = SSP_temp_5 = 0.; R_theta_compen_r = R_theta_compen_p = 0.; Gesture_Pelvis_1 = 0.;
				}
			} // End of else if(pSharedMemory->Demo_6_Flag == 1)


			if(pSharedMemory->Gesture_Flag == TRUE)
			{
				WristMotion();
				ShoulderTestMotion();
				WristConfigureMotion();

				if(pSharedMemory->ShakeHandsFlag != 0) ShakeHands();
			}

			//UpperBodyTime[0]++;
			//////////
			UpperMove();
			RefPosCmd();
		}
		

		}
		else if(pSharedMemory->WalkingExp00_Flag == FALSE)
		{
			// RTX_DeltaMove1 & 3 is related to ZMP control
			//RTX_DeltaMove1[0] = 0.;//RTX_DeltaMove[0];
			//RTX_DeltaMove1[1] = 0.;//RTX_DeltaMove[1];
			//RTX_DeltaMove1[2] = 0.;//RTX_DeltaMove[2];
			
			//RTX_DeltaMove2[0] = 0.;//RTX_DeltaMove[0];
			//RTX_DeltaMove2[1] = 0.;//RTX_DeltaMove[1];
			//RTX_DeltaMove2[2] = 0.;//RTX_DeltaMove[2];
			
			//RTX_DeltaMove3[0] = 0.;//RTX_DeltaMove[0];
			//RTX_DeltaMove3[1] = 0.;//RTX_DeltaMove[1];
			//RTX_DeltaMove3[2] = 0.;//RTX_DeltaMove[2];
		}
		
		//////////////////////////////////////////////
		if(pSharedMemory->InitialPositionSettingFlag == FALSE)
		{
			for(i=0 ; i<8 ; i++) 
			{
				data[0] = MotorPos[i][0];
				data[1] = MotorPos[i][1];
				data[2] = MotorPos[i][2];
				data[3] = MotorPos[i][3];
				data[4] = MotorPos[i][4];
				data[5] = MotorPos[i][5];
				
				CanSendMsg(0, REF_BASE_TXDF+i, data, 6, 0); // for lower body
			}
		}
		
		ReadSensor();
	}
	else ;

	/*
	RtGetClockTime(CLOCK_2,&testtime2);
	
	//time_x1 = testtime1->u.LowPart;
	int_time1 = (long)testtime1.QuadPart;
	//time_x2 = testtime2->u.LowPart;
	int_time2 = (long)testtime2.QuadPart;
	int_time3 = int_time2 - int_time1;
	*/
}

// 100 Hz timer interrupt
void RTFCNDCL TimerHandler2(PVOID context)
{	
	int i;
	unsigned char data[6];
	unsigned char data1[8];

	if(pSharedMemory->Read_Enc_Flag == TRUE)
	{
		ALLEncRead();
	}

	// Send Motor Ref ///////////////////////////////////////////////////////////////////
	//for(i=0 ; i<=7 ; i++) CanSendMsg(1, REF_BASE_TXDF+i, data, 6, 0);

	if(pSharedMemory->InitialPositionSettingFlag == FALSE)
		{
			for(i=JMC8 ; i<=JMC11 ; i++) 
			{
				data[0] = MotorPos[i][0];
				data[1] = MotorPos[i][1];
				data[2] = MotorPos[i][2];
				data[3] = MotorPos[i][3];
				data[4] = MotorPos[i][4];
				data[5] = MotorPos[i][5];
				
				CanSendMsg(1, REF_BASE_TXDF+i, data, 6, 0); // for upper body
			}

			for(i=EJMC0 ; i<=EJMC3 ; i++)
			{
				data[0] = MotorPos[i][0];
				data[1] = MotorPos[i][1];
				data[2] = MotorPos[i][2];
				data[3] = MotorPos[i][3];
				data[4] = MotorPos[i][4];
				data[5] = MotorPos[i][5];
				
				CanSendMsg(1, REF_BASE_TXDF+i, data, 6, 0); // for wrist & neck body
			}

			for(i=EJMC4 ; i<=EJMC5 ; i++)
			{
				data1[0] = MotorPos[i][0];
				data1[1] = MotorPos[i][1];
				data1[2] = MotorPos[i][2];
				data1[3] = MotorPos[i][3];
				data1[4] = MotorPos[i][4];
				data1[5] = MotorPos[i][5];
				data1[6] = MotorPos[i][6];
				data1[7] = MotorPos[i][7];

				MotorPos[i][5] = 0;
				MotorPos[i][6] = 0;
				MotorPos[i][7] = 0;

				CanSendMsg(1, REF_BASE_TXDF+i, data1, 8, 0); // for both hand
			}
		}
	/////////////////////////////////////////////////////////////////////////////////////
}

void LoadParameter()
{
	int i;

	/*
	for(i=0;i<12;i++)
	{
		PPR[RHY+i] = pSharedMemory->PPR[RHY+i];
		PLUS_MTR_DIR[RHY+i] = pSharedMemory->PLUS_MTR_DIR[RHY+i];
	}
	*/

	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		PPR[i] = pSharedMemory->PPR[i];
		PLUS_MTR_DIR[i] = pSharedMemory->PLUS_MTR_DIR[i];
	}

	PPR[LF1] = PPR_LF1;
	PPR[LF2] = PPR_LF2;
	PPR[LF3] = PPR_LF3;
	PPR[LF4] = PPR_LF4;
	PPR[LF5] = PPR_LF5;

	PPR[RF1] = PPR_RF1;
	PPR[RF2] = PPR_RF2;
	PPR[RF3] = PPR_RF3;
	PPR[RF4] = PPR_RF4;
	PPR[RF5] = PPR_RF5;

	PLUS_MTR_DIR[LF1] = DIR_LF1;
	PLUS_MTR_DIR[LF2] = DIR_LF2;
	PLUS_MTR_DIR[LF3] = DIR_LF3;
	PLUS_MTR_DIR[LF4] = DIR_LF4;
	PLUS_MTR_DIR[LF5] = DIR_LF5;

	PLUS_MTR_DIR[RF1] = DIR_RF1;
	PLUS_MTR_DIR[RF2] = DIR_RF2;
	PLUS_MTR_DIR[RF3] = DIR_RF3;
	PLUS_MTR_DIR[RF4] = DIR_RF4;
	PLUS_MTR_DIR[RF5] = DIR_RF5;

	pSharedMemory->LoadParameterFlag = FALSE;

}

void InitParameters(void)
{
	unsigned char i;
	unsigned char j;

	pSharedMemory->bExitFlag = FALSE;
	pSharedMemory->Tx_Flag = FALSE;
	pSharedMemory->Tx1_Flag = FALSE;
	pSharedMemory->Rx_Flag = FALSE;
	pSharedMemory->INT_Flag = FALSE;

	for(i=0 ; i<8 ; i++)
	{
		TxData[i] = 0;
	}

	TIME_AVG00 = 0;

	pSharedMemory->GYRO_RESET = FALSE;
	pSharedMemory->StartReadTheta = FALSE;
	pSharedMemory->FootAccReset = FALSE;
	pSharedMemory->Read_Enc_Flag = FALSE;
	pSharedMemory->Read_FTS_Flag = FALSE;
	pSharedMemory->Read_TILT_Flag = FALSE;
	pSharedMemory->POS_CTRL_Flag = FALSE;
	pSharedMemory->Ini_ZMP_Zero_Flag = FALSE;
	pSharedMemory->CUT_OFF = FALSE;
	pSharedMemory->DataSaveFlag = FALSE;

	pSharedMemory->TestModeFlag = FALSE;
	pSharedMemory->MotionFlagALL = 0;
	pSharedMemory->MOTION_Stop = 0;
	pSharedMemory->Arm_Motion = FALSE;
	pSharedMemory->ZMPSysIDFlag = FALSE;
	pSharedMemory->Walk_Ready_Flag = FALSE;
	pSharedMemory->Home_Flag = FALSE;
	pSharedMemory->Walk01Test_Flag = FALSE;
	pSharedMemory->DSP_Pose_Set_Flag = FALSE;
	pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;
	pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	pSharedMemory->SSP_Pose_Set_Flag = FALSE;
	pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;
	pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	pSharedMemory->SSP_OL_Save_Flag = FALSE;
	pSharedMemory->SSPCTRLOff = FALSE;
	pSharedMemory->SSPCTRLOn = FALSE;
	pSharedMemory->PushUpFlag = FALSE;
	pSharedMemory->WristMotionFlag = 0;
	pSharedMemory->WristMotionMode = 0;
	pSharedMemory->ShoulderMotionFlag = 0;
	pSharedMemory->WristConfigureFlag = 0;
	pSharedMemory->TorsoCTRLOnOff = FALSE;
	pSharedMemory->ZMP_Zero_Set_Flag = FALSE;
	pSharedMemory->RollAnkleTestFlag = FALSE;
	pSharedMemory->RollAnkleTestStopFlag = FALSE;
	pSharedMemory->PitchAnkleTestFlag = FALSE;
	pSharedMemory->PitchAnkleTestStopFlag = FALSE;
	pSharedMemory->WalkingExp00_Flag = FALSE;
	pSharedMemory->GoStop_Flag = FALSE;
	pSharedMemory->SET_Flag = FALSE;
	pSharedMemory->KeepGoing = FALSE;
	pSharedMemory->SwayAdjToggle = TRUE;
	pSharedMemory->Foot_Displacement_Flag = FALSE;
	pSharedMemory->EncFlag = FALSE;
	pSharedMemory->HipYawVibFlag = TRUE;
	pSharedMemory->InitialPositionSettingFlag = FALSE;
	pSharedMemory->LoadParameterFlag = FALSE;

	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		pSharedMemory->ENC_POS[i][0] = 0;
		pSharedMemory->ENC_POS[i][1] = 0;
	}

	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		pSharedMemory->Reftheta[i]=0.;
		pSharedMemory->Deltheta[i]=0.;
		pSharedMemory->RefVel[i]=(float)0.;
		pSharedMemory->theta[i]=0.;
		pSharedMemory->Oldtheta[i]=0.;
		pSharedMemory->Realtheta[i]=0.;

		pSharedMemory->Move_CNT[i] = 0;
		pSharedMemory->Tfinal[i] = 0;

		pSharedMemory->Move_Flag[i] = FALSE;

		pSharedMemory->Motor_State[i] = 0;
	}

	for(i=0;i<12;i++)
	{
		pSharedMemory->XYZDelta[i] = 0.;
		pSharedMemory->XYZreal[i] = 0.;
		pSharedMemory->XYZref[i] = 0.;

		pSharedMemory->fProfXYZ[i] = 0.;
	}

	for(i=0;i<3;i++)
	{
		pSharedMemory->ZMPInitAdjust[i] = 0.;
		pSharedMemory->ZMPSysID[i] = 0.; //0: X-Axis,  1: Y-Axis, 3: Z-Axis

		pSharedMemory->LeftAnkPos[i] = 0.;
		pSharedMemory->RightAnkPos[i] = 0.;
		pSharedMemory->OFFSETAdj[i] = 0.;
	}

	for(i=0;i<6;i++)
	{
		pSharedMemory->Delta_Foot_Position[i] = (float)0.;
	}

	for(i=0;i<NumOfMotions;i++) 
	{
		pSharedMemory->MotionFlag[i] = FALSE;
		pSharedMemory->MotionLength[i] = 0;
	}

	// Sensor variable initialization
	pSharedMemory->ACC_P = 0;
	pSharedMemory->ACC_R = 0;
	pSharedMemory->GYRO_P = 0;
	pSharedMemory->GYRO_R = 0;
	pSharedMemory->GYRO_Y = 0;

	pSharedMemory->RF_INCL_P = 0;
	pSharedMemory->RF_INCL_R = 0;
	pSharedMemory->LF_INCL_P = 0;
	pSharedMemory->LF_INCL_R = 0;

	pSharedMemory->RF_Tilt_P_Offset = 0;
	pSharedMemory->LF_Tilt_P_Offset = 0;

	pSharedMemory->RFOOT_Fz = 0;
	pSharedMemory->RFOOT_Mx = 0;
	pSharedMemory->RFOOT_My = 0;

	pSharedMemory->LFOOT_Fz = 0;
	pSharedMemory->LFOOT_Mx = 0;
	pSharedMemory->LFOOT_My = 0;

	pSharedMemory->RWRIST_Fz = 0;
	pSharedMemory->RWRIST_Mx = 0;
	pSharedMemory->RWRIST_My = 0;

	pSharedMemory->LWRIST_Fz = 0;
	pSharedMemory->LWRIST_Mx = 0;
	pSharedMemory->LWRIST_My = 0;

	pSharedMemory->N_LFOOT_Fz = (float)0.;
	pSharedMemory->NM_LFOOT_Mx = (float)0.;
	pSharedMemory->NM_LFOOT_My = (float)0.;

	pSharedMemory->N_RFOOT_Fz = (float)0.;
	pSharedMemory->NM_RFOOT_Mx = (float)0.;
	pSharedMemory->NM_RFOOT_My = (float)0.;

	pSharedMemory->N_LWRIST_Fz = (float)0.;
	pSharedMemory->NM_LWRIST_Mx = (float)0.;
	pSharedMemory->NM_LWRIST_My = (float)0.;

	pSharedMemory->N_RWRIST_Fz = (float)0.;
	pSharedMemory->NM_RWRIST_Mx = (float)0.;
	pSharedMemory->NM_RWRIST_My = (float)0.;

	pSharedMemory->RHipRollCompenMag = (float)0.;
	pSharedMemory->LHipRollCompenMag = 0.;

	pSharedMemory->RollVibGainFactor = (float)1.0;
	pSharedMemory->RollOrienGainFactor = (float)1.0;

	pSharedMemory->Pos_Pitch_Ref = (float)0.;
	pSharedMemory->Pos_Roll_Ref = (float)0.;

	pSharedMemory->X_ShapeFactorGain = (float)0.;
	pSharedMemory->ToeOffGain = (float)0.5;
	
	// HUBO2
	RF_DC_MAT[0][0] = (float)-0.0722;//-0.0714;//0.0704;
	RF_DC_MAT[0][1] = (float)0.0002;//0.0011;//-0.0005;
	RF_DC_MAT[0][2] = (float)0.0007;//0.0004;//0.0006;
	
	RF_DC_MAT[1][0] = (float)0.0012;//0.0015;//0.0010;
	RF_DC_MAT[1][1] = (float)0.0740;//0.0735;//-0.0752;
	RF_DC_MAT[1][2] = (float)-0.0014;//-0.0007;//0.0001;
	
	RF_DC_MAT[2][0] = (float)-0.0562;//-0.0104;//-0.0975;
	RF_DC_MAT[2][1] = (float)0.0469;//-0.0337;//0.1018;
	RF_DC_MAT[2][2] = (float)0.3234;//0.3235;//0.3253;
	
	LF_DC_MAT[0][0] = (float)0.07111;//0.0738;//0.0738;
	LF_DC_MAT[0][1] = (float)-0.0017;//-0.0005;//-0.0005;
	LF_DC_MAT[0][2] = (float)-0.0002;//0.0005;//0.0005;
	
	LF_DC_MAT[1][0] = (float)-0.0005;//-0.0058;
	LF_DC_MAT[1][1] = (float)-0.0723;//-0.0870;
	LF_DC_MAT[1][2] = (float)-0.0013;//0.0005;
	
	LF_DC_MAT[2][0] = (float)-0.0272;//-0.0171;//
	LF_DC_MAT[2][1] = (float)-0.1580;//-0.1999;
	LF_DC_MAT[2][2] = (float)0.3264;//0.3246;//

	pSharedMemory->Xzmp = (float)0.;
	pSharedMemory->Yzmp = (float)0.;

	pSharedMemory->LXzmp = (float)0.;
	pSharedMemory->LYzmp = (float)0.;

	pSharedMemory->RXzmp = (float)0.;
	pSharedMemory->RYzmp = (float)0.;

	pSharedMemory->M_Theta_P = (float)0.;
	pSharedMemory->M_Theta_R = (float)0.;
	pSharedMemory->M_Vel_P = (float)0.;
	pSharedMemory->M_Vel_R = (float)0.;

	pSharedMemory->New_Theta_P = (float)0.;
	pSharedMemory->New_Theta_R = (float)0.;
	pSharedMemory->New_Vel_P = (float)0.;
	pSharedMemory->New_Vel_R = (float)0.;
	
	pSharedMemory->Incl_P = (float)0.;
	pSharedMemory->Incl_R = (float)0.;

	pSharedMemory->LF_TILT_P = (float)0.;
	pSharedMemory->LF_TILT_R = (float)0.;
	pSharedMemory->RF_TILT_P = (float)0.;
	pSharedMemory->RF_TILT_R = (float)0.;

	pSharedMemory->Compen_Theta_P = (float)0.;
	pSharedMemory->Compen_Theta_R = (float)0.;
	
	pSharedMemory->Incl_Pitch_Offset = 0;
	pSharedMemory->Incl_Roll_Offset = 0;


	pSharedMemory->SWAYcompen = (float)0.;

	//////////////////////

	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		for(j=0;j<8;j++)
		{
			MotorPos[i][j] = 0;
		}
	}

	InvFlag = FALSE;

	RTX_ACC_R = 0;
	RTX_ACC_P = 0;

	RTX_GYRO_R = 0;
	RTX_GYRO_P = 0;
	RTX_GYRO_Y = 0;

	RTX_M_Theta_R = 0;
	RTX_M_Theta_P = 0;
	
	RTX_M_Theta_Offset_R = 0;
	RTX_M_Theta_Offset_P = 0;

	RTX_M_Vel_R = 0;
	RTX_M_Vel_P = 0;

	RTX_New_Theta_R = 0;
	RTX_New_Theta_P = 0;
	
	RTX_New_Theta_Offset_R = 0;
	RTX_New_Theta_Offset_P = 0;

	RTX_New_Vel_Offset_R = 0;
	RTX_New_Vel_Offset_P = 0;
	
	RTX_New_Vel_R = 0;
	RTX_New_Vel_P = 0;

	RTX_M_Tilt_Theta_R = (float)0.;
	RTX_M_Tilt_Theta_ROLD = (float)0.;
	RTX_M_Tilt_Vel_R = (float)0.;
	
	RTX_M_Tilt_Theta_P = (float)0.;
	RTX_M_Tilt_Theta_POLD = (float)0.;
	RTX_M_Tilt_Vel_P = (float)0.;

	RTX_M_Tilt_Thetaold_R = (float)0.;
	RTX_M_Tilt_Thetaold_P = (float)0.;
	RTX_M_Tilt_Theta_R_LPF = (float)0.;
	RTX_M_Tilt_Theta_P_LPF = (float)0.;
	
	RTX_M_Tilt_Velold_R = (float)0.;
	RTX_M_Tilt_Velold_P = (float)0.;
	RTX_M_Tilt_Vel_R_LPF = (float)0.;
	RTX_M_Tilt_Vel_P_LPF = (float)0.;

	RTX_M_Tilt_Theta_R = 0.0f;
	RTX_M_Tilt_Theta_ROLD = 0.0f;
	RTX_M_Tilt_Vel_R = 0.0f;
	
	RTX_M_Tilt_Theta_P = 0.0f;
	RTX_M_Tilt_Theta_POLD = 0.0f;
	RTX_M_Tilt_Vel_P = 0.0f;
	

	Gyro_P_Offset = 0;
	Gyro_R_Offset = 0;
	Gyro_Y_Offset = 0;

	GyroR0 = (float)0.;
	GyroP0 = (float)0.;
	GyroY0 = (float)0.;

	GyroP_deg = (float)0.;
	GyroR_deg = (float)0.;
	GyroY_deg = (float)0.;

	AccR_deg = (float)0.;
	AccP_deg = (float)0.;

	LPF_GYRO_Y1 = (float)0.;
	LPF_GYRO_Y1_OLD = (float)0.;

	LPF_AccR = (float)0.;
	LPF_AccP = (float)0.;
	LPF_AccR_old = (float)0.;
	LPF_AccP_old = (float)0.;

	LPF_New_AccR = (float)0.;
	LPF_New_AccP = (float)0.;
	LPF_New_AccR_old = (float)0.;
	LPF_New_AccP_old = (float)0.;

	HPF_M_ThetaR = (float)0.;
	HPF_M_ThetaP = (float)0.;

	HPF_M_ThetaR_old = (float)0.;
	HPF_M_ThetaP_old = (float)0.;

	HPF_New_ThetaR_old = (float)0.;
	HPF_New_ThetaP_old = (float)0.;

	RTX_CompenTheta_P = (float)0.;
	RTX_CompenTheta_R = (float)0.;

	RTX_RF_Tilt_R_Offset = 0;
	RTX_RF_Tilt_P_Offset = 0;

	RTX_LF_Tilt_R_Offset = 0;
	RTX_LF_Tilt_P_Offset = 0;

	RTX_RF_INCL_R = 0;
	RTX_RF_INCL_P = 0;
	RTX_LF_INCL_R0 = 0;
	RTX_LF_INCL_P0 = 0;

	FootTilt[0] = 0;
	FootTilt[1] = 0;
	FootTilt[2] = 0;
	FootTilt[3] = 0;

	RF_ACC_R_lp = (float)0.;
	RF_ACC_P_lp = (float)0.;
	LF_ACC_R_lp = (float)0.;
	LF_ACC_P_lp = (float)0.;

	RF_ACC_R_lp0 = (float)0.;
	RF_ACC_P_lp0 = (float)0.;
	LF_ACC_R_lp0 = (float)0.;
	LF_ACC_P_lp0 = (float)0.;

	RF_TILT_R = (float)0.;
	RF_TILT_P = (float)0.;
	LF_TILT_R = (float)0.;
	LF_TILT_P = (float)0.;

	RF_TILT_R_old = (float)0.;
	RF_TILT_P_old = (float)0.;
	LF_TILT_R_old = (float)0.;
	LF_TILT_P_old = (float)0.;

	RF_TILT_R_HPF = (float)0.;
	RF_TILT_P_HPF = (float)0.;
	LF_TILT_R_HPF = (float)0.;
	LF_TILT_P_HPF = (float)0.;

	RF_TILT_R_HPF_old = (float)0.;
	RF_TILT_P_HPF_old = (float)0.;
	LF_TILT_R_HPF_old = (float)0.;
	LF_TILT_P_HPF_old = (float)0.;

	RF_TILT_R_Vel = (float)0.;
	RF_TILT_P_Vel = (float)0.;
	LF_TILT_R_Vel = (float)0.;
	LF_TILT_P_Vel = (float)0.;

	RF_TILT_R_Vel_old = (float)0.;
	RF_TILT_P_Vel_old = (float)0.;
	LF_TILT_R_Vel_old = (float)0.;
	LF_TILT_P_Vel_old = (float)0.;

	UpRatio = (float)0.47;

	RTX_LFOOT_Fz = 0;
	RTX_LFOOT_Mx = 0;
	RTX_LFOOT_My = 0;

	RTX_LFOOT_Fz = 0;
	RTX_LFOOT_Mx = 0;
	RTX_LFOOT_My = 0;

	RTX_LWRIST_Fz = 0;
	RTX_LWRIST_Mx = 0;
	RTX_LWRIST_My = 0;

	RTX_RWRIST_Fz = 0;
	RTX_RWRIST_Mx = 0;
	RTX_RWRIST_My = 0;

	RTX_NM_RFOOT_Mx = 0.;	RTX_NM_RFOOT_My = 0.;	RTX_N_RFOOT_Fz = 0.;
	RTX_NM_LFOOT_Mx = 0.;	RTX_NM_LFOOT_My = 0.;	RTX_N_LFOOT_Fz = 0.;
	RTX_NM_RWRIST_Mx = 0.;	RTX_NM_RWRIST_My = 0.;	RTX_N_RWRIST_Fz = 0.;
	RTX_NM_LWRIST_Mx = 0.;	RTX_NM_LWRIST_My = 0.;	RTX_N_LWRIST_Fz = 0.;
	RTX_Xzmp = 0.;	RTX_Yzmp = 0.;
	RTX_RXzmp = 0.;	RTX_RYzmp = 0.;
	RTX_LXzmp = 0.;	RTX_LYzmp = 0.;

	RTX_NM_RWRIST_Mx_old = 0.;	RTX_NM_RWRIST_My_old = 0.;	RTX_N_RWRIST_Fz_old = 0.;
	RTX_NM_LWRIST_Mx_old = 0.;	RTX_NM_LWRIST_My_old = 0.;	RTX_N_LWRIST_Fz_old = 0.;
	RTX_NM_RWRIST_Mx_LPF = 0.;	RTX_NM_RWRIST_My_LPF = 0.;	RTX_N_RWRIST_Fz_LPF = 0.;
	RTX_NM_LWRIST_Mx_LPF = 0.;	RTX_NM_LWRIST_My_LPF = 0.;	RTX_N_LWRIST_Fz_LPF = 0.;


	pSharedMemory->VibGainR = (float)0.;
	pSharedMemory->VibGainY = (float)0.;

	pSharedMemory->TorsoCTRLGainR[0] = 0.;
	pSharedMemory->TorsoCTRLGainR[1] = 0.;
	pSharedMemory->TorsoCTRLGainP[0] = 0.;
	pSharedMemory->TorsoCTRLGainP[1] = 0.;

	pSharedMemory->Zmp_Zero_Offset = 0.;
	
	pSharedMemory->PushUpAMP = (float)0.;
	pSharedMemory->PushUpHz = (float)0.;
	
	pSharedMemory->WristAmp = (float)0.;
	pSharedMemory->WristHz = (float)0.;

	pSharedMemory->ShoulderPitchAmp = (float)0.;
	pSharedMemory->ShoulderRollAmp = (float)0.;
	pSharedMemory->ElbowAmp = (float)0.;

	pSharedMemory->ShoulderPitchHz = (float)0.;
	pSharedMemory->ShoulderRollHz = (float)0.;

	pSharedMemory->AnkleAmplitude = (float)0.;
	pSharedMemory->AnkleFreq = (float)0.;

	pSharedMemory->WalkSway = (float)(SWAY1);
	pSharedMemory->OLAnkComp = (float)1.5;

	pSharedMemory->tp_WalkSway = (float)(SWAY1);
	pSharedMemory->tp_OLAnkComp = (float)1.5;

	//pSharedMemory->ZMPref_AMP[0] = Init_Xzmp;
	pSharedMemory->ZMPref_AMP[1] = 75.;

	pSharedMemory->SwayDelayOpen = (float)2.5;
	pSharedMemory->SwayDelayRecover = (float)2.0;

	pSharedMemory->Acc_Pitch_Offset_Ini = (float)0.;
	pSharedMemory->Acc_Roll_Offset_Ini = (float)0.;
	
	pSharedMemory->UPRATIO = (float)0.47;
	pSharedMemory->UpRightPoseOffset = (float)0.;
	
	pSharedMemory->DelAnkleRoll[0] = 0.; // "0" Left, "1" Right
	pSharedMemory->DelAnkleRoll[1] = 0.; // "0" Left, "1" Right
	
	pSharedMemory->InitAnkleRoll[0] = 0.;// "0" Left, "1" Right
	pSharedMemory->InitAnkleRoll[1] = 0.;// "0" Left, "1" Right

	pSharedMemory->pHipMoveRatio = (float)0.;
	pSharedMemory->HipPitchAngle = (float)0.;
	pSharedMemory->FootPlacementGain = (float)0.;
	pSharedMemory->Roll_Ref_Gain = (float)0.;
	pSharedMemory->Pitch_Ref_Gain = (float)0.;
	pSharedMemory->AnkleRollGain = (float)1.0;

	for(i=0;i<50;i++) UpperBodyTime[i] = 0;


	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		PPR[i] = (float)0.;
		PLUS_MTR_DIR[i] = (float)0.;
		pSharedMemory->PPR[i] = (float)0.;
		pSharedMemory->PLUS_MTR_DIR[i] = (float)0.;
		pSharedMemory->Z_Ref[i] = 0;
	}

	//		For HUBO
	//////////////////////////////////////////////////
	PPR[0]  = (float)47232.;                // 오른 눈 pitch 감속비 128*246*1.5
	PPR[1]  = (float)31488.;                // 오른 눈 Roll 감속비
	PPR[2]  = (float)47232.;                // 왼 눈 Pitch 감속비 128*246*1.5
	PPR[3]  = (float)31488.;                // 왼 눈 Roll 감속비
	PPR[4]  = (float)6400.;					// 목 Pitch 감속비 32*100*2
	PPR[5]  = (float)3328.;					// 목 Yaw 감속비 32*104
	
	PPR[6]  = (float)48981.3333;            // 왼 엄지 감속비 128*246*28/18
	PPR[7]  = (float)48981.3333;            // 왼 검지 감속비
	PPR[8]  = (float)48981.3333;            // 왼 중지 감속비
	PPR[9]  = (float)48981.3333;            // 왼 약지 감속비
	PPR[10] = (float)48981.3333;			// 왼 새끼 손가락 감속비
	PPR[11] = (float)6400.;					// 왼 손목 Pitch 감속비 32*100*2
	PPR[12] = (float)3328.;					// 왼 손목 Roll 감속비 32*104
	
	PPR[13] = (float)48981.3333;            // 왼 엄지 감속비 128*246*28/18
	PPR[14] = (float)48981.3333;            // 왼 검지 감속비
	PPR[15] = (float)48981.3333;            // 왼 중지 감속비
	PPR[16] = (float)48981.3333;            // 왼 약지 감속비
	PPR[17] = (float)48981.3333;			// 왼 새끼 손가락 감속비
	PPR[18] = (float)6400.;					// 왼 손목 Pitch 감속비 32*100*2
	PPR[19] = (float)3328.;					// 왼 손목 Roll 감속비 32*104

	PPR[RWY] = PPR_RWY;
	PPR[RW1] = PPR_RW1;
	PPR[RW2] = PPR_RW2;
	PPR[LWY] = PPR_LWY;
	PPR[LW1] = PPR_LW1;
	PPR[LW2] = PPR_LW2;
	PPR[NKY] = PPR_NKY;
	PPR[NK1] = PPR_NK1;
	PPR[NK2] = PPR_NK2;
	
	PPR[RSP] = (float)PPR_RSP;				// 오른 어깨 Pitch 감속비 512*100*1
	PPR[RSR] = (float)PPR_RSR;                // 오른 어깨 Yaw 감속비 512*100
	PPR[RSY] = (float)PPR_RSY;				// 오른 어깨 Roll 감속비 512*100
	PPR[REB] = (float)PPR_REB;                // 오른 Elbow 감속비 512*100
	PPR[LSP] = (float)PPR_LSP;				// 왼 어깨 Pitch 감속비 512*100*1
	PPR[LSR] = (float)PPR_LSR;                // 왼 어깨 Yaw 감속비 512*100
	PPR[LSY] = (float)PPR_LSY;				// 왼 어깨 Roll 감속비 512*100
	PPR[LEB] = (float)PPR_LEB;                // 왼 Elbow 감속비 512*100
	PPR[WST] = (float)PPR_WST;				//  Trunk 감속비 512*100
	
	PPR[RHY] = (float)PPR_RHY;
	PPR[RHR] = (float)PPR_RHR;
	PPR[RHP] = (float)PPR_RHP;
	PPR[RKN] = (float)PPR_RKN;
	PPR[RAP] = (float)PPR_RAP;
	PPR[RAR] = (float)PPR_RAR;

	PPR[LHY] = (float)PPR_LHY;
	PPR[LHR] = (float)PPR_LHR;
	PPR[LHP] = (float)PPR_LHP;
	PPR[LKN] = (float)PPR_LKN;
	PPR[LAP] = (float)PPR_LAP;
	PPR[LAR] = (float)PPR_LAR;
	
	PLUS_MTR_DIR[0] = -1.;
	PLUS_MTR_DIR[1] = -1.;
	PLUS_MTR_DIR[2] = 1.;
	PLUS_MTR_DIR[3] = -1.;
	PLUS_MTR_DIR[4] = 1.;
	PLUS_MTR_DIR[5] = 1.;
	
	PLUS_MTR_DIR[6] = -1.;					// +1 : 시계방향이 + , -1 : 반시계방향이 +
	PLUS_MTR_DIR[7] = 1.;
	PLUS_MTR_DIR[8] = 1.;
	PLUS_MTR_DIR[9] = -1.;
	PLUS_MTR_DIR[10] = -1.;
	PLUS_MTR_DIR[11] = -1.;
	PLUS_MTR_DIR[12] = -1.;
	
	PLUS_MTR_DIR[13] = 1.;					// +1 : 시계방향이 + , -1 : 반시계방향이 +
	PLUS_MTR_DIR[14] = -1.;
	PLUS_MTR_DIR[15] = -1.;
	PLUS_MTR_DIR[16] = 1.;
	PLUS_MTR_DIR[17] = 1.;
	PLUS_MTR_DIR[18] = 1.;
	PLUS_MTR_DIR[19] = -1.;

	PLUS_MTR_DIR[RWY] = DIR_RWY;
	PLUS_MTR_DIR[RW1] = DIR_RW1;
	PLUS_MTR_DIR[RW2] = DIR_RW2;
	PLUS_MTR_DIR[LWY] = DIR_LWY;
	PLUS_MTR_DIR[LW1] = DIR_LW1;
	PLUS_MTR_DIR[LW2] = DIR_LW2;
	PLUS_MTR_DIR[NKY] = DIR_NKY;
	PLUS_MTR_DIR[NK1] = DIR_NK1;
	PLUS_MTR_DIR[NK2] = DIR_NK2;
	
	PLUS_MTR_DIR[RSP] = DIR_RSP;
	PLUS_MTR_DIR[RSR] = DIR_RSR; 
	PLUS_MTR_DIR[RSY] = DIR_RSY;
	PLUS_MTR_DIR[REB] = DIR_REB;
	PLUS_MTR_DIR[LSP] = DIR_LSP;
	PLUS_MTR_DIR[LSR] = DIR_LSR; 
	PLUS_MTR_DIR[LSY] = DIR_LSY;
	PLUS_MTR_DIR[LEB] = DIR_LEB;
	PLUS_MTR_DIR[WST] = DIR_WST;

	PLUS_MTR_DIR[RHY] = DIR_RHY;
	PLUS_MTR_DIR[RHR] = DIR_RHR;
	PLUS_MTR_DIR[RHP] = DIR_RHP;
	PLUS_MTR_DIR[RKN] = DIR_RKN;
	PLUS_MTR_DIR[RAP] = DIR_RAP;
	PLUS_MTR_DIR[RAR] = DIR_RAR;
	PLUS_MTR_DIR[LHY] = DIR_LHY;
	PLUS_MTR_DIR[LHR] = DIR_LHR;
	PLUS_MTR_DIR[LHP] = DIR_LHP;
	PLUS_MTR_DIR[LKN] = DIR_LKN;
	PLUS_MTR_DIR[LAP] = DIR_LAP;
	PLUS_MTR_DIR[LAR] = DIR_LAR;
	//////////////////////////////////////////////////
	
	for(i=0;i<3;i++)
	{
		RTX_BodyCenter[i]	=	0.;	// 0: X-Axis, 1: Y-Axis, 2: Z-Axis
		RTX_DeltaMove[i]	=	0.;	// 0: X-Axis, 1: Y-Axis, 2: Z-Axis
		RTX_DeltaMove2[i]	=	0.;	// 0: X-Axis, 1: Y-Axis, 2: Z-Axis
	}

	for(i=0;i<2;i++)
	{
		STATUS[i] = -2;
		oldSTATUS[i] = -2;

		RTX_COMPEN_Vib_Roll[i] = (float)0.;
		RTX_oldCOMPEN_Vib_Roll[i] = (float)0.;
		RTX_delCOMPEN_Vib_Roll[i] = (float)0.;

		RTX_COMPEN_Vib_Yaw[i] = (float)0.;
		RTX_oldCOMPEN_Vib_Yaw[i] = (float)0.;
		RTX_delCOMPEN_Vib_Yaw[i] = (float)0.;
	}

	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			RTX_COMPEN_Ankle_Roll[i][j] = (float)0.;
			RTX_COMPEN_Ankle_Pitch[i][j] = (float)0.;
			RTX_oldCOMPEN_Ankle_Roll[i][j] = (float)0.;
			RTX_oldCOMPEN_Ankle_Pitch[i][j] = (float)0.;
			RTX_delCOMPEN_Ankle_Roll[i][j] = (float)0.;
			RTX_delCOMPEN_Ankle_Pitch[i][j] = (float)0.;
		}
	}

	Status[0] = 0;
	Status[1] = 0;
	Status[2] = 0;	
	Status[3] = 0;
	Status[4] = 0;
	Status[5] = 0;	
	Status[6] = 0;
	Status[7] = 0;
	Status[8] = 0;

	DirDist[1][0] = (float)(SWAY1);
	DirDist[1][1] = 0.;
	DirDist[1][2] = 0.;
	DirDist[1][3] = 0.;
	DirDist[1][4] = 0.;
	DirDist[1][5] = 0.;
	DirDist[1][6] = 0.;
	DirDist[1][7] = 40.;
	DirDist[1][8] = 0.;
	
	DirDist[0][0] = (float)(SWAY1);
	DirDist[0][1] = 0.;
	DirDist[0][2] = 0.;
	DirDist[0][3] = 0.;
	DirDist[0][4] = 0.;
	DirDist[0][5] = 0.;
	DirDist[0][6] = 0.;
	DirDist[0][7] = 40.;
	DirDist[0][8] = 0.;

	NumStep = 0;
	OP_DistFwdBwd1 = 0.;
	OP_DistFwdBwd1old = 0.;

	RTXSWAYcompen1 = 0.;
	RTXSWAYcompen2 = 0.;
	RTXSWAYcompen3 = 0.;

	stretchedFlag = 0;
	Rstretched = 1;
	Lstretched = 1;

	ZMPrefAdd[0] = 0.;
	ZMPrefAdd[1] = 0.;

	FiveKG_R_Flag = 2;
	FiveKG_L_Flag = 2;

	AnkAdjust[0] = 1.;
	AnkAdjust[1] = 1.;

	AddDiff = (float)0.;
	RTX_HeightDiff[0] = (float)0.;
	RTX_HeightDiff[1] = (float)0.;

	v_oldCartPos2 = -L1-L2+READY_LEG_UP_AMP;
	v_delCartPos2 = 0.;
	v_oldCartPos5 = -L1-L2+READY_LEG_UP_AMP;
	v_delCartPos5 = 0.;

	LandLOK_Flag = 2;
	LandROK_Flag = 2;

	for(i=0;i<10;i++) TIMERecover[i]=0;

	ZMPref[0] = 0.;
	ZMPref[1] = 0.;

	Pos_HipPitch = (float)0.;
	Pos_HipPitchOLD = (float)0.;

	OL_x = 0.0;
	OR_x = 0.0;
	OL_y =  L0 + WLK_RDY_OFFSET;
	OR_y = -L0 - WLK_RDY_OFFSET;

	RTX_R_AnkleP = (float)0.;
	RTX_Adj_AnkleP = (float)0.;
	
	RTX_CTRL_Ankle[0] = (float)0.;
	RTX_CTRL_Ankle[1] = (float)0.;
	RTX_CTRL_Ankle[2] = (float)0.;
	RTX_CTRL_Ankle[3] = (float)0.;

	Xzmp_lp = oldXzmp_lp = 0.;
	Yzmp_lp = oldYzmp_lp = 0.;
	
	for(i=0;i<10;i++) INItemp[i] = (float)0.;

	for(i=0;i<6;i++)
	{
		v_AngPosEx[i]=(float)0.;
	}

	for(i=0;i<8;i++)
	{
		v_AngArm[i] = (float)0.;
	}
	
	for(i=0;i<2;i++)
	{
		v_CTRL_Ankle[i] = (float)0.;
		Heel_Landing[i] = (float)0.;
		Heel_LandingOLD[i] = (float)0.;
		Heel_Landing_LPF[i] = (float)0.;
		Heel_Landing_LPF_OLD[i] = (float)0.;
		Init_Heel_Angle[i] = (float)0.;
		Final_Heel_Angle[i] = (float)0.;
		Heel_InitFlag[i] = 0;
		Heel_Timer[i] = 0;
		//v_CTRL_HipRoll[i] = (float)0.;
	}
	
	HipMove = (float)0.;
	HipMoveFlag = 0;
	pSharedMemory->DataSaveFlag = FALSE;
	tp_delta_Heel = (float)0.;
	v_CTRL_PosHip = (float)0.;
	v_CTRL_PosHipOLD = (float)0.;
	Pos_HipPitch = (float)0.;
	Pos_HipPitchOLD = (float)0.;

	LZ = (float)0.;
	RZ = (float)0.;

	RSteadyFlag = 0;
	LSteadyFlag = 0;

	pSharedMemory->AnkleControlFlag[LEFT] = 0;
	pSharedMemory->AnkleControlFlag[RIGHT] = 0;

	pSharedMemory->Hip_test0[0] = (float)0.;
	pSharedMemory->Hip_test0[1] = (float)0.;
	pSharedMemory->Hip_test3[0] = (float)0.;
	pSharedMemory->Hip_test3[1] = (float)0.;
	pSharedMemory->Hip_test5_a[0] = (float)0.;
	pSharedMemory->Hip_test5_a[1] = (float)0.;

	InitialRoll[0] = (float)0.;
	InitialRoll[1] = (float)0.;
	InitialPitch[0] = (float)0.;
	InitialPitch[1] = (float)0.;

	temp_roll_ref[0] = (float)0.;
	temp_roll_ref[1] = (float)0.;

	temp_pitch_ref[0] = (float)0.;
	temp_pitch_ref[1] = (float)0.;

	AnkleRollRef[0] = (float)0.;
	AnkleRollRef[1] = (float)0.;
	AnklePitchRef[0] = (float)0.;
	AnklePitchRef[1] = (float)0.;

	ZMP_DSP_Angle[0] = (float)0.;	// x-dir
	ZMP_DSP_Angle[1] = (float)0.;	// y-dir
	
	ZMP_DSP_Angle_old[0] = (float)0.;	// x-dir
	ZMP_DSP_Angle_old[1] = (float)0.;	// y-dir
	
	tp_ZMP_DSP_Angle[0] = (float)0.;
	tp_ZMP_DSP_Angle[1] = (float)0.;
	
	DSP_ZMPRef[0] = (float)Init_Xzmp;
	DSP_ZMPRef[1] = (float)Init_Yzmp;
	
	Init_DSP_ZMP[0] = (float)Init_Xzmp;
	Init_DSP_ZMP[1] = (float)Init_Yzmp;
	
	Read_ZMP_Flag = FALSE;
	
	pSharedMemory->ZMP_DSP_CTRL_Flag = 0;
	pSharedMemory->ZMP_DSP_X_Gain = (float)1.0;//0.2;
	pSharedMemory->ZMP_DSP_Y_Gain = (float)3.0;//;
	
	pSharedMemory->ZMP_DSP_Y_IntegralGain = (float)0.;//-0.001;
	pSharedMemory->StartInitVelCoff = (float)1.;

	for(i=0;i<6;i++) InitDeltaFoot[i] = (float)0.;
	
	for(i=0;i<2;i++)
	{
		SumZMP[0][i] = (float)0.;
		SumZMP[1][i] = (float)0.;
		SumRoll[i] = (float)0.;
		SumPitch[i] = (float)0.;
		SumGyroRoll[i] = (float)0.;
		SumGyroPitch[i] = (float)0.;

		AvgZMP[0][i] = (float)0.;
		AvgZMP[1][i] = (float)0.;
		AvgRoll[i] = (float)0.;
		AvgPitch[i] = (float)0.;
		AvgGyroRoll[i] = (float)0.;
		AvgGyroPitch[i] = (float)0.;
		
		BodyEstimateTimer[i] = 0;
		BodyEstimateUpdateFlag[i] = 0;

		TotalSumZMP[0][i] = (float)0.;
		TotalSumZMP[1][i] = (float)0.;
		TotalSumRoll[i] = (float)0.;
		TotalSumPitch[i] = (float)0.;
		TotalSumGyroRoll[i] = (float)0.;
		TotalSumGyroPitch[i] = (float)0.;
		
		TotalAvgZMP[0][i] = (float)0.;
		TotalAvgZMP[1][i] = (float)0.;
		TotalAvgRoll[i] = (float)0.;
		TotalAvgPitch[i] = (float)0.;
		TotalAvgGyroRoll[i] = (float)0.;
		TotalAvgGyroPitch[i] = (float)0.;
		
		TotalBodyEstimateTimer[i] = 0;
		TotalBodyEstimateUpdateFlag[i] = 0;
	}

	// kirk variable
	
	
	pSharedMemory->Walking_Test_Flag = FALSE;
	pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	pSharedMemory->Walk_R_Side_Flag = FALSE;
	pSharedMemory->Walk_L_Side_Flag = FALSE;

	pSharedMemory->Kirk_WalkingFlag = FALSE;
	pSharedMemory->Int_CNT = 0;				// Global Counter !!!			// Global Counter !!!
	pSharedMemory->Mark_Time_Flag = FALSE;
	pSharedMemory->Walking_Stop_Flag = FALSE;
	pSharedMemory->Walk_FWD_Flag = FALSE;
	pSharedMemory->Walk_BWD_Flag = FALSE;
	pSharedMemory->FSM = 0;
	pSharedMemory->Motion_State = 6;	// 0 : Marking,  1 : FWD Walking,  -1 : BWD Walking
										// 2 : R-Side Walking,  3 : L-Side Walking
										// 4 : CW Turning,  5 : CCW Turning	
										// 6 : Stop;
										// 7 : UP , 8 : DN
	pSharedMemory->Path_Area_CNT = 0;
	Path_Local_CNT = 0;	

	pSharedMemory->Step_time = 95;
	
	pSharedMemory->Walk_Foot_Zdir_Amp = 25;
	pSharedMemory->Walk_BC_Ydir_Amp = 62;
	
	pSharedMemory->Amp_ankleR = 2.3f;
	pSharedMemory->Amp_ankleL = 2.3f;

	pSharedMemory->Delay_time = 10;

	pSharedMemory->Walk_Foot_Zdir_Amp = 25;
	pSharedMemory->Walk_BC_Ydir_Amp = 62;
	
	pSharedMemory->BC_x =0.;
	pSharedMemory->BC_y =0.;
	pSharedMemory->BC_z =0.;

	pSharedMemory->L_py = 0.;
	pSharedMemory->R_py = 0.;
	pSharedMemory->L_px = 0.;
	pSharedMemory->R_px = 0.;
	pSharedMemory->L_pz = 0.;
	pSharedMemory->R_pz = 0.;

	RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;

	DeltaMov_x_ini = 0.0f;//
	DeltaMov_y_ini = 0.0f;

	pSharedMemory->Equi_Adj_Rfoot_Z = pSharedMemory->Equi_Adj_Lfoot_Z = 0.0;
	pSharedMemory->Gain_LO_Con_p = pSharedMemory->Gain_LO_Con_r = 1.0;
	DeltaMov_x = DeltaMov_y = 0.0f;
	DeltaMov_x_dsp = DeltaMov_y_dsp = 0.0f;
	DeltaMov_x_ssp = DeltaMov_y_ssp = 0.0f;

	pSharedMemory->gain_temp1 = 0.0f;
	pSharedMemory->gain_temp2 = 0.0f;

	pSharedMemory->amp_temp1 = 76.0f;
	Equi_Adj_LRAP_Walking = 0.0f;

	Pit_y_a_0_Hspd = Pit_y_a_1_Hspd = 0.0f;

	pSharedMemory->Plus_Yzmp_avg = 0.0f;
	pSharedMemory->Minus_Yzmp_avg = 0.0f;

	Amp_BC_Y_Amp_Compen_M = 0.0f;
	Amp_BC_Y_Amp_Compen_W = 0.0f;
	Amp_BC_Y_Amp_Compen_B = 0.0f;
	
	temp_Plus_Yzmp_avg = temp_Minus_Yzmp_avg = 0.;
	zmp_CNT_1 = zmp_CNT_2 = 0;

	pSharedMemory->SSP_CTRL_MODE = 1;

	BC_Y_Amp_Comp_M(0,0,0);
	BC_Y_Amp_Comp_B(0,0,0);
	BC_Y_Amp_Comp_W(0,0,0,0);

	RTX_New_Vel_R_old = 0;
	RTX_New_Vel_P_old = 0;

	HPF2_New_ThetaR = 0.0f;
	HPF2_New_ThetaR_old = 0.0f;
	HPF2_New_ThetaR_old2 = 0.0f;
	
	HPF2_New_ThetaP = 0.0f;
	HPF2_New_ThetaP_old = 0.0f;
	HPF2_New_ThetaP_old2 = 0.0f;

	pSharedMemory->ShakeHandsFlag = 0;

	pSharedMemory->SearchBoardNo = 0;

	pSharedMemory->DSPS_Con_Flag = FALSE;
	pSharedMemory->SSPS_Con_Flag = FALSE;

	pSharedMemory->Test_CNT_0 = 0;
	pSharedMemory->Test_CNT_1 = 0;
	pSharedMemory->Test_CNT_2 = 0;

	pSharedMemory->Demo_4_Flag = FALSE;
	pSharedMemory->Demo_4_Off_Flag = FALSE;

	pSharedMemory->Demo_5_Flag = FALSE;
	pSharedMemory->Demo_5_Off_Flag = FALSE;

	pSharedMemory->Demo_6_Flag = FALSE;

	DSP_temp_1 = DSP_temp_2 = DSP_temp_3 = DSP_temp_4 = SSP_temp_1 = SSP_temp_2 =  SSP_temp_3 =  SSP_temp_4 = SSP_temp_5 = 0.;
	g_temp_theta_1 = g_temp_theta_2 = g_temp_theta_3 = g_temp_theta_4 = g_temp_theta_5 = g_temp_theta_6 = g_temp_theta_7 = g_temp_theta_8 = 0.; // for gesture
	g_temp_theta_9 = g_temp_theta_10 = g_temp_theta_11 = g_temp_theta_12 = g_temp_theta_13 = g_temp_theta_14 = g_temp_theta_15 = g_temp_theta_16 = 0.; // for gestures

	Gesture_Pelvis_2 = (float)0.;
	//Rob's Scripting parameters
	pSharedMemory->ScriptLoaded = 0; //start without a script running
}


void ALLTILTRead()
{
	int a,b;
	int c11;
	int d11;
	int e11;

	a=GetBuffno(SENSOR_IMU1_RXDF);
	b=GetBuffno(SENSOR_IMU2_RXDF);
	c11=GetBuffno(SENSOR_AD1_RXDF);
	d11=GetBuffno(SENSOR_AD2_RXDF);
	e11=GetBuffno(SENSOR_IMU3_RXDF);  // used for Analog Device Sensors


	//RTX_New_Vel_R = (short int)(RTX_Rx_Data[e11][4] + (RTX_Rx_Data[e11][5]<<8));
	//RTX_New_Vel_P = -(short int)(RTX_Rx_Data[e11][6] + (RTX_Rx_Data[e11][7]<<8));
	//RTX_New_Theta_R = (short int)(RTX_Rx_Data[e11][0] + (RTX_Rx_Data[e11][1]<<8));
	//RTX_New_Theta_P = -(short int)(RTX_Rx_Data[e11][2] + (RTX_Rx_Data[e11][3]<<8));

	RTX_New_Vel_R = (short int)(RTX_Rx_Data[e11][0] + (RTX_Rx_Data[e11][1]<<8));
	RTX_New_Vel_P = (short int)(RTX_Rx_Data[e11][2] + (RTX_Rx_Data[e11][3]<<8));
	RTX_New_Theta_R = (short int)(RTX_Rx_Data[e11][4] + (RTX_Rx_Data[e11][5]<<8) - ACC_R_OFFSET);
	RTX_New_Theta_P = -(short int)(RTX_Rx_Data[e11][6] + (RTX_Rx_Data[e11][7]<<8) - ACC_P_OFFSET);

	RTX_New_Tilt_Theta_P = (float)(ACC_P_GAIN*(RTX_New_Theta_P));	// 0.025 deg/digit
	RTX_New_Tilt_Theta_R = (float)(ACC_R_GAIN*(RTX_New_Theta_R));
	//RTX_New_Tilt_Theta_P = (float)((21./(72.*11.))*(RTX_New_Theta_P));	// 0.025 deg/digit
	//RTX_New_Tilt_Theta_R = (float)((21./(70.*11.))*(RTX_New_Theta_R));
	RTX_New_Tilt_Vel_P = (float)(-0.03663*(RTX_New_Vel_P - RTX_New_Vel_Offset_P));			// 0.03663 deg/sec / digit
	RTX_New_Tilt_Vel_R = (float)(-0.03663*(RTX_New_Vel_R - RTX_New_Vel_Offset_R));


	if(pSharedMemory->GYRO_RESET == TRUE)
	{
		TIME_AVG00++;
		if(TIME_AVG00>=SEC1+1)
		{
			pSharedMemory->GYRO_RESET = FALSE;
			TIME_AVG00 = 0;
			pSharedMemory->StartReadTheta = TRUE;
		}
		else if(TIME_AVG00<SEC1+1)
		{
			RTX_New_Theta_Offset_R+=RTX_New_Theta_R;
			RTX_New_Theta_Offset_P+=RTX_New_Theta_P;

			RTX_New_Vel_Offset_R+=RTX_New_Vel_R;
			RTX_New_Vel_Offset_P+=RTX_New_Vel_P;
			
			if(TIME_AVG00==SEC1)
			{
				RTX_New_Theta_Offset_R = RTX_New_Theta_Offset_R/SEC1;
				RTX_New_Theta_Offset_P = RTX_New_Theta_Offset_P/SEC1;

				RTX_New_Vel_Offset_R = RTX_New_Vel_Offset_R/SEC1;
				RTX_New_Vel_Offset_P = RTX_New_Vel_Offset_P/SEC1;
			}
		}
	}
	else if(pSharedMemory->GYRO_RESET == FALSE)
	{

	}

	if(pSharedMemory->FootAccReset == TRUE)
	{
		FootAccReset();
	}
	
	LPF_New_VelR = (float)((1. - M_GYRO_VEL_CutOff*DELTA_T)*LPF_New_VelR_old + M_GYRO_VEL_CutOff*DELTA_T*RTX_New_Tilt_Vel_R);
	LPF_New_VelP = (float)((1. - M_GYRO_VEL_CutOff*DELTA_T)*LPF_New_VelP_old + M_GYRO_VEL_CutOff*DELTA_T*RTX_New_Tilt_Vel_P);
	LPF_New_VelR_old = LPF_New_VelR;
	LPF_New_VelP_old = LPF_New_VelP;

	RTX_M_Tilt_Vel_R_LPF = LPF_New_VelR;
	RTX_M_Tilt_Vel_P_LPF = LPF_New_VelP;

	
	if(pSharedMemory->StartReadTheta == TRUE)
	{
		Pit_y_a_1_Hspd = (float)((1. - 2.*PI*0.05*DELTA_T)*Pit_y_a_0_Hspd + 2.*PI*0.05*DELTA_T*RTX_New_Tilt_Theta_P);
		Pit_y_a_0_Hspd = Pit_y_a_1_Hspd;
		
		LPF_New_AccR = (float)((1. - 2.*PI*IMU_CUT_OFF1*DELTA_T)*LPF_New_AccR_old + 2.*PI*IMU_CUT_OFF1*DELTA_T*RTX_New_Tilt_Theta_R);
		LPF_New_AccP = (float)((1. - 2.*PI*IMU_CUT_OFF1*DELTA_T)*LPF_New_AccP_old + 2.*PI*IMU_CUT_OFF1*DELTA_T*RTX_New_Tilt_Theta_P);
		LPF_New_AccR_old = LPF_New_AccR;
		LPF_New_AccP_old = LPF_New_AccP;
//
		LPF_AccR = LPF_New_AccR;
		LPF_AccP = LPF_New_AccP;

		LPF_New_VelR = (float)((1. - M_GYRO_VEL_CutOff*DELTA_T)*LPF_New_VelR_old + M_GYRO_VEL_CutOff*DELTA_T*RTX_New_Tilt_Vel_R);
		LPF_New_VelP = (float)((1. - M_GYRO_VEL_CutOff*DELTA_T)*LPF_New_VelP_old + M_GYRO_VEL_CutOff*DELTA_T*RTX_New_Tilt_Vel_P);
		LPF_New_VelR_old = LPF_New_VelR;
		LPF_New_VelP_old = LPF_New_VelP;

		HPF_New_ThetaR = (float)((1. - 2.*PI*IMU_CUT_OFF2*DELTA_T)*HPF_New_ThetaR_old + DELTA_T*(RTX_New_Tilt_Vel_R));
		HPF_New_ThetaP = (float)((1. - 2.*PI*IMU_CUT_OFF2*DELTA_T)*HPF_New_ThetaP_old + DELTA_T*(RTX_New_Tilt_Vel_P));

		HPF2_New_ThetaR = (float)((2. - 2.*2.*PI*IMU_CUT_OFF2*DELTA_T)*HPF2_New_ThetaR_old + (2.*2.*PI*IMU_CUT_OFF2*DELTA_T - 1. - (2.*PI*IMU_CUT_OFF2)*(2.*PI*IMU_CUT_OFF2)*DELTA_T*DELTA_T)*HPF2_New_ThetaR_old2 + DELTA_T*(RTX_New_Tilt_Vel_R - RTX_New_Tilt_Vel_ROLD)); 
		HPF2_New_ThetaR_old2 = HPF2_New_ThetaR_old;
		HPF2_New_ThetaR_old = HPF2_New_ThetaR;
		
		HPF2_New_ThetaP = (float)((2. - 2.*2.*PI*IMU_CUT_OFF2*DELTA_T)*HPF2_New_ThetaP_old + (2.*2.*PI*IMU_CUT_OFF2*DELTA_T - 1. - (2.*PI*IMU_CUT_OFF2)*(2.*PI*IMU_CUT_OFF2)*DELTA_T*DELTA_T)*HPF2_New_ThetaP_old2 + DELTA_T*(RTX_New_Tilt_Vel_P - RTX_New_Tilt_Vel_POLD)); 
		HPF2_New_ThetaP_old2 = HPF2_New_ThetaP_old;
		HPF2_New_ThetaP_old = HPF2_New_ThetaP;
	
		HPF_New_ThetaR_old = HPF_New_ThetaR;
		HPF_New_ThetaP_old = HPF_New_ThetaP;

		RTX_New_Tilt_Vel_ROLD = RTX_New_Tilt_Vel_R;
		RTX_New_Tilt_Vel_POLD = RTX_New_Tilt_Vel_P;

		RTX_New_CompenTheta_R = LPF_New_AccR + HPF2_New_ThetaR;
		RTX_New_CompenTheta_P = LPF_New_AccP + HPF2_New_ThetaP;

		RTX_CompenTheta_R = (float)(RTX_New_CompenTheta_R);
		RTX_CompenTheta_P = (float)(RTX_New_CompenTheta_P);
	}

	/////////////////// Foot ////////////////////////
	//RTX_RF_INCL_R =  (RTX_Rx_Data[96][0] | RTX_Rx_Data[96][1] << 8) - 512 - RTX_RF_Tilt_R_Offset - 3;
	//RTX_RF_INCL_P = -((RTX_Rx_Data[96][2] | RTX_Rx_Data[96][3] << 8) - 512) - RTX_RF_Tilt_P_Offset + 25;
	//RTX_LF_INCL_R =  (RTX_Rx_Data[97][0] | RTX_Rx_Data[97][1] << 8) - 512  - RTX_LF_Tilt_R_Offset - 12 - 20;
	//RTX_LF_INCL_P = -((RTX_Rx_Data[97][2] | RTX_Rx_Data[97][3] << 8) - 512) - RTX_LF_Tilt_P_Offset + 26 - 90;

	RTX_RF_INCL_R =  ((RTX_Rx_Data[c11][0] | RTX_Rx_Data[c11][1] << 8) >> 2) - RF_TILT_R_OFFSET - RTX_RF_Tilt_R_Offset ;
	RTX_RF_INCL_P = -(((RTX_Rx_Data[c11][2] | RTX_Rx_Data[c11][3] << 8) >> 2) - RF_TILT_P_OFFSET) - RTX_RF_Tilt_P_Offset;
	RTX_LF_INCL_R0 =  ((RTX_Rx_Data[d11][0] | RTX_Rx_Data[d11][1] << 8) >> 2) - LF_TILT_R_OFFSET - RTX_LF_Tilt_R_Offset;
	RTX_LF_INCL_P0 = -(((RTX_Rx_Data[d11][2] | RTX_Rx_Data[d11][3] << 8) >> 2) - LF_TILT_P_OFFSET) - RTX_LF_Tilt_P_Offset;


	//RTX_LF_INCL_R =  ((RTX_Rx_Data[c11][0] | RTX_Rx_Data[c11][1] << 8) >> 2) - RF_TILT_R_OFFSET - RTX_RF_Tilt_R_Offset ;
	//RTX_LF_INCL_P = -(((RTX_Rx_Data[c11][2] | RTX_Rx_Data[c11][3] << 8) >> 2) - RF_TILT_P_OFFSET) - RTX_RF_Tilt_P_Offset;
	//RTX_RF_INCL_R =  ((RTX_Rx_Data[d11][0] | RTX_Rx_Data[d11][1] << 8) >> 2) - LF_TILT_R_OFFSET - RTX_LF_Tilt_R_Offset;
	//RTX_RF_INCL_P = -(((RTX_Rx_Data[d11][2] | RTX_Rx_Data[d11][3] << 8) >> 2) - LF_TILT_P_OFFSET) - RTX_LF_Tilt_P_Offset;

	RF_ACC_R_lp = (float)((1. - 2.*PI*RFOOT_ACC_COF1*DELTA_T)*RF_ACC_R_lp0 + 2.*PI*RFOOT_ACC_COF1*DELTA_T*RTX_RF_INCL_R);
	RF_ACC_P_lp = (float)((1. - 2.*PI*RFOOT_ACC_COF1*DELTA_T)*RF_ACC_P_lp0 + 2.*PI*RFOOT_ACC_COF1*DELTA_T*RTX_RF_INCL_P);
	LF_ACC_R_lp = (float)((1. - 2.*PI*LFOOT_ACC_COF1*DELTA_T)*LF_ACC_R_lp0 + 2.*PI*LFOOT_ACC_COF1*DELTA_T*RTX_LF_INCL_R0);
	LF_ACC_P_lp = (float)((1. - 2.*PI*LFOOT_ACC_COF1*DELTA_T)*LF_ACC_P_lp0 + 2.*PI*LFOOT_ACC_COF1*DELTA_T*RTX_LF_INCL_P0);
	
	RF_ACC_R_lp0 = RF_ACC_R_lp;
	RF_ACC_P_lp0 = RF_ACC_P_lp;
	LF_ACC_R_lp0 = LF_ACC_R_lp;
	LF_ACC_P_lp0 = LF_ACC_P_lp;
	

	RF_TILT_P = (float)(RF_ACC_P_lp/COFF_RF_TILT_P);
	RF_TILT_R = (float)(RF_ACC_R_lp/COFF_RF_TILT_R);
	LF_TILT_P = (float)(LF_ACC_P_lp/COFF_LF_TILT_P);
	LF_TILT_R = (float)(LF_ACC_R_lp/COFF_LF_TILT_R);
	
	
	LF_TILT_R_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*LF_TILT_R_HPF_old + (LF_TILT_R - LF_TILT_R_old));
	RF_TILT_R_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*RF_TILT_R_HPF_old + (RF_TILT_R - RF_TILT_R_old));
	LF_TILT_P_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*LF_TILT_P_HPF_old + (LF_TILT_P - LF_TILT_P_old));
	RF_TILT_P_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*RF_TILT_P_HPF_old + (RF_TILT_P - RF_TILT_P_old));

	/*
	LF_TILT_R_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*LF_TILT_R_HPF_old + (LF_TILT_R - LF_TILT_R_old));
	RF_TILT_R_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*RF_TILT_R_HPF_old + (RF_TILT_R - LF_TILT_R_old));
	LF_TILT_P_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*LF_TILT_P_HPF_old + (LF_TILT_P - LF_TILT_P_old));
	RF_TILT_P_HPF = (float)((1.-2.*PI*FOOT_ACC_HPF_COF*DELTA_T)*RF_TILT_P_HPF_old + (RF_TILT_P - RF_TILT_P_old));
	*/
	
	LF_TILT_R_old = LF_TILT_R; LF_TILT_R_HPF_old = LF_TILT_R_HPF;
	RF_TILT_R_old = RF_TILT_R; RF_TILT_R_HPF_old = RF_TILT_R_HPF;
	
	LF_TILT_P_old = LF_TILT_P; LF_TILT_P_HPF_old = LF_TILT_P_HPF;
	RF_TILT_P_old = RF_TILT_P; RF_TILT_P_HPF_old = RF_TILT_P_HPF;
	
	LF_TILT_R_Vel = (float)((1. - 2.*PI*FOOT_VEL_LPF_COF*DELTA_T)*LF_TILT_R_Vel_old + DELTA_T*LF_ACC_R_lp0);
	RF_TILT_R_Vel = (float)((1. - 2.*PI*FOOT_VEL_LPF_COF*DELTA_T)*RF_TILT_R_Vel_old + DELTA_T*RF_ACC_R_lp0);
	
	LF_TILT_R_Vel_old = LF_TILT_R_Vel;
	RF_TILT_R_Vel_old = RF_TILT_R_Vel;
	
	LF_TILT_P_Vel = (float)((1. - 2.*PI*FOOT_VEL_LPF_COF*DELTA_T)*LF_TILT_P_Vel_old + DELTA_T*LF_ACC_P_lp0);
	RF_TILT_P_Vel = (float)((1. - 2.*PI*FOOT_VEL_LPF_COF*DELTA_T)*RF_TILT_P_Vel_old + DELTA_T*RF_ACC_P_lp0);
	
	LF_TILT_P_Vel_old = LF_TILT_P_Vel;
	RF_TILT_P_Vel_old = RF_TILT_P_Vel;

		
	/////////////////// Foot ////////////////////////
	
}

void ALLFTRead()
{
	int RFTS;
	int LFTS;
	int RWFTS;
	int LWFTS;

	RFTS=GetBuffno(SENSOR_FT1_RXDF);
	LFTS=GetBuffno(SENSOR_FT2_RXDF);
	RWFTS=GetBuffno(SENSOR_FT3_RXDF);
	LWFTS=GetBuffno(SENSOR_FT4_RXDF);
	

	RTX_RFOOT_My =  (int)((RTX_Rx_Data[RFTS][0] << 16  | (RTX_Rx_Data[RFTS][1] << 24))/65536);
	RTX_RFOOT_Mx =  (int)((RTX_Rx_Data[RFTS][2] << 16 | (RTX_Rx_Data[RFTS][3] << 24))/65536);
	RTX_RFOOT_Fz =  -(int)((RTX_Rx_Data[RFTS][4] << 16  | (RTX_Rx_Data[RFTS][5] << 24))/65536);	// sign is changed

	//RTX_RFOOT_My0 =  (int)((RTX_Rx_Data[RFTS][0] << 16  | (RTX_Rx_Data[RFTS][1] << 24))/65536);
	//RTX_RFOOT_Mx0 =  (int)((RTX_Rx_Data[RFTS][2] << 16 | (RTX_Rx_Data[RFTS][3] << 24))/65536);
	//RTX_RFOOT_Fz0 =  -(int)((RTX_Rx_Data[RFTS][4] << 16  | (RTX_Rx_Data[RFTS][5] << 24))/65536);	// sign is changed
	
	RTX_LFOOT_My =  (int)((RTX_Rx_Data[LFTS][0] << 16 | (RTX_Rx_Data[LFTS][1] << 24))/65536);
	RTX_LFOOT_Mx =  (int)((RTX_Rx_Data[LFTS][2] << 16 | (RTX_Rx_Data[LFTS][3] << 24))/65536);
	RTX_LFOOT_Fz =  -(int)((RTX_Rx_Data[LFTS][4] << 16 | (RTX_Rx_Data[LFTS][5] << 24))/65536);

	//RTX_RWRIST_My =  (int)((RTX_Rx_Data[RWFTS][0] << 16  | (RTX_Rx_Data[RWFTS][1] << 24))/65536);
	//RTX_RWRIST_Mx =  (int)((RTX_Rx_Data[RWFTS][2] << 16 | (RTX_Rx_Data[RWFTS][3] << 24))/65536);
	//RTX_RWRIST_Fz =  -(int)((RTX_Rx_Data[RWFTS][4] << 16  | (RTX_Rx_Data[RWFTS][5] << 24))/65536);	// sign is changed

	//RTX_LWRIST_My =  (int)((RTX_Rx_Data[LWFTS][0] << 16  | (RTX_Rx_Data[LWFTS][1] << 24))/65536);
	//RTX_LWRIST_Mx =  (int)((RTX_Rx_Data[LWFTS][2] << 16 | (RTX_Rx_Data[LWFTS][3] << 24))/65536);
	//RTX_LWRIST_Fz =  -(int)((RTX_Rx_Data[LWFTS][4] << 16  | (RTX_Rx_Data[LWFTS][5] << 24))/65536);	// sign is changed

	RTX_RWRIST_Mx =  (int)((RTX_Rx_Data[RWFTS][0] << 16  | (RTX_Rx_Data[RWFTS][1] << 24))/65536);
	RTX_RWRIST_My =  -(int)((RTX_Rx_Data[RWFTS][2] << 16 | (RTX_Rx_Data[RWFTS][3] << 24))/65536);
	RTX_RWRIST_Fz =  -(int)((RTX_Rx_Data[RWFTS][4] << 16  | (RTX_Rx_Data[RWFTS][5] << 24))/65536);	// sign is changed

	RTX_LWRIST_Mx =  (int)((RTX_Rx_Data[LWFTS][0] << 16  | (RTX_Rx_Data[LWFTS][1] << 24))/65536);
	RTX_LWRIST_My =  -(int)((RTX_Rx_Data[LWFTS][2] << 16 | (RTX_Rx_Data[LWFTS][3] << 24))/65536);
	RTX_LWRIST_Fz =  -(int)((RTX_Rx_Data[LWFTS][4] << 16  | (RTX_Rx_Data[LWFTS][5] << 24))/65536);	// sign is changed

	RTX_NM_RWRIST_My = (float)(0.060025*RTX_RWRIST_My);
	RTX_NM_RWRIST_Mx = (float)(0.060025*RTX_RWRIST_Mx);
	RTX_N_RWRIST_Fz = (float)(0.1*RTX_RWRIST_Fz);

	RTX_NM_LWRIST_My = (float)(0.060025*RTX_LWRIST_My);
	RTX_NM_LWRIST_Mx = (float)(0.060025*RTX_LWRIST_Mx);
	RTX_N_LWRIST_Fz = (float)(0.1*RTX_LWRIST_Fz);

	RTX_NM_RWRIST_My_LPF = (float)((1. - 2.*PI*WRIST_FT_M_COF*DELTA_T)*RTX_NM_RWRIST_My_old + 2.*PI*WRIST_FT_M_COF*DELTA_T*RTX_NM_RWRIST_My);
	RTX_NM_RWRIST_Mx_LPF = (float)((1. - 2.*PI*WRIST_FT_M_COF*DELTA_T)*RTX_NM_RWRIST_Mx_old + 2.*PI*WRIST_FT_M_COF*DELTA_T*RTX_NM_RWRIST_Mx);
	RTX_N_RWRIST_Fz_LPF = (float)((1. - 2.*PI*WRIST_FT_FZ_COF*DELTA_T)*RTX_N_RWRIST_Fz_old + 2.*PI*WRIST_FT_FZ_COF*DELTA_T*RTX_N_RWRIST_Fz);

	RTX_NM_LWRIST_My_LPF = (float)((1. - 2.*PI*WRIST_FT_M_COF*DELTA_T)*RTX_NM_LWRIST_My_old + 2.*PI*WRIST_FT_M_COF*DELTA_T*RTX_NM_LWRIST_My);
	RTX_NM_LWRIST_Mx_LPF = (float)((1. - 2.*PI*WRIST_FT_M_COF*DELTA_T)*RTX_NM_LWRIST_Mx_old + 2.*PI*WRIST_FT_M_COF*DELTA_T*RTX_NM_LWRIST_Mx);
	RTX_N_LWRIST_Fz_LPF = (float)((1. - 2.*PI*WRIST_FT_FZ_COF*DELTA_T)*RTX_N_LWRIST_Fz_old + 2.*PI*WRIST_FT_FZ_COF*DELTA_T*RTX_N_LWRIST_Fz);

	RTX_NM_RWRIST_My_old = RTX_NM_RWRIST_My_LPF;	RTX_NM_RWRIST_Mx_old = RTX_NM_RWRIST_Mx_LPF;	RTX_N_RWRIST_Fz_old = RTX_N_RWRIST_Fz_LPF;
	RTX_NM_LWRIST_My_old = RTX_NM_LWRIST_My_LPF;	RTX_NM_LWRIST_Mx_old = RTX_NM_LWRIST_Mx_LPF;	RTX_N_LWRIST_Fz_old = RTX_N_LWRIST_Fz_LPF;

	RTX_NM_RFOOT_Mx = -(float)(RF_DC_MAT[0][0]*RTX_RFOOT_Mx +  RF_DC_MAT[0][1]*RTX_RFOOT_My + RF_DC_MAT[0][2]*RTX_RFOOT_Fz);
	RTX_NM_RFOOT_My = (float)(RF_DC_MAT[1][0]*RTX_RFOOT_Mx +  RF_DC_MAT[1][1]*RTX_RFOOT_My + RF_DC_MAT[1][2]*RTX_RFOOT_Fz);
	//RTX_N_RFOOT_Fz = (float)(RF_DC_MAT[2][0]*RTX_RFOOT_Mx +  RF_DC_MAT[2][1]*RTX_RFOOT_My + RF_DC_MAT[2][2]*RTX_RFOOT_Fz);
	// scale factor is multiplied to adjust the measured value
	RTX_N_RFOOT_Fz = (float)((RF_DC_MAT[2][0]*RTX_RFOOT_Mx +  RF_DC_MAT[2][1]*RTX_RFOOT_My + RF_DC_MAT[2][2]*RTX_RFOOT_Fz));

	RTX_NM_LFOOT_Mx = -(float)(LF_DC_MAT[0][0]*RTX_LFOOT_Mx +  LF_DC_MAT[0][1]*RTX_LFOOT_My + LF_DC_MAT[0][2]*RTX_LFOOT_Fz);
	RTX_NM_LFOOT_My = (float)(LF_DC_MAT[1][0]*RTX_LFOOT_Mx +  LF_DC_MAT[1][1]*RTX_LFOOT_My + LF_DC_MAT[1][2]*RTX_LFOOT_Fz);
	RTX_N_LFOOT_Fz = (float)(LF_DC_MAT[2][0]*RTX_LFOOT_Mx +  LF_DC_MAT[2][1]*RTX_LFOOT_My + LF_DC_MAT[2][2]*RTX_LFOOT_Fz);

	
	
	
	if(RTX_N_RFOOT_Fz + RTX_N_LFOOT_Fz > 50.)
	{
		RTX_Xzmp =(float)(1000.*(RTX_NM_LFOOT_My + RTX_N_LFOOT_Fz*OL_x/1000.
								  + RTX_NM_RFOOT_My + RTX_N_RFOOT_Fz*OR_x/1000.)
								  /(RTX_N_LFOOT_Fz + RTX_N_RFOOT_Fz));
		RTX_Yzmp =(float)(1000.*(RTX_NM_LFOOT_Mx + RTX_N_LFOOT_Fz*OL_y/1000. 
								  + RTX_NM_RFOOT_Mx + RTX_N_RFOOT_Fz*OR_y/1000.)
								  /(RTX_N_LFOOT_Fz + RTX_N_RFOOT_Fz));
	}
	
	if(RTX_N_RFOOT_Fz > 50.)
	{
		RTX_RXzmp = (float)(1000.*(RTX_NM_RFOOT_My)/(RTX_N_RFOOT_Fz));
		RTX_RYzmp = (float)(1000.*(RTX_NM_RFOOT_Mx)/(RTX_N_RFOOT_Fz));
	}

	if(RTX_N_LFOOT_Fz > 50.)
	{
		RTX_LXzmp = (float)(1000.*(RTX_NM_LFOOT_My)/(RTX_N_LFOOT_Fz));
		RTX_LYzmp = (float)(1000.*(RTX_NM_LFOOT_Mx)/(RTX_N_LFOOT_Fz));
	}

	//RTX_ErrZMP[0] = RTX_Xzmp - RTX_RefZMP[0];
	//RTX_ErrZMP[1] = RTX_Yzmp - RTX_RefZMP[1];

	Err_Xzmp = Init_Xzmp - RTX_Xzmp; 
	Err_Yzmp = Init_Yzmp - RTX_Yzmp;
	
	/*
	if((stage00 == 0) || (stage00 == 2) || (stage00 == 4))
	{
		if((LSteadyFlag==0) && (RTX_N_LFOOT_Fz > FT_COND1)) {LSteadyFlag = 1; RSteadyFlag = 0;}

		if((RSteadyFlag==0) && (RTX_N_RFOOT_Fz > FT_COND1)) {RSteadyFlag = 1; LSteadyFlag = 0;}

		if(Status[0] == 1) RSteadyFlag = 0;
		
		if((LandLOK_Flag==0) && (RTX_N_LFOOT_Fz > FT_COND1)) {LandLOK_Flag = 1; LandROK_Flag = 0;}
		
		if((LandROK_Flag==0) && (RTX_N_RFOOT_Fz > FT_COND1)) {LandROK_Flag = 1; LandLOK_Flag = 0;}
		
		if(Status[0] == 1) LandROK_Flag = 0;
		
	}
	else if((stage00 == 1) || (stage00 == 3) || (stage00 == 5))
	{
		if(RTX_N_LFOOT_Fz < FT_COND1) LSteadyFlag = 0;

		if(RTX_N_RFOOT_Fz < FT_COND1) RSteadyFlag = 0;

		if(RTX_N_LFOOT_Fz < FT_COND1) LandLOK_Flag = 0;
		
		if(RTX_N_RFOOT_Fz < FT_COND1) LandROK_Flag = 0;
	}*/

	if(RTX_N_LFOOT_Fz > FT_COND1 && LandLOK_Flag == 0)  LandLOK_Flag = 1;
	
	if(RTX_N_RFOOT_Fz > FT_COND1 && LandROK_Flag == 0) LandROK_Flag = 1;
	
	if(RTX_N_RFOOT_Fz > 49) FiveKG_R_Flag = 1;
	if(RTX_N_LFOOT_Fz > 49) FiveKG_L_Flag = 1;

	
	Xzmp_lp = (float)((1 - 2*PI*ZMP_LP_CUTOFF*DELTA_T)*oldXzmp_lp + (2*PI*ZMP_LP_CUTOFF*DELTA_T)*RTX_Xzmp);
	Yzmp_lp = (float)((1 - 2*PI*ZMP_LP_CUTOFF*DELTA_T)*oldYzmp_lp + (2*PI*ZMP_LP_CUTOFF*DELTA_T)*RTX_Yzmp);

	//Xzmp_lp1 = (float)((1 - 2*PI*ZMP_LP_CUTOFF1*DELTA_T)*oldXzmp_lp1 + (2*PI*ZMP_LP_CUTOFF1*DELTA_T)*RTX_Xzmp);
	//Yzmp_lp1 = (float)((1 - 2*PI*ZMP_LP_CUTOFF1*DELTA_T)*oldYzmp_lp1 + (2*PI*ZMP_LP_CUTOFF1*DELTA_T)*RTX_Yzmp);

	oldXzmp_lp = Xzmp_lp;
	oldYzmp_lp = Yzmp_lp;
	
	//oldXzmp_lp1 = Xzmp_lp1;
	//oldYzmp_lp1 = Yzmp_lp1;
	
}

void	ALLEncRead()
{
	int i;
	int j;
	int JMC_Buff_no;
	unsigned char TxData[2];
	LARGE_INTEGER a;
	a.QuadPart = 2000000;
	
	TxData[1] = SendEncoder;

	
	for(j=0;j<=JMC7;j++)
	{
		TxData[0] = j;
		CanSendMsg(0, CMD_TXDF, TxData, 2, 0);
	}

	for(j=JMC8;j<=JMC11;j++)
	{
		TxData[0] = j;
		CanSendMsg(1, CMD_TXDF, TxData, 2, 0);
	}
	
	for(j=EJMC0;j<(EJMC0+TOTAL_EJMC_NUM);j++)
	{
		TxData[0] = j;
		CanSendMsg(1, CMD_TXDF, TxData, 2, 0);
	}

	//Sleep(200); // unit is 1 msec
	RtSleepFt(&a);	// unit is 100 nsec

	JMC_Buff_no = GetBuffno(ENC_BASE_RXDF);
	
	for(i=JMC_Buff_no;i<JMC_Buff_no+TOTAL_JMC_NUM;i++)
	{
		if((i == JMC_Buff_no+JMC1) || (i == JMC_Buff_no+JMC2) || (i == JMC_Buff_no+JMC5) || (i == JMC_Buff_no+JMC6))
		{
			pSharedMemory->ENC_POS[i-JMC_Buff_no][0]=(pSharedMemory->Rx_Data[i][0])|(pSharedMemory->Rx_Data[i][1]<<8)|(pSharedMemory->Rx_Data[i][2]<<16)|(pSharedMemory->Rx_Data[i][3]<<24);
		}
		else
		{
			pSharedMemory->ENC_POS[i-JMC_Buff_no][0]=(pSharedMemory->Rx_Data[i][0])|(pSharedMemory->Rx_Data[i][1]<<8)|(pSharedMemory->Rx_Data[i][2]<<16)|(pSharedMemory->Rx_Data[i][3]<<24);
			pSharedMemory->ENC_POS[i-JMC_Buff_no][1]=(pSharedMemory->Rx_Data[i][4])|(pSharedMemory->Rx_Data[i][5]<<8)|(pSharedMemory->Rx_Data[i][6]<<16)|(pSharedMemory->Rx_Data[i][7]<<24);
		}
	}

	for(i=JMC_Buff_no+32;i<JMC_Buff_no+32+TOTAL_EJMC_NUM;i++)
	{
		if((i == JMC_Buff_no+EJMC0) || (i == JMC_Buff_no+EJMC1) || (i == JMC_Buff_no+EJMC2))
		{
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][0] = (short int)((pSharedMemory->Rx_Data[i][0])|(pSharedMemory->Rx_Data[i][1]<<8));
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][1] = (short int)((pSharedMemory->Rx_Data[i][2])|(pSharedMemory->Rx_Data[i][3]<<8));
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][2] = (short int)((pSharedMemory->Rx_Data[i][4])|(pSharedMemory->Rx_Data[i][5]<<8));
		}
		else if(i == JMC_Buff_no+EJMC3)
		{
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][0] = ((pSharedMemory->Rx_Data[i][0])|(pSharedMemory->Rx_Data[i][1]<<8));
		}
		else if((i == JMC_Buff_no+EJMC4) || (i == JMC_Buff_no+EJMC5))
		{
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][0] = ((pSharedMemory->Rx_Data[i][0])|(pSharedMemory->Rx_Data[i][1]<<8));
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][1] = ((pSharedMemory->Rx_Data[i][2])|(pSharedMemory->Rx_Data[i][3]<<8));
			pSharedMemory->Ex_ENC_POS[i-JMC_Buff_no-32][2] = ((pSharedMemory->Rx_Data[i][4])|(pSharedMemory->Rx_Data[i][5]<<8));
		}
		// 손가락을 아직 정의 되지 않음.
	}

}

void ALLPOSCTRL()
{
	int i;
	float JNT_ANG[TOTAL_MTR_NUM];
	
	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		if(pSharedMemory->Move_Flag[i])
		{	
			pSharedMemory->Move_CNT[i]++;
			FTN_half_1_cos(pSharedMemory->Deltheta[i],pSharedMemory->Move_CNT[i],0,pSharedMemory->Tfinal[i],0,0,&JNT_ANG[i]);
			pSharedMemory->Reftheta[i] = pSharedMemory->Oldtheta[i] + JNT_ANG[i];
			pSharedMemory->RefVel[i] = (float)((pSharedMemory->Reftheta[i] - pSharedMemory->Oldtheta[i])/DELTA_T);
			
			RTxMoveAng(i,pSharedMemory->Reftheta[i]);
			
			if(pSharedMemory->Move_CNT[i] == pSharedMemory->Tfinal[i])
			{
				pSharedMemory->Oldtheta[i] = pSharedMemory->Reftheta[i];
				pSharedMemory->Move_Flag[i]=0;
				pSharedMemory->Move_CNT[i]=0;
			}
		}
	}
}

void	FootAccReset()
{
	static unsigned int i=0;
	
	if((i>=0)&&(i<SEC1))
	{
		FootTilt[0] = FootTilt[0] + RTX_LF_INCL_P0;
		FootTilt[1] = FootTilt[1] + RTX_LF_INCL_R0;
		FootTilt[2] = FootTilt[2] + RTX_RF_INCL_P;
		FootTilt[3] = FootTilt[3] + RTX_RF_INCL_R;
	}
	else if(i==SEC1)
	{
		RTX_LF_Tilt_P_Offset = FootTilt[0]/SEC1;
		RTX_LF_Tilt_R_Offset = FootTilt[1]/SEC1;
		RTX_RF_Tilt_P_Offset = FootTilt[2]/SEC1;
		RTX_RF_Tilt_R_Offset = FootTilt[3]/SEC1;
		
		pSharedMemory->FootAccReset = FALSE;
		i=0;
	}
	
	if(i<SEC1+2)	i++;
}

void SharedMEMUpdate()
{
	int i=0,j=0;
	
	for(i=0;i<MBSIZE;i++)
	{
		for(j=0;j<8;j++)
		{
			RTX_Rx_Data[i][j]=pSharedMemory->Rx_Data[i][j];
		}
	}

	/////////////////// FTS Reading //////////////////////
	
	pSharedMemory->RFOOT_My = RTX_RFOOT_My;
	pSharedMemory->RFOOT_Mx = RTX_RFOOT_Mx;
	pSharedMemory->RFOOT_Fz = RTX_RFOOT_Fz;

	//pSharedMemory->RFOOT_My = RTX_RFOOT_My0;
	//pSharedMemory->RFOOT_Mx = RTX_RFOOT_Mx0;
	//pSharedMemory->RFOOT_Fz = RTX_RFOOT_Fz0;
	
	pSharedMemory->LFOOT_My = RTX_LFOOT_My;
	pSharedMemory->LFOOT_Mx = RTX_LFOOT_Mx;
	pSharedMemory->LFOOT_Fz = RTX_LFOOT_Fz;
	
	
	pSharedMemory->RWRIST_Mx = RTX_RWRIST_Mx;
	pSharedMemory->RWRIST_My = RTX_RWRIST_My;
	pSharedMemory->RWRIST_Fz = RTX_RWRIST_Fz;
	
	pSharedMemory->LWRIST_Mx = RTX_LWRIST_Mx;
	pSharedMemory->LWRIST_My = RTX_LWRIST_My;
	pSharedMemory->LWRIST_Fz = RTX_LWRIST_Fz;
	
	
	pSharedMemory->NM_RFOOT_Mx	= RTX_NM_RFOOT_Mx;
	pSharedMemory->NM_RFOOT_My	= RTX_NM_RFOOT_My;
	pSharedMemory->N_RFOOT_Fz	= RTX_N_RFOOT_Fz;
	
	pSharedMemory->NM_LFOOT_Mx	= RTX_NM_LFOOT_Mx;
	pSharedMemory->NM_LFOOT_My	= RTX_NM_LFOOT_My;
	pSharedMemory->N_LFOOT_Fz	= RTX_N_LFOOT_Fz;
	
	pSharedMemory->NM_RWRIST_Mx = RTX_NM_RWRIST_Mx;
	pSharedMemory->NM_RWRIST_My = RTX_NM_RWRIST_My;
	pSharedMemory->N_RWRIST_Fz	= RTX_N_RWRIST_Fz;
	pSharedMemory->NM_LWRIST_Mx = RTX_NM_LWRIST_Mx;
	pSharedMemory->NM_LWRIST_My = RTX_NM_LWRIST_My;
	pSharedMemory->N_LWRIST_Fz	= RTX_N_LWRIST_Fz;
	
	pSharedMemory->Xzmp = RTX_Xzmp;
	pSharedMemory->Yzmp = RTX_Yzmp;
	
	pSharedMemory->RXzmp = RTX_RXzmp;
	pSharedMemory->RYzmp = RTX_RYzmp;
	
	pSharedMemory->LXzmp = RTX_LXzmp;
	pSharedMemory->LYzmp = RTX_LYzmp;

	/////////////////// Tilt Reading //////////////////////
	pSharedMemory->ACC_P = RTX_New_Theta_P;
	pSharedMemory->ACC_R = RTX_New_Theta_R;
	pSharedMemory->GYRO_P = RTX_New_Vel_P;
	pSharedMemory->GYRO_R = RTX_New_Vel_R;
	
	
	//RTX_Gyro_CutOffR =  pSharedMemory->Gyro_CutOffR;
	//RTX_Gyro_CutOffP =  pSharedMemory->Gyro_CutOffP;
	//RTX_Gyro_CutOffY =  pSharedMemory->Gyro_CutOffY;
	
	//RTX_Acc_CutOffR  =  pSharedMemory->Acc_CutOffR;
	//RTX_Acc_CutOffP  =  pSharedMemory->Acc_CutOffP;
	
	//pSharedMemory->Flt_AccR1 = FltAccR1;
	//pSharedMemory->Flt_AccP1 = FltAccP1;	
	
	//pSharedMemory->Tilt_theta_R = RTX_Tilt_theta_R;
	//pSharedMemory->Tilt_theta_P = RTX_Tilt_theta_P;
	//pSharedMemory->Tilt_theta_Y = RTX_Tilt_theta_Y;
	
	pSharedMemory->M_Theta_P = RTX_M_Tilt_Theta_R;
	pSharedMemory->M_Theta_R = RTX_M_Tilt_Theta_P;

	pSharedMemory->New_Theta_P = RTX_New_Theta_R;
	pSharedMemory->New_Theta_R = RTX_New_Theta_P;
	pSharedMemory->New_Vel_P = RTX_New_Vel_R;
	pSharedMemory->New_Vel_R = RTX_New_Vel_P;

	//pSharedMemory->New_Theta_P = RTX_New_Tilt_Theta_P;
	//pSharedMemory->New_Theta_R = RTX_New_Tilt_Theta_R;
	//pSharedMemory->New_Vel_P = RTX_New_Tilt_Vel_P;
	//pSharedMemory->New_Vel_R = RTX_New_Tilt_Vel_R;
	
	pSharedMemory->Incl_P = AccP_deg;
	pSharedMemory->Incl_R = AccR_deg;
	
	pSharedMemory->Compen_Theta_P = RTX_CompenTheta_P;
	pSharedMemory->Compen_Theta_R = RTX_CompenTheta_R;
		
	pSharedMemory->LF_INCL_P = RTX_LF_INCL_P0;
	pSharedMemory->LF_INCL_R = RTX_LF_INCL_R0;
	
	pSharedMemory->RF_INCL_R = RTX_RF_INCL_R;
	pSharedMemory->RF_INCL_P = RTX_RF_INCL_P;
	
	//pSharedMemory->RF_ACC_R_lp = RF_ACC_R_lp;
	//pSharedMemory->RF_ACC_P_lp = RF_ACC_P_lp;
	
	//pSharedMemory->LF_ACC_R_lp = LF_ACC_R_lp;
	//pSharedMemory->LF_ACC_P_lp = LF_ACC_P_lp;
	
	pSharedMemory->RF_TILT_R = RF_TILT_R;
	pSharedMemory->RF_TILT_P = RF_TILT_P;
	
	pSharedMemory->LF_TILT_R = LF_TILT_R;
	pSharedMemory->LF_TILT_P = LF_TILT_P;
	
	pSharedMemory->M_Theta_P = RTX_M_Tilt_Theta_P;
	pSharedMemory->M_Theta_R = RTX_M_Tilt_Theta_R;
	pSharedMemory->M_Vel_P = RTX_M_Tilt_Vel_P;
	pSharedMemory->M_Vel_R = RTX_M_Tilt_Vel_R;

	pSharedMemory->AvgXZmp[LEFT] = AvgZMP[LEFT][0];
	pSharedMemory->AvgXZmp[RIGHT] = AvgZMP[RIGHT][0];
	pSharedMemory->AvgYZmp[LEFT] = AvgZMP[LEFT][1];
	pSharedMemory->AvgYZmp[RIGHT] = AvgZMP[RIGHT][1];
	pSharedMemory->AvgRoll[LEFT] = AvgRoll[LEFT];
	pSharedMemory->AvgRoll[RIGHT] = AvgRoll[RIGHT];
	pSharedMemory->AvgPitch[LEFT] = AvgPitch[LEFT];
	pSharedMemory->AvgPitch[RIGHT] = AvgPitch[RIGHT];
	pSharedMemory->AvgGyroRoll[LEFT] = AvgGyroRoll[LEFT];
	pSharedMemory->AvgGyroRoll[RIGHT] = AvgGyroRoll[RIGHT];
	pSharedMemory->AvgGyroPitch[LEFT] = AvgGyroPitch[LEFT];
	pSharedMemory->AvgGyroPitch[RIGHT] = AvgGyroPitch[RIGHT];

	pSharedMemory->TotalAvgXZmp[LEFT] = TotalAvgZMP[LEFT][0];
	pSharedMemory->TotalAvgXZmp[RIGHT] = TotalAvgZMP[RIGHT][0];
	pSharedMemory->TotalAvgYZmp[LEFT] = TotalAvgZMP[LEFT][1];
	pSharedMemory->TotalAvgYZmp[RIGHT] = TotalAvgZMP[RIGHT][1];
	pSharedMemory->TotalAvgRoll[LEFT] = TotalAvgRoll[LEFT];
	pSharedMemory->TotalAvgRoll[RIGHT] = TotalAvgRoll[RIGHT];
	pSharedMemory->TotalAvgPitch[LEFT] = TotalAvgPitch[LEFT];
	pSharedMemory->TotalAvgPitch[RIGHT] = TotalAvgPitch[RIGHT];
	pSharedMemory->TotalAvgGyroRoll[LEFT] = TotalAvgGyroRoll[LEFT];
	pSharedMemory->TotalAvgGyroRoll[RIGHT] = TotalAvgGyroRoll[RIGHT];
	pSharedMemory->TotalAvgGyroPitch[LEFT] = TotalAvgGyroPitch[LEFT];
	pSharedMemory->TotalAvgGyroPitch[RIGHT] = TotalAvgGyroPitch[RIGHT];

	///////////////////// Motion Profile ////////////////////
	pSharedMemory->fProfXYZ[0] = RTX_fXYZ[0];
	pSharedMemory->fProfXYZ[1] = RTX_fXYZ[1];
	pSharedMemory->fProfXYZ[2] = RTX_fXYZ[2];
	pSharedMemory->fProfXYZ[3] = RTX_fXYZ[3];
	pSharedMemory->fProfXYZ[4] = RTX_fXYZ[4];
	pSharedMemory->fProfXYZ[5] = RTX_fXYZ[5];
}

void RTxMoveAng(unsigned char moID,float angle)
{
	long    Pulses;
	unsigned char BoardNo;
	unsigned char MotorCh;
	unsigned long temp;
	long	temp1;
	float	delta_pos;
	long	FingerPulse;
	unsigned long temp_hand;
	
	Pulses = (long)(angle*PLUS_MTR_DIR[moID]*PPR[moID]/360.);

	switch(moID)
	{
	case RHY:
		BoardNo = JMC0;
		MotorCh = 0;	// 1st motor
		break;
	case RHR:
		BoardNo = JMC0;
		MotorCh = 3;	// 2nd motor
		break;
	case RHP:
		BoardNo = JMC1;
		MotorCh = 0;
		break;
	case RKN:
		BoardNo = JMC2;
		MotorCh = 0;
		break;
	case RAP:
		BoardNo = JMC3;
		MotorCh = 0;
		break;
	case RAR:
		BoardNo = JMC3;
		MotorCh = 3;
		break;
	case LHY:
		BoardNo = JMC4;
		MotorCh = 0;
		break;
	case LHR:
		BoardNo = JMC4;
		MotorCh = 3;
		break;
	case LHP:
		BoardNo = JMC5;
		MotorCh = 0;
		break;
	case LKN:
		BoardNo = JMC6;
		MotorCh = 0;
		break;
	case LAP:
		BoardNo = JMC7;
		MotorCh = 0;
		break;
	case LAR:
		BoardNo = JMC7;
		MotorCh = 3;
		break;
	case RSP:
		BoardNo = JMC8;
		MotorCh = 0;
		break;
	case RSR:
		BoardNo = JMC8;
		MotorCh = 3;
		break;
	case RSY:
		BoardNo = JMC9;
		MotorCh = 0;
		break;
	case REB:
		BoardNo = JMC9;
		MotorCh = 3;
		break;
	case LSP:
		BoardNo = JMC10;
		MotorCh = 0;
		break;
	case LSR:
		BoardNo = JMC10;
		MotorCh = 3;
		break;
	case LSY:
		BoardNo = JMC11;
		MotorCh = 0;
		break;
	case LEB:
		BoardNo = JMC11;
		MotorCh = 3;
		break;
	case RWY:
		BoardNo = EJMC0;
		MotorCh = 0;
		break;
	case RW1:
		BoardNo = EJMC0;
		MotorCh = 2;
		break;
	case RW2:
		BoardNo = EJMC0;
		MotorCh = 4;
		break;
	case LWY:
		BoardNo = EJMC1;
		MotorCh = 0;
		break;
	case LW1:
		BoardNo = EJMC1;
		MotorCh = 2;
		break;
	case LW2:
		BoardNo = EJMC1;
		MotorCh = 4;
		break;
	case NKY:
		BoardNo = EJMC2;
		MotorCh = 0;
		break;
	case NK1:
		BoardNo = EJMC2;
		MotorCh = 2;
		break;
	case NK2:
		BoardNo = EJMC2;
		MotorCh = 4;
		break;
	case WST:
		BoardNo = EJMC3;
		MotorCh = 0;
		break;
	case RF1:
		BoardNo = EJMC4;
		MotorCh = 0;
		delta_pos = RTX_fREF[RF1] - RTX_fREFOLD[RF1];
		break;
	case RF2:
		BoardNo = EJMC4;
		MotorCh = 1;
		delta_pos = RTX_fREF[RF2] - RTX_fREFOLD[RF2];
		break;
	case RF3:
		BoardNo = EJMC4;
		MotorCh = 2;
		delta_pos = RTX_fREF[RF3] - RTX_fREFOLD[RF3];
		break;
	case RF4:
		BoardNo = EJMC4;
		MotorCh = 3;
		delta_pos = RTX_fREF[RF4] - RTX_fREFOLD[RF4];
		break;
	case RF5:
		BoardNo = EJMC4;
		MotorCh = 4;
		delta_pos = RTX_fREF[RF5] - RTX_fREFOLD[RF5];
		break;
	case LF1:
		BoardNo = EJMC5;
		MotorCh = 0;
		delta_pos = RTX_fREF[LF1] - RTX_fREFOLD[LF1];
		break;
	case LF2:
		BoardNo = EJMC5;
		MotorCh = 1;
		delta_pos = RTX_fREF[LF2] - RTX_fREFOLD[LF2];
		break;
	case LF3:
		BoardNo = EJMC5;
		MotorCh = 2;
		delta_pos = RTX_fREF[LF3] - RTX_fREFOLD[LF3];
		break;
	case LF4:
		BoardNo = EJMC5;
		MotorCh = 3;
		delta_pos = RTX_fREF[LF4] - RTX_fREFOLD[LF4];
		break;
	case LF5:
		BoardNo = EJMC5;
		MotorCh = 4;
		delta_pos = RTX_fREF[LF5] - RTX_fREFOLD[LF5];
		break;
	}

	//if(BoardNo <= JMC11)
	if((BoardNo <= JMC11) || (BoardNo == EJMC3))
	{
		temp = SignFunc(Pulses);

		if(Pulses < 0) temp1 = (((-Pulses) & 0x007FFFFF) | 0x00800000);
		else if(Pulses >= 0) temp1 = Pulses & 0x007FFFFF;

		MotorPos[BoardNo][0+MotorCh]=(unsigned char)(temp & 0xFF);
		MotorPos[BoardNo][1+MotorCh]=(unsigned char)((temp >> 8) & 0xFF);
		MotorPos[BoardNo][2+MotorCh]=(unsigned char)((temp >> 16) & 0xFF);
	}
	else if((BoardNo>=EJMC0) && (BoardNo<=EJMC2))
	{
		MotorPos[BoardNo][0+MotorCh] = (unsigned char)(Pulses & 0xFF);
		MotorPos[BoardNo][1+MotorCh] = (unsigned char)((Pulses >> 8) & 0xFF);
	}
	else if((BoardNo>=EJMC4) && (BoardNo<=EJMC5))
	{
		FingerPulse = (long)(delta_pos*PLUS_MTR_DIR[moID]*PPR[moID]/360.);

		temp_hand = HandSignFunc(FingerPulse);

		//if (FingerPulse < 0) FingerPulse =  (UINT)(((-FingerPulse) & 0x000007FF) | (1<<11));
		//else	;
		
		if(MotorCh == 0)
		{
			MotorPos[BoardNo][MotorCh] = (unsigned char)(temp_hand & 0xFF);
			MotorPos[BoardNo][5] = (unsigned char)(MotorPos[BoardNo][5] | ((temp_hand >> 8) & 0x0F));
		}
		else if(MotorCh == 1)
		{
			MotorPos[BoardNo][MotorCh] = (unsigned char)(temp_hand & 0xFF);
			MotorPos[BoardNo][5] = (unsigned char)(MotorPos[BoardNo][5] | (((temp_hand >> 8) & 0x0F)) << 4);
		}
		else if(MotorCh == 2)
		{
			MotorPos[BoardNo][MotorCh] = (unsigned char)(temp_hand & 0xFF);
			MotorPos[BoardNo][6] = (unsigned char)(MotorPos[BoardNo][6] | (((temp_hand >> 8) & 0x0F)));
		}
		else if(MotorCh == 3)
		{
			MotorPos[BoardNo][MotorCh] = (unsigned char)(temp_hand & 0xFF);
			MotorPos[BoardNo][6] = (unsigned char)(MotorPos[BoardNo][6] | (((temp_hand >> 8) & 0x0F)) << 4);
		}
		else if(MotorCh == 4)
		{
			MotorPos[BoardNo][MotorCh] = (unsigned char)(temp_hand & 0xFF);
			MotorPos[BoardNo][7] = (unsigned char)((temp_hand >> 8) & 0x0F);
		}
		//RtWprintf(L"\npulse = %d, finglerpulse = %ld", temp_hand, FingerPulse);
	}
}

//UINT SignFunc(long value)
unsigned long SignFunc(long value)
{
	if (value < 0) return( (UINT)(((-value) & 0x007FFFFF) | (1<<23)) );
	else	return( (UINT)(value) );
}

unsigned long HandSignFunc(long value)
{
	if (value < 0) return( (UINT)(((-value) & 0x000007FF) | (1<<11)) );
	else	return( (UINT)(value) );
}

void RefPosCmd()
{
	char i=0;

	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		pSharedMemory->Reftheta[i] = RTX_fREF[i];
		RTxMoveAng(i,RTX_fREF[i]);
		RTX_fREFOLD[i] = RTX_fREF[i];
	}
}


void LegKine(BOOL Tocken) // for initialization
{
	char i;
	static BOOL oldTocken;

	if(Tocken==FALSE)		// Inverse Kinematics 우선 모드
	{
		RTX_fYaw[0] = YAWAngles[0];
		RTX_fYaw[1] = YAWAngles[1];
		
		/*
		CartPosInput(1); // --> PosIput[]의 값을 생성

		if(InvKine(PosInput[0],PosInput[1],PosInput[2],RTX_fYaw[0],
				   PosInput[3],PosInput[4],PosInput[5],RTX_fYaw[1])==1)
				   */
		if(InvKine(PosInput[0],PosInput[1],PosInput[2],pSharedMemory->theta[LHY],
			PosInput[3],PosInput[4],PosInput[5],pSharedMemory->theta[RHY])==1)
		{
			for(i=0;i<6;i++)	RTX_fXYZ[i]=PosInput[i];

			//	PosInput[] --> Inverse Kinematics 입력
			//	InvLegAngle[] --> Inverse Kinematics 출력

			if(pSharedMemory->HipYawVibFlag == FALSE)
			{
				RTX_COMPEN_Vib_Yaw[0] = (float)0.;
				RTX_COMPEN_Vib_Yaw[1] = (float)0.;
			}

			MotionAnkleAngPos[0] = (float)(-0.3*MotionHipAngPos[0]);
			MotionAnkleAngPos[1] = (float)(-0.3*MotionHipAngPos[1]);

			PROF_REF[RHY]=RTX_fREF[RHY]=InvLegAngle[6] + RTX_COMPEN_Vib_Yaw[RIGHT];		// R-Hip Yaw	
			PROF_REF[RHR]=RTX_fREF[RHR]=InvLegAngle[7] + RTX_COMPEN_Vib_Roll[RIGHT] + ZMP_DSP_Angle[1] + Del_Mov_RHip_r;//+ v_CTRL_HipRoll[1] + RTX_COMPEN_Vib_Roll[1] + RTX_SSP_ZMP_Y_Hip[1] + sysID_EXP_JNT[RHR];
													 // R-Hip Roll		
			PROF_REF[RHP]=RTX_fREF[RHP]=InvLegAngle[8] + v_AngPosEx[3] + ZMP_DSP_Angle[0] + v_CTRL_PosHip + MotionHipAngPos[1];
													// R-Hip Pitch
			PROF_REF[RKN]=RTX_fREF[RKN]=InvLegAngle[9] + v_AngPosEx[4];		// R-Knee Pitch		
			PROF_REF[RAP]=RTX_fREF[RAP]=InvLegAngle[10] + Land_OnOff_RAP_2 + RTX_CTRL_Ankle[2] + R_theta_compen_p + landRF + Equi_Adj_LRAP_Walking + DelMov_LRAP_OL + MotionAnkleAngPos[1]; 
														//+ v_AngPosEx[5] - v_AngPosEx[4] + v_CTRL_Ankle[1] + RTX_COMPEN_Ankle_Pitch[RIGHT][1] + RTX_COMPEN_Ankle_Pitch[RIGHT][2]
														// - ZMP_DSP_Angle[0];
													  //+ RTX_COMPEN_AnkleP[1][0]+RTX_COMPEN_AnkleP[1][2]+RTX_COMPEN_AnkleP[1][3]
													  //+ sysID_EXP_JNT[33]
													  //+ PBalanceAnkWalking + PitchKick[1] + PitchLand[1]
													   	// R-Ankle Pitch
			//v_AngPosSwt[RAP] = PROF_REF[RAP] - InvLegAngle[33];  --> must be checked InvLegAngle[33]

			PROF_REF[RAR]=RTX_fREF[RAR]=InvLegAngle[11] + DelMov_RAR  + RTX_CTRL_Ankle[3] + R_theta_compen_r + landRF_r + SSP_temp_3;// ;
														//+ RTX_COMPEN_Ankle_Roll[RIGHT][0] + RTX_COMPEN_Ankle_Roll[RIGHT][1] + RTX_COMPEN_Ankle_Roll[RIGHT][2]
														// - ZMP_DSP_Angle[1];
													  //+ pSharedMemory->DelAnkleRoll[1]
													  //+ RTX_COMPEN_AnkleR[1][0]+RTX_COMPEN_AnkleR[1][2]+RTX_COMPEN_AnkleR[1][3]
													  //+ RTX_COMPEN_Ankle_Roll[1] + RTX_SSP_ZMP_Y_Ankle[1]
													  //+ sysID_EXP_JNT[34];
													  //+ pSharedMemory->Ankle_Compen[1];		// Ankle Compensation by M_INF gyro
														//+ AnkZMPOffset[1] + AnkZMPOffset1[1];
															// R-Ankle Roll	
			//v_AngPosSwt[RAR] = PROF_REF[RAR] - InvLegAngle[34];

			PROF_REF[LHY]=RTX_fREF[LHY]=InvLegAngle[0] + RTX_COMPEN_Vib_Yaw[LEFT];		// L-Hip Yaw
			PROF_REF[LHR]=RTX_fREF[LHR]=InvLegAngle[1] + RTX_COMPEN_Vib_Roll[LEFT] + ZMP_DSP_Angle[1] + Del_Mov_LHip_r;//+ v_CTRL_HipRoll[0] + RTX_COMPEN_Vib_Roll[0] + RTX_SSP_ZMP_Y_Hip[0] + sysID_EXP_JNT[LHR];// 
														// L-Hip Roll
			PROF_REF[LHP]=RTX_fREF[LHP]=InvLegAngle[2] + v_AngPosEx[0] + ZMP_DSP_Angle[0] + v_CTRL_PosHip + MotionHipAngPos[0] + SSP_temp_4;
													// L-Hip Pitch
			PROF_REF[LKN]=RTX_fREF[LKN]=InvLegAngle[3] + v_AngPosEx[1];		// L-Knee Pitch		
			PROF_REF[LAP]=RTX_fREF[LAP]=InvLegAngle[4] + Land_OnOff_LAP_2 + RTX_CTRL_Ankle[0] + L_theta_compen_p + landLF + Equi_Adj_LRAP_Walking + DelMov_LRAP_OL + MotionAnkleAngPos[0]; 
														//+ v_AngPosEx[2] - v_AngPosEx[1] + v_CTRL_Ankle[0] + RTX_COMPEN_Ankle_Pitch[LEFT][1] + RTX_COMPEN_Ankle_Pitch[LEFT][2]
														// - ZMP_DSP_Angle[0];
												     //+ RTX_COMPEN_AnkleP[0][0]+RTX_COMPEN_AnkleP[0][2]+RTX_COMPEN_AnkleP[0][3]
													 // + sysID_EXP_JNT[39]
													 //+ RTX_COMPEN_Ankle_Pitch[0];
													 //+ PBalanceAnkWalking + PitchKick[0] + PitchLand[0]
													 // L-Ankle Pitch
			//v_AngPosSwt[LAP] = PROF_REF[LAP] - InvLegAngle[39];

			PROF_REF[LAR]=RTX_fREF[LAR]=InvLegAngle[5] + DelMov_LAR + RTX_CTRL_Ankle[1] + L_theta_compen_r + landLF_r + (float)(DSP_temp_1/117.);// ;
														//+ RTX_COMPEN_Ankle_Roll[LEFT][0] + RTX_COMPEN_Ankle_Roll[LEFT][1] + RTX_COMPEN_Ankle_Roll[LEFT][2]
														// - ZMP_DSP_Angle[1];
													 //+ pSharedMemory->DelAnkleRoll[0]
													 //+ RTX_COMPEN_AnkleR[0][0]+RTX_COMPEN_AnkleR[0][2]+RTX_COMPEN_AnkleR[0][3]
													 //+ sysID_EXP_JNT[40]
													 //+ RTX_COMPEN_Ankle_Roll[0] + RTX_SSP_ZMP_Y_Ankle[0];
													 //+ AnkZMPOffset[1] + AnkZMPOffset1[1]
															// L-Ankle Roll
			//v_AngPosSwt[LAR] = PROF_REF[LAR] - InvLegAngle[40];

			//	RTX_CTRL_Ankle[i] // 0: L-Ankle P, 1: L-Ankle R, 2: R-Ankle P, 3: R-Ankle R // Ankle Position Controller
			//	RTX_fANKLE[i]	  // 0: L-Ankle P, 1: L-Ankle R, 2: R-Ankle P, 3: R-Ankle R // Ankle Profile Modification
			//  RTX_R_AnkleP: Force balance of ankle pitch between left and right by tuning right ankle pitch angle
			//	RTX_Adj_AnkleP: Attitude balance of whole body by tuning left and right ankle pitch simultaneously

			InvFlag = TRUE;
		}
	}
	else if(Tocken==TRUE)	// Forward Kinematics 우선 모드
	{

		//	AngleInput[] --> Forward Kinematics의 입력
		//	LPx, LPy, LPz; // 왼발 위치	  Forward Kinematics 출력
		//	RPx, RPy, RPz; // 오른발 위치 Forward Kinematics 출력
		AngPosInput(1);	// --> AngleInput[]의 값을 생성 : 하체

		PROF_REF[RHY]=RTX_fREF[RHY]=AngleInput[RHY]=RTX_fYaw[1];		// R-Hip Yaw	
		PROF_REF[RHR]=RTX_fREF[RHR]=AngleInput[RHR];					// R-Hip Roll		
		PROF_REF[RHP]=RTX_fREF[RHP]=AngleInput[RHP];					// R-Hip Pitch
		PROF_REF[RKN]=RTX_fREF[RKN]=AngleInput[RKN];					// R-Knee Pitch		
		PROF_REF[RAP]=RTX_fREF[RAP]=AngleInput[RAP];					// R-Ankle Pitch		
		PROF_REF[RAR]=RTX_fREF[RAR]=AngleInput[RAR];					// R-Ankle Roll

		PROF_REF[LHY]=RTX_fREF[LHY]=AngleInput[LHY]=RTX_fYaw[0];		// L-Hip Yaw
		PROF_REF[LHR]=RTX_fREF[LHR]=AngleInput[LHR];					// L-Hip Roll		
		PROF_REF[LHP]=RTX_fREF[LHP]=AngleInput[LHP];					// L-Hip Pitch
		PROF_REF[LKN]=RTX_fREF[LKN]=AngleInput[LKN];					// L-Knee Pitch		
		PROF_REF[LAP]=RTX_fREF[LAP]=AngleInput[LAP];					// L-Ankle Pitch
		PROF_REF[LAR]=RTX_fREF[LAR]=AngleInput[LAR];					// L-Ankle Roll

		FrdKine(AngleInput[LHY],AngleInput[LHR],AngleInput[LHP],AngleInput[LKN],AngleInput[LAP],AngleInput[LAR],
				AngleInput[RHY],AngleInput[RHR],AngleInput[RHP],AngleInput[RKN],AngleInput[RAP],AngleInput[RAR]);
		
		/// 다시 Forward Kinematics로 돌아오기 위한 변수 저장용
		RTX_fXYZ[0]=LPx;
		RTX_fXYZ[1]=LPy;
		RTX_fXYZ[2]=LPz;

		RTX_fXYZ[3]=RPx;
		RTX_fXYZ[4]=RPy;
		RTX_fXYZ[5]=RPz;
	}
	oldTocken = Tocken;

	// velocity calculation about to value calculated inverse kinematics.
	//for(i=0;i<12;i++)
	//{
	//	InvLegVel[i] = (float)((InvLegAngle[i] - InvLegAngleOLD[i])/DELTA_T);
//		InvLegAngleOLD[i] = InvLegAngle[i];
//	}
}


void DataSave()
{
	/// 데이터 저장용
	if(pSharedMemory->PROFTime[11]<(SaveData_ROW - 2))		pSharedMemory->PROFTime[11]++;
	else pSharedMemory->PROFTime[11] = (SaveData_ROW - 2);
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][0]=(float)pSharedMemory->PROFTime[11];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][1]=(float)pSharedMemory->Reftheta[RHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->Reftheta[RHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)pSharedMemory->Reftheta[RHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)pSharedMemory->Reftheta[RKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][5]=(float)pSharedMemory->Reftheta[RAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][6]=(float)pSharedMemory->Reftheta[RAR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][7]=(float)pSharedMemory->Reftheta[LHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][8]=(float)pSharedMemory->Reftheta[LHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][9]=(float)pSharedMemory->Reftheta[LHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][10]=(float)pSharedMemory->Reftheta[LKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][11]=(float)pSharedMemory->Reftheta[LAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][12]=(float)pSharedMemory->Reftheta[LAR];

	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][13]=(float)v_AngPosEx[0];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][14]=(float)v_AngPosEx[3];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][13]=(float)RTX_N_RFOOT_Fz;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][14]=(float)RTX_NM_RFOOT_Mx;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][15]=(float)RTX_NM_RFOOT_My;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][16]=(float)RTX_N_LFOOT_Fz;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][17]=(float)RTX_NM_LFOOT_Mx;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][18]=(float)RTX_NM_LFOOT_My;

	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][19]=(float)RTX_Xzmp;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][20]=(float)RTX_Yzmp;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][21]=(float)PosInput[5];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][22]=(float)RTX_COMPEN_Ankle_Roll[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][23]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][24]=(float)v_CTRL_Ankle[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][25]=(float)v_CTRL_Ankle[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][26]=(float)RTX_DeltaMove[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][27]=(float)RTX_DeltaMove[1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][28]=(float)RTX_DeltaMove[2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][29]=(float)RTX_CTRL_Ankle[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][30]=(float)RTX_CTRL_Ankle[1];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)RTX_CTRL_Ankle[2];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)RTX_CTRL_Ankle[3];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)ABSHipPos[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)ABSHipPos[1];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][33]=(float)RTX_COMPEN_Ankle_Roll[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][34]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][35]=(float)RTX_COMPEN_Ankle_Pitch[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][36]=(float)RTX_COMPEN_Ankle_Pitch[RIGHT][1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][37]=(float)RTX_COMPEN_Vib_Roll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][38]=(float)RTX_COMPEN_Vib_Roll[RIGHT];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][39]=(float)RTX_CompenTheta_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][40]=(float)RTX_CompenTheta_P;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][41]=(float)AccR_deg;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][42]=(float)LPF_GYRO_Y1;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][43]=(float)RTX_M_Tilt_Theta_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)RTX_M_Tilt_Theta_P;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)HPF_M_ThetaR;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)HPF_M_ThetaP;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][47]=(float)LPF_AccR;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][48]=(float)LPF_AccP;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][49]=(float)LF_ACC_R_lp0;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][50]=(float)RTX_M_Tilt_Vel_R_LPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][51]=(float)RTX_M_Tilt_Vel_P_LPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][52]=(float)RTX_M_Tilt_Vel_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][53]=(float)RTX_M_Tilt_Vel_P;

	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][54]=(float)RTX_COMPEN_Vib_Yaw[RIGHT];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][55]=(float)RTX_COMPEN_Vib_Yaw[LEFT];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][56]=(float)AccP_deg;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][54]=(float)InvLegAngle[1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][55]=(float)InvLegAngle[7];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][56]=(float)ZMP_DSP_Angle[1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][57]=(float)LF_TILT_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][58]=(float)RF_TILT_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][59]=(float)LF_TILT_R_HPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][60]=(float)RF_TILT_R_HPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][61]=(float)LF_TILT_R_HPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][62]=(float)RF_TILT_R_HPF;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][63]=(float)LF_TILT_R_Vel;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][64]=(float)RF_TILT_R_Vel;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][65]=(float)RTX_COMPEN_Ankle_Roll[LEFT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][66]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][67]=(float)RTX_COMPEN_Ankle_Pitch[LEFT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][68]=(float)RTX_COMPEN_Ankle_Pitch[RIGHT][2];
	
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][59]=(float)stage;
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][69]=(float)PosInput[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][70]=(float)PosInput[1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][71]=(float)PosInput[2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][72]=(float)PosInput[3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][73]=(float)PosInput[4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][74]=(float)PosInput[5];


	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][75]=(float)TotalSumZMP[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][76]=(float)TotalSumZMP[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][77]=(float)TotalSumZMP[RIGHT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][78]=(float)TotalSumZMP[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][79]=(float)TotalSumRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][80]=(float)TotalSumRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][81]=(float)TotalSumPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][82]=(float)TotalSumPitch[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][83]=(float)TotalSumGyroRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][84]=(float)TotalSumGyroRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][85]=(float)TotalSumGyroPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][86]=(float)TotalSumGyroPitch[RIGHT];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][87]=(float)TotalAvgZMP[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][88]=(float)TotalAvgZMP[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][89]=(float)TotalAvgZMP[RIGHT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][90]=(float)TotalAvgZMP[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][91]=(float)TotalAvgRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][92]=(float)TotalAvgRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][93]=(float)TotalAvgPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][94]=(float)TotalAvgPitch[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][95]=(float)TotalAvgGyroRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][96]=(float)TotalAvgGyroRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][97]=(float)TotalAvgGyroPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][98]=(float)TotalAvgGyroPitch[RIGHT];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][99]=(float)SumZMP[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][100]=(float)SumZMP[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][101]=(float)SumZMP[RIGHT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][101]=(float)SumZMP[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][103]=(float)SumRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][104]=(float)SumRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][105]=(float)SumPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][106]=(float)SumPitch[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][107]=(float)SumGyroRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][108]=(float)SumGyroRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][109]=(float)SumGyroPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][110]=(float)SumGyroPitch[RIGHT];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][111]=(float)AvgZMP[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][112]=(float)AvgZMP[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][113]=(float)AvgZMP[RIGHT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][114]=(float)AvgZMP[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][115]=(float)AvgRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][116]=(float)AvgRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][117]=(float)AvgPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][118]=(float)AvgPitch[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][119]=(float)AvgGyroRoll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][120]=(float)AvgGyroRoll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][121]=(float)AvgGyroPitch[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][122]=(float)AvgGyroPitch[RIGHT];


	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][120]=(float)pSharedMemory->X_ShapeFactor;
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][121]=(float)pSharedMemory->X_ShapeFactor_mod;
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][122]=(float)pSharedMemory->X_mod;


	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][95]=(float)pSharedMemory->Delta_Foot_Position[1];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][96]=(float)pSharedMemory->Delta_Foot_Position[4];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][123]=(float)GyroR_deg;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][124]=(float)GyroP_deg;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][125]=(float)GyroY_deg;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][126]=(float)RTX_HeightDiff[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][127]=(float)RTX_HeightDiff[1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][128]=(float)pSharedMemory->X_ShapeFactor;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][129]=(float)pSharedMemory->Y_ShapeFactor;

	/*
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][88]=(float)DSP_ZMPRef[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][89]=(float)DSP_ZMPRef[1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][90]=(float)ZMP_DSP_Angle[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][91]=(float)ZMP_DSP_Angle[1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][92]=(float)Init_DSP_ZMP[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][93]=(float)Init_DSP_ZMP[1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][94]=(float)pSharedMemory->ZMP_DSP_CTRL_Flag;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][95]=(float)pSharedMemory->PROFTime[22];
*/

	
	/*
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][35]=(float)InvLegAngle[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][36]=(float)InvLegAngle[1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][37]=(float)InvLegAngle[2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][38]=(float)InvLegAngle[3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][39]=(float)InvLegAngle[4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][40]=(float)InvLegAngle[5];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][41]=(float)InvLegAngle[6];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][42]=(float)InvLegAngle[7];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][43]=(float)InvLegAngle[8];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)InvLegAngle[9];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)InvLegAngle[10];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)InvLegAngle[11];
	*/
}

void DataSave1()
{
	/// 데이터 저장용
	if(pSharedMemory->PROFTime[11]<(SaveData_ROW - 2))		pSharedMemory->PROFTime[11]++;
	else pSharedMemory->PROFTime[11] = (SaveData_ROW - 2);
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][0]=(float)pSharedMemory->PROFTime[11];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][1]=(float)pSharedMemory->Reftheta[RHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->Reftheta[RHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)pSharedMemory->Reftheta[RHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)pSharedMemory->Reftheta[RKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][5]=(float)pSharedMemory->Reftheta[RAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][6]=(float)pSharedMemory->Reftheta[RAR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][7]=(float)pSharedMemory->Reftheta[LHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][8]=(float)pSharedMemory->Reftheta[LHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][9]=(float)pSharedMemory->Reftheta[LHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][10]=(float)pSharedMemory->Reftheta[LKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][11]=(float)pSharedMemory->Reftheta[LAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][12]=(float)pSharedMemory->Reftheta[LAR];
	
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][13]=(float)tp_cnt[0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][14]=(float)tp_cnt[1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][15]=(float)tp_cnt[2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][16]=(float)tp_cnt[3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][17]=(float)tp_cnt[4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][18]=(float)tp_cnt[5];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][19]=(float)int_time1;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][20]=(float)int_time2;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][21]=(float)int_time3; // calcluation time in interrupt
	
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][22]=(float)RTX_NM_LFOOT_Mx;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][23]=(float)RTX_NM_LFOOT_My;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][24]=(float)RTX_N_LFOOT_Fz;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][25]=(float)RTX_NM_RFOOT_Mx;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][26]=(float)RTX_NM_RFOOT_My;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][27]=(float)RTX_N_RFOOT_Fz;
	
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][28]=(float)RF_TILT_R_Vel;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][29]=(float)LF_TILT_R_Vel;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][30]=(float)LPF_GYRO_Y1;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)PosInput[3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)PosInput[4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][33]=(float)PosInput[5];
	


	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][34]=(float)RTX_CompenTheta_R;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][35]=(float)RTX_CompenTheta_P;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][36]=(float)RTX_COMPEN_Ankle_Roll[LEFT][0];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][37]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][0];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][38]=(float)RTX_COMPEN_Ankle_Roll[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][39]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][40]=(float)RTX_COMPEN_Ankle_Pitch[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][41]=(float)RTX_COMPEN_Ankle_Pitch[RIGHT][1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][42]=(float)RTX_COMPEN_Ankle_Roll[LEFT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][43]=(float)RTX_COMPEN_Ankle_Roll[RIGHT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)RTX_COMPEN_Ankle_Pitch[LEFT][2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)RTX_COMPEN_Ankle_Pitch[RIGHT][2];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)RTX_COMPEN_Vib_Roll[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][47]=(float)RTX_COMPEN_Vib_Roll[RIGHT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][48]=(float)RTX_COMPEN_Vib_Yaw[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][49]=(float)RTX_COMPEN_Vib_Yaw[RIGHT];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][50]=(float)v_CTRL_Ankle[LEFT];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][51]=(float)v_CTRL_Ankle[RIGHT];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][52]=(float)pSharedMemory->Pos_Pitch_Ref;

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][53]=(float)RTX_oldCOMPEN_Ankle_Roll[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][54]=(float)RTX_oldCOMPEN_Ankle_Roll[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][55]=(float)RTX_oldCOMPEN_Ankle_Pitch[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][56]=(float)RTX_oldCOMPEN_Ankle_Pitch[RIGHT][1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][57]=(float)RTX_delCOMPEN_Ankle_Roll[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][58]=(float)RTX_delCOMPEN_Ankle_Roll[RIGHT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][59]=(float)RTX_delCOMPEN_Ankle_Pitch[LEFT][1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][60]=(float)RTX_delCOMPEN_Ankle_Pitch[RIGHT][1];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][62]=(float)pSharedMemory->Reftheta[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][63]=(float)pSharedMemory->Reftheta[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][64]=(float)pSharedMemory->Reftheta[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][65]=(float)pSharedMemory->Reftheta[REB];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][66]=(float)pSharedMemory->Reftheta[LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][67]=(float)pSharedMemory->Reftheta[LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][68]=(float)pSharedMemory->Reftheta[LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][69]=(float)pSharedMemory->Reftheta[LEB];

}

void DataSave2()
{
	/// 데이터 저장용
	if(pSharedMemory->PROFTime[11]<(SaveData_ROW - 2))		pSharedMemory->PROFTime[11]++;
	else pSharedMemory->PROFTime[11] = (SaveData_ROW - 2);
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][0]=(float)pSharedMemory->PROFTime[11];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][1]=(float)pSharedMemory->Reftheta[RHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->Reftheta[RHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)pSharedMemory->Reftheta[RHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)pSharedMemory->Reftheta[RKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][5]=(float)pSharedMemory->Reftheta[RAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][6]=(float)pSharedMemory->Reftheta[RAR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][7]=(float)pSharedMemory->Reftheta[LHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][8]=(float)pSharedMemory->Reftheta[LHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][9]=(float)pSharedMemory->Reftheta[LHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][10]=(float)pSharedMemory->Reftheta[LKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][11]=(float)pSharedMemory->Reftheta[LAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][12]=(float)pSharedMemory->Reftheta[LAR];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][13]=(float)pSharedMemory->Reftheta[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][14]=(float)pSharedMemory->Reftheta[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][15]=(float)pSharedMemory->Reftheta[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][16]=(float)pSharedMemory->Reftheta[REB];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][17]=(float)pSharedMemory->Reftheta[LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][18]=(float)pSharedMemory->Reftheta[LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][19]=(float)pSharedMemory->Reftheta[LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][20]=(float)pSharedMemory->Reftheta[LEB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][21]=(float)pSharedMemory->Reftheta[RWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][22]=(float)pSharedMemory->Reftheta[RW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][23]=(float)pSharedMemory->Reftheta[RW2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][24]=(float)pSharedMemory->Reftheta[LWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][25]=(float)pSharedMemory->Reftheta[LW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][26]=(float)pSharedMemory->Reftheta[LW2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][27]=(float)pSharedMemory->Reftheta[NKY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][28]=(float)pSharedMemory->Reftheta[NK1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][29]=(float)pSharedMemory->Reftheta[NK2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][30]=(float)pSharedMemory->Reftheta[WST];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][33]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][34]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][REB];


	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][35]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][36]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][37]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][38]=(float)pSharedMemory->UpBody_MTN_CAP_Data[pSharedMemory->PROFTime[11]][LEB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][39]=(float)Extra_uppermovement[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][40]=(float)Extra_uppermovement[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][41]=(float)Extra_uppermovement[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][42]=(float)Extra_uppermovement[REB];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][43]=(float)Extra_uppermovement[RWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)Extra_uppermovement[RWY];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)UpperMovement[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)UpperMovement[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][47]=(float)UpperMovement[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][48]=(float)UpperMovement[REB];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][49]=(float)UpperMovement[LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][50]=(float)UpperMovement[LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][51]=(float)UpperMovement[LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][52]=(float)UpperMovement[LEB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][53]=(float)UpperMovement[WST];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][54]=(float)UpperMovement[RWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][55]=(float)UpperMovement[RW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][56]=(float)UpperMovement[RW2];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][57]=(float)UpperMovement[LWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][58]=(float)UpperMovement[LW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][59]=(float)UpperMovement[LW2];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][60]=(float)UpperMovement[NKY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][61]=(float)UpperMovement[NK1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][62]=(float)UpperMovement[NK2];


	
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)Old_Extra_uppermovement[RSP];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)Old_Extra_uppermovement[RSR];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)Old_Extra_uppermovement[RSY];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][47]=(float)Old_Extra_uppermovement[REB];
	//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][48]=(float)Old_Extra_uppermovement[RWY];
	
}

void DataSave3()
{
	/// 데이터 저장용
	if(pSharedMemory->PROFTime[11]<(SaveData_ROW - 2))		pSharedMemory->PROFTime[11]++;
	else pSharedMemory->PROFTime[11] = (SaveData_ROW - 2);
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][0]=(float)pSharedMemory->PROFTime[11];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][1]=(float)pSharedMemory->Reftheta[RHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->Reftheta[RHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)pSharedMemory->Reftheta[RHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)pSharedMemory->Reftheta[RKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][5]=(float)pSharedMemory->Reftheta[RAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][6]=(float)pSharedMemory->Reftheta[RAR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][7]=(float)pSharedMemory->Reftheta[LHY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][8]=(float)pSharedMemory->Reftheta[LHR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][9]=(float)pSharedMemory->Reftheta[LHP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][10]=(float)pSharedMemory->Reftheta[LKN];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][11]=(float)pSharedMemory->Reftheta[LAP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][12]=(float)pSharedMemory->Reftheta[LAR];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][13]=(float)pSharedMemory->Reftheta[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][14]=(float)pSharedMemory->Reftheta[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][15]=(float)pSharedMemory->Reftheta[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][16]=(float)pSharedMemory->Reftheta[REB];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][17]=(float)pSharedMemory->Reftheta[LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][18]=(float)pSharedMemory->Reftheta[LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][19]=(float)pSharedMemory->Reftheta[LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][20]=(float)pSharedMemory->Reftheta[LEB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][21]=(float)pSharedMemory->Reftheta[RWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][22]=(float)pSharedMemory->Reftheta[RW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][23]=(float)pSharedMemory->Reftheta[RW2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][24]=(float)pSharedMemory->Reftheta[LWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][25]=(float)pSharedMemory->Reftheta[LW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][26]=(float)pSharedMemory->Reftheta[LW2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][27]=(float)pSharedMemory->Reftheta[NKY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][28]=(float)pSharedMemory->Reftheta[NK1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][29]=(float)pSharedMemory->Reftheta[NK2];
	
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][30]=(float)UpperMovement[RSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][31]=(float)UpperMovement[RSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][32]=(float)UpperMovement[RSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][33]=(float)UpperMovement[REB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][34]=(float)UpperMovement[LSP];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][35]=(float)UpperMovement[LSR];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][36]=(float)UpperMovement[LSY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][37]=(float)UpperMovement[LEB];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][38]=(float)UpperMovement[RWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][39]=(float)UpperMovement[RW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][40]=(float)UpperMovement[RW2];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][41]=(float)UpperMovement[LWY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][42]=(float)UpperMovement[LW1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][43]=(float)UpperMovement[LW2];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][44]=(float)UpperMovement[NKY];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][45]=(float)UpperMovement[NK1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][46]=(float)UpperMovement[NK2];
	//Finger data starts here
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][47]=(float)pSharedMemory->Reftheta[RF1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][48]=(float)pSharedMemory->Reftheta[RF2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][49]=(float)pSharedMemory->Reftheta[RF3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][50]=(float)pSharedMemory->Reftheta[RF4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][51]=(float)pSharedMemory->Reftheta[RF5];

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][52]=(float)pSharedMemory->Reftheta[LF1];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][53]=(float)pSharedMemory->Reftheta[LF2];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][54]=(float)pSharedMemory->Reftheta[LF3];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][55]=(float)pSharedMemory->Reftheta[LF4];
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][56]=(float)pSharedMemory->Reftheta[LF5];

	
	
}




void ControlVarReset()
{
	ZLandingCTRLFlag = FALSE;

	UpRatio = pSharedMemory->UPRATIO;

	RTX_HeightDiff[0] = 0.;
	RTX_HeightDiff[1] = 0.;

	RStopZ = FALSE;
	LStopZ = FALSE;
			
	v_CartPos5 = v_CartPos[5]; v_oldCartPos5 = v_CartPos[5]; v_delCartPos5 = 0.;
	v_CartPos2 = v_CartPos[2]; v_oldCartPos2 = v_CartPos[2]; v_delCartPos2 = 0.;

	RTX_COMPEN_Ankle_Roll[LEFT][2] = 0.;
	RTX_COMPEN_Ankle_Roll[RIGHT][2] = 0.;
	RTX_COMPEN_Ankle_Pitch[LEFT][2] = 0.;
	RTX_COMPEN_Ankle_Pitch[RIGHT][2] = 0.;
			
	RTX_oldCOMPEN_Ankle_Roll[LEFT][2] = 0.;
	RTX_oldCOMPEN_Ankle_Roll[RIGHT][2] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[LEFT][2] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[RIGHT][2] = 0.;
			
	RTX_delCOMPEN_Ankle_Roll[LEFT][2] = 0.;
	RTX_delCOMPEN_Ankle_Roll[RIGHT][2] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[LEFT][2] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[RIGHT][2] = 0.;
	
	/*
	RTX_COMPEN_HIPR[0][1] = 0.;
	RTX_COMPEN_HIPR[1][1] = 0.;
	RTX_oldCOMPEN_HIPR[0][1] = 0.;
	RTX_oldCOMPEN_HIPR[1][1] = 0.;
	RTX_delCOMPEN_HIPR[0][1] = 0.;
	RTX_delCOMPEN_HIPR[1][1] = 0.;

	RTX_COMPEN_HIPY[0][1] = 0.;
	RTX_COMPEN_HIPY[1][1] = 0.;
	RTX_oldCOMPEN_HIPY[0][1] = 0.;
	RTX_oldCOMPEN_HIPY[1][1] = 0.;
	RTX_delCOMPEN_HIPY[0][1] = 0.;
	RTX_delCOMPEN_HIPY[1][1] = 0.;
	*/
	
	//FltGyroY1 = 0.;
	//RTX_Gyro_CutOffY = 0.;
	//FltGyroY0 = 0.;
	//RTX_Tilt_theta_Y = 0.;

	TIMERecover[0]=0;
	TIMERecover[1]=0;
	TIMERecover[2]=0;
	TIMERecover[3]=0;

	//RTX_DeltaMove1[0] = 0.;//RTX_DeltaMove[0];
	//RTX_DeltaMove1[1] = 0.;//RTX_DeltaMove[1];
	//RTX_DeltaMove1[2] = 0.;//RTX_DeltaMove[2];
			
	RTX_DeltaMove2[0] = 0.;//RTX_DeltaMove[0];
	RTX_DeltaMove2[1] = 0.;//RTX_DeltaMove[1];
	RTX_DeltaMove2[2] = 0.;//RTX_DeltaMove[2];

	//RTX_DeltaMove3[0] = 0.;//RTX_DeltaMove[0];
	//RTX_DeltaMove3[1] = 0.;//RTX_DeltaMove[1];
	//RTX_DeltaMove3[2] = 0.;//RTX_DeltaMove[2];
			
	//RTX_DeltaMove3TMP[0] = 0.;
	//RTX_DeltaMove3TMP[1] = 0.;
	//RTX_DeltaMove3TMP[2] = 0.;

	//RTX_DeltaMove3lp[0] = 0.;//RTX_DeltaMove[0];
	//RTX_DeltaMove3lp[1] = 0.;//RTX_DeltaMove[1];
	//RTX_DeltaMove3lp[2] = 0.;//RTX_DeltaMove[2];

	//CTRL_angle_stiff_ds3(0,0,0,0);
	//CTRL_angle_stiff_fwL(0,0,0,0);
			
	//CTRL_angle_stiff_fwR(0,0,0,0);
	//CTRL_angle_stiff_ds4(0,0,0,0);
			
	CTRL_RF_land_damp_roll(0,0,0,0);
	CTRL_LF_land_damp_roll(0,0,0,0);
	CTRL_land_damp_fwdR(0,0,0,0);
	CTRL_land_damp_fwdL(0,0,0,0);

	//CTRL_INCL_Ank_Pitch_Walking(0,0);
		
	//CTRL_dsp_compen_p_1(0,0);
	//CTRL_dsp_compen_p2_1(0,0);

	CTRL_new_compenfwd(0,0);
	CTRL_new_compen(0,0);

	//GYRO_Reset(2);
	
	//pSharedMemory->GYRO_RESET = TRUE;

	//CTRL_SSP_ZMP_CON_Y(0,0,0);
	//CTRL_SSP_ZMP_CON_LY(0,0,0);
	//CTRL_SSP_ZMP_CON_RY(0,0,0);

	//RTX_COMPEN_HIPR[0][2] = 0.;
	//RTX_COMPEN_HIPR[1][2] = 0.;

	//RTX_oldCOMPEN_HIPR[0][2] = 0.;
	//RTX_oldCOMPEN_HIPR[1][2] = 0.;

	//RTX_delCOMPEN_HIPR[0][2] = 0.;
	//RTX_delCOMPEN_HIPR[1][2] = 0.;

	OP_DistLftRht[1] = 0;
	OP_DistFwdBwd = pSharedMemory->DistFwdBwd;
	OP_AngTurn = pSharedMemory->AngTurn;

	pSharedMemory->SET_Flag = FALSE;
}


float C1_cosRecover(float oldData, float diffData, unsigned int Time, unsigned int start, unsigned int during)
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

void WalkAnkVarReset()
{
	RTX_COMPEN_Ankle_Roll[0][2] = 0.;
	RTX_COMPEN_Ankle_Roll[1][2] = 0.;
	RTX_COMPEN_Ankle_Pitch[0][2] = 0.;
	RTX_COMPEN_Ankle_Pitch[1][2] = 0.;
	
	RTX_oldCOMPEN_Ankle_Roll[0][2] = 0.;
	RTX_oldCOMPEN_Ankle_Roll[1][2] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[0][2] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[1][2] = 0.;
	
	RTX_delCOMPEN_Ankle_Roll[0][2] = 0.;
	RTX_delCOMPEN_Ankle_Roll[1][2] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[0][2] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[1][2] = 0.;
	
	//RTX_COMPEN_Ankle_Roll[0][3] = 0.;
	//RTX_COMPEN_Ankle_Roll[1][3] = 0.;
	//RTX_COMPEN_Ankle_Pitch[0][3] = 0.;
	//RTX_COMPEN_Ankle_Pitch[1][3] = 0.;
	
	/*
	RTX_oldCOMPEN_Ankle_Roll[0][3] = 0.;
	RTX_oldCOMPEN_Ankle_Roll[1][3] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[0][3] = 0.;
	RTX_oldCOMPEN_Ankle_Pitch[1][3] = 0.;
	
	RTX_delCOMPEN_Ankle_Roll[0][3] = 0.;
	RTX_delCOMPEN_Ankle_Roll[1][3] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[0][3] = 0.;
	RTX_delCOMPEN_Ankle_Pitch[1][3] = 0.;
	
	RTX_COMPEN_HIPR[0][1] = 0.;
	RTX_oldCOMPEN_HIPR[0][1] = 0.;
	RTX_delCOMPEN_HIPR[0][1] = 0.;
	
	RTX_COMPEN_HIPR[1][1] = 0.;
	RTX_oldCOMPEN_HIPR[1][1] = 0.;
	RTX_delCOMPEN_HIPR[1][1] = 0.;
	*/

	TIMERecover[0]=0;
	TIMERecover[1]=0;
	TIMERecover[2]=0;
	TIMERecover[3]=0;
}

void InitCTRL()
{
	//RTX_DeltaMove[0] = (float)(1.0*CTRL_new_compenfwd_kirk(Xzmp_lp, Init_Xzmp, 1)); //PI: X-Position
	//RTX_DeltaMove[1] = (float)(CTRL_new_compen_kirk(Yzmp_lp, pSharedMemory->Zmp_Zero_Offset, 1)); //PI: Y-Position
	//RTX_DeltaMove[2] = (float)(CTRL_INCL_Hip_Roll((float)(10.*0.043449*RTX_CompenTheta_R),1)); // Ankle Z-Position Balancing
	
	DeltaMov_x_ini = (float)(1.0*CTRL_new_compenfwd_kirk(Xzmp_lp, Init_Xzmp, 1)); //PI: X-Position
	DeltaMov_y_ini = (float)(CTRL_new_compen_kirk(Yzmp_lp, pSharedMemory->Zmp_Zero_Offset, 1)); //PI: Y-Position
	pSharedMemory->Equi_Adj_Rfoot_Z = (float)(CTRL_INCL_Hip_Roll((float)(LPF_AccR),1)); // Ankle Z-Position Balancing
	pSharedMemory->Equi_Adj_Lfoot_Z = -pSharedMemory->Equi_Adj_Rfoot_Z;
	
	pSharedMemory->BC_y = DeltaMov_y_ini;// + DeltaMov_y + pSharedMemory->BC_equi_comp_y + DelMov_BC_y_TOC + BC_Y_Amp_Compen - DSP_temp_1 + SSP_temp_1 + BC_y_ZMP_CON + Gesture_Step_BC_y + Start_Kick_BC_Y_Comp;// BC_Over_Swing_Comp //  Start_Kick_BC_Y_Comp ;// BC_Y_Amp_Compen;
	pSharedMemory->BC_x = DeltaMov_x_ini;// + DeltaMov_x + SSP_temp_5 + BC_x_ZMP_CON + Gesture_Step_BC_x ;//+ temp_hip_x;
	pSharedMemory->BC_z = -WLK_RDY_DOWN;// + 0.18*Gesture_Pelvis_1 + Gesture_Pelvis_2;
		
	pSharedMemory->R_px = - pSharedMemory->BC_x;// + Gesture_Step_RF_x;//+ Del_Mov_RF_x_Ang_Acc;
	pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y);// + pSharedMemory->R_py_Compen - DSP_temp_4 + Gesture_Step_RF_y;//+ Del_Mov_RF_y_Ang_Acc;
	pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + pSharedMemory->Equi_Adj_Rfoot_Z;
	
	pSharedMemory->L_px = - pSharedMemory->BC_x;// + Gesture_Step_LF_x;//+ Del_Mov_LF_x_Ang_Acc;
	pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y);// + pSharedMemory->L_py_Compen + DSP_temp_3 + Gesture_Step_LF_y;//+ Del_Mov_LF_y_Ang_Acc;
	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + pSharedMemory->Equi_Adj_Lfoot_Z;
		
	PosInput[0] = pSharedMemory->L_px;
	PosInput[1] = pSharedMemory->L_py;
	PosInput[2] = pSharedMemory->L_pz;
	PosInput[3] = pSharedMemory->R_px;
	PosInput[4] = pSharedMemory->R_py;
	PosInput[5] = pSharedMemory->R_pz;
	
	pSharedMemory->BC_y = 0.;
	pSharedMemory->BC_x = 0.;
	pSharedMemory->BC_z = -WLK_RDY_DOWN;
	
	RTX_R_AnkleP = (float)((-1.0)*CTRL_autotuneankle(RTX_NM_RFOOT_My-RTX_NM_LFOOT_My,1)); // Right Ankle Pitch Balance
	RTX_Adj_AnkleP = (float)(-CTRL_INCL_Ank_Pitch((float)(LPF_AccP),1)); // Body Balance by left and right ankle joint angle
	
	
	RTX_CTRL_Ankle[0] = RTX_Adj_AnkleP;
	RTX_CTRL_Ankle[2] = RTX_R_AnkleP + RTX_Adj_AnkleP;
	
	RTX_CTRL_Ankle[1] = (float)(0.5*CTRL_Torq_Zero_LAR(RTX_NM_LFOOT_Mx, 0., 1));
	RTX_CTRL_Ankle[3] = (float)(0.5*CTRL_Torq_Zero_RAR(RTX_NM_RFOOT_Mx, 0., 1));
	/*
	if(pSharedMemory->FootAccReset == TRUE)
	{
		InertialOffset();
		FootAccReset();
	}*/
}


void InitCTRLVar()
{
	for(unsigned char i=0;i<3;i++)
	{
		RTX_BodyCenter[i]	=	0.;  // 0: X-Axis, 1: Y-Axis, 2: Z-Axis
		RTX_DeltaMove[i]	=	0.;  // 0: X-Axis, 1: Y-Axis, 2: Z-Axis
	}
	/*
	for(i=0;i<2;i++)
	{
		RTX_RefZMP[i]  = 0;
		RTX_ErrZMP[i]  = 0;
		RTX_InitZMP[i] = 0;				
	}
	*/
	for(i=0;i<4;i++)
	{
		RTX_CTRL_Ankle[i]	= 0.; // 0: L-Ankle P, 1: L-Ankle R, 2: R-Ankle P, 3: R-Ankle R
	}
	CTRL_Torq_Zero_RAR(0,0,0);
	CTRL_Torq_Zero_LAR(0,0,0);
	
	CTRL_INCL_Hip_Roll(0,0);
	CTRL_new_compen(0,0);
	CTRL_new_compenfwd(0,0);
	
	CTRL_new_compenfwd(0,0);
	CTRL_INCL_Ank_Pitch(0,0);
	
	CTRL_new_compenfwd_kirk(0,0,0);
	CTRL_new_compen_kirk(0,0,0);
}

void InitVarSet(unsigned char mode)
{
	RStopZ = FALSE;
	LStopZ = FALSE;
	
	if(mode == 0)
	{
		INItemp[0] = v_CartPosCont00[0];
		INItemp[1] = v_CartPosCont00[1];
		INItemp[2] = v_CartPosCont00[2];
		INItemp[3] = v_CartPosCont00[3];
		INItemp[4] = v_CartPosCont00[4];
		INItemp[5] = v_CartPosCont00[5];
		
		INItemp[6] = RTX_CTRL_Ankle[0]; // Ankle Pitch Control
		INItemp[7] = RTX_CTRL_Ankle[2]; // Ankle Pitch Control
		
		INItemp[8] = RTX_CTRL_Ankle[1]; // Ankle Roll Control
		INItemp[9] = RTX_CTRL_Ankle[3]; // Ankle Roll Control
		
		//pSharedMemory->InitAnkleRoll[0] = InvLegAngle[5];
		//pSharedMemory->InitAnkleRoll[1] = InvLegAngle[11];
		
		//RTX_fREF[34]=pSharedMemory->InitAnkleRoll[1] + pSharedMemory->DelAnkleRoll[1];
		//RTX_fREF[40]=pSharedMemory->InitAnkleRoll[0] + pSharedMemory->DelAnkleRoll[0];
	}
	else if(mode == 1)
	{
		v_CartPosCont00[0] = INItemp[0];
		v_CartPosCont00[1] = INItemp[1];
		v_CartPosCont00[2] = INItemp[2];
		v_CartPosCont00[3] = INItemp[3];
		v_CartPosCont00[4] = INItemp[4];
		v_CartPosCont00[5] = INItemp[5];
		
		RTX_CTRL_Ankle[0] = INItemp[6]; // Ankle Pitch Control
		RTX_CTRL_Ankle[2] = INItemp[7]; // Ankle Pitch Control
		
		RTX_CTRL_Ankle[1] = INItemp[8]; // Ankle Roll Control
		RTX_CTRL_Ankle[3] = INItemp[9]; // Ankle Roll Control
		
		//pSharedMemory->InitAnkleRoll[0] = InvLegAngle[5];
		//pSharedMemory->InitAnkleRoll[1] = InvLegAngle[11];
		
		//RTX_fREF[34]=pSharedMemory->InitAnkleRoll[1] + pSharedMemory->DelAnkleRoll[1];
		//RTX_fREF[40]=pSharedMemory->InitAnkleRoll[0] + pSharedMemory->DelAnkleRoll[0];
		
	}
	else if(mode == 2)
	{
		pSharedMemory->Read_TILT_Flag = TRUE;
		pSharedMemory->ZMP_Zero_Set_Flag = TRUE;
	}
}

void GYRO_Reset(char RotAXIS)
{
	if(RotAXIS==0) //Roll
	{
	}
	else if(RotAXIS==1) //Pitch
	{
	}
	else if(RotAXIS==2) //Yaw
	{
		//FltGyroY1 = 0.;
		//RTX_Gyro_CutOffY = 0.;
		//FltGyroY0 = 0.;
		//RTX_Tilt_theta_Y = 0.;
	}
}

void KeepGoing()
{
	if((FiveKG_R_Flag == 0)&&(stretchedFlag == 1)&&(pSharedMemory->KeepGoing == FALSE))
	{
		if(pSharedMemory->GoStop_Flag == TRUE)
		{
			if(stage == 0)		pSharedMemory->PROFTime[5]--;
			else if(stage == 2)	pSharedMemory->PROFTime[7]--;
		}
		else if(pSharedMemory->GoStop_Flag == FALSE)
		{
			if(stage == 0)		pSharedMemory->PROFTime[8]--;
			else if(stage == 2) pSharedMemory->PROFTime[10]--;
		}
	}
	else if((FiveKG_L_Flag == 0)&&(stretchedFlag == 1)&&(pSharedMemory->KeepGoing == FALSE))
	{
		if(pSharedMemory->GoStop_Flag == TRUE)
		{
			if(stage == 1)		pSharedMemory->PROFTime[6]--;
		}
		else if(pSharedMemory->GoStop_Flag == FALSE)
		{
			if(stage == 1)		pSharedMemory->PROFTime[9]--;
		}
	}
}

void SSP_OL_L_Pose()
{
	static unsigned int localtimer = 0;
	static unsigned int localtimer0 = 0;
	
	PRF_L_SSP_Static(170, 40, pSharedMemory->PROFTime[12], 0, 80*TS);
	FTN_half_1_cos((float)-5.5,pSharedMemory->PROFTime[12],0,80*TS,0,0,&RTX_COMPEN_Ankle_Roll[RIGHT][0]);
	
	if(pSharedMemory->PROFTime[12]< (80*TS)+1)	pSharedMemory->PROFTime[12]++;	

	AnkleRollCompenBackUP();

	if((pSharedMemory->SSPCTRLOn == TRUE)&&(pSharedMemory->SSPCTRLOff == TRUE))	  // Initialize
	{
		/*
		CTRL_angle_stiff_ds4(0,0,0,0);
		CTRL_angle_stiff_fwR(0,0,0,0);
		CTRL_LF_Roll_Vib_Reduction(0, 0);
		CTRL_RF_Yaw_Vib_Reduction(0, 0);
		GYRO_Reset(2);
		*/
	}
	else if((pSharedMemory->SSPCTRLOn == FALSE)&&(pSharedMemory->SSPCTRLOff == TRUE)) // Control Off
	{
		// do nothing
		
	}
	else if((pSharedMemory->SSPCTRLOn == TRUE)&&(pSharedMemory->SSPCTRLOff == FALSE)) // Control On
	{
		// Ankle Posture Control
		RTX_COMPEN_Ankle_Roll[RIGHT][1] = (float)(-1.0 * Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0 ));
		RTX_COMPEN_Ankle_Pitch[RIGHT][1] = (float)(-1.0 * Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0));
		

		// Vibration Reduction Control
		
	}

	if(pSharedMemory->PushUpFlag == TRUE)
	{
		RZ = (float)(pSharedMemory->PushUpAMP*(1-cos(2.*PI*pSharedMemory->PROFTime[18]/(100.*TS)*pSharedMemory->PushUpHz))/2);
		if(pSharedMemory->PROFTime[18]/(100.*TS)*pSharedMemory->PushUpHz >= 1)
		{
			pSharedMemory->PROFTime[18] = 0;
		}
		else
		{
			pSharedMemory->PROFTime[18]++;
		}
	}
	else if(pSharedMemory->PushUpFlag == FALSE)
	{
		if(pSharedMemory->PROFTime[18]/(100.*TS)*pSharedMemory->PushUpHz >= 1)
		{
			pSharedMemory->PROFTime[18] = 0;
			pSharedMemory->PushUpHz = 0;
			pSharedMemory->PushUpAMP = 0;
		}
		else
		{
			RZ = (float)(pSharedMemory->PushUpAMP*(1.-cos(2.*PI*pSharedMemory->PROFTime[18]/(100.*TS)*pSharedMemory->PushUpHz))/2);
			pSharedMemory->PROFTime[18]++;
		}
	}
	

	BCDataCont0();
	LegKine(0);
	RefPosCmd();
}

void SSP_OL_R_Pose()
{
	static unsigned int localtimer = 0;
	static unsigned int localtimer0 = 0;
	
	PRF_R_SSP_Static(150, 40, pSharedMemory->PROFTime[12], 0, 80*TS); // 216/2=108
	FTN_half_1_cos((float)2.9,pSharedMemory->PROFTime[12],0,80*TS,0,0,&RTX_COMPEN_Ankle_Roll[LEFT][0]);
	
	if(pSharedMemory->PROFTime[12]< (80*TS)+1)	pSharedMemory->PROFTime[12]++;	

	AnkleRollCompenBackUP();

	if((pSharedMemory->SSPCTRLOn == TRUE)&&(pSharedMemory->SSPCTRLOff == TRUE))	  // Initialize
	{
		/*
		CTRL_angle_stiff_ds3(0,0,0,0);
		CTRL_angle_stiff_fwL(0,0,0,0);
		
		CTRL_RF_Roll_Vib_Reduction(0, 0);
		CTRL_LF_Yaw_Vib_Reduction(0, 0);
		GYRO_Reset(2);
		*/
	}
	else if((pSharedMemory->SSPCTRLOn == FALSE)&&(pSharedMemory->SSPCTRLOff == TRUE)) // Control Off
	{
		// do nothing
	}
	else if((pSharedMemory->SSPCTRLOn == TRUE)&&(pSharedMemory->SSPCTRLOff == FALSE)) // Control On
	{
		// Ankle Posture Control
		RTX_COMPEN_Ankle_Roll[LEFT][1] = (float)(-1.0 * Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0));
		RTX_COMPEN_Ankle_Pitch[LEFT][1] = (float)(-1.0 * Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0));
		
		//RTX_COMPEN_Vib_Roll[1] = (float)(-0.3*Right_Roll_Vib_Reduction(RTX_Tilt_RF_Roll_Vel, 1));	// sign change
		RTX_COMPEN_Vib_Roll[1] = (float)(-0.3*Right_Roll_Vib_Reduction(RF_TILT_R_Vel, 1));	// sign change
	}
	
	
	BCDataCont0();
	LegKine(0);
	RefPosCmd();
}

void AnkleRollCompenBackUP()
{
	unsigned char i, j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			RTX_oldCOMPEN_Ankle_Roll[i][j]=RTX_COMPEN_Ankle_Roll[i][j];
		}
	}
}

void BCDataCont()
{
	RTX_BodyCenter[0] = RTX_DeltaMove[0]; // X-Direction body center
	RTX_BodyCenter[1] = RTX_DeltaMove[1]; // Y-Direction body center
	RTX_BodyCenter[2] = RTX_DeltaMove[2]; // Z-Direction body center
	
	v_CartPosCont00[0] = -RTX_BodyCenter[0]; // 왼쪽 발 x 방향 제어
	v_CartPosCont00[1] = -RTX_BodyCenter[1]; // 왼쪽 발 y 방향 제어
	v_CartPosCont00[2] = -RTX_BodyCenter[2]; // 왼쪽 발 z 방향 제어
	
	v_CartPosCont00[3] = -RTX_BodyCenter[0]; // 오른쪽 발 x 방향 제어
	v_CartPosCont00[4] = -RTX_BodyCenter[1]; // 오른쪽 발 y 방향 제어
	v_CartPosCont00[5] = +RTX_BodyCenter[2]; // 오른쪽 발 z 방향 제어
	
	pSharedMemory->LeftAnkPos[0] = PosInput[0];
	pSharedMemory->LeftAnkPos[1] = PosInput[1];
	pSharedMemory->LeftAnkPos[2] = PosInput[2];
	
	pSharedMemory->RightAnkPos[0] = PosInput[3];
	pSharedMemory->RightAnkPos[1] = PosInput[4];
	pSharedMemory->RightAnkPos[2] = PosInput[5];
}

void BCDataCont0()
{
	v_CartPosCont000[0] = -RTX_DeltaMove0[0]-pSharedMemory->ZMPInitAdjust[0]; // 왼쪽 발 x 방향 제어
	v_CartPosCont000[1] = -RTX_DeltaMove0[1]-pSharedMemory->ZMPInitAdjust[1]; // 왼쪽 발 y 방향 제어
	v_CartPosCont000[2] = LZ;//+RTX_DeltaMove0[2]; // 왼쪽 발 z 방향 제어
	
	v_CartPosCont000[3] = -RTX_DeltaMove0[0]-pSharedMemory->ZMPInitAdjust[0]; // 오른쪽 발 x 방향 제어
	v_CartPosCont000[4] = -RTX_DeltaMove0[1]-pSharedMemory->ZMPInitAdjust[1]; // 오른쪽 발 y 방향 제어
	v_CartPosCont000[5] = RZ;//+RTX_DeltaMove0[2]; // 오른쪽 발 z 방향 제어
}

void BCDataCont2()
{
	v_CartPosCont02[0] = -RTX_DeltaMove2[0]; // 왼쪽 발 x 방향 제어
	v_CartPosCont02[1] = -RTX_DeltaMove2[1]; // 왼쪽 발 y 방향 제어
	//v_CartPosCont02[2] = -RTX_DeltaMove2[2]; // 왼쪽 발 z 방향 제어
	
	v_CartPosCont02[3] = -RTX_DeltaMove2[0]; // 오른쪽 발 x 방향 제어
	v_CartPosCont02[4] = -RTX_DeltaMove2[1]; // 오른쪽 발 y 방향 제어
	//v_CartPosCont02[5] = +RTX_DeltaMove2[2]; // 오른쪽 발 z 방향 제어
}

void UpperMove()
{
	AngPosInput(2);

	PROF_REF[RSP]=RTX_fREF[RSP]=AngleInput[RSP] + UpperMovement[RSP] + v_AngArm[0] + Extra_uppermovement[RSP];	// R-Shoulder Pitch	
	PROF_REF[RSR]=RTX_fREF[RSR]=AngleInput[RSR] + UpperMovement[RSR] + v_AngArm[1] + Extra_uppermovement[RSR];	// R-Shoulder Roll	
	PROF_REF[RSY]=RTX_fREF[RSY]=AngleInput[RSY] + UpperMovement[RSY] + v_AngArm[2] + Extra_uppermovement[RSY];	// R-Shoulder Yaw

	PROF_REF[REB]=RTX_fREF[REB]=AngleInput[REB] + UpperMovement[REB] + v_AngArm[3] + Extra_uppermovement[REB];	// R-Elbow	Pitch

	PROF_REF[LSP]=RTX_fREF[LSP]=AngleInput[LSP] + UpperMovement[LSP] + v_AngArm[4] + Extra_uppermovement[LSP];	// L-Shoulder Pitch
	PROF_REF[LSR]=RTX_fREF[LSR]=AngleInput[LSR] + UpperMovement[LSR] + v_AngArm[5] + Extra_uppermovement[LSR];	// L-Shoulder Roll
	PROF_REF[LSY]=RTX_fREF[LSY]=AngleInput[LSY] + UpperMovement[LSY] + v_AngArm[6] + Extra_uppermovement[LSY];	// L-Shoulder Yaw

	PROF_REF[LEB]=RTX_fREF[LEB]=AngleInput[LEB] + UpperMovement[LEB] + v_AngArm[7] + Extra_uppermovement[LEB];	// R-Elbow	Pitch
	
	PROF_REF[WST]=RTX_fREF[WST]=AngleInput[WST] + UpperMovement[WST];	// Waist Yaw

	PROF_REF[RWY]=RTX_fREF[RWY]=AngleInput[RWY] + UpperMovement[RWY] + Extra_uppermovement[RWY];
	PROF_REF[RW1]=RTX_fREF[RW1]=AngleInput[RW1] + UpperMovement[RW1];
	PROF_REF[RW2]=RTX_fREF[RW2]=AngleInput[RW2] + UpperMovement[RW2];

	PROF_REF[LWY]=RTX_fREF[LWY]=AngleInput[LWY] + UpperMovement[LWY] + Extra_uppermovement[LWY];
	PROF_REF[LW1]=RTX_fREF[LW1]=AngleInput[LW1] + UpperMovement[LW1];
	PROF_REF[LW2]=RTX_fREF[LW2]=AngleInput[LW2] + UpperMovement[LW2];

	PROF_REF[NKY]=RTX_fREF[NKY]=AngleInput[NKY] + UpperMovement[NKY];
	PROF_REF[NK1]=RTX_fREF[NK1]=AngleInput[NK1] + UpperMovement[NK1];
	PROF_REF[NK2]=RTX_fREF[NK2]=AngleInput[NK2] + UpperMovement[NK2];
	

	PROF_REF[LF1]=RTX_fREF[LF1]=AngleInput[LF1];
	PROF_REF[LF2]=RTX_fREF[LF2]=AngleInput[LF2];
	PROF_REF[LF3]=RTX_fREF[LF3]=AngleInput[LF3];
	PROF_REF[LF4]=RTX_fREF[LF4]=AngleInput[LF4];
	PROF_REF[LF5]=RTX_fREF[LF5]=AngleInput[LF5];

	PROF_REF[RF1]=RTX_fREF[RF1]=AngleInput[RF1];
	PROF_REF[RF2]=RTX_fREF[RF2]=AngleInput[RF2];
	PROF_REF[RF3]=RTX_fREF[RF3]=AngleInput[RF3];
	PROF_REF[RF4]=RTX_fREF[RF4]=AngleInput[RF4];
	PROF_REF[RF5]=RTX_fREF[RF5]=AngleInput[RF5];
}

void Walking_On_Spot()
{

	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			pSharedMemory->theta[RHY] = 0.;
			pSharedMemory->theta[LHY] = 0.;

			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;

			Path_Local_CNT = 0;

			Damping_control_init();
			Landing_control_init();

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;		

			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			pSharedMemory->Walking_Stop_Flag_2 = 0;
			Delay_LO_Control_Flag = FALSE;
			BC_x_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;
			pSharedMemory->Motion_State = 0; //Marking
		
		}

	if(pSharedMemory->Walking_Stop_Flag == 0 ){

		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // LF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[0]);  // 왼 다리  Lift
			
			// BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; }
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) + pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT + pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; }			

		}
		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if(Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2 ) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;

	
	}
	else{   // STOP 일 경우 
	//		test_6 = 1;
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == -1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT + 2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT + pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) + pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == -1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// LF
				temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[0];
				// RF
				temp_RF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = -(pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 && kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = -(float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	


		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0)	{
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

			
		// Damping Controller Switching	
		if(CTRL_mode == 3){
/*
			if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;

			Del_Mov_RF_y_Ang_Acc = Old_Del_Mov_RF_y_Ang_Acc - Old_Del_Mov_RF_y_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
			Del_Mov_RF_x_Ang_Acc = Old_Del_Mov_RF_x_Ang_Acc - Old_Del_Mov_RF_x_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/
			Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발떨림 제거

			landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			//LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); 
			//Land_Damp_LAP = old_Land_Damp_LAP - old_Land_Damp_LAP*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));
/*
			if(landLF_CNT == 10) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch

			if(landLF_CNT >= 10) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 +8)));

			if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landLF_CNT >= 15)  landLF_Tilt_R = - 0.3*temp_LF_TILT_R;
*/
			if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
			else {
					landLF = landLF_old = landLF_del = 0.;
					land_damp_fwd(0.,0.,0,0);
					//Old_Del_Mov_RF_y_Ang_Acc = 0.;
					//Old_Del_Mov_RF_x_Ang_Acc = 0.;
			}
			
		
			landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
			else { //new//
				landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
			} //new//

			 
			R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
			else {
				R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
				R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds4(0,0,0,0);   
					angle_stiff_fwR(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Right_Ankle_Control_Roll(0. ,0., 0.);
					Right_Ankle_Control_Pitch(0., 0., 0.);
				}
			}


			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
		
/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
*/			
			FiveKG_R_Flag = 0;
			LandROK_Flag = 0;
			Delay_LO_Control_Flag = FALSE;

		} // end of CTRL_mode 3
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandLOK_Flag = 0;		
	

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//
*/
			if(CTRL_mode == 1) { 
					Delay_LO_Control_Flag = FALSE;
					FiveKG_L_Flag = 0;					

/*
					if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0;}
				
					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}

					Del_Mov_LF_y_Ang_Acc = Old_Del_Mov_LF_y_Ang_Acc - Old_Del_Mov_LF_y_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
					Del_Mov_LF_x_Ang_Acc = Old_Del_Mov_LF_x_Ang_Acc - Old_Del_Mov_LF_x_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/
					//Del_Mov_LHip_r = 0.012*pSharedMemory->LF_TILT_R; //발떨림 제거					
					//Del_Mov_LHip_r = 0.008*pSharedMemory->LF_TILT_R; //발떨림 제거					
					Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); //발떨림 제거					
					
				
					landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					//RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); 
					//Land_Damp_RAP = old_Land_Damp_RAP - old_Land_Damp_RAP*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
/*
					if(pSharedMemory->Int_CNT > pSharedMemory->Step_time){

							if(landRF_CNT == 10) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch
						
							if(landRF_CNT >= 10) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 + 8))) ;

							if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
							if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
					}
*/
					if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
					else {
							landRF = landRF_old = landRF_del = 0.;
							land_damp_fwd(0.,0.,0,0);
							//Old_Del_Mov_LF_y_Ang_Acc = 0.;
							//Old_Del_Mov_LF_x_Ang_Acc = 0.;
					}
					
					
					landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
					else { //new//
						landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
						LF_land_damp_roll(0.,0.,0,0); //new//
					}//new//
					
					L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
					else {
						L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
						L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds3(0,0,0,0);   
							angle_stiff_fwL(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Left_Ankle_Control_Roll(0., 0., 0.);
							Left_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_LAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_LAP = Land_Damp_LAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_LHip_r = 0.;
			//Del_Mov_LHip_p = 0.;
			Del_Mov_RHip_r = 0.;
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_LF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_LF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_LF_x_Ang_Acc > 2) Del_LF_x_Ang_Acc = 2.0;
				else if(Del_LF_x_Ang_Acc < -2) Del_LF_x_Ang_Acc = -2.0;

				if(Del_LF_y_Ang_Acc > 2) Del_LF_y_Ang_Acc = 2.0;
				else if(Del_LF_y_Ang_Acc < -2) Del_LF_y_Ang_Acc = -2.0;
				
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}
			
			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_LF_Ang_Acc); 
			Del_Mov_LF_x_Ang_Acc = 1.0*Del_LF_x_Ang_Acc*temp_Del_LF_Ang_Acc;
			Del_Mov_LF_y_Ang_Acc = 1.0*Del_LF_y_Ang_Acc*temp_Del_LF_Ang_Acc;
			Old_Del_Mov_LF_y_Ang_Acc = Del_Mov_LF_y_Ang_Acc;
			Old_Del_Mov_LF_x_Ang_Acc = Del_Mov_LF_x_Ang_Acc;
*/

			if(LandLOK_Flag == 0) {
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				

				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
					landLF_old = landLF;
					landLF_del = (float)(0. - landLF);
					landLF_CNT = 0;

					landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landLF_r_old = landLF_r; //new//
					landLF_r_del = (float)(0. - landLF_r); //new//
					landLF_r_CNT = 0; //new//
				}
				
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_RAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_RAP = Land_Damp_RAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_RHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			Del_Mov_LHip_r = 0.; 
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
				
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_RF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_RF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_RF_x_Ang_Acc > 2) Del_RF_x_Ang_Acc = 2.0;
				else if(Del_RF_x_Ang_Acc < -2) Del_RF_x_Ang_Acc = -2.0;

				if(Del_RF_y_Ang_Acc > 2) Del_RF_y_Ang_Acc = 2.0;
				else if(Del_RF_y_Ang_Acc < -2) Del_RF_y_Ang_Acc = -2.0;
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}

			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_RF_Ang_Acc); 
			Del_Mov_RF_x_Ang_Acc = 1.0*Del_RF_x_Ang_Acc*temp_Del_RF_Ang_Acc;
			Del_Mov_RF_y_Ang_Acc = 1.0*Del_RF_y_Ang_Acc*temp_Del_RF_Ang_Acc;
			Old_Del_Mov_RF_y_Ang_Acc = Del_Mov_RF_y_Ang_Acc;
			Old_Del_Mov_RF_x_Ang_Acc = Del_Mov_RF_x_Ang_Acc;

			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//

				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0;	//new//		

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
					landRF_old = landRF;
					landRF_del = (float)(0. - landRF);
					landRF_CNT = 0;

					landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landRF_r_old = landRF_r; //new//
					landRF_r_del = (float)(0. - landRF_r); //new//
					landRF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				

				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			//Del_Mov_LHip_p = 0.;
			
			
			//
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->Gesture_Flag == FALSE)){
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{

				pSharedMemory->Motion_State = 6; // Stop

				if((pSharedMemory->Demo_4_Flag == FALSE) && (pSharedMemory->Demo_5_Flag == FALSE))
				{
					DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
					DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
				}
			}

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);

				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landRF = landLF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
					
		}

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		 // Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
		}
		
		// Landing Position Control
		if(CTRL_mode == 2 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 4 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_L_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_R_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}
		
		// Body center lateral amplitude compensation
		if(pSharedMemory->Yzmp > 0) {temp_Plus_Yzmp_avg = temp_Plus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_1++;}
		else if(pSharedMemory->Yzmp < 0) {temp_Minus_Yzmp_avg = temp_Minus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_2++;}

		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(zmp_CNT_1 != 0 && zmp_CNT_2 != 0){
			
				pSharedMemory->Plus_Yzmp_avg = temp_Plus_Yzmp_avg/zmp_CNT_1;
				pSharedMemory->Minus_Yzmp_avg = temp_Minus_Yzmp_avg/zmp_CNT_2;
	
				if(pSharedMemory->Path_Area_CNT >= 3){
					Amp_BC_Y_Amp_Compen_M = (float)(BC_Y_Amp_Comp_M((float)(0.5*(pSharedMemory->Plus_Yzmp_avg - pSharedMemory->Minus_Yzmp_avg)), AvgZMPAmp, 1));
				}
			}

			temp_Plus_Yzmp_avg = 0.;
			temp_Minus_Yzmp_avg = 0.;
			zmp_CNT_1 = 0;
			zmp_CNT_2 = 0;
		}

		BC_Y_Amp_Compen = (float)(Amp_BC_Y_Amp_Compen_M*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
		////////////////////////////////////////////////////////////////////////////////////////////////////

		// Body Center Adjustment
		//Temp_Inc_Sum = Temp_Inc_Sum + Rolling_angle; 
		Temp_Inc_Sum = Temp_Inc_Sum + RTX_CompenTheta_R;
		Temp_Inc_Sum_CNT++;
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}
		
	
	// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
				//Start_Kick_BC_Y_Comp = (float)(6.*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;

		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
			if(!pSharedMemory->Walking_Gesture_Flag){
			
				//pSharedMemory->theta[RSP] = -WLK_RDY_LRSP + WLKING_LRSP*0.5*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));		
				//pSharedMemory->theta[REB] = WLK_RDY_LREB + WLKING_LREB*0.5*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			
				//pSharedMemory->theta[LSP] = -WLK_RDY_LRSP + WLKING_LRSP*0.5*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				//pSharedMemory->theta[LEB] = WLK_RDY_LREB + WLKING_LREB*0.5*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));

				v_AngArm[0] = (float)(WLKING_LRSP*0.5*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));		
				v_AngArm[3] = (float)(WLKING_LREB*0.5*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				
				v_AngArm[4] = (float)(WLKING_LRSP*0.5*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				v_AngArm[7] = (float)(WLKING_LREB*0.5*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				//	pSharedMemory->theta[WST] = WLKING_WST*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			}

			if(pSharedMemory->Motion_State != 6){
				
					BC_y_ZMP_CON = (float)(pSharedMemory->gain_temp1*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
					BC_x_ZMP_CON = (float)(pSharedMemory->gain_temp2*SSP_ZMP_CON_X(10,Xzmp_lp,1));
					old_BC_y_ZMP_CON = BC_y_ZMP_CON;
					old_BC_x_ZMP_CON = BC_x_ZMP_CON;
					BC_x_ZMP_CON_CNT = 0;
			}
			else{
					BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					SSP_ZMP_CON_Y(0,0,0);
					SSP_ZMP_CON_X(0,0,0);

					if(BC_x_ZMP_CON_CNT < 50) BC_x_ZMP_CON_CNT++;
			}			
		}
			
		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking((float)(Pit_y_a_1_Hspd - 0.),1));
		}

		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + Start_Kick_BC_Y_Comp + DeltaMov_y + DeltaMov_y_dsp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA + DSP_temp_1 + SSP_temp_1;//
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + DeltaMov_x_dsp + BC_x_ZMP_CON + SSP_temp_5;
		pSharedMemory->BC_z = -WLK_RDY_DOWN + Gesture_Pelvis_2;

		pSharedMemory->R_px = - pSharedMemory->BC_x;// + Gesture_Step_RF_x;//+ Del_Mov_RF_x_Ang_Acc;
		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y - DSP_temp_4);// + pSharedMemory->R_py_Compen + Gesture_Step_RF_y;//+ Del_Mov_RF_y_Ang_Acc;
		
		pSharedMemory->L_px = - pSharedMemory->BC_x;// + Gesture_Step_LF_x;//+ Del_Mov_LF_x_Ang_Acc;
		pSharedMemory->L_py = (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + DSP_temp_3);// + pSharedMemory->L_py_Compen + Gesture_Step_LF_y;//+ Del_Mov_LF_y_Ang_Acc;
		
		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA + DSP_temp_2;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA + DSP_temp_2;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA + SSP_temp_2;// + Equi_Adj_Lfoot_Z_Walking + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA + SSP_temp_2;


		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;

		//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		//pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;
		
		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
	
		// End of if(pSharedMemory->Mark_Time_Flag && WLK_RDY_MODE == 1 && pSharedMemory->FSM == 0){ // 제자리걸음 , Left Foot Starting
}

void Forward_Walking()
{
	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
		for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
		pSharedMemory->theta[RHY] = 0.;
		pSharedMemory->theta[LHY] = 0.;

		RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;

		Damping_control_init();
		Landing_control_init();

		Del_Mov_RHip_r = 0.0f;
		Del_Mov_LHip_r = 0.0f;

		Temp_Inc_Sum = 0.0f;
		Temp_Inc_Sum_CNT = 0;
		Inc_Avg = 0.0f;

		DelMov_LRAP_OL_CNT = 0;
		DelMov_LRAP_OL = 0.0f;
		

		Delay_LO_Control_Flag = FALSE;
		Path_Local_CNT = 0;

		BC_x_ZMP_CON_CNT = 0; BC_y_ZMP_CON_CNT = 0;
		old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;
									
		abs_footRx_ref = abs_footRx_del = abs_footRx_old2 = 0.;
		abs_footLx_ref = abs_footLx_del = abs_footLx_old2 = 0.; 

		abs_footLx = abs_footLx_old = temp_abs_footLx_1 = temp_abs_footLx_2 = 0.;
		abs_footLx_CNT = 0;

		abs_footRx = abs_footRx_old = temp_abs_footRx_1 = temp_abs_footRx_2 = 0.;
		abs_footRx_CNT = 0;

		abs_hipx = abs_hipx_old = temp_abs_hipx = 0.;
		abs_hipx_CNT = 1;

		rel_footRx = rel_footLx = 0.;

		pSharedMemory->Walking_Stop_Flag_2 = 0;	
		pSharedMemory->Motion_State = 1; // FWD

		RAP_Landing_OnOff_CNT = 1;
		LAP_Landing_OnOff_CNT = 2;

		temp_LRHY_1_LT = temp_LRHY_2_LT = 0.; // 회전 관련
		LRHY_CNT_LT = 0; // 회전 관련
		temp_LRHY_1_RT = temp_LRHY_2_RT = 0.; // 회전 관련
		LRHY_CNT_RT = 1; // 회전 관련

		LF_More_Strech_old = LF_More_Strech = 0.;
		RF_More_Strech_old = RF_More_Strech = 0.;
		
		}

	if(pSharedMemory->Walking_Stop_Flag == 0 ){
	
		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // LF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[0]);  // 왼 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) + pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if(Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2 ) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;

	}
	else{   // STOP 일 경우 
			
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == -1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == -1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// LF
				temp_LF_Walk_Mov_Z =  (float)(0.75*pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[0]);
				// RF
				temp_RF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = -(pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(kirk_i==1){ // 둘째 걸음 
				// LF
				temp_LF_Walk_Mov_Z =  (float)(-0.75*pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[1]);
				// RF
				temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[1];
				//BC
				temp_BC_Walk_Mov_Y = (pSharedMemory->Walk_BC_Ydir_Amp)*BC_Walk_Mov_Y[1];
		
			}
			else if(temp_Path_Area_CNT >= 2 && pSharedMemory->Walking_Stop_Flag == 1 &&  kirk_i == pSharedMemory->Path_Area_CNT - 1){
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  (float)(0.75*pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i]);
					//BC
					temp_BC_Walk_Mov_Y =  pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  (float)(0.75*pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i]);
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
			}
			else if(temp_Path_Area_CNT >= 2 && pSharedMemory->Walking_Stop_Flag == 1 &&  kirk_i == pSharedMemory->Path_Area_CNT){
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  (float)(-0.75*pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i]);
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  (float)(-0.75*pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i]);
					// BC
					temp_BC_Walk_Mov_Y = (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 &&  kirk_i == pSharedMemory->Path_Area_CNT){
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	


		if(abs_hipx_CNT > 2) Temp_Step_Length_0 = pSharedMemory->Step_Length;
		else if(abs_hipx_CNT == 1) Temp_Step_Length_0 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
		else if(abs_hipx_CNT == 2) Temp_Step_Length_0 = (float)(pSharedMemory->Step_Length * 0.75);

		if(abs_footLx_CNT >= 4) Temp_Step_Length_1 = pSharedMemory->Step_Length ;
		else if(abs_footLx_CNT == 0) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
		else if(abs_footLx_CNT == 2) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.875);

		if(abs_footRx_CNT >= 2) Temp_Step_Length_2 = pSharedMemory->Step_Length;
		else if(abs_footRx_CNT == 0) Temp_Step_Length_2 = (float)(pSharedMemory->Step_Length * 0.625); // 보폭의 점차적인 증가
		
		// Abs_LF_X
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLx_1,pSharedMemory->Int_CNT,abs_footLx_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLx_2,pSharedMemory->Int_CNT,abs_footLx_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);

			PROF_ftn_1_cos(pSharedMemory->Int_CNT,LAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 5, pSharedMemory->Up_time/2 - pSharedMemory->Delay_time -5,0,0,0,0,&temp_theta_1); 
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,LAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2 - pSharedMemory->Delay_time,2*pSharedMemory->Delay_time + 0.3*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0,0,0,0,&temp_theta_2); 
			Land_OnOff_LAP_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,LAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2 + pSharedMemory->Delay_time + 0.3*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0.6*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0,0,0,0,&temp_theta_7); 
			
		}
		
		//if(abs_footLx_CNT == 0)	abs_footLx = (Temp_Step_Length_1 - Land_Off_Fwd_Disp)*(temp_abs_footLx_1 + temp_abs_footLx_2) + (Land_Off_Fwd_Disp*temp_abs_footLx_4) + abs_footLx_old;	
		if(abs_footLx_CNT == 0)	 {
			abs_footLx = Temp_Step_Length_1*(temp_abs_footLx_1 + temp_abs_footLx_2) + abs_footLx_old;
			Land_OnOff_LAP_2 = (float)(0.5*ANK_PITCH_ANG_UP*temp_theta_1 - (0.5*ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_2 + ANK_PITCH_ANG*temp_theta_7);
		}
		else if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			
			if(abs_footLx_CNT >= 4) Temp_Step_Length_1 = pSharedMemory->Step_Length;
			else if(abs_footLx_CNT == 2) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.75); // 보폭의 점차적인 증가

			abs_footLx = Temp_Step_Length_1*(temp_abs_footLx_1 + temp_abs_footLx_2) + abs_footLx_old;
			Land_OnOff_LAP_2 = (float)(0.5*ANK_PITCH_ANG_UP*temp_theta_1 - (0.5*ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_2 + ANK_PITCH_ANG*temp_theta_7);			
		}
		else {
			abs_footLx = 2*Temp_Step_Length_1*(temp_abs_footLx_1 + temp_abs_footLx_2) + abs_footLx_old;
			Land_OnOff_LAP_2 = ANK_PITCH_ANG_UP*temp_theta_1 - (ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_2 + ANK_PITCH_ANG*temp_theta_7;
		}
				
		
		if(LF_half_cyclDN_Status == 2 )  {	
			abs_footLx_old = abs_footLx;
			temp_abs_footLx_1 = 0.;
			temp_abs_footLx_2 = 0.;
			abs_footLx_CNT = abs_footLx_CNT+2;
		}

		
		if(Land_OnOff_LAP_Status == 4){
			LAP_Landing_OnOff_CNT = LAP_Landing_OnOff_CNT + 2;
		}

		// Abs_RF_X
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRx_1,pSharedMemory->Int_CNT,(abs_footRx_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRx_2,pSharedMemory->Int_CNT,(abs_footRx_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);

			PROF_ftn_1_cos(pSharedMemory->Int_CNT,RAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 5, pSharedMemory->Up_time/2 - pSharedMemory->Delay_time -5 ,0,0,0,0,&temp_theta_5); 
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,RAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2 - pSharedMemory->Delay_time,2*pSharedMemory->Delay_time + 0.3*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0,0,0,0,&temp_theta_6); 
			Land_OnOff_RAP_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,RAP_Landing_OnOff_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2 + pSharedMemory->Delay_time + 0.3*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0.6*(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time),0,0,0,0,&temp_theta_8); 
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
		
			if(abs_footRx_CNT >= 2) Temp_Step_Length_2 = pSharedMemory->Step_Length ;
			else if(abs_footRx_CNT == 0) Temp_Step_Length_2 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
			
			abs_footRx = Temp_Step_Length_2*(temp_abs_footRx_1 + temp_abs_footRx_2) + abs_footRx_old;
			Land_OnOff_RAP_2 = (float)(0.5*ANK_PITCH_ANG_UP*temp_theta_5 - (0.5*ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_6 + ANK_PITCH_ANG*temp_theta_8);
		}
		else {
			abs_footRx = 2*Temp_Step_Length_2*(temp_abs_footRx_1 + temp_abs_footRx_2) + abs_footRx_old;
			if(abs_footRx_CNT == 0) Land_OnOff_RAP_2 = (float)(0.75*ANK_PITCH_ANG_UP*temp_theta_5 - (0.75*ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_6 + ANK_PITCH_ANG*temp_theta_8);
			else  Land_OnOff_RAP_2 = ANK_PITCH_ANG_UP*temp_theta_5 - (ANK_PITCH_ANG_UP+ANK_PITCH_ANG)*temp_theta_6 + ANK_PITCH_ANG*temp_theta_8;
		}

		
		
		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRx_old = abs_footRx;
			temp_abs_footRx_1 = 0.;
			temp_abs_footRx_2 = 0.;
			abs_footRx_CNT = abs_footRx_CNT+2;
		}

		if(Land_OnOff_RAP_Status == 4){
			RAP_Landing_OnOff_CNT = RAP_Landing_OnOff_CNT + 2;
		}

		// 보폭 비율 설정
		
		abs_hipx_status = delayhalf1_cosdelay(-3,&temp_abs_hipx,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipx_CNT)- pSharedMemory->Delay_time,pSharedMemory->Step_time);

		abs_hipx = Temp_Step_Length_0*temp_abs_hipx + abs_hipx_old;
		
		
		if(abs_hipx_status == 2 && pSharedMemory->Walking_Stop_Flag == 0){
			abs_hipx_old = abs_hipx;
			temp_abs_hipx = 0.;
			abs_hipx_CNT++;
			if(temp_hip_x >= 10.) temp_hip_x = 10.;
			else if(temp_hip_x <= -10.) temp_hip_x = -10.;

			hip_Adj = (long)(temp_hip_x);
		}

		rel_footRx = abs_footRx - abs_hipx ; 
		rel_footLx = abs_footLx - abs_hipx ;


		if(CTRL_mode != 5 || LRHY_status_LT != 4){
				PROF_ftn_1_cos(pSharedMemory->Int_CNT, LRHY_CNT_LT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_1_LT);
				LRHY_status_LT = PROF_ftn_1_cos(pSharedMemory->Int_CNT,LRHY_CNT_LT*pSharedMemory->Step_time + pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_2_LT);
		}

		if(CTRL_mode != 5 || LRHY_status_RT != 4){
				PROF_ftn_1_cos(pSharedMemory->Int_CNT, LRHY_CNT_RT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_1_RT);
				LRHY_status_RT = PROF_ftn_1_cos(pSharedMemory->Int_CNT,LRHY_CNT_RT*pSharedMemory->Step_time + pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_2_RT);
		}

		if(LRHY_status_LT == 4){
			temp_LRHY_1_LT = temp_LRHY_2_LT = 0.;
			LRHY_CNT_LT = LRHY_CNT_LT + 2;
			pSharedMemory->FWD_Turning_Flag_1_LT = 1;
		}
		else {pSharedMemory->FWD_Turning_Flag_1_LT = 0;}

		if(LRHY_status_RT == 4){
			temp_LRHY_1_RT = temp_LRHY_2_RT = 0.;
			LRHY_CNT_RT = LRHY_CNT_RT + 2;
			pSharedMemory->FWD_Turning_Flag_1_RT = 1;
		}
		else {pSharedMemory->FWD_Turning_Flag_1_RT = 0;}


		if(pSharedMemory->FWD_Turning_Flag_2_LT == 1 && CTRL_mode != 5){
			pSharedMemory->theta[RHY] = -pSharedMemory->FWD_Turning_Angle*(temp_LRHY_1_LT - temp_LRHY_2_LT); 
			pSharedMemory->theta[LHY] = -pSharedMemory->theta[RHY];
		}
		else if(pSharedMemory->FWD_Turning_Flag_2_RT == 1 && CTRL_mode != 5){
			pSharedMemory->theta[RHY] = -pSharedMemory->FWD_Turning_Angle*(temp_LRHY_1_RT - temp_LRHY_2_RT); 
			pSharedMemory->theta[LHY] = -pSharedMemory->theta[RHY];
		}
 

		pSharedMemory->PIT_SUP_ANG_0 = 0.;


		//  Angle Roll Compensation NORMAL 
		if(pSharedMemory->BC_y < 0)	{
			if(pSharedMemory->Int_CNT >= pSharedMemory->Step_time*2 + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
				if(pSharedMemory->Step_Length >= 200) DelMov_RAR = (float)(1.0*pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				else if(pSharedMemory->Step_Length >= 150) DelMov_RAR = (float)(1.0*pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				else  DelMov_RAR = (float)(1.0*pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			}
			else DelMov_RAR = (float)(1.0*pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
			DelMov_LAR_TOC = 0.;
		}
		else {
			if(pSharedMemory->Int_CNT >= pSharedMemory->Step_time*2 + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
				if(pSharedMemory->Step_Length >= 200) DelMov_LAR = (float)(1.0*pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				else if(pSharedMemory->Step_Length >= 150) DelMov_LAR = (float)(1.0*pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				else  DelMov_LAR = (float)(1.0*pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			}
			else DelMov_LAR = (float)(1.0*pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
			DelMov_RAR_TOC = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){

			Delay_LO_Control_Flag = FALSE;
			LandROK_Flag = 0;
			FiveKG_R_Flag = 0;

			

			/*
			OR_x = abs_footRx - abs_footLx ;
			OL_x = 0.;			
			
			if(landLF_CNT == 10){landRF_Tilt = 0.; landRF_Tilt_R = 0.;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;

					
			// 지지발 각도 보상
			PROF_ftn_1_cos(Path_Local_CNT,pSharedMemory->Upstart_time, pSharedMemory->Up_time/2,0,0,0,0,&temp_theta_4); 
			Land_OnOff_RAP = pSharedMemory->PIT_SUP_ANG_0*temp_theta_3 - pSharedMemory->PIT_SUP_ANG_0*temp_theta_4; //mode 2 에서 사용된 발목각도를 recover 한다. 

			Del_Mov_RF_y_Ang_Acc = Old_Del_Mov_RF_y_Ang_Acc - Old_Del_Mov_RF_y_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
			Del_Mov_RF_x_Ang_Acc = Old_Del_Mov_RF_x_Ang_Acc - Old_Del_Mov_RF_x_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

			
			*/
			Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); //발떨림 제거			
			
			landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))));
			/*
			LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));
			RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));
			Land_Damp_LAP = old_Land_Damp_LAP - old_Land_Damp_LAP*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); 
			
			
			if(landLF_CNT == 20 ) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking;

			if(landLF_CNT >= 20 ) {
				landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 + 8))) ;
			}

			if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
					
			if(landLF_CNT >= 15) landLF_Tilt_R = - 0.3*temp_LF_TILT_R;
*/
			if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
			else {
					landLF = landLF_old = landLF_del = 0.;
					land_damp_fwd(0.,0.,0,0);
					//Old_Del_Mov_RF_x_Ang_Acc = 0.;
					//Old_Del_Mov_RF_y_Ang_Acc = 0.;
				}


			landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
			else { //new//
				landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
			} //new//

			
			 
			R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
			else {
				R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
				R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds4(0,0,0,0);   
					angle_stiff_fwR(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Right_Ankle_Control_Roll(0., 0., 0.);
					Right_Ankle_Control_Pitch(0., 0., 0.);
				}
			}

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
			}
			/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
			*/
			
		}
		else if(CTRL_mode == 0 || CTRL_mode == 1){

			LandLOK_Flag = 0;		
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
			}
			
			
			if(CTRL_mode == 0) {
		
				DelMov_LRAP_OL = (float)(-(pSharedMemory->Step_Length/200)*UpBody_Tilt_LRHP*0.5*(1.-cos(PI*DelMov_LRAP_OL_CNT/(pSharedMemory->Upstart_time)))); 
							
				if(DelMov_LRAP_OL_CNT < pSharedMemory->Upstart_time)
				{
					DelMov_LRAP_OL_CNT++;
				}
			}
				
			/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//
			*/
			if(CTRL_mode == 1) { 
					Delay_LO_Control_Flag = FALSE;
					FiveKG_L_Flag = 0;
					DelMov_LRAP_OL_CNT = 0;
					/*
					OL_x = abs_footLx - abs_footRx ;
					OR_x = 0.;

					
					if(landRF_CNT == 10){landLF_Tilt = 0.;	landLF_Tilt_R = 0.;}

					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}

					Del_Mov_LF_y_Ang_Acc = Old_Del_Mov_LF_y_Ang_Acc - Old_Del_Mov_LF_y_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
					Del_Mov_LF_x_Ang_Acc = Old_Del_Mov_LF_x_Ang_Acc - Old_Del_Mov_LF_x_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/
					Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); //발떨림제거
/*					
															
					// 지지발 각도 보상
					if(pSharedMemory->Path_Area_CNT > 0){
						PROF_ftn_1_cos(Path_Local_CNT,pSharedMemory->Upstart_time,pSharedMemory->Up_time/2,0,0,0,0,&temp_theta_4); 
						Land_OnOff_LAP = pSharedMemory->PIT_SUP_ANG_0*temp_theta_3 - pSharedMemory->PIT_SUP_ANG_0*temp_theta_4; //mode 4 에서 사용된 발목각도를 recover 한다. 

					}
							
					*/
					landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					/*
					RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
					LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
					Land_Damp_RAP = old_Land_Damp_RAP - old_Land_Damp_RAP*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); 

					if(pSharedMemory->Int_CNT > pSharedMemory->Step_time){
							if(landRF_CNT == 20 ) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking ;
						
							if(landRF_CNT >= 20 ) {
								landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 20 )/(pSharedMemory->Up_time/2 - 20 + 8 ))) ;
							}

							if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
					
							if(landRF_CNT >= 15) landRF_Tilt_R = - 0.3*temp_RF_TILT_R;
					}
					*/
					if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
					else {
							landRF = landRF_old = landRF_del = 0.;
							land_damp_fwd(0.,0.,0,0);
							//Old_Del_Mov_LF_y_Ang_Acc = 0.;
							//Old_Del_Mov_LF_x_Ang_Acc = 0.;
						}
					
					landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
					else { //new//
						landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
						LF_land_damp_roll(0.,0.,0,0); //new//
					}//new//
					

					L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
					else {
						L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
						L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds3(0,0,0,0);   
							angle_stiff_fwL(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Left_Ankle_Control_Roll(0., 0., 0.);
							Left_Ankle_Control_Pitch(0., 0., 0.);
						}
					}

			}
		}
		else if(CTRL_mode == 2){
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;

			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_LAP = LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_LAP = Land_Damp_LAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);

						
			//지지발 각도 보상
			PROF_ftn_1_cos(Path_Local_CNT,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time,0,0,0,0,&temp_theta_3); 
			Land_OnOff_RAP = pSharedMemory->PIT_SUP_ANG_0*temp_theta_3;
*/
			Del_Mov_LHip_r = 0.;
			Del_Mov_RHip_r = 0.;
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_LF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_LF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
		
				if(Del_LF_x_Ang_Acc > 2) Del_LF_x_Ang_Acc = 2.0;
				else if(Del_LF_x_Ang_Acc < -2) Del_LF_x_Ang_Acc = -2.0;

				if(Del_LF_y_Ang_Acc > 2) Del_LF_y_Ang_Acc = 2.0;
				else if(Del_LF_y_Ang_Acc < -2) Del_LF_y_Ang_Acc = -2.0;

			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}
			
			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_LF_Ang_Acc); 
			Del_Mov_LF_x_Ang_Acc = 1.0*Del_LF_x_Ang_Acc*temp_Del_LF_Ang_Acc;
			Del_Mov_LF_y_Ang_Acc = 1.0*Del_LF_y_Ang_Acc*temp_Del_LF_Ang_Acc;
			Old_Del_Mov_LF_y_Ang_Acc = Del_Mov_LF_y_Ang_Acc;
			Old_Del_Mov_LF_x_Ang_Acc = Del_Mov_LF_x_Ang_Acc;
			*/
		
			if(LandLOK_Flag == 0) {	
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); //modi//
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
				}
				
				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//

			}
			else { // when the load 30 kg is measured
				
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;

				if(Delay_LO_Control_Flag){
					landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); //modi//
					landLF_old = landLF;
					landLF_del = (float)(0. - landLF);
					landLF_CNT = 0;

					landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landLF_r_old = landLF_r; //new//
					landLF_r_del = (float)(0. - landLF_r); //new//
					landLF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
				}

				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			OR_x = abs_footRx - abs_footLx ;
			OL_x = 0.;

			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_RAP = LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_RAP = Land_Damp_RAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			
			// 지지발 각도 보상
			PROF_ftn_1_cos(Path_Local_CNT,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time,0,0,0,0,&temp_theta_3); 
			Land_OnOff_LAP = pSharedMemory->PIT_SUP_ANG_0*temp_theta_3;
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
				
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_RF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_RF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8 ;
				
				if(Del_RF_x_Ang_Acc > 2) Del_RF_x_Ang_Acc = 2.0;
				else if(Del_RF_x_Ang_Acc < -2) Del_RF_x_Ang_Acc = -2.0;

				if(Del_RF_y_Ang_Acc > 2) Del_RF_y_Ang_Acc = 2.0;
				else if(Del_RF_y_Ang_Acc < -2) Del_RF_y_Ang_Acc = -2.0;

			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}

			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_RF_Ang_Acc); 
			Del_Mov_RF_x_Ang_Acc = 1.0*Del_RF_x_Ang_Acc*temp_Del_RF_Ang_Acc;
			Del_Mov_RF_y_Ang_Acc = 1.0*Del_RF_y_Ang_Acc*temp_Del_RF_Ang_Acc;
			Old_Del_Mov_RF_y_Ang_Acc = Del_Mov_RF_y_Ang_Acc;
			Old_Del_Mov_RF_x_Ang_Acc = Del_Mov_RF_x_Ang_Acc;
			*/
	
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
				}

				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0;	//new//	

			}
			else {
				
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;

				if(Delay_LO_Control_Flag){
					landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
					landRF_old = landRF;
					landRF_del = (float)(0. - landRF);
					landRF_CNT = 0;

					landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landRF_r_old = landRF_r; //new//
					landRF_r_del = (float)(0. - landRF_r); //new//
					landRF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, DelMov_LRAP_OL));
				}
				

				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			OL_x = 0.;
			OR_x = 0.;
			Ref_Xzmp_Con_0 = 10.;

			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0);}

			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
			
*/
			

			Del_Mov_LHip_r = 0.;
			Del_Mov_RHip_r = 0.;
			

			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P

				DelMov_LRAP_OL = (float)(-(pSharedMemory->Step_Length/200)*UpBody_Tilt_LRHP + (pSharedMemory->Step_Length/200)*UpBody_Tilt_LRHP*0.5*(1.-cos(PI*DelMov_LRAP_OL_CNT/(pSharedMemory->Step_time)))); 
				if(DelMov_LRAP_OL_CNT < pSharedMemory->Step_time)
				{
					DelMov_LRAP_OL_CNT++;
				}

			}

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0); 
				
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landLF = landRF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
		} // End of else if(CTRL_mode == 5){

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 2 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 4 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_L_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_R_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}
		
		// Body center lateral amplitude compensation
		if(pSharedMemory->Yzmp > 0) {temp_Plus_Yzmp_avg = temp_Plus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_1++;}
		else if(pSharedMemory->Yzmp < 0) {temp_Minus_Yzmp_avg = temp_Minus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_2++;}
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(zmp_CNT_1 != 0 && zmp_CNT_2 != 0){
				
				pSharedMemory->Plus_Yzmp_avg = temp_Plus_Yzmp_avg/zmp_CNT_1;
				pSharedMemory->Minus_Yzmp_avg = temp_Minus_Yzmp_avg/zmp_CNT_2;
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					Amp_BC_Y_Amp_Compen_W = BC_Y_Amp_Comp_W((float)(0.5*(pSharedMemory->Plus_Yzmp_avg - pSharedMemory->Minus_Yzmp_avg)), AvgZMPAmp,pSharedMemory->Step_Length, 1);
				}
			}
			
			temp_Plus_Yzmp_avg = 0.;
			temp_Minus_Yzmp_avg = 0.;
			zmp_CNT_1 = 0;
			zmp_CNT_2 = 0;
		}
		
		BC_Y_Amp_Compen = (float)(Amp_BC_Y_Amp_Compen_W*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
		////////////////////////////////////////////////////////////////////////////////////////////////////

		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
			if(!pSharedMemory->Walking_Gesture_Flag){
				
				//pSharedMemory->theta[RSP] = -WLK_RDY_LRSP + WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;		
				//pSharedMemory->theta[REB] = WLK_RDY_LREB + WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				
				//pSharedMemory->theta[LSP] = -WLK_RDY_LRSP + -WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				//pSharedMemory->theta[LEB] = WLK_RDY_LREB + -WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				v_AngArm[0] = WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;		
				v_AngArm[3] = WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				
				v_AngArm[4] = -WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				v_AngArm[7] = -WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
			}
			
			if(pSharedMemory->Motion_State != 6){
				
				BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
				old_BC_y_ZMP_CON = BC_y_ZMP_CON;
				BC_y_ZMP_CON_CNT = 0;
				
				if(DelMov_RF_Walk_Z > 0.525*pSharedMemory->Walk_Foot_Zdir_Amp || DelMov_LF_Walk_Z > 0.525*pSharedMemory->Walk_Foot_Zdir_Amp){
					BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
					old_BC_x_ZMP_CON = BC_x_ZMP_CON;
					BC_x_ZMP_CON_CNT = 0;
				}
				else{
					BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/30)));
					SSP_ZMP_CON_X(0,0,0);
					if(BC_x_ZMP_CON_CNT < 30) BC_x_ZMP_CON_CNT++;
				}	
				
			}
			else{
				BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_y_ZMP_CON_CNT/50)));
				SSP_ZMP_CON_Y(0,0,0);
				
				if(BC_y_ZMP_CON_CNT < 50) BC_y_ZMP_CON_CNT++;
			}
			
		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd + DelMov_LRAP_OL,1));
		}

		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;


		if(pSharedMemory->Walk_BWD_Flag){
			pSharedMemory->R_px = - pSharedMemory->BC_x - rel_footRx;
			pSharedMemory->L_px = - pSharedMemory->BC_x - rel_footLx;
		}
		else{
			pSharedMemory->R_px = - pSharedMemory->BC_x + rel_footRx ;//+ Del_Mov_RF_x_Ang_Acc;
			pSharedMemory->L_px = - pSharedMemory->BC_x + rel_footLx ;//+ Del_Mov_LF_x_Ang_Acc;
		}

		
		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y + GAIN_CURVE*pSharedMemory->theta[RHY]);// - DSP_temp_4;//+ Del_Mov_RF_y_Ang_Acc;
		pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + GAIN_CURVE*pSharedMemory->theta[LHY]);// + DSP_temp_3;//+ Del_Mov_LF_y_Ang_Acc;

			
		//if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
		//	Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
		//}

		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;
		
		
		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;

		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	

		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;

	// End of else if(pSharedMemory->Walk_FWD_Flag && WLK_RDY_MODE == 1 && pSharedMemory->FSM == 0)
}

void Backward_Walking()
{
	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			pSharedMemory->theta[RHY] = 0.;
			pSharedMemory->theta[LHY] = 0.;

			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;
			Delay_LO_Control_Flag = FALSE;
			Path_Local_CNT = 0;
			Damping_control_init();
			Landing_control_init();

			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;

			BC_x_ZMP_CON_CNT = 0;BC_y_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;

			abs_footLx = abs_footLx_old = temp_abs_footLx_1 = temp_abs_footLx_2 = 0.;
			abs_footLx_CNT = 0;

			abs_footRx = abs_footRx_old = temp_abs_footRx_1 = temp_abs_footRx_2 = 0.;
			abs_footRx_CNT = 0;

			abs_hipx = abs_hipx_old = temp_abs_hipx = 0.;
			abs_hipx_CNT = 1;

			rel_footRx = rel_footLx = 0.;

			pSharedMemory->Walking_Stop_Flag_2 = 0;

			pSharedMemory->Motion_State = -1; // BWD
		}

	if(pSharedMemory->Walking_Stop_Flag == 0){

		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // RF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[0]);  // 오른 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if(Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2 ) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;

		
	}
	else{   // STOP 일 경우 
			
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == 1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == 1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// RF
				temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[0];
				// LF
				temp_LF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = (pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 && kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	


		if(abs_hipx_CNT > 2) Temp_Step_Length_0 = pSharedMemory->Step_Length;
		else if(abs_hipx_CNT == 1) Temp_Step_Length_0 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
		else if(abs_hipx_CNT == 2) Temp_Step_Length_0 = (float)(pSharedMemory->Step_Length * 0.75);

		if(abs_footRx_CNT >= 4) Temp_Step_Length_1 = pSharedMemory->Step_Length ;
		else if(abs_footRx_CNT == 0) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
		else if(abs_footRx_CNT == 2) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.875);

		if(abs_footLx_CNT >= 2) Temp_Step_Length_2 = pSharedMemory->Step_Length;
		else if(abs_footLx_CNT == 0) Temp_Step_Length_2 = (float)(pSharedMemory->Step_Length * 0.625); // 보폭의 점차적인 증가
		
		// Abs_LF_X
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLx_1,pSharedMemory->Int_CNT,(abs_footLx_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLx_2,pSharedMemory->Int_CNT,(abs_footLx_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			if(abs_footLx_CNT >= 2) Temp_Step_Length_2 = pSharedMemory->Step_Length ;
			else if(abs_footLx_CNT == 0) Temp_Step_Length_2 = (float)(pSharedMemory->Step_Length * 0.5); // 보폭의 점차적인 증가
			
			abs_footLx = Temp_Step_Length_2*(temp_abs_footLx_1 + temp_abs_footLx_2) + abs_footLx_old;	
		}
		else abs_footLx = 2*Temp_Step_Length_2*(temp_abs_footLx_1 + temp_abs_footLx_2) + abs_footLx_old;	 
		
		if(LF_half_cyclDN_Status == 2 )  {
			abs_footLx_old = abs_footLx;
			temp_abs_footLx_1 = 0.;
			temp_abs_footLx_2 = 0.;
			abs_footLx_CNT = abs_footLx_CNT+2;
		}

		// Abs_RF_X
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRx_1,pSharedMemory->Int_CNT,abs_footRx_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRx_2,pSharedMemory->Int_CNT,abs_footRx_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(abs_footRx_CNT == 0)	abs_footRx = Temp_Step_Length_1*(temp_abs_footRx_1 + temp_abs_footRx_2) + abs_footRx_old;	
		else if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
			
				if(abs_footRx_CNT >= 4) Temp_Step_Length_1 = pSharedMemory->Step_Length;
				else if(abs_footRx_CNT == 2) Temp_Step_Length_1 = (float)(pSharedMemory->Step_Length * 0.75); // 보폭의 점차적인 증가

				abs_footRx = Temp_Step_Length_1*(temp_abs_footRx_1 + temp_abs_footRx_2) + abs_footRx_old;	 
		}
		else	abs_footRx = 2*Temp_Step_Length_1*(temp_abs_footRx_1 + temp_abs_footRx_2) + abs_footRx_old;	 

		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRx_old = abs_footRx;
			temp_abs_footRx_1 = 0.;
			temp_abs_footRx_2 = 0.;
			abs_footRx_CNT = abs_footRx_CNT+2;
		}

		//if(CTRL_mode != 5){
			abs_hipx_status = delayhalf1_cosdelay(2,&temp_abs_hipx,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipx_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
		//}
	
		abs_hipx = Temp_Step_Length_0*temp_abs_hipx + abs_hipx_old;

		if(abs_hipx_status == 2 && pSharedMemory->Walking_Stop_Flag == 0){
			abs_hipx_old = abs_hipx;
			temp_abs_hipx = 0.;
			abs_hipx_CNT++;
		}

		rel_footRx = abs_footRx - abs_hipx ; 
		rel_footLx = abs_footLx - abs_hipx ;

		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0)	{
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){

			LandLOK_Flag = 0;
			FiveKG_L_Flag = 0;
			
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;

			if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0.;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
			*/
			landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); // 발 떨림 제거
			/*
			RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));

			if(landRF_CNT == 20) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

			if(landRF_CNT >= 20) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

			if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
			*/
			if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
			else {
				landRF = landRF_old = landRF_del = 0.;
				land_damp_fwd(0.,0.,0,0);
			}

			landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
			else { //new//
				landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
			} //new//
			
			
			 
			L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
			else {
				L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
				L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds3(0,0,0,0);   
					angle_stiff_fwL(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Left_Ankle_Control_Roll(0., 0., 0.);
					Left_Ankle_Control_Pitch(0., 0., 0.);
				}
			}
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}

			/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//			
			*/
		}
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandROK_Flag = 0;		
			
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
			/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
			*/

			if(CTRL_mode == 1) { 
					FiveKG_R_Flag = 0;
					
					/*
					OR_x = abs_footRx - abs_footLx ;
					OL_x = 0.;
								
					if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0.;}

					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}

					*/
					landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발 떨림 제거
					/*
					LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

					if(landLF_CNT == 20) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

					if(landLF_CNT >= 20) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

					if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
					if(landLF_CNT >= 15) landLF_Tilt_R = -0.3*temp_LF_TILT_R;
					*/
					if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
					else {
						landLF = landLF_old = landLF_del = 0.;
						land_damp_fwd(0.,0.,0,0);
					}

					landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
					else { //new//
						landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
						RF_land_damp_roll(0.,0.,0,0); //new//
					}//new//

					R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
					else {
						R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
						R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds4(0,0,0,0);   
							angle_stiff_fwR(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Right_Ankle_Control_Roll(0., 0., 0.);
							Right_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
			/*
			OR_x = abs_footRx - abs_footLx ;
			OL_x = 0.;
			*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_LFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0);
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
		
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0; //new//

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;
			*/
			Del_Mov_LHip_r = 0.;
			Del_Mov_RHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_RFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandLOK_Flag == 0) {	
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0);
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0;	//new//	

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			OL_x = 0.;
			OR_x = 0.;
			Ref_Xzmp_Con_0 = 10.;


			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			
			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
			}
			

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);  
				
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
								
				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landLF = landRF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
			//	DeltaMov_x = - 0.9*dsp_compen_p(Err_Xzmp,1); // P Controller
		} // End of Damping Controller Switching	

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 4 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 2 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_R_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_L_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}

		// Body center lateral amplitude compensation
		if(pSharedMemory->Yzmp > 0) {temp_Plus_Yzmp_avg = temp_Plus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_1++;}
		else if(pSharedMemory->Yzmp < 0) {temp_Minus_Yzmp_avg = temp_Minus_Yzmp_avg + pSharedMemory->Yzmp; zmp_CNT_2++;}
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(zmp_CNT_1 != 0 && zmp_CNT_2 != 0){
				
				pSharedMemory->Plus_Yzmp_avg = temp_Plus_Yzmp_avg/zmp_CNT_1;
				pSharedMemory->Minus_Yzmp_avg = temp_Minus_Yzmp_avg/zmp_CNT_2;
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					Amp_BC_Y_Amp_Compen_B = BC_Y_Amp_Comp_B((float)(0.5*(pSharedMemory->Plus_Yzmp_avg - pSharedMemory->Minus_Yzmp_avg)), AvgZMPAmp, 1);
				}
			}
			
			temp_Plus_Yzmp_avg = 0.;
			temp_Minus_Yzmp_avg = 0.;
			zmp_CNT_1 = 0;
			zmp_CNT_2 = 0;
		}
		
		BC_Y_Amp_Compen = (float)(Amp_BC_Y_Amp_Compen_B*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
		////////////////////////////////////////////////////////////////////////////////////////////////////

		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;
		
		if(pSharedMemory->Gesture_Flag == 0){
			if(!pSharedMemory->Walking_Gesture_Flag){
				//pSharedMemory->theta[RSP] = -WLK_RDY_LRSP - WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				//pSharedMemory->theta[LSP] = -WLK_RDY_LRSP + WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				//pSharedMemory->theta[REB] = WLK_RDY_LREB - WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				//pSharedMemory->theta[LEB] = WLK_RDY_LREB + WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;

				v_AngArm[0] = -WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				v_AngArm[4] = WLKING_LRSP*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				v_AngArm[3] = -WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
				v_AngArm[7] = WLKING_LREB*(abs_footLx-abs_footRx)/pSharedMemory->Step_Length;
			}
			
			if(pSharedMemory->Motion_State != 6){
				
					BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
					old_BC_y_ZMP_CON = BC_y_ZMP_CON;
					BC_y_ZMP_CON_CNT = 0;
					
				
					if(DelMov_RF_Walk_Z > 0.525*pSharedMemory->Walk_Foot_Zdir_Amp || DelMov_LF_Walk_Z > 0.525*pSharedMemory->Walk_Foot_Zdir_Amp){
						BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
						old_BC_x_ZMP_CON = BC_x_ZMP_CON;
						BC_x_ZMP_CON_CNT = 0;
					}
					else{
						BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/30)));
						SSP_ZMP_CON_X(0,0,0);
						if(BC_x_ZMP_CON_CNT < 30) BC_x_ZMP_CON_CNT++;
					}	
				
			}
			else{
					BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_y_ZMP_CON_CNT/50)));
					SSP_ZMP_CON_Y(0,0,0);
				
					if(BC_y_ZMP_CON_CNT < 50) BC_y_ZMP_CON_CNT++;
			}
			
		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd - 0.0f,1));
		}

		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;

		if(pSharedMemory->Walk_BWD_Flag){
			pSharedMemory->R_px = - pSharedMemory->BC_x - rel_footRx;
			pSharedMemory->L_px = - pSharedMemory->BC_x - rel_footLx;
		}
		else{
			pSharedMemory->R_px = - pSharedMemory->BC_x + rel_footRx;
			pSharedMemory->L_px = - pSharedMemory->BC_x + rel_footLx;
		}

		//OL_x = rel_footLx; // x 방향 ZMP Arm 설정 
		//OR_x = rel_footRx;


		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y);// - DSP_temp_4;
		pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y);// + DSP_temp_3;


		//if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
	//		Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
	//	}
				
		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;

		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;
		
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	

		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
}  // End of else if(pSharedMemory->Walk_FWD_Flag && WLK_RDY_MODE == 1 && pSharedMemory->FSM == 1)

void Left_Side_Walking()
{
	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			pSharedMemory->theta[RHY] = 0.;
			pSharedMemory->theta[LHY] = 0.;

			OL_x = 0.;
			OR_x = 0.;

			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;

			Delay_LO_Control_Flag = FALSE;
			Path_Local_CNT = 0;
			Damping_control_init();
			Landing_control_init();
			
			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;

			BC_x_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;

			abs_footLy = abs_footLy_old = temp_abs_footLy_1 = temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = 0;

			abs_footRy = abs_footRy_old = temp_abs_footRy_1 = temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = 0;

			abs_hipy = abs_hipy_old = temp_abs_hipy = 0.;
			abs_hipy_CNT = 1;

			rel_footRy = rel_footLy = 0.;

			pSharedMemory->Walking_Stop_Flag_2 = 0;	
			
			
			LF_More_Strech_old = RF_More_Strech_old = LF_More_Strech = RF_More_Strech = 0.;

			pSharedMemory->Motion_State = 3;  // L-side 
		}

	if(pSharedMemory->Walking_Stop_Flag == 0 ){
	
		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // LF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[0]);  // 왼 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if((Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2) && (temp_BC_Walk_Mov_Y > 0)) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;

		
	}
	else{   // STOP 일 경우 
		
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == -1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == -1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// LF
				temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[0];
				// RF
				temp_RF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = -(pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 &&  kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	
		
		// Abs_LF_Y
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLy_1,pSharedMemory->Int_CNT,abs_footLy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLy_2,pSharedMemory->Int_CNT,abs_footLy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	
		}
		else abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	 
		
		if(LF_half_cyclDN_Status == 2 )  {
			abs_footLy_old = abs_footLy;
			temp_abs_footLy_1 = 0.;
			temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = abs_footLy_CNT+2;
		}

		// Abs_RF_Y
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRy_1,pSharedMemory->Int_CNT,(abs_footRy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRy_2,pSharedMemory->Int_CNT,(abs_footRy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
				abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 
		}
		else	abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 

		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRy_old = abs_footRy;
			temp_abs_footRy_1 = 0.;
			temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = abs_footRy_CNT+2;
		}

		if(CTRL_mode != 5){
			abs_hipy_status = delayhalf1_cosdelay(3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
			//abs_hipy_status = delayhalf1_cosdelay(-3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
		}
	
		abs_hipy = pSharedMemory->Side_Step_Length*temp_abs_hipy + abs_hipy_old;

		if(abs_hipy_status == 2){
			abs_hipy_old = abs_hipy;
			temp_abs_hipy = 0.;
			abs_hipy_CNT = abs_hipy_CNT +2;
		}

		rel_footRy = abs_footRy - abs_hipy ; 
		rel_footLy = abs_footLy - abs_hipy ;


		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0){
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){
/*
			if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;

			Del_Mov_RF_y_Ang_Acc = Old_Del_Mov_RF_y_Ang_Acc - Old_Del_Mov_RF_y_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
			Del_Mov_RF_x_Ang_Acc = Old_Del_Mov_RF_x_Ang_Acc - Old_Del_Mov_RF_x_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/
			Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발떨림 제거

			landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			/*
			LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); 
			Land_Damp_LAP = old_Land_Damp_LAP - old_Land_Damp_LAP*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

			if(landLF_CNT == 10) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch

			if(landLF_CNT >= 10) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 +8)));

			if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landLF_CNT >= 15)  landLF_Tilt_R = - 0.3*temp_LF_TILT_R;
			*/
			if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
			else {
					landLF = landLF_old = landLF_del = 0.;
					land_damp_fwd(0.,0.,0,0);
					//Old_Del_Mov_RF_y_Ang_Acc = 0.;
					//Old_Del_Mov_RF_x_Ang_Acc = 0.;
			}
			
		
			landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
			else { //new//
				landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
			} //new//
	 
			R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
			else {
				R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
				R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds4(0,0,0,0);   
					angle_stiff_fwR(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Right_Ankle_Control_Roll (0., 0., 0.);
					Right_Ankle_Control_Pitch(0., 0., 0.);
				}
			}

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
*/			
			FiveKG_R_Flag = 0;
			LandROK_Flag = 0;
			Delay_LO_Control_Flag = FALSE;

		} // end of CTRL_mode 3
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandLOK_Flag = 0;		
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//
*/
			if(CTRL_mode == 1) { 
					Delay_LO_Control_Flag = FALSE;
					FiveKG_L_Flag = 0;					

/*
					if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0;}
				
					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}

					Del_Mov_LF_y_Ang_Acc = Old_Del_Mov_LF_y_Ang_Acc - Old_Del_Mov_LF_y_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
					Del_Mov_LF_x_Ang_Acc = Old_Del_Mov_LF_x_Ang_Acc - Old_Del_Mov_LF_x_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/
					Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); //발떨림 제거					
									
					landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					/*
					RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); 
					Land_Damp_RAP = old_Land_Damp_RAP - old_Land_Damp_RAP*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));

					if(pSharedMemory->Int_CNT > pSharedMemory->Step_time){

							if(landRF_CNT == 10) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch
						
							if(landRF_CNT >= 10) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 + 8))) ;

							if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
							if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
					}
					*/
					if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
					else {
							landRF = landRF_old = landRF_del = 0.;
							land_damp_fwd(0.,0.,0,0);
							//Old_Del_Mov_LF_y_Ang_Acc = 0.;
							//Old_Del_Mov_LF_x_Ang_Acc = 0.;
					}
					
					
					landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
					else { //new//
						landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
						LF_land_damp_roll(0.,0.,0,0); //new//
					}//new//
					
					L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
					else {
						L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
						L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds3(0,0,0,0);   
							angle_stiff_fwL(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Left_Ankle_Control_Roll(0., 0., 0.);
							Left_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_LAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_LAP = Land_Damp_LAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_LHip_r = 0.;
			//Del_Mov_LHip_p = 0.;
			Del_Mov_RHip_r = 0.;
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_LF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_LF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_LF_x_Ang_Acc > 2) Del_LF_x_Ang_Acc = 2.0;
				else if(Del_LF_x_Ang_Acc < -2) Del_LF_x_Ang_Acc = -2.0;

				if(Del_LF_y_Ang_Acc > 2) Del_LF_y_Ang_Acc = 2.0;
				else if(Del_LF_y_Ang_Acc < -2) Del_LF_y_Ang_Acc = -2.0;
				
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}
			
			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_LF_Ang_Acc); 
			Del_Mov_LF_x_Ang_Acc = 1.0*Del_LF_x_Ang_Acc*temp_Del_LF_Ang_Acc;
			Del_Mov_LF_y_Ang_Acc = 1.0*Del_LF_y_Ang_Acc*temp_Del_LF_Ang_Acc;
			Old_Del_Mov_LF_y_Ang_Acc = Del_Mov_LF_y_Ang_Acc;
			Old_Del_Mov_LF_x_Ang_Acc = Del_Mov_LF_x_Ang_Acc;
*/

			if(LandLOK_Flag == 0) {
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
					landLF_old = landLF;
					landLF_del = (float)(0. - landLF);
					landLF_CNT = 0;

					landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landLF_r_old = landLF_r; //new//
					landLF_r_del = (float)(0. - landLF_r); //new//
					landLF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_RAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_RAP = Land_Damp_RAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_RHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			Del_Mov_LHip_r = 0.; 
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
				
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_RF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_RF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_RF_x_Ang_Acc > 2) Del_RF_x_Ang_Acc = 2.0;
				else if(Del_RF_x_Ang_Acc < -2) Del_RF_x_Ang_Acc = -2.0;

				if(Del_RF_y_Ang_Acc > 2) Del_RF_y_Ang_Acc = 2.0;
				else if(Del_RF_y_Ang_Acc < -2) Del_RF_y_Ang_Acc = -2.0;
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}

			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_RF_Ang_Acc); 
			Del_Mov_RF_x_Ang_Acc = 1.0*Del_RF_x_Ang_Acc*temp_Del_RF_Ang_Acc;
			Del_Mov_RF_y_Ang_Acc = 1.0*Del_RF_y_Ang_Acc*temp_Del_RF_Ang_Acc;
			Old_Del_Mov_RF_y_Ang_Acc = Del_Mov_RF_y_Ang_Acc;
			Old_Del_Mov_RF_x_Ang_Acc = Del_Mov_RF_x_Ang_Acc;

			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
		
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0;	//new//		

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
					landRF_old = landRF;
					landRF_del = (float)(0. - landRF);
					landRF_CNT = 0;

					landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landRF_r_old = landRF_r; //new//
					landRF_r_del = (float)(0. - landRF_r); //new//
					landRF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			//Del_Mov_LHip_p = 0.;
			
			
			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
			}

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);
				
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landRF = landLF = 0; //new//
				landRF_r = landLF_r = 0; //new//
			}
			
		}

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 2 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 4 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_L_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_R_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}

		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
		
				//pSharedMemory->theta[RSY] = WLK_RDY_LRSY  + WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				///pSharedMemory->theta[LSY] = -WLK_RDY_LRSY  - WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));

				v_AngArm[1] = (float)(WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				v_AngArm[5] = (float)(-WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
			
			if(pSharedMemory->Motion_State != 6){
				
				BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
				BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
				old_BC_y_ZMP_CON = BC_y_ZMP_CON;
				old_BC_x_ZMP_CON = BC_x_ZMP_CON;
				BC_x_ZMP_CON_CNT = 0;
			}
			else{
					BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					SSP_ZMP_CON_Y(0,0,0);
					SSP_ZMP_CON_X(0,0,0);

					if(BC_x_ZMP_CON_CNT < 50) BC_x_ZMP_CON_CNT++;
			}
		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd - 0.0f,1));
		}

		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;


		pSharedMemory->R_px = - pSharedMemory->BC_x ;
		pSharedMemory->L_px = - pSharedMemory->BC_x ;
	
		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footRy);// - DSP_temp_4;
		pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footLy);// + DSP_temp_3;

		//if(pSharedMemory->Gesture_Flag == 0){
	//		Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
	//	}
		//Equi_Adj_Lfoot_Z_Walking = Equi_Adj_Rfoot_Z_Walking = Equi_Adj_LRAP_Walking = 0.;

		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;

		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;
		
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	
		
		
		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
} // End of else if(pSharedMemory->Walk_L_Side_Flag && WLK_RDY_MODE == 1){ // Walk Foward with Left Foot Starting


void Right_Side_Walking()
{
	static unsigned char kirk_i;
	
	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			pSharedMemory->theta[RHY] = 0.;
			pSharedMemory->theta[LHY] = 0.;

			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;
			
			Delay_LO_Control_Flag = FALSE;
			Path_Local_CNT = 0;
			Damping_control_init();
			Landing_control_init();

			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;

			BC_x_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;

			abs_footLy = abs_footLy_old = temp_abs_footLy_1 = temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = 0;

			abs_footRy = abs_footRy_old = temp_abs_footRy_1 = temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = 0;

			abs_hipy = abs_hipy_old = temp_abs_hipy = 0.;
			abs_hipy_CNT = 1;

			rel_footRy = rel_footLy = 0.;

			pSharedMemory->Walking_Stop_Flag_2 = 0;
		
			LF_More_Strech_old = RF_More_Strech_old = LF_More_Strech = RF_More_Strech = 0.;

			pSharedMemory->Motion_State = 2; // R-side
		}

	if(pSharedMemory->Walking_Stop_Flag == 0){

		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // RF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[0]);  // 오른 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if((Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2) && (temp_BC_Walk_Mov_Y < 0)) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;
	}
	else{   // STOP 일 경우 
			
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == 1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == 1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// RF
				temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[0];
				// LF
				temp_LF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = (pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 && kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	

		// Abs_LF_Y
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLy_1,pSharedMemory->Int_CNT,(abs_footLy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLy_2,pSharedMemory->Int_CNT,(abs_footLy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	
		}
		else abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	 
		
		if(LF_half_cyclDN_Status == 2 )  {
			abs_footLy_old = abs_footLy;
			temp_abs_footLy_1 = 0.;
			temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = abs_footLy_CNT+2;
		}

		// Abs_RF_Y
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRy_1,pSharedMemory->Int_CNT,abs_footRy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRy_2,pSharedMemory->Int_CNT,abs_footRy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
				abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 
		}
		else	abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 

		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRy_old = abs_footRy;
			temp_abs_footRy_1 = 0.;
			temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = abs_footRy_CNT+2;
		}

		if(CTRL_mode != 5){
			abs_hipy_status = delayhalf1_cosdelay(3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
			//abs_hipy_status = delayhalf1_cosdelay(-3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
		}
	
		abs_hipy = pSharedMemory->Side_Step_Length*temp_abs_hipy + abs_hipy_old;

		if(abs_hipy_status == 2){
			abs_hipy_old = abs_hipy;
			temp_abs_hipy = 0.;
			abs_hipy_CNT = abs_hipy_CNT + 2;
		}

		rel_footRy =  abs_hipy - abs_footRy ; 
		rel_footLy =  abs_hipy - abs_footLy ;

		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0){
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){

			LandLOK_Flag = 0;
			FiveKG_L_Flag = 0;
			
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;

			if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0.;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
			*/

			landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); // 발 떨림 제거
			/*
			RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));

			
			
			if(landRF_CNT == 20) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

			if(landRF_CNT >= 20) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

			if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
			*/
			if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
			else {
				landRF = landRF_old = landRF_del = 0.;
				land_damp_fwd(0.,0.,0,0);
			}

			landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
			else { //new//
				landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
			} //new//
			
			
			 
			L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
			else {
				L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
				L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds3(0,0,0,0);   
					angle_stiff_fwL(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Left_Ankle_Control_Roll(0., 0., 0.);
					Left_Ankle_Control_Pitch(0., 0., 0.);
				}
			}

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}

			/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//			
			*/
		}
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandROK_Flag = 0;		
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
			/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
			*/

			if(CTRL_mode == 1) { 
					FiveKG_R_Flag = 0;
					
					/*
					OR_x = abs_footRx - abs_footLx ;
					OL_x = 0.;
								
					if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0.;}

					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}
					*/
					
					landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발 떨림 제거
					/*
					LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

					if(landLF_CNT == 20) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

					if(landLF_CNT >= 20) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

					if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
					if(landLF_CNT >= 15) landLF_Tilt_R = -0.3*temp_LF_TILT_R;
					*/

					if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
					else {
						landLF = landLF_old = landLF_del = 0.;
						land_damp_fwd(0.,0.,0,0);
					}

					landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
					else { //new//
						landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
						RF_land_damp_roll(0.,0.,0,0); //new//
					}//new//

										
					R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
					else {
						R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
						R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds4(0,0,0,0);   
							angle_stiff_fwR(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Right_Ankle_Control_Roll(0., 0., 0.);
							Right_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
			/*
			OR_x = abs_footRx - abs_footLx ;
			OL_x = 0.;
			*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_LFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0);
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0; //new//

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
					
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;
			*/			
			Del_Mov_LHip_r = 0.;
			Del_Mov_RHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_RFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandLOK_Flag == 0) {	
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0);
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0;	//new//	

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			OL_x = 0.;
			OR_x = 0.;
			Ref_Xzmp_Con_0 = 10.;


			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			
			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
			}
			

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);  

				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landLF = landRF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
			//	DeltaMov_x = - 0.9*dsp_compen_p(Err_Xzmp,1); // P Controller
		} // End of Damping Controller Switching	

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 4 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 2 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_R_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_L_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
			
				//pSharedMemory->theta[RSY] = WLK_RDY_LRSY  + WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				//pSharedMemory->theta[LSY] = -WLK_RDY_LRSY  - WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));

				v_AngArm[1] = (float)(WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				v_AngArm[5] = (float)(-WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
			
			if(pSharedMemory->Motion_State != 6){
			
				BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
				BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
				old_BC_y_ZMP_CON = BC_y_ZMP_CON;
				old_BC_x_ZMP_CON = BC_x_ZMP_CON;
				BC_x_ZMP_CON_CNT = 0;
			}
			else{
					BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
					SSP_ZMP_CON_Y(0,0,0);
					SSP_ZMP_CON_X(0,0,0);

					if(BC_x_ZMP_CON_CNT < 50) BC_x_ZMP_CON_CNT++;
			}
		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd - 0.0f,1));
		}
	
		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;

		pSharedMemory->R_px = - pSharedMemory->BC_x ;
		pSharedMemory->L_px = - pSharedMemory->BC_x ;
		

		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footRy);// - DSP_temp_4;
		pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footLy);// + DSP_temp_3;

		//if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
	//		Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
	//	}
		//Equi_Adj_Lfoot_Z_Walking = Equi_Adj_Rfoot_Z_Walking = Equi_Adj_LRAP_Walking = 0.;

		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;
		
		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;
		
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	
		

		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
} // End of else if(pSharedMemory->Walk_R_Side_Flag && WLK_RDY_MODE == 1 ){ // Go Forward with Right Foot Starting

void Left_Turn_Walking()
{
	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			//pSharedMemory->theta[RHY] = 0.;
			//pSharedMemory->theta[LHY] = 0.;

			
			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;
			Delay_LO_Control_Flag = FALSE;
			Path_Local_CNT = 0;
			Damping_control_init();
			Landing_control_init();
			
			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;

			BC_x_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;
			
			abs_footLy = abs_footLy_old = temp_abs_footLy_1 = temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = 0;

			abs_footRy = abs_footRy_old = temp_abs_footRy_1 = temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = 0;

			abs_hipy = abs_hipy_old = temp_abs_hipy = 0.;
			abs_hipy_CNT = 1;

			rel_footRy = rel_footLy = 0.;

			temp_LRHY_1 = temp_LRHY_2 = 0.; // 회전 관련
			LRHY_CNT = 0; // 회전 관련

			pSharedMemory->Walking_Stop_Flag_2 = 0;	
			

			pSharedMemory->Motion_State = 5; // CCW
		}

	if(pSharedMemory->Walking_Stop_Flag == 0 ){
	
		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // LF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[0]);  // 왼 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if((Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2) && (temp_BC_Walk_Mov_Y > 0)) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;

	}
	else{   // STOP 일 경우 
		
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == -1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == -1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// LF
				temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[0];
				// RF
				temp_RF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = -(pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 &&  kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	
		
		// Abs_LF_Y
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLy_1,pSharedMemory->Int_CNT,abs_footLy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLy_2,pSharedMemory->Int_CNT,abs_footLy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	
		}
		else abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	 
		
		if(LF_half_cyclDN_Status == 2 )  {
			abs_footLy_old = abs_footLy;
			temp_abs_footLy_1 = 0.;
			temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = abs_footLy_CNT+2;
		}

		// Abs_RF_Y
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRy_1,pSharedMemory->Int_CNT,(abs_footRy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRy_2,pSharedMemory->Int_CNT,(abs_footRy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
				abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 
		}
		else	abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 

		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRy_old = abs_footRy;
			temp_abs_footRy_1 = 0.;
			temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = abs_footRy_CNT+2;
		}
		
		// Abs_Hip_Y
		if(CTRL_mode != 5){
			abs_hipy_status = delayhalf1_cosdelay(3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)- pSharedMemory->Delay_time,pSharedMemory->Step_time);
		}
	
		abs_hipy = pSharedMemory->Side_Step_Length*temp_abs_hipy + abs_hipy_old;

		if(abs_hipy_status == 2){
			abs_hipy_old = abs_hipy;
			temp_abs_hipy = 0.;
			abs_hipy_CNT = abs_hipy_CNT +2;
		}

		rel_footRy = abs_footRy - abs_hipy ; 
		rel_footLy = abs_footLy - abs_hipy ;

		if(CTRL_mode != 5 || LRHY_status != 4){
			PROF_ftn_1_cos(pSharedMemory->Int_CNT, LRHY_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_1);
			LRHY_status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,LRHY_CNT*pSharedMemory->Step_time + pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 2*10,0,0,0,0,&temp_LRHY_2);
		}

		if(LRHY_status == 4){
			temp_LRHY_1 = temp_LRHY_2 = 0.;
			LRHY_CNT = LRHY_CNT + 2;
		}

		pSharedMemory->theta[RHY] = -pSharedMemory->Turning_Angle*(temp_LRHY_1 - temp_LRHY_2);
		pSharedMemory->theta[LHY] = pSharedMemory->Turning_Angle*(temp_LRHY_1 - temp_LRHY_2);


		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0)	{
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){
/*
			if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;

			Del_Mov_RF_y_Ang_Acc = Old_Del_Mov_RF_y_Ang_Acc - Old_Del_Mov_RF_y_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
			Del_Mov_RF_x_Ang_Acc = Old_Del_Mov_RF_x_Ang_Acc - Old_Del_Mov_RF_x_Ang_Acc*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

*/
			Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발떨림 제거
			landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
/*			LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8))); 
			Land_Damp_LAP = old_Land_Damp_LAP - old_Land_Damp_LAP*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

			if(landLF_CNT == 10) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch

			if(landLF_CNT >= 10) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 +8)));

			if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landLF_CNT >= 15)  landLF_Tilt_R = - 0.3*temp_LF_TILT_R;
*/
			if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
			else {
					landLF = landLF_old = landLF_del = 0.;
					land_damp_fwd(0.,0.,0,0);
					//Old_Del_Mov_RF_y_Ang_Acc = 0.;
					//Old_Del_Mov_RF_x_Ang_Acc = 0.;
			}
			
		
			landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
			else { //new//
				landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
			} //new//

			 
			R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
			else {
				R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
				R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds4(0,0,0,0);   
					angle_stiff_fwR(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Right_Ankle_Control_Roll(0., 0., 0.);
					Right_Ankle_Control_Pitch(0., 0., 0.);
				}

			}

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
*/			
			FiveKG_R_Flag = 0;
			LandROK_Flag = 0;
			Delay_LO_Control_Flag = FALSE;

		} // end of CTRL_mode 3
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandLOK_Flag = 0;		
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//
*/
			if(CTRL_mode == 1) { 
					Delay_LO_Control_Flag = FALSE;
					FiveKG_L_Flag = 0;					

/*
					if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0;}
				
					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}

					Del_Mov_LF_y_Ang_Acc = Old_Del_Mov_LF_y_Ang_Acc - Old_Del_Mov_LF_y_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); // Compensation from angular acceleration
					Del_Mov_LF_x_Ang_Acc = Old_Del_Mov_LF_x_Ang_Acc - Old_Del_Mov_LF_x_Ang_Acc*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));
*/					
					Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); //발떨림 제거					
					landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
/*					RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8))); 
					Land_Damp_RAP = old_Land_Damp_RAP - old_Land_Damp_RAP*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));

					if(pSharedMemory->Int_CNT > pSharedMemory->Step_time){

							if(landRF_CNT == 10) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화 Pitch
						
							if(landRF_CNT >= 10) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 10)/(pSharedMemory->Up_time/2 - 10 + 8))) ;

							if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
							if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
					}
*/
					if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
					else {
							landRF = landRF_old = landRF_del = 0.;
							land_damp_fwd(0.,0.,0,0);
							//Old_Del_Mov_LF_y_Ang_Acc = 0.;
							//Old_Del_Mov_LF_x_Ang_Acc = 0.;
					}
					
					
					landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
					else { //new//
						landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
						LF_land_damp_roll(0.,0.,0,0); //new//
					}//new//

					L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
					else {
						L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
						L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds3(0,0,0,0);   
							angle_stiff_fwL(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Left_Ankle_Control_Roll(0., 0., 0.);
							Left_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_LAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_LAP = Land_Damp_LAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_LHip_r = 0.;
			//Del_Mov_LHip_p = 0.;
			Del_Mov_RHip_r = 0.;
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_LF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_LF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_LF_x_Ang_Acc > 2) Del_LF_x_Ang_Acc = 2.0;
				else if(Del_LF_x_Ang_Acc < -2) Del_LF_x_Ang_Acc = -2.0;

				if(Del_LF_y_Ang_Acc > 2) Del_LF_y_Ang_Acc = 2.0;
				else if(Del_LF_y_Ang_Acc < -2) Del_LF_y_Ang_Acc = -2.0;
				
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}
			
			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_LF_Ang_Acc); 
			Del_Mov_LF_x_Ang_Acc = 1.0*Del_LF_x_Ang_Acc*temp_Del_LF_Ang_Acc;
			Del_Mov_LF_y_Ang_Acc = 1.0*Del_LF_y_Ang_Acc*temp_Del_LF_Ang_Acc;
			Old_Del_Mov_LF_y_Ang_Acc = Del_Mov_LF_y_Ang_Acc;
			Old_Del_Mov_LF_x_Ang_Acc = Del_Mov_LF_x_Ang_Acc;
*/

			if(LandLOK_Flag == 0) {
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0); // pitch 방향  L.O Control	//modi//
					landLF_old = landLF;
					landLF_del = (float)(0. - landLF);
					landLF_CNT = 0;

					landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landLF_r_old = landLF_r; //new//
					landLF_r_del = (float)(0. - landLF_r); //new//
					landLF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				Land_Damp_RAP = 0.5*LAND_DAMP_ANG*temp_Gesture_Pelvis_1;
				old_Land_Damp_RAP = Land_Damp_RAP;
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
*/
			Del_Mov_RHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			Del_Mov_LHip_r = 0.; 
/*
			// Angular Velocity Measuring 
			if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2){
				temp1_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp1_Ang_Vel_r = 0.21*Roll_x_g_1_lp;
				
			}
			else if(Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2){
				temp2_Ang_Vel_p = 0.21*Pit_x_g_1_lp;
				temp2_Ang_Vel_r = 0.21*Roll_x_g_1_lp;

				Ang_Acc_p = (temp2_Ang_Vel_p - temp1_Ang_Vel_p)/0.02;
				Ang_Acc_r = (temp2_Ang_Vel_r - temp1_Ang_Vel_r)/0.02;

				Del_RF_x_Ang_Acc = -0.5*Ang_Acc_p/12.1053; 
				Del_RF_y_Ang_Acc = 0.5*(Ang_Acc_r/12.1053)*0.8;
				
				if(Del_RF_x_Ang_Acc > 2) Del_RF_x_Ang_Acc = 2.0;
				else if(Del_RF_x_Ang_Acc < -2) Del_RF_x_Ang_Acc = -2.0;

				if(Del_RF_y_Ang_Acc > 2) Del_RF_y_Ang_Acc = 2.0;
				else if(Del_RF_y_Ang_Acc < -2) Del_RF_y_Ang_Acc = -2.0;
			}
			else {Ang_Acc_p = 0.; Ang_Acc_r = 0.;}

			PROF_ftn_1_cos(Path_Local_CNT,(pSharedMemory->Up_time/2 - pSharedMemory->Delay_time)/2 + 2,0,pSharedMemory->Up_time/2 - pSharedMemory->Delay_time - 5,1,0,0,&temp_Del_RF_Ang_Acc); 
			Del_Mov_RF_x_Ang_Acc = 1.0*Del_RF_x_Ang_Acc*temp_Del_RF_Ang_Acc;
			Del_Mov_RF_y_Ang_Acc = 1.0*Del_RF_y_Ang_Acc*temp_Del_RF_Ang_Acc;
			Old_Del_Mov_RF_y_Ang_Acc = Del_Mov_RF_y_Ang_Acc;
			Old_Del_Mov_RF_x_Ang_Acc = Del_Mov_RF_x_Ang_Acc;

			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
	
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0;	//new//		

			}
			else {
				
				if(Delay_LO_Control_Flag){
					landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0); //modi//
					landRF_old = landRF;
					landRF_del = (float)(0. - landRF);
					landRF_CNT = 0;

					landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
					landRF_r_old = landRF_r; //new//
					landRF_r_del = (float)(0. - landRF_r); //new//
					landRF_r_CNT = 0; //new//
				}
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			//Del_Mov_RHip_p = 0.;
			//Del_Mov_LHip_p = 0.;
			
			
			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
			}

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);
				
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landRF = landLF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
			
		}
		
		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 2 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 4 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_L_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_R_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
			if(!pSharedMemory->Walking_Gesture_Flag){
				//pSharedMemory->theta[RSY] = WLK_RDY_LRSY  + WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				//pSharedMemory->theta[LSY] = -WLK_RDY_LRSY  - WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));

				v_AngArm[1] = (float)(WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				v_AngArm[5] = (float)(-WLKING_LRSY*(-pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
			}

			if(pSharedMemory->Motion_State != 6){
				
				BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
				BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
				old_BC_y_ZMP_CON = BC_y_ZMP_CON;
				old_BC_x_ZMP_CON = BC_x_ZMP_CON;
				BC_x_ZMP_CON_CNT = 0;
			}
			else{
				BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
				BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
				SSP_ZMP_CON_Y(0,0,0);
				SSP_ZMP_CON_X(0,0,0);
				
				if(BC_x_ZMP_CON_CNT < 50) BC_x_ZMP_CON_CNT++;
			}

		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd - 0.0f,1));
		}

		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;

		pSharedMemory->R_px = - pSharedMemory->BC_x ;
		pSharedMemory->L_px = - pSharedMemory->BC_x ;
	
		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footRy);// - DSP_temp_4;
		pSharedMemory->L_py = (float)( L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footLy);// + DSP_temp_3;

		//if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
		//	Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
		//}
		

		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;


		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;
		
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	

	
		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
} // End of else if(pSharedMemory->Walk_CCW_Turn_Flag && WLK_RDY_MODE == 1)

void Right_Turn_Walking()
{
	static unsigned char kirk_i;

	if(pSharedMemory->Int_CNT == 0){ // 변수 초기화 
			for(int j=0;j<MAX_STEP_NUM;j++) { BC_Walk_Mov_Y[j] = LF_Walk_Mov_Z[j] = RF_Walk_Mov_Z[j] = 0.;}
			
			//pSharedMemory->theta[RHY] = 0.;
			//pSharedMemory->theta[LHY] = 0.;

			
			RF_Landing_PosCon_Flag = LF_Landing_PosCon_Flag = 0;
			Delay_LO_Control_Flag = FALSE;
			Path_Local_CNT = 0;
			Damping_control_init();
			Landing_control_init();

			Temp_Inc_Sum = 0.0f;
			Temp_Inc_Sum_CNT = 0;
			Inc_Avg = 0.0f;

			Del_Mov_RHip_r = 0.0f;
			Del_Mov_LHip_r = 0.0f;

			BC_x_ZMP_CON_CNT = 0;
			old_BC_y_ZMP_CON = old_BC_x_ZMP_CON = 0;

			abs_footLy = abs_footLy_old = temp_abs_footLy_1 = temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = 0;

			abs_footRy = abs_footRy_old = temp_abs_footRy_1 = temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = 0;

			abs_hipy = abs_hipy_old = temp_abs_hipy = 0.;
			abs_hipy_CNT = 1;

			rel_footRy = rel_footLy = 0.;

			temp_LRHY_1 = temp_LRHY_2 = 0.;
			LRHY_CNT = 0;

			pSharedMemory->Walking_Stop_Flag_2 = 0;
		
			pSharedMemory->Motion_State = 4; // CW
		}

	if(pSharedMemory->Walking_Stop_Flag == 0){

		if(pSharedMemory->Path_Area_CNT==0){
			Path_Local_CNT = pSharedMemory->Int_CNT;
		    // RF
			PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Upstart_time,0,pSharedMemory->Step_time,1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[0]);  // 오른 다리  Lift
			
			 //BC
			PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,0+10,pSharedMemory->Step_time-10,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[0]); // BC Shift
			if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0;*/}
			
			if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 0;
			else CTRL_mode = 1;

		}
		else{
			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT; 

			if(pSharedMemory->Path_Area_CNT%2 == 1)	{
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				
				if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
				else CTRL_mode = 3;			 
			}
			else {
				//RF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(pSharedMemory->Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			
				//LF
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[pSharedMemory->Path_Area_CNT]);			

				if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
				else CTRL_mode = 1;
			}
				
				// BC
				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*pSharedMemory->Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[pSharedMemory->Path_Area_CNT]);
				if(PROF_Status == 4) {pSharedMemory->Path_Area_CNT++; /*Path_Local_CNT = 0 ;*/}			

		}

		temp_Path_Area_CNT = pSharedMemory->Path_Area_CNT ;
		
		if(temp_BC_Walk_Mov_Y > 0) Walk_Motion_Mode = 1;
		else if(temp_BC_Walk_Mov_Y < 0)	Walk_Motion_Mode = -1; 
		else Walk_Motion_Mode = 0;

		if((Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2) && (temp_BC_Walk_Mov_Y < 0)) pSharedMemory->Walking_Stop_Flag_2 = 1;
		else pSharedMemory->Walking_Stop_Flag_2 = 0;
	}
	else{   // STOP 일 경우 
			
			pSharedMemory->Path_Area_CNT = temp_Path_Area_CNT+1;

			Path_Local_CNT = pSharedMemory->Int_CNT - pSharedMemory->Step_time*temp_Path_Area_CNT; 

			if(Walk_Motion_Mode == 1){
				if(temp_Path_Area_CNT%2 == 1)	{
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			

					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			}
			else {				
				if(temp_Path_Area_CNT%2 == 1)	{
					//LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					//RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Step_time - ((pSharedMemory->Up_time/2)+pSharedMemory->Delay_time)) CTRL_mode = 2;
					else CTRL_mode = 3;	
				}
				else {
					// LF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,pSharedMemory->Step_time - ((pSharedMemory->Up_time/2) - pSharedMemory->Delay_time),0,&LF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1)+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+2),1,2*pSharedMemory->Delay_time,0,&LF_Walk_Mov_Z[temp_Path_Area_CNT+1]);			
					// RF
					PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT+pSharedMemory->Upstart_time,0,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),1,2*pSharedMemory->Delay_time,0,&RF_Walk_Mov_Z[temp_Path_Area_CNT]);			
					if(Path_Local_CNT < pSharedMemory->Upstart_time) CTRL_mode = 4;
					else CTRL_mode = 1;
				}
			} // END of if(Walk_Motion_Mode == 1)

				PROF_Status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*temp_Path_Area_CNT,pSharedMemory->Step_time,0,0,2*pSharedMemory->Delay_time,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT]);
								
				PROF_ftn_1_cos(pSharedMemory->Int_CNT,pSharedMemory->Step_time*(temp_Path_Area_CNT+1),pSharedMemory->Step_time,0,0,30,0,&BC_Walk_Mov_Y[temp_Path_Area_CNT+1]);
				
				//Path_Local_CNT++;
				if(PROF_Status == 4)  { 
					Path_Local_CNT = 0 ; 
					CTRL_mode = 5;
				}
				
	} // End of 	else{   // STOP 일 경우 


		for(kirk_i=0;kirk_i<pSharedMemory->Path_Area_CNT+1;kirk_i++) {	// 각 Path 구간의 amp. 지정 		
			
			if(kirk_i==0){ // 첫걸음 
				// RF
				temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[0];
				// LF
				temp_LF_Walk_Mov_Z =  0.;
				//BC
				temp_BC_Walk_Mov_Y = (pSharedMemory->Walk_BC_Ydir_Amp/2)*BC_Walk_Mov_Y[0];
		
			}
			else if(pSharedMemory->Walking_Stop_Flag == 1 && kirk_i == pSharedMemory->Path_Area_CNT) {
				
				if(kirk_i%2 == 1) { // 홀수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  (float)(-pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
				else{  // 짝수일 경우 
					// RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					// LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					// BC
					temp_BC_Walk_Mov_Y = (float)(pSharedMemory->Walk_BC_Ydir_Amp/2.*BC_Walk_Mov_Y[kirk_i]);
				}
			}
			else{ // 두번째 걸음부터 STOP  전까지  
				// LF
				if(kirk_i%2 == 1) { // 홀수일 경우  
					//RF
					temp_RF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
					//BC
					temp_BC_Walk_Mov_Y =  -pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}
				else{   // 짝수일 경우 
					//RF
					temp_RF_Walk_Mov_Z =  pSharedMemory->Walk_Foot_Zdir_Amp*RF_Walk_Mov_Z[kirk_i];
					//LF
					temp_LF_Walk_Mov_Z =  -pSharedMemory->Walk_Foot_Zdir_Amp*LF_Walk_Mov_Z[kirk_i];
                    //BC
					temp_BC_Walk_Mov_Y = pSharedMemory->Walk_BC_Ydir_Amp*BC_Walk_Mov_Y[kirk_i];
				}				
			}

			pSharedMemory->BC_y += temp_BC_Walk_Mov_Y;
			DelMov_LF_Walk_Z += temp_LF_Walk_Mov_Z;
			DelMov_RF_Walk_Z += temp_RF_Walk_Mov_Z;
		} // End of for(i=0;i<pSharedMemory->Path_Area_CNT+1;i++) {	

		// Abs_LF_Y
		if(CTRL_mode != 5 || DelMov_LF_Walk_Z > 0){
			LF_half_cyclUP_Status = half_cyclUP(&temp_abs_footLy_1,pSharedMemory->Int_CNT,(abs_footLy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			LF_half_cyclDN_Status = half_cyclDN(&temp_abs_footLy_2,pSharedMemory->Int_CNT,(abs_footLy_CNT+1)*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == -1){
			abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	
		}
		else abs_footLy = pSharedMemory->Side_Step_Length*(temp_abs_footLy_1 + temp_abs_footLy_2) + abs_footLy_old;	 
		
		if(LF_half_cyclDN_Status == 2 )  {
			abs_footLy_old = abs_footLy;
			temp_abs_footLy_1 = 0.;
			temp_abs_footLy_2 = 0.;
			abs_footLy_CNT = abs_footLy_CNT+2;
		}

		// Abs_RF_Y
		if(CTRL_mode != 5 || DelMov_RF_Walk_Z > 0){
			RF_half_cyclUP_Status = half_cyclUP(&temp_abs_footRy_1,pSharedMemory->Int_CNT,abs_footRy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time,pSharedMemory->Up_time/2);
			RF_half_cyclDN_Status = half_cyclDN(&temp_abs_footRy_2,pSharedMemory->Int_CNT,abs_footRy_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + pSharedMemory->Up_time/2,pSharedMemory->Up_time/2);
		}
		
		if(pSharedMemory->Walking_Stop_Flag == 1 && Walk_Motion_Mode == 1){
				abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 
		}
		else	abs_footRy = pSharedMemory->Side_Step_Length*(temp_abs_footRy_1 + temp_abs_footRy_2) + abs_footRy_old;	 

		if(RF_half_cyclDN_Status == 2 )  {
			abs_footRy_old = abs_footRy;
			temp_abs_footRy_1 = 0.;
			temp_abs_footRy_2 = 0.;
			abs_footRy_CNT = abs_footRy_CNT+2;
		}

		if(CTRL_mode != 5){
			abs_hipy_status = delayhalf1_cosdelay(3,&temp_abs_hipy,1.0,pSharedMemory->Int_CNT,pSharedMemory->Step_time*(abs_hipy_CNT)-pSharedMemory->Delay_time,pSharedMemory->Step_time);
		}
	
		abs_hipy = pSharedMemory->Side_Step_Length*temp_abs_hipy + abs_hipy_old;

		if(abs_hipy_status == 2){
			abs_hipy_old = abs_hipy;
			temp_abs_hipy = 0.;
			abs_hipy_CNT = abs_hipy_CNT + 2;
		}

		rel_footRy =  abs_hipy - abs_footRy ; 
		rel_footLy =  abs_hipy - abs_footLy ;

		
		if(CTRL_mode != 5 || LRHY_status != 4){
			PROF_ftn_1_cos(pSharedMemory->Int_CNT, LRHY_CNT*pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 10*2,0,0,0,0,&temp_LRHY_1);
			LRHY_status = PROF_ftn_1_cos(pSharedMemory->Int_CNT,LRHY_CNT*pSharedMemory->Step_time + pSharedMemory->Step_time + pSharedMemory->Upstart_time + 10,pSharedMemory->Up_time - 10*2,0,0,0,0,&temp_LRHY_2);
		}

		if(LRHY_status == 4){
			temp_LRHY_1 = temp_LRHY_2 = 0.;
			LRHY_CNT = LRHY_CNT + 2;
		}

		pSharedMemory->theta[RHY] = -pSharedMemory->Turning_Angle*(temp_LRHY_1 - temp_LRHY_2);
		pSharedMemory->theta[LHY] = pSharedMemory->Turning_Angle*(temp_LRHY_1 - temp_LRHY_2);

		//  Angle Roll Compensation 
		if(pSharedMemory->BC_y < 0)	{
			DelMov_RAR = (float)(pSharedMemory->Amp_ankleR*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_LAR = 0.;
		}
		else {
			DelMov_LAR = (float)(pSharedMemory->Amp_ankleL*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
			DelMov_RAR = 0.;
		}

		// Damping Controller Switching	
		if(CTRL_mode == 3){

			LandLOK_Flag = 0;
			FiveKG_L_Flag = 0;
			
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;

			if(landRF_CNT == 10) {landLF_Tilt = 0.;	landLF_Tilt_R = 0.;}

			Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
*/
			landRF = (float)(landRF_old + landRF_del*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			Del_Mov_LHip_r = (float)(LHIP_VIB_GAIN*pSharedMemory->LF_TILT_R); // 발 떨림 제거
/*			RF_More_Strech = RF_More_Strech_old - RF_More_Strech_old*0.5*(1.-cos(PI*landRF_CNT/(pSharedMemory->Up_time/2 + 8)));

			if(landRF_CNT == 20) temp_RF_TILT_P = pSharedMemory->RF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

			if(landRF_CNT >= 20) landRF_Tilt = 0.5*temp_RF_TILT_P*0.5*(1.-cos(PI*(landRF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

			if(landRF_CNT == 15) temp_RF_TILT_R = pSharedMemory->RF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
			if(landRF_CNT >= 15) landRF_Tilt_R = -0.3*temp_RF_TILT_R;
*/
			if(landRF_CNT < (pSharedMemory->Up_time/2 + 8))  landRF_CNT++;
			else {
				landRF = landRF_old = landRF_del = 0.;
				land_damp_fwd(0.,0.,0,0);
			}

			landLF_r = (float)(landLF_r_old + landLF_r_del*0.5*(1.-cos(PI*landLF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
			if(landLF_r_CNT < (pSharedMemory->Up_time/2))  landLF_r_CNT++; //new//
			else { //new//
				landLF_r = landLF_r_old = landLF_r_del = 0.; //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
			} //new//
			
			
			 
			L_theta_compen_r = (float)(L_theta_compen_r_old + L_theta_compen_r_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			L_theta_compen_p = (float)(L_theta_compen_p_old + L_theta_compen_p_del*0.5*(1.-cos(PI*L_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
			if(L_theta_compen_CNT < (pSharedMemory->Up_time/2))  L_theta_compen_CNT++;
			else {
				L_theta_compen_r = L_theta_compen_r_old = L_theta_compen_r_del = 0.;
				L_theta_compen_p = L_theta_compen_p_old = L_theta_compen_p_del = 0.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					angle_stiff_ds3(0,0,0,0);   
					angle_stiff_fwL(0,0,0,0);
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					Left_Ankle_Control_Roll(0., 0., 0.);
					Left_Ankle_Control_Pitch(0., 0., 0.);
				}
			}

			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
				R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}

			/*
			if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{     //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
			} //new//			
			*/
		}
		else if(CTRL_mode == 0 || CTRL_mode == 1){
			LandROK_Flag = 0;		
	
			if(pSharedMemory->SSP_CTRL_MODE == 1)
			{
				L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
				L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
			}
			else if(pSharedMemory->SSP_CTRL_MODE == 2)
			{
				L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
				L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
			}
			
			/*
			if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{      //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r;  //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
			} //new//
			*/

			if(CTRL_mode == 1) { 
					FiveKG_R_Flag = 0;
					
					/*
					OR_x = abs_footRx - abs_footLx ;
					OL_x = 0.;
								
					if(landLF_CNT == 10) {landRF_Tilt = 0.;	landRF_Tilt_R = 0.;}

					if(pSharedMemory->Int_CNT > 2*pSharedMemory->Step_time)   {
							Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
							old_Gesture_Pelvis_1 = Gesture_Pelvis_1;
					}
*/
					
					landLF = (float)(landLF_old + landLF_del*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)))); 
					Del_Mov_RHip_r = (float)(RHIP_VIB_GAIN*pSharedMemory->RF_TILT_R); // 발 떨림 제거
/*					LF_More_Strech = LF_More_Strech_old - LF_More_Strech_old*0.5*(1.-cos(PI*landLF_CNT/(pSharedMemory->Up_time/2 + 8)));

					if(landLF_CNT == 20) temp_LF_TILT_P = pSharedMemory->LF_TILT_P - Equi_Adj_LRAP_Walking; // 발바닥 경사계를 이용한 안정화

					if(landLF_CNT >= 20) landLF_Tilt = 0.5*temp_LF_TILT_P*0.5*(1.-cos(PI*(landLF_CNT - 20)/(pSharedMemory->Up_time/2 - 20 +8)));

					if(landLF_CNT == 15) temp_LF_TILT_R = pSharedMemory->LF_TILT_R ;// 발바닥 경사계를 이용한 안정화 Roll
						
					if(landLF_CNT >= 15) landLF_Tilt_R = -0.3*temp_LF_TILT_R;
*/
					if(landLF_CNT < (pSharedMemory->Up_time/2 + 8))  landLF_CNT++;
					else {
						landLF = landLF_old = landLF_del = 0.;
						land_damp_fwd(0.,0.,0,0);
					}

					landRF_r = (float)(landRF_r_old + landRF_r_del*0.5*(1.-cos(PI*landRF_r_CNT/(pSharedMemory->Up_time/2)))); //new//
					if(landRF_r_CNT < (pSharedMemory->Up_time/2))  landRF_r_CNT++; //new//
					else { //new//
						landRF_r = landRF_r_old = landRF_r_del = 0.; //new//
						RF_land_damp_roll(0.,0.,0,0); //new//
					}//new//
				
					R_theta_compen_r = (float)(R_theta_compen_r_old + R_theta_compen_r_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					R_theta_compen_p = (float)(R_theta_compen_p_old + R_theta_compen_p_del*0.5*(1.-cos(PI*R_theta_compen_CNT/(pSharedMemory->Up_time/2)))); 
					if(R_theta_compen_CNT < (pSharedMemory->Up_time/2))  R_theta_compen_CNT++;
					else {
						R_theta_compen_r = R_theta_compen_r_old = R_theta_compen_r_del = 0.;
						R_theta_compen_p = R_theta_compen_p_old = R_theta_compen_p_del = 0.;
						
						if(pSharedMemory->SSP_CTRL_MODE == 1)
						{
							angle_stiff_ds4(0,0,0,0);   
							angle_stiff_fwR(0,0,0,0);
						}
						else if(pSharedMemory->SSP_CTRL_MODE == 2)
						{
							Right_Ankle_Control_Roll(0., 0., 0.);
							Right_Ankle_Control_Pitch(0., 0., 0.);
						}
					}
			}
		}
		else if(CTRL_mode == 2){
			/*
			OR_x = abs_footRx - abs_footLx ;
			OL_x = 0.;
			*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_LFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_RFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandROK_Flag == 0) {	
				
				landRF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_RFOOT_My,1,0);
				landRF_old = landRF;
				landRF_del = (float)(0. - landRF);
				landRF_CNT = 0;

				landRF_r = (pSharedMemory->Gain_LO_Con_r)*RF_land_damp_roll(0.,pSharedMemory->NM_RFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landRF_r_old = landRF_r; //new//
				landRF_r_del = (float)(0. - landRF_r); //new//
				landRF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				L_theta_compen_r_old = L_theta_compen_r;
				L_theta_compen_r_del = (float)(0. - L_theta_compen_r);
				L_theta_compen_p_old = L_theta_compen_p;
				L_theta_compen_p_del = (float)(0. - L_theta_compen_p);

				L_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_LAR_Flag = 0; //new//

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_RAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_RAR = R_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_RAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 4){
			/*
			OL_x = abs_footLx - abs_footRx ;
			OR_x = 0.;
			*/
			Del_Mov_LHip_r = 0.;
			Del_Mov_RHip_r = 0.;
/*
			if(Path_Local_CNT <= 30){
				PROF_ftn_1_cos(Path_Local_CNT,0,30,0,0,0,0,&temp_Gesture_Pelvis_1); 
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*temp_Gesture_Pelvis_1;
				Sys_mass_spring_damper(0,0);
				//Sys_mass_spring_damper(0.9*N_RFOOT_Fz_lp - 450.0,1);
			}
			else Gesture_Pelvis_1 = -1.0*1000.*Sys_mass_spring_damper((1.0*N_LFOOT_Fz_lp - SPR_DAMP_THRES),1);
			*/
			if(LandLOK_Flag == 0) {	
				
				landLF = -(pSharedMemory->Gain_LO_Con_p)*land_damp_fwd(0.,pSharedMemory->NM_LFOOT_My,1,0);
				landLF_old = landLF;
				landLF_del = (float)(0. - landLF);
				landLF_CNT = 0;

				landLF_r = (pSharedMemory->Gain_LO_Con_r)*LF_land_damp_roll(0.,pSharedMemory->NM_LFOOT_Mx,1,0); // roll 방향  L.O Control  //new//
				landLF_r_old = landLF_r; //new//
				landLF_r_del = (float)(0. - landLF_r); //new//
				landLF_r_CNT = 0; //new//
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					R_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds4(0.,pSharedMemory->NM_RFOOT_Mx,1,0));
					R_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwR(0.,pSharedMemory->NM_RFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					R_theta_compen_r = (float)(-1.0*ANKLE_GAIN_RR*Right_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					R_theta_compen_p = (float)(-1.0*ANKLE_GAIN_RP*Right_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}

				R_theta_compen_r_old = R_theta_compen_r;
				R_theta_compen_r_del = (float)(0. - R_theta_compen_r);
				R_theta_compen_p_old = R_theta_compen_p;
				R_theta_compen_p_del = (float)(0. - R_theta_compen_p);

				R_theta_compen_CNT = 0;

				//pSharedMemory->Read_Dicson_RAR_Flag = 0;	//new//	

			}
			else {
				//OL_x = (abs_footLx - abs_footRx)/2. ;
				//OR_x = (abs_footRx - abs_footLx)/2.;
				
				if(pSharedMemory->SSP_CTRL_MODE == 1)
				{
					L_theta_compen_r = (float)((DAMP_GAIN_R)*angle_stiff_ds3(0.,pSharedMemory->NM_LFOOT_Mx,1,0));
					L_theta_compen_p = (float)(-1*(DAMP_GAIN_P)*angle_stiff_fwL(0.,pSharedMemory->NM_LFOOT_My,1,0));
				}
				else if(pSharedMemory->SSP_CTRL_MODE == 2)
				{
					L_theta_compen_r = (float)(-1.0*ANKLE_GAIN_LR*Left_Ankle_Control_Roll(RTX_CompenTheta_R, RTX_M_Tilt_Vel_R_LPF, 0.));
					L_theta_compen_p = (float)(-1.0*ANKLE_GAIN_LP*Left_Ankle_Control_Pitch(RTX_CompenTheta_P, RTX_M_Tilt_Vel_P_LPF, 0.));
				}
				
				/*
				if(pSharedMemory->Read_Dicson_LAR_Flag == 0)	{ //new//
					pSharedMemory->Discon_LAR = L_theta_compen_r; //new//
					pSharedMemory->Read_Dicson_LAR_Flag = 1; //new//
				}//new//
				*/
			}
		}
		else if(CTRL_mode == 5){
			/*
			if(SprDamp_CNT <= 20){
				Gesture_Pelvis_1 = old_Gesture_Pelvis_1 - old_Gesture_Pelvis_1*0.5*(1.-cos(PI*SprDamp_CNT/20));
				SprDamp_CNT++;
			}
			else if(SprDamp_CNT == 21) {old_Gesture_Pelvis_1 = Gesture_Pelvis_1 = 0.; temp_Gesture_Pelvis_1 = 0.; Sys_mass_spring_damper(0,0); SprDamp_CNT = 22;}

			OL_x = 0.;
			OR_x = 0.;
			Ref_Xzmp_Con_0 = 10.;


			pSharedMemory->Read_Dicson_LAR_Flag = 0; // new//
			pSharedMemory->Read_Dicson_RAR_Flag = 0; //new//
			*/
			Del_Mov_RHip_r = 0.;
			Del_Mov_LHip_r = 0.;
			
			//if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
			//if((pSharedMemory->BC_y < 5) && (pSharedMemory->BC_y > -5) && (pSharedMemory->MotionFlag[5] == FALSE)){
			if(pSharedMemory->BC_y < 5 && pSharedMemory->BC_y > -5)	{
				pSharedMemory->Motion_State = 6; // Stop

				DeltaMov_y = (float)(1.0*CTRL_dsp_compen_p(Err_Yzmp,1)); // P
				DeltaMov_x = (float)(1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1)); // P
			}
			

			if(!pSharedMemory->Gesture_Flag){
				angle_stiff_ds3(0,0,0,0);   
				angle_stiff_fwL(0,0,0,0);  
				angle_stiff_ds4(0,0,0,0);   
				angle_stiff_fwR(0,0,0,0);  
				
				Right_Ankle_Control_Roll(0., 0., 0.);
				Right_Ankle_Control_Pitch(0., 0., 0.);
				Left_Ankle_Control_Roll(0., 0., 0.);
				Left_Ankle_Control_Pitch(0., 0., 0.);

				L_theta_compen_r = 0;
				L_theta_compen_p = 0;
				R_theta_compen_r = 0;
				R_theta_compen_p = 0;
				
				
				land_damp_fwd(0.,0.,0,0); //new//
				LF_land_damp_roll(0.,0.,0,0); //new//
				RF_land_damp_roll(0.,0.,0,0); //new//
				landLF = landRF = 0; //new//
				landRF_r = landLF_r = 0; //new//
				
			}
			//	DeltaMov_x = - 0.9*dsp_compen_p(Err_Xzmp,1); // P Controller
		} // End of Damping Controller Switching	

		//DeltaMov_y = 1.0*CTRL_dsp_compen_p(Err_Yzmp,1); // P
		//DeltaMov_x = 1.0*CTRL_dsp_compen_p2(Err_Xzmp-Init_Xzmp,1); // P

		// Landing Time Control
		if(!pSharedMemory->Walking_Test_Flag){   
			if(CTRL_mode == 2 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_R_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
					
				}
			}
			else if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Up_time/2 - pSharedMemory->Delay_time )) { 
				if(FiveKG_L_Flag == 0) {
					pSharedMemory->Int_CNT--;
					
					Delay_LO_Control_Flag = TRUE;
				}
			}
			else if(CTRL_mode == 1)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_R_Flag = FALSE;
			}
			else if(CTRL_mode == 3)
			{
				Delay_LO_Control_Flag = FALSE;
				FiveKG_L_Flag = FALSE;
			}
		}

		// Landing Position Control
		if(CTRL_mode == 4 && FiveKG_L_Flag == 1 && DelMov_LF_Walk_Z > 0 && LF_Landing_PosCon_Flag == 0){
			DelMov_LF_Walk_Z_ref = DelMov_LF_Walk_Z;
			DelMov_LF_Walk_Z_del = (float)(0. - DelMov_LF_Walk_Z);
			DelMov_LF_Walk_Z_old = DelMov_LF_Walk_Z;
			LF_Landing_PosCon_Flag = 1;
			LF_Landing_PosCon_CNT = 0;
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleR > 1.8 && pSharedMemory->Amp_ankleR < 2.8){
					pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.01;
				}
			}
			
			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_LF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y - BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;			
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL - 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR + 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;
			*/
		}
		else if(CTRL_mode == 2 && FiveKG_R_Flag == 1 && DelMov_RF_Walk_Z > 0 && RF_Landing_PosCon_Flag == 0){
			DelMov_RF_Walk_Z_ref = DelMov_RF_Walk_Z;
			DelMov_RF_Walk_Z_del = (float)(0. - DelMov_RF_Walk_Z);
			DelMov_RF_Walk_Z_old = DelMov_RF_Walk_Z;
			RF_Landing_PosCon_Flag = 1;
			RF_Landing_PosCon_CNT = 0;
			
			/*
			if(pSharedMemory->Ankle_Compen_Flag){
				if(pSharedMemory->Amp_ankleL > 1.8 && pSharedMemory->Amp_ankleL < 2.8){
					pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.01;
				}		
			}

			BC_equi_com_y_con_input = Kp_BC_equi_com_y*DelMov_RF_Walk_Z;
			if(BC_equi_com_y_con_input > 1) BC_equi_com_y_con_input = 1;
			pSharedMemory->BC_equi_comp_y = pSharedMemory->BC_equi_comp_y + BC_equi_com_y_con_input;
			if(pSharedMemory->BC_equi_comp_y > SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = SOFT_TOUCH_BOUND ;
			else if(pSharedMemory->BC_equi_comp_y < -SOFT_TOUCH_BOUND) pSharedMemory->BC_equi_comp_y = -SOFT_TOUCH_BOUND;
			pSharedMemory->Amp_ankleL = pSharedMemory->Amp_ankleL + 0.1*BC_equi_com_y_con_input;
			pSharedMemory->Amp_ankleR = pSharedMemory->Amp_ankleR - 0.1*BC_equi_com_y_con_input;
			if(pSharedMemory->Amp_ankleL > UPPER_ANKL_R) pSharedMemory->Amp_ankleL = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleL < LOWER_ANKL_R) pSharedMemory->Amp_ankleL = LOWER_ANKL_R;
	
			if(pSharedMemory->Amp_ankleR > UPPER_ANKL_R) pSharedMemory->Amp_ankleR = UPPER_ANKL_R;
			else if(pSharedMemory->Amp_ankleR < LOWER_ANKL_R) pSharedMemory->Amp_ankleR = LOWER_ANKL_R;*/
		}
		else if(CTRL_mode == 1)
		{
			FiveKG_R_Flag = FALSE;
		}
		else if(CTRL_mode == 3)
		{
			FiveKG_L_Flag = FALSE;
		}

		if(LF_Landing_PosCon_Flag == 1 && CTRL_mode == 1){
			DelMov_LF_Walk_Z_ref = (float)(DelMov_LF_Walk_Z_old + DelMov_LF_Walk_Z_del*0.5*(1.-cos(PI*LF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(LF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				LF_Landing_PosCon_Flag  = 0;
				LF_Landing_PosCon_CNT = 0;
			}
			else LF_Landing_PosCon_CNT++;
		}
		else if(RF_Landing_PosCon_Flag == 1 && CTRL_mode == 3){
			DelMov_RF_Walk_Z_ref = (float)(DelMov_RF_Walk_Z_old + DelMov_RF_Walk_Z_del*0.5*(1.-cos(PI*RF_Landing_PosCon_CNT/(pSharedMemory->Up_time/2 + 8)))); 
			if(RF_Landing_PosCon_CNT > (pSharedMemory->Up_time/2 + 8)){
				RF_Landing_PosCon_Flag  = 0;
				RF_Landing_PosCon_CNT = 0;
			}
			else RF_Landing_PosCon_CNT++;
		}
		
		if(CTRL_mode == 4 && Path_Local_CNT == (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			if(Temp_Inc_Sum_CNT != 0){
				
				Inc_Avg = Temp_Inc_Sum/Temp_Inc_Sum_CNT;
				
				
				if(pSharedMemory->Path_Area_CNT >= 3){
					
					DelMov_BCA = (float)(DelMovCoff*(DelMov_BCA + 2.0*Inc_Avg));
					
					if(DelMov_BCA > 10.0) DelMov_BCA = 10.0;
					else if(DelMov_BCA < -10.0) DelMov_BCA = -10.0;
				}
			}
			
			Temp_Inc_Sum = 0.;
			Temp_Inc_Sum_CNT = 0;
		}

		// Starting Kick Compensation
		if(pSharedMemory->Int_CNT < pSharedMemory->Step_time + (pSharedMemory->Step_time - 2*pSharedMemory->Delay_time)/2){
			Start_Kick_BC_Y_Comp = (float)(START_KICK_AMP*pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
        }
		else Start_Kick_BC_Y_Comp = 0.;
		
		Ref_Yzmp_Con = (float)((1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*ZMP_REFY*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp));
		//Ref_Yzmp_Con = (1. - 2.*PI*ZMP_LP_COF*DELTA_T)*old_Ref_Yzmp_Con + 2.*PI*ZMP_LP_COF*DELTA_T*pSharedMemory->amp_temp1*(2*pSharedMemory->BC_y/pSharedMemory->Walk_BC_Ydir_Amp);
		old_Ref_Yzmp_Con = Ref_Yzmp_Con;

		if(pSharedMemory->Gesture_Flag == 0){
			if(!pSharedMemory->Walking_Gesture_Flag){
				//pSharedMemory->theta[RSY] = WLK_RDY_LRSY  + WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));
				//pSharedMemory->theta[LSY] = -WLK_RDY_LRSY  - WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.));

				v_AngArm[1] = (float)(WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
				v_AngArm[5] = (float)(-WLKING_LRSY*(pSharedMemory->BC_y/(pSharedMemory->Walk_BC_Ydir_Amp/2.)));
			}
			
			if(pSharedMemory->Motion_State != 6){
				
				BC_y_ZMP_CON = (float)(SSP_ZMP_GAIN_Y*SSP_ZMP_CON_Y(Ref_Yzmp_Con,Yzmp_lp,1));
				BC_x_ZMP_CON = (float)(SSP_ZMP_GAIN_X*SSP_ZMP_CON_X(10,Xzmp_lp,1));
				old_BC_y_ZMP_CON = BC_y_ZMP_CON;
				old_BC_x_ZMP_CON = BC_x_ZMP_CON;
				BC_x_ZMP_CON_CNT = 0;
			}
			else{
				BC_y_ZMP_CON = (float)(old_BC_y_ZMP_CON - old_BC_y_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
				BC_x_ZMP_CON = (float)(old_BC_x_ZMP_CON - old_BC_x_ZMP_CON*0.5*(1.-cos(PI*BC_x_ZMP_CON_CNT/50)));
				SSP_ZMP_CON_Y(0,0,0);
				SSP_ZMP_CON_X(0,0,0);
				
				if(BC_x_ZMP_CON_CNT < 50) BC_x_ZMP_CON_CNT++;
			}
		}

		if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
			//Equi_Adj_LRAP_Walking = CTRL_INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
			Equi_Adj_LRAP_Walking = (float)(-CTRL_INCL_Ank_Pitch_Walking(Pit_y_a_1_Hspd - 0.0f,1));
		}
		
		pSharedMemory->BC_y = pSharedMemory->BC_y + DeltaMov_y_ini + DeltaMov_y + Start_Kick_BC_Y_Comp + BC_y_ZMP_CON + BC_Y_Amp_Compen + DelMov_BCA;
		pSharedMemory->BC_x = DeltaMov_x_ini + DeltaMov_x + BC_x_ZMP_CON;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;

		pSharedMemory->R_px = - pSharedMemory->BC_x ;
		pSharedMemory->L_px = - pSharedMemory->BC_x ;
		

		pSharedMemory->R_py = (float)(-L0 - WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footRy);// - DSP_temp_4;
		pSharedMemory->L_py =  (float)(L0 + WLK_RDY_OFFSET - pSharedMemory->BC_y + rel_footLy);// + DSP_temp_3;

		//if(pSharedMemory->Gesture_Flag == 0 && pSharedMemory->Walking_Gesture_Flag == 0){
		//	Equi_Adj_LRAP_Walking = INCL_Ank_Pitch_Walking(0.0286156*Pit_y_a_1_Hspd - UpBody_Tilt_LRHP,1);
		//}

		if(RF_Landing_PosCon_Flag) pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z_ref + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// + Equi_Adj_Rfoot_Z_Walking + Gesture_Step_RF_z + RF_More_Strech;//+ Del_spring_R_pz;
		else pSharedMemory->R_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_RF_Walk_Z + pSharedMemory->Equi_Adj_Rfoot_Z - DelMov_BCA;// 
		
		if(LF_Landing_PosCon_Flag)	pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z_ref + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;// + Equi_Adj_Lfoot_Z_Walking + DSP_temp_2 + SSP_temp_2 + Gesture_Step_LF_z + LF_More_Strech;//+ Del_spring_L_pz;
		else pSharedMemory->L_pz = -L1 - L2 - pSharedMemory->BC_z + DelMov_LF_Walk_Z + pSharedMemory->Equi_Adj_Lfoot_Z + DelMov_BCA;
		
		PosInput[0] = pSharedMemory->L_px;
		PosInput[1] = pSharedMemory->L_py;
		PosInput[2] = pSharedMemory->L_pz;
		PosInput[3] = pSharedMemory->R_px;
		PosInput[4] = pSharedMemory->R_py;
		PosInput[5] = pSharedMemory->R_pz;
		
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][2]=(float)pSharedMemory->BC_y;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][3]=(float)DelMov_LF_Walk_Z;
		pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][4]=(float)DelMov_RF_Walk_Z;	
	
		pSharedMemory->BC_y = 0.;
		pSharedMemory->BC_x = 0.;
		pSharedMemory->BC_z = -WLK_RDY_DOWN;
		DelMov_LF_Walk_Z = 0.;
		DelMov_RF_Walk_Z = 0.;
} // End of else if(pSharedMemory->Walk_CCW_Turn_Flag && WLK_RDY_MODE == 1)

void Damping_control_init()
{
	// variable with damping controller
	L_theta_compen_r = L_theta_compen_p = R_theta_compen_r = R_theta_compen_p = 0.;
	L_theta_compen_r_old = L_theta_compen_p_old = R_theta_compen_r_old = R_theta_compen_p_old = 0.;
	L_theta_compen_r_del = L_theta_compen_p_del = R_theta_compen_r_del = R_theta_compen_p_del = 0.;
	L_theta_compen_CNT = 0;
	R_theta_compen_CNT = 0;
	
	angle_stiff_ds3(0,0,0,0);  // 
	angle_stiff_ds4(0,0,0,0);  //  
	angle_stiff_fwL(0,0,0,0);  //
	angle_stiff_fwR(0,0,0,0);  //
	
	Left_Ankle_Control_Roll(0., 0., 0.);
	Left_Ankle_Control_Pitch(0., 0., 0.);
	Right_Ankle_Control_Roll(0., 0., 0.);
	Right_Ankle_Control_Pitch(0., 0., 0.);
	// end of damping controller reset
}

void Landing_control_init()
{
	
	landRF = landLF = 0.;
	landRF_old = landLF_old = 0.;
	landRF_del = landLF_del = 0.;
	landRF_CNT = landLF_CNT = 0;

	land_damp_fwd(0.,0.,0,0); //new//
	LF_land_damp_roll(0.,0.,0,0); //new//
	RF_land_damp_roll(0.,0.,0,0); //new//

}

void WristMotion()
{
	if((pSharedMemory->WristMotionFlag == 1) || (pSharedMemory->WristMotionFlag == 2) || (pSharedMemory->WristMotionFlag == 3) || (pSharedMemory->WristMotionFlag == 4) || (pSharedMemory->WristMotionFlag == 5))	// wrist motion
	{
		UpperBodyTime[2]++;
		
		if(pSharedMemory->WristMotionMode == 2) PROF_Wrist_Shake1(UpperBodyTime[2], pSharedMemory->WristMotionFlag);
		else if(pSharedMemory->WristMotionMode == 3) PROF_Wrist_Shake2(UpperBodyTime[2], pSharedMemory->WristMotionFlag);
		else PROF_Wrist_Shake(UpperBodyTime[2], pSharedMemory->WristMotionFlag);
		
		if(UpperBodyTime[2] >= ((1/DELTA_T)/(pSharedMemory->WristHz))) 
		{
			if(pSharedMemory->WristMotionFlag == 1) pSharedMemory->WristMotionFlag = 2;
			else if(pSharedMemory->WristMotionFlag == 3) pSharedMemory->WristMotionFlag = 4;
			else if(pSharedMemory->WristMotionFlag == 4) pSharedMemory->WristMotionFlag = 5;
			
			UpperBodyTime[2] = 0;
		}
		
		if((pSharedMemory->WristMotionFlag == 5) && (UpperBodyTime[2] == 0)) pSharedMemory->WristMotionFlag = 0;
				
		//UpperMove();
		//RefPosCmd();
	}
	else if(pSharedMemory->WristMotionFlag == 0)
	{
		UpperBodyTime[2] = 0;
	}

}

void ShoulderTestMotion()
{
	if((pSharedMemory->ShoulderMotionFlag == 1) || (pSharedMemory->ShoulderMotionFlag == 2) || (pSharedMemory->ShoulderMotionFlag == 3) || (pSharedMemory->ShoulderMotionFlag == 4) || (pSharedMemory->ShoulderMotionFlag == 5))	// shoulder motion
	{
		UpperBodyTime[3]++;
		
		PROF_Shoulder_Shake(UpperBodyTime[3], pSharedMemory->ShoulderMotionFlag);
		
		if(UpperBodyTime[3] >= ((1/DELTA_T)/(pSharedMemory->ShoulderPitchHz))) 
		{
			if(pSharedMemory->ShoulderMotionFlag == 1) pSharedMemory->ShoulderMotionFlag = 2;
			else if(pSharedMemory->ShoulderMotionFlag == 3) pSharedMemory->ShoulderMotionFlag = 4;
			else if(pSharedMemory->ShoulderMotionFlag == 4) pSharedMemory->ShoulderMotionFlag = 5;
			
			UpperBodyTime[3] = 0;
		}
			
		if((pSharedMemory->ShoulderMotionFlag == 5) && (UpperBodyTime[3] == 0)) pSharedMemory->ShoulderMotionFlag = 0;
		
		//UpperMove();
		//RefPosCmd();
	}
	else if(pSharedMemory->ShoulderMotionFlag == 0)
	{
		UpperBodyTime[3] = 0;
	}
}

void WristConfigureMotion()
{
	if((pSharedMemory->WristConfigureFlag == 1) || (pSharedMemory->WristConfigureFlag == 2))
	{
		if(pSharedMemory->WristConfigureFlag == 1) 
		{
			UpperBodyTime[5] = 0;
			pSharedMemory->WristConfigureFlag = 2;
		}
		
		UpperBodyTime[5]++;
		
		PROF_WristConfigure1(UpperBodyTime[5]);
		
		if(UpperBodyTime[5] > 100*TS) {pSharedMemory->WristConfigureFlag = 0; UpperBodyTime[5] = 0;}
		
		//UpperMove();
		//RefPosCmd();
	}
	
	if((pSharedMemory->WristConfigureFlag == 3) || (pSharedMemory->WristConfigureFlag == 4))
	{
		if(pSharedMemory->WristConfigureFlag == 3) 
		{
			UpperBodyTime[5] = 0;
			pSharedMemory->WristConfigureFlag = 4;
		}
		UpperBodyTime[5]++;
		PROF_WristConfigure2(UpperBodyTime[5]);
		
		if(UpperBodyTime[5] > 100*TS) {pSharedMemory->WristConfigureFlag = 0; UpperBodyTime[5] = 0;}
		
		//UpperMove();
		//RefPosCmd();
	}
}

void ShakeHands()
{
	float res1;
	float res2;
	//UpperBodyTime[6] for shake hands

	res1 = 0.0f;
	res2 = 0.0f;

	if(pSharedMemory->ShakeHandsFlag == 1) 
	{
		UpperBodyTime[6] = 0;
		Wrist_mass_spring_damper_Fz(RTX_N_RWRIST_Fz_LPF, 0);
		Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF, 0);
		Torsion_mass_spring_damper_Mx(RTX_NM_RWRIST_Mx_LPF, 0);
		pSharedMemory->ShakeHandsFlag = 2;
	}

	if(pSharedMemory->ShakeHandsFlag == 2)
	{
		FTN_half_1_cos(1., UpperBodyTime[6], 0, 200, 10, 10, &res1);
	
		if(UpperBodyTime[6] < 200) UpperBodyTime[6]++;
		else UpperBodyTime[6] = 200;	

		//UpperMovement[RSP] = (float)(10.*res1 + 0.8*Wrist_mass_spring_damper_Fz(RTX_N_RWRIST_Fz_LPF,1));
		//UpperMovement[RSP] = (float)(10.*res1 - 0.5*Wrist_mass_spring_damper_Fz(RTX_N_RWRIST_Fz_LPF,1));
		UpperMovement[RSP] = (float)(50.*res1);
		
		//UpperMovement[RSY] = (float)(12.*res1 - 1.2*Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF,1));
		UpperMovement[RSY] = (float)(12.*res1);// - 1.2*Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF,1));
		
		UpperMovement[RSR] = (float)(-18.*res1);// + 0.6*Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF,1));
		//UpperMovement[RSR] = (float)(-18.*res1 + 0.6*Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF,1));
		UpperMovement[REB] = (float)(20.*res1 - 1.2*Torsion_mass_spring_damper_Mx(RTX_NM_RWRIST_Mx_LPF,1));

		UpperMovement[RW2] = (float)(-12.*res1);
		UpperMovement[WST] = (float)(10.*res1);
		UpperMovement[RW1] = (float)(12.*res1);
		UpperMovement[NKY] = (float)(-12.*res1);
		UpperMovement[NK1] = (float)(-12.*res1);
		UpperMovement[NK2] = (float)(12.*res1);

		//UpperMovement[RSP] = (float)(10.*res1);
		//UpperMovement[RSY] = 0.0f;
		//UpperMovement[RSR] = (float)(1.*res1);
		//UpperMovement[REB] = (float)(1.*res1);

		//pSharedMemory->temp[0] = Wrist_mass_spring_damper_Fz(RTX_N_RWRIST_Fz_LPF,1);
		//pSharedMemory->temp[1] = Torsion_mass_spring_damper_My(RTX_NM_RWRIST_My_LPF,1);
		//pSharedMemory->temp[2] = Torsion_mass_spring_damper_Mx(RTX_NM_RWRIST_Mx_LPF,1);
	

		OLD_UpperMovement[RSP] = UpperMovement[RSP];
		OLD_UpperMovement[RSY] = UpperMovement[RSY];
		OLD_UpperMovement[RSR] = UpperMovement[RSR];
		OLD_UpperMovement[REB] = UpperMovement[REB];
		OLD_UpperMovement[RW2] = UpperMovement[RW2];
		OLD_UpperMovement[WST] = UpperMovement[WST];
		OLD_UpperMovement[RW1] = UpperMovement[RW1];
		OLD_UpperMovement[NKY] = UpperMovement[NKY];
		OLD_UpperMovement[NK1] = UpperMovement[NK1];
		OLD_UpperMovement[NK2] = UpperMovement[NK2];
		
	}

	if(pSharedMemory->ShakeHandsFlag == 3)
	{
		UpperBodyTime[6] = 0;
		pSharedMemory->ShakeHandsFlag = 4;
	}

	if(pSharedMemory->ShakeHandsFlag == 4)
	{
		FTN_half_1_cos(1., UpperBodyTime[6], 0, 200, 10, 10, &res2); 

		if(UpperBodyTime[6] < 200) UpperBodyTime[6]++;
		else pSharedMemory->ShakeHandsFlag = 0; 	

		UpperMovement[RSP] = (float)(OLD_UpperMovement[RSP]*(1. - res2));
		UpperMovement[RSY] = (float)(OLD_UpperMovement[RSY]*(1. - res2));
		UpperMovement[RSR] = (float)(OLD_UpperMovement[RSR]*(1. - res2));
		UpperMovement[REB] = (float)(OLD_UpperMovement[REB]*(1. - res2));
		UpperMovement[RW2] = (float)(OLD_UpperMovement[RW2]*(1. - res2));
		UpperMovement[WST] = (float)(OLD_UpperMovement[WST]*(1. - res2));
		UpperMovement[RW1] = (float)(OLD_UpperMovement[RW1]*(1. - res2));
		UpperMovement[NKY] = (float)(OLD_UpperMovement[NKY]*(1. - res2));
		UpperMovement[NK1] = (float)(OLD_UpperMovement[NK1]*(1. - res2));
		UpperMovement[NK2] = (float)(OLD_UpperMovement[NK2]*(1. - res2));
	}

	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][9]=(float)res1;
	pSharedMemory->SaveData[pSharedMemory->PROFTime[11]][10]=(float)res2;
}