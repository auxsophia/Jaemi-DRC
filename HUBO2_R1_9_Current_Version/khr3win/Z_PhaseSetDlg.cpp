// Z_PhaseSetDlg.cpp : implementation file
//

#include "CommonDefinition.h"
#include "stdafx.h"
#include "khr3win.h"
#include "Z_PhaseSetDlg.h"
#include "Z_PhaseEncoderViewDlg.h"
#include "fstream.h"
#include "..\MotorParameter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool autoSetupFlag = false;
bool autoSetupStopFlag = false;
int autoSetupCount = 0;
int autoSetupErrorCount = 0;

extern CKhr3winApp theApp;
CZ_PhaseEncoderViewDlg m_Z_PhaseEncoderViewDlg;

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseSetDlg dialog


CZ_PhaseSetDlg::CZ_PhaseSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZ_PhaseSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZ_PhaseSetDlg)
	m_LHP_Offset = 0;
	m_LHR_Offset = 0;
	m_LKP_Offset = 0;
	m_RHP_Offset = 0;
	m_RHR_Offset = 0;
	m_RKP_Offset = 0;
	m_LHY_Offset = 0;
	m_LAP_Offset = 0;
	m_LAR_Offset = 0;
	m_RAP_Offset = 0;
	m_RAR_Offset = 0;
	m_RHY_Offset = 0;
	m_LAP_Offset_Rev = 0;
	m_LAR_Offset_Rev = 0;
	m_LHP_Offset_Rev = 0;
	m_LHR_Offset_Rev = 0;
	m_LHY_Offset_Rev = 0;
	m_LKP_Offset_Rev = 0;
	m_RAP_Offset_Rev = 0;
	m_RAR_Offset_Rev = 0;
	m_RHP_Offset_Rev = 0;
	m_RHR_Offset_Rev = 0;
	m_RHY_Offset_Rev = 0;
	m_RKP_Offset_Rev = 0;
	m_ZPosRefFlag = FALSE;
	m_LEB_Offset = 0;
	m_LEB_Offset_Rev = 0;
	m_LSP_Offset = 0;
	m_LSP_Offset_Rev = 0;
	m_LSR_Offset = 0;
	m_LSR_Offset_Rev = 0;
	m_LSY_Offset = 0;
	m_LSY_Offset_Rev = 0;
	m_REB_Offset = 0;
	m_REB_Offset_Rev = 0;
	m_RSP_Offset = 0;
	m_RSP_Offset_Rev = 0;
	m_RSR_Offset = 0;
	m_RSR_Offset_Rev = 0;
	m_RSY_Offset = 0;
	m_RSY_Offset_Rev = 0;
	m_LWY_Offset = 0;
	m_LWY_Offset_Rev = 0;
	m_RWY_Offset = 0;
	m_RWY_Offset_Rev = 0;
	m_WST_Offset = 0;
	m_WST_Offset_Rev = 0;
	m_NKY_Offset = 0;
	m_NKY_Offset_Rev = 0;
	//}}AFX_DATA_INIT
}


