// TObjMoji, shared by rel/moji_create.cpp, which defines MOJI_CTOR
// as inline so its factory inlines the constructor, and rel/moji_ctor.cpp,
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

struct MojiPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

struct MojiParam {
	s32 kind; // 0x00
};

extern "C" char* CL_TObjMoji;
extern "C" ModelFile mojiModelFiles[8];
extern "C" CCL_INFO mojiCclInfo[4];
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare, still fn_8003BF04 in main's symbols. Taking the
// collision base by reference adjusts `this` to it without the null test a
// pointer conversion would add, which is what calling the member does.
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjMoji : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	MojiPart parts[8]; // 0xD0

	TObjMoji(TObject* parent);
	virtual ~TObjMoji();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

MOJI_CTOR TObjMoji::TObjMoji(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjMoji;
	DispTime  = 0x110;

	int i;
	MojiParam* param = (MojiParam*)ObjParam->setData.setBuffer;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (i = 0; i < 8; i++) {
		parts[i].clump = fn_80150588(mojiModelFiles[i].model);
		parts[i].added = 0;
	}
	EditOnChange(&ObjParam->setData);

	if (param->kind == 1) {
		InitShare(*this, &mojiCclInfo[2], 2, 4);
	} else {
		InitShare(*this, &mojiCclInfo[0], 2, 4);
	}
}
