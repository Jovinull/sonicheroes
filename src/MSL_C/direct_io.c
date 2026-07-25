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
	__unavailable_file,
	__console_file,
	__disk_file,
};

extern void __stdio_atexit(void);
extern void* memcpy(void* dst, const void* src, u32 count);
extern void* __memrchr(const void* buffer, s32 value, u32 count);
extern s32 fseek(FILE* file, s32 offset, s32 mode);

u32 __fwrite(const void* buffer, u32 memb_size, u32 num_memb, FILE* file)
{
	u8* cur_ptr;
	u32 num_bytes;
	u32 rem_bytes;
	u32 bytes_written;
	s32 result;
	s32 buffered;

	if (fwide(file, 0) == 0)
		fwide(file, -1);

	rem_bytes = memb_size * num_memb;

	if (rem_bytes == 0 || file->state.error || file->mode.file_kind == __closed_file)
		return 0;

	if (file->mode.file_kind == __console_file)
		__stdio_atexit();

	buffered = !file->mode.binary_io || file->mode.buffer_mode == 2 || file->mode.buffer_mode == 1;

	if (file->state.io_state == __neutral && (file->mode.io_mode & 2)) {
		if (file->mode.io_mode & 4) {
			if (fseek(file, 0, 2) != 0)
				return 0;
		}
		file->state.io_state = __writing;
		__prep_buffer(file);
	}

	if (file->state.io_state != __writing) {
		file->state.error   = 1;
		file->buffer_length = 0;
		return 0;
	}

	cur_ptr       = (u8*)buffer;
	bytes_written = 0;

	if (rem_bytes != 0 && (file->buffer_ptr != file->buffer || buffered)) {
		file->buffer_length = file->buffer_size - (file->buffer_ptr - file->buffer);

		do {
			u8* newline = 0;

			num_bytes = file->buffer_length;
			if (num_bytes > rem_bytes)
				num_bytes = rem_bytes;

			if (file->mode.buffer_mode == 1 && num_bytes != 0) {
				newline = __memrchr(cur_ptr, '\n', num_bytes);
				if (newline != 0)
					num_bytes = newline + 1 - cur_ptr;
			}

			if (num_bytes != 0) {
				memcpy(file->buffer_ptr, cur_ptr, num_bytes);
				cur_ptr += num_bytes;
				bytes_written += num_bytes;
				rem_bytes -= num_bytes;
				file->buffer_ptr += num_bytes;
				file->buffer_length -= num_bytes;
			}

			if (file->buffer_length == 0 || newline != 0 || file->mode.buffer_mode == 0) {
				result = __flush_buffer(file, 0);
				if (result != 0) {
					file->state.error   = 1;
					file->buffer_length = 0;
					rem_bytes           = 0;
					break;
				}
			}
		} while (rem_bytes != 0 && buffered);
	}

	if (rem_bytes != 0 && !buffered) {
		u8* saved_buffer = file->buffer;
		u32 saved_size   = file->buffer_size;

		file->buffer      = cur_ptr;
		file->buffer_size = rem_bytes;
		file->buffer_ptr  = cur_ptr + rem_bytes;

		if (__flush_buffer(file, &num_bytes) != 0) {
			file->state.error   = 1;
			file->buffer_length = 0;
		}

		bytes_written += num_bytes;
		file->buffer      = saved_buffer;
		file->buffer_size = saved_size;
		__prep_buffer(file);
		file->buffer_length = 0;
	}

	if (file->mode.buffer_mode != 2)
		file->buffer_length = 0;

	return (bytes_written + memb_size - 1) / memb_size;
}

u32 fwrite(const void* buffer, u32 memb_size, u32 num_memb, FILE* file)
{
	return __fwrite(buffer, memb_size, num_memb, file);
}
