#if !defined(AFX_ZMPZERODLG_H__B42E5747_8B1C_4D50_A135_4DD1A981F0A2__INCLUDED_)
#define AFX_ZMPZERODLG_H__B42E5747_8B1C_4D50_A135_4DD1A981F0A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZMPZeroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZMPZeroDlg dialog
class CKhr3winDlg;

class CZMPZeroDlg : public CDialog
{
// Construction
public:
	void autoSetup();

	void DispUpdate();
	void WalkReady();
	void Init();
	CZMPZeroDlg(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
// Dialog Data
	//{{AFX_DATA(CZMPZeroDlg)
	enum { IDD = IDD_DIALOG_ZMP_ZERO };
	CButton	m_Foot_ACC_Reset;
	CButton	m_Button_Right;
	CButton	m_Button_Left;
	CButton	m_ZMP_Start;
	float	m_FT_LFz;
	float	m_FT_LMx;
	float	m_FT_LMy;
	float	m_FT_RFz;
	float	m_FT_RMx;
	float	m_FT_RMy;
	float	m_FT_X_ZMP;
	float	m_FT_Y_ZMP;
	float	m_FltAccP1;
	float	m_FltAccR1;
	int		m_ACC_P;
	int		m_ACC_R;
	float	m_Lx;
	float	m_Ly;
	float	m_Lz;
	float	m_Rx;
	float	m_Ry;
	float	m_Rz;
	float	m_ZmpOffset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZMPZeroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CZMPZeroDlg)
	afx_msg void OnButtonExit();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonLeftY();
	afx_msg void OnButtonRightY();
	afx_msg void OnButtonForwardP();
	afx_msg void OnButtonBackwardP();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonAccReset();
	afx_msg void OnButtonNullFt();
	afx_msg void OnButtonInclReset();
	//}}AFX_MSG
	CKhr3winDlg* m_pKhr3winDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZMPZERODLG_H__B42E5747_8B1C_4D50_A135_4DD1A981F0A2__INCLUDED_)
