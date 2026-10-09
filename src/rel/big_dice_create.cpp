#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bigdiceCreate, the factory the editor record for TObjBigDice points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp.
//
// The dice clones the four models the module keeps for
// "stg05_pn_ksaikoro01.dff" and its siblings into four parts, none of them in
// the world yet, and then applies its placement through its own EditOnChange,
// a virtual call through the first vtable.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct DicePart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjBigDice;
extern "C" ModelFile bigDiceModelFiles[4];
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);

class TObjBigDice : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	DicePart parts[4]; // 0xD0

	TObjBigDice(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBigDice;
		DispTime  = 0xF0;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		for (int i = 0; i < 4; i++) {
			parts[i].clump = fn_80150588(bigDiceModelFiles[i].model);
			parts[i].added = 0;
		}
		EditOnChange(&ObjParam->setData);
	}
	virtual ~TObjBigDice();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void bigdiceCreate(void)
{
	new TObjBigDice(lbl_8042C110);
}
