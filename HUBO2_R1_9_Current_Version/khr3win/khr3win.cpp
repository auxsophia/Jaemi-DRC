// khr3win.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "khr3win.h"
#include "khr3winDlg.h"
#include "CANwin.h"
#include "math.h"
#include "..\MotorParameter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKhr3winApp

BEGIN_MESSAGE_MAP(CKhr3winApp, CWinApp)
	//{{AFX_MSG_MAP(CKhr3winApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKhr3winApp construction

CKhr3winApp::CKhr3winApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKhr3winApp object

CKhr3winApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKhr3winApp initialization

BOOL CKhr3winApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Dir_PPR(); // Motor direction and Pulse per rotation

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CKhr3winDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CKhr3winApp::EnableHIP(unsigned char BoardNo)
{
	unsigned char TxData[3];

	TxData[0] = BoardNo;
	TxData[1] = HipEnable;
	TxData[2] = 0x01;
	
	
	if((BoardNo >= 0x00) && (BoardNo < 0x08))
	{
		// Can channel no. 1 is used.	-- for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 3);	
	}
	else
	{
		// Can channel no. 2 is used. 
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 3);	
	}
	
	Sleep(50);

}

void CKhr3winApp::SendCTRLOff(unsigned char BoardNo)
{
	unsigned char TxData[2];
	
	TxData[0] = BoardNo;
	TxData[1] = StopCMD; 
	
	if((BoardNo >= 0x00) && (BoardNo < 0x08))
	{
		// Can channel no. 1 is used.	for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 2);	
	}
	else
	{
		// Can channel no. 2 is used. 
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 2);	
	}

	Sleep(50);
}

void CKhr3winApp::DisableHIP(unsigned char BoardNo)
{
	unsigned char TxData[3];
	
	TxData[0] = BoardNo;
	TxData[1] = HipEnable;
	TxData[2] = 0x00;
	
	
	if((BoardNo >= 0x00) && (BoardNo < 0x08))
	{
		// Can channel no. 1 is used. -- for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 3);	
	}
	else
	{
		// Can channel no. 2 is used. -- for upper body
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 3);	
	}

	Sleep(50);
}

void CKhr3winApp::DisablePWM(unsigned char BoardNo)
{
	unsigned char TxData[7];
	unsigned char TxData1[8];
	
	TxData[0] = BoardNo;
	TxData[1] = PwmCMD;
	TxData[2] = 0x00;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;

	TxData1[0] = BoardNo;
	TxData1[1] = PwmCMD;
	TxData1[2] = 0x00;
	TxData1[3] = 0x00;
	TxData1[4] = 0x00;
	TxData1[5] = 0x00;
	TxData1[6] = 0x00;
	TxData1[7] = 0x00;
	
	if(BoardNo <= JMC7)
	{
		TxData[0] = BoardNo;
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 7);	
		Sleep(20);
	}
	else if((BoardNo >= JMC8) && (BoardNo <= JMC11))
	{
		TxData[0] = BoardNo;
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 7);	
		Sleep(20);
	}
	else if((BoardNo >= EJMC0 && BoardNo <= EJMC2))
	{
		TxData1[0] = BoardNo;
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData1, 8);	
		Sleep(20);
	}
	
    Sleep(20);
}

void CKhr3winApp::WINmoveANG_RPM(unsigned char MoID, float Angle, float rpm)
{
	theApp.m_pSharedMemory->Oldtheta[MoID]	=	theApp.m_pSharedMemory->Reftheta[MoID];
	theApp.m_pSharedMemory->Move_CNT[MoID]	=	0;
	theApp.m_pSharedMemory->Move_Flag[MoID] =	DISABLE;
	theApp.m_pSharedMemory->theta[MoID]		=	Angle;
	theApp.m_pSharedMemory->Deltheta[MoID]	=	theApp.m_pSharedMemory->theta[MoID] - theApp.m_pSharedMemory->Oldtheta[MoID];

	if(theApp.m_pSharedMemory->Deltheta[MoID] >= 0)
		theApp.m_pSharedMemory->Tfinal[MoID] = (unsigned long)( theApp.m_pSharedMemory->Deltheta[MoID]/0.06/rpm);
	else if(theApp.m_pSharedMemory->Deltheta[MoID]<0)
		theApp.m_pSharedMemory->Tfinal[MoID] = (unsigned long)(-theApp.m_pSharedMemory->Deltheta[MoID]/0.06/rpm);
	
	if(theApp.m_pSharedMemory->Tfinal[MoID] != 0) theApp.m_pSharedMemory->Move_Flag[MoID] = ENABLE;
	else   theApp.m_pSharedMemory->Move_Flag[MoID] = DISABLE;
}

