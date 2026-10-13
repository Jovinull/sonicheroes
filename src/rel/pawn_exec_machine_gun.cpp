#include "types.h"

// TObjEnemyPawn::ExecMachineGun (the PS2 build's name): with a gun and a muzzle
// frame, moves the gun to the muzzle and aims it at a point 0.25 down and 2
// back in the active motion's first bone space, from the muzzle.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
} RwMatrixTag;

typedef struct RwFrame RwFrame;
typedef struct RpHAnimHierarchy RpHAnimHierarchy;

class TMachineGun
{
public:
	void SetPosition(const RwV3d* pos);
	void SetAimPosition(const RwV3d* aim);
};

class ENEMYMTNMAN
{
public:
	RpHAnimHierarchy* GetActiveHAHPointer();
};

typedef struct Pawn {
	u8 unk000[0xB8];
	ENEMYMTNMAN motion; // 0xB8
	u8 unk0B9[0x253];
	RwFrame* muzzle; // 0x30C
	u8 unk310[0x4];
	TMachineGun* gun; // 0x314
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnGunAimZ[1];
extern "C" const f32 pawnGunAimY[1];

extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" RwMatrixTag* fn_8013F47C(RpHAnimHierarchy* hierarchy);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" void ExecMachineGun__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->gun != NULL && pawn->muzzle != NULL) {
		RwMatrixTag* ltm = fn_8019E8EC(pawn->muzzle);
		RwV3d pos;
		RwV3d aim;
		RwMatrixTag bone;

		pos.z = pos.y = pos.x = pawnZero[0];
		fn_8019941C(&pos, &pos, 1, ltm);
		pawn->gun->SetPosition(&pos);
		bone  = *fn_8013F47C(pawn->motion.GetActiveHAHPointer());
		aim.z = pawnGunAimZ[0];
		aim.y = pawnGunAimY[0];
		aim.x = pawnZero[0];
		fn_8019947C(&aim, &aim, 1, &bone);
		aim.x += pos.x;
		aim.y += pos.y;
		aim.z += pos.z;
		pawn->gun->SetAimPosition(&aim);
	}
}
