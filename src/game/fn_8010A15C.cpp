// Draws an effect at the object's position (0x10C) when it is visible (HYPOTHESIS; the effect and
// the object are UNKNOWN): skipped in game mode 0x18 (lbl_8029C310+0x2C) or when the position's
// height equals lbl_8042E7D8; otherwise, when a sphere of radius lbl_8042E7DC around the position
// passes the current camera's frustum test (fn_8019CE34, HYPOTHESIS: RwCameraFrustumTestSphere),
// it runs fn_800B7864(0), fn_800B7584 with the scale {8.5, 1.0, 2.5} (owned .rodata) and a size
// that shrinks with the height above 0xF8, and fn_800B7820. Built with -fp_contract off (separate
// fmuls/fsubs in retail).
#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct RwSphere {
	RwV3d center;
	f32 radius;
};

struct Engine8010A15C {
	void* curCamera; // 0x0
};

struct Game8010A15C {
	u8 pad0[0x2C];
	s32 f2C; // 0x2C
};

struct Obj8010A15C {
	u8 pad0[0xF8];
	f32 fF8; // 0xF8
	u8 padFC[0x10C - 0xFC];
	RwV3d pos;  // 0x10C
	RwV3d f118; // 0x118
};

extern "C" {
extern Game8010A15C lbl_8029C310;
extern Engine8010A15C* lbl_8042C9A4;
extern f32 lbl_8042E7D8;
extern f32 lbl_8042E7DC;
extern f32 lbl_8042E7E0;
extern f32 lbl_8042E7E4;
s32 fn_8019CE34(void* camera, RwSphere* sphere);
void fn_800B7864(s32 a);
void fn_800B7584(RwV3d* pos, RwV3d* b, RwV3d* scale, f32 size);
void fn_800B7820(void);

void fn_8010A15C(Obj8010A15C* o)
{
	if (lbl_8029C310.f2C != 0x18 && lbl_8042E7D8 != o->pos.y) {
		void* camera = lbl_8042C9A4->curCamera;
		RwSphere sphere;
		sphere.radius = lbl_8042E7DC;
		sphere.center = o->pos;
		if (fn_8019CE34(camera, &sphere) != 0) {
			fn_800B7864(0);
			RwV3d scale = { 8.5f, 1.0f, 2.5f };
			fn_800B7584(
			    &o->pos, &o->f118, &scale, lbl_8042E7E0 - lbl_8042E7E4 * (o->fF8 - o->pos.y));
			fn_800B7820();
		}
	}
}
}
