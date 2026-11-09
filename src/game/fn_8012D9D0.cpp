// Initializes the current object's state fields (0x84, 0x88, 0x9C) and returns 1,
// or returns 0 when there is no current object.

extern "C" {
struct Obj8012D9D0 {
	unsigned char pad[0x84];
	int a; // 0x84
	int b; // 0x88
	unsigned char pad2[0x9c - 0x8c];
	int c; // 0x9C
};
extern Obj8012D9D0* lbl_8042C760;

int fn_8012D9D0()
{
	if (lbl_8042C760 != 0) {
		lbl_8042C760->a = 1;
		lbl_8042C760->b = 0;
		lbl_8042C760->c = 0;
		return 1;
	}
	return 0;
}
}