void CKhr3winApp::SendRunCMD(unsigned char BoardNo)
{
	unsigned char TxData[2];
	
	TxData[0] = BoardNo;
	TxData[1] = RunCMD;    
	
	if((BoardNo >= 0x00) && (BoardNo < 0x08))
	{
		// Can channel no. 1 is used. -- for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 2);	
	}
	else
	{
		// Can channel no. 2 is used. -- for upper body
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 2);	
	}
	
	Sleep(50);
}

void CKhr3winApp::Encoder_ZeroCMD(unsigned char BoardNo)
{
	unsigned char TxData[3];
	
	TxData[0] = BoardNo;
	TxData[1] = EncZero;
	TxData[2] = 0x00;
	
	if((BoardNo >= JMC0) && (BoardNo <= JMC7))
	{
		// Can channel no. 1 is used. -- for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 3);	
	}
	else
	{
		// Can channel no. 2 is used. -- for upper body
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 3);	
	}

	Sleep(50);
}

void CKhr3winApp::Stop_CMD(unsigned char BoardNo)
{
	unsigned char TxData[2];

	TxData[0] = BoardNo;
	TxData[1] = StopCMD;
	
	if((BoardNo >= 0x00) && (BoardNo < 0x08))
	{
		// Can channel no. 1 is used. -- for lower body
		m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 2);	
	}
	else
	{
		// Can channel no. 2 is used. -- for upper body
		m_CanWinAPP.CAN_WRITE1(CMD_TXDF, TxData, 2);	
	}

	Sleep(50);
	
}

char CKhr3winApp::InvKineWin(double LPx, double LPy, double LPz, double LYaw, double RPx, double RPy, double RPz, double RYaw)
{
	char  i=0;
	double LYaw1;
	double RYaw1;
	double LValid=0.;
	double RValid=0.;
	double temp[4]={0,0,0,0};
	double temp1[4]={0,0,0,0};
	
	/******** Left Leg Inverse Kinematics *********/
	LYaw1=LYaw*deg2rad;
	LValid=(LPx*LPx+(LPy-L0)*(LPy-L0)+LPz*LPz-(L1*L1)-(L2*L2))/(2*L1*L2);
	if((LValid>1)||(LValid<-1)) return 0;
	
	LegAngle[0]=LYaw1; //[Radian] Left Hip Yaw
	LegAngle[3]=acos(LValid); //[Radian] Left Knee Angle
	LegAngle[1]=atan2(LPz, -LPx*sin(LYaw1)+(LPy-L0)*cos(LYaw1));//[Radian] Left Hip Roll
	
	temp[0]=-L2*sin(LegAngle[3]);
	temp[1]=L1+L2*cos(LegAngle[3]);
	temp[2]=LPx*cos(LYaw1)+(LPy-L0)*sin(LYaw1);
	temp[3]=-LPx*sin(LYaw1)*cos(LegAngle[1]) + (LPy-L0)*cos(LYaw1)*cos(LegAngle[1])+LPz*sin(LegAngle[1]);
	
	LValid = (temp[0]*temp[3]-temp[1]*temp[2])/(temp[0]*temp[0]+temp[1]*temp[1]);

	if((LValid>1)||(LValid<-1)) return 0;
	
	LegAngle[2]=asin(LValid);
	
	LegAngle[1]=LegAngle[1]+PI/2.; // Offset Setting
	
	/******* If Ankle Parallel Condition Applied*******/
	LegAngle[4]=-LegAngle[3]-LegAngle[2];
	LegAngle[5]=-LegAngle[1];
	/**************************************************/
	/******** End of Left Leg Inverse Kinematics *********/
	
	/******** Right Leg Inverse Kinematics *********/
	RYaw1=RYaw*deg2rad;
	RValid=(RPx*RPx+(RPy+L0)*(RPy+L0)+RPz*RPz-(L1*L1)-(L2*L2))/(2*L1*L2);
	if((RValid>1)||(RValid<-1)) return 0;
	
	LegAngle[6]=RYaw1; //[Radian] Right Hip Yaw
	LegAngle[9]=acos(RValid); //[Radian] Left Knee Angle
	LegAngle[7]=atan2(RPz, -RPx*sin(RYaw1)+(L0+RPy)*cos(RYaw1));//[Radian] Right Hip Roll
	
	temp1[0]=-L2*sin(LegAngle[9]);
	temp1[1]=L1+L2*cos(LegAngle[9]);
	temp1[2]=RPx*cos(RYaw1)+(RPy+L0)*sin(RYaw1);
	temp1[3]=-RPx*sin(RYaw1)*cos(LegAngle[7]) + (RPy+L0)*cos(RYaw1)*cos(LegAngle[7])+RPz*sin(LegAngle[7]);
	
	RValid = (temp1[0]*temp1[3]-temp1[1]*temp1[2])/(temp1[0]*temp1[0]+temp1[1]*temp1[1]);
	
	if((RValid>1)||(RValid<-1)) return 0;
	
	LegAngle[8]=asin(RValid);
	
	LegAngle[7]=LegAngle[7]+PI/2.; // Offset Setting
	
	/******* If Ankle Parallel Condition Applied*******/
	LegAngle[10]=-LegAngle[9]-LegAngle[8];
	LegAngle[11]=-LegAngle[7];
	/**************************************************/
	/******** End of Right Leg Inverse Kinematics *********/	

	/******* Radian to Degree Conversion **************/
	for(i=0;i<12;i++)
	{
		LegAngle[i]=LegAngle[i]*rad2deg;
	}
	/**************************************************/	
	return 1;
}

