// TObjBushZenmai, shared by rel/bush_zenmai_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

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

extern "C" char* CL_TObjBushZenmai;
extern "C" ModelFile bushZenmaiModelFile;
extern "C" CCL_INFO bushZenmaiCclInfo;
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

class TObjBushZenmai : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	RpClump* clump; // 0xD0
	s32 added;      // 0xD4

	TObjBushZenmai(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBushZenmai;
		DispTime  = 0xD8;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		clump = fn_80150588(bushZenmaiModelFile.model);
		added = 0;
		if (added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + bushZenmaiModelFile.world * 4), clump);
			added = 1;
		}

		InitShare(*this, &bushZenmaiCclInfo, 1, 4);
	}
	virtual void Exec();
	virtual ~TObjBushZenmai();
	virtual void EditOnChange(SETDATA_PARAM*);
};
