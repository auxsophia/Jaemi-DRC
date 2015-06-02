// khr3win.h : main header file for the KHR3WIN application
//

#if !defined(AFX_KHR3WIN_H__B8FC4F05_9CA8_427B_AE58_C8485FCD05A3__INCLUDED_)
#define AFX_KHR3WIN_H__B8FC4F05_9CA8_427B_AE58_C8485FCD05A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CANwin.h"

#include <rtapi.h>

/////////////////////////////////////////////////////////////////////////////
// CKhr3winApp:
// See khr3win.cpp for the implementation of this class
//
#include "..\SharedMemory.h"
//#include "C:\Documents and Settings\BeCool\πŸ≈¡ »≠∏È\BECOOL\KHR3\SharedMemory.h"

class CKhr3winApp : public CWinApp
{
public:
	CKhr3winApp();
protected:
	CCANwin		 m_CanWinAPP;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKhr3winApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
public:		
	void CAN_WRITE1(unsigned int CAN_ID, unsigned char TxData[], unsigned char TxDlc);
	void Home(int T);
	void Each_Stop_CMD(unsigned char MoID);
	void Send_Each_RunCMD(unsigned char MoID, unsigned char Mode);
	void KineChange(unsigned char mode);
	void Dir_PPR();
	void CAN_WRITE(unsigned int CAN_ID, unsigned char TxData[8], unsigned char TxDlc);
	double RPz;
	double RPy;
	double RPx;
	double LPz;
	double LPy;
	double LPx;
	double LegAngle[12];
	char FrdKineWin(double LTh1, double LTh2, double LTh3, double LTh4, double LTh5, double LTh6,
					double RTh1, double RTh2, double RTh3, double RTh4, double RTh5, double RTh6);
	char InvKineWin(double LPx, double LPy, double LPz, double LYaw, double RPx,double RPy, double RPz, double RYaw);
	void Stop_CMD(unsigned char BoardNo);
	void Encoder_ZeroCMD(unsigned char BoardNo);
	void SendRunCMD(unsigned char BoardNo);
	void WINmoveANG_RPM(unsigned char MoID, float Angle, float rpm);
	void DisablePWM(unsigned char BoardNo);
	void DisableHIP(unsigned char BoardNo);
	void SendCTRLOff(unsigned char BoardNo);
	void EnableHIP(unsigned char BoardNo);

	float PLUS_MTR_DIR[TOTAL_MTR_NUM], PPR[TOTAL_MTR_NUM];

	HANDLE			m_hSharedMemory;			// shared memory handler
	PSHARED_DATA	m_pSharedMemory;		// shared memory data
		
	MOTOR			m_Motor[TOTAL_MTR_NUM];
	mSTAT			m_mSTAT[TOTAL_MTR_NUM];
	mCTL			m_mCTL[TOTAL_MTR_NUM];
	jSTAT			m_jSTAT[TOTAL_JMC_NUM];
	
// Implementation	

	//{{AFX_MSG(CKhr3winApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KHR3WIN_H__B8FC4F05_9CA8_427B_AE58_C8485FCD05A3__INCLUDED_)