char CKhr3winApp::FrdKineWin(double LTh1, double LTh2, double LTh3, double LTh4, double LTh5, double LTh6,
							 double RTh1, double RTh2, double RTh3, double RTh4, double RTh5, double RTh6)
{
	double LTh1_; double LTh2_; double LTh3_; double LTh4_; double LTh5_; double LTh6_;
	double RTh1_; double RTh2_; double RTh3_; double RTh4_; double RTh5_; double RTh6_;

	LTh1_=LTh1*deg2rad;	LTh2_=LTh2*deg2rad;	LTh3_=LTh3*deg2rad;
	LTh4_=LTh4*deg2rad;	LTh5_=LTh5*deg2rad;	LTh6_=LTh6*deg2rad;

	RTh1_=RTh1*deg2rad;	RTh2_=RTh2*deg2rad;	RTh3_=RTh3*deg2rad;
	RTh4_=RTh4*deg2rad;	RTh5_=RTh5*deg2rad;	RTh6_=RTh6*deg2rad;

	LPx=-L1*(sin(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_)+cos(LTh1_)*sin(LTh3_))
		-L2*(cos(LTh1_)*sin(LTh3_+LTh4_)+sin(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_+LTh4_));

	LPy=-(-L0+L1*(cos(LTh1_)*cos(LTh2_+PI/2.)*cos(LTh3_)-sin(LTh1_)*sin(LTh3_))
			+L2*(cos(LTh1_)*cos(LTh2_+PI/2)*cos(LTh3_+LTh4_)-sin(LTh1_)*sin(LTh3_+LTh4_)));

	LPz=-(L1*sin(LTh2_+PI/2.)*cos(LTh3_)+L2*sin(LTh2_+PI/2.)*cos(LTh3_+LTh4_));

	
	RPx=-L1*(sin(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_)+cos(RTh1_)*sin(RTh3_))
		-L2*(cos(RTh1_)*sin(RTh3_+RTh4_)+sin(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_+RTh4_));
	
	RPy=-(+L0+L1*(cos(RTh1_)*cos(RTh2_+PI/2.)*cos(RTh3_)-sin(RTh1_)*sin(RTh3_))
			+L2*(cos(RTh1_)*cos(RTh2_+PI/2)*cos(RTh3_+RTh4_)-sin(RTh1_)*sin(RTh3_+RTh4_)));
	
	RPz=-(L1*sin(RTh2_+PI/2.)*cos(RTh3_)+L2*sin(RTh2_+PI/2.)*cos(RTh3_+RTh4_));

	return 1;
}

