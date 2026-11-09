// State handler: in state 0x1B calls fn_80044A94 and clears +0x6F8; in state 0xA clears +0x6F8 and either calls fn_80044A94 (when the low flag bits are set) or switches to state 4, resets the animation fields and calls fn_800465D8; then raises flag 4 at +0x8B8.

extern "C" {
struct Obj80044E10 {
	unsigned char pad[0x639];
	unsigned char c639;
	short s63a;
	short s63c;
	unsigned char pad1[2];
	int f640;
	unsigned char pad2[0x6f0 - 0x644];
	short s6f0;
	short s6f2;
	short s6f4;
	short s6f6;
	short s6f8;
	unsigned char pad3[0x8b8 - 0x6fa];
	short s8b8;
};
void fn_80044A94(void);
void fn_800465D8(void*, int);

void fn_80044E10(Obj80044E10* o)
{
	switch (o->s6f0) {
		case 27:
			fn_80044A94();
			o->s6f8 = 0;
			return;
		case 10:
			o->s6f8 = 0;
			if ((o->s6f6 & 3) != 0) {
				fn_80044A94();
			} else {
				short t;
				o->s6f0 = 4;
				t       = o->s6f6;
				o->s6f6 = t & ~0x500;
				o->s63a = 0;
				o->s63c = 0;
				o->f640 = 0;
				o->c639 = 0;
				fn_800465D8(o, t);
			}
			o->s8b8 = o->s8b8 | 4;
			return;
	}
}
}
