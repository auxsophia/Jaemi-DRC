#if !defined(AFX_PROFILEGRAPH_H__3FAA8116_78B2_4BE7_88B9_5EF49D661C85__INCLUDED_)
#define AFX_PROFILEGRAPH_H__3FAA8116_78B2_4BE7_88B9_5EF49D661C85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileGraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfileGraph dialog
#include "Board.h"

class CProfileGraph : public CDialog
{
// Construction
public:
	void UpdateBoardPoint();
	float m_Board_LFootZ;
	float m_Board_RFootZ;
	float m_Board_LFootY;
	float m_Board_RFootY;
	float m_Board_LFootX;
	float m_Board_RFootX;
	
	void DispXYZ();
	void InitBoard();
	void Init();
	CProfileGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProfileGraph)
	enum { IDD = IDD_DIALOG_PROF_GRAPH };
	CButton	m_Button_Hold;
	CBoard	m_Board_FootZ;
	CBoard	m_Board_FootY;
	CBoard	m_Board_FootX;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfileGraph)
	afx_msg void OnButtonHold();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEGRAPH_H__3FAA8116_78B2_4BE7_88B9_5EF49D661C85__INCLUDED_)
