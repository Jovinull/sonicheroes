#include "MSL_C/file_io.h"
#include "types.h"

enum {
	__neutral,
	__writing,
	__reading,
	__rereading,
};

enum {
	__closed_file,
	__disk_file,
	__console_file,
	__unavailable_file,
};

enum {
	__must_exist,
	__create_if_necessary,
	__create_or_truncate,
};

enum {
	__read = 1,
	__write,
	__read_write,
	__append,
};

extern void __stdio_atexit(void);
extern void clearerr(FILE* file);
extern s32 fclose(FILE* file);
extern s32 fflush(FILE* file);
extern s32 fseek(FILE* file, s32 offset, s32 mode);
extern void fn_801BB540(void* buffer);
extern s32 __flush_all(void);
extern void __init_file(FILE* file, __file_modes modes, u8* buffer, u32 size);
extern FILE* __find_unopened_file(void);
extern s32 __open_file(const char* name, __file_modes modes, u32* handle);
extern s32 ftell(FILE* file);

static inline s32 close_file(FILE* file)
{
	s32 flush_result;
	s32 close_result;

	if (file == 0)
		return -1;

	if (file->mode.file_kind == __closed_file)
		return 0;

	flush_result         = fflush(file);
	close_result         = file->close_proc(file->handle);
	file->mode.file_kind = __closed_file;
	file->handle         = 0;

	if (file->state.free_buffer)
		fn_801BB540(file->buffer);

	return (flush_result || close_result) ? -1 : 0;
}

s32 __get_file_modes(const char* mode, __file_modes* modes)
{
	s32 mode_str;
	const s8* mode_ptr;
	u8 open_mode;
	s32 io_mode;

	modes->file_kind        = __disk_file;
	modes->file_orientation = 0;
	modes->binary_io        = 0;
	mode_ptr                = (const s8*)mode;
	mode_str                = *mode_ptr++;

	switch (mode_str) {
		case 'r':
			open_mode = __must_exist;
			break;
		case 'w':
			open_mode = __create_or_truncate;
			break;
		case 'a':
			open_mode = __create_if_necessary;
			break;
		default:
			return 0;
	}

	modes->open_mode = open_mode;

	switch (*mode_ptr++) {
		case 'b':
			modes->binary_io = 1;
			if (*mode_ptr == '+')
				mode_str = (mode_str << 8) | '+';
			break;
		case '+':
			mode_str = (mode_str << 8) | '+';
			if (*mode_ptr == 'b')
				modes->binary_io = 1;
			break;
	}

	switch (mode_str) {
		case 'r':
			io_mode = __read;
			break;
		case 'w':
			io_mode = __write;
			break;
		case 'a':
			io_mode = __write | __append;
			break;
		case 'r+':
			io_mode = __read_write;
			break;
		case 'w+':
			io_mode = __read_write;
			break;
		case 'a+':
			io_mode = __read_write | __append;
			break;
	}

	modes->io_mode = io_mode;
	return 1;
}

FILE* freopen(const char* name, const char* mode, FILE* file)
{
	__file_modes modes;

	__stdio_atexit();

	if (file == 0)
		return 0;

	close_file(file);
	clearerr(file);

	if (!__get_file_modes(mode, &modes))
		return 0;

	__init_file(file, modes, 0, 0x1000);

	if (__open_file(name, modes, &file->handle) != 0) {
		file->mode.file_kind = __closed_file;
		if (file->state.free_buffer)
			fn_801BB540(file->buffer);
		return 0;
	}

	if (modes.io_mode & __append)
		fseek(file, 0, 2);

	return file;
}

FILE* fopen(const char* name, const char* mode)
{
	return freopen(name, mode, __find_unopened_file());
}

s32 fflush(FILE* file)
{
	u32 pos;

	if (file == 0)
		return __flush_all();

	if (file->state.error != 0 || file->mode.file_kind == __closed_file)
		return -1;

	if (file->mode.io_mode == __read)
		return 0;

	if (file->state.io_state >= __rereading)
		file->state.io_state = __reading;

	if (file->state.io_state == __reading)
		file->buffer_length = 0;

	if (file->state.io_state != __writing) {
		file->state.io_state = __neutral;
		return 0;
	}

	if (file->mode.file_kind != __disk_file)
		pos = 0;
	else
		pos = ftell(file);

	if (__flush_buffer(file, 0) != 0) {
		file->state.error   = 1;
		file->buffer_length = 0;
		return -1;
	}

	file->state.io_state = __neutral;
	file->position       = pos;
	file->buffer_length  = 0;
	return 0;
}

s32 fclose(FILE* file)
{
	return close_file(file);
}
