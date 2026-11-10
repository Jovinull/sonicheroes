// Stores the float into the indexed entry of lbl_803043E8 when it exists.
struct Ent800C28F4 {
	unsigned char pad0[0x34];
	float f34;
};

extern "C" {
extern Ent800C28F4* lbl_803043E8[];

void fn_800C28F4(int i, float v)
{
	Ent800C28F4* e = lbl_803043E8[i];
	if (e != 0) {
		e->f34 = v;
	}
}
}
