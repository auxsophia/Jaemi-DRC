// khr3winDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "khr3winDlg.h"
#include "EncReadDlg.h"
#include "FT_ReadDlg.h"
#include "TiltReadDlg.h"
#include "OpenLoopTestDlg.h"
#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKhr3winDlg dialog
extern CKhr3winApp theApp;

CKhr3winDlg::CKhr3winDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKhr3winDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKhr3winDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKhr3winDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKhr3winDlg)
	DDX_Control(pDX, IDC_BUTTON_MOTOR_STATE, m_ButtonMotorState);
	DDX_Control(pDX, IDC_BUTTON_KIRK_WALKIING, m_ButtonKirkWalking);
	DDX_Control(pDX, IDC_BUTTON_GAIN_SET, m_ButtonGainSetting);
	DDX_Control(pDX, IDC_BUTTON_Parameters, m_ButtonParameterSetting);
	DDX_Control(pDX, IDC_BUTTON_WALKING, m_ButtonWalking);
	DDX_Control(pDX, IDC_BUTTON_Z_PHASE, m_ButtonZ_Phase);
	DDX_Control(pDX, IDC_BUTTON_UTIL, m_ButtonUtilityWin);
	DDX_Control(pDX, IDC_BUTTON_WALK, m_ButtonWalk);
	DDX_Control(pDX, IDC_BUTTON_POSITION_CTRL_TEST, m_ButtonPOSTest);
	DDX_Control(pDX, IDC_BUTTON_OPEN_LOOP_TEST, m_ButtonOLTest);
	DDX_Control(pDX, IDC_BUTTON_RTX_ON,		m_ButtonRTXOn	);
	DDX_Control(pDX, IDC_BUTTON_ENC_READ,	m_ButtonEncRead	);
	DDX_Control(pDX, IDC_BUTTON_FT_READ,	m_ButtonFTRead	);
	DDX_Control(pDX, IDC_BUTTON_TILT_READ,	m_ButtonTiltRead);
	DDX_Control(pDX, IDC_BUTTON_CAN_ON,		m_ButtonCanOn	);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKhr3winDlg, CDialog)
	//{{AFX_MSG_MAP(CKhr3winDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAN_ON, OnButtonCanOn)
	ON_BN_CLICKED(IDC_BUTTON_RTX_ON, OnButtonRtxOn)
	ON_BN_CLICKED(IDC_BUTTON_ENC_READ, OnButtonEncRead)
	ON_BN_CLICKED(IDC_BUTTON_FT_READ, OnButtonFtRead)
	ON_BN_CLICKED(IDC_BUTTON_TILT_READ, OnButtonTiltRead)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)	
	ON_BN_CLICKED(IDC_BUTTON_OPEN_LOOP_TEST, OnButtonOpenLoopTest)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_CTRL_TEST, OnButtonPositionCtrlTest)
	ON_BN_CLICKED(IDC_BUTTON_ENC_ZERO, OnButtonEncZero)
	ON_BN_CLICKED(IDC_BUTTON_SAVELOG, OnButtonSavelog)
	ON_BN_CLICKED(IDC_BUTTON_CTRL_OFF, OnButtonCtrlOff)
	ON_BN_CLICKED(IDC_BUTTON_WALK, OnButtonWalk)
	ON_BN_CLICKED(IDC_BUTTON_UTIL, OnButtonUtil)
	ON_BN_CLICKED(IDC_BUTTON_Z_PHASE, OnButtonZPhase)
	ON_BN_CLICKED(IDC_BUTTON_ZMP_ZERO, OnButtonZmpZero)
	ON_BN_CLICKED(IDC_BUTTON_WALKING, OnButtonWalking)
	ON_BN_CLICKED(IDC_BUTTON_Parameters, OnBUTTONParameters)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_SET, OnButtonGainSet)
	ON_BN_CLICKED(IDC_BUTTON_KIRK_WALKIING, OnButtonKirkWalkiing)
	ON_BN_CLICKED(IDC_BUTTON_MOTOR_STATE, OnButtonMotorState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKhr3winDlg message handlers

BOOL CKhr3winDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitSharedMemory();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKhr3winDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKhr3winDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKhr3winDlg::OnButtonCanOn() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	m_ButtonCanOn.GetWindowText(strText);
	
	if(strText == "CAN ON")
	{
		RTXON();
		CANON();
		ButtonControl(CAN_ON);
	}
	else if(strText == "CAN OFF")
	{
		CANOFF();
		ButtonControl(CAN_OFF);
	}
}

void CKhr3winDlg::OnButtonRtxOn() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	m_ButtonRTXOn.GetWindowText(strText);
	
	if(strText == "RTX ON")
	{
		RTXON();
		ButtonControl(RTX_ON);
	}
	else if(strText == "RTX OFF")
	{
		ButtonControl(RTX_OFF);
	}
}
void CKhr3winDlg::Close()
{
	theApp.m_pSharedMemory->bExitFlag = TRUE;
	if(m_EncReadDlg.GetSafeHwnd())
		m_EncReadDlg.DestroyWindow();

	OnOK();
}

