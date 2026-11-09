// Puts the fighter into motion 0x2D (when its linked record is in mode 0xE) or 0x2C, with flag 0x1000, unless it is already in motion 0x3F with the flag set.

extern "C" {
struct Linked8004448C {
	unsigned char pad[0x154];
	int f154;
};
struct Fighter8004448C {
	unsigned char pad[0x6f4];
	short motion;
	short flags;
	unsigned char pad1[0x9b8 - 0x6f8];
	Linked8004448C* in;
};

void fn_8004448C(Fighter8004448C* f)
{
	if ((f->flags & 0x1000) == 0 || f->motion != 0x3F) {
		if (f->in->f154 == 0xe) {
			f->flags |= 0x1000;
			f->motion = 0x2d;
			return;
		}
		f->flags |= 0x1000;
		f->motion = 0x2c;
	}
}
}
