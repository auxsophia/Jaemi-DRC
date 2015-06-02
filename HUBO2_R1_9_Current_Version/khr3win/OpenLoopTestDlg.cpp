// OpenLoopTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Khr3winDlg.h"
#include "OpenLoopTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenLoopTestDlg dialog

extern CKhr3winApp theApp;

COpenLoopTestDlg::COpenLoopTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenLoopTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenLoopTestDlg)
	m_Duty00 = 0;
	m_Duty01 = 0;
	m_Duty02 = 0;
	m_Duty03 = 0;
	m_Duty04 = 0;
	m_Duty05 = 0;
	m_Duty06 = 0;
	m_Duty07 = 0;
	m_Duty08 = 0;
	m_Duty09 = 0;
	m_Duty10 = 0;
	m_Duty11 = 0;
	m_Duty13 = 0;
	m_Duty12 = 0;
	m_Duty14 = 0;
	m_Duty15 = 0;
	m_Duty16 = 0;
	m_Duty17 = 0;
	m_Duty18 = 0;
	m_Duty19 = 0;
	m_Duty20 = 0;
	m_Duty21 = 0;
	m_Duty22 = 0;
	m_Duty23 = 0;
	m_Duty24 = 0;
	m_Duty25 = 0;
	m_Duty26 = 0;
	m_Duty27 = 0;
	m_Duty28 = 0;
	m_Duty29 = 0;
	m_Duty30 = 0;
	m_Duty31 = 0;
	m_Duty32 = 0;
	m_Duty33 = 0;
	m_Duty34 = 0;
	m_Duty35 = 0;
	m_Duty36 = 0;
	m_Duty37 = 0;
	m_Duty38 = 0;
	m_Duty39 = 0;
	m_Duty40 = 0;
	m_Duty41 = 0;
	m_Duty42 = 0;
	m_Duty43 = 0;
	//}}AFX_DATA_INIT
	m_pKhr3winDlg = NULL;
}


void COpenLoopTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenLoopTestDlg)
	DDX_Control(pDX, IDC_BUTTON_STOP22, m_STOP22);
	DDX_Control(pDX, IDC_BUTTON_STOP21, m_STOP21);
	DDX_Control(pDX, IDC_BUTTON_STOP20, m_STOP20);
	DDX_Control(pDX, IDC_BUTTON_RUN22, m_RUN22);
	DDX_Control(pDX, IDC_BUTTON_RUN21, m_RUN21);
	DDX_Control(pDX, IDC_BUTTON_RUN20, m_RUN20);
	DDX_Control(pDX, IDC_BUTTON_STOP15, m_STOP15);
	DDX_Control(pDX, IDC_BUTTON_RUN15, m_RUN15);
	DDX_Control(pDX, IDC_BUTTON_STOP14, m_STOP14);
	DDX_Control(pDX, IDC_BUTTON_RUN14, m_RUN14);
	DDX_Control(pDX, IDC_BUTTON_STOP9, m_STOP09);
	DDX_Control(pDX, IDC_BUTTON_STOP8, m_STOP08);
	DDX_Control(pDX, IDC_BUTTON_STOP7, m_STOP07);
	DDX_Control(pDX, IDC_BUTTON_STOP6, m_STOP06);
	DDX_Control(pDX, IDC_BUTTON_STOP5, m_STOP05);
	DDX_Control(pDX, IDC_BUTTON_STOP4, m_STOP04);
	DDX_Control(pDX, IDC_BUTTON_STOP3, m_STOP03);
	DDX_Control(pDX, IDC_BUTTON_STOP2, m_STOP02);
	DDX_Control(pDX, IDC_BUTTON_STOP13, m_STOP13);
	DDX_Control(pDX, IDC_BUTTON_STOP12, m_STOP12);
	DDX_Control(pDX, IDC_BUTTON_STOP11, m_STOP11);
	DDX_Control(pDX, IDC_BUTTON_STOP10, m_STOP10);
	DDX_Control(pDX, IDC_BUTTON_STOP1, m_STOP01);
	DDX_Control(pDX, IDC_BUTTON_STOP0, m_STOP00);
	DDX_Control(pDX, IDC_BUTTON_RUN9, m_RUN09);
	DDX_Control(pDX, IDC_BUTTON_RUN8, m_RUN08);
	DDX_Control(pDX, IDC_BUTTON_RUN7, m_RUN07);
	DDX_Control(pDX, IDC_BUTTON_RUN6, m_RUN06);
	DDX_Control(pDX, IDC_BUTTON_RUN5, m_RUN05);
	DDX_Control(pDX, IDC_BUTTON_RUN4, m_RUN04);
	DDX_Control(pDX, IDC_BUTTON_RUN3, m_RUN03);
	DDX_Control(pDX, IDC_BUTTON_RUN2, m_RUN02);
	DDX_Control(pDX, IDC_BUTTON_RUN13, m_RUN13);
	DDX_Control(pDX, IDC_BUTTON_RUN12, m_RUN12);
	DDX_Control(pDX, IDC_BUTTON_RUN11, m_RUN11);
	DDX_Control(pDX, IDC_BUTTON_RUN10, m_RUN10);
	DDX_Control(pDX, IDC_BUTTON_RUN1, m_RUN01);
	DDX_Control(pDX, IDC_BUTTON_RUN0, m_RUN00);
	DDX_Text(pDX, IDC_EDIT00, m_Duty00);
	DDV_MinMaxInt(pDX, m_Duty00, -100, 100);
	DDX_Text(pDX, IDC_EDIT01, m_Duty01);
	DDV_MinMaxInt(pDX, m_Duty01, -100, 100);
	DDX_Text(pDX, IDC_EDIT02, m_Duty02);
	DDV_MinMaxInt(pDX, m_Duty02, -100, 100);
	DDX_Text(pDX, IDC_EDIT03, m_Duty03);
	DDV_MinMaxInt(pDX, m_Duty03, -100, 100);
	DDX_Text(pDX, IDC_EDIT04, m_Duty04);
	DDV_MinMaxInt(pDX, m_Duty04, -100, 100);
	DDX_Text(pDX, IDC_EDIT05, m_Duty05);
	DDV_MinMaxInt(pDX, m_Duty05, -100, 100);
	DDX_Text(pDX, IDC_EDIT06, m_Duty06);
	DDV_MinMaxInt(pDX, m_Duty06, -100, 100);
	DDX_Text(pDX, IDC_EDIT07, m_Duty07);
	DDV_MinMaxInt(pDX, m_Duty07, -100, 100);
	DDX_Text(pDX, IDC_EDIT08, m_Duty08);
	DDV_MinMaxInt(pDX, m_Duty08, -100, 100);
	DDX_Text(pDX, IDC_EDIT09, m_Duty09);
	DDV_MinMaxInt(pDX, m_Duty09, -100, 100);
	DDX_Text(pDX, IDC_EDIT10, m_Duty10);
	DDV_MinMaxInt(pDX, m_Duty10, -100, 100);
	DDX_Text(pDX, IDC_EDIT11, m_Duty11);
	DDV_MinMaxInt(pDX, m_Duty11, -100, 100);
	DDX_Text(pDX, IDC_EDIT13, m_Duty13);
	DDV_MinMaxInt(pDX, m_Duty13, -100, 100);
	DDX_Text(pDX, IDC_EDIT12, m_Duty12);
	DDX_Text(pDX, IDC_EDIT14, m_Duty14);
	DDV_MinMaxInt(pDX, m_Duty14, -100, 100);
	DDX_Text(pDX, IDC_EDIT15, m_Duty15);
	DDV_MinMaxInt(pDX, m_Duty15, -100, 100);
	DDX_Text(pDX, IDC_EDIT16, m_Duty16);
	DDV_MinMaxInt(pDX, m_Duty16, -100, 100);
	DDX_Text(pDX, IDC_EDIT17, m_Duty17);
	DDV_MinMaxInt(pDX, m_Duty17, -100, 100);
	DDX_Text(pDX, IDC_EDIT18, m_Duty18);
	DDV_MinMaxInt(pDX, m_Duty18, -100, 100);
	DDX_Text(pDX, IDC_EDIT19, m_Duty19);
	DDV_MinMaxInt(pDX, m_Duty19, -100, 100);
	DDX_Text(pDX, IDC_EDIT20, m_Duty20);
	DDV_MinMaxInt(pDX, m_Duty20, -100, 100);
	DDX_Text(pDX, IDC_EDIT21, m_Duty21);
	DDV_MinMaxInt(pDX, m_Duty21, -100, 100);
	DDX_Text(pDX, IDC_EDIT22, m_Duty22);
	DDV_MinMaxInt(pDX, m_Duty22, -100, 100);
	DDX_Text(pDX, IDC_EDIT23, m_Duty23);
	DDV_MinMaxInt(pDX, m_Duty23, -100, 100);
	DDX_Text(pDX, IDC_EDIT24, m_Duty24);
	DDV_MinMaxInt(pDX, m_Duty24, -100, 100);
	DDX_Text(pDX, IDC_EDIT25, m_Duty25);
	DDV_MinMaxInt(pDX, m_Duty25, -100, 100);
	DDX_Text(pDX, IDC_EDIT26, m_Duty26);
	DDV_MinMaxInt(pDX, m_Duty26, -100, 100);
	DDX_Text(pDX, IDC_EDIT27, m_Duty27);
	DDV_MinMaxInt(pDX, m_Duty27, -100, 100);
	DDX_Text(pDX, IDC_EDIT28, m_Duty28);
	DDV_MinMaxInt(pDX, m_Duty28, -100, 100);
	DDX_Text(pDX, IDC_EDIT29, m_Duty29);
	DDV_MinMaxInt(pDX, m_Duty29, -100, 100);
	DDX_Text(pDX, IDC_EDIT30, m_Duty30);
	DDV_MinMaxInt(pDX, m_Duty30, -100, 100);
	DDX_Text(pDX, IDC_EDIT31, m_Duty31);
	DDV_MinMaxInt(pDX, m_Duty31, -100, 100);
	DDX_Text(pDX, IDC_EDIT32, m_Duty32);
	DDV_MinMaxInt(pDX, m_Duty32, -100, 100);
	DDX_Text(pDX, IDC_EDIT33, m_Duty33);
	DDV_MinMaxInt(pDX, m_Duty33, -100, 100);
	DDX_Text(pDX, IDC_EDIT34, m_Duty34);
	DDX_Text(pDX, IDC_EDIT35, m_Duty35);
	DDV_MinMaxInt(pDX, m_Duty35, -100, 100);
	DDX_Text(pDX, IDC_EDIT36, m_Duty36);
	DDV_MinMaxInt(pDX, m_Duty36, -100, 100);
	DDX_Text(pDX, IDC_EDIT37, m_Duty37);
	DDV_MinMaxInt(pDX, m_Duty37, -100, 100);
	DDX_Text(pDX, IDC_EDIT38, m_Duty38);
	DDV_MinMaxInt(pDX, m_Duty38, -100, 100);
	DDX_Text(pDX, IDC_EDIT39, m_Duty39);
	DDV_MinMaxInt(pDX, m_Duty39, -100, 100);
	DDX_Text(pDX, IDC_EDIT40, m_Duty40);
	DDV_MinMaxInt(pDX, m_Duty40, -100, 100);
	DDX_Text(pDX, IDC_EDIT41, m_Duty41);
	DDX_Text(pDX, IDC_EDIT42, m_Duty42);
	DDX_Text(pDX, IDC_EDIT43, m_Duty43);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenLoopTestDlg, CDialog)
	//{{AFX_MSG_MAP(COpenLoopTestDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_RUN0, OnButtonRun0)
	ON_BN_CLICKED(IDC_BUTTON_STOP0, OnButtonStop0)
	ON_BN_CLICKED(IDC_BUTTON_RUN1, OnButtonRun1)
	ON_BN_CLICKED(IDC_BUTTON_STOP1, OnButtonStop1)
	ON_BN_CLICKED(IDC_BUTTON_RUN2, OnButtonRun2)
	ON_BN_CLICKED(IDC_BUTTON_STOP2, OnButtonStop2)
	ON_BN_CLICKED(IDC_BUTTON_RUN3, OnButtonRun3)
	ON_BN_CLICKED(IDC_BUTTON_STOP3, OnButtonStop3)
	ON_BN_CLICKED(IDC_BUTTON_RUN4, OnButtonRun4)
	ON_BN_CLICKED(IDC_BUTTON_STOP4, OnButtonStop4)
	ON_BN_CLICKED(IDC_BUTTON_RUN5, OnButtonRun5)
	ON_BN_CLICKED(IDC_BUTTON_STOP5, OnButtonStop5)
	ON_BN_CLICKED(IDC_BUTTON_RUN6, OnButtonRun6)
	ON_BN_CLICKED(IDC_BUTTON_STOP6, OnButtonStop6)
	ON_BN_CLICKED(IDC_BUTTON_RUN7, OnButtonRun7)
	ON_BN_CLICKED(IDC_BUTTON_STOP7, OnButtonStop7)
	ON_BN_CLICKED(IDC_BUTTON_RUN8, OnButtonRun8)
	ON_BN_CLICKED(IDC_BUTTON_STOP8, OnButtonStop8)
	ON_BN_CLICKED(IDC_BUTTON_RUN9, OnButtonRun9)
	ON_BN_CLICKED(IDC_BUTTON_STOP9, OnButtonStop9)
	ON_BN_CLICKED(IDC_BUTTON_RUN10, OnButtonRun10)
	ON_BN_CLICKED(IDC_BUTTON_STOP10, OnButtonStop10)
	ON_BN_CLICKED(IDC_BUTTON_RUN11, OnButtonRun11)
	ON_BN_CLICKED(IDC_BUTTON_STOP11, OnButtonStop11)
	ON_BN_CLICKED(IDC_BUTTON_RUN12, OnButtonRun12)
	ON_BN_CLICKED(IDC_BUTTON_STOP12, OnButtonStop12)
	ON_BN_CLICKED(IDC_BUTTON_RUN13, OnButtonRun13)
	ON_BN_CLICKED(IDC_BUTTON_STOP13, OnButtonStop13)
	ON_BN_CLICKED(IDC_BUTTON_RUN14, OnButtonRun14)
	ON_BN_CLICKED(IDC_BUTTON_RUN15, OnButtonRun15)
	ON_BN_CLICKED(IDC_BUTTON_STOP14, OnButtonStop14)
	ON_BN_CLICKED(IDC_BUTTON_STOP15, OnButtonStop15)
	ON_BN_CLICKED(IDC_BUTTON_RUN20, OnButtonRun20)
	ON_BN_CLICKED(IDC_BUTTON_STOP20, OnButtonStop20)
	ON_BN_CLICKED(IDC_BUTTON_RUN21, OnButtonRun21)
	ON_BN_CLICKED(IDC_BUTTON_STOP21, OnButtonStop21)
	ON_BN_CLICKED(IDC_BUTTON_RUN22, OnButtonRun22)
	ON_BN_CLICKED(IDC_BUTTON_STOP22, OnButtonStop22)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenLoopTestDlg message handlers

