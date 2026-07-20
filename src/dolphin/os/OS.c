#include "types.h"

// WORK IN PROGRESS, NonMatching in configure.py.
//
// This was first split as OSException.c covering 0x801D0DA4..0x801D1170. That
// was wrong. The string pool at 0x80291EA8 holds both the OSInit banner
// ("<< Dolphin SDK - OS release build ... >>", "Console Type", "Arena : 0x%x")
// and the exception strings ("Installing OSDBIntegrator", "Exceptions
// initialized"), in one pooled object. A shared pool means one translation
// unit, and the Dolphin SDK does keep OSInit and __OSExceptionInit together in
// OS.c. The split now covers 0x801D0840..0x801D1170.
//
// Functions are in the order the original emits them, which is the order they
// appear in the original source: this compiler does not reorder.
//
// This file is built with -opt nopeephole, set on the object in configure.py.
// The original was compiled without the peephole pass: with it on, register
// copies come out as addi rD,rS,0 where the original has mr, and a single exit
// return collapses into bnelr where the original branches to one trailing blr.
// Turning it off moved every function here at once.
//
// Every function is written. Eight of eleven match; what is left is register
// allocation:
//   ClearArena        99.6%  start lands in r4 and the base in r3, the original
//                            has them the other way round. Declaration and
//                            assignment order do not move it.
//   OSInit            99.1%  the arena ternary loads through r0 and copies to
//                            r3 instead of loading straight into r3. Four forms
//                            tried, this is the best of them.
//   OSExceptionInit   95.4%  the word count for the nop fill is hoisted out of
//                            the exception loop, so one more callee saved
//                            register is live than the original needs, the
//                            frame is 0x40 instead of 0x38, and every register
//                            number below r23 shifts by one. Almost the whole
//                            remaining diff is that shift.
//
// .data is 503 of 504 bytes. The strings and the vector table land in the right
// order; the original pads the section to eight and ours does not.
//
// Several of the remaining lines in OSInit and OSExceptionInit are nothing but
// the names of the .sbss externs below, which cannot be fixed from here.

#define NULL 0

typedef s64 OSTime;

#define SPR_GQR1 913
#define SPR_GQR2 914
#define SPR_GQR3 915
#define SPR_GQR4 916
#define SPR_GQR5 917
#define SPR_GQR6 918
#define SPR_GQR7 919

// Physical address zero is mirrored at 0x80000000 through the cache. Writing
// the OS globals this way rather than as bare constants keeps the compiler
// reusing one base register across the whole run of accesses, which is what
// the original does.
#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))

#define OS_CONSOLE_RETAIL      0x00000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_TDEV        0x20000000

#define OS_CONSOLE_EMULATOR    0x10000000
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_ARTHUR      0x10000002
#define OS_CONSOLE_MINNOW      0x10000003

#define OS_INTERRUPT_PI_RSW 0x16

#define __OS_EXCEPTION_MAX 15

typedef u8 __OSException;

typedef void (*__OSExceptionHandler)(u8 exception, void* context);
typedef void (*__OSInterruptHandler)(s16 interrupt, void* context);

typedef struct OSBootInfo {
	u8    diskID[0x20]; // 0x00
	u32   magic;        // 0x20
	u32   version;      // 0x24
	u32   memorySize;   // 0x28
	u32   consoleType;  // 0x2C
	void* arenaLo;      // 0x30
	void* arenaHi;      // 0x34
	void* FSTLocation;  // 0x38
	u32   FSTMaxLength; // 0x3C
} OSBootInfo;

// Pointed at by the word at physical 0xF4. Only debugFlag and padSpec are
// touched here.
typedef struct BI2Debug {
	u32 dummy[3];      // 0x00
	u32 debugFlag;     // 0x0C
	u32 trackLocation; // 0x10
	u32 trackSize;     // 0x14
	u32 countryCode;   // 0x18
	u32 unk1;          // 0x1C
	u32 unk2;          // 0x20
	u32 padSpec;       // 0x24
} BI2Debug;

