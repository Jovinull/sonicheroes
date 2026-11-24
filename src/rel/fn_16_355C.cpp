#include "types.h"

typedef struct Handle {
	u8 unk0[0x18]; // 0x00
	u32 flags;     // 0x18
} Handle;

typedef struct Object {
	u8 unk0[0x28];  // 0x00
	Handle* handle; // 0x28
	u8 unk2C[0x90]; // 0x2C
	s32 mode;       // 0xBC
	u8 unkC0[0x30]; // 0xC0
	void* drawA;    // 0xF0
	u8 unkF4[0x4];  // 0xF4
	void* drawB;    // 0xF8
} Object;

extern "C" s32* RpAtomicMCCGetCustomRenderCallBack(void* draw);

extern "C" u32 fn_16_170C(Handle** h);

extern "C" void fn_16_355C(Object* object, s32 mode)
{
	s32* slot;

	object->mode = mode;

	switch (object->mode) {
		case 0:
			slot  = RpAtomicMCCGetCustomRenderCallBack(object->drawA);
			*slot = fn_16_170C(&object->handle) + 4;
			slot  = RpAtomicMCCGetCustomRenderCallBack(object->drawB);
			*slot = fn_16_170C(&object->handle) + 4;
			break;
		case 1:
		case 2:
			slot  = RpAtomicMCCGetCustomRenderCallBack(object->drawA);
			*slot = 0x10;
			slot  = RpAtomicMCCGetCustomRenderCallBack(object->drawB);
			*slot = 0x10;
			break;
	}
}
