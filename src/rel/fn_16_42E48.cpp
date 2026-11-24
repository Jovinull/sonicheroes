extern "C" {
void copyVec3(char*, void*);
void fn_16_900(char*, void*);
void fn_16_42E48(char* self, void* a, void* b)
{
	if (a != 0) {
		copyVec3(self + 0x58, a);
	}
	if (b != 0) {
		fn_16_900(self + 0x64, b);
	}
}
}
