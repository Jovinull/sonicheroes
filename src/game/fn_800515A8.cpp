// Returns whether the squared distance between the two vectors is below the object's radius field.
#include "game/matrix.h"

struct R800515A8 {
	unsigned char pad0[8];
	float f8;
};
struct Obj800515A8 {
	RwV3d* f0;
	R800515A8* f4;
	unsigned char pad8[4];
	RwV3d* fC;
};

void SubVectorReturnToVector(const RwV3d* a, const RwV3d* b, RwV3d* out);

extern "C" int fn_800515A8(int unused, Obj800515A8* o)
{
	RwV3d d;
	SubVectorReturnToVector(o->fC, o->f0, &d);
	return d.z * d.z + (d.x * d.x + d.y * d.y) < o->f4->f8;
}
