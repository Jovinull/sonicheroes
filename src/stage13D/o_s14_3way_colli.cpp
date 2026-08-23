#include "types.h"

#pragma force_active on

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct EulerAngles {
	s32 y;
	s32 z;
	s32 x;
} EulerAngles;

typedef struct Frame {
	Vec3 position;
	EulerAngles angle;
} Frame;

typedef struct CollisionParams {
	s8 color;
	u8 pad01;
	s16 time;
	f32 scaleX;
	f32 scaleY;
	f32 scaleZ;
} CollisionParams;

typedef struct MotionFrame {
	u8 pad00[0x18];
	u32 flags;
	u8 pad1C[0xE];
	u8 listIndex;
	u8 pad2B;
	CollisionParams* params;
} MotionFrame;

typedef struct TObject {
	const char* className;
	u16 signal;
	u16 tag;
	struct TObject* prev;
	struct TObject* next;
	struct TObject* parent;
	struct TObject* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
} TObject;

typedef struct Motion {
	MotionFrame* frame;
	void** vtable;
} Motion;

typedef struct Transform {
	u8 pad00[0x10];
	void* collision;
	u8 pad14[0x4C];
	Vec3 position;
	EulerAngles angle;
	u32 pad78;
	Vec3 previousPosition;
} Transform;

typedef struct CollisionState {
	u32 flags;
	s16 time;
} CollisionState;

typedef struct CollisionNode {
	u8 pad00[0x28];
	u16 kind;
	u8 pad2A[6];
	CollisionState* state;
	u8 pad34[4];
	struct CollisionNode* next;
} CollisionNode;

typedef struct StageCollisionTable {
	u8 pad00[0x30];
	CollisionNode* lists[256];
} StageCollisionTable;

typedef struct CollisionObject {
	TObject base;
	Motion motion;
	Transform transform;
	void* allocatedCollision;
	u32 color;
	Vec3 scale;
} CollisionObject;

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	u16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

typedef struct IteratorResult {
	void* pad00;
	void* object;
} IteratorResult;

typedef struct GameObject {
	u8 pad00[0x78];
	void* actor;
} GameObject;

typedef struct PlayerData {
	u8 pad00[0x3A];
	s8 playerIndex;
	u8 pad3B[0xD5];
	s8 actorIds[16];
} PlayerData;

typedef struct CollisionDescriptor {
	u32 colors[4];
	u32 words[4];
	const f32* vertices;
	u32 tail[7];
} CollisionDescriptor;

class CollisionPrimaryBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	u8 layoutPad[0x24];
};

class CollisionEditBase
{
public:
	virtual void editOnChange(void*);
};

class CollisionVirtual : public CollisionPrimaryBase, public CollisionEditBase
{
public:
	virtual void editOnChange(void*);
};

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C180;
extern "C" void* lbl_8042C1A4;
extern "C" StageCollisionTable* lbl_8042C298;

extern "C" void __ct__7TObjectFP7TObject(TObject*, void*);
extern "C" void __dt__7TObjectFv(TObject*, s32);
extern "C" void Error__7TObjectFPc(void);
extern "C" void fn_800189A4(void*, TObject*);
extern "C" void* fn_80018A34(void*, u32);
extern "C" IteratorResult* fn_800211A8(Transform*);
extern "C" void fn_80021384(Transform*);
extern "C" void fn_80021824(void*);
extern "C" void fn_8003BC38(Transform*);
extern "C" void fn_8003C200(Transform*, const void*, s32, s32);
extern "C" void dtor_8003C52C(Transform*, s32);
extern "C" void fn_8003C618(Transform*);
extern "C" s32 fn_80041B64(void*);
extern "C" s32 fn_8005B8BC(Motion*);
extern "C" s32 fn_8005B8D8(Motion*);
extern "C" s32 fn_8005B9F0(Motion*);
extern "C" void fn_8005BC04(Motion*);
extern "C" void dtor_8005BD3C(Motion*, s32);
extern "C" void fn_8005BE6C(Motion*);
extern "C" void fn_80063E7C(void*, s32);
extern "C" PlayerData* fn_800924E4(void);

extern "C" void fn_9_1A9B4(void);
extern "C" void objDefaultPDisp(void);
extern "C" void objDefaultImmAftSetRaster(void);
extern "C" void objDefaultDebug(void);
extern "C" void objDefaultRender(void);

extern "C" const f32 collisionZero;
extern "C" const f32 collisionDefaultScale;
extern "C" const f32 collisionHalf;
extern "C" const u32 collisionShape[12];
extern "C" f32 collisionVertices[108];
extern "C" const char* collisionColorNames[4];
extern "C" CollisionDescriptor collisionDescriptor;
extern "C" void* __vt__16CollisionVirtual[];
#define collisionVtable __vt__16CollisionVirtual

