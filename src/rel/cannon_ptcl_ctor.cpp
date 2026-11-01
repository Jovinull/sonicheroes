#include "types.h"

// The constructor of the particle material in rel/cannon_ptcl_spawn.cpp, the
// same in the thirteen stage modules that share the engine core: the engine's
// material is built with flag 0x20000 and the description beside its virtual
// table, which then replaces the engine's.

extern "C" void fn_80065930(void* material, s32 flags, void* info);
extern "C" u8 cannonPtclInfo[];
extern "C" void* cannonPtclVtable[];

typedef struct CannonPtcl {
	u8 unk00[0x54];
	void** vtable; // 0x54
} CannonPtcl;

extern "C" CannonPtcl* cannonPtclCtor(CannonPtcl* material)
{
	fn_80065930(material, 0x20000, cannonPtclInfo);
	material->vtable = cannonPtclVtable;
	return material;
}
