// Picks the action ID (halfword at +0x6F0) from the mode of the linked object at +0x9B8: mode 3
// selects 0x35 or 0x34 depending on whether the float at +0xA5C exceeds lbl_8042D658, mode 2
// selects 4 or 0x29 depending on whether the linked object's +0x121 byte is 1; other modes leave it
// unchanged. Names are UNKNOWN.
struct Linked800732CC {
	unsigned char pad0[0x121];
	signed char f121; // 0x121
	unsigned char pad122[0x140 - 0x122];
	int mode; // 0x140
};

struct Object800732CC {
	unsigned char pad0[0x6F0];
	short action; // 0x6F0
	unsigned char pad6F2[0x9B8 - 0x6F2];
	Linked800732CC* linked; // 0x9B8
	unsigned char pad9BC[0xA5C - 0x9BC];
	float fA5C; // 0xA5C
};

extern "C" {
// .sdata2 threshold (non-const: reloaded per use as an ordinary global).
extern float lbl_8042D658;

void fn_800732CC(Object800732CC* object)
{
	Linked800732CC* linked = object->linked;
	switch (linked->mode) {
		case 2:
			if (linked->f121 == 1) {
				object->action = 4;
			} else {
				object->action = 0x29;
			}
			break;
		case 3:
			if (object->fA5C > lbl_8042D658) {
				object->action = 0x35;
			} else {
				object->action = 0x34;
			}
			break;
	}
}
}
