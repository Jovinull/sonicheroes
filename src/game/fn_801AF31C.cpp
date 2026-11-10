// Stores the value and the 0x01000000 marker into the object and the indexed table; returns 1.
extern "C" {
extern int lbl_8042CA60;
int fn_801AF31C(int* o, int v)
{
	*o                                 = v;
	((int*)((int)o + lbl_8042CA60))[8] = 0x01000000;
	return 1;
}
}
