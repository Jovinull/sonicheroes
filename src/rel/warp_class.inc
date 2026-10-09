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
	virtual ~TObjWarp();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

WARP_CTOR TObjWarp::TObjWarp(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjWarp;
	DispTime  = 0xB8;

	warpCclInfo.a = *(f32*)ObjParam->setData.setBuffer;
	Init(&warpCclInfo, 1, 4);
}
