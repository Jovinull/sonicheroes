// Stores the effect parameters and applies the FX texture to the matching atomic.
extern "C" {
extern unsigned int lbl_803E7668[];
extern char lbl_8042B824[4];
extern int lbl_8042C678;
extern unsigned int lbl_8042C67C;
extern unsigned int lbl_8042C680;
extern unsigned int lbl_8042C684;
void AtomicSetCustomFXTexture__FP8RpAtomicPv(int a, unsigned int* b);
void fn_801491A8(int a);
int objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(unsigned int a, int b, char* c);
unsigned int objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    unsigned int a, int b, char* c);

void fn_80115070(int a, unsigned int b, unsigned int c)
{
	lbl_8042C678 = a;
	lbl_8042C67C = b;
	lbl_8042C680 = c;
	if (b != 0) {
		unsigned int m = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
		    b, 0, lbl_8042B824);
		lbl_8042C684 = m;
		if (lbl_8042C680 != 0 && m != 0) {
			int at = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
			    lbl_8042C67C, 0, lbl_8042B824);
			lbl_803E7668[0] = lbl_8042C680;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(at, lbl_803E7668);
			fn_801491A8(at);
		}
	}
}
}
