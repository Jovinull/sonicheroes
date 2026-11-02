#include "types.h"

// The capture enemy's part setup (captureMakeParts here), the same in the
// seven stage modules that carry the capture: the parts still held are
// released (as captureReleaseParts does, inlined), then each of the six is
// made again from the module's loaded models.

typedef struct Capture {
	u8 unk000[0xE8];
	void* body; // 0x0E8
	u8 unk0EC[0x1EC];
	void* parts[5]; // 0x2D8
} Capture;

typedef struct RpClump RpClump;

extern "C" RpClump* captureModels[6];

extern "C" void fn_80150958(void* part);
extern "C" void* fn_80150588(RpClump* model);

// captureReleaseParts (rel/capture_release_parts.cpp), inlined.
static inline void captureFreeParts(Capture* object)
{
	if (object->parts[4] != NULL) {
		fn_80150958(object->parts[4]);
		object->parts[4] = NULL;
	}
	if (object->parts[3] != NULL) {
		fn_80150958(object->parts[3]);
		object->parts[3] = NULL;
	}
	if (object->parts[2] != NULL) {
		fn_80150958(object->parts[2]);
		object->parts[2] = NULL;
	}
	if (object->parts[1] != NULL) {
		fn_80150958(object->parts[1]);
		object->parts[1] = NULL;
	}
	if (object->parts[0] != NULL) {
		fn_80150958(object->parts[0]);
		object->parts[0] = NULL;
	}
	if (object->body != NULL) {
		fn_80150958(object->body);
		object->body = NULL;
	}
}

extern "C" void captureMakeParts(Capture* object)
{
	captureFreeParts(object);
	object->body     = fn_80150588(captureModels[0]);
	object->parts[0] = fn_80150588(captureModels[1]);
	object->parts[1] = fn_80150588(captureModels[2]);
	object->parts[2] = fn_80150588(captureModels[3]);
	object->parts[3] = fn_80150588(captureModels[4]);
	object->parts[4] = fn_80150588(captureModels[5]);
}
