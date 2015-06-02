// Walk00TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Khr3winDlg.h"
#include "Walk00TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKhr3winApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWalk00TestDlg dialog

CWalk00TestDlg::CWalk00TestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CWalk00TestDlg::IDD, pParent), m_Board_FootX(this, 3), m_Board_FootY(this, 3), m_Board_FootZ(this, 3)
{
	//{{AFX_DATA_INIT(CWalk00TestDlg)
	m_SideAmplitude = 0.0f;
	m_SwayAmplitude = 0.0f;
	m_DSP_During = 0;
	m_EDIT_OveralGLP = 0.0f;
	m_EDIT_OveralGLR = 0.0f;
	m_EDIT_OveralGRP = 0.0f;
	m_EDIT_OveralGRR = 0.0f;
	m_Vib_Gain = 0.0f;
	m_Vib_GainY = 0.0f;
	m_inAMPX = 0.0f;
	m_inAMPY = 0.0f;
	m_inFREQ = 0.0f;
	m_NumShake = 0;
	m_ZMP_OveralY = 4.0f;
	m_ZMP_OveralX = 1.1f;
	m_Push_Amp = 0.0f;
	m_Push_Hz = 0.0f;
	m_Torso_CTRL_Left_P = 0.0f;
	m_Torso_CTRL_Left_R = 0.0f;
	m_Torso_CTRL_Right_P = 0.0f;
	m_Torso_CTRL_Right_R = 0.0f;
	m_AnkleAmp = 0.0f;
	m_AnkleFq = 0.0f;
	m_WristAmp = 0.0f;
	m_WristHz = 0.0f;
	m_ShoulderHz = 0.0f;
	m_ShoulderPitchAmp = 0.0f;
	m_ShoulderRollAmp = 0.0f;
	m_I_Gain = 0.0f;
	m_HandAmp = 0.0f;
	m_HandFreq = 0.0f;
	m_WristMotionMode = 0;
	//}}AFX_DATA_INIT
}


