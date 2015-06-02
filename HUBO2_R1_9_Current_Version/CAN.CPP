#include "CAN.H"
#include "RTX.h"

// RTX에서 가져온 가상 주소
// PCM-3680 CAN 제어기는 'Memory Mapped IO' 방식을 사용하기 때문에
// 특정 주소에 값을 쓰면 IO가 작동을 한다.
extern PVOID vAddress;
unsigned int MBCounter = 0;


/******************************************************************************/
// RTX에서 CAN을 활성화 시킬 때 사용
// 외부에서 사용됨
void StartCAN(void)
{
	printf("\n>>> Initialize CAN hardware ... ");
	
    //------ set CAN card hardware setting
	if(InitCANHW() != ERR_OK )
    {
		RtWprintf(L"\n>>> Hardware initialization error occurred !!");
		ExitProcess(1);
    }
	
    CAN[0].old_irq = CAN[1].old_irq = IRQ_POLLING;
    if(InitCAN(0, BAUD_1M) != ERR_OK)  ExitProcess(1);
    if(InitCAN(1, BAUD_1M) != ERR_OK)  ExitProcess(1);
	
    InitMB(); 	// Initialize CAN message buffer
	
    RtWprintf(L"\n>>> CAN initialization O.K. ");
}
/******************************************************************************/



/******************************************************************************/
// CAN 제어기 초기화 함수
int InitCANHW(void)
{
	unsigned char data;
	
	// Check memory base address for PCM-3680 : 0xC000 ~ 0xDF00
	if( baseAddr>0xdf00 || baseAddr<0xc000 || (baseAddr%0x100) )
		return(ERR_SEG);			// Return : segment address set error
	
	// CAN0 Init. 
	data = CanRead(0, CR);			// read control register (CR)
	if(data & 0x01)					// check if "Reset Request" is set (Reset Mode)
	{
		// 1. CanWrite(0, CR, 0x60);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits -> 처음 프로그램
		// 2. CanWrite(0, CR, 0x06);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits -> by jungho77
		CanWrite(0, CR, 0x00);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits to 'Low'
		data = CanRead(0, CR);
		if(data & 0x01)				// if "Reset Request" is set to HIGH
			return(ERR_RESET);		// Return : reset error
	}
	CanReset(0);               		// Reset CAN port 0
	data = CanRead(0, CR);
	if(! (data & 0x01) )			// if "Reset Request" is disabled (LOW)
		return(ERR_RESET);			// Return : reset error
	else
		return(ERR_OK);				// if "Reset Request" is set to HIGH


	// CAN1 Init. 
	data = CanRead(1, CR);			// read control register (CR)
	if(data & 0x01)					// check if "Reset Request" is set (Reset Mode)
	{
		// 1. CanWrite(1, CR, 0x60);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits -> 처음 프로그램
		// 2. CanWrite(1, CR, 0x06);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits -> by jungho77
		CanWrite(1, CR, 0x00);     	// Set Transmit (TIE) & Receive (RIE) Interrupt Enable bits to 'Low'
		data = CanRead(1, CR);
		if(data & 0x01)				// if "Reset Request" is set to HIGH
			return(ERR_RESET);		// Return : reset error
	}
	CanReset(1);               		// Reset CAN port 0
	data = CanRead(1, CR);
	if(! (data & 0x01) )			// if "Reset Request" is disabled (LOW)
		return(ERR_RESET);			// Return : reset error
	else
		return(ERR_OK);				// if "Reset Request" is set to HIGH

}
/******************************************************************************/



