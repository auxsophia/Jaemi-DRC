// Z_PhaseEncoderViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Z_PhaseSetDlg.h"
#include "Z_PhaseEncoderViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseEncoderViewDlg dialog

extern CKhr3winApp theApp;

CZ_PhaseEncoderViewDlg::CZ_PhaseEncoderViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZ_PhaseEncoderViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZ_PhaseEncoderViewDlg)
	m_LHP_Enc = 0;
	m_LHR_Enc = 0;
	m_LKP_Enc = 0;
	m_RHP_Enc = 0;
	m_RHR_Enc = 0;
	m_RKP_Enc = 0;
	//}}AFX_DATA_INIT
}


void CZ_PhaseEncoderViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZ_PhaseEncoderViewDlg)
	DDX_Text(pDX, IDC_EDIT_LHP_ENC, m_LHP_Enc);
	DDX_Text(pDX, IDC_EDIT_LHR_ENC, m_LHR_Enc);
	DDX_Text(pDX, IDC_EDIT_LKP_ENC, m_LKP_Enc);
	DDX_Text(pDX, IDC_EDIT_RHP_ENC, m_RHP_Enc);
	DDX_Text(pDX, IDC_EDIT_RHR_ENC, m_RHR_Enc);
	DDX_Text(pDX, IDC_EDIT_RKP_ENC, m_RKP_Enc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZ_PhaseEncoderViewDlg, CDialog)
	//{{AFX_MSG_MAP(CZ_PhaseEncoderViewDlg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseEncoderViewDlg message handlers

void CZ_PhaseEncoderViewDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	theApp.m_pSharedMemory->Read_Enc_Flag = FALSE;
	OnOK();
}

void CZ_PhaseEncoderViewDlg::Init()
{
	//theApp.m_pSharedMemory->Read_Enc_Flag = TRUE;

	index=0;
	SetTimer(1, DISP_TIMER, NULL);
}

void CZ_PhaseEncoderViewDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		index++;
		DispEnc();
	}

	CDialog::OnTimer(nIDEvent);
}

void CZ_PhaseEncoderViewDlg::DispEnc()
{
	m_RHR_Enc = (theApp.m_pSharedMemory->Rx_Data[40][4]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[40][5] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[40][6] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[40][7] << 24) ;
	
	
	m_RHP_Enc = (theApp.m_pSharedMemory->Rx_Data[41][0]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[41][1] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[41][2] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[41][3] << 24) ;
	
	m_RKP_Enc = (theApp.m_pSharedMemory->Rx_Data[41][4]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[41][5] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[41][6] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[41][7] << 24) ;
	
	m_LHR_Enc = (theApp.m_pSharedMemory->Rx_Data[43][4]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[43][5] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[43][6] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[43][7] << 24) ;
	
	m_LHP_Enc = (theApp.m_pSharedMemory->Rx_Data[44][0]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[44][1] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[44][2] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[44][3] << 24) ;
	
	m_LKP_Enc = (theApp.m_pSharedMemory->Rx_Data[44][4]		 ) |
				(theApp.m_pSharedMemory->Rx_Data[44][5] <<  8) |
				(theApp.m_pSharedMemory->Rx_Data[44][6] << 16) |
				(theApp.m_pSharedMemory->Rx_Data[44][7] << 24) ;
	

	UpdateData(FALSE);
}
