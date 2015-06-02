// FT_ReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "FT_ReadDlg.h"
#include "Khr3winDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFT_ReadDlg dialog
extern CKhr3winApp theApp;

CFT_ReadDlg::CFT_ReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFT_ReadDlg::IDD, pParent), m_RFootFTBoard(this, 1), m_LFootFTBoard(this, 1), m_ZMPFTBoard(this, 1)
{
	//{{AFX_DATA_INIT(CFT_ReadDlg)
	//}}AFX_DATA_INIT
	m_pKhr3winDlg = NULL;
}


void CFT_ReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFT_ReadDlg)
	DDX_Control(pDX, IDC_BUTTON_FT_NULL, m_ButtonFTNULL);
	DDX_Control(pDX, IDC_STATIC_ZMP_FT_BOARD, m_ZMPFTBoard);
	DDX_Control(pDX, IDC_STATIC_LFOOT_FT_BOARD, m_LFootFTBoard);
	DDX_Control(pDX, IDC_STATIC_RFOOT_FT_BOARD, m_RFootFTBoard);
	DDX_Control(pDX, IDC_BUTTON_GRAPH, m_ButtonGraph);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_ButtonClose);
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_MX, m_RFOOT_Mx); 
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_MY, m_RFOOT_My);
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_FZ, m_RFOOT_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_MX1, m_NM_RFOOT_Mx); 
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_MY1, m_NM_RFOOT_My);
	DDX_Text(pDX, IDC_EDIT_FT_RFOOT_FZ1, m_N_RFOOT_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_MX, m_LFOOT_Mx);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_MY, m_LFOOT_My);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_FZ, m_LFOOT_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_MX1, m_NM_LFOOT_Mx);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_MY1, m_NM_LFOOT_My);
	DDX_Text(pDX, IDC_EDIT_FT_LFOOT_FZ1, m_N_LFOOT_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_RWRIST_MX, m_RWRIST_Mx);
	DDX_Text(pDX, IDC_EDIT_FT_RWRIST_MY, m_RWRIST_My);
	DDX_Text(pDX, IDC_EDIT_FT_RWRIST_FZ, m_RWRIST_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_LWRIST_MX, m_LWRIST_Mx);
	DDX_Text(pDX, IDC_EDIT_FT_LWRIST_MY, m_LWRIST_My);
	DDX_Text(pDX, IDC_EDIT_FT_LWRIST_FZ, m_LWRIST_Fz);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_RX, m_RXzmp);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_RY, m_RYzmp);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_LX, m_LXzmp);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_LY, m_LYzmp);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_X, m_Xzmp);
	DDX_Text(pDX, IDC_EDIT_FT_ZMP_Y, m_Yzmp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFT_ReadDlg, CDialog)
	//{{AFX_MSG_MAP(CFT_ReadDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, OnButtonGraph)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_FT_NULL, OnButtonFtNull)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFT_ReadDlg message handlers

BOOL CFT_ReadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CFT_ReadDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}
void CFT_ReadDlg::Close()
{
	m_pKhr3winDlg->ButtonControl(FT_CLOSE);
	theApp.m_pSharedMemory->Read_FTS_Flag = DISABLE;
	KillTimer(1);
	UpdateData(FALSE);
	DestroyWindow();
}

void CFT_ReadDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CFT_ReadDlg::Close();
}

void CFT_ReadDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	DispFT();
	CDialog::OnTimer(nIDEvent);
}

void CFT_ReadDlg::FTVarINIT()
{
	m_RWRIST_Fz			=		0;
	m_RWRIST_Mx			=		0;
	m_RWRIST_My			=		0;
	m_LFOOT_Fz			=		0;
	m_LFOOT_Mx			=		0;
	m_LFOOT_My			=		0;
	m_LWRIST_Fz			=		0;
	m_LWRIST_Mx			=		0;
	m_LWRIST_My			=		0;
	m_RFOOT_Fz			=		0;
	m_RFOOT_Mx			=		0;
	m_RFOOT_My			=		0;

	m_Xzmp				=		0.0f;
	m_Yzmp				=		0.0f;

	m_RXzmp				=		0.0f;
	m_RYzmp				=		0.0f;
	
	m_LXzmp				=		0.0f;
	m_LYzmp				=		0.0f;

	m_NM_RFOOT_Mx		=		0.0f;
	m_NM_RFOOT_My		=		0.0f;
	m_N_RFOOT_Fz		=		0.0f;
    m_NM_LFOOT_Mx		=		0.0f;
	m_NM_LFOOT_My		=		0.0f;
	m_N_LFOOT_Fz		=		0.0f;
	m_NM_RWRIST_Mx		=		0.0f;
	m_NM_RWRIST_My		=		0.0f;
	m_N_RWRIST_Fz		=		0.0f;
    m_NM_LWRIST_Mx		=		0.0f;
	m_NM_LWRIST_My		=		0.0f;
	m_N_LWRIST_Fz		=		0.0f;
}

