#if !defined(AFX_PARAMETERSETTING_H__7B92373F_6533_49D6_B128_4FEB64B13A07__INCLUDED_)
#define AFX_PARAMETERSETTING_H__7B92373F_6533_49D6_B128_4FEB64B13A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParameterSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameterSetting dialog
class CCANwin;

class CKhr3winDlg;

class CParameterSetting : public CDialog
{
// Construction
public:
	void DataLoad();
	void DataSave();
	void Init();
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }
	CParameterSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameterSetting)
	enum { IDD = IDD_DIALOG_PARAMETER_SETTING };
	float	m_DriveLAP;
	float	m_DriveLHP;
	float	m_DriveLAR;
	float	m_DriveLHR;
	float	m_DriveLHY;
	float	m_DriveLKN;
	float	m_DriveRAP;
	float	m_DriveRAR;
	float	m_DriveRHP;
	float	m_DriveRHR;
	float	m_DriveRHY;
	float	m_DriveRKN;
	float	m_DrivenLAP;
	float	m_DrivenLAR;
	float	m_DrivenLHP;
	float	m_DrivenLHR;
	float	m_DrivenLHY;
	float	m_DrivenLKN;
	float	m_DrivenRAP;
	float	m_DrivenRAR;
	float	m_DrivenRHP;
	float	m_DrivenRHR;
	float	m_DrivenRHY;
	float	m_DrivenRKN;
	float	m_HarmonicLAP;
	float	m_HarmonicLAR;
	float	m_HarmonicLHP;
	float	m_HarmonicLHR;
	float	m_HarmonicLHY;
	float	m_HarmonicLKN;
	float	m_HarmonicRAP;
	float	m_HarmonicRAR;
	float	m_HarmonicRHP;
	float	m_HarmonicRHR;
	float	m_HarmonicRHY;
	float	m_HarmonicRKN;
	float	m_EncLAP;
	float	m_EncLAR;
	float	m_EncLHP;
	float	m_EncLHR;
	float	m_EncLHY;
	float	m_EncLKN;
	float	m_EncRAP;
	float	m_EncRAR;
	float	m_EncRHP;
	float	m_EncRHR;
	float	m_EncRHY;
	float	m_EncRKN;
	long	m_PulseLAP;
	long	m_PulseLAR;
	long	m_PulseLHP;
	long	m_PulseLHR;
	long	m_PulseLHY;
	long	m_PulseLKN;
	long	m_PulseRAP;
	long	m_PulseRAR;
	long	m_PulseRHP;
	long	m_PulseRHR;
	long	m_PulseRHY;
	long	m_PulseRKN;
	long	m_RevLAP;
	long	m_RevLAR;
	long	m_RevLHP;
	long	m_RevLHR;
	long	m_RevLHY;
	long	m_RevLKN;
	long	m_RevRAP;
	long	m_RevRAR;
	long	m_RevRHP;
	long	m_RevRHR;
	long	m_RevRHY;
	long	m_RevRKN;
	long	m_LimitLAP;
	long	m_LimitLAR;
	long	m_LimitLHP;
	long	m_LimitLHR;
	long	m_LimitLHY;
	long	m_LimitLKN;
	long	m_LimitRAP;
	long	m_LimitRAR;
	long	m_LimitRHP;
	long	m_LimitRHR;
	long	m_LimitRHY;
	long	m_LimitRKN;
	float	m_DirLAP;
	float	m_DirLAR;
	float	m_DirLHP;
	float	m_DirLHR;
	float	m_DirLHY;
	float	m_DirLKN;
	float	m_DirRAP;
	float	m_DirRAR;
	float	m_DirRHP;
	float	m_DirRHR;
	float	m_DirRHY;
	float	m_DirRKN;
	float	m_DirLEB;
	float	m_DirLSP;
	float	m_DirLSR;
	float	m_DirLSY;
	float	m_DirLW1;
	float	m_DirLW2;
	float	m_DirLWY;
	float	m_DirREB;
	float	m_DirRSP;
	float	m_DirRSR;
	float	m_DirRSY;
	float	m_DirRW1;
	float	m_DirRW2;
	float	m_DirRWY;
	float	m_DriveLEB;
	float	m_DriveLSP;
	float	m_DriveLSR;
	float	m_DriveLSY;
	float	m_DriveLW1;
	float	m_DriveLW2;
	float	m_DriveLWY;
	float	m_DriveREB;
	float	m_DriveRSP;
	float	m_DriveRSR;
	float	m_DriveRSY;
	float	m_DriveRW1;
	float	m_DriveRW2;
	float	m_DriveRWY;
	float	m_DrivenLEB;
	float	m_DrivenLSP;
	float	m_DrivenLSR;
	float	m_DrivenLSY;
	float	m_DrivenLW1;
	float	m_DrivenLW2;
	float	m_DrivenLWY;
	float	m_DrivenREB;
	float	m_DrivenRSP;
	float	m_DrivenRSR;
	float	m_DrivenRSY;
	float	m_DrivenRW1;
	float	m_DrivenRW2;
	float	m_DrivenRWY;
	float	m_EncLEB;
	float	m_EncLSP;
	float	m_EncLSR;
	float	m_EncLSY;
	float	m_EncLW1;
	float	m_EncLW2;
	float	m_EncLWY;
	float	m_EncREB;
	float	m_EncRSP;
	float	m_EncRSR;
	float	m_EncRSY;
	float	m_EncRW1;
	float	m_EncRW2;
	float	m_EncRWY;
	float	m_HarmonicLEB;
	float	m_HarmonicLSP;
	float	m_HarmonicLSR;
	float	m_HarmonicLSY;
	float	m_HarmonicLW1;
	float	m_HarmonicLW2;
	float	m_HarmonicLWY;
	float	m_HarmonicREB;
	float	m_HarmonicRSP;
	float	m_HarmonicRSR;
	float	m_HarmonicRSY;
	float	m_HarmonicRW1;
	float	m_HarmonicRW2;
	float	m_HarmonicRWY;
	long	m_LimitLEB;
	long	m_LimitLSP;
	long	m_LimitLSR;
	long	m_LimitLSY;
	long	m_LimitLW1;
	long	m_LimitLW2;
	long	m_LimitLWY;
	long	m_LimitREB;
	long	m_LimitRSP;
	long	m_LimitRSR;
	long	m_LimitRSY;
	long	m_LimitRW1;
	long	m_LimitRW2;
	long	m_LimitRWY;
	long	m_PulseLEB;
	long	m_PulseLSP;
	long	m_PulseLSR;
	long	m_PulseLSY;
	long	m_PulseLW1;
	long	m_PulseLW2;
	long	m_PulseLWY;
	long	m_PulseREB;
	long	m_PulseRSP;
	long	m_PulseRSR;
	long	m_PulseRSY;
	long	m_PulseRW1;
	long	m_PulseRW2;
	long	m_PulseRWY;
	long	m_RevLEB;
	long	m_RevLSP;
	long	m_RevLSR;
	long	m_RevLSY;
	long	m_RevLW1;
	long	m_RevLW2;
	long	m_RevLWY;
	long	m_RevREB;
	long	m_RevRSP;
	long	m_RevRSR;
	long	m_RevRSY;
	long	m_RevRW1;
	long	m_RevRW2;
	long	m_RevRWY;
	float	m_HarmonicWST;
	long	m_LimitWST;
	long	m_PulseWST;
	long	m_RevWST;
	float	m_DirWST;
	float	m_DriveWST;
	float	m_DrivenWST;
	float	m_EncWST;
	float	m_DirNK1;
	float	m_DirNK2;
	float	m_DirNKY;
	float	m_DriveNK1;
	float	m_DriveNK2;
	float	m_DriveNKY;
	float	m_DrivenNK1;
	float	m_DrivenNK2;
	float	m_DrivenNKY;
	float	m_EncNK1;
	float	m_EncNK2;
	float	m_EncNKY;
	float	m_HarmonicNK1;
	float	m_HarmonicNK2;
	float	m_HarmonicNKY;
	long	m_LimitNK1;
	long	m_LimitNK2;
	long	m_LimitNKY;
	long	m_PulseNK1;
	long	m_PulseNK2;
	long	m_PulseNKY;
	long	m_RevNK1;
	long	m_RevNK2;
	long	m_RevNKY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	// Generated message map functions
	//{{AFX_MSG(CParameterSetting)
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERSETTING_H__7B92373F_6533_49D6_B128_4FEB64B13A07__INCLUDED_)
