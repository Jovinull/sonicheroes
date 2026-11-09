// Returns word 84 of the object in lbl_8042C760, or 0 when there is none.

extern "C" {
struct Obj8012DAA0 {
	unsigned char pad[0x84];
	int f84;
	unsigned char pad1[0x90 - 0x88];
	int f90;
	int f94;
};
extern Obj8012DAA0* lbl_8042C760;

int fn_8012DAA0()
{
	if (lbl_8042C760 != 0) {
		return lbl_8042C760->f84;
	}
	return 0;
}
}
