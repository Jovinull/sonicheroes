extern "C" {
void copyVec3(void*, void*);
void fn_16_900(void*, void*);
void fn_16_1B06C(register char* self)
{
	char* q = *(char**)(*(char**)(self + 0x28) + 0x2C);
	copyVec3(self + 0xC8, *(char**)(self + 0x28));
	fn_16_900(self + 0xD4, *(char**)(self + 0x28) + 0xC);
	*(unsigned char*)(self + 0xBC) = *(unsigned char*)q;
}
}
