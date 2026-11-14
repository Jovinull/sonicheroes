// Runs the optional callback at +0x0 of the object with (object, arg), then fn_8017C9E8 with the
// same arguments. Names are UNKNOWN.
struct Object8017C5A8 {
	void (*callback)(Object8017C5A8* object, void* arg); // 0x0
};

extern "C" {
void fn_8017C9E8(Object8017C5A8* object, void* arg);

void fn_8017C5A8(Object8017C5A8* object, void* arg)
{
	if (object->callback != 0) {
		object->callback(object, arg);
	}
	fn_8017C9E8(object, arg);
}
}