void CKhr3winApp::CAN_WRITE(unsigned int CAN_ID, unsigned char TxData[], unsigned char TxDlc)
{
	theApp.m_pSharedMemory->Tx_ID = CAN_ID;
	
	for(int i=0; i<TxDlc; i++)
	{
		theApp.m_pSharedMemory->Tx_Data[i] = TxData[i];
	}
	
	theApp.m_pSharedMemory->Tx_DLC = TxDlc;
	theApp.m_pSharedMemory->Tx_Flag = TRUE;
}

void CKhr3winApp::Dir_PPR()
{
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
	
	PPR[20] = (float)51200.;				// 오른 어깨 Pitch 감속비 512*100*1
	PPR[21] = (float)51200.;                // 오른 어깨 Yaw 감속비 512*100
	PPR[22] = (float)51200.;				// 오른 어깨 Roll 감속비 512*100
	PPR[23] = (float)51200.;                // 오른 Elbow 감속비 512*100
	PPR[24] = (float)51200.;				// 왼 어깨 Pitch 감속비 512*100*1
	PPR[25] = (float)51200.;                // 왼 어깨 Yaw 감속비 512*100
	PPR[26] = (float)51200.;				// 왼 어깨 Roll 감속비 512*100
	PPR[27] = (float)51200.;                // 왼 Elbow 감속비 512*100
	PPR[28] = (float)51200.;				//  Trunk 감속비 512*100

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
	
	PLUS_MTR_DIR[20] = -1.;
	PLUS_MTR_DIR[21] = -1.;
	PLUS_MTR_DIR[22] = 1.;
	PLUS_MTR_DIR[23] = -1.;
	PLUS_MTR_DIR[24] = 1.;
	PLUS_MTR_DIR[25] = 1.;
	PLUS_MTR_DIR[26] = 1.;
	PLUS_MTR_DIR[27] = 1.;
	PLUS_MTR_DIR[28] = 1.;
	
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
}

