// ParameterSetting.cpp : implementation file
//

#define ROW 12
#define COL	10

#include "stdafx.h"
#include "khr3win.h"
#include "ParameterSetting.h"
#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterSetting dialog


CParameterSetting::CParameterSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterSetting)
	m_DriveLAP = 0.0f;
	m_DriveLHP = 0.0f;
	m_DriveLAR = 0.0f;
	m_DriveLHR = 0.0f;
	m_DriveLHY = 0.0f;
	m_DriveLKN = 0.0f;
	m_DriveRAP = 0.0f;
	m_DriveRAR = 0.0f;
	m_DriveRHP = 0.0f;
	m_DriveRHR = 0.0f;
	m_DriveRHY = 0.0f;
	m_DriveRKN = 0.0f;
	m_DrivenLAP = 0.0f;
	m_DrivenLAR = 0.0f;
	m_DrivenLHP = 0.0f;
	m_DrivenLHR = 0.0f;
	m_DrivenLHY = 0.0f;
	m_DrivenLKN = 0.0f;
	m_DrivenRAP = 0.0f;
	m_DrivenRAR = 0.0f;
	m_DrivenRHP = 0.0f;
	m_DrivenRHR = 0.0f;
	m_DrivenRHY = 0.0f;
	m_DrivenRKN = 0.0f;
	m_HarmonicLAP = 0.0f;
	m_HarmonicLAR = 0.0f;
	m_HarmonicLHP = 0.0f;
	m_HarmonicLHR = 0.0f;
	m_HarmonicLHY = 0.0f;
	m_HarmonicLKN = 0.0f;
	m_HarmonicRAP = 0.0f;
	m_HarmonicRAR = 0.0f;
	m_HarmonicRHP = 0.0f;
	m_HarmonicRHR = 0.0f;
	m_HarmonicRHY = 0.0f;
	m_HarmonicRKN = 0.0f;
	m_EncLAP = 0.0f;
	m_EncLAR = 0.0f;
	m_EncLHP = 0.0f;
	m_EncLHR = 0.0f;
	m_EncLHY = 0.0f;
	m_EncLKN = 0.0f;
	m_EncRAP = 0.0f;
	m_EncRAR = 0.0f;
	m_EncRHP = 0.0f;
	m_EncRHR = 0.0f;
	m_EncRHY = 0.0f;
	m_EncRKN = 0.0f;
	m_PulseLAP = 0;
	m_PulseLAR = 0;
	m_PulseLHP = 0;
	m_PulseLHR = 0;
	m_PulseLHY = 0;
	m_PulseLKN = 0;
	m_PulseRAP = 0;
	m_PulseRAR = 0;
	m_PulseRHP = 0;
	m_PulseRHR = 0;
	m_PulseRHY = 0;
	m_PulseRKN = 0;
	m_RevLAP = 0;
	m_RevLAR = 0;
	m_RevLHP = 0;
	m_RevLHR = 0;
	m_RevLHY = 0;
	m_RevLKN = 0;
	m_RevRAP = 0;
	m_RevRAR = 0;
	m_RevRHP = 0;
	m_RevRHR = 0;
	m_RevRHY = 0;
	m_RevRKN = 0;
	m_LimitLAP = 0;
	m_LimitLAR = 0;
	m_LimitLHP = 0;
	m_LimitLHR = 0;
	m_LimitLHY = 0;
	m_LimitLKN = 0;
	m_LimitRAP = 0;
	m_LimitRAR = 0;
	m_LimitRHP = 0;
	m_LimitRHR = 0;
	m_LimitRHY = 0;
	m_LimitRKN = 0;
	m_DirLAP = 0.0f;
	m_DirLAR = 0.0f;
	m_DirLHP = 0.0f;
	m_DirLHR = 0.0f;
	m_DirLHY = 0.0f;
	m_DirLKN = 0.0f;
	m_DirRAP = 0.0f;
	m_DirRAR = 0.0f;
	m_DirRHP = 0.0f;
	m_DirRHR = 0.0f;
	m_DirRHY = 0.0f;
	m_DirRKN = 0.0f;
	m_DirLEB = 0.0f;
	m_DirLSP = 0.0f;
	m_DirLSR = 0.0f;
	m_DirLSY = 0.0f;
	m_DirLW1 = 0.0f;
	m_DirLW2 = 0.0f;
	m_DirLWY = 0.0f;
	m_DirREB = 0.0f;
	m_DirRSP = 0.0f;
	m_DirRSR = 0.0f;
	m_DirRSY = 0.0f;
	m_DirRW1 = 0.0f;
	m_DirRW2 = 0.0f;
	m_DirRWY = 0.0f;
	m_DriveLEB = 0.0f;
	m_DriveLSP = 0.0f;
	m_DriveLSR = 0.0f;
	m_DriveLSY = 0.0f;
	m_DriveLW1 = 0.0f;
	m_DriveLW2 = 0.0f;
	m_DriveLWY = 0.0f;
	m_DriveREB = 0.0f;
	m_DriveRSP = 0.0f;
	m_DriveRSR = 0.0f;
	m_DriveRSY = 0.0f;
	m_DriveRW1 = 0.0f;
	m_DriveRW2 = 0.0f;
	m_DriveRWY = 0.0f;
	m_DrivenLEB = 0.0f;
	m_DrivenLSP = 0.0f;
	m_DrivenLSR = 0.0f;
	m_DrivenLSY = 0.0f;
	m_DrivenLW1 = 0.0f;
	m_DrivenLW2 = 0.0f;
	m_DrivenLWY = 0.0f;
	m_DrivenREB = 0.0f;
	m_DrivenRSP = 0.0f;
	m_DrivenRSR = 0.0f;
	m_DrivenRSY = 0.0f;
	m_DrivenRW1 = 0.0f;
	m_DrivenRW2 = 0.0f;
	m_DrivenRWY = 0.0f;
	m_EncLEB = 0.0f;
	m_EncLSP = 0.0f;
	m_EncLSR = 0.0f;
	m_EncLSY = 0.0f;
	m_EncLW1 = 0.0f;
	m_EncLW2 = 0.0f;
	m_EncLWY = 0.0f;
	m_EncREB = 0.0f;
	m_EncRSP = 0.0f;
	m_EncRSR = 0.0f;
	m_EncRSY = 0.0f;
	m_EncRW1 = 0.0f;
	m_EncRW2 = 0.0f;
	m_EncRWY = 0.0f;
	m_HarmonicLEB = 0.0f;
	m_HarmonicLSP = 0.0f;
	m_HarmonicLSR = 0.0f;
	m_HarmonicLSY = 0.0f;
	m_HarmonicLW1 = 0.0f;
	m_HarmonicLW2 = 0.0f;
	m_HarmonicLWY = 0.0f;
	m_HarmonicREB = 0.0f;
	m_HarmonicRSP = 0.0f;
	m_HarmonicRSR = 0.0f;
	m_HarmonicRSY = 0.0f;
	m_HarmonicRW1 = 0.0f;
	m_HarmonicRW2 = 0.0f;
	m_HarmonicRWY = 0.0f;
	m_LimitLEB = 0;
	m_LimitLSP = 0;
	m_LimitLSR = 0;
	m_LimitLSY = 0;
	m_LimitLW1 = 0;
	m_LimitLW2 = 0;
	m_LimitLWY = 0;
	m_LimitREB = 0;
	m_LimitRSP = 0;
	m_LimitRSR = 0;
	m_LimitRSY = 0;
	m_LimitRW1 = 0;
	m_LimitRW2 = 0;
	m_LimitRWY = 0;
	m_PulseLEB = 0;
	m_PulseLSP = 0;
	m_PulseLSR = 0;
	m_PulseLSY = 0;
	m_PulseLW1 = 0;
	m_PulseLW2 = 0;
	m_PulseLWY = 0;
	m_PulseREB = 0;
	m_PulseRSP = 0;
	m_PulseRSR = 0;
	m_PulseRSY = 0;
	m_PulseRW1 = 0;
	m_PulseRW2 = 0;
	m_PulseRWY = 0;
	m_RevLEB = 0;
	m_RevLSP = 0;
	m_RevLSR = 0;
	m_RevLSY = 0;
	m_RevLW1 = 0;
	m_RevLW2 = 0;
	m_RevLWY = 0;
	m_RevREB = 0;
	m_RevRSP = 0;
	m_RevRSR = 0;
	m_RevRSY = 0;
	m_RevRW1 = 0;
	m_RevRW2 = 0;
	m_RevRWY = 0;
	m_HarmonicWST = 0.0f;
	m_LimitWST = 0;
	m_PulseWST = 0;
	m_RevWST = 0;
	m_DirWST = 0.0f;
	m_DriveWST = 0.0f;
	m_DrivenWST = 0.0f;
	m_EncWST = 0.0f;
	m_DirNK1 = 0.0f;
	m_DirNK2 = 0.0f;
	m_DirNKY = 0.0f;
	m_DriveNK1 = 0.0f;
	m_DriveNK2 = 0.0f;
	m_DriveNKY = 0.0f;
	m_DrivenNK1 = 0.0f;
	m_DrivenNK2 = 0.0f;
	m_DrivenNKY = 0.0f;
	m_EncNK1 = 0.0f;
	m_EncNK2 = 0.0f;
	m_EncNKY = 0.0f;
	m_HarmonicNK1 = 0.0f;
	m_HarmonicNK2 = 0.0f;
	m_HarmonicNKY = 0.0f;
	m_LimitNK1 = 0;
	m_LimitNK2 = 0;
	m_LimitNKY = 0;
	m_PulseNK1 = 0;
	m_PulseNK2 = 0;
	m_PulseNKY = 0;
	m_RevNK1 = 0;
	m_RevNK2 = 0;
	m_RevNKY = 0;
	//}}AFX_DATA_INIT
}


void CParameterSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterSetting)
	DDX_Text(pDX, IDC_EDIT_DRIVE_LAP, m_DriveLAP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LHP, m_DriveLHP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LAR, m_DriveLAR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LHR, m_DriveLHR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LHY, m_DriveLHY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LKN, m_DriveLKN);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RAP, m_DriveRAP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RAR, m_DriveRAR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RHP, m_DriveRHP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RHR, m_DriveRHR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RHY, m_DriveRHY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RKN, m_DriveRKN);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LAP, m_DrivenLAP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LAR, m_DrivenLAR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LHP, m_DrivenLHP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LHR, m_DrivenLHR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LHY, m_DrivenLHY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LKN, m_DrivenLKN);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RAP, m_DrivenRAP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RAR, m_DrivenRAR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RHP, m_DrivenRHP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RHR, m_DrivenRHR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RHY, m_DrivenRHY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RKN, m_DrivenRKN);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LAP, m_HarmonicLAP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LAR, m_HarmonicLAR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LHP, m_HarmonicLHP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LHR, m_HarmonicLHR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LHY, m_HarmonicLHY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LKN, m_HarmonicLKN);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RAP, m_HarmonicRAP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RAR, m_HarmonicRAR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RHP, m_HarmonicRHP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RHR, m_HarmonicRHR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RHY, m_HarmonicRHY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RKN, m_HarmonicRKN);
	DDX_Text(pDX, IDC_EDIT_ENC_LAP, m_EncLAP);
	DDX_Text(pDX, IDC_EDIT_ENC_LAR, m_EncLAR);
	DDX_Text(pDX, IDC_EDIT_ENC_LHP, m_EncLHP);
	DDX_Text(pDX, IDC_EDIT_ENC_LHR, m_EncLHR);
	DDX_Text(pDX, IDC_EDIT_ENC_LHY, m_EncLHY);
	DDX_Text(pDX, IDC_EDIT_ENC_LKN, m_EncLKN);
	DDX_Text(pDX, IDC_EDIT_ENC_RAP, m_EncRAP);
	DDX_Text(pDX, IDC_EDIT_ENC_RAR, m_EncRAR);
	DDX_Text(pDX, IDC_EDIT_ENC_RHP, m_EncRHP);
	DDX_Text(pDX, IDC_EDIT_ENC_RHR, m_EncRHR);
	DDX_Text(pDX, IDC_EDIT_ENC_RHY, m_EncRHY);
	DDX_Text(pDX, IDC_EDIT_ENC_RKN, m_EncRKN);
	DDX_Text(pDX, IDC_EDIT_PULSE_LAP, m_PulseLAP);
	DDX_Text(pDX, IDC_EDIT_PULSE_LAR, m_PulseLAR);
	DDX_Text(pDX, IDC_EDIT_PULSE_LHP, m_PulseLHP);
	DDX_Text(pDX, IDC_EDIT_PULSE_LHR, m_PulseLHR);
	DDX_Text(pDX, IDC_EDIT_PULSE_LHY, m_PulseLHY);
	DDX_Text(pDX, IDC_EDIT_PULSE_LKN, m_PulseLKN);
	DDX_Text(pDX, IDC_EDIT_PULSE_RAP, m_PulseRAP);
	DDX_Text(pDX, IDC_EDIT_PULSE_RAR, m_PulseRAR);
	DDX_Text(pDX, IDC_EDIT_PULSE_RHP, m_PulseRHP);
	DDX_Text(pDX, IDC_EDIT_PULSE_RHR, m_PulseRHR);
	DDX_Text(pDX, IDC_EDIT_PULSE_RHY, m_PulseRHY);
	DDX_Text(pDX, IDC_EDIT_PULSE_RKN, m_PulseRKN);
	DDX_Text(pDX, IDC_EDIT_REV_LAP, m_RevLAP);
	DDX_Text(pDX, IDC_EDIT_REV_LAR, m_RevLAR);
	DDX_Text(pDX, IDC_EDIT_REV_LHP, m_RevLHP);
	DDX_Text(pDX, IDC_EDIT_REV_LHR, m_RevLHR);
	DDX_Text(pDX, IDC_EDIT_REV_LHY, m_RevLHY);
	DDX_Text(pDX, IDC_EDIT_REV_LKN, m_RevLKN);
	DDX_Text(pDX, IDC_EDIT_REV_RAP, m_RevRAP);
	DDX_Text(pDX, IDC_EDIT_REV_RAR, m_RevRAR);
	DDX_Text(pDX, IDC_EDIT_REV_RHP, m_RevRHP);
	DDX_Text(pDX, IDC_EDIT_REV_RHR, m_RevRHR);
	DDX_Text(pDX, IDC_EDIT_REV_RHY, m_RevRHY);
	DDX_Text(pDX, IDC_EDIT_REV_RKN, m_RevRKN);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LAP, m_LimitLAP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LAR, m_LimitLAR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LHP, m_LimitLHP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LHR, m_LimitLHR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LHY, m_LimitLHY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LKN, m_LimitLKN);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RAP, m_LimitRAP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RAR, m_LimitRAR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RHP, m_LimitRHP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RHR, m_LimitRHR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RHY, m_LimitRHY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RKN, m_LimitRKN);
	DDX_Text(pDX, IDC_EDIT_DIR_LAP, m_DirLAP);
	DDV_MinMaxFloat(pDX, m_DirLAP, -1.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_DIR_LAR, m_DirLAR);
	DDX_Text(pDX, IDC_EDIT_DIR_LHP, m_DirLHP);
	DDX_Text(pDX, IDC_EDIT_DIR_LHR, m_DirLHR);
	DDX_Text(pDX, IDC_EDIT_DIR_LHY, m_DirLHY);
	DDX_Text(pDX, IDC_EDIT_DIR_LKN, m_DirLKN);
	DDX_Text(pDX, IDC_EDIT_DIR_RAP, m_DirRAP);
	DDX_Text(pDX, IDC_EDIT_DIR_RAR, m_DirRAR);
	DDX_Text(pDX, IDC_EDIT_DIR_RHP, m_DirRHP);
	DDX_Text(pDX, IDC_EDIT_DIR_RHR, m_DirRHR);
	DDX_Text(pDX, IDC_EDIT_DIR_RHY, m_DirRHY);
	DDX_Text(pDX, IDC_EDIT_DIR_RKN, m_DirRKN);
	DDX_Text(pDX, IDC_EDIT_DIR_LEB, m_DirLEB);
	DDX_Text(pDX, IDC_EDIT_DIR_LSP, m_DirLSP);
	DDX_Text(pDX, IDC_EDIT_DIR_LSR, m_DirLSR);
	DDX_Text(pDX, IDC_EDIT_DIR_LSY, m_DirLSY);
	DDX_Text(pDX, IDC_EDIT_DIR_LW1, m_DirLW1);
	DDX_Text(pDX, IDC_EDIT_DIR_LW2, m_DirLW2);
	DDX_Text(pDX, IDC_EDIT_DIR_LWY, m_DirLWY);
	DDX_Text(pDX, IDC_EDIT_DIR_REB, m_DirREB);
	DDX_Text(pDX, IDC_EDIT_DIR_RSP, m_DirRSP);
	DDX_Text(pDX, IDC_EDIT_DIR_RSR, m_DirRSR);
	DDX_Text(pDX, IDC_EDIT_DIR_RSY, m_DirRSY);
	DDX_Text(pDX, IDC_EDIT_DIR_RW1, m_DirRW1);
	DDX_Text(pDX, IDC_EDIT_DIR_RW2, m_DirRW2);
	DDX_Text(pDX, IDC_EDIT_DIR_RWY, m_DirRWY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LEB, m_DriveLEB);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LSP, m_DriveLSP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LSR, m_DriveLSR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LSY, m_DriveLSY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LW1, m_DriveLW1);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LW2, m_DriveLW2);
	DDX_Text(pDX, IDC_EDIT_DRIVE_LWY, m_DriveLWY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_REB, m_DriveREB);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RSP, m_DriveRSP);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RSR, m_DriveRSR);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RSY, m_DriveRSY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RW1, m_DriveRW1);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RW2, m_DriveRW2);
	DDX_Text(pDX, IDC_EDIT_DRIVE_RWY, m_DriveRWY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LEB, m_DrivenLEB);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LSP, m_DrivenLSP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LSR, m_DrivenLSR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LSY, m_DrivenLSY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LW1, m_DrivenLW1);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LW2, m_DrivenLW2);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_LWY, m_DrivenLWY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_REB, m_DrivenREB);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RSP, m_DrivenRSP);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RSR, m_DrivenRSR);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RSY, m_DrivenRSY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RW1, m_DrivenRW1);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RW2, m_DrivenRW2);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_RWY, m_DrivenRWY);
	DDX_Text(pDX, IDC_EDIT_ENC_LEB, m_EncLEB);
	DDX_Text(pDX, IDC_EDIT_ENC_LSP, m_EncLSP);
	DDX_Text(pDX, IDC_EDIT_ENC_LSR, m_EncLSR);
	DDX_Text(pDX, IDC_EDIT_ENC_LSY, m_EncLSY);
	DDX_Text(pDX, IDC_EDIT_ENC_LW1, m_EncLW1);
	DDX_Text(pDX, IDC_EDIT_ENC_LW2, m_EncLW2);
	DDX_Text(pDX, IDC_EDIT_ENC_LWY, m_EncLWY);
	DDX_Text(pDX, IDC_EDIT_ENC_REB, m_EncREB);
	DDX_Text(pDX, IDC_EDIT_ENC_RSP, m_EncRSP);
	DDX_Text(pDX, IDC_EDIT_ENC_RSR, m_EncRSR);
	DDX_Text(pDX, IDC_EDIT_ENC_RSY, m_EncRSY);
	DDX_Text(pDX, IDC_EDIT_ENC_RW1, m_EncRW1);
	DDX_Text(pDX, IDC_EDIT_ENC_RW2, m_EncRW2);
	DDX_Text(pDX, IDC_EDIT_ENC_RWY, m_EncRWY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LEB, m_HarmonicLEB);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LSP, m_HarmonicLSP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LSR, m_HarmonicLSR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LSY, m_HarmonicLSY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LW1, m_HarmonicLW1);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LW2, m_HarmonicLW2);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_LWY, m_HarmonicLWY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_REB, m_HarmonicREB);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RSP, m_HarmonicRSP);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RSR, m_HarmonicRSR);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RSY, m_HarmonicRSY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RW1, m_HarmonicRW1);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RW2, m_HarmonicRW2);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_RWY, m_HarmonicRWY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LEB, m_LimitLEB);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LSP, m_LimitLSP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LSR, m_LimitLSR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LSY, m_LimitLSY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LW1, m_LimitLW1);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LW2, m_LimitLW2);
	DDX_Text(pDX, IDC_EDIT_LIMIT_LWY, m_LimitLWY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_REB, m_LimitREB);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RSP, m_LimitRSP);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RSR, m_LimitRSR);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RSY, m_LimitRSY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RW1, m_LimitRW1);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RW2, m_LimitRW2);
	DDX_Text(pDX, IDC_EDIT_LIMIT_RWY, m_LimitRWY);
	DDX_Text(pDX, IDC_EDIT_PULSE_LEB, m_PulseLEB);
	DDX_Text(pDX, IDC_EDIT_PULSE_LSP, m_PulseLSP);
	DDX_Text(pDX, IDC_EDIT_PULSE_LSR, m_PulseLSR);
	DDX_Text(pDX, IDC_EDIT_PULSE_LSY, m_PulseLSY);
	DDX_Text(pDX, IDC_EDIT_PULSE_LW1, m_PulseLW1);
	DDX_Text(pDX, IDC_EDIT_PULSE_LW2, m_PulseLW2);
	DDX_Text(pDX, IDC_EDIT_PULSE_LWY, m_PulseLWY);
	DDX_Text(pDX, IDC_EDIT_PULSE_REB, m_PulseREB);
	DDX_Text(pDX, IDC_EDIT_PULSE_RSP, m_PulseRSP);
	DDX_Text(pDX, IDC_EDIT_PULSE_RSR, m_PulseRSR);
	DDX_Text(pDX, IDC_EDIT_PULSE_RSY, m_PulseRSY);
	DDX_Text(pDX, IDC_EDIT_PULSE_RW1, m_PulseRW1);
	DDX_Text(pDX, IDC_EDIT_PULSE_RW2, m_PulseRW2);
	DDX_Text(pDX, IDC_EDIT_PULSE_RWY, m_PulseRWY);
	DDX_Text(pDX, IDC_EDIT_REV_LEB, m_RevLEB);
	DDX_Text(pDX, IDC_EDIT_REV_LSP, m_RevLSP);
	DDX_Text(pDX, IDC_EDIT_REV_LSR, m_RevLSR);
	DDX_Text(pDX, IDC_EDIT_REV_LSY, m_RevLSY);
	DDX_Text(pDX, IDC_EDIT_REV_LW1, m_RevLW1);
	DDX_Text(pDX, IDC_EDIT_REV_LW2, m_RevLW2);
	DDX_Text(pDX, IDC_EDIT_REV_LWY, m_RevLWY);
	DDX_Text(pDX, IDC_EDIT_REV_REB, m_RevREB);
	DDX_Text(pDX, IDC_EDIT_REV_RSP, m_RevRSP);
	DDX_Text(pDX, IDC_EDIT_REV_RSR, m_RevRSR);
	DDX_Text(pDX, IDC_EDIT_REV_RSY, m_RevRSY);
	DDX_Text(pDX, IDC_EDIT_REV_RW1, m_RevRW1);
	DDX_Text(pDX, IDC_EDIT_REV_RW2, m_RevRW2);
	DDX_Text(pDX, IDC_EDIT_REV_RWY, m_RevRWY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_WST, m_HarmonicWST);
	DDX_Text(pDX, IDC_EDIT_LIMIT_WST, m_LimitWST);
	DDX_Text(pDX, IDC_EDIT_PULSE_WST, m_PulseWST);
	DDX_Text(pDX, IDC_EDIT_REV_WST, m_RevWST);
	DDX_Text(pDX, IDC_EDIT_DIR_WST, m_DirWST);
	DDX_Text(pDX, IDC_EDIT_DRIVE_WST, m_DriveWST);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_WST, m_DrivenWST);
	DDX_Text(pDX, IDC_EDIT_ENC_WST, m_EncWST);
	DDX_Text(pDX, IDC_EDIT_DIR_NK1, m_DirNK1);
	DDX_Text(pDX, IDC_EDIT_DIR_NK2, m_DirNK2);
	DDX_Text(pDX, IDC_EDIT_DIR_NKY, m_DirNKY);
	DDX_Text(pDX, IDC_EDIT_DRIVE_NK1, m_DriveNK1);
	DDX_Text(pDX, IDC_EDIT_DRIVE_NK2, m_DriveNK2);
	DDX_Text(pDX, IDC_EDIT_DRIVE_NKY, m_DriveNKY);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_NK1, m_DrivenNK1);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_NK2, m_DrivenNK2);
	DDX_Text(pDX, IDC_EDIT_DRIVEN_NKY, m_DrivenNKY);
	DDX_Text(pDX, IDC_EDIT_ENC_NK1, m_EncNK1);
	DDX_Text(pDX, IDC_EDIT_ENC_NK2, m_EncNK2);
	DDX_Text(pDX, IDC_EDIT_ENC_NKY, m_EncNKY);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_NK1, m_HarmonicNK1);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_NK2, m_HarmonicNK2);
	DDX_Text(pDX, IDC_EDIT_HARMONIC_NKY, m_HarmonicNKY);
	DDX_Text(pDX, IDC_EDIT_LIMIT_NK1, m_LimitNK1);
	DDX_Text(pDX, IDC_EDIT_LIMIT_NK2, m_LimitNK2);
	DDX_Text(pDX, IDC_EDIT_LIMIT_NKY, m_LimitNKY);
	DDX_Text(pDX, IDC_EDIT_PULSE_NK1, m_PulseNK1);
	DDX_Text(pDX, IDC_EDIT_PULSE_NK2, m_PulseNK2);
	DDX_Text(pDX, IDC_EDIT_PULSE_NKY, m_PulseNKY);
	DDX_Text(pDX, IDC_EDIT_REV_NK1, m_RevNK1);
	DDX_Text(pDX, IDC_EDIT_REV_NK2, m_RevNK2);
	DDX_Text(pDX, IDC_EDIT_REV_NKY, m_RevNKY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterSetting, CDialog)
	//{{AFX_MSG_MAP(CParameterSetting)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterSetting message handlers