void CZ_PhaseSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZ_PhaseSetDlg)
	DDX_Text(pDX, IDC_EDIT_LHP_OFFSET, m_LHP_Offset);
	DDV_MinMaxLong(pDX, m_LHP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LHR_OFFSET, m_LHR_Offset);
	DDV_MinMaxLong(pDX, m_LHR_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LKP_OFFSET, m_LKP_Offset);
	DDV_MinMaxLong(pDX, m_LKP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RHP_OFFSET, m_RHP_Offset);
	DDV_MinMaxLong(pDX, m_RHP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RHR_OFFSET, m_RHR_Offset);
	DDV_MinMaxLong(pDX, m_RHR_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RKP_OFFSET, m_RKP_Offset);
	DDV_MinMaxLong(pDX, m_RKP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LHY_OFFSET, m_LHY_Offset);
	DDV_MinMaxLong(pDX, m_LHY_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LAP_OFFSET, m_LAP_Offset);
	DDV_MinMaxLong(pDX, m_LAP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LAR_OFFSET, m_LAR_Offset);
	DDV_MinMaxLong(pDX, m_LAR_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RAP_OFFSET, m_RAP_Offset);
	DDV_MinMaxLong(pDX, m_RAP_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RAR_OFFSET, m_RAR_Offset);
	DDV_MinMaxLong(pDX, m_RAR_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_RHY_OFFSET, m_RHY_Offset);
	DDV_MinMaxLong(pDX, m_RHY_Offset, -4000, 4000);
	DDX_Text(pDX, IDC_EDIT_LAP_OFFSET_REV, m_LAP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LAP_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_LAR_OFFSET_REV, m_LAR_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LAR_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_LHP_OFFSET_REV, m_LHP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LHP_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_LHR_OFFSET_REV, m_LHR_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LHR_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_LHY_OFFSET_REV, m_LHY_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LHY_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_LKP_OFFSET_REV, m_LKP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_LKP_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RAP_OFFSET_REV, m_RAP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RAP_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RAR_OFFSET_REV, m_RAR_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RAR_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RHP_OFFSET_REV, m_RHP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RHP_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RHR_OFFSET_REV, m_RHR_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RHR_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RHY_OFFSET_REV, m_RHY_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RHY_Offset_Rev, 0, 200);
	DDX_Text(pDX, IDC_EDIT_RKP_OFFSET_REV, m_RKP_Offset_Rev);
	DDV_MinMaxLong(pDX, m_RKP_Offset_Rev, 0, 200);
	DDX_Check(pDX, IDC_CHECK_Z_POS_REF, m_ZPosRefFlag);
	DDX_Text(pDX, IDC_EDIT_LEB_OFFSET, m_LEB_Offset);
	DDX_Text(pDX, IDC_EDIT_LEB_OFFSET_REV, m_LEB_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_LSP_OFFSET, m_LSP_Offset);
	DDX_Text(pDX, IDC_EDIT_LSP_OFFSET_REV, m_LSP_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_LSR_OFFSET, m_LSR_Offset);
	DDX_Text(pDX, IDC_EDIT_LSR_OFFSET_REV, m_LSR_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_LSY_OFFSET, m_LSY_Offset);
	DDX_Text(pDX, IDC_EDIT_LSY_OFFSET_REV, m_LSY_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_REB_OFFSET, m_REB_Offset);
	DDX_Text(pDX, IDC_EDIT_REB_OFFSET_REV, m_REB_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_RSP_OFFSET, m_RSP_Offset);
	DDX_Text(pDX, IDC_EDIT_RSP_OFFSET_REV, m_RSP_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_RSR_OFFSET, m_RSR_Offset);
	DDX_Text(pDX, IDC_EDIT_RSR_OFFSET_REV, m_RSR_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_RSY_OFFSET, m_RSY_Offset);
	DDX_Text(pDX, IDC_EDIT_RSY_OFFSET_REV, m_RSY_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_LWY_OFFSET, m_LWY_Offset);
	DDX_Text(pDX, IDC_EDIT_LWY_OFFSET_REV, m_LWY_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_RWY_OFFSET, m_RWY_Offset);
	DDX_Text(pDX, IDC_EDIT_RWY_OFFSET_REV, m_RWY_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_WST_OFFSET, m_WST_Offset);
	DDX_Text(pDX, IDC_EDIT_WST_OFFSET_REV, m_WST_Offset_Rev);
	DDX_Text(pDX, IDC_EDIT_NKY_OFFSET, m_NKY_Offset);
	DDX_Text(pDX, IDC_EDIT_NKY_OFFSET_REV, m_NKY_Offset_Rev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZ_PhaseSetDlg, CDialog)
	//{{AFX_MSG_MAP(CZ_PhaseSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_ENC_SHOW, OnButtonEncShow)
	ON_BN_CLICKED(IDC_BUTTON_RHR_Z_POS, OnButtonRhrZPos)
	ON_BN_CLICKED(IDC_BUTTON_RHP_Z_POS, OnButtonRhpZPos)
	ON_BN_CLICKED(IDC_BUTTON_RKP_Z_POS, OnButtonRkpZPos)
	ON_BN_CLICKED(IDC_BUTTON_LHR_Z_POS, OnButtonLhrZPos)
	ON_BN_CLICKED(IDC_BUTTON_LHP_Z_POS, OnButtonLhpZPos)
	ON_BN_CLICKED(IDC_BUTTON_LKP_Z_POS, OnButtonLkpZPos)
	ON_BN_CLICKED(IDC_BUTTON_RHR_GO_OFFSET, OnButtonRhrGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RHP_GO_OFFSET, OnButtonRhpGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RKP_GO_OFFSET, OnButtonRkpGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LHR_GO_OFFSET, OnButtonLhrGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LHP_GO_OFFSET, OnButtonLhpGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LKP_GO_OFFSET, OnButtonLkpGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LHY_Z_POS, OnButtonLhyZPos)
	ON_BN_CLICKED(IDC_BUTTON_RHY_Z_POS, OnButtonRhyZPos)
	ON_BN_CLICKED(IDC_BUTTON_LAP_Z_POS, OnButtonLapZPos)
	ON_BN_CLICKED(IDC_BUTTON_LAR_Z_POS, OnButtonLarZPos)
	ON_BN_CLICKED(IDC_BUTTON_RAP_Z_POS, OnButtonRapZPos)
	ON_BN_CLICKED(IDC_BUTTON_RAR_Z_POS, OnButtonRarZPos)
	ON_BN_CLICKED(IDC_BUTTON_LHY_GO_OFFSET, OnButtonLhyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LAP_GO_OFFSET, OnButtonLapGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LAR_GO_OFFSET, OnButtonLarGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RHY_GO_OFFSET, OnButtonRhyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RAP_GO_OFFSET, OnButtonRapGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RAR_GO_OFFSET, OnButtonRarGoOffset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LSP_Z_POS, OnButtonLspZPos)
	ON_BN_CLICKED(IDC_BUTTON_LSR_Z_POS, OnButtonLsrZPos)
	ON_BN_CLICKED(IDC_BUTTON_LSY_Z_POS, OnButtonLsyZPos)
	ON_BN_CLICKED(IDC_BUTTON_LEB_Z_POS, OnButtonLebZPos)
	ON_BN_CLICKED(IDC_BUTTON_RSP_Z_POS, OnButtonRspZPos)
	ON_BN_CLICKED(IDC_BUTTON_RSY_Z_POS, OnButtonRsyZPos)
	ON_BN_CLICKED(IDC_BUTTON_RSR_Z_POS, OnButtonRsrZPos)
	ON_BN_CLICKED(IDC_BUTTON_REB_Z_POS, OnButtonRebZPos)
	ON_BN_CLICKED(IDC_BUTTON_RSP_GO_OFFSET, OnButtonRspGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RSR_GO_OFFSET, OnButtonRsrGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RSY_GO_OFFSET, OnButtonRsyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_REB_GO_OFFSET, OnButtonRebGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LSP_GO_OFFSET, OnButtonLspGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LSR_GO_OFFSET, OnButtonLsrGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LSY_GO_OFFSET, OnButtonLsyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LEB_GO_OFFSET, OnButtonLebGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_RWT_Z_POS, OnButtonRwtZPos)
	ON_BN_CLICKED(IDC_BUTTON_LWT_Z_POS, OnButtonLwtZPos)
	ON_BN_CLICKED(IDC_BUTTON_RWY_GO_OFFSET, OnButtonRwyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_LHD_Z_POS, OnButtonLhdZPos)
	ON_BN_CLICKED(IDC_BUTTON_RHD_Z_POS, OnButtonRhdZPos)
	ON_BN_CLICKED(IDC_BUTTON_WST_Z_POS, OnButtonWstZPos)
	ON_BN_CLICKED(IDC_BUTTON_WST_GO_OFFSET, OnButtonWstGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_NKY_Z_POS, OnButtonNkyZPos)
	ON_BN_CLICKED(IDC_BUTTON_NKY_GO_OFFSET, OnButtonNkyGoOffset)
	ON_BN_CLICKED(IDC_BUTTON_Z_REF_SAVE, OnButtonZRefSave)
	ON_BN_CLICKED(IDC_AutoSetup, OnAutoSetup)
	ON_BN_CLICKED(IDC_autoSetupStop, OnautoSetupStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseSetDlg message handlers

void CZ_PhaseSetDlg::Init()
{
	int i;

	/*
	m_RHR_Offset = 0;//-282;
	m_RHP_Offset = -364;
	m_RKP_Offset = -489;
	m_LHR_Offset = 0;//-350;
	m_LHP_Offset = -200;//-705;
	m_LKP_Offset = -145;
	*/

	m_ZPosRefFlag = TRUE;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD2), FALSE);

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD2), FALSE);

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST1), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST2), FALSE);
	
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD_FAIL), FALSE);

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT_FAIL), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD_FAIL), FALSE);

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST_FAIL), FALSE);
	
	for(i=0;i<TOTAL_MTR_NUM;i++)
	{
		m_Z_ref[i] = theApp.m_pSharedMemory->Z_Ref[i];
	}
	
	//m_Z_PhaseEncoderViewDlg.Create(IDD_DIALOG_Z_ENCODER,this);
	//m_Z_PhaseEncoderViewDlg.SetParentWindow(this);
	//m_Z_PhaseEncoderViewDlg.Init();
	//m_Z_PhaseEncoderViewDlg.ShowWindow(SW_SHOW);

	Sleep(50);
	UpdateData(FALSE);
	Sleep(50);
	
	/*
	for(i=0;i<TOTAL_JMC_NUM;i++) 
	{
		theApp.EnableHIP(i);
		Sleep(50);
	}

	for(i=EJMC0;i<(EJMC0+TOTAL_EJMC_NUM);i++) 
	{
		theApp.EnableHIP(i);
		Sleep(50);
	}
	*/

	
	/*

	for(int j = 0; j < TOTAL_MTR_NUM; j++)
	{
		theApp.m_pSharedMemory->Reftheta[j] = theApp.m_pSharedMemory->theta[j];
	}
	
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	*/
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;

	theApp.m_pSharedMemory->POS_CTRL_Flag = TRUE;
	
	/*
	theApp.Send_Each_RunCMD(RAR,0);  
	Sleep(30);
	theApp.Send_Each_RunCMD(LAR,0);
	Sleep(30);
	theApp.Send_Each_RunCMD(RAP,0);  
	Sleep(30);
	theApp.Send_Each_RunCMD(LAP,0);
	Sleep(30);
	theApp.Send_Each_RunCMD(WST,0);
	Sleep(30);
	theApp.Each_Stop_CMD(RAR);
	Sleep(30);
	theApp.Each_Stop_CMD(LAR);
	Sleep(30);
	theApp.Each_Stop_CMD(RAP);
	Sleep(30);
	theApp.Each_Stop_CMD(LAP);
	Sleep(30);
	theApp.Each_Stop_CMD(WST);
	*/
}

