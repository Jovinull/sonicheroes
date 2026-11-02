#include "types.h"

// The capture enemy's field reset (captureReset here), the same in the seven
// stage modules that carry the capture: no anchors, parts, icons, motion or
// held player, every shadow spot and the ground normal at the origin, the
// spin and pulse stopped, the bubble timer at ten with no bubbles (all
// sixteen cleared as captureBubbleInit does), and the enemy active and shown.

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
	u8 unk000[0x240];
	void* motion;    // 0x240
	void* paralysis; // 0x244
	s32 mode;        // 0x248
	u8 unk24C[0x1C];
	void* anchors[3]; // 0x268
	s32 found;        // 0x274
	s32 player;       // 0x278
	f32 rate;         // 0x27C
	s32 caught;       // 0x280
	s32 angle;        // 0x284
	f32 pulse;        // 0x288
	s32 spin;         // 0x28C
	u8 unk290[0x4];
	f32 swayX; // 0x294
	f32 swayZ; // 0x298
	u8 unk29C[0x18];
	s32 homeId; // 0x2B4
	u8 unk2B8[0x1C];
	s32 unk2D4;                // 0x2D4
	void* parts[3];            // 0x2D8
	void* shine;               // 0x2E4
	void* lastPart;            // 0x2E8
	void* lastAnchor;          // 0x2EC
	void* lifeIcon;            // 0x2F0
	void* searchIcon;          // 0x2F4
	RwV3d shadows[3];          // 0x2F8
	RwV3d ground;              // 0x31C
	s32 timer;                 // 0x328
	s32 count;                 // 0x32C
	CaptureBubble bubbles[16]; // 0x330
	s32 catchKind;             // 0x570
	s32 active;                // 0x574
	s32 shown;                 // 0x578
} Capture;

extern "C" const f32 captureZero;
extern "C" const f32 captureBubbleSink;
extern "C" const f32 captureRiseSpeed;
extern "C" const f32 captureDefaultRate;

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

extern "C" void captureReset(Capture* object)
{
	s32 i;

	object->anchors[0]   = NULL;
	object->anchors[1]   = NULL;
	object->anchors[2]   = NULL;
	object->shine        = NULL;
	object->shadows[0].x = object->shadows[0].y = object->shadows[0].z = captureZero;
	object->shadows[1].x = object->shadows[1].y = object->shadows[1].z = captureZero;
	object->shadows[2].x = object->shadows[2].y = object->shadows[2].z = captureZero;
	object->ground.x = object->ground.y = object->ground.z = captureZero;
	object->found                                          = -1;
	object->rate                                           = captureDefaultRate;
	object->caught                                         = 0;
	object->parts[0]                                       = NULL;
	object->parts[1]                                       = NULL;
	object->parts[2]                                       = NULL;
	object->angle                                          = 0;
	object->pulse                                          = captureZero;
	object->spin                                           = 0;
	object->timer                                          = 10;
	object->count                                          = 0;
	for (i = 0; i < 16; i++) {
		captureBubbleClear(&object->bubbles[i]);
	}
	object->swayX = object->swayZ = captureZero;
	object->lifeIcon              = NULL;
	object->searchIcon            = NULL;
	object->paralysis             = NULL;
	object->catchKind             = 0;
	object->motion                = NULL;
	object->homeId                = 0;
	object->mode                  = 0;
	object->unk2D4                = 0;
	object->active                = 1;
	object->shown                 = 1;
	object->lastPart              = NULL;
	object->lastAnchor            = NULL;
	object->player                = -1;
}
