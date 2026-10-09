// TObjBobinAir, shared by rel/bobin_air_create.cpp, which defines BOBIN_AIR_CTOR
// as inline so its factory inlines the constructor, and rel/bobin_air_ctor.cpp,
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

extern "C" char* CL_TObjBobinAir;
extern "C" ModelFile bobinAirModelFile;
extern "C" CCL_INFO bobinAirCclInfo;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjBobinAir : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	u8 unkD0[4];    // 0xD0
	RpClump* clump; // 0xD4
	s32 added;      // 0xD8
	s32 unkDC;      // 0xDC
	u8 unkE0[8];    // 0xE0

	TObjBobinAir(TObject* parent);
	virtual void Exec();
	virtual ~TObjBobinAir();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BOBIN_AIR_CTOR TObjBobinAir::TObjBobinAir(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBobinAir;
	DispTime  = 0xE8;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	ModelFile* file = &bobinAirModelFile;
	clump           = fn_80150588(file->model);
	added           = 0;
	if (added == 0) {
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
		added = 1;
	}

	InitShare(*this, &bobinAirCclInfo, 1, 4);
	flag |= 0x40;

	unkDC    = 0;
	unkE0[0] = 0;
	unkE0[1] = 0;
	unkE0[2] = 0;
	unkE0[3] = 0;
	unkE0[4] = 0;
	unkE0[5] = 0;
	unkE0[6] = 0;
	unkE0[7] = 0;
}
