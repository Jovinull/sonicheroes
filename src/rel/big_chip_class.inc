// TObjBigChip, shared by rel/big_chip_create.cpp, which defines BIG_CHIP_CTOR
// as inline so its factory inlines the constructor, and rel/big_chip_ctor.cpp,
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

struct ChipPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjBigChip;
extern "C" ModelFile bigChipModelFiles[5];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjBigChip : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	ChipPart parts[5]; // 0xD0

	TObjBigChip(TObject* parent);
	virtual void Exec();
	virtual ~TObjBigChip();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BIG_CHIP_CTOR TObjBigChip::TObjBigChip(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBigChip;
	DispTime  = 0xF8;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 5; i++) {
		ModelFile* file = &bigChipModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
	}
	EditOnChange(&ObjParam->setData);
}
