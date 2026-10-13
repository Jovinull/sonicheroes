#include "types.h"

struct SETOBJ_PARAM {
	u8 data[0x30];
};

extern "C" {
extern u8 lbl_16_bss_B9C[];
extern char lbl_16_data_4148[];
extern char lbl_16_data_44EC[];
extern char lbl_16_data_44FC[];
void fn_16_32F10(void);
void setupObjClass(SETOBJ_PARAM* param, char* name, void (*load)(), void (*unload)(),
    void (*create)(), void (*reset)(SETOBJ_PARAM*), u32 flags, u32 field18, u32 field20,
    u32 objectId, u32 field1E, u32 field21, char* fieldTypes, char* fieldNames);
}

extern "C" void fn_16_32F60(void)
{
	setupObjClass((SETOBJ_PARAM*)lbl_16_bss_B9C, lbl_16_data_44EC, 0, 0, fn_16_32F10, 0, 0x1000, 0,
	    0x32, 0x59, 2, 0, lbl_16_data_44FC, lbl_16_data_4148);
}

__declspec(section ".ctors") void (*const fn_16_32F60CtorEntry)(void) = fn_16_32F60;
