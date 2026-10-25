#include "game/effect/eff_bomb.h"
#include "game/object.h"
#include "game/setObj.h"

// rainfruitmiCreate, the factory rel/rainfruitmi_register.cpp puts in the
// editor record: a new TObjRainfruitmi (the class name its constructor stores)
// that copies the set data's position and angle, clones the small rain fruit's
// model into the world slot at 0x7258, takes the module's shape for its
// collision block (its third base) and sets up its ground walker (its fourth
// base): radius 15, bounce 0.9 and the ground attributes it ignores. The
// allocation is a real new-expression of the class (rel/sample1_create.cpp).

extern "C" char* CL_TObjRainfruitmi;
extern "C" void* rainfruitmiModel;
extern "C" CCL_INFO rainfruitmiCclInfo;
extern "C" f32 rainfruitmiZero;
extern "C" f32 rainfruitmiOne;
extern "C" f32 rainfruitmiRadius;
extern "C" f32 rainfruitmiBound;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void* memset(void* dst, s32 value, u32 size);

class TObjRainfruitmi : public TObject, public TObjSetObj, public C_COLLI, public OBJ_MoveOnGround
{
public:
	sAngle ang;     // 0xF0
	RwV3d spd;      // 0xFC
	u8 unk108[0xC]; // 0x108
	u8 pad114[0x4];
	f32 unk118;     // 0x118
	f32 unk11C;     // 0x11C
	RpClump* clump; // 0x120
	s32 added;      // 0x124
	RwV3d pos;      // 0x128

	TObjRainfruitmi(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjRainfruitmi;
		DispTime  = 0x134;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		clump     = fn_80150588(rainfruitmiModel);
		added     = 1;
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7258), clump);
		Init(&rainfruitmiCclInfo, 1, 4);
		strength = 3;
		unk118   = rainfruitmiOne;
		spd.x = spd.y = spd.z = unk11C = rainfruitmiZero;
		memset(unk108, 0, 0xC);
		radObject    = rainfruitmiRadius;
		bound_coef   = rainfruitmiBound;
		lattr_Ignore = 0x8002;
	}
	virtual ~TObjRainfruitmi();
};

extern "C" void rainfruitmiCreate(void)
{
	new TObjRainfruitmi(lbl_8042C110);
}