void CWalk00TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWalk00TestDlg)
	DDX_Control(pDX, IDC_BUTTON_CTRL_OFF, m_ButtonCTRLOff);
	DDX_Control(pDX, IDC_BUTTON_CTRL_ON, m_ButtonCTRLOn);
	DDX_Control(pDX, IDC_BUTTON_SSP_SAVE, m_Button_SSP_Save);
	DDX_Control(pDX, IDC_BUTTON_ROLL_TICK, m_Button_R_Tick);
	DDX_Control(pDX, IDC_BUTTON_PITCH_TICK, m_Button_P_Tick);
	DDX_Control(pDX, IDC_BUTTON_OL_R_SSP, m_ButtonOL_R_SSP);
	DDX_Control(pDX, IDC_BUTTON_OL_L_SSP, m_ButtonOL_L_SSP);
	DDX_Control(pDX, IDC_BUTTON_FT_NULL, m_Button_FT_Null);
	DDX_Control(pDX, IDC_BUTTON_SSP_CTRL_OFF, m_SSP_CTRL_Off);
	DDX_Control(pDX, IDC_BUTTON_SSP_CTRL_ON, m_SSP_CTRL_On);
	DDX_Control(pDX, IDC_BUTTON_SSP_OFF, m_SSP_Off);
	DDX_Control(pDX, IDC_BUTTON_SSP_ON, m_SSP_On);
	DDX_Control(pDX, IDC_BUTTON_DSP_POSE, m_DSP_Pose_Set);
	DDX_Control(pDX, IDC_BUTTON_DSP_POSE_EXIT, m_DSP_Pose_Reset);
	DDX_Control(pDX, IDC_BUTTON_DSP_OFF, m_DSP_Off);
	DDX_Control(pDX, IDC_BUTTON_DSP_ON, m_DSP_On);
	DDX_Control(pDX, IDC_BUTTON_GRAPH, m_ButtonGraph);
	DDX_Control(pDX, IDC_STATIC_X_POS_BOARD, m_Board_FootX);
	DDX_Control(pDX, IDC_STATIC_Y_POS_BOARD, m_Board_FootY);
	DDX_Control(pDX, IDC_STATIC_Z_POS_BOARD, m_Board_FootZ);
	DDX_Text(pDX, IDC_EDIT_FLOAT_SIDE, m_SideAmplitude);
	DDX_Text(pDX, IDC_EDIT_FLOAT_SWAY, m_SwayAmplitude);
	DDX_Text(pDX, IDC_EDIT_INT_DURING, m_DSP_During);
	DDX_Text(pDX, IDC_EDIT_OVERAL_LP, m_EDIT_OveralGLP);
	DDX_Text(pDX, IDC_EDIT_OVERAL_LR, m_EDIT_OveralGLR);
	DDX_Text(pDX, IDC_EDIT_OVERAL_RP, m_EDIT_OveralGRP);
	DDX_Text(pDX, IDC_EDIT_OVERAL_RR, m_EDIT_OveralGRR);
	DDX_Text(pDX, IDC_EDIT_VIB_GAIN, m_Vib_Gain);
	DDX_Text(pDX, IDC_EDIT_VIB_GAIN_Y, m_Vib_GainY);
	DDX_Text(pDX, IDC_EDIT_IN_AMP_X, m_inAMPX);
	DDX_Text(pDX, IDC_EDIT_IN_AMP_Y, m_inAMPY);
	DDX_Text(pDX, IDC_EDIT_IN_FREQ, m_inFREQ);
	DDX_Text(pDX, IDC_EDIT_IN_NUM_SHAKE, m_NumShake);
	DDX_Text(pDX, IDC_EDIT_ZMP, m_ZMP_OveralY);
	DDX_Text(pDX, IDC_EDIT_ZMP2, m_ZMP_OveralX);
	DDX_Text(pDX, IDC_EDIT_PUSH_AMP, m_Push_Amp);
	DDX_Text(pDX, IDC_EDIT_PUSH_HZ, m_Push_Hz);
	DDX_Text(pDX, IDC_EDIT_TORSO_INCL_CTRL_P_LEFT, m_Torso_CTRL_Left_P);
	DDX_Text(pDX, IDC_EDIT_TORSO_INCL_CTRL_R_LEFT, m_Torso_CTRL_Left_R);
	DDX_Text(pDX, IDC_EDIT_TORSO_INCL_CTRL_P_RIGHT, m_Torso_CTRL_Right_P);
	DDX_Text(pDX, IDC_EDIT_TORSO_INCL_CTRL_R_RIGHT, m_Torso_CTRL_Right_R);
	DDX_Text(pDX, IDC_EDIT_ANKLE_AMP, m_AnkleAmp);
	DDV_MinMaxFloat(pDX, m_AnkleAmp, 0.f, 10.f);
	DDX_Text(pDX, IDC_EDIT_ANKLE_FQ, m_AnkleFq);
	DDX_Text(pDX, IDC_EDIT_WRIST_AMP, m_WristAmp);
	DDX_Text(pDX, IDC_EDIT_WRIST_HZ, m_WristHz);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_HZ, m_ShoulderHz);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_PITCH_AMP, m_ShoulderPitchAmp);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_ROLL_AMP, m_ShoulderRollAmp);
	DDX_Text(pDX, IDC_EDIT_ZMP3, m_I_Gain);
	DDX_Text(pDX, IDC_EDIT_HAND_AMP, m_HandAmp);
	DDX_Text(pDX, IDC_EDIT_HAND_HZ, m_HandFreq);
	DDX_Text(pDX, IDC_EDIT_WRIST_MODE, m_WristMotionMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWalk00TestDlg, CDialog)
	//{{AFX_MSG_MAP(CWalk00TestDlg)
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, OnButtonGraph)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_READY, OnButtonReady)
	ON_BN_CLICKED(IDC_BUTTON_HOME, OnButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_WALK01, OnButtonWalk01)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DSP_POSE, OnButtonDspPose)
	ON_BN_CLICKED(IDC_BUTTON_DSP_ON, OnButtonDspOn)
	ON_BN_CLICKED(IDC_BUTTON_DSP_OFF, OnButtonDspOff)
	ON_BN_CLICKED(IDC_BUTTON_DSP_POSE_EXIT, OnButtonDspPoseExit)
	ON_BN_CLICKED(IDC_BUTTON_SSP_ON, OnButtonSspOn)
	ON_BN_CLICKED(IDC_BUTTON_SSP_OFF, OnButtonSspOff)
	ON_BN_CLICKED(IDC_BUTTON_SSP_CTRL_ON, OnButtonSspCtrlOn)
	ON_BN_CLICKED(IDC_BUTTON_SSP_CTRL_OFF, OnButtonSspCtrlOff)
	ON_BN_CLICKED(IDC_BUTTON_FT_NULL, OnButtonFtNull)
	ON_BN_CLICKED(IDC_BUTTON_OL_L_SSP, OnButtonOlLSsp)
	ON_BN_CLICKED(IDC_BUTTON_OL_R_SSP, OnButtonOlRSsp)
	ON_BN_CLICKED(IDC_BUTTON_ROLL_TICK, OnButtonRollTick)
	ON_BN_CLICKED(IDC_BUTTON_PITCH_TICK, OnButtonPitchTick)
	ON_BN_CLICKED(IDC_BUTTON_SSP_SAVE, OnButtonSspSave)
	ON_BN_CLICKED(IDC_BUTTON_OVERALL_G_SET, OnButtonOverallGSet)
	ON_BN_CLICKED(IDC_BUTTON_CTRL_ON, OnButtonCtrlOn)
	ON_BN_CLICKED(IDC_BUTTON_CTRL_OFF, OnButtonCtrlOff)
	ON_BN_CLICKED(IDC_BUTTON_X_ADD, OnButtonXAdd)
	ON_BN_CLICKED(IDC_BUTTON_X_SUB, OnButtonXSub)
	ON_BN_CLICKED(IDC_BUTTON_Y_ADD, OnButtonYAdd)
	ON_BN_CLICKED(IDC_BUTTON_Y_SUB, OnButtonYSub)
	ON_BN_CLICKED(IDC_BUTTON_ZMP_TEST_ON, OnButtonZmpTestOn)
	ON_BN_CLICKED(IDC_BUTTON_ZMP_TEST_OFF, OnButtonZmpTestOff)
	ON_BN_CLICKED(IDC_BUTTON_ZMP_ON, OnButtonZmpOn)
	ON_BN_CLICKED(IDC_BUTTON_ZMP_OFF, OnButtonZmpOff)
	ON_BN_CLICKED(IDC_BUTTON_SSP_PUSH_GO, OnButtonSspPushGo)
	ON_BN_CLICKED(IDC_BUTTON_SSP_PUSH_STOP, OnButtonSspPushStop)
	ON_BN_CLICKED(IDC_BUTTON_TORSO_CTRL_ON, OnButtonTorsoCtrlOn)
	ON_BN_CLICKED(IDC_BUTTON_TORSO_CTRL_OFF, OnButtonTorsoCtrlOff)
	ON_BN_CLICKED(IDC_BUTTON_TIME_RESET, OnButtonTimeReset)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_START, OnButtonFreqStart)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_STOP, OnButtonFreqStop)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_START2, OnButtonFreqStart2)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_STOP2, OnButtonFreqStop2)
	ON_BN_CLICKED(IDC_BUTTON_WRIST_MOTION_GO, OnButtonWristMotionGo)
	ON_BN_CLICKED(IDC_BUTTON_WRIST_MOTION_STOP, OnButtonWristMotionStop)
	ON_BN_CLICKED(IDC_BUTTON_SHOULDER_MOTION_GO, OnButtonShoulderMotionGo)
	ON_BN_CLICKED(IDC_BUTTON_SHOULDER_MOTION_STOP, OnButtonShoulderMotionStop)
	ON_BN_CLICKED(IDC_BUTTON_HAND_MOTION_GO, OnButtonHandMotionGo)
	ON_BN_CLICKED(IDC_BUTTON_HAND_MOTION_STOP, OnButtonHandMotionStop)
	ON_BN_CLICKED(IDC_BUTTON_CONTROLL_OFF, OnButtonControllOff)
	ON_BN_CLICKED(IDC_BUTTON_CONTROLL_ON, OnButtonControllOn)
	ON_BN_CLICKED(IDC_BUTTON_GRIP_ON, OnButtonGripOn)
	ON_BN_CLICKED(IDC_BUTTON_GRIP_OFF, OnButtonGripOff)
	ON_BN_CLICKED(IDC_BUTTON_GRIP_STOP, OnButtonGripStop)
	ON_BN_CLICKED(IDC_BUTTON_HANDUP, OnButtonHandup)
	ON_BN_CLICKED(IDC_BUTTON_HANDDOWN, OnButtonHanddown)
	ON_BN_CLICKED(IDC_BUTTON_GRIP_ON2, OnButtonGripOn2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWalk00TestDlg message handlers

void CWalk00TestDlg::Init()
{
	unsigned char i;
	theApp.m_pSharedMemory->INT_Flag = FALSE;

	theApp.m_pSharedMemory->TestModeFlag = TRUE;

	theApp.m_pSharedMemory->Arm_Motion = TRUE;//FALSE;
	theApp.m_pSharedMemory->MotionFlagALL = 0;
	theApp.m_pSharedMemory->ZMP_DSP_CTRL_Flag = FALSE;

	theApp.m_pSharedMemory->ZMPSysIDFlag = FALSE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;

	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 0;

	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;

	m_DSP_Pose_Set.EnableWindow(TRUE);
	m_DSP_Pose_Reset.EnableWindow(FALSE);
	m_DSP_On.EnableWindow(FALSE);
	m_DSP_Off.EnableWindow(FALSE);

	m_SSP_On.EnableWindow(TRUE);
	m_SSP_Off.EnableWindow(FALSE);
	m_SSP_CTRL_On.EnableWindow(FALSE);
	m_SSP_CTRL_Off.EnableWindow(FALSE);

	m_ButtonOL_L_SSP.EnableWindow(TRUE);
	m_ButtonOL_R_SSP.EnableWindow(TRUE);

	m_DSP_During	= 160;
	m_SideAmplitude = 70;
	m_SwayAmplitude = 180;

	theApp.m_pSharedMemory->DSP_During = m_DSP_During;
	theApp.m_pSharedMemory->DSP_SideAmplitude = (float)(-1. * m_SideAmplitude);
	theApp.m_pSharedMemory->DSP_SwayAmplitude = (float)m_SwayAmplitude;

	m_Board_RFootX=0.;
	m_Board_LFootX=0.;

	m_HandFreq = (float)0.;
	m_HandAmp = (float)0.;
		
	m_Board_RFootY=-L0;
	m_Board_LFootY= L0;
	
	m_Board_RFootZ=-(L1+L2);
	m_Board_LFootZ=-(L1+L2);

	theApp.m_pSharedMemory->SSPCTRLOn = FALSE;
	theApp.m_pSharedMemory->SSPCTRLOff = FALSE;

	m_EDIT_OveralGLP = 0;//1.;
	m_EDIT_OveralGLR = 0;//1.;
	m_EDIT_OveralGRP = 0;//1.;
	m_EDIT_OveralGRR = 0;//1.;

	InitBoard();
	SetTimer(1, DISP_TIMER, NULL);
	////// Joint Lock Enable
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		
		theApp.SendRunCMD(i);
		Sleep(50);
		
	}
	
	UpdateData(FALSE);

	theApp.m_pSharedMemory->INT_Flag = TRUE;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
}

