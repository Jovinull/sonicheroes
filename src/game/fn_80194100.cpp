// Reports whether a file can be opened for binary reading by opening and closing it with the
// engine file functions (HYPOTHESIS: the default RenderWare file-exists callback).
#include "game/rw_engine.h"

extern "C" {
// Open mode "rb" (.sdata string).
extern const char lbl_8042BDE0[3];

s32 fn_80194100(const char* name)
{
	void* file = lbl_8042C9A4->rwfopen(name, lbl_8042BDE0);
	s32 exists = (file != 0) ? 1 : 0;
	if (file != 0) {
		lbl_8042C9A4->rwfclose(file);
	}
	return exists;
}
}