/******************************************************************************/
// CAN 각 채널을 초기화 하는 함수.
// PCM-3680은 2개의 CAN 채널을 제공
int InitCAN(unsigned char channel, enum Bitrate BAUD)
{
	//------ reset CAN controller
	CanReset(channel);
	
    //------ CAN irq setting
	CAN[channel].irq = IRQ_POLLING;
	//------ CAN configuration
    CAN[channel].acc_code = 0x00;		// Write Acceptance Code
    CAN[channel].acc_mask = 0xFF;		// Write Acceptance Mask Register
	// *** 0xFF means "no bits are compared"
    CAN[channel].btr1 = 0x14; 			// Write Bus Timing Register 1
	//CAN[channel].btr1 = 0x32; 			// Write Bus Timing Register 1
	// Sampling = Single
	// Tseg1 = 6, Tseg2 = 2
	// Sampling Point @ 75%
    //------ Write Bus Timing Register 0
    //	SJW(Synchronization Jump Width)(b7,b6) = 4
    //  BRP(Baud Rate Prescaler)(b5..b0) = depends on Bitrate
    switch(BAUD) 
	{
	case BAUD_1M:	CAN[channel].btr0 = 0xC0;
		break;
	case BAUD_500K: CAN[channel].btr0 = 0xC1;
		break;
	case BAUD_250K:	CAN[channel].btr0 = 0xC3;
		break;
	case BAUD_125K: CAN[channel].btr0 = 0xC7;
		break;
	case BAUD_100K:	CAN[channel].btr0 = 0xC9;
		break;
	default:		return(ERR_BAUD);       // Bitrate setting error
    }
	
    if(CanConfig(channel) != ERR_OK) return(ERR_CONFIG);
	
    // Put CAN port to normal mode
    return(CanNormalRun(channel));		// successful initialization
}
/******************************************************************************/
int CanConfig(unsigned char channel)
{
	unsigned char temp;
	
	CanReset(channel);	// reset CAN controller
	
	//------ Write Control Register (CR)
	CanWrite(channel, CR, 0x01);	// Enter Reset Mode without setting RIE
	// and enter reset mode (Set Reset Request bit)
	
	//------ Write Bus Timing Register 0 & 1 (BTR0 & BTR1)
	// BTR can be accessed (read/write) if the reset mode is active
	CanWrite(channel, BTR0, CAN[channel].btr0); // Write Bus Timing Register 0 (BTR0)
	CanWrite(channel, BTR1, CAN[channel].btr1); // Write Bus Timing Register 1 (BTR1)
	
	temp = CanRead(channel, BTR0);
	if(temp != CAN[channel].btr0)			// Read BTR0 and confirm it
		return(ERR_CONFIG);					// fail to configure
	
	temp = CanRead(channel, BTR1);
	if(temp != CAN[channel].btr1)			// Read BTR1 and confirm it
		return(ERR_CONFIG);					// fail to configure
	
	//------ Write Acceptance Code Register (ACR) and
	//		 Acceptance Mask Register (AMR)
	CanWrite(channel, ACR, CAN[channel].acc_code);        // Write ACR
	CanWrite(channel, AMR, CAN[channel].acc_mask);        // Write AMR
	
	//------ Write Output Control Register (OCR)
	//   Set Normal Output Mode & Push-pull dirver
	CanWrite(channel, OCR, 0xfa);
	
	return(ERR_OK);	        // successful
}
/******************************************************************************/



/******************************************************************************/
// CAN 채널을 Normal 모드로 세팅
int CanNormalRun(unsigned char channel)
{
	unsigned char v = CanRead(channel, CR);	// read Control Register (CR)
	
	if(v & 0x01)	        // if Reset Request(RR) is set (Reset Mode)
	{
		CanWrite(channel, CR, v&0xfe);
		// On the '1-to-0' transition of RR bit,  CAN controller returns to "Operating Mode"
		return(ERR_OK);
	}
	else return(ERR_RR); // Error = current mode is not Reset Mode
}
/******************************************************************************/



/******************************************************************************/
// CAN Reset 함수
void CanReset(unsigned char channel)
{	
	unsigned char temp;
	temp = CanRead(channel, 0x0100);
	CanWrite(channel, 0x0100, temp);
	Sleep(100); 	// wait 100ms
}
/******************************************************************************/



/******************************************************************************/
// CAN 제어기의 메모리에 값을 쓰는 함수.
// CAN 메세지를 보내는 함수가 아님.
void CanWrite(unsigned char channel, unsigned int offset, unsigned char data)
{
	unsigned char *temp = (unsigned char *)vAddress;
	*(temp + offset + 0x200*channel) = data;
}
/******************************************************************************/



