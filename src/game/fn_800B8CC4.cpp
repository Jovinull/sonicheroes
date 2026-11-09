// Calls fn_801491A8, then fn_801527A4 with the object's field 0x18, the callback fn_800B8D98 and entry idx of lbl_802539B8.

extern "C" {
struct Obj800B8CC4 {
	unsigned char pad[0x18];
	int f18;
};
extern int lbl_802539B8[];
void fn_801491A8();
void fn_800B8D98();
void fn_801527A4(int, void (*)(), int);

void fn_800B8CC4(Obj800B8CC4* o, int idx)
{
	fn_801491A8();
	fn_801527A4(o->f18, fn_800B8D98, lbl_802539B8[idx]);
}
}
