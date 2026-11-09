// Loads the texture dictionary lbl_80288BA4 into lbl_8042C620 unless it is already loaded.

extern "C" {
extern void* lbl_8042C620;
extern char lbl_80288BA4[];
void* texLoadTexDictionaryFile__FPc(char*);

void fn_80112F3C()
{
	if (lbl_8042C620 == 0) {
		lbl_8042C620 = texLoadTexDictionaryFile__FPc(lbl_80288BA4);
	}
}
}
