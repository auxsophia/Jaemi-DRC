#if !defined(AFX_TILTREADDLG_H__B2C2056D_EC06_4EC3_81A4_862255B7C95E__INCLUDED_)
#define AFX_TILTREADDLG_H__B2C2056D_EC06_4EC3_81A4_862255B7C95E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TiltReadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTiltReadDlg dialog
#include "Board.h"

class CKhr3winDlg;

class CTiltReadDlg : public CDialog
{
// Construction
public:
	void UpdateBoardPoint();
	void InitBoard();
	void TiltStart();
	void TiltStop();
	void GyroReset();
	void Init();
	void DispTilt();
	void ButtonControl(int Msg);
	void Close();
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
	
	CTiltReadDlg(CWnd* pParent = NULL);   // standard constructor

	int		m_nTime;
// Dialog Data
	//{{AFX_DATA(CTiltReadDlg)
	enum { IDD = IDD_DIALOG_TILT_READ };
	CBoard	m_Board_Right_Foot_Incl;
	CBoard	m_Board_Left_Foot_Incl;
	CBoard	m_Board_Body_Pitch;
	CBoard	m_Board_Body_Roll;
	CButton	m_Button_Stop;
	CButton	m_Button_Reset;
	CButton	m_Button_Graph;
	CButton	m_Button_Close;
	float	m_Angle_Pitch;
	float	m_Angle_Roll;
	float	m_Gyro_CutOff_Pitch;
	float	m_Gyro_CutOff_Roll;
	float	m_Incl_CutOff_Pitch;
	float	m_Incl_CutOff_Roll;
	int		m_Gyro_Pitch;
	int		m_Gyro_Roll;
	int		m_Incl_Pitch;
	int		m_Incl_Roll;
	float	m_Left_Foot_Deg_Pitch;
	float	m_Left_Foot_Deg_Roll;
	int		m_Left_Foot_Incl_Pitch;
	int		m_Left_Foot_Incl_Roll;
	float	m_Left_Foot_LPF_Pitch;
	float	m_Left_Foot_LPF_Roll;
	float	m_Right_Foot_Deg_Pitch;
	float	m_Right_Foot_Deg_Roll;
	int		m_Right_Foot_Incl_Pitch;
	int		m_Right_Foot_Incl_Roll;
	float	m_Right_Foot_LPF_Pitch;
	float	m_Right_Foot_LPF_Roll;
	float	m_Gyro_CutOff_Yaw;
	int		m_Gyro_Yaw;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTiltReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CTiltReadDlg)
	afx_msg void OnButtonClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStop();
	afx_msg void OnButtonReset();
	afx_msg void OnPaint();
	afx_msg void OnButtonGraph();
	afx_msg void OnButtonHide();
	afx_msg void OnButtonStartCompensation();
	afx_msg void OnButtonDataSave();
	afx_msg void OnButtonFootAccReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TILTREADDLG_H__B2C2056D_EC06_4EC3_81A4_862255B7C95E__INCLUDED_)
