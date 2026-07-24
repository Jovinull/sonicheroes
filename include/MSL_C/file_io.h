#ifndef MSL_C_FILE_IO_H
#define MSL_C_FILE_IO_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Only the prefix of FILE that has been carved so far is named. The offsets
// are argued from the stdio code at 0x801BB0D4: a word handle at 0x0, a
// halfword of packed mode bits at 0x4, and three state bytes at 0x8, where
// 0x8 is read and written all over the buffered io paths, 0x9 is what feof
// returns and 0xA is set on every error path.
//
// The total size is 0x50, argued from __files: the array is 0x140 bytes and
// vprintf reaches stdout as __files + 0x50, so it holds four entries. The
// tail is still unmapped and only exists to make that stride come out right.
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
	u8 unmapped[0x45];
} FILE;

extern FILE __files[4];

s32 fwide(FILE* file, s32 mode);

#ifdef __cplusplus
}
#endif

#endif
