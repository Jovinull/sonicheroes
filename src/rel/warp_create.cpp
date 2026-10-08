#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// warpCreate, the factory rel/warp_register.cpp puts in the editor record for
// TObjWarp.
//
// It is the same 47 instructions in the thirteen stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The collision block at 0x30 is a third base, not a
// member: the original constructs it before it stores the vtables, and a member
// is constructed after them. The instance is 0xB8 bytes, the two bases of every
// placed object plus the 0x88 of C_COLLI.
//
// The constructor sets the radius of the module's collision shape from the
// first word of the placement's parameter block and hands the shape to the
// collision base. The shape is static data in the module, shared by every warp.
//
// The PS2 build names the class pointer CL_TObjWarp and the vtable
// __vt__8TObjWarp, and each module's symbols.txt uses those names; warpCclInfo
// is this file's name for the shape.

extern "C" char* CL_TObjWarp;
extern "C" CCL_INFO warpCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjWarp : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjWarp(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjWarp;
		DispTime  = 0xB8;

		warpCclInfo.a = *(f32*)ObjParam->setData.setBuffer;
		Init(&warpCclInfo, 1, 4);
	}
	virtual ~TObjWarp();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void warpCreate(void)
{
	new TObjWarp(lbl_8042C110);
}
