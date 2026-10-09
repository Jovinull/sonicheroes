#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13TsuitateCreate, the factory the editor record for TObjS13Partition
// points at, in stage13D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The module's loader (fn_9_75A80) builds the clump from the class's model
// description and the collision base takes two of the module's shapes. The
// clump's frame is then turned about Y by the placement's angle and moved to
// the placement, as in rel/s14d_crush_create.cpp. The 1 is the module's
// constant, read as an external.

extern "C" char* CL_TObjS13Partition;
extern "C" u32 s13PartitionModelInfo[];
extern "C" CCL_INFO s13PartitionCclInfo[2];
extern "C" const f32 s13PartitionOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS13Partition : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 unkB8;       // 0xB8
	RpClump* clump; // 0xBC

	TObjS13Partition(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS13Partition;
		DispTime  = 0xC0;

		fn_9_75A80(s13PartitionModelInfo, 0, &clump, 0);
		Init(s13PartitionCclInfo, 2, 4);

		if (clump != NULL) {
			void* frame = *(void**)((u8*)clump + 4);
			f32 sin     = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790((u8*)frame + 0x10, &AxisY,
			    s13PartitionOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sin, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &ObjParam->setData.pos, 2);
		}
		unkB8 = 0;
	}
	virtual ~TObjS13Partition();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s13TsuitateCreate(void)
{
	new TObjS13Partition(lbl_8042C110);
}
