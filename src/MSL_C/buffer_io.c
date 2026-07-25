#include "MSL_C/file_io.h"
#include "types.h"

enum {
	_IOFBF,
	_IOLBF,
	_IONBF,
};

enum {
	__neutral,
	__writing,
	__reading,
	__rereading,
};

enum {
	__no_io_error,
	__io_error,
	__io_EOF,
};

enum {
	__align_buffer,
	__dont_align_buffer,
};

extern void fn_801BB540(void*);
extern void* fn_801BB674(u32);
extern s32 fn_801BF9B8(FILE*);

static inline void prep_buffer(FILE* file)
{
	file->buffer_ptr    = file->buffer;
	file->buffer_length = file->buffer_size;
	file->buffer_length -= file->position & file->buffer_alignment;
	file->buffer_position = file->position;
}

s32 setvbuf(FILE* file, char* buffer, s32 mode, u32 size)
{
	s32 file_kind = file->mode.file_kind;

	if (mode == _IOFBF)
		fn_801BF9B8(file);

	if (file->state.io_state != __neutral || file_kind == 0)
		return -1;

	if (mode != _IOFBF && mode != _IOLBF && mode != _IONBF)
		return -1;

	if (file->buffer != 0 && file->state.free_buffer)
		fn_801BB540(file->buffer);

	file->mode.buffer_mode  = mode;
	file->state.free_buffer = 0;
	file->buffer            = &file->char_buffer_overflow;
	file->buffer_ptr        = &file->char_buffer_overflow;
	file->buffer_size       = 1;
	file->buffer_length     = 0;
	file->buffer_alignment  = 0;

	if (mode == _IOFBF || size < 1) {
		*file->buffer_ptr = 0;
		return 0;
	}

	if (buffer == 0) {
		buffer = fn_801BB674(size);
		if (buffer == 0)
			return -1;
		file->state.free_buffer = 1;
	}

	file->buffer           = (u8*)buffer;
	file->buffer_ptr       = file->buffer;
	file->buffer_size      = size;
	file->buffer_alignment = 0;
	return 0;
}

s32 __flush_buffer(FILE* file, u32* bytes_flushed)
{
	u32 buffer_length;
	s32 result;

	buffer_length = file->buffer_ptr - file->buffer;
	if (buffer_length != 0) {
		file->buffer_length = buffer_length;
		result
		    = file->write_proc(file->handle, file->buffer, &file->buffer_length, file->idle_proc);

		if (bytes_flushed != 0)
			*bytes_flushed = file->buffer_length;

		if (result != 0)
			return result;

		file->position += file->buffer_length;
	}

	prep_buffer(file);
	return __no_io_error;
}

s32 __load_buffer(FILE* file, u32* bytes_loaded, s32 alignment)
{
	s32 result;

	prep_buffer(file);
	if (alignment == __dont_align_buffer)
		file->buffer_length = file->buffer_size;

	result = file->read_proc(file->handle, file->buffer, &file->buffer_length, file->idle_proc);
	if (result == __io_EOF)
		file->buffer_length = 0;

	if (bytes_loaded != 0)
		*bytes_loaded = file->buffer_length;

	if (result != 0)
		return result;

	file->position += file->buffer_length;
	return __no_io_error;
}

void __prep_buffer(FILE* file)
{
	prep_buffer(file);
}
