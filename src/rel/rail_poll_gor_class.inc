// TObjRailPollGor, shared by rel/rail_poll_gor_create.cpp, which defines RAIL_POLL_GOR_CTOR
// as inline so its factory inlines the constructor, and rel/rail_poll_gor_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// One of the module's animated model files.
struct AnimModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
	u8 unk10[0xC];    // 0x10
};

struct RpHAnimHierarchy;

struct AnimPart {
	RpClump* clump;              // 0x00
	RpHAnimHierarchy* hierarchy; // 0x04
	s32 added;                   // 0x08
};

extern "C" char* CL_TObjRailPollGor;
extern "C" AnimModelFile railPollGorModelFiles[2];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" RpHAnimHierarchy* fn_800F3074(RpClump* clump);
extern "C" RpHAnimHierarchy* fn_8013F3A4(RpHAnimHierarchy* hierarchy);

class TObjRailPollGor : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;         // 0xB8
	sAngle ang;        // 0xC4
	s32 unkD0;         // 0xD0
	AnimPart parts[2]; // 0xD4

	TObjRailPollGor(TObject* parent);
	virtual ~TObjRailPollGor();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

RAIL_POLL_GOR_CTOR TObjRailPollGor::TObjRailPollGor(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjRailPollGor;
	DispTime  = 0xEC;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 2; i++) {
		AnimModelFile* file = &railPollGorModelFiles[i];
		parts[i].clump      = fn_80150588(file->model);
		parts[i].hierarchy  = fn_800F3074(parts[i].clump);
		parts[i].added      = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
		if (parts[i].hierarchy != NULL) {
			fn_8013F3A4(parts[i].hierarchy);
		}
	}
	unkD0 = 0;
}
