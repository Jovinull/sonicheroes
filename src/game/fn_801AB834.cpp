// Finds and reads a ".dds" texture file (HYPOTHESIS): for an absolute name, or with no image search
// path (fn_8019FE1C), the file is the name itself plus ".dds"; otherwise each ';'-separated search
// path entry is tried as directory + name + ".dds" until fn_801AB144 reads one. Returns what
// fn_801AB144 returns, or null when no candidate can be read. Names are inferred from this
// function only.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

extern "C" {
extern char lbl_8042BE68[5]; // ".dds"
// HYPOTHESIS: RwImageGetPath, the absolute-path test and the DDS file reader (base name, path).
const char* fn_8019FE1C(void);
s32 fn_80199E40(const char* path);
void* fn_801AB144(const char* name, const char* fileName);

void* fn_801AB834(const char* name)
{
	char fileName[256];
	const char* path = fn_8019FE1C();

	if (fn_80199E40(name) == 1 || path == 0 || *path == 0) {
		const char* base = name + lbl_8042C9A4->rwstrlen(name);
		while (*--base != '\\') {
		}
		lbl_8042C9A4->rwstrcpy(fileName, name);
		lbl_8042C9A4->rwstrcat(fileName, lbl_8042BE68);
		return fn_801AB144(base + 1, fileName);
	}

	while (path != 0 && *path != 0) {
		const char* next;
		u32 length;

		lbl_8042C9A4->rwstrchr(path, ';');
		next = lbl_8042C9A4->rwstrchr(path, ';');
		if (next != 0) {
			length = next - path;
			next++;
		} else {
			length = lbl_8042C9A4->rwstrlen(path);
		}
		memcpy(fileName, path, length);
		lbl_8042C9A4->rwstrcpy(fileName + length, name);
		lbl_8042C9A4->rwstrcat(fileName, lbl_8042BE68);
		{
			void* result = fn_801AB144(name, fileName);
			if (result != 0) {
				return result;
			}
		}
		path = next;
	}
	return 0;
}
}
