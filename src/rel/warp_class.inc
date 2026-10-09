// TObjWarp, shared by rel/warp_create.cpp, which defines WARP_CTOR
// as inline so its factory inlines the constructor, and rel/warp_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* CL_TObjWarp;
extern "C" CCL_INFO warpCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjWarp : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjWarp(TObject* parent);
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots, so each fragment unit can put first one it does not define:
	// rel/warp_exec.cpp (Exec) declares EditOnChange first, the others Exec.
#ifdef WARP_EDIT_FIRST
	virtual void EditOnChange(SETDATA_PARAM*);
#endif
	virtual void Exec();
	virtual ~TObjWarp();
	virtual void TDisp();
#ifndef WARP_EDIT_FIRST
	virtual void EditOnChange(SETDATA_PARAM*);
#endif
};

WARP_CTOR TObjWarp::TObjWarp(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjWarp;
	DispTime  = 0xB8;

	warpCclInfo.a = *(f32*)ObjParam->setData.setBuffer;
	Init(&warpCclInfo, 1, 4);
}
