#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// floatjCreate, the factory the editor record for TObjFloatJ points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The object clones the module's model into the world at 0x725C of the stage
// block, then sizes the module's shape: its radius is the first word of the
// placement's parameter block times the module's constant 20. The parameter
// block pointer is read first, before the class name.

struct FloatJParam {
	f32 size; // 0x00
};

extern "C" char* CL_TObjFloatJ;
extern "C" void* floatJModel;
extern "C" CCL_INFO floatJCclInfo;
extern "C" const f32 floatJScale[1];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjFloatJ : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;      // 0xB8
	RwV3d pos;      // 0xBC
	sAngle ang;     // 0xC8
	RpClump* clump; // 0xD4

	TObjFloatJ(TObject* parent)
	    : TObject(parent)
	{
		FloatJParam* param = (FloatJParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjFloatJ;
		DispTime  = 0xD8;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		clump = fn_80150588(floatJModel);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);

		floatJCclInfo.a = floatJScale[0] * param->size;
		Init(&floatJCclInfo, 1, 4);
		unkB8 = 0;
	}
	virtual ~TObjFloatJ();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void floatjCreate(void)
{
	new TObjFloatJ(lbl_8042C110);
}
