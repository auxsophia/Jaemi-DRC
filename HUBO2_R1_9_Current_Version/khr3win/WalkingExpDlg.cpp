// WalkingExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Khr3winDlg.h"
#include "WalkingExpDlg.h"
#include "math.h"

#define		swayCOMPEN00		0
#define		swayCOMPEN01		0
#define		swayCOMPEN02		0


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWalkingExpDlg dialog
extern CKhr3winApp theApp;

CWalkingExpDlg::CWalkingExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWalkingExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWalkingExpDlg)
	m_WalkingPeriod = 950;
	m_Check_KeepGoing = FALSE;
	m_EditSway = 76.f;
	m_EditAnkle = 2.2f;
	m_FwdBwd = 0.0f;
	m_LftRht = 0.0f;
	m_Turn = 0.0f;
	m_UpRatio = 0.47f;
	m_ZMP_AMP = 75.0f;
	m_X_Shape_Factor = 1.85f;
	m_Y_Shape_Factor = 0.87f;
	m_Sway_Factor = 0.87f;
	m_SwayDelayOpen = 2.5f;
	m_SwayDelayRecover = 2.0f;
	m_YOffset = 0.0f;
	m_XOffset = 0.0f;
	m_Check_Arm = FALSE;
	m_Sway_OnOff = TRUE;
	m_StepLength = 0.0f;
	m_HipMoveRatio = 0.0f;
	m_HipPitchAngle = 0.0f;
	m_HipRollCompen = 0.0f;
	m_HipRollCompenL = 0.0f;
	m_LFootDelta_Y = 0.0f;
	m_RFootDelta_Y = 0.0f;
	m_FootPlacementGain = 0.0f;
	m_RollRefGain = 0.0f;
	m_FootYGain = 0.0f;
	m_FootZGain = 0.0f;
	m_StartInitVelocityCoff = 0.0f;
	m_ZmpAddCoff = 0.0f;
	m_PitchRefGain = 0.0f;
	m_LFootDelta_X = 0.0f;
	m_RFootDelta_X = 0.0f;
	m_LandingPitchGain = 0.0f;
	m_LandingRollGain = 0.0f;
	m_AccPitchOffset = 0.0f;
	m_AccRollOffset = 0.0f;
	m_XshapeFactorGain = 0.0f;
	m_ToeOffGain = 0.0f;
	m_AnkleRollGain = 0.0f;
	m_YShapeFactorRecover = 0.0f;
	m_YShapeFactorOpen = 0.0f;
	//}}AFX_DATA_INIT
}


void CWalkingExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWalkingExpDlg)
	DDX_Control(pDX, IDC_BUTTON_FT_NULL, m_Button_FT_Null);
	DDX_Control(pDX, IDC_BUTTON_SET, m_ButtonSet);
	DDX_Control(pDX, IDC_BUTTON_GRAPH, m_ProfileGraph);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_WalkingPeriod);
	DDX_Check(pDX, IDC_CHECK_KEEPGOING, m_Check_KeepGoing);
	DDX_Text(pDX, IDC_EDIT_SWAY, m_EditSway);
	DDX_Text(pDX, IDC_EDIT_ANKLE_ANGLE, m_EditAnkle);
	DDX_Text(pDX, IDC_EDIT_FWDBWD, m_FwdBwd);
	DDV_MinMaxFloat(pDX, m_FwdBwd, 0.f, 400.f);
	DDX_Text(pDX, IDC_EDIT_LFTRHT, m_LftRht);
	DDV_MinMaxFloat(pDX, m_LftRht, 0.f, 300.f);
	DDX_Text(pDX, IDC_EDIT_TURN, m_Turn);
	DDV_MinMaxFloat(pDX, m_Turn, 0.f, 60.f);
	DDX_Text(pDX, IDC_EDIT_UPRATIO, m_UpRatio);
	DDV_MinMaxFloat(pDX, m_UpRatio, 0.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_ZMP_AMP, m_ZMP_AMP);
	DDX_Text(pDX, IDC_EDIT_X_SHAPE_FACTOR, m_X_Shape_Factor);
	DDX_Text(pDX, IDC_EDIT_Y_SHAPE_FACTOR, m_Y_Shape_Factor);
	DDX_Text(pDX, IDC_EDIT_SWAY_FACTOR, m_Sway_Factor);
	DDX_Text(pDX, IDC_EDIT_SWAY_DELAY_OPEN, m_SwayDelayOpen);
	DDX_Text(pDX, IDC_EDIT_SWAY_DELAY_RECOVER, m_SwayDelayRecover);
	DDX_Text(pDX, IDC_EDIT_SIDE_OFFSET, m_YOffset);
	DDX_Text(pDX, IDC_EDIT_FORWARD_OFFSET, m_XOffset);
	DDX_Check(pDX, IDC_CHECK_ARM, m_Check_Arm);
	DDX_Check(pDX, IDC_CHECK_SWAY_ONOFF, m_Sway_OnOff);
	DDX_Text(pDX, IDC_EDIT_STEP_LENGTH, m_StepLength);
	DDV_MinMaxFloat(pDX, m_StepLength, -150.f, 500.f);
	DDX_Text(pDX, IDC_EDIT_HIP_MOVE_RATIO, m_HipMoveRatio);
	DDV_MinMaxFloat(pDX, m_HipMoveRatio, 0.f, 0.1f);
	DDX_Text(pDX, IDC_EDIT_HIP_PITCH_ANGLE, m_HipPitchAngle);
	DDV_MinMaxFloat(pDX, m_HipPitchAngle, -10.f, 10.f);
	DDX_Text(pDX, IDC_EDIT_HIP_ROLL_COMPEN, m_HipRollCompen);
	DDV_MinMaxFloat(pDX, m_HipRollCompen, -3.f, 3.f);
	DDX_Text(pDX, IDC_EDIT_HIP_ROLL_COMPEN2, m_HipRollCompenL);
	DDV_MinMaxFloat(pDX, m_HipRollCompenL, -3.f, 3.f);
	DDX_Text(pDX, IDC_EDIT_LFOOT_DELTA_Y, m_LFootDelta_Y);
	DDX_Text(pDX, IDC_EDIT_RFOOT_DELTA_Y, m_RFootDelta_Y);
	DDX_Text(pDX, IDC_EDIT_FOOT_PLACEMENT_GAIN, m_FootPlacementGain);
	DDX_Text(pDX, IDC_EDIT_ROLL_REF_GAIN, m_RollRefGain);
	DDV_MinMaxFloat(pDX, m_RollRefGain, -3.f, 3.f);
	DDX_Text(pDX, IDC_EDIT_FOOT_Y_GAIN, m_FootYGain);
	DDX_Text(pDX, IDC_EDIT_FOOT_Z_GAIN, m_FootZGain);
	DDX_Text(pDX, IDC_EDIT_START_INIT_VELOCITY, m_StartInitVelocityCoff);
	DDX_Text(pDX, IDC_EDIT_ZMP_ADD_COFF, m_ZmpAddCoff);
	DDX_Text(pDX, IDC_EDIT_PITCH_REF_GAIN, m_PitchRefGain);
	DDX_Text(pDX, IDC_EDIT_LFOOT_DELTA_X, m_LFootDelta_X);
	DDX_Text(pDX, IDC_EDIT_RFOOT_DELTA_X, m_RFootDelta_X);
	DDX_Text(pDX, IDC_EDIT_LANDING_PITCH_GAIN, m_LandingPitchGain);
	DDX_Text(pDX, IDC_EDIT_LANDING_ROLL_GAIN, m_LandingRollGain);
	DDX_Text(pDX, IDC_EDIT_ACC_PITCH_OFFSET, m_AccPitchOffset);
	DDX_Text(pDX, IDC_EDIT_ACC_ROL_OFFSET, m_AccRollOffset);
	DDX_Text(pDX, IDC_EDIT_X_SHAPE_GAIN, m_XshapeFactorGain);
	DDX_Text(pDX, IDC_EDIT_TOEOFF_GAIN, m_ToeOffGain);
	DDX_Text(pDX, IDC_EDIT_ANKLE_ROLL_GAIN, m_AnkleRollGain);
	DDX_Text(pDX, IDC_EDIT_Y_SHAPE_RECOVER, m_YShapeFactorRecover);
	DDX_Text(pDX, IDC_EDIT_Y_SHAPE_OPEN, m_YShapeFactorOpen);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWalkingExpDlg, CDialog)
	//{{AFX_MSG_MAP(CWalkingExpDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_FAST, OnButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, OnButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, OnButtonGraph)
	ON_BN_CLICKED(IDC_BUTTON_WALK_READY, OnButtonWalkReady)
	ON_BN_CLICKED(IDC_BUTTON_HOME, OnButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_GO, OnButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_FT_NULL, OnButtonFtNull)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, OnButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, OnButtonBackward)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_CW, OnButtonCw)
	ON_BN_CLICKED(IDC_BUTTON_CCW, OnButtonCcw)
	ON_BN_CLICKED(IDC_BUTTON_0p8_10cm, OnBUTTON0p810cm)
	ON_BN_CLICKED(IDC_BUTTON_0p8_20cm, OnBUTTON0p820cm)
	ON_BN_CLICKED(IDC_BUTTON_0p95_10cm, OnBUTTON0p9510cm)
	ON_BN_CLICKED(IDC_BUTTON_0p95_30cm, OnBUTTON0p9530cm)
	ON_BN_CLICKED(IDC_BUTTON_0p8_25cm, OnBUTTON0p825cm)
	ON_BN_CLICKED(IDC_BUTTON_0p7_10cm, OnBUTTON0p710cm)
	ON_BN_CLICKED(IDC_BUTTON_0p7_20cm, OnBUTTON0p720cm)
	ON_BN_CLICKED(IDC_BUTTON_0p7_25cm, OnBUTTON0p725cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p7_5cm, OnBUTTONSide0p75cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p8_5cm, OnBUTTONSide0p85cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p95_5cm, OnBUTTONSide0p955cm)
	ON_BN_CLICKED(IDC_BUTTON_0p95_20cm, OnBUTTON0p9520cm)
	ON_BN_CLICKED(IDC_BUTTON_0p95_0cm, OnBUTTON0p950cm)
	ON_BN_CLICKED(IDC_BUTTON_0p8_0cm, OnBUTTON0p80cm)
	ON_BN_CLICKED(IDC_BUTTON_0p7_0cm, OnBUTTON0p70cm)
	ON_BN_CLICKED(IDC_BUTTON_SWAY_ADJ_ON, OnButtonSwayAdjOn)
	ON_BN_CLICKED(IDC_BUTTON_Side0p95_7cm, OnBUTTONSide0p957cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p95_10cm, OnBUTTONSide0p9510cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p8_7cm, OnBUTTONSide0p87cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p8_10cm, OnBUTTONSide0p810cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p7_7cm, OnBUTTONSide0p77cm)
	ON_BN_CLICKED(IDC_BUTTON_Side0p7_10cm, OnBUTTONSide0p710cm)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p7_10, OnBUTTONTURN0p710)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p8_10, OnBUTTONTURN0p810)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p95_10, OnBUTTONTURN0p9510)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p7_30, OnBUTTONTURN0p730)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p8_30, OnBUTTONTURN0p830)
	ON_BN_CLICKED(IDC_BUTTON_TURN_0p95_30, OnBUTTONTURN0p9530)
	ON_BN_CLICKED(IDC_BUTTON_X_PLUS, OnButtonXPlus)
	ON_BN_CLICKED(IDC_BUTTON_X_MINUS, OnButtonXMinus)
	ON_BN_CLICKED(IDC_BUTTON_Y_PLUS, OnButtonYPlus)
	ON_BN_CLICKED(IDC_BUTTON_Y_MINUS, OnButtonYMinus)
	ON_BN_CLICKED(IDC_BUTTON_ARM_ONOFF, OnButtonArmOnoff)
	ON_BN_CLICKED(IDC_BUTTON_MOTION1, OnButtonMotion1)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_STOP, OnButtonMotionStop)
	ON_BN_CLICKED(IDC_BUTTON_MOTION2, OnButtonMotion2)
	ON_BN_CLICKED(IDC_BUTTON_MOTION3, OnButtonMotion3)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_HIP_PITCH_INC1, OnButtonHipPitchInc1)
	ON_BN_CLICKED(IDC_BUTTON_HIP_PITCH_DEC, OnButtonHipPitchDec)
	ON_BN_CLICKED(IDC_BUTTON_HIP_PITCH_INC2, OnButtonHipPitchInc2)
	ON_BN_CLICKED(IDC_BUTTON_HIP_PITCH_DEC2, OnButtonHipPitchDec2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TIMER_RESET, OnButtonSaveTimerReset)
	ON_BN_CLICKED(IDC_BUTTON_STRIDE0, OnButtonStride0)
	ON_BN_CLICKED(IDC_BUTTON_ENCREAD_ON, OnButtonEncreadOn)
	ON_BN_CLICKED(IDC_BUTTON_ENCREAD_OFF, OnButtonEncreadOff)
	ON_BN_CLICKED(IDC_BUTTON_HIPYAW_VIB_ON, OnButtonHipyawVibOn)
	ON_BN_CLICKED(IDC_BUTTON_HIPYAW_VIB_OFF, OnButtonHipyawVibOff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWalkingExpDlg message handlers

void CWalkingExpDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	Close();
}

