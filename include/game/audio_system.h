#ifndef GAME_AUDIO_SYSTEM_H
#define GAME_AUDIO_SYSTEM_H

// dolphin/os.h has no C++ linkage guard and the other SDK headers include it, so it comes first
// inside an explicit C block.
extern "C" {
#include "dolphin/os.h"
}
#include "dolphin/arq.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"

// The audio system block at lbl_8042CF6C (fn_8020AD88 returns 0x0D000001 while that pointer is
// null): eight 0x1530-byte slots at 0x5478, the AXFX aux-effect contexts at 0xFE04 and 0x40 handles
// at 0x13F6C. Type and field names are inferred from the GameCube code; the subsystem's own names
// are not known.

struct PoolHandle {
	unsigned char active; // 0x00
	signed char channel;  // 0x01: index into PoolSystem::busy, negative when none
	unsigned char pad2[0x2];
	int param4;  // 0x04
	int param8;  // 0x08
	int paramC;  // 0x0C
	int param10; // 0x10
};

// Singly linked list node of the audio library's list helpers (fn_80206340 and neighbours); a
// list is a pointer to its first node.
struct PoolListNode {
	PoolListNode* next; // 0x00
	void* data;         // 0x04
};

// Sequence playback state of a slot (slot offset 0x48), set up by fn_8020B8A0.
struct PoolSequence {
	unsigned short f00; // 0x00
	unsigned char pad02[0x2];
	unsigned int f04; // 0x04
	unsigned char pad08[0x18 - 0x8];
	float f18; // 0x18
	unsigned char pad1C[0x20 - 0x1C];
	long long timeA; // 0x20: both advanced by the paused time on resume (fn_8020B5E8)
	long long timeB; // 0x28
	unsigned char pad30[0x3C - 0x30];
	int param;            // 0x3C
	unsigned char* data;  // 0x40: sequence data after its 0x28-byte header
	unsigned char* start; // 0x44
	unsigned char pad48[0x58 - 0x48];
};

// Sixteen of these per slot, from slot offset 0xA4 (reset by fn_80209C48). fn_802094A4 maps MIDI
// controllers onto them: 7 -> f10, 10 -> f18, 11 -> f14, 62 -> f20/f24, 63 -> f20, 64 -> bit 0
// of f00.
struct PoolChannel {
	int f00;   // 0x00
	int index; // 0x04: channel number (fn_80209AA4)
	int f08;   // 0x08: controllers 0/32 (bank select), see fn_802094A4
	int f0C;   // 0x0C: program (MIDI program change, fn_802096B0)
	int f10;   // 0x10
	int f14;   // 0x14
	int f18;   // 0x18
	int f1C;   // 0x1C
	int f20;   // 0x20
	int f24;   // 0x24
	int f28;   // 0x28
	int f2C;   // 0x2C: passed to fn_802073A0 by fn_80209318
	unsigned char pad30[0x8];
	unsigned int f38; // 0x38
	float f3C;        // 0x3C
	float f40;        // 0x40
	unsigned char pad44[0x4];
};

struct PoolSlot {
	int active;          // 0x00: bit 31 set while the slot runs (fn_80209A3C clears it)
	unsigned int flags4; // 0x04: bit 0 set while paused (fn_8020B730), bit 1 checked on resume
	// Two linear ramps advanced by fn_802092A8 and fn_8020917C: value moves from start to target
	// while remaining counts down from duration in steps of 5; remaining is -1 when idle.
	float rampAValue;           // 0x08
	float f0C;                  // 0x0C
	float f10;                  // 0x10
	float rampATarget;          // 0x14
	float rampAStart;           // 0x18
	float rampADuration;        // 0x1C
	float rampARemaining;       // 0x20
	float rampBValue;           // 0x24
	float f28;                  // 0x28
	float rampBTarget;          // 0x2C
	float rampBStart;           // 0x30
	float rampBDuration;        // 0x34
	float rampBRemaining;       // 0x38
	float f3C;                  // 0x3C: set by fn_802090B8
	long long pauseTime;        // 0x40: system time when paused
	PoolSequence seq;           // 0x48: sequence state, reset by fn_8020B8A0
	PoolListNode* objects;      // 0xA0: the slot's objects (swept by fn_80206578)
	PoolChannel channels[16];   // 0xA4
	unsigned int events[0x400]; // 0x524: queued MIDI events (status, data1, data2, extra bytes)
	int eventRead;              // 0x1524
	int eventWrite;             // 0x1528
	int eventCount;             // 0x152C
};

