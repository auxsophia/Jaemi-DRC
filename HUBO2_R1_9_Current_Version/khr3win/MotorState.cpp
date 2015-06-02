// MotorState.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "MotorState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotorState dialog

extern CKhr3winApp theApp;

CMotorState::CMotorState(CWnd* pParent /*=NULL*/)
	: CDialog(CMotorState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotorState)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMotorState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotorState)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMotorState, CDialog)
	//{{AFX_MSG_MAP(CMotorState)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotorState message handlers

void CMotorState::Init()
{
		theApp.m_pSharedMemory->Motor_State[RHP] = 0;

		SetTimer(1,1000,NULL);
}

void CMotorState::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(theApp.m_pSharedMemory->Motor_State[RHP] == ENC_FAIL) 
	{
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC1), TRUE);
	}
	else if(theApp.m_pSharedMemory->Motor_State[RHP] == MOTOR_JAM)
	{
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC2), TRUE);
	}
	else if(theApp.m_pSharedMemory->Motor_State[RHP] == FOLLOWER_FAIL)
	{
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC3), TRUE);
	}
	else
	{
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC1), FALSE);
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC2), FALSE);
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC3), FALSE);

	}
	CDialog::OnTimer(nIDEvent);
}

void CMotorState::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(1);
	theApp.m_pSharedMemory->Motor_State[RHP] = 0;
	CDialog::OnOK();
}
