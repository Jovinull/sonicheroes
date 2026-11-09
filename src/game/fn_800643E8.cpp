// The word an object's target points at, when the object has its 0x10000 flag
// and a target; 0 otherwise.

extern "C" {
struct Obj800643E8 {
	int unk0;
	int flags; // 0x04
	unsigned char pad[0x24];
	int* target; // 0x2C
};

int fn_800643E8(Obj800643E8* obj)
{
	if ((obj->flags & 0x10000) != 0) {
		if (obj->target == 0) {
			return 0;
		}
		return *obj->target;
	}
	return 0;
}
}