// 0x40 of these from system offset 0x54, each owning one AX voice (fn_80208CE4 hands them out;
// fn_80208C38 counts the ones with nonzero flags). Bit 31 of flags marks one in use, bit 30 one
// still waiting for its voice.
struct PoolEntry10C {
	int flags; // 0x00
	int index; // 0x04: position in the array (fn_80208E28)
	int f08;   // 0x08
	int f0C;   // 0x0C
	float f10; // 0x10
	unsigned char pad14[0x34 - 0x14];
	AXVPB* voice; // 0x34
	unsigned char pad38[0x104 - 0x38];
	int f104; // 0x104
	int f108; // 0x108
};

// 0x40 of these from system offset 0x4354; fn_80206F04 counts the ones with a nonzero first byte.
struct PoolEntry14 {
	unsigned char used; // 0x00
	unsigned char pad1[0x14 - 0x1];
};

// 0x20-byte heap block header: "MF" for a free block, "MB" for a used block and the end marker
// (fn_80205DF4, fn_80205CBC). The memory handed out follows the header.
struct PoolHeapBlock {
	unsigned short tag;  // 0x00
	unsigned short f2;   // 0x02
	PoolHeapBlock* next; // 0x04
	unsigned char pad8[0x18];
};

// A sounding note of a slot (the data of a node in PoolSlot::objects), made by fn_80206948.
struct PoolObject {
	unsigned char pad0[0x2];
	unsigned char channel; // 0x02
	unsigned char key;     // 0x03
	unsigned char pad4[0xC - 0x4];
	PoolSlot* slot;        // 0x0C
	PoolListNode* entries; // 0x10: its voice entries
};

typedef void (*PoolRequestCallback)(unsigned int arg);

// Heap copy of a bank chunk.
struct PoolBank {
	unsigned char* data; // null when nothing is loaded
	unsigned int size;
};

// 0x10-byte chunk header of a bank image ("gcax" + a kind tag); `size` bytes of data follow.
struct PoolChunk {
	unsigned int tag0; // "gcax"
	unsigned int tag1;
	unsigned int f8;
	unsigned int size;
};

struct PoolSystem {
	int f00;  // 0x00: nonzero once the system runs
	int size; // 0x04: sizeof(PoolSystem), set by fn_8020A12C
	int lock; // 0x08: update nesting count, changed with interrupts disabled
	int f0C;  // 0x0C: result of fn_80208C38
	int f10;  // 0x10: result of fn_80206F04
	int pad14;
	long long time;     // 0x18: OSGetTime() of the current update
	long long prevTime; // 0x20
	unsigned char pad28[0x2C - 0x28];
	float f2C; // 0x2C: cleared by fn_8020A12C
	unsigned char pad30[0x38 - 0x30];
	int voiceCount;     // 0x38: AX voices to acquire up front, at most 0x40 (fn_80208E28)
	int voicesAcquired; // 0x3C: AX voices taken by fn_80208CE4
	unsigned char pad40[0x4];
	int f44; // 0x44: 1 keeps a paused slot's handle (fn_802066AC) instead of releasing it
	unsigned char pad48[0x50 - 0x48];
	int nextEntry;                             // 0x50: rotating search start of fn_80208CE4
	PoolEntry10C entries10C[0x40];             // 0x54
	PoolEntry14 entries14[0x40];               // 0x4354
	unsigned char* heap;                       // 0x4854: 32-byte aligned heap start (fn_80205DF4)
	unsigned int heapSize;                     // 0x4858
	ARQRequest requests[0x40];                 // 0x485C: ARAM transfers posted by fn_80205848
	unsigned char busy[0x40];                  // 0x505C: nonzero while the request is in flight
	unsigned int arqOwner;                     // 0x509C
	PoolRequestCallback requestCallback[0x40]; // 0x50A0: called by fn_80205B08 on completion
	unsigned int requestCallbackArg[0x40];     // 0x51A0
	unsigned char pad52A0[0x4];
	unsigned int aramSize;             // 0x52A4: ARAM bytes taken by fn_8020A12C
	int arenaFree;                     // 0x52A8: bytes left for fn_80206104
	int arenaNext;                     // 0x52AC: offset of the next region
	unsigned int aramBase;             // 0x52B0: ARAlloc result
	unsigned int aramZero;             // 0x52B4: 0x500 zeroed ARAM bytes at the arena start
	unsigned int regionDefaults[0x10]; // 0x52B8: default region sizes set by fn_802061B4
	struct {
		int offset;
		int size;
	} regions[0x10];          // 0x52F8: reserved by fn_80206104
	PoolBank banks[0x10];     // 0x5378: "gcaxMPBP" chunks loaded by fn_80205F9C
	PoolBank sequences[0x10]; // 0x53F8: "gcaxMSB " chunks loaded by fn_80205EA4
	PoolSlot slots[8];        // 0x5478
	unsigned char padFDF8[0xFDFC - 0xFDF8];
	void* searchKey; // 0xFDFC: object fn_80206804 looks for (set by fn_80206578)
	unsigned char padFE00[0xFE04 - 0xFE00];
	AXFX_REVERBSTD reverbStd; // 0xFE04: aux effect contexts selected by fn_80209CDC
	AXFX_REVERBHI reverbHi;   // 0xFF58
	AXFX_CHORUS chorus;       // 0x10138
	AXFX_DELAY delay;         // 0x101D4
	unsigned char pad10[0x13A38 - 0x101D4 - sizeof(AXFX_DELAY)];
	unsigned char f13A38; // 0x13A38: cleared by fn_802061B4
	unsigned char pad13A39[0x2];
	unsigned char skipped; // 0x13A3B: updates skipped because one was already running
	unsigned char pad13A3C[0x8];
	float f13A44; // 0x13A44: set to 1.004184 by fn_802061B4
	unsigned char pad13A48[0x4];
	unsigned char zeroBuffer[0x520]; // 0x13A4C: 32-byte aligned 0x500 zero bytes sent to ARAM
	PoolHandle handles[0x40];        // 0x13F6C
	unsigned char f1446C;            // 0x1446C: passed to the bank loaders
	unsigned char pad1446D[0x3];
};

