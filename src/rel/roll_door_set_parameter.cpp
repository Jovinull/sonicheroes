#include "types.h"

// TObjRolldoor::SetParameter (the PS2 build's name): the door takes its
// position and angles from its placement, and from the placement's
// parameters its push speed (plus a base), its turn (scaled into an angle)
// and its push time.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct RollDoorParams {
	f32 speed; // 0x00
	f32 turn;  // 0x04
	s16 time;  // 0x08
} RollDoorParams;

typedef struct RollDoorSetData {
	RwV3d pos;              // 0x00
	sAngle ang;             // 0x0C
	u8 unk18[0x14];         // 0x18
	RollDoorParams* params; // 0x2C
} RollDoorSetData;

typedef struct RollDoor {
	u8 unk00[0x28];           // 0x00
	RollDoorSetData* setData; // 0x28
	u8 unk2C[0x90];           // 0x2C
	s16 pushTime;             // 0xBC
	u8 unkBE[0x2];            // 0xBE
	RwV3d pos;                // 0xC0
	sAngle ang;               // 0xCC
	u8 unkD8[0x4];            // 0xD8
	f32 speed;                // 0xDC
	s32 turn;                 // 0xE0
} RollDoor;

extern "C" const f32 lbl_8_rodata_AD4[1];
extern "C" const f32 lbl_8_rodata_B10[1];

extern "C" void SetParameter__12TObjRolldoorFv(RollDoor* object)
{
	object->pos            = object->setData->pos;
	object->ang            = object->setData->ang;
	RollDoorParams* params = object->setData->params;
	object->speed          = lbl_8_rodata_AD4[0] + params->speed;
	object->turn           = lbl_8_rodata_B10[0] * params->turn;
	object->pushTime       = params->time;
}
