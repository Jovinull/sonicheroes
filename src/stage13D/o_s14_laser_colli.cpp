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

typedef struct TObjectStorage {
	const char* className;
	u16 signal;
	u16 tag;
	struct TObjectStorage* prev;
	struct TObjectStorage* next;
	struct TObjectStorage* parent;
	struct TObjectStorage* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
} TObjectStorage;

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
	TObjectStorage base;
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

struct RwTexCoords;
struct RwTexture;
struct sAngle;
typedef struct IMPRIM_INFO {
	u32 flag;
	u32 drawType;
	u16 vertNum;
	u16 indexNum;
	s16* index;
	Vec3* pos;
	u32* color;
	RwTexCoords* uv;
	Vec3* normal;
	Vec3* TransPos;
	sAngle* RotAng;
	Vec3* Scale;
	RwTexture* texture;
} IMPRIM_INFO;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C180;
extern "C" void* lbl_8042C1A4;
extern "C" StageCollisionTable* lbl_8042C298;

extern "C" void __ct__7TObjectFP7TObject(TObjectStorage*, void*);
extern "C" void __dt__7TObjectFv(TObjectStorage*, s32);
extern "C" void Error__7TObjectFPc(void);
extern "C" void Free__9THeapCtrlFPv(void*, TObjectStorage*);
extern "C" void* Malloc__9THeapCtrlFUi(void*, u32);
extern "C" IteratorResult* fn_800211A8(Transform*);
extern "C" void CalcRange__7C_COLLIFv(Transform*);
extern "C" void fn_80021824(void*);
extern "C" void Entry__7C_COLLIFv(Transform*);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(Transform*, const void*, s32, s32);
extern "C" void __dt__7C_COLLIFv(Transform*, s32);
extern "C" void __ct__7C_COLLIFv(Transform*);
extern "C" s32 fn_80041B64(void*);
extern "C" s32 CheckMustKill__10TObjSetObjFv(Motion*);
extern "C" s32 OnEdit__10TObjSetObjFv(Motion*);
extern "C" s32 CheckRangeOut__10TObjSetObjFv(Motion*);
extern "C" void SetEnd__10TObjSetObjFv(Motion*);
extern "C" void __dt__10TObjSetObjFv(Motion*, s32);
extern "C" void __ct__10TObjSetObjFv(Motion*);
extern "C" void fn_80063E7C(void*, s32);
extern "C" PlayerData* fn_800924E4(void);

extern "C" void Disp__7TObjectFv(void);
extern "C" void objDefaultPDisp(void);
extern "C" void objDefaultImmAftSetRaster(void);
extern "C" void objDefaultDebug(void);
extern "C" void objDefaultRender(void);

extern "C" const f32 collisionDefaultScale;
extern "C" const f32 collisionHalf;
extern "C" const u32 collisionShape[12];
extern "C" Vec3 collisionVertices[36];
extern "C" const char* collisionColorNames[4];
extern "C" u32 colli_color[4];
extern "C" IMPRIM_INFO prim_colli;

struct SETDATA_PARAM;
class TObject
{
public:
	const char* ClassName;
	u16 Signal, Tag;
	TObject *Prev, *Next, *Parent, *Child;
	TObject(TObject*);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}
	static void operator delete(void* memory)
	{
		Free__9THeapCtrlFPv(lbl_8042C148, (TObjectStorage*)memory);
	}
};
class TObjSetObj
{
public:
	MotionFrame* ObjParam;
	TObjSetObj();
	~TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);
};
class C_COLLI
{
	u32 fields[34];

public:
	C_COLLI();
	~C_COLLI();
};
class TObjS14LaserColli : public TObject, public TObjSetObj, public C_COLLI
{
public:
	void* pImPrim;
	u32 color;
	Vec3 scale;
	TObjS14LaserColli(TObject*);
	virtual ~TObjS14LaserColli();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
	void SetCommuicateStrage(u8);
	void ApplyCommunicateList(u8);
};
typedef char NativeSize[(sizeof(TObjS14LaserColli) == 204) ? 1 : -1];
void TObjS14LaserColli::SetCommuicateStrage(u8 listIndex)
{
	CollisionObject* object = (CollisionObject*)this;
	CollisionParams* params = ObjParam->params;
	CollisionNode* head     = lbl_8042C298->lists[listIndex];
	CollisionNode* node     = head;
	if (head == NULL) {
		return;
	}
	while (node != NULL) {
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
	}
}

void TObjS14LaserColli::TDisp()
{
	CollisionObject* object = (CollisionObject*)this;
	if (object->allocatedCollision != NULL) {
		fn_80063E7C(object->allocatedCollision, 1);
		object->allocatedCollision = NULL;
	}
}

// Reconstruction of the inlined communication loop. Its guarded form retains
// the observed Exec control flow; the standalone method retains its early return.
inline void TObjS14LaserColli::ApplyCommunicateList(u8 listIndex)
{
	CollisionObject* object = (CollisionObject*)this;
	CollisionParams* params = ObjParam->params;
	CollisionNode* head     = lbl_8042C298->lists[listIndex];
	CollisionNode* node     = head;
	if (head != NULL) {
		while (node != NULL) {
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
		}
	}
}

