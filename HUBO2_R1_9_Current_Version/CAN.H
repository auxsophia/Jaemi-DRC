#include "CANID.h"

/******************************************************************************/
// Definition of Registers for CAN controller
#define		MBSIZE			352//100		// MB를 변경할 경우 'SharedMemory.h'의 Rx_Data[MBSIZE][8]도 바꿔 줄것!!
#define		IRQ_POLLING     0

#define		IMR1			0x21    // Interrupt Mask Register 1 (IMR1)
#define		IMR2			0xA1    // Interrupt Mask Register 2 (IMR2)

#define		EOI1			0x20    // End of Interrupt 1
#define		EOI2			0xA0    // End of Interrupt 2

#define		CR				0       // Control Register
#define		CMR				1       // Command Register
#define		SR				2       // Status Register
#define		IR				3       // Interrupt Register
#define		ACR				4       // Acceptance Code Register
#define		AMR				5       // Acceptance Mask Register
#define		BTR0			6       // Bus Timing Register 0
#define		BTR1			7       // Bus Timing Register 1
#define		OCR				8       // Output Control Regsiter
#define		TR				9       // Test Register

#define		TXID1			10      // Identifier 1 of Transmit Buffer
#define		TXID2			11      // Identifier 2 of Transmit Buffer
#define		TXDATA			12      // Transmit Data unsigned char 1

#define		RXID1			20      // Identifier 1 of Receive Buffer
#define		RXID2			21      // Identifier 2 of Receive Buffer
#define		RXDATA			22      // Receive Data unsigned char 1

#define		ERR_OK          0x00    // No Error
#define		ERR_SEG         0x10    // seg_addr set error
#define		ERR_RESET		0x11	// reset error
#define		ERR_IRQ         0x12    // irq_no set error
#define		ERR_BAUD		0x13	// Baudrate setting error
#define		ERR_HW          0xFF    // CAN hardware error

#define		ERR_NODATA      0x01    // No Received Data
#define		ERR_SEND        0x02    // Fail to send CAN msg
#define		ERR_CONFIG      0x03    // CAN Configuration fail
#define		ERR_RR          0x04    // No Reset Mode
#define		ERR_MB          0xFF    // No matching id is found

#define		NODATA          0x00    // No data is available
#define		NEWDATA         0x01    // New received data is available
#define		OVERRUN         0x02    // Data Overrun
#define		TRANSMITTED     0x03    // Data has been transmitted
// End of Definition for CAN Controller
/******************************************************************************/



/******************************************************************************/
// Definition of Data Structures for CAN Communication
typedef struct _MYCAN
{
	unsigned char irq;			// IRQ number
	unsigned char old_irq;		// Old IRQ number

	unsigned char acc_code;		// Acceptance Code Register (ACR)
	unsigned char acc_mask;		// Acceptance Mask Register (AMR)
	unsigned char btr0;			// Bus Timing Register 0 (BTR0)
	unsigned char btr1;     	// Bus Timing Register 1 (BTR1)
} MYCAN;
typedef struct _MYMB
{
	unsigned short	id;			// Identifier
	unsigned short	idread;		// read Identifier
	unsigned char	rtr;     	// Remote Transmission Request
	unsigned char	dlc;		// Data Length Code
	unsigned char	data[8];	// Data unsigned char
	unsigned char	status;		// status of message buffer
} MYMB;
enum Bitrate 
{ 
	BAUD_1M,     // =0: 1 Mbit/sec
	BAUD_500K,   // =1: 500 kbit/sec
	BAUD_250K,   // =2: 250 kbit/sec
	BAUD_125K,   // =3: 125 kbit/sec
	BAUD_100K    // =4: 100 kbit/sec
};
// End od Dfinition for CAN Communication
/******************************************************************************/

extern MYCAN CAN[2];
extern MYMB MB[MBSIZE];
extern unsigned char rBuf[2];


void			StartCAN(void);
int				InitCANHW(void);
int				InitCAN(unsigned char channel, enum Bitrate BAUD);
int				CanConfig(unsigned char channel);
int				CanNormalRun(unsigned char channel);
void			CanReset(unsigned char channel);
void			CanWrite(unsigned char channel, unsigned int addr, unsigned char data);
unsigned char	CanRead(unsigned char channel, unsigned int offset);
void			InitMB(void);
void			ConfigMB(unsigned short buff_no, unsigned short id);
void			ConfigMB(unsigned short id);
int				CanSendMsg(unsigned char channel, unsigned short id, unsigned char *data,
						   unsigned char dlc, unsigned char rtr);
int				CanReceiveMsg(unsigned char channel, unsigned short id);
void			CanReceiveMsg(unsigned char channel);
unsigned short	GetBuffno(unsigned short id);
int				ReadMBData(unsigned short id, unsigned char *data);





