void CWalkingExpDlg::Close()
{
	m_pKhr3winDlg->ButtonControl(WALKING_EXP_CLOSE);
	DestroyWindow();
}

void CWalkingExpDlg::Init()
{
	//Initialization Routine Here
	//theApp.m_pSharedMemory->UpRightPoseOffset = 0.;
	m_WalkingPeriod=800;
	WalkingPeriod=m_WalkingPeriod;
	m_EditSway = 78;//70;
	SwayMod = m_EditSway;
	m_EditAnkle = (float)1.6;//1.2;
	m_UpRatio = (float)0.47;
	m_FootYGain = (float)0.;
	m_FootZGain = (float)0.;
	m_RollRefGain = (float)-0.5;
	m_ToeOffGain = (float)0.5;
	m_XshapeFactorGain = (float)0.0005;
	m_X_Shape_Factor = (float)1.5;
	m_Y_Shape_Factor = (float)1.2;
	m_YShapeFactorOpen = (float)1.2;
	m_YShapeFactorRecover = (float)1.2;
	m_Sway_Factor = (float)1.0;
	m_StartInitVelocityCoff = (float)0.8;
	m_PitchRefGain = (float)-0.5;
	m_LandingRollGain = (float)0.2;
	m_LandingPitchGain = (float)0.2;

	UpdateData(FALSE);

	// TODO: Add your control notification handler code here

	theApp.m_pSharedMemory->TestModeFlag = FALSE;

	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;
	
	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 0;
	
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;
	
	theApp.m_pSharedMemory->WalkingExp00_Flag = FALSE;
	theApp.m_pSharedMemory->GoStop_Flag = FALSE;
	
	theApp.m_pSharedMemory->SET_Flag = FALSE;
}

void CWalkingExpDlg::OnButtonHide() 
{
	// TODO: Add your control notification handler code here
	m_pKhr3winDlg->m_ButtonWalking.SetWindowText("Walking Show");
	ShowWindow(SW_HIDE);
}

