#include "types.h"

// Build fragment for the stage-failure animation workspace. The retail DOL
// places this regular BSS input before the SpAdvStgFailed code object's BSS
// position, so it cannot be emitted by that code object.
extern "C" {
u8 lbl_80303EC8[0x70];
}