void CParameterSetting::Init()
{

}

void CParameterSetting::DataSave()
{
	// retrieve data
	UpdateData(TRUE);
	
	// open file
	ofstream fout("parameter.par");
	if (!fout.is_open())
	{
		AfxMessageBox("SaveDataToFile() :: parameter.par 파일을 열 수 없습니다.", MB_OK);
		//return -1;
	}
	
	// save data

	fout << m_HarmonicRHY << " " << m_DriveRHY << " " << m_DrivenRHY << " " << m_EncRHY << " " << m_RevRHY << " " <<m_PulseRHY << " " << m_LimitRHY << " " << m_DirRHY << endl;
	fout << m_HarmonicRHR << " " << m_DriveRHR << " " << m_DrivenRHR << " " << m_EncRHR << " " << m_RevRHR << " " <<m_PulseRHR << " " << m_LimitRHR << " " << m_DirRHR << endl;
	fout << m_HarmonicRHP << " " << m_DriveRHP << " " << m_DrivenRHP << " " << m_EncRHP << " " << m_RevRHP << " " <<m_PulseRHP << " " << m_LimitRHP << " " << m_DirRHP << endl;
	fout << m_HarmonicRKN << " " << m_DriveRKN << " " << m_DrivenRKN << " " << m_EncRKN << " " << m_RevRKN << " " <<m_PulseRKN << " " << m_LimitRKN << " " << m_DirRKN << endl;
	fout << m_HarmonicRAP << " " << m_DriveRAP << " " << m_DrivenRAP << " " << m_EncRAP << " " << m_RevRAP << " " <<m_PulseRAP << " " << m_LimitRAP << " " << m_DirRAP << endl;
	fout << m_HarmonicRAR << " " << m_DriveRAR << " " << m_DrivenRAR << " " << m_EncRAR << " " << m_RevRAR << " " <<m_PulseRAR << " " << m_LimitRAR << " " << m_DirRAR << endl;

	fout << m_HarmonicLHY << " " << m_DriveLHY << " " << m_DrivenLHY << " " << m_EncLHY << " " << m_RevLHY << " " <<m_PulseLHY << " " << m_LimitLHY << " " << m_DirLHY << endl;
	fout << m_HarmonicLHR << " " << m_DriveLHR << " " << m_DrivenLHR << " " << m_EncLHR << " " << m_RevLHR << " " <<m_PulseLHR << " " << m_LimitLHR << " " << m_DirLHR << endl;
	fout << m_HarmonicLHP << " " << m_DriveLHP << " " << m_DrivenLHP << " " << m_EncLHP << " " << m_RevLHP << " " <<m_PulseLHP << " " << m_LimitLHP << " " << m_DirLHP << endl;
	fout << m_HarmonicLKN << " " << m_DriveLKN << " " << m_DrivenLKN << " " << m_EncLKN << " " << m_RevLKN << " " <<m_PulseLKN << " " << m_LimitLKN << " " << m_DirLKN << endl;
	fout << m_HarmonicLAP << " " << m_DriveLAP << " " << m_DrivenLAP << " " << m_EncLAP << " " << m_RevLAP << " " <<m_PulseLAP << " " << m_LimitLAP << " " << m_DirLAP << endl;
	fout << m_HarmonicLAR << " " << m_DriveLAR << " " << m_DrivenLAR << " " << m_EncLAR << " " << m_RevLAR << " " <<m_PulseLAR << " " << m_LimitLAR << " " << m_DirLAR << endl;
	

	fout << m_HarmonicRSP << " " << m_DriveRSP << " " << m_DrivenRSP << " " << m_EncRSP << " " << m_RevRSP << " " << m_PulseRSP << " " << m_LimitRSP << " " << m_DirRSP << endl;
	fout << m_HarmonicRSR << " " << m_DriveRSR << " " << m_DrivenRSR << " " << m_EncRSR << " " << m_RevRSR << " " << m_PulseRSR << " " << m_LimitRSR << " " << m_DirRSR << endl;
	fout << m_HarmonicRSY << " " << m_DriveRSY << " " << m_DrivenRSY << " " << m_EncRSY << " " << m_RevRSY << " " << m_PulseRSY << " " << m_LimitRSY << " " << m_DirRSY << endl;
	fout << m_HarmonicREB << " " << m_DriveREB << " " << m_DrivenREB << " " << m_EncREB << " " << m_RevREB << " " << m_PulseREB << " " << m_LimitREB << " " << m_DirREB << endl;
	fout << m_HarmonicRWY << " " << m_DriveRWY << " " << m_DrivenRWY << " " << m_EncRWY << " " << m_RevRWY << " " << m_PulseRWY << " " << m_LimitRWY << " " << m_DirRWY << endl;
	fout << m_HarmonicRW1 << " " << m_DriveRW1 << " " << m_DrivenRW1 << " " << m_EncRW1 << " " << m_RevRW1 << " " << m_PulseRW1 << " " << m_LimitRW1 << " " << m_DirRW1 << endl;
	fout << m_HarmonicRW2 << " " << m_DriveRW2 << " " << m_DrivenRW2 << " " << m_EncRW2 << " " << m_RevRW2 << " " << m_PulseRW2 << " " << m_LimitRW2 << " " << m_DirRW2 << endl;

	fout << m_HarmonicLSP << " " << m_DriveLSP << " " << m_DrivenLSP << " " << m_EncLSP << " " << m_RevLSP << " " << m_PulseLSP << " " << m_LimitLSP << " " << m_DirLSP << endl;
	fout << m_HarmonicLSR << " " << m_DriveLSR << " " << m_DrivenLSR << " " << m_EncLSR << " " << m_RevLSR << " " << m_PulseLSR << " " << m_LimitLSR << " " << m_DirLSR << endl;
	fout << m_HarmonicLSY << " " << m_DriveLSY << " " << m_DrivenLSY << " " << m_EncLSY << " " << m_RevLSY << " " << m_PulseLSY << " " << m_LimitLSY << " " << m_DirLSY << endl;
	fout << m_HarmonicLEB << " " << m_DriveLEB << " " << m_DrivenLEB << " " << m_EncLEB << " " << m_RevLEB << " " << m_PulseLEB << " " << m_LimitLEB << " " << m_DirLEB << endl;
	fout << m_HarmonicLWY << " " << m_DriveLWY << " " << m_DrivenLWY << " " << m_EncLWY << " " << m_RevLWY << " " << m_PulseLWY << " " << m_LimitLWY << " " << m_DirLWY << endl;
	fout << m_HarmonicLW1 << " " << m_DriveLW1 << " " << m_DrivenLW1 << " " << m_EncLW1 << " " << m_RevLW1 << " " << m_PulseLW1 << " " << m_LimitLW1 << " " << m_DirLW1 << endl;
	fout << m_HarmonicLW2 << " " << m_DriveLW2 << " " << m_DrivenLW2 << " " << m_EncLW2 << " " << m_RevLW2 << " " << m_PulseLW2 << " " << m_LimitLW2 << " " << m_DirLW2 << endl;

	fout << m_HarmonicWST << " " << m_DriveWST << " " << m_DrivenWST << " " << m_EncWST << " " << m_RevWST << " " << m_PulseWST << " " << m_LimitWST << " " << m_DirWST << endl;

	fout << m_HarmonicNKY << " " << m_DriveNKY << " " << m_DrivenNKY << " " << m_EncNKY << " " << m_RevNKY << " " << m_PulseNKY << " " << m_LimitNKY << " " << m_DirNKY << endl;
	fout << m_HarmonicNK1 << " " << m_DriveNK1 << " " << m_DrivenNK1 << " " << m_EncNK1 << " " << m_RevNK1 << " " << m_PulseNK1 << " " << m_LimitNK1 << " " << m_DirNK1 << endl;
	fout << m_HarmonicNK2 << " " << m_DriveNK2 << " " << m_DrivenNK2 << " " << m_EncNK2 << " " << m_RevNK2 << " " << m_PulseNK2 << " " << m_LimitNK2 << " " << m_DirNK2 << endl;
	



	// close file
	fout.close();
	
	//return 0;

}

