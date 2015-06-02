// Board.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "Board.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoard

CBoard::CBoard(CWnd* pWnd,int Num)
{
	m_pWnd = pWnd;
	m_Num = Num;
	InitBoard(CENTERPOINT_LEFTMIDDLE);
}

CBoard::~CBoard()
{
}


BEGIN_MESSAGE_MAP(CBoard, CStatic)
	//{{AFX_MSG_MAP(CBoard)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoard message handlers

void CBoard::InitBoard(int nMsg)
{
	ASSERT(m_pWnd);

	m_bStartGraph = FALSE;

	m_nXMax = m_nYMax = 0;
	m_nXMin = m_nYMin = 0;
	m_nXGap = m_nYGap = 0;

	m_nTimeGap = 100;
	m_nColorNum = 0;
	m_nMaxIdx = 0;
	m_nTimeValue = 10;
	
	m_CenterPoint = CPoint(0, 0);
	m_GraphColor = RGB(255, 0, 0);
	m_BoardColor = RGB(255, 255, 255);

	GetClientRect(&m_BoardRect);

	m_BoardRect.left += 50;
	m_BoardRect.right -= 15;
	m_BoardRect.top += 15;
	m_BoardRect.bottom -= 40;
	
	SetCenterPoint(nMsg);

	for(int i = 0; i < 6; i++)
	{
		m_CoordinatePoint[i] = CPoint(0,0);
		m_OldPoint[i] = m_CenterPoint;
		m_strGraphName[i]       = "";
	}
}

void CBoard::SelectColor(int nColor)
{
	switch(nColor)
	{
	case 0:
		m_GraphColor = RGB(255, 0, 0);
		break;
	case 1:
		m_GraphColor = RGB(0, 255, 0);
		break;
	case 2:
		m_GraphColor = RGB(0, 0, 255);
		break;
	case 3:
		m_GraphColor = RGB(255, 255, 0);
		break;
	case 4:
		m_GraphColor = RGB(255, 0, 255);
		break;
	case 5:
		m_GraphColor = RGB(0, 255, 255);
		break;
	}
}

BOOL CBoard::SetGraphName(int nMaxIdx, CString GraphName0, CString GraphName1, CString GraphName2, CString GraphName3, CString GraphName4, CString GraphName5)
{
	if(m_nMaxIdx >6 || m_nMaxIdx < 0)
	{
		MessageBox("nIdx is over Value ( nIdx max = 5; min = 0)");
		return FALSE;
	}
	m_nMaxIdx = nMaxIdx;

	m_strGraphName[0] = GraphName0;
	m_strGraphName[1] = GraphName1;
	m_strGraphName[2] = GraphName2;
	m_strGraphName[3] = GraphName3;
	m_strGraphName[4] = GraphName4;
	m_strGraphName[5] = GraphName5;

	return TRUE;
}

void CBoard::SetCenterPoint(int nMsg)
{

	CPoint middlePoint;

		middlePoint.x = (m_BoardRect.left + m_BoardRect.right) / 2;
		middlePoint.y = (m_BoardRect.top + m_BoardRect.bottom) / 2;

		switch(nMsg)
		{
		case CENTERPOINT_LEFTDOWN:
			m_CenterPoint = CPoint(m_BoardRect.left, m_BoardRect.bottom);
			break;
		case CENTERPOINT_LEFTMIDDLE:
			m_CenterPoint = CPoint(m_BoardRect.left, middlePoint.y);
			break;
		case CENTERPOINT_LEFTTOP:
			m_CenterPoint = CPoint(m_BoardRect.left, m_BoardRect.top);
			break;
		case CENTERPOINT_MIDDLE:
			m_CenterPoint = middlePoint;
			break;
		}

		m_nCenterType = nMsg;
}

void CBoard::DrawBoard()
{
	CBrush br(m_BoardColor);
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	CRect rect;

		GetClientRect(&rect);
		m_pDC->SelectObject(&br);
		m_pDC->SelectObject(&pen);
		m_pDC->Rectangle(&rect);
	
	DrawXYLine();
	DrawGapLine();
	DrawLineText();
}

void CBoard::DrawGraph()
{
	for(int i = 0; i < m_nMaxIdx; i++)
	{
		SelectColor(i);
		
		CPen pen(PS_SOLID, 3, m_GraphColor);

		m_pDC->SelectObject(&pen);

		m_CoordinatePoint[i].x = (int)((m_BoardRect.right - m_BoardRect.left) / (m_nXMax - m_nXMin) / 1000 * m_nTimeValue + m_CenterPoint.x);
		
		if(m_nCenterType == CENTERPOINT_LEFTTOP)
			m_CoordinatePoint[i].y = (int)( m_CenterPoint.y  - ((m_BoardRect.bottom - m_BoardRect.top) / (m_nYMax - m_nYMin) * (m_CoordinatePoint[i].y - m_nYMax)));
		else
			m_CoordinatePoint[i].y = (int)(m_CenterPoint.y  - ((m_BoardRect.bottom - m_BoardRect.top) / (m_nYMax - m_nYMin) * m_CoordinatePoint[i].y));
	
		if(m_CoordinatePoint[i].x >= m_BoardRect.right)
		{
			DrawBoard();
			m_nTimeValue = (int)m_nTimeGap;
			
			for(int j = 0; j < m_nMaxIdx; j++)
			{
				m_OldPoint[j].x = m_BoardRect.left;
				m_CoordinatePoint[j].x = m_BoardRect.left;
			}
			i = m_nMaxIdx;
		}
		else
		{
			m_pDC->MoveTo(m_OldPoint[i].x, m_OldPoint[i].y);
			m_pDC->LineTo(m_CoordinatePoint[i].x, m_CoordinatePoint[i].y);
	
			m_OldPoint[i] = m_CoordinatePoint[i];
		}
	}
	
}

