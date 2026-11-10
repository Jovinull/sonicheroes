// Constructor: runs the base initialiser, installs the vtable at +0x18 and clears the object's state fields.
struct Obj80058ED0 {
	int f0;
	unsigned char pad4[0x14];
	void* f18;
	unsigned char pad1C[0x2];
	short f1E;
	unsigned char pad20[0xC];
	void* f2C;
	unsigned char pad30[0xA3C];
	int fA6C;
	int fA70;
	int fA74;
	int fA78;
	unsigned char padA7C[0xC];
	int fA88;
	int fA8C;
	int fA90;
	int fA94;
	int fA98;
	int fA9C;
	int fAA0;
	int fAA4;
	int fAA8;
	int fAAC;
	int fAB0;
	int fAB4;
	int fAB8;
	int fABC;
	int fAC0;
	int fAC4;
	unsigned char padAC8[0x4];
	float fACC;
};

extern "C" {
extern unsigned char lbl_802430FC[];
extern int lbl_8042B208;
extern float lbl_8042D430;
void fn_8005B4F0(Obj80058ED0* o);

Obj80058ED0* fn_80058ED0(Obj80058ED0* o)
{
	fn_8005B4F0(o);
	o->f18  = lbl_802430FC;
	o->f2C  = lbl_802430FC + 0x2C;
	o->fA6C = 0;
	o->fA70 = 0;
	o->fA74 = 0;
	o->fA78 = 0;
	o->f0   = lbl_8042B208;
	o->f1E  = 0xAE0;
	o->fA94 = 0;
	o->fAB8 = 0;
	o->fAC0 = 0;
	o->fAC4 = 0;
	o->fACC = lbl_8042D430;
	o->fA88 = 0;
	o->fA8C = 0;
	o->fA90 = 0;
	o->fA98 = 0;
	o->fA9C = 0;
	o->fAA0 = 0;
	o->fAA4 = 0;
	o->fAA8 = 0;
	o->fAAC = 0;
	o->fAB0 = 0;
	o->fAB4 = 0;
	o->fABC = 0;
	return o;
}
}
