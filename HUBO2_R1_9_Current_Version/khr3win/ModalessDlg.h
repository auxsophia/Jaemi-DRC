#if !defined(AFX_MODALESSDLG_H__A2983C75_047C_4757_A643_81EBE453EAB8__INCLUDED_)
#define AFX_MODALESSDLG_H__A2983C75_047C_4757_A643_81EBE453EAB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModalessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModalessDlg dialog

class CModalessDlg : public CDialog
{
// Construction
public:
	CModalessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModalessDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModalessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModalessDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODALESSDLG_H__A2983C75_047C_4757_A643_81EBE453EAB8__INCLUDED_)