typedef struct DVDDriveInfo {
	u16 revisionLevel; // 0x00
	u16 deviceCode;    // 0x02
	u32 releaseDate;   // 0x04
	u8  pad[24];       // 0x08
} DVDDriveInfo;

typedef struct DVDCommandBlock {
	struct DVDCommandBlock* next;                   // 0x00
	struct DVDCommandBlock* prev;                   // 0x04
	u32   command;                                  // 0x08
	s32   state;                                    // 0x0C
	u32   offset;                                   // 0x10
	u32   length;                                   // 0x14
	void* addr;                                     // 0x18
	u32   currTransferSize;                         // 0x1C
	u32   transferredSize;                          // 0x20
	void* id;                                       // 0x24
	void (*callback)(s32, struct DVDCommandBlock*); // 0x28
	void* userData;                                 // 0x2C
} DVDCommandBlock;

extern void __OSUnhandledException(void);

extern int    OSDisableInterrupts(void);
extern void   OSEnableInterrupts(void);
extern OSTime __OSGetSystemTime(void);
extern u32    OSGetResetCode(void);
extern void*  OSGetArenaHi(void);
extern void*  OSGetArenaLo(void);
extern void   OSSetArenaHi(void* newHi);
extern void   OSSetArenaLo(void* newLo);
extern void   OSReport(const char* msg, ...);
extern void   OSRegisterVersion(const char* version);
extern void   OSInitAlarm(void);
extern void*  memset(void* dst, int val, u32 n);

extern void PPCMtmmcr0(u32 value);
extern void PPCMtmmcr1(u32 value);
extern void PPCMtpmc1(u32 value);
extern void PPCMtpmc2(u32 value);
extern void PPCMtpmc3(u32 value);
extern void PPCMtpmc4(u32 value);
extern void PPCDisableSpeculation(void);
extern void PPCSetFpNonIEEEMode(void);
extern u32  PPCMfhid2(void);
extern void PPCMthid2(u32 value);

static void OSExceptionInit(void);
extern void __OSInitSystemCall(void);
extern void __OSModuleInit(void);
extern void __OSInterruptInit(void);
extern void __OSContextInit(void);
extern void __OSCacheInit(void);
extern void __OSInitSram(void);
extern void __OSThreadInit(void);
extern void __OSInitAudioSystem(void);
extern void __OSInitMemoryProtection(void);
extern void __OSResetSWInterruptHandler(s16 interrupt, void* context);
extern __OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, __OSInterruptHandler handler);

extern void EXIInit(void);
extern void SIInit(void);
extern void DVDInit(void);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info,
                            void (*callback)(s32, DVDCommandBlock*));
extern void EnableMetroTRKInterrupts(void);
// Forward declared: OSExceptionInit installs it and OSExceptionVector names it,
// but the original emits the handler last, so it cannot be moved up.
void OSDefaultExceptionHandler(register u8 exception, register void* context);

extern void DBPrintf(const char* msg, ...);
extern int  __DBIsExceptionMarked(u8 exception);
extern void DCFlushRangeNoSync(void* addr, u32 nBytes);
extern void ICInvalidateRange(void* addr, u32 nBytes);
extern void* memcpy(void* dst, const void* src, u32 n);
extern __OSExceptionHandler __OSSetExceptionHandler(u8 exception, __OSExceptionHandler handler);

extern void* __OSSavedRegionStart;
extern void* __OSSavedRegionEnd;

// The previous run leaves the region it wants preserved recorded just under the
// top of MEM1.
#define OS_SAVED_REGION_START (*(void**)0x812FDFF0)
#define OS_SAVED_REGION_END   (*(void**)0x812FDFEC)

#define OS_RESET_RESTART 0x80000000

