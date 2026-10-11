#include "types.h"

// The checkpoint star's opaque draw (checkpointStarDispOpaque here; the
// fading one is rel/checkpoint_star_disp.cpp): while the game is not paused and
// the star is fully shown (alpha 1 or more), it lights the scene with the
// regular light and draws the star with alpha 0xFF on each atomic
// (checkpointBind).

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

typedef struct CheckpointMaterial {
	u8 unk00[0x4]; // 0x00
	RwRGBA color;  // 0x04
} CheckpointMaterial;

typedef struct CheckpointStar {
	s32 state;       // 0x00
	u8 unk04[0x2C];  // 0x04
	RpClump* clump;  // 0x30
	RpClump* effect; // 0x34
	u8 unk38[0x40];  // 0x38
	f32 alpha;       // 0x78
} CheckpointStar;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" u8* lbl_8042C180;
extern "C" const f32 checkpointZero[1];
extern "C" const f32 checkpointOne[1];
extern "C" const f32 checkpointByteScale[1];
extern "C" CheckpointMaterial* checkpointStarEffectMaterial;
extern "C" RpAtomic* checkpointBind(RpAtomic* atomic, void* data);
extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void checkpointStarDispOpaque(CheckpointStar* star)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		if (star->alpha >= checkpointOne[0]) {
			lbl_802D5E80.SetCurrentNum(0x10);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			u8 alpha = 0xFF;
			fn_8014FFBC(star->clump, checkpointBind, &alpha);
			fn_8014FF2C(star->clump);
		}
	}
}
