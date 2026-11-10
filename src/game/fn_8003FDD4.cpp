// Resets the player's action state fields (counters, flags and default floats) to their initial values.
struct Obj8003FDD4 {
	unsigned char pad0[0x638];
	unsigned char f638;
	unsigned char f639;
	short f63A;
	short f63C;
	unsigned char pad63E[0x2];
	int f640;
	int f644;
	int f648;
	int f64C;
	int f650;
	int f654;
	int f658;
	int f65C;
	int f660;
	int f664;
	short f668;
	unsigned char pad66A[0x2];
	float f66C;
	short f670;
	short f672;
	float f674;
	unsigned char pad678[0x10];
	short f688;
	short f68A;
	float f68C;
	float f690;
	float f694;
	float f698;
	float f69C;
	unsigned char f6A0;
	unsigned char f6A1;
	short f6A2;
	float f6A4;
	int f6A8;
	unsigned char pad6AC[0x33B];
	unsigned char f9E7;
	unsigned char pad9E8[0x1];
	unsigned char f9E9;
};

extern "C" {
extern float lbl_8042D0E8;
extern float lbl_8042D120;

void fn_8003FDD4(Obj8003FDD4* o)
{
	o->f688 = 0;
	o->f68A = 0;
	float z = lbl_8042D120;
	o->f68C = z;
	o->f698 = z;
	o->f694 = z;
	o->f690 = z;
	o->f6A0 = 0;
	o->f69C = lbl_8042D0E8;
	o->f6A8 = 0;
	o->f638 = 0;
	o->f9E7 = 0;
	o->f9E9 = 0;
	o->f639 = 0;
	o->f63A = 0;
	o->f63C = 0;
	o->f640 = 0;
	o->f644 = 0;
	o->f648 = 0;
	o->f64C = 0;
	o->f650 = 0;
	o->f654 = 0;
	o->f658 = 0;
	o->f65C = 0;
	o->f660 = 0;
	o->f664 = 0;
	o->f668 = 0;
	o->f66C = z;
	o->f670 = 0;
	o->f672 = 0;
	o->f674 = z;
	o->f6A1 = 0;
	o->f6A2 = 0;
	o->f6A4 = z;
}
}
