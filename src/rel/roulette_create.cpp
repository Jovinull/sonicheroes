#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// rouletteCreate, the factory rel/roulette_register.cpp puts in the editor
// record for TObjRoulette, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "stg05_on_rourette.dff": clone the module's
// model and, unless it is already in, add it to the world slot the model file
// names, reaching the model file through a local pointer.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjRoulette;
extern "C" ModelFile rouletteModelFile;
extern "C" CCL_INFO rouletteCclInfo;
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

class TObjRoulette : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	RpClump* clump; // 0xD0
	s32 added;      // 0xD4

	TObjRoulette(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjRoulette;
		DispTime  = 0xD8;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		ModelFile* file = &rouletteModelFile;
		clump           = fn_80150588(file->model);
		added           = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
			added = 1;
		}

		InitShare(*this, &rouletteCclInfo, 1, 4);
	}
	virtual ~TObjRoulette();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void rouletteCreate(void)
{
	new TObjRoulette(lbl_8042C110);
}
