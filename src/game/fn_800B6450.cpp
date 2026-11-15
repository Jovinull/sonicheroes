// Destructor of the sound manager (the object lbl_8042C388 points at; the class name is
// UNKNOWN): stops it (fn_800B48B8), shuts the active stream down when +0x970 is set
// (fn_8020AD44, fn_8020ADCC(2)), frees the six sound buffers (+0x97C/+0x978 pairs, RwFree),
// calls fn_8020AE38, destroys the 0x2B voice records (0x38 bytes each from +0x8, destructor
// dtor_800B6D40) and frees the object when flags > 0. Returns the object.
#include "types.h"

struct Buffer800B6450 {
	s32 size;   // 0x0 (+0x978)
	void* data; // 0x4 (+0x97C)
};

struct Manager800B6450 {
	u8 pad0[8];
	u8 voices[0x2B][0x38]; // 0x8
	s32 streaming;         // 0x970
	s8 unknown974;         // 0x974
	s8 unknown975;         // 0x975
	u8 pad976[2];
	Buffer800B6450 buffers[6]; // 0x978
};

struct RwEngine800B6450 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

extern "C" {
extern RwEngine800B6450* lbl_8042C9A4;
void fn_800B48B8(Manager800B6450* manager);
void fn_8020AD44(void);
void fn_8020ADCC(s32 value);
void fn_8020AE38(void);
void* dtor_800B6D40(void* voice, s16 flags);
void __destroy_arr(void* array, void* dtor, u32 size, u32 count);
void __dl__FPv(void* p);
}

// Frees sound buffer `index` (0-5).
static inline void FreeBuffer(Manager800B6450* manager, s8 index)
{
	if (index >= 0 && index < 6) {
		if (manager->buffers[index].data != NULL) {
			if (manager->buffers[index].data != NULL) {
				lbl_8042C9A4->rwfree(manager->buffers[index].data);
			}
			manager->buffers[index].data = NULL;
			manager->buffers[index].size = 0;
		}
	}
}

extern "C" Manager800B6450* fn_800B6450(Manager800B6450* manager, s16 flags)
{
	if (manager != NULL) {
		s8 i;

		fn_800B48B8(manager);
		if (manager->streaming != 0) {
			fn_8020AD44();
			fn_8020ADCC(2);
			manager->unknown974 = 0;
			manager->unknown975 = 0;
			manager->streaming  = 0;
		}
		for (i = 0; i < 6; i++) {
			FreeBuffer(manager, i);
		}
		fn_8020AE38();
		__destroy_arr(manager->voices, (void*)dtor_800B6D40, 0x38, 0x2B);
		if (flags > 0) {
			__dl__FPv(manager);
		}
	}
	return manager;
}
