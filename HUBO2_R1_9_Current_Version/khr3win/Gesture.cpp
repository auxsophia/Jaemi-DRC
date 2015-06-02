// Gesture.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Gesture.h"
#include "KirkWalking2.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int Flag_Com2_auto = 0;

/////////////////////////////////////////////////////////////////////////////
// CGesture dialog
HWND hCommWnd2;	//serial

extern int Flag_Com2;
extern CKhr3winApp theApp;

CGesture::CGesture(CWnd* pParent /*=NULL*/)
: CDialog(CGesture::IDD, pParent)
{
	//	hCommWnd2= m_hWnd;	// serial
	//{{AFX_DATA_INIT(CGesture)
	m_WristMotionMode = 0;
	m_WristAmp = 0.0f;
	m_WristHz = 0.0f;
	m_ShoulderHz = 0.0f;
	m_ShoulderRollAmp = 0.0f;
	m_ShoulderPitchAmp = 0.0f;
	m_GripDuty = 0;
	m_LeftHandActivation = FALSE;
	m_RightHandActivation = FALSE;
	m_ElbowAmp = 0.0f;
	//}}AFX_DATA_INIT
	m_pKirkWalking2 = NULL;
	//OnCommunication( 2, 0);
}


void CGesture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	OnCommunication( 2, 0);
	//{{AFX_DATA_MAP(CGesture)
	DDX_Text(pDX, IDC_EDIT_WRIST_MODE, m_WristMotionMode);
	DDX_Text(pDX, IDC_EDIT_WRIST_AMP, m_WristAmp);
	DDX_Text(pDX, IDC_EDIT_WRIST_HZ, m_WristHz);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_HZ, m_ShoulderHz);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_ROLL_AMP, m_ShoulderRollAmp);
	DDX_Text(pDX, IDC_EDIT_SHOULDER_PITCH_AMP, m_ShoulderPitchAmp);
	DDX_Text(pDX, IDC_EDIT_GRIP_DUTY, m_GripDuty);
	DDV_MinMaxInt(pDX, m_GripDuty, 0, 10);
	DDX_Check(pDX, IDC_CHECK_LEFT_HAND, m_LeftHandActivation);
	DDX_Check(pDX, IDC_CHECK_RIGHT_HAND, m_RightHandActivation);
	DDX_Text(pDX, IDC_EDIT_ELBOW_AMP, m_ElbowAmp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGesture, CDialog)
//{{AFX_MSG_MAP(CGesture)
ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
ON_BN_CLICKED(IDC_BUTTON_MOTION1, OnButtonMotion1)
ON_BN_CLICKED(IDC_BUTTON_MOTION2, OnButtonMotion2)
ON_BN_CLICKED(IDC_BUTTON_MOTION3, OnButtonMotion3)
ON_BN_CLICKED(IDC_BUTTON_MOTION4, OnButtonMotion4)
ON_BN_CLICKED(IDC_BUTTON_CONTROLL_OFF, OnButtonControllOff)
ON_BN_CLICKED(IDC_BUTTON_CONTROLL_ON, OnButtonControllOn)
ON_BN_CLICKED(IDC_BUTTON_GRIP_ON, OnButtonGripOn)
ON_BN_CLICKED(IDC_BUTTON_GRIP_OFF, OnButtonGripOff)
ON_BN_CLICKED(IDC_BUTTON_GRIP_STOP, OnButtonGripStop)
ON_BN_CLICKED(IDC_BUTTON_GRIP_ON2, OnButtonGripOn2)
ON_BN_CLICKED(IDC_BUTTON_HANDUP, OnButtonHandup)
ON_BN_CLICKED(IDC_BUTTON_HANDDOWN, OnButtonHanddown)
ON_BN_CLICKED(IDC_BUTTON_WRIST_MOTION_GO, OnButtonWristMotionGo)
ON_BN_CLICKED(IDC_BUTTON_WRIST_MOTION_STOP, OnButtonWristMotionStop)
ON_BN_CLICKED(IDC_BUTTON_SHOULDER_MOTION_GO, OnButtonShoulderMotionGo)
ON_BN_CLICKED(IDC_BUTTON_SHOULDER_MOTION_STOP, OnButtonShoulderMotionStop)
ON_BN_CLICKED(IDC_BUTTON_MOTION5, OnButtonMotion5)
ON_BN_CLICKED(IDC_BUTTON_MOTION6, OnButtonMotion6)
ON_BN_CLICKED(IDC_BUTTON_MOTION7, OnButtonMotion7)
ON_BN_CLICKED(IDC_BUTTON_MOTION8, OnButtonMotion8)
ON_BN_CLICKED(IDC_BUTTON_MOTION9, OnButtonMotion9)
ON_BN_CLICKED(IDC_BUTTON_MOTION10, OnButtonMotion10)
ON_BN_CLICKED(IDC_BUTTON_SHAKE_HANDS_START, OnButtonShakeHandsStart)
ON_BN_CLICKED(IDC_BUTTON_SHAKE_HANDS_STOP, OnButtonShakeHandsStop)
ON_BN_CLICKED(IDC_BUTTON_MOTION11, OnButtonMotion11)
ON_BN_CLICKED(IDC_BUTTON_MOTION13, OnButtonMotion13)
ON_BN_CLICKED(IDC_BUTTON_MOTION14, OnButtonMotion14)
ON_BN_CLICKED(IDC_BUTTON_MOTION15, OnButtonMotion15)
ON_BN_CLICKED(IDC_BUTTON_MOTION16, OnButtonMotion16)
ON_BN_CLICKED(IDC_BUTTON_MOTION17, OnButtonMotion17)
ON_BN_CLICKED(IDC_BUTTON_MOTION18, OnButtonMotion18)
ON_BN_CLICKED(IDC_BUTTON_MOTION19, OnButtonMotion19)
ON_BN_CLICKED(IDC_BUTTON_MOTION_ACTIVATION, OnButtonMotionActivation)
ON_BN_CLICKED(IDC_CHECK_RIGHT_HAND, OnCheckRightHand)
ON_BN_CLICKED(IDC_CHECK_LEFT_HAND, OnCheckLeftHand)
ON_BN_CLICKED(IDC_BUTTON_MOTION20, OnButtonMotion20)
ON_BN_CLICKED(IDC_BUTTON_MOTION21, OnButtonMotion21)
ON_BN_CLICKED(IDC_BUTTON_MOTION22, OnButtonMotion22)
ON_BN_CLICKED(IDC_BUTTON_MOTION23, OnButtonMotion23)
ON_BN_CLICKED(IDC_BUTTON_MOTION24, OnButtonMotion24)
ON_BN_CLICKED(IDC_BUTTON_MOTION12, OnButtonMotion12)
ON_BN_CLICKED(IDC_BUTTON_MOTION25, OnButtonMotion25)
ON_BN_CLICKED(IDC_BUTTON_MOTION26, OnButtonMotion26)
ON_BN_CLICKED(IDC_BUTTON_MOTION27, OnButtonMotion27)
ON_BN_CLICKED(IDC_BUTTON_MOTION28, OnButtonMotion28)
ON_BN_CLICKED(IDC_BUTTON_MOTION29, OnButtonMotion29)
ON_BN_CLICKED(IDC_BUTTON_MOTION30, OnButtonMotion30)
ON_BN_CLICKED(IDC_BUTTON_MOTION31, OnButtonMotion31)
ON_BN_CLICKED(IDC_BUTTON_DSP_CONTROL, OnButtonDspControl)
ON_BN_CLICKED(IDC_BUTTON_DSP_CONTROL_ON, OnButtonDspControlOn)
ON_BN_CLICKED(IDC_BUTTON_DSP_CONTROL_OFF, OnButtonDspControlOff)
ON_BN_CLICKED(IDC_BUTTON_DSP_CONTROL_STOP, OnButtonDspControlStop)
ON_BN_CLICKED(IDC_BUTTON_SSP_CONTROL, OnButtonSspControl)
ON_BN_CLICKED(IDC_BUTTON_SSP_CONTROL_ON, OnButtonSspControlOn)
ON_BN_CLICKED(IDC_BUTTON_SSP_CONTROL_OFF, OnButtonSspControlOff)
ON_BN_CLICKED(IDC_BUTTON_SSP_CONTROL_STOP, OnButtonSspControlStop)
ON_BN_CLICKED(IDC_BUTTON_SSP_UPDOWN, OnButtonSspUpdown)
ON_BN_CLICKED(IDC_Com2Open, OnCom2Open)
ON_BN_CLICKED(IDC_Com2Close, OnCom2Close)
ON_MESSAGE(WM_COMM_READ2, OnCommunication)  // dan edit
ON_BN_CLICKED(IDC_Com2Check, OnCom2Check)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_GESTURE_RAISE_RIGHT_HAND, OnGestureRaiseRightHand)
ON_BN_CLICKED(IDC_GESTURE_RAISE_RIGHT_ARM, OnGestureRaiseRightArm)
ON_BN_CLICKED(IDC_GESTURE_RIGHT_ARM_CIRCLE, OnGestureRightArmCircle)
ON_BN_CLICKED(IDC_GESTURE_RAISE_LEFT_HAND, OnGestureRaiseLeftHand)
ON_BN_CLICKED(IDC_GESTURE_RAISE_LEFT_ARM, OnGestureRaiseLeftArm)
ON_BN_CLICKED(IDC_GESTURE_LEFT_ARM_CIRCLE, OnGestureLeftArmCircle)
ON_BN_CLICKED(IDC_GESTURE_TOUCH_HEAD, OnGestureTouchHead)
ON_BN_CLICKED(IDC_GESTURE_TIP_HAT, OnGestureTipHat)
ON_BN_CLICKED(IDC_GESTURE_TOUCH_NOSE, OnGestureTouchNose)
ON_BN_CLICKED(IDC_GESTURE_CLAP_HANDS, OnGestureClapHands)
ON_BN_CLICKED(IDC_GESTURE_RUB_STOMACH, OnGestureRubStomach)
ON_BN_CLICKED(IDC_GESTURE_FLAP_ARMS, OnGestureFlapArms)
ON_BN_CLICKED(IDC_GESTURE_CHOOCHOO, OnGestureChoochoo)
ON_BN_CLICKED(IDC_GESTURE_HANDS_ON_HIPS, OnGestureHandsOnHips)
ON_BN_CLICKED(IDC_GESTURE_SPEED_SLOW, OnGestureSpeedSlow)
ON_BN_CLICKED(IDC_GESTURE_SPEED_MEDIUM, OnGestureSpeedMedium)
ON_BN_CLICKED(IDC_GESTURE_SPEED_FAST, OnGestureSpeedFast)
ON_BN_CLICKED(IDC_JAEMI_SAYS_SCRIPT1, OnJaemiSaysScript1)
ON_BN_CLICKED(IDC_JAEMI_SAYS_SCRIPT2, OnJaemiSaysScript2)
	ON_BN_CLICKED(IDC_JAEMI_SAYS_CANCEL, OnJaemiSaysCancel)
	ON_BN_CLICKED(IDC_GESTURE_AUX_BEND_RIGHT_ELBOW, OnGestureAuxBendRightElbow)
	ON_BN_CLICKED(IDC_GESTURE_AUX_UNLV, OnGestureAuxUnlv)
	ON_BN_CLICKED(IDC_GESTURE_HANDS_ON_HIPS2, OnHelloWorld)
	ON_BN_CLICKED(IDC_GESTURE_HELLO_WORLD, OnGestureHelloWorld)
	//}}AFX_MSG_MAP
ON_MESSAGE(WM_COMM_READ2, OnCommunication)  // dan edit
//ON_MESSAGE(WM_COMM_READ2, OnCom2Check)		// dan edit
//ON_MESSAGE(WM_COMM_READ2, OnCommunication)
//	OnCommunication( 2, 0);
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGesture message handlers

BOOL CGesture::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	//OnCommunication( 2, 0);
	//hCommWnd= m_hWnd;	// serial
	return CDialog::Create(IDD, pParentWnd);
	
}

void CGesture::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Gesture_Flag = FALSE;
	m_pKirkWalking2->m_pGesture = NULL;
	OnCom2Close();		// close the comport if it is open
	
	DestroyWindow();	
}

void CGesture::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}

void CGesture::OnButtonMotion1() 
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
	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float	Constant[26];
	float	CosCoeff[26][67];
	float	SinCoeff[26][67];
	float	sum;
	
	int		NoOfCoeff[26] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	
	FILE *ifp;
	
	GetDlgItem(IDC_BUTTON_MOTION1)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[2] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\8-2-1-coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 3000; // dim : 10 mdec.
	
	
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
	
	for(t=0; t < T; t=t+10)
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
			for(j=0;j<=10;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-10][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-10][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-10][JointIndex])*0.1*j);
				}
				//else if(t == 0)
				//{
				//		theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j][JointIndex] = (float)(0. + (scale[JointIndex]*sum - 0.)*0.1*j);
				//		}
				
				//theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex])*0.1*j);
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[2] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[2] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	GetDlgItem(IDC_BUTTON_MOTION1)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion2() 
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
	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	//float	Constant[26];
	//float	CosCoeff[26][67];
	//float	SinCoeff[26][67];
	float	Constant[16];
	float	CosCoeff[16][67];
	float	SinCoeff[16][67];
	float	sum;
	
	//int		NoOfCoeff[26] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67};
	int		NoOfCoeff[16] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	
	FILE *ifp;
	
	GetDlgItem(IDC_BUTTON_MOTION2)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[2] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\8-2-1-coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 2600; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[2] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[2] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	GetDlgItem(IDC_BUTTON_MOTION2)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion3() 
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
	
	float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float	Constant[26];
	float	CosCoeff[26][67];
	float	SinCoeff[26][67];
	float	sum;
	
	int		NoOfCoeff[26] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	
	FILE *ifp;
	
	GetDlgItem(IDC_BUTTON_MOTION3)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[2] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\8-2-1-coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 3000; // dim : 10 mdec.
	
	
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
	
	for(t=0; t < T; t=t+5)
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
			for(j=0;j<=5;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-5][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-5][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-5][JointIndex])*0.2*j);
				}
				//else if(t == 0)
				//{
				//		theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j][JointIndex] = (float)(0. + (scale[JointIndex]*sum - 0.)*0.1*j);
				//		}
				
				//theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex])*0.1*j);
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[2] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[2] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	GetDlgItem(IDC_BUTTON_MOTION3)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion4() 
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
	
	float scale[16] = { 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f,  1.0f};	
	
	float	Constant[16];
	float	CosCoeff[16][67];
	float	SinCoeff[16][67];
	float	sum;
	
	int		NoOfCoeff[16] = {53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	MotionNo = 2;
	GetDlgItem(IDC_BUTTON_MOTION4)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\8-2-1-coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 2600; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION4)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonControllOff() 
{
	// TODO: Add your control notification handler code here
	theApp.Stop_CMD(EJMC4);
	Sleep(50);
	theApp.Stop_CMD(EJMC5);
	Sleep(50);
	theApp.EnableHIP(EJMC4);
	Sleep(50);
	theApp.EnableHIP(EJMC5);
	Sleep(20);
	
	GetDlgItem(IDC_BUTTON_GRIP_ON)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GRIP_OFF)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GRIP_ON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GRIP_STOP)->EnableWindow(TRUE);
}

void CGesture::OnButtonControllOn() 
{
	// TODO: Add your control notification handler code here
	theApp.SendRunCMD(EJMC4);
	Sleep(50);
	theApp.SendRunCMD(EJMC5);
	Sleep(50);
}

void CGesture::OnButtonGripOn() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	UpdateData(TRUE);
	
	if(m_RightHandActivation == TRUE) {TxData[0] = EJMC4; TxData[3]=0x00 | (m_GripDuty & 0x0F);}
	else if(m_LeftHandActivation == TRUE) {TxData[0] = EJMC5; TxData[3]=0x00 | (m_GripDuty & 0x0F);} 
	else {TxData[0] = EJMC4; TxData[3]=0x00 | (m_GripDuty & 0x0F);}
	
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	//TxData[3]=0x00 | (m_GripDuty & 0x0F);
	TxData[4]=0x00 | ((m_GripDuty+1) & 0x0F);
	TxData[5]=0x00 | (m_GripDuty & 0x0F);		// twice duty than other motor
	TxData[6]=0x00 | (m_GripDuty & 0x0F);		// twice duty than other motor
	TxData[7]=0x00 | ((m_GripDuty+1) & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CGesture::OnButtonGripOff() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	if(m_RightHandActivation == TRUE) {TxData[0] = EJMC4; TxData[3]=0x10 | (3 & 0x0F);}
	else if(m_LeftHandActivation == TRUE) {TxData[0] = EJMC5; TxData[3]=0x10 | (3 & 0x0F);}
	else {TxData[0] = EJMC4; TxData[3]=0x10 | (3 & 0x0F);}
	
	//TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	//TxData[3]=0x10 | (3 & 0x0F);
	TxData[4]=0x10 | (4 & 0x0F);
	TxData[5]=0x10 | (3 & 0x0F);
	TxData[6]=0x10 | (3 & 0x0F);
	TxData[7]=0x10 | (4 & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CGesture::OnButtonGripStop() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	
	if(m_RightHandActivation == TRUE) TxData[0] = EJMC4;
	else if(m_LeftHandActivation == TRUE) TxData[0] = EJMC5; 
	else TxData[0] = EJMC4;
	
	//TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	TxData[3]=0x10 | (0 & 0x0F);
	TxData[4]=0x10 | (0 & 0x0F);
	TxData[5]=0x10 | (0 & 0x0F);
	TxData[6]=0x10 | (0 & 0x0F);
	TxData[7]=0x10 | (0 & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CGesture::OnButtonGripOn2() 
{
	// TODO: Add your control notification handler code here
	unsigned char TxData[8];
	int duty;
	
	
	UpdateData(TRUE);
	
	duty = (int)(m_GripDuty/2.);
	
	if(m_RightHandActivation == TRUE) {TxData[0] = EJMC4; TxData[3]=0x00 | (duty & 0x0F);}
	else if(m_LeftHandActivation == TRUE) {TxData[0] = EJMC5; TxData[3]=0x00 | (duty & 0x0F);}
	else {TxData[0] = EJMC4; TxData[3]=0x00 | (duty & 0x0F);}
	
	//TxData[0]=EJMC4;
	TxData[1]=PwmCMD;
	TxData[2]=0x01;
	
	//TxData[3]=0x00 | (duty & 0x0F);
	TxData[4]=0x00 | (duty & 0x0F);
	TxData[5]=0x00 | (duty & 0x0F);
	TxData[6]=0x00 | (duty & 0x0F);
	TxData[7]=0x00 | (duty & 0x0F);
	
	theApp.CAN_WRITE1(CMD_TXDF, TxData, 8);
}

void CGesture::OnButtonHandup() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_BUTTON_HANDUP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_HANDDOWN)->EnableWindow(TRUE);
	theApp.m_pSharedMemory->WristConfigureFlag = 1;
}

void CGesture::OnButtonHanddown() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_BUTTON_HANDDOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_HANDUP)->EnableWindow(TRUE);
	theApp.m_pSharedMemory->WristConfigureFlag = 3;
}

void CGesture::OnButtonWristMotionGo() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_GO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_STOP)->EnableWindow(TRUE);
	
	UpdateData(TRUE);
	theApp.m_pSharedMemory->WristAmp = m_WristAmp;
	theApp.m_pSharedMemory->WristHz = m_WristHz;
	theApp.m_pSharedMemory->WristMotionMode = m_WristMotionMode;
	
	theApp.m_pSharedMemory->WristMotionFlag = 1;
}

void CGesture::OnButtonWristMotionStop() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_GO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_STOP)->EnableWindow(TRUE);
	theApp.m_pSharedMemory->WristMotionFlag = 3;
}

BOOL CGesture::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_GO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WRIST_MOTION_STOP)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BUTTON_GRIP_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GRIP_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GRIP_ON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GRIP_STOP)->EnableWindow(FALSE);
	
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGesture::OnButtonShoulderMotionGo() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_SHOULDER_MOTION_GO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHOULDER_MOTION_STOP)->EnableWindow(TRUE);
	
	UpdateData(TRUE);
	theApp.m_pSharedMemory->ShoulderPitchAmp = m_ShoulderPitchAmp;
	theApp.m_pSharedMemory->ShoulderRollAmp = m_ShoulderRollAmp;
	theApp.m_pSharedMemory->ElbowAmp = m_ElbowAmp;
	theApp.m_pSharedMemory->ShoulderPitchHz = m_ShoulderHz;
	theApp.m_pSharedMemory->ShoulderRollHz = m_ShoulderHz;
	
	
	theApp.m_pSharedMemory->ShoulderMotionFlag = 1;	
}

void CGesture::OnButtonShoulderMotionStop() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_SHOULDER_MOTION_GO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHOULDER_MOTION_STOP)->EnableWindow(TRUE);
	
	theApp.m_pSharedMemory->ShoulderMotionFlag = 3;
}



