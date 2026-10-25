#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// kazariobjCreate, the factory rel/kazariobj_register.cpp puts in the editor
// record: a new TObjKazariObj (the class name its constructor stores). The set
// data's first parameter picks which of the 3 decorations it shows (one out of
// range falls back to the first): each model is cloned and only the picked one
// goes into the world slot at 0x7278. The collision block (its third base)
// then takes the picked one's shape. The allocation is a real new-expression
// of the class (rel/sample1_create.cpp).

// one entry of the family's table: its file name and the model once loaded
struct KazariobjEntry {
	const char* name; // 0x0
	void* model;      // 0x4
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

// the set data's parameters
struct KazariobjParam {
	s32 kind; // 0x00: the decoration shown
};

extern "C" char* CL_TObjKazariObj;
extern "C" KazariobjEntry kazariobjTable[3];
extern "C" CCL_INFO kazariobjCclInfo[3];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare (fn_8003BF04), as rel/yajirusi_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjKazariObj : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;          // 0xB8
	RwV3d pos;          // 0xBC
	sAngle ang;         // 0xC8
	ModelPart parts[3]; // 0xD4

	// puts part `no` into the world slot or takes it out; the u32 index gives
	// the part its own induction register, as the retail has it
	inline void SetShow(u32 no, int show)
	{
		if (show) {
			if (parts[no].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), parts[no].clump);
				parts[no].added = 1;
			}
		} else if (parts[no].added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7278), parts[no].clump);
			parts[no].added = 0;
		}
	}

	TObjKazariObj(TObject* parent)
	    : TObject(parent)
	{
		KazariobjParam* param = (KazariobjParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjKazariObj;
		DispTime  = 0xEC;
		if (param->kind >= 3) {
			param->kind = 0;
		}
		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;
		for (int i = 0; i < 3; i++) {
			KazariobjEntry* file = &kazariobjTable[i];
			parts[i].clump       = fn_80150588(file->model);
			parts[i].added       = 0;
			SetShow(i, i == param->kind);
		}
		InitShare(*this, &kazariobjCclInfo[param->kind], 1, 4);
		unkB8 = 0;
	}
	virtual ~TObjKazariObj();
};

extern "C" void kazariobjCreate(void)
{
	new TObjKazariObj(lbl_8042C110);
}
