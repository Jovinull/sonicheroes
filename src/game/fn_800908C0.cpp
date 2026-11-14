// Queues an item for player p of a team in the first free of its eight slots (signed bytes at
// 0x24C, with the player at 0x25C and a cleared byte at 0x254). A positive item in game mode 5
// (fn_80018C98) is also announced with fn_80137D0C. Returns 1 when queued, 0 when full.
struct Player800908C0 {
	unsigned char pad0[0x761];
	signed char f761;
};

struct Team800908C0 {
	unsigned char pad0[0x110];
	signed char f110[4];
	Player800908C0* players[4]; // 0x114
	unsigned char pad124[0x24C - 0x124];
	signed char items[8];  // 0x24C
	signed char f254[8];   // 0x254
	signed char owners[8]; // 0x25C
};

extern "C" {
extern int lbl_80239EE8[];
int fn_80018C98(void);
void fn_80137D0C(int sound, int a, int b);

int fn_800908C0(Team800908C0* t, int p, int item)
{
	int i;
	for (i = 0; i < 8; i++) {
		if (t->items[i] == 0) {
			t->items[i]  = item;
			t->owners[i] = p;
			t->f254[i]   = 0;
			if (item > 0 && fn_80018C98() == 5) {
				fn_80137D0C(lbl_80239EE8[item], t->players[p]->f761, t->f110[p]);
			}
			return 1;
		}
	}
	return 0;
}
}
