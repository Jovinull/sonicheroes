// Sets the screen fade parameter (selected by mode 0 or 1) for the object's handle and records the mode.
struct Obj8004DC80 {
	unsigned char pad0[0x28];
	int f28;
};

extern "C" {
extern float lbl_8042C20C;
extern float lbl_8042C210;
extern int lbl_8042C218;
void fn_8019CD68(int a, float f);

void fn_8004DC80(Obj8004DC80* o, int mode)
{
	switch (mode) {
		case 1:
			fn_8019CD68(o->f28, lbl_8042C210);
			break;
		case 0:
			fn_8019CD68(o->f28, lbl_8042C20C);
			break;
	}
	lbl_8042C218 = mode;
}
}
