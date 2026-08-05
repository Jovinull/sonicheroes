#include "types.h"

// Three more methods of the stage-01 object base whose update, destructor,
// constructor and editor callback are in rel/o_s01_base.cpp: an empty slot, the
// collision-mesh release and its counterpart that builds the mesh.
//
// The claim is .text 0x0007CCD8 to 0x0007CDA4 and nothing else. None of the
// three reads a constant, so they own no rodata; the mesh table at data 0xA210
// and the world global are only referenced, not defined here.
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
// is why fn_8015BD78 appears here and not there. The build path does reach the
// world global, but at +0x72AC rather than the +0x725C those two use, so the
// field is given its own name here rather than reusing theirs.

typedef struct VolumeBody VolumeBody;

typedef struct Volume {
	s8 kind;          // 0x00
	u8 unk1[0x03];    // 0x01
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

typedef struct World {
	u8 unk0[0x72AC];      // 0x0000
	void* collisionScene; // 0x72AC
} World;

// Three meshes, chosen by the volume's kind byte.
extern "C" void* s01ObjectBaseMeshTable[3];
extern "C" World* lbl_8042C1D0;

extern "C" void* fn_80150588(void* source);
extern "C" void* fn_8015BD78(void* mesh);
extern "C" void fn_8015BB08(void* scene, void* mesh);
extern "C" void fn_8005E394(void* mesh, s32 flags);
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

// Builds the collision mesh for the volume's kind and registers it with the
// world's collision scene.
extern "C" void s01ObjectBaseCreateMesh(S01ObjectBase* object)
{
	object->volume.mesh = fn_80150588(s01ObjectBaseMeshTable[object->volume.kind]);

	fn_8015BB08(lbl_8042C1D0->collisionScene, object->volume.mesh);
	fn_8005E394(object->volume.mesh, 0);
}
