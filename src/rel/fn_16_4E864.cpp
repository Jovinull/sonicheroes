extern "C" {
void fn_8011B7CC(void* anim);

void fn_16_4E864(void** arg0)
{
	if (*arg0 != 0) {
		fn_8011B7CC(*arg0);
		*arg0 = 0;
	}
}
}
