#if !defined(AFX_FT_READDLG_H__F83781EE_DD76_488B_866E_661AC57F2C76__INCLUDED_)
#define AFX_FT_READDLG_H__F83781EE_DD76_488B_866E_661AC57F2C76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FT_ReadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFT_ReadDlg dialog
#include "Board.h"

class CKhr3winDlg;
class CFT_ReadDlg : public CDialog
{
// Construction
public:
	CFT_ReadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFT_ReadDlg)
	enum { IDD = IDD_DIALOG_FT_READ };
	CButton	m_ButtonFTNULL;
	CBoard	m_ZMPFTBoard;
	CBoard	m_LFootFTBoard;
	CBoard	m_RFootFTBoard;
	CButton	m_ButtonGraph;
	CButton	m_ButtonClose;
	//}}AFX_DATA
public:
	void FT_Null();
	void Init();
	float ChangeValue(float nValue);
	void UpdateBoardPoint();
	void InitBoard();
	void ButtonControl(int Msg);
	void DispFT();
	void FTVarINIT();
	void Close();
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

	int		m_RWRIST_Fz;
	int		m_RWRIST_Mx;
	int		m_RWRIST_My;
	int		m_LFOOT_Fz;
	int		m_LFOOT_Mx;
	int		m_LFOOT_My;
	int		m_LWRIST_Fz;
	int		m_LWRIST_Mx;
	int		m_LWRIST_My;
	int		m_RFOOT_Fz;
	int		m_RFOOT_Mx;
	int		m_RFOOT_My;

	float	m_Xzmp;
	float	m_Yzmp;

	float	m_RXzmp;
	float	m_RYzmp;

	float	m_LXzmp;
	float	m_LYzmp;

	float	m_NM_RFOOT_Mx;
	float	m_NM_RFOOT_My;
	float	m_N_RFOOT_Fz;
    float	m_NM_LFOOT_Mx;
	float	m_NM_LFOOT_My;
	float	m_N_LFOOT_Fz;
	float	m_NM_RWRIST_Mx;
	float	m_NM_RWRIST_My;
	float	m_N_RWRIST_Fz;
    float	m_NM_LWRIST_Mx;
	float	m_NM_LWRIST_My;
	float	m_N_LWRIST_Fz;

	int		m_nTime;

	void Null_CMD(unsigned char Module_ID, unsigned char Mode);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFT_ReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CFT_ReadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGraph();
	afx_msg void OnPaint();
	afx_msg void OnButtonFtNull();
	afx_msg void OnButtonHide();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FT_READDLG_H__F83781EE_DD76_488B_866E_661AC57F2C76__INCLUDED_)
