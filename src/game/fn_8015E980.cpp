#include "types.h"

// Forwards the object context, a subobject pointer, and its nested halfword.
extern "C" {
struct Node8015E980 {
	u8 pad[4];
	u16 field4;
};
struct Holder8015E980 {
	u8 pad[0x80];
	Node8015E980* field80;
};
void fn_8015E180(void*, Holder8015E980*, void*, u16);
void fn_8015E980(void* owner, Holder8015E980* object)
{
	fn_8015E180(owner, object, (u8*)object + 0x34, object->field80->field4);
}
}
