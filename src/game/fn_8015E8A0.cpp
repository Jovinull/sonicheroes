#include "types.h"

// Forwards the object context and its nested halfword to fn_8015E180.
extern "C" {
struct Node8015E8A0 {
	u8 pad[4];
	u16 field4;
};
struct Holder8015E8A0 {
	u8 pad[0x54];
	Node8015E8A0* field54;
};
void fn_8015E180(void*, Holder8015E8A0*, void*, u16);
void fn_8015E8A0(void* owner, Holder8015E8A0* object)
{
	fn_8015E180(owner, object, (u8*)object + 0x58, object->field54->field4);
}
}
