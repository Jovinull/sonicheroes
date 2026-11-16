extern "C" {
void copyVec3(void* dst, void* src);
void fn_16_4AF74(void* p);
void fn_16_4B164(void* p, void* src);
}

extern "C" void fn_16_4B0C8(register char* self, void* a, void* b, void* c)
{
	*(int*)(self + 0xC4) = 1;
	if (a != 0) {
		copyVec3(self + 0x40, a);
	}
	if (b != 0) {
		copyVec3(self + 0x4C, b);
	}
	if (c != 0) {
		fn_16_4B164(self + 0x28, c);
		return;
	}
	fn_16_4AF74(self + 0x28);
}