void COpenLoopTestDlg::Init()
{
	unsigned char i = 0;

	theApp.m_pSharedMemory->InitialPositionSettingFlag = FALSE;
	
//	AfxMessageBox("Hello");
	m_Duty00 = 0;
	m_Duty01 = 0;
	m_Duty02 = 0;
	m_Duty03 = 0;
	m_Duty04 = 0;
	m_Duty05 = 0;
	m_Duty06 = 0;
	m_Duty07 = 0;
	m_Duty08 = 0;
	m_Duty09 = 0;
	m_Duty10 = 0;
	m_Duty11 = 0;
	m_Duty13 = 0;
	m_Duty12 = 0;
	m_Duty14 = 0;
	m_Duty15 = 0;
	m_Duty16 = 0;
	m_Duty17 = 0;
	m_Duty18 = 0;
	m_Duty19 = 0;
	m_Duty20 = 0;
	m_Duty21 = 0;
	m_Duty22 = 0;
	m_Duty23 = 0;
	m_Duty24 = 0;
	m_Duty25 = 0;
	m_Duty26 = 0;
	m_Duty27 = 0;
	m_Duty28 = 0;
	m_Duty29 = 0;
	m_Duty30 = 0;
	m_Duty31 = 0;
	m_Duty32 = 0;
	m_Duty33 = 0;
	m_Duty34 = 0;
	m_Duty35 = 0;
	m_Duty36 = 0;
	m_Duty37 = 0;
	m_Duty38 = 0;
	m_Duty39 = 0;
	m_Duty40 = 0;

	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.DisableHIP(i);
		Sleep(50);
		
		theApp.SendCTRLOff(i);
		Sleep(50);
	}

	for(i=EJMC0;i<EJMC0+TOTAL_EJMC_NUM;i++)
	{
		theApp.DisableHIP(i);
		Sleep(50);
		
		theApp.SendCTRLOff(i);
		Sleep(50);
	}
	

	OLCANInit();
	Sleep(50);
	
	//for(i=0;i<TOTAL_JMC_NUM;i++)	RunStop[i]= 0;
	for(i=0;i<30;i++)	RunStop[i]= 0;
	
	UpdateData(FALSE);
}

