// Blends an object's target matrix towards a key matrix (HYPOTHESIS: a key-frame cursor step):
// the target's position, right and up rows become base + (key - base) * t, using the base matrix
// held at +0xC of the object, then the target matrix is re-orthonormalised (fn_8019565C) and its
// frame updated (fn_8017348C), and the object's dirty word at +0x8 is cleared. Returns the
// object. Names are inferred from this function only.
// NonMatching: retail loads the base x before the key x in the first row (2 words: the two loads
// are swapped). Operand and argument order variants do not reproduce it.
#include "game/object.h"

struct Target80201C78 {
	u8 pad0[0xC];
	RwMatrix matrix; // 0xC
};

struct Blend80201C78 {
	u8 pad0[0x4];
	Target80201C78* target; // 0x4
	s32 dirty;              // 0x8
	RwMatrix base;          // 0xC
};

extern "C" {
// HYPOTHESIS: RwMatrixOrthoNormalize-style fix-up and the frame update.
void fn_8019565C(RwMatrix* matrix);
void fn_8017348C(Target80201C78* target);
}

// out = base + (key - base) * t, as the RenderWare vector macros expand it.
static inline void Blend80201C78Row(RwV3d* out, const RwV3d* key, const RwV3d* base, f32 t)
{
	out->x = key->x - base->x;
	out->y = key->y - base->y;
	out->z = key->z - base->z;
	out->x = out->x * t;
	out->y = out->y * t;
	out->z = out->z * t;
	out->x = out->x + base->x;
	out->y = out->y + base->y;
	out->z = out->z + base->z;
}

extern "C" {
Blend80201C78* fn_80201C78(Blend80201C78* blend, const RwMatrix* key, f32 t)
{
	Blend80201C78Row(&blend->target->matrix.pos, &key->pos, &blend->base.pos, t);
	Blend80201C78Row(&blend->target->matrix.right, &key->right, &blend->base.right, t);
	Blend80201C78Row(&blend->target->matrix.up, &key->up, &blend->base.up, t);
	fn_8019565C(&blend->target->matrix);
	fn_8017348C(blend->target);
	blend->dirty = 0;
	return blend;
}
}