extern "C" {
extern PoolSystem* lbl_8042CF6C;
extern char lbl_8023D4C8[];
extern char lbl_8023D4EC[];
extern const float lbl_804300A0; // .sdata2 literal (float)0x88888888
}

// Resets channel `ch` of a slot to its defaults with interrupts disabled (fn_80209C48, also
// inlined by fn_80209AA4). lbl_804300A0 is const so its load may be scheduled early, as in retail.
static inline void ResetPoolChannel(PoolSlot* s, int ch)
{
	BOOL enabled        = OSDisableInterrupts();
	s->channels[ch].f00 = 0;
	s->channels[ch].f10 = 100;
	s->channels[ch].f18 = 0x40;
	s->channels[ch].f1C = 0x2000;
	s->channels[ch].f14 = 0x7F;
	s->channels[ch].f20 = 0;
	s->channels[ch].f28 = 0;
	s->channels[ch].f24 = -1;
	s->channels[ch].f38 = 0x88888888;
	s->channels[ch].f3C = lbl_804300A0;
	s->channels[ch].f40 = lbl_804300A0;
	OSRestoreInterrupts(enabled);
}

// Index of the first idle ARAM request; with all 0x40 busy it reports lbl_8023D4C8 with the file
// name lbl_8023D4EC and line 0xC2, then hangs.
static inline int FindFreeArqRequest(void)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		if (lbl_8042CF6C->busy[i] == 0) {
			return i;
		}
	}
	OSReport(lbl_8023D4C8, lbl_8023D4EC, 0xC2);
	while (1) {
	}
}

// 0 for an active record of the pool, 0x07000103 for null, 0x07000102 otherwise.
static inline int CheckPoolHandle(PoolSystem* sys, PoolHandle* h)
{
	int i;
	if (h == 0) {
		return 0x07000103;
	}
	for (i = 0; i < 0x40; i++) {
		if (h == &sys->handles[i]) {
			if (h->active == 0) {
				break;
			}
			return 0;
		}
	}
	return 0x07000102;
}

// 0 for an active slot of the pool, 0x07000103 for null, 0x07000102 otherwise.
static inline int CheckPoolSlot(PoolSystem* sys, PoolSlot* s)
{
	int i;
	if (s == 0) {
		return 0x07000103;
	}
	for (i = 0; i < 8; i++) {
		if (s == &sys->slots[i]) {
			if (s->active == 0) {
				break;
			}
			return 0;
		}
	}
	return 0x07000102;
}

#endif
