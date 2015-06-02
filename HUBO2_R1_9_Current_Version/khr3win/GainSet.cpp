// GainSet.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "GainSet.h"
#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGainSet dialog


CGainSet::CGainSet(CWnd* pParent /*=NULL*/)
	: CDialog(CGainSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGainSet)
	m_LAP_Kd0 = 0;
	m_LAP_Kd1 = 0;
	m_LAP_Ki0 = 0;
	m_LAP_Ki1 = 0;
	m_LAP_Kp0 = 0;
	m_LAP_Kp1 = 0;
	m_LAR_Kd0 = 0;
	m_LAR_Kd1 = 0;
	m_LAR_Ki0 = 0;
	m_LAR_Ki1 = 0;
	m_LAR_Kp0 = 0;
	m_LAR_Kp1 = 0;
	m_LHP_Kd0 = 0;
	m_LHP_Kd1 = 0;
	m_LHP_Ki0 = 0;
	m_LHP_Ki1 = 0;
	m_LHP_Kp0 = 0;
	m_LHP_Kp1 = 0;
	m_LHR_Kd0 = 0;
	m_LHR_Kd1 = 0;
	m_LHR_Ki0 = 0;
	m_LHR_Ki1 = 0;
	m_LHR_Kp1 = 0;
	m_LHY_Kd0 = 0;
	m_LHY_Kd1 = 0;
	m_LHY_Ki0 = 0;
	m_LHY_Ki1 = 0;
	m_LHY_Kp0 = 0;
	m_LHY_Kp1 = 0;
	m_LKN_Kd0 = 0;
	m_LKN_Kd1 = 0;
	m_LKN_Ki0 = 0;
	m_LKN_Ki1 = 0;
	m_LKN_Kp0 = 0;
	m_LKN_Kp1 = 0;
	m_RAP_Kd0 = 0;
	m_RAP_Kd1 = 0;
	m_RAP_Ki0 = 0;
	m_RAP_Ki1 = 0;
	m_RAP_Kp0 = 0;
	m_RAP_Kp1 = 0;
	m_RAR_Kd0 = 0;
	m_RAR_Kd1 = 0;
	m_RAR_Ki0 = 0;
	m_RAR_Ki1 = 0;
	m_RAR_Kp0 = 0;
	m_RAR_Kp1 = 0;
	m_RHP_Kd0 = 0;
	m_RHP_Kd1 = 0;
	m_RHP_Ki0 = 0;
	m_RHP_Ki1 = 0;
	m_RHP_Kp0 = 0;
	m_RHP_Kp1 = 0;
	m_RHR_Kd0 = 0;
	m_RHR_Kd1 = 0;
	m_RHR_Ki0 = 0;
	m_RHR_Ki1 = 0;
	m_RHR_Kp0 = 0;
	m_RHR_Kp1 = 0;
	m_RHY_Kd0 = 0;
	m_RHY_Kd1 = 0;
	m_RHY_Ki0 = 0;
	m_RHY_Ki1 = 0;
	m_RHY_Kp0 = 0;
	m_RHY_Kp1 = 0;
	m_RKN_Kd0 = 0;
	m_RKN_Kd1 = 0;
	m_RKN_Ki0 = 0;
	m_RKN_Ki1 = 0;
	m_RKN_Kp0 = 0;
	m_RKN_Kp1 = 0;
	m_LHR_Kp0 = 0;
	m_LEB_Kd0 = 0;
	m_LEB_Kd1 = 0;
	m_LEB_Ki0 = 0;
	m_LEB_Ki1 = 0;
	m_LEB_Kp0 = 0;
	m_LEB_Kp1 = 0;
	m_LSP_Kd0 = 0;
	m_LSP_Kd1 = 0;
	m_LSP_Ki0 = 0;
	m_LSP_Ki1 = 0;
	m_LSP_Kp0 = 0;
	m_LSP_Kp1 = 0;
	m_LSR_Kd0 = 0;
	m_LSR_Kd1 = 0;
	m_LSR_Ki0 = 0;
	m_LSR_Ki1 = 0;
	m_LSR_Kp0 = 0;
	m_LSR_Kp1 = 0;
	m_LSY_Kd0 = 0;
	m_LSY_Kd1 = 0;
	m_LSY_Ki0 = 0;
	m_LSY_Ki1 = 0;
	m_LSY_Kp0 = 0;
	m_LSY_Kp1 = 0;
	m_LW1_Kd0 = 0;
	m_LW1_Kd1 = 0;
	m_LW1_Ki0 = 0;
	m_LW1_Ki1 = 0;
	m_LW1_Kp0 = 0;
	m_LW1_Kp1 = 0;
	m_LW2_Kd0 = 0;
	m_LW2_Kd1 = 0;
	m_LW2_Ki0 = 0;
	m_LW2_Ki1 = 0;
	m_LW2_Kp0 = 0;
	m_LW2_Kp1 = 0;
	m_LWY_Kd0 = 0;
	m_LWY_Kd1 = 0;
	m_LWY_Ki0 = 0;
	m_LWY_Ki1 = 0;
	m_LWY_Kp0 = 0;
	m_LWY_Kp1 = 0;
	m_REB_Kd0 = 0;
	m_REB_Kd1 = 0;
	m_REB_Ki0 = 0;
	m_REB_Ki1 = 0;
	m_REB_Kp0 = 0;
	m_REB_Kp1 = 0;
	m_RSP_Kd0 = 0;
	m_RSP_Kd1 = 0;
	m_RSP_Ki0 = 0;
	m_RSP_Ki1 = 0;
	m_RSP_Kp0 = 0;
	m_RSP_Kp1 = 0;
	m_RSR_Kd0 = 0;
	m_RSR_Kd1 = 0;
	m_RSR_Ki0 = 0;
	m_RSR_Ki1 = 0;
	m_RSR_Kp0 = 0;
	m_RSR_Kp1 = 0;
	m_RSY_Kd0 = 0;
	m_RSY_Kd1 = 0;
	m_RSY_Ki0 = 0;
	m_RSY_Ki1 = 0;
	m_RSY_Kp0 = 0;
	m_RSY_Kp1 = 0;
	m_RW1_Kd0 = 0;
	m_RW1_Kd1 = 0;
	m_RW1_Ki0 = 0;
	m_RW1_Ki1 = 0;
	m_RW1_Kp0 = 0;
	m_RW1_Kp1 = 0;
	m_RW2_Kd0 = 0;
	m_RW2_Kd1 = 0;
	m_RW2_Ki0 = 0;
	m_RW2_Ki1 = 0;
	m_RW2_Kp0 = 0;
	m_RW2_Kp1 = 0;
	m_RWY_Kd0 = 0;
	m_RWY_Kd1 = 0;
	m_RWY_Ki0 = 0;
	m_RWY_Ki1 = 0;
	m_RWY_Kp0 = 0;
	m_RWY_Kp1 = 0;
	m_WST_Kd0 = 0;
	m_WST_Kd1 = 0;
	m_WST_Ki0 = 0;
	m_WST_Ki1 = 0;
	m_WST_Kp0 = 0;
	m_WST_Kp1 = 0;
	m_NK1_Kd0 = 0;
	m_NK1_Ki0 = 0;
	m_NK1_Ki1 = 0;
	m_NK1_Kp0 = 0;
	m_NK1_Kp1 = 0;
	m_NK2_Kd0 = 0;
	m_NK2_Kd1 = 0;
	m_NK2_Ki0 = 0;
	m_NK2_Ki1 = 0;
	m_NK2_Kp0 = 0;
	m_NK2_Kp1 = 0;
	m_NKY_Kd0 = 0;
	m_NK1_Kd1 = 0;
	m_NKY_Kd1 = 0;
	m_NKY_Ki0 = 0;
	m_NKY_Ki1 = 0;
	m_NKY_Kp0 = 0;
	m_NKY_Kp1 = 0;
	//}}AFX_DATA_INIT
}


void CGainSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGainSet)
	DDX_Text(pDX, IDC_EDIT_LAP_KD0, m_LAP_Kd0);
	DDX_Text(pDX, IDC_EDIT_LAP_KD1, m_LAP_Kd1);
	DDX_Text(pDX, IDC_EDIT_LAP_KI0, m_LAP_Ki0);
	DDX_Text(pDX, IDC_EDIT_LAP_KI1, m_LAP_Ki1);
	DDX_Text(pDX, IDC_EDIT_LAP_KP0, m_LAP_Kp0);
	DDX_Text(pDX, IDC_EDIT_LAP_KP1, m_LAP_Kp1);
	DDX_Text(pDX, IDC_EDIT_LAR_KD0, m_LAR_Kd0);
	DDX_Text(pDX, IDC_EDIT_LAR_KD1, m_LAR_Kd1);
	DDX_Text(pDX, IDC_EDIT_LAR_KI0, m_LAR_Ki0);
	DDX_Text(pDX, IDC_EDIT_LAR_KI1, m_LAR_Ki1);
	DDX_Text(pDX, IDC_EDIT_LAR_KP0, m_LAR_Kp0);
	DDX_Text(pDX, IDC_EDIT_LAR_KP1, m_LAR_Kp1);
	DDX_Text(pDX, IDC_EDIT_LHP_KD0, m_LHP_Kd0);
	DDX_Text(pDX, IDC_EDIT_LHP_KD1, m_LHP_Kd1);
	DDX_Text(pDX, IDC_EDIT_LHP_KI0, m_LHP_Ki0);
	DDX_Text(pDX, IDC_EDIT_LHP_KI1, m_LHP_Ki1);
	DDX_Text(pDX, IDC_EDIT_LHP_KP0, m_LHP_Kp0);
	DDX_Text(pDX, IDC_EDIT_LHP_KP1, m_LHP_Kp1);
	DDX_Text(pDX, IDC_EDIT_LHR_KD0, m_LHR_Kd0);
	DDX_Text(pDX, IDC_EDIT_LHR_KD1, m_LHR_Kd1);
	DDX_Text(pDX, IDC_EDIT_LHR_KI0, m_LHR_Ki0);
	DDX_Text(pDX, IDC_EDIT_LHR_KI1, m_LHR_Ki1);
	DDX_Text(pDX, IDC_EDIT_LHR_KP1, m_LHR_Kp1);
	DDX_Text(pDX, IDC_EDIT_LHY_KD0, m_LHY_Kd0);
	DDX_Text(pDX, IDC_EDIT_LHY_KD1, m_LHY_Kd1);
	DDX_Text(pDX, IDC_EDIT_LHY_KI0, m_LHY_Ki0);
	DDX_Text(pDX, IDC_EDIT_LHY_KI1, m_LHY_Ki1);
	DDX_Text(pDX, IDC_EDIT_LHY_KP0, m_LHY_Kp0);
	DDX_Text(pDX, IDC_EDIT_LHY_KP1, m_LHY_Kp1);
	DDX_Text(pDX, IDC_EDIT_LKN_KD0, m_LKN_Kd0);
	DDX_Text(pDX, IDC_EDIT_LKN_KD1, m_LKN_Kd1);
	DDX_Text(pDX, IDC_EDIT_LKN_KI0, m_LKN_Ki0);
	DDX_Text(pDX, IDC_EDIT_LKN_KI1, m_LKN_Ki1);
	DDX_Text(pDX, IDC_EDIT_LKN_KP0, m_LKN_Kp0);
	DDX_Text(pDX, IDC_EDIT_LKN_KP1, m_LKN_Kp1);
	DDX_Text(pDX, IDC_EDIT_RAP_KD0, m_RAP_Kd0);
	DDX_Text(pDX, IDC_EDIT_RAP_KD1, m_RAP_Kd1);
	DDX_Text(pDX, IDC_EDIT_RAP_KI0, m_RAP_Ki0);
	DDX_Text(pDX, IDC_EDIT_RAP_KI1, m_RAP_Ki1);
	DDX_Text(pDX, IDC_EDIT_RAP_KP0, m_RAP_Kp0);
	DDX_Text(pDX, IDC_EDIT_RAP_KP1, m_RAP_Kp1);
	DDX_Text(pDX, IDC_EDIT_RAR_KD0, m_RAR_Kd0);
	DDX_Text(pDX, IDC_EDIT_RAR_KD1, m_RAR_Kd1);
	DDX_Text(pDX, IDC_EDIT_RAR_KI0, m_RAR_Ki0);
	DDX_Text(pDX, IDC_EDIT_RAR_KI1, m_RAR_Ki1);
	DDX_Text(pDX, IDC_EDIT_RAR_KP0, m_RAR_Kp0);
	DDX_Text(pDX, IDC_EDIT_RAR_KP1, m_RAR_Kp1);
	DDX_Text(pDX, IDC_EDIT_RHP_KD0, m_RHP_Kd0);
	DDX_Text(pDX, IDC_EDIT_RHP_KD1, m_RHP_Kd1);
	DDX_Text(pDX, IDC_EDIT_RHP_KI0, m_RHP_Ki0);
	DDX_Text(pDX, IDC_EDIT_RHP_KI1, m_RHP_Ki1);
	DDX_Text(pDX, IDC_EDIT_RHP_KP0, m_RHP_Kp0);
	DDX_Text(pDX, IDC_EDIT_RHP_KP1, m_RHP_Kp1);
	DDX_Text(pDX, IDC_EDIT_RHR_KD0, m_RHR_Kd0);
	DDX_Text(pDX, IDC_EDIT_RHR_KD1, m_RHR_Kd1);
	DDX_Text(pDX, IDC_EDIT_RHR_KI0, m_RHR_Ki0);
	DDX_Text(pDX, IDC_EDIT_RHR_KI1, m_RHR_Ki1);
	DDX_Text(pDX, IDC_EDIT_RHR_KP0, m_RHR_Kp0);
	DDX_Text(pDX, IDC_EDIT_RHR_KP1, m_RHR_Kp1);
	DDX_Text(pDX, IDC_EDIT_RHY_KD0, m_RHY_Kd0);
	DDX_Text(pDX, IDC_EDIT_RHY_KD1, m_RHY_Kd1);
	DDX_Text(pDX, IDC_EDIT_RHY_KI0, m_RHY_Ki0);
	DDX_Text(pDX, IDC_EDIT_RHY_KI1, m_RHY_Ki1);
	DDX_Text(pDX, IDC_EDIT_RHY_KP0, m_RHY_Kp0);
	DDX_Text(pDX, IDC_EDIT_RHY_KP1, m_RHY_Kp1);
	DDX_Text(pDX, IDC_EDIT_RKN_KD0, m_RKN_Kd0);
	DDX_Text(pDX, IDC_EDIT_RKN_KD1, m_RKN_Kd1);
	DDX_Text(pDX, IDC_EDIT_RKN_KI0, m_RKN_Ki0);
	DDX_Text(pDX, IDC_EDIT_RKN_KI1, m_RKN_Ki1);
	DDX_Text(pDX, IDC_EDIT_RKN_KP0, m_RKN_Kp0);
	DDX_Text(pDX, IDC_EDIT_RKN_KP1, m_RKN_Kp1);
	DDX_Text(pDX, IDC_EDIT_LHR_KP0, m_LHR_Kp0);
	DDX_Text(pDX, IDC_EDIT_LEB_KD0, m_LEB_Kd0);
	DDX_Text(pDX, IDC_EDIT_LEB_KD1, m_LEB_Kd1);
	DDX_Text(pDX, IDC_EDIT_LEB_KI0, m_LEB_Ki0);
	DDX_Text(pDX, IDC_EDIT_LEB_KI1, m_LEB_Ki1);
	DDX_Text(pDX, IDC_EDIT_LEB_KP0, m_LEB_Kp0);
	DDX_Text(pDX, IDC_EDIT_LEB_KP1, m_LEB_Kp1);
	DDX_Text(pDX, IDC_EDIT_LSP_KD0, m_LSP_Kd0);
	DDX_Text(pDX, IDC_EDIT_LSP_KD1, m_LSP_Kd1);
	DDX_Text(pDX, IDC_EDIT_LSP_KI0, m_LSP_Ki0);
	DDX_Text(pDX, IDC_EDIT_LSP_KI1, m_LSP_Ki1);
	DDX_Text(pDX, IDC_EDIT_LSP_KP0, m_LSP_Kp0);
	DDX_Text(pDX, IDC_EDIT_LSP_KP1, m_LSP_Kp1);
	DDX_Text(pDX, IDC_EDIT_LSR_KD0, m_LSR_Kd0);
	DDX_Text(pDX, IDC_EDIT_LSR_KD1, m_LSR_Kd1);
	DDX_Text(pDX, IDC_EDIT_LSR_KI0, m_LSR_Ki0);
	DDX_Text(pDX, IDC_EDIT_LSR_KI1, m_LSR_Ki1);
	DDX_Text(pDX, IDC_EDIT_LSR_KP0, m_LSR_Kp0);
	DDX_Text(pDX, IDC_EDIT_LSR_KP1, m_LSR_Kp1);
	DDX_Text(pDX, IDC_EDIT_LSY_KD0, m_LSY_Kd0);
	DDX_Text(pDX, IDC_EDIT_LSY_KD1, m_LSY_Kd1);
	DDX_Text(pDX, IDC_EDIT_LSY_KI0, m_LSY_Ki0);
	DDX_Text(pDX, IDC_EDIT_LSY_KI1, m_LSY_Ki1);
	DDX_Text(pDX, IDC_EDIT_LSY_KP0, m_LSY_Kp0);
	DDX_Text(pDX, IDC_EDIT_LSY_KP1, m_LSY_Kp1);
	DDX_Text(pDX, IDC_EDIT_LW1_KD0, m_LW1_Kd0);
	DDX_Text(pDX, IDC_EDIT_LW1_KD1, m_LW1_Kd1);
	DDX_Text(pDX, IDC_EDIT_LW1_KI0, m_LW1_Ki0);
	DDX_Text(pDX, IDC_EDIT_LW1_KI1, m_LW1_Ki1);
	DDX_Text(pDX, IDC_EDIT_LW1_KP0, m_LW1_Kp0);
	DDX_Text(pDX, IDC_EDIT_LW1_KP1, m_LW1_Kp1);
	DDX_Text(pDX, IDC_EDIT_LW2_KD0, m_LW2_Kd0);
	DDX_Text(pDX, IDC_EDIT_LW2_KD1, m_LW2_Kd1);
	DDX_Text(pDX, IDC_EDIT_LW2_KI0, m_LW2_Ki0);
	DDX_Text(pDX, IDC_EDIT_LW2_KI1, m_LW2_Ki1);
	DDX_Text(pDX, IDC_EDIT_LW2_KP0, m_LW2_Kp0);
	DDX_Text(pDX, IDC_EDIT_LW2_KP1, m_LW2_Kp1);
	DDX_Text(pDX, IDC_EDIT_LWY_KD0, m_LWY_Kd0);
	DDX_Text(pDX, IDC_EDIT_LWY_KD1, m_LWY_Kd1);
	DDX_Text(pDX, IDC_EDIT_LWY_KI0, m_LWY_Ki0);
	DDX_Text(pDX, IDC_EDIT_LWY_KI1, m_LWY_Ki1);
	DDX_Text(pDX, IDC_EDIT_LWY_KP0, m_LWY_Kp0);
	DDX_Text(pDX, IDC_EDIT_LWY_KP1, m_LWY_Kp1);
	DDX_Text(pDX, IDC_EDIT_REB_KD0, m_REB_Kd0);
	DDX_Text(pDX, IDC_EDIT_REB_KD1, m_REB_Kd1);
	DDX_Text(pDX, IDC_EDIT_REB_KI0, m_REB_Ki0);
	DDX_Text(pDX, IDC_EDIT_REB_KI1, m_REB_Ki1);
	DDX_Text(pDX, IDC_EDIT_REB_KP0, m_REB_Kp0);
	DDX_Text(pDX, IDC_EDIT_REB_KP1, m_REB_Kp1);
	DDX_Text(pDX, IDC_EDIT_RSP_KD0, m_RSP_Kd0);
	DDX_Text(pDX, IDC_EDIT_RSP_KD1, m_RSP_Kd1);
	DDX_Text(pDX, IDC_EDIT_RSP_KI0, m_RSP_Ki0);
	DDX_Text(pDX, IDC_EDIT_RSP_KI1, m_RSP_Ki1);
	DDX_Text(pDX, IDC_EDIT_RSP_KP0, m_RSP_Kp0);
	DDX_Text(pDX, IDC_EDIT_RSP_KP1, m_RSP_Kp1);
	DDX_Text(pDX, IDC_EDIT_RSR_KD0, m_RSR_Kd0);
	DDX_Text(pDX, IDC_EDIT_RSR_KD1, m_RSR_Kd1);
	DDX_Text(pDX, IDC_EDIT_RSR_KI0, m_RSR_Ki0);
	DDX_Text(pDX, IDC_EDIT_RSR_KI1, m_RSR_Ki1);
	DDX_Text(pDX, IDC_EDIT_RSR_KP0, m_RSR_Kp0);
	DDX_Text(pDX, IDC_EDIT_RSR_KP1, m_RSR_Kp1);
	DDX_Text(pDX, IDC_EDIT_RSY_KD0, m_RSY_Kd0);
	DDX_Text(pDX, IDC_EDIT_RSY_KD1, m_RSY_Kd1);
	DDX_Text(pDX, IDC_EDIT_RSY_KI0, m_RSY_Ki0);
	DDX_Text(pDX, IDC_EDIT_RSY_KI1, m_RSY_Ki1);
	DDX_Text(pDX, IDC_EDIT_RSY_KP0, m_RSY_Kp0);
	DDX_Text(pDX, IDC_EDIT_RSY_KP1, m_RSY_Kp1);
	DDX_Text(pDX, IDC_EDIT_RW1_KD0, m_RW1_Kd0);
	DDX_Text(pDX, IDC_EDIT_RW1_KD1, m_RW1_Kd1);
	DDX_Text(pDX, IDC_EDIT_RW1_KI0, m_RW1_Ki0);
	DDX_Text(pDX, IDC_EDIT_RW1_KI1, m_RW1_Ki1);
	DDX_Text(pDX, IDC_EDIT_RW1_KP0, m_RW1_Kp0);
	DDX_Text(pDX, IDC_EDIT_RW1_KP1, m_RW1_Kp1);
	DDX_Text(pDX, IDC_EDIT_RW2_KD0, m_RW2_Kd0);
	DDX_Text(pDX, IDC_EDIT_RW2_KD1, m_RW2_Kd1);
	DDX_Text(pDX, IDC_EDIT_RW2_KI0, m_RW2_Ki0);
	DDX_Text(pDX, IDC_EDIT_RW2_KI1, m_RW2_Ki1);
	DDX_Text(pDX, IDC_EDIT_RW2_KP0, m_RW2_Kp0);
	DDX_Text(pDX, IDC_EDIT_RW2_KP1, m_RW2_Kp1);
	DDX_Text(pDX, IDC_EDIT_RWY_KD0, m_RWY_Kd0);
	DDX_Text(pDX, IDC_EDIT_RWY_KD1, m_RWY_Kd1);
	DDX_Text(pDX, IDC_EDIT_RWY_KI0, m_RWY_Ki0);
	DDX_Text(pDX, IDC_EDIT_RWY_KI1, m_RWY_Ki1);
	DDX_Text(pDX, IDC_EDIT_RWY_KP0, m_RWY_Kp0);
	DDX_Text(pDX, IDC_EDIT_RWY_KP1, m_RWY_Kp1);
	DDX_Text(pDX, IDC_EDIT_WST_KD, m_WST_Kd0);
	DDX_Text(pDX, IDC_EDIT_WST_KD1, m_WST_Kd1);
	DDX_Text(pDX, IDC_EDIT_WST_KI, m_WST_Ki0);
	DDX_Text(pDX, IDC_EDIT_WST_KI1, m_WST_Ki1);
	DDX_Text(pDX, IDC_EDIT_WST_KP, m_WST_Kp0);
	DDX_Text(pDX, IDC_EDIT_WST_KP1, m_WST_Kp1);
	DDX_Text(pDX, IDC_EDIT_NK1_KD0, m_NK1_Kd0);
	DDX_Text(pDX, IDC_EDIT_NK1_KI0, m_NK1_Ki0);
	DDX_Text(pDX, IDC_EDIT_NK1_KI1, m_NK1_Ki1);
	DDX_Text(pDX, IDC_EDIT_NK1_KP0, m_NK1_Kp0);
	DDX_Text(pDX, IDC_EDIT_NK1_KP1, m_NK1_Kp1);
	DDX_Text(pDX, IDC_EDIT_NK2_KD0, m_NK2_Kd0);
	DDX_Text(pDX, IDC_EDIT_NK2_KD1, m_NK2_Kd1);
	DDX_Text(pDX, IDC_EDIT_NK2_KI0, m_NK2_Ki0);
	DDX_Text(pDX, IDC_EDIT_NK2_KI1, m_NK2_Ki1);
	DDX_Text(pDX, IDC_EDIT_NK2_KP0, m_NK2_Kp0);
	DDX_Text(pDX, IDC_EDIT_NK2_KP1, m_NK2_Kp1);
	DDX_Text(pDX, IDC_EDIT_NKY_KD0, m_NKY_Kd0);
	DDX_Text(pDX, IDC_EDIT_NK1_KD1, m_NK1_Kd1);
	DDX_Text(pDX, IDC_EDIT_NKY_KD1, m_NKY_Kd1);
	DDX_Text(pDX, IDC_EDIT_NKY_KI0, m_NKY_Ki0);
	DDX_Text(pDX, IDC_EDIT_NKY_KI1, m_NKY_Ki1);
	DDX_Text(pDX, IDC_EDIT_NKY_KP0, m_NKY_Kp0);
	DDX_Text(pDX, IDC_EDIT_NKY_KP1, m_NKY_Kp1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGainSet, CDialog)
	//{{AFX_MSG_MAP(CGainSet)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_LOAD, OnButtonGainLoad)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_SAVE, OnButtonGainSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGainSet message handlers

