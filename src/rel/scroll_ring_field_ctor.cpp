#include "types.h"

// TObjRingSubstance's constructors (the PS2 build's struct, one ring of a
// ring group; scrollRingFieldCtor and scrollRingFieldCtorInit here, after the
// destructor's name). The most derived object first points its two empty
// virtual bases at the ends of the ring; then the collision and the ground
// movement are built, the ring takes its vtable and its collision one sphere.
// The second constructor also hands the ring its group and number (the third
// virtual slot, Init) first.

extern "C" u8 ringCclInfo[];
extern "C" void* scrollRingFieldVtable[];

extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void __ct__16OBJ_MoveOnGroundFv(void* move);
extern "C" void fn_8003BF04(void* colli, void* info, s32 count, u8 kind);

struct RingSubstanceData {
	u8 unk00[0xD8];
};

struct RingSubstance : public RingSubstanceData {
	virtual void vslot0();
	virtual void Init(void* group, s32 number);
};

extern "C" void* scrollRingFieldCtor(void* object, s16 most)
{
	u8* base = (u8*)object;

	if (most) {
		*(void**)(base + 0xC0) = base + 0xE4;
		*(void**)(base + 0xC4) = base + 0xE5;
	}
	__ct__7C_COLLIFv(object);
	__ct__16OBJ_MoveOnGroundFv(base + 0x88);
	*(void**)(base + 0xD8) = scrollRingFieldVtable;
	fn_8003BF04(object, ringCclInfo, 1, 6);
	return object;
}

extern "C" void* scrollRingFieldCtorInit(void* object, s16 most, void* group, s32 number)
{
	u8* base = (u8*)object;

	if (most) {
		*(void**)(base + 0xC0) = base + 0xE4;
		*(void**)(base + 0xC4) = base + 0xE5;
	}
	__ct__7C_COLLIFv(object);
	__ct__16OBJ_MoveOnGroundFv(base + 0x88);
	*(void**)(base + 0xD8) = scrollRingFieldVtable;
	((RingSubstance*)object)->Init(group, number);
	fn_8003BF04(object, ringCclInfo, 1, 6);
	return object;
}
