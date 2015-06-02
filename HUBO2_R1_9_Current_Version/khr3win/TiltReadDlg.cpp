// TiltReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "TiltReadDlg.h"
#include "Khr3winDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTiltReadDlg dialog

extern CKhr3winApp theApp;

CTiltReadDlg::CTiltReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTiltReadDlg::IDD, pParent), m_Board_Body_Roll(this, 2), m_Board_Body_Pitch(this, 2)
										 , m_Board_Right_Foot_Incl(this, 2), m_Board_Left_Foot_Incl(this, 2)
{
	m_pKhr3winDlg = NULL;
	//{{AFX_DATA_INIT(CTiltReadDlg)
	m_Angle_Pitch = 0.0f;
	m_Angle_Roll = 0.0f;
	m_Gyro_CutOff_Pitch = (float)(2*PI*0.04);
	m_Gyro_CutOff_Roll  = (float)(2*PI*0.04);
	m_Incl_CutOff_Pitch = (float)(2*PI*0.04);
	m_Incl_CutOff_Roll  = (float)(2*PI*0.04);
	m_Gyro_Pitch = 0;
	m_Gyro_Roll = 0;
	m_Incl_Pitch = 0;
	m_Incl_Roll = 0;
	m_Left_Foot_Deg_Pitch = 0.0f;
	m_Left_Foot_Deg_Roll = 0.0f;
	m_Left_Foot_Incl_Pitch = 0;
	m_Left_Foot_Incl_Roll =  0;
	m_Left_Foot_LPF_Pitch = 0.0f;
	m_Left_Foot_LPF_Roll = 0.0f;
	m_Right_Foot_Deg_Pitch = 0.0f;
	m_Right_Foot_Deg_Roll = 0.0f;
	m_Right_Foot_Incl_Pitch = 0;
	m_Right_Foot_Incl_Roll = 0;
	m_Right_Foot_LPF_Pitch = 0.0f;
	m_Right_Foot_LPF_Roll = 0.0f;
	m_Gyro_CutOff_Yaw	= (float)(2*PI*0.1);
	m_Gyro_Yaw	= 0;
	//}}AFX_DATA_INIT
}

void CTiltReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTiltReadDlg)
	DDX_Control(pDX, IDC_STATIC_RIGHT_FOOT_INCL_BOARD, m_Board_Right_Foot_Incl);
	DDX_Control(pDX, IDC_STATIC_LEFT_FOOT_INCL_BOARD, m_Board_Left_Foot_Incl);
	DDX_Control(pDX, IDC_STATIC_BODY_PITCH_BOARD, m_Board_Body_Pitch);
	DDX_Control(pDX, IDC_STATIC_BODY_ROLL_BOARD, m_Board_Body_Roll);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_Button_Stop);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_Button_Reset);
	DDX_Control(pDX, IDC_BUTTON_GRAPH, m_Button_Graph);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_Button_Close);
	DDX_Text(pDX, IDC_ANGLE_P, m_Angle_Pitch);
	DDX_Text(pDX, IDC_ANGLE_R, m_Angle_Roll);
	DDX_Text(pDX, IDC_GYRO_CUT_OFF_P, m_Gyro_CutOff_Pitch);
	DDX_Text(pDX, IDC_GYRO_CUT_OFF_R, m_Gyro_CutOff_Roll);
	DDX_Text(pDX, IDC_INCL_CUT_OFF_P, m_Incl_CutOff_Pitch);
	DDX_Text(pDX, IDC_INCL_CUT_OFF_R, m_Incl_CutOff_Roll);
	DDX_Text(pDX, IDC_GYRO_P, m_Gyro_Pitch);
	DDX_Text(pDX, IDC_GYRO_R, m_Gyro_Roll);
	DDX_Text(pDX, IDC_INCL_P, m_Incl_Pitch);
	DDX_Text(pDX, IDC_INCL_R, m_Incl_Roll);
	DDX_Text(pDX, IDC_LEFT_DEG_P, m_Left_Foot_Deg_Pitch);
	DDX_Text(pDX, IDC_LEFT_DEG_R, m_Left_Foot_Deg_Roll);
	DDX_Text(pDX, IDC_LEFT_INCL_P, m_Left_Foot_Incl_Pitch);
	DDX_Text(pDX, IDC_LEFT_INCL_R, m_Left_Foot_Incl_Roll);
	DDX_Text(pDX, IDC_LEFT_LPF_P, m_Left_Foot_LPF_Pitch);
	DDX_Text(pDX, IDC_LEFT_LPF_R, m_Left_Foot_LPF_Roll);
	DDX_Text(pDX, IDC_RIGHT_DEG_P, m_Right_Foot_Deg_Pitch);
	DDX_Text(pDX, IDC_RIGHT_DEG_R, m_Right_Foot_Deg_Roll);
	DDX_Text(pDX, IDC_RIGHT_INCL_P, m_Right_Foot_Incl_Pitch);
	DDX_Text(pDX, IDC_RIGHT_INCL_R, m_Right_Foot_Incl_Roll);
	DDX_Text(pDX, IDC_RIGHT_LPF_P, m_Right_Foot_LPF_Pitch);
	DDX_Text(pDX, IDC_RIGHT_LPF_R, m_Right_Foot_LPF_Roll);
	DDX_Text(pDX, IDC_GYRO_CUT_OFF_Y, m_Gyro_CutOff_Yaw);
	DDX_Text(pDX, IDC_GYRO_Y, m_Gyro_Yaw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTiltReadDlg, CDialog)
	//{{AFX_MSG_MAP(CTiltReadDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, OnButtonGraph)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_START_COMPENSATION, OnButtonStartCompensation)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SAVE, OnButtonDataSave)
	ON_BN_CLICKED(IDC_BUTTON_FOOT_ACC_RESET, OnButtonFootAccReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTiltReadDlg message handlers

void CTiltReadDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CTiltReadDlg::Close();
}

