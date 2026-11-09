// Releases the two owned objects at 0xA44 (fn_800126C8) and 0xA50 (ONEFILE destructor) when set and clears the pointers.

extern "C" {
struct Obj8005B268 {
	unsigned char pad[0xa44];
	unsigned fa44;
	unsigned char pad1[0xa50 - 0xa48];
	unsigned fa50;
};
void fn_800126C8(unsigned);
void __dt__7ONEFILEFv(unsigned, int);

void fn_8005B268(Obj8005B268* o)
{
	if (o->fa44 != 0) {
		fn_800126C8(o->fa44);
		o->fa44 = 0;
	}
	if (o->fa50 != 0) {
		__dt__7ONEFILEFv(o->fa50, 1);
		o->fa50 = 0;
	}
}
}
