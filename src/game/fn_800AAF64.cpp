// For player slot idx (0..7) of lbl_802AD070: unless the leader of its group record (+0x9B8,
// "team" is an inferred name) is in state 0x12 or mode 0x26/0x27, sets the group's flag byte
// 0x20D + the player's signed index at 0x9BD.
struct Player800AAF64;
struct Team800AAF64 {
	unsigned char pad0[0x3B];
	signed char leader;
	unsigned char pad3C[0x114 - 0x3C];
	Player800AAF64* players[3];
	unsigned char pad120[0x20D - 0x120];
	unsigned char f20D[3];
};
struct Player800AAF64 {
	unsigned char pad0[0x628];
	int f628;
	unsigned char pad62C[0x6F0 - 0x62C];
	short f6F0;
	unsigned char pad6F2[0x9B8 - 0x6F2];
	Team800AAF64* team;
	unsigned char pad9BC[0x1];
	signed char f9BD;
};
extern "C" {
extern Player800AAF64* lbl_802AD070[];
void fn_800AAF64(int idx)
{
	Player800AAF64* p = lbl_802AD070[idx];
	Team800AAF64* team;
	Player800AAF64* leader;
	if (idx < 0 || idx >= 8 || p == 0) {
		return;
	}
	team = p->team;
	if (team == 0) {
		return;
	}
	leader = team->players[team->leader];
	if (leader->f628 == 0x12) {
		return;
	}
	if (leader->f6F0 == 0x26 || leader->f6F0 == 0x27) {
		return;
	}
	team->f20D[p->f9BD] = 1;
}
}