void CBoard::DrawXYLine()
{
	CPen pen(PS_SOLID, 3, RGB(0,0,0));

		m_pDC->SelectObject(&pen);
		// X_LINE
		m_pDC->MoveTo(m_CenterPoint.x, m_BoardRect.top);
		m_pDC->LineTo(m_CenterPoint.x, m_BoardRect.bottom);

		//Y_LINE
		m_pDC->MoveTo(m_BoardRect.left, m_CenterPoint.y);
		m_pDC->LineTo(m_BoardRect.right, m_CenterPoint.y);	
}

void CBoard::DrawGapLine()
{
	CPen pen(PS_DOT, 1, RGB(5,5,5));
	float XPoint = (float)m_CenterPoint.x;
	float YPoint = (float)m_CenterPoint.y;
	int i;
	CPoint point;
	CString strText;

		m_nBoardYGap = ((m_BoardRect.bottom - m_BoardRect.top) / (m_nYMax - m_nYMin)) * m_nYGap;
		m_nBoardXGap = ((m_BoardRect.right - m_BoardRect.left) / (m_nXMax - m_nXMin)) * m_nXGap;
		
		m_nXCount = (int)((m_nYMax - m_nYMin) / m_nYGap);
		m_nYCount = (int)((m_nXMax - m_nXMin) / m_nXGap);
		
		m_pDC->SelectObject(&pen);

		switch(m_nCenterType)
		{
		case CENTERPOINT_LEFTMIDDLE:
			//////////////////////////////////////////////////////////////////////////
			// X_LINE 
			DrawXGapLine();

			for(i = 0; i < m_nYCount ; i++)
			{
				//Y_LINE
				XPoint += m_nBoardXGap;
				m_pDC->MoveTo((int)XPoint, m_BoardRect.top);
				m_pDC->LineTo((int)XPoint, m_BoardRect.bottom + 10);
				
				point = CPoint((int)XPoint , m_BoardRect.bottom + 25);
				strText.Format("%d", (int)m_nXGap * (i + 1));
				DrawGapNum(point, strText);
			}
			break;
		case CENTERPOINT_MIDDLE:
			DrawXGapLine();
			DrawYGapLine();
			break;
		case CENTERPOINT_LEFTDOWN:
			for(i = 0; i < m_nXCount; i++)
			{
				// X_LINE 
				YPoint -= m_nBoardYGap;
				m_pDC->MoveTo(m_BoardRect.left - 10, (int)YPoint);
				m_pDC->LineTo(m_BoardRect.right, (int)YPoint);
				
				point = CPoint(m_BoardRect.left - 30 ,(int)YPoint);
				strText.Format("%5.f", m_nYGap * (i + 1));
				DrawGapNum(point, strText);
			}
			
			for(i = 0; i < m_nYCount; i++)
			{
				//Y_LINE
				XPoint += m_nBoardXGap;
				
				m_pDC->MoveTo((int)XPoint, m_BoardRect.top);
				m_pDC->LineTo((int)XPoint, m_BoardRect.bottom + 10);
				
				point = CPoint((int)XPoint, m_BoardRect.bottom + 25);
				strText.Format("%d", (int)m_nXGap * (i + 1));
				DrawGapNum(point, strText);
			}			
			break;
		case CENTERPOINT_LEFTTOP:
			for(i = 0; i < m_nXCount; i++)
			{
				YPoint += m_nBoardYGap;
				// X_LINE +
				m_pDC->MoveTo(m_BoardRect.left - 10, (int)YPoint);
				m_pDC->LineTo(m_BoardRect.right, (int)YPoint);
				
				point = CPoint(m_BoardRect.left - 30 ,(int)YPoint);
				strText.Format("%5.f",  m_nYMax -1 * m_nYGap * (i + 1));
				DrawGapNum(point, strText);
			}
			
			for(i = 0; i < m_nYCount ; i++)
			{
				//Y_LINE
				XPoint += m_nBoardXGap;
				m_pDC->MoveTo((int)XPoint, m_BoardRect.top);
				m_pDC->LineTo((int)XPoint, m_BoardRect.bottom + 10);
				
				point = CPoint((int)XPoint , m_BoardRect.bottom + 25);
				strText.Format("%d", (int)m_nXGap * (i + 1));
				DrawGapNum(point, strText);
			}
			break;
		}		
}
void CBoard::DrawGapNum(CPoint TextPoint, CString strText)
{
	CRect rect;
	
	rect.SetRect(TextPoint.x - 20 , TextPoint.y - 10, TextPoint.x + 20, TextPoint.y + 10);
	DrawText(m_pDC->m_hDC, strText, strText.GetLength(), &rect, DT_SINGLELINE | DT_CENTER);
}

