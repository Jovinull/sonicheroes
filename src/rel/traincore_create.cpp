#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// traincoreCreate, the factory rel/traincore_register.cpp puts in the editor
// record: a new TObjTrainCore (the class name its constructor stores) that
// copies the set data's position and angle, clones its 2 models into the world
// slots their files name and takes the module's shape for its collision block
// (its third base). Unless the set data's condition has bit 0x10000, it then
// starts effect 9 at its offset point turned by its angle (fn_800628D0) and
// keeps its handle. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp).

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjTrainCore;
extern "C" ModelFile traincoreModelFiles[3];
extern "C" CCL_INFO traincoreCclInfo;
extern "C" RwV3d traincoreEffectOffset;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);
extern "C" void* fn_800628D0(s32 kind, RwV3d* pos, sAngle* ang);
void RelativeCalcPoint(RwV3d* out, RwV3d* point, RwV3d* origin, sAngle* ang);

// C_COLLI::InitShare (fn_8003BF04), as rel/yajirusi_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjTrainCore : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4
	u8 padD0[0x4];
	void* effect;       // 0xD4
	ModelPart parts[2]; // 0xD8
	u8 padE8[0x8];

	TObjTrainCore(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjTrainCore;
		DispTime  = 0xF0;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		for (int i = 0; i <= 1; i++) {
			ModelFile* file = &traincoreModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
		}
		InitShare(*this, &traincoreCclInfo, 1, 4);
		if ((ObjParam->setData.condition.Flag & 0x10000) == 0) {
			RwV3d point;

			point.x = traincoreEffectOffset.x + pos.x;
			point.y = traincoreEffectOffset.y + pos.y;
			point.z = traincoreEffectOffset.z + pos.z;
			RelativeCalcPoint(&point, &point, &pos, &ang);
			effect = fn_800628D0(9, &point, &ang);
		} else {
			effect = NULL;
		}
	}
	virtual ~TObjTrainCore();
};

extern "C" void traincoreCreate(void)
{
	new TObjTrainCore(lbl_8042C110);
}
