// Sets the halfword at 0x200, sets bit 2 of the halfword at 0x206 and calls fn_800CBC80 with lbl_8024EFB0.

extern "C" {
struct Obj800912F0 {
	unsigned char pad[0x200];
	short s200;
	unsigned char pad1[4];
	short s206;
};
extern unsigned char lbl_8024EFB0[];
void fn_800CBC80(void*);

void fn_800912F0(Obj800912F0* o)
{
	o->s200 = 0x384;
	o->s206 |= 4;
	fn_800CBC80(lbl_8024EFB0);
}
}
