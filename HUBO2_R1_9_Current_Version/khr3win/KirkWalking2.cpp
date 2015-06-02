// KirkWalking2.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "KirkWalking2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKirkWalking2 dialog

HWND hCommWnd;	//serial
//global hCommWnd;
extern CKhr3winApp theApp;

CKirkWalking2::CKirkWalking2(CWnd* pParent /*=NULL*/)
	: CDialog(CKirkWalking2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKirkWalking2)
	m_BC_Y_AMP = 0.0f;
	m_FOOT_Z_AMP = 0.0f;
	m_R_comp_angle = 0.0f;
	m_L_comp_angle = 0.0f;
	m_StepLength = 0.0f;
	m_SideStepLength = 0.0f;
	m_TurningAngle = 0.0f;
	m_WalkTestMode = FALSE;
	m_LORollGain = 0.0f;
	m_LOPitchGain = 0.0f;
	m_Temp1 = 0.0f;
	m_Temp2 = 0.0f;
	m_AmpTemp1 = 0.0f;
	m_StepTime = 0;
	m_CtrlModeDamping = FALSE;
	m_CtrlModePosture = FALSE;
	m_pGesture = NULL;
	m_ArmMotion = FALSE;
	//}}AFX_DATA_INIT
}


void CKirkWalking2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKirkWalking2)
	DDX_Text(pDX, IDC_EDIT_BC_Y_AMP, m_BC_Y_AMP);
	DDX_Text(pDX, IDC_EDIT_FOOT_Z_AMP, m_FOOT_Z_AMP);
	DDX_Text(pDX, IDC_EDIT_L_COMP_ANGLE, m_R_comp_angle);
	DDX_Text(pDX, IDC_EDIT_R_COMP_ANGLE, m_L_comp_angle);
	DDX_Text(pDX, IDC_EDIT_STEP_LENGTH, m_StepLength);
	DDX_Text(pDX, IDC_EDIT_SIDE_STEP_LENGTH, m_SideStepLength);
	DDX_Text(pDX, IDC_EDIT_TURNING_ANGLE, m_TurningAngle);
	DDX_Check(pDX, IDC_CHECK_WALK_TEST_MODE, m_WalkTestMode);
	DDX_Text(pDX, IDC_EDIT_LO_ROLL_GAIN, m_LORollGain);
	DDX_Text(pDX, IDC_EDIT_LO_PITCH_GAIN, m_LOPitchGain);
	DDX_Text(pDX, IDC_EDIT_TEMP1, m_Temp1);
	DDX_Text(pDX, IDC_EDIT_TEMP2, m_Temp2);
	DDX_Text(pDX, IDC_EDIT_AMP_TEMP, m_AmpTemp1);
	DDX_Text(pDX, IDC_EDIT_STEP_TIME, m_StepTime);
	DDX_Check(pDX, IDC_CTRL_MODE_DAMPING, m_CtrlModeDamping);
	DDX_Check(pDX, IDC_CTRL_MODE_POSTURE, m_CtrlModePosture);
	DDX_Check(pDX, IDC_CHECK_ARM_MOTION, m_ArmMotion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKirkWalking2, CDialog)
	//{{AFX_MSG_MAP(CKirkWalking2)
	ON_BN_CLICKED(IDC_BUTTON_WALK_IN_PLACE, OnButtonWalkInPlace)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_WLK_READY, OnButtonWlkReady)
	ON_BN_CLICKED(IDC_BUTTON_HOME, OnButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_GO_FWD, OnButtonGoFwd)
	ON_BN_CLICKED(IDC_BUTTON_GO_BWD, OnButtonGoBwd)
	ON_BN_CLICKED(IDC_BUTTON_L_SIDE, OnButtonLSide)
	ON_BN_CLICKED(IDC_BUTTON_R_SIDE, OnButtonRSide)
	ON_BN_CLICKED(IDC_BUTTON_CCW, OnButtonCcw)
	ON_BN_CLICKED(IDC_BUTTON_CW, OnButtonCw)
	ON_BN_CLICKED(IDC_BUTTON_TIMER_RESET, OnButtonTimerReset)
	ON_BN_CLICKED(IDC_CTRL_MODE_DAMPING, OnCtrlModeDamping)
	ON_BN_CLICKED(IDC_CTRL_MODE_POSTURE, OnCtrlModePosture)
	ON_BN_CLICKED(IDC_BUTTON_GESTURE, OnButtonGesture)
	ON_WM_CREATE()
	ON_MESSAGE(WM_COMM_READ, OnCommunication)  
	ON_BN_CLICKED(IDC_BUTTON_COM1OPEN, OnButtonCom1open)
	ON_BN_CLICKED(IDC_BUTTON_COM1CLOSE, OnButtonCom1close)
	ON_BN_CLICKED(IDC_BUTTON_NO_WALK_IN_PLACE, OnButtonNoWalkInPlace)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMM_READ, OnCommunication)  
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKirkWalking2 message handlers