void CGainSet::Init()
{

}

void CGainSet::GainLoad()
{
	// open file
	ifstream fin("GainSetting.set");
	if (!fin.is_open())
	{
		AfxMessageBox("LoadDataFromFile() :: GainSetting.set 파일을 열 수 없습니다.", MB_OK);
		//return -1;
	}
	
	// read data
	fin >> m_RHY_Kp0 >> m_RHY_Kd0 >> m_RHY_Ki0 >> m_RHY_Kp1 >> m_RHY_Kd1 >> m_RHY_Ki1;
	fin >> m_RHR_Kp0 >> m_RHR_Kd0 >> m_RHR_Ki0 >> m_RHR_Kp1 >> m_RHR_Kd1 >> m_RHR_Ki1;
	fin >> m_RHP_Kp0 >> m_RHP_Kd0 >> m_RHP_Ki0 >> m_RHP_Kp1 >> m_RHP_Kd1 >> m_RHP_Ki1;
	fin >> m_RKN_Kp0 >> m_RKN_Kd0 >> m_RKN_Ki0 >> m_RKN_Kp1 >> m_RKN_Kd1 >> m_RKN_Ki1;
	fin >> m_RAP_Kp0 >> m_RAP_Kd0 >> m_RAP_Ki0 >> m_RAP_Kp1 >> m_RAP_Kd1 >> m_RAP_Ki1;
	fin >> m_RAR_Kp0 >> m_RAR_Kd0 >> m_RAR_Ki0 >> m_RAR_Kp1 >> m_RAR_Kd1 >> m_RAR_Ki1;
	
	fin >> m_LHY_Kp0 >> m_LHY_Kd0 >> m_LHY_Ki0 >> m_LHY_Kp1 >> m_LHY_Kd1 >> m_LHY_Ki1;
	fin >> m_LHR_Kp0 >> m_LHR_Kd0 >> m_LHR_Ki0 >> m_LHR_Kp1 >> m_LHR_Kd1 >> m_LHR_Ki1;
	fin >> m_LHP_Kp0 >> m_LHP_Kd0 >> m_LHP_Ki0 >> m_LHP_Kp1 >> m_LHP_Kd1 >> m_LHP_Ki1;
	fin >> m_LKN_Kp0 >> m_LKN_Kd0 >> m_LKN_Ki0 >> m_LKN_Kp1 >> m_LKN_Kd1 >> m_LKN_Ki1;
	fin >> m_LAP_Kp0 >> m_LAP_Kd0 >> m_LAP_Ki0 >> m_LAP_Kp1 >> m_LAP_Kd1 >> m_LAP_Ki1;
	fin >> m_LAR_Kp0 >> m_LAR_Kd0 >> m_LAR_Ki0 >> m_LAR_Kp1 >> m_LAR_Kd1 >> m_LAR_Ki1;
	
	fin >> m_RSP_Kp0 >> m_RSP_Kd0 >> m_RSP_Ki0 >> m_RSP_Kp1	>> m_RSP_Kd1 >> m_RSP_Ki1;
	fin >> m_RSR_Kp0 >> m_RSR_Kd0 >> m_RSR_Ki0 >> m_RSR_Kp1	>> m_RSR_Kd1 >> m_RSR_Ki1;
	fin >> m_RSY_Kp0 >> m_RSY_Kd0 >> m_RSY_Ki0 >> m_RSY_Kp1	>> m_RSY_Kd1 >> m_RSY_Ki1;
	fin >> m_REB_Kp0 >> m_REB_Kd0 >> m_REB_Ki0 >> m_REB_Kp1	>> m_REB_Kd1 >> m_REB_Ki1;
	fin >> m_RWY_Kp0 >> m_RWY_Kd0 >> m_RWY_Ki0 >> m_RWY_Kp1	>> m_RWY_Kd1 >> m_RWY_Ki1;
	fin >> m_RW1_Kp0 >> m_RW1_Kd0 >> m_RW1_Ki0 >> m_RW1_Kp1	>> m_RW1_Kd1 >> m_RW1_Ki1;
	fin >> m_RW2_Kp0 >> m_RW2_Kd0 >> m_RW2_Ki0 >> m_RW2_Kp1	>> m_RW2_Kd1 >> m_RW2_Ki1;

	fin >> m_LSP_Kp0 >> m_LSP_Kd0 >> m_LSP_Ki0 >> m_LSP_Kp1	>> m_LSP_Kd1 >> m_LSP_Ki1;
	fin >> m_LSR_Kp0 >> m_LSR_Kd0 >> m_LSR_Ki0 >> m_LSR_Kp1	>> m_LSR_Kd1 >> m_LSR_Ki1;
	fin >> m_LSY_Kp0 >> m_LSY_Kd0 >> m_LSY_Ki0 >> m_LSY_Kp1	>> m_LSY_Kd1 >> m_LSY_Ki1;
	fin >> m_LEB_Kp0 >> m_LEB_Kd0 >> m_LEB_Ki0 >> m_LEB_Kp1	>> m_LEB_Kd1 >> m_LEB_Ki1;
	fin >> m_LWY_Kp0 >> m_LWY_Kd0 >> m_LWY_Ki0 >> m_LWY_Kp1	>> m_LWY_Kd1 >> m_LWY_Ki1;
	fin >> m_LW1_Kp0 >> m_LW1_Kd0 >> m_LW1_Ki0 >> m_LW1_Kp1	>> m_LW1_Kd1 >> m_LW1_Ki1;
	fin >> m_LW2_Kp0 >> m_LW2_Kd0 >> m_LW2_Ki0 >> m_LW2_Kp1	>> m_LW2_Kd1 >> m_LW2_Ki1;

	fin >> m_WST_Kp0 >> m_WST_Kd0 >> m_WST_Ki0 >> m_WST_Kp1	>> m_WST_Kd1 >> m_WST_Ki1;

	fin >> m_NKY_Kp0 >> m_NKY_Kd0 >> m_NKY_Ki0 >> m_NKY_Kp1	>> m_NKY_Kd1 >> m_NKY_Ki1;
	fin >> m_NK1_Kp0 >> m_NK1_Kd0 >> m_NK1_Ki0 >> m_NK1_Kp1	>> m_NK1_Kd1 >> m_NK1_Ki1;
	fin >> m_NK2_Kp0 >> m_NK2_Kd0 >> m_NK2_Ki0 >> m_NK2_Kp1	>> m_NK2_Kd1 >> m_NK2_Ki1;
	
	
	// close file
	fin.close();
	
	// print data
	UpdateData(FALSE);
	
	//return 0;
	
	

}

