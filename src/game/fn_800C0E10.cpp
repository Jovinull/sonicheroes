// Sets word 0x48 of the object in lbl_8042C41C when it exists and its word 0x44 is 1.

extern "C" {
struct Obj800C0E10 {
	unsigned char pad[0x44];
	int f44;
	int f48;
};
extern Obj800C0E10* lbl_8042C41C;

void fn_800C0E10()
{
	if (lbl_8042C41C != 0 && lbl_8042C41C->f44 == 1) {
		lbl_8042C41C->f48 = 1;
	}
}
}
