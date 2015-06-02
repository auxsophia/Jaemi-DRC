// CANwin.cpp: implementation of the CCANwin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "khr3win.h"
#include "CANwin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CKhr3winApp theApp;

CCANwin::CCANwin()
{

}

CCANwin::~CCANwin()
{

}

void CCANwin::BuffClear()
{
//	AfxMessageBox("Hello");
	int i,j;
	for(i=0;i<MBSIZE;i++)
	{
		for(j=0;j<8;j++)
		{
			theApp.m_pSharedMemory->Rx_Data[i][j] = NULL;
		}
	}
	Sleep(50);
}

void CCANwin::FlagClear()
{
	Sleep(50);
}

void CCANwin::PingCAN(int num)
{
	//unsigned char	TxData[5];
	unsigned char	TxData[8];
	unsigned char	TxData1[7];
	//unsigned char	TxData2[2];
	unsigned char	TxData2[3];
	int a;

	switch(num)
	{
	case 0:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RHY];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RHR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RHY] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RHR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[RHY] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[RHR] >> 8) & 0x0F) << 4));
		break;
	case 1:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RHP];
		TxData[4] = 0;
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RHP] & 0xFF);
		TxData[6] = 0;
		TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Z_Ref[RHP] >> 8) & 0x0F);
		break;
	case 2:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RKN];
		TxData[4] = 0;
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RKN] & 0xFF);
		TxData[6] = 0;
		TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Z_Ref[RKN] >> 8) & 0x0F);
		break;
	case 3:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RAP];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RAR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RAP] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RAR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[RAP] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[RAR] >> 8) & 0x0F) << 4));
		break;
	case 4:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LHY];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LHR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LHY] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LHR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[LHY] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[LHR] >> 8) & 0x0F) << 4));
		break;
	case 5:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LHP];
		TxData[4] = 0;
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LHP] & 0xFF);
		TxData[6] = 0;
		TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Z_Ref[LHP] >> 8) & 0x0F);
		break;
	case 6:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LKN];
		TxData[4] = 0;
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LKN] & 0xFF);
		TxData[6] = 0;
		TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Z_Ref[LKN] >> 8) & 0x0F);
		break;
	case 7:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LAP];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LAR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LAP] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LAR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[LAP] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[LAR] >> 8) & 0x0F) << 4));
		break;
	case 8:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RSP];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RSR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RSP] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RSR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[RSP] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[RSR] >> 8) & 0x0F) << 4));
		break;
	case 9:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RSY];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[REB];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RSY] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[REB] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[RSY] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[REB] >> 8) & 0x0F) << 4));
		break;
	case 10:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LSP];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LSR];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LSP] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LSR] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[LSP] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[LSR] >> 8) & 0x0F) << 4));
		break;
	case 11:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LSY];
		TxData[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LEB];
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LSY] & 0xFF);
		TxData[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LEB] & 0xFF);
		TxData[7] = (unsigned char)(((theApp.m_pSharedMemory->Z_Ref[LSY] >> 8) & 0x0F) | (((theApp.m_pSharedMemory->Z_Ref[LEB] >> 8) & 0x0F) << 4));
		break;
	case EJMC0:
		TxData1[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RWY];
		TxData1[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RW1];
		TxData1[5] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[RW2];
		TxData1[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[RWY] & 0xFF);
		break;
	case EJMC1:
		TxData1[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LWY];
		TxData1[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LW1];
		TxData1[5] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[LW2];
		TxData1[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[LWY] & 0xFF);
		break;
	case EJMC2:
		TxData1[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[NKY];
		TxData1[4] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[NK1];
		TxData1[5] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[NK2];
		TxData1[6] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[NKY] & 0xFF);
		break;
	case EJMC3:
		TxData[3] = (unsigned char)theApp.m_pSharedMemory->Limit_Rev[WST];
		TxData[4] = 0;
		TxData[5] = (unsigned char)(theApp.m_pSharedMemory->Z_Ref[WST] & 0xFF);
		TxData[6] = 0;
		TxData[7] = (unsigned char)((theApp.m_pSharedMemory->Z_Ref[WST] >> 8) & 0x0F);
		break;
	}

	a = INT_TIME;
	
	TxData[0]= num;
	TxData[1]= NameInfo;

	TxData1[0]= num;
	TxData1[1]= NameInfo;

	TxData2[0]= num;
	TxData2[1]= NameInfo;
	
	TxData[2] = (unsigned char)(a & 0x00FF);
	
	
	if(num<8) CAN_WRITE(CMD_TXDF,TxData,8);
	else if((num>=48) && (num<48+TOTAL_SEN_NUM)) 
	{
		if((num == FT3) || (num == FT4)) CAN_WRITE1(CMD_TXDF,TxData,8);
		else CAN_WRITE(CMD_TXDF,TxData,5);
	}
	else if((num >= JMC8) && (num <= JMC11))
	{
		TxData[2] = INT_TIME1;	// 10msec
		CAN_WRITE1(CMD_TXDF,TxData,8);
	}
	else if((num >= EJMC0) && (num <= EJMC2))
	{
		TxData1[2] = INT_TIME1;	// 10msec
		CAN_WRITE1(CMD_TXDF,TxData1,7);
	}
	else if(num == EJMC3)
	{
		TxData[2] = INT_TIME1;	// 10msec
		CAN_WRITE1(CMD_TXDF,TxData,8);
	}
	else if((num >= EJMC4) && (num <= EJMC5))
	{
		TxData2[2] = INT_TIME1;	// 10msec
		CAN_WRITE1(CMD_TXDF,TxData2,3);
	}

	Sleep(50);
}