void CGainSet::GainSave()
{
	UpdateData(TRUE);
	
	// open file
	ofstream fout("GainSetting.set");
	if (!fout.is_open())
	{
		AfxMessageBox("SaveDataToFile() :: GainSetting.set 파일을 열 수 없습니다.", MB_OK);
		//return -1;
	}
	
	// save data
	
	fout << m_RHY_Kp0 << " " << m_RHY_Kd0 << " " << m_RHY_Ki0 << " " << m_RHY_Kp1 << " " << m_RHY_Kd1 << " " << m_RHY_Ki1 << endl;
	fout << m_RHR_Kp0 << " " << m_RHR_Kd0 << " " << m_RHR_Ki0 << " " << m_RHR_Kp1 << " " << m_RHR_Kd1 << " " << m_RHR_Ki1 << endl;
	fout << m_RHP_Kp0 << " " << m_RHP_Kd0 << " " << m_RHP_Ki0 << " " << m_RHP_Kp1 << " " << m_RHP_Kd1 << " " << m_RHP_Ki1 << endl;
	fout << m_RKN_Kp0 << " " << m_RKN_Kd0 << " " << m_RKN_Ki0 << " " << m_RKN_Kp1 << " " << m_RKN_Kd1 << " " << m_RKN_Ki1 << endl;
	fout << m_RAP_Kp0 << " " << m_RAP_Kd0 << " " << m_RAP_Ki0 << " " << m_RAP_Kp1 << " " << m_RAP_Kd1 << " " << m_RAP_Ki1 << endl;
	fout << m_RAR_Kp0 << " " << m_RAR_Kd0 << " " << m_RAR_Ki0 << " " << m_RAR_Kp1 << " " << m_RAR_Kd1 << " " << m_RAR_Ki1 << endl;
	
	fout << m_LHY_Kp0 << " " << m_LHY_Kd0 << " " << m_LHY_Ki0 << " " << m_LHY_Kp1 << " " << m_LHY_Kd1 << " " << m_LHY_Ki1 << endl;
	fout << m_LHR_Kp0 << " " << m_LHR_Kd0 << " " << m_LHR_Ki0 << " " << m_LHR_Kp1 << " " << m_LHR_Kd1 << " " << m_LHR_Ki1 << endl;
	fout << m_LHP_Kp0 << " " << m_LHP_Kd0 << " " << m_LHP_Ki0 << " " << m_LHP_Kp1 << " " << m_LHP_Kd1 << " " << m_LHP_Ki1 << endl;
	fout << m_LKN_Kp0 << " " << m_LKN_Kd0 << " " << m_LKN_Ki0 << " " << m_LKN_Kp1 << " " << m_LKN_Kd1 << " " << m_LKN_Ki1 << endl;
	fout << m_LAP_Kp0 << " " << m_LAP_Kd0 << " " << m_LAP_Ki0 << " " << m_LAP_Kp1 << " " << m_LAP_Kd1 << " " << m_LAP_Ki1 << endl;
	fout << m_LAR_Kp0 << " " << m_LAR_Kd0 << " " << m_LAR_Ki0 << " " << m_LAR_Kp1 << " " << m_LAR_Kd1 << " " << m_LAR_Ki1 << endl;
	
	fout << m_RSP_Kp0 << " " << m_RSP_Kd0 << " " << m_RSP_Ki0 << " " << m_RSP_Kp1 << " " << m_RSP_Kd1 << " " << m_RSP_Ki1 << endl;
	fout << m_RSR_Kp0 << " " << m_RSR_Kd0 << " " << m_RSR_Ki0 << " " << m_RSR_Kp1 << " " << m_RSR_Kd1 << " " << m_RSR_Ki1 << endl;
	fout << m_RSY_Kp0 << " " << m_RSY_Kd0 << " " << m_RSY_Ki0 << " " << m_RSY_Kp1 << " " << m_RSY_Kd1 << " " << m_RSY_Ki1 << endl;
	fout << m_REB_Kp0 << " " << m_REB_Kd0 << " " << m_REB_Ki0 << " " << m_REB_Kp1 << " " << m_REB_Kd1 << " " << m_REB_Ki1 << endl;
	fout << m_RWY_Kp0 << " " << m_RWY_Kd0 << " " << m_RWY_Ki0 << " " << m_RWY_Kp1 << " " << m_RWY_Kd1 << " " << m_RWY_Ki1 << endl;
	fout << m_RW1_Kp0 << " " << m_RW1_Kd0 << " " << m_RW1_Ki0 << " " << m_RW1_Kp1 << " " << m_RW1_Kd1 << " " << m_RW1_Ki1 << endl;
	fout << m_RW2_Kp0 << " " << m_RW2_Kd0 << " " << m_RW2_Ki0 << " " << m_RW2_Kp1 << " " << m_RW2_Kd1 << " " << m_RW2_Ki1 << endl;

	fout << m_LSP_Kp0 << " " << m_LSP_Kd0 << " " << m_LSP_Ki0 << " " << m_LSP_Kp1 << " " << m_LSP_Kd1 << " " << m_LSP_Ki1 << endl;
	fout << m_LSR_Kp0 << " " << m_LSR_Kd0 << " " << m_LSR_Ki0 << " " << m_LSR_Kp1 << " " << m_LSR_Kd1 << " " << m_LSR_Ki1 << endl;
	fout << m_LSY_Kp0 << " " << m_LSY_Kd0 << " " << m_LSY_Ki0 << " " << m_LSY_Kp1 << " " << m_LSY_Kd1 << " " << m_LSY_Ki1 << endl;
	fout << m_LEB_Kp0 << " " << m_LEB_Kd0 << " " << m_LEB_Ki0 << " " << m_LEB_Kp1 << " " << m_LEB_Kd1 << " " << m_LEB_Ki1 << endl;
	fout << m_LWY_Kp0 << " " << m_LWY_Kd0 << " " << m_LWY_Ki0 << " " << m_LWY_Kp1 << " " << m_LWY_Kd1 << " " << m_LWY_Ki1 << endl;
	fout << m_LW1_Kp0 << " " << m_LW1_Kd0 << " " << m_LW1_Ki0 << " " << m_LW1_Kp1 << " " << m_LW1_Kd1 << " " << m_LW1_Ki1 << endl;
	fout << m_LW2_Kp0 << " " << m_LW2_Kd0 << " " << m_LW2_Ki0 << " " << m_LW2_Kp1 << " " << m_LW2_Kd1 << " " << m_LW2_Ki1 << endl;

	fout << m_WST_Kp0 << " " << m_WST_Kd0 << " " << m_WST_Ki0 << " " << m_WST_Kp1 << " " << m_WST_Kd1 << " " << m_WST_Ki1 << endl;

	fout << m_NKY_Kp0 << " " << m_NKY_Kd0 << " " << m_NKY_Ki0 << " " << m_NKY_Kp1 << " " << m_NKY_Kd1 << " " << m_NKY_Ki1 << endl;
	fout << m_NK1_Kp0 << " " << m_NK1_Kd0 << " " << m_NK1_Ki0 << " " << m_NK1_Kp1 << " " << m_NK1_Kd1 << " " << m_NK1_Ki1 << endl;
	fout << m_NK2_Kp0 << " " << m_NK2_Kd0 << " " << m_NK2_Ki0 << " " << m_NK2_Kp1 << " " << m_NK2_Kd1 << " " << m_NK2_Ki1 << endl;


	// close file
	fout.close();
	
	//return 0;
	
	
}

void CGainSet::OnButtonGainLoad() 
{
	// TODO: Add your control notification handler code here
	GainLoad();
}

void CGainSet::OnButtonGainSave() 
{
	// TODO: Add your control notification handler code here
	GainSave();	
}
