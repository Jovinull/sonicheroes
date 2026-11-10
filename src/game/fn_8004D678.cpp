// Applies the selected preset row of lbl_802C216C: sets the draw mode, the object's float and three parameters.
struct Ent8004D678 {
	float f0;
	int f4;
	int f8;
	int fC;
};
struct Obj28_8004D678 {
	unsigned char pad0[0x88];
	float f88;
};
struct Own8004D678 {
	unsigned char pad0[0x28];
	Obj28_8004D678* f28;
};

extern "C" {
extern Ent8004D678 lbl_802C216C[];
extern int lbl_8042C218;
void fn_80194234(int id, int v);

void fn_8004D678(Own8004D678* o)
{
	Ent8004D678* e = &lbl_802C216C[lbl_8042C218];
	fn_80194234(0xE, 1);
	o->f28->f88 = e->f0;
	fn_80194234(0x10, e->f4);
	fn_80194234(0xF, e->f8);
	fn_80194234(0x11, (int)&e->fC);
}
}
