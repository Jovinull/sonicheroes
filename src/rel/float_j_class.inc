// TObjFloatJ, shared by rel/float_j_create.cpp, which defines FLOAT_J_CTOR
// as inline so its factory inlines the constructor, and rel/float_j_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjFloatJ(TObject* parent);
	virtual void Exec();
	virtual ~TObjFloatJ();
	virtual void EditOnChange(SETDATA_PARAM*);
};

FLOAT_J_CTOR TObjFloatJ::TObjFloatJ(TObject* parent)
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
