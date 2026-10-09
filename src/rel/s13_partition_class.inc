// TObjS13Partition, shared by rel/s13_partition_create.cpp, which defines S13_PARTITION_CTOR
// as inline so its factory inlines the constructor, and rel/s13_partition_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjS13Partition(TObject* parent);
	virtual ~TObjS13Partition();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S13_PARTITION_CTOR TObjS13Partition::TObjS13Partition(TObject* parent)
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
