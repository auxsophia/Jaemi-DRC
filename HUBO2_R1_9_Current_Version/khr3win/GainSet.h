#if !defined(AFX_GAINSET_H__A8D9D20D_1D1B_488D_85CF_053DBB2B87D7__INCLUDED_)
#define AFX_GAINSET_H__A8D9D20D_1D1B_488D_85CF_053DBB2B87D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GainSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGainSet dialog
class CCANwin;

class CKhr3winDlg;

class CGainSet : public CDialog
{
// Construction
public:
	void GainSave();
	void GainLoad();
	void Init();
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
	CGainSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGainSet)
	enum { IDD = IDD_DIALOG_GAIN_SETTING };
	long	m_LAP_Kd0;
	long	m_LAP_Kd1;
	long	m_LAP_Ki0;
	long	m_LAP_Ki1;
	long	m_LAP_Kp0;
	long	m_LAP_Kp1;
	long	m_LAR_Kd0;
	long	m_LAR_Kd1;
	long	m_LAR_Ki0;
	long	m_LAR_Ki1;
	long	m_LAR_Kp0;
	long	m_LAR_Kp1;
	long	m_LHP_Kd0;
	long	m_LHP_Kd1;
	long	m_LHP_Ki0;
	long	m_LHP_Ki1;
	long	m_LHP_Kp0;
	long	m_LHP_Kp1;
	long	m_LHR_Kd0;
	long	m_LHR_Kd1;
	long	m_LHR_Ki0;
	long	m_LHR_Ki1;
	long	m_LHR_Kp1;
	long	m_LHY_Kd0;
	long	m_LHY_Kd1;
	long	m_LHY_Ki0;
	long	m_LHY_Ki1;
	long	m_LHY_Kp0;
	long	m_LHY_Kp1;
	long	m_LKN_Kd0;
	long	m_LKN_Kd1;
	long	m_LKN_Ki0;
	long	m_LKN_Ki1;
	long	m_LKN_Kp0;
	long	m_LKN_Kp1;
	long	m_RAP_Kd0;
	long	m_RAP_Kd1;
	long	m_RAP_Ki0;
	long	m_RAP_Ki1;
	long	m_RAP_Kp0;
	long	m_RAP_Kp1;
	long	m_RAR_Kd0;
	long	m_RAR_Kd1;
	long	m_RAR_Ki0;
	long	m_RAR_Ki1;
	long	m_RAR_Kp0;
	long	m_RAR_Kp1;
	long	m_RHP_Kd0;
	long	m_RHP_Kd1;
	long	m_RHP_Ki0;
	long	m_RHP_Ki1;
	long	m_RHP_Kp0;
	long	m_RHP_Kp1;
	long	m_RHR_Kd0;
	long	m_RHR_Kd1;
	long	m_RHR_Ki0;
	long	m_RHR_Ki1;
	long	m_RHR_Kp0;
	long	m_RHR_Kp1;
	long	m_RHY_Kd0;
	long	m_RHY_Kd1;
	long	m_RHY_Ki0;
	long	m_RHY_Ki1;
	long	m_RHY_Kp0;
	long	m_RHY_Kp1;
	long	m_RKN_Kd0;
	long	m_RKN_Kd1;
	long	m_RKN_Ki0;
	long	m_RKN_Ki1;
	long	m_RKN_Kp0;
	long	m_RKN_Kp1;
	long	m_LHR_Kp0;
	long	m_LEB_Kd0;
	long	m_LEB_Kd1;
	long	m_LEB_Ki0;
	long	m_LEB_Ki1;
	long	m_LEB_Kp0;
	long	m_LEB_Kp1;
	long	m_LSP_Kd0;
	long	m_LSP_Kd1;
	long	m_LSP_Ki0;
	long	m_LSP_Ki1;
	long	m_LSP_Kp0;
	long	m_LSP_Kp1;
	long	m_LSR_Kd0;
	long	m_LSR_Kd1;
	long	m_LSR_Ki0;
	long	m_LSR_Ki1;
	long	m_LSR_Kp0;
	long	m_LSR_Kp1;
	long	m_LSY_Kd0;
	long	m_LSY_Kd1;
	long	m_LSY_Ki0;
	long	m_LSY_Ki1;
	long	m_LSY_Kp0;
	long	m_LSY_Kp1;
	long	m_LW1_Kd0;
	long	m_LW1_Kd1;
	long	m_LW1_Ki0;
	long	m_LW1_Ki1;
	long	m_LW1_Kp0;
	long	m_LW1_Kp1;
	long	m_LW2_Kd0;
	long	m_LW2_Kd1;
	long	m_LW2_Ki0;
	long	m_LW2_Ki1;
	long	m_LW2_Kp0;
	long	m_LW2_Kp1;
	long	m_LWY_Kd0;
	long	m_LWY_Kd1;
	long	m_LWY_Ki0;
	long	m_LWY_Ki1;
	long	m_LWY_Kp0;
	long	m_LWY_Kp1;
	long	m_REB_Kd0;
	long	m_REB_Kd1;
	long	m_REB_Ki0;
	long	m_REB_Ki1;
	long	m_REB_Kp0;
	long	m_REB_Kp1;
	long	m_RSP_Kd0;
	long	m_RSP_Kd1;
	long	m_RSP_Ki0;
	long	m_RSP_Ki1;
	long	m_RSP_Kp0;
	long	m_RSP_Kp1;
	long	m_RSR_Kd0;
	long	m_RSR_Kd1;
	long	m_RSR_Ki0;
	long	m_RSR_Ki1;
	long	m_RSR_Kp0;
	long	m_RSR_Kp1;
	long	m_RSY_Kd0;
	long	m_RSY_Kd1;
	long	m_RSY_Ki0;
	long	m_RSY_Ki1;
	long	m_RSY_Kp0;
	long	m_RSY_Kp1;
	long	m_RW1_Kd0;
	long	m_RW1_Kd1;
	long	m_RW1_Ki0;
	long	m_RW1_Ki1;
	long	m_RW1_Kp0;
	long	m_RW1_Kp1;
	long	m_RW2_Kd0;
	long	m_RW2_Kd1;
	long	m_RW2_Ki0;
	long	m_RW2_Ki1;
	long	m_RW2_Kp0;
	long	m_RW2_Kp1;
	long	m_RWY_Kd0;
	long	m_RWY_Kd1;
	long	m_RWY_Ki0;
	long	m_RWY_Ki1;
	long	m_RWY_Kp0;
	long	m_RWY_Kp1;
	long	m_WST_Kd0;
	long	m_WST_Kd1;
	long	m_WST_Ki0;
	long	m_WST_Ki1;
	long	m_WST_Kp0;
	long	m_WST_Kp1;
	long	m_NK1_Kd0;
	long	m_NK1_Ki0;
	long	m_NK1_Ki1;
	long	m_NK1_Kp0;
	long	m_NK1_Kp1;
	long	m_NK2_Kd0;
	long	m_NK2_Kd1;
	long	m_NK2_Ki0;
	long	m_NK2_Ki1;
	long	m_NK2_Kp0;
	long	m_NK2_Kp1;
	long	m_NKY_Kd0;
	long	m_NK1_Kd1;
	long	m_NKY_Kd1;
	long	m_NKY_Ki0;
	long	m_NKY_Ki1;
	long	m_NKY_Kp0;
	long	m_NKY_Kp1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGainSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGainSet)
	afx_msg void OnButtonGainLoad();
	afx_msg void OnButtonGainSave();
	//}}AFX_MSG
	CKhr3winDlg* m_pKhr3winDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAINSET_H__A8D9D20D_1D1B_488D_85CF_053DBB2B87D7__INCLUDED_)
