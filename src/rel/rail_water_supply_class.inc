// TObjRailWaterSupply, shared by rel/rail_water_supply_create.cpp, which defines RAIL_WATER_SUPPLY_CTOR
// as inline so its factory inlines the constructor, and rel/rail_water_supply_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjRailWaterSupply;
extern "C" ModelFile railWaterSupplyModelFiles[2];
extern "C" CCL_INFO railWaterSupplyCclInfo[5];
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjRailWaterSupply : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[2]; // 0xD0

	TObjRailWaterSupply(TObject* parent);
	virtual ~TObjRailWaterSupply();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

RAIL_WATER_SUPPLY_CTOR TObjRailWaterSupply::TObjRailWaterSupply(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjRailWaterSupply;
	DispTime  = 0xE0;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 2; i++) {
		ModelFile* file = &railWaterSupplyModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
	}
	InitShare(*this, railWaterSupplyCclInfo, 5, 4);
}
