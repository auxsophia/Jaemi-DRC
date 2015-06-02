#if !defined(AFX_GESTURE_H__791ADFCA_7F9C_44F7_A101_28D6CC67DFF9__INCLUDED_)
#define AFX_GESTURE_H__791ADFCA_7F9C_44F7_A101_28D6CC67DFF9__INCLUDED_
#include "CommThread.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Gesture.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGesture dialog
class CCANwin;

class CKirkWalking2;

class CGesture : public CDialog
{
// Construction
public:
	void pointRight();
	void pointLeft();
	void pointBothLeftRight();
	void OnCOMpoint(char r);
	void JaemiSaysChoose(char r, int s);
	char serial_cnt2;
	void DataReset();
	CKirkWalking2 *m_pKirkWalking2;
	void SetParentWindow(CKirkWalking2* m_KirkWalking2) { m_pKirkWalking2  = m_KirkWalking2; }
	CGesture(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CGesture)
	enum { IDD = IDD_DIALOG_GESTURE };
	int		m_WristMotionMode;
	float	m_WristAmp;
	float	m_WristHz;
	float	m_ShoulderHz;
	float	m_ShoulderRollAmp;
	float	m_ShoulderPitchAmp;
	int		m_GripDuty;
	BOOL	m_LeftHandActivation;
	BOOL	m_RightHandActivation;
	float	m_ElbowAmp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGesture)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
//	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCommThread m_portCOM;	// serial
	// Generated message map functions
	//{{AFX_MSG(CGesture)
	afx_msg void OnButtonClose();
	afx_msg void OnButtonMotion1();
	afx_msg void OnButtonMotion2();
	afx_msg void OnButtonMotion3();
	afx_msg void OnButtonMotion4();
	afx_msg void OnButtonControllOff();
	afx_msg void OnButtonControllOn();
	afx_msg void OnButtonGripOn();
	afx_msg void OnButtonGripOff();
	afx_msg void OnButtonGripStop();
	afx_msg void OnButtonGripOn2();
	afx_msg void OnButtonHandup();
	afx_msg void OnButtonHanddown();
	afx_msg void OnButtonWristMotionGo();
	afx_msg void OnButtonWristMotionStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonShoulderMotionGo();
	afx_msg void OnButtonShoulderMotionStop();
	afx_msg void OnButtonMotion5();
	afx_msg void OnButtonMotion6();
	afx_msg void OnButtonMotion7();
	afx_msg void OnButtonMotion8();
	afx_msg void OnButtonMotion9();
	afx_msg void OnButtonMotion10();
	afx_msg void OnButtonShakeHandsStart();
	afx_msg void OnButtonShakeHandsStop();
	afx_msg void OnButtonMotion11();
	afx_msg void OnButtonMotion13();
	afx_msg void OnButtonMotion14();
	afx_msg void OnButtonMotion15();
	afx_msg void OnButtonMotion16();
	afx_msg void OnButtonMotion17();
	afx_msg void OnButtonMotion18();
	afx_msg void OnButtonMotion19();
	afx_msg void OnButtonMotionActivation();
	afx_msg void OnCheckRightHand();
	afx_msg void OnCheckLeftHand();
	afx_msg void OnButtonMotion20();
	afx_msg void OnButtonMotion21();
	afx_msg void OnButtonMotion22();
	afx_msg void OnButtonMotion23();
	afx_msg void OnButtonMotion24();
	afx_msg void OnButtonMotion12();
	afx_msg void OnButtonMotion25();
	afx_msg void OnButtonMotion26();
	afx_msg void OnButtonMotion27();
	afx_msg void OnButtonMotion28();
	afx_msg void OnButtonMotion29();
	afx_msg void OnButtonMotion30();
	afx_msg void OnButtonMotion31();
	afx_msg void OnButtonDspControl();
	afx_msg void OnButtonDspControlOn();
	afx_msg void OnButtonDspControlOff();
	afx_msg void OnButtonDspControlStop();
	afx_msg void OnButtonSspControl();
	afx_msg void OnButtonSspControlOn();
	afx_msg void OnButtonSspControlOff();
	afx_msg void OnButtonSspControlStop();
	afx_msg void OnButtonSspUpdown();
	afx_msg void OnCom2Open();
	afx_msg void OnCom2Close();
	afx_msg LONG OnCommunication(UINT, LONG);	// serial
	afx_msg void OnCom2Check();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGestureRaiseRightHand();
	afx_msg void OnGestureRaiseRightArm();
	afx_msg void OnGestureRightArmCircle();
	afx_msg void OnGestureRaiseLeftHand();
	afx_msg void OnGestureRaiseLeftArm();
	afx_msg void OnGestureLeftArmCircle();
	afx_msg void OnGestureTouchHead();
	afx_msg void OnGestureTipHat();
	afx_msg void OnGestureTouchNose();
	afx_msg void OnGestureClapHands();
	afx_msg void OnGestureRubStomach();
	afx_msg void OnGestureFlapArms();
	afx_msg void OnGestureChoochoo();
	afx_msg void OnGestureHandsOnHips();
	afx_msg void OnGestureSpeedSlow();
	afx_msg void OnGestureSpeedMedium();
	afx_msg void OnGestureSpeedFast();
	afx_msg void OnJaemiSaysScript1();
	afx_msg void OnJaemiSaysScript2();
	afx_msg void OnJaemiSaysCancel();
	afx_msg void OnGestureAuxBendRightElbow();
	afx_msg void OnGestureRaiseRightHand2();
	afx_msg void OnGestureAuxUnlv();
	afx_msg void OnHelloWorld();
	afx_msg void OnGestureHelloWorld();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GESTURE_H__791ADFCA_7F9C_44F7_A101_28D6CC67DFF9__INCLUDED_)