void CZ_PhaseSetDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
/*	theApp.m_pSharedMemory->INT_Flag = FALSE;
		
	unsigned char i;
	// Control Off Routine
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.SendCTRLOff(i);	// 제어를 끈다.
		Sleep(50);				// 중요!!! 시간  Delay 
		theApp.Stop_CMD(i);		// 중요 !!! PWM  을  영으로 확실히 셋팅
		Sleep(50);
	}
	
	theApp.m_pSharedMemory->POS_CTRL_Flag = DISABLE;

	// Encoder Zero Routine
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.Encoder_ZeroCMD(i);
		Sleep(50);
	}
	

	// Position Control On Routile
	Sleep(50);
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
	}
		
	
	for(int j = 0; j < TOTAL_MTR_NUM; j++)
	{
		//theApp.m_pSharedMemory->Reftheta[j] = theApp.m_pSharedMemory->theta[j];
		
		theApp.m_pSharedMemory->Reftheta[j] = (float)0.;
		theApp.m_pSharedMemory->theta[j] = (float)0.;
		theApp.m_pSharedMemory->Deltheta[j] = (float)0.;
		theApp.m_pSharedMemory->Oldtheta[j] = (float)0.;
		theApp.m_pSharedMemory->Move_CNT[j] = 0;
		theApp.m_pSharedMemory->Tfinal[j] = 0;
		
		theApp.m_pSharedMemory->Move_Flag[j] = TRUE;	
	}
	
	
	
	theApp.m_pSharedMemory->POS_CTRL_Flag = TRUE;
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	theApp.m_pSharedMemory->INT_Flag = TRUE;
	
	Sleep(100);

	theApp.m_pSharedMemory->INT_Flag = FALSE;
	Sleep(20);
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.SendRunCMD(i);
		Sleep(50);
	}
*/
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	theApp.m_pSharedMemory->INT_Flag = TRUE;


	OnOK();
	DestroyWindow();
}

void CZ_PhaseSetDlg::OnButtonEncShow() 
{
	// TODO: Add your control notification handler code here
	m_Z_PhaseEncoderViewDlg.SetParentWindow(this);
	m_Z_PhaseEncoderViewDlg.Init();
	m_Z_PhaseEncoderViewDlg.ShowWindow(SW_SHOW);	
}

void CZ_PhaseSetDlg::OnButtonRhrZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC0;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC0][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC0][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR_FAIL), FALSE);
	
	a = CalPulse(RHR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC0;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x20;
	else TxData[2] = 0x40;

	//TxData[2] = 0x20;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonRhpZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC1;

	theApp.m_pSharedMemory->Rx_Data[288+JMC1][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC1][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP_FAIL), FALSE);
	
	a = CalPulse(RHP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC1;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;
	else TxData[2] = 0x30;

	//TxData[2] = 0x10;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonRkpZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC2;

	theApp.m_pSharedMemory->Rx_Data[288+JMC2][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC2][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP_FAIL), FALSE);
	
	a = CalPulse(RKN);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC2;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;	//0x11
	else TxData[2] = 0x30;

	//TxData[2] = 0x11;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonLhrZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC4;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC4][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC4][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR_FAIL), FALSE);
	
	a = CalPulse(LHR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC4;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x21;
	else TxData[2] = 0x41;

	//TxData[2] = 0x21;
	
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonLhpZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC5;

	theApp.m_pSharedMemory->Rx_Data[288+JMC5][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC5][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP_FAIL), FALSE);
	
	a = CalPulse(LHP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC5;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	//TxData[2] = 0x11;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonLkpZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC6;

	theApp.m_pSharedMemory->Rx_Data[288+JMC6][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC6][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), FALSE);
	
	a = CalPulse(LKN);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC6;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;	//0x10
	else TxData[2] = 0x31;

	//TxData[2] = 0x10;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonRhrGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RHR_Offset >= 0) f_temp = (float)(m_RHR_Offset_Rev*4000. + m_RHR_Offset);
	else f_temp = (float)(-(m_RHR_Offset_Rev*4000. - m_RHR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RHR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RHR]));
	theApp.WINmoveANG_RPM(RHR,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRhpGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RHP_Offset >= 0) f_temp = (float)(m_RHP_Offset_Rev*4000. + m_RHP_Offset);
	else f_temp = (float)(-(m_RHP_Offset_Rev*4000. - m_RHP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RHP));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RHP]));
	theApp.WINmoveANG_RPM(RHP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRkpGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RKP_Offset >= 0) f_temp = (float)(m_RKP_Offset_Rev*4000. + m_RKP_Offset);
	else f_temp = (float)(-(m_RKP_Offset_Rev*4000. - m_RKP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RKN));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RKN]));
	theApp.WINmoveANG_RPM(RKN,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLhrGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LHR_Offset >= 0) f_temp = (float)(m_LHR_Offset_Rev*4000. + m_LHR_Offset);
	else f_temp = (float)(-(m_LHR_Offset_Rev*4000. - m_LHR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_LHR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LHR]));
	theApp.WINmoveANG_RPM(LHR,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLhpGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LHP_Offset >= 0) f_temp = (float)(m_LHP_Offset_Rev*4000. + m_LHP_Offset);
	else f_temp = (float)(-(m_LHP_Offset_Rev*4000. - m_LHP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_LHP));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LHP]));
	theApp.WINmoveANG_RPM(LHP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLkpGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LKP_Offset >= 0) f_temp = (float)(m_LKP_Offset_Rev*4000. + m_LKP_Offset);
	else f_temp = (float)(-(m_LKP_Offset_Rev*4000. - m_LKP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_LKN));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LKN]));
	theApp.WINmoveANG_RPM(LKN,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLhyZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->Rx_Data[288+JMC4][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC4][6] = 0x00;
	
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY_FAIL), FALSE);

	a = CalPulse(LHY);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);

	theApp.m_pSharedMemory->SearchBoardNo = JMC4;
	
	TxData[0] = JMC4;
	TxData[1] = GoLimitPos;
	
	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;
	else TxData[2] = 0x30;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonRhyZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC0;

	theApp.m_pSharedMemory->Rx_Data[288+JMC0][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC0][6] = 0x00;
	
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY_FAIL), FALSE);

	a = CalPulse(RHY);

	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC0;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	//TxData[2] = 0x11;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
	
}