void CKhr3winDlg::OnButtonEncRead() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	theApp.m_pSharedMemory->INT_Flag = FALSE;
	theApp.m_pSharedMemory->Rx_Flag = TRUE;

		m_ButtonEncRead.GetWindowText(strText);
	
		if(strText == "Enc SHOW")
		{
			ButtonControl(Enc_SHOW);
			theApp.m_pSharedMemory->Read_Enc_Flag=TRUE;
		}
		else if(strText == "Enc HIDE")
		{
			ButtonControl(Enc_HIDE);
//			theApp.m_pSharedMemory->Read_Enc_Flag=FALSE;
		}
		else
		{
			ButtonControl(Enc_CREATE);
			theApp.m_pSharedMemory->Read_Enc_Flag=TRUE;
		}
}

void CKhr3winDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString strText;

	m_ButtonEncRead.GetWindowText(strText);
	if(strText == "Enc HIDE")
		ButtonControl(Enc_HIDE);

	m_ButtonFTRead.GetWindowText(strText);
	if(strText == "FT HIDE")
		ButtonControl(FT_HIDE);

	CDialog::OnLButtonDown(nFlags, point);
}

void CKhr3winDlg::ButtonControl(int Msg)
{
	switch(Msg)
	{
/////////////////////////////////////////////////////////////////////
// Enc Button
	case Enc_CREATE:
		CreateEncDlg();
	case Enc_SHOW:
		m_EncReadDlg.ShowWindow(SW_SHOW);
		m_ButtonEncRead.SetWindowText("Enc HIDE");
		m_EncReadDlg.SetTimer(1,DISP_TIMER,NULL);
		break;

	case Enc_HIDE:
		m_EncReadDlg.ShowWindow(SW_HIDE);
		m_ButtonEncRead.SetWindowText("Enc SHOW");
		m_EncReadDlg.KillTimer(1);
		break;

	case Enc_CLOSE:
		m_ButtonEncRead.SetWindowText("Enc READ");
		break;
																   //
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// FT Read Button	
	case FT_CREATE:
		CreateFTDlg();
	case FT_SHOW:
		m_FT_ReadDlg.ShowWindow(SW_SHOW);
		m_ButtonFTRead.SetWindowText("FT HIDE");
		m_FT_ReadDlg.SetTimer(1,DISP_TIMER,NULL);//DISP_TIMER
		break;
		
	case FT_HIDE:
		m_FT_ReadDlg.ShowWindow(SW_HIDE);
		m_ButtonFTRead.SetWindowText("FT SHOW");
		m_FT_ReadDlg.KillTimer(1);
		break;
		
	case FT_CLOSE:
		m_ButtonFTRead.SetWindowText("FT READ");
		m_FT_ReadDlg.KillTimer(1);
		break;
																   //
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Tilt Read Button	
	case TILT_CREATE:
		CreateTiltDlg();
	case TILT_SHOW:
		m_TiltReadDlg.ShowWindow(SW_SHOW);
		m_ButtonTiltRead.SetWindowText("TILT HIDE");
		m_TiltReadDlg.SetTimer(1,DISP_TIMER,NULL);//DISP_TIMER
		break;
		
	case TILT_HIDE:
		m_TiltReadDlg.ShowWindow(SW_HIDE);
		m_ButtonTiltRead.SetWindowText("TILT SHOW");
		m_TiltReadDlg.KillTimer(1);
		break;
		
	case TILT_CLOSE:
		m_ButtonTiltRead.SetWindowText("TILT READ");
		m_TiltReadDlg.KillTimer(1);
		break;													   //
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Open Loop Test

	case OL_CREATE:
		CreateOLTestDlg();
	
	case OL_SHOW:
		m_OpenLoopTestDlg.ShowWindow(SW_SHOW);
		m_ButtonOLTest.SetWindowText("OL Hide");
		break;

	case OL_HIDE:
		m_OpenLoopTestDlg.ShowWindow(SW_HIDE);
		m_ButtonOLTest.SetWindowText("OL Show");
		break;

	case OL_CLOSE:
		m_ButtonOLTest.SetWindowText("OL Start");
		break;		
																   //
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Position control - Joint Test
	case POS_CREATE:
		CreatePOSTestDlg();

	case POS_SHOW:
		m_PositionControlDlg.ShowWindow(SW_SHOW);
		m_ButtonPOSTest.SetWindowText("POS Hide");
		break;

	case POS_HIDE:
		m_PositionControlDlg.ShowWindow(SW_HIDE);
		m_ButtonPOSTest.SetWindowText("POS Show");
		break;

	case POS_CLOSE:
		m_ButtonPOSTest.SetWindowText("POS CTRL Start");
		break;
																   //
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Walking - Joint Test
	case WALK_CREATE:
		CreateWalkDlg();

	case WALK_SHOW:
		m_Walk00TestDlg.ShowWindow(SW_SHOW);
		m_ButtonWalk.SetWindowText("Walk Hide");
		break;

	case WALK_HIDE:
		m_Walk00TestDlg.ShowWindow(SW_HIDE);
		m_ButtonWalk.SetWindowText("Walk Show");
		break;

	case WALK_CLOSE:
		m_ButtonWalk.SetWindowText("Walk01");
		break;
																	//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
	case WALKING_EXP_CREATE:
		CreateWalkingExpDlg();
	case WALKING_EXP_SHOW:
		m_WalkingExpDlg.ShowWindow(SW_SHOW);
		m_ButtonWalking.SetWindowText("Walking Hide");
		break;
	case WALKING_EXP_HIDE:
		m_WalkingExpDlg.ShowWindow(SW_HIDE);
		m_ButtonWalking.SetWindowText("Walking Show");
		break;
	case WALKING_EXP_CLOSE:
		m_ButtonWalking.SetWindowText("Walking Exp.");
		break;
//
/////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////
		//
	case KIRK_WALKING_EXP_CREATE:
		CreateKirkWalkingDlg();
	case KIRK_WALKING_EXP_SHOW:
		m_KirkWalking2Dlg.ShowWindow(SW_SHOW);
		m_ButtonKirkWalking.SetWindowText("Walking Hide");
		break;
	case KIRK_WALKING_EXP_HIDE:
		m_KirkWalking2Dlg.ShowWindow(SW_HIDE);
		m_ButtonKirkWalking.SetWindowText("Walking Show");
		break;
	case KIRK_WALKING_EXP_CLOSE:
		m_ButtonKirkWalking.SetWindowText("Walking Exp.");
		break;
		//
		/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// Parameter setting
		
	case PARAMETER_SETTING_CREATE:
		CreateParameterSetting();
		
	case PARAMETER_SETTING_SHOW:
		m_ParameterSetting.ShowWindow(SW_SHOW);
		m_ButtonParameterSetting.SetWindowText("Para Hide");
		break;
		
	case PARAMETER_SETTING_HIDE:
		m_ParameterSetting.ShowWindow(SW_HIDE);
		m_ButtonParameterSetting.SetWindowText("Para Show");
		m_ParameterSetting.SetWindowText("Para Show");
		break;
		
	case PARAMETER_SETTING_CLOSE:
		m_ButtonParameterSetting.SetWindowText("Para Start");
		m_ParameterSetting.SetWindowText("Para Start");
		break;		
//
/////////////////////////////////////////////////////////////////////
// GAIN setting
		
	case GAIN_SETTING_CREATE:
		CreateGainSetting();
		
	case GAIN_SETTING_SHOW:
		m_GainSetting.ShowWindow(SW_SHOW);
		m_ButtonGainSetting.SetWindowText("GAIN Hide");
		break;
		
	case GAIN_SETTING_HIDE:
		m_GainSetting.ShowWindow(SW_HIDE);
		m_ButtonGainSetting.SetWindowText("GAIN Show");
		m_GainSetting.SetWindowText("GAIN Show");
		break;
		
	case GAIN_SETTING_CLOSE:
		m_ButtonGainSetting.SetWindowText("GAIN Start");
		m_GainSetting.SetWindowText("GAIN Start");
		break;		
//
/////////////////////////////////////////////////////////////////////
// MOTOR STATE
		
	case MOTOR_STATE_CREATE:
		CreateMotorState();
		
	case MOTOR_STATE_SHOW:
		m_MotorState.ShowWindow(SW_SHOW);
		m_ButtonMotorState.SetWindowText("State Hide");
		break;
		
	case MOTOR_STATE_HIDE:
		m_MotorState.ShowWindow(SW_HIDE);
		m_ButtonMotorState.SetWindowText("State Show");
		m_MotorState.SetWindowText("State Show");
		break;
		
	case MOTOR_STATE_CLOSE:
		m_ButtonMotorState.SetWindowText("State Start");
		m_MotorState.SetWindowText("State Start");
		break;		
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	case CAN_ON:
		m_ButtonCanOn.SetWindowText("CAN OFF");
		m_ButtonRTXOn.SetWindowText("RTX OFF");
		break;
	case CAN_OFF:
		m_ButtonCanOn.SetWindowText("CAN ON");
		m_ButtonRTXOn.SetWindowText("RTX ON");
		break;
	case RTX_ON:
		m_ButtonRTXOn.SetWindowText("RTX OFF");
		m_ButtonCanOn.SetWindowText("CAN OFF");
		break;
	case RTX_OFF:
		Close();
		break;
	}
}

