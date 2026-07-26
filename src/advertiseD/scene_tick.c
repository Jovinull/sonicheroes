#include "types.h"

// The module's main per-frame step: refresh the five slots, then run whichever
// of the fifteen states it is in.
//
// The translation unit runs from fn_1_354C at 0x354C to the end of fn_1_358C
// at 0x368C, and owns .data 0x9E8 to 0xA24. That block is not written here: it
// is the jump table the compiler builds for the switch, and nothing else reads
// it.
//
// The order the cases are written in is read off that table rather than
// guessed. It maps state minus five to an offset inside the function, and the
// offsets put the bodies in the order 5, 6, 7, 8, 12, 13, 14, 15, then 9, 10
// and 11 sharing one, then 19, 16, 17. State 18 is absent and falls through to
// doing nothing.

typedef struct Scene {
	u8 unk0[0x28];  // 0x00
	s32 state;      // 0x28
	u8 unk2C[0x54]; // 0x2C
	s32 unk80;      // 0x80
} Scene;

extern "C" void fn_800A8264(Scene* scene);
extern "C" void fn_1_131C(Scene* scene, s32 index);
extern "C" void fn_1_2164(Scene* scene);
extern "C" void fn_1_2234(Scene* scene);
extern "C" void fn_1_2390(Scene* scene);
extern "C" void fn_1_24FC(Scene* scene);
extern "C" void fn_1_2688(Scene* scene);
extern "C" void fn_1_2760(Scene* scene);
extern "C" void fn_1_27C4(Scene* scene);
extern "C" void fn_1_2884(Scene* scene);
extern "C" void fn_1_293C(Scene* scene);
extern "C" void fn_1_2AC8(Scene* scene);
extern "C" void fn_1_2F40(Scene* scene);
extern "C" void fn_1_30A8(Scene* scene);

extern "C" void fn_1_354C(Scene* scene)
{
	if (scene->unk80 != 0 || (scene->state != 5 && scene->state != 11)) {
		fn_800A8264(scene);
	}
}

extern "C" void fn_1_358C(Scene* scene)
{
	s32 i;

	for (i = 0; i != 5; i++) {
		fn_1_131C(scene, i);
	}

	switch (scene->state) {
		case 5:
			fn_1_30A8(scene);
			break;
		case 6:
			fn_1_2F40(scene);
			break;
		case 7:
			fn_1_2AC8(scene);
			break;
		case 8:
			fn_1_293C(scene);
			break;
		case 12:
			fn_1_2884(scene);
			break;
		case 13:
			fn_1_27C4(scene);
			break;
		case 14:
			fn_1_2760(scene);
			break;
		case 15:
			fn_1_2688(scene);
			break;
		case 9:
		case 10:
		case 11:
			fn_1_24FC(scene);
			break;
		case 19:
			fn_1_2390(scene);
			break;
		case 16:
			fn_1_2234(scene);
			break;
		case 17:
			fn_1_2164(scene);
			break;
	}
}
