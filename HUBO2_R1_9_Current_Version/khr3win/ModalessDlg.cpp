// ModalessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "khr3win.h"
#include "ModalessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModalessDlg dialog


CModalessDlg::CModalessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModalessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModalessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModalessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModalessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModalessDlg, CDialog)
	//{{AFX_MSG_MAP(CModalessDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModalessDlg message handlers
