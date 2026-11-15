// Gathers the lights affecting an atomic (HYPOTHESIS: the GameCube atomic lighting setup): clears
// the light accumulator (colour 0, alpha 1), and for a lit geometry in a current world sets the
// ambient state (fn_8015D8A4), advances the engine light frame and walks the world sectors the
// atomic touches; each atomic-lighting light not yet seen this frame whose sphere reaches the
// atomic's world bounding sphere is applied (fn_8015DAC4). A used accumulator has its colour
// clamped to 1. Returns the atomic. Names are inferred from this function only.
// NonMatching: instruction stream matches; retail stores the accumulator through the incoming r4
// and assigns the sector/light loop registers differently (outer list r27/r26, light matrix r29),
// and loads the clamp operands in the opposite registers (35 words). Declaration permutations
// do not reproduce it.
#include "game/rw_engine.h"

struct LightAccum8015CBBC {
	u8 pad0[0xC];
	f32 red;     // 0xC
	f32 green;   // 0x10
	f32 blue;    // 0x14
	f32 alpha;   // 0x18
	s32 used;    // 0x1C
	s32 count20; // 0x20
	s32 value24; // 0x24
};

struct Light8015CBBC {
	RwObject object; // 0x0: flags bit 0 lights atomics
	u8 pad8[0x14 - 0x8];
	f32 radius; // 0x14
	u8 pad18[0x3C - 0x18];
	u16 lightFrame; // 0x3C
};

struct LightTie8015CBBC {
	RwLLLink link;        // 0x0
	Light8015CBBC* light; // 0x8
};

struct Sector8015CBBC {
	u8 pad0[0x48];
	RwLinkList lights; // 0x48
};

struct SectorTie8015CBBC {
	RwLLLink link;          // 0x0
	Sector8015CBBC* sector; // 0x8
};

struct Geometry8015CBBC {
	u8 pad0[0x8];
	u32 flags; // 0x8
};

struct Atomic8015CBBC {
	u8 pad0[0x18];
	Geometry8015CBBC* geometry; // 0x18
	u8 pad1C[0x64 - 0x1C];
	RwLinkList sectors; // 0x64
};

#define RP_GEOMETRY_LIGHT      0x20
#define RP_LIGHT_LIGHT_ATOMICS 0x1

extern "C" {
extern f32 lbl_8042F398; // 0.0f
extern f32 lbl_8042F39C; // 1.0f
void fn_8015D8A4(s32 enable);
// HYPOTHESIS: RwFrameGetLTM and RpAtomicGetWorldBoundingSphere.
RwMatrix* fn_8019E8EC(void* frame);
RwSphere* fn_8014F9C4(Atomic8015CBBC* atomic);
void fn_8015DAC4(Light8015CBBC* light, LightAccum8015CBBC* accum);

Atomic8015CBBC* fn_8015CBBC(Atomic8015CBBC* atomic, LightAccum8015CBBC* accum)
{
	RwLLLink* cur;
	RwLLLink* lightLink;
	RwMatrix* ltm;
	RwSphere* sphere;
	u32 geometryFlags;

	geometryFlags = atomic->geometry->flags;

	accum->count20 = 0;
	accum->red     = lbl_8042F398;
	accum->green   = lbl_8042F398;
	accum->blue    = lbl_8042F398;
	accum->alpha   = lbl_8042F39C;
	accum->used    = 0;
	accum->value24 = 0;

	if ((geometryFlags & RP_GEOMETRY_LIGHT) && lbl_8042C9A4->curWorld != 0) {
		fn_8015D8A4(1);
		lbl_8042C9A4->lightFrame++;
		for (cur = atomic->sectors.link.next; cur != &atomic->sectors.link; cur = cur->next) {
			Sector8015CBBC* sector = ((SectorTie8015CBBC*)cur)->sector;
			for (lightLink = sector->lights.link.next; lightLink != &sector->lights.link;
			    lightLink  = lightLink->next) {
				Light8015CBBC* light = ((LightTie8015CBBC*)lightLink)->light;
				if (light != 0 && light->lightFrame != lbl_8042C9A4->lightFrame
				    && (light->object.flags & RP_LIGHT_LIGHT_ATOMICS)) {
					f32 dx;
					f32 dy;
					f32 dz;
					f32 reach;

					light->lightFrame = lbl_8042C9A4->lightFrame;
					ltm               = fn_8019E8EC(light->object.parent);
					sphere            = fn_8014F9C4(atomic);
					dx                = sphere->center.x - ltm->pos.x;
					dy                = sphere->center.y - ltm->pos.y;
					dz                = sphere->center.z - ltm->pos.z;
					reach             = sphere->radius + light->radius;
					if (dx * dx + dy * dy + dz * dz < reach * reach) {
						fn_8015DAC4(((LightTie8015CBBC*)lightLink)->light, accum);
					}
				}
			}
		}
	}

	if (accum->used != 0) {
		if (accum->red > lbl_8042F39C) {
			accum->red = lbl_8042F39C;
		}
		if (accum->green > lbl_8042F39C) {
			accum->green = lbl_8042F39C;
		}
		if (accum->blue > lbl_8042F39C) {
			accum->blue = lbl_8042F39C;
		}
	}
	return atomic;
}
}