void TObjS14LaserColli::Exec()
{
	CollisionObject* object = (CollisionObject*)this;
	CollisionParams* params = ObjParam->params;
	if (CheckRangeOut__10TObjSetObjFv(&object->motion) != 0
	    || CheckMustKill__10TObjSetObjFv(&object->motion) != 0) {
		object->base.signal |= 1;
		return;
	}
	if (((s8*)lbl_8042C180)[0x1F] != 0) {
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->motion) != 0) {
		object->scale = *(Vec3*)&params->scaleX;
		object->color = colli_color[params->color];
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
			ApplyCommunicateList(ObjParam->listIndex);
			found = 1;
		}
	}

	if (found != 0) {
		ObjParam->flags |= 0x10000;
		object->base.signal |= 1;
		return;
	}

	MotionFrame* frame                 = ObjParam;
	object->transform.previousPosition = object->transform.position;
	object->transform.position.x       = ((Frame*)frame)->position.x;
	object->transform.position.y       = ((Frame*)frame)->position.y;
	object->transform.position.z       = ((Frame*)frame)->position.z;
	object->transform.angle.y          = ((Frame*)frame)->angle.y;
	object->transform.angle.z          = ((Frame*)frame)->angle.z;
	object->transform.angle.x          = ((Frame*)frame)->angle.x;
	Entry__7C_COLLIFv(&object->transform);
}

TObjS14LaserColli::~TObjS14LaserColli()
{
	TObjS14LaserColli::TDisp();
	CollisionObject* object = (CollisionObject*)this;
	if ((object->motion.frame->flags & 0x10000) != 0)
		SetEnd__10TObjSetObjFv(&object->motion);
}

TObjS14LaserColli::TObjS14LaserColli(TObject* owner)
    : TObject(owner)
    , TObjSetObj()
    , C_COLLI()
{
	CollisionObject* object = (CollisionObject*)this;

	Motion* motion          = &object->motion;
	CollisionParams* params = motion->frame->params;
	if (OnEdit__10TObjSetObjFv(motion) != 0 && 0.0f == params->scaleX && 0.0f == params->scaleY
	    && 0.0f == params->scaleZ) {
		params->scaleX = collisionDefaultScale;
		params->scaleY = collisionDefaultScale;
		params->scaleZ = collisionDefaultScale;
	}
	object->scale              = *(Vec3*)&params->scaleX;
	object->color              = colli_color[params->color];
	object->allocatedCollision = NULL;
	Init__7C_COLLIFP8CCL_INFOiUc(&object->transform, collisionShape, 1, 4);

	f32* size = (f32*)((u8*)object->transform.collision + 0x14);
	size[0]   = collisionHalf * object->scale.x;
	size[1]   = collisionHalf * object->scale.y;
	size[2]   = collisionHalf * object->scale.z;
	CalcRange__7C_COLLIFv(&object->transform);
	*(u16*)((u8*)&object->transform + 8) &= ~0x40;
}

void TObjS14LaserColli::EditOnChange(SETDATA_PARAM* data)
{
	CollisionParams* params = *(CollisionParams**)((u8*)data + 0x2C);
	if (params->scaleX < 0.0f) {
		params->scaleX = 0.0f;
	}
	if (params->scaleY < 0.0f) {
		params->scaleY = 0.0f;
	}
	if (params->scaleZ < 0.0f) {
		params->scaleZ = 0.0f;
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

extern "C" void collisionCreate(void)
{
	new TObjS14LaserColli((TObject*)lbl_8042C110);
}

extern "C" ObjectEntry collisionEntry;
extern "C" char collisionDisplayName[15];
extern "C" char collisionFieldTypes[6];
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

extern "C" Vec3 collisionVertices[36] = {
	{ 0.5f, 0.5f, 0.5f },
	{ -0.5f, -0.5f, 0.5f },
	{ 0.5f, -0.5f, 0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ -0.5f, -0.5f, 0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ 0.5f, 0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ 0.5f, 0.5f, -0.5f },
	{ 0.5f, -0.5f, -0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ 0.5f, 0.5f, -0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ 0.5f, -0.5f, 0.5f },
	{ -0.5f, -0.5f, 0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ 0.5f, -0.5f, -0.5f },
	{ 0.5f, -0.5f, 0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f, 0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ 0.5f, -0.5f, 0.5f },
	{ 0.5f, -0.5f, -0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ 0.5f, -0.5f, -0.5f },
	{ 0.5f, 0.5f, -0.5f },
};

extern "C" u32 colli_color[4]     = { 0x880000FF, 0x88FFFF00, 0x88FF0000, 0x88FFFFFF };
extern "C" IMPRIM_INFO prim_colli = {
	0,
	3,
	36,
	0,
	NULL,
	collisionVertices,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

extern "C" const __declspec(section ".rodata") f32 collisionDefaultScale = 100.0f;
extern "C" const __declspec(section ".rodata") f32 collisionHalf         = 0.5f;
// Residual configured zero atom; historical ownership remains inferred.
extern "C" const __declspec(section ".rodata") u32 collisionRodataPad = 0;

extern "C" char collisionDisplayName[15] = "S14 3WAY COLLI";
extern "C" char collisionFieldTypes[6]   = "csFFF";

extern "C" {
ObjectEntry collisionEntry;
// Existing configured zero-storage extent; original declaration is unknown.
u32 collisionBssTail[3];
}

__declspec(section ".ctors") void (*const collisionCtorEntry)(void) = collisionRegister;

#pragma force_active reset
