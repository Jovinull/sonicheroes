// Chooses the render callback and state mask of an object's plugin record (HYPOTHESIS: a
// GameCube instancing/lighting setup keyed on the record's feature flags at 0xA0; names inferred):
// clears the six callback slots at 0x24-0x38, stores in 0x28 the callback for the first matching
// feature group (with a variant when flag 0x01000000 is set) and builds the state mask at 0x44
// from that choice plus two prioritised flag groups and flag 0x10.
#include "types.h"

typedef void (*Callback801FD4E4)(void);

struct Record801FD4E4 {
	u8 pad0[0x24];
	Callback801FD4E4 callbacks[6]; // 0x24 (0x28 is the one chosen here)
	u8 pad3C[0x44 - 0x3C];
	u32 stateMask; // 0x44
	u8 pad48[0xA0 - 0x48];
	u32 featureFlags; // 0xA0
};

extern "C" {
extern s32 lbl_8042CF48; // Plugin offset of the record (HYPOTHESIS)

void fn_801FE390(void);
void fn_801FDFCC(void);
void fn_801FEB1C(void);
void fn_801FE754(void);
void fn_80200414(void);
void fn_801FFFD0(void);
void fn_801FFB68(void);
void fn_801FF6FC(void);
void fn_801FF300(void);
void fn_801FEF28(void);

void fn_801FD4E4(void* object)
{
	Record801FD4E4* record = *(Record801FD4E4**)((u8*)object + lbl_8042CF48);
	u32 mask               = 0;

	record->callbacks[0] = 0;
	record->callbacks[1] = 0;
	record->callbacks[2] = 0;
	record->callbacks[3] = 0;
	record->callbacks[4] = 0;
	record->callbacks[5] = 0;

	if (record->featureFlags & 0x8) {
		if (record->featureFlags & 0x01000000) {
			mask |= 0x2;
			record->callbacks[1] = fn_801FE390;
		} else {
			mask |= 0x1;
			record->callbacks[1] = fn_801FDFCC;
		}
	} else if (record->featureFlags & 0x8000) {
		if (record->featureFlags & 0x01000000) {
			mask |= 0x8;
			record->callbacks[1] = fn_801FEB1C;
		} else {
			mask |= 0x4;
			record->callbacks[1] = fn_801FE754;
		}
	} else if (record->featureFlags & 0x20) {
		if (record->featureFlags & 0x4) {
			if (record->featureFlags & 0x01000000) {
				mask |= 0x200;
				record->callbacks[1] = fn_80200414;
			} else {
				mask |= 0x100;
				record->callbacks[1] = fn_801FFFD0;
			}
		} else if (record->featureFlags & 0x01000000) {
			mask |= 0x80;
			record->callbacks[1] = fn_801FFB68;
		} else {
			mask |= 0x40;
			record->callbacks[1] = fn_801FF6FC;
		}
	} else if (record->featureFlags & 0x4) {
		if (record->featureFlags & 0x01000000) {
			mask |= 0x20;
			record->callbacks[1] = fn_801FF300;
		} else {
			mask |= 0x10;
			record->callbacks[1] = fn_801FEF28;
		}
	} else if (record->featureFlags & 0x01000000) {
		mask |= 0x8;
		record->callbacks[1] = fn_801FEB1C;
	} else {
		mask |= 0x4;
		record->callbacks[1] = fn_801FE754;
	}

	if (record->featureFlags & 0x80) {
		mask |= 0x100000;
	} else if (record->featureFlags & 0x100) {
		mask |= 0x200000;
	} else if (record->featureFlags & 0x80000) {
		mask |= 0x400000;
	} else if (record->featureFlags & 0x100000) {
		mask |= 0x800000;
	}

	if (record->featureFlags & 0x2) {
		mask |= 0x10000;
	} else if (record->featureFlags & 0x40) {
		mask |= 0x20000;
	} else if (record->featureFlags & 0x40000) {
		mask |= 0x40000;
	} else {
		mask |= 0x80000;
	}

	if (record->featureFlags & 0x10) {
		mask |= 0x1000000;
	}
	record->stateMask = mask;
}
}
