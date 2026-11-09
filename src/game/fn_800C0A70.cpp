// Sets word 0x48 of the object in lbl_8042C424 when it exists and its word 0x44 is 1.

extern "C" {
struct Obj800C0A70 {
	unsigned char pad[0x44];
	int f44;
	int f48;
};
extern Obj800C0A70* lbl_8042C424;

void fn_800C0A70()
{
	if (lbl_8042C424 != 0 && lbl_8042C424->f44 == 1) {
		lbl_8042C424->f48 = 1;
	}
}
}
