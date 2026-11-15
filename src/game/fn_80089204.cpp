// Decides whether the player's current state allows the linked record's mode.

extern "C" {
struct Linked80089204 {
	unsigned char pad0[0x140];
	int mode; // 0x140
};

struct Obj80089204 {
	unsigned char pad0[0x761];
	signed char c761; // 0x761
	unsigned char pad1[0x9B0 - 0x762];
	int f9B0; // 0x9B0
	unsigned char pad2[4];
	Linked80089204* linked; // 0x9B8
};

int fn_80089204(Obj80089204* o)
{
	switch (o->linked->mode) {
		case 0:
		case 4:
		case 7:
		case 10:
			if (o->f9B0 == 0) {
				return 1;
			}
			break;
		case 1:
		case 5:
		case 6:
		case 8:
		case 11:
			if (o->f9B0 == 0) {
				return 1;
			}
			break;
		case 2:
		case 12:
			switch (o->c761) {
				case 2:
				case 5:
				case 8:
				case 11:
					return 1;
			}
			break;
		case 3:
		case 9:
			if (o->f9B0 == 0) {
				return 1;
			}
			break;
	}
	return 0;
}
}
