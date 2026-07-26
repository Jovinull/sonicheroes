#include "types.h"

// TObjSwitch, as far as it has been carved: the parameter guard and the unload
// hook that follows it.
//
// The guard is the last slot of the class's second base's vtable, the
// same slot springClamp and sample1Clamp fill for their classes. This one does
// a second job: after bounding the three editor fields it writes the label each
// one currently reads as back into the block the editor displays.
//
// The claim is .text 0x4B44 to 0x4C4C and nothing else. The three name tables
// and the label block stay with the module and are reached as externals: the
// tables are only read here, but the block is written by another function that
// is still assembly, and the strings the tables point at sit between them, so
// no single range covers what would have to be claimed.
//
// The strings say what the fields are. The first picks between "ALTERNATE
// Type", "TOUCH Type", "ONCE Type" and "INTERLOCK Type", so it is bounded to
// zero through three. The second picks between "not in use" and "Ref. ID" and
// is bounded to zero or one. The third is a flag rather than an index, so it is
// normalised to zero or one instead of clamped, and it chooses between the
// shared label and "SOUND - PiPoRi".
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else.

typedef struct SwitchParams {
	s8 type;  // 0x00
	s8 ref;   // 0x01
	u8 unk2;  // 0x02
	u8 sound; // 0x03
} SwitchParams;

typedef struct Frame {
	u8 unk0[0x2C];        // 0x00
	SwitchParams* params; // 0x2C
} Frame;

typedef struct Switch {
	u8 unk0[0x30]; // 0x00
	void* state;   // 0x30
} Switch;

extern "C" void* memset(void* dst, s32 value, u32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* switchLabels[];
extern "C" const char* switchTypeNames[];
extern "C" const char* switchRefNames[];
extern "C" const char* switchSoundNames[];

// The object it is called on is not used: everything it touches hangs off the
// keyframe it is handed, or is module wide.
extern "C" void switchClamp(void* object, Frame* frame)
{
	SwitchParams* params = frame->params;

	if (params->type < 0) {
		params->type = 0;
	}
	if (params->type >= 4) {
		params->type = 3;
	}

	if (params->ref < 0) {
		params->ref = 0;
	}
	if (params->ref > 0) {
		params->ref = 1;
	}

	if (params->sound != 0) {
		params->sound = 1;
	}

	switchLabels[0] = switchTypeNames[params->type];
	switchLabels[2] = switchRefNames[params->ref];
	switchLabels[3] = switchSoundNames[params->sound];
}

// The unload hook the module's registration record points at. It clears the
// block the switch keeps its wiring in, if there is one.
extern "C" void switchUnload(Switch* object)
{
	void* state = object->state;

	if (state != NULL) {
		memset(state, 0, 0x14);
	}
}
