#if !defined(AFX_MOTORSTATE_H__1E33A5F4_ACAB_4E57_B447_F45F1FEF1CC8__INCLUDED_)
#define AFX_MOTORSTATE_H__1E33A5F4_ACAB_4E57_B447_F45F1FEF1CC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotorState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotorState dialog
class CCANwin;
class CKhr3winDlg;

class CMotorState : public CDialog
{
// Construction
public:
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg)  { m_pKhr3winDlg  = pKhr3winDlg; }
	void Init();
	CMotorState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMotorState)
	enum { IDD = IDD_DIALOG_MOTOR_STATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotorState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;

	// Generated message map functions
	//{{AFX_MSG(CMotorState)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTORSTATE_H__1E33A5F4_ACAB_4E57_B447_F45F1FEF1CC8__INCLUDED_)