void CKhr3winDlg::CreateEncDlg()
{
	if(!m_EncReadDlg.m_hWnd)
	{
		m_EncReadDlg.Create(IDD_DIALOG_ENC_READ, this);
		m_EncReadDlg.SetParentWindow(this);
	}
}

void CKhr3winDlg::CreateFTDlg()
{
	if(!m_FT_ReadDlg.m_hWnd)
	{
		m_FT_ReadDlg.Create(IDD_DIALOG_FT_READ, this);
		m_FT_ReadDlg.SetParentWindow(this);
		m_FT_ReadDlg.Init();
	}
}

void CKhr3winDlg::CreateTiltDlg()
{
	if(!m_TiltReadDlg.m_hWnd)
	{
		m_TiltReadDlg.Create(IDD_DIALOG_TILT_READ, this);
		m_TiltReadDlg.SetParentWindow(this);
		m_TiltReadDlg.Init();
	}
}

void CKhr3winDlg::CreateOLTestDlg()
{
	if(!m_OpenLoopTestDlg.m_hWnd)
	{
		m_OpenLoopTestDlg.Create(IDD_DIALOG_OPEN_LOOP_TEST,this);
		m_OpenLoopTestDlg.SetParentWindow(this);
		m_OpenLoopTestDlg.Init();
	}
}

void CKhr3winDlg::CreatePOSTestDlg()
{
	if(!m_PositionControlDlg.m_hWnd)
	{
		m_PositionControlDlg.Create(IDD_DIALOG_POSITION_CONTROL,this);
		m_PositionControlDlg.SetParentWindow(this);
		m_PositionControlDlg.Init();
	}
}

