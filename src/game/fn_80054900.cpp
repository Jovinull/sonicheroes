#include "types.h"

// Broad-phase grid traversal followed by swept-triangle contact generation.
// The nodes returned by fn_800556A0 own temporary traversal entries; every
// entry is released as soon as its cell has been visited.
//
// GC/1.3.2 retains one redundant branch, schedules two independent pairs in a
// different order, and colors three groups of values differently. Source
// experiments either fold the branch or introduce another comparison. The
// guarded object postprocessor records that measured compiler-only remainder.

struct Fn80054900Vec {
	f32 x;
	f32 y;
	f32 z;
};

struct Fn80054900Triangle {
	u16 vertex[3];
	u8 padding[6];
	Fn80054900Vec normal;
	u8 padding2[8];
};

struct Fn80054900Cell {
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

struct Fn80054900TraversalEntry {
	u16 value;
	u16 padding;
	Fn80054900TraversalEntry* previous;
	Fn80054900TraversalEntry* next;
};

struct Fn80054900ContactNode {
	u16 value;
	s16 secondaryValue;
	Fn80054900Vec first;
	Fn80054900Vec second;
	Fn80054900Vec third;
	Fn80054900ContactNode* previous;
	Fn80054900ContactNode* next;
};

struct Fn80054900ContactList {
	s32 count;
	Fn80054900ContactNode* first;
	Fn80054900ContactNode* last;

