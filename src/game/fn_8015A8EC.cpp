// Initializes the callback cell at the object + lbl_8042C91C offset (0, previous callback from 0x10), sets the halfword at 0x60 from the global record and installs fn_8015A7F0 as the callback at 0x10.

extern "C" {
extern int lbl_8042C91C;
struct Cell8015A8EC {
	int f0;
	void (*f4)();
};
struct Obj8015A8EC {
	unsigned char pad[0x10];
	void (*f10)();
	unsigned char pad1[0x60 - 0x14];
	short s60;
};
struct Rec8015A8EC {
	unsigned char pad[8];
	unsigned short f8;
};
extern Rec8015A8EC* lbl_8042C9A4;
void fn_8015A7F0();

void fn_8015A8EC(Obj8015A8EC* o)
{
	Cell8015A8EC* t = (Cell8015A8EC*)((unsigned char*)o + lbl_8042C91C);
	t->f0           = 0;
	o->s60          = lbl_8042C9A4->f8 - 1;
	t->f4           = o->f10;
	o->f10          = fn_8015A7F0;
}
}
