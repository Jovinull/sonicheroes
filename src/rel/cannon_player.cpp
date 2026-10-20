#include "types.h"

#include "src/rel/cannon_class.inc"
#include "src/rel/cannon_smoke_class.inc"

// TObjCannon::CannonPlayer (the PS2 build's name and argument): the cannon
// fires a player. Like CannonPlayerToCancel it sets the player at the barrel's
// tip and launches it along the barrel, here with the launch kind and speed of
// the team's formation; it plays sound 0x102A, has the team do its launch
// reaction, kicks the barrel back, shakes the camera for the first players
// and leaves smoke at the barrel's mouth.
//
// NonMatching (2 words): the team's index (an s8) is compared with the player
// count after `lbz r0; extsb r4, r0`; the retail sign-extends it in place
// (`lbz r4; extsb r4, r4`). Locals of every width, inline helpers, a cast, the
// reversed compare and opt_propagation off did not change it.

typedef struct CannonTeam {
	u8 unk000[0x38];
	s8 index; // 0x38
	u8 unk039[0x113];
	s8 kind; // 0x14C
} CannonTeam;

extern "C" void* lbl_8042C388;
extern "C" void* lbl_8042C1F8;
extern "C" s32 lbl_8042C204;
extern "C" const f32 cannonRadToAngle[1];
extern "C" const f32 cannonRecoil[1];
extern "C" const f32 cannonShakePower[1];

extern "C" double asin(double x);
extern "C" double atan2(double y, double x);
extern "C" CannonTeam* fn_800924E4(s32 player);
extern "C" void fn_800E0B40(s32 player, f32 speed, sAngle* angle, s32 kind);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg3);
extern "C" void fn_8004CC7C(void* camera);
extern "C" void fn_8004D5F4(void* camera, f32 power, s32 time);
extern "C" void fn_8004CC3C(void* camera);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, void* angle);

static inline s32 cannonLaunchKind(Cannon* object)
{
	switch (object->formation) {
		case 0:
			return object->launchKind[0];
		case 1:
			return object->launchKind[2];
		case 2:
		default:
			return object->launchKind[1];
	}
}

static inline f32 cannonLaunchSpeed(Cannon* object)
{
	switch (object->formation) {
		case 0:
			return object->launchSpeed[0];
		case 1:
			return object->launchSpeed[2];
		case 2:
		default:
			return object->launchSpeed[1];
	}
}

extern "C" void CannonPlayer__10TObjCannonFi(Cannon* object, s32 player)
{
	CannonTeam* team = fn_800924E4(player);
	s32 kind         = cannonLaunchKind(object);
	RwMatrixTag matrix;
	sAngle angle;
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
	fn_800E0B40(player, cannonLaunchSpeed(object), &angle, kind);
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x102A, 0, 0);
	}
	fn_8001F674(team->kind, 4, 0xF, 0);
	object->recoil = cannonRecoil[0];
	if (team->index < lbl_8042C204) {
		fn_8004CC7C(lbl_8042C1F8);
		fn_8004D5F4(lbl_8042C1F8, cannonShakePower[0], 10);
		fn_8004CC3C(lbl_8042C1F8);
	}
	new TObjCannonSmoke((TObject*)object, &object->tip2, &angle);
}
