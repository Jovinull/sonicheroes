extern "C" {
void* fn_8013F484(void* frame);
void fn_8019EB10(void* frame, void* (*cb)(void*, void*), void* data);
void* fn_16_475C0(void* frame, void* data);

void* fn_16_47560(register char* obj)
{
	void* result = 0;
	result       = fn_8013F484(*(void**)(obj + 4));
	if (result == 0) {
		fn_8019EB10(*(void**)(obj + 4), fn_16_475C0, &result);
	}
	return result;
}
}
