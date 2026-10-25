#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bushCreate, the factory rel/bush_register.cpp puts in the editor record: a
// new TObjBush (the class name its constructor stores) that copies the set
// data's position and angle, clones the bush's model into the world slot at
// 0x7278 and takes the module's shape for its collision block (its third
// base), as rel/bobin_create.cpp does. The allocation is a real new-expression
// of the class (rel/sample1_create.cpp).

// the model file: its name, the archive it is read from and the model once
// loaded
typedef struct BushEntry {
	const char* name; // 0x00
	void* archive;    // 0x04
	void* model;      // 0x08
} BushEntry;

extern "C" char* CL_TObjBush;
extern "C" BushEntry bushModelFile[1];
extern "C" CCL_INFO bushCclInfo;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare (fn_8003BF04), as rel/bobin_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjBush : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;      // 0xB8
	RwV3d pos;      // 0xBC
	sAngle ang;     // 0xC8
	RpClump* clump; // 0xD4

	TObjBush(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBush;
		DispTime  = 0xD8;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		// a loop over the one model file: the retail keeps its hoisted pointers
		for (int i = 0; i < 1; i++) {
			clump = fn_80150588(bushModelFile[i].model);
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), clump);
		}
		InitShare(*this, &bushCclInfo, 1, 4);
		unkB8 = 0;
	}
	virtual ~TObjBush();
};

extern "C" void bushCreate(void)
{
	new TObjBush(lbl_8042C110);
}
