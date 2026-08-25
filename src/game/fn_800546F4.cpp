#include "types.h"

// Prunes geometrically equivalent nodes from a linked list, preferring the
// node selected by its flags and squared vector length.

struct Fn800546F4Vector {
	f32 x;
	f32 y;
	f32 z;
};

struct Fn800546F4Lookup {
	u16 vectorIndex;
	u8 padding[10];
	Fn800546F4Vector normal;
	u8 padding2[8];
};

struct Fn800546F4Node {
	u16 lookupIndex;
	s16 flags;
	f32 x;
	f32 y;
	f32 z;
	u8 padding[24];
	Fn800546F4Node* previous;
	Fn800546F4Node* next;
};

struct Fn800546F4List {
	u32 count;
	Fn800546F4Node* first;
	Fn800546F4Node* last;
};
struct Fn800546F4Context {
	u32 padding;
	Fn800546F4Lookup* lookups;
	Fn800546F4Vector* vectors;
};

extern "C" f64 lbl_8042D3B8;
extern "C" void fn_80053FB8(Fn800546F4List*, Fn800546F4Node*);
extern "C" f64 __fabs(f64);

extern "C" void fn_800546F4(Fn800546F4Context* context, Fn800546F4List* list)
{
	Fn800546F4Lookup* currentLookup;
	Fn800546F4Vector* currentVector;
	Fn800546F4Node* current = list->first;
	f64 threshold           = lbl_8042D3B8;
	while (current != 0) {
		Fn800546F4Node* next      = current->next;
		currentLookup             = &context->lookups[current->lookupIndex];
		currentVector             = &context->vectors[currentLookup->vectorIndex];
		Fn800546F4Node* candidate = current->next;
		while (candidate != 0) {
			Fn800546F4Node* candidateNext     = candidate->next;
			Fn800546F4Lookup* candidateLookup = &context->lookups[candidate->lookupIndex];
			Fn800546F4Vector* candidateVector = &context->vectors[candidateLookup->vectorIndex];
			if ((f32)__fabs(currentLookup->normal.x - candidateLookup->normal.x) < threshold
			    && (f32)__fabs(currentLookup->normal.y - candidateLookup->normal.y) < threshold
			    && (f32)__fabs(currentLookup->normal.z - candidateLookup->normal.z) < threshold) {
				f32 projected = currentLookup->normal.x * (candidateVector->x - currentVector->x)
				    + currentLookup->normal.y * (candidateVector->y - currentVector->y)
				    + currentLookup->normal.z * (candidateVector->z - currentVector->z);
				if ((f32)__fabs(projected) < threshold) {
					s32 candidateFlags = candidate->flags & 0x70;
					if (candidateFlags != 0) {
						if ((current->flags & 0x70) == 0) {
							goto removeCandidate;
						}
					}
					if ((s32)(candidateFlags != 0) == (s32)((current->flags & 0x70) != 0)) {
						f32 currentLength = current->x * current->x + current->y * current->y
						    + current->z * current->z;
						f32 candidateLength = candidate->x * candidate->x
						    + candidate->y * candidate->y + candidate->z * candidate->z;
						if (currentLength < candidateLength) {
							goto removeCandidate;
						} else {
							goto removeCurrent;
						}
					}
					goto removeCurrent;
				removeCandidate:
					if (candidate == next)
						next = candidateNext;
					fn_80053FB8(list, candidate);
					goto nextCandidate;
				removeCurrent:
					fn_80053FB8(list, current);
					break;
				}
			}
		nextCandidate:
			candidate = candidateNext;
		}
		current = next;
	}
}
