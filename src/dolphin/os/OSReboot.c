#include "types.h"

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef s64 OSTime;

typedef struct OSContext {
	u32 gpr[32];
	u32 cr;
	u32 lr;
	u32 ctr;
	u32 xer;
	f64 fpr[32];
	u32 fpscr_pad;
	u32 fpscr;
	u32 srr0;
	u32 srr1;
	u16 mode;
	u16 state;
	u32 gqr[8];
	u32 psf_pad;
	f64 psf[32];
} OSContext;

typedef struct DVDCommandBlock {
	u8 pad[0x30];
} DVDCommandBlock;

typedef struct DVDDiskID {
	u8 pad[8];
	u8 streaming;
} DVDDiskID;

typedef struct ApploaderHeader {
	char date[16];
	u32 entry;
	u32 size;
	u32 rebootSize;
	u32 reserved;
} ApploaderHeader;

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))
#define OS_BUS_CLOCK              __OSBusClock
#define OS_TIMER_CLOCK            (OS_BUS_CLOCK / 4)
#define OSRoundUp32B(x)           (((u32)(x) + 31) & ~31)

#ifdef __MWERKS__
u32 __OSBusClock : 0x800000F8;
u32 UNK_817FFFFC : 0x817FFFFC;
u32 UNK_817FFFF8 : 0x817FFFF8;
u32 BOOT_REGION_START : 0x812FDFF0;
u32 BOOT_REGION_END : 0x812FDFEC;
u8 OS_REBOOT_BOOL : 0x800030E2;
#else
extern u32 __OSBusClock;
extern u32 UNK_817FFFFC;
extern u32 UNK_817FFFF8;
extern u32 BOOT_REGION_START;
extern u32 BOOT_REGION_END;
extern u8 OS_REBOOT_BOOL;
#endif

extern BOOL OSDisableInterrupts(void);
extern BOOL OSEnableInterrupts(void);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern OSTime OSGetTime(void);
extern void ICInvalidateRange(void* addr, u32 nBytes);
extern void ICFlashInvalidate(void);
extern void __OSDoHotReset(u32 resetCode);

extern void DVDInit(void);
extern void DVDSetAutoInvalidation(BOOL enable);
extern void DVDResume(void);
extern DVDDiskID* DVDGetCurrentDiskID(void);
extern BOOL DVDCheckDisk(void);
extern void __DVDPrepareResetAsync(void (*callback)(s32, DVDCommandBlock*));
extern void DVDCancelStreamAsync(DVDCommandBlock* block, void* callback);
extern BOOL DVDReadAbsAsyncPrio(
    DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock* block);
extern void AISetStreamPlayState(s32 state);
extern void AISetStreamVolLeft(s32 volume);
extern void AISetStreamVolRight(s32 volume);

extern BOOL __OSIsGcam;

static ApploaderHeader Header;
static void* SaveStart;
static void* SaveEnd;
static volatile BOOL Prepared;

static ASM void Run(register void* entryPoint)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	sync
	isync
	mtlr    r3
	blr
#endif // clang-format on
}

static void Callback(s32 result, DVDCommandBlock* block)
{
	Prepared = TRUE;
}

static inline BOOL IsStreamEnabled(void)
{
	if (DVDGetCurrentDiskID()->streaming) {
		return TRUE;
	}
	return FALSE;
}

static inline void ReadApploader(OSTime start)
{
	if (DVDCheckDisk() == 0 || OSGetTime() - start > OS_TIMER_CLOCK) {
		__OSDoHotReset(UNK_817FFFFC);
	}
}

void __OSReboot(u32 resetCode, u32 bootDol)
{
	OSContext exceptionContext;
	DVDCommandBlock dvdCmd;
	DVDCommandBlock dvdCmd2;
	DVDCommandBlock dvdCmd3;
	u32 length;
	u32 offset;
	OSTime time;

	OSDisableInterrupts();
	UNK_817FFFFC      = 0;
	UNK_817FFFF8      = 0;
	OS_REBOOT_BOOL    = TRUE;
	BOOT_REGION_START = (u32)SaveStart;
	BOOT_REGION_END   = (u32)SaveEnd;

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);

	DVDInit();
	DVDSetAutoInvalidation(TRUE);
	DVDResume();
	Prepared = FALSE;
	__DVDPrepareResetAsync(Callback);

	__OSMaskInterrupts(0xFFFFFFE0);
	__OSUnmaskInterrupts(0x400);
	OSEnableInterrupts();

	time = OSGetTime();
	while (Prepared != TRUE) {
		ReadApploader(time);
	}

	if (!__OSIsGcam && IsStreamEnabled()) {
		AISetStreamVolLeft(0);
		AISetStreamVolRight(0);
		DVDCancelStreamAsync(&dvdCmd, NULL);
		time = OSGetTime();
		while (DVDGetCommandBlockStatus(&dvdCmd)) {
			ReadApploader(time);
		}
		AISetStreamPlayState(0);
	}

	DVDReadAbsAsyncPrio(&dvdCmd2, &Header, 0x20, 0x2440, NULL, 0);
	time = OSGetTime();
	while (DVDGetCommandBlockStatus(&dvdCmd2)) {
		ReadApploader(time);
	}

	offset = Header.size + 0x20;
	length = OSRoundUp32B(Header.rebootSize);
	DVDReadAbsAsyncPrio(&dvdCmd3, (void*)0x81300000, length, offset + 0x2440, NULL, 0);
	time = OSGetTime();
	while (DVDGetCommandBlockStatus(&dvdCmd3)) {
		ReadApploader(time);
	}

	ICInvalidateRange((void*)0x81300000, length);
	OSDisableInterrupts();
	ICFlashInvalidate();
	Run((void*)0x81300000);
}
