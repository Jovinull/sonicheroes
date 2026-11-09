// Sets the halfword at 0x202, applies SetPlayerMuteki for the player in byte 0x38 and calls fn_800CBC80 with lbl_8024EFA0.

extern "C" {
struct Obj800912B4 {
	unsigned char pad[0x38];
	signed char c38;
	unsigned char pad1[0x202 - 0x39];
	short s202;
};
extern unsigned char lbl_8024EFA0[];
void SetPlayerMuteki__Fi(int);
void fn_800CBC80(void*);

void fn_800912B4(Obj800912B4* o)
{
	o->s202 = 0x4ec;
	SetPlayerMuteki__Fi(o->c38);
	fn_800CBC80(lbl_8024EFA0);
}
}