void CWalkingExpDlg::OnButtonFast() 
{
	// TODO: Add your control notification handler code here

	if(WalkingPeriod == 950)
	{
		m_WalkingPeriod = 800;
	}
	else if(WalkingPeriod == 800)
	{
		m_WalkingPeriod = 700;
	}
	else if(WalkingPeriod == 700)
	{
		m_WalkingPeriod = 700;
	}

	WalkingPeriod=m_WalkingPeriod;

	if(m_WalkingPeriod == 950)
	{
		OLAnkleComp = (float)2.3;
		SwayMod = 80;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}
	else if(m_WalkingPeriod == 800)
	{
		OLAnkleComp = (float)1.7;
		SwayMod = 70;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}
	else if(m_WalkingPeriod == 700)
	{
		OLAnkleComp = (float)1.3;
		SwayMod = 63;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;

	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;

	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;

	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonSlow() 
{
	// TODO: Add your control notification handler code here
	
	if(WalkingPeriod == 950)
	{
		m_WalkingPeriod = 950;
	}
	else if(WalkingPeriod == 800)
	{
		m_WalkingPeriod = 950;
	}
	else if(WalkingPeriod == 700)
	{
		m_WalkingPeriod = 800;
	}
	
	WalkingPeriod=m_WalkingPeriod;

	if(m_WalkingPeriod == 950)
	{
		OLAnkleComp = (float)2.3;
		SwayMod = 80;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}
	else if(m_WalkingPeriod == 800)
	{
		OLAnkleComp = (float)1.7;
		SwayMod = 70;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}
	else if(m_WalkingPeriod == 700)
	{
		OLAnkleComp = (float)1.3;
		SwayMod = 63;
		theApp.m_pSharedMemory->WalkSway = SwayMod;
	}

	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;

	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;

	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactorOpen = m_YShapeFactorOpen;
	theApp.m_pSharedMemory->Y_ShapeFactorRecover = m_YShapeFactorRecover;
	theApp.m_pSharedMemory->X_ShapeFactor = m_X_Shape_Factor;
	theApp.m_pSharedMemory->ZMPref_AMP[1]=m_ZMP_AMP;
	WalkingPeriod=m_WalkingPeriod;
	SwayMod=m_EditSway;
	OLAnkleComp=m_EditAnkle;
	theApp.m_pSharedMemory->SET_Flag = TRUE;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonGraph() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	char	ButtonCase;

	m_ProfileGraph.GetWindowText(strText);

	if(strText == "Graph")			ButtonCase = 0;
	else if(strText == "Graph On")	ButtonCase = 1;
	else if(strText == "Graph Off")	ButtonCase = 2;

	switch(ButtonCase)
	{
		case 0:
			m_ProfileGraph.SetWindowText("Graph On");
			CreateGraph();
		case 1:
			m_ProfileGraph.SetWindowText("Graph Off");
			m_ProfileGraphDlg.ShowWindow(SW_SHOW);
		break;
		
		case 2:
			m_ProfileGraph.SetWindowText("Graph On");
			m_ProfileGraphDlg.ShowWindow(SW_HIDE);
		break;
	}
}

void CWalkingExpDlg::CreateGraph()
{
	if(!m_ProfileGraphDlg.m_hWnd)
	{
		m_ProfileGraphDlg.Create(IDD_DIALOG_PROF_GRAPH,this);
		m_ProfileGraphDlg.Init();
		m_ProfileGraphDlg.ShowWindow(SW_SHOW);
	}
}

void CWalkingExpDlg::OnButtonWalkReady() 
{
	//unsigned char i;
	/*
	////// Joint Lock Enable
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	*/
	
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[0]=-1;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	
	theApp.m_pSharedMemory->Walk_Ready_Flag = TRUE;
	
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	theApp.m_pSharedMemory->Home_Flag = FALSE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 0;
	
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->WalkingExp00_Flag = FALSE;
	theApp.m_pSharedMemory->GoStop_Flag = FALSE;
	
}

void CWalkingExpDlg::OnButtonHome() 
{
	//unsigned char i;

	/*
	////// Joint Lock Enable
	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		theApp.EnableHIP(i);
		Sleep(50);
		
		theApp.SendRunCMD(i);
		Sleep(50);
	}
	*/
	
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[1]=0;
	
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Walk01Test_Flag = FALSE;
	
	theApp.m_pSharedMemory->Home_Flag = TRUE;
	
	theApp.m_pSharedMemory->DSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->DSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->SSP_Pose_Set_Flag = 0;
	
	theApp.m_pSharedMemory->SSP_Pose_Reset_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_On_Flag = FALSE;
	theApp.m_pSharedMemory->SSP_Pose_CTRL_Off_Flag = FALSE;

	theApp.m_pSharedMemory->WalkingExp00_Flag = FALSE;
	theApp.m_pSharedMemory->GoStop_Flag = FALSE;
}

void CWalkingExpDlg::OnButtonGo()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->KeepGoing = m_Check_KeepGoing;

	//theApp.m_pSharedMemory->RHipRollCompenMag = m_HipRollCompen;
	//theApp.m_pSharedMemory->LHipRollCompenMag = m_HipRollCompenL;

	theApp.m_pSharedMemory->PROFTime[5]=0;
	theApp.m_pSharedMemory->PROFTime[6]=-100;
	theApp.m_pSharedMemory->PROFTime[7]=-100;

	theApp.m_pSharedMemory->PROFTime[8]=0;
	theApp.m_pSharedMemory->PROFTime[9]=0;
	theApp.m_pSharedMemory->PROFTime[10]=0;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[12] = 0;

	// changed by becool
	WalkingPeriod=m_WalkingPeriod;
	SwayMod=m_EditSway;
	OLAnkleComp=m_EditAnkle;
	//theApp.m_pSharedMemory->FootPlacementGain = m_FootPlacementGain;
	theApp.m_pSharedMemory->Roll_Ref_Gain = m_RollRefGain;
	theApp.m_pSharedMemory->Pitch_Ref_Gain = m_PitchRefGain;
	//theApp.m_pSharedMemory->FootYGain = m_FootYGain;
	//theApp.m_pSharedMemory->FootZGain = m_FootZGain;
	//////////////////////////////////////////////////////////////////////////
	
	theApp.m_pSharedMemory->WalkingExp00_Flag = TRUE;
	theApp.m_pSharedMemory->SHWalkingPeriod = WalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	theApp.m_pSharedMemory->StartInitVelCoff = m_StartInitVelocityCoff;
	theApp.m_pSharedMemory->ZMPAddCoff = m_ZmpAddCoff;

	theApp.m_pSharedMemory->Incl_Pitch_Offset = (int)m_AccPitchOffset;
	theApp.m_pSharedMemory->Incl_Roll_Offset = (int)m_AccRollOffset;
	theApp.m_pSharedMemory->LandingPitchGain = m_LandingPitchGain;
	theApp.m_pSharedMemory->LandingRollGain = m_LandingRollGain;

	theApp.m_pSharedMemory->DistLftRht = 0;
	theApp.m_pSharedMemory->DistFwdBwd = m_StepLength;
	theApp.m_pSharedMemory->AngTurn = 0;
	
	theApp.m_pSharedMemory->X_ShapeFactor = m_X_Shape_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactorOpen = m_YShapeFactorOpen;
	theApp.m_pSharedMemory->Y_ShapeFactorRecover = m_YShapeFactorRecover;
	theApp.m_pSharedMemory->X_ShapeFactorGain = m_XshapeFactorGain;
	theApp.m_pSharedMemory->ToeOffGain = m_ToeOffGain;
	
	theApp.m_pSharedMemory->tp_OLAnkComp = OLAnkleComp;
	theApp.m_pSharedMemory->tp_WalkSway = SwayMod;

	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	theApp.m_pSharedMemory->WalkSway = SwayMod;

	theApp.m_pSharedMemory->GoStop_Flag = TRUE;

	
	UpdateData(FALSE);


	m_ButtonSet.EnableWindow(DISABLE);
}

void CWalkingExpDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[8]=theApp.m_pSharedMemory->PROFTime[5];
	theApp.m_pSharedMemory->PROFTime[9]=theApp.m_pSharedMemory->PROFTime[6];
	theApp.m_pSharedMemory->PROFTime[10]=theApp.m_pSharedMemory->PROFTime[7];


	theApp.m_pSharedMemory->PROFTime[5]=0;
	theApp.m_pSharedMemory->PROFTime[6]=0;
	theApp.m_pSharedMemory->PROFTime[7]=0;

	theApp.m_pSharedMemory->SHWalkingPeriod = WalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;

	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;

	theApp.m_pSharedMemory->WalkingExp00_Flag = TRUE;
	theApp.m_pSharedMemory->DSP_ZMP_Recover_Flag = TRUE;
	theApp.m_pSharedMemory->GoStop_Flag = FALSE;
	//theApp.m_pSharedMemory->Foot_Displacement_Flag = 0;

	m_ButtonSet.EnableWindow(ENABLE);

	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonFtNull() 
{
	// TODO: Add your control notification handler code here
	m_Button_FT_Null.EnableWindow(FALSE);
	m_pKhr3winDlg->m_FT_ReadDlg.FT_Null();
	m_Button_FT_Null.EnableWindow(TRUE);
}

void CWalkingExpDlg::OnButtonForward() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn;

	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;

	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonBackward() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]>-1)
		theApp.m_pSharedMemory->DirButton[0]--;
	else if(theApp.m_pSharedMemory->DirButton[0]<=-1)
		theApp.m_pSharedMemory->DirButton[0] = -1;
	
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonLeft() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[1]<1)
		theApp.m_pSharedMemory->DirButton[1]++;
	else if(theApp.m_pSharedMemory->DirButton[1]>=1)
		theApp.m_pSharedMemory->DirButton[1] = 1;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	SwayMod=m_EditSway;
	OLAnkleComp=m_EditAnkle;
	//theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	//theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->tp_OLAnkComp = OLAnkleComp;
	theApp.m_pSharedMemory->tp_WalkSway = SwayMod;

	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonRight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn;

	if(theApp.m_pSharedMemory->DirButton[1]>-1)
		theApp.m_pSharedMemory->DirButton[1]--;
	else if(theApp.m_pSharedMemory->DirButton[1]<=-1)
		theApp.m_pSharedMemory->DirButton[1] = -1;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	SwayMod=m_EditSway;
	OLAnkleComp=m_EditAnkle;
	//theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	//theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->tp_OLAnkComp = OLAnkleComp;
	theApp.m_pSharedMemory->tp_WalkSway = SwayMod;
	
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonCw() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_LftRht = (float)30;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;
	
	if(theApp.m_pSharedMemory->DirButton[2]>-1)
		theApp.m_pSharedMemory->DirButton[2]--;
	else if(theApp.m_pSharedMemory->DirButton[2]<=-1)
		theApp.m_pSharedMemory->DirButton[2] = -1;
	
	if(theApp.m_pSharedMemory->DirButton[1]>-1)
		theApp.m_pSharedMemory->DirButton[1]--;
	else if(theApp.m_pSharedMemory->DirButton[1]<=-1)
		theApp.m_pSharedMemory->DirButton[1] = -1;
	
	if(WalkingPeriod == 700)
	{
		m_WalkingPeriod = 700;
		WalkingPeriod=m_WalkingPeriod;
		
		m_UpRatio = (float)0.47;
		theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
		
		OLAnkleComp = (float)1.2;

		if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 63;
		else	SwayMod = 69;

		theApp.m_pSharedMemory->WalkSway = SwayMod;
		theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		m_Sway_Factor = (float)0.8;
		m_Y_Shape_Factor = (float)0.8;
		
		m_SwayDelayOpen = (float)2.5;
		m_SwayDelayRecover = (float)1.2;
	}
	else if (WalkingPeriod == 800)
	{
		m_WalkingPeriod = 800;
		WalkingPeriod=m_WalkingPeriod;
		
		SwayMod=m_EditSway;
		OLAnkleComp=m_EditAnkle;
		

		//if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 70;
		//else	SwayMod = 77;
		
		theApp.m_pSharedMemory->tp_WalkSway = SwayMod;	
		theApp.m_pSharedMemory->tp_OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->tp_WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->tp_OLAnkComp;
		
		//theApp.m_pSharedMemory->WalkSway = SwayMod;	
		//theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		//m_EditSway = theApp.m_pSharedMemory->WalkSway;
		//m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		
		//m_Sway_Factor = (float)0.8;
		//m_Y_Shape_Factor = (float)0.8;
		
		m_SwayDelayOpen = (float)2.2;
		m_SwayDelayRecover = (float)1.8;
	}
	else if (WalkingPeriod == 950)
	{
		m_WalkingPeriod = 950;	
		WalkingPeriod=m_WalkingPeriod;
		
		OLAnkleComp = (float)2.2;

		if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 76;
		else	SwayMod = 79;
		
		theApp.m_pSharedMemory->WalkSway = SwayMod;
		theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		m_Sway_Factor = (float)0.87;
		m_Y_Shape_Factor = (float)0.87;
		m_SwayDelayOpen = (float)2.5;
		m_SwayDelayRecover = (float)2.0;
	}
		
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnButtonCcw() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_LftRht = (float)30;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;

	if(theApp.m_pSharedMemory->DirButton[2]<1)
		theApp.m_pSharedMemory->DirButton[2]++;
	else if(theApp.m_pSharedMemory->DirButton[2]>=1)
		theApp.m_pSharedMemory->DirButton[2] = 1;
	
	if(theApp.m_pSharedMemory->DirButton[1]<1)
		theApp.m_pSharedMemory->DirButton[1]++;
	else if(theApp.m_pSharedMemory->DirButton[1]>=1)
		theApp.m_pSharedMemory->DirButton[1] = 1;
	
	if(WalkingPeriod == 700)
	{
		m_WalkingPeriod = 700;
		WalkingPeriod=m_WalkingPeriod;
		
		m_UpRatio = (float)0.47;
		theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
		
		OLAnkleComp = (float)1.2;

		if(theApp.m_pSharedMemory->DirButton[2]==0)	SwayMod = 63;
		else	SwayMod = 69;

		theApp.m_pSharedMemory->WalkSway = SwayMod;
		theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		m_Sway_Factor = (float)0.8;
		m_Y_Shape_Factor = (float)0.8;
		
		m_SwayDelayOpen = (float)2.5;
		m_SwayDelayRecover = (float)1.2;
	}
	else if (WalkingPeriod == 800)
	{
		m_WalkingPeriod = 800;
		WalkingPeriod=m_WalkingPeriod;
		
		//OLAnkleComp = (float)1.7;

		//if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 70;
		//else	SwayMod = 77;
		
		theApp.m_pSharedMemory->tp_WalkSway = SwayMod;	
		theApp.m_pSharedMemory->tp_OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->tp_WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->tp_OLAnkComp;
		
		//theApp.m_pSharedMemory->WalkSway = SwayMod;	
		//theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		//m_EditSway = theApp.m_pSharedMemory->WalkSway;
		//m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		
		//m_Sway_Factor = (float)0.8;
		//m_Y_Shape_Factor = (float)0.8;
		
		m_SwayDelayOpen = (float)2.2;
		m_SwayDelayRecover = (float)1.8;
	}
	else if (WalkingPeriod == 950)
	{
		m_WalkingPeriod = 950;	
		WalkingPeriod=m_WalkingPeriod;
		
		OLAnkleComp = (float)2.2;

		if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 76;
		else	SwayMod = 79;
		
		theApp.m_pSharedMemory->WalkSway = SwayMod;
		theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
		
		m_EditSway = theApp.m_pSharedMemory->WalkSway;
		m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
		
		theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
		theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
		
		m_Sway_Factor = (float)0.87;
		m_Y_Shape_Factor = (float)0.87;
		m_SwayDelayOpen = (float)2.5;
		m_SwayDelayRecover = (float)2.0;
	}

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;


	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p810cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =800;
	WalkingPeriod=m_WalkingPeriod;

	//theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.3;	

	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.7;//m_X_Shape_Factor;

	OLAnkleComp = (float)1.5;
	SwayMod = 70;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;

	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 100;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;

	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p820cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =800;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.7;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.6;//m_X_Shape_Factor;

	OLAnkleComp = (float)1.3;
	SwayMod = 70;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 200;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p9510cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_WalkingPeriod =950;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.3;	

	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.85;//m_X_Shape_Factor;

	OLAnkleComp = (float)2.1;//2.3;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 100;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;

	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p9530cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =950;
	WalkingPeriod=m_WalkingPeriod;

	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.65;	

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.85;//m_X_Shape_Factor;
	
	OLAnkleComp = (float)2.1;//2.05;
	SwayMod = 78;//80;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 300;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTON0p825cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =800;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.9;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.6;//m_X_Shape_Factor;

	OLAnkleComp = (float)1.2;
	SwayMod = 70;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 250;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p710cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =700;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = 1.;	

	m_UpRatio = (float)0.425;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.7;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1]=(float)75.;
	OLAnkleComp = (float)1.2;
	SwayMod = 66;//64;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 100;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;

	theApp.m_pSharedMemory->PROFTime[11] = 0;	
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p720cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =700;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = 1.5;
	
	m_UpRatio = (float)0.425;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.6;
	theApp.m_pSharedMemory->ZMPref_AMP[1]=(float)75.;
	OLAnkleComp = (float)1.2;
	SwayMod = 65; //64;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 200;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTON0p725cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =700;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = 1.5;
	
	m_UpRatio = (float)0.425;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.55;
	theApp.m_pSharedMemory->ZMPref_AMP[1]=(float)75.;
	OLAnkleComp = (float)1.1;
	SwayMod = 66;//64
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 250;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p75cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod = 700;
	WalkingPeriod=m_WalkingPeriod;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	OLAnkleComp = (float)1.2;
	SwayMod = 63;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;

	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)1.2;

	m_LftRht = (float)50;
		
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONSide0p85cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod = 800;
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)1.7;
	SwayMod = 70;

	theApp.m_pSharedMemory->WalkSway = SwayMod;	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;


	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;

	m_SwayDelayOpen = (float)2.2;
	m_SwayDelayRecover = (float)1.8;

	m_LftRht = (float)50;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p955cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_WalkingPeriod = 950;	
	WalkingPeriod=m_WalkingPeriod;

	OLAnkleComp = (float)2.2;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;

	m_Sway_Factor = (float)0.87;
	m_Y_Shape_Factor = (float)0.87;
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)2.0;

	m_LftRht = (float)50;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTON0p9520cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod =950;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = (float)0.5;	

	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.85;//m_X_Shape_Factor;

	OLAnkleComp = (float)2.1;//2.05;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 200;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnBUTTON0p950cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =950;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = 0.;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	OLAnkleComp = (float)2.2;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 0;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnBUTTON0p80cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =800;
	WalkingPeriod=m_WalkingPeriod;

	theApp.m_pSharedMemory->UpRightPoseOffset = 0.;

	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	theApp.m_pSharedMemory->X_ShapeFactor = (float)1.7;//m_X_Shape_Factor;
	
	OLAnkleComp = (float)1.6;
	SwayMod = 70;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 0;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];
	m_X_Shape_Factor = theApp.m_pSharedMemory->X_ShapeFactor;

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTON0p70cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod =700;
	WalkingPeriod=m_WalkingPeriod;
	
	theApp.m_pSharedMemory->UpRightPoseOffset = 0.;
	
	m_UpRatio = (float)0.5;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	OLAnkleComp = (float)1.1;//1.3
	SwayMod = 66;//64
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = 0;
	theApp.m_pSharedMemory->AngTurn = m_Turn;
	
	if(theApp.m_pSharedMemory->DirButton[0]<1)
		theApp.m_pSharedMemory->DirButton[0]++;
	else if(theApp.m_pSharedMemory->DirButton[0]>=1)
		theApp.m_pSharedMemory->DirButton[0] = 1;
	
	theApp.m_pSharedMemory->ZMPref_AMP[1] = m_ZMP_AMP;
	m_LftRht = theApp.m_pSharedMemory->DistLftRht;
	m_FwdBwd = theApp.m_pSharedMemory->DistFwdBwd;
	m_Turn = theApp.m_pSharedMemory->AngTurn;
	m_ZMP_AMP = theApp.m_pSharedMemory->ZMPref_AMP[1];

	theApp.m_pSharedMemory->PROFTime[11] = 0;
	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnButtonSwayAdjOn() 
{
	// TODO: Add your control notification handler code here
	if(m_Sway_OnOff == FALSE)	m_Sway_OnOff = TRUE;
	else m_Sway_OnOff = FALSE;

	if(m_Sway_OnOff == TRUE)	theApp.m_pSharedMemory->SwayAdjToggle = TRUE;
	else theApp.m_pSharedMemory->SwayAdjToggle = FALSE;
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p957cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod = 950;	
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)2.2;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.85;
	m_Y_Shape_Factor = (float)0.85;
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)2.0;
	
	m_LftRht = (float)70;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p9510cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod = 950;	
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)2.2;
	SwayMod = 76;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.83;
	m_Y_Shape_Factor = (float)0.84;
	m_SwayDelayOpen = (float)2.35;
	m_SwayDelayRecover = (float)2.25;
	
	m_LftRht = (float)100;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p87cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod = 800;
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)1.7;
	SwayMod = 70;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.78;

	m_SwayDelayOpen = (float)2.3;
	m_SwayDelayRecover = (float)1.6;
	
	m_LftRht = (float)70;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;

	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;

	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnBUTTONSide0p810cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_WalkingPeriod = 800;
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)1.7;
	SwayMod = 70;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	m_Sway_Factor = (float)0.7;
	m_Y_Shape_Factor = (float)0.7;
	
	m_SwayDelayOpen = (float)2.0;
	m_SwayDelayRecover = (float)1.8;
	
	m_LftRht = (float)100;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnBUTTONSide0p77cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod = 700;
	WalkingPeriod=m_WalkingPeriod;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	OLAnkleComp = (float)1.2;
	SwayMod = 63;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)1.2;
	
	m_LftRht = (float)70;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);	
}

