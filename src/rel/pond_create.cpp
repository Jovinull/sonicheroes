#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// pondCreate, the factory rel/pond_register.cpp puts in the editor record: a
// new TObjPond (the class name its constructor stores) that copies the set
// data's position and angle and, for each of the pond's 3 entries, clones its
// two models and adds them to the world slots the entry names. The allocation
// is a real new-expression of the class (rel/sample1_create.cpp); the part
// helper takes a u32 index, as rel/kazariobj_create.cpp's does.

typedef struct PondEntry {
	const char* name;  // 0x00
	const char* name2; // 0x04
	void* archive;     // 0x08
	s32 world;         // 0x0C
	s32 world2;        // 0x10
	void* model;       // 0x14
	void* model2;      // 0x18
} PondEntry;           // 0x1C

struct PondPart {
	RpClump* clump;  // 0x00
	RpClump* clump2; // 0x04
	s32 added;       // 0x08
};

extern "C" char* CL_TObjPond;
extern "C" PondEntry pondTable[3];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjPond : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	PondPart parts[3]; // 0xD0

	// puts both of part `no`'s clumps into their entry's world slots
	inline void Show(u32 no)
	{
		if (parts[no].added == 0) {
			fn_8015BB08(
			    *(void**)(lbl_8042C1D0 + 0x7250 + pondTable[no].world * 4), parts[no].clump);
			fn_8015BB08(
			    *(void**)(lbl_8042C1D0 + 0x7250 + pondTable[no].world2 * 4), parts[no].clump2);
			parts[no].added = 1;
		}
	}

	TObjPond(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjPond;
		DispTime  = 0xF4;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		for (int i = 0; i < 3; i++) {
			PondEntry* file = &pondTable[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].clump2 = fn_80150588(file->model2);
			parts[i].added  = 0;
			Show(i);
		}
	}
	virtual ~TObjPond();
};

extern "C" void pondCreate(void)
{
	new TObjPond(lbl_8042C110);
}
