extern "C" {
void copyVec3(void*, void*);
void fn_16_42E04(char* self, register void* p)
{
	if (p != 0) {
		copyVec3(self + 0x70, p);
	}
}
}
