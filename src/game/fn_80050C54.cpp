// Maps the mode at +0x34 of the first entry of lbl_80303DC8 to a flag bit (0..3 -> 0x100..0x800), 0x1000 when the global state is 2, otherwise returns arg0 unchanged.

extern "C" {
struct Glob80050C54 {
	unsigned char pad[0x28];
	signed char c28;
};
struct Entry80050C54 {
	unsigned char pad[0x34];
	int f34;
};
extern Glob80050C54* lbl_8042C180;
extern Entry80050C54* lbl_80303DC8[];

int fn_80050C54(int a)
{
	if (lbl_8042C180->c28 == 2) {
		return 0x1000;
	}
	switch ((*(Entry80050C54**)lbl_80303DC8)->f34) {
		case 0:
			return 0x100;
		case 1:
			return 0x200;
		case 2:
			return 0x400;
		case 3:
			return 0x800;
	}
	return a;
}
}