void CParameterSetting::DataLoad()
{
	// open file
	ifstream fin("parameter.par");
	if (!fin.is_open())
	{
		AfxMessageBox("LoadDataFromFile() :: parameter.par 파일을 열 수 없습니다.", MB_OK);
		//return -1;
	}
	
	// read data

	fin >> m_HarmonicRHY >> m_DriveRHY >> m_DrivenRHY >> m_EncRHY >> m_RevRHY >> m_PulseRHY >> m_LimitRHY >> m_DirRHY;
	fin >> m_HarmonicRHR >> m_DriveRHR >> m_DrivenRHR >> m_EncRHR >> m_RevRHR >> m_PulseRHR >> m_LimitRHR >> m_DirRHR;
	fin >> m_HarmonicRHP >> m_DriveRHP >> m_DrivenRHP >> m_EncRHP >> m_RevRHP >> m_PulseRHP >> m_LimitRHP >> m_DirRHP;
	fin >> m_HarmonicRKN >> m_DriveRKN >> m_DrivenRKN >> m_EncRKN >> m_RevRKN >> m_PulseRKN >> m_LimitRKN >> m_DirRKN;
	fin >> m_HarmonicRAP >> m_DriveRAP >> m_DrivenRAP >> m_EncRAP >> m_RevRAP >> m_PulseRAP >> m_LimitRAP >> m_DirRAP;
	fin >> m_HarmonicRAR >> m_DriveRAR >> m_DrivenRAR >> m_EncRAR >> m_RevRAR >> m_PulseRAR >> m_LimitRAR >> m_DirRAR;

	fin >> m_HarmonicLHY >> m_DriveLHY >> m_DrivenLHY >> m_EncLHY >> m_RevLHY >> m_PulseLHY >> m_LimitLHY >> m_DirLHY;
	fin >> m_HarmonicLHR >> m_DriveLHR >> m_DrivenLHR >> m_EncLHR >> m_RevLHR >> m_PulseLHR >> m_LimitLHR >> m_DirLHR;
	fin >> m_HarmonicLHP >> m_DriveLHP >> m_DrivenLHP >> m_EncLHP >> m_RevLHP >> m_PulseLHP >> m_LimitLHP >> m_DirLHP;
	fin >> m_HarmonicLKN >> m_DriveLKN >> m_DrivenLKN >> m_EncLKN >> m_RevLKN >> m_PulseLKN >> m_LimitLKN >> m_DirLKN;
	fin >> m_HarmonicLAP >> m_DriveLAP >> m_DrivenLAP >> m_EncLAP >> m_RevLAP >> m_PulseLAP >> m_LimitLAP >> m_DirLAP;
	fin >> m_HarmonicLAR >> m_DriveLAR >> m_DrivenLAR >> m_EncLAR >> m_RevLAR >> m_PulseLAR >> m_LimitLAR >> m_DirLAR;

	fin >> m_HarmonicRSP >> m_DriveRSP >> m_DrivenRSP >> m_EncRSP >> m_RevRSP >> m_PulseRSP >> m_LimitRSP >> m_DirRSP;
	fin >> m_HarmonicRSR >> m_DriveRSR >> m_DrivenRSR >> m_EncRSR >> m_RevRSR >> m_PulseRSR >> m_LimitRSR >> m_DirRSR;
	fin >> m_HarmonicRSY >> m_DriveRSY >> m_DrivenRSY >> m_EncRSY >> m_RevRSY >> m_PulseRSY >> m_LimitRSY >> m_DirRSY;
	fin >> m_HarmonicREB >> m_DriveREB >> m_DrivenREB >> m_EncREB >> m_RevREB >> m_PulseREB >> m_LimitREB >> m_DirREB;
	fin >> m_HarmonicRWY >> m_DriveRWY >> m_DrivenRWY >> m_EncRWY >> m_RevRWY >> m_PulseRWY >> m_LimitRWY >> m_DirRWY;
	fin >> m_HarmonicRW1 >> m_DriveRW1 >> m_DrivenRW1 >> m_EncRW1 >> m_RevRW1 >> m_PulseRW1 >> m_LimitRW1 >> m_DirRW1;
	fin >> m_HarmonicRW2 >> m_DriveRW2 >> m_DrivenRW2 >> m_EncRW2 >> m_RevRW2 >> m_PulseRW2 >> m_LimitRW2 >> m_DirRW2;


	fin >> m_HarmonicLSP >> m_DriveLSP >> m_DrivenLSP >> m_EncLSP >> m_RevLSP >> m_PulseLSP >> m_LimitLSP >> m_DirLSP;
	fin >> m_HarmonicLSR >> m_DriveLSR >> m_DrivenLSR >> m_EncLSR >> m_RevLSR >> m_PulseLSR >> m_LimitLSR >> m_DirLSR;
	fin >> m_HarmonicLSY >> m_DriveLSY >> m_DrivenLSY >> m_EncLSY >> m_RevLSY >> m_PulseLSY >> m_LimitLSY >> m_DirLSY;
	fin >> m_HarmonicLEB >> m_DriveLEB >> m_DrivenLEB >> m_EncLEB >> m_RevLEB >> m_PulseLEB >> m_LimitLEB >> m_DirLEB;
	fin >> m_HarmonicLWY >> m_DriveLWY >> m_DrivenLWY >> m_EncLWY >> m_RevLWY >> m_PulseLWY >> m_LimitLWY >> m_DirLWY;
	fin >> m_HarmonicLW1 >> m_DriveLW1 >> m_DrivenLW1 >> m_EncLW1 >> m_RevLW1 >> m_PulseLW1 >> m_LimitLW1 >> m_DirLW1;
	fin >> m_HarmonicLW2 >> m_DriveLW2 >> m_DrivenLW2 >> m_EncLW2 >> m_RevLW2 >> m_PulseLW2 >> m_LimitLW2 >> m_DirLW2;

	fin >> m_HarmonicWST >> m_DriveWST >> m_DrivenWST >> m_EncWST >> m_RevWST >> m_PulseWST >> m_LimitWST >> m_DirWST;

	fin >> m_HarmonicNKY >> m_DriveNKY >> m_DrivenNKY >> m_EncNKY >> m_RevNKY >> m_PulseNKY >> m_LimitNKY >> m_DirNKY;
	fin >> m_HarmonicNK1 >> m_DriveNK1 >> m_DrivenNK1 >> m_EncNK1 >> m_RevNK1 >> m_PulseNK1 >> m_LimitNK1 >> m_DirNK1;
	fin >> m_HarmonicNK2 >> m_DriveNK2 >> m_DrivenNK2 >> m_EncNK2 >> m_RevNK2 >> m_PulseNK2 >> m_LimitNK2 >> m_DirNK2;
	

	
	// close file
	fin.close();
	
	// print data
	UpdateData(FALSE);
	
	//return 0;

}