// These live in .sbss between db.c and OSFpu.c. They cannot be declared here:
// giving OS.c both 0x8042CAE0..0x8042CAF0 and 0x8042CB00..0x8042CB08 puts
// OSFpu.c's ZeroF and ZeroPS in the middle and dtk reports a cyclic link order.
// So they belong to some other unit and are referenced from here.
extern OSBootInfo* BootInfo;
extern u32*        BI2DebugFlag;
extern u32         BI2DebugFlagHolder;
extern int         __OSIsGcam;

extern OSTime __OSStartTime;
extern int    __OSInIPL;
extern u32    __PADSpec;
extern int    __DVDLongFileNameFlag;

// Set by the drive inquiry, read by the boot path out of the OS globals.
#define OS_DEVICE_CODE (*(u16*)0x800030E6)

// Linker defined, see ldscript.lcf. Declared as unsized arrays so the compiler
// cannot decide they are small enough to reach through r13.
extern char _stack_addr[];
extern char __ArenaLo[];
extern char __ArenaHi[];

// Points inside the assembly functions further down. OSExceptionInit copies
// those bodies over the hardware vectors and patches one instruction in the
// middle of the template, so it needs the addresses of the pieces. They are
// declared here and defined by `entry` directives inside the asm blocks.
extern void __OSDBINTSTART(void);
extern void __OSDBINTEND(void);
extern void __OSDBJUMPEND(void);
extern void __OSEVStart(void);
extern void __OSEVEnd(void);
extern void __OSEVSetNumber(void);
extern void __DBVECTOR(void);

const char* __OSVersion = "<< Dolphin SDK - OS\trelease build: Jul 23 2003 11:27:16 (0x2301) >>";

static int AreWeInitialized;
static __OSExceptionHandler* OSExceptionTable;

// Filled in by the drive inquiry the boot path fires off, read back out of the
// OS globals later. These have to be statics of this unit, not externs: the
// original reaches the command block as base+0x20 off the same register it
// used for the drive info, and the compiler only knows that offset for objects
// whose .bss layout it decides itself.
static DVDDriveInfo    DriveInfo;
static DVDCommandBlock DriveBlock;

u32 OSGetConsoleType(void)
{
	u32 type;

	// Two returns, not one assignment and a fallthrough. The original branches
	// out of the first one to a shared trailing blr, which is what a second
	// return statement produces and an assignment does not.
	if (BootInfo == NULL || (type = BootInfo->consoleType) == 0) {
		return OS_CONSOLE_ARTHUR;
	}
	return type;
}

static void ClearArena(void)
{
	void* end;
	void* start;
	u32   size;

	if (OSGetResetCode() != OS_RESET_RESTART) {
		__OSSavedRegionStart = NULL;
		__OSSavedRegionEnd   = NULL;
		size                 = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);
		return;
	}

	start = OS_SAVED_REGION_START;
	end   = OS_SAVED_REGION_END;

	__OSSavedRegionStart = start;
	__OSSavedRegionEnd   = end;

	if (start == NULL) {
		size = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);
		return;
	}

	if (OSGetArenaLo() < __OSSavedRegionStart) {
		if (OSGetArenaHi() <= __OSSavedRegionStart) {
			size = (u32)OSGetArenaHi() - (u32)OSGetArenaLo();
			memset(OSGetArenaLo(), 0, size);
			return;
		}

		size = (u32)__OSSavedRegionStart - (u32)OSGetArenaLo();
		memset(OSGetArenaLo(), 0, size);

		// The local has to be assigned inside the if, not before it. Reading
		// the global into it beforehand loads too early; reading it here is
		// what makes the compiler hold the value in r31 across the
		// OSGetArenaHi call instead of loading it twice.
		if (OSGetArenaHi() > __OSSavedRegionEnd) {
			end  = __OSSavedRegionEnd;
			size = (u32)OSGetArenaHi() - (u32)end;
			memset(end, 0, size);
		}
	}
}

static void InquiryCallback(s32 result, DVDCommandBlock* block)
{
	switch (block->state) {
	case 0:
		OS_DEVICE_CODE = DriveInfo.deviceCode | 0x8000;
		break;
	default:
		OS_DEVICE_CODE = 1;
		break;
	}
}

