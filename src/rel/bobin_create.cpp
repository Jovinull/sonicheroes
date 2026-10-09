#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bobinCreate, the factory rel/bobin_register.cpp puts in the editor record for
// TObjBobin, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "s05_on_bobin.dff": clone the module's model
// and, unless it is already in, add it to the world slot the model file names,
// reaching the model file through a local pointer, and ends by clearing one
// word and setting the float at 0xD0 to the module's zero.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" char* CL_TObjBobin;
extern "C" ModelFile bobinModelFile;
extern "C" CCL_INFO bobinCclInfo;
extern "C" const f32 bobinZero[1];
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

class TObjBobin : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	f32 unkD0;      // 0xD0
	RpClump* clump; // 0xD4
	s32 added;      // 0xD8
	s32 unkDC;      // 0xDC
	u8 unkE0[0x20]; // 0xE0

	TObjBobin(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBobin;
		DispTime  = 0x100;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		ModelFile* file = &bobinModelFile;
		clump           = fn_80150588(file->model);
		added           = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
			added = 1;
		}

		InitShare(*this, &bobinCclInfo, 1, 4);
		unkDC = 0;
		unkD0 = bobinZero[0];
	}
	virtual ~TObjBobin();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void bobinCreate(void)
{
	new TObjBobin(lbl_8042C110);
}
