// Clears word 0x188 of the object in lbl_8042C150; returns 1.

extern "C" {
struct Obj800EBB14 {
	unsigned char pad[0x188];
	int f188;
};
extern Obj800EBB14* lbl_8042C150;

int fn_800EBB14()
{
	lbl_8042C150->f188 = 0;
	return 1;
}
}
