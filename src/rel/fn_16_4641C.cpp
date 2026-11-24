typedef unsigned char u8;
extern "C" {
void* fn_80226468(void* geometry);
void fn_80226440(void* atomic, void* hierarchy);
void* fn_16_4641C(register void* atomic, void* data);
}

void* fn_16_4641C(register void* atomic, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomic + 0x18)) != 0)
		fn_80226440(atomic, data);
	return atomic;
}
