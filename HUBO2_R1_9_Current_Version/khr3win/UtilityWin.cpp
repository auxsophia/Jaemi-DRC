// UtilityWin.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "UtilityWin.h"
#include "Khr3winDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUtilityWin dialog
extern CKhr3winApp theApp;

CUtilityWin::CUtilityWin(CWnd* pParent /*=NULL*/)
	: CDialog(CUtilityWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUtilityWin)
	m_L_Ankle_Pitch = -21.0356696568582;
	m_L_Ankle_Roll = -0.409248619733057;
	m_L_Hip_Pitch = -21.0356696568582;
	m_L_Hip_Roll = 0.409248619733057;
	m_L_Knee_Pitch = 42.0713393137164;
	m_L_Px = 0.0f;
	m_L_Py = L0+4.;
	m_L_Pz = -(L1+L2)+40.;
	m_L_Yaw = 0.0f;
	m_R_Ankle_Pitch = -21.0356696568582;
	m_R_Ankle_Roll = 0.409248619733057;
	m_R_Hip_Pitch = -21.0356696568582;
	m_R_Hip_Roll = -0.409248619733057;
	m_R_Knee_Pitch = 42.0713393137164;

	m_R_Px = 0.0f;
	m_R_Py = -L0-4.;
	m_R_Pz = -(L1+L2)+40.;
	m_R_Yaw = 0.0f;
	m_R_FRD_Yaw = 0.0f;
	m_L_FRD_Yaw = 0.0f;
	//}}AFX_DATA_INIT
}


void CUtilityWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUtilityWin)
	DDX_Text(pDX, IDC_EDIT_LANKLEPITCH, m_L_Ankle_Pitch);
	DDX_Text(pDX, IDC_EDIT_LANKLEROLL, m_L_Ankle_Roll);
	DDX_Text(pDX, IDC_EDIT_LHIPPITCH, m_L_Hip_Pitch);
	DDX_Text(pDX, IDC_EDIT_LHIPROLL, m_L_Hip_Roll);
	DDX_Text(pDX, IDC_EDIT_LKNEE, m_L_Knee_Pitch);
	DDX_Text(pDX, IDC_EDIT_LPX, m_L_Px);
	DDX_Text(pDX, IDC_EDIT_LPY, m_L_Py);
	DDX_Text(pDX, IDC_EDIT_LPZ, m_L_Pz);
	DDX_Text(pDX, IDC_EDIT_LYAW, m_L_Yaw);
	DDX_Text(pDX, IDC_EDIT_RANKLEPITCH, m_R_Ankle_Pitch);
	DDX_Text(pDX, IDC_EDIT_RANKLEROLL, m_R_Ankle_Roll);
	DDX_Text(pDX, IDC_EDIT_RHIPPITCH, m_R_Hip_Pitch);
	DDX_Text(pDX, IDC_EDIT_RHIPROLL, m_R_Hip_Roll);
	DDX_Text(pDX, IDC_EDIT_RKNEEPITCH, m_R_Knee_Pitch);
	DDX_Text(pDX, IDC_EDIT_RPY, m_R_Py);
	DDX_Text(pDX, IDC_EDIT_RPX, m_R_Px);
	DDX_Text(pDX, IDC_EDIT_RPZ, m_R_Pz);
	DDX_Text(pDX, IDC_EDIT_RYAW, m_R_Yaw);
	DDX_Text(pDX, IDC_EDIT_FRD_RYAW, m_R_FRD_Yaw);
	DDX_Text(pDX, IDC_EDIT_FRD_LYAW, m_L_FRD_Yaw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUtilityWin, CDialog)
	//{{AFX_MSG_MAP(CUtilityWin)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SOLVE_FORWARD, OnButtonSolveForward)
	ON_BN_CLICKED(IDC_BUTTON_SOLVE_INVERSE, OnButtonSolveInverse)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATER, OnButtonCalculater)
	ON_BN_CLICKED(IDC_BUTTON_NOTE_PAD, OnButtonNotePad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUtilityWin message handlers

void CUtilityWin::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	OnOK();	
}

void CUtilityWin::OnButtonSolveForward() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.FrdKineWin(m_L_FRD_Yaw,m_L_Hip_Roll,m_L_Hip_Pitch,m_L_Knee_Pitch,m_L_Ankle_Pitch,m_L_Ankle_Roll,
					  m_R_FRD_Yaw,m_R_Hip_Roll,m_R_Hip_Pitch,m_R_Knee_Pitch,m_R_Ankle_Pitch,m_R_Ankle_Roll);

	m_L_Yaw=m_L_FRD_Yaw;
	m_L_Px=theApp.LPx;
	m_L_Py=theApp.LPy;
	m_L_Pz=theApp.LPz;

	m_R_Yaw=m_R_FRD_Yaw;
	m_R_Px=theApp.RPx;
	m_R_Py=theApp.RPy;
	m_R_Pz=theApp.RPz;

	UpdateData(FALSE);
}

void CUtilityWin::OnButtonSolveInverse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(theApp.InvKineWin(m_L_Px,m_L_Py,m_L_Pz,m_L_Yaw,m_R_Px,m_R_Py,m_R_Pz,m_R_Yaw)==1)
	{

	m_L_FRD_Yaw=theApp.LegAngle[0];
	m_L_Hip_Roll=theApp.LegAngle[1];
	m_L_Hip_Pitch=theApp.LegAngle[2];
	m_L_Knee_Pitch=theApp.LegAngle[3];
	m_L_Ankle_Pitch=theApp.LegAngle[4];
	m_L_Ankle_Roll=theApp.LegAngle[5];

	m_R_FRD_Yaw=theApp.LegAngle[6];
	m_R_Hip_Roll=theApp.LegAngle[7];
	m_R_Hip_Pitch=theApp.LegAngle[8];
	m_R_Knee_Pitch=theApp.LegAngle[9];
	m_R_Ankle_Pitch=theApp.LegAngle[10];
	m_R_Ankle_Roll=theApp.LegAngle[11];
	}
	else MessageBox("Kinematics Error");

	UpdateData(FALSE);	
}

void CUtilityWin::OnButtonCalculater() 
{
	// TODO: Add your control notification handler code here
	WinExec("calc.exe",SW_SHOW);
}

void CUtilityWin::OnButtonNotePad() 
{
	// TODO: Add your control notification handler code here
	WinExec("notepad.exe",SW_SHOW);
}
