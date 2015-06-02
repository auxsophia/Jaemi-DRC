#if !defined(AFX_POSITIONCONTROL_H__7AB22B54_FA9F_4339_B8F5_2323975E1A41__INCLUDED_)
#define AFX_POSITIONCONTROL_H__7AB22B54_FA9F_4339_B8F5_2323975E1A41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PositionControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPositionControl dialog
class CCANwin;

class CKhr3winDlg;

class CPositionControl : public CDialog
{
// Construction
public:
	float m_POS[TOTAL_MTR_NUM];
	float m_RPM[TOTAL_JMC_NUM];
	void POS_CTRL_Run(int numJMC);
	void Close();
	void Init();
	CPositionControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPositionControl)
	enum { IDD = IDD_DIALOG_POSITION_CONTROL };
	float	m_Pos_RHR;
	float	m_Pos_RHY;
	float	m_RPM_JMC0;
	float	m_RPM_JMC1;
	float	m_RPM_JMC2;
	float	m_RPM_JMC3;
	float	m_RPM_JMC4;
	float	m_RPM_JMC5;
	float	m_RPM_JMC6;
	float	m_RPM_JMC7;
	float	m_Pos_LAP;
	float	m_Pos_LAR;
	float	m_Pos_LHP;
	float	m_Pos_LHR;
	float	m_Pos_LHY;
	float	m_Pos_RAP;
	float	m_Pos_RAR;
	float	m_Pos_RHP;
	float	m_Pos_RKN;
	float	m_Pos_LKN;
	float	m_RPM_JMC10;
	float	m_RPM_JMC11;
	float	m_Pos_LSP;
	float	m_Pos_LEB;
	float	m_Pos_LSR;
	float	m_Pos_LSY;
	float	m_Pos_REB;
	float	m_Pos_RSP;
	float	m_Pos_RSR;
	float	m_Pos_RSY;
	float	m_RPM_JMC8;
	float	m_RPM_JMC9;
	float	m_RPM_EJMC0;
	float	m_RPM_EJMC1;
	float	m_RPM_EJMC2;
	float	m_Pos_RW1;
	float	m_Pos_RW2;
	float	m_Pos_RWY;
	float	m_Pos_LW1;
	float	m_Pos_LW2;
	float	m_Pos_LWY;
	float	m_Pos_NK1;
	float	m_Pos_NK2;
	float	m_Pos_NKY;
	float	m_RPM_EJMC3;
	float	m_Pos_WST;
	//}}AFX_DATA

	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPositionControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CPositionControl)
	afx_msg void OnButtonClose();
	afx_msg void OnButtonRun0();
	afx_msg void OnButtonRun1();
	afx_msg void OnButtonRun2();
	afx_msg void OnButtonRun3();
	afx_msg void OnButtonRun4();
	afx_msg void OnButtonRun5();
	afx_msg void OnButtonRun6();
	afx_msg void OnButtonRun7();
	afx_msg void OnButtonRun8();
	afx_msg void OnButtonRun9();
	afx_msg void OnButtonRun10();
	afx_msg void OnButtonRun11();
	afx_msg void OnButtonRun12();
	afx_msg void OnButtonRun13();
	afx_msg void OnButtonPose1();
	afx_msg void OnButtonPoseHome();
	afx_msg void OnButtonRun17();
	afx_msg void OnButtonRun18();
	afx_msg void OnButtonRun19();
	afx_msg void OnButtonRun23();
	afx_msg void OnButtonRun24();
	afx_msg void OnButtonRun25();
	afx_msg void OnButtonRun16();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSITIONCONTROL_H__7AB22B54_FA9F_4339_B8F5_2323975E1A41__INCLUDED_)
