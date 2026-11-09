// Search callback: when the name at 0x10 of the object equals the given name, remembers the object in lbl_8042C2E8 and returns 0; otherwise returns the object.

extern "C" {
int strcmp(const char*, const char*);
extern void* lbl_8042C2E8;

void* fn_8005FA44(unsigned char* o, const char* name)
{
	if (strcmp((char*)o + 0x10, name) == 0) {
		lbl_8042C2E8 = o;
		return 0;
	}
	return o;
}
}
