// Gathers the lighting of a world for a light record (HYPOTHESIS: the world light pass): clears
// the record (colour to the .sdata2 constant lbl_8042F3A8, scale to lbl_8042F3AC, HYPOTHESIS 0.0f
// and 1.0f) and, when the current world is lit (flag 0x20 at 0x8), runs fn_8015D8A4(2), advances
// the engine light frame and adds every enabled light (flag 0x2 of byte 0x2) of the world's light
// list at 0x48 with fn_8015DAC4; an over-bright record (word 0x1C) is then clamped to 1.0f per
// channel. Returns the world. Field names are inferred from this function only.
// NonMatching: in the clamp the retail code keeps the channel in f1 and the limit in f0; ours swaps
// them (12 words differ).
#include "game/rw_engine.h"

struct Light8015D4C4 {
	u8 pad0[0x2];
	u8 flags; // 0x2
};

struct LightLink8015D4C4 {
	RwLLLink link;        // 0x0
	Light8015D4C4* light; // 0x8
};

struct World8015D4C4 {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x48 - 0xC];
	RwLinkList lights; // 0x48
};

struct Lighting8015D4C4 {
	u8 pad0[0xC];
	f32 red;      // 0xC
	f32 green;    // 0x10
	f32 blue;     // 0x14
	f32 scale;    // 0x18
	s32 overflow; // 0x1C
	s32 word20;   // 0x20
	s32 word24;   // 0x24
};

extern "C" {
extern f32 lbl_8042F3A8;
extern f32 lbl_8042F3AC;

void fn_8015D8A4(s32 mode);
void fn_8015DAC4(Light8015D4C4* light, Lighting8015D4C4* lighting);

World8015D4C4* fn_8015D4C4(World8015D4C4* world, Lighting8015D4C4* lighting)
{
	lighting->word20   = 0;
	lighting->red      = lbl_8042F3A8;
	lighting->green    = lbl_8042F3A8;
	lighting->blue     = lbl_8042F3A8;
	lighting->scale    = lbl_8042F3AC;
	lighting->overflow = 0;
	lighting->word24   = 0;

	if (((World8015D4C4*)lbl_8042C9A4->curWorld)->flags & 0x20) {
		RwLLLink* cur;
		RwLLLink* end;

		fn_8015D8A4(2);
		lbl_8042C9A4->lightFrame++;
		end = &world->lights.link;
		for (cur = world->lights.link.next; cur != end; cur = cur->next) {
			Light8015D4C4* light = ((LightLink8015D4C4*)cur)->light;
			if (light && (light->flags & 0x2)) {
				fn_8015DAC4(light, lighting);
			}
		}
	}

	if (lighting->overflow) {
		if (lighting->red > lbl_8042F3AC) {
			lighting->red = lbl_8042F3AC;
		}
		if (lighting->green > lbl_8042F3AC) {
			lighting->green = lbl_8042F3AC;
		}
		if (lighting->blue > lbl_8042F3AC) {
			lighting->blue = lbl_8042F3AC;
		}
	}
	return world;
}
}
