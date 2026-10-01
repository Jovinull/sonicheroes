#ifndef DOLPHIN_AXFX_INTERNAL_H
#define DOLPHIN_AXFX_INTERNAL_H

#include <dolphin/types.h>
#include <dolphin/ax.h>
#include <dolphin/axfx.h>

// Library-private AXFX declarations (after doldecomp/dolsdk2004
// src/axfx/__axfx.h).

// OS, AI, cache and C library glue the audio units need, kept here as the
// other dolphin units keep theirs.

#define OS_BUS_CLOCK   (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

void OSRegisterVersion(const char* version);
void DCFlushRange(void* addr, u32 nBytes);
void DCStoreRange(void* addr, u32 nBytes);

typedef void (*AIDCallback)(void);
AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AIInitDMA(u32 start_addr, u32 length);
void AIStartDMA(void);
void AIStopDMA(void);
void AISetStreamVolLeft(u8 volume);
void AISetStreamVolRight(u8 volume);

typedef int OSHeapHandle;
extern volatile OSHeapHandle __OSCurrHeap;
void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);
#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr)   OSFreeToHeap(__OSCurrHeap, (ptr))

typedef unsigned long size_t;
void* memset(void* dst, int c, size_t n);
void* memcpy(void* dst, const void* src, size_t n);
float powf(float x, float y);

#ifdef __cplusplus
extern "C" {
#endif

extern void* (*__AXFXAlloc)(u32);
extern void (*__AXFXFree)(void*);

#ifdef __cplusplus
}
#endif

#endif
