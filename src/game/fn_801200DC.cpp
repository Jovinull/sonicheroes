// When the global table is allocated and fn_80018EA8 reports success, stores the float into entry idx of the table at +0x28.
struct Rec801200DC {
	unsigned char pad0[0x28];
	float f28[1];
};

extern "C" {
extern Rec801200DC* lbl_8042C700;
extern unsigned char lbl_8029C310[];
int fn_80018EA8(unsigned char* p);

void fn_801200DC(int idx, float v)
{
	Rec801200DC* r = lbl_8042C700;
	if (r != 0 && fn_80018EA8(lbl_8029C310) == 0) {
		r->f28[idx] = v;
	}
}
}