void CWalk00TestDlg::OnButtonGraph() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;

	m_ButtonGraph.GetWindowText(strText);
	
	if(strText == "Graph Start")
	{
		m_Board_FootX.StartGraph(DISP_TIMER);
		m_Board_FootY.StartGraph(DISP_TIMER);
		m_Board_FootZ.StartGraph(DISP_TIMER);
		
		SetTimer(1, DISP_TIMER, NULL);
		ButtonControl(WALK_GRAPH_START);
	}
	else if(strText == "Graph Hold")
	{
		m_Board_FootX.KillTimer(1);
		m_Board_FootY.KillTimer(1);
		m_Board_FootZ.KillTimer(1);
		
		KillTimer(1);		
		ButtonControl(WALK_GRAPH_HOLD);
	}
}

void CWalk00TestDlg::ButtonControl(int Msg)
{
	switch(Msg)
	{
	/////////////////////////////////////////////////////////////////////
	// Graph Button
	case WALK_GRAPH_START:
		m_ButtonGraph.SetWindowText("Graph Hold");
		break;
	case WALK_GRAPH_HOLD:
		m_ButtonGraph.SetWindowText("Graph Start");
		break;
	}
}

void CWalk00TestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
	if(nIDEvent==1)
	{
		DispXYZ();
	}
}

