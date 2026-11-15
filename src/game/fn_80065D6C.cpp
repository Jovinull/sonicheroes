// Draws the particle materials of the particle core (TObjPtclCore, its list at +0x28) with none of
// flags 0x1E set, through their DispManager virtual, between fn_80194234(0xE, 0) and
// fn_80194234(0xE, 1) (HYPOTHESIS: a render-state toggle). While the debug byte +0x20 of
// lbl_8042C180 is set, only materials with flag 0x10000000 are drawn. Nothing is drawn without the
// core singleton lbl_8042C2E0.
// CORROBORATED: this is TObjPtclCore::Disp(). GameCube: it fills the Disp slot of the
// TObjPtclCore vtable lbl_80243C18 (after Exec, fn_80065E20, and before TDisp, fn_80065CAC, in
// TObject's virtual order). PS2 metadata (NTSC-U SLUS_207.18): TObjPtclCore::PDisp, TDisp and Disp
// are consecutive in the same order as fn_80065BF8, fn_80065CAC and fn_80065D6C, with the same
// reference sets. The symbol keeps its address-based name.
#include "types.h"

// Local view of PARTICLE_MATERIAL: flags at +0x4, list link at +0x48, vtable pointer at +0x54.
class PARTICLE_MATERIAL
{
public:
	u8 unknown0[4];
	s32 flags; // 0x4
	u8 unknown8[0x48 - 0x8];
	PARTICLE_MATERIAL* next; // 0x48
	u8 unknown4C[0x54 - 0x4C];
	virtual void MoveManager();
	virtual void DispManager();
};

struct PtclCoreD6C {
	u8 pad0[0x28];
	PARTICLE_MATERIAL* materials; // 0x28
};

struct DebugD6C {
	u8 pad0[0x20];
	s8 enabled; // 0x20
};

extern "C" {
extern void* lbl_8042C2E0;
extern DebugD6C* lbl_8042C180;
void fn_80194234(s32 state, s32 value);

void fn_80065D6C(PtclCoreD6C* core)
{
	PARTICLE_MATERIAL* material;

	if (lbl_8042C2E0 != NULL && core->materials != NULL) {
		material = core->materials;
		fn_80194234(0xE, 0);
		while (material != NULL) {
			s32 flags = material->flags;

			if (lbl_8042C180->enabled && !(flags & 0x10000000)) {
				material = material->next;
				continue;
			}
			if ((flags & 0x1E) == 0) {
				material->DispManager();
			}
			material = material->next;
		}
		fn_80194234(0xE, 1);
	}
}
}
