#include "types.h"

// Puts the object into state 1 and loads the pair of values that go with the
// stage it is showing.
//
// The translation unit is the single function fn_1_4294, .text 0x4294 to
// 0x42D8. The table at .rodata 0xC4 is left to the module and only referenced
// here, so this unit emits no data of its own.
//
// It is a leaf: no prologue, no frame.

typedef struct StageValues {
	s32 first;  // 0x00
	s32 second; // 0x04
} StageValues;

typedef struct Stage {
	u8 unk0[0x2C];  // 0x00
	s32 state;      // 0x2C
	u8 unk30[0x30]; // 0x30
	s32 unk60;      // 0x60
	s32 unk64;      // 0x64
	s32 unk68;      // 0x68
	u8 unk6C[0x24]; // 0x6C
	s32 index;      // 0x90
} Stage;

extern "C" const StageValues lbl_1_rodata_C4[];

extern "C" void fn_1_4294(Stage* stage)
{
	stage->state = 1;
	stage->unk60 = stage->index + 6;
	stage->unk64 = lbl_1_rodata_C4[stage->index].first;
	stage->unk68 = lbl_1_rodata_C4[stage->index].second;
}