void CZ_PhaseSetDlg::OnButtonLapZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC7;

	theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
	
	a = CalPulse(LAP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC7;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	//TxData[2] = 0x11;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
}

void CZ_PhaseSetDlg::OnButtonLarZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC7;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC7][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
	
	a = CalPulse(LAR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC7;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x21;
	else TxData[2] = 0x41;

	//TxData[2] = 0x21;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonRapZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC3;

	theApp.m_pSharedMemory->Rx_Data[288+JMC3][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC3][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP_FAIL), FALSE);
	
	a = CalPulse(RAP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC3;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;
	else TxData[2] = 0x30;

	//TxData[2] = 0x10;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
	
}

void CZ_PhaseSetDlg::OnButtonRarZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC3;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC3][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC3][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR_FAIL), FALSE);
	
	a = CalPulse(RAR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC3;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x20;
	else TxData[2] = 0x40;

	//TxData[2] = 0x20;
	
	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE(CMD_TXDF, TxData, 8);
	
}

void CZ_PhaseSetDlg::OnButtonLhyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LHY_Offset >= 0) f_temp = (float)(m_LHY_Offset_Rev*4000. + m_LHY_Offset);
	else f_temp = (float)(-(m_LHY_Offset_Rev*4000. - m_LHY_Offset));

	//f_angle = (float)(360.*(f_temp)/(PPR_LHY));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LHY]));
	theApp.WINmoveANG_RPM(LHY,f_angle,(float)0.1);	

}

void CZ_PhaseSetDlg::OnButtonLapGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LAP_Offset >= 0) f_temp = (float)(m_LAP_Offset_Rev*4000. + m_LAP_Offset);
	else f_temp = (float)(-(m_LAP_Offset_Rev*4000. - m_LAP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_LAP));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LAP]));
	theApp.WINmoveANG_RPM(LAP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLarGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LAR_Offset >= 0) f_temp = (float)(m_LAR_Offset_Rev*4000. + m_LAR_Offset);
	else f_temp = (float)(-(m_LAR_Offset_Rev*4000. - m_LAR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_LAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LAR]));
	theApp.WINmoveANG_RPM(LAR,f_angle,(float)0.1);	
	
}

void CZ_PhaseSetDlg::OnButtonRhyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RHY_Offset >= 0) f_temp = (float)(m_RHY_Offset_Rev*4000. + m_RHY_Offset);
	else f_temp = (float)(-(m_RHY_Offset_Rev*4000. - m_RHY_Offset));

	//f_temp = (float)m_RHY_Offset;
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RHY));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RHY]));
	theApp.WINmoveANG_RPM(RHY,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRapGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RAP_Offset >= 0) f_temp = (float)(m_RAP_Offset_Rev*4000. + m_RAP_Offset);
	else f_temp = (float)(-(m_RAP_Offset_Rev*4000. - m_RAP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAP));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RAP]));
	theApp.WINmoveANG_RPM(RAP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRarGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RAR_Offset >= 0) f_temp = (float)(m_RAR_Offset_Rev*4000. + m_RAR_Offset);
	else f_temp = (float)(-(m_RAR_Offset_Rev*4000. - m_RAR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RAR]));
	theApp.WINmoveANG_RPM(RAR,f_angle,(float)0.1);	
}

long CZ_PhaseSetDlg::CalPulse(int MotorNo)
{
	long EncSize;

	if((MotorNo >= RHY) && (MotorNo <= LAR)) EncSize = 4000;
	else if((MotorNo >= RSP) && (MotorNo <= LEB)) EncSize = 4000;
	else if(MotorNo == WST) EncSize = 4000;
	else EncSize = 128;

	if(theApp.m_pSharedMemory->Offset_Pulse[MotorNo] >= 0)
	{
		return (long)(theApp.m_pSharedMemory->PLUS_MTR_DIR[MotorNo]*(theApp.m_pSharedMemory->Offset_Rev[MotorNo]*EncSize + theApp.m_pSharedMemory->Offset_Pulse[MotorNo]));
	}
	else 
	{
		return (long)(theApp.m_pSharedMemory->PLUS_MTR_DIR[MotorNo]*(-(theApp.m_pSharedMemory->Offset_Rev[MotorNo]*EncSize - theApp.m_pSharedMemory->Offset_Pulse[MotorNo])));
	}
}

