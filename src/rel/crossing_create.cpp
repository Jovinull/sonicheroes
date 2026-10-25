#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// crossingCreate, the factory rel/crossing_register.cpp puts in the editor
// record: a new TObjCrossing (the class name its constructor stores) that
// copies the set data's position and angle and clones its thirteen models,
// adding the first to its world slot (the others are only taken out of theirs
// should they be in), takes the module's shape for its collision block, starts
// in state 3 when the set data's condition has bit 0x10000 (else 0) and clears
// the rest of its state. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp); the part loop is rel/big_chip_class.inc's.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct CrossingPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

extern "C" char* CL_TObjCrossing;
extern "C" ModelFile crossingModelFiles[13];
extern "C" CCL_INFO crossingCclInfo;
extern "C" const f32 lbl_6_rodata_1288;
extern "C" const f32 lbl_6_rodata_1298;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);
extern "C" void* memset(void* dst, s32 value, u32 size);

// C_COLLI::InitShare (fn_8003BF04), as rel/bobin_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjCrossing : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;              // 0xB8
	sAngle ang;             // 0xC4
	CrossingPart parts[13]; // 0xD0
	s32 state;              // 0x138
	s32 unk13C;             // 0x13C
	s32 unk140;             // 0x140
	f32 unk144;             // 0x144
	u8 unk148[0x20];        // 0x148
	u8 unk168[0x184];       // 0x168

	TObjCrossing(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjCrossing;
		DispTime  = 0x2EC;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		for (int i = 0; i < 13; i++) {
			ModelFile* file = &crossingModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			if (i == 0) {
				if (parts[i].added == 0) {
					fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
					parts[i].added = 1;
				}
			} else {
				if (parts[i].added == 1) {
					fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
					parts[i].added = 0;
				}
			}
		}
		InitShare(*this, &crossingCclInfo, 1, 4);
		if (ObjParam->setData.condition.Flag & 0x10000) {
			state = 3;
		} else {
			state = 0;
		}
		unk13C = 0;
		unk144 = lbl_6_rodata_1288;
		unk140 = 0;
		unk144 = lbl_6_rodata_1298;
		memset(unk148, 0, 0x20);
	}
	virtual ~TObjCrossing();
};

extern "C" void crossingCreate(void)
{
	new TObjCrossing(lbl_8042C110);
}
