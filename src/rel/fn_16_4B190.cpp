extern "C" {
void copyVec3(char* out, char* in);
char* fn_16_4B190(char* self, char* src)
{
	copyVec3(self + 0x94, src);
	return self + 0x94;
}
}
