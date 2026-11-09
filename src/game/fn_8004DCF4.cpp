// Returns the address of the record at 0xA4 of player `i` in the current team record.

extern "C" {
extern unsigned char lbl_802B908C[];
extern int lbl_8042C1FC;

void* fn_8004DCF4(int unused, int i)
{
	return lbl_802B908C + lbl_8042C1FC * 0x2324 + i * 0x114 + 0xa4;
}
}
