#include "types.h"

// TObjEnemyPawn::ResetVariable (the PS2 build's name, by its member order):
// clears the pawn's working state (counters, timers, links, the four slots to
// -1), sets it shown and active, and resets its local matrix to the identity
// (RenderWare's RwMatrixSetIdentity, store order included).

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

typedef struct Pawn {
	u8 unk000[0x240];
	s32 unk240;   // 0x240
	s32 unk244;   // 0x244
	s32 nextMode; // 0x248
	u8 unk24C[0x4];
	s32 unk250; // 0x250
	u8 unk254[0xC];
	s32 unk260; // 0x260
	s32 unk264; // 0x264
	s32 unk268; // 0x268
	s32 unk26C; // 0x26C
	u8 unk270[0x4];
	s32 unk274; // 0x274
	u8 unk278[0x4];
	s32 unk27C; // 0x27C
	u8 unk280[0x4];
	s32 unk284; // 0x284
	s32 unk288; // 0x288
	s32 unk28C; // 0x28C
	u8 unk290[0x54];
	s32 unk2E4; // 0x2E4
	s32 unk2E8; // 0x2E8
	s32 shown;  // 0x2EC
	s32 unk2F0; // 0x2F0
	u8 unk2F4[0x8];
	s32 unk2FC; // 0x2FC
	u8 unk300[0x4];
	s32 unk304; // 0x304
	s32 unk308; // 0x308
	s32 unk30C; // 0x30C
	s32 unk310; // 0x310
	s32 unk314; // 0x314
	u8 unk318[0x8];
	s32 unk320;         // 0x320
	s32 unk324;         // 0x324
	RwMatrixTag matrix; // 0x328
	s32 unk368;         // 0x368
	s32 unk36C;         // 0x36C
	s32 unk370;         // 0x370
	s32 unk374;         // 0x374
	s32 active;         // 0x378
	s32 unk37C;         // 0x37C
	s32 broken;         // 0x380
	s32 ctrlTimer;      // 0x384
	s32 rounds;         // 0x388
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnOne[1];

extern "C" void ResetVariable__13TObjEnemyPawnFv(Pawn* pawn)
{
	RwMatrixTag* m;

	pawn->unk250   = 0;
	pawn->unk260   = 0;
	pawn->unk264   = 0;
	pawn->unk268   = 0;
	pawn->unk284   = 0;
	pawn->unk288   = 0;
	pawn->shown    = 1;
	pawn->unk2E4   = 0;
	pawn->unk2E8   = 0;
	pawn->unk244   = 0;
	pawn->unk2F0   = 0;
	pawn->unk2FC   = 0;
	pawn->unk240   = 0;
	pawn->unk26C   = -1;
	pawn->unk274   = -1;
	pawn->unk27C   = -1;
	pawn->unk28C   = -1;
	pawn->unk304   = 0;
	pawn->unk308   = 0;
	pawn->unk30C   = 0;
	pawn->unk310   = 0;
	pawn->unk314   = 0;
	pawn->unk320   = 0;
	pawn->nextMode = 0;
	pawn->unk324   = -1;
	m              = &pawn->matrix;
	m->right.x = m->up.y = m->at.z = pawnOne[0];
	m->right.y = m->right.z = m->up.x = pawnZero[0];
	m->up.z = m->at.x = m->at.y = pawnZero[0];
	m->pos.x = m->pos.y = m->pos.z = pawnZero[0];
	m->flags |= 0x20003;
	pawn->unk368    = 0;
	pawn->unk36C    = 0;
	pawn->unk370    = 0;
	pawn->unk374    = 0;
	pawn->active    = 1;
	pawn->unk37C    = 1;
	pawn->broken    = 0;
	pawn->ctrlTimer = 0;
	pawn->rounds    = 0;
}
