// Waits for the GX draw sync token of the object, advancing the global token first when it matches.
struct Obj8015C004 {
	unsigned char pad0[0x18];
	unsigned short f18;
};

extern "C" {
extern unsigned short lbl_8042BE88;
void GXSetDrawSync(unsigned short v);
int fn_801B2894(unsigned short v);
void GXInvalidateVtxCache();

void fn_8015C004(Obj8015C004* o)
{
	if (o->f18 == *(volatile unsigned short*)&lbl_8042BE88) {
		GXSetDrawSync(lbl_8042BE88);
		lbl_8042BE88 = (lbl_8042BE88 + 1) % 57344;
	}
	do {
	} while (fn_801B2894(o->f18) == 0);
	GXInvalidateVtxCache();
}
}
