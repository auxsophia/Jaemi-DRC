// CommThread.h: interface for the CCommThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMTHREAD_H__E4CB1386_ABE2_438D_B49B_AA95E194C620__INCLUDED_)
#define AFX_COMMTHREAD_H__E4CB1386_ABE2_438D_B49B_AA95E194C620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//---------------------------- ��� ���� --------------------------//
#define	BUFF_SIZE	10000
#define	WM_COMM_READ	(WM_USER+1)	
#define WM_COMM_READ2	(WM_USER+1)
//#define WM_COMM_READ2	(WM_USER+2) // dan edit	

#define	ASCII_LF		0x0a
#define	ASCII_CR		0x0d
#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13



// Queue Ŭ���� ���� //
class	CQueue
{
public:
	BYTE	buff[BUFF_SIZE];
	int		m_iHead, m_iTail;
	
	CQueue();
	void	Clear();
	int		GetSize();
	BOOL	PutByte(BYTE b);		// 1 byte �ֱ�
	BOOL	GetByte(BYTE *pb);		// 1 byte ������

};


//	��� Ŭ����	CCommThread 

// ��Ʈ ���� : OpenPort("COM1", CBR_9600);
// ��Ʈ���� �б� :
//   ��Ʈ�� �� �Ŀ� ��Ʈ�� �ڷᰡ �����ϸ� WM_COMM_READ �޽����� ���� 
//   �����쿡 ���޵ȴ�. ON_MESSAGE ��ũ�θ� �̿�, �Լ��� �����ϰ�
//   m_ReadData String�� ����� �����͸� �̿� �б�
// ��Ʈ�� ���� : WriteComm(buff, 30)�� ���� ���ۿ� �� ũ�⸦ �ǳ׸� �ȴ�.

class CCommThread  
{
public:
	CCommThread();
	virtual ~CCommThread();
	
	
public:
	//--------- ȯ�� ���� -----------------------------------------//
	HANDLE		m_hComm;				// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;			// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bConnected;			// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead, m_osWrite;	// ��Ʈ ���� Overlapped structure
	HANDLE		m_hThreadWatchComm;		// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;				// WM_COMM_READ�� �Բ� ������ �μ�.
	
	//--------- ��� ���� -----------------------------------------//
	CQueue	m_QueueRead;
	
	//--------- �ܺ� ��� �Լ� ------------------------------------//
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam);
	BOOL	ClosePort();
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);
	
	//--------- ���� ��� �Լ� ------------------------------------//
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);
	
};
#endif // !defined(AFX_COMMTHREAD_H__E4CB1386_ABE2_438D_B49B_AA95E194C620__INCLUDED_)

// Thread�� ����� �Լ� 
DWORD	ThreadWatchComm(CCommThread* pComm);


