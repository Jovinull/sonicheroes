#include "types.h"

struct Fn80054048Vec { f32 x; f32 y; f32 z; };
struct Fn80054048Node {
    u16 value;
    s16 secondaryValue;
    Fn80054048Vec first;
    Fn80054048Vec second;
    Fn80054048Vec third;
    Fn80054048Node* previous;
    Fn80054048Node* next;
};
struct Fn80054048List { s32 count; Fn80054048Node* first; Fn80054048Node* last; };
struct Fn80054048Allocator { u8 padding[0x140]; Fn80054048Node* (*allocate)(u32, u32); };
extern "C" Fn80054048Allocator* lbl_8042C9A4;

extern "C" void fn_80054048(Fn80054048List* list, u16 value, const Fn80054048Vec* first,
    const Fn80054048Vec* second, const Fn80054048Vec* third, const s16* secondaryValue)
{
    Fn80054048Node* node = lbl_8042C9A4->allocate(sizeof(Fn80054048Node), 1);
    if (node != 0) {
        if (list->first != 0) {
            node->next = list->first;
            list->first->previous = node;
        }
        node->value = value;
        if (first != 0) node->first = *first;
        if (second != 0) node->second = *second;
        if (third != 0) node->third = *third;
        if (secondaryValue != 0) node->secondaryValue = *secondaryValue;
        list->first = node;
        if (list->count == 0) list->last = node;
        list->count++;
    }
}