void CWalk00TestDlg::DispXYZ()
{
	/*
	m_Board_RFootX=0;
	m_Board_LFootX=0;
	
	m_Board_RFootY=-L0;
	m_Board_LFootY=+L0;
	
	m_Board_RFootZ=-(L1+L2);
	m_Board_LFootZ=-(L1+L2);
	*/
	m_Board_RFootX=theApp.m_pSharedMemory->fProfXYZ[3];
	m_Board_LFootX=theApp.m_pSharedMemory->fProfXYZ[0];
	
	m_Board_RFootY=theApp.m_pSharedMemory->fProfXYZ[4];
	m_Board_LFootY=theApp.m_pSharedMemory->fProfXYZ[1];
	
	m_Board_RFootZ=theApp.m_pSharedMemory->fProfXYZ[5];
	m_Board_LFootZ=theApp.m_pSharedMemory->fProfXYZ[2];
}

void CWalk00TestDlg::InitBoard()
{
	m_Board_FootX.SetBoardDC(m_Board_FootX.GetDC());
	m_Board_FootX.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_FootX.SetXRange(10, 0);
	m_Board_FootX.SetYRange(100, -100);
	m_Board_FootX.SetXYGap(1, 50);
	m_Board_FootX.SetGraphName(2,"R-X","L-X");
	
	m_Board_FootY.SetBoardDC(m_Board_FootY.GetDC());
	m_Board_FootY.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_FootY.SetXRange(10, 0);
	m_Board_FootY.SetYRange(180, -180);
	m_Board_FootY.SetXYGap(1, 100);
	m_Board_FootY.SetGraphName(2,"R-Y","L-Y");
	
	m_Board_FootZ.SetBoardDC(m_Board_FootZ.GetDC());
	m_Board_FootZ.InitBoard(CENTERPOINT_LEFTTOP);
	m_Board_FootZ.SetXRange(10, 0);
	m_Board_FootZ.SetYRange(-400, -600);
	m_Board_FootZ.SetXYGap(1, 100);
	m_Board_FootZ.SetGraphName(2,"R-Z","L-Z");
}

