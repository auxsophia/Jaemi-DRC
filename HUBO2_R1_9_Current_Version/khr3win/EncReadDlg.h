#if !defined(AFX_ENCREADDLG_H__718402E3_71BA_4D28_9E1E_9AF09797D33A__INCLUDED_)
#define AFX_ENCREADDLG_H__718402E3_71BA_4D28_9E1E_9AF09797D33A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EncReadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEncReadDlg dialog
class CKhr3winDlg;
class CEncReadDlg : public CDialog
{
// Construction
public:
	void Close();
	CEncReadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEncReadDlg)
	enum { IDD = IDD_DIALOG_ENC_READ };

	long	m_Edit_Enc0;
	long	m_Edit_Enc1;
	long	m_Edit_Enc2;
	long	m_Edit_Enc3;
	long	m_Edit_Enc4;
	long	m_Edit_Enc5;
	long	m_Edit_Enc6;
	long	m_Edit_Enc7;
	long	m_Edit_Enc8;
	long	m_Edit_Enc9;
	long	m_Edit_Enc10;
	long	m_Edit_Enc11;
	long	m_Edit_Enc12;
	long	m_Edit_Enc13;
	long	m_Edit_Enc14;
	long	m_Edit_Enc15;
	long	m_Edit_Enc16;
	long	m_Edit_Enc17;
	long	m_Edit_Enc18;
	long	m_Edit_Enc19;
	long	m_Edit_Enc20;
	long	m_Edit_Enc21;
	long	m_Edit_Enc22;
	long	m_Edit_Enc23;
	long	m_Edit_Enc24;
	long	m_Edit_Enc25;
	long	m_Edit_Enc26;
	long	m_Edit_Enc27;
	long	m_Edit_Enc28;
	long	m_Edit_Enc29;
	long	m_Edit_Enc30;
	long	m_Edit_Enc31;
	long	m_Edit_Enc32;
	long	m_Edit_Enc33;
	long	m_Edit_Enc34;
	long	m_Edit_Enc35;
	long	m_Edit_Enc36;
	long	m_Edit_Enc37;
	long	m_Edit_Enc38;
	long	m_Edit_Enc39;
	long	m_Edit_Enc40;
	long	m_Edit_Enc41;
	long	m_Edit_Enc42;
	long	m_Edit_Enc43;

	unsigned	int	m_Edit_Monitoring;
	
	//}}AFX_DATA
public:
	void GetEnc();
	void EncVarINIT();
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CEncReadDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCREADDLG_H__718402E3_71BA_4D28_9E1E_9AF09797D33A__INCLUDED_)





















