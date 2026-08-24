#include "MSL_C/file_io.h"

enum {
	__closed_file,
};

enum {
	__unoriented,
	__char_oriented,
	__wide_oriented,
};

s32 fwide(FILE* file, s32 mode)
{
	s32 orientation;
	s32 result;

	if (file == 0 || file->mode.file_kind == __closed_file)
		return 0;

	orientation = file->mode.file_orientation;
	switch (orientation) {
		case __unoriented:
			if (mode > 0)
				file->mode.file_orientation = __wide_oriented;
			else if (mode < 0)
				file->mode.file_orientation = __char_oriented;
			result = mode;
			break;
		case __wide_oriented:
			result = 1;
			break;
		case __char_oriented:
			result = -1;
			break;
	}

	return result;
}
