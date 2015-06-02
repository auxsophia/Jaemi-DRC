#if !defined(AFX_Z_PHASEENCODERVIEWDLG_H__5BA09819_B46D_40AA_A069_5FDD11620738__INCLUDED_)
#define AFX_Z_PHASEENCODERVIEWDLG_H__5BA09819_B46D_40AA_A069_5FDD11620738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Z_PhaseEncoderViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZ_PhaseEncoderViewDlg dialog
class CZ_PhaseSetDlg;
class CZ_PhaseEncoderViewDlg : public CDialog
{
// Construction
public:
	void DispEnc();
	unsigned int index;
	void Init();
	CZ_PhaseEncoderViewDlg(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CZ_PhaseSetDlg* pCZ_PhaseSetDlg) { m_pCZ_PhaseSetDlg  = pCZ_PhaseSetDlg; }
// Dialog Data
	//{{AFX_DATA(CZ_PhaseEncoderViewDlg)
	enum { IDD = IDD_DIALOG_Z_ENCODER };
	long	m_LHP_Enc;
	long	m_LHR_Enc;
	long	m_LKP_Enc;
	long	m_RHP_Enc;
	long	m_RHR_Enc;
	long	m_RKP_Enc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZ_PhaseEncoderViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZ_PhaseEncoderViewDlg)
	afx_msg void OnButtonExit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	CZ_PhaseSetDlg* m_pCZ_PhaseSetDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Z_PHASEENCODERVIEWDLG_H__5BA09819_B46D_40AA_A069_5FDD11620738__INCLUDED_)
