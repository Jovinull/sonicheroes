#include "types.h"

// Broad-phase grid traversal followed by swept-triangle contact generation.
// The nodes returned by fn_800556A0 own temporary traversal entries; every
// entry is released as soon as its cell has been visited.

struct Fn80054900Vec { f32 x; f32 y; f32 z; };

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
extern "C" Fn80054900TraversalEntry* fn_800556A0(Fn80054900Grid*, const Fn80054900Vec*,
    const Fn80054900Vec*, f32);
extern "C" void fn_80054230(Fn80054900TraversalEntry*);
extern "C" void* fn_80057644(u32);
extern "C" void fn_8005421C(Fn80054900ContactList*);
extern "C" void fn_80054048(Fn80054900ContactList*, u16, const Fn80054900Vec*,
    const Fn80054900Vec*, const Fn80054900Vec*, const s16*);
extern "C" s32 fn_800D218C(const Fn80054900Vec*, f32, const Fn80054900Vec*,
    Fn80054900Vec*, Fn80054900Vec*);
extern "C" s32 fn_800D2ED4(const Fn80054900Vec*, f32, Fn80054900Vec*,
    const Fn80054900Vec*, Fn80054900Vec*, Fn80054900Vec*, s16*);

static f32 fn_80054900LengthSq(const Fn80054900Vec& value)
{
    return value.z * value.z + value.x * value.x + value.y * value.y;
}

static f32 fn_80054900DistanceSq(const Fn80054900Vec& left, const Fn80054900Vec& right)
{
    Fn80054900Vec delta;
    delta.x = left.x - right.x;
    delta.y = left.y - right.y;
    delta.z = left.z - right.z;
    return fn_80054900LengthSq(delta);
}

extern "C" Fn80054900ContactList* fn_80054900(Fn80054900Grid* grid, const Fn80054900Vec* point,
    Fn80054900Vec* direction, f32 radius, u32* contactType, s32 (*predicate)(Fn80054900Triangle*))
{
    Fn80054900ContactList* contacts = 0;
    Fn80054900Vec normalizedDirection;
    if (fn_801991B4(direction) > 0.0f) {
        fn_801990E0(&normalizedDirection, direction);
    } else {
        normalizedDirection.x = 0.0f;
        normalizedDirection.y = 0.0f;
        normalizedDirection.z = 0.0f;
    }

    *contactType = 0;
    Fn80054900Vec remainingDirection = *direction;
    grid->contactMode = 1;

    u32 activeBlocks = *(u32*)((u8*)grid + 0x1C);
    u32* visited = grid->visited;
    s32 wordsLeft = grid->visitedWordCount;
    while (activeBlocks != 0) {
        if ((activeBlocks & 1) != 0) {
            s32 words = wordsLeft < 64 ? wordsLeft : 64;
            for (s32 index = 0; index < words; index++) visited[index] = 0;
        }
        visited += 64;
        wordsLeft -= 64;
        activeBlocks >>= 1;
    }
    *(u32*)((u8*)grid + 0x1C) = 0;

    Fn80054900TraversalEntry* traversal = fn_800556A0(grid, point, direction, radius);
    if (traversal == 0) return 0;

    f32 reachSq = radius * radius + fn_80054900LengthSq(*direction);
    while (traversal != 0) {
        Fn80054900Cell* cell = &grid->cells[traversal->value];
        for (s32 triangleSlot = 0; triangleSlot < cell->count; triangleSlot++) {
            u16 triangleIndex;
            if (cell->count == 1 || (cell->count == 2 && triangleSlot == 0)) {
                triangleIndex = (u16)cell->triangleIndices.packedIndices;
            } else if (cell->count == 2 && triangleSlot == 1) {
                triangleIndex = (u16)(cell->triangleIndices.packedIndices >> 16);
            } else {
                triangleIndex = cell->triangleIndices.indices[triangleSlot];
            }

            u32 visitedMask = 1 << (triangleIndex & 31);
            u32 visitedWord = triangleIndex >> 5;
            if ((grid->visited[visitedWord] & visitedMask) == 0) {
                Fn80054900Triangle* triangle = &grid->triangles[triangleIndex];
                f32 facing = normalizedDirection.z * triangle->normal.z;
                facing += normalizedDirection.x * triangle->normal.x;
                facing += normalizedDirection.y * triangle->normal.y;
                if (facing >= 0.0f && (predicate == 0 || predicate(triangle) != 0)) {
                    Fn80054900Vec triangleVertices[3];
                    triangleVertices[0] = grid->vertices[triangle->vertex[0]];
                    triangleVertices[1] = grid->vertices[triangle->vertex[1]];
                    triangleVertices[2] = grid->vertices[triangle->vertex[2]];

                    f32 triangleReachSq = fn_80054900DistanceSq(triangleVertices[1], triangleVertices[0]);
                    f32 alternateReachSq = fn_80054900DistanceSq(triangleVertices[0], triangleVertices[2]);
                    if (triangleReachSq < alternateReachSq) triangleReachSq = alternateReachSq;
                    f32 remainingReachSq = triangleReachSq + reachSq;
                    remainingReachSq -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
                    if (remainingReachSq > 0.0f) {
                        remainingReachSq -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
                        if (remainingReachSq > 0.0f) {
                            remainingReachSq -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
                            if (remainingReachSq > 0.0f) {
                                if (grid->contactMode == 1 && *contactType == 2) {
                                    Fn80054900Vec surfacePoint;
                                    Fn80054900Vec correction;
                                    if (fn_800D218C(point, radius, triangleVertices, &surfacePoint, &correction) != 0) {
                                        Fn80054900Vec resolvedPoint;
                                        resolvedPoint.x = point->x + correction.x;
                                        resolvedPoint.y = point->y + correction.y;
                                        resolvedPoint.z = point->z + correction.z;
                                        fn_80054048(contacts, triangleIndex, 0, &resolvedPoint, &surfacePoint, 0);
                                    }
                                } else {
                                    s16 secondaryValue = 0;
                                    Fn80054900Vec firstContact;
                                    Fn80054900Vec secondContact;
                                    s32 result = fn_800D2ED4(point, radius, &remainingDirection, triangleVertices,
                                        &firstContact, &secondContact, &secondaryValue);
                                    if (result != 0) {
                                        if (contacts == 0) {
                                            contacts = (Fn80054900ContactList*)fn_80057644(sizeof(Fn80054900ContactList));
                                            if (contacts != 0) fn_8005421C(contacts);
                                        }
                                        if (grid->contactMode == 1) {
                                            if (result == 2) {
                                                fn_80054048(contacts, triangleIndex, 0, &secondContact, &firstContact,
                                                    &secondaryValue);
                                                *contactType = 2;
                                            } else {
                                                fn_80054048(contacts, triangleIndex, &firstContact, &secondContact, 0,
                                                    &secondaryValue);
                                                *contactType = 1;
                                                remainingDirection = firstContact;
                                            }
                                        } else if (fn_80054900LengthSq(remainingDirection) > 0.0f) {
                                            fn_80054048(contacts, triangleIndex, &firstContact, &secondContact, 0,
                                                &secondaryValue);
                                            *contactType = 1;
                                        } else {
                                            fn_80054048(contacts, triangleIndex, 0, &secondContact, &firstContact,
                                                &secondaryValue);
                                            *contactType = 2;
                                        }
                                    }
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