void OSInit(void)
{
	BI2Debug* DebugInfo;
	u32       consoleType;
	void*     arenaLo;
	void*     arenaHi;

	if (AreWeInitialized != 0) {
		return;
	}
	AreWeInitialized = 1;

	__OSStartTime = __OSGetSystemTime();
	OSDisableInterrupts();

	// Silence the performance monitor before anything else touches it.
	PPCMtmmcr0(0);
	PPCMtmmcr1(0);
	PPCMtpmc1(0);
	PPCMtpmc2(0);
	PPCMtpmc3(0);
	PPCMtpmc4(0);
	PPCDisableSpeculation();
	PPCSetFpNonIEEEMode();

	BI2DebugFlag          = NULL;
	BootInfo              = (OSBootInfo*)OSPhysicalToCached(0x0000);
	__DVDLongFileNameFlag = 0;

	DebugInfo = (BI2Debug*)*(u32*)OSPhysicalToCached(0x00F4);
	if (DebugInfo != NULL) {
		BI2DebugFlag                       = &DebugInfo->debugFlag;
		__PADSpec                          = (u32)DebugInfo->padSpec;
		*(u8*)OSPhysicalToCached(0x30E8) = (u8)*BI2DebugFlag;
		*(u8*)OSPhysicalToCached(0x30E9) = (u8)__PADSpec;
	} else if (BootInfo->arenaHi) {
		BI2DebugFlagHolder = (u32)(*(u8*)OSPhysicalToCached(0x30E8));
		BI2DebugFlag       = &BI2DebugFlagHolder;
		__PADSpec          = (u32)(*(u8*)OSPhysicalToCached(0x30E9));
	}

	__DVDLongFileNameFlag = 1;

	arenaLo = BootInfo->arenaLo;
	OSSetArenaLo((arenaLo == NULL) ? (void*)__ArenaLo : arenaLo);

	// The debugger keeps its stack just above the arena, so give it room.
	if (BootInfo->arenaLo == NULL && BI2DebugFlag != NULL && (*BI2DebugFlag < 2)) {
		OSSetArenaLo((void*)OSRoundUp32B(_stack_addr));
	}

	arenaHi = BootInfo->arenaHi;
	OSSetArenaHi((arenaHi == NULL) ? (void*)__ArenaHi : arenaHi);

	OSExceptionInit();
	__OSInitSystemCall();
	OSInitAlarm();
	__OSModuleInit();
	__OSInterruptInit();
	__OSSetInterruptHandler(OS_INTERRUPT_PI_RSW, __OSResetSWInterruptHandler);
	__OSContextInit();
	__OSCacheInit();
	EXIInit();
	SIInit();
	__OSInitSram();
	__OSThreadInit();
	__OSInitAudioSystem();

	// Turn the write gather pipe off.
	PPCMthid2(PPCMfhid2() & ~0x40000000);

	if (!__OSInIPL) {
		__OSInitMemoryProtection();
	}

	OSReport("\nDolphin OS\n");
	OSReport("Kernel built : %s %s\n", "Jul 23 2003", "11:27:16");
	OSReport("Console Type : ");

	consoleType = OSGetConsoleType();
	switch ((u32)(consoleType & 0xF0000000)) {
	case OS_CONSOLE_RETAIL:
		OSReport("Retail %d\n", consoleType);
		break;

	case OS_CONSOLE_DEVELOPMENT:
	case OS_CONSOLE_TDEV:
		// The switch value has its top nibble stripped but the case labels do
		// not, so nothing here can ever be selected and every development
		// board falls through to the default. That is what the original does.
		switch ((u32)(consoleType & 0x0FFFFFFF)) {
		case OS_CONSOLE_EMULATOR:
			OSReport("Mac Emulator\n");
			break;
		case OS_CONSOLE_PC_EMULATOR:
			OSReport("PC Emulator\n");
			break;
		case OS_CONSOLE_ARTHUR:
			OSReport("EPPC Arthur\n");
			break;
		case OS_CONSOLE_MINNOW:
			OSReport("EPPC Minnow\n");
			break;
		default:
			OSReport("Development HW%d (%08x)\n", (consoleType & 0x0FFFFFFF) - 3, consoleType);
			break;
		}
		break;

	default:
		OSReport("%08x\n", consoleType);
		break;
	}

	OSReport("Memory %d MB\n", BootInfo->memorySize >> 20);

	// Right to left argument evaluation puts the Hi call first, which is the
	// order the original has.
	OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());

	OSRegisterVersion(__OSVersion);

	if (BI2DebugFlag != NULL && (*BI2DebugFlag >= 2)) {
		EnableMetroTRKInterrupts();
	}

	ClearArena();
	OSEnableInterrupts();

	if (!__OSInIPL) {
		DVDInit();
		if (__OSIsGcam) {
			*(u16*)OSPhysicalToCached(0x30E6) = 0x9000;
		} else {
			DCInvalidateRange(&DriveInfo, sizeof(DriveInfo));
			DVDInquiryAsync(&DriveBlock, &DriveInfo, InquiryCallback);
		}
	}
}

