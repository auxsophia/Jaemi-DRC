#if !defined(AFX_WALK00TESTDLG_H__91FCF33E_DBC4_470B_9E43_7923A1906224__INCLUDED_)
#define AFX_WALK00TESTDLG_H__91FCF33E_DBC4_470B_9E43_7923A1906224__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Walk00TestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWalk00TestDlg dialog
#include "Board.h"

class CKhr3winDlg;
class CWalk00TestDlg : public CDialog
{
// Construction
public:
	float m_Board_LFootZ;
	float m_Board_RFootZ;
	float m_Board_LFootY;
	float m_Board_RFootY;
	float m_Board_LFootX;
	float m_Board_RFootX;
	void UpdateBoardPoint();
	void InitBoard();
	void DispXYZ();
	void ButtonControl(int Msg);
	void Init();
	CWalk00TestDlg(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
// Dialog Data
	//{{AFX_DATA(CWalk00TestDlg)
	enum { IDD = IDD_DIALOG_WALK };
	CButton	m_ButtonCTRLOff;
	CButton	m_ButtonCTRLOn;
	CButton	m_Button_SSP_Save;
	CButton	m_Button_R_Tick;
	CButton	m_Button_P_Tick;
	CButton	m_ButtonOL_R_SSP;
	CButton	m_ButtonOL_L_SSP;
	CButton	m_Button_FT_Null;
	CButton	m_SSP_CTRL_Off;
	CButton	m_SSP_CTRL_On;
	CButton	m_SSP_Off;
	CButton	m_SSP_On;
	CButton	m_DSP_Pose_Set;
	CButton	m_DSP_Pose_Reset;
	CButton	m_DSP_Off;
	CButton	m_DSP_On;
	CButton	m_ButtonGraph;
	CBoard  m_Board_FootX;
	CBoard  m_Board_FootY;
	CBoard  m_Board_FootZ;
	float	m_SideAmplitude;
	float	m_SwayAmplitude;
	int		m_DSP_During;
	float	m_EDIT_OveralGLP;
	float	m_EDIT_OveralGLR;
	float	m_EDIT_OveralGRP;
	float	m_EDIT_OveralGRR;
	float	m_Vib_Gain;
	float	m_Vib_GainY;
	float	m_inAMPX;
	float	m_inAMPY;
	float	m_inFREQ;
	UINT	m_NumShake;
	float	m_ZMP_OveralY;
	float	m_ZMP_OveralX;
	float	m_Push_Amp;
	float	m_Push_Hz;
	float	m_Torso_CTRL_Left_P;
	float	m_Torso_CTRL_Left_R;
	float	m_Torso_CTRL_Right_P;
	float	m_Torso_CTRL_Right_R;
	float	m_AnkleAmplitude;
	float	m_AnkleFreq;
	float	m_AnkleAmp;
	float	m_AnkleFq;
	float	m_WristAmp;
	float	m_WristHz;
	float	m_ShoulderHz;
	float	m_ShoulderPitchAmp;
	float	m_ShoulderRollAmp;
	float	m_I_Gain;
	float	m_HandAmp;
	float	m_HandFreq;
	int		m_WristMotionMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalk00TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWalk00TestDlg)
	afx_msg void OnButtonGraph();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonReady();
	afx_msg void OnButtonHome();
	afx_msg void OnButtonWalk01();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonDspPose();
	afx_msg void OnButtonDspOn();
	afx_msg void OnButtonDspOff();
	afx_msg void OnButtonDspPoseExit();
	afx_msg void OnButtonSspOn();
	afx_msg void OnButtonSspOff();
	afx_msg void OnButtonSspCtrlOn();
	afx_msg void OnButtonSspCtrlOff();
	afx_msg void OnButtonFtNull();
	afx_msg void OnButtonOlLSsp();
	afx_msg void OnButtonOlRSsp();
	afx_msg void OnButtonRollTick();
	afx_msg void OnButtonPitchTick();
	afx_msg void OnButtonSspSave();
	afx_msg void OnButtonOverallGSet();
	afx_msg void OnButtonCtrlOn();
	afx_msg void OnButtonCtrlOff();
	afx_msg void OnButtonXAdd();
	afx_msg void OnButtonXSub();
	afx_msg void OnButtonYAdd();
	afx_msg void OnButtonYSub();
	afx_msg void OnButtonZmpTestOn();
	afx_msg void OnButtonZmpTestOff();
	afx_msg void OnButtonZmpOn();
	afx_msg void OnButtonZmpOff();
	afx_msg void OnButtonSspPushGo();
	afx_msg void OnButtonSspPushStop();
	afx_msg void OnButtonTorsoCtrlOn();
	afx_msg void OnButtonTorsoCtrlOff();
	afx_msg void OnButtonTimeReset();
	afx_msg void OnButtonFreqStart();
	afx_msg void OnButtonFreqStop();
	afx_msg void OnButtonFreqStart2();
	afx_msg void OnButtonFreqStop2();
	afx_msg void OnButtonWristMotionGo();
	afx_msg void OnButtonWristMotionStop();
	afx_msg void OnButtonShoulderMotionGo();
	afx_msg void OnButtonShoulderMotionStop();
	afx_msg void OnButtonHandMotionGo();
	afx_msg void OnButtonHandMotionStop();
	afx_msg void OnButtonControllOff();
	afx_msg void OnButtonControllOn();
	afx_msg void OnButtonGripOn();
	afx_msg void OnButtonGripOff();
	afx_msg void OnButtonGripStop();
	afx_msg void OnButtonHandup();
	afx_msg void OnButtonHanddown();
	afx_msg void OnButtonGripOn2();
	//}}AFX_MSG
	CKhr3winDlg* m_pKhr3winDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALK00TESTDLG_H__91FCF33E_DBC4_470B_9E43_7923A1906224__INCLUDED_)
