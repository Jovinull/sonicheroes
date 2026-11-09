// Clears the state word (0x2310) of team record `i`.

extern "C" {
struct Player8004CDBC {
	unsigned char pad[0x90];
	int f90;
	int f94;
	unsigned char pad1[0xa0 - 0x98];
	int fa0;
	unsigned char pad2[0x114 - 0xa4];
};
struct Team8004CDBC {
	Player8004CDBC pl[8];
	unsigned char pad[0x2310 - 8 * 0x114];
	int f2310;
	unsigned char pad1[0x231c - 0x2314];
	int f231c;
	unsigned char pad2[0x2324 - 0x2320];
};
extern Team8004CDBC lbl_802B908C[];

void fn_8004CDBC(int unused, int i)
{
	lbl_802B908C[i].f2310 = 0;
}
}