/******************************************************************************/
// CAN 제어기의 메모리 값을 읽어오는 함수.
// CAN 메세지를 읽는 함수가 아님.
unsigned char CanRead(unsigned char channel, unsigned int offset)
{
	unsigned char *temp = (unsigned char *)vAddress;
	unsigned char data = *(temp + offset + 0x200*channel);
	return data;
}
/******************************************************************************/



/******************************************************************************/
// 메세지바이트를 할당하거나 초기화 할때 사용
// 새로운 메세지를 추가할 때 이 함수를 이용하여 할당해야함
void InitMB(void)
{	
	unsigned short i;
	/////////////////////// 수정 및 추가  /////////////////////////
	//ConfigMB(buff_no, id);
	/*
	ConfigMB(SENSOR_FT1_RXDF);
	ConfigMB(SENSOR_AD1_RXDF);
	ConfigMB(SENSOR_FT2_RXDF);
	ConfigMB(SENSOR_AD2_RXDF);
	ConfigMB(SENSOR_IMU1_RXDF);
	ConfigMB(SENSOR_IMU2_RXDF);

	ConfigMB(DAOFFSET1_RXDF);
	ConfigMB(ADOFFSET1_RXDF);
	ConfigMB(OFFSET1_RXDF);
	ConfigMB(DAOFFSET2_RXDF);
	ConfigMB(ADOFFSET2_RXDF);
	ConfigMB(OFFSET2_RXDF);
*/
	// 0 ~ 79 for sensor MB. : 80EA
	for(i=0 ; i<16 ; i++)
	{
		ConfigMB(SENSOR_FT_BASE_RXDF+i);
		ConfigMB(SENSOR_AD_BASE_RXDF+i);
		ConfigMB(DAOFFSET_BASE_RXDF+i);
		ConfigMB(ADOFFSET_BASE_RXDF+i);
		ConfigMB(OFFSET_BASE_RXDF+i);
	}

	// 80 ~ 127 for Encoder MB : 48EA
	for(i=0 ; i<48 ; i++) 
	{
		ConfigMB(ENC_BASE_RXDF+i);
	}

	// 128 ~ 223
	for(i=0 ; i<48 ; i++) 
	{
		ConfigMB(CUR_BASE_RXDF+i);
		ConfigMB(PM_BASE_RXDF+i);
	}

	// 224 ~ 287 for name MB : 64 EA
	for(i=0 ; i<64 ; i++) 
	{
		ConfigMB(NAME_BASE_RXDF+i);
	}


	// 288 ~ 351 
	for(i=0 ; i<64 ; i++) 
	{
		ConfigMB(STAT_BASE_RXDF+i);
	}
	// Total MBsize = 352
	
}
/******************************************************************************/



/******************************************************************************/
// MB(MessageByte)를 초기화
void ConfigMB(unsigned short buff_no, unsigned short id)
{
	unsigned char i;
	
	MB[buff_no].id = id;	 		// assigned id
	
	MB[buff_no].idread = 0x0000;    // read id
	MB[buff_no].rtr = 0x00;     	// Remote Transmission Request
	MB[buff_no].dlc = 0x00;			// Data Length Code
	
	for(i=0; i<8; i++) MB[buff_no].data[i]=0x00;	// Data unsigned char
	MB[buff_no].status = NODATA;	// initial MB status = No Data
}
/******************************************************************************/
// MB(MessageByte)를 초기화
void ConfigMB(unsigned short id)
{
	unsigned char i;
	
	MB[MBCounter].id = id;	 			// assigned id
	//RtWprintf(L"\nMB[MBCounter].id = %x",MB[MBCounter].id);
	
	MB[MBCounter].idread = 0x0000;		// read id
	MB[MBCounter].rtr = 0x00;     		// Remote Transmission Request
	MB[MBCounter].dlc = 0x00;			// Data Length Code
	
	for(i=0; i<8; i++) MB[MBCounter].data[i]=0x00;	// Data unsigned char
	MB[MBCounter].status = NODATA;		// initial MB status = No Data

	MBCounter++;
}
/******************************************************************************/




