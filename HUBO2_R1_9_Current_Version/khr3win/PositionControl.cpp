// PositionControl.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Khr3winDlg.h"
#include "PositionControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPositionControl dialog

extern CKhr3winApp theApp;

CPositionControl::CPositionControl(CWnd* pParent /*=NULL*/)
	: CDialog(CPositionControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPositionControl)
	m_Pos_RHR = 0.0f;
	m_Pos_RHY = 0.0f;
	m_RPM_JMC0 = 0.0f;
	m_RPM_JMC1 = 0.0f;
	m_RPM_JMC2 = 0.0f;
	m_RPM_JMC3 = 0.0f;
	m_RPM_JMC4 = 0.0f;
	m_RPM_JMC5 = 0.0f;
	m_RPM_JMC6 = 0.0f;
	m_RPM_JMC7 = 0.0f;
	m_Pos_LAP = 0.0f;
	m_Pos_LAR = 0.0f;
	m_Pos_LHP = 0.0f;
	m_Pos_LHR = 0.0f;
	m_Pos_LHY = 0.0f;
	m_Pos_RAP = 0.0f;
	m_Pos_RAR = 0.0f;
	m_Pos_RHP = 0.0f;
	m_Pos_RKN = 0.0f;
	m_Pos_LKN = 0.0f;
	m_RPM_JMC10 = 0.0f;
	m_RPM_JMC11 = 0.0f;
	m_Pos_LSP = 0.0f;
	m_Pos_LEB = 0.0f;
	m_Pos_LSR = 0.0f;
	m_Pos_LSY = 0.0f;
	m_Pos_REB = 0.0f;
	m_Pos_RSP = 0.0f;
	m_Pos_RSR = 0.0f;
	m_Pos_RSY = 0.0f;
	m_RPM_JMC8 = 0.0f;
	m_RPM_JMC9 = 0.0f;
	m_RPM_EJMC0 = 0.0f;
	m_RPM_EJMC1 = 0.0f;
	m_RPM_EJMC2 = 0.0f;
	m_Pos_RW1 = 0.0f;
	m_Pos_RW2 = 0.0f;
	m_Pos_RWY = 0.0f;
	m_Pos_LW1 = 0.0f;
	m_Pos_LW2 = 0.0f;
	m_Pos_LWY = 0.0f;
	m_Pos_NK1 = 0.0f;
	m_Pos_NK2 = 0.0f;
	m_Pos_NKY = 0.0f;
	m_RPM_EJMC3 = 0.0f;
	m_Pos_WST = 0.0f;
	//}}AFX_DATA_INIT
	m_pKhr3winDlg = NULL;
}


void CPositionControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPositionControl)
	DDX_Text(pDX, IDC_EDIT_RHR, m_Pos_RHR);
	DDX_Text(pDX, IDC_EDIT_RHY, m_Pos_RHY);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC0, m_RPM_JMC0);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC1, m_RPM_JMC1);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC2, m_RPM_JMC2);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC3, m_RPM_JMC3);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC4, m_RPM_JMC4);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC5, m_RPM_JMC5);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC6, m_RPM_JMC6);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC7, m_RPM_JMC7);
	DDX_Text(pDX, IDC_EDIT_LAP, m_Pos_LAP);
	DDX_Text(pDX, IDC_EDIT_LAR, m_Pos_LAR);
	DDX_Text(pDX, IDC_EDIT_LHP, m_Pos_LHP);
	DDX_Text(pDX, IDC_EDIT_LHR, m_Pos_LHR);
	DDX_Text(pDX, IDC_EDIT_LHY, m_Pos_LHY);
	DDX_Text(pDX, IDC_EDIT_RAP, m_Pos_RAP);
	DDX_Text(pDX, IDC_EDIT_RAR, m_Pos_RAR);
	DDX_Text(pDX, IDC_EDIT_RHP, m_Pos_RHP);
	DDX_Text(pDX, IDC_EDIT_RKN, m_Pos_RKN);
	DDX_Text(pDX, IDC_EDIT_LKN, m_Pos_LKN);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC10, m_RPM_JMC10);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC11, m_RPM_JMC11);
	DDX_Text(pDX, IDC_EDIT_LSP, m_Pos_LSP);
	DDX_Text(pDX, IDC_EDIT_LEB, m_Pos_LEB);
	DDX_Text(pDX, IDC_EDIT_LSR, m_Pos_LSR);
	DDX_Text(pDX, IDC_EDIT_LSY, m_Pos_LSY);
	DDX_Text(pDX, IDC_EDIT_REB, m_Pos_REB);
	DDX_Text(pDX, IDC_EDIT_RSP, m_Pos_RSP);
	DDX_Text(pDX, IDC_EDIT_RSR, m_Pos_RSR);
	DDX_Text(pDX, IDC_EDIT_RSY, m_Pos_RSY);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC8, m_RPM_JMC8);
	DDX_Text(pDX, IDC_EDIT_RPM_JMC9, m_RPM_JMC9);
	DDX_Text(pDX, IDC_EDIT_RPM_EJMC0, m_RPM_EJMC0);
	DDX_Text(pDX, IDC_EDIT_RPM_EJMC1, m_RPM_EJMC1);
	DDX_Text(pDX, IDC_EDIT_RPM_EJMC2, m_RPM_EJMC2);
	DDX_Text(pDX, IDC_EDIT_RW1, m_Pos_RW1);
	DDX_Text(pDX, IDC_EDIT_RW2, m_Pos_RW2);
	DDX_Text(pDX, IDC_EDIT_RWY, m_Pos_RWY);
	DDX_Text(pDX, IDC_EDIT_LW1, m_Pos_LW1);
	DDX_Text(pDX, IDC_EDIT_LW2, m_Pos_LW2);
	DDX_Text(pDX, IDC_EDIT_LWY, m_Pos_LWY);
	DDX_Text(pDX, IDC_EDIT_NK1, m_Pos_NK1);
	DDX_Text(pDX, IDC_EDIT_NK2, m_Pos_NK2);
	DDX_Text(pDX, IDC_EDIT_NKY, m_Pos_NKY);
	DDX_Text(pDX, IDC_EDIT_RPM_EJMC3, m_RPM_EJMC3);
	DDX_Text(pDX, IDC_EDIT_WST, m_Pos_WST);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPositionControl, CDialog)
	//{{AFX_MSG_MAP(CPositionControl)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_RUN0, OnButtonRun0)
	ON_BN_CLICKED(IDC_BUTTON_RUN1, OnButtonRun1)
	ON_BN_CLICKED(IDC_BUTTON_RUN2, OnButtonRun2)
	ON_BN_CLICKED(IDC_BUTTON_RUN3, OnButtonRun3)
	ON_BN_CLICKED(IDC_BUTTON_RUN4, OnButtonRun4)
	ON_BN_CLICKED(IDC_BUTTON_RUN5, OnButtonRun5)
	ON_BN_CLICKED(IDC_BUTTON_RUN6, OnButtonRun6)
	ON_BN_CLICKED(IDC_BUTTON_RUN7, OnButtonRun7)
	ON_BN_CLICKED(IDC_BUTTON_RUN8, OnButtonRun8)
	ON_BN_CLICKED(IDC_BUTTON_RUN9, OnButtonRun9)
	ON_BN_CLICKED(IDC_BUTTON_RUN10, OnButtonRun10)
	ON_BN_CLICKED(IDC_BUTTON_RUN11, OnButtonRun11)
	ON_BN_CLICKED(IDC_BUTTON_RUN12, OnButtonRun12)
	ON_BN_CLICKED(IDC_BUTTON_RUN13, OnButtonRun13)
	ON_BN_CLICKED(IDC_BUTTON_POSE1, OnButtonPose1)
	ON_BN_CLICKED(IDC_BUTTON_POSE_HOME, OnButtonPoseHome)
	ON_BN_CLICKED(IDC_BUTTON_RUN17, OnButtonRun17)
	ON_BN_CLICKED(IDC_BUTTON_RUN18, OnButtonRun18)
	ON_BN_CLICKED(IDC_BUTTON_RUN19, OnButtonRun19)
	ON_BN_CLICKED(IDC_BUTTON_RUN23, OnButtonRun23)
	ON_BN_CLICKED(IDC_BUTTON_RUN24, OnButtonRun24)
	ON_BN_CLICKED(IDC_BUTTON_RUN25, OnButtonRun25)
	ON_BN_CLICKED(IDC_BUTTON_RUN16, OnButtonRun16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPositionControl message handlers

void CPositionControl::Init()
{
	unsigned char i;

	theApp.m_pSharedMemory->INT_Flag = FALSE;
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	UpdateData(FALSE);
	Sleep(50);	
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
	}

	for(i=32;i<(32+TOTAL_EJMC_NUM);i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
	}
	
	
	for(int j = 0; j < TOTAL_MTR_NUM; j++)
	{
		theApp.m_pSharedMemory->Reftheta[j] = theApp.m_pSharedMemory->theta[j];
	}
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.SendRunCMD(i);
		Sleep(50);
	}

	for(i=32;i<(32+TOTAL_EJMC_NUM);i++)
	{
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	theApp.m_pSharedMemory->POS_CTRL_Flag = ENABLE;
	theApp.m_pSharedMemory->INT_Flag = TRUE;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
}

