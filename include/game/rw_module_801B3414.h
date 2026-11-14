#ifndef GAME_RW_MODULE_801B3414_H
#define GAME_RW_MODULE_801B3414_H

#include "game/rw_engine.h"

// RenderWare module opened by fn_801B3474 and closed by fn_801B3414. Which RenderWare module this
// is remains UNKNOWN; names below are inferred from the open/close code only.

extern "C" {
// Module bookkeeping: offset of the module globals in the engine block.
extern RwModuleInfo lbl_8042CA80;
// Non-zero once the module is open.
extern s32 lbl_8042CA88;
// Shared heap created on open by fn_801B7814 (fn_801B3884 returns it).
extern void* lbl_8042CA8C;

// Create (fn_801B7814: heap of at least the given size) and destroy of the shared heap.
void* fn_801B7814(s32 arg);
void fn_801B7778(void* handle);
}

// Module globals: the 0x34-byte entry free list is the first field.
#define RW_MODULE_801B3414_GLOBALS   ((u8*)lbl_8042C9A4 + lbl_8042CA80.globalsOffset)
#define RW_MODULE_801B3414_FREE_LIST (*(RwFreeList**)RW_MODULE_801B3414_GLOBALS)

#endif
