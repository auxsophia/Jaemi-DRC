// khr3winDlg.h : header file
//

#if !defined(AFX_KHR3WINDLG_H__39AF0425_866D_4655_A97C_FDDB951EF7DE__INCLUDED_)
#define AFX_KHR3WINDLG_H__39AF0425_866D_4655_A97C_FDDB951EF7DE__INCLUDED_

#include "KirkWalking2.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKhr3winDlg dialog
#include "CANwin.h"
#include "EncReadDlg.h"
#include "FT_ReadDlg.h"
#include "TiltReadDlg.h"
#include "OpenLoopTestDlg.h"
#include "PositionControl.h"
#include "UtilityWin.h"
#include "Walk00TestDlg.h"
#include "Z_PhaseSetDlg.h"
#include "ZMPZeroDlg.h"
#include "WalkingExpDlg.h"
#include "ParameterSetting.h"	// Added by ClassView
#include "GainSet.h"	// Added by ClassView
#include "MotorState.h"
//#include "KirkWalking.h"	// Added by ClassView

class CKhr3winDlg : public CDialog
{
// Construction
public:
	CMotorState m_MotorState;
	void CreateMotorState();
	CKirkWalking2 m_KirkWalking2Dlg;
	void CreateKirkWalkingDlg();
	//KirkWalking m_KirkWalkingDlg;
	void GainSet(int MotorNo);
	void CreateGainSetting();
	CGainSet m_GainSetting;
	void LoadParameter();
	CParameterSetting ParaInit;
	void CreateParameterSetting();
	CParameterSetting m_ParameterSetting;
	void CreateWalkingExpDlg();
	void CreateZ_PhaseDlg();
	void CreateWalkDlg();
	void SaveLog();
	void CreatePOSTestDlg();
	void InitSharedMemory();
	
	void RTXOFF();
	void RTXON();
	
	void CANOFF();
	void CANON();

	void CreateEncDlg();
	void CreateFTDlg();
	void CreateTiltDlg();
	void CreateOLTestDlg();

	void ButtonControl(int Msg);
	void Close();
	CKhr3winDlg(CWnd* pParent = NULL);	// standard constructor

	CFT_ReadDlg			m_FT_ReadDlg;
	CTiltReadDlg		m_TiltReadDlg;
	CWalk00TestDlg		m_Walk00TestDlg;
	CWalkingExpDlg		m_WalkingExpDlg;

//	Dialog Data
	//{{AFX_DATA(CKhr3winDlg)
	enum { IDD = IDD_KHR3WIN_DIALOG };
	CButton	m_ButtonMotorState;
	CButton	m_ButtonKirkWalking;
	CButton	m_ButtonGainSetting;
	CButton	m_ButtonParameterSetting;
	CButton	m_ButtonWalking;
	CButton	m_ButtonZ_Phase;
	CButton	m_ButtonUtilityWin;
	CButton	m_ButtonWalk;
	CButton	m_ButtonPOSTest;
	CButton	m_ButtonOLTest;
	CButton	m_ButtonRTXOn;
	CButton	m_ButtonEncRead;
	CButton m_ButtonFTRead;
	CButton	m_ButtonTiltRead;
	CButton	m_ButtonCanOn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKhr3winDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	CCANwin				m_CANwin;
	CEncReadDlg			m_EncReadDlg;
	COpenLoopTestDlg	m_OpenLoopTestDlg;
	CPositionControl	m_PositionControlDlg;
	CUtilityWin			m_UtilityWinDlg;

	CZ_PhaseSetDlg		m_Z_PhaseSetDlg;
	CZMPZeroDlg			m_ZMPZeroDlg;

	// Generated message map functions
	//{{AFX_MSG(CKhr3winDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCanOn();
	afx_msg void OnButtonRtxOn();
	afx_msg void OnButtonEncRead();
	afx_msg void OnButtonFtRead();
	afx_msg void OnButtonTiltRead();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonExit();
	afx_msg void OnButtonOpenLoopTest();
	afx_msg void OnButtonPositionCtrlTest();
	afx_msg void OnButtonEncZero();
	afx_msg void OnButtonSavelog();
	afx_msg void OnButtonCtrlOff();
	afx_msg void OnButtonWalk();
	afx_msg void OnButtonUtil();
	afx_msg void OnButtonZPhase();
	afx_msg void OnButtonZmpZero();
	afx_msg void OnButtonWalking();
	afx_msg void OnBUTTONParameters();
	afx_msg void OnButtonGainSet();
	afx_msg void OnButtonKirkWalkiing();
	afx_msg void OnButtonMotorState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KHR3WINDLG_H__39AF0425_866D_4655_A97C_FDDB951EF7DE__INCLUDED_)
