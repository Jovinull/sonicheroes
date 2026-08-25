#include "types.h"

// Stationary sphere overlap query.  It uses the same compact cell-index
// encoding as the swept query and releases its temporary traversal list while
// producing a contact list.

struct Fn80054F08Vec { f32 x; f32 y; f32 z; };

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
};

struct Fn80054F08Grid {
    Fn80054F08Cell* cells;
    Fn80054F08Triangle* triangles;
    Fn80054F08Vec* vertices;
    u32* visited;
    s32 visitedWordCount;
    u32* traversalVisited;
    s32 traversalVisitedWordCount;
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
extern "C" s32 fn_800D218C(const Fn80054F08Vec*, f32, const Fn80054F08Vec*,
    Fn80054F08Vec*, Fn80054F08Vec*);
extern "C" void* fn_80057644(u32);
extern "C" void fn_8005421C(Fn80054F08ContactList*);
extern "C" void fn_80054048(Fn80054F08ContactList*, u16, const Fn80054F08Vec*,
    const Fn80054F08Vec*, const Fn80054F08Vec*, const s16*);

static void fn_80054F08ClearVisited(u32* visited, s32 wordCount, u32 activeBlocks)
{
    while (activeBlocks != 0) {
        if ((activeBlocks & 1) != 0) {
            s32 words = wordCount < 64 ? wordCount : 64;
            for (s32 index = 0; index < words; index++) visited[index] = 0;
        }
        visited += 64;
        wordCount -= 64;
        activeBlocks >>= 1;
    }
}

extern "C" Fn80054F08ContactList* fn_80054F08(Fn80054F08Grid* grid, const Fn80054F08Vec* point,
    f32 radius, s32 (*predicate)(Fn80054F08Triangle*))
{
    Fn80054F08ContactList* contacts = 0;
    fn_80054F08ClearVisited(grid->visited, grid->visitedWordCount, *(u32*)((u8*)grid + 0x1C));
    *(u32*)((u8*)grid + 0x1C) = 0;
    fn_80054F08ClearVisited(grid->traversalVisited, grid->traversalVisitedWordCount, grid->traversalActiveBlocks);
    grid->traversalActiveBlocks = 0;

    Fn80054F08Vec upper;
    Fn80054F08Vec lower;
    upper.x = point->x + radius;
    upper.z = point->z + radius;
    lower.x = point->x - radius;
    lower.z = point->z - radius;

    Fn80054F08Cell* cell = fn_8005438C(grid, point);
    Fn80054F08Vec center;
    fn_8005430C(grid, cell, &center);
    f32 extent = grid->cellExtents[cell->padding3[4]];
    Fn80054F08TraversalEntry* traversal;
    if (upper.x < center.x + extent && center.x - extent < lower.x &&
        upper.z < center.z + extent && center.z - extent < lower.z) {
        traversal = fn_8005428C(0, cell->value);
    } else {
        traversal = fn_80055874(grid, 0, cell, point, radius, &upper, &lower);
    }
    if (traversal == 0) return 0;

    f32 radiusSq = radius * radius;
    while (traversal != 0) {
        Fn80054F08Cell* currentCell = &grid->cells[traversal->value];
        for (s32 triangleSlot = 0; triangleSlot < currentCell->count; triangleSlot++) {
            u16 triangleIndex;
            if (currentCell->count == 1 || (currentCell->count == 2 && triangleSlot == 0)) {
                triangleIndex = (u16)currentCell->triangleIndices.packedIndices;
            } else if (currentCell->count == 2 && triangleSlot == 1) {
                triangleIndex = (u16)(currentCell->triangleIndices.packedIndices >> 16);
            } else {
                triangleIndex = currentCell->triangleIndices.indices[triangleSlot];
            }

            u32 visitedMask = 1 << (triangleIndex & 31);
            u32 visitedWord = triangleIndex >> 5;
            if ((grid->visited[visitedWord] & visitedMask) == 0) {
                Fn80054F08Triangle* triangle = &grid->triangles[triangleIndex];
                if (predicate == 0 || predicate(triangle) != 0) {
                    Fn80054F08Vec triangleVertices[3];
                    triangleVertices[0] = grid->vertices[triangle->vertex[0]];
                    triangleVertices[1] = grid->vertices[triangle->vertex[1]];
                    triangleVertices[2] = grid->vertices[triangle->vertex[2]];

                    f32 reachSq = fn_800D71DC(&triangleVertices[1], &triangleVertices[0]);
                    f32 alternateReachSq = fn_800D71DC(&triangleVertices[2], &triangleVertices[0]);
                    if (reachSq < alternateReachSq) reachSq = alternateReachSq;
                    reachSq += radiusSq;
                    reachSq -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
                    if (reachSq > 0.0f) {
                        reachSq -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
                        if (reachSq > 0.0f) {
                            reachSq -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
                            if (reachSq > 0.0f) {
                                Fn80054F08Vec surfacePoint;
                                Fn80054F08Vec correction;
                                if (fn_800D218C(point, radius, triangleVertices, &surfacePoint, &correction) != 0) {
                                    Fn80054F08Vec resolvedPoint;
                                    resolvedPoint.x = point->x + correction.x;
                                    resolvedPoint.y = point->y + correction.y;
                                    resolvedPoint.z = point->z + correction.z;
                                    if (contacts == 0) {
                                        contacts = (Fn80054F08ContactList*)fn_80057644(sizeof(Fn80054F08ContactList));
                                        if (contacts != 0) fn_8005421C(contacts);
                                    }
                                    fn_80054048(contacts, triangleIndex, &correction, &resolvedPoint, &surfacePoint, 0);
                                }
                            }
                        }
                    }
                }
                grid->visited[visitedWord] |= visitedMask;
                *(u32*)((u8*)grid + 0x1C) |= 1 << (triangleIndex >> 11);
            }
        }
        Fn80054F08TraversalEntry* next = traversal->next;
        fn_80054230(traversal);
        traversal = next;
    }
    return contacts;
}
