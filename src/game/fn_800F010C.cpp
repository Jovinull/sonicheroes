// Clears the object's three state fields, runs fn_800EFA08, raises the float at +0x7C4 to +0x840 when mode 1 is active and sets +0x7C0 when the +0x63C counter is non-zero.
struct Sub800F010C {
	unsigned char pad0[0x140];
	int f140;
};
struct Obj800F010C {
	unsigned char pad0[0x63A];
	short f63A;
	short f63C;
	unsigned char pad63E[2];
	int f640;
	unsigned char pad644[0x17C];
	float f7C0;
	float f7C4;
	unsigned char pad7C8[0x78];
	float f840;
	unsigned char pad844[0x174];
	Sub800F010C* f9B8;
};

extern "C" {
extern float lbl_8042E3E4;
void fn_800EFA08();

void fn_800F010C(Obj800F010C* o)
{
	o->f63A = 0;
	o->f63C = 0;
	o->f640 = 0;
	fn_800EFA08();
	if (o->f9B8->f140 == 1) {
		if (o->f7C4 < o->f840) {
			o->f7C4 = o->f840;
		}
	}
	if (o->f63C != 0) {
		o->f7C0 = lbl_8042E3E4;
	}
}
}
