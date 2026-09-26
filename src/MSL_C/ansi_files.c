#include "types.h"

// MSL ansi_files.c, 0x801BC864 to 0x801BCB64: the standard streams and the
// open-file list. It owns __files (.data 0x802913D8), the three 0x100 byte
// console buffers (.bss 0x803EDDB0, in reverse declaration order) and five
// functions, held in reverse source order (-inline deferred).
// Reference: zeldaret/tww src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/
// ansi_files.c for __files, __close_all and __flush_all; __init_file,
// __find_unopened_file and __flush_line_buffered_output_files were written
// from the original instructions. Built with GC/1.3 like the rest of MSL_C.
//
// The FILE layout here is the full Metrowerks one. include/MSL_C/file_io.h
// names the same 0x50 bytes more coarsely for the stdio units carved earlier.

typedef unsigned long size_t;
typedef unsigned long __file_handle;
typedef unsigned short wchar_t;

enum __file_kinds { __closed_file, __disk_file, __console_file, __unavailable_file };

enum __io_states { __neutral, __writing, __reading, __rereading };

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

typedef struct {
	unsigned int open_mode : 2;
	unsigned int io_mode : 3;
	unsigned int buffer_mode : 2;
	unsigned int file_kind : 3;
	unsigned int file_orientation : 2;
	unsigned int binary_io : 1;
} __file_modes;

typedef struct {
	unsigned int io_state : 3;
	unsigned int free_buffer : 1;
	unsigned char eof;
	unsigned char error;
} __file_state;

typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(
    __file_handle file, unsigned long* position, int mode, __idle_proc idle_proc);
typedef int (*__io_proc)(
    __file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
typedef int (*__close_proc)(__file_handle file);

typedef struct _FILE {
	__file_handle handle;                   // 0x00
	__file_modes mode;                      // 0x04
	__file_state state;                     // 0x08
	unsigned char is_dynamically_allocated; // 0x0C
	char char_buffer;                       // 0x0D
	char char_buffer_overflow;              // 0x0E
	char ungetc_buffer[2];                  // 0x0F
	wchar_t ungetc_wide_buffer[2];          // 0x12
	unsigned long position;                 // 0x18
	unsigned char* buffer;                  // 0x1C
	unsigned long buffer_size;              // 0x20
	unsigned char* buffer_ptr;              // 0x24
	unsigned long buffer_length;            // 0x28
	unsigned long buffer_alignment;         // 0x2C
	unsigned long saved_buffer_length;      // 0x30
	unsigned long buffer_position;          // 0x34
	__pos_proc position_proc;               // 0x38
	__io_proc read_proc;                    // 0x3C
	__io_proc write_proc;                   // 0x40
	__close_proc close_proc;                // 0x44
	__idle_proc idle_proc;                  // 0x48
	struct _FILE* next_file_struct;         // 0x4C
} FILE;

int __read_console(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __write_console(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __close_console(__file_handle file);

int __position_file(__file_handle file, unsigned long* position, int mode, __idle_proc idle_proc);
int __read_file(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __write_file(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __close_file(__file_handle file);

int fclose(FILE* file);
int fflush(FILE* file);
int setvbuf(FILE* file, char* buff, int mode, size_t size);
void* malloc(size_t size);
void free(void* ptr);
void* memset(void* dst, int c, size_t n);

static unsigned char stdin_buff[0x100];
static unsigned char stdout_buff[0x100];
static unsigned char stderr_buff[0x100];

// clang-format off
FILE __files[4] = {
	{ 0, { 0, 1, 1, __console_file, 0 }, { __neutral, 0, 0, 0 }, 0, 0, 0, { 0, 0 }, { 0, 0 }, 0,
	  stdin_buff, sizeof(stdin_buff), stdin_buff, 0, 0, 0, 0,
	  NULL, __read_console, __write_console, __close_console, NULL, &__files[1] },
	{ 1, { 0, 2, 1, __console_file, 0 }, { __neutral, 0, 0, 0 }, 0, 0, 0, { 0, 0 }, { 0, 0 }, 0,
	  stdout_buff, sizeof(stdout_buff), stdout_buff, 0, 0, 0, 0,
	  NULL, __read_console, __write_console, __close_console, NULL, &__files[2] },
	{ 2, { 0, 2, 0, __console_file, 0 }, { __neutral, 0, 0, 0 }, 0, 0, 0, { 0, 0 }, { 0, 0 }, 0,
	  stderr_buff, sizeof(stderr_buff), stderr_buff, 0, 0, 0, 0,
	  NULL, __read_console, __write_console, __close_console, NULL, &__files[3] },
};
// clang-format on

FILE* __find_unopened_file(void)
{
	FILE* p = __files[2].next_file_struct;
	FILE* plast;

	while (p != NULL) {
		if (p->mode.file_kind == __closed_file)
			return p;

		plast = p;
		p     = p->next_file_struct;
	}

	if ((p = (FILE*)malloc(sizeof(FILE))) != NULL) {
		memset(p, 0, sizeof(FILE));
		p->is_dynamically_allocated = 1;
		plast->next_file_struct     = p;
		return p;
	}

	return NULL;
}

void __init_file(FILE* file, __file_modes mode, char* buff, size_t size)
{
	file->handle            = 0;
	file->mode              = mode;
	file->state.io_state    = __neutral;
	file->state.free_buffer = 0;
	file->state.eof         = 0;
	file->state.error       = 0;
	file->position          = 0;

	if (size)
		setvbuf(file, buff, _IOFBF, size);
	else
		setvbuf(file, NULL, _IONBF, 0);

	file->buffer_ptr    = file->buffer;
	file->buffer_length = 0;

	if (file->mode.file_kind == __disk_file) {
		file->position_proc = __position_file;
		file->read_proc     = __read_file;
		file->write_proc    = __write_file;
		file->close_proc    = __close_file;
	}

	file->idle_proc = NULL;
}

void __close_all(void)
{
	FILE* file = &__files[0];
	FILE* last_file;

	while (file != NULL) {
		if (file->mode.file_kind != __closed_file) {
			fclose(file);
		}

		last_file = file;
		file      = file->next_file_struct;

		if (last_file->is_dynamically_allocated) {
			free(last_file);
		} else {
			last_file->mode.file_kind = __unavailable_file;
			if (file != NULL && file->is_dynamically_allocated) {
				last_file->next_file_struct = NULL;
			}
		}
	}
}

unsigned int __flush_all(void)
{
	unsigned int ret = 0;
	FILE* file       = &__files[0];

	while (file) {
		if (file->mode.file_kind != __closed_file && fflush(file)) {
			ret = -1;
		}
		file = file->next_file_struct;
	}

	return ret;
}

int __flush_line_buffered_output_files(void)
{
	int ret    = 0;
	FILE* file = &__files[0];

	while (file) {
		if (file->mode.file_kind != __closed_file && (file->mode.buffer_mode & _IOLBF)
		    && file->state.io_state == __writing) {
			if (fflush(file))
				ret = -1;
		}
		file = file->next_file_struct;
	}

	return ret;
}
