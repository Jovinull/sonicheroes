// Loads the current world's global lights into GX (HYPOTHESIS: the GameCube world-sector lighting
// setup; names inferred). Walks the world's light list (links at 0x34 of each light) and, for
// every light whose flags match the mask: a directional light (subtype 1) gets the next hardware
// slot of lbl_803EC6B8, its attenuation (plugin data at lbl_8042C940, or 1/0/0 and 1/0/0), a
// distant position against its view-space direction (the LTM at vector transformed by the matrix
// at lbl_803EDB8C), its colour scaled to bytes, and is loaded with its slot bit recorded in the
// state; any other light adds its colour to the state's ambient sum and sets the ambient flag.
// NonMatching: retail keeps the light, slot and list registers one step apart from this source's
// and puts the named colour below the by-value argument copy on the stack (27 words, same
// instructions). Moving the colour declaration, an aggregate initialiser and an RwRGBA cast do
// not change the stack order.
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"
#include "game/object.h"

enum RpLightType8015D8A4 { RP_LIGHT_DIRECTIONAL = 1 };

struct Light8015D8A4 {
	u8 type;         // 0x0
	u8 subType;      // 0x1
	u8 flags;        // 0x2
	u8 privateFlags; // 0x3
	RwFrame* frame;  // 0x4
	u8 pad8[0x18 - 0x8];
	RwRGBAReal color; // 0x18
	u8 pad28[0x34 - 0x28];
	RwLLLink inWorld; // 0x34
};

// Per-light GX attenuation (plugin data at lbl_8042C940).
struct LightAttn8015D8A4 {
	u32 enabled; // 0x0
	f32 a0;      // 0x4
	f32 a1;      // 0x8
	f32 a2;      // 0xC
	f32 k0;      // 0x10
	f32 k1;      // 0x14
	f32 k2;      // 0x18
};

struct World8015D8A4 {
	u8 pad0[0x3C];
	RwLinkList lights; // 0x3C
};

struct LightState8015D8A4 {
	u8 pad0[0xC];
	f32 ambientRed;   // 0xC
	f32 ambientGreen; // 0x10
	f32 ambientBlue;  // 0x14
	u8 pad18[0x1C - 0x18];
	s32 hasAmbient; // 0x1C
	u32 lightMask;  // 0x20
	s32 numLights;  // 0x24
};

extern "C" {
extern s32 lbl_8042C940; // Plugin offset of the light attenuation (HYPOTHESIS)
extern GXLightObj lbl_803EC6B8[8];
extern RwMatrix lbl_803EDB8C; // View matrix used for light directions (HYPOTHESIS)
// .sdata2 constants: 1, 0, the distance of a directional light and the colour scale.
extern f32 lbl_8042F3B0;
extern f32 lbl_8042F3B4;
extern f32 lbl_8042F3B8;
extern f32 lbl_8042F3BC;

// HYPOTHESIS: RwFrameGetLTM, RwV3dTransformVectors and GXInitLightAttn.
RwMatrix* fn_8019E8EC(RwFrame* frame);
RwV3d* fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrix* matrix);
void fn_801F4A70(GXLightObj* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);

void fn_8015D8A4(u8 mask, LightState8015D8A4* state)
{
	World8015D8A4* world = (World8015D8A4*)lbl_8042C9A4->curWorld;
	RwLLLink* cur        = world->lights.link.next;
	RwLLLink* end        = &world->lights.link;

	while (cur != end) {
		Light8015D8A4* light = (Light8015D8A4*)((u8*)cur - 0x34);
		if (light != 0 && (light->flags & mask)) {
			if ((RpLightType8015D8A4)light->subType == RP_LIGHT_DIRECTIONAL) {
				s32 slot = state->numLights;
				RwV3d dir;
				LightAttn8015D8A4* attn;
				GXColor color;

				fn_8019947C(&dir, &fn_8019E8EC(light->frame)->at, 1, &lbl_803EDB8C);
				attn = (LightAttn8015D8A4*)((u8*)light + lbl_8042C940);
				if (attn->enabled == 0) {
					fn_801F4A70(&lbl_803EC6B8[slot], lbl_8042F3B0, lbl_8042F3B4, lbl_8042F3B4,
					    lbl_8042F3B0, lbl_8042F3B4, lbl_8042F3B4);
				} else {
					fn_801F4A70(&lbl_803EC6B8[slot], attn->a0, attn->a1, attn->a2, attn->k0,
					    attn->k1, attn->k2);
				}
				GXInitLightPos(&lbl_803EC6B8[slot], lbl_8042F3B8 * -dir.x, lbl_8042F3B8 * dir.y,
				    lbl_8042F3B8 * -dir.z);
				color.r = lbl_8042F3BC * light->color.red;
				color.g = lbl_8042F3BC * light->color.green;
				color.b = lbl_8042F3BC * light->color.blue;
				color.a = 0;
				GXInitLightColor(&lbl_803EC6B8[slot], color);
				GXLoadLightObjImm(&lbl_803EC6B8[slot], (GXLightID)(1 << slot));
				state->lightMask |= 1 << state->numLights;
				state->numLights++;
			} else {
				state->ambientRed += light->color.red;
				state->ambientGreen += light->color.green;
				state->ambientBlue += light->color.blue;
				state->hasAmbient = 1;
			}
		}
		cur = cur->next;
	}
}
}
