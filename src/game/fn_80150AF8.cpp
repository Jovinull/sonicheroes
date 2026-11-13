#include "types.h"

// Updates the records at owner + 0x08 and entry + 0x3C/0x40.
extern "C" {
struct Link80150AF8 {
	Link80150AF8* field0;
	Link80150AF8* field4;
};
struct Owner80150AF8 {
	u8 pad[8];
	Link80150AF8* volatile field8;
};
struct Entry80150AF8 {
	u8 pad[0x3C];
	Owner80150AF8* field3C;
	Link80150AF8 link40;
};

void fn_80150AF8(Owner80150AF8* owner, Entry80150AF8* entry)
{
	entry->link40.field0  = owner->field8;
	entry->link40.field4  = (Link80150AF8*)&owner->field8;
	owner->field8->field4 = &entry->link40;
	owner->field8         = &entry->link40;
	entry->field3C        = owner;
}
}
