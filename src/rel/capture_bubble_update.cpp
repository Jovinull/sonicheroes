#include "types.h"

// The capture enemy's bubbles (captureBubbleUpdate here), the same in the
// seven stage modules that carry the capture. While active, every ten frames
// a new bubble (up to sixteen) starts at the enemy, cleared as
// captureBubbleInit does, with its top 40 below; every bubble follows the
// enemy across and moves as captureBubbleMove does; the ones that sank past
// their top are replaced by the last one; and the enemy's bubble sound
// (0x4012) plays.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureBubble {
	RwV3d pos;   // 0x00
	RwV3d speed; // 0x0C
	f32 scale;   // 0x18
	f32 grow;    // 0x1C
	f32 top;     // 0x20
} CaptureBubble; // 0x24

typedef struct Capture {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x1DC];
	s32 timer;                 // 0x328
	s32 count;                 // 0x32C
	CaptureBubble bubbles[16]; // 0x330
	u8 unk570[0x4];
	s32 active; // 0x574
} Capture;

extern "C" void* lbl_8042C388;
extern "C" const f32 captureZero;
extern "C" const f32 captureBubbleSink;
extern "C" const f32 captureRiseSpeed;
extern "C" const f32 captureSearchDrop;
extern "C" const f32 captureBubbleMax;

extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

// captureBubbleInit (rel/capture_bubble_init.cpp), inlined.
static inline void captureBubbleClear(CaptureBubble* bubble)
{
	bubble->pos.x = bubble->pos.y = bubble->pos.z = captureZero;
	bubble->speed.x = bubble->speed.z = captureZero;
	bubble->speed.y                   = captureBubbleSink;
	bubble->scale                     = captureZero;
	bubble->grow                      = captureRiseSpeed;
	bubble->top                       = captureZero;
}

// captureBubbleMove (rel/capture_bubble_move.cpp), inlined.
static inline void captureBubbleStep(CaptureBubble* bubble)
{
	bubble->pos.x += bubble->speed.x;
	bubble->pos.y += bubble->speed.y;
	bubble->pos.z += bubble->speed.z;
	bubble->scale += bubble->grow;
	if (bubble->scale > captureBubbleMax) {
		bubble->scale = *(volatile const f32*)&captureBubbleMax;
	}
}

extern "C" void captureBubbleUpdate(Capture* object)
{
	s32 i;
	s32 j;

	if (object->active == 0) {
		return;
	}
	if (--object->timer < 0) {
		object->timer = 10;
		if (object->count < 16) {
			captureBubbleClear(&object->bubbles[object->count]);
			{
				CaptureBubble* bubble = &object->bubbles[object->count];

				bubble->pos.x = object->pos.x;
				bubble->pos.y = object->pos.y;
				bubble->pos.z = object->pos.z;
			}
			object->bubbles[object->count].top = object->pos.y - captureSearchDrop;
			object->count++;
		}
	}
	for (i = 0; i < object->count; i++) {
		object->bubbles[i].pos.x = object->pos.x;
		object->bubbles[i].pos.z = object->pos.z;
		captureBubbleStep(&object->bubbles[i]);
	}
	for (j = 0; j < object->count;) {
		if (object->bubbles[j].pos.y >= object->bubbles[j].top) {
			j++;
		} else {
			object->bubbles[j] = object->bubbles[object->count - 1];
			object->count--;
		}
	}
	if (lbl_8042C388 != NULL) {
		fn_800B4A38(lbl_8042C388, 0x4012, &object->pos, object, 3, 0, 2);
	}
}
