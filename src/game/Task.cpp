typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct TObjectBase {
	u8 kind[4];
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct THeapCtrl {
	u8 data[12];

	THeapCtrl(u32 size, u32 alignment);
	void Free(void* object);
	void* Malloc(u32 size);
	static void* operator new(unsigned long size);
	static void operator delete(void* object);
};

extern "C" THeapCtrl* lbl_8042C148;

struct TObject : public TObjectBase {
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
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

	int CheckAlive();
	int GetChildCount();
	void ImmAftSetRasterChild();
	void TDispChild();
	void PDispChild();
	void DispChild();
	void ExecChild();
	void DeleteChild();
	void KillChild();
	void Kill();
	static void operator delete(void* object);
	static void* operator new(unsigned long size);
};

struct TMainTask : public TObject {
	virtual ~TMainTask();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();

	TMainTask();
	void Reset();
	void PauseChild();
	void ContinueChild();
	void Finalize();
	void Initialize();
};

char* CL_TObject     = "TObject";
char* CL_TMainTask   = "TMainTask";
char* CL_TL_SU       = "TL_SU";
char* CL_TL_00       = "TL_00";
char* CL_TL_01       = "TL_01";
char* CL_TL_02       = "TL_02";
char* CL_TL_03       = "TL_03";
char* CL_TL_04       = "TL_04";
char* CL_TL_05       = "TL_05";
char* CL_TL_06       = "TL_06";
char* CL_TL_07       = "TL_07";
char* CL_TL_PARTICLE = "TL_PARTICLE";
char* CL_TL_TIMESTOP = "TL_TIMESTOP";

TObject* TL_SU;
TObject* TL_00;
TObject* TL_01;
TObject* TL_02;
TObject* TL_03;
TObject* TL_04;
TObject* TL_05;
TObject* TL_06;
TObject* TL_07;
TObject* TL_PARTICLE;
TObject* TL_TIMESTOP;
u32 ObjectCount;
u32 TaskNest;
u32 ExecSleepFlag;
u32 ExecSleepFlagOld;
u32 DispSleepFlag;
u32 DispSleepFlagOld;
u32 ImmAftSetRasterSleepFlag;
u32 ImmAftSetRasterSleepFlagOld;
struct RwRaster;
RwRaster* charSet_Debug;
THeapCtrl* TaskHeap;

#define lbl_8042ADA0 CL_TObject
#define lbl_8042ADB0 CL_TL_SU
#define lbl_8042ADBC CL_TL_00
#define lbl_8042ADC8 CL_TL_01
#define lbl_8042ADD4 CL_TL_02
#define lbl_8042ADE0 CL_TL_03
#define lbl_8042ADEC CL_TL_04
#define lbl_8042ADF8 CL_TL_05
#define lbl_8042AE04 CL_TL_06
#define lbl_8042AE10 CL_TL_07
#define lbl_8042AE14 CL_TL_PARTICLE
#define lbl_8042AE18 CL_TL_TIMESTOP
#define lbl_8042C0F8 TL_SU
#define lbl_8042C0FC TL_00
#define lbl_8042C100 TL_01
#define lbl_8042C104 TL_02
#define lbl_8042C108 TL_03
#define lbl_8042C10C TL_04
#define lbl_8042C110 TL_05
#define lbl_8042C114 TL_06
#define lbl_8042C118 TL_07
#define lbl_8042C11C TL_PARTICLE
#define lbl_8042C120 TL_TIMESTOP
#define lbl_8042C124 ObjectCount
#define lbl_8042C128 TaskNest
#define lbl_8042C12C ExecSleepFlag
#define lbl_8042C130 ExecSleepFlagOld
#define lbl_8042C134 DispSleepFlag
#define lbl_8042C138 DispSleepFlagOld
#define lbl_8042C13C ImmAftSetRasterSleepFlag
#define lbl_8042C140 ImmAftSetRasterSleepFlagOld
#define lbl_8042C148 TaskHeap

extern "C" {
extern void* __vt__7TObject[];

u64 OSGetTime();
void fn_8005751C();
void fn_80057574();
void fn_80017878(TObject*);
void fn_80017AEC(TObject*);
void fn_80017DF0(TObject*);
void fn_80018064(TObject*);
void fn_80018368(TObject*);
void fn_80018AB0(THeapCtrl*, int);
void* fn_80018A34(THeapCtrl*, u32);
void fn_80057520(char*);
}

extern TMainTask MainTask;

#define DESTROY_CHILDREN(root)                                                                     \
	do {                                                                                           \
		TObject* object = (root);                                                                  \
		while (object->child != 0)                                                                 \
			delete (TObject*)object->child;                                                        \
	} while (0)

void TMainTask::Reset()
{
	DESTROY_CHILDREN(lbl_8042C11C);
	DESTROY_CHILDREN(lbl_8042C118);
	DESTROY_CHILDREN(lbl_8042C114);
	DESTROY_CHILDREN(lbl_8042C110);
	DESTROY_CHILDREN(lbl_8042C10C);
	DESTROY_CHILDREN(lbl_8042C108);
	DESTROY_CHILDREN(lbl_8042C104);
	DESTROY_CHILDREN(lbl_8042C100);
	DESTROY_CHILDREN(lbl_8042C0FC);
}

void TMainTask::PauseChild()
{
	lbl_8042C104->flags ^= 8;
	lbl_8042C108->flags ^= 8;
	lbl_8042C10C->flags ^= 8;
	lbl_8042C110->flags ^= 8;
	lbl_8042C114->flags ^= 8;
	lbl_8042C118->flags ^= 8;
	lbl_8042C11C->flags ^= 8;
}

void TMainTask::ContinueChild()
{
	lbl_8042C104->flags &= ~8;
	lbl_8042C108->flags &= ~8;
	lbl_8042C10C->flags &= ~8;
	lbl_8042C110->flags &= ~8;
	lbl_8042C114->flags &= ~8;
	lbl_8042C118->flags &= ~8;
	lbl_8042C11C->flags &= ~8;
}

void TMainTask::Debug()
{
	fn_8005751C();
	fn_80057574();
}

#define PROFILE_WRAPPER(name, trigger, mask, previous, flag, callback, offset)                     \
	void TMainTask::name()                                                                         \
	{                                                                                              \
		TObject* object = (TObject*)this;                                                          \
		u64 start       = OSGetTime();                                                             \
		if (trigger != previous) {                                                                 \
			TObject* cursor = (TObject*)MainTask.child;                                            \
			u32 bit         = 1;                                                                   \
			while (cursor != 0) {                                                                  \
				if (mask & bit)                                                                    \
					cursor->flags |= flag;                                                         \
				else                                                                               \
					cursor->flags &= ~flag;                                                        \
				cursor = (TObject*)cursor->next;                                                   \
				bit <<= 1;                                                                         \
			}                                                                                      \
			previous = trigger;                                                                    \
		}                                                                                          \
		callback(object);                                                                          \
		u64 end                       = OSGetTime();                                               \
		*(u16*)((u8*)object + offset) = (u16)((((u32)end - (u32)start) * 8)                        \
		    / (((*(volatile u32*)0x800000F8) >> 2) / 125000));                                     \
	}

PROFILE_WRAPPER(ImmAftSetRaster, lbl_8042C13C, lbl_8042C134, lbl_8042C140, 0x10, fn_80017878, 0x20)
PROFILE_WRAPPER(TDisp, lbl_8042C134, lbl_8042C134, lbl_8042C138, 0x10, fn_80017AEC, 0x20)
PROFILE_WRAPPER(PDisp, lbl_8042C134, lbl_8042C134, lbl_8042C138, 0x10, fn_80017DF0, 0x22)
PROFILE_WRAPPER(Disp, lbl_8042C134, lbl_8042C134, lbl_8042C138, 0x10, fn_80018064, 0x1E)
PROFILE_WRAPPER(Exec, lbl_8042C12C, lbl_8042C12C, lbl_8042C130, 8, fn_80018368, 0x1C)

static inline void destroyAndClear(TObject*& object)
{
	delete object;
	object = 0;
}

void TMainTask::Finalize()
{
	destroyAndClear(lbl_8042C0F8);
	destroyAndClear(lbl_8042C0FC);
	destroyAndClear(lbl_8042C100);
	destroyAndClear(lbl_8042C104);
	destroyAndClear(lbl_8042C108);
	destroyAndClear(lbl_8042C10C);
	destroyAndClear(lbl_8042C110);
	destroyAndClear(lbl_8042C114);
	destroyAndClear(lbl_8042C118);
	destroyAndClear(lbl_8042C11C);
	destroyAndClear(lbl_8042C120);
	fn_80018AB0(lbl_8042C148, 1);
	lbl_8042C148 = 0;
}

static inline TObject* makeRoot(TObject* parent)
{
	TObject* object = (TObject*)fn_80018A34(lbl_8042C148, 40);
	if (object != 0) {
		*(void**)((u8*)object + 0x18) = __vt__7TObject;
		object->flags                 = 0;
		object->field1C               = 0;
		object->field1E               = 0;
		object->field20               = 0;
		object->field24               = 0;
		object->parent                = parent;
		object->child                 = 0;
		*(void**)&object->kind        = lbl_8042ADA0;
		object->field1E               = 40;
		if (parent == 0) {
			object->prev = object;
			object->next = 0;
		} else if (parent->child != 0) {
			TObject* child    = (TObject*)parent->child;
			object->prev      = child->prev;
			object->next      = 0;
			child->prev->next = object;
			child->prev       = object;
		} else {
			object->prev  = object;
			parent->child = object;
			object->next  = 0;
		}
		++lbl_8042C124;
	}
	return object;
}

void TMainTask::Initialize()
{
	THeapCtrl* pool = new THeapCtrl(0x70000, 16);
	lbl_8042C148    = pool;
	TObject* parent = (TObject*)this;

	lbl_8042C0F8                 = makeRoot(parent);
	*(void**)&lbl_8042C0F8->kind = lbl_8042ADB0;
	lbl_8042C0FC                 = makeRoot(parent);
	*(void**)&lbl_8042C0FC->kind = lbl_8042ADBC;
	lbl_8042C100                 = makeRoot(parent);
	*(void**)&lbl_8042C100->kind = lbl_8042ADC8;
	lbl_8042C104                 = makeRoot(parent);
	*(void**)&lbl_8042C104->kind = lbl_8042ADD4;
	lbl_8042C108                 = makeRoot(parent);
	*(void**)&lbl_8042C108->kind = lbl_8042ADE0;
	lbl_8042C10C                 = makeRoot(parent);
	*(void**)&lbl_8042C10C->kind = lbl_8042ADEC;
	lbl_8042C110                 = makeRoot(parent);
	*(void**)&lbl_8042C110->kind = lbl_8042ADF8;
	lbl_8042C114                 = makeRoot(parent);
	*(void**)&lbl_8042C114->kind = lbl_8042AE04;
	lbl_8042C118                 = makeRoot(parent);
	*(void**)&lbl_8042C118->kind = lbl_8042AE10;
	lbl_8042C11C                 = makeRoot(parent);
	*(void**)&lbl_8042C11C->kind = lbl_8042AE14;
	lbl_8042C120                 = makeRoot(parent);
	*(void**)&lbl_8042C120->kind = lbl_8042AE18;
}

void TObject::DeleteChild()
{
	while (child != 0)
		delete (TObject*)child;
}

void TObject::operator delete(void* object)
{
	lbl_8042C148->Free(object);
}

TObject::~TObject()
{
	if (flags & 0x20) {
		for (;;) {
		}
	}
	flags |= 0x20;
	DeleteChild();

	if (parent != 0) {
		if (prev == this) {
			parent->child = 0;
		} else if (parent->child == this) {
			parent->child = next;
			prev->next    = 0;
			if (next != 0)
				next->prev = prev;
		} else {
			prev->next = next;
			if (next != 0)
				next->prev = prev;
			else
				parent->child->prev = prev;
		}
	}
	--lbl_8042C124;
}

TMainTask::~TMainTask()
{
	DeleteChild();
	fn_80018AB0(lbl_8042C148, 1);
}

int TObject::CheckAlive()
{
	TObject* object = this;
	while (object) {
		if (object->flags & 1)
			return 0;
		object = (TObject*)object->parent;
	}
	return 1;
}

int TObject::GetChildCount()
{
	int count       = 0;
	TObject* object = (TObject*)child;
	while (object) {
		++count;
		object = (TObject*)object->next;
	}
	return count;
}

void TObject::Error(char* message)
{
	fn_80057520(message);
}

void TObject::ImmAftSetRasterChild()
{
	++lbl_8042C128;
	TObject* object = (TObject*)child;
	while (object) {
		object->ImmAftSetRaster();
		object->ImmAftSetRasterChild();
		object = (TObject*)object->next;
	}
	--lbl_8042C128;
}

void TObject::TDispChild()
{
	++lbl_8042C128;
	TObject* object = (TObject*)child;
	while (object) {
		if (!(object->flags & 0x10)) {
			object->TDisp();
			object->TDispChild();
		}
		object = (TObject*)object->next;
	}
	--lbl_8042C128;
}

void TObject::PDispChild()
{
	++lbl_8042C128;
	TObject* object = (TObject*)child;
	while (object != 0) {
		object->PDisp();
		object->PDispChild();
		object = (TObject*)object->next;
	}
	--lbl_8042C128;
}

void TObject::DispChild()
{
	++lbl_8042C128;
	TObject* object = (TObject*)child;
	while (object != 0) {
		if (!(object->flags & 0x10)) {
			object->Disp();
			object->DispChild();
		}
		object = (TObject*)object->next;
	}
	--lbl_8042C128;
}

#pragma dont_inline on
void TObject::ExecChild()
{
	++lbl_8042C128;
	TObject* cobj = (TObject*)child;
	while (child != 0 && cobj != 0) {
		TObject* object = cobj;
		cobj            = (TObject*)cobj->next;
		if ((object->flags & 0xF) != 0) {
			if (object->flags & 1) {
				object->flags &= ~1;
				if (!(object->flags & 0x20)) {
					delete object;
					continue;
				}
			}
			if (object->flags & 2) {
				while (object->child != 0)
					delete (TObject*)object->child;
				object->Exec();
				object->flags &= ~2;
			}
			if (object->flags & 4)
				continue;
			if (object->flags & 8)
				continue;
		} else {
			object->Exec();
			object->ExecChild();
		}
	}
	--lbl_8042C128;
}
#pragma dont_inline reset

#pragma defer_codegen on
void TObject::Kill()
{
	flags |= 1;
}
#pragma defer_codegen reset

void TObject::KillChild()
{
	TObject* object = (TObject*)child;
	while (object != 0) {
		((TObject*)child)->Kill();
		((TObject*)child)->KillChild();
		object = (TObject*)object->next;
	}
}

TObject::TObject(TObject* parent)
{
	flags          = 0;
	field1C        = 0;
	field1E        = 0;
	field20        = 0;
	field24        = 0;
	this->parent   = parent;
	child          = 0;
	*(void**)&kind = lbl_8042ADA0;
	field1E        = 40;
	if (parent == 0) {
		prev = this;
		next = 0;
	} else if (parent->child != 0) {
		TObject* first    = (TObject*)parent->child;
		prev              = first->prev;
		next              = 0;
		first->prev->next = this;
		first->prev       = this;
	} else {
		prev          = this;
		parent->child = this;
		next          = 0;
	}
	++lbl_8042C124;
}

inline TMainTask::TMainTask()
    : TObject(0)
{
	*(char**)&kind = CL_TMainTask;
	field1E        = sizeof(TMainTask);
}

TMainTask MainTask;

void TObject::Exec() { }
void TObject::Disp() { }
void TObject::TDisp() { }
void TObject::PDisp() { }

void TObject::ImmAftSetRaster() { }
void TObject::Debug() { }
void TObject::Render() { }
