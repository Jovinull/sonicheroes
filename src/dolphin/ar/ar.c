#include "types.h"

// The ARAM driver, 0x801DFFC8 to 0x801E1B08. Identified by the AR version
// string in .data, the 0xCC00502x ARAM DMA registers and the stack
// allocator over the 0x4000 ARAM base. The original linker smart-stripped
// the unused accessors (ARGetDMAStatus, ARCheckInit, ARGetBaseAddress,
// ARGetSize, ARGetInternalSize), so only the functions present in the DOL
// are defined here.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;

typedef void (*ARCallback)(void);

typedef struct OSContext {
	u8 pad[0x2C8];
} OSContext;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void (*__OSSetInterruptHandler(s16 interrupt, void (*handler)(s16, OSContext*)))(
    s16, OSContext*);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern void OSRegisterVersion(const char* version);
extern void DCFlushRange(void* addr, u32 nBytes);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void PPCSync(void);
extern void* memset(void* dest, int val, u32 count);

// The ARAM side of the DSP interface register block, as a CW
// absolute-address array. Indexes 16..21 are the DMA registers, 13 is the
// refresh register, 9 is the ARAM mode, 11 the ARAM size.
#ifdef __MWERKS__
volatile u16 __ARRegs[] : 0xCC005000;
#else
extern volatile u16 __ARRegs[];
#endif

#define AR_ARAM_BASE 0x4000

static void __ARHandler(s16 interrupt, OSContext* context);
// Not static: a function-pointer table in game data (lbl_80269200)
// references __ARChecksize, so the symbol must have external linkage.
void __ARChecksize(void);

// The SDK version banner; the string literal is the unit's only .data.
static char VersionString[]
    = "<< Dolphin SDK - AR\trelease build: Apr 17 2003 12:33:55 (0x2301) >>";
char* __ARVersion = VersionString;

static ARCallback __AR_Callback;
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;
static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32* __AR_BlockLength;
static BOOL __AR_init_flag = FALSE;

ARCallback ARRegisterDMACallback(ARCallback callback)
{
	ARCallback oldCallback;
	BOOL enabled;

	oldCallback   = __AR_Callback;
	enabled       = OSDisableInterrupts();
	__AR_Callback = callback;
	OSRestoreInterrupts(enabled);
	return oldCallback;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
	BOOL enabled;

	enabled      = OSDisableInterrupts();
	__ARRegs[16] = (u16)((__ARRegs[16] & ~0x3FF) | (mainmem_addr >> 16));
	__ARRegs[17] = (u16)((__ARRegs[17] & ~0xFFE0) | (mainmem_addr & 0xFFFF));
	__ARRegs[18] = (u16)((__ARRegs[18] & ~0x3FF) | (aram_addr >> 16));
	__ARRegs[19] = (u16)((__ARRegs[19] & ~0xFFE0) | (aram_addr & 0xFFFF));
	__ARRegs[20] = (u16)((__ARRegs[20] & ~0x8000) | (type << 15));
	__ARRegs[20] = (u16)((__ARRegs[20] & ~0x3FF) | (length >> 16));
	__ARRegs[21] = (u16)((__ARRegs[21] & ~0xFFE0) | (length & 0xFFFF));
	OSRestoreInterrupts(enabled);
}

u32 ARAlloc(u32 length)
{
	u32 tmp;
	BOOL enabled;

	enabled = OSDisableInterrupts();

	tmp = __AR_StackPointer;
	__AR_StackPointer += length;
	*__AR_BlockLength = length;
	__AR_BlockLength++;
	__AR_FreeBlocks--;

	OSRestoreInterrupts(enabled);
	return tmp;
}

u32 ARFree(u32* length)
{
	BOOL enabled;

	enabled = OSDisableInterrupts();

	__AR_BlockLength--;
	if (length) {
		*length = *__AR_BlockLength;
	}
	__AR_StackPointer -= *__AR_BlockLength;
	__AR_FreeBlocks++;

	OSRestoreInterrupts(enabled);
	return __AR_StackPointer;
}

u32 ARInit(u32* stack_index_addr, u32 num_entries)
{
	BOOL enabled;

	if (__AR_init_flag == TRUE) {
		return AR_ARAM_BASE;
	}

	OSRegisterVersion(__ARVersion);

	enabled       = OSDisableInterrupts();
	__AR_Callback = NULL;
	__OSSetInterruptHandler(6, __ARHandler);
	__OSUnmaskInterrupts(0x02000000);

	__AR_StackPointer = AR_ARAM_BASE;
	__AR_FreeBlocks   = num_entries;
	__AR_BlockLength  = stack_index_addr;

	__ARRegs[13] = (u16)((__ARRegs[13] & 0xFF) | (__ARRegs[13] & ~0xFF));

	__ARChecksize();

	__AR_init_flag = TRUE;
	OSRestoreInterrupts(enabled);
	return __AR_StackPointer;
}

