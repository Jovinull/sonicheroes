// Returns word 0xA0 of player `i` of the current team record.

extern "C" {
struct Player8004DD18 {
	unsigned char pad[0x90];
	int f90;
	int f94;
	unsigned char pad1[0xa0 - 0x98];
	int fa0;
	unsigned char pad2[0x114 - 0xa4];
};
struct Team8004DD18 {
	Player8004DD18 pl[8];
	unsigned char pad[0x2310 - 8 * 0x114];
	int f2310;
	unsigned char pad1[0x231c - 0x2314];
	int f231c;
	unsigned char pad2[0x2324 - 0x2320];
};
extern Team8004DD18 lbl_802B908C[];
extern int lbl_8042C1FC;

int fn_8004DD18(int unused, int i)
{
	return lbl_802B908C[lbl_8042C1FC].pl[i].fa0;
}
}
