#include "MSL_C/file_io.h"
#include "types.h"

enum {
	SEEK_SET,
	SEEK_CUR,
	SEEK_END,
};

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
	__read = 1,
	__write,
	__read_write,
	__append,
};

extern s32 errno;
extern s32 _fseek(FILE* file, s32 offset, s32 whence);

static inline s32 tell_file(FILE* file)
{
	s32 chars_in_undo_buffer = 0;
	s32 position;
	u8 file_kind = file->mode.file_kind;

	if (!((file_kind == __disk_file) || (file_kind == __console_file)) || file->state.error) {
		errno = 0x28;
		return -1;
	}

	if (file->state.io_state == __neutral)
		return file->position;

	position = file->buffer_position + (file->buffer_ptr - file->buffer);

	if (file->state.io_state >= __rereading) {
		chars_in_undo_buffer = file->state.io_state - __rereading + 1;
		position -= chars_in_undo_buffer;
	}

	return position;
}

s32 fseek(FILE* file, s32 offset, s32 whence)
{
	return _fseek(file, offset, whence);
}

s32 _fseek(FILE* file, s32 offset, s32 whence)
{
	__pos_proc position_proc;
	u8 file_kind = file->mode.file_kind;

	if (file_kind != __disk_file || file->state.error != 0) {
		errno = 0x28;
		return -1;
	}

	if (file->state.io_state == __writing) {
		if (__flush_buffer(file, 0) != 0) {
			file->state.error   = 1;
			file->buffer_length = 0;
			errno               = 0x28;
			return -1;
		}
	}

	if (whence == SEEK_CUR) {
		whence = SEEK_SET;
		offset += tell_file(file);
	}

	if (whence != SEEK_END && file->mode.io_mode != __read_write
	    && (file->state.io_state == __reading || file->state.io_state == __rereading)) {
		if (offset >= file->position || offset < file->buffer_position) {
			file->state.io_state = __neutral;
		} else {
			file->buffer_ptr     = file->buffer + (offset - file->buffer_position);
			file->buffer_length  = file->position - offset;
			file->state.io_state = __reading;
		}
	} else {
		file->state.io_state = __neutral;
	}

	if (file->state.io_state == __neutral) {
		position_proc = file->position_proc;
		if (position_proc != 0
		    && position_proc(file->handle, (u32*)&offset, whence, file->idle_proc) != 0) {
			file->state.error   = 1;
			file->buffer_length = 0;
			errno               = 0x28;
			return -1;
		}

		file->state.eof     = 0;
		file->position      = offset;
		file->buffer_length = 0;
	}

	return 0;
}

s32 ftell(FILE* file)
{
	return tell_file(file);
}
