// Returns the string at 0x50 of the object stored at word 4 of lbl_8042B624, or 0 when there is none or it is empty.

extern "C" {
struct Holder800CBB18 {
	int a;
	char* p;
};
extern Holder800CBB18 lbl_8042B624;
unsigned strlen(const char*);

char* fn_800CBB18()
{
	char* t = lbl_8042B624.p;
	if (t != 0) {
		if (strlen(t + 0x50) == 0) {
			return 0;
		}
		return t + 0x50;
	}
	return 0;
}
}
