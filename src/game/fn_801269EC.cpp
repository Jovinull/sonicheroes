// Copies 2 bytes from arg1 to +0xB0 and 4 bytes from arg2 to +0xB2 of the buffer pointed to by arg0.

extern "C" {
void* memcpy(void*, const void*, unsigned);
struct Holder801269EC {
	unsigned char* p;
};

void fn_801269EC(Holder801269EC* o, void* a1, void* src)
{
	memcpy(o->p + 0xb0, a1, 2);
	memcpy(o->p + 0xb2, src, 4);
}
}
