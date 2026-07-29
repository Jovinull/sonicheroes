typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

struct TObject;

extern "C" {
void FreeHeap(void* heap, void* object);
void* AllocHeap(void* heap, u32 size);
extern void* TaskHeap;
}

struct TObjectBase {
	u8 kind[4];
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct TObject : public TObjectBase {
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void StartFadeOut();
	virtual void Virtual1();
	virtual void Exec();
	virtual void Disp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();

	u16 field1C;
	u16 field1E;
	u16 field20;
	u16 pad22;
	u16 field24;
	u16 pad26;
	u32 field28;

	static void operator delete(void* object) { FreeHeap(TaskHeap, object); }
	static void* operator new(unsigned long size) { return AllocHeap(TaskHeap, size); }
};

struct RwV3d {
	float x;
	float y;
	float z;
};

struct FadeScreen {
	u8 data[0x4C];

	FadeScreen();
	~FadeScreen();
	void Exec();
};

struct SpAdvStgFailed : public TObject {
	SpAdvStgFailed(TObject* parent, void* stage);
	virtual ~SpAdvStgFailed();
	virtual void Exec();
	virtual void Disp();
	virtual void StartFadeOut();

	bool IsFadeOutDone();

	void* resource;
	RwV3d position;
	FadeScreen fade;
	s32 state;
};

struct FailedResource {
	u32 values[9];
};

extern "C" {
void GetRenderState(s32 state, s32* value);
void SetRenderState(s32 state, s32 value);
void DrawResource(void* resource);
void StopResource(void* handle, RwV3d* position, s32 mode);
void* GetResourceHandle(void* resource);
void ReleaseResourceHandle(void* handle, void* resource);
void DestroyResource(void* resource);
void* AllocResource(void*);
void AttachResource(void*, void*);
RwV3d* GetAnimationPosition(void*);
void* GetAnimation(void*);
void SetStageFailed(void*, s32);
void DestroyAnimation(void*);
void DestroyStageFailedController(void*);

extern void* StageController;
extern void* StageFailedDrawList;
extern u8 StageFailedResourceName[];
}

extern FailedResource StageFailedResources[5];

// The first word belongs to the preceding retail input atom.  Keeping the
// remainder here preserves the original contiguous table while allowing this
// independently reconstructed object to retain its natural 8-byte alignment.
u32 StageFailedResourcesTail[44] = {
	4,
	1,
	0,
	0xBF800000,
	0x3DCCCCCD,
	0x3F800000,
	(u32)StageFailedResourceName,
	4,
	0,
	4,
	2,
	0,
	0xBF800000,
	0x3DCCCCCD,
	0x3F800000,
	(u32)StageFailedResourceName,
	5,
	0,
	4,
	1,
	0,
	0xBF800000,
	0x3DCCCCCD,
	0x3F800000,
	(u32)StageFailedResourceName,
	6,
	0,
	5,
	3,
	0,
	0xBF800000,
	0x3DCCCCCD,
	0x3F800000,
	(u32)StageFailedResourceName,
	7,
	0,
	14,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

// The GameCube section order proves this storage was a separate linker input:
// keeping it in this code object creates an impossible .text/.bss order cycle.
extern "C" u8 lbl_80303EC8[0x70];
#define StageFailedAnimation lbl_80303EC8
extern "C" {
void* StageFailedArchive;
void* StageFailedController;
}

static inline s32 IsStageControllerReady(void* value)
{
	u8* controller = (u8*)value;
	s32 ready      = 0;
	if (*(s32*)(controller + 0x30) == 0 && *(s32*)(controller + 0x3C) == 0
	    && *(s32*)(controller + 0x58) == -1)
		ready = 1;
	return ready;
}

bool SpAdvStgFailed::IsFadeOutDone()
{
	return state == 2;
}

void SpAdvStgFailed::Exec() { }

void SpAdvStgFailed::Disp()
{
	s32 old8;
	s32 old6;
	s32 old9;
	s32 old12;
	s32 old20;
	s32 old14;
	s32 old10;
	s32 old11;

	GetRenderState(8, &old8);
	GetRenderState(6, &old6);
	GetRenderState(9, &old9);
	GetRenderState(12, &old12);
	GetRenderState(20, &old20);
	GetRenderState(14, &old14);
	GetRenderState(10, &old10);
	GetRenderState(11, &old11);
	SetRenderState(8, 1);
	SetRenderState(6, 1);
	SetRenderState(9, 2);
	SetRenderState(12, 1);
	SetRenderState(20, 2);
	SetRenderState(14, 0);
	SetRenderState(10, 5);
	SetRenderState(11, 6);
	if (state != 2 && resource != 0)
		DrawResource(resource);
	SetRenderState(8, old8);
	SetRenderState(6, old6);
	SetRenderState(9, old9);
	SetRenderState(12, old12);
	SetRenderState(20, old20);
	SetRenderState(14, old14);
	SetRenderState(10, old10);
	SetRenderState(11, old11);
}

void SpAdvStgFailed::StartFadeOut()
{
	if (resource != 0) {
		void* handle = *(void**)((u8*)resource + 4);
		if (handle != 0)
			StopResource(handle, &position, 0);
	}

	switch (state) {
		case 0: {
			if (StageController != 0) {
				s32 ready = IsStageControllerReady(StageController);
				if (ready) {
					*(s32*)((u8*)this + 0x58) = 3;
					state                     = 1;
				}
			} else
				state = 2;
			break;
		}
		case 1:
			if (*(u32*)((u8*)this + 0x4C) & 2)
				state = 2;
			break;
		case 2:
			break;
	}
	fade.Exec();
}

SpAdvStgFailed::~SpAdvStgFailed()
{
	void* current = resource;
	if (current != 0) {
		void* handle = GetResourceHandle(current);
		ReleaseResourceHandle(handle, current);
		DestroyResource(resource);
		resource = 0;
	}
}

inline SpAdvStgFailed::SpAdvStgFailed(TObject* parent, void* stage)
    : TObject(parent)
{
	*(void**)&kind = StageFailedDrawList;
	field1E        = sizeof(SpAdvStgFailed);
	field28        = *(u32*)stage;
	resource       = 0;
	RwV3d* source  = GetAnimationPosition(StageFailedAnimation);
	position.x     = source->x;
	position.y     = source->y;
	position.z     = source->z;
	position.z += 20.0f;
	state = 0;

	if (resource == 0) {
		resource = AllocResource(StageFailedArchive);
		if (resource != 0)
			AttachResource(GetAnimation(StageFailedAnimation), resource);
	}

	*(void**)((u8*)this + 0x6C)           = resource;
	*(FailedResource**)((u8*)this + 0x68) = StageFailedResources;
	*(s32*)((u8*)this + 0x58)             = 0;
	fade.Exec();

	if (StageController != 0) {
		SetStageFailed(StageController, *(s32*)stage);
		*(s32*)((u8*)StageController + 0x60) = 1;
	}
}

SpAdvStgFailed* GoStageFailed(TObject* parent, void* stage)
{
	return new SpAdvStgFailed(parent, stage);
}

void FinalizeStageFailed()
{
	for (u32 i = 0; i != 5; ++i) {
		if (*(void**)&StageFailedResources[i] != 0) {
			DestroyStageFailedController(*(void**)&StageFailedResources[i]);
			*(void**)&StageFailedResources[i] = 0;
		}
	}
	if (StageFailedArchive != 0) {
		DestroyResource(StageFailedArchive);
		StageFailedArchive = 0;
	}
	if (StageFailedController != 0) {
		DestroyAnimation(StageFailedController);
		StageFailedController = 0;
	}
}
