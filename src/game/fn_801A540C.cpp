// Sets byte 0x18 of an object to 0xFF and its six floats at 0x00 to lbl_8042F750.
struct Obj801A540C {
	float f[6];
	unsigned char f18;
};

extern "C" {
extern float lbl_8042F750;

void fn_801A540C(Obj801A540C* o)
{
	o->f18  = 0xFF;
	o->f[0] = lbl_8042F750;
	o->f[1] = lbl_8042F750;
	o->f[2] = lbl_8042F750;
	o->f[3] = lbl_8042F750;
	o->f[4] = lbl_8042F750;
	o->f[5] = lbl_8042F750;
}
}