void CZ_PhaseSetDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	int buff_no;
	int buff_no1;
	int i;
	unsigned char z_ref0;
	unsigned char z_ref1;
	unsigned char z_ref2;
	unsigned char z_ref3;

	buff_no = 288;
	buff_no1 = 129;//128;

	int ch1[TOTAL_JMC_NUM];
	int ch2[TOTAL_JMC_NUM];

	int ch1_ex[TOTAL_EJMC_NUM];
	int ch2_ex[TOTAL_EJMC_NUM];
	int ch3_ex[TOTAL_EJMC_NUM];

	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		if(m_ZPosRefFlag == TRUE)
		{
			if((theApp.m_pSharedMemory->Rx_Data[buff_no+i][5] & 0x03) == 0x01) ch1[i] = 1;	// ok
			else if((theApp.m_pSharedMemory->Rx_Data[buff_no+i][5] & 0x03) == 0x02) ch1[i] = 2;	//fail
			else ch1[i] = 0;

			if((theApp.m_pSharedMemory->Rx_Data[buff_no+i][6] & 0x03) == 0x01) ch2[i] = 1;	// ok
			else if((theApp.m_pSharedMemory->Rx_Data[buff_no+i][6] & 0x03) == 0x02) ch2[i] = 2;	//fail
			else ch2[i] = 0;	
		}
	}

	if(m_ZPosRefFlag == FALSE)
	{
		z_ref0 = theApp.m_pSharedMemory->Rx_Data[(int)(buff_no1+(2*theApp.m_pSharedMemory->SearchBoardNo))][0];
		z_ref1 = theApp.m_pSharedMemory->Rx_Data[(int)(buff_no1+(2*theApp.m_pSharedMemory->SearchBoardNo))][1];
		z_ref2 = theApp.m_pSharedMemory->Rx_Data[(int)(buff_no1+(2*theApp.m_pSharedMemory->SearchBoardNo))][4];
		z_ref3 = theApp.m_pSharedMemory->Rx_Data[(int)(buff_no1+(2*theApp.m_pSharedMemory->SearchBoardNo))][5];

		switch(theApp.m_pSharedMemory->SearchBoardNo)
		{
		case JMC0:
			m_Z_ref[RHY] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[RHR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC1:
			m_Z_ref[RHP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			break;
		case JMC2:
			m_Z_ref[RKN] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			break;
		case JMC3:
			m_Z_ref[RAP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[RAR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC4:
			m_Z_ref[LHY] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[LHR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC5:
			m_Z_ref[LHP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			break;
		case JMC6:
			m_Z_ref[LKN] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			break;
		case JMC7:
			m_Z_ref[LAP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[LAR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC8:
			m_Z_ref[RSP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[RSR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC9:
			m_Z_ref[RSY] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[REB] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC10:
			m_Z_ref[LSP] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[LSR] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case JMC11:
			m_Z_ref[LSY] = z_ref0 + ((z_ref1<<8) & 0xFF00);
			m_Z_ref[LEB] = z_ref2 + ((z_ref3<<8) & 0xFF00);
			break;
		case EJMC3:
			m_Z_ref[WST] = z_ref0 + ((z_ref1<<8) & 0xFF00);
		}	
	}

	for(i=0;i<TOTAL_EJMC_NUM;i++)
	{
		if(m_ZPosRefFlag == TRUE)
		{
			if(i == (EJMC3 - EJMC0))
			{
				if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][5] & 0x03) == 0x01) ch1_ex[i] = 1;	// ok
				else if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][5] & 0x03) == 0x02) ch1_ex[i] = 2;	//fail
				else ch1_ex[i] = 0;
			}
			else
			{
				if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][5] & 0x03) == 0x01) ch1_ex[i] = 1;	// ok
				else if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][5] & 0x03) == 0x02) ch1_ex[i] = 2;	//fail
				else ch1_ex[i] = 0;

				if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][6] & 0x03) == 0x01) ch2_ex[i] = 1;	// ok
				else if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][6] & 0x03) == 0x02) ch2_ex[i] = 2;	//fail
				else ch2_ex[i] = 0;

				if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][7] & 0x03) == 0x01) ch3_ex[i] = 1;	// ok
				else if((theApp.m_pSharedMemory->Rx_Data[buff_no+32+i][7] & 0x03) == 0x02) ch3_ex[i] = 2;	//fail
				else ch3_ex[i] = 0;
			}
		}
		
	}

	if(m_ZPosRefFlag == TRUE)
	{
		if(ch1[JMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY_FAIL), FALSE);
		}
		else if(ch1[JMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHY_FAIL), FALSE);
		}
	
		if(ch2[JMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR_FAIL), FALSE);
		}
		else if(ch2[JMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHR_FAIL), FALSE);
		}

		if(ch1[JMC1] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP_FAIL), FALSE);
		}
		else if(ch1[JMC1] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHP_FAIL), FALSE);
		}

		if(ch1[JMC2] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP_FAIL), FALSE);
		}
		else if(ch1[JMC2] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RKP_FAIL), FALSE);
		}

		if(ch1[JMC3] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP_FAIL), FALSE);
		}
		else if(ch1[JMC3] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAP_FAIL), FALSE);
		}
		
		if(ch2[JMC3] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR_FAIL), FALSE);
		}
		else if(ch2[JMC3] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RAR_FAIL), FALSE);
		}
		///////////
		if(ch1[JMC4] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY_FAIL), FALSE);
		}
		else if(ch1[JMC4] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHY_FAIL), FALSE);
		}
		
		if(ch2[JMC4] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR_FAIL), FALSE);
		}
		else if(ch2[JMC4] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHR_FAIL), FALSE);
		}

		if(ch1[JMC5] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP_FAIL), FALSE);
		}
		else if(ch1[JMC5] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHP_FAIL), FALSE);
		}

		if(ch1[JMC6] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), FALSE);
		}
		else if(ch1[JMC6] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), FALSE);
		}	

		if(ch1[JMC7] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
		else if(ch1[JMC7] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
		
		if(ch2[JMC7] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}
		else if(ch2[JMC7] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}

		if(ch1[JMC8] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP_FAIL), FALSE);
		}
		else if(ch1[JMC8] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
	
		if(ch2[JMC8] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR_FAIL), FALSE);
		}
		else if(ch2[JMC8] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}
	
		if(ch1[JMC9] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY_FAIL), FALSE);
		}
		else if(ch1[JMC9] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
	
		if(ch2[JMC9] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB_FAIL), FALSE);
		}
		else if(ch2[JMC9] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}

		if(ch1[JMC10] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP_FAIL), FALSE);
		}
		else if(ch1[JMC10] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
		
		if(ch2[JMC10] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR_FAIL), FALSE);
		}
		else if(ch2[JMC10] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}

		if(ch1[JMC11] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY_FAIL), FALSE);
		}
		else if(ch1[JMC11] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}
		
		if(ch2[JMC11] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB_FAIL), FALSE);
		}
		else if(ch2[JMC11] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAR_FAIL), FALSE);
		}

		if(ch1_ex[EJMC0-EJMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT_FAIL), FALSE);
		}
		else if(ch1_ex[EJMC0-EJMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}	

		if(ch1_ex[EJMC1-EJMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT_FAIL), FALSE);
		}
		else if(ch1_ex[EJMC1-EJMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LAP_FAIL), FALSE);
		}

		if(ch1_ex[EJMC4-EJMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD_FAIL), FALSE);
		}
		else if(ch1_ex[EJMC4-EJMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RHD_FAIL), TRUE);
		}

		if(ch1_ex[EJMC5-EJMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD_FAIL), FALSE);
		}
		else if(ch1_ex[EJMC5-EJMC0] == 2)
		{	
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LHD_FAIL), TRUE);
		}

		if(ch1_ex[EJMC3-EJMC0] == 1)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST2), TRUE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST_FAIL), FALSE);
		}
		else if(ch1_ex[EJMC3-EJMC0] == 2)
		{
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST1), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST2), FALSE);
			::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST_FAIL), TRUE);
		}
		else
		{
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP1), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP2), FALSE);
			//::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LKP_FAIL), FALSE);
		}	

		//-----------------------------------------------------------------------
		//-----------[auto setup start]------------------------------------------
		//-----------------------------------------------------------------------
		autoSetup();
		//-----------------------------------------------------------------------
		//-----------[auto setup end]--------------------------------------------
		//-----------------------------------------------------------------------
	}
	
	CDialog::OnTimer(nIDEvent);

}



