// Sets bit 0 of the halfword at 4 of the object in lbl_8042C704 and clears the pointer, if any.

extern "C" {
struct Obj80120060 {
	unsigned char pad[4];
	unsigned short f4;
};
extern Obj80120060* lbl_8042C704;

void fn_80120060()
{
	if (lbl_8042C704 != 0) {
		lbl_8042C704->f4 |= 1;
		lbl_8042C704 = 0;
	}
}
}