void CGesture::OnButtonMotion5() 
{
	// TODO: Add your control notification handler code here
	// 0: Torso yaw
	// 1: Head yaw
	// 2: Head pitch\
	// 3: LSP
	// 4: LSR
	// 5: LSY
	// 6: LEB
	// 7: LWR
	// 8: LWP
	// 9: RSP
	// 10: RSR
	// 11: RSY
	// 12: REB
	// 13: RWR
	// 14: RWP
	// 15: LRHP
	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f,  0.8f};	
	
	float	Constant[16];
	float	CosCoeff[16][134];
	float	SinCoeff[16][134];
	float	sum;
	
	int		NoOfCoeff[16] = {134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	MotionNo = 3;
	GetDlgItem(IDC_BUTTON_MOTION5)->EnableWindow(FALSE);
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\TeGukGuncoeff.txt","r");
	
	//ifp = fopen("C:\\user\\MotionCapture\\for_taichi_long.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 12000; // dim : 10 mdec.
	//T = 15000; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();	
	
	/*
	for(m=0;m<T;m++)
	{
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
	fscanf(ifp,"%f",&theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[m][JointIndex]);
	}
	}
	fclose(ifp);
	*/
	
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION5)->EnableWindow(TRUE);
	
	
}

void CGesture::OnButtonMotion6() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 1.0f,  0.8f,  0.8f,  0.8f,  1.0f,  0.8f, 1.0f, 0.8f, 0.8f,  0.8f,  1.f, 0.8f, 0.8f};	
	
	float	Constant[16];
	float	CosCoeff[16][61];
	float	SinCoeff[16][61];
	float	Coeff[16][123];
	float	sum;
	
	int		NoOfCoeff[16] = {61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 4;
	GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\taichi_short.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 5500;//6000;//6900; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < 123; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(TRUE);
	
	/*	
	// TODO: Add your control notification handler code here
	int i,j,T,t;
	int MotionNo;
	
	  MotionNo = 4;
	  GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(FALSE);
	  
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		  T = 6900;
		  
			
			  for(i=0 ; i < 17 ; i++)
			  for(j=0 ; j < 10000 ; j++)
			  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[j][i] = NULL; 
			  
				for(t=0 ; t < T ; t++){ 
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][0] = (float)(0.5*(3.27628+0.68241*cos(1*2*3.1415926536/T*t)-3.64545*sin(1*2*3.1415926536/T*t)+6.65076*cos(2*2*3.1415926536/T*t)-2.74957*sin(2*2*3.1415926536/T*t)-9.83118*cos(3*2*3.1415926536/T*t)+7.44259*sin(3*2*3.1415926536/T*t)-8.69259*cos(4*2*3.1415926536/T*t)+1.67809*sin(4*2*3.1415926536/T*t)-0.53011*cos(5*2*3.1415926536/T*t)-4.65449*sin(5*2*3.1415926536/T*t)+9.39606*cos(6*2*3.1415926536/T*t)-10.43641*sin(6*2*3.1415926536/T*t)+10.35332*cos(7*2*3.1415926536/T*t)+10.97989*sin(7*2*3.1415926536/T*t)-0.13410*cos(8*2*3.1415926536/T*t)-1.81056*sin(8*2*3.1415926536/T*t)-14.83241*cos(9*2*3.1415926536/T*t)+4.86660*sin(9*2*3.1415926536/T*t)-2.07477*cos(10*2*3.1415926536/T*t)-2.92810*sin(10*2*3.1415926536/T*t)+6.42151*cos(11*2*3.1415926536/T*t)+0.76421*sin(11*2*3.1415926536/T*t)+3.69885*cos(12*2*3.1415926536/T*t)-6.99965*sin(12*2*3.1415926536/T*t)-2.71415*cos(13*2*3.1415926536/T*t)+1.80060*sin(13*2*3.1415926536/T*t)-1.93552*cos(14*2*3.1415926536/T*t)+4.81128*sin(14*2*3.1415926536/T*t)+5.32741*cos(15*2*3.1415926536/T*t)+1.19909*sin(15*2*3.1415926536/T*t)-5.35964*cos(16*2*3.1415926536/T*t)-4.20924*sin(16*2*3.1415926536/T*t)-1.02505*cos(17*2*3.1415926536/T*t)+1.93341*sin(17*2*3.1415926536/T*t)-0.30397*cos(18*2*3.1415926536/T*t)-0.02446*sin(18*2*3.1415926536/T*t)+3.76898*cos(19*2*3.1415926536/T*t)+1.28810*sin(19*2*3.1415926536/T*t)+0.77305*cos(20*2*3.1415926536/T*t)-1.35543*sin(20*2*3.1415926536/T*t)-1.37240*cos(21*2*3.1415926536/T*t)-2.15448*sin(21*2*3.1415926536/T*t)-1.62402*cos(22*2*3.1415926536/T*t)+1.91299*sin(22*2*3.1415926536/T*t)+0.51775*cos(23*2*3.1415926536/T*t)+0.81695*sin(23*2*3.1415926536/T*t)+0.25680*cos(24*2*3.1415926536/T*t)+1.25455*sin(24*2*3.1415926536/T*t)+0.75927*cos(25*2*3.1415926536/T*t)-2.15486*sin(25*2*3.1415926536/T*t)-1.01068*cos(26*2*3.1415926536/T*t)-0.27626*sin(26*2*3.1415926536/T*t)+0.38190*cos(27*2*3.1415926536/T*t)-0.22478*sin(27*2*3.1415926536/T*t)+0.25724*cos(28*2*3.1415926536/T*t)
				+0.19365*sin(28*2*3.1415926536/T*t)-0.28533*cos(29*2*3.1415926536/T*t)+0.13148*sin(29*2*3.1415926536/T*t)+0.13133*cos(30*2*3.1415926536/T*t)-0.05466*sin(30*2*3.1415926536/T*t)-0.68061*cos(31*2*3.1415926536/T*t)+0.08879*sin(31*2*3.1415926536/T*t)+0.06534*cos(32*2*3.1415926536/T*t)+0.41498*sin(32*2*3.1415926536/T*t)+0.61482*cos(33*2*3.1415926536/T*t)-0.26778*sin(33*2*3.1415926536/T*t)+0.11327*cos(34*2*3.1415926536/T*t)-0.75457*sin(34*2*3.1415926536/T*t)-0.33297*cos(35*2*3.1415926536/T*t)+0.01226*sin(35*2*3.1415926536/T*t)-0.55459*cos(36*2*3.1415926536/T*t)+0.18454*sin(36*2*3.1415926536/T*t)+0.14160*cos(37*2*3.1415926536/T*t)+0.40599*sin(37*2*3.1415926536/T*t)-0.04548*cos(38*2*3.1415926536/T*t)+0.06936*sin(38*2*3.1415926536/T*t)+0.39514*cos(39*2*3.1415926536/T*t)+0.06792*sin(39*2*3.1415926536/T*t)-0.49496*cos(40*2*3.1415926536/T*t)-0.17666*sin(40*2*3.1415926536/T*t)-0.12225*cos(41*2*3.1415926536/T*t)-0.06988*sin(41*2*3.1415926536/T*t)+0.23952*cos(42*2*3.1415926536/T*t)+0.12198*sin(42*2*3.1415926536/T*t)+0.47018*cos(43*2*3.1415926536/T*t)-0.26261*sin(43*2*3.1415926536/T*t)-0.56008*cos(44*2*3.1415926536/T*t)-0.04185*sin(44*2*3.1415926536/T*t)-0.27592*cos(45*2*3.1415926536/T*t)+0.24152*sin(45*2*3.1415926536/T*t)+0.32029*cos(46*2*3.1415926536/T*t)+0.37254*sin(46*2*3.1415926536/T*t)+0.08153*cos(47*2*3.1415926536/T*t)-0.11070*sin(47*2*3.1415926536/T*t)-0.00471*cos(48*2*3.1415926536/T*t)+0.00460*sin(48*2*3.1415926536/T*t)-0.03353*cos(49*2*3.1415926536/T*t)-0.38732*sin(49*2*3.1415926536/T*t)+0.15918*cos(50*2*3.1415926536/T*t)-0.07048*sin(50*2*3.1415926536/T*t)-0.14843*cos(51*2*3.1415926536/T*t)+0.12980*sin(51*2*3.1415926536/T*t)-0.04628*cos(52*2*3.1415926536/T*t)+0.18327*sin(52*2*3.1415926536/T*t)-0.20544*cos(53*2*3.1415926536/T*t)-0.06463*sin(53*2*3.1415926536/T*t)+0.01062*cos(54*2*3.1415926536/T*t)-0.04059*sin(54*2*3.1415926536/T*t)+0.18117*cos(55*2*3.1415926536/T*t)+0.13758*sin(55*2*3.1415926536/T*t)
				+0.08203*cos(56*2*3.1415926536/T*t)-0.15230*sin(56*2*3.1415926536/T*t)-0.15441*cos(57*2*3.1415926536/T*t)+0.01201*sin(57*2*3.1415926536/T*t)+0.08414*cos(58*2*3.1415926536/T*t)-0.12730*sin(58*2*3.1415926536/T*t)+0.06736*cos(59*2*3.1415926536/T*t)-0.08987*sin(59*2*3.1415926536/T*t)-0.17639*cos(60*2*3.1415926536/T*t)+0.09878*sin(60*2*3.1415926536/T*t)-0.11713*cos(61*2*3.1415926536/T*t)+0.07669*sin(61*2*3.1415926536/T*t)));
				
				  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][1] = (float)(0.8*(-4.24116+0.22923*cos(1*2*3.1415926536/T*t)+1.97810*sin(1*2*3.1415926536/T*t)+1.56870*cos(2*2*3.1415926536/T*t)+0.80714*sin(2*2*3.1415926536/T*t)+0.24402*cos(3*2*3.1415926536/T*t)+2.13016*sin(3*2*3.1415926536/T*t)+2.98164*cos(4*2*3.1415926536/T*t)-0.94658*sin(4*2*3.1415926536/T*t)-3.18191*cos(5*2*3.1415926536/T*t)-4.05273*sin(5*2*3.1415926536/T*t)-3.85439*cos(6*2*3.1415926536/T*t)+2.44487*sin(6*2*3.1415926536/T*t)+4.78576*cos(7*2*3.1415926536/T*t)+0.25429*sin(7*2*3.1415926536/T*t)+1.09867*cos(8*2*3.1415926536/T*t)-1.53108*sin(8*2*3.1415926536/T*t)-0.59891*cos(9*2*3.1415926536/T*t)+2.93002*sin(9*2*3.1415926536/T*t)-0.18088*cos(10*2*3.1415926536/T*t)-0.45871*sin(10*2*3.1415926536/T*t)-0.88875*cos(11*2*3.1415926536/T*t)-3.03469*sin(11*2*3.1415926536/T*t)-2.47086*cos(12*2*3.1415926536/T*t)+1.53373*sin(12*2*3.1415926536/T*t)+2.21720*cos(13*2*3.1415926536/T*t)+0.99790*sin(13*2*3.1415926536/T*t)+0.13003*cos(14*2*3.1415926536/T*t)-1.82448*sin(14*2*3.1415926536/T*t)+0.26505*cos(15*2*3.1415926536/T*t)+0.79475*sin(15*2*3.1415926536/T*t)+1.03965*cos(16*2*3.1415926536/T*t)+0.62846*sin(16*2*3.1415926536/T*t)+0.40031*cos(17*2*3.1415926536/T*t)-0.23521*sin(17*2*3.1415926536/T*t)-0.92500*cos(18*2*3.1415926536/T*t)-0.85400*sin(18*2*3.1415926536/T*t)+0.30844*cos(19*2*3.1415926536/T*t)-0.72399*sin(19*2*3.1415926536/T*t)-0.41177*cos(20*2*3.1415926536/T*t)-0.12635*sin(20*2*3.1415926536/T*t)-0.39383*cos(21*2*3.1415926536/T*t)+0.91159*sin(21*2*3.1415926536/T*t)+0.44638*cos(22*2*3.1415926536/T*t)+0.74054*sin(22*2*3.1415926536/T*t)+1.23770*cos(23*2*3.1415926536/T*t)-0.62255*sin(23*2*3.1415926536/T*t)-0.49902*cos(24*2*3.1415926536/T*t)-0.61506*sin(24*2*3.1415926536/T*t)-0.81255*cos(25*2*3.1415926536/T*t)+0.66130*sin(25*2*3.1415926536/T*t)+0.66685*cos(26*2*3.1415926536/T*t)+0.25796*sin(26*2*3.1415926536/T*t)+0.03316*cos(27*2*3.1415926536/T*t)-0.44795*sin(27*2*3.1415926536/T*t)-0.33340*cos(28*2*3.1415926536/T*t)
				  +0.42795*sin(28*2*3.1415926536/T*t)+0.25862*cos(29*2*3.1415926536/T*t)+0.21643*sin(29*2*3.1415926536/T*t)-0.38778*cos(30*2*3.1415926536/T*t)-0.39200*sin(30*2*3.1415926536/T*t)+0.20312*cos(31*2*3.1415926536/T*t)+0.54057*sin(31*2*3.1415926536/T*t)+0.61691*cos(32*2*3.1415926536/T*t)-0.21498*sin(32*2*3.1415926536/T*t)-0.39782*cos(33*2*3.1415926536/T*t)-0.32330*sin(33*2*3.1415926536/T*t)-0.17194*cos(34*2*3.1415926536/T*t)+0.37268*sin(34*2*3.1415926536/T*t)+0.30663*cos(35*2*3.1415926536/T*t)+0.18876*sin(35*2*3.1415926536/T*t)+0.02879*cos(36*2*3.1415926536/T*t)-0.03278*sin(36*2*3.1415926536/T*t)+0.15678*cos(37*2*3.1415926536/T*t)-0.06819*sin(37*2*3.1415926536/T*t)+0.00782*cos(38*2*3.1415926536/T*t)-0.19751*sin(38*2*3.1415926536/T*t)-0.01646*cos(39*2*3.1415926536/T*t)+0.04615*sin(39*2*3.1415926536/T*t)+0.02522*cos(40*2*3.1415926536/T*t)+0.16196*sin(40*2*3.1415926536/T*t)+0.20191*cos(41*2*3.1415926536/T*t)+0.06460*sin(41*2*3.1415926536/T*t)+0.04317*cos(42*2*3.1415926536/T*t)-0.26841*sin(42*2*3.1415926536/T*t)-0.13192*cos(43*2*3.1415926536/T*t)-0.15846*sin(43*2*3.1415926536/T*t)-0.02724*cos(44*2*3.1415926536/T*t)+0.22194*sin(44*2*3.1415926536/T*t)+0.22168*cos(45*2*3.1415926536/T*t)-0.02610*sin(45*2*3.1415926536/T*t)-0.15175*cos(46*2*3.1415926536/T*t)-0.16211*sin(46*2*3.1415926536/T*t)+0.04363*cos(47*2*3.1415926536/T*t)+0.07853*sin(47*2*3.1415926536/T*t)+0.06699*cos(48*2*3.1415926536/T*t)-0.06167*sin(48*2*3.1415926536/T*t)-0.18369*cos(49*2*3.1415926536/T*t)+0.00415*sin(49*2*3.1415926536/T*t)+0.11779*cos(50*2*3.1415926536/T*t)+0.06437*sin(50*2*3.1415926536/T*t)+0.21310*cos(51*2*3.1415926536/T*t)-0.11809*sin(51*2*3.1415926536/T*t)-0.04893*cos(52*2*3.1415926536/T*t)-0.07114*sin(52*2*3.1415926536/T*t)-0.14610*cos(53*2*3.1415926536/T*t)+0.09284*sin(53*2*3.1415926536/T*t)+0.05538*cos(54*2*3.1415926536/T*t)+0.01905*sin(54*2*3.1415926536/T*t)-0.02914*cos(55*2*3.1415926536/T*t)-0.05310*sin(55*2*3.1415926536/T*t)
				  -0.00578*cos(56*2*3.1415926536/T*t)+0.07598*sin(56*2*3.1415926536/T*t)+0.12478*cos(57*2*3.1415926536/T*t)-0.05165*sin(57*2*3.1415926536/T*t)-0.02717*cos(58*2*3.1415926536/T*t)-0.12877*sin(58*2*3.1415926536/T*t)-0.04569*cos(59*2*3.1415926536/T*t)+0.13107*sin(59*2*3.1415926536/T*t)+0.12480*cos(60*2*3.1415926536/T*t)+0.05497*sin(60*2*3.1415926536/T*t)+0.09391*cos(61*2*3.1415926536/T*t)-0.06051*sin(61*2*3.1415926536/T*t)));
				  
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][2] = (float)(0.2*(6.53594-0.05637*cos(1*2*3.1415926536/T*t)+0.41411*sin(1*2*3.1415926536/T*t)-1.16771*cos(2*2*3.1415926536/T*t)+0.68455*sin(2*2*3.1415926536/T*t)-0.67330*cos(3*2*3.1415926536/T*t)-0.45578*sin(3*2*3.1415926536/T*t)+0.90705*cos(4*2*3.1415926536/T*t)-0.84155*sin(4*2*3.1415926536/T*t)-0.12031*cos(5*2*3.1415926536/T*t)-0.88101*sin(5*2*3.1415926536/T*t)-0.76608*cos(6*2*3.1415926536/T*t)+0.31381*sin(6*2*3.1415926536/T*t)-0.30138*cos(7*2*3.1415926536/T*t)-0.12159*sin(7*2*3.1415926536/T*t)-0.44274*cos(8*2*3.1415926536/T*t)+0.27687*sin(8*2*3.1415926536/T*t)-0.83423*cos(9*2*3.1415926536/T*t)+0.50831*sin(9*2*3.1415926536/T*t)+0.11855*cos(10*2*3.1415926536/T*t)+0.20012*sin(10*2*3.1415926536/T*t)-0.02081*cos(11*2*3.1415926536/T*t)-0.61691*sin(11*2*3.1415926536/T*t)-0.02941*cos(12*2*3.1415926536/T*t)+0.09226*sin(12*2*3.1415926536/T*t)-0.06418*cos(13*2*3.1415926536/T*t)+0.46131*sin(13*2*3.1415926536/T*t)-0.63557*cos(14*2*3.1415926536/T*t)-0.27082*sin(14*2*3.1415926536/T*t)-0.72214*cos(15*2*3.1415926536/T*t)+0.01619*sin(15*2*3.1415926536/T*t)+0.07442*cos(16*2*3.1415926536/T*t)+0.07123*sin(16*2*3.1415926536/T*t)+0.29491*cos(17*2*3.1415926536/T*t)-0.31810*sin(17*2*3.1415926536/T*t)+0.03876*cos(18*2*3.1415926536/T*t)+0.61791*sin(18*2*3.1415926536/T*t)-0.28882*cos(19*2*3.1415926536/T*t)+0.23213*sin(19*2*3.1415926536/T*t)+0.16348*cos(20*2*3.1415926536/T*t)-0.33167*sin(20*2*3.1415926536/T*t)-0.35595*cos(21*2*3.1415926536/T*t)-0.43936*sin(21*2*3.1415926536/T*t)-0.37993*cos(22*2*3.1415926536/T*t)+0.09940*sin(22*2*3.1415926536/T*t)+0.22724*cos(23*2*3.1415926536/T*t)+0.15658*sin(23*2*3.1415926536/T*t)+0.10967*cos(24*2*3.1415926536/T*t)-0.04978*sin(24*2*3.1415926536/T*t)-0.15266*cos(25*2*3.1415926536/T*t)+0.10506*sin(25*2*3.1415926536/T*t)+0.06587*cos(26*2*3.1415926536/T*t)+0.07932*sin(26*2*3.1415926536/T*t)+0.00311*cos(27*2*3.1415926536/T*t)-0.21258*sin(27*2*3.1415926536/T*t)+0.03427*cos(28*2*3.1415926536/T*t)
					+0.03433*sin(28*2*3.1415926536/T*t)-0.00777*cos(29*2*3.1415926536/T*t)-0.02875*sin(29*2*3.1415926536/T*t)-0.15049*cos(30*2*3.1415926536/T*t)-0.01896*sin(30*2*3.1415926536/T*t)-0.15171*cos(31*2*3.1415926536/T*t)+0.21027*sin(31*2*3.1415926536/T*t)+0.14356*cos(32*2*3.1415926536/T*t)+0.09148*sin(32*2*3.1415926536/T*t)+0.01756*cos(33*2*3.1415926536/T*t)+0.00721*sin(33*2*3.1415926536/T*t)-0.15446*cos(34*2*3.1415926536/T*t)-0.09701*sin(34*2*3.1415926536/T*t)-0.07795*cos(35*2*3.1415926536/T*t)+0.07833*sin(35*2*3.1415926536/T*t)-0.03949*cos(36*2*3.1415926536/T*t)+0.00607*sin(36*2*3.1415926536/T*t)-0.11331*cos(37*2*3.1415926536/T*t)-0.04384*sin(37*2*3.1415926536/T*t)-0.04237*cos(38*2*3.1415926536/T*t)-0.00313*sin(38*2*3.1415926536/T*t)-0.03607*cos(39*2*3.1415926536/T*t)+0.08406*sin(39*2*3.1415926536/T*t)-0.09745*cos(40*2*3.1415926536/T*t)+0.04549*sin(40*2*3.1415926536/T*t)+0.03571*cos(41*2*3.1415926536/T*t)+0.05683*sin(41*2*3.1415926536/T*t)-0.04853*cos(42*2*3.1415926536/T*t)-0.03202*sin(42*2*3.1415926536/T*t)-0.15103*cos(43*2*3.1415926536/T*t)-0.04929*sin(43*2*3.1415926536/T*t)+0.00883*cos(44*2*3.1415926536/T*t)+0.11661*sin(44*2*3.1415926536/T*t)+0.01335*cos(45*2*3.1415926536/T*t)-0.01748*sin(45*2*3.1415926536/T*t)-0.05615*cos(46*2*3.1415926536/T*t)-0.07479*sin(46*2*3.1415926536/T*t)-0.04815*cos(47*2*3.1415926536/T*t)-0.00390*sin(47*2*3.1415926536/T*t)-0.04888*cos(48*2*3.1415926536/T*t)-0.03673*sin(48*2*3.1415926536/T*t)-0.13565*cos(49*2*3.1415926536/T*t)+0.00276*sin(49*2*3.1415926536/T*t)+0.01106*cos(50*2*3.1415926536/T*t)+0.05614*sin(50*2*3.1415926536/T*t)+0.07472*cos(51*2*3.1415926536/T*t)-0.03524*sin(51*2*3.1415926536/T*t)-0.08185*cos(52*2*3.1415926536/T*t)+0.00787*sin(52*2*3.1415926536/T*t)-0.08873*cos(53*2*3.1415926536/T*t)+0.00111*sin(53*2*3.1415926536/T*t)-0.02182*cos(54*2*3.1415926536/T*t)-0.02921*sin(54*2*3.1415926536/T*t)-0.11021*cos(55*2*3.1415926536/T*t)-0.01837*sin(55*2*3.1415926536/T*t)
					-0.09339*cos(56*2*3.1415926536/T*t)-0.00025*sin(56*2*3.1415926536/T*t)-0.04273*cos(57*2*3.1415926536/T*t)+0.05575*sin(57*2*3.1415926536/T*t)-0.03628*cos(58*2*3.1415926536/T*t)-0.00730*sin(58*2*3.1415926536/T*t)-0.06357*cos(59*2*3.1415926536/T*t)+0.07053*sin(59*2*3.1415926536/T*t)+0.02051*cos(60*2*3.1415926536/T*t)+0.05823*sin(60*2*3.1415926536/T*t)+0.01107*cos(61*2*3.1415926536/T*t)-0.04690*sin(61*2*3.1415926536/T*t)));
					
					  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][3] = (float)(0.8*(50.25943-3.71405*cos(1*2*3.1415926536/T*t)+19.00386*sin(1*2*3.1415926536/T*t)+5.77671*cos(2*2*3.1415926536/T*t)+11.67729*sin(2*2*3.1415926536/T*t)-9.47892*cos(3*2*3.1415926536/T*t)-7.28290*sin(3*2*3.1415926536/T*t)+0.71253*cos(4*2*3.1415926536/T*t)+10.45979*sin(4*2*3.1415926536/T*t)-17.96951*cos(5*2*3.1415926536/T*t)-0.96084*sin(5*2*3.1415926536/T*t)-10.51620*cos(6*2*3.1415926536/T*t)+18.41199*sin(6*2*3.1415926536/T*t)+9.66822*cos(7*2*3.1415926536/T*t)-4.35870*sin(7*2*3.1415926536/T*t)-6.07224*cos(8*2*3.1415926536/T*t)+6.60145*sin(8*2*3.1415926536/T*t)-0.85310*cos(9*2*3.1415926536/T*t)+4.56331*sin(9*2*3.1415926536/T*t)-9.23511*cos(10*2*3.1415926536/T*t)-8.08258*sin(10*2*3.1415926536/T*t)-13.13606*cos(11*2*3.1415926536/T*t)-6.86320*sin(11*2*3.1415926536/T*t)-9.46198*cos(12*2*3.1415926536/T*t)+8.00700*sin(12*2*3.1415926536/T*t)+4.56104*cos(13*2*3.1415926536/T*t)-0.22052*sin(13*2*3.1415926536/T*t)-0.18340*cos(14*2*3.1415926536/T*t)-5.14959*sin(14*2*3.1415926536/T*t)+3.40377*cos(15*2*3.1415926536/T*t)+0.75458*sin(15*2*3.1415926536/T*t)+0.28495*cos(16*2*3.1415926536/T*t)+0.29433*sin(16*2*3.1415926536/T*t)+1.36893*cos(17*2*3.1415926536/T*t)-2.52915*sin(17*2*3.1415926536/T*t)-1.84440*cos(18*2*3.1415926536/T*t)-4.10721*sin(18*2*3.1415926536/T*t)-0.85098*cos(19*2*3.1415926536/T*t)-2.60764*sin(19*2*3.1415926536/T*t)-2.67287*cos(20*2*3.1415926536/T*t)-1.11344*sin(20*2*3.1415926536/T*t)+0.72310*cos(21*2*3.1415926536/T*t)+1.76967*sin(21*2*3.1415926536/T*t)+1.66748*cos(22*2*3.1415926536/T*t)-1.01544*sin(22*2*3.1415926536/T*t)+0.73988*cos(23*2*3.1415926536/T*t)-3.21065*sin(23*2*3.1415926536/T*t)-2.60879*cos(24*2*3.1415926536/T*t)+0.78029*sin(24*2*3.1415926536/T*t)+2.39778*cos(25*2*3.1415926536/T*t)+1.56804*sin(25*2*3.1415926536/T*t)+0.46825*cos(26*2*3.1415926536/T*t)-1.66227*sin(26*2*3.1415926536/T*t)+1.33196*cos(27*2*3.1415926536/T*t)-0.84323*sin(27*2*3.1415926536/T*t)-0.42586*cos(28*2*3.1415926536/T*t)
					  -1.58054*sin(28*2*3.1415926536/T*t)+0.07545*cos(29*2*3.1415926536/T*t)-0.77776*sin(29*2*3.1415926536/T*t)-1.32499*cos(30*2*3.1415926536/T*t)-0.20743*sin(30*2*3.1415926536/T*t)+1.65442*cos(31*2*3.1415926536/T*t)+0.89544*sin(31*2*3.1415926536/T*t)+0.13340*cos(32*2*3.1415926536/T*t)-0.46735*sin(32*2*3.1415926536/T*t)+0.27011*cos(33*2*3.1415926536/T*t)+1.38262*sin(33*2*3.1415926536/T*t)+1.03708*cos(34*2*3.1415926536/T*t)+0.32098*sin(34*2*3.1415926536/T*t)+1.20849*cos(35*2*3.1415926536/T*t)+0.13427*sin(35*2*3.1415926536/T*t)+0.10868*cos(36*2*3.1415926536/T*t)-0.35855*sin(36*2*3.1415926536/T*t)+0.37684*cos(37*2*3.1415926536/T*t)+0.03989*sin(37*2*3.1415926536/T*t)+0.05925*cos(38*2*3.1415926536/T*t)-0.26364*sin(38*2*3.1415926536/T*t)+0.27260*cos(39*2*3.1415926536/T*t)+0.63688*sin(39*2*3.1415926536/T*t)+0.68952*cos(40*2*3.1415926536/T*t)+0.51761*sin(40*2*3.1415926536/T*t)+0.63767*cos(41*2*3.1415926536/T*t)-0.16186*sin(41*2*3.1415926536/T*t)-0.33616*cos(42*2*3.1415926536/T*t)-0.38753*sin(42*2*3.1415926536/T*t)+0.21854*cos(43*2*3.1415926536/T*t)+0.69883*sin(43*2*3.1415926536/T*t)+0.23679*cos(44*2*3.1415926536/T*t)+0.16226*sin(44*2*3.1415926536/T*t)+0.25532*cos(45*2*3.1415926536/T*t)+0.04381*sin(45*2*3.1415926536/T*t)+0.29773*cos(46*2*3.1415926536/T*t)-0.38097*sin(46*2*3.1415926536/T*t)+0.24172*cos(47*2*3.1415926536/T*t)+0.10824*sin(47*2*3.1415926536/T*t)+0.10034*cos(48*2*3.1415926536/T*t)-0.18254*sin(48*2*3.1415926536/T*t)-0.01544*cos(49*2*3.1415926536/T*t)+0.50552*sin(49*2*3.1415926536/T*t)+0.29473*cos(50*2*3.1415926536/T*t)+0.01015*sin(50*2*3.1415926536/T*t)-0.09943*cos(51*2*3.1415926536/T*t)+0.19478*sin(51*2*3.1415926536/T*t)-0.03461*cos(52*2*3.1415926536/T*t)+0.25668*sin(52*2*3.1415926536/T*t)-0.08363*cos(53*2*3.1415926536/T*t)+0.13012*sin(53*2*3.1415926536/T*t)+0.11807*cos(54*2*3.1415926536/T*t)-0.25707*sin(54*2*3.1415926536/T*t)-0.07737*cos(55*2*3.1415926536/T*t)-0.11941*sin(55*2*3.1415926536/T*t)
					  -0.09317*cos(56*2*3.1415926536/T*t)+0.08442*sin(56*2*3.1415926536/T*t)-0.20823*cos(57*2*3.1415926536/T*t)+0.23422*sin(57*2*3.1415926536/T*t)-0.07856*cos(58*2*3.1415926536/T*t)+0.09341*sin(58*2*3.1415926536/T*t)-0.03018*cos(59*2*3.1415926536/T*t)-0.03276*sin(59*2*3.1415926536/T*t)+0.06610*cos(60*2*3.1415926536/T*t)-0.05726*sin(60*2*3.1415926536/T*t)-0.31162*cos(61*2*3.1415926536/T*t)-0.13899*sin(61*2*3.1415926536/T*t)));
					  
						theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][4] = (float)(0.8*(-13.04009-1.09522*cos(1*2*3.1415926536/T*t)+7.07506*sin(1*2*3.1415926536/T*t)-0.98415*cos(2*2*3.1415926536/T*t)-0.65249*sin(2*2*3.1415926536/T*t)+1.90588*cos(3*2*3.1415926536/T*t)+1.10241*sin(3*2*3.1415926536/T*t)-0.00755*cos(4*2*3.1415926536/T*t)-1.88256*sin(4*2*3.1415926536/T*t)+0.24441*cos(5*2*3.1415926536/T*t)+0.43430*sin(5*2*3.1415926536/T*t)-0.10264*cos(6*2*3.1415926536/T*t)+3.45285*sin(6*2*3.1415926536/T*t)+2.45179*cos(7*2*3.1415926536/T*t)-0.80376*sin(7*2*3.1415926536/T*t)-5.14179*cos(8*2*3.1415926536/T*t)-5.13632*sin(8*2*3.1415926536/T*t)+2.45864*cos(9*2*3.1415926536/T*t)+1.77040*sin(9*2*3.1415926536/T*t)+0.54700*cos(10*2*3.1415926536/T*t)-1.97099*sin(10*2*3.1415926536/T*t)-2.83424*cos(11*2*3.1415926536/T*t)+1.89808*sin(11*2*3.1415926536/T*t)-1.01876*cos(12*2*3.1415926536/T*t)+2.54258*sin(12*2*3.1415926536/T*t)+4.41334*cos(13*2*3.1415926536/T*t)+3.22875*sin(13*2*3.1415926536/T*t)+0.97385*cos(14*2*3.1415926536/T*t)-2.81153*sin(14*2*3.1415926536/T*t)+1.92621*cos(15*2*3.1415926536/T*t)-0.42450*sin(15*2*3.1415926536/T*t)+1.47769*cos(16*2*3.1415926536/T*t)-3.02159*sin(16*2*3.1415926536/T*t)+0.73929*cos(17*2*3.1415926536/T*t)-1.30521*sin(17*2*3.1415926536/T*t)-1.89261*cos(18*2*3.1415926536/T*t)-1.85351*sin(18*2*3.1415926536/T*t)+0.17554*cos(19*2*3.1415926536/T*t)+1.66910*sin(19*2*3.1415926536/T*t)+0.39061*cos(20*2*3.1415926536/T*t)-1.02310*sin(20*2*3.1415926536/T*t)+0.82494*cos(21*2*3.1415926536/T*t)+1.73123*sin(21*2*3.1415926536/T*t)+1.57281*cos(22*2*3.1415926536/T*t)-0.78284*sin(22*2*3.1415926536/T*t)+1.08363*cos(23*2*3.1415926536/T*t)-0.87262*sin(23*2*3.1415926536/T*t)-0.28271*cos(24*2*3.1415926536/T*t)-1.38012*sin(24*2*3.1415926536/T*t)-0.30883*cos(25*2*3.1415926536/T*t)+0.38473*sin(25*2*3.1415926536/T*t)-0.31527*cos(26*2*3.1415926536/T*t)-0.78876*sin(26*2*3.1415926536/T*t)-0.16056*cos(27*2*3.1415926536/T*t)+0.58374*sin(27*2*3.1415926536/T*t)+0.56608*cos(28*2*3.1415926536/T*t)
						-0.09761*sin(28*2*3.1415926536/T*t)+0.29019*cos(29*2*3.1415926536/T*t)-0.06134*sin(29*2*3.1415926536/T*t)+0.09601*cos(30*2*3.1415926536/T*t)+0.42523*sin(30*2*3.1415926536/T*t)+0.57480*cos(31*2*3.1415926536/T*t)-0.09779*sin(31*2*3.1415926536/T*t)+0.12002*cos(32*2*3.1415926536/T*t)-0.78817*sin(32*2*3.1415926536/T*t)-0.08517*cos(33*2*3.1415926536/T*t)+0.49152*sin(33*2*3.1415926536/T*t)+0.30250*cos(34*2*3.1415926536/T*t)+0.32597*sin(34*2*3.1415926536/T*t)+0.33681*cos(35*2*3.1415926536/T*t)-0.26152*sin(35*2*3.1415926536/T*t)+0.13060*cos(36*2*3.1415926536/T*t)-0.13220*sin(36*2*3.1415926536/T*t)+0.07957*cos(37*2*3.1415926536/T*t)+0.48852*sin(37*2*3.1415926536/T*t)+0.66585*cos(38*2*3.1415926536/T*t)-0.05175*sin(38*2*3.1415926536/T*t)-0.12027*cos(39*2*3.1415926536/T*t)+0.00468*sin(39*2*3.1415926536/T*t)+0.60297*cos(40*2*3.1415926536/T*t)+0.22158*sin(40*2*3.1415926536/T*t)+0.29748*cos(41*2*3.1415926536/T*t)-0.52012*sin(41*2*3.1415926536/T*t)-0.00600*cos(42*2*3.1415926536/T*t)-0.08397*sin(42*2*3.1415926536/T*t)+0.04456*cos(43*2*3.1415926536/T*t)-0.15335*sin(43*2*3.1415926536/T*t)+0.10635*cos(44*2*3.1415926536/T*t)-0.14049*sin(44*2*3.1415926536/T*t)-0.20130*cos(45*2*3.1415926536/T*t)+0.10775*sin(45*2*3.1415926536/T*t)+0.17224*cos(46*2*3.1415926536/T*t)+0.32164*sin(46*2*3.1415926536/T*t)+0.32987*cos(47*2*3.1415926536/T*t)+0.16240*sin(47*2*3.1415926536/T*t)+0.21421*cos(48*2*3.1415926536/T*t)-0.00717*sin(48*2*3.1415926536/T*t)+0.13071*cos(49*2*3.1415926536/T*t)+0.05164*sin(49*2*3.1415926536/T*t)+0.20223*cos(50*2*3.1415926536/T*t)-0.15441*sin(50*2*3.1415926536/T*t)-0.15818*cos(51*2*3.1415926536/T*t)-0.05928*sin(51*2*3.1415926536/T*t)+0.16457*cos(52*2*3.1415926536/T*t)+0.18567*sin(52*2*3.1415926536/T*t)+0.16151*cos(53*2*3.1415926536/T*t)+0.03150*sin(53*2*3.1415926536/T*t)+0.02236*cos(54*2*3.1415926536/T*t)+0.10002*sin(54*2*3.1415926536/T*t)+0.12762*cos(55*2*3.1415926536/T*t)
						+0.12625*sin(55*2*3.1415926536/T*t)+0.29439*cos(56*2*3.1415926536/T*t)+0.02418*sin(56*2*3.1415926536/T*t)+0.06734*cos(57*2*3.1415926536/T*t)-0.15417*sin(57*2*3.1415926536/T*t)-0.00241*cos(58*2*3.1415926536/T*t)+0.12557*sin(58*2*3.1415926536/T*t)+0.22558*cos(59*2*3.1415926536/T*t)-0.09289*sin(59*2*3.1415926536/T*t)+0.07671*cos(60*2*3.1415926536/T*t)-0.03651*sin(60*2*3.1415926536/T*t)+0.16896*cos(61*2*3.1415926536/T*t)+0.03736*sin(61*2*3.1415926536/T*t)));
						
						  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][5] = (float)(0.8*(49.11733-5.90033*cos(1*2*3.1415926536/T*t)-2.09627*sin(1*2*3.1415926536/T*t)+5.76104*cos(2*2*3.1415926536/T*t)-5.41178*sin(2*2*3.1415926536/T*t)+10.87645*cos(3*2*3.1415926536/T*t)+2.71667*sin(3*2*3.1415926536/T*t)-4.39945*cos(4*2*3.1415926536/T*t)+1.35877*sin(4*2*3.1415926536/T*t)-4.56918*cos(5*2*3.1415926536/T*t)+0.22586*sin(5*2*3.1415926536/T*t)-11.79206*cos(6*2*3.1415926536/T*t)+4.28636*sin(6*2*3.1415926536/T*t)+7.77605*cos(7*2*3.1415926536/T*t)-1.11984*sin(7*2*3.1415926536/T*t)-5.57093*cos(8*2*3.1415926536/T*t)-1.30277*sin(8*2*3.1415926536/T*t)+1.72605*cos(9*2*3.1415926536/T*t)+8.47755*sin(9*2*3.1415926536/T*t)-11.51203*cos(10*2*3.1415926536/T*t)-1.39469*sin(10*2*3.1415926536/T*t)-6.53940*cos(11*2*3.1415926536/T*t)+2.14658*sin(11*2*3.1415926536/T*t)-8.21363*cos(12*2*3.1415926536/T*t)+1.07122*sin(12*2*3.1415926536/T*t)+3.49372*cos(13*2*3.1415926536/T*t)+4.88037*sin(13*2*3.1415926536/T*t)-0.18664*cos(14*2*3.1415926536/T*t)-6.21913*sin(14*2*3.1415926536/T*t)+2.37176*cos(15*2*3.1415926536/T*t)-1.78052*sin(15*2*3.1415926536/T*t)-1.63611*cos(16*2*3.1415926536/T*t)-0.54756*sin(16*2*3.1415926536/T*t)+1.28532*cos(17*2*3.1415926536/T*t)-0.28397*sin(17*2*3.1415926536/T*t)-6.75824*cos(18*2*3.1415926536/T*t)-4.49109*sin(18*2*3.1415926536/T*t)-0.95966*cos(19*2*3.1415926536/T*t)+0.18116*sin(19*2*3.1415926536/T*t)-4.61373*cos(20*2*3.1415926536/T*t)+0.16282*sin(20*2*3.1415926536/T*t)+2.32679*cos(21*2*3.1415926536/T*t)+4.12295*sin(21*2*3.1415926536/T*t)-1.12255*cos(22*2*3.1415926536/T*t)-2.35813*sin(22*2*3.1415926536/T*t)+1.47350*cos(23*2*3.1415926536/T*t)+1.10104*sin(23*2*3.1415926536/T*t)-1.14019*cos(24*2*3.1415926536/T*t)-2.09827*sin(24*2*3.1415926536/T*t)+0.37480*cos(25*2*3.1415926536/T*t)+1.35257*sin(25*2*3.1415926536/T*t)-1.34432*cos(26*2*3.1415926536/T*t)-1.00283*sin(26*2*3.1415926536/T*t)+0.22089*cos(27*2*3.1415926536/T*t)-1.21946*sin(27*2*3.1415926536/T*t)-2.96084*cos(28*2*3.1415926536/T*t)
						  -1.66253*sin(28*2*3.1415926536/T*t)-0.47439*cos(29*2*3.1415926536/T*t)+1.00328*sin(29*2*3.1415926536/T*t)-1.72306*cos(30*2*3.1415926536/T*t)+0.13067*sin(30*2*3.1415926536/T*t)+1.55591*cos(31*2*3.1415926536/T*t)+0.74577*sin(31*2*3.1415926536/T*t)-0.53223*cos(32*2*3.1415926536/T*t)-0.65518*sin(32*2*3.1415926536/T*t)+1.02174*cos(33*2*3.1415926536/T*t)+1.59160*sin(33*2*3.1415926536/T*t)+0.06420*cos(34*2*3.1415926536/T*t)-0.49061*sin(34*2*3.1415926536/T*t)+0.47348*cos(35*2*3.1415926536/T*t)+0.07004*sin(35*2*3.1415926536/T*t)-0.58422*cos(36*2*3.1415926536/T*t)-0.57983*sin(36*2*3.1415926536/T*t)-0.36155*cos(37*2*3.1415926536/T*t)-0.06693*sin(37*2*3.1415926536/T*t)-1.24143*cos(38*2*3.1415926536/T*t)+0.08322*sin(38*2*3.1415926536/T*t)+0.54936*cos(39*2*3.1415926536/T*t)+1.42566*sin(39*2*3.1415926536/T*t)-0.15132*cos(40*2*3.1415926536/T*t)+0.17926*sin(40*2*3.1415926536/T*t)-0.02509*cos(41*2*3.1415926536/T*t)+0.41522*sin(41*2*3.1415926536/T*t)-0.28338*cos(42*2*3.1415926536/T*t)-0.23932*sin(42*2*3.1415926536/T*t)-0.01994*cos(43*2*3.1415926536/T*t)+0.35156*sin(43*2*3.1415926536/T*t)-0.50710*cos(44*2*3.1415926536/T*t)-0.00612*sin(44*2*3.1415926536/T*t)-0.01879*cos(45*2*3.1415926536/T*t)+0.12599*sin(45*2*3.1415926536/T*t)-0.39090*cos(46*2*3.1415926536/T*t)-0.74217*sin(46*2*3.1415926536/T*t)-0.54267*cos(47*2*3.1415926536/T*t)-0.02588*sin(47*2*3.1415926536/T*t)-0.44626*cos(48*2*3.1415926536/T*t)+0.23531*sin(48*2*3.1415926536/T*t)-0.03872*cos(49*2*3.1415926536/T*t)+0.28792*sin(49*2*3.1415926536/T*t)-0.25313*cos(50*2*3.1415926536/T*t)-0.33036*sin(50*2*3.1415926536/T*t)-0.06210*cos(51*2*3.1415926536/T*t)+0.42888*sin(51*2*3.1415926536/T*t)-0.12132*cos(52*2*3.1415926536/T*t)+0.19004*sin(52*2*3.1415926536/T*t)-0.54463*cos(53*2*3.1415926536/T*t)+0.01356*sin(53*2*3.1415926536/T*t)-0.32177*cos(54*2*3.1415926536/T*t)-0.17055*sin(54*2*3.1415926536/T*t)-0.18042*cos(55*2*3.1415926536/T*t)-0.28892*sin(55*2*3.1415926536/T*t)
						  -0.79133*cos(56*2*3.1415926536/T*t)-0.09978*sin(56*2*3.1415926536/T*t)-0.48044*cos(57*2*3.1415926536/T*t)+0.28116*sin(57*2*3.1415926536/T*t)-0.22652*cos(58*2*3.1415926536/T*t)+0.06217*sin(58*2*3.1415926536/T*t)-0.28825*cos(59*2*3.1415926536/T*t)-0.02328*sin(59*2*3.1415926536/T*t)-0.29098*cos(60*2*3.1415926536/T*t)+0.07374*sin(60*2*3.1415926536/T*t)-0.34716*cos(61*2*3.1415926536/T*t)-0.01379*sin(61*2*3.1415926536/T*t)));
						  
							theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][6] = (float)(0.8*(20.36956-1.93823*cos(1*2*3.1415926536/T*t)-7.43090*sin(1*2*3.1415926536/T*t)-10.85462*cos(2*2*3.1415926536/T*t)-0.47428*sin(2*2*3.1415926536/T*t)-3.56281*cos(3*2*3.1415926536/T*t)+0.36973*sin(3*2*3.1415926536/T*t)+0.43200*cos(4*2*3.1415926536/T*t)+8.44758*sin(4*2*3.1415926536/T*t)+0.88524*cos(5*2*3.1415926536/T*t)+0.68708*sin(5*2*3.1415926536/T*t)-2.52328*cos(6*2*3.1415926536/T*t)-3.13461*sin(6*2*3.1415926536/T*t)+7.48918*cos(7*2*3.1415926536/T*t)-7.96063*sin(7*2*3.1415926536/T*t)-0.57495*cos(8*2*3.1415926536/T*t)+1.81304*sin(8*2*3.1415926536/T*t)+1.14913*cos(9*2*3.1415926536/T*t)-0.47445*sin(9*2*3.1415926536/T*t)-7.74667*cos(10*2*3.1415926536/T*t)-1.77230*sin(10*2*3.1415926536/T*t)+1.27364*cos(11*2*3.1415926536/T*t)+4.83831*sin(11*2*3.1415926536/T*t)-0.36000*cos(12*2*3.1415926536/T*t)+1.85183*sin(12*2*3.1415926536/T*t)+1.72084*cos(13*2*3.1415926536/T*t)+1.64599*sin(13*2*3.1415926536/T*t)+1.51894*cos(14*2*3.1415926536/T*t)+1.77876*sin(14*2*3.1415926536/T*t)+0.60629*cos(15*2*3.1415926536/T*t)+0.34929*sin(15*2*3.1415926536/T*t)-1.69877*cos(16*2*3.1415926536/T*t)+1.00454*sin(16*2*3.1415926536/T*t)-0.50401*cos(17*2*3.1415926536/T*t)-0.39040*sin(17*2*3.1415926536/T*t)-3.56409*cos(18*2*3.1415926536/T*t)+2.28988*sin(18*2*3.1415926536/T*t)+1.18413*cos(19*2*3.1415926536/T*t)+0.58872*sin(19*2*3.1415926536/T*t)-0.92121*cos(20*2*3.1415926536/T*t)-0.13950*sin(20*2*3.1415926536/T*t)+1.22597*cos(21*2*3.1415926536/T*t)+0.94182*sin(21*2*3.1415926536/T*t)-0.92265*cos(22*2*3.1415926536/T*t)+0.39140*sin(22*2*3.1415926536/T*t)-0.49469*cos(23*2*3.1415926536/T*t)+0.17971*sin(23*2*3.1415926536/T*t)+0.24453*cos(24*2*3.1415926536/T*t)+0.17192*sin(24*2*3.1415926536/T*t)+0.80485*cos(25*2*3.1415926536/T*t)+0.04065*sin(25*2*3.1415926536/T*t)-0.52419*cos(26*2*3.1415926536/T*t)+1.10580*sin(26*2*3.1415926536/T*t)+1.07411*cos(27*2*3.1415926536/T*t)-0.55323*sin(27*2*3.1415926536/T*t)-0.66840*cos(28*2*3.1415926536/T*t)
							-0.28766*sin(28*2*3.1415926536/T*t)-0.70009*cos(29*2*3.1415926536/T*t)+0.45952*sin(29*2*3.1415926536/T*t)-0.43968*cos(30*2*3.1415926536/T*t)-0.00195*sin(30*2*3.1415926536/T*t)+0.27972*cos(31*2*3.1415926536/T*t)+0.49911*sin(31*2*3.1415926536/T*t)+0.17108*cos(32*2*3.1415926536/T*t)+0.67576*sin(32*2*3.1415926536/T*t)+0.30625*cos(33*2*3.1415926536/T*t)-0.51654*sin(33*2*3.1415926536/T*t)+0.28028*cos(34*2*3.1415926536/T*t)-0.35384*sin(34*2*3.1415926536/T*t)-0.57716*cos(35*2*3.1415926536/T*t)-0.62632*sin(35*2*3.1415926536/T*t)-0.73907*cos(36*2*3.1415926536/T*t)-0.22767*sin(36*2*3.1415926536/T*t)+0.00901*cos(37*2*3.1415926536/T*t)-0.29486*sin(37*2*3.1415926536/T*t)-0.49870*cos(38*2*3.1415926536/T*t)+0.14215*sin(38*2*3.1415926536/T*t)+0.11829*cos(39*2*3.1415926536/T*t)+0.37267*sin(39*2*3.1415926536/T*t)+0.32024*cos(40*2*3.1415926536/T*t)-0.04943*sin(40*2*3.1415926536/T*t)-0.22285*cos(41*2*3.1415926536/T*t)+0.04306*sin(41*2*3.1415926536/T*t)-0.04195*cos(42*2*3.1415926536/T*t)-0.46467*sin(42*2*3.1415926536/T*t)-0.17229*cos(43*2*3.1415926536/T*t)-0.07317*sin(43*2*3.1415926536/T*t)+0.04068*cos(44*2*3.1415926536/T*t)+0.02630*sin(44*2*3.1415926536/T*t)-0.31304*cos(45*2*3.1415926536/T*t)+0.09928*sin(45*2*3.1415926536/T*t)-0.03743*cos(46*2*3.1415926536/T*t)-0.13274*sin(46*2*3.1415926536/T*t)-0.32082*cos(47*2*3.1415926536/T*t)-0.12428*sin(47*2*3.1415926536/T*t)-0.03624*cos(48*2*3.1415926536/T*t)-0.04936*sin(48*2*3.1415926536/T*t)-0.35859*cos(49*2*3.1415926536/T*t)+0.05294*sin(49*2*3.1415926536/T*t)-0.07699*cos(50*2*3.1415926536/T*t)+0.02183*sin(50*2*3.1415926536/T*t)+0.01530*cos(51*2*3.1415926536/T*t)+0.05454*sin(51*2*3.1415926536/T*t)+0.08873*cos(52*2*3.1415926536/T*t)-0.01721*sin(52*2*3.1415926536/T*t)-0.01631*cos(53*2*3.1415926536/T*t)-0.15124*sin(53*2*3.1415926536/T*t)-0.00635*cos(54*2*3.1415926536/T*t)-0.09825*sin(54*2*3.1415926536/T*t)-0.01956*cos(55*2*3.1415926536/T*t)-0.03149*sin(55*2*3.1415926536/T*t)
							-0.13190*cos(56*2*3.1415926536/T*t)-0.10685*sin(56*2*3.1415926536/T*t)-0.01066*cos(57*2*3.1415926536/T*t)+0.11530*sin(57*2*3.1415926536/T*t)-0.03213*cos(58*2*3.1415926536/T*t)+0.06695*sin(58*2*3.1415926536/T*t)+0.02200*cos(59*2*3.1415926536/T*t)+0.02358*sin(59*2*3.1415926536/T*t)+0.02083*cos(60*2*3.1415926536/T*t)-0.04709*sin(60*2*3.1415926536/T*t)-0.04041*cos(61*2*3.1415926536/T*t)-0.01350*sin(61*2*3.1415926536/T*t)));
							
							  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][7] = (float)(0.8*(-8.66402+16.87444*cos(1*2*3.1415926536/T*t)+11.73329*sin(1*2*3.1415926536/T*t)-7.39558*cos(2*2*3.1415926536/T*t)+23.37325*sin(2*2*3.1415926536/T*t)-11.37133*cos(3*2*3.1415926536/T*t)-11.46970*sin(3*2*3.1415926536/T*t)+2.27164*cos(4*2*3.1415926536/T*t)+16.17104*sin(4*2*3.1415926536/T*t)-34.83780*cos(5*2*3.1415926536/T*t)+2.09626*sin(5*2*3.1415926536/T*t)-6.60861*cos(6*2*3.1415926536/T*t)+14.28425*sin(6*2*3.1415926536/T*t)+26.20266*cos(7*2*3.1415926536/T*t)-0.17167*sin(7*2*3.1415926536/T*t)+5.80496*cos(8*2*3.1415926536/T*t)-2.02389*sin(8*2*3.1415926536/T*t)-1.24389*cos(9*2*3.1415926536/T*t)+4.26436*sin(9*2*3.1415926536/T*t)+7.70098*cos(10*2*3.1415926536/T*t)-6.93694*sin(10*2*3.1415926536/T*t)-8.72565*cos(11*2*3.1415926536/T*t)-5.42855*sin(11*2*3.1415926536/T*t)-2.52086*cos(12*2*3.1415926536/T*t)+0.62231*sin(12*2*3.1415926536/T*t)+0.22865*cos(13*2*3.1415926536/T*t)+4.39424*sin(13*2*3.1415926536/T*t)+1.64295*cos(14*2*3.1415926536/T*t)+1.10291*sin(14*2*3.1415926536/T*t)-0.82330*cos(15*2*3.1415926536/T*t)-0.50405*sin(15*2*3.1415926536/T*t)+1.43046*cos(16*2*3.1415926536/T*t)+3.05714*sin(16*2*3.1415926536/T*t)-0.75455*cos(17*2*3.1415926536/T*t)+0.24796*sin(17*2*3.1415926536/T*t)-3.84097*cos(18*2*3.1415926536/T*t)-1.43282*sin(18*2*3.1415926536/T*t)+1.95251*cos(19*2*3.1415926536/T*t)+2.71988*sin(19*2*3.1415926536/T*t)+0.66749*cos(20*2*3.1415926536/T*t)-2.20535*sin(20*2*3.1415926536/T*t)+0.10256*cos(21*2*3.1415926536/T*t)+0.05268*sin(21*2*3.1415926536/T*t)+2.30759*cos(22*2*3.1415926536/T*t)+0.41857*sin(22*2*3.1415926536/T*t)-0.60757*cos(23*2*3.1415926536/T*t)-3.35690*sin(23*2*3.1415926536/T*t)-2.66775*cos(24*2*3.1415926536/T*t)-1.21510*sin(24*2*3.1415926536/T*t)+1.89651*cos(25*2*3.1415926536/T*t)+1.90544*sin(25*2*3.1415926536/T*t)+0.56129*cos(26*2*3.1415926536/T*t)-1.03979*sin(26*2*3.1415926536/T*t)+0.34256*cos(27*2*3.1415926536/T*t)-1.69937*sin(27*2*3.1415926536/T*t)+0.88762*cos(28*2*3.1415926536/T*t)
							  +1.17864*sin(28*2*3.1415926536/T*t)-0.02852*cos(29*2*3.1415926536/T*t)-0.19316*sin(29*2*3.1415926536/T*t)+0.45868*cos(30*2*3.1415926536/T*t)-1.29371*sin(30*2*3.1415926536/T*t)+1.01322*cos(31*2*3.1415926536/T*t)-0.28524*sin(31*2*3.1415926536/T*t)+0.53455*cos(32*2*3.1415926536/T*t)+1.04753*sin(32*2*3.1415926536/T*t)+0.07257*cos(33*2*3.1415926536/T*t)-1.89453*sin(33*2*3.1415926536/T*t)+1.35647*cos(34*2*3.1415926536/T*t)+0.71977*sin(34*2*3.1415926536/T*t)+1.23537*cos(35*2*3.1415926536/T*t)-1.03544*sin(35*2*3.1415926536/T*t)-0.61028*cos(36*2*3.1415926536/T*t)-1.28111*sin(36*2*3.1415926536/T*t)+0.26086*cos(37*2*3.1415926536/T*t)+0.44973*sin(37*2*3.1415926536/T*t)+1.27929*cos(38*2*3.1415926536/T*t)-0.27475*sin(38*2*3.1415926536/T*t)-0.29642*cos(39*2*3.1415926536/T*t)-1.25661*sin(39*2*3.1415926536/T*t)+1.55363*cos(40*2*3.1415926536/T*t)+0.55610*sin(40*2*3.1415926536/T*t)+0.64168*cos(41*2*3.1415926536/T*t)-0.14781*sin(41*2*3.1415926536/T*t)+0.66911*cos(42*2*3.1415926536/T*t)-0.89690*sin(42*2*3.1415926536/T*t)+0.52585*cos(43*2*3.1415926536/T*t)-0.06055*sin(43*2*3.1415926536/T*t)+1.67068*cos(44*2*3.1415926536/T*t)+0.73778*sin(44*2*3.1415926536/T*t)+0.54556*cos(45*2*3.1415926536/T*t)-0.77631*sin(45*2*3.1415926536/T*t)+0.34606*cos(46*2*3.1415926536/T*t)-0.38570*sin(46*2*3.1415926536/T*t)+0.61845*cos(47*2*3.1415926536/T*t)+0.26231*sin(47*2*3.1415926536/T*t)+0.96216*cos(48*2*3.1415926536/T*t)-0.48463*sin(48*2*3.1415926536/T*t)+0.30573*cos(49*2*3.1415926536/T*t)+0.11243*sin(49*2*3.1415926536/T*t)+0.62729*cos(50*2*3.1415926536/T*t)+0.29194*sin(50*2*3.1415926536/T*t)+0.29496*cos(51*2*3.1415926536/T*t)-0.22155*sin(51*2*3.1415926536/T*t)+0.55617*cos(52*2*3.1415926536/T*t)+0.35227*sin(52*2*3.1415926536/T*t)+0.98171*cos(53*2*3.1415926536/T*t)+0.35889*sin(53*2*3.1415926536/T*t)+0.60777*cos(54*2*3.1415926536/T*t)-0.56030*sin(54*2*3.1415926536/T*t)+0.11647*cos(55*2*3.1415926536/T*t)+0.01134*sin(55*2*3.1415926536/T*t)
							  +0.35072*cos(56*2*3.1415926536/T*t)+0.44471*sin(56*2*3.1415926536/T*t)+0.80767*cos(57*2*3.1415926536/T*t)+0.13521*sin(57*2*3.1415926536/T*t)+0.53425*cos(58*2*3.1415926536/T*t)-0.07574*sin(58*2*3.1415926536/T*t)+0.29301*cos(59*2*3.1415926536/T*t)+0.21297*sin(59*2*3.1415926536/T*t)+0.55746*cos(60*2*3.1415926536/T*t)-0.15785*sin(60*2*3.1415926536/T*t)+0.34486*cos(61*2*3.1415926536/T*t)-0.01869*sin(61*2*3.1415926536/T*t)));
							  
								theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][8] = (float)(0.5*(2.84478-2.89363*cos(1*2*3.1415926536/T*t)-2.99201*sin(1*2*3.1415926536/T*t)-0.15526*cos(2*2*3.1415926536/T*t)-2.91810*sin(2*2*3.1415926536/T*t)+0.67806*cos(3*2*3.1415926536/T*t)+0.16028*sin(3*2*3.1415926536/T*t)+0.53149*cos(4*2*3.1415926536/T*t)-1.85870*sin(4*2*3.1415926536/T*t)+4.90663*cos(5*2*3.1415926536/T*t)-1.12130*sin(5*2*3.1415926536/T*t)+1.08827*cos(6*2*3.1415926536/T*t)-2.27345*sin(6*2*3.1415926536/T*t)-3.52565*cos(7*2*3.1415926536/T*t)+0.06782*sin(7*2*3.1415926536/T*t)-0.79581*cos(8*2*3.1415926536/T*t)-0.10569*sin(8*2*3.1415926536/T*t)+0.08580*cos(9*2*3.1415926536/T*t)-1.29821*sin(9*2*3.1415926536/T*t)-1.03720*cos(10*2*3.1415926536/T*t)+0.89972*sin(10*2*3.1415926536/T*t)+0.90709*cos(11*2*3.1415926536/T*t)+1.30284*sin(11*2*3.1415926536/T*t)+0.99255*cos(12*2*3.1415926536/T*t)+0.25132*sin(12*2*3.1415926536/T*t)+0.26952*cos(13*2*3.1415926536/T*t)-0.82079*sin(13*2*3.1415926536/T*t)-0.31791*cos(14*2*3.1415926536/T*t)-0.25920*sin(14*2*3.1415926536/T*t)+0.25127*cos(15*2*3.1415926536/T*t)+0.00128*sin(15*2*3.1415926536/T*t)-0.03167*cos(16*2*3.1415926536/T*t)-0.34795*sin(16*2*3.1415926536/T*t)-0.03107*cos(17*2*3.1415926536/T*t)+0.03386*sin(17*2*3.1415926536/T*t)+0.73286*cos(18*2*3.1415926536/T*t)+0.35604*sin(18*2*3.1415926536/T*t)-0.18231*cos(19*2*3.1415926536/T*t)-0.34096*sin(19*2*3.1415926536/T*t)-0.07684*cos(20*2*3.1415926536/T*t)+0.35178*sin(20*2*3.1415926536/T*t)-0.02885*cos(21*2*3.1415926536/T*t)-0.22735*sin(21*2*3.1415926536/T*t)-0.25297*cos(22*2*3.1415926536/T*t)+0.08115*sin(22*2*3.1415926536/T*t)-0.00908*cos(23*2*3.1415926536/T*t)+0.49470*sin(23*2*3.1415926536/T*t)+0.49097*cos(24*2*3.1415926536/T*t)+0.48762*sin(24*2*3.1415926536/T*t)-0.19948*cos(25*2*3.1415926536/T*t)-0.16631*sin(25*2*3.1415926536/T*t)+0.01470*cos(26*2*3.1415926536/T*t)+0.21981*sin(26*2*3.1415926536/T*t)-0.00058*cos(27*2*3.1415926536/T*t)+0.07112*sin(27*2*3.1415926536/T*t)-0.10373*cos(28*2*3.1415926536/T*t)
								-0.15785*sin(28*2*3.1415926536/T*t)-0.29827*cos(29*2*3.1415926536/T*t)+0.02902*sin(29*2*3.1415926536/T*t)-0.00041*cos(30*2*3.1415926536/T*t)+0.44568*sin(30*2*3.1415926536/T*t)-0.14042*cos(31*2*3.1415926536/T*t)+0.03740*sin(31*2*3.1415926536/T*t)-0.13928*cos(32*2*3.1415926536/T*t)-0.08973*sin(32*2*3.1415926536/T*t)-0.12021*cos(33*2*3.1415926536/T*t)+0.28596*sin(33*2*3.1415926536/T*t)-0.14300*cos(34*2*3.1415926536/T*t)-0.00345*sin(34*2*3.1415926536/T*t)-0.33030*cos(35*2*3.1415926536/T*t)+0.13067*sin(35*2*3.1415926536/T*t)+0.14893*cos(36*2*3.1415926536/T*t)+0.25738*sin(36*2*3.1415926536/T*t)-0.13703*cos(37*2*3.1415926536/T*t)-0.00933*sin(37*2*3.1415926536/T*t)-0.19067*cos(38*2*3.1415926536/T*t)+0.02413*sin(38*2*3.1415926536/T*t)-0.02947*cos(39*2*3.1415926536/T*t)+0.15438*sin(39*2*3.1415926536/T*t)-0.18350*cos(40*2*3.1415926536/T*t)-0.08735*sin(40*2*3.1415926536/T*t)-0.28448*cos(41*2*3.1415926536/T*t)-0.04715*sin(41*2*3.1415926536/T*t)-0.17710*cos(42*2*3.1415926536/T*t)+0.17785*sin(42*2*3.1415926536/T*t)-0.10487*cos(43*2*3.1415926536/T*t)+0.14064*sin(43*2*3.1415926536/T*t)-0.29449*cos(44*2*3.1415926536/T*t)-0.15335*sin(44*2*3.1415926536/T*t)-0.12818*cos(45*2*3.1415926536/T*t)+0.14467*sin(45*2*3.1415926536/T*t)-0.01696*cos(46*2*3.1415926536/T*t)+0.05482*sin(46*2*3.1415926536/T*t)-0.18189*cos(47*2*3.1415926536/T*t)-0.06829*sin(47*2*3.1415926536/T*t)-0.16044*cos(48*2*3.1415926536/T*t)+0.05973*sin(48*2*3.1415926536/T*t)-0.04731*cos(49*2*3.1415926536/T*t)-0.01292*sin(49*2*3.1415926536/T*t)-0.15609*cos(50*2*3.1415926536/T*t)-0.10094*sin(50*2*3.1415926536/T*t)-0.11736*cos(51*2*3.1415926536/T*t)-0.01082*sin(51*2*3.1415926536/T*t)-0.13272*cos(52*2*3.1415926536/T*t)+0.00109*sin(52*2*3.1415926536/T*t)-0.15722*cos(53*2*3.1415926536/T*t)-0.07476*sin(53*2*3.1415926536/T*t)-0.11757*cos(54*2*3.1415926536/T*t)+0.05179*sin(54*2*3.1415926536/T*t)-0.02709*cos(55*2*3.1415926536/T*t)
								+0.03078*sin(55*2*3.1415926536/T*t)-0.07367*cos(56*2*3.1415926536/T*t)-0.07995*sin(56*2*3.1415926536/T*t)-0.14319*cos(57*2*3.1415926536/T*t)-0.03402*sin(57*2*3.1415926536/T*t)-0.03676*cos(58*2*3.1415926536/T*t)+0.04917*sin(58*2*3.1415926536/T*t)-0.03498*cos(59*2*3.1415926536/T*t)-0.12345*sin(59*2*3.1415926536/T*t)-0.13485*cos(60*2*3.1415926536/T*t)+0.00674*sin(60*2*3.1415926536/T*t)-0.06109*cos(61*2*3.1415926536/T*t)+0.03360*sin(61*2*3.1415926536/T*t)));
								
								  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][9] = (float)(0.8*(69.78513-4.51330*cos(1*2*3.1415926536/T*t)+1.23270*sin(1*2*3.1415926536/T*t)-8.61509*cos(2*2*3.1415926536/T*t)+12.15755*sin(2*2*3.1415926536/T*t)-7.00303*cos(3*2*3.1415926536/T*t)-8.48613*sin(3*2*3.1415926536/T*t)-18.19616*cos(4*2*3.1415926536/T*t)+3.79716*sin(4*2*3.1415926536/T*t)+1.45236*cos(5*2*3.1415926536/T*t)+11.08850*sin(5*2*3.1415926536/T*t)+5.73933*cos(6*2*3.1415926536/T*t)-1.41099*sin(6*2*3.1415926536/T*t)-17.69333*cos(7*2*3.1415926536/T*t)+9.28362*sin(7*2*3.1415926536/T*t)-15.98334*cos(8*2*3.1415926536/T*t)+2.11815*sin(8*2*3.1415926536/T*t)-12.20012*cos(9*2*3.1415926536/T*t)+1.00366*sin(9*2*3.1415926536/T*t)+8.20855*cos(10*2*3.1415926536/T*t)+8.17057*sin(10*2*3.1415926536/T*t)-5.29860*cos(11*2*3.1415926536/T*t)+5.58157*sin(11*2*3.1415926536/T*t)+7.09239*cos(12*2*3.1415926536/T*t)-13.03605*sin(12*2*3.1415926536/T*t)-3.89312*cos(13*2*3.1415926536/T*t)-2.99897*sin(13*2*3.1415926536/T*t)-4.03782*cos(14*2*3.1415926536/T*t)-4.41578*sin(14*2*3.1415926536/T*t)+1.10499*cos(15*2*3.1415926536/T*t)-1.32162*sin(15*2*3.1415926536/T*t)-3.90280*cos(16*2*3.1415926536/T*t)-3.71254*sin(16*2*3.1415926536/T*t)-5.28533*cos(17*2*3.1415926536/T*t)-2.84515*sin(17*2*3.1415926536/T*t)-0.78129*cos(18*2*3.1415926536/T*t)+3.54227*sin(18*2*3.1415926536/T*t)+0.39108*cos(19*2*3.1415926536/T*t)+3.26496*sin(19*2*3.1415926536/T*t)+4.94668*cos(20*2*3.1415926536/T*t)-2.44375*sin(20*2*3.1415926536/T*t)+1.20285*cos(21*2*3.1415926536/T*t)-1.52367*sin(21*2*3.1415926536/T*t)+0.58724*cos(22*2*3.1415926536/T*t)-3.69227*sin(22*2*3.1415926536/T*t)-0.20659*cos(23*2*3.1415926536/T*t)+0.93622*sin(23*2*3.1415926536/T*t)+0.64149*cos(24*2*3.1415926536/T*t)-3.09987*sin(24*2*3.1415926536/T*t)+0.24491*cos(25*2*3.1415926536/T*t)-1.56065*sin(25*2*3.1415926536/T*t)-1.71077*cos(26*2*3.1415926536/T*t)-1.70316*sin(26*2*3.1415926536/T*t)-0.64144*cos(27*2*3.1415926536/T*t)+0.63885*sin(27*2*3.1415926536/T*t)
								  +0.23837*cos(28*2*3.1415926536/T*t)+3.23528*sin(28*2*3.1415926536/T*t)+1.93882*cos(29*2*3.1415926536/T*t)-0.48363*sin(29*2*3.1415926536/T*t)+2.71440*cos(30*2*3.1415926536/T*t)-0.73837*sin(30*2*3.1415926536/T*t)-0.35973*cos(31*2*3.1415926536/T*t)-0.57788*sin(31*2*3.1415926536/T*t)+0.39869*cos(32*2*3.1415926536/T*t)-0.52015*sin(32*2*3.1415926536/T*t)+0.63127*cos(33*2*3.1415926536/T*t)+0.23775*sin(33*2*3.1415926536/T*t)+0.03812*cos(34*2*3.1415926536/T*t)-0.40112*sin(34*2*3.1415926536/T*t)+0.00314*cos(35*2*3.1415926536/T*t)-0.53509*sin(35*2*3.1415926536/T*t)+0.19292*cos(36*2*3.1415926536/T*t)+1.16146*sin(36*2*3.1415926536/T*t)+0.19084*cos(37*2*3.1415926536/T*t)+1.01940*sin(37*2*3.1415926536/T*t)+1.31854*cos(38*2*3.1415926536/T*t)+0.48513*sin(38*2*3.1415926536/T*t)+0.94265*cos(39*2*3.1415926536/T*t)-0.23134*sin(39*2*3.1415926536/T*t)+0.01670*cos(40*2*3.1415926536/T*t)-0.39452*sin(40*2*3.1415926536/T*t)-0.01020*cos(41*2*3.1415926536/T*t)-0.20378*sin(41*2*3.1415926536/T*t)+0.32115*cos(42*2*3.1415926536/T*t)+0.30434*sin(42*2*3.1415926536/T*t)-0.14677*cos(43*2*3.1415926536/T*t)+0.09602*sin(43*2*3.1415926536/T*t)+0.33172*cos(44*2*3.1415926536/T*t)-0.10824*sin(44*2*3.1415926536/T*t)-0.51874*cos(45*2*3.1415926536/T*t)-0.04684*sin(45*2*3.1415926536/T*t)+0.06085*cos(46*2*3.1415926536/T*t)+0.63771*sin(46*2*3.1415926536/T*t)+0.32094*cos(47*2*3.1415926536/T*t)+0.49958*sin(47*2*3.1415926536/T*t)+0.65240*cos(48*2*3.1415926536/T*t)-0.03892*sin(48*2*3.1415926536/T*t)+0.20334*cos(49*2*3.1415926536/T*t)-0.16196*sin(49*2*3.1415926536/T*t)-0.16657*cos(50*2*3.1415926536/T*t)+0.08477*sin(50*2*3.1415926536/T*t)+0.06534*cos(51*2*3.1415926536/T*t)-0.13545*sin(51*2*3.1415926536/T*t)-0.07480*cos(52*2*3.1415926536/T*t)+0.10852*sin(52*2*3.1415926536/T*t)+0.05012*cos(53*2*3.1415926536/T*t)-0.17573*sin(53*2*3.1415926536/T*t)-0.08762*cos(54*2*3.1415926536/T*t)-0.14861*sin(54*2*3.1415926536/T*t)
								  -0.46659*cos(55*2*3.1415926536/T*t)+0.15930*sin(55*2*3.1415926536/T*t)-0.00062*cos(56*2*3.1415926536/T*t)+0.37796*sin(56*2*3.1415926536/T*t)+0.13078*cos(57*2*3.1415926536/T*t)+0.25505*sin(57*2*3.1415926536/T*t)+0.03701*cos(58*2*3.1415926536/T*t)+0.05061*sin(58*2*3.1415926536/T*t)-0.10365*cos(59*2*3.1415926536/T*t)-0.30456*sin(59*2*3.1415926536/T*t)-0.13656*cos(60*2*3.1415926536/T*t)+0.00877*sin(60*2*3.1415926536/T*t)-0.16119*cos(61*2*3.1415926536/T*t)-0.21752*sin(61*2*3.1415926536/T*t)));
								  
									theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][10] = (float)(0.8*(10.31317+5.87450*cos(1*2*3.1415926536/T*t)-3.13387*sin(1*2*3.1415926536/T*t)-1.62830*cos(2*2*3.1415926536/T*t)+3.25312*sin(2*2*3.1415926536/T*t)+0.26853*cos(3*2*3.1415926536/T*t)-3.61920*sin(3*2*3.1415926536/T*t)-1.90673*cos(4*2*3.1415926536/T*t)-9.10986*sin(4*2*3.1415926536/T*t)+1.99025*cos(5*2*3.1415926536/T*t)+6.46016*sin(5*2*3.1415926536/T*t)+3.83865*cos(6*2*3.1415926536/T*t)-0.46326*sin(6*2*3.1415926536/T*t)-12.96492*cos(7*2*3.1415926536/T*t)+0.20003*sin(7*2*3.1415926536/T*t)+3.73678*cos(8*2*3.1415926536/T*t)+4.19392*sin(8*2*3.1415926536/T*t)+4.01382*cos(9*2*3.1415926536/T*t)-0.96627*sin(9*2*3.1415926536/T*t)+2.76337*cos(10*2*3.1415926536/T*t)+1.19691*sin(10*2*3.1415926536/T*t)-0.02839*cos(11*2*3.1415926536/T*t)-1.86649*sin(11*2*3.1415926536/T*t)+0.50481*cos(12*2*3.1415926536/T*t)-2.31647*sin(12*2*3.1415926536/T*t)-3.30129*cos(13*2*3.1415926536/T*t)-1.50289*sin(13*2*3.1415926536/T*t)-1.19736*cos(14*2*3.1415926536/T*t)+2.41282*sin(14*2*3.1415926536/T*t)-4.44574*cos(15*2*3.1415926536/T*t)-0.82258*sin(15*2*3.1415926536/T*t)+0.12587*cos(16*2*3.1415926536/T*t)+2.87148*sin(16*2*3.1415926536/T*t)-0.63779*cos(17*2*3.1415926536/T*t)+0.89783*sin(17*2*3.1415926536/T*t)+0.33438*cos(18*2*3.1415926536/T*t)+1.16745*sin(18*2*3.1415926536/T*t)-0.82096*cos(19*2*3.1415926536/T*t)-1.84589*sin(19*2*3.1415926536/T*t)+0.21569*cos(20*2*3.1415926536/T*t)+0.33559*sin(20*2*3.1415926536/T*t)-0.71631*cos(21*2*3.1415926536/T*t)+0.19495*sin(21*2*3.1415926536/T*t)-0.49953*cos(22*2*3.1415926536/T*t)-0.16023*sin(22*2*3.1415926536/T*t)-1.89580*cos(23*2*3.1415926536/T*t)-0.26475*sin(23*2*3.1415926536/T*t)+0.15029*cos(24*2*3.1415926536/T*t)+0.74037*sin(24*2*3.1415926536/T*t)-0.74686*cos(25*2*3.1415926536/T*t)-0.57707*sin(25*2*3.1415926536/T*t)-0.31673*cos(26*2*3.1415926536/T*t)+0.90942*sin(26*2*3.1415926536/T*t)-0.16882*cos(27*2*3.1415926536/T*t)+0.08772*sin(27*2*3.1415926536/T*t)
									+0.38117*cos(28*2*3.1415926536/T*t)-0.17394*sin(28*2*3.1415926536/T*t)+0.31798*cos(29*2*3.1415926536/T*t)+0.31382*sin(29*2*3.1415926536/T*t)+0.25409*cos(30*2*3.1415926536/T*t)-0.53207*sin(30*2*3.1415926536/T*t)-0.52992*cos(31*2*3.1415926536/T*t)-0.38397*sin(31*2*3.1415926536/T*t)-0.28728*cos(32*2*3.1415926536/T*t)+0.04553*sin(32*2*3.1415926536/T*t)+0.18715*cos(33*2*3.1415926536/T*t)-0.15292*sin(33*2*3.1415926536/T*t)+0.04786*cos(34*2*3.1415926536/T*t)-0.17518*sin(34*2*3.1415926536/T*t)-0.53485*cos(35*2*3.1415926536/T*t)+0.18298*sin(35*2*3.1415926536/T*t)-0.12676*cos(36*2*3.1415926536/T*t)+0.07755*sin(36*2*3.1415926536/T*t)+0.43960*cos(37*2*3.1415926536/T*t)+0.14096*sin(37*2*3.1415926536/T*t)+0.22723*cos(38*2*3.1415926536/T*t)-0.00395*sin(38*2*3.1415926536/T*t)-0.01974*cos(39*2*3.1415926536/T*t)-0.49559*sin(39*2*3.1415926536/T*t)-0.30780*cos(40*2*3.1415926536/T*t)-0.36002*sin(40*2*3.1415926536/T*t)-0.39741*cos(41*2*3.1415926536/T*t)-0.18477*sin(41*2*3.1415926536/T*t)-0.29948*cos(42*2*3.1415926536/T*t)+0.20436*sin(42*2*3.1415926536/T*t)-0.05055*cos(43*2*3.1415926536/T*t)+0.12075*sin(43*2*3.1415926536/T*t)-0.44484*cos(44*2*3.1415926536/T*t)+0.09341*sin(44*2*3.1415926536/T*t)+0.17557*cos(45*2*3.1415926536/T*t)+0.42893*sin(45*2*3.1415926536/T*t)+0.34924*cos(46*2*3.1415926536/T*t)+0.09615*sin(46*2*3.1415926536/T*t)-0.13945*cos(47*2*3.1415926536/T*t)-0.35004*sin(47*2*3.1415926536/T*t)-0.27223*cos(48*2*3.1415926536/T*t)-0.13064*sin(48*2*3.1415926536/T*t)-0.31666*cos(49*2*3.1415926536/T*t)-0.20335*sin(49*2*3.1415926536/T*t)-0.45610*cos(50*2*3.1415926536/T*t)+0.08729*sin(50*2*3.1415926536/T*t)-0.04930*cos(51*2*3.1415926536/T*t)+0.12643*sin(51*2*3.1415926536/T*t)-0.06060*cos(52*2*3.1415926536/T*t)+0.12906*sin(52*2*3.1415926536/T*t)-0.12207*cos(53*2*3.1415926536/T*t)-0.00308*sin(53*2*3.1415926536/T*t)-0.05875*cos(54*2*3.1415926536/T*t)+0.04795*sin(54*2*3.1415926536/T*t)
									+0.07744*cos(55*2*3.1415926536/T*t)+0.16705*sin(55*2*3.1415926536/T*t)-0.14214*cos(56*2*3.1415926536/T*t)-0.16670*sin(56*2*3.1415926536/T*t)-0.12862*cos(57*2*3.1415926536/T*t)-0.02572*sin(57*2*3.1415926536/T*t)-0.13515*cos(58*2*3.1415926536/T*t)+0.05223*sin(58*2*3.1415926536/T*t)-0.25445*cos(59*2*3.1415926536/T*t)-0.04008*sin(59*2*3.1415926536/T*t)-0.09862*cos(60*2*3.1415926536/T*t)+0.14252*sin(60*2*3.1415926536/T*t)-0.07916*cos(61*2*3.1415926536/T*t)+0.10391*sin(61*2*3.1415926536/T*t)));
									
									  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][11] = (float)(0.8*(32.67699+14.53274*cos(1*2*3.1415926536/T*t)-6.10895*sin(1*2*3.1415926536/T*t)+3.63589*cos(2*2*3.1415926536/T*t)-0.25563*sin(2*2*3.1415926536/T*t)+0.16211*cos(3*2*3.1415926536/T*t)+10.81750*sin(3*2*3.1415926536/T*t)-10.66744*cos(4*2*3.1415926536/T*t)-9.81388*sin(4*2*3.1415926536/T*t)+13.12491*cos(5*2*3.1415926536/T*t)+4.65107*sin(5*2*3.1415926536/T*t)+4.81115*cos(6*2*3.1415926536/T*t)-1.68378*sin(6*2*3.1415926536/T*t)-11.26370*cos(7*2*3.1415926536/T*t)+14.07429*sin(7*2*3.1415926536/T*t)-9.56225*cos(8*2*3.1415926536/T*t)-12.33456*sin(8*2*3.1415926536/T*t)-12.49843*cos(9*2*3.1415926536/T*t)-5.56210*sin(9*2*3.1415926536/T*t)-3.35171*cos(10*2*3.1415926536/T*t)+2.76995*sin(10*2*3.1415926536/T*t)+1.33480*cos(11*2*3.1415926536/T*t)+10.89655*sin(11*2*3.1415926536/T*t)-3.57334*cos(12*2*3.1415926536/T*t)+0.07182*sin(12*2*3.1415926536/T*t)+0.46216*cos(13*2*3.1415926536/T*t)+1.96498*sin(13*2*3.1415926536/T*t)+1.89197*cos(14*2*3.1415926536/T*t)+1.52556*sin(14*2*3.1415926536/T*t)-0.66186*cos(15*2*3.1415926536/T*t)-0.17651*sin(15*2*3.1415926536/T*t)-1.00897*cos(16*2*3.1415926536/T*t)-13.86662*sin(16*2*3.1415926536/T*t)-6.64109*cos(17*2*3.1415926536/T*t)-0.56548*sin(17*2*3.1415926536/T*t)-0.98883*cos(18*2*3.1415926536/T*t)+1.18841*sin(18*2*3.1415926536/T*t)-4.40668*cos(19*2*3.1415926536/T*t)+4.63913*sin(19*2*3.1415926536/T*t)+1.35197*cos(20*2*3.1415926536/T*t)+0.96409*sin(20*2*3.1415926536/T*t)+3.00636*cos(21*2*3.1415926536/T*t)-0.75570*sin(21*2*3.1415926536/T*t)+1.52004*cos(22*2*3.1415926536/T*t)-2.83465*sin(22*2*3.1415926536/T*t)-1.73136*cos(23*2*3.1415926536/T*t)-2.19575*sin(23*2*3.1415926536/T*t)-1.05624*cos(24*2*3.1415926536/T*t)-2.70934*sin(24*2*3.1415926536/T*t)-1.17004*cos(25*2*3.1415926536/T*t)-1.11736*sin(25*2*3.1415926536/T*t)-1.61990*cos(26*2*3.1415926536/T*t)-1.07871*sin(26*2*3.1415926536/T*t)-3.63508*cos(27*2*3.1415926536/T*t)+0.98156*sin(27*2*3.1415926536/T*t)
									  +0.73155*cos(28*2*3.1415926536/T*t)+2.06908*sin(28*2*3.1415926536/T*t)+1.58201*cos(29*2*3.1415926536/T*t)+1.61311*sin(29*2*3.1415926536/T*t)+1.40631*cos(30*2*3.1415926536/T*t)-0.74935*sin(30*2*3.1415926536/T*t)+0.82010*cos(31*2*3.1415926536/T*t)-0.98619*sin(31*2*3.1415926536/T*t)+0.25243*cos(32*2*3.1415926536/T*t)-1.48783*sin(32*2*3.1415926536/T*t)-1.33424*cos(33*2*3.1415926536/T*t)-1.23476*sin(33*2*3.1415926536/T*t)-2.14050*cos(34*2*3.1415926536/T*t)-0.32973*sin(34*2*3.1415926536/T*t)-0.77626*cos(35*2*3.1415926536/T*t)+0.55208*sin(35*2*3.1415926536/T*t)-0.15274*cos(36*2*3.1415926536/T*t)+1.17249*sin(36*2*3.1415926536/T*t)+0.39663*cos(37*2*3.1415926536/T*t)+1.71006*sin(37*2*3.1415926536/T*t)+0.56969*cos(38*2*3.1415926536/T*t)+0.90305*sin(38*2*3.1415926536/T*t)+1.17279*cos(39*2*3.1415926536/T*t)-0.69419*sin(39*2*3.1415926536/T*t)-0.05441*cos(40*2*3.1415926536/T*t)-0.86921*sin(40*2*3.1415926536/T*t)-0.91043*cos(41*2*3.1415926536/T*t)-0.31642*sin(41*2*3.1415926536/T*t)-0.75491*cos(42*2*3.1415926536/T*t)-0.10446*sin(42*2*3.1415926536/T*t)-0.28547*cos(43*2*3.1415926536/T*t)+0.50921*sin(43*2*3.1415926536/T*t)-0.09026*cos(44*2*3.1415926536/T*t)+0.18662*sin(44*2*3.1415926536/T*t)-0.84773*cos(45*2*3.1415926536/T*t)+0.28793*sin(45*2*3.1415926536/T*t)-0.24192*cos(46*2*3.1415926536/T*t)+0.25725*sin(46*2*3.1415926536/T*t)-0.11607*cos(47*2*3.1415926536/T*t)+0.10291*sin(47*2*3.1415926536/T*t)+0.28461*cos(48*2*3.1415926536/T*t)+0.40510*sin(48*2*3.1415926536/T*t)-0.17530*cos(49*2*3.1415926536/T*t)-0.68811*sin(49*2*3.1415926536/T*t)-0.42597*cos(50*2*3.1415926536/T*t)-0.36314*sin(50*2*3.1415926536/T*t)-0.53883*cos(51*2*3.1415926536/T*t)-0.25499*sin(51*2*3.1415926536/T*t)-0.56061*cos(52*2*3.1415926536/T*t)+0.48316*sin(52*2*3.1415926536/T*t)-0.24084*cos(53*2*3.1415926536/T*t)+0.35404*sin(53*2*3.1415926536/T*t)+0.20532*cos(54*2*3.1415926536/T*t)-0.14031*sin(54*2*3.1415926536/T*t)
									  -0.44438*cos(55*2*3.1415926536/T*t)-0.08503*sin(55*2*3.1415926536/T*t)-0.29593*cos(56*2*3.1415926536/T*t)+0.44421*sin(56*2*3.1415926536/T*t)-0.57972*cos(57*2*3.1415926536/T*t)-0.37219*sin(57*2*3.1415926536/T*t)-0.37018*cos(58*2*3.1415926536/T*t)+0.26392*sin(58*2*3.1415926536/T*t)-0.36764*cos(59*2*3.1415926536/T*t)+0.21192*sin(59*2*3.1415926536/T*t)-0.41217*cos(60*2*3.1415926536/T*t)+0.05987*sin(60*2*3.1415926536/T*t)+0.02089*cos(61*2*3.1415926536/T*t)-0.10645*sin(61*2*3.1415926536/T*t)));
									  
										theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][12] = (float)(0.8*(20.38225+1.64588*cos(1*2*3.1415926536/T*t)+2.89739*sin(1*2*3.1415926536/T*t)-1.83830*cos(2*2*3.1415926536/T*t)-4.61828*sin(2*2*3.1415926536/T*t)+2.54015*cos(3*2*3.1415926536/T*t)+1.77712*sin(3*2*3.1415926536/T*t)-3.96585*cos(4*2*3.1415926536/T*t)-10.06086*sin(4*2*3.1415926536/T*t)+3.29453*cos(5*2*3.1415926536/T*t)-9.67322*sin(5*2*3.1415926536/T*t)-5.71890*cos(6*2*3.1415926536/T*t)-4.93256*sin(6*2*3.1415926536/T*t)-13.24796*cos(7*2*3.1415926536/T*t)+13.11370*sin(7*2*3.1415926536/T*t)+2.40923*cos(8*2*3.1415926536/T*t)-2.53159*sin(8*2*3.1415926536/T*t)-1.12592*cos(9*2*3.1415926536/T*t)-2.12496*sin(9*2*3.1415926536/T*t)+2.10156*cos(10*2*3.1415926536/T*t)+3.86977*sin(10*2*3.1415926536/T*t)-10.34720*cos(11*2*3.1415926536/T*t)+6.27879*sin(11*2*3.1415926536/T*t)+9.79759*cos(12*2*3.1415926536/T*t)+3.23223*sin(12*2*3.1415926536/T*t)+5.58162*cos(13*2*3.1415926536/T*t)+2.47500*sin(13*2*3.1415926536/T*t)-0.69681*cos(14*2*3.1415926536/T*t)-3.03024*sin(14*2*3.1415926536/T*t)-2.89639*cos(15*2*3.1415926536/T*t)-0.89680*sin(15*2*3.1415926536/T*t)-3.64656*cos(16*2*3.1415926536/T*t)-1.15134*sin(16*2*3.1415926536/T*t)-0.11843*cos(17*2*3.1415926536/T*t)+1.96541*sin(17*2*3.1415926536/T*t)-0.02963*cos(18*2*3.1415926536/T*t)+3.95326*sin(18*2*3.1415926536/T*t)-1.34507*cos(19*2*3.1415926536/T*t)-0.85865*sin(19*2*3.1415926536/T*t)+0.76959*cos(20*2*3.1415926536/T*t)-0.58304*sin(20*2*3.1415926536/T*t)-0.55818*cos(21*2*3.1415926536/T*t)+2.55747*sin(21*2*3.1415926536/T*t)+0.72522*cos(22*2*3.1415926536/T*t)+0.45483*sin(22*2*3.1415926536/T*t)+0.53774*cos(23*2*3.1415926536/T*t)-0.62301*sin(23*2*3.1415926536/T*t)+0.42223*cos(24*2*3.1415926536/T*t)-1.68099*sin(24*2*3.1415926536/T*t)-1.75628*cos(25*2*3.1415926536/T*t)+0.52270*sin(25*2*3.1415926536/T*t)-0.03244*cos(26*2*3.1415926536/T*t)+1.01963*sin(26*2*3.1415926536/T*t)+1.33904*cos(27*2*3.1415926536/T*t)+0.46403*sin(27*2*3.1415926536/T*t)-0.47186*cos(28*2*3.1415926536/T*t)
										-0.98021*sin(28*2*3.1415926536/T*t)+0.44567*cos(29*2*3.1415926536/T*t)-0.98782*sin(29*2*3.1415926536/T*t)-1.05838*cos(30*2*3.1415926536/T*t)+1.29650*sin(30*2*3.1415926536/T*t)+0.07324*cos(31*2*3.1415926536/T*t)+0.09422*sin(31*2*3.1415926536/T*t)+1.14263*cos(32*2*3.1415926536/T*t)-0.50746*sin(32*2*3.1415926536/T*t)-0.73152*cos(33*2*3.1415926536/T*t)-0.97131*sin(33*2*3.1415926536/T*t)-0.94495*cos(34*2*3.1415926536/T*t)+0.00613*sin(34*2*3.1415926536/T*t)-0.76472*cos(35*2*3.1415926536/T*t)+0.78343*sin(35*2*3.1415926536/T*t)+0.63510*cos(36*2*3.1415926536/T*t)+0.77048*sin(36*2*3.1415926536/T*t)+0.86702*cos(37*2*3.1415926536/T*t)-0.58256*sin(37*2*3.1415926536/T*t)-0.27908*cos(38*2*3.1415926536/T*t)-1.12197*sin(38*2*3.1415926536/T*t)-1.17000*cos(39*2*3.1415926536/T*t)+0.02505*sin(39*2*3.1415926536/T*t)-0.69010*cos(40*2*3.1415926536/T*t)+0.46949*sin(40*2*3.1415926536/T*t)+0.82794*cos(41*2*3.1415926536/T*t)+0.07537*sin(41*2*3.1415926536/T*t)-0.20341*cos(42*2*3.1415926536/T*t)+0.11309*sin(42*2*3.1415926536/T*t)-0.44995*cos(43*2*3.1415926536/T*t)-0.70097*sin(43*2*3.1415926536/T*t)-0.55840*cos(44*2*3.1415926536/T*t)+0.33281*sin(44*2*3.1415926536/T*t)-0.12411*cos(45*2*3.1415926536/T*t)+0.72692*sin(45*2*3.1415926536/T*t)+0.58709*cos(46*2*3.1415926536/T*t)+0.26699*sin(46*2*3.1415926536/T*t)-0.14520*cos(47*2*3.1415926536/T*t)-0.33157*sin(47*2*3.1415926536/T*t)-0.32308*cos(48*2*3.1415926536/T*t)-0.39880*sin(48*2*3.1415926536/T*t)-0.51156*cos(49*2*3.1415926536/T*t)+0.12378*sin(49*2*3.1415926536/T*t)-0.12928*cos(50*2*3.1415926536/T*t)+0.49438*sin(50*2*3.1415926536/T*t)+0.27426*cos(51*2*3.1415926536/T*t)-0.26473*sin(51*2*3.1415926536/T*t)-0.16758*cos(52*2*3.1415926536/T*t)-0.23492*sin(52*2*3.1415926536/T*t)-0.30294*cos(53*2*3.1415926536/T*t)+0.04982*sin(53*2*3.1415926536/T*t)+0.14773*cos(54*2*3.1415926536/T*t)+0.36894*sin(54*2*3.1415926536/T*t)+0.20793*cos(55*2*3.1415926536/T*t)+0.13985*sin(55*2*3.1415926536/T*t)
										-0.01973*cos(56*2*3.1415926536/T*t)-0.40815*sin(56*2*3.1415926536/T*t)-0.11781*cos(57*2*3.1415926536/T*t)-0.35275*sin(57*2*3.1415926536/T*t)-0.48660*cos(58*2*3.1415926536/T*t)+0.32365*sin(58*2*3.1415926536/T*t)-0.03851*cos(59*2*3.1415926536/T*t)+0.34256*sin(59*2*3.1415926536/T*t)+0.27982*cos(60*2*3.1415926536/T*t)+0.15977*sin(60*2*3.1415926536/T*t)-0.02238*cos(61*2*3.1415926536/T*t)-0.15019*sin(61*2*3.1415926536/T*t)));
										
										  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][13] = (float)(0.8*(0.04860+25.38404*cos(1*2*3.1415926536/T*t)-8.49050*sin(1*2*3.1415926536/T*t)-3.35720*cos(2*2*3.1415926536/T*t)+31.77281*sin(2*2*3.1415926536/T*t)-18.05870*cos(3*2*3.1415926536/T*t)-22.58424*sin(3*2*3.1415926536/T*t)-5.33560*cos(4*2*3.1415926536/T*t)-8.46877*sin(4*2*3.1415926536/T*t)-3.74659*cos(5*2*3.1415926536/T*t)+21.58656*sin(5*2*3.1415926536/T*t)+12.89902*cos(6*2*3.1415926536/T*t)+0.99924*sin(6*2*3.1415926536/T*t)-26.09863*cos(7*2*3.1415926536/T*t)-8.68803*sin(7*2*3.1415926536/T*t)+2.11423*cos(8*2*3.1415926536/T*t)-0.76205*sin(8*2*3.1415926536/T*t)-9.32746*cos(9*2*3.1415926536/T*t)+1.59083*sin(9*2*3.1415926536/T*t)+11.00185*cos(10*2*3.1415926536/T*t)+1.53785*sin(10*2*3.1415926536/T*t)-8.43344*cos(11*2*3.1415926536/T*t)-7.03899*sin(11*2*3.1415926536/T*t)+0.73635*cos(12*2*3.1415926536/T*t)+7.04244*sin(12*2*3.1415926536/T*t)-2.89742*cos(13*2*3.1415926536/T*t)+8.54838*sin(13*2*3.1415926536/T*t)+0.27194*cos(14*2*3.1415926536/T*t)+3.50172*sin(14*2*3.1415926536/T*t)-0.20973*cos(15*2*3.1415926536/T*t)-0.57164*sin(15*2*3.1415926536/T*t)+3.10416*cos(16*2*3.1415926536/T*t)-2.40400*sin(16*2*3.1415926536/T*t)-2.55077*cos(17*2*3.1415926536/T*t)+2.62053*sin(17*2*3.1415926536/T*t)+2.61854*cos(18*2*3.1415926536/T*t)-2.16883*sin(18*2*3.1415926536/T*t)+1.45842*cos(19*2*3.1415926536/T*t)+3.66636*sin(19*2*3.1415926536/T*t)+2.27517*cos(20*2*3.1415926536/T*t)-2.13173*sin(20*2*3.1415926536/T*t)-1.82052*cos(21*2*3.1415926536/T*t)+0.18796*sin(21*2*3.1415926536/T*t)-0.60145*cos(22*2*3.1415926536/T*t)-1.55104*sin(22*2*3.1415926536/T*t)+0.43225*cos(23*2*3.1415926536/T*t)+2.48310*sin(23*2*3.1415926536/T*t)+0.00744*cos(24*2*3.1415926536/T*t)-1.27346*sin(24*2*3.1415926536/T*t)+0.65286*cos(25*2*3.1415926536/T*t)+0.80613*sin(25*2*3.1415926536/T*t)+0.13406*cos(26*2*3.1415926536/T*t)-1.08283*sin(26*2*3.1415926536/T*t)+3.27764*cos(27*2*3.1415926536/T*t)+0.17895*sin(27*2*3.1415926536/T*t)+0.08136*cos(28*2*3.1415926536/T*t)
										  -1.84448*sin(28*2*3.1415926536/T*t)+1.58161*cos(29*2*3.1415926536/T*t)-1.66605*sin(29*2*3.1415926536/T*t)-0.56203*cos(30*2*3.1415926536/T*t)-0.96569*sin(30*2*3.1415926536/T*t)+0.36766*cos(31*2*3.1415926536/T*t)+0.76162*sin(31*2*3.1415926536/T*t)-1.06298*cos(32*2*3.1415926536/T*t)-1.14399*sin(32*2*3.1415926536/T*t)+1.81719*cos(33*2*3.1415926536/T*t)-0.92347*sin(33*2*3.1415926536/T*t)+0.39822*cos(34*2*3.1415926536/T*t)-1.73396*sin(34*2*3.1415926536/T*t)-0.17623*cos(35*2*3.1415926536/T*t)-0.74359*sin(35*2*3.1415926536/T*t)-0.22210*cos(36*2*3.1415926536/T*t)+0.69034*sin(36*2*3.1415926536/T*t)+1.89660*cos(37*2*3.1415926536/T*t)-0.40416*sin(37*2*3.1415926536/T*t)+0.87763*cos(38*2*3.1415926536/T*t)+0.23568*sin(38*2*3.1415926536/T*t)+0.09657*cos(39*2*3.1415926536/T*t)-1.56828*sin(39*2*3.1415926536/T*t)-0.81397*cos(40*2*3.1415926536/T*t)+0.79960*sin(40*2*3.1415926536/T*t)+1.55619*cos(41*2*3.1415926536/T*t)-1.21539*sin(41*2*3.1415926536/T*t)+0.82841*cos(42*2*3.1415926536/T*t)+0.47277*sin(42*2*3.1415926536/T*t)+0.57739*cos(43*2*3.1415926536/T*t)-0.68752*sin(43*2*3.1415926536/T*t)+0.54555*cos(44*2*3.1415926536/T*t)-0.35015*sin(44*2*3.1415926536/T*t)+0.74003*cos(45*2*3.1415926536/T*t)-0.05912*sin(45*2*3.1415926536/T*t)+0.62942*cos(46*2*3.1415926536/T*t)+0.62104*sin(46*2*3.1415926536/T*t)+0.08659*cos(47*2*3.1415926536/T*t)+0.22144*sin(47*2*3.1415926536/T*t)+0.65538*cos(48*2*3.1415926536/T*t)+0.50426*sin(48*2*3.1415926536/T*t)+0.83443*cos(49*2*3.1415926536/T*t)-0.20054*sin(49*2*3.1415926536/T*t)+1.03412*cos(50*2*3.1415926536/T*t)+0.31418*sin(50*2*3.1415926536/T*t)+0.69725*cos(51*2*3.1415926536/T*t)-0.72414*sin(51*2*3.1415926536/T*t)+0.56561*cos(52*2*3.1415926536/T*t)-0.17724*sin(52*2*3.1415926536/T*t)+0.28884*cos(53*2*3.1415926536/T*t)+0.06398*sin(53*2*3.1415926536/T*t)+0.47300*cos(54*2*3.1415926536/T*t)+0.45267*sin(54*2*3.1415926536/T*t)+0.18572*cos(55*2*3.1415926536/T*t)+0.29755*sin(55*2*3.1415926536/T*t)
										  +0.65573*cos(56*2*3.1415926536/T*t)-0.22466*sin(56*2*3.1415926536/T*t)+0.01808*cos(57*2*3.1415926536/T*t)+0.16525*sin(57*2*3.1415926536/T*t)+0.57633*cos(58*2*3.1415926536/T*t)+0.10212*sin(58*2*3.1415926536/T*t)+0.07252*cos(59*2*3.1415926536/T*t)+0.32651*sin(59*2*3.1415926536/T*t)+0.68282*cos(60*2*3.1415926536/T*t)-0.09845*sin(60*2*3.1415926536/T*t)+0.03797*cos(61*2*3.1415926536/T*t)+0.19847*sin(61*2*3.1415926536/T*t)));
										  
											
											  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][14] = (float)(0.5*(-3.29783+4.81821*cos(1*2*3.1415926536/T*t)-0.43947*sin(1*2*3.1415926536/T*t)+0.24924*cos(2*2*3.1415926536/T*t)+4.01381*sin(2*2*3.1415926536/T*t)-2.97245*cos(3*2*3.1415926536/T*t)-0.97687*sin(3*2*3.1415926536/T*t)-1.09820*cos(4*2*3.1415926536/T*t)-0.04259*sin(4*2*3.1415926536/T*t)+0.11577*cos(5*2*3.1415926536/T*t)+4.12540*sin(5*2*3.1415926536/T*t)+2.02409*cos(6*2*3.1415926536/T*t)+1.30891*sin(6*2*3.1415926536/T*t)-3.37541*cos(7*2*3.1415926536/T*t)-0.96651*sin(7*2*3.1415926536/T*t)+0.18433*cos(8*2*3.1415926536/T*t)-0.21403*sin(8*2*3.1415926536/T*t)-1.00099*cos(9*2*3.1415926536/T*t)+0.21743*sin(9*2*3.1415926536/T*t)+1.50748*cos(10*2*3.1415926536/T*t)+0.57125*sin(10*2*3.1415926536/T*t)-0.91778*cos(11*2*3.1415926536/T*t)-1.00203*sin(11*2*3.1415926536/T*t)-0.28940*cos(12*2*3.1415926536/T*t)+0.94850*sin(12*2*3.1415926536/T*t)-0.58401*cos(13*2*3.1415926536/T*t)+1.34316*sin(13*2*3.1415926536/T*t)+0.13746*cos(14*2*3.1415926536/T*t)+1.00619*sin(14*2*3.1415926536/T*t)-0.37510*cos(15*2*3.1415926536/T*t)+0.27117*sin(15*2*3.1415926536/T*t)+0.81808*cos(16*2*3.1415926536/T*t)-0.92357*sin(16*2*3.1415926536/T*t)-0.46275*cos(17*2*3.1415926536/T*t)+0.05333*sin(17*2*3.1415926536/T*t)+0.41402*cos(18*2*3.1415926536/T*t)+0.06923*sin(18*2*3.1415926536/T*t)-0.24720*cos(19*2*3.1415926536/T*t)+0.43935*sin(19*2*3.1415926536/T*t)+0.72323*cos(20*2*3.1415926536/T*t)+0.03543*sin(20*2*3.1415926536/T*t)-0.24316*cos(21*2*3.1415926536/T*t)-0.12582*sin(21*2*3.1415926536/T*t)-0.27814*cos(22*2*3.1415926536/T*t)-0.02787*sin(22*2*3.1415926536/T*t)-0.14485*cos(23*2*3.1415926536/T*t)+0.18888*sin(23*2*3.1415926536/T*t)+0.17812*cos(24*2*3.1415926536/T*t)-0.26321*sin(24*2*3.1415926536/T*t)+0.23485*cos(25*2*3.1415926536/T*t)-0.08016*sin(25*2*3.1415926536/T*t)-0.08641*cos(26*2*3.1415926536/T*t)-0.15069*sin(26*2*3.1415926536/T*t)+0.19751*cos(27*2*3.1415926536/T*t)+0.21154*sin(27*2*3.1415926536/T*t)+0.33132*cos(28*2*3.1415926536/T*t)
											  -0.24819*sin(28*2*3.1415926536/T*t)+0.30288*cos(29*2*3.1415926536/T*t)-0.10604*sin(29*2*3.1415926536/T*t)-0.18034*cos(30*2*3.1415926536/T*t)-0.20906*sin(30*2*3.1415926536/T*t)+0.03006*cos(31*2*3.1415926536/T*t)+0.02090*sin(31*2*3.1415926536/T*t)-0.00123*cos(32*2*3.1415926536/T*t)-0.13413*sin(32*2*3.1415926536/T*t)+0.31325*cos(33*2*3.1415926536/T*t)-0.23031*sin(33*2*3.1415926536/T*t)-0.06074*cos(34*2*3.1415926536/T*t)-0.24262*sin(34*2*3.1415926536/T*t)+0.08090*cos(35*2*3.1415926536/T*t)-0.15365*sin(35*2*3.1415926536/T*t)-0.11711*cos(36*2*3.1415926536/T*t)+0.17530*sin(36*2*3.1415926536/T*t)+0.47803*cos(37*2*3.1415926536/T*t)+0.14575*sin(37*2*3.1415926536/T*t)+0.14947*cos(38*2*3.1415926536/T*t)+0.06864*sin(38*2*3.1415926536/T*t)+0.19629*cos(39*2*3.1415926536/T*t)-0.30310*sin(39*2*3.1415926536/T*t)-0.13205*cos(40*2*3.1415926536/T*t)-0.08782*sin(40*2*3.1415926536/T*t)+0.20383*cos(41*2*3.1415926536/T*t)-0.08697*sin(41*2*3.1415926536/T*t)+0.09978*cos(42*2*3.1415926536/T*t)+0.02966*sin(42*2*3.1415926536/T*t)+0.24602*cos(43*2*3.1415926536/T*t)-0.13136*sin(43*2*3.1415926536/T*t)+0.12793*cos(44*2*3.1415926536/T*t)+0.03861*sin(44*2*3.1415926536/T*t)+0.08630*cos(45*2*3.1415926536/T*t)+0.00280*sin(45*2*3.1415926536/T*t)+0.14694*cos(46*2*3.1415926536/T*t)+0.22445*sin(46*2*3.1415926536/T*t)+0.07468*cos(47*2*3.1415926536/T*t)-0.07105*sin(47*2*3.1415926536/T*t)+0.16018*cos(48*2*3.1415926536/T*t)+0.08100*sin(48*2*3.1415926536/T*t)+0.13656*cos(49*2*3.1415926536/T*t)-0.12903*sin(49*2*3.1415926536/T*t)+0.17831*cos(50*2*3.1415926536/T*t)+0.07425*sin(50*2*3.1415926536/T*t)+0.19416*cos(51*2*3.1415926536/T*t)-0.11763*sin(51*2*3.1415926536/T*t)+0.12490*cos(52*2*3.1415926536/T*t)-0.03143*sin(52*2*3.1415926536/T*t)+0.01417*cos(53*2*3.1415926536/T*t)+0.02409*sin(53*2*3.1415926536/T*t)+0.06593*cos(54*2*3.1415926536/T*t)+0.11491*sin(54*2*3.1415926536/T*t)+0.03616*cos(55*2*3.1415926536/T*t)
											  +0.10104*sin(55*2*3.1415926536/T*t)+0.22453*cos(56*2*3.1415926536/T*t)-0.04894*sin(56*2*3.1415926536/T*t)-0.02985*cos(57*2*3.1415926536/T*t)-0.09791*sin(57*2*3.1415926536/T*t)+0.07008*cos(58*2*3.1415926536/T*t)+0.00603*sin(58*2*3.1415926536/T*t)-0.00579*cos(59*2*3.1415926536/T*t)+0.08491*sin(59*2*3.1415926536/T*t)+0.17349*cos(60*2*3.1415926536/T*t)+0.03896*sin(60*2*3.1415926536/T*t)+0.05227*cos(61*2*3.1415926536/T*t)+0.01099*sin(61*2*3.1415926536/T*t)));
											  
												theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][15] = (float)(1.0*(-0.47979+0.32499*cos(1*2*3.1415926536/T*t)-0.15320*sin(1*2*3.1415926536/T*t)+1.35128*cos(2*2*3.1415926536/T*t)+0.03855*sin(2*2*3.1415926536/T*t)+0.08702*cos(3*2*3.1415926536/T*t)+0.49522*sin(3*2*3.1415926536/T*t)-0.77019*cos(4*2*3.1415926536/T*t)+0.12280*sin(4*2*3.1415926536/T*t)-0.54421*cos(5*2*3.1415926536/T*t)+0.27537*sin(5*2*3.1415926536/T*t)+0.29877*cos(6*2*3.1415926536/T*t)+0.12495*sin(6*2*3.1415926536/T*t)-0.18981*cos(7*2*3.1415926536/T*t)-0.20076*sin(7*2*3.1415926536/T*t)-0.19031*cos(8*2*3.1415926536/T*t)+0.87695*sin(8*2*3.1415926536/T*t)-0.26345*cos(9*2*3.1415926536/T*t)-0.25996*sin(9*2*3.1415926536/T*t)+0.23890*cos(10*2*3.1415926536/T*t)+0.02736*sin(10*2*3.1415926536/T*t)+0.08860*cos(11*2*3.1415926536/T*t)-0.04554*sin(11*2*3.1415926536/T*t)+0.07970*cos(12*2*3.1415926536/T*t)+0.16684*sin(12*2*3.1415926536/T*t)-0.05557*cos(13*2*3.1415926536/T*t)+0.00548*sin(13*2*3.1415926536/T*t)-0.07938*cos(14*2*3.1415926536/T*t)-0.16225*sin(14*2*3.1415926536/T*t)-0.06316*cos(15*2*3.1415926536/T*t)-0.28315*sin(15*2*3.1415926536/T*t)+0.32992*cos(16*2*3.1415926536/T*t)-0.12381*sin(16*2*3.1415926536/T*t)-0.01544*cos(17*2*3.1415926536/T*t)+0.06120*sin(17*2*3.1415926536/T*t)+0.12826*cos(18*2*3.1415926536/T*t)+0.16159*sin(18*2*3.1415926536/T*t)-0.05956*cos(19*2*3.1415926536/T*t)+0.00081*sin(19*2*3.1415926536/T*t)+0.11194*cos(20*2*3.1415926536/T*t)-0.18018*sin(20*2*3.1415926536/T*t)-0.04350*cos(21*2*3.1415926536/T*t)+0.00878*sin(21*2*3.1415926536/T*t)-0.12088*cos(22*2*3.1415926536/T*t)-0.19225*sin(22*2*3.1415926536/T*t)+0.00384*cos(23*2*3.1415926536/T*t)+0.08143*sin(23*2*3.1415926536/T*t)+0.00509*cos(24*2*3.1415926536/T*t)-0.04424*sin(24*2*3.1415926536/T*t)-0.00241*cos(25*2*3.1415926536/T*t)-0.01554*sin(25*2*3.1415926536/T*t)-0.22551*cos(26*2*3.1415926536/T*t)-0.08297*sin(26*2*3.1415926536/T*t)-0.06079*cos(27*2*3.1415926536/T*t)+0.08277*sin(27*2*3.1415926536/T*t)
												+0.12374*cos(28*2*3.1415926536/T*t)+0.02364*sin(28*2*3.1415926536/T*t)+0.04635*cos(29*2*3.1415926536/T*t)-0.04568*sin(29*2*3.1415926536/T*t)-0.06533*cos(30*2*3.1415926536/T*t)-0.10341*sin(30*2*3.1415926536/T*t)+0.06696*cos(31*2*3.1415926536/T*t)+0.08557*sin(31*2*3.1415926536/T*t)-0.00290*cos(32*2*3.1415926536/T*t)+0.04002*sin(32*2*3.1415926536/T*t)+0.04530*cos(33*2*3.1415926536/T*t)-0.00785*sin(33*2*3.1415926536/T*t)-0.02299*cos(34*2*3.1415926536/T*t)-0.06774*sin(34*2*3.1415926536/T*t)-0.00524*cos(35*2*3.1415926536/T*t)+0.01545*sin(35*2*3.1415926536/T*t)+0.01581*cos(36*2*3.1415926536/T*t)+0.00447*sin(36*2*3.1415926536/T*t)+0.04691*cos(37*2*3.1415926536/T*t)-0.02719*sin(37*2*3.1415926536/T*t)+0.05369*cos(38*2*3.1415926536/T*t)-0.06426*sin(38*2*3.1415926536/T*t)-0.04880*cos(39*2*3.1415926536/T*t)+0.03934*sin(39*2*3.1415926536/T*t)-0.04532*cos(40*2*3.1415926536/T*t)+0.03550*sin(40*2*3.1415926536/T*t)+0.01499*cos(41*2*3.1415926536/T*t)-0.01217*sin(41*2*3.1415926536/T*t)+0.02176*cos(42*2*3.1415926536/T*t)-0.01066*sin(42*2*3.1415926536/T*t)-0.02303*cos(43*2*3.1415926536/T*t)-0.01742*sin(43*2*3.1415926536/T*t)-0.05453*cos(44*2*3.1415926536/T*t)+0.00905*sin(44*2*3.1415926536/T*t)+0.00308*cos(45*2*3.1415926536/T*t)+0.01918*sin(45*2*3.1415926536/T*t)+0.03638*cos(46*2*3.1415926536/T*t)+0.00140*sin(46*2*3.1415926536/T*t)+0.01409*cos(47*2*3.1415926536/T*t)+0.03346*sin(47*2*3.1415926536/T*t)-0.04816*cos(48*2*3.1415926536/T*t)+0.00016*sin(48*2*3.1415926536/T*t)+0.01738*cos(49*2*3.1415926536/T*t)-0.00919*sin(49*2*3.1415926536/T*t)-0.00937*cos(50*2*3.1415926536/T*t)+0.04397*sin(50*2*3.1415926536/T*t)+0.02141*cos(51*2*3.1415926536/T*t)+0.01193*sin(51*2*3.1415926536/T*t)-0.02503*cos(52*2*3.1415926536/T*t)-0.03935*sin(52*2*3.1415926536/T*t)+0.00338*cos(53*2*3.1415926536/T*t)+0.00390*sin(53*2*3.1415926536/T*t)-0.04598*cos(54*2*3.1415926536/T*t)-0.00937*sin(54*2*3.1415926536/T*t)
												-0.01308*cos(55*2*3.1415926536/T*t)+0.04402*sin(55*2*3.1415926536/T*t)+0.02599*cos(56*2*3.1415926536/T*t)-0.03915*sin(56*2*3.1415926536/T*t)-0.02130*cos(57*2*3.1415926536/T*t)-0.01152*sin(57*2*3.1415926536/T*t)+0.00115*cos(58*2*3.1415926536/T*t)+0.01395*sin(58*2*3.1415926536/T*t)-0.00678*cos(59*2*3.1415926536/T*t)+0.01511*sin(59*2*3.1415926536/T*t)-0.01878*cos(60*2*3.1415926536/T*t)+0.01428*sin(60*2*3.1415926536/T*t)+0.01389*cos(61*2*3.1415926536/T*t)-0.02342*sin(61*2*3.1415926536/T*t)));
												
												  theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][16] = 0.;
												  
													}
													
													  theApp.Home(T);
													  
														theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
														
														  theApp.m_pSharedMemory->MotionFlagALL = 1;
														  theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
														  theApp.m_pSharedMemory->PROFTime[11] = 0;
														  
															theApp.m_pSharedMemory->PROFTime[19] = 0;
															theApp.m_pSharedMemory->MOTION_Stop = 0;
															
															  GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(TRUE);
*/
}

