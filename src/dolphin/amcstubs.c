#include "types.h"

// Stub implementations for hardware this build never talks to. The linker still
// needs the symbols, so each one is present and does nothing useful.

int Hu_IsStub(void)
{
	return 0;
}

void EXI2_Init(void) { }

void EXI2_EnableInterrupts(void) { }

int EXI2_Poll(void)
{
	return 0;
}

int EXI2_ReadN(void* buf, s32 len)
{
	return 0;
}

int EXI2_WriteN(const void* buf, s32 len)
{
	return 0;
}

void EXI2_Reserve(void) { }

void EXI2_Unreserve(void) { }

int AMC_IsStub(void)
{
	return 1;
}

void DBClose(void) { }

void DBOpen(void) { }
