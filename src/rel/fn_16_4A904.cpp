extern "C" {
void copyVec3(void*, void*);
void fn_16_4A904(register char* self, void* p)
{
	if (*(int*)(self + 0x174) != 0) {
		copyVec3(self + 0x17C, p);
	}
}
}
