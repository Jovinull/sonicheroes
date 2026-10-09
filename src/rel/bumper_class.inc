// TObjBumper, shared by rel/bumper_create.cpp, which defines BUMPER_CTOR
// as inline so its factory inlines the constructor, and rel/bumper_ctor.cpp,
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

struct BumperPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
	s32 unk8;       // 0x08
};

extern "C" char* CL_TObjBumper;
extern "C" ModelFile bumperModelFiles[4];
extern "C" CCL_INFO bumperCclInfo[5];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjBumper : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 unkB8[4];         // 0xB8
	RwV3d pos;           // 0xBC
	sAngle ang;          // 0xC8
	u8 unkD4[0x20];      // 0xD4
	BumperPart parts[4]; // 0xF4

	TObjBumper(TObject* parent);
	virtual ~TObjBumper();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BUMPER_CTOR TObjBumper::TObjBumper(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBumper;
	DispTime  = 0x124;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 4; i++) {
		parts[i].clump = fn_80150588(bumperModelFiles[i].model);
		parts[i].added = 0;
		parts[i].unk8  = 0;
	}

	Init(bumperCclInfo, 5, 4);
	if (parts[3].added == 0) {
		fn_8015BB08(
		    ((void**)(lbl_8042C1D0 + 0x7250))[bumperModelFiles[3].world], parts[3].clump);
		parts[3].added = 1;
	}

	EditOnChange(&ObjParam->setData);
	memset(unkD4, 0, sizeof(unkD4));
}
