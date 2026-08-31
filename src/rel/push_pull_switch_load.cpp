#include "types.h"

// TObjPushPullSwitch's asset hooks: the reset, the unload and the load.
//
// The claim is .text 0x516F8 to 0x518D4 and nothing else. Every object it
// touches lives in the module's own .bss and .data and is reached as an
// external, renamed to the shared names below in each module's symbols.txt.
// The factory at 0x518D4 stays assembly for the reason recorded in
// docs/object-post-processors.md, and the record that names all four is
// already carved as rel/push_pull_switch_register.cpp.
//
// The run is the same in the nine stage modules that share this revision of
// the engine core: 01D, 03D, 05D, 07D, 09D, 11D, 31D, 32D and 33D.
//
// Naming comes from the strings the load reads. The model is "OBJ_SWB.DFF" and
// the six names it looks up are "o_on", "o_on2", "o_on3", "o_off", "o_off2"
// and "o_off3", so the six archive results are the switch's lit and unlit
// textures in that order. Which of the two materials the walk below ends up
// finding is not decided by the names, so `pushPullSwitchMaterials` is left
// with the neutral name.

typedef struct Archive Archive;

extern "C" Archive* fn_8005EC0C(void);
extern "C" void* fn_801A4BBC(Archive* archive, const char* name);
extern "C" void* fn_8005EA04(const char* name);
extern "C" void* fn_8005E394(void* model, s32 index);
extern "C" void* fn_8005E410(void* model, void* current, const char* name);
extern "C" void* memset(void* dst, s32 value, s32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* pushPullSwitchModel;
extern "C" void* pushPullSwitchMaterials[2];
extern "C" void* pushPullSwitchMesh;
extern "C" void* pushPullSwitchOnTexture;
extern "C" void* pushPullSwitchOnTexture2;
extern "C" void* pushPullSwitchOnTexture3;
extern "C" void* pushPullSwitchOffTexture;
extern "C" void* pushPullSwitchOffTexture2;
extern "C" void* pushPullSwitchOffTexture3;
extern "C" const char* pushPullSwitchTextureNames[6];
extern "C" char pushPullSwitchModelName[];

typedef struct PushPullSwitch {
	u8 unk0[0x30];  // 0x00
	void* instance; // 0x30
} PushPullSwitch;   // 0x34

// Only the instance block is cleared; the object itself is left alone.
extern "C" void pushPullSwitchReset(PushPullSwitch* object)
{
	void* instance = object->instance;

	if (instance != NULL) {
		memset(instance, 0, 0x14);
	}
}

// The textures and the mesh are deliberately not cleared here.
extern "C" void pushPullSwitchUnload(void)
{
	pushPullSwitchModel        = NULL;
	pushPullSwitchMaterials[0] = NULL;
	pushPullSwitchMaterials[1] = NULL;
}

static void pushPullSwitchFindMaterials(void)
{
	void* previous;
	s32 i;
	void** slot;
	const char** name;

	previous = NULL;

	for (i = 0, slot = pushPullSwitchMaterials; i < 2; i++) {
		*slot = NULL;
		name  = pushPullSwitchTextureNames;

		while (*slot == NULL) {
			*slot = fn_8005E410(pushPullSwitchModel, previous, *name);
			name++;
		}

		previous = *slot;
		slot++;
	}
}

extern "C" void pushPullSwitchLoad(void)
{
	Archive* archive;

	archive = fn_8005EC0C();

	pushPullSwitchOnTexture   = fn_801A4BBC(archive, pushPullSwitchTextureNames[0]);
	pushPullSwitchOnTexture2  = fn_801A4BBC(archive, pushPullSwitchTextureNames[1]);
	pushPullSwitchOnTexture3  = fn_801A4BBC(archive, pushPullSwitchTextureNames[2]);
	pushPullSwitchOffTexture  = fn_801A4BBC(archive, pushPullSwitchTextureNames[3]);
	pushPullSwitchOffTexture2 = fn_801A4BBC(archive, pushPullSwitchTextureNames[4]);
	pushPullSwitchOffTexture3 = fn_801A4BBC(archive, pushPullSwitchTextureNames[5]);

	pushPullSwitchModel = fn_8005EA04(pushPullSwitchModelName);
	pushPullSwitchMesh  = fn_8005E394(pushPullSwitchModel, 0);

	// Each slot takes the first material the model answers with, resuming the
	// walk from the one before it so the two never land on the same material.
	pushPullSwitchFindMaterials();
}
