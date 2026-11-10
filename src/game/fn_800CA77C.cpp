// Copies a name (at most 0x20 characters) into slot idx (0..8) of the current stream object's table and announces it through fn_80116E3C, with a second announcement when the name matches lbl_8025501C.
struct Holder800CA77C {
	unsigned char pad0[0x4C];
	char* f4C;
};

extern "C" {
extern signed char lbl_8042C470;
extern Holder800CA77C* lbl_8042B624;
extern char lbl_803E774C[];
extern char lbl_8025501C[];
extern char lbl_8025502C[];
unsigned int strlen(const char* s);
char* strcpy(char* d, const char* s);
int strcmp(const char* a, const char* b);
int fn_80116D2C(char* p);
void fn_80116E3C(int h, char* s);

void fn_800CA77C(char* name, signed char idx)
{
	char* table;
	if (lbl_8042C470 == 2 && lbl_8042B624 != 0) {
		table = lbl_8042B624->f4C;
		if (table != 0 && idx >= 0 && idx <= 8 && strlen(name) <= 0x20) {
			strcpy(table + (idx << 5) + 0xC, name);
			fn_80116E3C(fn_80116D2C(lbl_803E774C), name);
			if (strcmp(name, lbl_8025501C) == 0) {
				fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_8025502C);
			}
		}
	}
}
}
