struct RpClump;
struct RwRGBAReal;
struct Elem {
	RpClump* clump;
	char pad[0x58];
	RwRGBAReal* dummy;
};
struct Holder {
	char pad[0x2C];
	char* objs[0x200];
};
extern "C" {
void fn_80194294(int state, int* value);
void fn_80194234(int state, int value);
void fn_8014FF2C(RpClump* clump);
void objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(RpClump*, RwRGBAReal*);
}
extern "C" void fn_16_3F3D4(Holder* h)
{
	int src;
	int dst;
	int i;
	fn_80194294(0xA, &src);
	fn_80194294(0xB, &dst);
	fn_80194234(0xA, 3);
	fn_80194234(0xB, 2);
	for (i = 0; i < 0x200; i++) {
		if (h->objs[i] != 0) {
			char* o = h->objs[i];
			objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(
			    *(RpClump**)o, (RwRGBAReal*)(o + 0x5C));
			fn_8014FF2C(*(RpClump**)o);
		}
	}
	fn_80194234(0xA, src);
	fn_80194234(0xB, dst);
}
