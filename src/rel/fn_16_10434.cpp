typedef signed char s8;
typedef signed short s16;
extern "C" {
void copyVec3(void*, void*);
void fn_16_900(void*, void*);
void fn_16_10434(register char* self)
{
	s16* p;
	copyVec3(self + 0xC4, *(void**)(self + 0x28));
	fn_16_900(self + 0xD0, *(char**)(self + 0x28) + 0xC);
	p                   = *(s16**)(*(char**)(self + 0x28) + 0x2C);
	*(s8*)(self + 0xC0) = *p;
}
}
