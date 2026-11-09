// Sets bit 0 of the halfword at 4 of the objects in lbl_8042C278, lbl_8042C298 and lbl_8042C2A0 (when set), and clears lbl_8042C2A0.

extern "C" {
struct Obj8005B558 {
	unsigned char pad[4];
	unsigned short f4;
};
extern Obj8005B558* lbl_8042C278;
extern Obj8005B558* lbl_8042C298;
extern Obj8005B558* lbl_8042C2A0;

void fn_8005B558()
{
	if (lbl_8042C278 != 0) {
		lbl_8042C278->f4 |= 1;
	}
	if (lbl_8042C298 != 0) {
		lbl_8042C298->f4 |= 1;
	}
	if (lbl_8042C2A0 != 0) {
		lbl_8042C2A0->f4 |= 1;
		lbl_8042C2A0 = 0;
	}
}
}
