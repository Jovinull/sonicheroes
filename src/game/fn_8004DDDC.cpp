// Looks up, in the table at lbl_80239A30 (12-byte entries), the entry the current
// team's record at the given index points at, and returns its first word.
// fn_8004DDA8 does the same for another field and table.

extern "C" {
extern unsigned char lbl_802B908C[];
extern int lbl_8042C1FC;
struct Trio12 {
	int first;
	int second;
	int third;
};
extern Trio12 lbl_80239A30[];

int fn_8004DDDC(int unused, int index)
{
	unsigned char* entry = lbl_802B908C;

	entry += lbl_8042C1FC * 0x2324;
	entry += index * 0x114;
	return lbl_80239A30[*(int*)(entry + 0x90)].first;
}
}
