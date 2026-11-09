// Calls fn_801A4B3C(a, entry) for each of the 8 entries of lbl_80304228 that is set.

extern "C" {
struct Node800BE274 {
	int f0;
	int f4;
};
extern Node800BE274* lbl_80304228[8];
void fn_801A4B3C(int, Node800BE274*);

void fn_800BE274(int a)
{
	unsigned char i = 0;
	for (; i < 8; i++) {
		if (lbl_80304228[i] != 0) {
			fn_801A4B3C(a, lbl_80304228[i]);
		}
	}
}
}
