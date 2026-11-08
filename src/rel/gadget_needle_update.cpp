#include "types.h"

// TEnemyGadgetNeedle::Update (the PS2 build's name): the needle gadget keeps its
// body and its needles on the searcher's jet frame, scaled by how far they have
// grown; the sound comes from the body's position. Growing (mode 2) the needles
// gain a step a frame up to their full size, which starts the extend sound and
// settles the mode on 3; retracting (mode 4) the retract sound starts when they
// are full size, and they shrink down to their smallest, which settles it on 1.
//
// The full-size limit is read through a volatile pointer: the retail reloads it
// for the store after the compare. The minimum is not, the retail keeps it.

#include "src/rel/searcher.inc"

typedef struct GadgetNeedle {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	f32 growth;       // 0x3C
	RpClump* needles; // 0x40
} GadgetNeedle;

typedef struct RwMatrixTag {
	u8 unk00[0x30];
	RwV3d pos; // 0x30
} RwMatrixTag;

extern "C" void* lbl_8042C388;
extern "C" const f32 gadgetBombDragY;
extern "C" const f32 gadgetBombScaleXZ;
extern "C" const f32 gadgetOne;
extern "C" const RwV3d needleSoundPos;
extern "C" const RwV3d needleBodyScale;
extern "C" const RwV3d needleScale;

extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019ECCC(RwFrame* frame, RwMatrixTag* matrix, s32 combine);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void Update__18TEnemyGadgetNeedleFv(GadgetNeedle* gadget)
{
	RwV3d soundPos = needleSoundPos;
	const volatile f32* limit;
	const f32* floorLimit;
	RwMatrixTag* matrix;
	RwFrame* frame;

	frame = gadget->base.pClump->frame;
	if (frame != NULL) {
		matrix = fn_8019E8EC(((Searcher*)gadget->enemy)->jetFrame);
		if (matrix != NULL) {
			RwV3d scale = needleBodyScale;
			f32 growth  = gadget->growth;

			scale.x = growth;
			scale.y = growth;
			scale.z = growth;
			fn_8019EC30(frame, &scale, 0);
			fn_8019ECCC(frame, matrix, 2);
			soundPos = matrix->pos;
		}
	}
	if (gadget->needles != NULL) {
		RwFrame* frame2      = gadget->needles->frame;
		RwMatrixTag* matrix2 = fn_8019E8EC(((Searcher*)gadget->enemy)->jetFrame);
		frame                = frame2;
		matrix               = matrix2;
		if (matrix != NULL) {
			RwV3d scale = needleScale;
			f32 growth  = gadget->growth;

			scale.x = growth;
			scale.y = growth;
			scale.z = growth;
			fn_8019EC30(frame, &scale, 0);
			fn_8019ECCC(frame, matrix, 2);
		}
	}
	switch (gadget->base.gmode) {
		case 2:
			gadget->growth = gadget->growth + gadgetBombDragY;
			if (gadget->growth > *(limit = &gadgetOne)) {
				gadget->growth     = *limit;
				gadget->base.gmode = (TEnemyGadget::eGadgetMode)3;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4003, &soundPos, NULL, 1, 0, 0);
				}
			}
		case 3:
		case 1:
			break;
		case 4:
			if (gadgetOne == gadget->growth && lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4004, &soundPos, NULL, 1, 0, 0);
			}
			gadget->growth = gadget->growth - gadgetBombDragY;
			if (gadget->growth < *(floorLimit = &gadgetBombScaleXZ)) {
				gadget->growth     = *floorLimit;
				gadget->base.gmode = (TEnemyGadget::eGadgetMode)1;
			}
			break;
	}
}