void CGesture::OnButtonMotion7() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	//float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.8f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.8f};	
	
	float	Constant[16];
	float	CosCoeff[16][10];
	float	SinCoeff[16][10];
	float	sum;
	
	int		NoOfCoeff[16] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	MotionNo = 5;
	GetDlgItem(IDC_BUTTON_MOTION7)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\22coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 1300; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION7)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion8() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.8f};	
	
	float	Constant[16];
	float	CosCoeff[16][48];
	float	SinCoeff[16][48];
	float	sum;
	
	int		NoOfCoeff[16] = {48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 6;
	GetDlgItem(IDC_BUTTON_MOTION8)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\8-2-coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 2460; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	GetDlgItem(IDC_BUTTON_MOTION8)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonMotion9() 
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
	
	
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 7;
	GetDlgItem(IDC_BUTTON_MOTION9)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 705;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion10() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][56];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][56];	// 56 means number of coefficient
	float	Coeff[16][113];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 56;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 113;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 8;
	GetDlgItem(IDC_BUTTON_MOTION10)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\1a.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 6000;//7000; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION10)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonShakeHandsStart() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ShakeHandsFlag = 1;
	
	GetDlgItem(IDC_BUTTON_SHAKE_HANDS_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHAKE_HANDS_STOP)->EnableWindow(TRUE);
}