#include "FT_ReadDlg.h"
#include "TiltReadDlg.h"
#include "Walk00TestDlg.h"
#include "ProfileGraph.h"

void CBoard::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_Num)
	{
		case 1:
			((CFT_ReadDlg*)m_pWnd)->UpdateBoardPoint();
			break;
		case 2:
			((CTiltReadDlg*)m_pWnd)->UpdateBoardPoint();
			break;
		case 3:
			((CWalk00TestDlg*)m_pWnd)->UpdateBoardPoint();
			break;
		case 4:
			((CProfileGraph*)m_pWnd)->UpdateBoardPoint();
			break;
	}


	m_nTimeValue += m_nTimeGap; 
	DrawGraph();

	CStatic::OnTimer(nIDEvent);
}

void CBoard::StartGraph(UINT nTimeGap)
{
	if(!m_bStartGraph)
	{	
		DrawBoard();
		m_bStartGraph = TRUE;
	}
	m_nTimeGap = nTimeGap;
//	MessageBox("1");
	SetTimer(1, nTimeGap, NULL);
}

void CBoard::DrawLineText()
{
	CPoint point;
	for(int i = 0; i < m_nMaxIdx; i++)
	{
		SelectColor(i);

		CPen pen(PS_SOLID, 2, m_GraphColor);
		
			m_pDC->SelectObject(&pen);

			point.x = m_BoardRect.right - 20;
			point.y = m_BoardRect.top + 10 + 15 * i;

			m_pDC->MoveTo(point.x - 60, point.y);
			m_pDC->LineTo(point.x - 30, point.y);	
		
		DrawGapNum( point, m_strGraphName[i]);
	}
}

void CBoard::SetCoordinatePoint(int nIdx, int nValue)
{
 	m_CoordinatePoint[nIdx].y = nValue;
}

void CBoard::DrawXGapLine()
{
	CPen pen(PS_DOT, 1, RGB(5,5,5));
	float XPoint = (float)m_CenterPoint.x;
	float YPoint = (float)m_CenterPoint.y;
	int i;
	CPoint point;
	CString strText;

	m_pDC->SelectObject(&pen);
	
	for(i = 0; i < m_nXCount / 2; i++)
	{
		// X_LINE +				
		YPoint += m_nBoardYGap;
		m_pDC->MoveTo(m_BoardRect.left - 10, (int)YPoint);
		m_pDC->LineTo(m_BoardRect.right, (int)YPoint);
		
		point = CPoint(m_BoardRect.left -30 , (int)YPoint);
		strText.Format("%5.f", -1 * m_nYGap * (i + 1));
		DrawGapNum(point, strText);
	}
	YPoint = (float)m_CenterPoint.y;
	
	for(i = 0; i < m_nXCount / 2; i++)
	{
		// X_LINE -
		YPoint -= m_nBoardYGap;
		m_pDC->MoveTo(m_BoardRect.left - 10, (int)YPoint);
		m_pDC->LineTo(m_BoardRect.right, (int)YPoint);
		
		point = CPoint(m_BoardRect.left - 30 , (int)YPoint);
		strText.Format("%5.f",  m_nYGap * (i + 1));
		DrawGapNum(point, strText);
	}
}

void CBoard::DrawYGapLine()
{
	CPen pen(PS_DOT, 1, RGB(5,5,5));
	float XPoint = (float)m_CenterPoint.x;
	float YPoint = (float)m_CenterPoint.y;
	int i;
	CPoint point;
	CString strText;
	
	m_pDC->SelectObject(&pen);
	
	for(i = 0; i < m_nYCount / 2; i++)
	{
		// Y_LINE +				
		XPoint += m_nBoardXGap;
		m_pDC->MoveTo((int)XPoint, m_BoardRect.top);
		m_pDC->LineTo((int)XPoint, m_BoardRect.bottom + 10);		
		
		point = CPoint((int)XPoint , m_BoardRect.bottom + 25);
		strText.Format("%d", (int)m_nXGap * (i + 1));
		DrawGapNum(point, strText);
	}
	XPoint = (float)m_CenterPoint.x;
	
	for(i = 0; i < m_nYCount / 2; i++)
	{
		// Y_LINE -
		XPoint -= m_nBoardXGap;
		
		m_pDC->MoveTo((int)XPoint, m_BoardRect.top);
		m_pDC->LineTo((int)XPoint, m_BoardRect.bottom + 10);		
		
		point = CPoint((int)XPoint , m_BoardRect.bottom + 25);
		strText.Format("%d", (int)-1 * m_nXGap * (i + 1));
		DrawGapNum(point, strText);
	}
}





















