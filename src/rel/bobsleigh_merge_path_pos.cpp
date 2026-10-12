#include "types.h"

// TObjBobsleigh::GetMergePathPos (the PS2 build's name): the point at the
// given index along the merged course. The index wraps at the course's length;
// the merged road pieces are walked until the one holding it, whose ID is
// reported when asked. A piece is a pair of paths: the main one, or the other
// one when the asked path (0 or 1) does not match the piece's kind; a reversed
// piece counts from its far end.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RoadPath {
	s16 unk00; // 0x00
	s16 count; // 0x02
	u8 unk04[0x4];
	RwV3d* points; // 0x08
} RoadPath;

typedef struct MergeRoad MergeRoad;
struct MergeRoad {
	RoadPath* main;  // 0x00
	RoadPath* other; // 0x04
	s32 id;          // 0x08
	u8 unk0C[0x4];
	MergeRoad* next; // 0x10
	s32 start;       // 0x14
	s32 kind;        // 0x18
	s32 reversed;    // 0x1C
};

typedef struct MergeRoadData {
	u8 unk00[0x4];
	s32 length; // 0x04
	u8 unk08[0x4];
	MergeRoad* first; // 0x0C
} MergeRoadData;

extern "C" RwV3d*
GetMergePathPos__13TObjBobsleighFP13MergeRoadDataiQ213TObjBobsleigh15ENUM_MERGE_PATHPi(
    void* object, MergeRoadData* data, int index, int which, s32* id)
{
	MergeRoad* road = data->first;
	int wrapped;
	int point;
	RoadPath* path;
	RwV3d* points;

	wrapped = index % data->length;
	for (;;) {
		if (id != NULL) {
			*id = road->id;
		}
		point = wrapped - road->start;
		path  = road->main;
		if (point < path->count) {
			if ((road->kind == 0 && which == 0) || (road->kind != 0 && which == 1)) {
				path = road->main;
			} else {
				path = road->other;
			}
			points = path->points;
			if (road->reversed != 0) {
				return &points[path->count - 1 - point];
			}
			return &points[point];
		}
		road = road->next;
	}
}
