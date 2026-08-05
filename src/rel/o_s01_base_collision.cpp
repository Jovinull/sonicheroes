#include "types.h"

// Two more methods of the stage-01 object base whose update, destructor,
// constructor and editor callback are in rel/o_s01_base.cpp: an empty slot and
// the collision-mesh release.
//
// The claim is .text 0x0007CCD8 to 0x0007CD38 and nothing else. Neither
// function reads a constant, so the pair owns no rodata.
//
// This is the same translation unit as rel/o_s01_base.cpp, split across two
// sources rather than one because the eight bytes at 0x0007CCD0 between them
// are the adjustor thunk into the editor callback. CodeWarrior emits a thunk
// only for a virtual member of a class with a second base, and the base's class
// name is not recoverable, so writing one would mean inventing a mangled symbol
// for it. The thunk is left in the automatic split until the class is
// identified, and the two sources meet either side of it.
//
// The mesh release takes the scene from the mesh itself rather than from the
// world global that rel/ironball_dtor.cpp and rel/dashpanel_dtor.cpp use, which
// is why fn_8015BD78 appears here and not there.

typedef struct VolumeBody VolumeBody;

typedef struct Volume {
	u8 unk0[0x04];    // 0x00
	void* mesh;       // 0x04
	u16 flags;        // 0x08
	u8 unk0A[0x06];   // 0x0A
	VolumeBody* body; // 0x10
	u8 unk14[0x74];   // 0x14
} Volume;             // 0x88

typedef struct S01ObjectBase {
	u8 unk0[0x30]; // 0x00
	Volume volume; // 0x30
} S01ObjectBase;   // 0xB8

extern "C" void* fn_8015BD78(void* mesh);
extern "C" void fn_8015BBF8(void* scene, void* mesh);
extern "C" void fn_80150958(void* mesh);

extern "C" void s01ObjectBaseNoop(void) { }

// Unregisters the collision mesh from the scene that owns it and drops the
// reference. The resource manager owns the allocation.
extern "C" void s01ObjectBaseReleaseMesh(S01ObjectBase* object)
{
	void* mesh = object->volume.mesh;

	if (mesh != NULL) {
		fn_8015BBF8(fn_8015BD78(mesh), mesh);
		fn_80150958(object->volume.mesh);
		object->volume.mesh = NULL;
	}
}