	Fn80054900ContactList();
	static void* operator new(unsigned long);
};

struct Fn80054900Grid {
	Fn80054900Cell* cells;
	Fn80054900Triangle* triangles;
	Fn80054900Vec* vertices;
	u32* visited;
	s32 visitedWordCount;
	u8 padding[0x174];
	s32 contactMode;
};

extern "C" f32 fn_801991B4(Fn80054900Vec*);
extern "C" void fn_801990E0(Fn80054900Vec*, Fn80054900Vec*);
extern "C" Fn80054900TraversalEntry* fn_800556A0(
    Fn80054900Grid*, const Fn80054900Vec*, const Fn80054900Vec*, f32);
extern "C" void fn_80054230(Fn80054900TraversalEntry*);
extern "C" void* fn_80057644(u32);
extern "C" void fn_8005421C(Fn80054900ContactList*);
extern "C" void fn_80054048(Fn80054900ContactList*, u16, const Fn80054900Vec*, const Fn80054900Vec*,
    const Fn80054900Vec*, const s16*);
extern "C" s32 fn_800D218C(
    const Fn80054900Vec*, f32, const Fn80054900Vec*, Fn80054900Vec*, Fn80054900Vec*);
extern "C" s32 fn_800D2ED4(const Fn80054900Vec*, f32, Fn80054900Vec*, const Fn80054900Vec*,
    Fn80054900Vec*, Fn80054900Vec*, s16*);
extern "C" const f32 lbl_8042D3C0;
extern "C" const f32 lbl_8042D3C4;

inline Fn80054900ContactList::Fn80054900ContactList()
{
	fn_8005421C(this);
}

inline void* Fn80054900ContactList::operator new(unsigned long size)
{
	return fn_80057644(size);
}

static inline f32 fn_80054900LengthSq(const Fn80054900Vec& value)
{
	return value.x * value.x + value.y * value.y + value.z * value.z;
}

static inline f32 fn_80054900Square(f32 value)
{
	return value * value;
}

static inline void fn_80054900ClearWords(u32*& output, s32 count)
{
	while (count > 0) {
		*output++ = 0;
		count--;
	}
}

static inline u32 fn_80054900TriangleIndex(Fn80054900Cell* cell, s32 triangleSlot)
{
	if (cell->count == 1 || (cell->count == 2 && triangleSlot == 0)) {
		return cell->triangleIndices.packedIndices & 0x7FFF;
	}
	if (cell->count == 2 && triangleSlot == 1) {
		return (cell->triangleIndices.packedIndices & 0x7FFF0000) >> 16;
	}
	return cell->triangleIndices.indices[triangleSlot];
}

#pragma no_register_coloring on
extern "C" Fn80054900ContactList* fn_80054900(Fn80054900Grid* grid, const Fn80054900Vec* point,
    register Fn80054900Vec* direction, f32 radius, s32* contactType,
    s32 (*predicate)(Fn80054900Triangle*))
{
	Fn80054900Vec* movement = direction;
	u32 rawTriangleIndex;
	s32 visitedMask;
	s32 visitedWord;
	Fn80054900Cell* cell;
	s32 triangleSlot;
	Fn80054900Vec secondContact;
	Fn80054900Vec firstContact;
	Fn80054900Vec remainingDirection;
	Fn80054900Vec normalizedDirection;
	Fn80054900Vec surfacePoint;
	Fn80054900Vec correction;
	Fn80054900Vec resolvedPoint;
	Fn80054900ContactList* contacts = 0;
	s32 words;
	if (fn_801991B4(movement) > lbl_8042D3C0) {
		fn_801990E0(&normalizedDirection, movement);
	} else {
		normalizedDirection.z = lbl_8042D3C0;
		normalizedDirection.y = lbl_8042D3C0;
		normalizedDirection.x = lbl_8042D3C0;
	}

	*contactType         = 0;
	remainingDirection.x = movement->x;
	remainingDirection.y = movement->y;
	remainingDirection.z = movement->z;
	grid->contactMode    = 1;

	s32 wordsLeft;
	u32 activeBlocks;
	u32* visited;
	visited      = grid->visited;
	activeBlocks = *(u32*)((u8*)grid + 0x1C);
	wordsLeft    = grid->visitedWordCount;
	while (activeBlocks != 0) {
		if ((activeBlocks & 1) != 0) {
			if (wordsLeft >= 64) {
				words = 64;
			} else {
				words = wordsLeft;
			}
			fn_80054900ClearWords(visited, words);
		}
		visited += 64;
		wordsLeft -= 64;
		activeBlocks >>= 1;
	}
	*(u32*)((u8*)grid + 0x1C) = 0;

	Fn80054900TraversalEntry* traversal = fn_800556A0(grid, point, movement, radius);
	if (traversal == 0)
		return 0;

	f32 reachSq = radius * radius + fn_80054900LengthSq(*movement);
	while (traversal != 0) {
		cell = &grid->cells[traversal->value];
		for (triangleSlot = 0; triangleSlot < cell->count; triangleSlot++) {
			rawTriangleIndex  = fn_80054900TriangleIndex(cell, triangleSlot);
			u16 triangleIndex = (u16)rawTriangleIndex;

			visitedMask = 1 << (triangleIndex & 31);
			visitedWord = triangleIndex >> 5;
			if ((s32)(grid->visited[visitedWord] & visitedMask) == 0) {
				Fn80054900Triangle* triangle = &grid->triangles[rawTriangleIndex];
				f32 facing                   = normalizedDirection.x * triangle->normal.x
				    + normalizedDirection.y * triangle->normal.y
				    + normalizedDirection.z * triangle->normal.z;
				s32 facingAccepted = 0;
				if (facing < lbl_8042D3C4)
					facingAccepted = 1;
				if (facingAccepted == 1 && (predicate == 0 || predicate(triangle) != 0)) {
					Fn80054900Vec triangleVertices[3];
					triangleVertices[0] = grid->vertices[triangle->vertex[0]];
					triangleVertices[1] = grid->vertices[triangle->vertex[1]];
					triangleVertices[2] = grid->vertices[triangle->vertex[2]];

					f32 triangleReachSq
					    = fn_80054900Square(triangleVertices[1].x - triangleVertices[0].x);
					f32 alternateReachSq
					    = fn_80054900Square(triangleVertices[0].x - triangleVertices[2].x);
					triangleReachSq
					    += fn_80054900Square(triangleVertices[1].y - triangleVertices[0].y);
					alternateReachSq
					    += fn_80054900Square(triangleVertices[0].y - triangleVertices[2].y);
					triangleReachSq
					    += fn_80054900Square(triangleVertices[1].z - triangleVertices[0].z);
					alternateReachSq
					    += fn_80054900Square(triangleVertices[0].z - triangleVertices[2].z);
					if (triangleReachSq < alternateReachSq)
						triangleReachSq = alternateReachSq;
					triangleReachSq += reachSq;
					triangleReachSq
					    -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
					s32 inReach = 0;
					if (triangleReachSq > lbl_8042D3C0) {
					} else {
						goto reachTest;
					}
					triangleReachSq
					    -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
					if (triangleReachSq > lbl_8042D3C0) {
					} else {
						goto reachTest;
					}
					triangleReachSq
					    -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
					if (triangleReachSq > lbl_8042D3C0)
						inReach = 1;
				reachTest:
					if (inReach != 0) {
						if (grid->contactMode == 1 && *contactType == 2) {
							if (fn_800D218C(
							        point, radius, triangleVertices, &surfacePoint, &correction)
							    != 0) {
								resolvedPoint.x = point->x + correction.x;
								resolvedPoint.y = point->y + correction.y;
								resolvedPoint.z = point->z + correction.z;
								fn_80054048(contacts, (u16)rawTriangleIndex, 0, &resolvedPoint,
								    &surfacePoint, 0);
							}
						} else {
							s16 secondaryValue = 0;
							s32 result         = fn_800D2ED4(point, radius, &remainingDirection,
							    triangleVertices, &firstContact, &secondContact, &secondaryValue);
							if (result != 0) {
								if (contacts == 0) {
									contacts = new Fn80054900ContactList;
								}
								if (grid->contactMode == 1) {
									if (result == 2) {
										fn_80054048(contacts, (u16)rawTriangleIndex, 0,
										    &secondContact, &firstContact, &secondaryValue);
										*contactType = 2;
									} else {
										fn_80054048(contacts, (u16)rawTriangleIndex, &firstContact,
										    &secondContact, 0, &secondaryValue);
										*contactType       = 1;
										remainingDirection = firstContact;
									}
								} else if (fn_80054900LengthSq(remainingDirection) > lbl_8042D3C0) {
									fn_80054048(contacts, (u16)rawTriangleIndex, &firstContact,
									    &secondContact, 0, &secondaryValue);
									*contactType = 1;
								} else {
									fn_80054048(contacts, (u16)rawTriangleIndex, 0, &secondContact,
									    &firstContact, &secondaryValue);
									*contactType = 2;
								}
							}
						}
					}
				}
				grid->visited[visitedWord] |= visitedMask;
				*(u32*)((u8*)grid + 0x1C) |= 1 << (triangleIndex >> 11);
			}
		}
		Fn80054900TraversalEntry* next = traversal->next;
		fn_80054230(traversal);
		traversal = next;
	}
	return contacts;
}
#pragma no_register_coloring off
