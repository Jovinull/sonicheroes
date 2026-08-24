#include "types.h"

// fn_8005428C allocates a three-word list node, links it immediately before
// the supplied node when present, and assigns its 16-bit value.  The only data
// reference is the pre-existing global allocator, so this is a recorded
// function carve rather than a claimed source translation-unit boundary.
struct Fn8005428CNode {
    u16 value;
    u16 padding;
    Fn8005428CNode* previous;
    Fn8005428CNode* next;
};

struct Fn8005428CAllocator {
    u8 padding[0x134];
    Fn8005428CNode* (*allocate)(u32 size);
};

extern "C" Fn8005428CAllocator* lbl_8042C9A4;

extern "C" Fn8005428CNode* fn_8005428C(Fn8005428CNode* next, u16 value)
{
    Fn8005428CNode* node = lbl_8042C9A4->allocate(sizeof(Fn8005428CNode));
    if (node == 0) {
        return 0;
    }

    if (next != 0) {
        node->next = next;
        next->previous = node;
    } else {
        node->next = 0;
    }
    node->previous = 0;
    node->value = value;
    return node;
}
