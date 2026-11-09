// Copies three words from the source into lbl_802892D8.

extern "C" {
struct Vec80119564 {
	int a;
	int b;
	int c;
};
extern int lbl_802892D8[];

void fn_80119564(Vec80119564* o)
{
	lbl_802892D8[0] = o->a;
	lbl_802892D8[1] = o->b;
	lbl_802892D8[2] = o->c;
}
}
