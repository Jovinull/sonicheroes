#include "types.h"

// The scroll ring's EditOnChange (scrollRingEditOnChange here): it does what
// the ring's does (rel/ring_object_edit.cpp: kind, count and the two spacings
// within their bounds, the editor's ring fields named by kind), then keeps its
// own speed and wait from going negative and names its editor's fields by the
// same kind.

typedef struct ScrollRingParams {
	s16 kind;     // 0x00
	s16 count;    // 0x02
	f32 spacingA; // 0x04
	f32 spacingB; // 0x08
	u8 pad0C[0xC];
	s16 wait; // 0x18
	u8 pad1A[0x2];
	f32 speed; // 0x1C
} ScrollRingParams;

typedef struct ScrollRingEdit {
	u8 unk00[0x2C];
	ScrollRingParams* params; // 0x2C
} ScrollRingEdit;

extern "C" const char* ringObjectFieldNames[];
extern "C" const char* scrollRingObjectFieldNames[];
extern "C" const char* ringObjectFields0[];
extern "C" const char* ringObjectFields1[];
extern "C" const char* ringObjectFields2[];
extern "C" const char* ringObjectFields3[];

extern "C" const f32 scrollRingStopped[1];
extern "C" const f32 ringObjectBound1[1];

extern "C" void scrollRingEditOnChange(void* object, ScrollRingEdit* edit)
{
	ScrollRingParams* params = edit->params;
	const f32* limit;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 5) {
		params->kind = 4;
	}
	if (params->count < 0) {
		params->count = 0;
	}
	if (params->count > 127) {
		params->count = 127;
	}
	if (params->spacingA < *(limit = scrollRingStopped)) {
		params->spacingA = *limit;
	}
	if (params->spacingA > *(limit = ringObjectBound1)) {
		params->spacingA = *limit;
	}
	if (params->spacingB < *(limit = scrollRingStopped)) {
		params->spacingB = *limit;
	}
	if (params->spacingB > *(limit = ringObjectBound1)) {
		params->spacingB = *limit;
	}
	ringObjectFieldNames[0] = ringObjectFields0[params->kind];
	ringObjectFieldNames[1] = ringObjectFields1[params->kind];
	ringObjectFieldNames[2] = ringObjectFields2[params->kind];
	ringObjectFieldNames[3] = ringObjectFields3[params->kind];
	if (params->speed < *(limit = scrollRingStopped)) {
		params->speed = *limit;
	}
	if (params->wait < 0) {
		params->wait = 0;
	}
	scrollRingObjectFieldNames[0] = ringObjectFields0[params->kind];
	scrollRingObjectFieldNames[1] = ringObjectFields1[params->kind];
	scrollRingObjectFieldNames[2] = ringObjectFields2[params->kind];
	scrollRingObjectFieldNames[3] = ringObjectFields3[params->kind];
}