void CKhr3winApp::KineChange(unsigned char mode)
{
	static	unsigned char	oldmode;
	unsigned char	TxData[8];
	
	// 0: inverse kinematics
	// 1: forward kinematics
	// 2: Theta angle set
	// 3: XYZ position set

	if((mode!=oldmode)||(mode==2)||(mode==3))
	{
		TxData[0] = 'a';
		//TxData[1] = InfoCMD;
		TxData[2] = 'e';
		CAN_WRITE(CMD_TXDF,TxData,8);
	
		Sleep(100);
	
		m_Motor[0].CurrPos=	(theApp.m_pSharedMemory->Rx_Data[24][0])		|
							(theApp.m_pSharedMemory->Rx_Data[24][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[24][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[24][3] << 24)	;
			
		m_Motor[1].CurrPos = (theApp.m_pSharedMemory->Rx_Data[24][4])		|
							(theApp.m_pSharedMemory->Rx_Data[24][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[24][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[24][7] << 24)	;
	
		m_Motor[2].CurrPos = (theApp.m_pSharedMemory->Rx_Data[25][0])		|
							(theApp.m_pSharedMemory->Rx_Data[25][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[25][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[25][3] << 24)	;
	
		m_Motor[3].CurrPos = (theApp.m_pSharedMemory->Rx_Data[25][4])		|
							(theApp.m_pSharedMemory->Rx_Data[25][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[25][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[25][7] << 24)	;
	
		m_Motor[4].CurrPos = (theApp.m_pSharedMemory->Rx_Data[26][0])		|
							(theApp.m_pSharedMemory->Rx_Data[26][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[26][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[26][3] << 24)	;
			
		m_Motor[5].CurrPos = (theApp.m_pSharedMemory->Rx_Data[26][4])		|
							(theApp.m_pSharedMemory->Rx_Data[26][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[26][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[26][7] << 24)	;
		
			// Left Hand (JMC1)
		m_Motor[6].CurrPos=	(theApp.m_pSharedMemory->Rx_Data[27][0])		|
							(theApp.m_pSharedMemory->Rx_Data[27][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[27][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[27][3] << 24)	;
			
		m_Motor[7].CurrPos = (theApp.m_pSharedMemory->Rx_Data[27][4])		|
							(theApp.m_pSharedMemory->Rx_Data[27][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[27][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[27][7] << 24)	;
			
		m_Motor[8].CurrPos = (theApp.m_pSharedMemory->Rx_Data[28][0])		|
							(theApp.m_pSharedMemory->Rx_Data[28][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[28][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[28][3] << 24)	;
		
		m_Motor[9].CurrPos = (theApp.m_pSharedMemory->Rx_Data[28][4])		|
							(theApp.m_pSharedMemory->Rx_Data[28][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[28][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[28][7] << 24)	;
			
		m_Motor[10].CurrPos = (theApp.m_pSharedMemory->Rx_Data[29][0])		|
							(theApp.m_pSharedMemory->Rx_Data[29][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[29][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[29][3] << 24)	;
			
		m_Motor[11].CurrPos = (theApp.m_pSharedMemory->Rx_Data[29][4])		|
							(theApp.m_pSharedMemory->Rx_Data[29][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[29][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[29][7] << 24)	;
			
		m_Motor[12].CurrPos= (theApp.m_pSharedMemory->Rx_Data[30][0])		|
							(theApp.m_pSharedMemory->Rx_Data[30][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[30][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[30][3] << 24)	;
			
			// Right Hand (JMC2)
		m_Motor[13].CurrPos = (theApp.m_pSharedMemory->Rx_Data[31][0])		|
							(theApp.m_pSharedMemory->Rx_Data[31][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[31][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[31][3] << 24)	;
			
		m_Motor[14].CurrPos = (theApp.m_pSharedMemory->Rx_Data[31][4])		|
							(theApp.m_pSharedMemory->Rx_Data[31][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[31][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[31][7] << 24)	;
			
		m_Motor[15].CurrPos = (theApp.m_pSharedMemory->Rx_Data[32][0])		|
							(theApp.m_pSharedMemory->Rx_Data[32][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[32][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[32][3] << 24)	;
			
		m_Motor[16].CurrPos = (theApp.m_pSharedMemory->Rx_Data[32][4])		|
							(theApp.m_pSharedMemory->Rx_Data[32][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[32][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[32][7] << 24)	;
			
		m_Motor[17].CurrPos = (theApp.m_pSharedMemory->Rx_Data[33][0])		|
							(theApp.m_pSharedMemory->Rx_Data[33][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[33][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[33][3] << 24)	;
			
		m_Motor[18].CurrPos = (theApp.m_pSharedMemory->Rx_Data[33][4])		|
							(theApp.m_pSharedMemory->Rx_Data[33][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[33][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[33][7] << 24)	;
	
		m_Motor[19].CurrPos = (theApp.m_pSharedMemory->Rx_Data[34][0])		|
							(theApp.m_pSharedMemory->Rx_Data[34][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[34][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[34][3] << 24)	;
			
			// Right Shoulder Pitch-Yaw (JMC3)
		m_Motor[20].CurrPos = (theApp.m_pSharedMemory->Rx_Data[35][0])		|
							(theApp.m_pSharedMemory->Rx_Data[35][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[35][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[35][3] << 24)	;
			
		m_Motor[21].CurrPos = (theApp.m_pSharedMemory->Rx_Data[35][4])		|
							(theApp.m_pSharedMemory->Rx_Data[35][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[35][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[35][7] << 24)	;
	
			// Right Shoulder Roll, Elbow (JMC4)
		m_Motor[22].CurrPos = (theApp.m_pSharedMemory->Rx_Data[36][0])		|
							(theApp.m_pSharedMemory->Rx_Data[36][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[36][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[36][3] << 24)	;
	
		m_Motor[23].CurrPos = (theApp.m_pSharedMemory->Rx_Data[36][4])		|
							(theApp.m_pSharedMemory->Rx_Data[36][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[36][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[36][7] << 24)	;
	
			// Right Shoulder Pitch-Yaw (JMC5)
		m_Motor[24].CurrPos = (theApp.m_pSharedMemory->Rx_Data[37][0])		|
							(theApp.m_pSharedMemory->Rx_Data[37][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[37][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[37][3] << 24)	;
			
		m_Motor[25].CurrPos = (theApp.m_pSharedMemory->Rx_Data[37][4])		|
							(theApp.m_pSharedMemory->Rx_Data[37][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[37][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[37][7] << 24)	;
	
			// Right Shoulder Roll, Elbow (JMC6)
		m_Motor[26].CurrPos = (theApp.m_pSharedMemory->Rx_Data[38][0])		|
							(theApp.m_pSharedMemory->Rx_Data[38][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[38][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[38][3] << 24)	;
			
		m_Motor[27].CurrPos = (theApp.m_pSharedMemory->Rx_Data[38][4])		|
							(theApp.m_pSharedMemory->Rx_Data[38][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[38][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[38][7] << 24)	;
			
			// Trunk Yaw
		m_Motor[28].CurrPos = (theApp.m_pSharedMemory->Rx_Data[39][0])		|
							(theApp.m_pSharedMemory->Rx_Data[39][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[39][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[39][3] << 24)	;
	
			// Right Hip Yaw-Roll
		m_Motor[29].CurrPos = (theApp.m_pSharedMemory->Rx_Data[40][0])		|
							(theApp.m_pSharedMemory->Rx_Data[40][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[40][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[40][3] << 24)	;
			
		m_Motor[30].CurrPos = (theApp.m_pSharedMemory->Rx_Data[40][4])		|
							(theApp.m_pSharedMemory->Rx_Data[40][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[40][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[40][7] << 24)	;
	
			// Right Hip Pitch, Knee
		m_Motor[31].CurrPos = (theApp.m_pSharedMemory->Rx_Data[41][0])		|
							(theApp.m_pSharedMemory->Rx_Data[41][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[41][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[41][3] << 24)	;
			
		m_Motor[32].CurrPos = (theApp.m_pSharedMemory->Rx_Data[41][4])		|
							(theApp.m_pSharedMemory->Rx_Data[41][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[41][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[41][7] << 24)	;
	
			// Right Ankle Pitch-Roll
		m_Motor[33].CurrPos = (theApp.m_pSharedMemory->Rx_Data[42][0])		|
							(theApp.m_pSharedMemory->Rx_Data[42][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[42][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[42][3] << 24)	;
			
		m_Motor[34].CurrPos = (theApp.m_pSharedMemory->Rx_Data[42][4])		|
							(theApp.m_pSharedMemory->Rx_Data[42][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[42][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[42][7] << 24)	;
	
			// Left Hip Yaw-Roll
		m_Motor[35].CurrPos = (theApp.m_pSharedMemory->Rx_Data[43][0])		|
							(theApp.m_pSharedMemory->Rx_Data[43][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[43][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[43][3] << 24)	;
			
		m_Motor[36].CurrPos = (theApp.m_pSharedMemory->Rx_Data[43][4])		|
							(theApp.m_pSharedMemory->Rx_Data[43][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[43][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[43][7] << 24)	;
		
			// Left Hip Pitch, Knee
		m_Motor[37].CurrPos = (theApp.m_pSharedMemory->Rx_Data[44][0])		|
							(theApp.m_pSharedMemory->Rx_Data[44][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[44][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[44][3] << 24)	;
		
		m_Motor[38].CurrPos = (theApp.m_pSharedMemory->Rx_Data[44][4])		|
							(theApp.m_pSharedMemory->Rx_Data[44][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[44][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[44][7] << 24)	;
			
			// Left Ankle Pitch-Roll
		m_Motor[39].CurrPos = (theApp.m_pSharedMemory->Rx_Data[45][0])		|
							(theApp.m_pSharedMemory->Rx_Data[45][1] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[45][2] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[45][3] << 24)	;
		
		m_Motor[40].CurrPos = (theApp.m_pSharedMemory->Rx_Data[45][4])		|
							(theApp.m_pSharedMemory->Rx_Data[45][5] <<	8)	|
							(theApp.m_pSharedMemory->Rx_Data[45][6] << 16)	|
							(theApp.m_pSharedMemory->Rx_Data[45][7] << 24)	;
	
		// Real Realtheta[] Calculation
		for(int i=0;i<TOTAL_MTR_NUM;i++)
		{
			m_pSharedMemory->Realtheta[i]=(float)(m_Motor[i].CurrPos*PLUS_MTR_DIR[i]/PPR[i]*360.);
		}
	}

	if((mode == 1)&&(oldmode == 0)) // inverse->forward
	{
		for(int i=0;i<TOTAL_MTR_NUM;i++)
		{
			m_pSharedMemory->Deltheta[i]=m_pSharedMemory->Realtheta[i]-m_pSharedMemory->Reftheta[i];
			m_pSharedMemory->Reftheta[i]=m_pSharedMemory->Reftheta[i]+m_pSharedMemory->Deltheta[i];
		}
		Sleep(100);

		oldmode = 1;
	}

	else if((mode == 0)&&(oldmode == 1)||(mode==3)) // forward -> inverse
	{
		float JntTheta[TOTAL_MTR_NUM];

		for(int i=0;i<TOTAL_MTR_NUM;i++)
		{
			JntTheta[i]=m_pSharedMemory->Realtheta[i];
		}

		FrdKineWin(JntTheta[35],JntTheta[36],JntTheta[37],JntTheta[38],JntTheta[39],JntTheta[40],
				   JntTheta[29],JntTheta[30],JntTheta[31],JntTheta[32],JntTheta[33],JntTheta[34]);
		
		m_pSharedMemory->XYZreal[0]=(float)LPx;
		m_pSharedMemory->XYZreal[1]=(float)LPy;
		m_pSharedMemory->XYZreal[2]=(float)LPz;
		
		m_pSharedMemory->XYZreal[3]=(float)RPx;
		m_pSharedMemory->XYZreal[4]=(float)RPy;
		m_pSharedMemory->XYZreal[5]=(float)RPz;

		for(i=0;i<12;i++)
		{
			m_pSharedMemory->XYZDelta[i] = m_pSharedMemory->XYZreal[i] - m_pSharedMemory->XYZref[i];
			m_pSharedMemory->XYZref[i]   = m_pSharedMemory->XYZref[i]  + m_pSharedMemory->XYZDelta[i];
		}
		Sleep(100);

		oldmode = 0;
	}

	else if(mode==2) // inverse->forward
	{
		for(int i=0;i<TOTAL_MTR_NUM;i++)
		{
			m_pSharedMemory->Deltheta[i]=m_pSharedMemory->Realtheta[i]-m_pSharedMemory->Reftheta[i];
			m_pSharedMemory->Reftheta[i]=m_pSharedMemory->Reftheta[i]+m_pSharedMemory->Deltheta[i];
		}
		m_pSharedMemory->DelAnkleRoll[0] = m_pSharedMemory->Reftheta[LAR] - m_pSharedMemory->InitAnkleRoll[0];
		m_pSharedMemory->DelAnkleRoll[1] = m_pSharedMemory->Reftheta[RAR] - m_pSharedMemory->InitAnkleRoll[1];
		Sleep(100);
	}
}


void CKhr3winApp::Send_Each_RunCMD(unsigned char MoID, unsigned char Mode)
{
	unsigned char TxData[8];
	TxData[0] = MoID;
	TxData[1] = RunCMD;
	TxData[2] = Mode;
	m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 3);
}

void CKhr3winApp::Each_Stop_CMD(unsigned char MoID)
{
	unsigned char TxData[8];
	TxData[0] = MoID;
    TxData[1] = StopCMD;
	m_CanWinAPP.CAN_WRITE(CMD_TXDF, TxData, 2);
}

void CKhr3winApp::Home(int T)
{
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][0] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][1] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][2] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][3] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][4] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][5] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][6] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][7] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][8] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][9] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][10] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][11] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][12] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][13] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][14] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][15] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][16] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][17] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][18] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][19] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][20] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][21] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][22] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][23] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][24] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][25] = 0.;
	theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[T-1][26] = 0.;
}

void CKhr3winApp::CAN_WRITE1(unsigned int CAN_ID, unsigned char TxData[], unsigned char TxDlc)
{
	theApp.m_pSharedMemory->Tx1_ID = CAN_ID;
	
	for(int i=0; i<TxDlc; i++)
	{
		theApp.m_pSharedMemory->Tx1_Data[i] = TxData[i];
	}
	
	theApp.m_pSharedMemory->Tx1_DLC = TxDlc;
	theApp.m_pSharedMemory->Tx1_Flag = TRUE;
}