void CZ_PhaseSetDlg::OnButtonLspZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC10;

	theApp.m_pSharedMemory->Rx_Data[288+JMC10][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSP_FAIL), FALSE);
	
	a = CalPulse(LSP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC10;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonLsrZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC10;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSR_FAIL), FALSE);
	
	a = CalPulse(LSR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC10;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x21;
	else TxData[2] = 0x41;

	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonLsyZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC11;

	theApp.m_pSharedMemory->Rx_Data[288+JMC11][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LSY_FAIL), FALSE);
	
	a = CalPulse(LSY);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC11;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);		
}

void CZ_PhaseSetDlg::OnButtonLebZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC11;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC11][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LEB_FAIL), FALSE);
	
	a = CalPulse(LEB);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC11;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x21;
	else TxData[2] = 0x41;

	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);		
}

void CZ_PhaseSetDlg::OnButtonRspZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC8;

	theApp.m_pSharedMemory->Rx_Data[288+JMC8][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSP_FAIL), FALSE);
	
	a = CalPulse(RSP);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC8;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;
	else TxData[2] = 0x30;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonRsyZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC9;

	theApp.m_pSharedMemory->Rx_Data[288+JMC9][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSY_FAIL), FALSE);
	
	a = CalPulse(RSY);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC9;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x10;//0x11;
	else TxData[2] = 0x30;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonRsrZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC8;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC8][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RSR_FAIL), FALSE);
	
	a = CalPulse(RSR);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC8;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x20;
	else TxData[2] = 0x40;

	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonRebZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = JMC9;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+JMC9][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_REB_FAIL), FALSE);
	
	a = CalPulse(REB);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = JMC9;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x20;
	else TxData[2] = 0x40;

	
	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = ((a>>8) & (0xFF));
	TxData[6] = (a & 0xFF);
	TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonRspGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RSP_Offset >= 0) f_temp = (float)(m_RSP_Offset_Rev*4000. + m_RSP_Offset);
	else f_temp = (float)(-(m_RSP_Offset_Rev*4000. - m_RSP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RSP]));
	theApp.WINmoveANG_RPM(RSP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRsrGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RSR_Offset >= 0) f_temp = (float)(m_RSR_Offset_Rev*4000. + m_RSR_Offset);
	else f_temp = (float)(-(m_RSR_Offset_Rev*4000. - m_RSR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RSR]));
	theApp.WINmoveANG_RPM(RSR,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRsyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RSY_Offset >= 0) f_temp = (float)(m_RSY_Offset_Rev*4000. + m_RSY_Offset);
	else f_temp = (float)(-(m_RSY_Offset_Rev*4000. - m_RSY_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RSY]));
	theApp.WINmoveANG_RPM(RSY,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRebGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_REB_Offset >= 0) f_temp = (float)(m_REB_Offset_Rev*4000. + m_REB_Offset);
	else f_temp = (float)(-(m_REB_Offset_Rev*4000. - m_REB_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[REB]));
	theApp.WINmoveANG_RPM(REB,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLspGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LSP_Offset >= 0) f_temp = (float)(m_LSP_Offset_Rev*4000. + m_LSP_Offset);
	else f_temp = (float)(-(m_LSP_Offset_Rev*4000. - m_LSP_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LSP]));
	theApp.WINmoveANG_RPM(LSP,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLsrGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LSR_Offset >= 0) f_temp = (float)(m_LSR_Offset_Rev*4000. + m_LSR_Offset);
	else f_temp = (float)(-(m_LSR_Offset_Rev*4000. - m_LSR_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LSR]));
	theApp.WINmoveANG_RPM(LSR,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLsyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LSY_Offset >= 0) f_temp = (float)(m_LSY_Offset_Rev*4000. + m_LSY_Offset);
	else f_temp = (float)(-(m_LSY_Offset_Rev*4000. - m_LSY_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LSY]));
	theApp.WINmoveANG_RPM(LSY,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLebGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_LEB_Offset >= 0) f_temp = (float)(m_LEB_Offset_Rev*4000. + m_LEB_Offset);
	else f_temp = (float)(-(m_LEB_Offset_Rev*4000. - m_LEB_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[LEB]));
	theApp.WINmoveANG_RPM(LEB,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonRwtZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[7];
	long	a;
	long	b;
	long	c;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = EJMC0;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC0][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC0][6] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC0][7] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_RWT_FAIL), FALSE);
	
	a = (short)CalPulse(RWY);
	b = CalPulse1(RW1);
	c = CalPulse1(RW2);

	//a= (short)0;
	//b= (short)0;
	//c= (short)0;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = EJMC0;
	TxData[1] = GoLimitPos;


	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	
	TxData[3] = a & 0xFF;
	TxData[4] = (a >> 8) & 0xFF;
	TxData[5] = b & 0xFF;
	TxData[6] = c & 0xFF;
	//TxData[7] = (((a>>16) & (0x0F)) << 4);

	//TxData[3] = 0x00;
	//TxData[4] = 0x00;
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 7);	
}

long CZ_PhaseSetDlg::CalPulse1(int MotorNo)
{
	// offset calculation for 3ch-board, 1 & 2 motor
	// return value is number of (revolutions/10)

	long EncSize;

	EncSize = 128;

	if(theApp.m_pSharedMemory->Offset_Pulse[MotorNo] == 128)
	{
		return (long)(theApp.m_pSharedMemory->PLUS_MTR_DIR[MotorNo]*(10*theApp.m_pSharedMemory->Offset_Rev[MotorNo]));
	}
	else return 0;
}

void CZ_PhaseSetDlg::OnButtonLwtZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[7];
	long	a;
	long	b;
	long	c;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = EJMC1;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC1][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC1][6] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC1][7] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_LWT_FAIL), FALSE);
	
	a = (short int)CalPulse(LWY);
	b = CalPulse1(LW1);
	c = CalPulse1(LW2);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = EJMC1;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	
	TxData[3] = a & 0xFF;
	TxData[4] = (a >> 8) & 0xFF;
	TxData[5] = b & 0xFF;
	TxData[6] = c & 0xFF;
	//TxData[7] = (((a>>16) & (0x0F)) << 4);
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 7);	
}

void CZ_PhaseSetDlg::OnButtonRwyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_RWY_Offset >= 0) f_temp = (float)(m_RWY_Offset_Rev*128. + m_RWY_Offset);
	else f_temp = (float)(-(m_RWY_Offset_Rev*128. - m_RWY_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[RWY]));
	theApp.WINmoveANG_RPM(RWY,f_angle,(float)0.1);	
}

void CZ_PhaseSetDlg::OnButtonLhdZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[7];

	TxData[0]=EJMC5;
	TxData[1]=GoLimitPos;
	//TxData[2]=(7 & 0xFF);
	//TxData[3]=(7 & 0xFF);
	//TxData[4]=(7 & 0xFF);
	//TxData[5]=(7 & 0xFF);
	//TxData[6]=(7 & 0xFF);
	// midified
	TxData[2]=(4 & 0xFF);
	TxData[3]=(4 & 0xFF);
	TxData[4]=(4 & 0xFF);
	TxData[5]=(4 & 0xFF);
	TxData[6]=(4 & 0xFF);

	theApp.CAN_WRITE1(CMD_TXDF, TxData, 7);
}