/******************************************************************************/
// CAN 메세지를 보내는 함수
int CanSendMsg(unsigned char channel, unsigned short id, unsigned char *data, unsigned char dlc, unsigned char rtr)
{
    unsigned char v, i;

	//RtWprintf(L"\n>>> ID:%x Tx_Data:%x Tx_DLC:%x", id, data[0], dlc);

    v = id >> 3;
    CanWrite(channel, TXID1, v);	// write Identifier (ID.10 .. ID.3)
    v = id & 0x07;        			// write Identifier (ID.2 .. ID.0) to b7..b5
    v <<= 5;
	
    if(rtr==1) v |= 0x10;  			// check Remote Transmit Request (RTR) bit
	
    v += dlc;            			// add Data Length Code (DLC)
    CanWrite(channel, TXID2, v);	// Write Identifier unsigned char 2
	
    for(i=0; i<dlc; i++) CanWrite(channel, TXDATA+i, *(data+i));	// write Data unsigned char
	
    // Write TR of Command Register (CMR)
    CanWrite(channel, CMR, 0x01);	// Set Transmission Request (TR): message will be transmitted
	
    while(1)
    {
		v = CanRead(channel, SR);	// Read Status Register (SR)
		if(v & 0x40)				// If Error Status(ES) bit is set
			return(ERR_SEND);		// fail to send
		if(v & 0x08)				// when Transmission Complete Status (TCS) bit is set
			return(ERR_OK);	        // return (=successful)
    }
}
/******************************************************************************/



/******************************************************************************/
// CAN 메세지를 받는 함수
int CanReceiveMsg(unsigned char channel, unsigned short id)
{
	unsigned char rBuf[2];
	unsigned short i;
	unsigned short buff_no;
	unsigned short idread;
	
	if(CAN[channel].irq == IRQ_POLLING)	// polling
	{
		if(CanRead(channel, SR) & 0x01)	// Read Status Register (SR)
		{								// Check if Receive Buffer Status (RBS) is set
			// if RBS=1, one or more msg are available in RXFIFO
			rBuf[0] = CanRead(channel, RXID1);	// read Identifier (ID.10 .. ID.3)
			rBuf[1] = CanRead(channel, RXID2);	// Read Identifier(ID.2 .. ID.0), RTR, DLC(=lower nibble)
			
			idread = rBuf[0];
			idread <<= 3;
			idread |= (rBuf[1]>>5);	// extract id from rBuf
			buff_no = GetBuffno(idread);    // get message buffer number
			//RtWprintf(L"\nbuff_no = %x", buff_no);
			MB[buff_no].idread = idread; 	// read id
			//RtWprintf(L"\nidrad = %x", idread);
			MB[buff_no].rtr = (rBuf[1]>>4) & 0x01;	// RTR
			//RtWprintf(L"\nrtr = %x", MB[buff_no].rtr);
			MB[buff_no].dlc = rBuf[1] & 0x0f;     	// DLC
			//RtWprintf(L"\ndlc = %x", MB[buff_no].dlc);
			
			for(i=0; i<MB[buff_no].dlc; i++)
			{
				MB[buff_no].data[i] = 
				pSharedMemory->Rx_Data[buff_no][i] = CanRead(channel, RXDATA+i);	// read data unsigned char according to DLC(Data Length Code)
			}
			
			// release receive buffer (RRB) of Command Register (CMR)
			CanWrite(channel, CMR, 0x04); 	// release memory space in RXFIFO
			
			if(MB[buff_no].status==NODATA) MB[buff_no].status = NEWDATA;    // Write NEWDATA flag to Status unsigned char
			else if(MB[buff_no].status==NEWDATA) MB[buff_no].status = OVERRUN;
			else;
		}
	}
	else ;

	//if(idread == id) return(ERR_OK);
	//else return(ERR_NODATA);

	

	// Read CAN msg if new data is available
	//RtWprintf(L"\n\ndata = %x", MB[buff_no].status);
	//RtWprintf(L"\nbuff no = %x", buff_no);
	

	buff_no = GetBuffno(id);

	//RtWprintf(L"\nbuff noX = %x", buff_no);
	//RtWprintf(L"\ndata = %x", MB[buff_no].status);
	

	// Error = No Received Data
	if(MB[buff_no].status==NODATA) return(ERR_NODATA);
	else
	{
		// Set CAN status unsigned char to NODATA
		MB[buff_no].status = NODATA;
		// No errors detected
		return(ERR_OK);
	} 
}
/******************************************************************************/



