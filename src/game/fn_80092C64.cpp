// For each rank k from 0 to the team's signed count at 0x39 (inclusive), passes the first player
// other than the one at index 0x3A whose word 0x9B0 equals k to fn_800898F8.
struct Player80092C64 {
	unsigned char pad0[0x9B0];
	int f9B0;
};

struct Team80092C64 {
	unsigned char pad0[0x39];
	signed char count;
	signed char skip;
	unsigned char pad3B[0x114 - 0x3B];
	Player80092C64* players[1];
};

extern "C" {
void fn_800898F8(Player80092C64* p);

void fn_80092C64(Team80092C64* t)
{
	int k;
	for (k = 0; k <= t->count; k++) {
		int j;
		for (j = 0; j < t->count; j++) {
			if (j != t->skip && t->players[j] != 0 && t->players[j]->f9B0 == k) {
				fn_800898F8(t->players[j]);
				break;
			}
		}
	}
}
}
