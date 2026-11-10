// Eases the two speed floats towards their targets, snapping state 0/1 to 2; returns 1 once the main speed has reached the floor.
struct Obj8011927C {
	unsigned char padB1[0xB1];
	unsigned char fB1;
	unsigned char padB2[0x29];
	float fDC;
	float fE0;
	float fE4;
	float fE8;
};

float AdjustFloat(float a, float b, float c);

extern "C" {
extern float lbl_8042EA5C;
extern float lbl_8042EA70;
extern float lbl_8042EA88;
extern float lbl_8042EA8C;
extern float lbl_8042EA90;
extern float lbl_8042EA94;

int fn_8011927C(Obj8011927C* o)
{
	unsigned char t = o->fB1;
	if ((signed char)t == 1 || (signed char)t == 0) {
		o->fB1 = 2;
	}
	o->fE8 = AdjustFloat(o->fE8, lbl_8042EA5C, lbl_8042EA70);
	o->fE0 = AdjustFloat(o->fE0, lbl_8042EA5C, lbl_8042EA88);
	if (o->fE0 <= lbl_8042EA5C) {
		o->fDC = lbl_8042EA5C;
		return 1;
	}
	if (o->fE0 <= lbl_8042EA8C * o->fE4) {
		o->fDC = AdjustFloat(o->fDC, lbl_8042EA90, lbl_8042EA94);
	}
	return 0;
}
}
