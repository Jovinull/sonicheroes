// Calls callback(entry, data) for each entry of the pointer array at +0x10 of the object (count at
// +0x14), stopping early when it returns null. Names are UNKNOWN. Returns the object.
struct Object80159E18 {
	unsigned char pad0[0x10];
	void** entries; // 0x10
	int count;      // 0x14
};

typedef void* (*Callback80159E18)(void* entry, void* data);

extern "C" {
Object80159E18* fn_80159E18(Object80159E18* object, Callback80159E18 callback, void* data)
{
	int count = object->count;
	int i;
	for (i = 0; i < count; i++) {
		if (callback(object->entries[i], data) == 0) {
			return object;
		}
	}
	return object;
}
}
