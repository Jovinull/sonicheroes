#include "types.h"

// TObjS13CloudPtcl::Move (the PS2 build's name): after the particle's common
// move (fn_80061CD8), a cloud particle fades in by 5 a frame up to its most
// alpha over its first 60 frames, keeps it for its life, then fades out by 5 a
// frame and ends once clear; it counts its frames.

struct PARTICLE_INSTANCE {
	u8 unk00[0xA];
	s16 frame; // 0x0A
	u8 unk0C[0x4];
	u32 color; // 0x10
};

struct TObjS13CloudPtcl {
	u8 unk00[0xB4];
	u8 maxAlpha; // 0xB4
	u8 unkB5;
	s16 life; // 0xB6
};

extern "C" s32 fn_80061CD8(TObjS13CloudPtcl* self, PARTICLE_INSTANCE* instance);

extern "C" s32 Move__16TObjS13CloudPtclFP17PARTICLE_INSTANCE(
    TObjS13CloudPtcl* self, PARTICLE_INSTANCE* instance)
{
	if (fn_80061CD8(self, instance) == 0) {
		return 0;
	}
	if (instance->frame < 0x3C) {
		u8 alpha = (instance->color & 0xFF000000) >> 24;

		if (alpha < self->maxAlpha) {
			if (alpha + 5 >= self->maxAlpha) {
				instance->color = (self->maxAlpha << 24) | (instance->color & 0xFFFFFF);
			} else {
				instance->color = (instance->color & 0xFFFFFF) | ((alpha + 5) << 24);
			}
		}
	} else if (instance->frame > self->life + 0x3C) {
		s32 alpha = ((instance->color & 0xFF000000) >> 24) - 5;

		if (alpha <= 0) {
			instance->color = instance->color & 0xFFFFFF;
			return 0;
		}
		instance->color = (instance->color & 0xFFFFFF) | (alpha << 24);
	}
	instance->frame++;
	return 1;
}
