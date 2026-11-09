// Runs fn_801491A8, then fn_801527A4 with the object's field 0x18, the callback fn_800B8D98 and entry *p of lbl_802539B8 (or 0 when p is null); returns the object.

extern "C" {
struct Obj800B8C48 {
	unsigned char pad[0x18];
	int f18;
};
extern int lbl_802539B8[];
void fn_800B8D98();
void fn_801491A8();
void fn_801527A4(int, void (*)(), int);

Obj800B8C48* fn_800B8C48(Obj800B8C48* o, int* p)
{
	int h;
	fn_801491A8();
	h = o->f18;
	if (p != 0) {
		fn_801527A4(h, fn_800B8D98, lbl_802539B8[*p]);
	} else {
		fn_801527A4(h, fn_800B8D98, 0);
	}
	return o;
}
}
