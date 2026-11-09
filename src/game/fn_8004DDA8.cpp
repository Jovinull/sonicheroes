// Looks up, in the table at lbl_80239B74 (8-byte entries), the entry the current
// team's record at the given index points at, and returns its first word. The
// team records are 0x2324 bytes and hold 0x114-byte entries.

extern "C" {
extern unsigned char lbl_802B908C[];
extern int lbl_8042C1FC;
struct Pair8 {
	int first;
	int second;
};
extern Pair8 lbl_80239B74[];

int fn_8004DDA8(int unused, int index)
{
	unsigned char* entry = lbl_802B908C;

	entry += lbl_8042C1FC * 0x2324;
	entry += index * 0x114;
	return lbl_80239B74[*(int*)(entry + 0x11D0)].first;
}
}
