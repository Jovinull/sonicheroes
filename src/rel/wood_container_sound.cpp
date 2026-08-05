#include "types.h"

// WoodContainer's sound hook. It plays one cue through the sound handle
// when that handle is live, and does nothing otherwise.
//
// The claim is .text 0x00014198 to 0x000141D8 and nothing else. It
// reads no constant, so it owns no rodata.
//
// The name is read from the layout and from an existing reading of the same
// idiom: the run sits directly after
// woodContainerRegister in that family's block, and rel/obj_box_trigger.cpp already
// reaches the same global through the same call to play a cue, reading the
// second argument as the sound id. Here that id is 0x1048.
//
// The body is byte for byte the same as the wood container's, which is why the
// two are separate sources rather than one: each module's split names its own
// run, and the two runs sit at different addresses.
//
// The run is the same in the twelve stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

extern "C" void* lbl_8042C388;

extern "C" void fn_800B52E8(void* handle, s32 sound, s32 a, s32 b);

extern "C" void woodContainerPlaySound(void)
{
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1048, 0, 0);
	}
}
