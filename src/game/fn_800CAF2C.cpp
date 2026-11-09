// In mode 1, clears the 0x20-byte name field at 0x70 of both objects in lbl_8042B624 and copies the two given names there.

extern "C" {
struct Pair800CAF2C {
	unsigned char* a;
	unsigned char* b;
};
extern Pair800CAF2C lbl_8042B624;
extern unsigned char lbl_8042C470;
void* memset(void*, int, unsigned);
char* strcpy(char*, const char*);

void fn_800CAF2C(char* x, char* y)
{
	unsigned char* t;
	if ((signed char)lbl_8042C470 == 1) {
		t = lbl_8042B624.a;
		if (t != 0) {
			memset(t + 0x70, 0, 0x20);
			strcpy((char*)t + 0x70, x);
		}
		t = lbl_8042B624.b;
		if (t != 0) {
			memset(t + 0x70, 0, 0x20);
			strcpy((char*)t + 0x70, y);
		}
	}
}
}