void CTiltReadDlg::Close()
{
	theApp.m_pSharedMemory->Read_TILT_Flag = FALSE; //일단 이렇게 둔다.. 나중에 수정 해야함.
	theApp.m_pSharedMemory->GYRO_RESET	=	FALSE;
	m_pKhr3winDlg->ButtonControl(TILT_CLOSE);
	KillTimer(1);
	DestroyWindow();
}

void CTiltReadDlg::ButtonControl(int Msg)
{
	switch(Msg)
	{
	/////////////////////////////////////////////////////////////////////
	// Graph Button
	case TILT_STOP:
		TiltStop();
		m_Button_Stop.SetWindowText("Start");
		break;
	case TILT_START:
		TiltStart();
		m_Button_Stop.SetWindowText("Stop");
		break;
	case TILT_GRAPH_ON:
		m_Button_Graph.SetWindowText("Graph Hold");
		break;
	case TILT_GRAPH_HOLD:
		m_Button_Graph.SetWindowText("Graph Start");
		break;
	}	
}

void CTiltReadDlg::OnTimer(UINT nIDEvent) 
{
	DispTilt();
	CDialog::OnTimer(nIDEvent);
}

void CTiltReadDlg::DispTilt()
{
	m_Angle_Pitch = theApp.m_pSharedMemory->Compen_Theta_P;
	m_Angle_Roll = theApp.m_pSharedMemory->Compen_Theta_R;
	
	m_Incl_Pitch = theApp.m_pSharedMemory->ACC_P;
	m_Incl_Roll  = theApp.m_pSharedMemory->ACC_R;

	m_Gyro_Pitch = theApp.m_pSharedMemory->GYRO_P;
	m_Gyro_Roll  = theApp.m_pSharedMemory->GYRO_R;

	m_Left_Foot_Deg_Pitch = theApp.m_pSharedMemory->LF_TILT_P;
	m_Left_Foot_Deg_Roll  = theApp.m_pSharedMemory->LF_TILT_R;

	m_Left_Foot_Incl_Pitch = theApp.m_pSharedMemory->LF_INCL_P;
	m_Left_Foot_Incl_Roll  = theApp.m_pSharedMemory->LF_INCL_R;

	m_Right_Foot_Deg_Pitch = theApp.m_pSharedMemory->RF_TILT_P;
	m_Right_Foot_Deg_Roll  = theApp.m_pSharedMemory->RF_TILT_R;

	m_Right_Foot_Incl_Pitch = theApp.m_pSharedMemory->RF_INCL_P;
	m_Right_Foot_Incl_Roll  = theApp.m_pSharedMemory->RF_INCL_R;

	UpdateData(FALSE);
}

void CTiltReadDlg::Init()
{
	m_nTime = 0;
	theApp.m_pSharedMemory->Read_TILT_Flag	=	TRUE;
	theApp.m_pSharedMemory->GYRO_RESET		=	FALSE;
	theApp.m_pSharedMemory->CUT_OFF			=	TRUE;
	InitBoard();
	UpdateData(FALSE);
}

void CTiltReadDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	CString strText;

	m_Button_Stop.GetWindowText(strText);

	if(strText == "Stop")
	{
		ButtonControl(TILT_STOP);
	}
	else if(strText == "Start")
	{
		ButtonControl(TILT_START);
	}
}

void CTiltReadDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	GyroReset();
}

void CTiltReadDlg::GyroReset()
{
	theApp.m_pSharedMemory->GYRO_RESET	=	TRUE;
}

void CTiltReadDlg::TiltStop()
{
	theApp.m_pSharedMemory->CUT_OFF = FALSE;
	KillTimer(1);
}

