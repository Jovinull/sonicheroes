#include "types.h"

// Loads the language version of a file and hands it to fn_8012D080: formats the object's file
// name pattern (0x0) with the language suffix lbl_8028A2A0[language] (language byte 0x13 of the
// game state lbl_8042C180; an out-of-range value falls back to 1), reads the whole file
// (fn_800426E0) into a file descriptor (buffer at 0x8, size at 0xC), passes it to fn_8012D080 and
// frees the buffer (fn_800426B4). What the object and the file are is UNKNOWN.

struct GameState8012CB70 {
	u8 pad0[0x13];
	s8 language; // 0x13
};

struct File8012CB70 {
	s32 f0;
	s32 f4;
	void* data; // 0x8
	u32 size;   // 0xC
};

struct Obj8012CB70 {
	const char* format; // 0x0
};

extern "C" {
extern GameState8012CB70* lbl_8042C180;
extern const char* lbl_8028A2A0[8];
int sprintf(char* buffer, const char* format, ...);
void* fn_800426E0(const char* name, u32* size);
void fn_800426B4(void* address);
void fn_8012D080(Obj8012CB70* o, File8012CB70* file);

void fn_8012CB70(Obj8012CB70* o)
{
	char name[0x100]; // HYPOTHESIS: 0x100-0x10C give the retail frame
	File8012CB70 file;
	u32 size;

	if (o != NULL) {
		const char* format = o->format;
		s32 language       = lbl_8042C180->language;
		if (language < 0 || language >= 7) {
			language = 1;
		}
		sprintf(name, format, lbl_8028A2A0[language]);
		file.data = fn_800426E0(name, &size);
		file.size = size;
		fn_8012D080(o, &file);
		fn_800426B4(file.data);
	}
}
}
