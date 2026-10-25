#include "types.h"

// The factory rel/ring_register.cpp puts in the ring group's editor record, the
// same in the twelve stage modules that share the engine core. It allocates
// 0x58 bytes and hands them to the module's constructor (left as assembly and
// named ringObjectCtor here), with the task at lbl_8042C110 as its owner; then
// it sets the rings' three shading values (the middle one is the shade
// rel/scroll_ring_field_init.cpp gives each ring), stage 43 having its own.

// the game state: only the stage is read here
typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" f32 scrollRingParamA;
extern "C" f32 scrollRingShade;
extern "C" f32 scrollRingParamC;
extern "C" const f32 ringCreateStage43A;
extern "C" const f32 ringCreateStage43B;
extern "C" const f32 ringCreateStage43C;
extern "C" const f32 ringCreateDefaultA;
extern "C" const f32 ringCreateDefaultB;
extern "C" const f32 ringCreateDefaultC;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* ringObjectCtor(void* object, void* owner);

extern "C" void ringObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58);

	if (memory != NULL) {
		ringObjectCtor(memory, lbl_8042C110);
	}
	if (lbl_8029C310.stage == 43) {
		scrollRingParamA = ringCreateStage43A;
		scrollRingShade  = ringCreateStage43B;
		scrollRingParamC = ringCreateStage43C;
	} else {
		scrollRingParamA = ringCreateDefaultA;
		scrollRingShade  = ringCreateDefaultB;
		scrollRingParamC = ringCreateDefaultC;
	}
}
