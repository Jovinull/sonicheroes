#include "types.h"

struct TEXTURE_ENTRY {
	void* texture;
	char* name;
};

struct TEXTURE_LIST {
	TEXTURE_ENTRY* entries;
	u32 count;
};

extern "C" void fn_801A46D0(void* dictionary);

static inline void ReleaseList(TEXTURE_LIST* list)
{
	TEXTURE_ENTRY* entry = list->entries;
	u32 i                = 0;

	while (i < list->count) {
		if (entry != NULL) {
			if (entry->texture != NULL) {
				entry->texture = NULL;
			}
		}
		i++;
		entry++;
	}
}

extern "C" void fn_8005FA8C(void* dictionary, TEXTURE_LIST* list)
{
	ReleaseList(list);
	fn_801A46D0(dictionary);
}
