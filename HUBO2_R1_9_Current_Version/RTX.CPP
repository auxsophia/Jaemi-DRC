#include "RTX.h"

PVOID vAddress;
/******************************************************************************/
void RtxInit(void)
{
	unsigned long temp;
	LARGE_INTEGER physAddr;
	LARGE_INTEGER waiting;
	LARGE_INTEGER liPeriod;
	LARGE_INTEGER waiting2;
	LARGE_INTEGER liPeriod2;

	// Shared memory
	hSharedMemory = RtOpenSharedMemory(
										SHM_MAP_WRITE,				// access mode
										FALSE,						// don't care
										L"Can Shared Data",			// name of shared memory
										(VOID **)&pSharedMemory);	// shared memory data address
	if (hSharedMemory == NULL)
	{
		RtWprintf(L"\n>>> RtOpenSharedMemory error = %d\n", GetLastError());
		ExitProcess(1);
	}
	else RtWprintf(L"\n>>> RtOpenSharedMemory is OK..!!");

	// Memory mapping
	temp = baseAddr;
	temp = temp << 4;
	physAddr.QuadPart = temp;
	vAddress = RtMapMemory(physAddr, 0xDFFF, 1);
	if(vAddress==NULL) RtWprintf(L"\n>>> Failure on RtMapMemory..!\n");
	else;

	// Timer for 2 msec (500 Hz)
	liPeriod.QuadPart = timeInt;
	waiting.QuadPart = 30000000;
	if (! (hTimer = RtCreateTimer(
                                  NULL,            // security
                                  0,               // stack size - 0 uses default
                                  TimerHandler,    // timer handler
                                  NULL,            // NULL context (argument to handler)
                                  RT_PRIORITY_MAX, // priority
                                  CLOCK_2) ))      // RTX HAL timer
    {
        RtWprintf(L"\n>>> RtCreateTimer for 2 msec (500 Hz) error = %d\n", GetLastError());
        ExitProcess(1);
    }
	else;
    if (! RtSetTimerRelative( hTimer,              // hTimer
                              &waiting,            // pExpiration
                              &liPeriod) )         // pInterval
    {
        RtWprintf(L"\n>>> RtSetTimerRelative error (2 msec or 500 Hz= %d\n",GetLastError());
        ExitProcess(1);
    }
	else;

	// Timer for 4 msec (100 Hz)
	liPeriod2.QuadPart = timeInt2;
	waiting2.QuadPart = 30000000+timeInt;
	if (! (hTimer2 = RtCreateTimer(
		NULL,            // security
		0,               // stack size - 0 uses default
		TimerHandler2,    // timer handler
		NULL,            // NULL context (argument to handler)
		RT_PRIORITY_MAX-1, // priority
		CLOCK_2) ))      // RTX HAL timer
    {
        RtWprintf(L"\n>>> RtCreateTimer for 10 msec (100 Hz) error = %d\n", GetLastError());
        ExitProcess(1);
    }
	else;
    if (! RtSetTimerRelative( hTimer2,              // hTimer
		&waiting2,            // pExpiration
		&liPeriod2) )         // pInterval
    {
        RtWprintf(L"\n>>> RtSetTimerRelative error (10 msec or 100 Hz= %d\n",GetLastError());
        ExitProcess(1);
    }
	else;
}
/******************************************************************************/
void RtxEnd(void)
{
	BOOL temp = RtUnmapMemory(vAddress);
}
/******************************************************************************/




















/******************************************************************************/