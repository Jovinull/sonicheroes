// For each of the 8 entries of lbl_80304228 that is set and has a word at 4, runs fn_801A4C84 on that word and then fn_801A4B8C on the entry.

extern "C" {
struct Node800BE1F4 {
	int f0;
	unsigned f4;
};
extern Node800BE1F4* lbl_80304228[8];
void fn_801A4C84(unsigned);
void fn_801A4B8C(Node800BE1F4*);

void fn_800BE1F4()
{
	unsigned char i = 0;
	for (; i < 8; i++) {
		Node800BE1F4* t = lbl_80304228[i];
		if (t != 0 && t->f4 != 0) {
			fn_801A4C84(t->f4);
			fn_801A4B8C(lbl_80304228[i]);
		}
	}
}
}