void COpenLoopTestDlg::Close()
{
	unsigned char i;
	m_pKhr3winDlg->ButtonControl(OL_CLOSE);
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.DisablePWM(i);
		Sleep(50);
		
		theApp.DisableHIP(i);
		Sleep(50);
	}
	
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;

	DestroyWindow();
}

void COpenLoopTestDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	
	Close();
	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void COpenLoopTestDlg::OnButtonRun0() 
{
	// TODO: Add your control notification handler code here
	RunStop[0] = 1;
	OLRunStop00(RunStop[0]);
}

void COpenLoopTestDlg::OnButtonStop0() 
{
	// TODO: Add your control notification handler code here
	RunStop[0] = 0;
	OLRunStop00(RunStop[0]);	
}

void COpenLoopTestDlg::OnButtonRun1() 
{
	// TODO: Add your control notification handler code here
	RunStop[1] = 1;
	OLRunStop01(RunStop[1]);	
}

void COpenLoopTestDlg::OnButtonStop1() 
{
	// TODO: Add your control notification handler code here
	RunStop[1] = 0;
	OLRunStop01(RunStop[1]);	
}

void COpenLoopTestDlg::OnButtonRun2() 
{
	// TODO: Add your control notification handler code here
	RunStop[2] = 1;
	OLRunStop02(RunStop[2]);	
}

void COpenLoopTestDlg::OnButtonStop2() 
{
	// TODO: Add your control notification handler code here
	RunStop[2] = 0;
	OLRunStop02(RunStop[2]);	
}

void COpenLoopTestDlg::OnButtonRun3() 
{
	// TODO: Add your control notification handler code here
	RunStop[3] = 1;
	OLRunStop03(RunStop[3]);	
}

void COpenLoopTestDlg::OnButtonStop3() 
{
	// TODO: Add your control notification handler code here
	RunStop[3] = 0;
	OLRunStop03(RunStop[3]);	
}

void COpenLoopTestDlg::OnButtonRun4() 
{
	// TODO: Add your control notification handler code here
	RunStop[4] = 1;
	OLRunStop04(RunStop[4]);	
}

void COpenLoopTestDlg::OnButtonStop4() 
{
	// TODO: Add your control notification handler code here
	RunStop[4] = 0;
	OLRunStop04(RunStop[4]);
}

void COpenLoopTestDlg::OnButtonRun5() 
{
	// TODO: Add your control notification handler code here
	RunStop[5] = 1;
	OLRunStop05(RunStop[5]);		
}

void COpenLoopTestDlg::OnButtonStop5() 
{
	// TODO: Add your control notification handler code here
	RunStop[5] = 0;
	OLRunStop05(RunStop[5]);	
}

void COpenLoopTestDlg::OnButtonRun6() 
{
	// TODO: Add your control notification handler code here
	RunStop[6] = 1;
	OLRunStop06(RunStop[6]);	
}

void COpenLoopTestDlg::OnButtonStop6() 
{
	// TODO: Add your control notification handler code here
	RunStop[6] = 0;
	OLRunStop06(RunStop[6]);
}

void COpenLoopTestDlg::OnButtonRun7() 
{
	// TODO: Add your control notification handler code here
	RunStop[7] = 1;
	OLRunStop07(RunStop[7]);	
}

void COpenLoopTestDlg::OnButtonStop7() 
{
	// TODO: Add your control notification handler code here
	RunStop[7] = 0;
	OLRunStop07(RunStop[7]);	
}

void COpenLoopTestDlg::OnButtonRun8() 
{
	// TODO: Add your control notification handler code here
	RunStop[8] = 1;
	OLRunStop08(RunStop[8]);
}

void COpenLoopTestDlg::OnButtonStop8() 
{
	// TODO: Add your control notification handler code here
	RunStop[8] = 0;
	OLRunStop08(RunStop[8]);	
}

void COpenLoopTestDlg::OnButtonRun9() 
{
	// TODO: Add your control notification handler code here
	RunStop[9] = 1;
	OLRunStop09(RunStop[9]);	
}

void COpenLoopTestDlg::OnButtonStop9() 
{
	// TODO: Add your control notification handler code here
	RunStop[9] = 0;
	OLRunStop09(RunStop[9]);		
}

void COpenLoopTestDlg::OnButtonRun10() 
{
	// TODO: Add your control notification handler code here
	RunStop[10] = 1;
	OLRunStop10(RunStop[10]);	
}

void COpenLoopTestDlg::OnButtonStop10() 
{
	// TODO: Add your control notification handler code here
	RunStop[10] = 0;
	OLRunStop10(RunStop[10]);	
}

void COpenLoopTestDlg::OnButtonRun11() 
{
	// TODO: Add your control notification handler code here
	RunStop[11] = 1;
	OLRunStop11(RunStop[11]);
	//PwmRun(JMC12);		// Left Hip Yaw-Roll
}

void COpenLoopTestDlg::OnButtonStop11() 
{
	// TODO: Add your control notification handler code here
	RunStop[11] = 0;
	OLRunStop11(RunStop[11]);
	//PwmStop(JMC12);		// Left Hip Yaw-Roll
}

void COpenLoopTestDlg::OnButtonRun12() 
{
	// TODO: Add your control notification handler code here
	RunStop[12] = 1;
	OLRunStop12(RunStop[12]);
	//PwmRun(JMC13);		// Left Hip pitch
}