void CZ_PhaseSetDlg::OnButtonRhdZPos() 
{
	// TODO: Add your control notification handler code here
	//unsigned char TxData[8];
	unsigned char TxData[7];

	
	TxData[0]=EJMC4;
	TxData[1]=GoLimitPos;
	TxData[2]=(4 & 0xFF);
	TxData[3]=(4 & 0xFF);
	TxData[4]=(4 & 0xFF);
	TxData[5]=(4 & 0xFF);
	TxData[6]=(4 & 0xFF);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 7);
	
}

void CZ_PhaseSetDlg::OnButtonWstZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[8];
	long	a;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = EJMC3;

	theApp.m_pSharedMemory->Rx_Data[288+EJMC3][5] = 0x00;
	//theApp.m_pSharedMemory->Rx_Data[288+JMC10][6] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_WST_FAIL), FALSE);
	
	a = CalPulse(WST);
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = EJMC3;
	TxData[1] = GoLimitPos;

	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	if (a < 0) a = (((-a) & 0x0007FFFF) | (1<<19));
	else;
	
	TxData[3] = ((a>>8) & (0xFF));
	TxData[4] = (a & 0xFF);
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = ((a>>16) & (0x0F));
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}

void CZ_PhaseSetDlg::OnButtonWstGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_WST_Offset >= 0) f_temp = (float)(m_WST_Offset_Rev*4000. + m_WST_Offset);
	else f_temp = (float)(-(m_WST_Offset_Rev*4000. - m_WST_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[WST]));
	theApp.WINmoveANG_RPM(WST,f_angle,(float)0.2);	
}

void CZ_PhaseSetDlg::OnButtonNkyZPos() 
{
	// TODO: Add your control notification handler code here
	unsigned char	TxData[7];
	long	a;
	long	b;
	long	c;

	UpdateData(TRUE);
	theApp.m_pSharedMemory->SearchBoardNo = EJMC2;

	//theApp.m_pSharedMemory->Rx_Data[288+JMC7][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC2][5] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC2][6] = 0x00;
	theApp.m_pSharedMemory->Rx_Data[288+EJMC2][7] = 0x00;

	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_NKY1), TRUE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_NKY2), FALSE);
	::EnableWindow(::GetDlgItem(m_hWnd, IDC_STATIC_NKY_FAIL), FALSE);
	
	a = (short)CalPulse(NKY);
	b = CalPulse1(NK1);
	c = CalPulse1(NK2);

	//a= (short)0;
	//b= (short)0;
	//c= (short)0;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	Sleep(50);
	
	TxData[0] = EJMC2;
	TxData[1] = GoLimitPos;


	if(m_ZPosRefFlag == TRUE) TxData[2] = 0x11;
	else TxData[2] = 0x31;

	
	TxData[3] = a & 0xFF;
	TxData[4] = (a >> 8) & 0xFF;
	TxData[5] = b & 0xFF;
	TxData[6] = c & 0xFF;
	//TxData[7] = (((a>>16) & (0x0F)) << 4);

	//TxData[3] = 0x00;
	//TxData[4] = 0x00;
	
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 7);	
}

void CZ_PhaseSetDlg::OnButtonNkyGoOffset() 
{
	// TODO: Add your control notification handler code here
	float	f_temp,f_angle;
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	Sleep(50);
	UpdateData(TRUE);
	
	if(m_NKY_Offset >= 0) f_temp = (float)(m_NKY_Offset_Rev*128. + m_NKY_Offset);
	else f_temp = (float)(-(m_NKY_Offset_Rev*128. - m_NKY_Offset));
	
	//f_angle = (float)(360.*(f_temp)/(PPR_RAR));
	f_angle = (float)(360.*(f_temp)/(theApp.m_pSharedMemory->PPR[NKY]));
	theApp.WINmoveANG_RPM(NKY,f_angle,(float)0.2);
}

void CZ_PhaseSetDlg::OnButtonZRefSave() 
{
	// TODO: Add your control notification handler code here
	// open file
	ofstream fout("z_ref.ref");
	if (!fout.is_open())
	{
		AfxMessageBox("SaveDataToFile() :: z_ref.ref 파일을 열 수 없습니다.", MB_OK);
		//return -1;
	}
	
	// save data

	fout << m_Z_ref[RHY] << endl;
	fout << m_Z_ref[RHR] << endl;
	fout << m_Z_ref[RHP] << endl;
	fout << m_Z_ref[RKN] << endl;
	fout << m_Z_ref[RAP] << endl;
	fout << m_Z_ref[RAR] << endl;

	fout << m_Z_ref[LHY] << endl;
	fout << m_Z_ref[LHR] << endl;
	fout << m_Z_ref[LHP] << endl;
	fout << m_Z_ref[LKN] << endl;
	fout << m_Z_ref[LAP] << endl;
	fout << m_Z_ref[LAR] << endl;

	fout << m_Z_ref[RSP] << endl;
	fout << m_Z_ref[RSR] << endl;
	fout << m_Z_ref[RSY] << endl;
	fout << m_Z_ref[REB] << endl;

	fout << m_Z_ref[LSP] << endl;
	fout << m_Z_ref[LSR] << endl;
	fout << m_Z_ref[LSY] << endl;
	fout << m_Z_ref[LEB] << endl;

	fout << m_Z_ref[RWY] << endl;
	fout << m_Z_ref[RW1] << endl;
	fout << m_Z_ref[RW2] << endl;

	fout << m_Z_ref[LWY] << endl;
	fout << m_Z_ref[LW1] << endl;
	fout << m_Z_ref[LW2] << endl;

	fout << m_Z_ref[NKY] << endl;
	fout << m_Z_ref[NK1] << endl;
	fout << m_Z_ref[NK2] << endl;

	fout << m_Z_ref[WST] << endl;
	

	// close file
	fout.close();
}

void CZ_PhaseSetDlg::OnAutoSetup() 
{
	// TODO: Add your control notification handler code here
	// this function will automatically run through the setup for each joint.  
	// it will search for each body part reading as if it were a book
	// it will wait until one is finished with (ok) hilighted 
	// if failed then must do the rest manually
	//int temp = 0;
	GetDlgItem( IDC_AutoSetup )->EnableWindow(false);  // disables button after press once
	autoSetupFlag = true;

	/*
	OnButtonLhyZPos();
	while(( temp != 1))	// holds here until joint is calibrated
	{
		temp = ch1[JMC4];
	}

	OnButtonRhyZPos();
	while((temp != 1) ) // holds here until joint is calibrated
	{
		temp = ch1[JMC0];
	}

	*/
}



