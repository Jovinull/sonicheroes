#include "types.h"

// The objSecollision object's Exec (objSecollisionExec here): the sound trigger
// volume. Out of range or marked to die, it ends. While the editor moves it, it
// takes the placement's position and, for the two one-shot kinds, does nothing
// more. Otherwise, unless the game's flag at 0x1F is set, it collides and on a
// hit plays its sound by kind: 0 plays it once, 1 plays it once at the volume
// (both then mark the placement used and end the object), 2 and 4 attach it to
// the object, 3 and 5 attach it at the volume (as 0x23/0x25 when the second
// parameter is 1). Then it records the volume's position and angles and
// re-enters its collision.
//
// The byte at 0x06 of the parameters is unsigned and every call casts it to
// signed, except kind 5's plain call, which passes it as it is.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct ObjSecollisionParams {
	u32 sound;   // 0x00
	s8 kind;     // 0x04
	u8 attached; // 0x05
	u8 unk06;    // 0x06
	u8 pad07;    // 0x07
	s16 range;   // 0x08
} ObjSecollisionParams;

typedef struct ObjSecollisionSetData {
	RwV3d pos;                    // 0x00
	s32 angX;                     // 0x0C
	s32 angY;                     // 0x10
	s32 angZ;                     // 0x14
	u32 flags;                    // 0x18
	u8 unk1C[0x10];               // 0x1C
	ObjSecollisionParams* params; // 0x2C
} ObjSecollisionSetData;

typedef struct ObjSecollisionHit {
	u8 unk00[0x4];
	u32 hit; // 0x04
} ObjSecollisionHit;

typedef struct ObjSecollision {
	u8 unk00[0x4];
	u16 signal;                     // 0x04
	u8 unk06[0x22];                 // 0x06
	ObjSecollisionSetData* setdata; // 0x28
	void* setobjVtable;             // 0x2C
	u8 colli[0x60];                 // 0x30
	RwV3d colliPos;                 // 0x90
	s32 colliAngX;                  // 0x9C
	s32 colliAngY;                  // 0xA0
	s32 colliAngZ;                  // 0xA4
	u8 unkA8[0x4];                  // 0xA8
	RwV3d colliOldPos;              // 0xAC
	RwV3d pos;                      // 0xB8
} ObjSecollision;

extern "C" u8* lbl_8042C180;
extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;

extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setobj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setobj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setobj);
extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void fn_80021824(void* list);
extern "C" ObjSecollisionHit* fn_800211A8(void* colli);
extern "C" void fn_800B52E8(void* sound, u16 id, s32 arg2, s32 arg3);
extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);

extern "C" void objSecollisionExec(ObjSecollision* object)
{
	ObjSecollisionParams* params = object->setdata->params;
	ObjSecollisionHit* hit;
	ObjSecollisionSetData* setdata;

	if (CheckRangeOut__10TObjSetObjFv(&object->setdata)
	    || CheckMustKill__10TObjSetObjFv(&object->setdata)) {
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->setdata)) {
		setdata       = object->setdata;
		object->pos.x = setdata->pos.x;
		object->pos.y = setdata->pos.y;
		object->pos.z = setdata->pos.z;
		if (params->kind == 0 || params->kind == 1) {
			return;
		}
	}
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return;
	}
	fn_80021824(lbl_8042C1A4);
	hit = fn_800211A8(object->colli);
	if ((hit != NULL ? hit->hit : 0) != 0) {
		switch (params->kind) {
			case 0:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, params->sound, 0, 0);
				}
				object->setdata->flags |= 0x10000;
				object->signal |= 1;
				return;
			case 1:
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(
					    lbl_8042C388, params->sound, &object->pos, NULL, 1, (s8)params->unk06, 0);
				}
				object->setdata->flags |= 0x10000;
				object->signal |= 1;
				return;
			case 2:
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, NULL, object, 2, 0, params->range);
				}
				break;
			case 3:
				if (params->attached == 1 && lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, &object->pos, object, 0x23,
					    (s8)params->unk06, params->range);
				} else if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, &object->pos, object, 3,
					    (s8)params->unk06, params->range);
				}
				break;
			case 4:
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, NULL, object, 4, 0, params->range);
				}
				break;
			case 5:
				if (params->attached == 1 && lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, &object->pos, object, 0x25,
					    (s8)params->unk06, params->range);
				} else if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, params->sound, &object->pos, object, 5, params->unk06,
					    params->range);
				}
				break;
		}
	}
	setdata               = object->setdata;
	object->colliOldPos.x = object->colliPos.x;
	object->colliOldPos.y = object->colliPos.y;
	object->colliOldPos.z = object->colliPos.z;
	object->colliPos.x    = object->pos.x;
	object->colliPos.y    = object->pos.y;
	object->colliPos.z    = object->pos.z;
	object->colliAngX     = setdata->angX;
	object->colliAngY     = setdata->angY;
	object->colliAngZ     = setdata->angZ;
	Entry__7C_COLLIFv(object->colli);
}
