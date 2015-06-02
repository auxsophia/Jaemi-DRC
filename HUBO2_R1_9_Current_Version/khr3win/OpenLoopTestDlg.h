#if !defined(AFX_OPENLOOPTESTDLG_H__11E36D53_0598_4293_98D0_F7A94FA9813C__INCLUDED_)
#define AFX_OPENLOOPTESTDLG_H__11E36D53_0598_4293_98D0_F7A94FA9813C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenLoopTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenLoopTestDlg dialog
class CCANwin;

class CKhr3winDlg;

class COpenLoopTestDlg : public CDialog
{
// Construction
public:
	void OLRunStop22(char Flag);
	void OLRunStop21(char Flag);
	void OLRunStop20(char Flag);
	void OLRunStop15(char Flag);
	void OLRunStop14(char Flag);
	void PwmRun(unsigned char BoardNo);
	void PwmStop(unsigned char BoardNo);
	void OLCANInit();
	void OLStop(int BeginID, int EndID);
	void OLRun(int BeginID, int EndID);
	void OLRunStop13(char Flag);
	void OLRunStop12(char Flag);
	void OLRunStop11(char Flag);
	void OLRunStop10(char Flag);
	void OLRunStop09(char Flag);
	void OLRunStop08(char Flag);
	void OLRunStop07(char Flag);
	void OLRunStop06(char Flag);
	void OLRunStop05(char Flag);
	void OLRunStop04(char Flag);
	void OLRunStop03(char Flag);
	void OLRunStop02(char Flag);
	void OLRunStop01(char Flag);
	void OLRunStop00(char Flag);
	char RunStop[30];
	void Close();
	void Init();
	COpenLoopTestDlg(CWnd* pParent = NULL);   // standard constructor

	Byte TxData[8], RxData[8], Txdlc, Rxdlc, TxPort, RxPort, rtr;
    WORD RxID, TxID;

// Dialog Data
	//{{AFX_DATA(COpenLoopTestDlg)
	enum { IDD = IDD_DIALOG_OPEN_LOOP_TEST };
	CButton	m_STOP22;
	CButton	m_STOP21;
	CButton	m_STOP20;
	CButton	m_RUN22;
	CButton	m_RUN21;
	CButton	m_RUN20;
	CButton	m_STOP15;
	CButton	m_RUN15;
	CButton	m_STOP14;
	CButton	m_RUN14;
	CButton	m_STOP09;
	CButton	m_STOP08;
	CButton	m_STOP07;
	CButton	m_STOP06;
	CButton	m_STOP05;
	CButton	m_STOP04;
	CButton	m_STOP03;
	CButton	m_STOP02;
	CButton	m_STOP13;
	CButton	m_STOP12;
	CButton	m_STOP11;
	CButton	m_STOP10;
	CButton	m_STOP01;
	CButton	m_STOP00;
	CButton	m_RUN09;
	CButton	m_RUN08;
	CButton	m_RUN07;
	CButton	m_RUN06;
	CButton	m_RUN05;
	CButton	m_RUN04;
	CButton	m_RUN03;
	CButton	m_RUN02;
	CButton	m_RUN13;
	CButton	m_RUN12;
	CButton	m_RUN11;
	CButton	m_RUN10;
	CButton	m_RUN01;
	CButton	m_RUN00;
	int		m_Duty00;
	int		m_Duty01;
	int		m_Duty02;
	int		m_Duty03;
	int		m_Duty04;
	int		m_Duty05;
	int		m_Duty06;
	int		m_Duty07;
	int		m_Duty08;
	int		m_Duty09;
	int		m_Duty10;
	int		m_Duty11;
	int		m_Duty13;
	int		m_Duty12;
	int		m_Duty14;
	int		m_Duty15;
	int		m_Duty16;
	int		m_Duty17;
	int		m_Duty18;
	int		m_Duty19;
	int		m_Duty20;
	int		m_Duty21;
	int		m_Duty22;
	int		m_Duty23;
	int		m_Duty24;
	int		m_Duty25;
	int		m_Duty26;
	int		m_Duty27;
	int		m_Duty28;
	int		m_Duty29;
	int		m_Duty30;
	int		m_Duty31;
	int		m_Duty32;
	int		m_Duty33;
	int		m_Duty34;
	int		m_Duty35;
	int		m_Duty36;
	int		m_Duty37;
	int		m_Duty38;
	int		m_Duty39;
	int		m_Duty40;
	int		m_Duty41;
	int		m_Duty42;
	int		m_Duty43;
	//}}AFX_DATA
	void SetParentWindow(CKhr3winDlg* pKhr3winDlg) { m_pKhr3winDlg  = pKhr3winDlg; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenLoopTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKhr3winDlg* m_pKhr3winDlg;
	CCANwin		 m_CanWinOL;
	// Generated message map functions
	//{{AFX_MSG(COpenLoopTestDlg)
	afx_msg void OnButtonClose();
	afx_msg void OnButtonRun0();
	afx_msg void OnButtonStop0();
	afx_msg void OnButtonRun1();
	afx_msg void OnButtonStop1();
	afx_msg void OnButtonRun2();
	afx_msg void OnButtonStop2();
	afx_msg void OnButtonRun3();
	afx_msg void OnButtonStop3();
	afx_msg void OnButtonRun4();
	afx_msg void OnButtonStop4();
	afx_msg void OnButtonRun5();
	afx_msg void OnButtonStop5();
	afx_msg void OnButtonRun6();
	afx_msg void OnButtonStop6();
	afx_msg void OnButtonRun7();
	afx_msg void OnButtonStop7();
	afx_msg void OnButtonRun8();
	afx_msg void OnButtonStop8();
	afx_msg void OnButtonRun9();
	afx_msg void OnButtonStop9();
	afx_msg void OnButtonRun10();
	afx_msg void OnButtonStop10();
	afx_msg void OnButtonRun11();
	afx_msg void OnButtonStop11();
	afx_msg void OnButtonRun12();
	afx_msg void OnButtonStop12();
	afx_msg void OnButtonRun13();
	afx_msg void OnButtonStop13();
	afx_msg void OnButtonRun14();
	afx_msg void OnButtonRun15();
	afx_msg void OnButtonStop14();
	afx_msg void OnButtonStop15();
	afx_msg void OnButtonRun20();
	afx_msg void OnButtonStop20();
	afx_msg void OnButtonRun21();
	afx_msg void OnButtonStop21();
	afx_msg void OnButtonRun22();
	afx_msg void OnButtonStop22();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENLOOPTESTDLG_H__11E36D53_0598_4293_98D0_F7A94FA9813C__INCLUDED_)
