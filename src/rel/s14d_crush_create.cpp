#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14dCrushCreate, the factory rel/s14d_crush_register.cpp puts in the editor
// record for TObjS14Crush, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The module's loader (fn_9_75A80) builds the clump from the class's model
// description; when there is one, every atomic gets the class's render
// callback and the placement's light. The first object of a placement leaves a
// one-word record on it. The clump's frame is then turned about Y by the
// placement's angle, as one minus the cosine and the sine the matrix call
// takes, and moved to the placement. The 1 is the module's constant, read as
// an external.

struct PlacementRecord {
	s32 count; // 0x00
};

extern "C" char* CL_TObjS14Crush;
extern "C" u32 s14CrushModelInfo[];
extern "C" const f32 s14CrushOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" void fn_9_D4B8C(void);
extern "C" void fn_8014FFBC(RpClump* clump, void (*callback)(void), u32 light);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS14Crush : public TObject, public TObjSetObj
{
public:
	u8 unk30;       // 0x30
	u16 unk32;      // 0x32
	RpClump* clump; // 0x34

	TObjS14Crush(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14Crush;
		DispTime  = 0x38;

		fn_9_75A80(s14CrushModelInfo, 0, &clump, 0);
		if (clump != NULL) {
			fn_8014FFBC(
			    clump, fn_9_D4B8C, ((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
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
			    s14CrushOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sin, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
		unk30 = 0;
	}
	virtual ~TObjS14Crush();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s14dCrushCreate(void)
{
	new TObjS14Crush(lbl_8042C110);
}
