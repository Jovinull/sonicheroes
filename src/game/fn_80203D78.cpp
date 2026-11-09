// Tears the object down: fn_802008DC on its two sub-blocks, resets the ids to -1, releases the handle at 0x30 and clears the second sub-block; returns arg0.

extern "C" {
struct Sub80203D78 {
	int f0;
	unsigned f4;
	int f8;
	int fc;
};
struct Obj80203D78 {
	int f0;
	unsigned char sub4[0x1c];
	unsigned char sub20[0x10];
	unsigned f30;
	int f34;
	int f38;
};
void fn_802008DC(void*, void*);
void fn_80205484(unsigned);
Sub80203D78* fn_80202210(Sub80203D78*);

int fn_80203D78(int a, Obj80203D78* o)
{
	fn_802008DC(o->sub4, o->sub20);
	o->f0  = 0;
	o->f34 = -1;
	o->f38 = -1;
	if (o->f30 != 0) {
		fn_80205484(o->f30);
	}
	fn_80202210((Sub80203D78*)o->sub20);
	o->f30 = 0;
	return a;
}
}