void CPositionControl::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	Close();
}

void CPositionControl::Close()
{
	m_pKhr3winDlg->ButtonControl(POS_CLOSE);
	theApp.m_pSharedMemory->POS_CTRL_Flag = DISABLE;

	DestroyWindow();
}

void CPositionControl::OnButtonRun0() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(0);
}

void CPositionControl::OnButtonRun1() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(1);
}

void CPositionControl::OnButtonRun2() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(2);	
}

void CPositionControl::OnButtonRun3() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(3);
}

void CPositionControl::OnButtonRun4() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(4);
}

void CPositionControl::OnButtonRun5() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(5);	
}

void CPositionControl::OnButtonRun6() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(6);
}

void CPositionControl::OnButtonRun7() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(7);
}

void CPositionControl::OnButtonRun8() 
{
	// TODO: Add your control notification handler code here
	//POS_CTRL_Run(8);
	POS_CTRL_Run(JMC8);
}

void CPositionControl::OnButtonRun9() 
{
	// TODO: Add your control notification handler code here
	//POS_CTRL_Run(9);
	POS_CTRL_Run(JMC9);
}

void CPositionControl::OnButtonRun10() 
{
	// TODO: Add your control notification handler code here
	//POS_CTRL_Run(10);
	POS_CTRL_Run(JMC10);
}

void CPositionControl::OnButtonRun11() 
{
	// TODO: Add your control notification handler code here
	//POS_CTRL_Run(11);
	POS_CTRL_Run(JMC11);
}

void CPositionControl::OnButtonRun12() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(12);
}

void CPositionControl::OnButtonRun13() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(13);
}

