// Returns the value at +0x30 of the object stored at arg0 within the table lbl_8042C858, or 0 when there is none.

extern "C" {
struct Node80149480 {
	unsigned char pad[0x30];
	int f30;
};
extern int lbl_8042C858;

int fn_80149480(int a)
{
	Node80149480* t = *(Node80149480**)(a + lbl_8042C858);
	if (t == 0) {
		return 0;
	}
	return t->f30;
}
}
