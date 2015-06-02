// ZMPZeroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "ZMPZeroDlg.h"
#include "FT_ReadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZMPZeroDlg dialog

extern CKhr3winApp theApp;

CZMPZeroDlg::CZMPZeroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZMPZeroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZMPZeroDlg)
	m_FT_LFz = 0.0f;
	m_FT_LMx = 0.0f;
	m_FT_LMy = 0.0f;
	m_FT_RFz = 0.0f;
	m_FT_RMx = 0.0f;
	m_FT_RMy = 0.0f;
	m_FT_X_ZMP = 0.0f;
	m_FT_Y_ZMP = 0.0f;
	m_FltAccP1 = 0.0f;
	m_FltAccR1 = 0.0f;
	m_ACC_P = 0;
	m_ACC_R = 0;
	m_Lx = 0.0f;
	m_Ly = 0.0f;
	m_Lz = 0.0f;
	m_Rx = 0.0f;
	m_Ry = 0.0f;
	m_Rz = 0.0f;
	m_ZmpOffset = 0.0f;
	//}}AFX_DATA_INIT
}


void CZMPZeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZMPZeroDlg)
	DDX_Control(pDX, IDC_BUTTON_ACC_RESET, m_Foot_ACC_Reset);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_Button_Right);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_Button_Left);
	DDX_Control(pDX, IDC_BUTTON_START, m_ZMP_Start);
	DDX_Text(pDX, IDC_EDIT_L_Fz, m_FT_LFz);
	DDX_Text(pDX, IDC_EDIT_L_Mx, m_FT_LMx);
	DDX_Text(pDX, IDC_EDIT_L_My, m_FT_LMy);
	DDX_Text(pDX, IDC_EDIT_R_Fz, m_FT_RFz);
	DDX_Text(pDX, IDC_EDIT_R_Mx, m_FT_RMx);
	DDX_Text(pDX, IDC_EDIT_R_My, m_FT_RMy);
	DDX_Text(pDX, IDC_EDIT_X_ZMP, m_FT_X_ZMP);
	DDX_Text(pDX, IDC_EDIT_Y_ZMP, m_FT_Y_ZMP);
	DDX_Text(pDX, IDC_EDIT_ACC_PITCH_LPF, m_FltAccP1);
	DDX_Text(pDX, IDC_EDIT_ACC_ROLL_LPF, m_FltAccR1);
	DDX_Text(pDX, IDC_EDIT_ACC_PITCH_RAW, m_ACC_P);
	DDX_Text(pDX, IDC_EDIT_ACC_ROLL_RAW, m_ACC_R);
	DDX_Text(pDX, IDC_EDIT_Lx, m_Lx);
	DDX_Text(pDX, IDC_EDIT_Ly, m_Ly);
	DDX_Text(pDX, IDC_EDIT_Lz, m_Lz);
	DDX_Text(pDX, IDC_EDIT_Rx, m_Rx);
	DDX_Text(pDX, IDC_EDIT_Ry, m_Ry);
	DDX_Text(pDX, IDC_EDIT_Rz, m_Rz);
	DDX_Text(pDX, IDC_EDIT_ZMP_OFFSET, m_ZmpOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZMPZeroDlg, CDialog)
	//{{AFX_MSG_MAP(CZMPZeroDlg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LEFT_Y, OnButtonLeftY)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_Y, OnButtonRightY)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD_P, OnButtonForwardP)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD_P, OnButtonBackwardP)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_ACC_RESET, OnButtonAccReset)
	ON_BN_CLICKED(IDC_BUTTON_NULL_FT, OnButtonNullFt)
	ON_BN_CLICKED(IDC_BUTTON_INCL_RESET, OnButtonInclReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZMPZeroDlg message handlers

void CZMPZeroDlg::Init()
{
	WalkReady();
	m_Foot_ACC_Reset.EnableWindow(FALSE);
	SetTimer(1,DISP_TIMER,NULL);
}

void CZMPZeroDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag	=	FALSE;
	theApp.m_pSharedMemory->ZMP_Zero_Set_Flag	=	FALSE;
	KillTimer(1);
	OnOK();
	DestroyWindow();
}

void CZMPZeroDlg::WalkReady()
{
	////// Joint Lock Enable
//theApp.KineChange(2); // Forward Mode Offset Set
//theApp.KineChange(3); // Inverse Mode Offset Set

	unsigned char i;
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	
	

	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[0]=-1;
	
	theApp.m_pSharedMemory->Walk_Ready_Flag = TRUE;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;

	theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag =	TRUE;
	theApp.m_pSharedMemory->ZMP_Zero_Set_Flag =	FALSE;
}

void CZMPZeroDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	CString	ButtonText;

	m_ZMP_Start.GetWindowText(ButtonText);
	if(ButtonText == "FT Null")
	{
		m_ZMP_Start.EnableWindow(FALSE);
		
		//((CFT_ReadDlg*)AfxGetApp())->FT_Disable();
		theApp.m_pSharedMemory->INT_Flag = FALSE;
		//Sleep(100);
		Sleep(200);
		((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT1,0);
		//Sleep(100);				// 중요 !!!
		Sleep(200);
		((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT2,0);  // Null ALL CHANNELS
		//Sleep(100);
		Sleep(200);
		((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT3,0);  // Null ALL CHANNELS
		//Sleep(100);
		Sleep(200);
		((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT4,0);  // Null ALL CHANNELS
		//Sleep(100);
		Sleep(200);

		//((CFT_ReadDlg*)AfxGetApp())->FT_Enable();
		theApp.m_pSharedMemory->INT_Flag = TRUE;
		
		m_Foot_ACC_Reset.EnableWindow(FALSE);
		m_ZMP_Start.EnableWindow();
		m_ZMP_Start.SetWindowText("Start");
	}
	else if(ButtonText == "Start")
	{
		theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
		theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag = TRUE;
		theApp.m_pSharedMemory->ZMP_Zero_Set_Flag = TRUE;

		theApp.m_pSharedMemory->DataSaveFlag = TRUE;
		theApp.m_pSharedMemory->PROFTime[11] = 0;

		m_ZMP_Start.SetWindowText("Set");

		m_Foot_ACC_Reset.EnableWindow(TRUE);
	}

	else if(ButtonText == "Set")
	{
		theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;

		theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag = FALSE;
		theApp.m_pSharedMemory->ZMP_Zero_Set_Flag = TRUE;
//		theApp.KineChange(2);
		m_ZMP_Start.EnableWindow(FALSE);
		m_Foot_ACC_Reset.EnableWindow(FALSE);
		Sleep(2000);

		theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag = FALSE;
		theApp.m_pSharedMemory->ZMP_Zero_Set_Flag = FALSE;

		AfxMessageBox("Posture initialization is done");
//		theApp.KineChange(2);
	}
}

void CZMPZeroDlg::OnButtonLeft() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Zmp_Zero_Offset += 0.5;
}

void CZMPZeroDlg::OnButtonRight() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Zmp_Zero_Offset -= 0.5;
}

void CZMPZeroDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	m_Button_Left.EnableWindow(FALSE);
	m_Button_Right.EnableWindow(FALSE);
}

void CZMPZeroDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	DispUpdate();

	CDialog::OnTimer(nIDEvent);
}

void CZMPZeroDlg::DispUpdate()
{
	m_FT_LFz = theApp.m_pSharedMemory->N_LFOOT_Fz;
	m_FT_LMx = theApp.m_pSharedMemory->NM_LFOOT_Mx;
	m_FT_LMy = theApp.m_pSharedMemory->NM_LFOOT_My;
	m_FT_RFz = theApp.m_pSharedMemory->N_RFOOT_Fz;
	m_FT_RMx = theApp.m_pSharedMemory->NM_RFOOT_Mx;
	m_FT_RMy = theApp.m_pSharedMemory->NM_RFOOT_My;
	m_FT_X_ZMP = theApp.m_pSharedMemory->Xzmp;
	m_FT_Y_ZMP = theApp.m_pSharedMemory->Yzmp;
	
	//m_FltAccP1 = theApp.m_pSharedMemory->Flt_AccP1;
	//m_FltAccR1 = theApp.m_pSharedMemory->Flt_AccR1;
	
	m_ACC_P = theApp.m_pSharedMemory->ACC_P;
	m_ACC_R = theApp.m_pSharedMemory->ACC_R;

	/*
	m_Lx = theApp.m_pSharedMemory->LeftAnkPos[0];
	m_Ly = theApp.m_pSharedMemory->LeftAnkPos[1];
	m_Lz = theApp.m_pSharedMemory->LeftAnkPos[2];

	m_Rx = theApp.m_pSharedMemory->RightAnkPos[0];
	m_Ry = theApp.m_pSharedMemory->RightAnkPos[1];
	m_Rz = theApp.m_pSharedMemory->RightAnkPos[2];
	*/
	m_Lx = theApp.m_pSharedMemory->L_px;
	m_Ly = theApp.m_pSharedMemory->L_py;
	m_Lz = theApp.m_pSharedMemory->L_pz;
	
	m_Rx = theApp.m_pSharedMemory->R_px;
	m_Ry = theApp.m_pSharedMemory->R_py;
	m_Rz = theApp.m_pSharedMemory->R_pz;

	m_ZmpOffset = theApp.m_pSharedMemory->Zmp_Zero_Offset;

	UpdateData(FALSE);
}

void CZMPZeroDlg::OnButtonLeftY() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Acc_Roll_Offset_Ini--;
}

void CZMPZeroDlg::OnButtonRightY()
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Acc_Roll_Offset_Ini++;
}

void CZMPZeroDlg::OnButtonForwardP() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Acc_Pitch_Offset_Ini--;	
}

void CZMPZeroDlg::OnButtonBackwardP() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Acc_Pitch_Offset_Ini++;	
}

void CZMPZeroDlg::OnButtonAccReset() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->FootAccReset = TRUE;
}

void CZMPZeroDlg::OnButtonNullFt() 
{
	// TODO: Add your control notification handler code here
	//((CFT_ReadDlg*)AfxGetApp())->FT_Disable();
	theApp.m_pSharedMemory->INT_Flag = FALSE;
	Sleep(100);
	((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT1,0);	// right F/T
	Sleep(100);				// 중요 !!!
	((CFT_ReadDlg*)AfxGetApp())->Null_CMD(FT2,0);  // Left F/T
	Sleep(100);
	//((CFT_ReadDlg*)AfxGetApp())->Null_CMD(RWT,0);  // Null ALL CHANNELS
	Sleep(100);
	//((CFT_ReadDlg*)AfxGetApp())->Null_CMD(LWT,0);  // Null ALL CHANNELS
	Sleep(100);
	
	//((CFT_ReadDlg*)AfxGetApp())->FT_Enable();
	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void CZMPZeroDlg::OnButtonInclReset() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Incl_Pitch_Offset = m_ACC_P;
	theApp.m_pSharedMemory->Incl_Roll_Offset = m_ACC_R;
}

void CZMPZeroDlg::autoSetup()
{

}
