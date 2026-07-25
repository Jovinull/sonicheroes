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

enum {
	__no_io_error,
	__io_error,
	__io_EOF,
};

extern void __stdio_atexit(void);
extern s32 fseek(FILE* file, s32 offset, s32 mode);

s32 fputc(s32 character, FILE* file);
s32 fgetc(FILE* file);

s32 fputs(const char* string, FILE* file)
{
	s8 character;
	s32 result = 0;

	while ((character = *string++) != 0) {
		if ((fwide(file, -1) >= 0                ? -1
		            : file->buffer_length-- != 0 ? * file->buffer_ptr++ = character
		                                         : fputc(character, file))
		    == -1) {
			result = -1;
			break;
		}
	}

	return result;
}

s32 fputc(s32 character, FILE* file)
{
	s32 file_kind = file->mode.file_kind;

	file->buffer_length = 0;
	if (file->state.error || file_kind == __closed_file)
		return -1;

	if (file_kind == __console_file)
		__stdio_atexit();

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
		return -1;
	}

	if (file->mode.buffer_mode == 2
	    || file->buffer_size == (u32)(file->buffer_ptr - file->buffer)) {
		if (__flush_buffer(file, 0) != 0) {
			file->state.error   = 1;
			file->buffer_length = 0;
			return -1;
		}
	}

	file->buffer_length--;
	*file->buffer_ptr++ = character;

	if (file->mode.buffer_mode != 2) {
		if (file->mode.buffer_mode == 0 || character == '\n') {
			if (__flush_buffer(file, 0) != 0) {
				file->state.error   = 1;
				file->buffer_length = 0;
				return -1;
			}
		}

		file->buffer_length = 0;
	}

	return (u8)character;
}

char* fgets(char* string, s32 count, register FILE* file)
{
	char* current;
	s32 character;

	current = string;
	count -= 1;

	if (count < 0)
		return 0;

	if (count != 0) {
		do {
			if (fwide(file, -1) >= 0)
				character = -1;
			else if (file->buffer_length-- != 0) {
				character = *file->buffer_ptr++;
			} else {
				character = fgetc(file);
			}

			if (character == -1) {
				if (!file->state.eof || current == string)
					return 0;
				break;
			}

			*current++ = character;
			if (character == '\n')
				break;
		} while (--count != 0);
	}

	*current = 0;
	return string;
}

s32 fgetc(FILE* file)
{
	s32 io_state;
	s32 result;

	file->buffer_length = 0;
	if (file->state.error || file->mode.file_kind == __closed_file)
		return -1;

	io_state = file->state.io_state;
	if (io_state == __writing || !(file->mode.io_mode & 1)) {
		file->state.error   = 1;
		file->buffer_length = 0;
		return -1;
	}

	if (io_state >= __rereading) {
		file->state.io_state = io_state - 1;
		if (io_state == __rereading)
			file->buffer_length = file->saved_buffer_length;
		return (&file->char_buffer)[io_state];
	}

	file->state.io_state = __reading;
	result               = __load_buffer(file, 0, 0);
	if (result != __no_io_error || file->buffer_length == 0) {
		if (result == __io_error) {
			file->state.error   = 1;
			file->buffer_length = 0;
		} else {
			file->state.io_state = __neutral;
			file->state.eof      = 1;
			file->buffer_length  = 0;
		}
		return -1;
	}

	file->buffer_length--;
	return *file->buffer_ptr++;
}
