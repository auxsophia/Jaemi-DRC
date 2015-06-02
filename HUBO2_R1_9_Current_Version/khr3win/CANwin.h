// CANwin.h: interface for the CCANwin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CANWIN_H__747773E3_F716_4878_B38A_588C8EAE6543__INCLUDED_)
#define AFX_CANWIN_H__747773E3_F716_4878_B38A_588C8EAE6543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\CommonDefinition.h"
#include "..\CAN.h"

class CCANwin  
{
public:
	CCANwin();
	virtual ~CCANwin();	

public:
	void CAN_WRITE1(unsigned int CAN_ID, unsigned char TxData[8], unsigned char TxDlc);
	void CAN_WRITE(unsigned int CAN_ID, unsigned char TxData[8], unsigned char TxDlc);
	void PingReply();
	void PingCAN(int num);
	void FlagClear();
	void BuffClear();
};

#endif // !defined(AFX_CANWIN_H__747773E3_F716_4878_B38A_588C8EAE6543__INCLUDED_)

#define		ENABLE			1
#define		DISABLE			0


