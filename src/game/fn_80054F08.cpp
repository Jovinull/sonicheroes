#include "types.h"

// Stationary sphere overlap query. It uses the same compact cell-index encoding
// as the swept query and releases its temporary traversal list while producing
// a contact list.
//
// GC/1.3.2 retains two redundant branches that source-level continue/goto and
// short-circuit forms either fold or reproduce with duplicate comparisons. It
// also schedules one independent constant load earlier and assigns four
// short-lived values different registers. The guarded object postprocessor
// describes that measured remainder; remove it if a source form reproduces the
// same compiler choices.

struct Fn80054F08Vec {
	f32 x;
	f32 y;
	f32 z;
};

struct Fn80054F08Triangle {
	u16 vertex[3];
	u8 padding[6];
	Fn80054F08Vec normal;
	u8 padding2[8];
};

struct Fn80054F08Cell {
	u16 value;
	u8 padding[2];
	u16 firstChild;
	u8 padding2[8];
	u16 count;
	union {
		u32 packedIndices;
		u16* indices;
	} triangleIndices;
	u8 padding3[12];
};

struct Fn80054F08TraversalEntry {
	u16 value;
	u16 padding;
	Fn80054F08TraversalEntry* previous;
	Fn80054F08TraversalEntry* next;
};

struct Fn80054F08ContactNode {
	u16 value;
	s16 secondaryValue;
	Fn80054F08Vec first;
	Fn80054F08Vec second;
	Fn80054F08Vec third;
	Fn80054F08ContactNode* previous;
	Fn80054F08ContactNode* next;
};

struct Fn80054F08ContactList {
	s32 count;
	Fn80054F08ContactNode* first;
	Fn80054F08ContactNode* last;

	Fn80054F08ContactList();
	static void* operator new(unsigned long);
};

struct Fn80054F08Grid {
	Fn80054F08Cell* cells;
	Fn80054F08Triangle* triangles;
	Fn80054F08Vec* vertices;
	u32* visited;
	s32 visitedWordCount;
	u32* traversalVisited;
	s32 traversalVisitedWordCount;
	u32 visitedActiveBlocks;
	u32 traversalActiveBlocks;
	u8 padding[0x30];
	f32 cellExtents[1];
};

extern "C" Fn80054F08Cell* fn_8005438C(Fn80054F08Grid*, const Fn80054F08Vec*);
extern "C" void fn_8005430C(Fn80054F08Grid*, const Fn80054F08Cell*, Fn80054F08Vec*);
extern "C" Fn80054F08TraversalEntry* fn_8005428C(Fn80054F08TraversalEntry*, u16);
extern "C" Fn80054F08TraversalEntry* fn_80055874(Fn80054F08Grid*, Fn80054F08TraversalEntry*,
    Fn80054F08Cell*, const Fn80054F08Vec*, f32, const Fn80054F08Vec*, const Fn80054F08Vec*);
extern "C" void fn_80054230(Fn80054F08TraversalEntry*);
extern "C" f32 fn_800D71DC(const Fn80054F08Vec*, const Fn80054F08Vec*);
extern "C" s32 fn_800D218C(
    const Fn80054F08Vec*, f32, const Fn80054F08Vec*, Fn80054F08Vec*, Fn80054F08Vec*);
extern "C" void* fn_80057644(u32);
extern "C" void fn_8005421C(Fn80054F08ContactList*);
extern "C" void fn_80054048(Fn80054F08ContactList*, u16, const Fn80054F08Vec*, const Fn80054F08Vec*,
    const Fn80054F08Vec*, const s16*);
extern "C" const f32 lbl_8042D3C0;

inline Fn80054F08ContactList::Fn80054F08ContactList()
{
	fn_8005421C(this);
}

inline void* Fn80054F08ContactList::operator new(unsigned long size)
{
	return fn_80057644(size);
}

static void fn_80054F08ClearVisited(s32 wordCount, u32 activeBlocks, u32* visited)
{
	for (; activeBlocks != 0; visited += 64, wordCount -= 64, activeBlocks >>= 1) {
		if ((activeBlocks & 1) != 0) {
			s32 words;
			if (wordCount >= 64) {
				words = 64;
			} else {
				words = wordCount;
			}
			while (words > 0) {
				*visited++ = 0;
				words--;
			}
		}
		continue;
	}
}

static inline u32 fn_80054F08TriangleIndex(Fn80054F08Cell* cell, s32 triangleSlot)
{
	if (cell->count == 1 || (cell->count == 2 && triangleSlot == 0)) {
		return cell->triangleIndices.packedIndices & 0x7FFF;
	}
	if (cell->count == 2 && triangleSlot == 1) {
		return (cell->triangleIndices.packedIndices & 0x7FFF0000) >> 16;
	}
	return cell->triangleIndices.indices[triangleSlot];
}

