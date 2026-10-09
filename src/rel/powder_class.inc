// TObjPowder, shared by rel/powder_create.cpp, which defines POWDER_CTOR
// as inline so its factory inlines the constructor, and rel/powder_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"
#include "MSL_C/string.h"

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// One grain of powder: its clump, whether it is in the world, and the rest of
// its state.
struct PowderPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
	u8 unk08[0x18];
};

// The placement's parameters: +4 picks the model file.
struct PowderParam {
	s32 unk0; // 0x00
	s32 kind; // 0x04
};

extern "C" char* CL_TObjPowder;
extern "C" ModelFile powderModelFiles[3];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;

class TObjPowder : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;             // 0xB8
	sAngle ang;            // 0xC4
	PowderPart parts[128]; // 0xD0
	s32 unk10D0;           // 0x10D0

	TObjPowder(TObject* parent);
	virtual void Exec();
	virtual ~TObjPowder();
	virtual void EditOnChange(SETDATA_PARAM*);
};

POWDER_CTOR TObjPowder::TObjPowder(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjPowder;
	DispTime  = 0x10D4;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	memset(parts, 0, sizeof(parts));
	unk10D0 = 0;
}
