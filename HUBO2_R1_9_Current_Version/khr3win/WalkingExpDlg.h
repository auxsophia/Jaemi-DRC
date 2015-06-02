#if !defined(AFX_WALKINGEXPDLG_H__DB7B266B_CCA7_481F_8AB5_8E3401D6B1E8__INCLUDED_)
#define AFX_WALKINGEXPDLG_H__DB7B266B_CCA7_481F_8AB5_8E3401D6B1E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WalkingExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWalkingExpDlg dialog
#include "Board.h"
#include "ProfileGraph.h"

class CKhr3winDlg;
class CWalkingExpDlg : public CDialog
{
// Construction
public:
	float OLAnkleComp;
	float SwayMod;

	void CreateGraph();
	unsigned int WalkingPeriod;
	void Init();
	void Close();
	CWalkingExpDlg(CWnd* pParent = NULL);   // standard constructor
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

	CProfileGraph m_ProfileGraphDlg;
// Dialog Data
	//{{AFX_DATA(CWalkingExpDlg)
	enum { IDD = IDD_DIALOG_WALK_EXP };
	CButton	m_Button_FT_Null;
	CButton	m_ButtonSet;
	CButton	m_ProfileGraph;
	UINT	m_WalkingPeriod;
	BOOL	m_Check_KeepGoing;
	float	m_EditSway;
	float	m_EditAnkle;
	float	m_FwdBwd;
	float	m_LftRht;
	float	m_Turn;
	float	m_UpRatio;
	float	m_ZMP_AMP;
	float	m_X_Shape_Factor;
	float	m_Y_Shape_Factor;
	float	m_Sway_Factor;
	float	m_SwayDelayOpen;
	float	m_SwayDelayRecover;
	float	m_YOffset;
	float	m_XOffset;
	BOOL	m_Check_Arm;
	BOOL	m_Sway_OnOff;
	float	m_StepLength;
	float	m_HipMoveRatio;
	float	m_HipPitchAngle;
	float	m_HipRollCompen;
	float	m_HipRollCompenL;
	float	m_LFootDelta_Y;
	float	m_RFootDelta_Y;
	float	m_FootPlacementGain;
	float	m_RollRefGain;
	float	m_FootYGain;
	float	m_FootZGain;
	float	m_StartInitVelocityCoff;
	float	m_ZmpAddCoff;
	float	m_PitchRefGain;
	float	m_LFootDelta_X;
	float	m_RFootDelta_X;
	float	m_LandingPitchGain;
	float	m_LandingRollGain;
	float	m_AccPitchOffset;
	float	m_AccRollOffset;
	float	m_XshapeFactorGain;
	float	m_ToeOffGain;
	float	m_AnkleRollGain;
	float	m_YShapeFactorRecover;
	float	m_YShapeFactorOpen;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalkingExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWalkingExpDlg)
	afx_msg void OnButtonClose();
	afx_msg void OnButtonHide();
	afx_msg void OnButtonFast();
	afx_msg void OnButtonSlow();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonGraph();
	afx_msg void OnButtonWalkReady();
	afx_msg void OnButtonHome();
	afx_msg void OnButtonGo();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonFtNull();
	afx_msg void OnButtonForward();
	afx_msg void OnButtonBackward();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnButtonCw();
	afx_msg void OnButtonCcw();
	afx_msg void OnBUTTON0p810cm();
	afx_msg void OnBUTTON0p820cm();
	afx_msg void OnBUTTON0p9510cm();
	afx_msg void OnBUTTON0p9530cm();
	afx_msg void OnBUTTON0p825cm();
	afx_msg void OnBUTTON0p710cm();
	afx_msg void OnBUTTON0p720cm();
	afx_msg void OnBUTTON0p725cm();
	afx_msg void OnBUTTONSide0p75cm();
	afx_msg void OnBUTTONSide0p85cm();
	afx_msg void OnBUTTONSide0p955cm();
	afx_msg void OnBUTTON0p9520cm();
	afx_msg void OnBUTTON0p950cm();
	afx_msg void OnBUTTON0p80cm();
	afx_msg void OnBUTTON0p70cm();
	afx_msg void OnButtonSwayAdjOn();
	afx_msg void OnBUTTONSide0p957cm();
	afx_msg void OnBUTTONSide0p9510cm();
	afx_msg void OnBUTTONSide0p87cm();
	afx_msg void OnBUTTONSide0p87cm2();
	afx_msg void OnBUTTONSide0p810cm();
	afx_msg void OnBUTTONSide0p77cm();
	afx_msg void OnBUTTONSide0p710cm();
	afx_msg void OnBUTTONTURN0p710();
	afx_msg void OnBUTTONTURN0p810();
	afx_msg void OnBUTTONTURN0p9510();
	afx_msg void OnBUTTONTURN0p730();
	afx_msg void OnBUTTONTURN0p830();
	afx_msg void OnBUTTONTURN0p9530();
	afx_msg void OnButtonXPlus();
	afx_msg void OnButtonXMinus();
	afx_msg void OnButtonYPlus();
	afx_msg void OnButtonYMinus();
	afx_msg void OnButtonArmOnoff();
	afx_msg void OnButtonMotion1();
	afx_msg void OnButtonMotionStop();
	afx_msg void OnButtonMotion2();
	afx_msg void OnButtonMotion3();
	afx_msg void OnButtonChange();
	afx_msg void OnButtonHipPitchInc1();
	afx_msg void OnButtonHipPitchDec();
	afx_msg void OnButtonHipPitchInc2();
	afx_msg void OnButtonHipPitchDec2();
	afx_msg void OnButtonSaveTimerReset();
	afx_msg void OnButtonStride0();
	afx_msg void OnButtonEncreadOn();
	afx_msg void OnButtonEncreadOff();
	afx_msg void OnButtonHipyawVibOn();
	afx_msg void OnButtonHipyawVibOff();
	//}}AFX_MSG
	CKhr3winDlg* m_pKhr3winDlg;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALKINGEXPDLG_H__DB7B266B_CCA7_481F_8AB5_8E3401D6B1E8__INCLUDED_)