void CGesture::OnButtonShakeHandsStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->ShakeHandsFlag = 3;
	GetDlgItem(IDC_BUTTON_SHAKE_HANDS_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHAKE_HANDS_STOP)->EnableWindow(FALSE);
}

void CGesture::DataReset()  // this happens after you press a button
{
	int i,j;
	
	for(i=0;i<24000;i++)
	{
		for(j=0;j<16;j++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[i][j] = 0.0f;
		}
	}
	//OnCommunication( 2, 0);
	
	
}

void CGesture::OnButtonMotion11() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][42];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][42];	// 56 means number of coefficient
	float	Coeff[16][85];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 42;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 85;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 9;
	GetDlgItem(IDC_BUTTON_MOTION11)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\1b.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 5000;//7000; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION11)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion13() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 10;
	GetDlgItem(IDC_BUTTON_MOTION13)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 400; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION13)->EnableWindow(TRUE);	
}

void CGesture::OnButtonMotion14() 
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
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 11;



	if( theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE )
	{
		//GetDlgItem(IDC_BUTTON_MOTION14)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MOTION31)->EnableWindow(TRUE);
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		T = 30;//7000; // dim : 10 msec.
		
		DataReset();
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
		GetDlgItem(IDC_ComMotion)->SetWindowText("tap");
	}
	else
	{
		GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
	}
}

