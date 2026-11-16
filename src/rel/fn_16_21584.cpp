extern "C" void copyVec3(void* dst, void* src);

extern "C" void fn_16_21584(register char* obj)
{
	copyVec3(obj + 0xC0, obj + 0x104);
}
