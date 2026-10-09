#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// mojiCreate, the factory the editor record for TObjMoji points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes the module's shapes through InitShare, as rel/key_object_create.cpp
// does.
//
// It is rel/big_dice_create.cpp for eight models, starting with
// "stg05_on_moji01.dff": clone each into its own part, apply the placement
// through the class's own EditOnChange, and then take two of the module's four
// shapes, the second pair when the first word of the parameter block is 1. The
// parameter block pointer is read with the position, and the loop counter is
// declared before it, which is the order the original gives them registers.

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

	TObjMoji(TObject* parent)
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
	virtual ~TObjMoji();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void mojiCreate(void)
{
	new TObjMoji(lbl_8042C110);
}
