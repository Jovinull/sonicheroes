#ifndef DOLPHIN_CARD_INTERNAL_H
#define DOLPHIN_CARD_INTERNAL_H

#include <dolphin/card.h>
#include <dolphin/exi.h>

// Library-private CARD declarations (after doldecomp/dolsdk2004
// src/card/__card.h), plus the OS, cache and C library glue the CARD units
// need, kept here as the other dolphin units keep theirs.

typedef u32 OSTick;

#define OS_BASE_CACHED 0x80000000
#define __OSBusClock   (*(u32*)(OS_BASE_CACHED | 0x00F8))
#define OS_BUS_CLOCK   __OSBusClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#define OSTicksToSeconds(ticks)     ((ticks) / (OS_TIMER_CLOCK))
#define OSSecondsToTicks(sec)       ((sec) * (OS_TIMER_CLOCK))
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))

#define OSPhysicalToCached(paddr) ((void*)((u32)(OS_BASE_CACHED + (u32)(paddr))))
#define OSCachedToPhysical(caddr) ((u32)((u32)(caddr) - OS_BASE_CACHED))

typedef struct OSSram {
	u16 checkSum;      // 0x00
	u16 checkSumInv;   // 0x02
	u32 ead0;          // 0x04
	u32 ead1;          // 0x08
	u32 counterBias;   // 0x0C
	s8 displayOffsetH; // 0x10
	u8 ntd;            // 0x11
	u8 language;       // 0x12
	u8 flags;          // 0x13
} OSSram;              // 0x14

typedef struct OSSramEx {
	u8 flashID[2][12];      // 0x00
	u32 wirelessKeyboardID; // 0x18
	u16 wirelessPadID[4];   // 0x1C
	u8 dvdErrorCode;        // 0x24
	u8 _padding0;           // 0x25
	u8 flashIDCheckSum[2];  // 0x26
	u16 gbs;                // 0x28
	u8 _padding1[2];        // 0x2A
} OSSramEx;                 // 0x2C

OSSram* __OSLockSram(void);
OSSramEx* __OSLockSramEx(void);
BOOL __OSUnlockSram(BOOL commit);
BOOL __OSUnlockSramEx(BOOL commit);

typedef BOOL (*OSResetFunction)(BOOL final);
typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
	OSResetFunction func;      // 0x00
	u32 priority;              // 0x04
	OSResetFunctionInfo* next; // 0x08
	OSResetFunctionInfo* prev; // 0x0C
};

#ifdef __MWERKS__
volatile u16 __VIRegs[] : 0xCC002000;
u8 __gUnknown800030E3 : (OS_BASE_CACHED | 0x30E3);
#else
extern volatile u16 __VIRegs[];
extern u8 __gUnknown800030E3;
#endif

#define OFFSET(addr, align) (((u32)(addr) & ((align) - 1)))
#define OSRoundUp32B(x)     (((u32)(x) + 32 - 1) & ~(32 - 1))

void OSRegisterResetFunction(OSResetFunctionInfo* info);
void OSRegisterVersion(const char* version);
u16 OSGetFontEncode(void);
OSTick OSGetTick(void);

void DCFlushRange(void* addr, u32 nBytes);
void DCStoreRange(void* addr, u32 nBytes);

typedef unsigned long size_t;
void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int c, size_t n);
int memcmp(const void* a, const void* b, size_t n);
size_t strlen(const char* s);
char* strncpy(char* dst, const char* src, size_t n);

#ifdef __cplusplus
extern "C" {
#endif

// CARDStatEx
s32 __CARDGetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);
s32 __CARDSetStatusExAsync(s32 chan, s32 fileNo, CARDDir* dirent, CARDCallback callback);
s32 __CARDSetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);

// CARDUnlock
s32 __CARDUnlock(s32 chan, u8 flashID[12]);

// CARDRead
s32 __CARDSeek(CARDFileInfo* fileInfo, s32 length, s32 offset, CARDControl** pcard);

// CARDRdwr
s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);
s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);

// CARDRaw
s32 __CARDRawReadAsync(s32 chan, void* buf, s32 length, s32 offset, CARDCallback callback);
s32 __CARDRawRead(s32 chan, void* buf, s32 length, s32 offset);
s32 __CARDRawErase(s32 chan, s32 offset);
s32 __CARDRawEraseAsync(s32 chan, s32 offset, CARDCallback callback);

// CARDOpen
BOOL __CARDCompareFileName(CARDDir* ent, const char* fileName);
s32 __CARDAccess(CARDControl* card, CARDDir* ent);
s32 __CARDIsPublic(CARDDir* ent);
s32 __CARDGetFileNo(CARDControl* card, const char* fileName, s32* pfileNo);
BOOL __CARDIsOpened(CARDControl* card, s32 fileNo);
s32 __CARDIsWritable(CARDControl* card, CARDDir* ent);
s32 __CARDIsReadable(CARDControl* card, CARDDir* ent);

// CARDNet
extern u16 __CARDVendorID;
extern u8 __CARDPermMask;
int __CARDEnableGlobal(int enable);
int __CARDEnableCompany(int enable);

// CARDMount
void __CARDMountCallback(s32 chan, s32 result);
void __CARDDisable(BOOL disable);

// CARDFormat
s32 CARDFormatAsync(s32 chan, CARDCallback callback);
s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback);
s32 __CARDFormatRegion(s32 chan, u16 encode);

// CARDDir
CARDDir* __CARDGetDirBlock(CARDControl* card);
s32 __CARDUpdateDir(s32 chan, CARDCallback callback);

// CARDCheck
void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv);
s32 __CARDVerify(CARDControl* card);

// CARDBlock
void* __CARDGetFatBlock(CARDControl* card);
s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);
s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback callback);

// CARDBios
extern CARDControl __CARDBlock[2];

extern DVDDiskID* __CARDDiskID;
extern DVDDiskID __CARDDiskNone;

void __CARDDefaultApiCallback(s32 chan, s32 result);
void __CARDSyncCallback(s32 chan, s32 result);
void __CARDExtHandler(s32 chan, OSContext* context);
void __CARDExiHandler(s32 chan, OSContext* context);
void __CARDTxHandler(s32 chan, OSContext* context);
void __CARDUnlockedHandler(s32 chan, OSContext* context);
int __CARDReadNintendoID(s32 chan, u32* id);
s32 __CARDEnableInterrupt(s32 chan, BOOL enable);
s32 __CARDReadStatus(s32 chan, u8* status);
int __CARDReadVendorID(s32 chan, u16* id);
s32 __CARDClearStatus(s32 chan);
s32 __CARDSleep(s32 chan);
s32 __CARDWakeup(s32 chan);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDWritePage(s32 chan, CARDCallback callback);
s32 __CARDErase(s32 chan, CARDCallback callback);
s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
void __CARDSetDiskID(const DVDDiskID* id);
s32 __CARDGetControlBlock(s32 chan, CARDControl** pcard);
s32 __CARDPutControlBlock(CARDControl* card, s32 result);
s32 __CARDSync(s32 chan);
u16 __CARDGetFontEncode(void);
u16 __CARDSetFontEncode(u16 encode);

#ifdef __cplusplus
}
#endif

#endif
