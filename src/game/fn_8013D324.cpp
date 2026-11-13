#include "types.h"

extern "C" {
extern s32 lbl_8042C820;
void fn_8013CC54();

struct Obj8013D324 {
	u8 pad[0x48];
	void (*callback)();
};

void fn_8013D324(Obj8013D324* object)
{
	s32 offset                               = lbl_8042C820;
	void (*oldCallback)()                    = object->callback;
	*(void (**)())((u8*)object + offset + 8) = oldCallback;
	object->callback                         = fn_8013CC54;
}
}
