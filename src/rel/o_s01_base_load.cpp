#include "types.h"

// The lazy load of the stage-01 object base. The first object of each kind
// registers that kind's clump with the sound system and attaches its mesh to
// the shared cache slot; later objects of the same kind find the flag already
// set and do nothing.
//
// The claim is .text 0x0007CE84 to 0x0007CF2C and nothing else. It reads no
// constant, so it owns no rodata. The four tables stay in the module's data and
// bss and are renamed to the names below.
//
// It belongs to the class rel/o_s01_base.cpp reconstructs: it reads the kind
// byte at +0x30 and the mesh at +0x34, which is where that class's volume puts
// them, and the mesh is the one rel/o_s01_base_collision.cpp builds and
// releases.
//
// There are three kinds. The flag table is 0xC bytes, the cache is 0xCC and the
// stride is 68, and 0xCC is three times 68; dtk sizes the clump and volume
// tables larger only because nothing references past their third entry yet.
//
// The kind byte is read three times rather than kept in a local. The compiler
// folds the first three lookups onto one index because nothing separates them,
// but the two calls invalidate it either side, which is what the original does.
//
// This unit is a fragment: the functions either side of it, at 0x0007CDA4 and
// 0x0007CF2C, share compiler-generated rodata with two more in the same
// translation unit and have to be carved as one group of five.

typedef struct Volume {
	s8 kind;       // 0x00
	u8 unk1[0x03]; // 0x01
	void* mesh;    // 0x04
	u8 unk8[0x80]; // 0x08
} Volume;          // 0x88

typedef struct S01ObjectBase {
	u8 unk0[0x30]; // 0x00
	Volume volume; // 0x30
} S01ObjectBase;   // 0xB8

typedef struct MeshCacheSlot {
	u8 unk0[68]; // 0x00
} MeshCacheSlot; // 0x44

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void* s01ObjectBaseClumps[];
extern "C" s32 s01ObjectBaseLoaded[];
extern "C" f32 s01ObjectBaseVolumes[];
extern "C" MeshCacheSlot s01ObjectBaseMeshCache[];

extern "C" void fn_8011B844(void* clump, f32 volume);
extern "C" void fn_8005BF88(void);
extern "C" void fn_8014FFBC(void* mesh, void* callback, MeshCacheSlot* slot);

extern "C" void s01ObjectBaseLoad(S01ObjectBase* object)
{
	if (s01ObjectBaseLoaded[object->volume.kind] == 0) {
		fn_8011B844(
		    s01ObjectBaseClumps[object->volume.kind], s01ObjectBaseVolumes[object->volume.kind]);

		fn_8014FFBC(
		    object->volume.mesh, (void*)fn_8005BF88, &s01ObjectBaseMeshCache[object->volume.kind]);

		s01ObjectBaseLoaded[object->volume.kind] = 1;
	}
}