void CWalkingExpDlg::OnBUTTONSide0p710cm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_WalkingPeriod = 700;
	WalkingPeriod=m_WalkingPeriod;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;

	OLAnkleComp = (float)1.2;
	SwayMod = 63;
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.7;
	m_Y_Shape_Factor = (float)0.7;
	
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)1.2;
	
	m_LftRht = (float)100;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	
	UpdateData(FALSE);		
}

void CWalkingExpDlg::OnBUTTONTURN0p710() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)10;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;
	
	m_WalkingPeriod = 700;
	WalkingPeriod=m_WalkingPeriod;
		
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	OLAnkleComp = (float)1.2;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 63;
	else	SwayMod = 69;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)1.2;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONTURN0p810() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)10;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;

	m_WalkingPeriod = 800;
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)1.7;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 70;
	else	SwayMod = 77;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.2;
	m_SwayDelayRecover = (float)1.8;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONTURN0p9510() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)10;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;

	m_WalkingPeriod = 950;	
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)2.2;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 76;
	else	SwayMod = 79;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.87;
	m_Y_Shape_Factor = (float)0.87;
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)2.0;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONTURN0p730() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)30;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;
	
	m_WalkingPeriod = 700;
	WalkingPeriod=m_WalkingPeriod;
	
	m_UpRatio = (float)0.47;
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	
	OLAnkleComp = (float)1.2;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 63;
	else	SwayMod = 69;

	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)1.2;

	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONTURN0p830() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)30;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;
	
	m_WalkingPeriod = 800;
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)1.7;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 70;
	else	SwayMod = 77;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;	
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	
	m_Sway_Factor = (float)0.8;
	m_Y_Shape_Factor = (float)0.8;
	
	m_SwayDelayOpen = (float)2.2;
	m_SwayDelayRecover = (float)1.8;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnBUTTONTURN0p9530() 
{
	// TODO: Add your control notification handler code here
	m_LftRht = (float)30;
	m_Turn = (float)30;
	theApp.m_pSharedMemory->DistLftRht = m_LftRht;
	theApp.m_pSharedMemory->DistFwdBwd = m_FwdBwd;
	theApp.m_pSharedMemory->AngTurn = m_Turn/2;
	
	m_WalkingPeriod = 950;	
	WalkingPeriod=m_WalkingPeriod;
	
	OLAnkleComp = (float)2.2;

	if(theApp.m_pSharedMemory->DirButton[2] == 0)	SwayMod = 76;
	else	SwayMod = 79;
	
	theApp.m_pSharedMemory->WalkSway = SwayMod;
	theApp.m_pSharedMemory->OLAnkComp = OLAnkleComp;
	
	m_EditSway = theApp.m_pSharedMemory->WalkSway;
	m_EditAnkle = theApp.m_pSharedMemory->OLAnkComp;
	
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = WalkingPeriod;
	
	m_Sway_Factor = (float)0.87;
	m_Y_Shape_Factor = (float)0.87;
	m_SwayDelayOpen = (float)2.5;
	m_SwayDelayRecover = (float)2.0;
	
	theApp.m_pSharedMemory->YSway_Factor = m_Sway_Factor;
	theApp.m_pSharedMemory->Y_ShapeFactor = m_Y_Shape_Factor;
	
	theApp.m_pSharedMemory->SwayDelayOpen = m_SwayDelayOpen;
	theApp.m_pSharedMemory->SwayDelayRecover = m_SwayDelayRecover;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonXPlus() 
{
	// TODO: Add your control notification handler code here
	m_XOffset++;
	theApp.m_pSharedMemory->OFFSETAdj[0] = m_XOffset;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonXMinus() 
{
	// TODO: Add your control notification handler code here
	m_XOffset--;
	theApp.m_pSharedMemory->OFFSETAdj[0] = m_XOffset;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonYPlus() 
{
	// TODO: Add your control notification handler code here
	m_YOffset++;
	theApp.m_pSharedMemory->OFFSETAdj[1] = m_YOffset;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonYMinus() 
{
	// TODO: Add your control notification handler code here
	m_YOffset--;
	theApp.m_pSharedMemory->OFFSETAdj[1] = m_YOffset;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonArmOnoff() 
{
	// TODO: Add your control notification handler code here
	if(m_Check_Arm == TRUE)
		m_Check_Arm = FALSE;
	else
		m_Check_Arm = TRUE;


	if(m_Check_Arm == TRUE)
	{
		theApp.m_pSharedMemory->Arm_Motion=TRUE;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
	else
	{
		theApp.m_pSharedMemory->Arm_Motion=FALSE;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}

	
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonMotion1() 
{
	// TODO: Add your control notification handler code here
	// 0: Torso yaw
	// 1: Head yaw
	// 2: Head pitch
	// 3: LSP
	// 4: LSY
	// 5: LSR
	// 6: LEB
	// 7: LWR
	// 8: LWP
	// 9: RSP
	// 10: RSY
	// 11: RSR
	// 12: REB
	// 13: RWR
	// 14: RWP
	// 15: LRHP
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f,  1.f};	
	//float	scale[16] = {0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f};	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float	Constant[26];
	float	CosCoeff[26][41];
	float	SinCoeff[26][41];
	float	sum;

	//BYTE	TxData[8];

	int		NoOfCoeff[26] = {33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41};
	int		m;
	int		JointIndex;
	int		t;
	int		T;

	FILE *ifp;

	theApp.m_pSharedMemory->MotionFlag[1] = FALSE;
	
	ifp = fopen("C:\\user\\mrquick\\KHR3\\MotionCapture\\4-2-coeff.txt","r");
	
	//TxData[0] = 3;
	//CAN_WRITE(0x66, TxData, 8);
	
	fseek( ifp, 0L, SEEK_SET );

	//	T = 1690; //normal
	//T = 2100; //slow
	T = 3000;
	////
	
	for(JointIndex=0; JointIndex < 26; JointIndex++)
	{
		fscanf(ifp,"%f",&Constant[JointIndex]);
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&CosCoeff[JointIndex][m]);
		}
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&SinCoeff[JointIndex][m]);
		}
	}
	fclose(ifp);

	for(t=0; t < T; t++)
	{
		for(JointIndex=0; JointIndex < 26; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = scale[JointIndex]*sum;
		}
	}
	theApp.Home(T);

	theApp.m_pSharedMemory->MotionLength[1] = T;

	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[1] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}
void CWalkingExpDlg::OnButtonMotion2() 
{
	// TODO: Add your control notification handler code here
	// 0: Torso yaw
	// 1: Head yaw
	// 2: Head pitch\
	// 3: LSP
	// 4: LSY
	// 5: LSR
	// 6: LEB
	// 7: LWR
	// 8: LWP
	// 9: RSP
	// 10: RSY
	// 11: RSR
	// 12: REB
	// 13: RWR
	// 14: RWP
	// 15: LRHP
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f,  1.f};	
	//float	scale[16] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f};	
	//float	scale[16] = {0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f};	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float	Constant[26];
	float	CosCoeff[26][67];
	float	SinCoeff[26][67];
	float	sum;
	
	//BYTE	TxData[8];
	
	//int		NoOfCoeff[26] = {48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
	int		NoOfCoeff[26] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	
	FILE *ifp;
	
	theApp.m_pSharedMemory->MotionFlag[2] = FALSE;
	
	//ifp = fopen("D:\\user\\mrquick\\KHR3\\MotionCapture\\4-2-coeff.txt","r");
	//ifp = fopen("D:\\user\\MotionCapture\\8-2-coeff.txt","r");
	ifp = fopen("C:\\user\\MotionCapture\\8-2-1-coeff.txt","r");
	
	//TxData[0] = 3;
	//CAN_WRITE(0x66, TxData, 8);
	
	fseek( ifp, 0L, SEEK_SET );
	
	//	T = 1690; //normal
	T = 5400; //slow
	////
	
	for(JointIndex=0; JointIndex < 26; JointIndex++)
	{
		fscanf(ifp,"%f",&Constant[JointIndex]);
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&CosCoeff[JointIndex][m]);
		}
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&SinCoeff[JointIndex][m]);
		}
	}
	fclose(ifp);
	
	for(t=0; t < T; t++)
	{
		for(JointIndex=0; JointIndex < 26; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = scale[JointIndex]*sum;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[2] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[2] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CWalkingExpDlg::OnButtonMotionStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->MOTION_Stop = 1;
}


void CWalkingExpDlg::OnButtonMotion3() 
{
	// TODO: Add your control notification handler code here
	// 0: Torso yaw
	// 1: Head yaw
	// 2: Head pitch\
	// 3: LSP
	// 4: LSY
	// 5: LSR
	// 6: LEB
	// 7: LWR
	// 8: LWP
	// 9: RSP
	// 10: RSY
	// 11: RSR
	// 12: REB
	// 13: RWR
	// 14: RWP
	// 15: LRHP
	
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f, 1.0f,  -1.f,  -1.f,  1.f,  1.f,  1.f,  1.f};	
	//float	scale[16] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f};	
	//float	scale[16] = {0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f};	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float	Constant[26];
	float	CosCoeff[26][41];
	float	SinCoeff[26][41];
	float	sum;
	
	//BYTE	TxData[8];
	
	//int		NoOfCoeff[26] = {48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
	int NoOfCoeff[26] = {33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41};

	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	
	FILE *ifp;
	
	theApp.m_pSharedMemory->MotionFlag[3] = FALSE;
	
	//ifp = fopen("D:\\user\\mrquick\\KHR3\\MotionCapture\\4-2-coeff.txt","r");
	//ifp = fopen("D:\\user\\MotionCapture\\8-2-coeff.txt","r");
	ifp = fopen("C:\\user\\MotionCapture\\4-2-coeff_080723.txt","r");
	
	//TxData[0] = 3;
	//CAN_WRITE(0x66, TxData, 8);
	
	fseek( ifp, 0L, SEEK_SET );
	
	//	T = 1690; //normal
	T = 3400; //slow
	////
	
	for(JointIndex=0; JointIndex < 26; JointIndex++)
	{
		fscanf(ifp,"%f",&Constant[JointIndex]);
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&CosCoeff[JointIndex][m]);
		}
		for(m=0; m < NoOfCoeff[JointIndex]; m++)
		{
			fscanf(ifp,"%f",&SinCoeff[JointIndex][m]);
		}
	}
	fclose(ifp);
	
	for(t=0; t < T; t++)
	{
		for(JointIndex=0; JointIndex < 26; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = scale[JointIndex]*sum;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[3] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[3] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;	
}

void CWalkingExpDlg::OnButtonChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	theApp.m_pSharedMemory->UPRATIO = m_UpRatio;
	theApp.m_pSharedMemory->SHWalkingPeriod = theApp.m_pSharedMemory->SHnewWalkingPeriod;
	theApp.m_pSharedMemory->SHnewWalkingPeriod = m_WalkingPeriod;
	theApp.m_pSharedMemory->X_ShapeFactor = m_X_Shape_Factor;
	theApp.m_pSharedMemory->X_ShapeFactorGain = m_XshapeFactorGain;
	
	theApp.m_pSharedMemory->pHipMoveRatio = m_HipMoveRatio;
	theApp.m_pSharedMemory->Delta_Foot_Position[1] = m_LFootDelta_Y;
	theApp.m_pSharedMemory->Delta_Foot_Position[4] = m_RFootDelta_Y;
	theApp.m_pSharedMemory->FootPlacementGain = m_FootPlacementGain;
	theApp.m_pSharedMemory->Roll_Ref_Gain = m_RollRefGain;
	
	
	theApp.m_pSharedMemory->DistLftRht = 0;
	theApp.m_pSharedMemory->DistFwdBwd = m_StepLength;
	theApp.m_pSharedMemory->AngTurn = 0;

	
	//if(theApp.m_pSharedMemory->DirButton[0]<1) theApp.m_pSharedMemory->DirButton[0]++;
	//else if(theApp.m_pSharedMemory->DirButton[0]>=1) theApp.m_pSharedMemory->DirButton[0]=1;

	if(m_StepLength >= 0) 
	{
		theApp.m_pSharedMemory->DistFwdBwd = m_StepLength;
		theApp.m_pSharedMemory->DirButton[0] = 1;
		theApp.m_pSharedMemory->AnkleRollGain = (float)1.0;
	}
	else if(m_StepLength < 0)
	{
		theApp.m_pSharedMemory->DirButton[0] = -1;
		theApp.m_pSharedMemory->DistFwdBwd = (float)(-1.*m_StepLength);
		theApp.m_pSharedMemory->AnkleRollGain = m_AnkleRollGain;
	}

}

