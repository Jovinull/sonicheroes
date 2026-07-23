#include "types.h"

// The ARAM request queue, 0x801E1B08 to 0x801E1EA4. Identified by the ARQ
// version string in .data and the two-priority request queues over the AR
// DMA driver. The original linker smart-stripped ARQReset, ARQRemoveRequest,
// ARQFlushQueue and the chunk-size accessors; only the functions present in
// the DOL are defined here. __ARQPopTaskQueueHi has no out-of-line body in
// the DOL: it is a fully inlined static inline function.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;

typedef void (*ARQCallback)(u32 pointerToRequest);

typedef struct ARQRequest {
	struct ARQRequest* next; // 0x00
	u32 owner;               // 0x04
	u32 type;                // 0x08
	u32 priority;            // 0x0C
	u32 source;              // 0x10
	u32 dest;                // 0x14
	u32 length;              // 0x18
	ARQCallback callback;    // 0x1C
} ARQRequest;

#define ARQ_TYPE_MRAM_TO_ARAM  0
#define ARQ_PRIORITY_LOW       0
#define ARQ_PRIORITY_HIGH      1
#define ARQ_CHUNK_SIZE_DEFAULT 0x1000

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSRegisterVersion(const char* version);

typedef void (*ARCallback)(void);
extern ARCallback ARRegisterDMACallback(ARCallback callback);
extern void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);

static void __ARQServiceQueueLo(void);
static void __ARQCallbackHack(u32 pointerToRequest);
static void __ARQInterruptServiceRoutine(void);

// The SDK version banner; the string literal is the unit's only .data.
static char VersionString[]
    = "<< Dolphin SDK - ARQ\trelease build: Apr 17 2003 12:33:56 (0x2301) >>";
char* __ARQVersion = VersionString;

static ARQRequest* __ARQRequestQueueHi;
static ARQRequest* __ARQRequestTailHi;
static ARQRequest* __ARQRequestQueueLo;
static ARQRequest* __ARQRequestTailLo;
static ARQRequest* __ARQRequestPendingHi;
static ARQRequest* __ARQRequestPendingLo;
static ARQCallback __ARQCallbackHi;
static ARQCallback __ARQCallbackLo;
static u32 __ARQChunkSize;
static volatile BOOL __ARQ_init_flag;

// Starts the head of the high-priority queue and promotes it to pending.
// Fully inlined at both call sites in the original.
static inline void __ARQPopTaskQueueHi(void)
{
	if (__ARQRequestQueueHi) {
		if (__ARQRequestQueueHi->type == ARQ_TYPE_MRAM_TO_ARAM) {
			ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source,
			    __ARQRequestQueueHi->dest, __ARQRequestQueueHi->length);
		} else {
			ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->dest,
			    __ARQRequestQueueHi->source, __ARQRequestQueueHi->length);
		}
		__ARQCallbackHi       = __ARQRequestQueueHi->callback;
		__ARQRequestPendingHi = __ARQRequestQueueHi;
		__ARQRequestQueueHi   = __ARQRequestQueueHi->next;
	}
}

static void __ARQServiceQueueLo(void)
{
	if (!__ARQRequestPendingLo && __ARQRequestQueueLo) {
		__ARQRequestPendingLo = __ARQRequestQueueLo;
		__ARQRequestQueueLo   = __ARQRequestQueueLo->next;
	}

	if (__ARQRequestPendingLo) {
		if (__ARQRequestPendingLo->length <= __ARQChunkSize) {
			if (__ARQRequestPendingLo->type == ARQ_TYPE_MRAM_TO_ARAM) {
				ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
				    __ARQRequestPendingLo->dest, __ARQRequestPendingLo->length);
			} else {
				ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest,
				    __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);
			}
			__ARQCallbackLo = __ARQRequestPendingLo->callback;
		} else {
			if (__ARQRequestPendingLo->type == ARQ_TYPE_MRAM_TO_ARAM) {
				ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
				    __ARQRequestPendingLo->dest, __ARQChunkSize);
			} else {
				ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest,
				    __ARQRequestPendingLo->source, __ARQChunkSize);
			}
		}
		__ARQRequestPendingLo->length -= __ARQChunkSize;
		__ARQRequestPendingLo->source += __ARQChunkSize;
		__ARQRequestPendingLo->dest += __ARQChunkSize;
	}
}

static void __ARQCallbackHack(u32 pointerToRequest) { }

static void __ARQInterruptServiceRoutine(void)
{
	if (__ARQCallbackHi) {
		(*__ARQCallbackHi)((u32)__ARQRequestPendingHi);
		__ARQRequestPendingHi = NULL;
		__ARQCallbackHi       = NULL;
	} else if (__ARQCallbackLo) {
		(*__ARQCallbackLo)((u32)__ARQRequestPendingLo);
		__ARQRequestPendingLo = NULL;
		__ARQCallbackLo       = NULL;
	}

	__ARQPopTaskQueueHi();

	if (!__ARQRequestPendingHi) {
		__ARQServiceQueueLo();
	}
}

void ARQInit(void)
{
	if (__ARQ_init_flag == TRUE) {
		return;
	}

	OSRegisterVersion(__ARQVersion);

	// One chained assignment, not two statements: the chain stores the Lo
	// queue first, matching the original's store order (the two stores are
	// byte-identical apart from their sda21 offsets, so objdiff scores the
	// swapped pair 100% — only linking catches it).
	__ARQRequestQueueHi = __ARQRequestQueueLo = NULL;
	__ARQChunkSize                            = ARQ_CHUNK_SIZE_DEFAULT;

	ARRegisterDMACallback((ARCallback)__ARQInterruptServiceRoutine);

	__ARQRequestPendingHi = NULL;
	__ARQRequestPendingLo = NULL;
	__ARQCallbackHi       = NULL;
	__ARQCallbackLo       = NULL;

	__ARQ_init_flag = TRUE;
}

void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest,
    u32 length, ARQCallback callback)
{
	BOOL enabled;

	request->next   = NULL;
	request->owner  = owner;
	request->type   = type;
	request->source = source;
	request->dest   = dest;
	request->length = length;

	if (callback) {
		request->callback = callback;
	} else {
		request->callback = __ARQCallbackHack;
	}

	enabled = OSDisableInterrupts();

	switch (priority) {
		case ARQ_PRIORITY_LOW:
			if (__ARQRequestQueueLo) {
				__ARQRequestTailLo->next = request;
			} else {
				__ARQRequestQueueLo = request;
			}
			__ARQRequestTailLo = request;
			break;
		case ARQ_PRIORITY_HIGH:
			if (__ARQRequestQueueHi) {
				__ARQRequestTailHi->next = request;
			} else {
				__ARQRequestQueueHi = request;
			}
			__ARQRequestTailHi = request;
			break;
	}

	if (!__ARQRequestPendingHi && !__ARQRequestPendingLo) {
		__ARQPopTaskQueueHi();

		if (!__ARQRequestPendingHi) {
			__ARQServiceQueueLo();
		}
	}

	OSRestoreInterrupts(enabled);
}
