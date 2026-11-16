extern "C" void copyVec3(void*, void*);
extern "C" int fn_16_2A730(char* self, void* src)
{
	copyVec3(self + 0x38, src);
	return 1;
}