/******************************************************************************/
// CAN 메세지를 받는 함수(CAN 메세지 버퍼를 확인. 특정 아이디를 체크하지는 않음)
void CanReceiveMsg(unsigned char channel)
{
	unsigned char rBuf[2];
	unsigned short i;
	unsigned short buff_no;
	unsigned short idread;
	
	if(CAN[channel].irq == IRQ_POLLING)	// polling
	{
		if(CanRead(channel, SR) & 0x01)	// Read Status Register (SR)
		{								// Check if Receive Buffer Status (RBS) is set
			// if RBS=1, one or more msg are available in RXFIFO
			rBuf[0] = CanRead(channel, RXID1);	// read Identifier (ID.10 .. ID.3)
			rBuf[1] = CanRead(channel, RXID2);	// Read Identifier(ID.2 .. ID.0), RTR, DLC(=lower nibble)
			
			idread = rBuf[0];
			idread <<= 3;
			idread |= (rBuf[1]>>5);	// extract id from rBuf
			buff_no = GetBuffno(idread);    // get message buffer number
			//RtWprintf(L"\nbuff_no = %x", buff_no);
			MB[buff_no].idread = idread; 	// read id
			//RtWprintf(L"\nidrad = %x", idread);
			MB[buff_no].rtr = (rBuf[1]>>4) & 0x01;	// RTR
			//RtWprintf(L"\nrtr = %x", MB[buff_no].rtr);
			MB[buff_no].dlc = rBuf[1] & 0x0f;     	// DLC
			//RtWprintf(L"\ndlc = %x", MB[buff_no].dlc);
			
			for(i=0; i<MB[buff_no].dlc; i++)
			{
				MB[buff_no].data[i] = 
					pSharedMemory->Rx_Data[buff_no][i] = CanRead(channel, RXDATA+i);	// read data unsigned char according to DLC(Data Length Code)
			}
			
			// release receive buffer (RRB) of Command Register (CMR)
			CanWrite(channel, CMR, 0x04); 	// release memory space in RXFIFO
			
			if(MB[buff_no].status==NODATA) MB[buff_no].status = NEWDATA;    // Write NEWDATA flag to Status unsigned char
			else if(MB[buff_no].status==NEWDATA) MB[buff_no].status = OVERRUN;
			else;
		}
	}
	else ;
}
/******************************************************************************/




/******************************************************************************/
// 해당 ID가 몇 번째 메세지바이트(MB)인지를 확인하는 함수
unsigned short GetBuffno(unsigned short id)
{
	unsigned short i;

	for(i=0 ; i < MBSIZE ; i++)
	{
		if(id == MB[i].id) return i;
	}

	return(MBSIZE-1);
}
/******************************************************************************/



/******************************************************************************/
// MessageBox에 있는 데이터를 읽을때 사용
// 반환값은 읽은 데이터가 새로운 것인지 아닌지를 알려줌.
int ReadMBData(unsigned short id, unsigned char *data)
{
	// Read CAN msg if new data is available
	unsigned char i;
	unsigned short buff_no = GetBuffno(id);
	if(MB[buff_no].status==NEWDATA || MB[buff_no].status==OVERRUN)
	{
		MB[buff_no].status = NODATA;		// Set CAN status unsigned char to NODATA
		for(i=0; i<8 ; i++) *(data+i) = MB[buff_no].data[i];	// Read Data unsigned char from message unsigned char
		
		return(ERR_OK);	        // No errors detected
	}
	else return(ERR_NODATA);		// Error = No Received Data
}
/******************************************************************************/











/******************************************************************************/