extern "C" void collisionApply(CollisionObject* object, u8 listIndex)
{
	CollisionParams* params = object->motion.frame->params;
	CollisionNode* node     = lbl_8042C298->lists[listIndex];
	if (node == NULL) {
		return;
	}
	do {
		if (node->kind == 0x1402 || node->kind == 0x1404 || node->kind == 0x1483) {
			CollisionState* state = node->state;
			if (state != NULL) {
				if (params->time == 0) {
					state->time = 30;
				} else {
					state->time = params->time;
				}
				switch (params->color) {
					case 0:
						state->flags |= 1;
						break;
					case 1:
						state->flags |= 2;
						break;
					case 2:
						state->flags |= 4;
						break;
					case 3:
						state->flags |= 7;
						break;
				}
			}
		}
		node = node->next;
	} while (node != NULL);
}

extern "C" void collisionRelease(CollisionObject* object)
{
	if (object->allocatedCollision != NULL) {
		fn_80063E7C(object->allocatedCollision, 1);
		object->allocatedCollision = NULL;
	}
}

extern "C" void collisionExec(CollisionObject* object)
{
	CollisionParams* params = object->motion.frame->params;
	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= 1;
		return;
	}
	if (((s8*)lbl_8042C180)[0x1F] != 0) {
		return;
	}
	if (fn_8005B8D8(&object->motion) != 0) {
		object->scale = *(Vec3*)&params->scaleX;
		object->color = collisionDescriptor.colors[params->color];
		return;
	}

	s32 found = 0;
	fn_80021824(&lbl_8042C1A4);
	IteratorResult* result;
	GameObject* gameObject;
	while ((gameObject
	           = ((result = fn_800211A8(&object->transform)) != NULL ? (GameObject*)result->object
	                                                                 : NULL))
	    != NULL) {
		s32 actorId        = fn_80041B64(gameObject->actor);
		PlayerData* player = fn_800924E4();
		if (player != NULL && actorId == player->actorIds[player->playerIndex]) {
			MotionFrame* activeFrame      = object->motion.frame;
			CollisionParams* activeParams = activeFrame->params;
			CollisionNode* node           = lbl_8042C298->lists[activeFrame->listIndex];
			if (node != NULL) {
				while (node != NULL) {
					if (node->kind == 0x1402 || node->kind == 0x1404 || node->kind == 0x1483) {
						CollisionState* state = node->state;
						if (state != NULL) {
							if (activeParams->time == 0) {
								state->time = 30;
							} else {
								state->time = activeParams->time;
							}
							switch (activeParams->color) {
								case 0:
									state->flags |= 1;
									break;
								case 1:
									state->flags |= 2;
									break;
								case 2:
									state->flags |= 4;
									break;
								case 3:
									state->flags |= 7;
									break;
							}
						}
					}
					node = node->next;
				}
			}
			found = 1;
		}
	}

	if (found != 0) {
		object->motion.frame->flags |= 0x10000;
		object->base.signal |= 1;
		return;
	}

	MotionFrame* frame                 = object->motion.frame;
	object->transform.previousPosition = object->transform.position;
	object->transform.position.x       = ((Frame*)frame)->position.x;
	object->transform.position.y       = ((Frame*)frame)->position.y;
	object->transform.position.z       = ((Frame*)frame)->position.z;
	object->transform.angle.y          = ((Frame*)frame)->angle.y;
	object->transform.angle.z          = ((Frame*)frame)->angle.z;
	object->transform.angle.x          = ((Frame*)frame)->angle.x;
	fn_8003BC38(&object->transform);
}