// Fills a code region with nop words. Written as a helper so the word count is
// a local of the inlined body rather than a variable of the caller's loop,
// which is what keeps the compiler from hoisting it out of that loop.
static void NopFill(void* dst, u32 nBytes)
{
	u32* p = (u32*)dst;
	u32  n = (nBytes + 3) / 4;

	while (n--) {
		*p++ = 0x60000000;
	}
}

// Copies OSExceptionVector's body over each hardware vector, patching the
// exception number into the template on the way. The debugger gets a say: an
// exception it has marked is either left to it entirely or routed through the
// integrator, and the branch slot in the middle of the template is filled with
// either that jump or with nops.
static void OSExceptionInit(void)
{
	// Not contiguous, which is why this is a table and not 0x100 + (n << 8).
	static u32 ExceptionVectorTable[] = {
		0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700, 0x800,
		0x900, 0xC00, 0xD00, 0xF00, 0x1300, 0x1400, 0x1700,
	};

	__OSException exception;
	u32*  opCodeAddr;
	u32   oldOpCode;
	void* destAddr;
	void* dbIntDest;
	void* evStart;
	u32   dbIntSize;
	u32   dbJumpSize;
	u32   evSize;

	opCodeAddr = (u32*)__OSEVSetNumber;
	oldOpCode  = *opCodeAddr;
	evStart    = __OSEVStart;
	evSize     = (u32)__OSEVEnd - (u32)evStart;

	dbIntDest = OSPhysicalToCached(0x60);
	if (*(u32*)dbIntDest == 0) {
		DBPrintf("Installing OSDBIntegrator\n");
		dbIntSize = (u32)__OSDBINTEND - (u32)__OSDBINTSTART;
		memcpy(dbIntDest, __OSDBINTSTART, dbIntSize);
		DCFlushRangeNoSync(dbIntDest, dbIntSize);
		__sync();
		ICInvalidateRange(dbIntDest, dbIntSize);
	}

	dbJumpSize = (u32)__OSDBJUMPEND - (u32)__OSDBINTEND;

	for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
		// Leave it alone entirely if the debugger has claimed it.
		if (BI2DebugFlag && (*BI2DebugFlag >= 2) && __DBIsExceptionMarked(exception)) {
			DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n", exception);
			continue;
		}

		*opCodeAddr = oldOpCode | exception;

		if (__DBIsExceptionMarked(exception)) {
			DBPrintf(">>> OSINIT: exception %d vectored to debugger\n", exception);
			memcpy(__DBVECTOR, __OSDBINTEND, dbJumpSize);
		} else {
			NopFill(__DBVECTOR, dbJumpSize);
		}

		destAddr = OSPhysicalToCached(ExceptionVectorTable[exception]);
		memcpy(destAddr, evStart, evSize);
		DCFlushRangeNoSync(destAddr, evSize);
		__sync();
		ICInvalidateRange(destAddr, evSize);
	}

	OSExceptionTable = OSPhysicalToCached(0x3000);
	for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
		__OSSetExceptionHandler(exception, OSDefaultExceptionHandler);
	}

	*opCodeAddr = oldOpCode;
	DBPrintf("Exceptions initialized...\n");
}

