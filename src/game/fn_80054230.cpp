#include "types.h"

// fn_80054230 removes the node initialized by fn_8005421C from its doubly
// linked list, then releases it through the global allocator.  Its only data
// reference is that pre-existing allocator pointer; this records the proven
// function range without claiming the surrounding translation-unit boundary.
struct Fn80054230Node {
    void* value;
    Fn80054230Node* previous;
    Fn80054230Node* next;
};

struct Fn80054230Allocator {
    u8 padding[0x138];
    void (*release)(Fn80054230Node*);
};

extern "C" Fn80054230Allocator* lbl_8042C9A4;

extern "C" void fn_80054230(Fn80054230Node* node)
{
    if (node != 0) {
        if (node->previous != 0) {
            node->previous->next = node->next;
        }
        if (node->next != 0) {
            node->next->previous = node->previous;
        }
        lbl_8042C9A4->release(node);
    }
}
