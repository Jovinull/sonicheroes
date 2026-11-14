// Dispatches (object, arg) to the callback at +0x1B0 of the object, or to fn_8017CEC0 when none is
// installed; nothing happens when either argument is null. Names are UNKNOWN.
struct Object8017CE74 {
	unsigned char pad0[0x1B0];
	void (*f1B0)(Object8017CE74* object, void* arg); // 0x1B0
};

extern "C" {
void fn_8017CEC0(Object8017CE74* object, void* arg);

void fn_8017CE74(Object8017CE74* object, void* arg)
{
	if (object == 0 || arg == 0) {
		return;
	}
	if (object->f1B0 != 0) {
		object->f1B0(object, arg);
	} else {
		fn_8017CEC0(object, arg);
	}
}
}