void CWalk00TestDlg::UpdateBoardPoint()
{
	UpdateData();

	m_Board_FootX.SetCoordinatePoint(0, (int)m_Board_RFootX);
	m_Board_FootX.SetCoordinatePoint(1, (int)m_Board_LFootX);

	m_Board_FootY.SetCoordinatePoint(0, (int)m_Board_RFootY);
	m_Board_FootY.SetCoordinatePoint(1, (int)m_Board_LFootY);
	
	m_Board_FootZ.SetCoordinatePoint(0, (int)m_Board_RFootZ);
	m_Board_FootZ.SetCoordinatePoint(1, (int)m_Board_LFootZ);
}

void CWalk00TestDlg::OnButtonReady() 
{	
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[0]=0;
	
	theApp.m_pSharedMemory->Walk_Ready_Flag = TRUE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;

	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;

	/*
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	

	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;

	theApp.m_pSharedMemory->SSPCTRLOn = FALSE;
	theApp.m_pSharedMemory->SSPCTRLOff = FALSE;
	*/
	m_ButtonOL_R_SSP.EnableWindow(TRUE);
	m_ButtonOL_L_SSP.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonHome() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[1]=-1;

	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = TRUE;

	/*
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;
	*/
	m_ButtonOL_R_SSP.EnableWindow(TRUE);
	m_ButtonOL_L_SSP.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonWalk01()
{
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[2]=0;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = TRUE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	/*
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;
	*/
}

void CWalk00TestDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;

	theApp.m_pSharedMemory->SSPCTRLOn = FALSE;
	theApp.m_pSharedMemory->SSPCTRLOff = FALSE;
	
	KillTimer(1);
	OnOK();
	DestroyWindow();

	m_pKhr3winDlg->m_ButtonWalk.SetWindowText("Walk01");
}

void CWalk00TestDlg::OnButtonDspPose() 
{
	// TODO: Add your control notification handler code here
	unsigned char i;

	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		theApp.SendRunCMD(i);
		Sleep(50);
		
	}
		
	UpdateData(TRUE);
	
	theApp.m_pSharedMemory->DSP_During = m_DSP_During;
	theApp.m_pSharedMemory->DSP_SideAmplitude = (float)(-1. * m_SideAmplitude);
	theApp.m_pSharedMemory->DSP_SwayAmplitude = (float)m_SwayAmplitude;

	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 1;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;
	
	theApp.m_pSharedMemory->PROFTime[3] = 0;

	m_DSP_Pose_Reset.EnableWindow(TRUE);
	m_DSP_Pose_Set.EnableWindow(FALSE);
	m_DSP_On.EnableWindow(TRUE);
	m_DSP_Off.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonDspOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 2;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = TRUE;

	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;
	
	m_DSP_Pose_Reset.EnableWindow(FALSE);
	m_DSP_Pose_Set.EnableWindow(FALSE);
	m_DSP_On.EnableWindow(FALSE);
	m_DSP_Off.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonDspOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 2;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = TRUE;

	m_DSP_Pose_Reset.EnableWindow(TRUE);
	m_DSP_Pose_Set.EnableWindow(FALSE);
	m_DSP_On.EnableWindow(TRUE);
	m_DSP_Off.EnableWindow(FALSE);
}

void CWalk00TestDlg::OnButtonDspPoseExit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	theApp.m_pSharedMemory->DSP_During = m_DSP_During;
	theApp.m_pSharedMemory->DSP_SideAmplitude = (float)(-1 * m_SideAmplitude);
	theApp.m_pSharedMemory->DSP_SwayAmplitude = (float)m_SwayAmplitude;

	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 3;
	
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = TRUE;
	
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = TRUE;

	theApp.m_pSharedMemory->PROFTime[3] = 0;

	m_DSP_Pose_Reset.EnableWindow(FALSE);
	m_DSP_Pose_Set.EnableWindow(TRUE);
	m_DSP_On.EnableWindow(FALSE);
	m_DSP_Off.EnableWindow(FALSE);
}

