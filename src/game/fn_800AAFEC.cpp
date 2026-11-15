// Finds the first team (lbl_80303DC8) whose marker is active (+0x21C) and within 300 of `pos` (its
// marker position +0x220; Distance2P2P is squared), returning 1-4 for team phases 0-3 (+0x34) and
// storing the character kind of its previous leader (+0x3B, kinds at +0x110) in *kind; 0 when none.
// HYPOTHESIS: a proximity trigger for team actions; the roles are UNKNOWN.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Team800AAFEC {
	u8 pad0[0x34];
	s32 phase; // 0x34
	u8 pad38[3];
	s8 previous; // 0x3B
	u8 pad3C[0x110 - 0x3C];
	s8 kinds[3]; // 0x110
	u8 pad113[0x21C - 0x113];
	s8 markerActive; // 0x21C
	u8 pad21D[3];
	RwV3d marker; // 0x220
};

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" {
extern Team800AAFEC* lbl_80303DC8[4];
extern f32 lbl_8042DBA4; // 90000.0f (300 squared)

s32 fn_800AAFEC(RwV3d* pos, s32* kind)
{
	Team800AAFEC* team;
	int i;
	s32 result;

	result = 0;
	for (i = 0; i < 4; i++) {
		team = lbl_80303DC8[i];
		if (team != NULL && team->markerActive != 0) {
			f32 d = Distance2P2P(&team->marker, pos);

			switch (team->phase) {
				case 3:
					if (d < lbl_8042DBA4) {
						result = 4;
					}
					break;
				case 2:
					if (d < lbl_8042DBA4) {
						result = 3;
					}
					break;
				case 1:
					if (d < lbl_8042DBA4) {
						result = 2;
					}
					break;
				case 0:
					if (d < lbl_8042DBA4) {
						result = 1;
					}
					break;
			}
			if (result != 0) {
				*kind = team->kinds[team->previous];
				break;
			}
		}
	}
	return result;
}
}