void CParameterSetting::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	DataLoad();
}

void CParameterSetting::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	DataSave();	
}

//DEL int CParameterSetting::DataLoad1()
//DEL {
//DEL 	//int data[ROW][COL] = {0, };
//DEL 	float data[ROW][COL];
//DEL 	int iLine, iColumn;
//DEL 	char chLine, chColumn;
//DEL 	
//DEL 	// open file
//DEL 	ifstream fin("data.txt");
//DEL 	if (!fin.is_open())
//DEL 	{
//DEL 		AfxMessageBox("LoadDataFromFile() :: data.dat 파일을 열 수 없습니다.", MB_OK);
//DEL 		return -1;
//DEL 	}
//DEL 	
//DEL 	// read data
//DEL 	for (int i = 0; i < ROW; i++)
//DEL 	{
//DEL 		fout >> chLine >> iLine >> chColumn >> iColumn;
//DEL 		
//DEL 		if (chLine == 'l' && iLine == i && chColumn == 'c')
//DEL 		{
//DEL 			int iTemp;
//DEL 			for (int j = 0; j < iColumn; j++)
//DEL 			{
//DEL 				if (j < COL)
//DEL 					fout >> data[i][j];
//DEL 				else
//DEL 					fout >> iTemp;
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 	
//DEL 	//m_editData00 = data[0][0]; m_editData01 = data[0][1]; m_editData02 = data[0][2];	// "데이타 추가/삭제 시 수정할 부분"
//DEL 	//m_editData10 = data[1][0]; m_editData11 = data[1][1]; m_editData12 = data[1][2];
//DEL 	//m_editData20 = data[2][0]; m_editData21 = data[2][1]; m_editData22 = data[2][2];
//DEL 	//m_editData30 = data[3][0]; m_editData31 = data[3][1]; m_editData32 = data[3][2];
//DEL 	
//DEL 	m_HarmonicRHY = data[0][0];
//DEL 	m_HarmonicRHR = data[1][0];
//DEL 	m_HarmonicRHP = data[2][0];
//DEL 	m_HarmonicRKN = data[3][0];
//DEL 	m_HarmonicRAP = data[4][0];
//DEL 	m_HarmonicRAR = data[5][0];
//DEL 	m_HarmonicLHY = data[6][0];
//DEL 	m_HarmonicLHR = data[7][0];
//DEL 	m_HarmonicLHP = data[8][0];
//DEL 	m_HarmonicLKN = data[9][0];
//DEL 	m_HarmonicLAP = data[10][0];
//DEL 	m_HarmonicLAR = data[11][0];
//DEL 	
//DEL 	m_DriveRHY = data[0][1];
//DEL 	m_DriveRHR = data[1][1];
//DEL 	m_DriveRHP = data[2][1];
//DEL 	m_DriveRKN = data[3][1];
//DEL 	m_DriveRAP = data[4][1];
//DEL 	m_DriveRAR = data[5][1];
//DEL 	m_DriveLHY = data[6][1];
//DEL 	m_DriveLHR = data[7][1];
//DEL 	m_DriveLHP = data[8][1];
//DEL 	m_DriveLKN = data[9][1];
//DEL 	m_DriveLAP = data[10][1];
//DEL 	m_DriveLAR = data[11][1];
//DEL 	
//DEL 	m_DrivenRHY = data[0][2];
//DEL 	m_DrivenRHR = data[1][2];
//DEL 	m_DrivenRHP = data[2][2];
//DEL 	m_DrivenRKN = data[3][2];
//DEL 	m_DrivenRAP = data[4][2];
//DEL 	m_DrivenRAR = data[5][2];
//DEL 	m_DrivenLHY = data[6][2];
//DEL 	m_DrivenLHR = data[7][2];
//DEL 	m_DrivenLHP = data[8][2];
//DEL 	m_DrivenLKN = data[9][2];
//DEL 	m_DrivenLAP = data[10][2];
//DEL 	m_DrivenLAR = data[11][2];
//DEL 	
//DEL 	m_EncRHY = data[0][3];
//DEL 	m_EncRHR = data[1][3];
//DEL 	m_EncRHP = data[2][3];
//DEL 	m_EncRKN = data[3][3];
//DEL 	m_EncRAP = data[4][3];
//DEL 	m_EncRAR = data[5][3];
//DEL 	m_EncLHY = data[6][3];
//DEL 	m_EncLHR = data[7][3];
//DEL 	m_EncLHP = data[8][3];
//DEL 	m_EncLKN = data[9][3];
//DEL 	m_EncLAP = data[10][3];
//DEL 	m_EncLAR = data[11][3];
//DEL 	
//DEL 	m_RevRHY = data[0][4];
//DEL 	m_RevRHR = data[1][4];
//DEL 	m_RevRHP = data[2][4];
//DEL 	m_RevRKN = data[3][4];
//DEL 	m_RevRAP = data[4][4];
//DEL 	m_RevRAR = data[5][4];
//DEL 	m_RevLHY = data[6][4];
//DEL 	m_RevLHR = data[7][4];
//DEL 	m_RevLHP = data[8][4];
//DEL 	m_RevLKN = data[9][4];
//DEL 	m_RevLAP = data[10][4];
//DEL 	m_RevLAR = data[11][4];
//DEL 	
//DEL 	m_PulseRHY = data[0][5];
//DEL 	m_PulseRHR = data[1][5];
//DEL 	m_PulseRHP = data[2][5];
//DEL 	m_PulseRKN = data[3][5];
//DEL 	m_PulseRAP = data[4][5];
//DEL 	m_PulseRAR = data[5][5];
//DEL 	m_PulseLHY = data[6][5];
//DEL 	m_PulseLHR = data[7][5];
//DEL 	m_PulseLHP = data[8][5];
//DEL 	m_PulseLKN = data[9][5];
//DEL 	m_PulseLAP = data[10][5];
//DEL 	m_PulseLAR = data[11][5];
//DEL 	
//DEL 	m_LimitRHY = data[0][6];
//DEL 	m_LimitRHR = data[1][6];
//DEL 	m_LimitRHP = data[2][6];
//DEL 	m_LimitRKN = data[3][6];
//DEL 	m_LimitRAP = data[4][6];
//DEL 	m_LimitRAR = data[5][6];
//DEL 	m_LimitLHY = data[6][6];
//DEL 	m_LimitLHR = data[7][6];
//DEL 	m_LimitLHP = data[8][6];
//DEL 	m_LimitLKN = data[9][6];
//DEL 	m_LimitLAP = data[10][6];
//DEL 	m_LimitLAR = data[11][6];
//DEL 
//DEL 	// close file
//DEL 	fin.close();
//DEL 	
//DEL 	// print data
//DEL 	UpdateData(FALSE);
//DEL 	
//DEL 	return 0;
//DEL 
//DEL }

