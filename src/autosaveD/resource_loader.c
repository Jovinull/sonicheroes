#include "types.h"

extern char lbl_2_data_468[];
extern char* lbl_2_data_418[5];
struct Resource;
struct Archive;

extern Archive* lbl_2_bss_50;
extern u32 lbl_2_bss_54[5];

extern "C" Resource* fn_80057644(u32 size);
extern "C" Resource* fn_800BCC84(Resource* resource, const char* path, s32 flags);
extern "C" void* fn_80012994(u32 size);
extern "C" Archive* fn_800BC580(Resource* resource, s32 type, void* buffer);
extern "C" void* fn_801A4BBC(Archive* archive, const char* name);
extern "C" void fn_800126C8(void* buffer);
extern "C" void fn_800BCBD4(Resource* resource, s32 free);

static inline Resource* create_resource(void)
{
	Resource* resource = fn_80057644(0x58);
	if (resource != NULL) {
		resource = fn_800BCC84(resource, lbl_2_data_468, 0);
	}
	return resource;
}

extern "C" void fn_2_3EC0(void)
{
	Resource* resource;
	void* buffer;
	s32 i;

	resource = create_resource();

	if (resource != NULL) {
		buffer = fn_80012994(0x300000);
		if (buffer != NULL) {
			lbl_2_bss_50 = fn_800BC580(resource, 2, buffer);
			if (lbl_2_bss_50 != NULL) {
				for (i = 0; i != 5; i++) {
					void* entry = fn_801A4BBC(lbl_2_bss_50, lbl_2_data_418[i]);
					if (entry != NULL) {
						lbl_2_bss_54[i] = *(u32*)entry;
					}
				}
			}
			fn_800126C8(buffer);
		}
		fn_800BCBD4(resource, 1);
	}
}