extern "C" Fn80054F08ContactList* fn_80054F08(Fn80054F08Grid* grid, const Fn80054F08Vec* point,
    f32 radius, s32 (*predicate)(Fn80054F08Triangle*))
{
	u32 rawTriangleIndex;
	s32 visitedWord;
	u32 visitedMask;
	Fn80054F08Cell* cell;
	Fn80054F08Cell* currentCell;
	s32 triangleSlot;
	Fn80054F08Triangle* triangle;
	Fn80054F08TraversalEntry* traversal;
	Fn80054F08ContactList* contacts;
	Fn80054F08TraversalEntry* next;
	Fn80054F08Vec triangleVertices[3];
	Fn80054F08Vec surfacePoint;
	Fn80054F08Vec correction;
	Fn80054F08Vec resolvedPoint;
	Fn80054F08Vec center;
	Fn80054F08Vec lower;
	Fn80054F08Vec upper;
	f32 extent;
	contacts = 0;
	fn_80054F08ClearVisited(grid->visitedWordCount, grid->visitedActiveBlocks, grid->visited);
	grid->visitedActiveBlocks = 0;
	fn_80054F08ClearVisited(
	    grid->traversalVisitedWordCount, grid->traversalActiveBlocks, grid->traversalVisited);
	grid->traversalActiveBlocks = 0;

	upper.x = point->x + radius;
	upper.z = point->z + radius;
	lower.x = point->x - radius;
	lower.z = point->z - radius;

	cell = fn_8005438C(grid, point);
	fn_8005430C(grid, cell, &center);
	extent = grid->cellExtents[cell->padding3[4]];
	Fn80054F08TraversalEntry* selectedTraversal;
	if (upper.x < extent + center.x && center.x - extent < lower.x && upper.z < extent + center.z
	    && center.z - extent < lower.z) {
		selectedTraversal = fn_8005428C(0, cell->value);
	} else {
		selectedTraversal = fn_80055874(grid, 0, cell, point, radius, &upper, &lower);
	}
	traversal = selectedTraversal;
	if (traversal == 0)
		return 0;

	f32 radiusSq = radius * radius;
	while (traversal != 0) {
		currentCell = &grid->cells[traversal->value];
		for (triangleSlot = 0; triangleSlot < currentCell->count; triangleSlot++) {
			rawTriangleIndex  = fn_80054F08TriangleIndex(currentCell, triangleSlot);
			u16 triangleIndex = (u16)rawTriangleIndex;

			visitedMask = 1 << (triangleIndex & 31);
			visitedWord = triangleIndex >> 5;
			if ((s32)(grid->visited[visitedWord] & visitedMask) == 0) {
				triangle = &grid->triangles[rawTriangleIndex];
				if (predicate == 0 || predicate(triangle) != 0) {
					triangleVertices[0] = grid->vertices[triangle->vertex[0]];
					triangleVertices[1] = grid->vertices[triangle->vertex[1]];
					triangleVertices[2] = grid->vertices[triangle->vertex[2]];

					f32 reachSq          = fn_800D71DC(&triangleVertices[1], &triangleVertices[0]);
					f32 alternateReachSq = fn_800D71DC(&triangleVertices[2], &triangleVertices[0]);
					if (reachSq < alternateReachSq)
						reachSq = alternateReachSq;
					reachSq += radiusSq;
					reachSq
					    -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
					s32 inReach = 0;
					if (reachSq > lbl_8042D3C0) {
					} else {
						goto reachTest;
					}
					reachSq
					    -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
					if (reachSq > lbl_8042D3C0) {
					} else {
						goto reachTest;
					}
					reachSq
					    -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
					if (reachSq > lbl_8042D3C0)
						inReach = 1;
				reachTest:
					if (inReach != 0) {
						if (fn_800D218C(point, radius, triangleVertices, &surfacePoint, &correction)
						    != 0) {
							resolvedPoint.x = point->x + correction.x;
							resolvedPoint.y = point->y + correction.y;
							resolvedPoint.z = point->z + correction.z;
							if (contacts == 0) {
								contacts = new Fn80054F08ContactList;
							}
							fn_80054048(contacts, (u16)rawTriangleIndex, &correction,
							    &resolvedPoint, &surfacePoint, 0);
						}
					}
				}
				grid->visited[visitedWord] |= visitedMask;
				grid->visitedActiveBlocks |= 1 << (triangleIndex >> 11);
			}
		}
		next = traversal->next;
		fn_80054230(traversal);
		traversal = next;
	}
	return contacts;
}
