// Sets the word at 0x4C of the object in lbl_8042C42C to 1, if any.

extern "C" {
struct Obj800C0288 {
	unsigned char pad[0x4c];
	int f4c;
};
extern Obj800C0288* lbl_8042C42C;

void fn_800C0288()
{
	if (lbl_8042C42C != 0) {
		lbl_8042C42C->f4c = 1;
	}
}
}
