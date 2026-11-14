// Processes object with a selected callback: without a +0x4 block it only runs fn_8015597C and
// returns the record lbl_8028D2B8; otherwise flag bit 0 selects the record's callback/argument pair
// (+0x10/+0x14) or fn_801585BC with no argument, and a successful call is followed by fn_8015597C.
// Names are UNKNOWN. Returns the callback's result (null for a null object or a failed call).
struct Object8015884C {
	unsigned char pad0[0x4];
	void* f4; // 0x4
};

struct Record8015884C {
	unsigned char pad0[0x10];
	void* (*callback)(Object8015884C* object, void* arg); // 0x10
	void* arg;                                            // 0x14
};

extern "C" {
extern Record8015884C lbl_8028D2B8;
void fn_8015597C(Object8015884C* object);
void* fn_801585BC(Object8015884C* object, void* arg);

void* fn_8015884C(Object8015884C* object, unsigned int flags)
{
	void* (*callback)(Object8015884C* object, void* arg);
	void* arg;
	void* result;
	if (object != 0) {
		if (object->f4 == 0) {
			fn_8015597C(object);
			return &lbl_8028D2B8;
		}
		if (flags & 1) {
			callback = lbl_8028D2B8.callback;
			arg      = lbl_8028D2B8.arg;
		} else {
			callback = fn_801585BC;
			arg      = 0;
		}
		result = callback(object, arg);
		if (result != 0) {
			fn_8015597C(object);
			return result;
		}
	}
	return 0;
}
}
