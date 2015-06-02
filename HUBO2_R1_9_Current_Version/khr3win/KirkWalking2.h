#if !defined(AFX_KIRKWALKING2_H__573D5599_F73F_4671_947B_4C8B75466A6B__INCLUDED_)
#define AFX_KIRKWALKING2_H__573D5599_F73F_4671_947B_4C8B75466A6B__INCLUDED_

#include "Gesture.h"	// Added by ClassView
#include "CommThread.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KirkWalking2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKirkWalking2 dialog
class CCANwin;

class CKhr3winDlg;

class CGesture;

class CKirkWalking2 : public CDialog
{
// Construction
public:
	CGesture dg_Gesture;
	char serial_cnt;
	CGesture *m_pGesture;
	int Walking_Mode;	// 0 : Marking,  1 : FWD Walking,  -1 : BWD Walking
						// 2 : R-Side Walking,  3 : L-Side Walking
						// 4 : CW Turning,  5 : CCW Turning	
						// 6 : Stop;
						// 7 : UP , 8 : DN
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
	void Init();
	CKirkWalking2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKirkWalking2)
	enum { IDD = IDD_DIALOG_KIRK2_WALKING };
	float	m_BC_Y_AMP;
	float	m_FOOT_Z_AMP;
	float	m_R_comp_angle;
	float	m_L_comp_angle;
	float	m_StepLength;
	float	m_SideStepLength;
	float	m_TurningAngle;
	BOOL	m_WalkTestMode;
	float	m_LORollGain;
	float	m_LOPitchGain;
	float	m_Temp1;
	float	m_Temp2;
	float	m_AmpTemp1;
	UINT	m_StepTime;
	BOOL	m_CtrlModeDamping;
	BOOL	m_CtrlModePosture;
	BOOL	m_ArmMotion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKirkWalking2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCommThread m_portCOM;	// serial
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CKirkWalking2)
	afx_msg void OnButtonWalkInPlace();
	afx_msg void OnButtonStop();
	virtual void OnOK();
	afx_msg void OnButtonWlkReady();
	afx_msg void OnButtonHome();
	afx_msg void OnButtonGoFwd();
	afx_msg void OnButtonGoBwd();
	afx_msg void OnButtonLSide();
	afx_msg void OnButtonRSide();
	afx_msg void OnButtonCcw();
	afx_msg void OnButtonCw();
	afx_msg void OnButtonTimerReset();
	afx_msg void OnCtrlModeDamping();
	afx_msg void OnCtrlModePosture();
	afx_msg void OnButtonGesture();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnCommunication(UINT, LONG);	// serial
	afx_msg void OnButtonCom1open();
	afx_msg void OnButtonCom1close();
	afx_msg void OnButtonNoWalkInPlace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KIRKWALKING2_H__573D5599_F73F_4671_947B_4C8B75466A6B__INCLUDED_)
