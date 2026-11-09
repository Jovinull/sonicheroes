// Puts the fighter into motion 0x2A (flag 0x1000 set, field 0x670 cleared) unless it is already in motion 0x3F with the flag set.

extern "C" {
struct Fighter800444F0 {
	unsigned char pad[0x670];
	short f670;
	unsigned char pad1[0x6f4 - 0x672];
	short motion;
	short flags;
};

void fn_800444F0(Fighter800444F0* f)
{
	if ((f->flags & 0x1000) == 0 || f->motion != 0x3F) {
		f->flags |= 0x1000;
		f->motion = 0x2A;
		f->f670   = 0;
	}
}
}
