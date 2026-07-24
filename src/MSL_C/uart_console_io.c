#include "types.h"

extern s32 InitializeUART(u32 baud_rate);
extern s32 WriteUARTN(u8* buffer, u32 count);
extern s32 __TRK_write_console(u32 handle, u8* buffer, u32* count, void* idle_proc);

s32 __close_console(void)
{
	return 0;
}

static inline s32 __init_uart_console(void)
{
	s32 err                = 0;
	static s32 initialized = 0;

	if (initialized == 0) {
		err = InitializeUART(57600);

		if (err == 0)
			initialized = 1;
	}

	return err;
}

s32 __write_console(u32 handle, u8* buffer, u32* count, void* idle_proc)
{
	if (__init_uart_console() != 0)
		return 1;

	if (WriteUARTN(buffer, *count) != 0) {
		*count = 0;
		return 1;
	}

	__TRK_write_console(handle, buffer, count, idle_proc);
	return 0;
}
