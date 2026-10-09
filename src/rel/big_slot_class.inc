// TObjBigSlot, shared by rel/big_slot_create.cpp, which defines BIG_SLOT_CTOR
// as inline so its factory inlines the constructor, and rel/big_slot_ctor.cpp,
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

struct SlotReel {
	s32 unk0; // 0x00
	s32 unk4; // 0x04
	s32 unk8; // 0x08
	s32 unkC; // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjBigSlot;
extern "C" ModelFile bigSlotModelFiles[3];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjBigSlot : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[3]; // 0xD0
	s32 unkE8;          // 0xE8
	SlotReel reels[3];  // 0xEC

	TObjBigSlot(TObject* parent);
	virtual void Exec();
	virtual ~TObjBigSlot();
	virtual void EditOnChange(SETDATA_PARAM*);
};

BIG_SLOT_CTOR TObjBigSlot::TObjBigSlot(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBigSlot;
	DispTime  = 0x11C;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 3; i++) {
		ModelFile* file = &bigSlotModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
	}
	for (int k = 0; k < 3; k++) {
		reels[k].unk0 = 0;
		reels[k].unk8 = 0;
		reels[k].unk4 = 0;
	}
	unkE8 = 0;
}