void CKirkWalking2::Init()
{
	m_BC_Y_AMP = (float)76.0;
	m_FOOT_Z_AMP = (float)35.0;

	m_L_comp_angle = (float)2.2;
	m_R_comp_angle = (float)2.2;
	m_StepLength = 150.0f;

	m_TurningAngle = 15.0f;
	m_SideStepLength = 60.0f;

	m_LOPitchGain = 2.0f;
	m_LORollGain = 1.0f;

	m_StepTime = 80;

	m_Temp1 = 1.0f;
	m_Temp2 = 1.0f;
	m_AmpTemp1 = 76.0f;
	
	m_WalkTestMode = FALSE;
	m_CtrlModeDamping = FALSE;
	m_CtrlModePosture = TRUE;
	theApp.m_pSharedMemory->SSP_CTRL_MODE = 2;
	m_ArmMotion = FALSE;

	theApp.m_pSharedMemory->Kirk_WalkingFlag = TRUE;
	
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CKirkWalking2::OnButtonWalkInPlace() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->gain_temp1 = m_Temp1;
	theApp.m_pSharedMemory->gain_temp2 = m_Temp2;
	theApp.m_pSharedMemory->amp_temp1 = m_AmpTemp1;
	
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
		
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;

	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;

	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;

	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = DISABLE;
	theApp.m_pSharedMemory->Mark_Time_Flag = ENABLE;
	theApp.m_pSharedMemory->FSM = FALSE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	Walking_Mode = 0;
}

void CKirkWalking2::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	

	while(theApp.m_pSharedMemory->Walking_Stop_Flag == DISABLE)
	{
		if(theApp.m_pSharedMemory->Walking_Stop_Flag_2 == 1)
		{
			theApp.m_pSharedMemory->Walking_Stop_Flag = ENABLE;
		}
	}

	
	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(TRUE);

	Walking_Mode = 6;
}

void CKirkWalking2::OnOK() 
{
	// TODO: Add extra validation here

	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;

	theApp.m_pSharedMemory->Kirk_WalkingFlag = FALSE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	
	
	CDialog::OnOK();
}

void CKirkWalking2::OnButtonWlkReady() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[0]=-1;
	
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	
	theApp.m_pSharedMemory->Walk_Ready_Flag = TRUE;
}

void CKirkWalking2::OnButtonHome() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->PROFTime[1]=0;
	
	theApp.m_pSharedMemory->DSP_Pose_Set_Flag = 0;
	theApp.m_pSharedMemory->Walk_Ready_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;

	
	theApp.m_pSharedMemory->Home_Flag = TRUE;
}

void CKirkWalking2::OnButtonGoFwd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;

	if(m_StepLength >= 250) m_StepLength = 250;
	else if(m_StepLength <=0) m_StepLength = 0;

	theApp.m_pSharedMemory->Step_Length = m_StepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;
	

	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;

	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = ENABLE;
	theApp.m_pSharedMemory->FSM = FALSE;

	Walking_Mode = 1;
	
}

void CKirkWalking2::OnButtonGoBwd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;
	
	if(m_StepLength >= 150) m_StepLength = 150;
	else if(m_StepLength <=0) m_StepLength = 0;

	theApp.m_pSharedMemory->Step_Length = m_StepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;
	

	
	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;

	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = TRUE;
	theApp.m_pSharedMemory->FSM = 1;
}

