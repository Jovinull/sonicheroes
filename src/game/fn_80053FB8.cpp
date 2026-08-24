#include "types.h"

// fn_80053FB8 unlinks an element from the list and releases it through the
// existing global allocator.  It references no local data and records only
// its independently provable function range.
struct Fn80053FB8Node {
    u8 padding[0x28];
    Fn80053FB8Node* previous;
    Fn80053FB8Node* next;
};

struct Fn80053FB8List {
    u32 count;
    Fn80053FB8Node* first;
    Fn80053FB8Node* last;
};

struct Fn80053FB8Allocator {
    u8 padding[0x138];
    void (*release)(Fn80053FB8Node*);
};

extern "C" Fn80053FB8Allocator* lbl_8042C9A4;

extern "C" void fn_80053FB8(Fn80053FB8List* list, Fn80053FB8Node* node)
{
    if (node != 0) {
        if (node->previous != 0) {
            node->previous->next = node->next;
        } else {
            list->first = node->next;
        }
        if (node->next != 0) {
            node->next->previous = node->previous;
        } else {
            list->last = node->previous;
        }
        lbl_8042C9A4->release(node);
        list->count--;
    }
}
