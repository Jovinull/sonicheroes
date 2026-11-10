// Gathers the three positions of the objects listed in lbl_802539C4 and passes them with the callback fn_800B899C to fn_80159E9C.
struct V3_800B8904 {
	float x;
	float y;
	float z;
};
struct Src800B8904 {
	unsigned char pad0[0x30];
	float f30;
	float f34;
	float f38;
};

extern "C" {
extern int lbl_802539C4[];
extern unsigned char fn_800B899C[];
Src800B8904* fn_8019E8EC(int a);
void fn_80159E9C(int a, unsigned char* cb, V3_800B8904* v);

void fn_800B8904(int a)
{
	V3_800B8904 sp[3];
	int i;
	for (i = 0; i < 3; i++) {
		Src800B8904* s = fn_8019E8EC(lbl_802539C4[i]);
		sp[i].x        = s->f30;
		sp[i].y        = s->f34;
		sp[i].z        = s->f38;
	}
	fn_80159E9C(a, fn_800B899C, sp);
}
}
