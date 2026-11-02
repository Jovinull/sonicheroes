#include "types.h"

// The capture enemy's marker lookups, the same in the seven stage modules that
// carry the capture. captureFindMarker walks the placement list given to the
// marker object (kind 0x65) with the given ID and hands back its place;
// captureFindHome looks up the enemy's home marker in its placement's list
// (inlined) and raises it by the module's 40. Both return whether a marker
// was found.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureSetObj {
	RwV3d pos; // 0x00
	u8 unk0C[0x1C];
	u16 kind; // 0x28
	u8 pad2A[0x2];
	s32* param; // 0x2C
	u8 unk30[0x8];
	struct CaptureSetObj* next; // 0x38
} CaptureSetObj;

typedef struct CaptureSetLists {
	u8 unk00[0x30];
	CaptureSetObj* lists[1]; // 0x30
} CaptureSetLists;

typedef struct CaptureSetData {
	u8 unk00[0x2A];
	u8 list; // 0x2A
} CaptureSetData;

typedef struct Capture {
	u8 unk000[0xB0];
	CaptureSetData* setData; // 0x0B0
	u8 unk0B4[0x1F4];
	RwV3d home; // 0x2A8
	s32 homeId; // 0x2B4
} Capture;

extern "C" CaptureSetLists* lbl_8042C298;
extern "C" const f32 captureSearchDrop;

static inline s32 captureMarkerLookup(RwV3d* out, s32 id, u8 list)
{
	CaptureSetObj* first = lbl_8042C298->lists[list];
	CaptureSetObj* set   = first;

	if (first == NULL) {
		return 0;
	}
	while (set != NULL) {
		if (set->kind == 0x65) {
			s32* param = set->param;

			if (param != NULL && *param == id) {
				out->x = set->pos.x;
				out->y = set->pos.y;
				out->z = set->pos.z;
				return 1;
			}
		}
		set = set->next;
	}
	return 0;
}

extern "C" s32 captureFindHome(Capture* object)
{
	s32 found = captureMarkerLookup(&object->home, object->homeId, object->setData->list);

	object->home.y += captureSearchDrop;
	return found;
}

extern "C" s32 captureFindMarker(Capture* object, RwV3d* out, s32 id, u8 list)
{
	CaptureSetObj* first = lbl_8042C298->lists[list];
	CaptureSetObj* set   = first;

	if (first == NULL) {
		return 0;
	}
	while (set != NULL) {
		if (set->kind == 0x65) {
			s32* param = set->param;

			if (param != NULL && *param == id) {
				out->x = set->pos.x;
				out->y = set->pos.y;
				out->z = set->pos.z;
				return 1;
			}
		}
		set = set->next;
	}
	return 0;
}
