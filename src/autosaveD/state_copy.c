#include "types.h"

typedef struct Pair {
	u32 first;
	u32 second;
} Pair;

typedef struct AutosaveState {
	u32 unk_0x0;
	u32 unk_0x4;
	u32 unk_0x8;
	u32 unk_0xC;
	u32 unk_0x10;
	Pair unk_0x14;
	u32 unk_0x1C;
	Pair unk_0x20;
	Pair unk_0x28;
	Pair unk_0x30;
	u32 unk_0x38;
	u32 unk_0x3C;
	u32 unk_0x40;
} AutosaveState;

static inline void copy_pair(Pair* destination, const volatile Pair* source)
{
	u32 first  = source->first;
	u32 second = source->second;

	destination->first  = first;
	destination->second = second;
}

extern "C" void fn_2_3D64(AutosaveState* destination, const AutosaveState* source)
{
	destination->unk_0x0  = source->unk_0x0;
	destination->unk_0x4  = source->unk_0x4;
	destination->unk_0x8  = source->unk_0x8;
	destination->unk_0xC  = source->unk_0xC;
	destination->unk_0x10 = source->unk_0x10;
	copy_pair(&destination->unk_0x14, &source->unk_0x14);
	destination->unk_0x1C = source->unk_0x1C;
	copy_pair(&destination->unk_0x20, &source->unk_0x20);
	copy_pair(&destination->unk_0x28, &source->unk_0x28);
	copy_pair(&destination->unk_0x30, &source->unk_0x30);
	destination->unk_0x38 = source->unk_0x38;
	destination->unk_0x3C = source->unk_0x3C;
	destination->unk_0x40 = source->unk_0x40;
}