void CWalk00TestDlg::OnButtonSspOn() 
{
	// TODO: Add your control notification handler code here
	unsigned char i;
	
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	
	
	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 1;
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->PROFTime[4] = 0;

	m_SSP_On.EnableWindow(FALSE);
	m_SSP_Off.EnableWindow(TRUE);
	m_SSP_CTRL_On.EnableWindow(TRUE);
	m_SSP_CTRL_Off.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonSspOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 3;
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = TRUE;
	theApp.m_pSharedMemory->PROFTime[4] = 0;
	m_SSP_On.EnableWindow(TRUE);
	m_SSP_Off.EnableWindow(FALSE);
	m_SSP_CTRL_On.EnableWindow(FALSE);
	m_SSP_CTRL_Off.EnableWindow(FALSE);
}

void CWalk00TestDlg::OnButtonSspCtrlOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 2;
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = TRUE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;
	m_SSP_On.EnableWindow(FALSE);
	m_SSP_Off.EnableWindow(FALSE);
	m_SSP_CTRL_On.EnableWindow(FALSE);
	m_SSP_CTRL_Off.EnableWindow(TRUE);	
}

void CWalk00TestDlg::OnButtonSspCtrlOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 2;
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = TRUE;
	m_SSP_On.EnableWindow(FALSE);
	m_SSP_Off.EnableWindow(TRUE);
	m_SSP_CTRL_On.EnableWindow(TRUE);
	m_SSP_CTRL_Off.EnableWindow(FALSE);	
}

void CWalk00TestDlg::OnButtonFtNull() 
{
	// TODO: Add your control notification handler code here
	m_Button_FT_Null.EnableWindow(FALSE);
	m_pKhr3winDlg->m_FT_ReadDlg.FT_Null();
	m_Button_FT_Null.EnableWindow(TRUE);
}

void CWalk00TestDlg::OnButtonOlLSsp() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = TRUE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->PROFTime[12]=0;

	theApp.m_pSharedMemory->SSPCTRLOn = TRUE;
	theApp.m_pSharedMemory->SSPCTRLOff = TRUE;

	m_ButtonOL_L_SSP.EnableWindow(FALSE);
	m_ButtonOL_R_SSP.EnableWindow(FALSE);
}

void CWalk00TestDlg::OnButtonOlRSsp() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_OL_L_Pose_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_OL_R_Pose_Flag = TRUE;
	
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;

	theApp.m_pSharedMemory->PROFTime[12]=0;

	theApp.m_pSharedMemory->SSPCTRLOn = TRUE;
	theApp.m_pSharedMemory->SSPCTRLOff = TRUE;

	m_ButtonOL_L_SSP.EnableWindow(FALSE);
	m_ButtonOL_R_SSP.EnableWindow(FALSE);
}

void CWalk00TestDlg::OnButtonRollTick() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = TRUE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;

	theApp.m_pSharedMemory->PROFTime[13]=0;
	theApp.m_pSharedMemory->PROFTime[11]=0;
}

void CWalk00TestDlg::OnButtonPitchTick() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = TRUE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = FALSE;
	theApp.m_pSharedMemory->PROFTime[13]=0;
	theApp.m_pSharedMemory->PROFTime[11]=0;
}

void CWalk00TestDlg::OnButtonSspSave() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSP_Tick_Roll_Save_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Tick_Pitch_Save_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_OL_Save_Flag = TRUE;
	theApp.m_pSharedMemory->PROFTime[13]=0;
	theApp.m_pSharedMemory->PROFTime[11]=0;
}

void CWalk00TestDlg::OnButtonOverallGSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->SSPCTRLOn = FALSE;
	theApp.m_pSharedMemory->SSPCTRLOff = TRUE;
	
	//theApp.m_pSharedMemory->DampOveralRP = m_EDIT_OveralGRP;
	//theApp.m_pSharedMemory->DampOveralLP = m_EDIT_OveralGLP;

	//theApp.m_pSharedMemory->DampOveralRR = m_EDIT_OveralGRR;
	//theApp.m_pSharedMemory->DampOveralLR = m_EDIT_OveralGLR;
	theApp.m_pSharedMemory->VibGainR = m_Vib_Gain;
	theApp.m_pSharedMemory->VibGainY = m_Vib_GainY;
	UpdateData(FALSE);
}

void CWalk00TestDlg::OnButtonCtrlOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSPCTRLOn = TRUE;
	theApp.m_pSharedMemory->SSPCTRLOff = FALSE;
}

