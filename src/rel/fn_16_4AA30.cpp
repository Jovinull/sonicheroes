extern "C" {
void copyVec3(void*, void*);
void fn_16_4AC54(void*, int);
void fn_16_4ACF4(void*, int);
}

extern "C" void fn_16_4AA30(char* self, void* arg1, int arg2, int arg3)
{
	copyVec3(self + 0x17C, arg1);
	*(int*)(self + 0x188) = arg2;
	*(int*)(self + 0x18C) = arg3;
	fn_16_4AC54(self, arg2);
	fn_16_4ACF4(self, 1);
}
