// TObjDestructRail, shared by rel/destruct_rail_create.cpp, which defines DESTRUCT_RAIL_CTOR
// as inline so its factory inlines the constructor, and rel/destruct_rail_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* CL_TObjDestructRail;
extern "C" CCL_INFO destructRailCclInfo;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjDestructRail : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	s32 unkD0;      // 0xD0
	u8 unkD4[0x10]; // 0xD4

	TObjDestructRail(TObject* parent);
	virtual ~TObjDestructRail();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

DESTRUCT_RAIL_CTOR TObjDestructRail::TObjDestructRail(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjDestructRail;
	DispTime  = 0xE4;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	InitShare(*this, &destructRailCclInfo, 1, 4);
	unkD0 = 0;
}