void CFT_ReadDlg::DispFT()
{
	m_RWRIST_Fz = theApp.m_pSharedMemory->RWRIST_Fz;
	m_RWRIST_Mx = theApp.m_pSharedMemory->RWRIST_Mx;
	m_RWRIST_My = theApp.m_pSharedMemory->RWRIST_My;
	m_LFOOT_Fz	= theApp.m_pSharedMemory->LFOOT_Fz;
	m_LFOOT_Mx	= theApp.m_pSharedMemory->LFOOT_Mx;
	m_LFOOT_My	= theApp.m_pSharedMemory->LFOOT_My;
	m_LWRIST_Fz = theApp.m_pSharedMemory->LWRIST_Fz;
	m_LWRIST_Mx = theApp.m_pSharedMemory->LWRIST_Mx;
	m_LWRIST_My = theApp.m_pSharedMemory->LWRIST_My;
	m_RFOOT_Fz	= theApp.m_pSharedMemory->RFOOT_Fz;
	m_RFOOT_Mx  = theApp.m_pSharedMemory->RFOOT_Mx;	
	m_RFOOT_My	= theApp.m_pSharedMemory->RFOOT_My;

	m_NM_RFOOT_Mx	= ChangeValue(theApp.m_pSharedMemory->NM_RFOOT_Mx);
	m_NM_RFOOT_My	= ChangeValue(theApp.m_pSharedMemory->NM_RFOOT_My);
	m_N_RFOOT_Fz	= ChangeValue(theApp.m_pSharedMemory->N_RFOOT_Fz);
    m_NM_LFOOT_Mx	= ChangeValue(theApp.m_pSharedMemory->NM_LFOOT_Mx);
	m_NM_LFOOT_My	= ChangeValue(theApp.m_pSharedMemory->NM_LFOOT_My);
	m_N_LFOOT_Fz	= ChangeValue(theApp.m_pSharedMemory->N_LFOOT_Fz);

	m_NM_RWRIST_Mx	= ChangeValue(theApp.m_pSharedMemory->NM_RWRIST_Mx);
	m_NM_RWRIST_My	= ChangeValue(theApp.m_pSharedMemory->NM_RWRIST_My);
	m_N_RWRIST_Fz	= ChangeValue(theApp.m_pSharedMemory->N_RWRIST_Fz);
    m_NM_LWRIST_Mx	= ChangeValue(theApp.m_pSharedMemory->NM_LWRIST_Mx);
	m_NM_LWRIST_My	= ChangeValue(theApp.m_pSharedMemory->NM_LWRIST_My);
	m_N_LWRIST_Fz	= ChangeValue(theApp.m_pSharedMemory->N_LWRIST_Fz);

	m_Xzmp		= theApp.m_pSharedMemory->Xzmp;
	m_Yzmp		= theApp.m_pSharedMemory->Yzmp;

	m_RXzmp		= theApp.m_pSharedMemory->RXzmp;
	m_RYzmp		= theApp.m_pSharedMemory->RYzmp;
	
	m_LXzmp		= theApp.m_pSharedMemory->LXzmp;
	m_LYzmp		= theApp.m_pSharedMemory->LYzmp;

	UpdateData(FALSE);
}

void CFT_ReadDlg::OnButtonGraph() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_ButtonGraph.GetWindowText(strText);
	
	if(strText == "Graph Start")
	{
		m_RFootFTBoard.StartGraph(DISP_TIMER);
		m_LFootFTBoard.StartGraph(DISP_TIMER);
		m_ZMPFTBoard.StartGraph(DISP_TIMER);

		SetTimer(1, DISP_TIMER, NULL);
		ButtonControl(FTDLG_FT_GRAPH_ON);
	}
	else if(strText == "Graph Hold")
	{
		KillTimer(1);

		m_RFootFTBoard.KillTimer(1);
		m_LFootFTBoard.KillTimer(1);
		m_ZMPFTBoard.KillTimer(1);
		
		ButtonControl(FTDLG_FT_GRAPH_HOLD);
	}
}

void CFT_ReadDlg::ButtonControl(int Msg)
{
	switch(Msg)
	{
	/////////////////////////////////////////////////////////////////////
	// Graph Button
	case FTDLG_FT_GRAPH_HOLD:
		m_ButtonGraph.SetWindowText("Graph Start");
		break;
		
	case FTDLG_FT_GRAPH_ON:
		m_ButtonGraph.SetWindowText("Graph Hold");
		break;
	}	
}