void CCANwin::PingReply()
{
	int				i=0,			j=0;
	int				can_cnt = 0;	
	int JMC_Suc[TOTAL_JMC_NUM];
	int	JMC_FREQ[TOTAL_JMC_NUM];
	int	EJMC_Suc[TOTAL_EJMC_NUM];
	int	EJMC_FREQ[TOTAL_EJMC_NUM];
	int SEN_Suc[TOTAL_SEN_NUM];
	//int SEN_FREQ[TOTAL_SEN_NUM];
	int	temp_dat;
	CString			result,			result_2;

	//(theApp.m_pSharedMemory->Rx_Data[224+i][1]<<16) | (theApp.m_pSharedMemory->Rx_Data[224+i][2]) == INT_FREQ; 
	// for JMC controller
	for(i=JMC0;i<=JMC7;i++)
	{
		temp_dat = (int)(theApp.m_pSharedMemory->Rx_Data[224+i][0]);
		if(temp_dat == INT_TIME) 
		{
			JMC_FREQ[i] = INT_TIME;
			JMC_Suc[i] = 1;
		}
		else JMC_Suc[i] = 0;

		for(j=0;j<8;j++) theApp.m_pSharedMemory->Rx_Data[224+i][j] = NULL;
	}

	for(i=JMC8;i<=JMC11;i++)
	{
		temp_dat = (int)(theApp.m_pSharedMemory->Rx_Data[224+i][0]);
		if(temp_dat == INT_TIME1) 
		{
			JMC_FREQ[i] = INT_TIME1;
			JMC_Suc[i] = 1;
		}
		else JMC_Suc[i] = 0;

		for(j=0;j<8;j++) theApp.m_pSharedMemory->Rx_Data[224+i][j] = NULL;
	}

	// for EJMC controller
	for(i=0;i<TOTAL_EJMC_NUM;i++)
	{
		//if(theApp.m_pSharedMemory->Rx_Data[224+32+i][1] != 0) 
		temp_dat = (int)(theApp.m_pSharedMemory->Rx_Data[224+32+i][0]);
		if(temp_dat == INT_TIME1) 
		{
			EJMC_FREQ[i] = INT_TIME1;
			EJMC_Suc[i] = 1;
		}
		else EJMC_Suc[i] = 0;
		
		for(j=0;j<8;j++) 
			theApp.m_pSharedMemory->Rx_Data[224+32+i][j] = NULL;
	}

	// for Sensor board
	for(i=0;i<TOTAL_SEN_NUM;i++)
	{
		if(theApp.m_pSharedMemory->Rx_Data[224+32+16+i][1] != 0) 
		{
			//SEN_FREQ[i] = INT_TIME;
			SEN_Suc[i] = 1;
		}
		else SEN_Suc[i] = 0;
		
		for(j=0;j<8;j++) 
			theApp.m_pSharedMemory->Rx_Data[224+32+16+i][j] = NULL;
	}


	for(i=0;i<TOTAL_JMC_NUM;i++)
	{
		if(JMC_Suc[i] == 0)
		{
			result.Format("%2d th JMC Board --------\n",i);
			result_2 += result;
		}
		else
		{
			result.Format("%2d th JMC Board is ready for %d msec Int. time.\n",i,JMC_FREQ[i]);
			result_2 += result;
		}
	}

	result.Format("~~~~~~~~~~~~~~~~~~~~\n\n");
	result_2 += result;

	for(i=0;i<TOTAL_EJMC_NUM;i++)
	{
		if(EJMC_Suc[i] == 0)
		{
			result.Format("%2d th EJMC Board --------\n",i);
			result_2 += result;
		}
		else
		{
			result.Format("%2d th EJMC Board is ready for %d msec Int. time.\n",i,EJMC_FREQ[i]);
			result_2 += result;
		}
	}

	result.Format("~~~~~~~~~~~~~~~~~~~~\n\n");
	result_2 += result;

	for(i=0;i<TOTAL_SEN_NUM;i++)
	{
		if(SEN_Suc[i] == 0)
		{
			result.Format("%2d th Sensor --------\n",i);
			result_2 += result;
		}
		else
		{
			result.Format("%2d th Sensor Board is ready.\n",i);
			result_2 += result;
		}
	}

	AfxMessageBox(result_2);
	
	//if(can_cnt != 0) AfxMessageBox(result_2);
	//else AfxMessageBox("All Modules are Working ...");
}
void CCANwin::CAN_WRITE(unsigned int CAN_ID, unsigned char TxData[8], unsigned char TxDlc)
{
	theApp.m_pSharedMemory->Tx_ID = CAN_ID;

	for(int i=0; i<TxDlc; i++)
	{
		theApp.m_pSharedMemory->Tx_Data[i] = TxData[i];
	}

	theApp.m_pSharedMemory->Tx_DLC = TxDlc;
	theApp.m_pSharedMemory->Tx_Flag = TRUE;
}

void CCANwin::CAN_WRITE1(unsigned int CAN_ID, unsigned char TxData[], unsigned char TxDlc)
{
	theApp.m_pSharedMemory->Tx1_ID = CAN_ID;

	for(int i=0; i<TxDlc; i++)
	{
		theApp.m_pSharedMemory->Tx1_Data[i] = TxData[i];
	}

	theApp.m_pSharedMemory->Tx1_DLC = TxDlc;
	theApp.m_pSharedMemory->Tx1_Flag = TRUE;
}
