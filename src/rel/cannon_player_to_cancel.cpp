#include "types.h"

#include "src/rel/cannon_class.inc"

// TObjCannon::CannonPlayerToCancel (the PS2 build's name and argument). It sets
// the player at the barrel's tip and launches it along the barrel (its angles
// worked out from the barrel matrix's up axis, facing back along the barrel's
// yaw) with the barrel drop as speed, plays sound 0x102A, has the player's team
// do its launch reaction (fn_8001F674 with 4 and 15) and waits 15 frames.

typedef struct CannonAngle {
	s32 x, y, z;
} CannonAngle;

typedef struct CannonTeam {
	u8 unk000[0x14C];
	s8 kind; // 0x14C
} CannonTeam;

extern "C" void* lbl_8042C388;
extern "C" const f32 cannonRadToAngle[1];

extern "C" double asin(double x);
extern "C" double atan2(double y, double x);
extern "C" CannonTeam* fn_800924E4(s32 player);
extern "C" void fn_800E0B40(s32 player, f32 speed, CannonAngle* angle, s32 kind);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg3);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, void* angle);

extern "C" void CannonPlayerToCancel__10TObjCannonFi(Cannon* object, s32 player)
{
	CannonTeam* team = fn_800924E4(player);
	RwMatrixTag matrix;
	CannonAngle angle;
	f32 sin;

	objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
	    object->replace, player, 0, &object->tip, NULL);
	angle.y = object->barrelYaw + 0x8000;
	sin     = fn_800D7B00(object->barrelPitch);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(object->barrelPitch), sin, 0);
	sin = fn_800D7B00(object->barrelYaw);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(object->barrelYaw), sin, 2);
	RwV3d dir = matrix.up;
	angle.x   = cannonRadToAngle[0] * (f32)asin(dir.z);
	angle.z   = -(s32)(cannonRadToAngle[0] * (f32)atan2(dir.x, dir.y));
	fn_800E0B40(player, cannonBarrelDrop[0], &angle, 5);
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x102A, 0, 0);
	}
	fn_8001F674(team->kind, 4, 0xF, 0);
	object->timer = 0xF;
}
