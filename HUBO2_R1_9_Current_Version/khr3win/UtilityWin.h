#if !defined(AFX_UTILITYWIN_H__E0ECB8CA_1A4F_4AD6_9325_0375352B7ECC__INCLUDED_)
#define AFX_UTILITYWIN_H__E0ECB8CA_1A4F_4AD6_9325_0375352B7ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UtilityWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUtilityWin dialog
class CKhr3winDlg;
class CUtilityWin : public CDialog
{
// Construction
public:
	CUtilityWin(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

// Dialog Data
	//{{AFX_DATA(CUtilityWin)
	enum { IDD = IDD_DIALOG_UTIL };
	double	m_L_Ankle_Pitch;
	double	m_L_Ankle_Roll;
	double	m_L_Hip_Pitch;
	double	m_L_Hip_Roll;
	double	m_L_Knee_Pitch;
	double	m_L_Px;
	double	m_L_Py;
	double	m_L_Pz;
	double	m_L_Yaw;
	double	m_R_Ankle_Pitch;
	double	m_R_Ankle_Roll;
	double	m_R_Hip_Pitch;
	double	m_R_Hip_Roll;
	double	m_R_Knee_Pitch;
	double	m_R_Py;
	double	m_R_Px;
	double	m_R_Pz;
	double	m_R_Yaw;
	double	m_R_FRD_Yaw;
	double	m_L_FRD_Yaw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilityWin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CUtilityWin)
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSolveForward();
	afx_msg void OnButtonSolveInverse();
	afx_msg void OnButtonCalculater();
	afx_msg void OnButtonNotePad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTILITYWIN_H__E0ECB8CA_1A4F_4AD6_9325_0375352B7ECC__INCLUDED_)
