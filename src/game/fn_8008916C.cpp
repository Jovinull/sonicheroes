// Clears the tracked-target flag when fn_80090040 reports done or the squared distance between the two stored points exceeds lbl_8042B298.
struct Obj8008916C {
	unsigned char pad0[0x5E0];
	int f5E0;
	float f5E4;
	float f5E8;
	float f5EC;
	float f5F0;
	float f5F4;
	float f5F8;
};

extern "C" {
extern float lbl_8042B298;
int fn_80090040();

void fn_8008916C(Obj8008916C* o)
{
	if (o->f5E0 != 0) {
		if (fn_80090040() != 0) {
			o->f5E0 = 0;
		} else {
			if ((o->f5F8 - o->f5EC) * (o->f5F8 - o->f5EC)
			        + ((o->f5F0 - o->f5E4) * (o->f5F0 - o->f5E4)
			            + (o->f5F4 - o->f5E8) * (o->f5F4 - o->f5E8))
			    > lbl_8042B298) {
				o->f5E0 = 0;
			}
		}
	}
}
}
