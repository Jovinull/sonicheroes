extern "C" {
void copyVec3(void* out, void* in);
void fn_16_23EA8(char* a, void* b)
{
	copyVec3(a + 0xC0, b);
}
}
