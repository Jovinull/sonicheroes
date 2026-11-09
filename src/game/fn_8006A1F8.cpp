// Releases the pending resources of the object depending on its type, then runs the base cleanup.
struct Obj8006A1F8 {
	unsigned char pad0[0x761];
	signed char f761;
	unsigned char pad762[0x2EE];
	unsigned int fA50;
	unsigned char padA54[0x14];
	unsigned int fA68;
	unsigned char padA6C[0x118];
	unsigned int fB84;
};
struct G8042C1D0 {
	unsigned char pad[0x7258];
	int f7258;
};

extern "C" {
extern G8042C1D0* lbl_8042C1D0;
void fn_8003CB38(Obj8006A1F8* o);
void fn_8015BBF8(int a, unsigned int b);
unsigned int fn_8015BD78(unsigned int a);

void fn_8006A1F8(Obj8006A1F8* o)
{
	switch (o->f761) {
		case 7:
			if (o->fA50 != 0 && fn_8015BD78(o->fA50) != 0) {
				fn_8015BBF8(lbl_8042C1D0->f7258, o->fA50);
			}
			if (o->fB84 != 0 && fn_8015BD78(o->fB84) != 0) {
				fn_8015BBF8(lbl_8042C1D0->f7258, o->fB84);
			}
			break;
		case 10:
			if (o->fA68 != 0 && fn_8015BD78(o->fA68) != 0) {
				fn_8015BBF8(lbl_8042C1D0->f7258, o->fA68);
			}
			break;
	}
	fn_8003CB38(o);
}
}
