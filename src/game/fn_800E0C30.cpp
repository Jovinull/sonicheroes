// If the slot's controller check passes and the player's mode is outside 2..3 and nothing blocks it, restarts the slot's 0x3C-frame timer; returns whether the check passed.

struct Mode800E0C30 {
	unsigned char pad0[0x140];
	int f140;
};
struct Slot800E0C30 {
	unsigned char pad0[0x254];
	int f254;
	Mode800E0C30* f258;
};
struct Timer800E0C30 {
	unsigned char pad0[4];
	short s4;
};

extern "C" {
extern Timer800E0C30* lbl_802AD090[];
extern Slot800E0C30* lbl_802AD0D0[];
int fn_800E0CC8(int, int, int);
int fn_80091FAC(void);

int fn_800E0C30(int k, int p4, int p5)
{
	Timer800E0C30* a = lbl_802AD090[k];
	Slot800E0C30* b  = lbl_802AD0D0[k];
	int t;
	if (fn_800E0CC8(k, p4, p5) == 0) {
		return 0;
	}
	t = b->f258->f140;
	if ((t >= 4 || t < 2) && fn_80091FAC() == 0 && b->f254 == 0) {
		a->s4 = 0x3c;
	}
	return 1;
}
}