void CGesture::OnButtonMotion15() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][44];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][44];	// 56 means number of coefficient
	float	Coeff[16][89];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 44;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 89;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 12;
	GetDlgItem(IDC_BUTTON_MOTION15)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\1c.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 5500;//7000; // dim : 10 msec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION15)->EnableWindow(TRUE);
}

void CGesture::OnButtonMotion16() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][38];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][38];	// 56 means number of coefficient
	float	Coeff[16][77];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 38;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 77;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 13;
	GetDlgItem(IDC_BUTTON_MOTION16)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\1d.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 5000;//7000; // dim : 10 msec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION16)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonMotion17() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][46];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][46];	// 56 means number of coefficient
	float	Coeff[16][93];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 46;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 93;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 14;
	GetDlgItem(IDC_BUTTON_MOTION17)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\1e.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 5500;//7000; // dim : 10 msec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION17)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonMotion18() 
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
	
	//float scale[16] = { 1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f, 1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.5f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.5f, 0.8f, 0.3f};	
	
	float	Constant[16];
	float	CosCoeff[16][13];	// 56 means number of coefficient, user should change.
	float	SinCoeff[16][13];	// 56 means number of coefficient
	float	Coeff[16][27];		// 113 means number of coefficient, user should change.
	float	sum;
	
	int		NoOfCoeff[16];// = {56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	int		NoCoeff, NoCoeff1;
	
	FILE *ifp;
	
	NoCoeff = 13;		// 56 means number of coefficient, user should change.
	NoCoeff1 = 27;		// 113 means number of coefficient, user should change.
	for(m=0;m<16;m++)
	{
		NoOfCoeff[m] = NoCoeff;
	}
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 15;
	GetDlgItem(IDC_BUTTON_MOTION18)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\2r1.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 1650;//7000; // dim : 10 msec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
	{
		for(m=0; m < NoCoeff1; m++)
		{
			fscanf(ifp,"%f",&Coeff[JointIndex][m]);
		}
		
		Constant[JointIndex] = Coeff[JointIndex][0];
		for(m=1; m <= NoOfCoeff[JointIndex]; m++)
		{
			CosCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m-1];
			SinCoeff[JointIndex][m-1] = Coeff[JointIndex][2*m];	
		}
	}
	fclose(ifp);
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION18)->EnableWindow(TRUE);
	
}

