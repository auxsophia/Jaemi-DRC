// ProfileGraph.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "ProfileGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileGraph dialog
extern CKhr3winApp theApp;

CProfileGraph::CProfileGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileGraph::IDD, pParent), m_Board_FootX(this, 4), m_Board_FootY(this, 4), m_Board_FootZ(this, 4)
{
	//{{AFX_DATA_INIT(CProfileGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProfileGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileGraph)
	DDX_Control(pDX, IDC_BUTTON_HOLD, m_Button_Hold);
	DDX_Control(pDX, IDC_STATIC_Z_POS_BOARD, m_Board_FootZ);
	DDX_Control(pDX, IDC_STATIC_Y_POS_BOARD, m_Board_FootY);
	DDX_Control(pDX, IDC_STATIC_X_POS_BOARD, m_Board_FootX);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProfileGraph, CDialog)
	//{{AFX_MSG_MAP(CProfileGraph)
	ON_BN_CLICKED(IDC_BUTTON_HOLD, OnButtonHold)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileGraph message handlers

void CProfileGraph::Init()
{
	InitBoard();
	UpdateData(FALSE);
	SetTimer(1, DISP_TIMER, NULL);
}

void CProfileGraph::OnButtonHold() 
{
	// TODO: Add your control notification handler code here
	CString	strText;
	m_Button_Hold.GetWindowText(strText);
	
	if(strText == "Hold")
	{
		m_Board_FootX.KillTimer(1);
		m_Board_FootY.KillTimer(1);
		m_Board_FootZ.KillTimer(1);
		KillTimer(1);
		m_Button_Hold.SetWindowText("Start");
	}
	else if(strText == "Start")
	{
		SetTimer(1, DISP_TIMER, NULL);
		m_Button_Hold.SetWindowText("Hold");
	}
}

void CProfileGraph::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default	
	CDialog::OnTimer(nIDEvent);
	if(nIDEvent==1)
	{
		DispXYZ();
	}
}

void CProfileGraph::InitBoard()
{
	m_Board_FootX.SetBoardDC(m_Board_FootX.GetDC());
	m_Board_FootX.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_FootX.SetXRange(10, 0);
	m_Board_FootX.SetYRange(100, -100);
	m_Board_FootX.SetXYGap(1, 50);
	m_Board_FootX.SetGraphName(2,"R-X","L-X");
	
	m_Board_FootY.SetBoardDC(m_Board_FootY.GetDC());
	m_Board_FootY.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_Board_FootY.SetXRange(10, 0);
	m_Board_FootY.SetYRange(180, -180);
	m_Board_FootY.SetXYGap(1, 100);
	m_Board_FootY.SetGraphName(2,"R-Y","L-Y");
		
	m_Board_FootZ.SetBoardDC(m_Board_FootZ.GetDC());
	m_Board_FootZ.InitBoard(CENTERPOINT_LEFTTOP);
	m_Board_FootZ.SetXRange(10, 0);
	m_Board_FootZ.SetYRange(-400, -600);
	m_Board_FootZ.SetXYGap(1, 100);
	m_Board_FootZ.SetGraphName(2,"R-Z","L-Z");
}

void CProfileGraph::DispXYZ()
{
	m_Board_RFootX=theApp.m_pSharedMemory->fProfXYZ[3];
	m_Board_LFootX=theApp.m_pSharedMemory->fProfXYZ[0];
	
	m_Board_RFootY=theApp.m_pSharedMemory->fProfXYZ[4];
	m_Board_LFootY=theApp.m_pSharedMemory->fProfXYZ[1];
	
	m_Board_RFootZ=theApp.m_pSharedMemory->fProfXYZ[5];
	m_Board_LFootZ=theApp.m_pSharedMemory->fProfXYZ[2];

	
	m_Board_FootX.StartGraph(DISP_TIMER);
	m_Board_FootY.StartGraph(DISP_TIMER);
	m_Board_FootZ.StartGraph(DISP_TIMER);
}

void CProfileGraph::UpdateBoardPoint()
{
	UpdateData();
	
	m_Board_FootX.SetCoordinatePoint(0, (int)m_Board_RFootX);
	m_Board_FootX.SetCoordinatePoint(1, (int)m_Board_LFootX);
	
	m_Board_FootY.SetCoordinatePoint(0, (int)m_Board_RFootY);
	m_Board_FootY.SetCoordinatePoint(1, (int)m_Board_LFootY);
	
	m_Board_FootZ.SetCoordinatePoint(0, (int)m_Board_RFootZ);
	m_Board_FootZ.SetCoordinatePoint(1, (int)m_Board_LFootZ);
}
