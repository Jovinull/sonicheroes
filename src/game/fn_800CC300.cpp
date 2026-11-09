// Returns the string at 0x50 of the object lbl_8042B624 points to, or 0 when there is none or it is empty.

extern "C" {
extern char* lbl_8042B624;
unsigned strlen(const char*);

char* fn_800CC300()
{
	char* t = lbl_8042B624;
	if (t != 0) {
		if (strlen(t + 0x50) == 0) {
			return 0;
		}
		return t + 0x50;
	}
	return 0;
}
}