// Copied over the exception vector area at boot, so it runs from a fixed
// address rather than from wherever the linker put it.
asm void __OSDBIntegrator(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
entry __OSDBINTSTART
	li      r5,0x40
	mflr    r3
	stw     r3,0xC(r5)
	lwz     r3,8(r5)
	oris    r3,r3,0x8000
	mtlr    r3
	li      r3,0x30
	mtmsr   r3
	blr
entry __OSDBINTEND
#endif // clang-format on
}

// Reached by a branch from __OSDBIntegrator's end label.
asm void __OSDBJump(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	bla     0x60
entry __OSDBJUMPEND
#endif // clang-format on
}

__OSExceptionHandler __OSSetExceptionHandler(u8 exception, __OSExceptionHandler handler)
{
	__OSExceptionHandler oldHandler;

	oldHandler                  = OSExceptionTable[exception];
	OSExceptionTable[exception] = handler;
	return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(u8 exception) { return OSExceptionTable[exception]; }

asm void OSExceptionVector(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
entry __OSEVStart
	mtsprg  0,r4
	lwz     r4,0xC0(r0)
	stw     r3,0xC(r4)
	mfsprg  r3,0
	stw     r3,0x10(r4)
	stw     r5,0x14(r4)
	lhz     r3,0x1A2(r4)
	ori     r3,r3,2
	sth     r3,0x1A2(r4)
	mfcr    r3
	stw     r3,0x80(r4)
	mflr    r3
	stw     r3,0x84(r4)
	mfctr   r3
	stw     r3,0x88(r4)
	mfxer   r3
	stw     r3,0x8C(r4)
	mfsrr0  r3
	stw     r3,0x198(r4)
	mfsrr1  r3
	stw     r3,0x19C(r4)
	mr      r5,r3
entry __DBVECTOR
	nop
	mfmsr   r3
	ori     r3,r3,0x30
	mtsrr1  r3
entry __OSEVSetNumber
	li      r3,0
	lwz     r4,0xD4(r0)
	rlwinm. r5,r5,0,30,30
	bne     dbvector
	lis     r5,OSDefaultExceptionHandler@ha
	addi    r5,r5,OSDefaultExceptionHandler@l
	mtsrr0  r5
	rfi
dbvector:
	clrlslwi r5,r3,24,2
	lwz     r5,0x3000(r5)
	mtsrr0  r5
	rfi
entry __OSEVEnd
	nop
#endif // clang-format on
}

asm void OSDefaultExceptionHandler(register u8 exception, register void* context) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stw     r0,0(r4)
	stw     r1,4(r4)
	stw     r2,8(r4)
	stmw    r6,0x18(r4)
	mfspr   r0,SPR_GQR1
	stw     r0,0x1A8(r4)
	mfspr   r0,SPR_GQR2
	stw     r0,0x1AC(r4)
	mfspr   r0,SPR_GQR3
	stw     r0,0x1B0(r4)
	mfspr   r0,SPR_GQR4
	stw     r0,0x1B4(r4)
	mfspr   r0,SPR_GQR5
	stw     r0,0x1B8(r4)
	mfspr   r0,SPR_GQR6
	stw     r0,0x1BC(r4)
	mfspr   r0,SPR_GQR7
	stw     r0,0x1C0(r4)
	mfdsisr r5
	mfdar   r6
	stwu    r1,-8(r1)
	b       __OSUnhandledException
#endif // clang-format on
}
