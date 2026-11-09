// Stores the maximum decode sample count at +0x38 and forwards it to the decoder handle at +4.

extern "C" {
struct Obj_ADXSJD_SetMaxDecSmpl {
	unsigned char pad[4];
	int f4;
	int f8;
	unsigned char pad1[0x2c];
	int f38;
};
void ADXB_SetAhxDecSmpl(int);

void ADXSJD_SetMaxDecSmpl(Obj_ADXSJD_SetMaxDecSmpl* o, int a)
{
	o->f38 = a;
	ADXB_SetAhxDecSmpl(o->f4);
}
}