void CFT_ReadDlg::Null_CMD(unsigned char Module_ID, unsigned char Mode)
{
	BYTE	TxData[3]={0, 0, 0};
	
	TxData[0] =	Module_ID;
	TxData[1] = NullCMD;    
	TxData[2] = Mode;
	if((Module_ID == FT1) || (Module_ID == FT2))
	{
		//((CCANwin*)AfxGetApp())->CAN_WRITE(CMD_TXDF_FTS, TxData, 8);
		((CCANwin*)AfxGetApp())->CAN_WRITE(CMD_TXDF, TxData, 3);
	}
	else if((Module_ID == FT3) || (Module_ID == FT4))
	{
		((CCANwin*)AfxGetApp())->CAN_WRITE1(CMD_TXDF, TxData, 3);
	}
	Sleep(50);

}

void CFT_ReadDlg::OnButtonFtNull() 
{
	// TODO: Add your control notification handler code here
	m_ButtonFTNULL.EnableWindow(FALSE);
	theApp.m_pSharedMemory->INT_Flag = FALSE;

	Null_CMD(FT1,0);  // Null ALL CHANNELS OF 
	//Sleep(100);       // 중요 !!!
	Sleep(500);
	Null_CMD(FT2,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(500);
	
	Null_CMD(FT3,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(300);
	Null_CMD(FT4,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(300);
	

	theApp.m_pSharedMemory->INT_Flag = TRUE;
	theApp.m_pSharedMemory->Read_FTS_Flag = ENABLE;
	m_ButtonFTNULL.EnableWindow();
}



void CFT_ReadDlg::InitBoard()
{
	m_RFootFTBoard.SetBoardDC(m_RFootFTBoard.GetDC());
	m_RFootFTBoard.InitBoard(CENTERPOINT_LEFTMIDDLE);	
	m_RFootFTBoard.SetXRange(10, 0);
	m_RFootFTBoard.SetYRange(30, -30);
	m_RFootFTBoard.SetXYGap(1, 10);
	m_RFootFTBoard.SetGraphName(3, "Mx", "My", "Fz");

	m_LFootFTBoard.SetBoardDC(m_LFootFTBoard.GetDC());
	m_LFootFTBoard.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_LFootFTBoard.SetXRange(10, 0);
	m_LFootFTBoard.SetYRange(30, -30);
	m_LFootFTBoard.SetXYGap(1, 10);
	m_LFootFTBoard.SetGraphName(3, "Mx", "My", "Fz");

	m_ZMPFTBoard.SetBoardDC(m_ZMPFTBoard.GetDC());
	m_ZMPFTBoard.InitBoard(CENTERPOINT_LEFTMIDDLE);
	m_ZMPFTBoard.SetXRange(10, 0);
	m_ZMPFTBoard.SetYRange(500, -500);
	m_ZMPFTBoard.SetXYGap(1, 200);
	m_ZMPFTBoard.SetGraphName(2, "Xzmp", "Yzmp");
}

void CFT_ReadDlg::UpdateBoardPoint()
{
	
	UpdateData();

	m_RFootFTBoard.SetCoordinatePoint(0, (int)m_NM_RFOOT_Mx);
	m_RFootFTBoard.SetCoordinatePoint(1, (int)m_NM_RFOOT_My);
	m_RFootFTBoard.SetCoordinatePoint(2, (int)m_N_RFOOT_Fz);

	m_LFootFTBoard.SetCoordinatePoint(0, (int)m_NM_LFOOT_Mx);
	m_LFootFTBoard.SetCoordinatePoint(1, (int)m_NM_LFOOT_My);
	m_LFootFTBoard.SetCoordinatePoint(2, (int)m_N_LFOOT_Fz);
	
	m_ZMPFTBoard.SetCoordinatePoint(0, (int)m_Xzmp);
	m_ZMPFTBoard.SetCoordinatePoint(1, (int)m_Yzmp);
}

float CFT_ReadDlg::ChangeValue(float nValue)
{
	return (float)((int)(nValue * 100)/100.0);
}

void CFT_ReadDlg::Init()
{
	theApp.m_pSharedMemory->Read_FTS_Flag = ENABLE;
	FTVarINIT();
	m_nTime = 0;
	InitBoard();
	UpdateData(FALSE);
}

void CFT_ReadDlg::OnButtonHide() 
{
	// TODO: Add your control notification handler code here
	m_pKhr3winDlg->m_ButtonFTRead.SetWindowText("FT SHOW");
	ShowWindow(SW_HIDE);
}

void CFT_ReadDlg::FT_Null()
{
	// TODO: Add your control notification handler code here
	m_ButtonFTNULL.EnableWindow(FALSE);
	theApp.m_pSharedMemory->INT_Flag = FALSE;
	
	Null_CMD(FT1,0);  // Null ALL CHANNELS OF 
	//Sleep(100);       // 중요 !!!
	Sleep(200);       // 중요 !!!
	Null_CMD(FT2,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(200);
	//Null_CMD(RWT,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(200);
	//Null_CMD(LWT,0);  // Null ALL CHANNELS
	//Sleep(100);
	Sleep(200);
	
	theApp.m_pSharedMemory->INT_Flag = TRUE;
	m_ButtonFTNULL.EnableWindow();
}
