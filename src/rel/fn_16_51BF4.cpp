extern "C" {
void fn_8014FFBC(void* clump, void* callback, int* data);
void fn_16_51BEC();

int fn_16_51BF4(int a)
{
	int z;
	fn_8014FFBC((void*)a, (void*)fn_16_51BEC, &z);
	return z;
}
}