void CWalk00TestDlg::OnButtonCtrlOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSPCTRLOn = FALSE;
	theApp.m_pSharedMemory->SSPCTRLOff = TRUE;
}

void CWalk00TestDlg::OnButtonXAdd() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ZMPInitAdjust[0]	= theApp.m_pSharedMemory->ZMPInitAdjust[0] + (float)0.5;
}

void CWalk00TestDlg::OnButtonXSub() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ZMPInitAdjust[0]	= theApp.m_pSharedMemory->ZMPInitAdjust[0] - (float)0.5;
}

void CWalk00TestDlg::OnButtonYAdd() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ZMPInitAdjust[1]	= theApp.m_pSharedMemory->ZMPInitAdjust[1] + (float)0.5;
}

void CWalk00TestDlg::OnButtonYSub() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ZMPInitAdjust[1]	= theApp.m_pSharedMemory->ZMPInitAdjust[1] - (float)0.5;
}

void CWalk00TestDlg::OnButtonZmpTestOn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->ZMPSysID[0] = m_inAMPX;
	theApp.m_pSharedMemory->ZMPSysID[1] = m_inAMPY;
	theApp.m_pSharedMemory->ZMPSysID[2] = m_inFREQ;
	theApp.m_pSharedMemory->NumShake = m_NumShake;
	UpdateData(FALSE);
	
	//theApp.m_pSharedMemory->PROFTime[14] = 0;
	theApp.m_pSharedMemory->ZMPSysIDFlag = TRUE;
}

void CWalk00TestDlg::OnButtonZmpTestOff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->ZMPSysID[0] = m_inAMPX;
	theApp.m_pSharedMemory->ZMPSysID[1] = m_inAMPY;
	theApp.m_pSharedMemory->ZMPSysID[2] = m_inFREQ;
	theApp.m_pSharedMemory->NumShake = m_NumShake;
	UpdateData(FALSE);
	
	//theApp.m_pSharedMemory->PROFTime[14] = 0;
	theApp.m_pSharedMemory->ZMPSysIDFlag = FALSE;
}

void CWalk00TestDlg::OnButtonZmpOn()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	theApp.m_pSharedMemory->ZMP_DSP_X_Gain = m_ZMP_OveralX;
	theApp.m_pSharedMemory->ZMP_DSP_Y_Gain = m_ZMP_OveralY;
	theApp.m_pSharedMemory->ZMP_DSP_Y_IntegralGain = m_I_Gain;
	theApp.m_pSharedMemory->ZMP_DSP_CTRL_Flag = 1;
}

void CWalk00TestDlg::OnButtonZmpOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ZMP_DSP_CTRL_Flag = 2;
}

void CWalk00TestDlg::OnButtonSspPushGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->PushUpAMP = m_Push_Amp;
	theApp.m_pSharedMemory->PushUpHz = m_Push_Hz;
	theApp.m_pSharedMemory->PushUpFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[18] = 0;
	UpdateData(FALSE);
}

void CWalk00TestDlg::OnButtonSspPushStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	theApp.m_pSharedMemory->PushUpFlag = FALSE;

	UpdateData(FALSE);
}

void CWalk00TestDlg::OnButtonTorsoCtrlOn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->TorsoCTRLGainP[0] = m_Torso_CTRL_Left_P;
	theApp.m_pSharedMemory->TorsoCTRLGainR[0] = m_Torso_CTRL_Left_R;

	theApp.m_pSharedMemory->TorsoCTRLGainP[1] = m_Torso_CTRL_Right_P;
	theApp.m_pSharedMemory->TorsoCTRLGainR[1] = m_Torso_CTRL_Right_R;
	UpdateData(FALSE);

	theApp.m_pSharedMemory->TorsoCTRLOnOff = TRUE;
}

void CWalk00TestDlg::OnButtonTorsoCtrlOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->TorsoCTRLGainP[0] = 0.;
	theApp.m_pSharedMemory->TorsoCTRLGainR[0] = 0.;
	
	theApp.m_pSharedMemory->TorsoCTRLGainP[1] = 0.;
	theApp.m_pSharedMemory->TorsoCTRLGainR[1] = 0.;

	theApp.m_pSharedMemory->TorsoCTRLOnOff = FALSE;
}



void CWalk00TestDlg::OnButtonTimeReset() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->DataSaveFlag=TRUE;
	theApp.m_pSharedMemory->PROFTime[11]=0;
}