extern "C" CollisionObject* collisionDtor(CollisionObject* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = collisionVtable;
		object->motion.vtable = collisionVtable + 11;
		collisionRelease(object);
		if ((object->motion.frame->flags & 0x10000) != 0) {
			fn_8005BC04(&object->motion);
		}
		dtor_8003C52C(&object->transform, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" CollisionObject* collisionCtor(CollisionObject* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);
	fn_8003C618(&object->transform);
	object->base.vtable   = collisionVtable;
	object->motion.vtable = collisionVtable + 11;

	Motion* motion          = &object->motion;
	CollisionParams* params = motion->frame->params;
	if (fn_8005B8D8(motion) != 0 && collisionZero == params->scaleX
	    && collisionZero == params->scaleY && collisionZero == params->scaleZ) {
		params->scaleX = collisionDefaultScale;
		params->scaleY = collisionDefaultScale;
		params->scaleZ = collisionDefaultScale;
	}
	object->scale              = *(Vec3*)&params->scaleX;
	object->color              = collisionDescriptor.colors[params->color];
	object->allocatedCollision = NULL;
	fn_8003C200(&object->transform, collisionShape, 1, 4);

	f32* size = (f32*)((u8*)object->transform.collision + 0x14);
	size[0]   = collisionHalf * object->scale.x;
	size[1]   = collisionHalf * object->scale.y;
	size[2]   = collisionHalf * object->scale.z;
	fn_80021384(&object->transform);
	*(u16*)((u8*)&object->transform + 8) &= ~0x40;
	return object;
}

void CollisionVirtual::editOnChange(void* data)
{
	CollisionParams* params = *(CollisionParams**)((u8*)data + 0x2C);
	if (params->scaleX < collisionZero) {
		params->scaleX = collisionZero;
	}
	if (params->scaleY < collisionZero) {
		params->scaleY = collisionZero;
	}
	if (params->scaleZ < collisionZero) {
		params->scaleZ = collisionZero;
	}
	if (params->color < 0) {
		params->color = 0;
	}
	if (params->color >= 4) {
		params->color = 3;
	}
	if (params->time < 0) {
		params->time = 0;
	}
	extern const char* collisionFieldNames[5];
	collisionFieldNames[0] = collisionColorNames[params->color];
}

class CollisionAllocation
{
public:
	CollisionObject object;
	CollisionAllocation(void* owner) { collisionCtor(&object, owner); }
	static void* operator new(unsigned long, void* memory) { return memory; }
};

extern "C" void collisionCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, sizeof(CollisionAllocation));
	if (memory != NULL) {
		new (memory) CollisionAllocation(lbl_8042C110);
	}
}

extern "C" ObjectEntry collisionEntry;
extern "C" char collisionDisplayName[15];
extern "C" char collisionFieldTypes[12];
extern "C" const char* collisionFieldNames[5];

extern "C" void collisionRegister(void)
{
	collisionEntry.flags      = 0;
	collisionEntry.unk18      = 0;
	collisionEntry.name       = collisionDisplayName;
	collisionEntry.load       = NULL;
	collisionEntry.unload     = NULL;
	collisionEntry.create     = collisionCreate;
	collisionEntry.reset      = NULL;
	collisionEntry.flags      = 0;
	collisionEntry.unk18      = 0;
	collisionEntry.unk20      = 50;
	collisionEntry.unk1C      = 0x1403;
	collisionEntry.unk1E      = 2;
	collisionEntry.unk21      = 100;
	collisionEntry.fieldTypes = collisionFieldTypes;
	collisionEntry.fieldNames = collisionFieldNames;
	if (collisionEntry.fieldTypes != NULL) {
		collisionEntry.flags |= 8;
	} else {
		collisionEntry.flags &= ~8;
	}
}

extern "C" char collisionFieldColor[]  = "COLOR:";
extern "C" char collisionFieldTime[]   = "TIME(def 30frm)";
extern "C" char collisionFieldScaleX[] = "SCALE X";
extern "C" char collisionFieldScaleY[] = "SCALE Y";
extern "C" char collisionFieldScaleZ[] = "SCALE Z";

extern "C" const char* collisionFieldNames[5] = {
	collisionFieldColor,
	collisionFieldTime,
	collisionFieldScaleX,
	collisionFieldScaleY,
	collisionFieldScaleZ,
};

extern "C" char collisionColorBlue[]   = "COLOR:BLUE";
extern "C" char collisionColorYellow[] = "COLOR:YELLOW";
extern "C" char collisionColorRed[]    = "COLOR:RED";
extern "C" char collisionColorAll[]    = "COLOR:ALL";

extern "C" const char* collisionColorNames[4] = {
	collisionColorBlue,
	collisionColorYellow,
	collisionColorRed,
	collisionColorAll,
};

extern "C" const u32 collisionShape[12] = {
	0x0005F00C,
	4,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

extern "C" f32 collisionVertices[108] = {
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	-0.5f,
	-0.5f,
	0.5f,
	0.5f,
	-0.5f,
};

extern "C" CollisionDescriptor collisionDescriptor = {
	{ 0x880000FF, 0x88FFFF00, 0x88FF0000, 0x88FFFFFF },
	{ 0, 3, 0x00240000, 0 },
	collisionVertices,
	{ 0, 0, 0, 0, 0, 0, 0 },
};

extern "C" const __declspec(section ".rodata") f32 collisionZero         = 0.0f;
extern "C" const __declspec(section ".rodata") f32 collisionDefaultScale = 100.0f;
extern "C" const __declspec(section ".rodata") f32 collisionHalf         = 0.5f;
extern "C" const __declspec(section ".rodata") u32 collisionRodataPad    = 0;

extern "C" char collisionDisplayName[15] = "S14 3WAY COLLI";
extern "C" char collisionFieldTypes[12]  = "csFFF";

extern "C" {
ObjectEntry collisionEntry;
u32 collisionBssTail[3];
}

__declspec(section ".ctors") void (*const collisionCtorEntry)(void) = collisionRegister;

#pragma force_active reset
