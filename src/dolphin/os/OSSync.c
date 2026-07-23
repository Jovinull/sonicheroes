#include "types.h"

// The system call vector. The translation unit runs from the vector at
// 0x801D628C to 0x801D6310, between OSStopwatch and OSThread.
//
// The vector body is assembly in the original source too: it runs as the sc
// exception handler, flashing the data cache through HID0 and returning with
// rfi. The entry directives place the copy range labels the initializer uses.

typedef int BOOL;

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

extern void* memcpy(void* dst, const void* src, u32 n);
extern void DCFlushRangeNoSync(void* addr, u32 nBytes);
extern void ICInvalidateRange(void* addr, u32 nBytes);

void __OSSystemCallVectorStart(void);
void __OSSystemCallVectorEnd(void);

static ASM void SystemCallVector(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
entry __OSSystemCallVectorStart
	mfspr   r9, 1008
	ori     r10, r9, 0x8
	mtspr   1008, r10
	isync
	sync
	mtspr   1008, r9
	rfi
entry __OSSystemCallVectorEnd
	nop
#endif // clang-format on
}

void __OSInitSystemCall(void)
{
	void* addr = OSPhysicalToCached(0xC00);

	memcpy(addr, (void*)__OSSystemCallVectorStart,
	    (u32)__OSSystemCallVectorEnd - (u32)__OSSystemCallVectorStart);
	DCFlushRangeNoSync(addr, 0x100);
	__sync();
	ICInvalidateRange(addr, 0x100);
}
