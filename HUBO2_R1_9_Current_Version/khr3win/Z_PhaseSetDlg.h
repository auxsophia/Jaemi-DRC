#if !defined(AFX_Z_PHASESETDLG_H__22EFCF21_C121_47BD_AF08_64AE7F58134D__INCLUDED_)
#define AFX_Z_PHASESETDLG_H__22EFCF21_C121_47BD_AF08_64AE7F58134D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Z_PhaseSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseSetDlg dialog
class CKhr3winDlg;
class CZ_PhaseSetDlg : public CDialog
{
// Construction
public:
	void autoSetup();
	long m_Z_ref[TOTAL_MTR_NUM];
	long CalPulse1(int MotorNo);
	long CalPulse(int MotorNo);

	void Init();
	CZ_PhaseSetDlg(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

// Dialog Data
	//{{AFX_DATA(CZ_PhaseSetDlg)
	enum { IDD = IDD_DIALOG_Z_PHASE };
	long	m_LHP_Offset;
	long	m_LHR_Offset;
	long	m_LKP_Offset;
	long	m_RHP_Offset;
	long	m_RHR_Offset;
	long	m_RKP_Offset;
	long	m_LHY_Offset;
	long	m_LAP_Offset;
	long	m_LAR_Offset;
	long	m_RAP_Offset;
	long	m_RAR_Offset;
	long	m_RHY_Offset;
	long	m_LAP_Offset_Rev;
	long	m_LAR_Offset_Rev;
	long	m_LHP_Offset_Rev;
	long	m_LHR_Offset_Rev;
	long	m_LHY_Offset_Rev;
	long	m_LKP_Offset_Rev;
	long	m_RAP_Offset_Rev;
	long	m_RAR_Offset_Rev;
	long	m_RHP_Offset_Rev;
	long	m_RHR_Offset_Rev;
	long	m_RHY_Offset_Rev;
	long	m_RKP_Offset_Rev;
	BOOL	m_ZPosRefFlag;
	long	m_LEB_Offset;
	long	m_LEB_Offset_Rev;
	long	m_LSP_Offset;
	long	m_LSP_Offset_Rev;
	long	m_LSR_Offset;
	long	m_LSR_Offset_Rev;
	long	m_LSY_Offset;
	long	m_LSY_Offset_Rev;
	long	m_REB_Offset;
	long	m_REB_Offset_Rev;
	long	m_RSP_Offset;
	long	m_RSP_Offset_Rev;
	long	m_RSR_Offset;
	long	m_RSR_Offset_Rev;
	long	m_RSY_Offset;
	long	m_RSY_Offset_Rev;
	long	m_LWY_Offset;
	long	m_LWY_Offset_Rev;
	long	m_RWY_Offset;
	long	m_RWY_Offset_Rev;
	long	m_WST_Offset;
	long	m_WST_Offset_Rev;
	long	m_NKY_Offset;
	long	m_NKY_Offset_Rev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZ_PhaseSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZ_PhaseSetDlg)
	afx_msg void OnButtonExit();
	afx_msg void OnButtonEncShow();
	afx_msg void OnButtonRhrZPos();
	afx_msg void OnButtonRhpZPos();
	afx_msg void OnButtonRkpZPos();
	afx_msg void OnButtonLhrZPos();
	afx_msg void OnButtonLhpZPos();
	afx_msg void OnButtonLkpZPos();
	afx_msg void OnButtonRhrGoOffset();
	afx_msg void OnButtonRhpGoOffset();
	afx_msg void OnButtonRkpGoOffset();
	afx_msg void OnButtonLhrGoOffset();
	afx_msg void OnButtonLhpGoOffset();
	afx_msg void OnButtonLkpGoOffset();
	afx_msg void OnButtonLhyZPos();
	afx_msg void OnButtonRhyZPos();
	afx_msg void OnButtonLapZPos();
	afx_msg void OnButtonLarZPos();
	afx_msg void OnButtonRapZPos();
	afx_msg void OnButtonRarZPos();
	afx_msg void OnButtonLhyGoOffset();
	afx_msg void OnButtonLapGoOffset();
	afx_msg void OnButtonLarGoOffset();
	afx_msg void OnButtonRhyGoOffset();
	afx_msg void OnButtonRapGoOffset();
	afx_msg void OnButtonRarGoOffset();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonLspZPos();
	afx_msg void OnButtonLsrZPos();
	afx_msg void OnButtonLsyZPos();
	afx_msg void OnButtonLebZPos();
	afx_msg void OnButtonRspZPos();
	afx_msg void OnButtonRsyZPos();
	afx_msg void OnButtonRsrZPos();
	afx_msg void OnButtonRebZPos();
	afx_msg void OnButtonRspGoOffset();
	afx_msg void OnButtonRsrGoOffset();
	afx_msg void OnButtonRsyGoOffset();
	afx_msg void OnButtonRebGoOffset();
	afx_msg void OnButtonLspGoOffset();
	afx_msg void OnButtonLsrGoOffset();
	afx_msg void OnButtonLsyGoOffset();
	afx_msg void OnButtonLebGoOffset();
	afx_msg void OnButtonRwtZPos();
	afx_msg void OnButtonLwtZPos();
	afx_msg void OnButtonRwyGoOffset();
	afx_msg void OnButtonLhdZPos();
	afx_msg void OnButtonRhdZPos();
	afx_msg void OnButtonWstZPos();
	afx_msg void OnButtonWstGoOffset();
	afx_msg void OnButtonNkyZPos();
	afx_msg void OnButtonNkyGoOffset();
	afx_msg void OnButtonZRefSave();
	afx_msg void OnCheckZPosRef();
	afx_msg void OnAutoSetup();
	afx_msg void OnautoSetupStop();
	//}}AFX_MSG
	
	CKhr3winDlg* m_pKhr3winDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Z_PHASESETDLG_H__22EFCF21_C121_47BD_AF08_64AE7F58134D__INCLUDED_)
