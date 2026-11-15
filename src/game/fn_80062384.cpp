// Destructor of PARTICLE_TASK (name CORROBORATED by the PS2 build, which also shows its
// PARTICLE_MATERIAL base at +0x28; the GameCube symbol keeps its address name because a REL and
// other units call it by that name). It installs the class vtable lbl_80243B38 and its
// PARTICLE_MATERIAL part (+0x2C into it, stored at +0x7C), frees the task's buffer (+0xAC) with
// RwFree, destroys the PARTICLE_MATERIAL and TObject bases and frees the object when flags > 0.
// Returns the object.
#include "types.h"

struct ParticleTask80062384 {
	u8 pad0[0x18];
	void* vtable; // 0x18 (TObject)
	u8 pad1C[0x28 - 0x1C];
	u8 material[0x54];    // 0x28 (PARTICLE_MATERIAL base)
	void* materialVtable; // 0x7C
	u8 pad80[0xAC - 0x80];
	void* buffer; // 0xAC
};

// The RenderWare engine globals: only the free hook is used (+0x138, RwFree).
struct RwEngine80062384 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

struct THeapCtrl;

extern "C" {
extern u8 lbl_80243B38[];
extern RwEngine80062384* lbl_8042C9A4;
extern THeapCtrl* lbl_8042C148;
void __dt__17PARTICLE_MATERIALFv(void* material, s32 flags);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);

ParticleTask80062384* fn_80062384(ParticleTask80062384* task, s16 flags)
{
	if (task != NULL) {
		task->vtable         = lbl_80243B38;
		task->materialVtable = lbl_80243B38 + 0x2C;
		if (task->buffer != NULL) {
			lbl_8042C9A4->rwfree(task->buffer);
			task->buffer = NULL;
		}
		__dt__17PARTICLE_MATERIALFv(task->material, 0);
		__dt__7TObjectFv(task, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, task);
		}
	}
	return task;
}
}