static void __ARHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;
	u16 tmp;

	tmp         = __ARRegs[5];
	tmp         = (u16)((tmp & ~0x88) | 0x20);
	__ARRegs[5] = tmp;

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);

	if (__AR_Callback) {
		(*__AR_Callback)();
	}

	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

// The DMA helper family below is fully inlined into __ARChecksize; the
// original object kept no out-of-line bodies (static inline emits none).

static inline void __ARWaitForDMA(void)
{
	while (__ARRegs[5] & 0x200) {
	}
}

static inline void __ARClearInterrupt(void)
{
	__ARRegs[5] = (u16)((__ARRegs[5] & ~0x88) | 0x20);
}

static inline void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
	// Main mem address
	__ARRegs[16] = (u16)((__ARRegs[16] & ~0x3FF) | (u16)(mmem_addr >> 16));
	__ARRegs[17] = (u16)((__ARRegs[17] & ~0xFFE0) | (u16)(mmem_addr & 0xFFFF));

	// ARAM address
	__ARRegs[18] = (u16)((__ARRegs[18] & ~0x3FF) | (u16)(aram_addr >> 16));
	__ARRegs[19] = (u16)((__ARRegs[19] & ~0xFFE0) | (u16)(aram_addr & 0xFFFF));

	// DMA buffer size (write direction)
	__ARRegs[20] = (u16)(__ARRegs[20] & ~0x8000);

	__ARRegs[20] = (u16)((__ARRegs[20] & ~0x3FF) | (u16)(length >> 16));
	__ARRegs[21] = (u16)((__ARRegs[21] & ~0xFFE0) | (u16)(length & 0xFFFF));

	__ARWaitForDMA();
	__ARClearInterrupt();
}

static inline void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
	// Main mem address
	__ARRegs[16] = (u16)((__ARRegs[16] & ~0x3FF) | (u16)(mmem_addr >> 16));
	__ARRegs[17] = (u16)((__ARRegs[17] & ~0xFFE0) | (u16)(mmem_addr & 0xFFFF));

	// ARAM address
	__ARRegs[18] = (u16)((__ARRegs[18] & ~0x3FF) | (u16)(aram_addr >> 16));
	__ARRegs[19] = (u16)((__ARRegs[19] & ~0xFFE0) | (u16)(aram_addr & 0xFFFF));

	// DMA buffer size (read direction)
	__ARRegs[20] = (u16)(__ARRegs[20] | 0x8000);

	__ARRegs[20] = (u16)((__ARRegs[20] & ~0x3FF) | (u16)(length >> 16));
	__ARRegs[21] = (u16)((__ARRegs[21] & ~0xFFE0) | (u16)(length & 0xFFFF));

	__ARWaitForDMA();
	__ARClearInterrupt();
}

#define OSRoundUp32B(x) (((u32)(x) + 0x1F) & ~0x1F)

