#include "types.h"

struct Fn80054158Node { u8 padding[0x28]; Fn80054158Node* previous; Fn80054158Node* next; };
struct Fn80054158List { s32 count; Fn80054158Node* first; Fn80054158Node* last; };
struct Fn80054158Allocator { u8 padding[0x138]; void (*release)(Fn80054158Node*); };
extern "C" Fn80054158Allocator* lbl_8042C9A4;
extern "C" void __dl(void*);

extern "C" Fn80054158List* fn_80054158(Fn80054158List* list, s16 destroy)
{
    if (list != 0) {
        if (list->count != 0) {
            Fn80054158Node* previous = 0;
            do {
                Fn80054158Node* next = 0;
                if (list->first->next != 0) {
                    list->first->next->previous = previous;
                    next = list->first->next;
                }
                lbl_8042C9A4->release(list->first);
                list->first = next;
            } while (list->first != 0);
            list->last = 0;
            list->count = 0;
        }
        if (destroy > 0) __dl(list);
    }
    return list;
}