void CWalk00TestDlg::OnButtonFreqStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	theApp.m_pSharedMemory->AnkleAmplitude = m_AnkleAmp;
	theApp.m_pSharedMemory->AnkleFreq = m_AnkleFq;

	theApp.m_pSharedMemory->RollAnkleTestFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->PROFTime[13] = 0;
	
}

void CWalk00TestDlg::OnButtonFreqStop() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->RollAnkleTestStopFlag = TRUE;
}

void CWalk00TestDlg::OnButtonFreqStart2() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	theApp.m_pSharedMemory->AnkleAmplitude = m_AnkleAmp;
	theApp.m_pSharedMemory->AnkleFreq = m_AnkleFq;
	
	theApp.m_pSharedMemory->PitchAnkleTestFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->PROFTime[13] = 0;
}

void CWalk00TestDlg::OnButtonFreqStop2() 
{
	// TODO: Add your control notification handler code here

	theApp.m_pSharedMemory->PitchAnkleTestStopFlag = TRUE;
}



void CWalk00TestDlg::OnButtonWristMotionGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->WristAmp = m_WristAmp;
	theApp.m_pSharedMemory->WristHz = m_WristHz;
	theApp.m_pSharedMemory->WristMotionMode = m_WristMotionMode;

	theApp.m_pSharedMemory->WristMotionFlag = 1;
}

void CWalk00TestDlg::OnButtonWristMotionStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->WristMotionFlag = 3;
}

void CWalk00TestDlg::OnButtonShoulderMotionGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->ShoulderPitchAmp = m_ShoulderPitchAmp;
	theApp.m_pSharedMemory->ShoulderRollAmp = m_ShoulderRollAmp;
	theApp.m_pSharedMemory->ShoulderPitchHz = m_ShoulderHz;
	theApp.m_pSharedMemory->ShoulderRollHz = m_ShoulderHz;
	
	theApp.m_pSharedMemory->ShoulderMotionFlag = 1;
}

void CWalk00TestDlg::OnButtonShoulderMotionStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ShoulderMotionFlag = 3;
}

void CWalk00TestDlg::OnButtonHandMotionGo() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	theApp.m_pSharedMemory->HandAmp = m_HandAmp;
	theApp.m_pSharedMemory->HandFreq = m_HandFreq;

	theApp.m_pSharedMemory->HandMotionFlag = 1;
}

void CWalk00TestDlg::OnButtonHandMotionStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HandMotionFlag = 2;
}

void CWalk00TestDlg::OnButtonControllOff() 
{
	// TODO: Add your control notification handler code here
	
	theApp.Stop_CMD(EJMC4);
	Sleep(50);
	theApp.Stop_CMD(EJMC5);
	Sleep(50);
	
}

void CWalk00TestDlg::OnButtonControllOn() 
{
	// TODO: Add your control notification handler code here
	theApp.SendRunCMD(EJMC4);
	Sleep(50);
	theApp.SendRunCMD(EJMC5);
	Sleep(50);
}

void CWalk00TestDlg::OnButtonGripOn() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];

	TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	TxData[3]=0x00 | (5 & 0x0F);
	TxData[4]=0x00 | (5 & 0x0F);
	TxData[5]=0x00 | (5 & 0x0F);
	TxData[6]=0x00 | (5 & 0x0F);
	TxData[7]=0x00 | (5 & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
	//HUBO2Win->CANWrite(CMD_TXDF,TxData,8);
}

void CWalk00TestDlg::OnButtonGripOff() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	TxData[3]=0x10 | (3 & 0x0F);
	TxData[4]=0x10 | (3 & 0x0F);
	TxData[5]=0x10 | (3 & 0x0F);
	TxData[6]=0x10 | (3 & 0x0F);
	TxData[7]=0x10 | (3 & 0x0F);

	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CWalk00TestDlg::OnButtonGripStop() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	TxData[3]=0x10 | (0 & 0x0F);
	TxData[4]=0x10 | (0 & 0x0F);
	TxData[5]=0x10 | (0 & 0x0F);
	TxData[6]=0x10 | (0 & 0x0F);
	TxData[7]=0x10 | (0 & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CWalk00TestDlg::OnButtonHandup() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->WristConfigureFlag = 1;
}

void CWalk00TestDlg::OnButtonHanddown() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->WristConfigureFlag = 3;
}

void CWalk00TestDlg::OnButtonGripOn2() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	TxData[3]=0x00 | (3 & 0x0F);
	TxData[4]=0x00 | (3 & 0x0F);
	TxData[5]=0x00 | (3 & 0x0F);
	TxData[6]=0x00 | (3 & 0x0F);
	TxData[7]=0x00 | (3 & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);	
}
