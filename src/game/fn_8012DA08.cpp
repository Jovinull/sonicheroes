// Returns 0 when the object in lbl_8042C760 exists and its word 0x88 is 0; otherwise 1.

extern "C" {
struct Obj8012DA08 {
	unsigned char pad[0x88];
	int f88;
};
extern Obj8012DA08* lbl_8042C760;

int fn_8012DA08()
{
	if (lbl_8042C760 != 0 && lbl_8042C760->f88 == 0) {
		return 0;
	}
	return 1;
}
}
