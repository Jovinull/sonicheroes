extern "C" {
void fn_16_18164(void* a, void* b);
struct S {
	char pad[0x68];
	char* arr;
};
void fn_16_17974(S* obj)
{
	int i;
	if (obj->arr != 0) {
		for (i = 0; i < 3; i++) {
			fn_16_18164(obj->arr + i * 0x34, obj);
		}
	}
}
}
