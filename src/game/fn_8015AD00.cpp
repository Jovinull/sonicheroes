// Initializes the callback cell at the object + lbl_8042C924 offset (0, previous callback from 0x10) and installs fn_8015AA68 as the callback at 0x10.

extern "C" {
extern int lbl_8042C924;
struct Cell8015AD00 {
	int f0;
	void (*f4)();
};
struct Obj8015AD00 {
	unsigned char pad[0x10];
	void (*f10)();
};
void fn_8015AA68();

void fn_8015AD00(Obj8015AD00* o)
{
	Cell8015AD00* t = (Cell8015AD00*)((unsigned char*)o + lbl_8042C924);
	t->f0           = 0;
	t->f4           = o->f10;
	o->f10          = fn_8015AA68;
}
}
