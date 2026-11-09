// Stores the AHX decode sample count at +0xB4 and the derived frame count (samples / 96) at +0xB8.

extern "C" {
struct Obj_ADXB_SetAhxDecSmpl {
	unsigned char pad[0xb4];
	int fb4;
	unsigned fb8;
};

void ADXB_SetAhxDecSmpl(Obj_ADXB_SetAhxDecSmpl* o, int a)
{
	o->fb4 = a;
	o->fb8 = a / 96;
}
}