void CWalkingExpDlg::OnButtonHipPitchInc1() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipPitchAngle = (float)(theApp.m_pSharedMemory->HipPitchAngle + 0.5);
	m_HipPitchAngle = theApp.m_pSharedMemory->HipPitchAngle;
	UpdateData(FALSE);
	
}

void CWalkingExpDlg::OnButtonHipPitchDec() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipPitchAngle = (float)(theApp.m_pSharedMemory->HipPitchAngle - 0.5);
	m_HipPitchAngle = theApp.m_pSharedMemory->HipPitchAngle;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonHipPitchInc2() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipPitchAngle = (float)(theApp.m_pSharedMemory->HipPitchAngle + 0.1);
	m_HipPitchAngle = theApp.m_pSharedMemory->HipPitchAngle;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonHipPitchDec2() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipPitchAngle = (float)(theApp.m_pSharedMemory->HipPitchAngle - 0.1);
	m_HipPitchAngle = theApp.m_pSharedMemory->HipPitchAngle;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonSaveTimerReset() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[11] = 0;
}

void CWalkingExpDlg::OnButtonStride0() 
{
	// TODO: Add your control notification handler code here
	m_StepLength = (float)0.;
	theApp.m_pSharedMemory->DistFwdBwd = m_StepLength;
	UpdateData(FALSE);
}

void CWalkingExpDlg::OnButtonEncreadOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->EncFlag = TRUE;
}

void CWalkingExpDlg::OnButtonEncreadOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->EncFlag = FALSE;
}



void CWalkingExpDlg::OnButtonHipyawVibOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipYawVibFlag = TRUE;
}

void CWalkingExpDlg::OnButtonHipyawVibOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->HipYawVibFlag = FALSE;
}
