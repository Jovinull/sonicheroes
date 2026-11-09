// Stores the input stream-joint at +8 and forwards it to the decoder handle at +4.

extern "C" {
struct Obj_ADXSJD_SetInSj {
	unsigned char pad[4];
	int f4;
	int f8;
};
void ADXB_SetAhxInSj(int);

void ADXSJD_SetInSj(Obj_ADXSJD_SetInSj* o, int a)
{
	o->f8 = a;
	ADXB_SetAhxInSj(o->f4);
}
}
