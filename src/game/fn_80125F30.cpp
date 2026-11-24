#include "game/rw_engine.h"

// TMemoryCardCtrl::~TMemoryCardCtrl() (CORROBORATED by the PS2 build: its TMemoryCardCtrl members
// Get_Exist, the eight Req_* requests, Disp, Exec, the destructor, the constructor, Create,
// Finalize and Initialize line up with the GameCube functions from 0x80125530 to 0x80126374, and
// __vt__15TMemoryCardCtrl has the same 0x2C size), written out as the function MWCC makes of it:
// installs the class vtable, frees the two RenderWare buffers at 0xB0 and 0xB4, destroys and frees
// the save layout at 0x2C (fn_80126790) and the card controller at 0x28 (fn_8012823C), clears the
// global lbl_8042C724, runs the TObject destructor and frees the object on the game heap when the
// delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Menu80125F30 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	void* card; // 0x28
	void* f2C;  // 0x2C
	u8 pad30[0xB0 - 0x30];
	void* bufferB0; // 0xB0
	void* bufferB4; // 0xB4
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 __vt__15TMemoryCardCtrl[];
extern s32 lbl_8042C724;
void* fn_80126790(void* object, s16 flags);
void* fn_8012823C(void* card, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Menu80125F30* __dt__15TMemoryCardCtrlFv(Menu80125F30* menu, s16 flags)
{
	if (menu != NULL) {
		menu->vtable = __vt__15TMemoryCardCtrl;
		if (menu->bufferB0 != NULL) {
			lbl_8042C9A4->rwfree(menu->bufferB0);
		}
		if (menu->bufferB4 != NULL) {
			lbl_8042C9A4->rwfree(menu->bufferB4);
		}
		if (menu->f2C != NULL) {
			fn_80126790(menu->f2C, 1);
		}
		if (menu->card != NULL) {
			fn_8012823C(menu->card, 1);
		}
		lbl_8042C724 = 0;
		__dt__7TObjectFv(menu, 0);
		if (flags > 0) {
			lbl_8042C148->Free(menu);
		}
	}
	return menu;
}
}
