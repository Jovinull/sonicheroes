// Runs the callback at +0x10 of the object with (object, arg), or, when none is installed,
// fn_8017C5A8 with the 27-byte string lbl_8028F050. Names are UNKNOWN.
struct Object8017E708 {
	unsigned char pad0[0x10];
	void (*callback)(Object8017E708* object, void* arg); // 0x10
};

extern "C" {
extern char lbl_8028F050[];
void fn_8017C5A8(Object8017E708* object, void* arg);

void fn_8017E708(Object8017E708* object, void* arg)
{
	if (object->callback != 0) {
		object->callback(object, arg);
	} else {
		fn_8017C5A8(object, lbl_8028F050);
	}
}
}