void CGesture::OnButtonMotion19() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 16;
	GetDlgItem(IDC_BUTTON_MOTION19)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 320; // dim : 10 mdec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION19)->EnableWindow(TRUE);	
}

void CGesture::OnButtonMotionActivation() 
{
	// TODO: Add your control notification handler code here
	//if(theApp.m_pSharedMemory->MotionFlag[2] == TRUE) GetDlgItem(IDC_BUTTON_MOTION4)->EnableWindow(TRUE);
	//if(theApp.m_pSharedMemory->MotionFlag[3] == TRUE) GetDlgItem(IDC_BUTTON_MOTION5)->EnableWindow(TRUE);
	//if(theApp.m_pSharedMemory->MotionFlag[4] == TRUE) GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(TRUE);
	//if(theApp.m_pSharedMemory->MotionFlag[5] == TRUE) GetDlgItem(IDC_BUTTON_MOTION7)->EnableWindow(TRUE);
	
	//if(theApp.m_pSharedMemory->MotionFlag[16] == F) GetDlgItem(IDC_BUTTON_MOTION19)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BUTTON_MOTION4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION9)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION10)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION12)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION13)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MOTION14)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MOTION15)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION16)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION17)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION18)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION19)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION20)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION21)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION22)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION23)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION24)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION25)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION26)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION27)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION28)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION29)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION30)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOTION31)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_RAISE_RIGHT_HAND)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_RAISE_RIGHT_ARM)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_RIGHT_ARM_CIRCLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_RAISE_LEFT_HAND)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_RAISE_LEFT_ARM)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_LEFT_ARM_CIRCLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_TOUCH_HEAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_TOUCH_NOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_RUB_STOMACH)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_CHOOCHOO)->EnableWindow(TRUE);
	//GetDlgItem(IDC_GESTURE_TIP_HAT)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_CLAP_HANDS)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_FLAP_ARMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_HANDS_ON_HIPS)->EnableWindow(TRUE);
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT2)->EnableWindow(TRUE);
	//enable radio buttons
	GetDlgItem(IDC_GESTURE_SPEED_SLOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_SPEED_MEDIUM)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_SPEED_FAST)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_AUX_BEND_RIGHT_ELBOW)->EnableWindow(TRUE); 
	GetDlgItem(IDC_GESTURE_AUX_UNLV)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_HELLO_WORLD)->EnableWindow(TRUE);
}

