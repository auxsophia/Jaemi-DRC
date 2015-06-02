#include <windows.h>
#include <rtapi.h>
#include <stdio.h>
#include "SharedMemory.h"
#include "CommonDefinition.h"


/******************************************************************************/
#define timeInt		10000*INT_TIME		// 2 msec (500 Hz)
//#define timeInt		40000		// 4 msec (250 Hz)
#define timeInt2	100000		// 10 msec (100 Hz)
#define baseAddr	0xDA00
/******************************************************************************/


/******************************************************************************/
extern PSHARED_DATA	pSharedMemory;	// shared memory data
extern HANDLE hSharedMemory;		// shared memory handler
extern HANDLE hTimer;				// timer handler for 2 msec (500 Hz)
extern HANDLE hTimer2;				// timer handler for 10 msec (100 Hz)
/******************************************************************************/

void RtxInit(void);
void RtxEnd(void);
void RTFCNDCL TimerHandler(void *nContext);		// 2 msec (500 Hz)
void RTFCNDCL TimerHandler2(void *nContext);		// 10 msec (500 Hz)




















