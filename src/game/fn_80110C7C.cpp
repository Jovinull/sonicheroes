// Caps the positive count at 0x30 to 1 and, when word 0x3C is clear and the handle at 0x58 is not
// -1, passes that handle to fn_800CB1E8.
struct Obj80110C7C {
	unsigned char pad0[0x30];
	int f30;
	unsigned char pad34[0x8];
	int f3C;
	unsigned char pad40[0x18];
	int f58;
};

extern "C" {
void fn_800CB1E8(int handle);

void fn_80110C7C(Obj80110C7C* o)
{
	if (o->f30 > 0) {
		o->f30 = 1;
	}
	if (o->f3C == 0 && o->f58 != -1) {
		fn_800CB1E8(o->f58);
	}
}
}