void CKhr3winDlg::CreateWalkDlg()
{
	if(!m_Walk00TestDlg.m_hWnd)
	{
	
	}
}

void CKhr3winDlg::CANON()
{
	int j;
	m_CANwin.BuffClear();
	m_CANwin.FlagClear();

	theApp.m_pSharedMemory->Rx_Flag = TRUE;
	Sleep(100);
	
	LoadParameter();
	//m_CANwin.PingCAN(JMC4);
	//Sleep(100);
	
	
	for(j=0; j<TOTAL_JMC_NUM;j++)
	{
		m_CANwin.PingCAN(j);
		Sleep(100);
	}

	for(j=32; j<32+TOTAL_EJMC_NUM;j++)
	{
		m_CANwin.PingCAN(j);
		Sleep(100);
	}
	
	for(j=48; j<48+TOTAL_SEN_NUM;j++)
	{
		m_CANwin.PingCAN(j);
		Sleep(100);
	}

	for(j=RHY;j<=LAR;j++)
	{
		GainSet(j);
		Sleep(100);
	}

	for(j=RSP;j<=LEB;j++)
	{
		GainSet(j);
		Sleep(100);
	}

	for(j=RWY;j<=LW2;j++)
	{
		GainSet(j);
		Sleep(100);
	}
	

	theApp.m_pSharedMemory->LoadParameterFlag = TRUE;
	
	m_CANwin.PingReply();

	theApp.m_pSharedMemory->Rx_Flag = FALSE;
	Sleep(1000);
	
	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void CKhr3winDlg::CANOFF()
{
	theApp.m_pSharedMemory->bExitFlag = TRUE;	
}

void CKhr3winDlg::RTXON()
{
	//LPCTSTR RTSS_RUNNER = "E:\\HUBO2\\HUBO2___Win32_RTSS_Release\\HUBO2.rtss";
	//LPCTSTR RTSS_RUNNER = "D:\\user\\becool\\KHR3\\khr3___Win32_RTSS_Release\\Khr3.rtss";
	LPCTSTR RTSS_RUNNER = "..\\HUBO2___Win32_RTSS_Release\\HUBO2.rtss";
	PROCESS_INFORMATION pi;

	if ( !RtCreateProcess(
							RTSS_RUNNER,	// path of RTX program
							NULL,			// command line to execute
							NULL,			// don't care
							NULL,			// don't care
							NULL,			// don't care
							NULL,			// don't care
							NULL,			// don't care
							NULL,			// don't care
							NULL,			// don't care
							&pi ))			// process information
	{
		RtWprintf(L"RtCreateProcess error = %d\n", GetLastError());
		ExitProcess(1);
	}
	else RtCloseHandle(pi.hProcess);

	Sleep(500);  // 매우 중요 !!!

	
}

void CKhr3winDlg::RTXOFF()
{
	Close();
	theApp.m_pSharedMemory->bExitFlag = TRUE;
	theApp.m_pSharedMemory->Read_Enc_Flag=FALSE;
	theApp.m_pSharedMemory->Read_Enc_Flag=FALSE;
	theApp.m_pSharedMemory->Read_FTS_Flag=FALSE;
	theApp.m_pSharedMemory->Read_TILT_Flag = FALSE;
}

void CKhr3winDlg::InitSharedMemory()
{
	theApp.m_hSharedMemory = RtCreateSharedMemory(
										PAGE_READWRITE,				// access mode
										0,							// maximum size high
										sizeof(SHARED_DATA),		// maximum size low	
										"Can Shared Data",			// name of shared memory
										(VOID **)&theApp.m_pSharedMemory);	// shared memory data address 

	if (theApp.m_hSharedMemory == NULL)
	{
		RtWprintf(L"RtCreateSharedMemory error = %d\n", GetLastError());
		ExitProcess(1);
	}
}

void CKhr3winDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
/*	char i;

	theApp.SendCTRLOff();	// 제어를 끈다.
	Sleep(30);				// 중요!!! 시간  Delay 
	theApp.Stop_CMD();		// 중요 !!! PWM  을  영으로 확실히 셋팅
	Sleep(30);
	
	for(i=0;i<TOTAL_MTR_NUM;i++)	theApp.DisableHIP(i); // HIP을 Disable시킴
*/
	theApp.m_pSharedMemory->bExitFlag = TRUE;
	PostQuitMessage(0);
}

void CKhr3winDlg::OnButtonFtRead() 
{
	// TODO: Add your control notification handler code here

	CString strText;

	m_ButtonFTRead.GetWindowText(strText);
	
	if(strText == "FT HIDE")
	{
		ButtonControl(FT_HIDE);
	}
	else if(strText =="FT SHOW")
	{
		ButtonControl(FT_SHOW);
	}
	else 
	{
		ButtonControl(FT_CREATE);
	}
}

void CKhr3winDlg::OnButtonTiltRead() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonTiltRead.GetWindowText(strText);
	
	if(strText == "TILT HIDE")
	{
		ButtonControl(TILT_HIDE);
	}
	else if(strText =="TILT SHOW")
	{
		ButtonControl(TILT_SHOW);
	}
	else 
	{
		ButtonControl(TILT_CREATE);
	}	
}

