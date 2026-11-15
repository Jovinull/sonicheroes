// Releases a player's resource table (+0x5D8): 8-byte entries of a 3-letter kind and a pointer,
// ended by an entry whose kind starts with '\n'. "UVB" entries are released with fn_8011B7CC
// (HYPOTHESIS: UV animations), "TMB" entries with RwFree, all others with fn_80150958
// (HYPOTHESIS: clumps); the pointers are cleared, the table is deleted (delete[]) and the pointer
// cleared. The kind strings are lbl_8042AF08 and lbl_8042AF0C.
#include "types.h"

struct Resource8003F678 {
	char kind[4]; // 0x0
	void* data;   // 0x4
};

struct Player8003F678 {
	u8 pad0[0x5D8];
	Resource8003F678* resources; // 0x5D8
};

struct RwEngine8003F678 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

extern "C" {
extern char lbl_8042AF08[4]; // "UVB"
extern char lbl_8042AF0C[4]; // "TMB"
extern RwEngine8003F678* lbl_8042C9A4;
int strncmp(const char* a, const char* b, unsigned long n);
void fn_8011B7CC(void* data);
void fn_80150958(void* data);
void __dla__FPv(void* p);

void fn_8003F678(Player8003F678* p)
{
	int i;

	for (i = 0; p->resources[i].kind[0] != '\n'; i++) {
		if (strncmp(p->resources[i].kind, lbl_8042AF08, 3) == 0) {
			if (p->resources[i].data != NULL) {
				fn_8011B7CC(p->resources[i].data);
			}
		} else if (strncmp(p->resources[i].kind, lbl_8042AF0C, 3) == 0) {
			if (p->resources[i].data != NULL) {
				lbl_8042C9A4->rwfree(p->resources[i].data);
			}
		} else if (p->resources[i].data != NULL) {
			fn_80150958(p->resources[i].data);
		}
		p->resources[i].data = NULL;
	}
	__dla__FPv(p->resources);
	p->resources = NULL;
}
}