void CKirkWalking2::OnButtonLSide() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);


	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;
	
	if(m_SideStepLength >= 100) m_StepLength = 100;
	else if(m_StepLength <=0) m_StepLength = 0;

	theApp.m_pSharedMemory->Side_Step_Length = m_SideStepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;


	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	//theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	
	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = TRUE;
	theApp.m_pSharedMemory->FSM = 0;
	Walking_Mode = 3;
}

void CKirkWalking2::OnButtonRSide() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;
	
	if(m_SideStepLength >= 100) m_StepLength = 100;
	else if(m_StepLength <=0) m_StepLength = 0;
	
	theApp.m_pSharedMemory->Side_Step_Length = m_SideStepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;
	
	
	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	//theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	
	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = TRUE;
	theApp.m_pSharedMemory->FSM = 0;
	Walking_Mode = 2;
}

void CKirkWalking2::OnButtonCcw() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	//theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = 25.f;
	theApp.m_pSharedMemory->Turning_Angle = m_TurningAngle;
	
	if(m_SideStepLength >= 100) m_SideStepLength = 100;
	else if(m_SideStepLength <=0) m_SideStepLength = 0;
	
	theApp.m_pSharedMemory->Side_Step_Length = m_SideStepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;
	
	
	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	//theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	
	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = TRUE;
	theApp.m_pSharedMemory->FSM = 0;
	Walking_Mode = 5;
}

void CKirkWalking2::OnButtonCw() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;
	
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	//theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = 25.f;
	theApp.m_pSharedMemory->Turning_Angle = m_TurningAngle;
	
	if(m_SideStepLength >= 100) m_SideStepLength = 100;
	else if(m_SideStepLength <=0) m_SideStepLength = 0;
	
	theApp.m_pSharedMemory->Side_Step_Length = m_SideStepLength;
	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;
	
	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;
	
	
	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	theApp.m_pSharedMemory->Mark_Time_Flag = DISABLE;
	theApp.m_pSharedMemory->Walk_FWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_BWD_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_L_Side_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_R_Side_Flag = FALSE;
	//theApp.m_pSharedMemory->Walk_CW_Turn_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CCW_Turn_Flag = FALSE;
	
	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = FALSE;
	theApp.m_pSharedMemory->Walk_CW_Turn_Flag = TRUE;
	theApp.m_pSharedMemory->FSM = 0;
	Walking_Mode = 4;
}

void CKirkWalking2::OnButtonTimerReset() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
}

void CKirkWalking2::OnCtrlModeDamping() 
{
	// TODO: Add your control notification handler code here
	
	m_CtrlModePosture = FALSE;
	m_CtrlModeDamping = TRUE;

	theApp.m_pSharedMemory->SSP_CTRL_MODE = 1;
	UpdateData(FALSE);
}

void CKirkWalking2::OnCtrlModePosture() 
{
	// TODO: Add your control notification handler code here
	
	m_CtrlModePosture = TRUE;
	m_CtrlModeDamping = FALSE;
	
	theApp.m_pSharedMemory->SSP_CTRL_MODE = 2;
	UpdateData(FALSE);
}

void CKirkWalking2::OnButtonGesture() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	theApp.m_pSharedMemory->Arm_Motion = m_ArmMotion;

	theApp.m_pSharedMemory->Gesture_Flag = TRUE;

	if(m_pGesture != NULL)
	{
		m_pGesture->SetFocus();
	}
	else
	{
		m_pGesture = new CGesture;
		m_pGesture->SetParentWindow(this);
		m_pGesture->Create(this);
		m_pGesture->ShowWindow(SW_SHOW);
	}
}

int CKirkWalking2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	hCommWnd= m_hWnd;	// serial

	return 0;
}


void CKirkWalking2::OnButtonCom1open() 
{
	// TODO: Add your control notification handler code here
	if(!m_portCOM.OpenPort("COM1",115200,1)) // open com1 port baud rate 19200
	{
		AfxMessageBox(" fail..");
	}
	else
	{
		AfxMessageBox(" success..");
	}	

	GetDlgItem(IDC_BUTTON_COM1OPEN)->EnableWindow(FALSE);
}