void CPositionControl::POS_CTRL_Run(int numJMC)
{
	//int i;

	theApp.m_pSharedMemory->RTX_Index = 0;

 	UpdateData(TRUE);

	m_RPM[0] = m_RPM_JMC0;
	m_POS[RHY] = m_Pos_RHY;	m_POS[RHR] = m_Pos_RHR;
	
	m_RPM[1] = m_RPM_JMC1;
	m_POS[RHP] = m_Pos_RHP;

	m_RPM[2] = m_RPM_JMC2;
	m_POS[RKN] = m_Pos_RKN;

	m_RPM[3] = m_RPM_JMC3;
	m_POS[RAP] = m_Pos_RAP;	m_POS[RAR] = m_Pos_RAR;

	m_RPM[4] = m_RPM_JMC4;
	m_POS[LHY] = m_Pos_LHY;	m_POS[LHR] = m_Pos_LHR;
	
	m_RPM[5] = m_RPM_JMC5;
	m_POS[LHP] = m_Pos_LHP;
	
	m_RPM[6] = m_RPM_JMC6;
	m_POS[LKN] = m_Pos_LKN;
	
	m_RPM[7] = m_RPM_JMC7;
	m_POS[LAP] = m_Pos_LAP;	m_POS[LAR] = m_Pos_LAR;

	m_RPM[8] = m_RPM_JMC8;
	m_POS[RSP] = m_Pos_RSP;	m_POS[RSR] = m_Pos_RSR;

	m_RPM[9] = m_RPM_JMC9;
	m_POS[RSY] = m_Pos_RSY;	m_POS[REB] = m_Pos_REB;

	m_RPM[10] = m_RPM_JMC10;
	m_POS[LSP] = m_Pos_LSP;	m_POS[LSR] = m_Pos_LSR;
	
	m_RPM[11] = m_RPM_JMC11;
	m_POS[LSY] = m_Pos_LSY;	m_POS[LEB] = m_Pos_LEB;

	m_RPM[EJMC0] = m_RPM_EJMC0;
	m_POS[RWY] = m_Pos_RWY;	m_POS[RW1] = m_Pos_RW1;	m_POS[RW2] = m_Pos_RW2;

	m_RPM[EJMC1] = m_RPM_EJMC1;
	m_POS[LWY] = m_Pos_LWY;	m_POS[LW1] = m_Pos_LW1;	m_POS[LW2] = m_Pos_LW2;

	m_RPM[EJMC2] = m_RPM_EJMC2;
	m_POS[NKY] = m_Pos_NKY;	m_POS[NK1] = m_Pos_NK1;	m_POS[NK2] = m_Pos_NK2;

	m_RPM[EJMC3] = m_RPM_EJMC3;
	m_POS[WST] = m_Pos_WST;
	
	switch(numJMC)
	{
	case 0:
		theApp.WINmoveANG_RPM(RHY, m_POS[RHY],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(RHR, m_POS[RHR],m_RPM[numJMC]);
		break;
	case 1:
		theApp.WINmoveANG_RPM(RHP, m_POS[RHP],m_RPM[numJMC]);
		break;
	case 2:
		theApp.WINmoveANG_RPM(RKN, m_POS[RKN],m_RPM[numJMC]);
		break;
	case 3:
		theApp.WINmoveANG_RPM(RAP, m_POS[RAP],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(RAR, m_POS[RAR],m_RPM[numJMC]);
	case 4:
		theApp.WINmoveANG_RPM(LHY, m_POS[LHY],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LHR, m_POS[LHR],m_RPM[numJMC]);
		break;
	case 5:
		theApp.WINmoveANG_RPM(LHP, m_POS[LHP],m_RPM[numJMC]);
		break;
	case 6:
		theApp.WINmoveANG_RPM(LKN, m_POS[LKN],m_RPM[numJMC]);
		break;
	case 7:
		theApp.WINmoveANG_RPM(LAP, m_POS[LAP],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LAR, m_POS[LAR],m_RPM[numJMC]);
		break;
	case JMC8:
		theApp.WINmoveANG_RPM(RSP, m_POS[RSP],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(RSR, m_POS[RSR],m_RPM[numJMC]);
		break;
	case JMC9:
		theApp.WINmoveANG_RPM(RSY, m_POS[RSY],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(REB, m_POS[REB],m_RPM[numJMC]);
		break;
	case JMC10:
		theApp.WINmoveANG_RPM(LSP, m_POS[LSP],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LSR, m_POS[LSR],m_RPM[numJMC]);
		break;
	case JMC11:
		theApp.WINmoveANG_RPM(LSY, m_POS[LSY],m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LEB, m_POS[LEB],m_RPM[numJMC]);
		break;
	case EJMC0:
		theApp.WINmoveANG_RPM(RWY, m_POS[RWY], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(RW1, m_POS[RW1], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(RW2, m_POS[RW2], m_RPM[numJMC]);
		break;
	case EJMC1:
		theApp.WINmoveANG_RPM(LWY, m_POS[LWY], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LW1, m_POS[LW1], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(LW2, m_POS[LW2], m_RPM[numJMC]);
		break;
	case EJMC2:
		theApp.WINmoveANG_RPM(NKY, m_POS[NKY], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(NK1, m_POS[NK1], m_RPM[numJMC]);
		theApp.WINmoveANG_RPM(NK2, m_POS[NK2], m_RPM[numJMC]);
		break;
	case EJMC3:
		theApp.WINmoveANG_RPM(WST, m_POS[WST], m_RPM[numJMC]);
	/*
	case 20:
		theApp.WINmoveANG_RPM(RHY, m_POS[RHY],m_RPM[0]);
		theApp.WINmoveANG_RPM(RHR, m_POS[RHR],m_RPM[0]);
		theApp.WINmoveANG_RPM(RHP, m_POS[RHP],m_RPM[0]);
		theApp.WINmoveANG_RPM(RKN, m_POS[RKN],m_RPM[0]);
		theApp.WINmoveANG_RPM(RAP, m_POS[RAP],m_RPM[0]);
		theApp.WINmoveANG_RPM(RAR, m_POS[RAR],m_RPM[0]);
		break;
	case 21:
		theApp.WINmoveANG_RPM(LHY, m_POS[LHY],m_RPM[4]);
		theApp.WINmoveANG_RPM(LHR, m_POS[LHR],m_RPM[4]);
		theApp.WINmoveANG_RPM(LHP, m_POS[LHP],m_RPM[4]);
		theApp.WINmoveANG_RPM(LKN, m_POS[LKN],m_RPM[4]);
		theApp.WINmoveANG_RPM(LAP, m_POS[LAP],m_RPM[4]);
		theApp.WINmoveANG_RPM(LAR, m_POS[LAR],m_RPM[4]);
		break;
	case 22:
		theApp.WINmoveANG_RPM(RHY, m_POS[RHY],m_RPM[0]);
		theApp.WINmoveANG_RPM(RHR, m_POS[RHR],m_RPM[0]);
		theApp.WINmoveANG_RPM(RHP, m_POS[RHP],m_RPM[0]);
		theApp.WINmoveANG_RPM(RKN, m_POS[RKN],m_RPM[0]);
		theApp.WINmoveANG_RPM(RAP, m_POS[RAP],m_RPM[0]);
		theApp.WINmoveANG_RPM(RAR, m_POS[RAR],m_RPM[0]);
		theApp.WINmoveANG_RPM(LHY, m_POS[LHY],m_RPM[0]);
		theApp.WINmoveANG_RPM(LHR, m_POS[LHR],m_RPM[0]);
		theApp.WINmoveANG_RPM(LHP, m_POS[LHP],m_RPM[0]);
		theApp.WINmoveANG_RPM(LKN, m_POS[LKN],m_RPM[0]);
		theApp.WINmoveANG_RPM(LAP, m_POS[LAP],m_RPM[0]);
		theApp.WINmoveANG_RPM(LAR, m_POS[LAR],m_RPM[0]);
		break;
		*/
	}
		

}

void CPositionControl::OnButtonPose1() 
{
	// TODO: Add your control notification handler code here
	char	i;
	float	Pose1[TOTAL_MTR_NUM];
	float	tp_rpm;

	Pose1[0] = 0.;
	Pose1[1] = 0.;
	Pose1[2] = 0.;
	Pose1[3] = 0.;
	Pose1[4] = 0.;
	
	Pose1[5] = 0.;
	Pose1[6] = 0.;
	Pose1[7] = 0.;
	Pose1[8] = 0.;
	Pose1[9] = 0.;
	
	Pose1[10] = 0.;
	Pose1[11] = 0.;
	Pose1[12] = 0.;
	Pose1[13] = 0.;
	Pose1[14] = 0.;
	
	Pose1[15] = 0.;
	Pose1[16] = 0.;
	Pose1[17] = 0.;
	Pose1[18] = 0.;
	Pose1[19] = 0.;
	
	Pose1[20] = 0.;
	Pose1[21] = 0.;
	Pose1[22] = 0.;
	Pose1[23] = 0.;
	Pose1[24] = 0.;

	Pose1[25] = 0.;
	Pose1[26] = 0.;
	Pose1[27] = 0.;
	Pose1[28] = 0.;
	
	/*
	Pose1[29] = 0.;
	Pose1[30] = (float)-0.4092486;
	Pose1[31] = (float)-21.0356696;
	Pose1[32] = (float)42.0713393;
	Pose1[33] = (float)-21.0356696;
	Pose1[34] = (float)0.4092486;
	
	Pose1[35] = 0.;
	Pose1[36] = (float)0.4092486;
	Pose1[37] = (float)-21.0356696;
	Pose1[38] = (float)42.0713393;
	Pose1[39] = (float)-21.0356696;
	Pose1[40] = (float)-0.4092486;
	*/

	Pose1[RHY] = 3.;
	Pose1[RHR] = 3.;
	Pose1[RHP] = 3.;
	Pose1[RKN] = 3.;
	Pose1[RAP] = 3.;
	Pose1[RAR] = 3.;

	Pose1[LHY] = 3.;
	Pose1[LHR] = 3.;
	Pose1[LHP] = 3.;
	Pose1[LKN] = 3.;
	Pose1[LAP] = 3.;
	Pose1[LAR] = 3.;

	tp_rpm = (float)0.2;

	for(i=0;i<TOTAL_MTR_NUM;i++)	theApp.WINmoveANG_RPM(i,Pose1[i], tp_rpm);

	
	m_RPM[0] = (float)tp_rpm;
	m_Pos_RHY = Pose1[RHY];	m_Pos_RHR = Pose1[RHR];
	
	m_RPM[1] = (float)tp_rpm;
	m_Pos_RHP = Pose1[RHP];
	
	m_RPM[2] = (float)tp_rpm;
	m_Pos_RKN = Pose1[RKN];
	
	m_RPM[3] = (float)tp_rpm;
	m_Pos_RAP = Pose1[RAP];	m_Pos_RAR = Pose1[RAR];
	
	m_RPM[4] = (float)tp_rpm;
	m_Pos_LHY = Pose1[LHY];	m_Pos_LHR = Pose1[LHR];
	
	m_RPM[5] = (float)tp_rpm;
	m_Pos_LHP = Pose1[LHP]; 
	
	m_RPM[6] = (float)tp_rpm;
	m_Pos_LKN = Pose1[LKN];
	
	m_RPM[7] = (float)tp_rpm;
	m_Pos_LAP = Pose1[LAP];	m_Pos_LAR = Pose1[LAR];

	UpdateData(FALSE);
}

void CPositionControl::OnButtonPoseHome() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	char	i;
	float	Pose1[TOTAL_MTR_NUM];
	float tp_rpm;
	
	Pose1[0] = 0.;
	Pose1[1] = 0.;
	Pose1[2] = 0.;
	Pose1[3] = 0.;
	Pose1[4] = 0.;
	
	Pose1[5] = 0.;
	Pose1[6] = 0.;
	Pose1[7] = 0.;
	Pose1[8] = 0.;
	Pose1[9] = 0.;
	
	Pose1[10] = 0.;
	Pose1[11] = 0.;
	Pose1[12] = 0.;
	Pose1[13] = 0.;
	Pose1[14] = 0.;
	
	Pose1[15] = 0.;
	Pose1[16] = 0.;
	Pose1[17] = 0.;
	Pose1[18] = 0.;
	Pose1[19] = 0.;
	
	Pose1[RSP] = 0.;
	Pose1[RSR] = 0.;
	Pose1[RSY] = 0.;
	Pose1[REB] = 0.;
		
	Pose1[LSP] = 0.;
	Pose1[LSR] = 0.;
	Pose1[LSY] = 0.;
	Pose1[LEB] = 0.;
	
	Pose1[WST] = 0.;

	Pose1[RHY] = 0.;
	Pose1[RHR] = 0.;
	Pose1[RHP] = 0.;
	Pose1[RKN] = 0.;
	Pose1[RAP] = 0.;
	Pose1[RAR] = 0.;
	
	Pose1[LHY] = 0.;
	Pose1[LHR] = 0.;
	Pose1[LHP] = 0.;
	Pose1[LKN] = 0.;
	Pose1[LAP] = 0.;
	Pose1[LAR] = 0.;
	
	tp_rpm = (float)0.2;

	for(i=0;i<TOTAL_MTR_NUM;i++)	theApp.WINmoveANG_RPM(i,Pose1[i], tp_rpm);

	m_RPM[0] = (float)tp_rpm;
	m_Pos_RHY = Pose1[RHY];	m_Pos_RHR = Pose1[RHR];
	
	m_RPM[1] = (float)tp_rpm;
	m_Pos_RHP = Pose1[RHP];
	
	m_RPM[2] = (float)tp_rpm;
	m_Pos_RKN = Pose1[RKN];
	
	m_RPM[3] = (float)tp_rpm;
	m_Pos_RAP = Pose1[RAP];	m_Pos_RAR = Pose1[RAR];
	
	m_RPM[4] = (float)tp_rpm;
	m_Pos_LHY = Pose1[LHY];	m_Pos_LHR = Pose1[LHR];
	
	m_RPM[5] = (float)tp_rpm;
	m_Pos_LHP = Pose1[LHP]; 
	
	m_RPM[6] = (float)tp_rpm;
	m_Pos_LKN = Pose1[LKN];
	
	m_RPM[7] = (float)tp_rpm;
	m_Pos_LAP = Pose1[LAP];	m_Pos_LAR = Pose1[LAR];
	
	UpdateData(FALSE);	
}

void CPositionControl::OnButtonRun17() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(20);	// move right leg
}

void CPositionControl::OnButtonRun18() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(21);	// move left leg
}

void CPositionControl::OnButtonRun19() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(22);	// move both leg
}

void CPositionControl::OnButtonRun23() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(EJMC0);
}

void CPositionControl::OnButtonRun24() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(EJMC1);
}

void CPositionControl::OnButtonRun25() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(EJMC2);	
}

void CPositionControl::OnButtonRun16() 
{
	// TODO: Add your control notification handler code here
	POS_CTRL_Run(EJMC3);	
}
