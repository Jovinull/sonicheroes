#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjDuct's destructor (the class name is the string its constructor stores in
// the class-name word). It takes the object's clone out of its world slot when
// it was added and releases it, then the bases run down; the body of
// rel/roulette_dtor.cpp (the one-turn loop included). Only stage07D has it.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile ductModelFile;
extern "C" u8* lbl_8042C1D0;
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

// Exec comes first so that it is the key function and no unit of ours emits
// the vtable
class TObjDuct : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;      // 0xB8
	sAngle ang;     // 0xC4
	RpClump* clump; // 0xD0
	s32 added;      // 0xD4

	virtual void Exec();
	virtual ~TObjDuct();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TObjDuct::~TObjDuct()
{
	ModelFile* file = &ductModelFile;

	for (int i = 0; i < 1; i++) {
		if (added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
			added = 0;
		}
		fn_80150958(clump);
		clump = NULL;
	}
}
