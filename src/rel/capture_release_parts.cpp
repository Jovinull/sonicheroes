#include "types.h"

// The capture enemy's part release (captureReleaseParts here), the same in the
// seven stage modules that carry the capture: each of its six parts still
// held goes back through fn_80150958, last first.

typedef struct Capture {
	u8 unk000[0xE8];
	void* body; // 0x0E8
	u8 unk0EC[0x1EC];
	void* parts[5]; // 0x2D8
} Capture;

extern "C" void fn_80150958(void* part);

extern "C" void captureReleaseParts(Capture* object)
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
