#include "types.h"

struct Fn8005446CAllocator { u8 padding[0x138]; void (*release)(void*); };
struct Fn8005446CGrid {
    u8 padding[0xC];
    void* first;
    u8 padding2[4];
    void* second;
    u8 padding3[0x16C];
    void* third;
};
extern "C" Fn8005446CAllocator* lbl_8042C9A4;
extern "C" void __dl(void*);

extern "C" Fn8005446CGrid* fn_8005446C(Fn8005446CGrid* grid, s16 destroy)
{
    if (grid != 0) {
        lbl_8042C9A4->release(grid->third);
        grid->third = 0;
        if (grid->first != 0) {
            lbl_8042C9A4->release(grid->first);
            grid->first = 0;
        }
        if (grid->second != 0) {
            lbl_8042C9A4->release(grid->second);
            grid->second = 0;
        }
        if (destroy > 0) __dl(grid);
    }
    return grid;
}
