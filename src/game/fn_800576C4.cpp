// Prints the three words at 0x28, 0x2C and 0x30 of the object with the format lbl_80242C44.

extern "C" {
struct Obj800576C4 {
	unsigned char pad[0x28];
	int f28;
	int f2c;
	int f30;
};
extern char lbl_80242C44[];
void fn_80057524(const char*, ...);

void fn_800576C4(Obj800576C4* o)
{
	fn_80057524(lbl_80242C44, o->f28, o->f2c, o->f30);
}
}
