#ifndef GAME_ATOMIC_PLUGIN_12F_H
#define GAME_ATOMIC_PLUGIN_12F_H

#include "types.h"

// Atomic plugin 0x12F, registered by fn_801FC470 (HYPOTHESIS: through RpAtomicRegisterPlugin).
// Each atomic holds a pointer to heap data at offset lbl_8042CF48. Field names are inferred from
// the plugin units around 0x801FC3C8 only; the plugin's purpose is UNKNOWN.

struct Atomic12F;

struct Atomic12FPluginData {
	u8 pad0[0x4];
	s32 count; // 0x4
	u8 pad8[0x4];
	void* buffer;                      // 0xC: heap block owned by the data
	void (*finish)(Atomic12F* atomic); // 0x10
	u8 pad14[0x8];
	void (*flush)(Atomic12F* atomic, void* block, s32 count, u32 flags); // 0x1C
	s32 (*process)(Atomic12F* atomic, void* block, s32 count);           // 0x20
	u8 pad24[0x3C - 0x24];
	u32 pendingFlags; // 0x3C
	u32 activeFlags;  // 0x40
	u8 pad44[0x4];
	u8 block[0x98 - 0x48]; // 0x48: extent HYPOTHESIS (fn_801FD214 addresses 0x98)
};

extern "C" {
// Offset of the plugin data pointer inside an atomic.
extern s32 lbl_8042CF48;
}

#define ATOMIC_12F_DATA(atomic) (*(Atomic12FPluginData**)((u8*)(atomic) + lbl_8042CF48))

#endif
