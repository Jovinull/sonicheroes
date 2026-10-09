// TObjBigDice, shared by rel/big_dice_create.cpp, which defines BIG_DICE_CTOR
// as inline so its factory inlines the constructor, and rel/big_dice_ctor.cpp,
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

	TObjBigDice(TObject* parent);
	virtual ~TObjBigDice();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BIG_DICE_CTOR TObjBigDice::TObjBigDice(TObject* parent)
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
