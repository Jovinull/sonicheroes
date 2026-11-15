// Resolves a matrix by space id (HYPOTHESIS): ids from 0x10 select a frame of the frame table at
// engine + lbl_8042C848 (count, frames), whose LTM is inverted into out (fn_80195B5C) or, with a
// parent, multiplied by the parent into out (fn_80195674); a missing frame yields the parent, or
// the identity in out. Id 3 is the global matrix lbl_803EDB8C (multiplied by the parent when one is
// given), id 2 is the parent itself. Returns the resolved matrix, or null.
// NonMatching: retail returns the global matrix through r0 (addi r0; mr r3, r0), one instruction
// more than this source's direct return, which shifts the later branch targets (23 words). A local,
// parameter reuse, const and wrapper-struct declarations of lbl_803EDB8C do not reproduce it.
#include "game/rw_engine.h"

// Frame table kept in the engine globals at lbl_8042C848.
struct FrameTable8014543C {
	u32 count;        // 0x0
	RwFrame** frames; // 0x4
};

#define SPACE_8014543C_PARENT      2
#define SPACE_8014543C_GLOBAL      3
#define SPACE_8014543C_FIRST_FRAME 0x10

extern "C" {
extern s32 lbl_8042C848;
extern RwMatrix lbl_803EDB8C;
extern const f32 lbl_8042F288; // 1.0f
extern const f32 lbl_8042F28C; // 0.0f
// HYPOTHESIS: RwFrameGetLTM, RwMatrixInvert and RwMatrixMultiply.
RwMatrix* fn_8019E8EC(RwFrame* frame);
RwMatrix* fn_80195B5C(RwMatrix* dst, const RwMatrix* src);
RwMatrix* fn_80195674(RwMatrix* dst, const RwMatrix* a, const RwMatrix* b);

RwMatrix* fn_8014543C(s32 space, RwMatrix* parent, RwMatrix* out)
{
	if (space >= SPACE_8014543C_FIRST_FRAME) {
		FrameTable8014543C* table = (FrameTable8014543C*)((u8*)lbl_8042C9A4 + lbl_8042C848);
		u32 count                 = table->count;
		RwFrame** frames          = table->frames;
		u32 index                 = space - SPACE_8014543C_FIRST_FRAME;
		if (index < count && frames != 0 && frames[index] != 0) {
			if (parent != 0) {
				RwMatrix inverse;
				fn_80195B5C(&inverse, fn_8019E8EC(frames[index]));
				fn_80195674(out, parent, &inverse);
			} else {
				fn_80195B5C(out, fn_8019E8EC(frames[index]));
			}
			return out;
		}
		if (parent != 0) {
			return parent;
		}
		RW_MATRIX_SET_IDENTITY(out, lbl_8042F288, lbl_8042F28C);
		return out;
	}
	if (space == SPACE_8014543C_GLOBAL) {
		if (parent != 0) {
			fn_80195674(out, parent, &lbl_803EDB8C);
			return out;
		}
		return &lbl_803EDB8C;
	}
	if (space == SPACE_8014543C_PARENT) {
		if (parent != 0) {
			return parent;
		}
		return 0;
	}
	return 0;
}
}