void CKhr3winDlg::OnButtonOpenLoopTest() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	theApp.m_pSharedMemory->INT_Flag = FALSE;
	
	m_ButtonOLTest.GetWindowText(strText);
	
	if(strText == "OL Hide")
	{
		ButtonControl(OL_HIDE);
	}
	else if(strText =="OL Show")
	{
		ButtonControl(OL_SHOW);
	}
	else 
	{
		ButtonControl(OL_CREATE);
	}	
}

void CKhr3winDlg::OnButtonPositionCtrlTest() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	theApp.m_pSharedMemory->INT_Flag = TRUE;

	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;

	m_ButtonPOSTest.GetWindowText(strText);

	if(strText == "POS Hide")
	{
		ButtonControl(POS_HIDE);
	}
	else if(strText == "POS Show")
	{
		ButtonControl(POS_SHOW);
	}
	else
	{
		ButtonControl(POS_CREATE);
	}
}

void CKhr3winDlg::OnButtonEncZero() 
{
	// TODO: Add your control notification handler code here
	unsigned char i;
	theApp.m_pSharedMemory->INT_Flag = FALSE;
	Sleep(50);

	for(i=0;i<TOTAL_JMC_NUM;i++) theApp.Encoder_ZeroCMD(i);

	for(i=EJMC0;i<(EJMC0+TOTAL_EJMC_NUM);i++) theApp.Encoder_ZeroCMD(i);

	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void CKhr3winDlg::OnButtonSavelog() 
{
	// TODO: Add your control notification handler code here
	SaveLog();	
}

void CKhr3winDlg::SaveLog()
{
	int i=0, j=0;
	CString FileName;
	char szFilter[] = "DAT Files (*.dat) |*.DAT|ALL Files (*.*) |*.*|";
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	szFilter );
	if(dlg.DoModal()==IDOK)
	{
		FileName=dlg.GetPathName();
		if(FileName.Find(".")==-1) FileName+=".dat";
		
		FILE *SaveFile;
		SaveFile=fopen(FileName,"w");
		
		for(i=1;i<SaveData_ROW-1;i++)
		{
			for(j=0;j<SaveData_COL;j++)
			{
				fprintf(SaveFile,"%f\t",theApp.m_pSharedMemory->SaveData[i][j]);
			}
			fprintf(SaveFile,"\n");
		}
	 
		/*
		for(i=0;i<12;i++)
		{
			fprintf(SaveFile,"%f\n",theApp.m_pSharedMemory->PPR[RHY+i]);
		}

		for(i=0;i<12;i++)
		{
			fprintf(SaveFile,"%f\n",theApp.m_pSharedMemory->temp[i]);
		}
		*/
		fclose(SaveFile);
	}
}

void CKhr3winDlg::OnButtonCtrlOff()
{
	// TODO: Add your control notification handler code here
	unsigned char i;

	theApp.m_pSharedMemory->INT_Flag = FALSE;
	Sleep(100);

	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.SendCTRLOff(i);	// 제어를 끈다.
		Sleep(30);				// 중요!!! 시간  Delay 
		theApp.Stop_CMD(i);		// 중요 !!! PWM  을  영으로 확실히 셋팅
		Sleep(30);
	}

	for(i=EJMC0;i<=(EJMC0+TOTAL_EJMC_NUM);i++)
	{
		theApp.SendCTRLOff(i);	// 제어를 끈다.
		Sleep(30);				// 중요!!! 시간  Delay 
		theApp.Stop_CMD(i);		// 중요 !!! PWM  을  영으로 확실히 셋팅
		Sleep(30);
	}

	theApp.m_pSharedMemory->POS_CTRL_Flag = FALSE;
	theApp.m_pSharedMemory->INT_Flag = TRUE;
}

void CKhr3winDlg::OnButtonWalk()
{
	// TODO: Add your control notification handler code here
	CString strText;

	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	m_ButtonWalk.GetWindowText(strText);
	
	if(strText == "Walk Hide")
	{
		ButtonControl(WALK_HIDE);
	}
	else if(strText == "Walk Show")
	{
		ButtonControl(WALK_SHOW);
	}
	else
	{
		ButtonControl(WALK_CREATE);
	}
}

void CKhr3winDlg::OnButtonUtil() 
{
	// TODO: Add your control notification handler code here
	if(!m_UtilityWinDlg.m_hWnd)
	{
		m_UtilityWinDlg.Create(IDD_DIALOG_UTIL, this);
		m_UtilityWinDlg.SetParentWindow(this);
	}
	m_UtilityWinDlg.ShowWindow(SW_SHOW);
}

void CKhr3winDlg::OnButtonZPhase() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->InitialPositionSettingFlag = TRUE;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->Rx_Flag = TRUE;
	CreateZ_PhaseDlg();
}

void CKhr3winDlg::CreateZ_PhaseDlg()
{
	if(!m_Z_PhaseSetDlg.m_hWnd)
	{
		m_Z_PhaseSetDlg.Create(IDD_DIALOG_Z_PHASE,this);
		m_Z_PhaseSetDlg.SetParentWindow(this);
		m_Z_PhaseSetDlg.Init();
		m_Z_PhaseSetDlg.ShowWindow(SW_SHOW);
		m_Z_PhaseSetDlg.SetTimer(1, DISP_TIMER,NULL);
	}
}