void CZ_PhaseSetDlg::autoSetup()
{
	// this function will automatically run through the setup for each joint.  
	// it will search for each body part reading as if it were a book
	// it will wait until one is finished with (ok) hilighted 
	// if failed then must do the rest manually
	// case 0 through 11 is only for the lower body joints
	if (autoSetupFlag && !autoSetupStopFlag) 
	{
		switch(autoSetupCount)
		{
		case 0:  //LHY
			if(!(GetDlgItem(IDC_STATIC_LHY1)->IsWindowEnabled()))  // LHY
			{
				OnButtonLhyZPos();
				autoSetupCount++;
			}
				
			break;
		case 1:  //RHY
			if((GetDlgItem(IDC_STATIC_LHY2)->IsWindowEnabled()))		// RHY (checks to make sure previsou one is done // checks the ok button
			{
				OnButtonRhyZPos();
				autoSetupCount++;
			}
			break;

		case 2: // LHR
			if((GetDlgItem(IDC_STATIC_RHY2)->IsWindowEnabled()))
			{
				OnButtonLhrZPos();
				autoSetupCount++;
			}
			break;

		case 3: //RHR
			if((GetDlgItem(IDC_STATIC_LHR2)->IsWindowEnabled()))
			{
				OnButtonRhrZPos();
				autoSetupCount++;
			}
			break;

		case 4: //LHP
			if((GetDlgItem(IDC_STATIC_RHR2)->IsWindowEnabled()))
			{
				OnButtonLhpZPos();
				autoSetupCount++;
			}
			break;

		case 5: //RHP
			if((GetDlgItem(IDC_STATIC_LHP2)->IsWindowEnabled()))
			{
				OnButtonRhpZPos();
				autoSetupCount++;
			}
			break;

		case 6: //LKP
			if((GetDlgItem(IDC_STATIC_RHP2)->IsWindowEnabled()))
			{
				OnButtonLkpZPos();
				autoSetupCount++;
			}
			break;

		case 7: //RKP
			if((GetDlgItem(IDC_STATIC_LKP2)->IsWindowEnabled()))
			{
				OnButtonRkpZPos();
				autoSetupCount++;
			}
			break;

		case 8: //LAP
			if((GetDlgItem(IDC_STATIC_RKP2)->IsWindowEnabled()))
			{
				OnButtonLapZPos();
				autoSetupCount++;
			}
			break;

		case 9: // RAP
			if((GetDlgItem(IDC_STATIC_LAP2)->IsWindowEnabled()))
			{
				OnButtonRapZPos();
				autoSetupCount++;
			}
			break;

		case 10: // LAR
			if((GetDlgItem(IDC_STATIC_RAP2)->IsWindowEnabled()))
			{
				OnButtonLarZPos();
				autoSetupCount++;
			}
			break;

		case 11: // RAR
			if((GetDlgItem(IDC_STATIC_LAR2)->IsWindowEnabled()))
			{
				OnButtonRarZPos();
				autoSetupCount++;
			}
			break;

		//------------------------------------------------------------------
		//-------------------[ upper body start ]---------------------------
		//------------------------------------------------------------------
		// for this part (the upper body) each will be ran twice if needed
		case 12: //LSP
			if((GetDlgItem(IDC_STATIC_RAR2)->IsWindowEnabled()))
			{
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonLspZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_LSP_FAIL)->IsWindowEnabled())
						{
							OnButtonLspZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_LSP2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_LSP_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_LSP2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}

			}
			break;
			
		case 13: //RSP
			{
			
			if((GetDlgItem(IDC_STATIC_LSP2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonRspZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_RSP_FAIL)->IsWindowEnabled())
						{
							OnButtonRspZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_RSP2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_RSP_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_RSP2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 14: //LSR
			{
			
			if((GetDlgItem(IDC_STATIC_RSP2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonLsrZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_LSR_FAIL)->IsWindowEnabled())
						{
							OnButtonLsrZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_LSR2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_LSR_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_LSR2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 15: //RSR
			{
			
			if((GetDlgItem(IDC_STATIC_LSR2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonRsrZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_RSR_FAIL)->IsWindowEnabled())
						{
							OnButtonRsrZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_RSR2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_RSR_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_RSR2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;



			case 16: //LSY
			{
			
			if((GetDlgItem(IDC_STATIC_RSR2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonLsyZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_LSY_FAIL)->IsWindowEnabled())
						{
							OnButtonLsyZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_LSY2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_LSY_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_LSY2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;



			case 17: //RSY
			{
			
			if((GetDlgItem(IDC_STATIC_LSY2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonRsyZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_RSY_FAIL)->IsWindowEnabled())
						{
							OnButtonRsyZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_RSY2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_RSY_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_RSY2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 18: //LEB
			{
			
			if((GetDlgItem(IDC_STATIC_RSY2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonLebZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_LEB_FAIL)->IsWindowEnabled())
						{
							OnButtonLebZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_LEB2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_LEB_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_LEB2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 19: //REB
			{
			
			if((GetDlgItem(IDC_STATIC_LEB2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonRebZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_REB_FAIL)->IsWindowEnabled())
						{
							OnButtonRebZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_REB2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_REB_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_REB2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;



			case 20: //LWT
			{
			
			if((GetDlgItem(IDC_STATIC_REB2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonLwtZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_LWT_FAIL)->IsWindowEnabled())
						{
							OnButtonLwtZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_LWT2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_LWT_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_LWT2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 21: //RWT
			{
			
			if((GetDlgItem(IDC_STATIC_LWT2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonRwtZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_RWT_FAIL)->IsWindowEnabled())
						{
							OnButtonRwtZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_RWT2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_RWT_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_RWT2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 22: //WST
			{
			
			if((GetDlgItem(IDC_STATIC_RWT2)->IsWindowEnabled()))
				switch(autoSetupErrorCount)
				{
				
				case 0:
					{
						OnButtonWstZPos();
						autoSetupErrorCount++;
					}
				break;

				case 1:
					{
						if(GetDlgItem(IDC_STATIC_WST_FAIL)->IsWindowEnabled())
						{
							OnButtonWstZPos();
							autoSetupErrorCount++;
						}
						else if(GetDlgItem(IDC_STATIC_WST2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;

				case 2:
					{
						if(GetDlgItem(IDC_STATIC_WST_FAIL)->IsWindowEnabled())
						{
							autoSetupCount = -1;
						}
						else if(GetDlgItem(IDC_STATIC_WST2)->IsWindowEnabled())
						{
							autoSetupErrorCount = 0;
							autoSetupCount++;
						}
					}
					break;
				}
			}
			break;


			case 23: // NKY
			if((GetDlgItem(IDC_STATIC_WST2)->IsWindowEnabled()))
			{
				OnButtonNkyZPos();
				autoSetupCount++;
			}
			break;















		}
	}
	 

}

void CZ_PhaseSetDlg::OnautoSetupStop() 
{
	// TODO: Add your control notification handler code here
	// this function will stop the auto setup after the current search
	autoSetupStopFlag = true;
	
}
