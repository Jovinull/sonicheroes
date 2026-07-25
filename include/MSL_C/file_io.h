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
	u32 file_orientation : 2;
	u32 binary_io : 1;
} __file_modes;

typedef struct {
	u32 io_state : 3;
	u32 free_buffer : 1;
	u8 eof;
	u8 error;
} __file_state;

typedef void (*__idle_proc)(void);
typedef s32 (*__pos_proc)(u32 handle, u32* position, s32 mode, __idle_proc idle_proc);
typedef s32 (*__io_proc)(u32 handle, u8* buffer, u32* count, __idle_proc idle_proc);
typedef s32 (*__close_proc)(u32 handle);

typedef struct {
	u32 handle;
	__file_modes mode;
	__file_state state;
	u8 char_buffer;
	u8 char_buffer_overflow;
	u8 ungetc_buffer[2];
	u16 ungetc_wide_buffer[2];
	u8 position_padding[4];
	u32 position;
	u8* buffer;
	u32 buffer_size;
	u8* buffer_ptr;
	u32 buffer_length;
	u32 buffer_alignment;
	u32 saved_buffer_length;
	u32 buffer_position;
	__pos_proc position_proc;
	__io_proc read_proc;
	__io_proc write_proc;
	__close_proc close_proc;
	__idle_proc idle_proc;
	u8 padding[4];
} FILE;

extern FILE __files[4];

s32 fwide(FILE* file, s32 mode);
s32 __flush_buffer(FILE* file, u32* bytes_flushed);
s32 __load_buffer(FILE* file, u32* bytes_loaded, s32 alignment);
void __prep_buffer(FILE* file);

#ifdef __cplusplus
}
#endif

#endif