//DEL int CParameterSetting::DataSave1()
//DEL {
//DEL 	UpdateData(TRUE);
//DEL 	
//DEL 	//int data[ROW][COL] = {0, };
//DEL 	float data[ROW][COL];
//DEL 
//DEL 	data[0][0] = m_HarmonicRHY;
//DEL 	data[1][0] = m_HarmonicRHR;
//DEL 	data[2][0] = m_HarmonicRHP;
//DEL 	data[3][0] = m_HarmonicRKN;
//DEL 	data[4][0] = m_HarmonicRAP;
//DEL 	data[5][0] = m_HarmonicRAR;
//DEL 	data[6][0] = m_HarmonicLHY;
//DEL 	data[7][0] = m_HarmonicLHR;
//DEL 	data[8][0] = m_HarmonicLHP;
//DEL 	data[9][0] = m_HarmonicLKN;
//DEL 	data[10][0] = m_HarmonicLAP;
//DEL 	data[11][0] = m_HarmonicLAR;
//DEL 	
//DEL 	data[0][1] = m_DriveRHY;
//DEL 	data[1][1] = m_DriveRHR;
//DEL 	data[2][1] = m_DriveRHP;
//DEL 	data[3][1] = m_DriveRKN;
//DEL 	data[4][1] = m_DriveRAP;
//DEL 	data[5][1] = m_DriveRAR;
//DEL 	data[6][1] = m_DriveLHY;
//DEL 	data[7][1] = m_DriveLHR;
//DEL 	data[8][1] = m_DriveLHP;
//DEL 	data[9][1] = m_DriveLKN;
//DEL 	data[10][1] = m_DriveLAP;
//DEL 	data[11][1] = m_DriveLAR;
//DEL 
//DEL 	data[0][2] = m_DrivenRHY;
//DEL 	data[1][2] = m_DrivenRHR;
//DEL 	data[2][2] = m_DrivenRHP;
//DEL 	data[3][2] = m_DrivenRKN;
//DEL 	data[4][2] = m_DrivenRAP;
//DEL 	data[5][2] = m_DrivenRAR;
//DEL 	data[6][2] = m_DrivenLHY;
//DEL 	data[7][2] = m_DrivenLHR;
//DEL 	data[8][2] = m_DrivenLHP;
//DEL 	data[9][2] = m_DrivenLKN;
//DEL 	data[10][2] = m_DrivenLAP;
//DEL 	data[11][2] = m_DrivenLAR;
//DEL 
//DEL 	data[0][3] = m_EncRHY;
//DEL 	data[1][3] = m_EncRHR;
//DEL 	data[2][3] = m_EncRHP;
//DEL 	data[3][3] = m_EncRKN;
//DEL 	data[4][3] = m_EncRAP;
//DEL 	data[5][3] = m_EncRAR;
//DEL 	data[6][3] = m_EncLHY;
//DEL 	data[7][3] = m_EncLHR;
//DEL 	data[8][3] = m_EncLHP;
//DEL 	data[9][3] = m_EncLKN;
//DEL 	data[10][3] = m_EncLAP;
//DEL 	data[11][3] = m_EncLAR;
//DEL 
//DEL 	data[0][4] = m_RevRHY;
//DEL 	data[1][4] = m_RevRHR;
//DEL 	data[2][4] = m_RevRHP;
//DEL 	data[3][4] = m_RevRKN;
//DEL 	data[4][4] = m_RevRAP;
//DEL 	data[5][4] = m_RevRAR;
//DEL 	data[6][4] = m_RevLHY;
//DEL 	data[7][4] = m_RevLHR;
//DEL 	data[8][4] = m_RevLHP;
//DEL 	data[9][4] = m_RevLKN;
//DEL 	data[10][4] = m_RevLAP;
//DEL 	data[11][4] = m_RevLAR;
//DEL 
//DEL 	data[0][5] = m_PulseRHY;
//DEL 	data[1][5] = m_PulseRHR;
//DEL 	data[2][5] = m_PulseRHP;
//DEL 	data[3][5] = m_PulseRKN;
//DEL 	data[4][5] = m_PulseRAP;
//DEL 	data[5][5] = m_PulseRAR;
//DEL 	data[6][5] = m_PulseLHY;
//DEL 	data[7][5] = m_PulseLHR;
//DEL 	data[8][5] = m_PulseLHP;
//DEL 	data[9][5] = m_PulseLKN;
//DEL 	data[10][5] = m_PulseLAP;
//DEL 	data[11][5] = m_PulseLAR;
//DEL 
//DEL 	data[0][6] = m_LimitRHY;
//DEL 	data[1][6] = m_LimitRHR;
//DEL 	data[2][6] = m_LimitRHP;
//DEL 	data[3][6] = m_LimitRKN;
//DEL 	data[4][6] = m_LimitRAP;
//DEL 	data[5][6] = m_LimitRAR;
//DEL 	data[6][6] = m_LimitLHY;
//DEL 	data[7][6] = m_LimitLHR;
//DEL 	data[8][6] = m_LimitLHP;
//DEL 	data[9][6] = m_LimitLKN;
//DEL 	data[10][6] = m_LimitLAP;
//DEL 	data[11][6] = m_LimitLAR;
//DEL 
//DEL 	
//DEL 
//DEL 	// open file
//DEL 	ofstream fout("data.txt");
//DEL 	if (!fout.is_open())
//DEL 	{
//DEL 		AfxMessageBox("SaveDataToFile() :: data.dat 파일을 열 수 없습니다.", MB_OK);
//DEL 		return -1;
//DEL 	}
//DEL 	
//DEL 	// save data
//DEL 	for (int i = 0; i < ROW; i++)
//DEL 	{
//DEL 		fout << 'l' << " "<< i << " " << 'c' << " " << COL << " ";		// data index (l line_number c column_count)
//DEL 		
//DEL 		for (int j = 0; j < COL; j++)
//DEL 		{
//DEL 			fout << data[i][j] << " ";
//DEL 		}
//DEL 		fout << endl;
//DEL 	}
//DEL 	
//DEL 	// close file
//DEL 	fout.close();
//DEL 	
//DEL 	return 0;
//DEL 
//DEL }
