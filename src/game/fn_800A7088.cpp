// TObjEnemy's destructor (its slot in the TObjEnemy vtable lbl_80252FB4; the symbol keeps its
// address name because the enemy RELs call it by that name). Installs the vtable and its
// TObjSetObj part (+0x2C into it, at +0xB4), unlinks and deletes every enemy key of the list at
// +0x228, then destroys the ENEMYMTNMAN member (+0xB8) and the TObjSetObj (+0xB0), C_COLLI (+0x28)
// and TObject bases, and frees the object when flags > 0. Returns the object.
#include "types.h"

struct ObjEnemyKey;

struct Enemy800A7088 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0x88];          // 0x28 (C_COLLI base)
	u8 setObj[4];            // 0xB0 (TObjSetObj base)
	void* setObjVtable;      // 0xB4
	u8 motion[0x228 - 0xB8]; // 0xB8 (ENEMYMTNMAN member; extent UNKNOWN)
	ObjEnemyKey* keys;       // 0x228
};

struct THeapCtrl;

extern "C" {
extern u8 lbl_80252FB4[];
extern THeapCtrl* lbl_8042C148;
void UnlinkKey__11ObjEnemyKeyFv(ObjEnemyKey* key);
void __dl__FPv(void* p);
void __dt__11ENEMYMTNMANFv(void* motion, s32 flags);
void __dt__10TObjSetObjFv(void* setObj, s32 flags);
void __dt__7C_COLLIFv(void* colli, s32 flags);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);

Enemy800A7088* fn_800A7088(Enemy800A7088* o, s16 flags)
{
	if (o != NULL) {
		ObjEnemyKey* key;

		o->vtable       = lbl_80252FB4;
		o->setObjVtable = lbl_80252FB4 + 0x2C;
		while ((key = o->keys) != NULL) {
			UnlinkKey__11ObjEnemyKeyFv(key);
			__dl__FPv(key);
		}
		__dt__11ENEMYMTNMANFv(o->motion, 0);
		__dt__10TObjSetObjFv(o->setObj, 0);
		__dt__7C_COLLIFv(o->colli, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
