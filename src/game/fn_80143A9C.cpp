// Zeroes the 8 bytes at lbl_8042C9A4 + lbl_8042C848 and returns the object.

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042C848;
void* memset(void*, int, unsigned);

void* fn_80143A9C(void* o)
{
	memset((char*)lbl_8042C9A4 + lbl_8042C848, 0, 8);
	return o;
}
}
