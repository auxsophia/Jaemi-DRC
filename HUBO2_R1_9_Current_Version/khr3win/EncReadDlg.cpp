// EncReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "EncReadDlg.h"
#include "Khr3winDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEncReadDlg dialog
extern CKhr3winApp theApp;

CEncReadDlg::CEncReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncReadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncReadDlg)
	EncVarINIT();
	
	//}}AFX_DATA_INIT
	m_pKhr3winDlg = NULL;
}


void CEncReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncReadDlg)

	DDX_Text(pDX, IDC_EDIT_MONITORING, m_Edit_Monitoring);
	// Head (JMC0)
	DDX_Text(pDX, IDC_EDIT_ENC0 , m_Edit_Enc0 );
	DDX_Text(pDX, IDC_EDIT_ENC1 , m_Edit_Enc1 );
	DDX_Text(pDX, IDC_EDIT_ENC2 , m_Edit_Enc2 );
	DDX_Text(pDX, IDC_EDIT_ENC3 , m_Edit_Enc3 );
	DDX_Text(pDX, IDC_EDIT_ENC4 , m_Edit_Enc4 );
	DDX_Text(pDX, IDC_EDIT_ENC5 , m_Edit_Enc5 );
	// Left Hand (JMC1)
	DDX_Text(pDX, IDC_EDIT_ENC6 , m_Edit_Enc6 );
	DDX_Text(pDX, IDC_EDIT_ENC7 , m_Edit_Enc7 );
	DDX_Text(pDX, IDC_EDIT_ENC8 , m_Edit_Enc8 );
	DDX_Text(pDX, IDC_EDIT_ENC9 , m_Edit_Enc9 );
	DDX_Text(pDX, IDC_EDIT_ENC10, m_Edit_Enc10);
	DDX_Text(pDX, IDC_EDIT_ENC11, m_Edit_Enc11);
	DDX_Text(pDX, IDC_EDIT_ENC12, m_Edit_Enc12);
	// Right Hand (JMC2)
	DDX_Text(pDX, IDC_EDIT_ENC13, m_Edit_Enc13);
	DDX_Text(pDX, IDC_EDIT_ENC14, m_Edit_Enc14);
	DDX_Text(pDX, IDC_EDIT_ENC15, m_Edit_Enc15);
	DDX_Text(pDX, IDC_EDIT_ENC16, m_Edit_Enc16);
	DDX_Text(pDX, IDC_EDIT_ENC17, m_Edit_Enc17);
	DDX_Text(pDX, IDC_EDIT_ENC18, m_Edit_Enc18);
	DDX_Text(pDX, IDC_EDIT_ENC19, m_Edit_Enc19);
	// Right Shoulder Pitch, Yaw (JMC3)
	DDX_Text(pDX, IDC_EDIT_ENC20, m_Edit_Enc20);
	DDX_Text(pDX, IDC_EDIT_ENC21, m_Edit_Enc21);
	// Right Shoulder, Right Elbow (JMC4)
	DDX_Text(pDX, IDC_EDIT_ENC22, m_Edit_Enc22);
	DDX_Text(pDX, IDC_EDIT_ENC23, m_Edit_Enc23);
	// Left Shoulder Pitch, Yaw (JMC5)
	DDX_Text(pDX, IDC_EDIT_ENC24, m_Edit_Enc24);
	DDX_Text(pDX, IDC_EDIT_ENC25, m_Edit_Enc25);
	// Left Shoulder, Elbow (JMC6)
	DDX_Text(pDX, IDC_EDIT_ENC26, m_Edit_Enc26);
	DDX_Text(pDX, IDC_EDIT_ENC27, m_Edit_Enc27);
	// Trunk
	DDX_Text(pDX, IDC_EDIT_ENC28, m_Edit_Enc28);
	// Right Hip Yaw, Roll
	DDX_Text(pDX, IDC_EDIT_ENC29, m_Edit_Enc29);
	DDX_Text(pDX, IDC_EDIT_ENC30, m_Edit_Enc30);
	// Right Hip Pitch, Knee
	DDX_Text(pDX, IDC_EDIT_ENC31, m_Edit_Enc31);
	DDX_Text(pDX, IDC_EDIT_ENC32, m_Edit_Enc32);
	// Right Ankle Pitch, Roll
	DDX_Text(pDX, IDC_EDIT_ENC33, m_Edit_Enc33);
	DDX_Text(pDX, IDC_EDIT_ENC34, m_Edit_Enc34);
	// Left Hip Yaw, Roll
	DDX_Text(pDX, IDC_EDIT_ENC35, m_Edit_Enc35);
	DDX_Text(pDX, IDC_EDIT_ENC36, m_Edit_Enc36);
	// Left Hip Pitch, Knee
	DDX_Text(pDX, IDC_EDIT_ENC37, m_Edit_Enc37);
	DDX_Text(pDX, IDC_EDIT_ENC38, m_Edit_Enc38);
	// Left Ankle Pitch, Roll
	DDX_Text(pDX, IDC_EDIT_ENC39, m_Edit_Enc39);
	DDX_Text(pDX, IDC_EDIT_ENC40, m_Edit_Enc40);

	DDX_Text(pDX, IDC_EDIT_ENC41, m_Edit_Enc41);
	DDX_Text(pDX, IDC_EDIT_ENC42, m_Edit_Enc42);
	DDX_Text(pDX, IDC_EDIT_ENC43, m_Edit_Enc43);

		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEncReadDlg, CDialog)
	//{{AFX_MSG_MAP(CEncReadDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncReadDlg message handlers

void CEncReadDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		GetEnc();
		m_Edit_Monitoring++;
		UpdateData(false);
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CEncReadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	EncVarINIT();	
	theApp.m_pSharedMemory->Read_Enc_Flag=TRUE;
	UpdateData(FALSE);
	SetTimer(1,DISP_TIMER,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CEncReadDlg::Close()
{
	m_pKhr3winDlg->ButtonControl(Enc_CLOSE);


	theApp.m_pSharedMemory->Read_Enc_Flag = FALSE;
	
	KillTimer(1);
	UpdateData(FALSE);
	DestroyWindow();
}

void CEncReadDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	Close();
	
	Sleep(1000);
	theApp.m_pSharedMemory->Rx_Flag = FALSE;
	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void CEncReadDlg::EncVarINIT()
{
	m_Edit_Enc0  =  0;
	m_Edit_Enc1  =  0;
	m_Edit_Enc2  =  0;
	m_Edit_Enc3  =  0;
	m_Edit_Enc4  =  0;
	m_Edit_Enc5  =  0;
	m_Edit_Enc6  =  0;
	m_Edit_Enc7  =  0;
	m_Edit_Enc8  =  0;
	m_Edit_Enc9  =  0;
	m_Edit_Enc10 =  0;
	m_Edit_Enc11 =  0;
	m_Edit_Enc12 =  0;
	m_Edit_Enc13 =  0;
	m_Edit_Enc14 =  0;
	m_Edit_Enc15 =  0;
	m_Edit_Enc16 =  0;
	m_Edit_Enc17 =  0;
	m_Edit_Enc18 =  0;
	m_Edit_Enc19 =  0;
	m_Edit_Enc20 =  0;
	m_Edit_Enc21 =  0;
	m_Edit_Enc22 =  0;
	m_Edit_Enc23 =  0;
	m_Edit_Enc24 =  0;
	m_Edit_Enc25 =  0;
	m_Edit_Enc26 =  0;
	m_Edit_Enc27 =  0;
	m_Edit_Enc28 =  0;
	m_Edit_Enc29 =  0;
	m_Edit_Enc30 =  0;
	m_Edit_Enc31 =  0;
	m_Edit_Enc32 =  0;
	m_Edit_Enc33 =  0;
	m_Edit_Enc34 =  0;
	m_Edit_Enc35 =  0;
	m_Edit_Enc36 =  0;
	m_Edit_Enc37 =  0;
	m_Edit_Enc38 =  0;
	m_Edit_Enc39 =  0;
	m_Edit_Enc40 =  0;
	m_Edit_Enc41 =  0;
	m_Edit_Enc42 =  0;
	m_Edit_Enc43 =  0;

	m_Edit_Monitoring =  0;
}

void CEncReadDlg::GetEnc()
{
	// Head (JMC0)
	theApp.m_Motor[0].CurrPos= theApp.m_pSharedMemory->ENC_POS[24][0];
	m_Edit_Enc0=theApp.m_Motor[0].CurrPos;
		
	theApp.m_Motor[1].CurrPos = theApp.m_pSharedMemory->ENC_POS[24][1];
	m_Edit_Enc1=theApp.m_Motor[1].CurrPos;

	theApp.m_Motor[2].CurrPos = theApp.m_pSharedMemory->ENC_POS[25][0];
	m_Edit_Enc2=theApp.m_Motor[2].CurrPos;

	theApp.m_Motor[3].CurrPos = theApp.m_pSharedMemory->ENC_POS[25][1];
	m_Edit_Enc3=theApp.m_Motor[3].CurrPos;

	theApp.m_Motor[4].CurrPos = theApp.m_pSharedMemory->ENC_POS[26][0];
	m_Edit_Enc4=theApp.m_Motor[4].CurrPos;
		
	theApp.m_Motor[5].CurrPos = theApp.m_pSharedMemory->ENC_POS[26][1];
	m_Edit_Enc5=theApp.m_Motor[5].CurrPos;
	//Right Wrist (EJMC0)
	theApp.m_Motor[RWY].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC0-EJMC0][0];
	m_Edit_Enc42=theApp.m_Motor[RWY].CurrPos;

	theApp.m_Motor[RW1].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC0-EJMC0][1];
	//m_Edit_Enc18=theApp.m_Motor[RW1].CurrPos;
	m_Edit_Enc18=(long)(theApp.m_pSharedMemory->Ex_ENC_POS[EJMC0-EJMC0][1]);

	theApp.m_Motor[RW2].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC0-EJMC0][2];
	m_Edit_Enc19=theApp.m_Motor[RW2].CurrPos;
	
	//Left Wrist (EJMC1)
	theApp.m_Motor[LWY].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC1-EJMC0][0];
	m_Edit_Enc42=theApp.m_Motor[LWY].CurrPos;

	theApp.m_Motor[LW1].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC1-EJMC0][1];
	m_Edit_Enc11=theApp.m_Motor[LW1].CurrPos;
		
	theApp.m_Motor[LW2].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC1-EJMC0][2];
	m_Edit_Enc12=theApp.m_Motor[LW2].CurrPos;

	//Neck (EJMC2)
	theApp.m_Motor[NKY].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC2-EJMC0][0];
	m_Edit_Enc43=theApp.m_Motor[NKY].CurrPos;

	theApp.m_Motor[NK1].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC2-EJMC0][1];
	m_Edit_Enc4=theApp.m_Motor[NKY].CurrPos;
		
	theApp.m_Motor[NK2].CurrPos = theApp.m_pSharedMemory->Ex_ENC_POS[EJMC2-EJMC0][2];
	m_Edit_Enc5=theApp.m_Motor[NK2].CurrPos;


	// Trunk Yaw (EJMC3)
	theApp.m_Motor[WST].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC3][0];
	m_Edit_Enc28=theApp.m_Motor[EJMC3].CurrPos;
	// Right Hand (EJMC4)
	theApp.m_Motor[RF1].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC4][0];
	m_Edit_Enc13=theApp.m_Motor[RF1].CurrPos;
		
	theApp.m_Motor[RF2].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC4][1];
	m_Edit_Enc14=theApp.m_Motor[RF2].CurrPos;
		
	theApp.m_Motor[RF3].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC4][0];
	m_Edit_Enc15=theApp.m_Motor[RF3].CurrPos;
		
	theApp.m_Motor[RF4].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC4][1];
	m_Edit_Enc16=theApp.m_Motor[RF5].CurrPos;
		
	theApp.m_Motor[RF5].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC4][0];
	m_Edit_Enc17=theApp.m_Motor[RF5].CurrPos;

	// Left Hand (EJMC5)
	theApp.m_Motor[LF1].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC5][0];
	m_Edit_Enc6=theApp.m_Motor[LF1].CurrPos;
		
	theApp.m_Motor[LF2].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC5][1];
	m_Edit_Enc7=theApp.m_Motor[LF2].CurrPos;
	
	theApp.m_Motor[LF3].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC5][0];
	m_Edit_Enc8=theApp.m_Motor[LF3].CurrPos;
		
	theApp.m_Motor[LF4].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC5][1];
	m_Edit_Enc9=theApp.m_Motor[LF4].CurrPos;
		
	theApp.m_Motor[LF5].CurrPos = theApp.m_pSharedMemory->ENC_POS[EJMC5][0];
	m_Edit_Enc10=theApp.m_Motor[LF5].CurrPos;
	
	// Right Shoulder Pitch-Roll (JMC8)
	theApp.m_Motor[RSP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC8][0];
	m_Edit_Enc20=theApp.m_Motor[RSP].CurrPos;
				
	theApp.m_Motor[RSR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC8][1];
	m_Edit_Enc21=theApp.m_Motor[RSR].CurrPos;

	// Right Shoulder Yaw, Elbow (JMC9)
	theApp.m_Motor[RSY].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC9][0];
	m_Edit_Enc22=theApp.m_Motor[RSY].CurrPos;

	theApp.m_Motor[REB].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC9][1];
	m_Edit_Enc23=theApp.m_Motor[REB].CurrPos;

	// Left Shoulder Pitch-Yaw (JMC10)
	theApp.m_Motor[LSP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC10][0];
	m_Edit_Enc24=theApp.m_Motor[LSP].CurrPos;
				
	theApp.m_Motor[LSR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC10][1];
	m_Edit_Enc25=theApp.m_Motor[LSR].CurrPos;

	// Left Shoulder Roll, Elbow (JMC11)
	theApp.m_Motor[LSY].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC11][0];
	m_Edit_Enc26=theApp.m_Motor[LSY].CurrPos;
		
	theApp.m_Motor[LEB].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC11][1];
	m_Edit_Enc27=theApp.m_Motor[LEB].CurrPos;
		
	// Right Hip Yaw-Roll - JMC0
	theApp.m_Motor[RHY].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC0][0];
	m_Edit_Enc29=theApp.m_Motor[RHY].CurrPos;
		
	theApp.m_Motor[RHR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC0][1];
	m_Edit_Enc30=theApp.m_Motor[RHR].CurrPos;

	// Right Hip Pitch - JMC1
	theApp.m_Motor[RHP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC1][0];
	m_Edit_Enc31=theApp.m_Motor[RHP].CurrPos;
	
	// Right Knee - JMC2
	theApp.m_Motor[RKN].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC2][0];
	m_Edit_Enc32=theApp.m_Motor[RKN].CurrPos;

	// Right Ankle Pitch-Roll - JMC3
	theApp.m_Motor[RAP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC3][0];
	m_Edit_Enc33=theApp.m_Motor[RAP].CurrPos;
		
	theApp.m_Motor[RAR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC3][1];
	m_Edit_Enc34=theApp.m_Motor[RAR].CurrPos;

	// Left Hip Yaw-Roll - JMC4
	theApp.m_Motor[LHY].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC4][0];
	m_Edit_Enc35=theApp.m_Motor[LHY].CurrPos;
		
	theApp.m_Motor[LHR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC4][1];
	m_Edit_Enc36=theApp.m_Motor[LHR].CurrPos;
		
	// Left Hip Pitch - JMC5
	theApp.m_Motor[LHP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC5][0];
	m_Edit_Enc37=theApp.m_Motor[LHP].CurrPos;
		
	// Left Knee Pitch - JMC6
	theApp.m_Motor[LKN].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC6][0];
	m_Edit_Enc38=theApp.m_Motor[LKN].CurrPos;
		
	// Left Ankle Pitch-Roll - JMC7
	theApp.m_Motor[LAP].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC7][0];
	m_Edit_Enc39=theApp.m_Motor[LAP].CurrPos;
		
	theApp.m_Motor[LAR].CurrPos = theApp.m_pSharedMemory->ENC_POS[JMC7][1];
	m_Edit_Enc40=theApp.m_Motor[LAR].CurrPos;
}
