#include "types.h"

// The retained PS2 o_sample2.cpp marker identifies this as the complete
// TObjSample2 translation unit. Its constructor, destructor, Disp, Exec,
// vtable, class pointer, parameter record, and static initializer names agree
// with the relationships in the GameCube block.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
};

struct Frame {
	Vec3 position;
	Rot3 rotation;
};

struct TObject {
	char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;
	void** vtable;
	s16 field1C;
	s16 objectSize;
	s16 field20;
	s16 field22;
	s16 field24;
	s16 field26;
};

struct TMotion {
	Frame* frame;
	void** vtable;
};

class TObjSample2
{
public:
	TObject object;
	TMotion motion;
	Vec3 position;
	Rot3 rotation;

	TObjSample2(TObject* owner);
	~TObjSample2();

	void Disp();
	void Exec();

	static void operator delete(void* object);
};

struct SETOBJ_PARAM {
	u8 data[0x30];
};

extern "C" {
void copyVec3(Vec3* destination, const Vec3* source);
void markSampleForDeletion(TObject* object);
void* __nw__10TObjSampleFUl(u32 size);
void setupObjClass(SETOBJ_PARAM* param, char* name, void (*load)(), void (*unload)(),
    void (*create)(), void (*reset)(SETOBJ_PARAM*), u32 flags, u32 field18, u32 field20,
    u32 objectId, u32 field1E, u32 field21, void* fieldTypes, void* fieldNames);
void fn_8005B8B8();
s32 fn_8005B8BC(TMotion* motion);
s32 fn_8005B8D8(TMotion* motion);
s32 fn_8005B9F0(TMotion* motion);
void dtor_8005BD3C(TMotion* motion, s16 flags);
void fn_8005BE6C(TMotion* motion);
void fn_800D72C0(const Vec3* first, const Vec3* second, Vec3* result);
void __ct__7TObjectFP7TObject(TObject* object, TObject* owner);
void __dt__7TObjectFv(TObject* object, s16 flags);

void sampleHook0();
void sampleHook1();
void sampleHook2();
void sampleHook3();
void sampleHook4();
void Error__7TObjectFPc();
extern TObject* lbl_8042C110;
extern Vec3* lbl_8042C208;

TObjSample2* __ct__11TObjSample2FP7TObject(TObjSample2* object, TObject* owner);
TObjSample2* __dt__11TObjSample2Fv(TObjSample2* object, s16 flags);
void Disp__11TObjSample2Fv(TObjSample2* object);
void Exec__11TObjSample2Fv(TObjSample2* object);
void fn_16_900(Rot3* destination, const Rot3* source);
}

char TObjSample2ClassName[] = "TObjSample2";
char* CL_TObjSample2        = TObjSample2ClassName;

void* __vt__11TObjSample2[] = {
	0,
	0,
	(void*)__dt__11TObjSample2Fv,
	(void*)Exec__11TObjSample2Fv,
	(void*)Disp__11TObjSample2Fv,
	(void*)sampleHook0,
	(void*)sampleHook1,
	(void*)sampleHook2,
	(void*)sampleHook3,
	(void*)Error__7TObjectFPc,
	(void*)sampleHook4,
	0,
	0,
	(void*)fn_8005B8B8,
};

char TObjSample2DisplayName[16] = "SAMPLE2 OBJECT";

SETOBJ_PARAM ObjSample2Param;

void TObjSample2::Disp() { }

void TObjSample2::Exec()
{
	Vec3 delta;

	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		markSampleForDeletion(&object);
		return;
	}

	if (fn_8005B8D8(&motion) != 0) {
		copyVec3(&position, &motion.frame->position);
		return;
	}

	rotation.y += 0x38E;
	fn_800D72C0(lbl_8042C208, &motion.frame->position, &delta);
}

TObjSample2::~TObjSample2()
{
	object.vtable = __vt__11TObjSample2;
	motion.vtable = __vt__11TObjSample2 + 11;
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(&object, 0);
}

TObjSample2::TObjSample2(TObject* owner)
{
	__ct__7TObjectFP7TObject(&object, owner);
	fn_8005BE6C(&motion);
	object.vtable     = __vt__11TObjSample2;
	motion.vtable     = __vt__11TObjSample2 + 11;
	object.className  = CL_TObjSample2;
	object.objectSize = sizeof(TObjSample2);
	copyVec3(&position, &motion.frame->position);
	fn_16_900(&rotation, &motion.frame->rotation);
}

extern "C" void fn_16_900(Rot3* destination, const Rot3* source)
{
	destination->x = source->x;
	destination->y = source->y;
	destination->z = source->z;
}

static void startObjSample2()
{
	TObjSample2* object = (TObjSample2*)__nw__10TObjSampleFUl(sizeof(TObjSample2));
	if (object != 0) {
		object = __ct__11TObjSample2FP7TObject(object, lbl_8042C110);
	}
}

static void registerObjSample2()
{
	setupObjClass(&ObjSample2Param, TObjSample2DisplayName, 0, 0, startObjSample2, 0, 0, 0, 0x1E,
	    0xFFFE, 6, 0, 0, 0);
}

__declspec(section ".ctors") void (*const TObjSample2CtorEntry)() = registerObjSample2;
