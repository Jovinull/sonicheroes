#include "types.h"

// TObjSwitch's draw step. It hands the switch's current state material whatever
// the object resolves to, sets the raster up, and then calls through the draw
// record's own render pointer.
//
// The claim is .text 0x4AC4 to 0x4B44 and nothing else. It reads no constant and
// owns no data: the two state slots it uses are the ones rel/switch_load.cpp
// fills in, already renamed in every module.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// The last call is through a function pointer held in the draw record, not a
// virtual call: the pointer is fetched from the record while the object stays in
// the first argument, which a method call would not do.

typedef struct DrawRecord {
	u8 unk0[0x48];                // 0x00
	void (*render)(void* object); // 0x48
} DrawRecord;

extern "C" u8 lbl_802D5E80[];

extern "C" void* fn_8005F6D4(void* object);
extern "C" void fn_8015498C(void* material, void* source);
extern "C" void fn_80053660(void* raster, s32 mode);
extern "C" void fn_8005349C(void* raster, u8 level);

// Filled in by rel/switch_load.cpp, renamed in each module's symbols.txt.
extern "C" void* switchStateMaterial;
extern "C" void* switchStateDraw;

extern "C" void* switchGuard(void* object)
{
	fn_8015498C(switchStateMaterial, fn_8005F6D4(object));

	fn_80053660(lbl_802D5E80, 16);
	fn_8005349C(lbl_802D5E80, lbl_802D5E80[1214]);

	((DrawRecord*)switchStateDraw)->render(object);

	return object;
}
