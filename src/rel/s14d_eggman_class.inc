// TObjS14Eggman, shared by rel/s14d_eggman_create.cpp, which defines S14D_EGGMAN_CTOR
// as inline so its factory inlines the constructor, and rel/s14d_eggman_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct PlacementRecord {
	s32 count; // 0x00
};

extern "C" char* CL_TObjS14Eggman;
extern "C" u32 s14EggmanModelInfo[];
extern "C" const f32 s14EggmanOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" void fn_9_D3360(void);
extern "C" void fn_8014FFBC(RpClump* clump, void (*callback)(void), u32 light);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS14Eggman : public TObject, public TObjSetObj
{
public:
	u8 unk30;       // 0x30
	u16 unk32;      // 0x32
	RpClump* clump; // 0x34

	TObjS14Eggman(TObject* parent);
	virtual void Exec();
	virtual ~TObjS14Eggman();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S14D_EGGMAN_CTOR TObjS14Eggman::TObjS14Eggman(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjS14Eggman;
	DispTime  = 0x38;

	fn_9_75A80(s14EggmanModelInfo, 0, &clump, 0);
	if (clump != NULL) {
		fn_8014FFBC(
		    clump, fn_9_D3360, ((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
	}

	if (ObjParam->originalWork == NULL) {
		PlacementRecord* record = new PlacementRecord;
		ObjParam->originalWork  = record;
		record->count           = 0;
	}

	unk32 = 0;
	if (clump != NULL) {
		void* frame = *(void**)((u8*)clump + 4);
		f32 sin     = fn_800D7B00(ObjParam->setData.ang.y);
		fn_80195790((u8*)frame + 0x10, &AxisY,
		    s14EggmanOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sin, 0);
		fn_8019E880(frame);
		fn_8019EB94(frame, &ObjParam->setData.pos, 2);
	}
	unk30 = 0;
}
