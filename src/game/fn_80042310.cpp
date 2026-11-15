#include "game/rw_engine.h"

// Loads a REL module (HYPOTHESIS: the stage/object module loader; the first argument, perhaps the
// owning manager, is unused): the file name is `name` plus
// lbl_8042AF24 and lbl_8042AF28 (HYPOTHESIS: "." and "rel"), its length (as fn_80042554) sizes a
// 32-byte rounded RwMalloc buffer the file is read into (as fn_800425E8). The module is linked
// (OSLink) with its own bss block, its prolog runs (it registers its hook with fn_800421B4 in
// lbl_8042C1C8), and a 0x1C-byte record (the hook, `name`, the header, the file and bss buffers)
// is pushed on the hook list lbl_8042C1C4 (see fn_800422C4). Returns 0, or -1 when the file
// cannot be read (the buffer and record are freed then).

// The RwFileFunctions slots used (fopen +0x4, fclose +0x8, fread +0xC).
struct RwFileFunctions80042310 {
	void* rwfexist;                                              // 0x0
	void* (*rwfopen)(const char* name, const char* access);      // 0x4
	s32 (*rwfclose)(void* fp);                                   // 0x8
	u32 (*rwfread)(void* buffer, u32 size, u32 count, void* fp); // 0xC
};

// The OSModuleHeader fields used (see src/dolphin/os/OSLink.c).
struct Header80042310 {
	u8 pad0[0x20];
	u32 bssSize; // 0x20
	u8 pad24[0x34 - 0x24];
	void (*prolog)(void); // 0x34
};

// The hook a module registers (fn_800421B4).
struct Hook80042310 {
	u32 unknown0;           // 0x0
	void (*callback)(void); // 0x4
};

struct Module80042310 {
	u32 unknown0;           // 0x0 (copied from the hook)
	void (*callback)(void); // 0x4
	Module80042310* next;   // 0x8
	const char* name;       // 0xC
	Header80042310* header; // 0x10
	void* file;             // 0x14
	void* bss;              // 0x18
};

extern "C" {
extern char lbl_8042AF20[4];
extern char lbl_8042AF24[2];
extern char lbl_8042AF28[5];
extern Module80042310* lbl_8042C1C4;
extern Hook80042310* lbl_8042C1C8;
char* strcpy(char* dst, const char* src);
char* strcat(char* dst, const char* src);
char* RsPathnameCreate(const char* name);
void RsPathnameDestroy(char* name);
RwFileFunctions80042310* RwOsGetFileInterface(void);
s32 skyfsGetLength(void* fp);
void DCInvalidateRange(void* addr, u32 length);
s32 OSLink(Header80042310* module, void* bss);
}

// fn_80042554.
static inline s32 FileLength(const char* name)
{
	char* path;
	RwFileFunctions80042310* files;
	s32 length;
	void* fp;

	path  = RsPathnameCreate(name);
	files = RwOsGetFileInterface();
	fp    = files->rwfopen(path, lbl_8042AF20);
	RsPathnameDestroy(path);
	if (fp == NULL) {
		length = -1;
	} else {
		length = skyfsGetLength(fp);
		files->rwfclose(fp);
	}
	return length;
}

// fn_800425E8 with the size out-parameter.
static inline s32 ReadFile(const char* name, void* buffer, s32* size)
{
	char* path;
	RwFileFunctions80042310* files;
	s32 length;
	void* fp;

	path  = RsPathnameCreate(name);
	files = RwOsGetFileInterface();
	fp    = files->rwfopen(path, lbl_8042AF20);
	RsPathnameDestroy(path);
	if (fp == NULL) {
		if (size != NULL) {
			*size = 0;
		}
		length = -1;
	} else {
		length = skyfsGetLength(fp);
		DCInvalidateRange(buffer, length);
		length = files->rwfread(buffer, 1, length, fp);
		if (size != NULL) {
			*size = length;
		}
		files->rwfclose(fp);
	}
	return length;
}

extern "C" s32 fn_80042310(void* manager, const char* name)
{
	s32 size;
	char path[0x2C];

	strcpy(path, name);
	strcat(path, lbl_8042AF24);
	strcat(path, lbl_8042AF28);
	Module80042310* module = new Module80042310;
	module->file           = lbl_8042C9A4->rwmalloc((FileLength(path) + 31) & ~31);
	if (ReadFile(path, module->file, &size) != -1) {
		module->header = (Header80042310*)module->file;
		module->bss    = lbl_8042C9A4->rwmalloc((module->header->bssSize + 31) & ~31);
		OSLink(module->header, module->bss);
		lbl_8042C1C8 = NULL;
		module->header->prolog();
		Hook80042310* hook = lbl_8042C1C8;
		module->unknown0   = hook->unknown0;
		module->callback   = hook->callback;
		module->name       = name;
		module->next       = NULL;
		if (lbl_8042C1C4 != NULL) {
			module->next = lbl_8042C1C4;
		}
		lbl_8042C1C4 = module;
	} else {
		lbl_8042C9A4->rwfree(module->file);
		delete module;
		return -1;
	}
	return 0;
}
