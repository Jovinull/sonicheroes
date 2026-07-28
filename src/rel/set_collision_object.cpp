#include "types.h"

// TObjSetCollision, as far as it has been carved: the parameter guard, the two
// hooks the module's registration record points at, and the factory.
//
// The guard is the last slot of the class's second base's
// vtable, the same slot switchClamp and springClamp fill for their classes.
// Like the switch it also refreshes the four labels the editor shows, one per
// field, all four picked by the shape the volume is set to.
//
// The claim is .text 0x5F4C to 0x616C, .rodata 0xE8 to 0xF0 and the .ctors word
// that names the registration. The four name
// tables and the label block stay with the module and are reached as
// externals: the block is written by another function that is still assembly,
// and the strings the tables point at sit between them, so no single range
// covers what would have to be claimed.
//
// The strings say what the fields are. The shape picks between "SPHERE",
// "CYLINDER", "RECTANGLE" and "CYLINDER XZ", so it is bounded to zero through
// three, and the three sizes are bounded to zero up to a thousand. Which of the
// three sizes a shape actually uses is what the other tables encode: a sphere
// labels the first "Scale R" and the other two "not in use", a cylinder adds
// "Scale H", and so on.
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else.

typedef struct SetCollisionParams {
	s32 shape; // 0x00
	f32 sizeX; // 0x04
	f32 sizeY; // 0x08
	f32 sizeZ; // 0x0C
} SetCollisionParams;

typedef struct Frame {
	u8 unk0[0x2C];              // 0x00
	SetCollisionParams* params; // 0x2C
} Frame;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

// The record the module registers the class with, the same shape every TObj*
// uses. The last two fields are what the editor lays the parameters out from:
// one character per field saying what type it is, and the label array the guard
// above keeps up to date.
typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	s16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
} ObjectEntry;               // 0x2C

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* setCollisionCtor(void* object, void* owner);
extern "C" ObjectEntry setCollisionEntry;
extern "C" char setCollisionDisplayName[];
extern "C" char setCollisionFieldTypes[];
extern "C" const char* setCollisionLabels[];
extern "C" const char* setCollisionShapeNames[];
extern "C" const char* setCollisionSizeXNames[];
extern "C" const char* setCollisionSizeYNames[];
extern "C" const char* setCollisionSizeZNames[];

// The object it is called on is not used: everything it touches hangs off the
// keyframe it is handed, or is module wide.
extern "C" void setCollisionClamp(void* object, Frame* frame)
{
	SetCollisionParams* params = frame->params;

	if (params->shape < 0) {
		params->shape = 0;
	}
	if (params->shape >= 4) {
		params->shape = 3;
	}

	if (params->sizeX < 0.0f) {
		params->sizeX = 0.0f;
	}
	if (params->sizeX > 1000.0f) {
		params->sizeX = 1000.0f;
	}

	if (params->sizeY < 0.0f) {
		params->sizeY = 0.0f;
	}
	if (params->sizeY > 1000.0f) {
		params->sizeY = 1000.0f;
	}

	if (params->sizeZ < 0.0f) {
		params->sizeZ = 0.0f;
	}
	if (params->sizeZ > 1000.0f) {
		params->sizeZ = 1000.0f;
	}

	setCollisionLabels[0] = setCollisionShapeNames[params->shape];
	setCollisionLabels[1] = setCollisionSizeXNames[params->shape];
	setCollisionLabels[2] = setCollisionSizeYNames[params->shape];
	setCollisionLabels[3] = setCollisionSizeZNames[params->shape];
}

extern "C" void setCollisionUnload(void) { }

extern "C" void setCollisionLoad(void) { }

// Allocates one volume. The constructor is a real call rather than something
// inlined, which is what keeps this down to four lines: the factories that have
// it inlined spend an extra register copy no source form reproduces.
extern "C" void setCollisionCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xE8);

	if (memory != NULL) {
		setCollisionCtor(memory, lbl_8042C110);
	}
}

// Fills the record in and hands it to the editor. The module's .ctors list
// names this, so it runs before the stage does.
extern "C" void setCollisionRegister(void)
{
	setCollisionEntry.flags = 0;
	setCollisionEntry.unk18 = 0;

	setCollisionEntry.name   = setCollisionDisplayName;
	setCollisionEntry.load   = setCollisionLoad;
	setCollisionEntry.unload = setCollisionUnload;
	setCollisionEntry.create = setCollisionCreate;
	setCollisionEntry.unk10  = NULL;

	setCollisionEntry.flags = 0x20000;
	setCollisionEntry.unk18 = 0;
	setCollisionEntry.unk20 = 0x1E;
	setCollisionEntry.unk1C = 0x50;
	setCollisionEntry.unk1E = 2;
	setCollisionEntry.unk21 = 0;

	setCollisionEntry.fieldTypes = setCollisionFieldTypes;
	setCollisionEntry.fieldNames = setCollisionLabels;

	if (setCollisionFieldTypes != NULL) {
		setCollisionEntry.flags |= 8;
	} else {
		setCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const setCollisionCtorEntry)(void) = setCollisionRegister;
