extern "C" {
void RpAtomicMCCSetMaterialPointer(void*, void*);
struct O {
	char pad[0xF0];
	void* a[2];
};
void fn_16_34324(register O* self, void* mat)
{
	int i;
	void* m = mat;
	for (i = 0; i < 2; i++) {
		RpAtomicMCCSetMaterialPointer(self->a[i], m);
	}
}
}