void CTiltReadDlg::TiltStart()
{
	UpdateData(TRUE);

	//theApp.m_pSharedMemory->Gyro_CutOffR = m_Gyro_CutOff_Roll;
	//theApp.m_pSharedMemory->Gyro_CutOffP = m_Gyro_CutOff_Pitch;
	//theApp.m_pSharedMemory->Gyro_CutOffY = m_Gyro_CutOff_Yaw;

	//theApp.m_pSharedMemory->Acc_CutOffR = m_Incl_CutOff_Roll;
	//theApp.m_pSharedMemory->Acc_CutOffP = m_Incl_CutOff_Pitch;

	theApp.m_pSharedMemory->CUT_OFF = TRUE;
	
	SetTimer(1,DISP_TIMER,NULL);
}

void CTiltReadDlg::InitBoard()
{
	m_Board_Body_Roll.SetBoardDC(m_Board_Body_Roll.GetDC());
	m_Board_Body_Roll.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_Body_Roll.SetXRange(10, 0);
	m_Board_Body_Roll.SetYRange(15, -15);
	m_Board_Body_Roll.SetXYGap(1, 5);
	m_Board_Body_Roll.SetGraphName(1,"Roll");

	m_Board_Body_Pitch.SetBoardDC(m_Board_Body_Pitch.GetDC());
	m_Board_Body_Pitch.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_Body_Pitch.SetXRange(10, 0);
	m_Board_Body_Pitch.SetYRange(15, -15);
	m_Board_Body_Pitch.SetXYGap(1, 5);
	m_Board_Body_Pitch.SetGraphName(1,"Pitch");

	m_Board_Left_Foot_Incl.SetBoardDC(m_Board_Left_Foot_Incl.GetDC());
	m_Board_Left_Foot_Incl.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_Left_Foot_Incl.SetXRange(10, 0);
	m_Board_Left_Foot_Incl.SetYRange(15, -15);
	m_Board_Left_Foot_Incl.SetXYGap(1, 5);
	m_Board_Left_Foot_Incl.SetGraphName(2,"Roll","Pitch");
		
	m_Board_Right_Foot_Incl.SetBoardDC(m_Board_Right_Foot_Incl.GetDC());
	m_Board_Right_Foot_Incl.InitBoard(CENTERPOINT_LEFTMIDDLE);	
	m_Board_Right_Foot_Incl.SetXRange(10, 0);
	m_Board_Right_Foot_Incl.SetYRange(15, -15);
	m_Board_Right_Foot_Incl.SetXYGap(1, 5);
	m_Board_Right_Foot_Incl.SetGraphName(2, "Roll", "Pitch");
}

void CTiltReadDlg::UpdateBoardPoint()
{
	UpdateData();

	m_Board_Body_Roll.SetCoordinatePoint(0, (int)m_Angle_Roll);

	m_Board_Body_Pitch.SetCoordinatePoint(0, (int)m_Angle_Pitch);
	
	m_Board_Left_Foot_Incl.SetCoordinatePoint(0, (int)m_Left_Foot_Deg_Roll);
	m_Board_Left_Foot_Incl.SetCoordinatePoint(1, (int)m_Left_Foot_Deg_Pitch);

	m_Board_Right_Foot_Incl.SetCoordinatePoint(0, (int)m_Right_Foot_Deg_Roll);
	m_Board_Right_Foot_Incl.SetCoordinatePoint(1, (int)m_Right_Foot_Deg_Pitch);

}

void CTiltReadDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}

void CTiltReadDlg::OnButtonGraph() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_Button_Graph.GetWindowText(strText);
	
	if(strText == "Graph Start")
	{
		m_Board_Body_Pitch.StartGraph(DISP_TIMER);
		m_Board_Body_Roll.StartGraph(DISP_TIMER);
		m_Board_Left_Foot_Incl.StartGraph(DISP_TIMER);
		m_Board_Right_Foot_Incl.StartGraph(DISP_TIMER);

		SetTimer(1, DISP_TIMER, NULL);
		ButtonControl(TILT_GRAPH_ON);
	}
	else if(strText == "Graph Hold")
	{
		KillTimer(1);

		m_Board_Body_Roll.KillTimer(1);
		m_Board_Body_Pitch.KillTimer(1);
		m_Board_Left_Foot_Incl.KillTimer(1);
		m_Board_Right_Foot_Incl.KillTimer(1);
		
		ButtonControl(TILT_GRAPH_HOLD);
	}	
}

void CTiltReadDlg::OnButtonHide() 
{
	// TODO: Add your control notification handler code here
	m_pKhr3winDlg->m_ButtonTiltRead.SetWindowText("TILT SHOW");
	ShowWindow(SW_HIDE);
}

void CTiltReadDlg::OnButtonStartCompensation() 
{
	// TODO: Add your control notification handler code here
	
	//theApp.m_pSharedMemory->StartReadTheta = TRUE;
	theApp.m_pSharedMemory->GYRO_RESET	=	TRUE;
	theApp.m_pSharedMemory->FootAccReset = TRUE;
}

void CTiltReadDlg::OnButtonDataSave() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->DataSaveFlag=TRUE;
	theApp.m_pSharedMemory->PROFTime[11]=0;
}

void CTiltReadDlg::OnButtonFootAccReset() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->FootAccReset = TRUE;
}