void CKhr3winDlg::OnButtonZmpZero() 
{
	// TODO: Add your control notification handler code here
	CreateFTDlg();
	m_ButtonFTRead.SetWindowText("FT SHOW");
	CreateTiltDlg();
	m_ButtonTiltRead.SetWindowText("TILT SHOW");
	
	if(!m_ZMPZeroDlg.m_hWnd)
	{
		m_ZMPZeroDlg.Create(IDD_DIALOG_ZMP_ZERO,this);
		m_ZMPZeroDlg.SetParentWindow(this);
		m_ZMPZeroDlg.Init();
		m_ZMPZeroDlg.ShowWindow(SW_SHOW);
	}
	theApp.m_pSharedMemory->Ini_ZMP_Zero_Flag=TRUE;
}

void CKhr3winDlg::OnButtonWalking() 
{
	// TODO: Add your control notification handler code here

	CString strText;
	
	
	m_ButtonWalking.GetWindowText(strText);

	if(strText == "Walking Hide")
	{
		ButtonControl(WALKING_EXP_HIDE);
	}
	else if(strText == "Walking Show")
	{
		ButtonControl(WALKING_EXP_SHOW);
	}
	else
	{
		ButtonControl(WALKING_EXP_CREATE);
	}
}

void CKhr3winDlg::CreateWalkingExpDlg()
{
	if(!m_WalkingExpDlg.m_hWnd)
	{
		
	}
}



void CKhr3winDlg::OnBUTTONParameters() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonParameterSetting.GetWindowText(strText);
	
	if(strText == "Para Hide")
	{
		ButtonControl(PARAMETER_SETTING_HIDE);
	}
	else if(strText == "Para Show")
	{
		ButtonControl(PARAMETER_SETTING_SHOW);
	}
	else
	{
		ButtonControl(PARAMETER_SETTING_CREATE);
	}
}

void CKhr3winDlg::CreateParameterSetting()
{
	if(!m_ParameterSetting.m_hWnd)
	{
		m_ParameterSetting.Create(IDD_DIALOG_PARAMETER_SETTING, this);
		m_ParameterSetting.SetParentWindow(this);
		m_ParameterSetting.Init();
	}	

}

