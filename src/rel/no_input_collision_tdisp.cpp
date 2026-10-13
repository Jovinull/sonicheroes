#include "types.h"

// The no-input collision's TDisp (noInputCollisionTDisp here): only with the
// game's debug display flag (byte 5) set, it draws the collision's marker model
// lit by the placement's light bits, with render states 0xA and 0xB set to 2
// and 0x14 to 1 (put back after).

typedef struct RpClump RpClump;

typedef struct NoInputPlacement {
	u8 unk00[0x18];
	u32 flag; // 0x18
} NoInputPlacement;

typedef struct NoInputCollision {
	u8 unk00[0x28];
	NoInputPlacement* placement; // 0x28
	u8 unk2C[0xB8];
	RpClump* clump; // 0xE4
} NoInputCollision;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" CLIGHT lbl_802D5E80;

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void noInputCollisionTDisp(NoInputCollision* object)
{
	if ((s8)lbl_8042C180[5] != 0) {
		s32 src;
		s32 dst;
		s32 cull;

		fn_80194294(0xA, &src);
		fn_80194294(0xB, &dst);
		fn_80194294(0x14, &cull);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		lbl_802D5E80.SetCurrentNum(((object->placement->flag & 0x1C0000) >> 18) + 4);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		fn_8014FF2C(object->clump);
		fn_80194234(0x14, cull);
		fn_80194234(0xA, src);
		fn_80194234(0xB, dst);
	}
}
