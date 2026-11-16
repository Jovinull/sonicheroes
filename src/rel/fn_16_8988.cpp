extern "C" {
extern void* lbl_8042C180;
int fn_16_F20(void* game, int flag);
void markSampleForDeletion(void* object);
void fn_16_9A34(void* object);
void fn_16_8988(void* object);
}

void fn_16_8988(void* object)
{
	if (fn_16_F20(lbl_8042C180, 0x22)) {
		markSampleForDeletion(object);
	} else {
		fn_16_9A34(object);
	}
}
