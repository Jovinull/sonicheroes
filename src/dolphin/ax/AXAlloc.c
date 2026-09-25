#include "types.h"
#include <dolphin/ax.h>

#include "__ax.h"

// AXAlloc.c of the Dolphin SDK AX audio library, 0x801E1F48 to 0x801E2410.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/ax/AXAlloc.c (public reconstruction of the
// Dolphin SDK); this DOL carries the 2003 release build "<< Dolphin SDK - AX ... Jul 29 2003 16:15:36 >>".
// Compiled with GC/1.2.5n like the other SDK units. The original linker
// smart-stripped the functions nothing in the game calls; they are still
// defined here, as in the SDK source, and the linker drops them again.

static AXVPB* __AXStackHead[AX_PRIORITY_STACKS];
static AXVPB* __AXStackTail[AX_PRIORITY_STACKS];

static AXVPB* __AXCallbackStack;

static u32 __AXCheckStacks(void)
{
	u32 i;
	u32 voices;
	AXVPB* voice;

	voices = 0;
	for (i = 0; i < 32; i++) {
		voice = __AXStackHead[i];
		while (voice != 0) {
			voices++;
			if (voices > 64) {
				return 0;
			}

			voice = voice->next;
		}
	}

	return 1;
}

AXVPB* __AXGetStackHead(u32 priority)
{
	return __AXStackHead[priority];
}

void __AXServiceCallbackStack(void)
{
	AXVPB* p;

	for (p = __AXPopCallbackStack(); p; p = __AXPopCallbackStack()) {
		if (p->priority != 0) {
			if (p->callback) {
				p->callback(p);
			}

			__AXRemoveFromStack(p);
			__AXPushFreeStack(p);
		}
	}
}

void __AXInitVoiceStacks(void)
{
	u32 i;

	__AXCallbackStack = NULL;
	for (i = 0; i < AX_PRIORITY_STACKS; i++) {
		__AXStackHead[i] = __AXStackTail[i] = 0;
	}
}

void __AXAllocInit(void)
{
#ifdef DEBUG
	OSReport("Initializing AXAlloc code module\n");
#endif
	__AXInitVoiceStacks();
}

void __AXAllocQuit(void)
{
#ifdef DEBUG
	OSReport("Shutting down AXAlloc code module\n");
#endif
	__AXInitVoiceStacks();
}

void __AXPushFreeStack(AXVPB* p)
{
	p->next          = __AXStackHead[0];
	__AXStackHead[0] = p;
	p->priority      = 0;
}

AXVPB* __AXPopFreeStack(void)
{
	AXVPB* p;

	p = (void*)(u32)&__AXStackHead[0]->next;
	if (p) {
		__AXStackHead[0] = p->next;
	}
	return p;
}

void __AXPushCallbackStack(AXVPB* p)
{
	p->next1          = __AXCallbackStack;
	__AXCallbackStack = p;
}

AXVPB* __AXPopCallbackStack(void)
{
	AXVPB* p;

	p = (void*)(u32)&__AXCallbackStack[0];
	if (p) {
		__AXCallbackStack = p->next1;
	}
	return p;
}

void __AXRemoveFromStack(AXVPB* p)
{
	u32 i;
	AXVPB* head;
	AXVPB* tail;

	i    = p->priority;
	head = __AXStackHead[i];
	tail = __AXStackTail[i];
	if (head == tail) {
		__AXStackHead[i] = __AXStackTail[i] = 0;
		return;
	}

	if (p == head) {
		__AXStackHead[i]       = p->next;
		__AXStackHead[i]->prev = 0;
		return;
	}

	if (p == tail) {
		__AXStackTail[i]       = p->prev;
		__AXStackTail[i]->next = 0;
		return;
	}

	head       = p->prev;
	tail       = p->next;
	head->next = tail;
	tail->prev = head;
}

void __AXPushStackHead(AXVPB* p, u32 priority)
{

	p->next = __AXStackHead[priority];
	p->prev = 0;

	if (p->next) {
		__AXStackHead[priority]->prev = p;
		__AXStackHead[priority]       = p;
	} else {
		__AXStackTail[priority] = p;
		__AXStackHead[priority] = p;
	}

	p->priority = priority;
}

AXVPB* __AXPopStackFromBottom(u32 priority)
{
	AXVPB* p;

	p = NULL;
	if (__AXStackHead[priority]) {
		if (__AXStackHead[priority] == __AXStackTail[priority]) {
			p                       = __AXStackHead[priority];
			__AXStackHead[priority] = __AXStackTail[priority] = 0;
		} else if (__AXStackTail[priority]) {
			p                             = __AXStackTail[priority];
			__AXStackTail[priority]       = p->prev;
			__AXStackTail[priority]->next = 0;
		}
	}

	return p;
}

void AXFreeVoice(AXVPB* p)
{
	BOOL old;

	old = OSDisableInterrupts();
	__AXRemoveFromStack(p);
	if (p->pb.state == 1) {
		p->depop = 1;
	}
	__AXSetPBDefault(p);
	__AXPushFreeStack(p);

	OSRestoreInterrupts(old);
}

AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext)
{
	BOOL old;
	AXVPB* p;
	u32 i;

	old = OSDisableInterrupts();
	p   = __AXPopFreeStack();
	if (p == 0) {
		for (i = 1; i < priority; i++) {
			p = __AXPopStackFromBottom(i);
			if (p) {
				if (p->pb.state == 1) {
					p->depop = 1;
				}
				if (p->callback != 0) {
					p->callback(p);
				}
				break;
			}
		}
	}

	if (p) {
		__AXPushStackHead(p, priority);
		p->callback    = callback;
		p->userContext = userContext;
		__AXSetPBDefault(p);
	}

	OSRestoreInterrupts(old);
	return p;
}

void AXSetVoicePriority(AXVPB* p, u32 priority)
{
	BOOL old;

	old = OSDisableInterrupts();
	__AXRemoveFromStack(p);
	__AXPushStackHead(p, priority);

	OSRestoreInterrupts(old);
}