void COpenLoopTestDlg::OnButtonStop12() 
{
	// TODO: Add your control notification handler code here
	RunStop[12] = 0;
	OLRunStop12(RunStop[12]);
	//PwmStop(JMC13);		// Left Hip pitch
}

void COpenLoopTestDlg::OnButtonRun13() 
{
	// TODO: Add your control notification handler code here
	RunStop[13] = 1;
	OLRunStop13(RunStop[13]);	
}

void COpenLoopTestDlg::OnButtonStop13() 
{
	// TODO: Add your control notification handler code here
	RunStop[13] = 0;
	OLRunStop13(RunStop[13]);	
}

void COpenLoopTestDlg::OLRunStop00(char Flag)
{
	if(Flag == 1) // Run
	{
		OLRun(0,5);
		m_RUN00.EnableWindow(FALSE);
		m_STOP00.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		OLStop(0,5);
		m_STOP00.EnableWindow(FALSE);
		m_RUN00.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop01(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(6,12);
		PwmRun(EJMC5);
		m_RUN01.EnableWindow(FALSE);
		m_STOP01.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(6,12);
		PwmStop(EJMC5);
		m_STOP01.EnableWindow(FALSE);
		m_RUN01.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop02(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(13,19);
		PwmRun(EJMC4);
		m_RUN02.EnableWindow(FALSE);
		m_STOP02.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(13,19);
		PwmStop(EJMC4);
		m_STOP02.EnableWindow(FALSE);
		m_RUN02.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop03(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(20,21);
		PwmRun(JMC8);
		m_RUN03.EnableWindow(FALSE);
		m_STOP03.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(20,21);
		PwmStop(JMC8);
		m_STOP03.EnableWindow(FALSE);
		m_RUN03.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop04(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(22,23);
		PwmRun(JMC9);
		m_RUN04.EnableWindow(FALSE);
		m_STOP04.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(22,23);
		PwmStop(JMC9);
		m_STOP04.EnableWindow(FALSE);
		m_RUN04.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop05(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(24,25);
		PwmRun(JMC10);
		m_RUN05.EnableWindow(FALSE);
		m_STOP05.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(24,25);
		PwmStop(JMC10);
		m_STOP05.EnableWindow(FALSE);
		m_RUN05.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop06(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(26,27);
		PwmRun(JMC11);
		m_RUN06.EnableWindow(FALSE);
		m_STOP06.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(26,27);
		PwmStop(JMC11);
		m_STOP06.EnableWindow(FALSE);
		m_RUN06.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop07(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(28,28);
		PwmRun(EJMC3);
		m_RUN07.EnableWindow(FALSE);
		m_STOP07.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(28,28);
		PwmStop(EJMC3);
		m_STOP07.EnableWindow(FALSE);
		m_RUN07.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop08(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(29,30);
		PwmRun(JMC0);	// Right Hip yaw & roll
		m_RUN08.EnableWindow(FALSE);
		m_STOP08.EnableWindow(TRUE);		
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(29,30);
		PwmStop(JMC0);	// Right Hip yaw & roll
		m_STOP08.EnableWindow(FALSE);
		m_RUN08.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop09(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(31,32);
		PwmRun(JMC1);	// Right Hip pitch
		m_RUN09.EnableWindow(FALSE);
		m_STOP09.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(31,32);
		PwmStop(JMC1);	// Right Hip pitch
		m_STOP09.EnableWindow(FALSE);
		m_RUN09.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop10(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(33,34);
		PwmRun(JMC2);		// Right Knee pitch
		m_RUN10.EnableWindow(FALSE);
		m_STOP10.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(33,34);
		PwmStop(JMC2);		// Right Knee Pitch
		m_STOP10.EnableWindow(FALSE);
		m_RUN10.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop11(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(35,36);
		PwmRun(JMC3);		// Right Ankle pitch & roll
		m_RUN11.EnableWindow(FALSE);
		m_STOP11.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(35,36);
		PwmStop(JMC3);		// Right Ankle pitch & roll
		m_STOP11.EnableWindow(FALSE);
		m_RUN11.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop12(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(37,38);
		PwmRun(JMC4);		// Left Hip yaw & roll
		m_RUN12.EnableWindow(FALSE);
		m_STOP12.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(37,38);
		PwmStop(JMC4);		// Left Hip yaw & roll
		m_STOP12.EnableWindow(FALSE);
		m_RUN12.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop13(char Flag)
{
	if(Flag == 1) // Run
	{
		//OLRun(39,40);
		PwmRun(JMC5);		// Left Hip pitch
		m_RUN13.EnableWindow(FALSE);
		m_STOP13.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		//OLStop(39,40);
		PwmStop(JMC5);		// Left Hip pitch
		m_STOP13.EnableWindow(FALSE);
		m_RUN13.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRun(int BeginID, int EndID)
{
	int moID,PWM[TOTAL_MTR_NUM],DIR[TOTAL_MTR_NUM];

	UpdateData(TRUE);
	
	PWM[0] = m_Duty00;
	PWM[1] = m_Duty01;
	PWM[2] = m_Duty02;
	PWM[3] = m_Duty03;
	PWM[4] = m_Duty04;
	PWM[5] = m_Duty05;
	PWM[6] = m_Duty06;
	PWM[7] = m_Duty07;
	PWM[8] = m_Duty08;
	PWM[9] = m_Duty09;
	PWM[10] = m_Duty10;
	PWM[11] = m_Duty11;
	PWM[12] = m_Duty12;
	PWM[13] = m_Duty13;
	PWM[14] = m_Duty14;
	PWM[15] = m_Duty15;
	PWM[16] = m_Duty16;
	PWM[17] = m_Duty17;
	PWM[18] = m_Duty18;
	PWM[19] = m_Duty19;
	PWM[20] = m_Duty20;
	PWM[21] = m_Duty21;
	PWM[22] = m_Duty22;
	PWM[23] = m_Duty23;
	PWM[24] = m_Duty24;
	PWM[25] = m_Duty25;
	PWM[26] = m_Duty26;
	PWM[27] = m_Duty27;
	PWM[28] = m_Duty28;
	PWM[29] = m_Duty29;
	PWM[30] = m_Duty30;
	PWM[31] = m_Duty31;
	PWM[32] = m_Duty32;
	PWM[33] = m_Duty33;
	PWM[34] = m_Duty34;
	PWM[35] = m_Duty35;
	PWM[36] = m_Duty36;
	PWM[37] = m_Duty37;
	PWM[38] = m_Duty38;
	PWM[39] = m_Duty39;
	PWM[40] = m_Duty40;

	for(moID = BeginID; moID < EndID+1; moID++)
	{
		if(PWM[moID] >= 0)
		{
			DIR[moID] = 0;
			if(PWM[moID] >= 99)
			{
				PWM[moID] = 99;
			}
		}
		else if(PWM[moID] < 0)
		{
			DIR[moID] = 1;
			if(PWM[moID] <= -99)
			{
				if(moID<20)	PWM[moID] = 1;
				else PWM[moID] = 99;
			}
			else
			{
				if(moID<20)	PWM[moID]=100 + PWM[moID];
				else PWM[moID] = -PWM[moID];
			}
		}

		Txdlc = 3;
		TxData[0] = moID;
		TxData[1] = DIR[moID];
		TxData[2] = PWM[moID];
		
		//m_CanWinOL.CAN_WRITE(PWM_TXDF,TxData,Txdlc);
		m_CanWinOL.CAN_WRITE(CMD_TXDF,TxData,Txdlc);
		Sleep(20);
	}
}

void COpenLoopTestDlg::OLStop(int BeginID, int EndID)
{
	int moID;
	
	for(moID = BeginID; moID < EndID+1; moID++)
	{
		Txdlc = 3;
		TxData[0] = moID;
		TxData[1] = 0;
		TxData[2] = 0;
		
		//m_CanWinOL.CAN_WRITE(PWM_TXDF,TxData,Txdlc);
		Sleep(20);
	}
}

void COpenLoopTestDlg::OLCANInit()
{
	unsigned char i;
	unsigned char TxData[7];
	unsigned char TxData1[8];

	TxData[1] = PwmCMD;
	TxData[2] = 0x01;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;

	TxData1[1] = PwmCMD;
	TxData1[2] = 0x01;
	TxData1[3] = 0x00;
	TxData1[4] = 0x00;
	TxData1[5] = 0x00;
	TxData1[6] = 0x00;
	TxData1[7] = 0x00;

	for(i=0;i<7;i++)
	{
		TxData[0] = i;
		m_CanWinOL.CAN_WRITE(CMD_TXDF, TxData, 7);
		Sleep(50);
		theApp.EnableHIP(i);
	}

	for(i=8;i<TOTAL_JMC_NUM;i++)
	{
		TxData[0] = i;
		m_CanWinOL.CAN_WRITE1(CMD_TXDF, TxData, 7);
		Sleep(50);
		theApp.EnableHIP(i);
	}
	
	for(i=EJMC0;i<EJMC0+TOTAL_EJMC_NUM;i++)
	{
		TxData1[0] = i;
		m_CanWinOL.CAN_WRITE1(CMD_TXDF, TxData1, 7);
		Sleep(50);
		theApp.EnableHIP(i);
	}
}



void COpenLoopTestDlg::PwmStop(unsigned char BoardNo)
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
		m_CanWinOL.CAN_WRITE(CMD_TXDF,TxData,7);
		Sleep(20);
	}
	else if((BoardNo >= JMC8) && (BoardNo <= JMC11))
	{
		TxData[0] = BoardNo;
		m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData,7);
		Sleep(20);
	}
	else if((BoardNo >= EJMC0 && BoardNo <= EJMC2))
	{
		TxData1[0] = BoardNo;
		m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData1,8);
		Sleep(20);
	}
	else if(BoardNo == EJMC3)
	{
		TxData[0] = BoardNo;
		m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData,7);
		Sleep(20);
	}

}

void COpenLoopTestDlg::PwmRun(unsigned char BoardNo)
{
	
	int moID1, moID2, PWM[TOTAL_MTR_NUM],DIR[TOTAL_MTR_NUM];
	int moID3, moID4, moID5;
	unsigned char TxData[7];
	unsigned char TxData1[8];
	UpdateData(TRUE);
	
	//PWM[REP] = m_Duty00;
	//PWM[REY] = m_Duty01;
	//PWM[LEP] = m_Duty02;
	//PWM[LEY] = m_Duty03;
	
	PWM[NKY] = m_Duty43;
	PWM[NK1] = m_Duty04;
	PWM[NK2] = m_Duty05;
	PWM[LF1] = m_Duty06;
	PWM[LF2] = m_Duty07;
	PWM[LF3] = m_Duty08;
	PWM[LF4] = m_Duty09;
	PWM[LF5] = m_Duty10;
	PWM[LWY] = m_Duty41;
	PWM[LW1] = m_Duty11;
	PWM[LW2] = m_Duty12;
	
	PWM[RF1] = m_Duty13;
	PWM[RF2] = m_Duty14;
	PWM[RF3] = m_Duty15;
	PWM[RF4] = m_Duty16;
	PWM[RF5] = m_Duty17;
	PWM[RWY] = m_Duty42;
	PWM[RW1] = m_Duty18;
	PWM[RW2] = m_Duty19;
	
	PWM[RSP] = m_Duty20;
	PWM[RSR] = m_Duty21;
	PWM[RSY] = m_Duty22;
	PWM[REB] = m_Duty23;
	PWM[LSP] = m_Duty24;
	PWM[LSR] = m_Duty25;
	PWM[LSY] = m_Duty26;
	PWM[LEB] = m_Duty27;
	PWM[WST] = m_Duty28;
	//////////////////
	PWM[RHY] = m_Duty29;
	PWM[RHR] = m_Duty30;
	PWM[RHP] = m_Duty31;
	PWM[RKN] = m_Duty32;
	PWM[RAP] = m_Duty33;
	PWM[RAR] = m_Duty34;
	PWM[LHY] = m_Duty35;
	PWM[LHR] = m_Duty36;
	PWM[LHP] = m_Duty37;
	PWM[LKN] = m_Duty38;
	PWM[LAP] = m_Duty39;
	PWM[LAR] = m_Duty40;


	switch(BoardNo)
	{
		case JMC0:
			moID1 = RHY;	moID2 = RHR;
			break ;
		case JMC1:
			moID1 = RHP;	moID2 = RHP;
			break;
		case JMC2:
			moID1 = RKN;	moID2 = RKN;
			break;
		case JMC3:
			moID1 = RAP;	moID2 = RAR;
			break;
		case JMC4:
			moID1 = LHY;	moID2 = LHR;
			break ;
		case JMC5:
			moID1 = LHP;	moID2 = LHP;
			break;
		case JMC6:
			moID1 = LKN;	moID2 = LKN;
			break;
		case JMC7:
			moID1 = LAP;	moID2 = LAR;
			break;
		case JMC8:
			moID1 = RSP;	moID2 = RSR;
			break;
		case JMC9:
			moID1 = RSY;	moID2 = REB;
			break;
		case JMC10:
			moID1 = LSP;	moID2 = LSR;
			break;
		case JMC11:
			moID1 = LSY;	moID2 = LEB;
			break;
		case EJMC0:
			moID1 = RWY;	moID2 = RW1;	moID3 = RW2;
			break;
		case EJMC1:
			moID1 = LWY;	moID2 = LW1;	moID3 = LW2;
			break;
		case EJMC2:
			moID1 = NKY;	moID2 = NK1;	moID3 = NK2;
			break;
		case EJMC3:
			moID1 = WST;	moID2 = WST;
			break;
		case EJMC4:
			moID1 = RF1;	moID2 = RF2;	moID3 = RF3;	moID4 = RF4;	moID5 = RF5;
			break;
		case EJMC5:
			moID1 = LF1;	moID2 = LF2;	moID3 = LF3;	moID4 = LF4;	moID5 = LF5;
			break;
	}
	
	if((BoardNo == JMC1) || (BoardNo == JMC2) || (BoardNo == JMC5) || (BoardNo == JMC6))
	{
		if(PWM[moID1] >= 0)
		{
			DIR[moID1] = 0;
			DIR[moID2] = 0;
			if(PWM[moID1] >= 99) {PWM[moID1] = 99; PWM[moID2] = 99;}
			
		}
		else if(PWM[moID1] < 0)
		{
			DIR[moID1] = 1;
			DIR[moID2] = 1;
			if(PWM[moID1] <= -99) {PWM[moID1] = 99; PWM[moID2] = 99;}
			else {PWM[moID1] = -PWM[moID1]; PWM[moID2] = PWM[moID1];}
		}
	}
	else if((BoardNo <= JMC11) || (BoardNo == EJMC3))
	{
		if(PWM[moID1] >= 0)
		{
			DIR[moID1] = 0;
			if(PWM[moID1] >= 99) PWM[moID1] = 99;
			
		}
		else if(PWM[moID1] < 0)
		{
			DIR[moID1] = 1;
			if(PWM[moID1] <= -99) PWM[moID1] = 99;
			else PWM[moID1] = -PWM[moID1];
		}
		/*
		if(PWM[moID2] >= 0)
		{
			DIR[moID2] = 0;
			if(PWM[moID2] >= 99) PWM[moID2] = 99;
			
		}
		else if(PWM[moID2] < 0)
		{
			DIR[moID2] = 1;
			if(PWM[moID2] <= -99) PWM[moID2] = 99;
			else PWM[moID2] = -PWM[moID2];
		}*/
		DIR[moID2] = DIR[moID1];
		PWM[moID2] = PWM[moID1];
	}
	else if((BoardNo >= EJMC0) && (BoardNo <= EJMC2))
	{
		if(PWM[moID1] >= 0)
		{
			DIR[moID1] = 0;
			if(PWM[moID1] >= 99) PWM[moID1] = 99;
			
		}
		else if(PWM[moID1] < 0)
		{
			DIR[moID1] = 1;
			if(PWM[moID1] <= -99) PWM[moID1] = 99;
			else PWM[moID1] = -PWM[moID1];
		}
		
		if(PWM[moID2] >= 0)
		{
			DIR[moID2] = 0;
			if(PWM[moID2] >= 99) PWM[moID2] = 99;
			
		}
		else if(PWM[moID2] < 0)
		{
			DIR[moID2] = 1;
			if(PWM[moID2] <= -99) PWM[moID2] = 99;
			else PWM[moID2] = -PWM[moID2];
		}

		if(PWM[moID3] >= 0)
		{
			DIR[moID3] = 0;
			if(PWM[moID3] >= 99) PWM[moID3] = 99;
			
		}
		else if(PWM[moID3] < 0)
		{
			DIR[moID3] = 1;
			if(PWM[moID3] <= -99) PWM[moID3] = 99;
			else PWM[moID3] = -PWM[moID3];
		}
	}

	if(BoardNo <= JMC11)
	{
		TxData[0] = BoardNo;
		TxData[1] = PwmCMD;
		TxData[2] = 0x01;
		TxData[3] = DIR[moID1];
		TxData[4] = PWM[moID1];
		TxData[5] = DIR[moID2];
		TxData[6] = PWM[moID2];
	
		if(BoardNo <= JMC7)
		{
			m_CanWinOL.CAN_WRITE(CMD_TXDF,TxData,7);
			Sleep(20);
		}
		else
		{
			m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData,7);
			Sleep(20);
		}
		
	}
	else if((BoardNo >= EJMC0) && (BoardNo <=EJMC2))
	{
		TxData1[0] = BoardNo;
		TxData1[1] = PwmCMD;
		TxData1[2] = 0x01;
		TxData1[3] = DIR[moID1];
		TxData1[4] = PWM[moID1];
		TxData1[6] = PWM[moID2];
		TxData1[7] = PWM[moID3];

		if((DIR[moID2] == 0) && (DIR[moID3] == 0)) TxData1[5] = 0x00;
		else if((DIR[moID2] == 1) && (DIR[moID3] == 0)) TxData1[5] = 0x01;
		else if((DIR[moID2] == 0) && (DIR[moID3] == 1)) TxData1[5] = 0x10;
		else if((DIR[moID2] == 1) && (DIR[moID3] == 1)) TxData1[5] = 0x11;
		else ;

		m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData1,8);
		Sleep(20);
	}
	else if(BoardNo == EJMC3)
	{
		TxData[0] = BoardNo;
		TxData[1] = PwmCMD;
		TxData[2] = 0x01;
		TxData[3] = DIR[moID1];
		TxData[4] = PWM[moID1];
		TxData[5] = 0x00;
		TxData[6] = 0x00;
	
		m_CanWinOL.CAN_WRITE1(CMD_TXDF,TxData,7);
		Sleep(20);
	}
	
	
}

void COpenLoopTestDlg::OLRunStop14(char Flag)
{
	if(Flag == 1) // Run
	{
		PwmRun(JMC6);		// Left Knee pitch
		m_RUN14.EnableWindow(FALSE);
		m_STOP14.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		PwmStop(JMC6);		// Left Knee pitch
		m_STOP14.EnableWindow(FALSE);
		m_RUN14.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop15(char Flag)
{
	if(Flag == 1) // Run
	{
		PwmRun(JMC7);		// Left Ankle pitch & roll
		m_RUN15.EnableWindow(FALSE);
		m_STOP15.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		PwmStop(JMC7);		// Left Ankle pitch & roll
		m_STOP15.EnableWindow(FALSE);
		m_RUN15.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OnButtonRun14() 
{
	// TODO: Add your control notification handler code here
	RunStop[14] = 1;
	OLRunStop14(RunStop[14]);	
	
}

void COpenLoopTestDlg::OnButtonRun15() 
{
	// TODO: Add your control notification handler code here
	RunStop[15] = 1;
	OLRunStop15(RunStop[15]);	
}

void COpenLoopTestDlg::OnButtonStop14() 
{
	// TODO: Add your control notification handler code here
	RunStop[14] = 0;
	OLRunStop14(RunStop[14]);	
	
}

void COpenLoopTestDlg::OnButtonStop15() 
{
	// TODO: Add your control notification handler code here
	RunStop[15] = 0;
	OLRunStop15(RunStop[15]);	
	
}

void COpenLoopTestDlg::OnButtonRun20() 
{
	// TODO: Add your control notification handler code here
	RunStop[20] = 1;
	OLRunStop20(RunStop[20]);	
}

void COpenLoopTestDlg::OnButtonStop20() 
{
	// TODO: Add your control notification handler code here
	RunStop[20] = 0;
	OLRunStop20(RunStop[20]);
}

void COpenLoopTestDlg::OLRunStop20(char Flag)
{
	if(Flag == 1) // Run
	{
		PwmRun(EJMC1);		// Left Ankle pitch & roll
		m_RUN20.EnableWindow(FALSE);
		m_STOP20.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		PwmStop(EJMC1);		// Left Ankle pitch & roll
		m_STOP20.EnableWindow(FALSE);
		m_RUN20.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop21(char Flag)
{
	if(Flag == 1) // Run
	{
		PwmRun(EJMC0);		// Left Ankle pitch & roll
		m_RUN21.EnableWindow(FALSE);
		m_STOP21.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		PwmStop(EJMC0);		// Left Ankle pitch & roll
		m_STOP21.EnableWindow(FALSE);
		m_RUN21.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OLRunStop22(char Flag)
{
	if(Flag == 1) // Run
	{
		PwmRun(EJMC2);		// Left Ankle pitch & roll
		m_RUN22.EnableWindow(FALSE);
		m_STOP22.EnableWindow(TRUE);
	}
	else if(Flag == 0) // Stop
	{
		PwmStop(EJMC2);		// Left Ankle pitch & roll
		m_STOP22.EnableWindow(FALSE);
		m_RUN22.EnableWindow(TRUE);
	}
}

void COpenLoopTestDlg::OnButtonRun21() 
{
	// TODO: Add your control notification handler code here
	RunStop[21] = 1;
	OLRunStop21(RunStop[21]);
}

void COpenLoopTestDlg::OnButtonStop21() 
{
	// TODO: Add your control notification handler code here
	RunStop[21] = 0;
	OLRunStop21(RunStop[21]);
}

void COpenLoopTestDlg::OnButtonRun22() 
{
	// TODO: Add your control notification handler code here
	RunStop[22] = 1;
	OLRunStop22(RunStop[22]);
}

void COpenLoopTestDlg::OnButtonStop22() 
{
	// TODO: Add your control notification handler code here
	RunStop[22] = 0;
	OLRunStop22(RunStop[22]);
}
