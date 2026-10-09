// TObjEFLensSet::TDisp. Only the set nearest the camera focus draws (the focus
// is the position lbl_8042C208 points at; GetNearestLens walks the efLensTop
// chain through each lens's GetPosition, in lens_flare_class.inc), and not when
// its placement asks for kind 1 or while the mode flag at +0x20 of lbl_8042C180
// is 1. The drawing is TObjEFLensTmp::TDisp's (rel/lens_flare_tmp_tdisp.cpp),
// followed by three calls on the current camera (lbl_8042C9A4). GetNearestLens
// returns NULL itself for an empty chain, which is the original's `li r28, 0`
// over a register that already holds it. The classes are in
// lens_flare_class.inc.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"
#include "game/mobject.h"

// The current camera's field at +0x80.
struct LensCamera {
	u8 unk00[0x80];
	f32 unk80; // 0x80
};

// The mode object lbl_8042C180 points at.
struct LensGameMode {
	u8 unk00[0x20];
	s8 unk20; // 0x20
};

extern "C" LensGameMode* lbl_8042C180;
extern "C" RwCamera** lbl_8042C9A4;
extern "C" f32 fn_8019421C(void);
extern "C" f32 fn_80194228(void);
extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);
extern "C" void fn_8019CC00(RwCamera* camera);
extern "C" void fn_8019CC28(RwCamera* camera);
extern "C" void fn_8016EE88(RwCamera* camera);

void TObjEFLensSet::TDisp()
{
	EFLensSetParam* param = (EFLensSetParam*)ObjParam->setData.setBuffer;

	if (this == GetNearestLens()) {
		if (param == NULL || param->kind != 1) {
			if (lbl_8042C180->unk20 != 1) {
				f32 first  = fn_8019421C();
				f32 second = fn_80194228();
				s32 fog;

				unk30 = lensFlareOne[0] / ((LensCamera*)GetCurrentCameraPointer())->unk80;
				unk34 = second - first;

				fn_80194294(0xE, &fog);
				fn_80194234(0xE, 0);
				fn_80194234(0xA, 5);
				fn_80194234(0xB, 2);
				DispPtcl();
				fn_80194234(0xA, 5);
				fn_80194234(0xB, 6);
				fn_80194234(0xE, fog);

				RwCamera* camera = *lbl_8042C9A4;
				fn_8019CC00(camera);
				fn_8019CC28(camera);
				fn_8016EE88(camera);
			}
		}
	}
}
