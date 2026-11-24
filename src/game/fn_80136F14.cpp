// Constructor of a HUD task base class (HYPOTHESIS; the class name is UNKNOWN, its vtable is
// lbl_8028B024 and its destructor dtor_80136EA8; fn_80137214 and fn_8013764C derive from it),
// written out as the function MWCC makes of it: builds the TObject under `parent`, sets the class
// name lbl_8042BC20 and the object size 0x40, an opaque white colour (0x3C) and two float pairs.
// Nothing can throw after the base, so the exception table has no actions.
#include "types.h"

struct Obj80136F14 {
	char* className; // 0x00
	u8 pad4[0x18 - 0x4];
	void* vtable;   // 0x18
	u16 f1C;        // 0x1C
	u16 objectSize; // 0x1E
	u8 pad20[0x2C - 0x20];
	f32 f2C;  // 0x2C
	f32 f30;  // 0x30
	f32 f34;  // 0x34
	f32 f38;  // 0x38
	u8 red;   // 0x3C
	u8 green; // 0x3D
	u8 blue;  // 0x3E
	u8 alpha; // 0x3F
};

extern "C" {
extern u8 lbl_8028B024[];
extern char* lbl_8042BC20;
extern f32 lbl_8042F0B0;
extern f32 lbl_8042F0B4;
void __ct__7TObjectFP7TObject(void* object, void* parent);

Obj80136F14* fn_80136F14(Obj80136F14* o, void* parent)
{
	__ct__7TObjectFP7TObject(o, parent);
	o->vtable     = lbl_8028B024;
	o->className  = lbl_8042BC20;
	o->objectSize = 0x40;
	o->alpha      = 0xFF;
	o->red        = 0xFF;
	o->green      = 0xFF;
	o->blue       = 0xFF;
	o->f30 = o->f2C = lbl_8042F0B0;
	o->f38 = o->f34 = lbl_8042F0B4;
	return o;
}
}
