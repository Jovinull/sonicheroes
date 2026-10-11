// TObjKey::Disappear (the PS2 build's name): the key is taken. It marks itself
// done (state 2) and its placement with condition bit 0x10000, clears the
// game's flag at 0x26, bursts two puffs of particles a little above itself,
// plays sound 0xE016 when there is a sound object, then takes its model out of
// the world and destroys it, deletes the object at +0xD8 and raises bit 0 of
// its signal. The class is in key_object_class.inc.

#define KEY_OBJECT_CTOR inline
#include "src/rel/key_object_class.inc"

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" const RwV3d keyDisappearDirection;
extern "C" const f32 keyDisappearRise[1];
extern "C" const f32 keyDisappearBurstA[1];
extern "C" const f32 keyDisappearBurstB[1];
extern "C" void* objEmitBurst(const RwV3d* position, const RwV3d* velocity, f32 amount);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 arg2, s32 arg3);
extern "C" void fn_800C1978(void);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

void TObjKey::Disappear()
{
	unkD0 = 2;
	ObjParam->setData.condition.Flag |= 0x10000;
	if (lbl_8042C180 != NULL) {
		lbl_8042C180[0x26] = 0;
	}

	RwV3d direction = keyDisappearDirection;
	RwV3d position;
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	position.y = pos.y + keyDisappearRise[0];
	objEmitBurst(&position, &direction, keyDisappearBurstA[0]);
	objEmitBurst(&position, &direction, keyDisappearBurstB[0]);

	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0xE016, 0, 0);
	}
	fn_800C1978();

	if (clump != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		fn_80150958(clump);
		clump = NULL;
	}
	if ((TObject*)unkD8 != NULL) {
		delete (TObject*)unkD8;
		unkD8 = 0;
	}
	Signal |= 1;
}
