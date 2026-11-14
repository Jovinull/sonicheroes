// Calls callback(entry, object, data) for each 0x100-byte entry of the array returned by
// fn_8019460C for the object's +0xAC handle (count at +0xB0). Names are UNKNOWN. Returns the
// object.
#include "types.h"

struct Entry80173D74 {
	unsigned char b[0x100];
};

struct Object80173D74 {
	unsigned char pad0[0xAC];
	void* handle;       // 0xAC
	unsigned int count; // 0xB0
};

typedef void (*Callback80173D74)(Entry80173D74* entry, Object80173D74* object, void* data);

extern "C" {
Entry80173D74* fn_8019460C(void* handle);

Object80173D74* fn_80173D74(Object80173D74* object, Callback80173D74 callback, void* data)
{
	Entry80173D74* base = fn_8019460C(object->handle);
	Entry80173D74* end  = base + object->count;
	Entry80173D74* entry;
	for (entry = base; entry != end; entry++) {
		callback(entry, object, data);
	}
	return object;
}
}
