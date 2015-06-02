#if !defined(AFX_BOARD_H__2ABD397E_537F_4BDB_ACF6_9C0627B47D6B__INCLUDED_)
#define AFX_BOARD_H__2ABD397E_537F_4BDB_ACF6_9C0627B47D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Board.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoard window

class CBoard : public CStatic
{
// Construction
public:
	CBoard(CWnd* pWnd,int Num);
	virtual ~CBoard();
// Attributes
public:

// Operations
public:
	void	DrawYGapLine();
	void	DrawXGapLine();
	void	DrawLineText();
	void	DrawGapLine();
	void	StartGraph(UINT nTimeGap);
	void	DrawGapNum(CPoint TextPoint, CString strText);
	void	DrawXYLine();
	void	SetXRange(int nMax, int nMin) { m_nXMin = (float)nMin; m_nXMax = (float)nMax; }
	void	SetYRange(int nMax, int nMin) { m_nYMin = (float)nMin; m_nYMax = (float)nMax; }
	void	SetXYGap(float nXGap, float nYGap) { m_nXGap = nXGap; m_nYGap = nYGap; }
	void	SetCenterPoint(int Msg);
	void	SetCoordinatePoint(int nIdx, int nValue);
	BOOL	SetGraphName(int nMaxIdx, CString GraphName0, CString GraphName1 = "", CString GraphName2 = "", CString GraphName3 = "", CString GraphName4 = "", CString GraphName5 = "");
	void	DrawGraph();
	void	SelectColor(int nColor);
	void	InitBoard(int nMsg);
	void	DrawBoard();
	void	SetBoardColor(COLORREF color) { m_BoardColor = color; }
	void	SetBoardDC(CDC* pDC) { m_pDC = pDC; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoard)
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:
	BOOL m_bStartGraph;
	CWnd*			m_pWnd;	
	CRect			m_BoardRect;
	CPoint			m_CoordinatePoint[6];
	CPoint			m_OldPoint[6];

	int				m_nTimeValue;
	UINT			m_nTimeGap;
	int				m_Num;
	CPoint			m_CenterPoint;
	float			m_nXMax;
	float			m_nXMin;
	float			m_nYMax;
	float			m_nYMin;
	int				m_nColorNum;
	COLORREF		m_GraphColor;
	COLORREF		m_BoardColor;
	CDC*			m_pDC;
	CString			m_strGraphName[6];
	float			m_nXGap;
	float			m_nYGap;
	float			m_nBoardXGap;
	float			m_nBoardYGap;
	int				m_nXCount;
	int				m_nYCount;
	int				m_nMaxIdx;
	int				m_nCenterType;
	//{{AFX_MSG(CBoard)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOARD_H__2ABD397E_537F_4BDB_ACF6_9C0627B47D6B__INCLUDED_)





