void CKhr3winDlg::LoadParameter()
{
	float Harmonic[TOTAL_MTR_NUM];
	float Drive[TOTAL_MTR_NUM];
	float Driven[TOTAL_MTR_NUM];
	float Enc[TOTAL_MTR_NUM];
	long Offset_Rev[TOTAL_MTR_NUM];
	long Offset_Pulse[TOTAL_MTR_NUM];
	long Limit_Rev[TOTAL_MTR_NUM];
	float Dir[TOTAL_MTR_NUM];
	//FILE *fp;
	int i;

	long kp0[TOTAL_MTR_NUM];
	long kp1[TOTAL_MTR_NUM];
	long kd0[TOTAL_MTR_NUM];
	long kd1[TOTAL_MTR_NUM];
	long ki0[TOTAL_MTR_NUM];
	long ki1[TOTAL_MTR_NUM];

	int No_Data_line;

	No_Data_line = 30;

	// open file
	ifstream fin("parameter.par");
	if (!fin.is_open())
	{
		AfxMessageBox("LoadDataFromFile() :: parameter.par 파일을 열 수 없습니다.", MB_OK);
	}
	else
	{
		for(i=0;i<No_Data_line;i++)
		{
			fin >> Harmonic[i] >> Drive[i] >> Driven[i] >> Enc[i] >> Offset_Rev[i] >> Offset_Pulse[i] >> Limit_Rev[i] >> Dir[i];
			//fscanf(fp,"%f %f %f %f",&a1,&a2,&a3,&a4);
			
			if(i<12)
			{
				theApp.m_pSharedMemory->PPR[RHY+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[RHY+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[RHY+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[RHY+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[RHY+i] = Dir[i];
			}
			else if((i>=12) && (i<16))
			{
				theApp.m_pSharedMemory->PPR[RSP-12+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[RSP-12+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[RSP-12+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[RSP-12+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[RSP-12+i] = Dir[i];
			}
			else if((i>=16) && (i<19))
			{
				theApp.m_pSharedMemory->PPR[RWY-16+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[RWY-16+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[RWY-16+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[RWY-16+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[RWY-16+i] = Dir[i];
			}
			else if((i>=19) && (i<23))
			{
				theApp.m_pSharedMemory->PPR[LSP-19+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[LSP-19+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[LSP-19+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[LSP-19+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[LSP-19+i] = Dir[i];
			}
			else if((i>=23) && (i<26))
			{
				theApp.m_pSharedMemory->PPR[LWY-23+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[LWY-23+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[LWY-23+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[LWY-23+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[LWY-23+i] = Dir[i];
			}
			else if(i == 26)
			{
				theApp.m_pSharedMemory->PPR[WST] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[WST] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[WST] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[WST] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[WST] = Dir[i];
			}
			else if((i>=27) && (i<30))
			{
				theApp.m_pSharedMemory->PPR[NKY-27+i] = (float)(Harmonic[i]*(Driven[i]/Drive[i])*Enc[i]);
				theApp.m_pSharedMemory->Offset_Pulse[NKY-27+i] = Offset_Pulse[i];
				theApp.m_pSharedMemory->Offset_Rev[NKY-27+i] = Offset_Rev[i];
				theApp.m_pSharedMemory->Limit_Rev[NKY-27+i] = Limit_Rev[i];
				theApp.m_pSharedMemory->PLUS_MTR_DIR[NKY-27+i] = Dir[i];
			}
			else ;
			
		}
		
		//AfxMessageBox("Parameters are loaded.", MB_OK);	
	}
	
	// close file
	fin.close();

	// open file
	ifstream fin2("GainSetting.set");
	if (!fin2.is_open())
	{
		AfxMessageBox("LoadDataFromFile() :: GainSetting.set 파일을 열 수 없습니다.", MB_OK);
	}
	else
	{
		for(i=0;i<No_Data_line;i++)
		{
			fin2 >> kp0[i] >> kd0[i] >> ki0[i] >> kp1[i] >> kd1[i] >> ki1[i];
			//fscanf(fp,"%f %f %f %f",&a1,&a2,&a3,&a4);
			
			if(i<12)
			{
				theApp.m_pSharedMemory->Kp0[RHY+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[RHY+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[RHY+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[RHY+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[RHY+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[RHY+i] = ki1[i];
			}
			else if( (i>=12) && (i<16))
			{
				theApp.m_pSharedMemory->Kp0[RSP-12+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[RSP-12+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[RSP-12+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[RSP-12+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[RSP-12+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[RSP-12+i] = ki1[i];
			}
			else if((i>=16) && (i<19))
			{
				theApp.m_pSharedMemory->Kp0[RWY-16+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[RWY-16+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[RWY-16+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[RWY-16+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[RWY-16+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[RWY-16+i] = ki1[i];
			}
			else if((i>=19) && (i<23))
			{
				theApp.m_pSharedMemory->Kp0[LSP-19+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[LSP-19+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[LSP-19+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[LSP-19+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[LSP-19+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[LSP-19+i] = ki1[i];
			}
			else if((i>=23) && (i<26))
			{
				theApp.m_pSharedMemory->Kp0[LWY-23+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[LWY-23+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[LWY-23+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[LWY-23+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[LWY-23+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[LWY-23+i] = ki1[i];
			}
			else if(i==26)
			{
				theApp.m_pSharedMemory->Kp0[WST] = kp0[i];
				theApp.m_pSharedMemory->Kp1[WST] = kp1[i];
				theApp.m_pSharedMemory->Kd0[WST] = kd0[i];
				theApp.m_pSharedMemory->Kd1[WST] = kd1[i];
				theApp.m_pSharedMemory->Ki0[WST] = ki0[i];
				theApp.m_pSharedMemory->Ki1[WST] = ki1[i];
			}
			else if((i>=27) && (i<30))
			{
				theApp.m_pSharedMemory->Kp0[NKY-27+i] = kp0[i];
				theApp.m_pSharedMemory->Kp1[NKY-27+i] = kp1[i];
				theApp.m_pSharedMemory->Kd0[NKY-27+i] = kd0[i];
				theApp.m_pSharedMemory->Kd1[NKY-27+i] = kd1[i];
				theApp.m_pSharedMemory->Ki0[NKY-27+i] = ki0[i];
				theApp.m_pSharedMemory->Ki1[NKY-27+i] = ki1[i];
			}
			else ;
			
			
		}
		
		//AfxMessageBox("Gains are loaded.", MB_OK);	
	}
	
	fin2.close();

	// open file
	ifstream fin3("z_ref.ref");
	if (!fin3.is_open())
	{
		AfxMessageBox("LoadDataFromFile() :: z_ref.ref 파일을 열 수 없습니다.", MB_OK);
	}
	else
	{
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RHY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RHR];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RHP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RKN];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RAP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RAR];

		fin3 >> theApp.m_pSharedMemory->Z_Ref[LHY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LHR];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LHP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LKN];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LAP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LAR];

		fin3 >> theApp.m_pSharedMemory->Z_Ref[RSP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RSR];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RSY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[REB];

		fin3 >> theApp.m_pSharedMemory->Z_Ref[LSP];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LSR];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LSY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LEB];
		
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RWY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RW1];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[RW2];

		fin3 >> theApp.m_pSharedMemory->Z_Ref[LWY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LW1];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[LW2];
				
		fin3 >> theApp.m_pSharedMemory->Z_Ref[NKY];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[NK1];
		fin3 >> theApp.m_pSharedMemory->Z_Ref[NK2];
	
		fin3 >> theApp.m_pSharedMemory->Z_Ref[WST];
		
		//AfxMessageBox("Z_ref is loaded.", MB_OK);	
	}

	fin3.close();
}

void CKhr3winDlg::OnButtonGainSet() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonParameterSetting.GetWindowText(strText);
	
	if(strText == "GAIN Hide")
	{
		ButtonControl(GAIN_SETTING_HIDE);
	}
	else if(strText == "GAIN Show")
	{
		ButtonControl(GAIN_SETTING_SHOW);
	}
	else
	{
		ButtonControl(GAIN_SETTING_CREATE);
	}
}

void CKhr3winDlg::CreateGainSetting()
{
	if(!m_GainSetting.m_hWnd)
	{
		m_GainSetting.Create(IDD_DIALOG_GAIN_SETTING, this);
		m_GainSetting.SetParentWindow(this);
		m_GainSetting.Init();
	}
}

void CKhr3winDlg::GainSet(int MotorNo)
{
	unsigned char TxData[8];
	unsigned char tp_BoardNo;
	tp_BoardNo = 0;
	
	switch (MotorNo){
	case RHY:
		tp_BoardNo = 0;
		TxData[1] = 0x07;
		break;
	case RHR:
		tp_BoardNo = 0;
		TxData[1] = 0x08;
		break;
	case RHP:
		tp_BoardNo = 1;
		TxData[1] = 0x07;
		break;
	case RKN :
		tp_BoardNo = 2;
		TxData[1] = 0x07;
		break;
	case RAP:
		tp_BoardNo = 3;
		TxData[1] = 0x07;
		break;
	case RAR:
		tp_BoardNo = 3;
		TxData[1] = 0x08;
		break;
	case LHY:
		tp_BoardNo = 4;
		TxData[1] = 0x07;
		break;
	case LHR:
		tp_BoardNo = 4;
		TxData[1] = 0x08;
		break;
	case LHP:
		tp_BoardNo = 5;
		TxData[1] = 0x07;
		break;
	case LKN :
		tp_BoardNo = 6;
		TxData[1] = 0x07;
		break;
	case LAP:
		tp_BoardNo = 7;
		TxData[1] = 0x07;
		break;
	case LAR:
		tp_BoardNo = 7;
		TxData[1] = 0x08;
		break;
	case RSP:
		tp_BoardNo = JMC8;
		TxData[1] = 0x07;
		break;
	case RSR:
		tp_BoardNo = JMC8;
		TxData[1] = 0x08;
		break;
	case RSY:
		tp_BoardNo = JMC9;
		TxData[1] = 0x07;
		break;
	case REB:
		tp_BoardNo = JMC9;
		TxData[1] = 0x08;
		break;
	case LSP:
		tp_BoardNo = JMC10;
		TxData[1] = 0x07;
		break;
	case LSR:
		tp_BoardNo = JMC10;
		TxData[1] = 0x08;
		break;
	case LSY:
		tp_BoardNo = JMC11;
		TxData[1] = 0x07;
		break;
	case LEB:
		tp_BoardNo = JMC11;
		TxData[1] = 0x08;
		break;
	case RWY:
		tp_BoardNo = EJMC0;
		TxData[1] = 0x07;
		break;
	case RW1:
		tp_BoardNo = EJMC0;
		TxData[1] = 0x08;
		break;
	case RW2:
		tp_BoardNo = EJMC0;
		TxData[1] = 0x08;
		break;
	case LWY:
		tp_BoardNo = EJMC1;
		TxData[1] = 0x07;
		break;
	case LW1:
		tp_BoardNo = EJMC1;
		TxData[1] = 0x08;
		break;
	case LW2:
		tp_BoardNo = EJMC1;
		TxData[1] = 0x08;
		break;
	}
	
	TxData[0] = tp_BoardNo;
	
	//if((MotorNo == RHR) || (MotorNo == RAR) || (MotorNo == LHR) || (MotorNo == LAR)) TxData[1] = 0x08;
	//else TxData[1] = 0x07;
	
	
	TxData[2] = (unsigned char)(theApp.m_pSharedMemory->Kp0[MotorNo] & 0xFF);
	TxData[3] = (unsigned char)((theApp.m_pSharedMemory->Kp0[MotorNo] >> 8) & 0xFF);
	TxData[4] = (unsigned char)(theApp.m_pSharedMemory->Ki0[MotorNo] & 0xFF);
	TxData[5] = (unsigned char)((theApp.m_pSharedMemory->Ki0[MotorNo] >> 8) & 0xFF);
	TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Kd0[MotorNo] & 0xFF);
	TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Kd0[MotorNo] >> 8) & 0xFF);
	
	if((tp_BoardNo >= JMC0) && (tp_BoardNo <= JMC7))
	{
		m_CANwin.CAN_WRITE(CMD_TXDF,TxData,8);
	}
	else
	{
		m_CANwin.CAN_WRITE1(CMD_TXDF,TxData,8);
	}

	Sleep(50);
	
}

void CKhr3winDlg::OnButtonKirkWalkiing() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonWalking.GetWindowText(strText);
	
	if(strText == "Walking Hide")
	{
		ButtonControl(KIRK_WALKING_EXP_HIDE);
	}
	else if(strText == "Walking Show")
	{
		ButtonControl(KIRK_WALKING_EXP_SHOW);
	}
	else
	{
		ButtonControl(KIRK_WALKING_EXP_CREATE);
	}
}

void CKhr3winDlg::CreateKirkWalkingDlg()
{
	if(!m_KirkWalking2Dlg.m_hWnd)
	{
		m_KirkWalking2Dlg.Create(IDD_DIALOG_KIRK2_WALKING,this);
		m_KirkWalking2Dlg.SetParentWindow(this);
		m_KirkWalking2Dlg.Init();
	}

}

void CKhr3winDlg::OnButtonMotorState() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonWalking.GetWindowText(strText);
	
	if(strText == "State Hide")
	{
		ButtonControl(MOTOR_STATE_HIDE);
	}
	else if(strText == "State Show")
	{
		ButtonControl(MOTOR_STATE_SHOW);
	}
	else
	{
		ButtonControl(MOTOR_STATE_CREATE);
	}
}

void CKhr3winDlg::CreateMotorState()
{
	if(!m_MotorState.m_hWnd)
	{
		m_MotorState.Create(IDD_DIALOG_MOTOR_STATE,this);
		m_MotorState.SetParentWindow(this);
		m_MotorState.Init();
	}
}


