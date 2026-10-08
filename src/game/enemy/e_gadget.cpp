// Whole-TU auto,deferred retains the exact inline-destructor exception order.
// Automatic and out-of-class-inline trials interspersed bodies or moved its EH
// record last. Reversed out-of-line definitions leave a leading 148-byte inline
// group before the 500-byte method group; fix_e_gadget_object.py moves intact
// compiler atoms and one exception-index row only. See the unit evidence.
#include "game/enemy/e_gadget.h"
struct RwCamera;
struct RwSphere {
	RwV3d center;
	f32 radius;
};
struct CurrentCameraView {
	RwCamera* currentCamera;
};
extern "C" {
extern TObject* lbl_8042C114;
extern CurrentCameraView* lbl_8042C9A4;
s32 fn_8019CE34(RwCamera*, const RwSphere*);
s32 fn_80017800();
}
TEnemyGadget::TEnemyGadget(TObjEnemy* owner)
    : TObject(lbl_8042C114)
{
	pOwner   = owner;
	pClump   = NULL;
	IsKilled = 0;
	gmode    = E_GM_STANDBY;
}

void TEnemyGadget::Exec()
{
	if (IsKilled)
		Signal |= 1;
	else if (fn_80017800())
		Update();
}

void TEnemyGadget::Disp()
{
	if (!IsKilled && CanDisp())
		DispOpaq();
}

void TEnemyGadget::TDisp()
{
	if (!IsKilled && CanDisp())
		DispTrans();
}

s32 TEnemyGadget::CheckCameraFrustum(const RwV3d* pos, f32 radius)
{
	if (!pClump)
		return 1;
	RwSphere sphere;
	sphere.center = *pos;
	sphere.radius = radius;
	return fn_8019CE34(lbl_8042C9A4->currentCamera, &sphere) != 0;
}
