// TObjBobin, shared by rel/bobin_create.cpp, which defines BOBIN_CTOR
// as inline so its factory inlines the constructor, and rel/bobin_ctor.cpp,
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

	TObjBobin(TObject* parent);
	virtual ~TObjBobin();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BOBIN_CTOR TObjBobin::TObjBobin(TObject* parent)
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
