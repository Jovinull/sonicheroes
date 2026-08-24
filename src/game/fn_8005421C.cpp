#include "types.h"

// fn_8005421C initializes the three-word node returned by the 12-byte
// allocator at each of its call sites.  The range has no data references, so
// this is a safe recorded leaf-function carve rather than a claimed source
// translation-unit boundary.
struct Fn8005421CNode {
    void* value;
    Fn8005421CNode* previous;
    Fn8005421CNode* next;
};

extern "C" void fn_8005421C(Fn8005421CNode* node)
{
    node->value = 0;
    node->next = 0;
    node->previous = 0;
}