void CKirkWalking2::OnButtonCom1close() 
{
	// TODO: Add your control notification handler code here
	m_portCOM.ClosePort();

	GetDlgItem(IDC_BUTTON_COM1OPEN)->EnableWindow(TRUE);	
}

LRESULT CKirkWalking2::OnCommunication(UINT port, LONG lParam)	// serial
{
	int size = 0;
	BYTE aByte;
	char Buffer[50];
	char cmd;
	CString output;

	size = (m_portCOM.m_QueueRead).GetSize();

	if(size==0) return 0;

	if(size <= 50){
		serial_cnt++;

		for(int j=0; j<size; j++ )
		{
			(m_portCOM.m_QueueRead).GetByte(&aByte);		
			Buffer[j] = aByte;
		}	
		output = Buffer;

	}
	else{
		return 0;
	}

	//SetDlgItemText(IDC_EDIT_SERIALTEST, output);

	if(Buffer[0] = '#'){
		cmd = Buffer[1];
		switch(cmd){
		case 'a':
			OnButtonWalkInPlace();
			break;
		case 'b':
			OnButtonStop();
			break;
		case 'c':
			OnButtonGesture();
			break;
		default:
			break;
		}
	}

	return 0;
}

void CKirkWalking2::OnButtonNoWalkInPlace() 
{

	// walk in place
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(FALSE);

	theApp.m_pSharedMemory->gain_temp1 = m_Temp1;
	theApp.m_pSharedMemory->gain_temp2 = m_Temp2;
	theApp.m_pSharedMemory->amp_temp1 = m_AmpTemp1;
	
	theApp.m_pSharedMemory->Amp_ankleL = m_L_comp_angle;
	theApp.m_pSharedMemory->Amp_ankleR = m_R_comp_angle;
		
	theApp.m_pSharedMemory->Walk_BC_Ydir_Amp = m_BC_Y_AMP;
	theApp.m_pSharedMemory->Walk_Foot_Zdir_Amp = m_FOOT_Z_AMP;

	theApp.m_pSharedMemory->Gain_LO_Con_r = m_LORollGain;
	theApp.m_pSharedMemory->Gain_LO_Con_p = m_LOPitchGain;

	//theApp.m_pSharedMemory->Step_time = 95;
	theApp.m_pSharedMemory->Step_time = m_StepTime;
	theApp.m_pSharedMemory->dsp_ratio = (float)0.05;
	theApp.m_pSharedMemory->Delay_time = 10;

	theApp.m_pSharedMemory->Up_time = (unsigned int)(theApp.m_pSharedMemory->Step_time*(1 - theApp.m_pSharedMemory->dsp_ratio));
	theApp.m_pSharedMemory->Upstart_time = theApp.m_pSharedMemory->Step_time - theApp.m_pSharedMemory->Up_time/2 -  theApp.m_pSharedMemory->Delay_time;






	//dan
	theApp.m_pSharedMemory->Walking_Test_Flag = m_WalkTestMode;

	theApp.m_pSharedMemory->Int_CNT = 0;
	theApp.m_pSharedMemory->Path_Area_CNT = 0;
	theApp.m_pSharedMemory->Walking_Stop_Flag = ENABLE;  // changed to make walk stop
	//theApp.m_pSharedMemory->Walking_Stop_Flag = DISABLE;
	theApp.m_pSharedMemory->Mark_Time_Flag = ENABLE;
	theApp.m_pSharedMemory->FSM = FALSE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->DataSaveFlag = TRUE;
//	Walking_Mode = 0;


	// Stop
    theApp.m_pSharedMemory->Walking_Stop_Flag_2 = 1;




/*
	while(theApp.m_pSharedMemory->Walking_Stop_Flag == DISABLE)
	{
		if(theApp.m_pSharedMemory->Walking_Stop_Flag_2 == 1)
		{
			theApp.m_pSharedMemory->Walking_Stop_Flag = ENABLE;
		}
	}
*/
	
	GetDlgItem(IDC_BUTTON_WALK_IN_PLACE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GO_FWD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GO_BWD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_L_SIDE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_R_SIDE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CCW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CW)->EnableWindow(TRUE);

	Walking_Mode = 6;
	
}
