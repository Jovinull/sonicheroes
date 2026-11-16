typedef int s32;

extern "C" {
void fn_16_4D91C(void* item, s32 arg);

struct Lst {
	s32 count;
	void** items;
};

void fn_16_4DE08(Lst* self, s32 arg1)
{
	s32 i;

	for (i = 0; i < self->count; i++) {
		fn_16_4D91C(self->items[i], arg1);
	}
}
}
