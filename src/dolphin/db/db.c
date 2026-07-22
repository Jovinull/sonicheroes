#include "types.h"
#include "dolphin/os.h"

// The interface block and the saved context pointer both live in the OS globals
// area, and the addresses are converted between cached and physical by adding
// 0x80000000 and letting it wrap.
#define DB_INTERFACE_ADDR 0x80000040
#define DB_HANDLER_SLOT   (*(void**)0x80000048)
#define DB_CONTEXT_SLOT   (*(u32*)0xC0)

extern void PPCHalt(void);

// Declared in this order because the compiler lays small bss out in reverse,
// and the original has __DBInterface at the lower address.
int DBVerbose;
void* __DBInterface;

void DBInit(void);
static void DBExceptionDestinationAux(void);
void __DBExceptionDestination(void);
u32 __DBIsExceptionMarked(u8 exception);
void DBPrintf(const char* msg, ...);

void DBInit(void)
{
	__DBInterface   = (void*)DB_INTERFACE_ADDR;
	DB_HANDLER_SLOT = (void*)((u32)__DBExceptionDestination + 0x80000000);
	DBVerbose       = 1;
}

// Reached by a tail branch from __DBExceptionDestination, so it must stay a
// separate function.
#pragma dont_inline on
static void DBExceptionDestinationAux(void)
{
	u32 phys      = DB_CONTEXT_SLOT;
	void* context = (void*)(phys + 0x80000000);

	OSReport("DBExceptionDestination\n");
	OSDumpContext(context);
	PPCHalt();
}
#pragma dont_inline off

asm void __DBExceptionDestination(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfmsr   r3
	ori     r3,r3,0x30
	mtmsr   r3
	b       DBExceptionDestinationAux
#endif // clang-format on
}

u32 __DBIsExceptionMarked(u8 exception) { return ((u32*)__DBInterface)[1] & (1 << exception); }

// Release build stub. It still has to accept the varargs so the caller side
// matches, but the body is empty.
void DBPrintf(const char* msg, ...) { }
