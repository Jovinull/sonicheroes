// Player state change: unless the player is in mode 0x3F with flag 0x1000 set, a player in state
// 0x21, 0x26 or 0x27 is put into state 0x26 (clearing the halfword 0x14E of the block at 0x760,
// resetting the vectors with fn_800E12FC and clearing flags 0x2500); any other state sets flag
// 0x1000 and mode 0x17. Block layouts are inferred.
struct Block80043F28 {
	unsigned char pad0[0x14E];
	short f14E;
};

struct Player80043F28 {
	unsigned char pad0[0x6F0];
	short state; // 0x6F0
	unsigned char pad6F2[0x2];
	short mode;  // 0x6F4
	short flags; // 0x6F6
	unsigned char pad6F8[0x720 - 0x6F8];
	unsigned char f720[0x40];
	Block80043F28 f760;
};

extern "C" {
void fn_800E12FC(void* a, Block80043F28* b);

void fn_80043F28(Player80043F28* p)
{
	unsigned char* a = p->f720;
	Block80043F28* b = &p->f760;
	if ((p->flags & 0x1000) && p->mode == 0x3F) {
		return;
	}
	switch (p->state) {
		case 0x21:
		case 0x26:
		case 0x27:
			p->state = 0x26;
			b->f14E  = 0;
			fn_800E12FC(a, b);
			p->flags &= ~0x2500;
			break;
		default:
			p->flags |= 0x1000;
			p->mode = 0x17;
			break;
	}
}
}
