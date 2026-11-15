#include "game/matrix.h"

// Places the interpolated model (lbl_8042C418) at the object lbl_8042C41C: with the current camera
// (lbl_8042C9A4 +0x0) run through fn_8019CC00, fn_8019CC28 and fn_8016EE88 before and after, the
// model's frame matrix (fn_801733F4 of fn_802043AC) becomes the object's matrix (+0x4C), scaled by
// lbl_802541A8, moved by lbl_8023A548 (with X replaced by lbl_8042DE84 in mode 1) and scaled by
// lbl_802541B4, and the frame is updated (fn_8017348C). HYPOTHESIS: RwMatrixScale and
// RwMatrixTranslate (combine 2 = post-concatenate); the camera calls are UNKNOWN.

struct Object800C0EA0 {
	u8 pad0[0x4C];
	RwMatrixTag matrix; // 0x4C
};

extern "C" {
extern void** lbl_8042C9A4;
extern Object800C0EA0* lbl_8042C41C;
extern void* lbl_8042C418;
extern const RwV3d lbl_802541A8;
extern const RwV3d lbl_802541B4;
extern const RwV3d lbl_8023A548;
extern const f32 lbl_8042DE84;
void fn_8019CC00(void* camera);
void fn_8019CC28(void* camera);
void fn_8016EE88(void* camera);
void* fn_802043AC(void* anim);
RwMatrixTag* fn_801733F4(void* frame);
void fn_8017348C(void* frame);
RwMatrixTag* fn_80195E44(RwMatrixTag* matrix, const RwV3d* scale, s32 combine);
RwMatrixTag* fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
}

extern "C" void fn_800C0EA0(s32 mode)
{
	if (lbl_8042C41C == NULL || lbl_8042C418 == NULL) {
		return;
	}
	void* camera = *lbl_8042C9A4;
	fn_8019CC00(camera);
	fn_8019CC28(camera);
	fn_8016EE88(camera);
	Object800C0EA0* object = lbl_8042C41C;
	void* frame            = fn_802043AC(lbl_8042C418);
	RwMatrixTag* matrix    = fn_801733F4(frame);
	*matrix                = object->matrix;
	fn_80195E44(matrix, &lbl_802541A8, 2);
	RwV3d offset = lbl_8023A548;
	if (mode == 1) {
		offset.x = lbl_8042DE84;
	}
	fn_80196050(matrix, &offset, 2);
	fn_80195E44(matrix, &lbl_802541B4, 2);
	fn_8017348C(frame);
	camera = *lbl_8042C9A4;
	fn_8019CC00(camera);
	fn_8019CC28(camera);
	fn_8016EE88(camera);
}