void CGesture::OnCheckRightHand() 
{
	// TODO: Add your control notification handler code here
	m_RightHandActivation = TRUE;
	m_LeftHandActivation = FALSE;
	
	UpdateData(FALSE);
}

void CGesture::OnCheckLeftHand() 
{
	// TODO: Add your control notification handler code here
	m_LeftHandActivation = TRUE;
	m_RightHandActivation = FALSE;
	
	UpdateData(FALSE);
}

void CGesture::OnButtonMotion20() 
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
	
	
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 17;
	GetDlgItem(IDC_BUTTON_MOTION20)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 700;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion21() 
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
	
	
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 18;
	GetDlgItem(IDC_BUTTON_MOTION21)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 1200;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion22() 
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
	
	//float scale[16] = { 0.7f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f,  1.0f};	
	//float scale[16] = { 0.7f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f,  1.0f};	
	float scale[16] = { 0.8f,  0.8f,  0.8f, 0.8f,  0.8f,  0.8f,  0.8f,  0.8f,  0.8f, 0.8f, 0.8f, 0.8f,  0.8f,  0.8f, 0.8f, 0.8f};	
	float	Constant[16];
	float	CosCoeff[16][15];
	float	SinCoeff[16][15];
	float	sum;
	
	int		NoOfCoeff[16] = {15, 15, 15, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	MotionNo = 19;
	GetDlgItem(IDC_BUTTON_MOTION22)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\Roboworld_clap_coeff_2Hz.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 580; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion23() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 20;
	GetDlgItem(IDC_BUTTON_MOTION23)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 900; // dim : 10 mdec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion24() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 21;
	GetDlgItem(IDC_BUTTON_MOTION24)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 500; // dim : 10 mdec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion12() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 22;
	GetDlgItem(IDC_BUTTON_MOTION12)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MOTION13)->EnableWindow(TRUE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 200; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION12)->EnableWindow(TRUE);	
}

