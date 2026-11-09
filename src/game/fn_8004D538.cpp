// Hands on the element at the given index of the table at lbl_802B908C, whose
// elements are 0x2324 bytes.

extern "C" {
extern unsigned char lbl_802B908C[];
int fn_80050AB8(void*);

int fn_8004D538(int unused, int index)
{
	return fn_80050AB8(lbl_802B908C + index * 0x2324);
}
}
