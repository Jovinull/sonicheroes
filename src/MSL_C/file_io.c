#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// Only the prefix of FILE that this translation unit touches is mapped. The
// offsets are argued from the stdio code at 0x801BB0D4: a word handle at 0x0,
// a halfword of packed mode bits at 0x4, and three state bytes at 0x8, where
// 0x8 is read and written all over the buffered io paths, 0x9 is what feof
// returns and 0xA is set on every error path. The rest of the struct is not
// carved yet, so nothing here may depend on its size.
typedef struct {
	u32 open_mode : 2;
	u32 io_mode : 3;
	u32 buffer_mode : 2;
	u32 file_kind : 3;
	u32 binary_io : 1;
} __file_modes;

typedef struct {
	u8 io_state;
	u8 eof;
	u8 error;
} __file_state;

typedef struct {
	u32 handle;
	__file_modes mode;
	__file_state state;
} FILE;

// Registered so that exit() flushes and closes every open stream. The hook
// itself lives in the small data area, which is why the store is sda21.
extern void __close_all(void);
extern void (*__stdio_exit)(void);

void __stdio_atexit(void)
{
	__stdio_exit = __close_all;
}

int feof(FILE* file)
{
	return file->state.eof;
}

void clearerr(FILE* file)
{
	file->state.eof   = 0;
	file->state.error = 0;
}