void CGesture::OnButtonMotion25() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 23;
	GetDlgItem(IDC_BUTTON_MOTION25)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 30; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion26() 
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
	
	float scale[16] = { -0.7f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  1.0f,  1.0f};	
	//float scale[16] = { 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  0.5f,  0.5f, 0.5f, 0.5f};	
	float	Constant[16];
	float	CosCoeff[16][67];
	float	SinCoeff[16][67];
	float	sum;
	
	int		NoOfCoeff[16] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
	
	int		m;
	int		JointIndex;
	int		t;
	int		T;
	int		j;
	int		MotionNo;
	
	FILE *ifp;
	
	MotionNo = 24;
	GetDlgItem(IDC_BUTTON_MOTION26)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	ifp = fopen("C:\\user\\MotionCapture\\Hand_wave_coeff.txt","r");
	
	fseek( ifp, 0L, SEEK_SET );
	
	T = 900; // dim : 10 mdec.
	// T must be 3 times integer
	
	
	for(JointIndex=0; JointIndex < 16; JointIndex++)
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
	
	DataReset();
	
	for(t=0; t < T; t=t+3)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			for(m=0; m < NoOfCoeff[JointIndex]; m++)
			{
				if(m==0)
				{
					sum = Constant[JointIndex];
				}
				
				sum = (float)(sum + CosCoeff[JointIndex][m]*cos(2*(m+1)*PI/T*t) + SinCoeff[JointIndex][m]*sin(2*(m+1)*PI/T*t));
			}
			for(j=0;j<=3;j++)
			{
				
				if(t != 0)
				{
					theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t+j-3][JointIndex] = (float)(theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex] + (scale[JointIndex]*sum - theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t-3][JointIndex])*(1./3.)*j);
				}
			}
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion27() 
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
	
	
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 25;
	GetDlgItem(IDC_BUTTON_MOTION27)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 1200;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion28() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 26;
	GetDlgItem(IDC_BUTTON_MOTION28)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 200; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION14)->EnableWindow(TRUE);	
}

void CGesture::OnButtonMotion29() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 27;
	GetDlgItem(IDC_BUTTON_MOTION29)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 200; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	//theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
	
	//GetDlgItem(IDC_BUTTON_MOTION14)->EnableWindow(TRUE);	
}

void CGesture::OnButtonMotion30() 
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
	
	
	
	int		T;
	int		MotionNo;
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 28;
	GetDlgItem(IDC_BUTTON_MOTION30)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MOTION14)->EnableWindow(TRUE);	
	GetDlgItem(IDC_BUTTON_MOTION31)->EnableWindow(FALSE);	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 102;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonMotion31() 
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
	
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 29;
	GetDlgItem(IDC_BUTTON_MOTION31)->EnableWindow(FALSE);
	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 102; // dim : 10 msec.
	// T must be 3 times integer
	
	DataReset();
	
	for(t=0; t < T; t=t+1)
	{
		for(JointIndex=0; JointIndex < 16; JointIndex++)
		{
			theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
		}
	}
	theApp.Home(T);
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::OnButtonDspControl() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->Test_CNT_0 = 0;
	theApp.m_pSharedMemory->Test_CNT_1 = 0;
	theApp.m_pSharedMemory->Demo_4_Flag = ENABLE;
	
}

void CGesture::OnButtonDspControlOn() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->DSPS_Con_Flag = ENABLE;
}

void CGesture::OnButtonDspControlOff() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->DSPS_Con_Flag = DISABLE;
}

void CGesture::OnButtonDspControlStop() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->Demo_4_Off_Flag = ENABLE;
	theApp.m_pSharedMemory->DSPS_Con_Flag = DISABLE;
	
}

void CGesture::OnButtonSspControl() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->Test_CNT_0 = 0;
	theApp.m_pSharedMemory->Test_CNT_1 = 0;
	theApp.m_pSharedMemory->SSPS_Con_Flag = DISABLE;
	theApp.m_pSharedMemory->Demo_5_Flag = ENABLE;
}

void CGesture::OnButtonSspControlOn() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSPS_Con_Flag = ENABLE;	
}

void CGesture::OnButtonSspControlOff() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->SSPS_Con_Flag = DISABLE;
}

void CGesture::OnButtonSspControlStop() 
{
	// TODO: Add your control notification handler code here
	theApp.m_pSharedMemory->Demo_5_Off_Flag = ENABLE;
	theApp.m_pSharedMemory->SSPS_Con_Flag = DISABLE;
}

void CGesture::OnButtonSspUpdown() 
{
	// TODO: Add your control notification handler code here
	
	theApp.m_pSharedMemory->Test_CNT_0 = 0;
	theApp.m_pSharedMemory->Demo_6_Flag = ENABLE;
}





void CGesture::OnCom2Open() 
{
	// TODO: Add your control notification handler code here
	if (hCommWnd2 != m_hWnd)
	{
		hCommWnd2= m_hWnd;	// serial
	}
	if(!m_portCOM.OpenPort("COM1",115200,1)) // open com2 port baud rate 115200
	{
		AfxMessageBox(" fail..");
	}
	else
	{
		AfxMessageBox(" Success..");
		Flag_Com2_auto = 1;			// set the flag for auto read of com2
	}	
	
	GetDlgItem(IDC_Com2Open)->EnableWindow(FALSE);
}

void CGesture::OnCom2Close() 
{
	// TODO: Add your control notification handler code here
	
	m_portCOM.ClosePort();
	Flag_Com2_auto = 0;			// remove flag for auto com2 read
	
	GetDlgItem(IDC_Com2Open)->EnableWindow(TRUE);
	
}

LRESULT CGesture::OnCommunication(UINT port, LONG lParam)
{
	int size = 0;
	BYTE aByte;
	char Buffer[50];
	char cmd;
	CString output;
	
	size = (m_portCOM.m_QueueRead).GetSize();
	
	if(size==0) return 0;
	
	if(size <= 50){
		serial_cnt2++;
		
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
	
	if(Buffer[0] = char(255)){
		cmd = Buffer[1];

		/*
		int nflength = sizeof(theApp.m_pSharedMemory->MotionFlag);
		bool nfhold = false;
		
		for(int i = 0; i<nflength; i++)
		{
			bool nfTemp = theApp.m_pSharedMemory->MotionFlag[i];
			nfhold = nfhold | nfTemp;


		}

		*/

		if(!theApp.m_pSharedMemory->MotionFlagALL) //nfhold)
		{

			switch(cmd){
			case 's':					// start the tap at 45deg
				OnButtonMotion30();
				GetDlgItem(IDC_ComMotion)->SetWindowText("Start Tap");
				break;
			case 'e':					// end the tap go back to 0 deg from 45 deg
				OnButtonMotion31();
				GetDlgItem(IDC_ComMotion)->SetWindowText("End Tap");
				break;
			case 't':					// tap right elbow bend 10 deg for 0.3 sec
				if(!(theApp.m_pSharedMemory->MotionFlag[11]))
				{
					OnButtonMotion14();
					GetDlgItem(IDC_ComMotion)->SetWindowText("Tap");
				}
				else
				{
					GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
				}
				break;
			case 'c':					// close gesture window
				OnButtonClose();
				GetDlgItem(IDC_ComMotion)->SetWindowText("Close Gesture Window");
				break;
			case 'r':
				OnButtonMotionActivation();		// reset the buttons
				GetDlgItem(IDC_ComMotion)->SetWindowText("Reset Buttons");
				break;
			case 'h':
				if(!theApp.m_pSharedMemory->MotionFlag[24])
				{
					OnButtonMotion26();		// hand wave
					GetDlgItem(IDC_ComMotion)->SetWindowText("Hand Wave");
				}
				else
				{
					GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
				}

				break;
			case 'w':		// Welcome
				if(!theApp.m_pSharedMemory->MotionFlag[5])
				{
					OnButtonMotion7();
					GetDlgItem(IDC_ComMotion)->SetWindowText("Welcome");
				}
				else
				{
					GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
				}
				break;
			case 'p':
				OnCOMpoint(Buffer[2]);
				GetDlgItem(IDC_ComMotion)->SetWindowText("Point");
				break;

			case 'J':		// jaemi says stuff
				JaemiSaysChoose(Buffer[2], Buffer[3]);		// Jaemi Says Gestures
				break;
			case 'S':
				OnButtonSspUpdown();
				GetDlgItem(IDC_ComMotion)->SetWindowText("Stand One Foot");
				break;

			default:
				break;
			}

		}
		else
		{
			GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
		}
	}
	
	return 0;
	
}

void CGesture::JaemiSaysChoose(char r, int s)	// Jaemi Says Gestures
{
	// r = the choice
	// s = the speed 0 = slow, 1 = mediam, 2 = fast

	if( s >= 0 && s <4)		// sets the speed
	{
		theApp.m_pSharedMemory->JaemiSaysMotionSpeed = s;
	}
	else
	{
		theApp.m_pSharedMemory->JaemiSaysMotionSpeed = 0;
	}



	bool jTemp = false;

	for( int i = 30; i < 44; i++)
	{
		jTemp = jTemp || theApp.m_pSharedMemory->MotionFlag[i];
	}

	if(!jTemp)
	{
		switch(r){
		case 'c':		// choo choo
			OnGestureChoochoo();
			GetDlgItem(IDC_ComMotion)->SetWindowText("ChooChoo");
			break;
		case 'f':
			OnGestureFlapArms();
			GetDlgItem(IDC_ComMotion)->SetWindowText("Flap Arms");
			break;
		case 'C':
			OnGestureClapHands();
			GetDlgItem(IDC_ComMotion)->SetWindowText("Clap Hands");
		default:
			break;
		}
	}
	else
	{
		GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
	}



}

void CGesture::OnCOMpoint(char r)
{
	bool mF[5];	// motion flag check
	mF[0] = theApp.m_pSharedMemory->MotionFlag[44];
	mF[1] = theApp.m_pSharedMemory->MotionFlag[45];
	mF[2] = theApp.m_pSharedMemory->MotionFlag[46];

	if( mF[0] == FALSE && mF[1] == FALSE && mF[2] == FALSE )
	{
		switch(r){

		case 'R':
			pointRight();
			break;
		case 'L':
			pointLeft();
			break;
		case 'B':
			pointBothLeftRight();
			break;
		}
	}
	else
	{
		GetDlgItem(IDC_ComMotion)->SetWindowText("Still in Motion");
	}

}

void CGesture::OnCom2Check() 
{
	
	// TODO: Add your control notification handler code here
	OnCommunication( 2, 0);
	
}


void CGesture::pointRight()
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
	
	
	
	int		T;
	int		MotionNo;


	GetDlgItem(IDC_ComMotion)->SetWindowText("pointRight()");
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 44;	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 273;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::pointLeft()
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
	
	
	
	int		T;
	int		MotionNo;


	GetDlgItem(IDC_ComMotion)->SetWindowText("pointLeft()");
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 45;	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 273;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

void CGesture::pointBothLeftRight()
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
	
	
	
	int		T;
	int		MotionNo;


	GetDlgItem(IDC_ComMotion)->SetWindowText("pointBothLeftRight()");
	
	theApp.m_pSharedMemory->PROFTime[11] = 0;
	MotionNo = 46;	
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	
	T = 273;//7000; // dim : 10 msec.
	
	DataReset();
	
	theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
	
	theApp.m_pSharedMemory->MotionFlagALL = 1;
	theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
	
	theApp.m_pSharedMemory->PROFTime[19] = 0;
	theApp.m_pSharedMemory->MOTION_Stop = 0;
}

/*
BOOL CGesture::OnCommand(WPARAM wParam, LPARAM lParam) 
{
// TODO: Add your specialized code here and/or call the base class

  return CDialog::OnCommand(wParam, lParam);
  }
  
	BOOL CGesture::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
	{
	// TODO: Add your specialized code here and/or call the base class
	OnCommunication( 2, 0);
	return CDialog::OnNotify(wParam, lParam, pResult);
	}
*/
void CGesture::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnCommunication( 2, 0);
	CDialog::OnTimer(nIDEvent);
}

//##################### PTM Demo Gestures start Here #################################

void CGesture::OnGestureRaiseRightHand() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 30;
	
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RAISE_RIGHT_HAND)->EnableWindow(FALSE);
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 150;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionLength[MotionNo] = 0;
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureRaiseRightArm() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 31;
	
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RAISE_RIGHT_ARM)->EnableWindow(FALSE);
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 120;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureRightArmCircle() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 32;
	
	
	//theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RIGHT_ARM_CIRCLE)->EnableWindow(FALSE);
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 360;
			break;
		case 2:
			T = 240;
			break;
		case 0:
		default:
			T = 660;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureRaiseLeftHand() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 33;
	
	
	//theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RAISE_LEFT_HAND)->EnableWindow(FALSE);
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 120;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureRaiseLeftArm() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 34;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RAISE_LEFT_ARM)->EnableWindow(FALSE);
		/*
		//theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 120;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureLeftArmCircle() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 35;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_LEFT_ARM_CIRCLE)->EnableWindow(FALSE);
		
		//theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 360;
			break;
		case 2:
			T = 240;
			break;
		case 0:
		default:
			T = 660;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureTouchHead() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 36;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_TOUCH_HEAD)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 300;
			break;
		case 2:
			T = 231;
			break;
		case 0:
		default:
			T = 381;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureTouchNose() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 37;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_TOUCH_NOSE)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 300;
			break;
		case 2:
			T = 231;
			break;
		case 0:
		default:
			T = 381;
			break;	
		}
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureTipHat() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 38;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_TIP_HAT)->EnableWindow(FALSE);
		
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 200;
			break;
		case 2:
			T=150;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureRubStomach() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 39;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_RUB_STOMACH)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 309;
			break;
		case 2:
			T = 210;
			break;
		case 0:
		default:
			T = 408;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}
void CGesture::OnGestureChoochoo() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 40;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_CHOOCHOO)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 306;
			break;
		case 2:
			T = 261;
			break;
		case 0:
		default:
			T = 399;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureClapHands() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 41;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_CLAP_HANDS)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 270;
			break;
		case 2:
			T = 201;
			break;
		case 0:
		default:
			T = 399;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureFlapArms() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 42;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_FLAP_ARMS)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 270;
			break;
		case 2:
			T = 201;
			break;
		case 0:
		default:
			T = 399;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

void CGesture::OnGestureHandsOnHips() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 43;
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_HANDS_ON_HIPS)->EnableWindow(FALSE);
		/*
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = FALSE;
		
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 300;
			break;
		case 2:
			T = 180;
			break;
		case 0:
		default:
			T = 501;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}

//Add radio button functions here

void CGesture::OnGestureSpeedSlow()
{
	//only allow speed changes when Jaemi is at rest
	//if(theApp.m_pSharedMemory->MotionFlagALL == FALSE){	theApp.m_pSharedMemory->JaemiSaysMotionSpeed=0;}
	theApp.m_pSharedMemory->JaemiSaysMotionSpeed=0;
}

void CGesture::OnGestureSpeedMedium()
{
	//if(theApp.m_pSharedMemory->MotionFlagALL == FALSE){theApp.m_pSharedMemory->JaemiSaysMotionSpeed=1;}
	theApp.m_pSharedMemory->JaemiSaysMotionSpeed=1;
}

void CGesture::OnGestureSpeedFast()
{
	//if(theApp.m_pSharedMemory->MotionFlagALL == FALSE){theApp.m_pSharedMemory->JaemiSaysMotionSpeed=2;}
	theApp.m_pSharedMemory->JaemiSaysMotionSpeed=2;
}

void CGesture::OnJaemiSaysScript1() 
{
	//Code to run series of gestures
	//theApp.m_pSharedMemory->CurrentScript=1;
	theApp.m_pSharedMemory->ScriptLoaded=1;
	theApp.m_pSharedMemory->ScriptIndex=0;
	//theApp.m_pSharedMemory->JaemiSaysMotionSpeed=0;
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_MEDIUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_FAST)->EnableWindow(FALSE);
}

void CGesture::OnJaemiSaysScript2() 
{
	//Code to run series of gestures
	theApp.m_pSharedMemory->ScriptLoaded=2;
	theApp.m_pSharedMemory->ScriptIndex=0;
	//theApp.m_pSharedMemory->JaemiSaysMotionSpeed=0;
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_MEDIUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_GESTURE_SPEED_FAST)->EnableWindow(FALSE);
}



void CGesture::OnJaemiSaysCancel() 
{
	//theApp.m_pSharedMemory->CurrentScript=2;
	theApp.m_pSharedMemory->ScriptLoaded=0;
	theApp.m_pSharedMemory->ScriptIndex=0;
	GetDlgItem(IDC_GESTURE_SPEED_SLOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_SPEED_MEDIUM)->EnableWindow(TRUE);
	GetDlgItem(IDC_GESTURE_SPEED_FAST)->EnableWindow(TRUE);
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_JAEMI_SAYS_SCRIPT2)->EnableWindow(TRUE);
}


void CGesture::OnGestureAuxBendRightElbow() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 47;
	
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_AUX_BEND_RIGHT_ELBOW)->EnableWindow(FALSE); 
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 120;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = 600;
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}


void CGesture::OnGestureAuxUnlv() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 48;
	T = 8000;
	
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_AUX_UNLV)->EnableWindow(FALSE); 
		/*
		switch(theApp.m_pSharedMemory->JaemiSaysMotionSpeed)
		{
		case 1:
			T = 201;
			break;
		case 2:
			T = 120;
			break;
		case 0:
		default:
			T = 300;
			break;	
		}
		
		DataReset();
		
		for(t=0; t < T; t=t+1)
		{
			for(JointIndex=0; JointIndex < 16; JointIndex++)
			{
				theApp.m_pSharedMemory->UpBody_MTN_CAP_Data[t][JointIndex] = (float)0.0f;
			}
		}
		theApp.Home(T);
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		*/
		
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		//theApp.m_pSharedMemory->PROFTime[11] = 0;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}
}


void CGesture::OnHelloWorld() 
{
	int		JointIndex;
	int		t;
	int		T;
	
	int		MotionNo;
	MotionNo = 49;
	T = ; // Set max time.
	
	if(theApp.m_pSharedMemory->MotionFlag[MotionNo] == FALSE)
	{
		GetDlgItem(IDC_GESTURE_HELLO_WORLD)->EnableWindow(FALSE); 
		theApp.m_pSharedMemory->MotionLength[MotionNo] = T;
		theApp.m_pSharedMemory->MotionFlagALL = 1;
		theApp.m_pSharedMemory->MotionFlag[MotionNo] = TRUE;
		
		theApp.m_pSharedMemory->PROFTime[19] = 0;
		theApp.m_pSharedMemory->MOTION_Stop = 0;
	}	
}