void __ARChecksize(void)
{
	u8 test_data_pad[63];
	u8 dummy_data_pad[63];
	u8 buffer_pad[63];
	u8 save_pad_1[63];
	u8 save_pad_2[63];
	u8 save_pad_3[63];
	u8 save_pad_4[63];
	u8 save_pad_5[63];
	u32* test_data;
	u32* dummy_data;
	u32* buffer;
	u32* save1;
	u32* save2;
	u32* save3;
	u32* save4;
	u32* save5;
	u16 ARAM_mode = 0;
	u32 ARAM_size = 0;
	u32 i;

	do {
	} while (!(__ARRegs[11] & 1));

	ARAM_mode = 3;
	ARAM_size = __AR_InternalSize = 0x1000000;
	__ARRegs[9]                   = (u16)(((__ARRegs[9] & 0xFFFFFFC0) | 3) | 0x20);

	test_data  = (u32*)(OSRoundUp32B(test_data_pad));
	dummy_data = (u32*)(OSRoundUp32B(dummy_data_pad));
	buffer     = (u32*)(OSRoundUp32B(buffer_pad));

	save1 = (u32*)(OSRoundUp32B(save_pad_1));
	save2 = (u32*)(OSRoundUp32B(save_pad_2));
	save3 = (u32*)(OSRoundUp32B(save_pad_3));
	save4 = (u32*)(OSRoundUp32B(save_pad_4));
	save5 = (u32*)(OSRoundUp32B(save_pad_5));

	for (i = 0; i < 8; i++) {
		*(test_data + i)  = 0xDEADBEEF;
		*(dummy_data + i) = 0xBAD0BAD0;
	}

	DCFlushRange((void*)test_data, 0x20);
	DCFlushRange((void*)dummy_data, 0x20);

	__AR_ExpansionSize = 0;

	DCInvalidateRange((void*)save1, 0x20);
	__ARReadDMA((u32)save1, ARAM_size + 0, 0x20);
	PPCSync();

	__ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

	memset((void*)buffer, 0, 0x20);
	DCFlushRange((void*)buffer, 0x20);

	__ARReadDMA((u32)buffer, ARAM_size + 0x0000000, 0x20);
	PPCSync();

	if (buffer[0] == test_data[0]) {
		DCInvalidateRange((void*)save2, 0x20);
		__ARReadDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
		PPCSync();

		DCInvalidateRange((void*)save3, 0x20);
		__ARReadDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
		PPCSync();

		DCInvalidateRange((void*)save4, 0x20);
		__ARReadDMA((u32)save4, ARAM_size + 0x0000200, 0x20);
		PPCSync();

		DCInvalidateRange((void*)save5, 0x20);
		__ARReadDMA((u32)save5, ARAM_size + 0x0400000, 0x20);
		PPCSync();

		__ARWriteDMA((u32)dummy_data, ARAM_size + 0x0200000, 0x20);
		__ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

		memset((void*)buffer, 0, 0x20);
		DCFlushRange((void*)buffer, 0x20);

		__ARReadDMA((u32)buffer, ARAM_size + 0x0200000, 0x20);
		PPCSync();

		if (buffer[0] == test_data[0]) {
			__ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);

			ARAM_mode |= 0 << 1;
			ARAM_size += 0x0200000;
			__AR_ExpansionSize = 0x0200000;
		} else {
			__ARWriteDMA((u32)dummy_data, ARAM_size + 0x1000000, 0x20);
			__ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

			memset((void*)buffer, 0, 0x20);
			DCFlushRange((void*)buffer, 0x20);

			__ARReadDMA((u32)buffer, ARAM_size + 0x1000000, 0x20);
			PPCSync();

			if (buffer[0] == test_data[0]) {
				__ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
				__ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);

				ARAM_mode |= 4 << 1;
				ARAM_size += 0x0400000;
				__AR_ExpansionSize = 0x0400000;
			} else {
				__ARWriteDMA((u32)dummy_data, ARAM_size + 0x0000200, 0x20);
				__ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

				memset((void*)buffer, 0, 0x20);
				DCFlushRange((void*)buffer, 0x20);

				__ARReadDMA((u32)buffer, ARAM_size + 0x0000200, 0x20);
				PPCSync();

				if (buffer[0] == test_data[0]) {
					__ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
					__ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
					__ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);

					ARAM_mode |= 8 << 1;
					ARAM_size += 0x0800000;
					__AR_ExpansionSize = 0x0800000;
				} else {
					__ARWriteDMA((u32)dummy_data, ARAM_size + 0x0400000, 0x20);

					__ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

					memset((void*)buffer, 0, 0x20);
					DCFlushRange((void*)buffer, 0x20);

					__ARReadDMA((u32)buffer, ARAM_size + 0x0400000, 0x20);
					PPCSync();

					if (buffer[0] == test_data[0]) {
						__ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
						__ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
						__ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
						__ARWriteDMA((u32)save4, ARAM_size + 0x0000200, 0x20);

						ARAM_mode |= 12 << 1;
						ARAM_size += 0x1000000;
						__AR_ExpansionSize = 0x1000000;
					} else {
						__ARWriteDMA((u32)save1, ARAM_size + 0x0000000, 0x20);
						__ARWriteDMA((u32)save2, ARAM_size + 0x0200000, 0x20);
						__ARWriteDMA((u32)save3, ARAM_size + 0x1000000, 0x20);
						__ARWriteDMA((u32)save4, ARAM_size + 0x0000200, 0x20);
						__ARWriteDMA((u32)save5, ARAM_size + 0x0400000, 0x20);

						ARAM_mode |= 16 << 1;
						ARAM_size += 0x2000000;
						__AR_ExpansionSize = 0x2000000;
					}
				}
			}
		}

		__ARRegs[9] = (u16)((__ARRegs[9] & ~(0x07 | 0x38)) | ARAM_mode);
	}

	*(u32*)0xC00000D0 = ARAM_size;
	__AR_Size         = ARAM_size;
}
