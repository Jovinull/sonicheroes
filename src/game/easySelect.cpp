#include "types.h"

extern "C" void* __ct__7TObjectFP7TObject(void*, void*);
extern "C" void* fn_80018A34(void*, u32);
extern "C" void* lbl_8042C148;

struct TObject {
	u8 pad00[4];
	u16 flags;
	u8 pad06[0x12];
	static void* operator new(unsigned long size) { return fn_80018A34(lbl_8042C148, size); }
	static void operator delete(void*);

	TObject(TObject* parent) { __ct__7TObjectFP7TObject(this, parent); }
	~TObject();
};

struct ConstructedChild : TObject {
	u8 pad18[0x10];

	ConstructedChild(TObject* parent)
	    : TObject(parent)
	{
	}
};

struct EasySelect;
typedef void (*ChangeMode)(EasySelect*, s32);
typedef void (*Draw)(EasySelect*);

struct EasyVTable {
	void* slots[11];
	ChangeMode changeMode;
	Draw draw;
};

struct EasyCallBase {
	u8 pad00[0x18];
};

struct EasyCall : EasyCallBase {
	virtual ~EasyCall();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8(s32);
	virtual void slot9();
};

enum InputResult {
	INPUT_NONE    = 0,
	INPUT_CONFIRM = 1,
	INPUT_CANCEL  = 2,
	INPUT_OTHER   = 3,
};

struct UserInterface {
	InputResult inputResult();
	void cancel();
};

struct EasySelect : TObject {
	EasyVTable* vtable;
	u8 pad1C[0xC];
	s32 previousMode;
	s32 mode;
	s32 nextMode;
	f32 frame;
	void* animation;
	void* field3C;
	int field40;
	int field44;
	int field48;
	void* child;
	void* field50;
	s32 field54;
	s32 field58;
	u8 pad5C[4];
	s32 field60;
	s32 field64;
	s32 field68;
	s32 field6C;
	s32 field70;
	s32 field74;
	s32 timer;
	u8 alpha;

	EasySelect(TObject*);
};

struct SelectionCallback;
typedef void* (*CreateSelection)(EasySelect*, s32*, SelectionCallback*);

struct SelectionCallback {
	void* unused;
	CreateSelection create;
};

struct SelectionState {
	u8 pad00[0xC];
	int stage;
	int previousStage;
	u8 pad14[0x34];
	SelectionCallback* callback;
	u8 pad4C[0xC];
	u32 flags;
	int character;
	int team;
	u8 selectedStage;
};

struct MainState {
	u8 pad00[0x13];
	s8 character;
	s8 team;
};

struct DisplayState {
	u8 pad00[4];
	s32 width;
	s32 height;
};

struct ScreenVertex {
	f32 x;
	f32 y;
	f32 z;
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
	f32 u;
	f32 v;
};

struct Animation {
	u8 pad00[8];
	struct Key {
		u8 pad00[4];
		f32 frame;
	}* keys;
};

struct AnimationRange {
	s32 frame;
	s32 start;
	s32 end;
};

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct EasySelectCollision {
	u8 pad00[0x4C];
	Vec3 position;
	u32 flags;
};

extern "C" {
extern void* lbl_8042C148;
extern MainState* lbl_8042C180;
extern SelectionState lbl_80303EC8;
extern DisplayState RsGlobal;

void fn_8012CC20(void*);
void* __ct__7TObjectFP7TObject(void*, void*);
void* fn_80018A34(void*, u32);
void* __dt__7TObjectFv(void*, s32);
void fn_800189A4(void*, void*);
void* fn_8011EFB0(void*);
void fn_80194294(s32, u32*);
void fn_80194234(s32, u32);
void fn_8019421C();
void fn_800A7658();
void fn_801942C0(s32, ScreenVertex*, s32);
void fn_8001867C(void*);
void fn_8012CEF0(void*, f32);
s32 fn_8013B76C(void*);
void fn_80110C7C(UserInterface*);
void fn_80204144(void*, void*, s32);
void fn_8020139C(void*, s32);
void* fn_80041FF4();
s32 fn_80192F38(void*, s32, s32, s32);
void* fn_80203B74(s32, void*);
void fn_80197ED8(void*, s32);
void fn_80018368(void*);
void fn_80016BBC(void*);
void fn_80159798(void*);
void* fn_80159920(void*);
void* fn_8011F17C(void*);
void fn_8011EF2C(void*, void*);
u32 repCheck(void*, u16, s32, s32);
void fn_8020577C();
void fn_8016F084();
void fn_8016EF70();
void fn_80205624();
void fn_8016EE28(f32);
void* RsPathnameCreate(void*);
void fn_8016E054();
void RsPathnameDestroy(void*);
void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(void*);
void fn_8019CF28(void*, void*, s32);
void RsCameraShowRaster();
void fn_8019EB94(void*, const void*, s32);
void* fn_8019CC28();
void fn_801AFFB0(s32, s32, s32, s32, s32);
void fn_801AF914(s32);
void fn_80018064(void*);
void fn_801115A0(void*);
void fn_8019CC00();
void fn_80017DF0(void*);
void fn_80017AEC(void*);
void fn_80177C50();
void fn_801AD3C0(void*, s32);
f32 GXGetYScaleFactor(u16, u16);
void GXSetDispCopyYScale(f32);
void fn_800A7614();
void fn_8016EBC0(f32*, f32*, f32*);
void* fn_802043AC(void*);
void* fn_80204918(void*);
void fn_80173614(void*, s32);
void fn_8017349C(void*, f32, f32);
struct RenderCamera;
void fn_801734F4(RenderCamera*, f32, f32);
void fn_8017442C(void*);
void fn_802043B4(void*, f32);
void fn_802041EC(void*);
void fn_802033F4(void*);
extern void* lbl_8042C34C;
extern u8 lbl_8029C2E4[];
extern u8 lbl_8042B330;
extern u8 lbl_80253118[];
extern u8 lbl_80239F50[];
struct GXRenderModeObj {
	u8 pad00[6];
	u16 field06;
	u16 field08;
};
extern GXRenderModeObj GXNtsc480Prog;
extern GXRenderModeObj GXEurgb60Hz480IntDf;
extern UserInterface* lbl_8042C610;
extern u8 lbl_8029BBD0[];
extern int lbl_802408F8[];
extern u32 lbl_8042CFA0;
extern u32 lbl_8042CFA4;
extern u32 lbl_8042CFA8;
extern u8 lbl_8042C0C0;

void fn_80018984();
void fn_80018988();
void fn_80018950();
void fn_80018954();
void Error__7TObjectFPc();
void fn_80018958();

void fn_800A8290(EasySelect*);
void fn_800A8264(EasySelect*);
EasySelect* fn_800A8620(EasySelect*, s16);

EasySelect* lbl_8042C348;

EasyVTable lbl_80253124 = { {
	                            NULL,
	                            NULL,
	                            (void*)fn_800A8620,
	                            (void*)fn_800A8290,
	                            (void*)fn_800A8264,
	                            (void*)fn_80018984,
	                            (void*)fn_80018988,
	                            (void*)fn_80018950,
	                            (void*)fn_80018954,
	                            (void*)Error__7TObjectFPc,
	                            (void*)fn_80018958,
	                        },
	NULL, NULL };
}

#pragma force_active on
extern volatile const u32 lbl_8042DB48 = 0xFF;
extern volatile const f32 lbl_8042DB4C = 1.0f;
extern volatile const f32 lbl_8042DB50 = 0.0f;

inline void setCameraOffset(RenderCamera* camera, f32 width, f32* xValues, f32 scaleX, u8* raster,
    f32 height, f32* yValues, f32 scaleY)
{
	f32 xOffset;
	f32 half;
	xOffset = width * xValues[0] / scaleX - *(f32*)(raster + 8);
	half    = 0.5f;
	fn_801734F4(camera, xOffset * half,
	    *(f32*)(raster + 0xC) + (height * yValues[1] / scaleY - *(f32*)(raster + 0xC)) / 2.0f);
}

#pragma force_active reset

inline int getActivePort()
{
	return -1;
}

inline int valuesDiffer(int left, int right)
{
	return ((unsigned int)((left - right) | (right - left))) >> 31;
}

inline int selectionValuesDiffer(int left, int right)
{
	return left != right;
}

inline EasySelect* callObject(EasySelect* self)
{
	return self;
}

#pragma opt_propagation off
#pragma opt_dead_code off
#pragma opt_lifetimes off
#pragma opt_propagation on
inline InputResult UserInterface::inputResult()
{
	int index = getActivePort();
	if (index == -1)
		index = 0;
	u8* rows        = lbl_8029BBD0;
	int mapOffset   = index * sizeof(int);
	int* mapping    = lbl_802408F8;
	int mappedIndex = *(int*)((u8*)mapping + mapOffset);
	u8* row         = rows + mappedIndex * 0x4C;
	u32 buttons     = *(u32*)(row + 0x50);
	InputResult result;
	if ((buttons & lbl_8042CFA4) != 0)
		result = INPUT_CONFIRM;
	else if ((buttons & lbl_8042CFA0) != 0)
		result = INPUT_CANCEL;
	else if ((buttons & lbl_8042CFA8) != 0)
		result = INPUT_OTHER;
	else
		result = INPUT_NONE;
	return result;
}

inline void UserInterface::cancel()
{
	fn_80110C7C(this);
}
#pragma opt_propagation off

inline void executeController(EasySelect* self)
{
	if (self->field50 != NULL) {
		UserInterface* userInterface;
		if (fn_8013B76C(self->field50) == 0 && (userInterface = lbl_8042C610) != NULL) {
			InputResult result = userInterface->inputResult();
			switch (result) {
				case 0:
				case 1:
					break;
				case 2:
					userInterface->cancel();
					break;
				case 3:
					break;
			}
		} else {
			self->mode = self->field54;
		}
	} else {
		self->mode = self->field54;
	}
}
#pragma opt_propagation on
#pragma opt_dead_code on
#pragma opt_lifetimes reset

extern "C" void fn_800A80E0(EasySelect* self, AnimationRange* ranges, s32 index)
{
	Animation* animation = (Animation*)self->animation;
	if (animation == NULL)
		return;
	Animation::Key* keys = animation->keys;
	s32 frame            = ranges[index].frame;
	self->frame          = keys[frame].frame;
	self->field70        = ranges[index].start;
	self->field74        = ranges[index].end;
}

extern "C" void fn_800A8120(EasySelect* self)
{
	if (self->animation == NULL)
		return;
	self->frame += *(volatile const f32*)&lbl_8042DB4C;
	Animation* animation = (Animation*)self->animation;
	if (animation->keys[self->field74].frame < self->frame)
		self->frame = animation->keys[self->field70].frame;
}

extern "C" void fn_800A8174(EasySelect* self, s32 value)
{
	if (value < 0)
		return;
	self->field58 = value;
	self->field54 = self->previousMode;
	self->mode    = 4;
}

extern "C" void fn_800A8194(EasySelect* self)
{
	if (self->animation == NULL)
		return;
	f32 frame   = *(volatile f32*)&self->frame;
	f32 one     = *(volatile const f32*)&lbl_8042DB4C;
	self->frame = frame + one;
	s32 finished;
	switch (self->field6C) {
		case 1: {
			Animation* animation = (Animation*)self->animation;
			finished             = animation->keys[self->field68].frame <= one + self->frame;
			break;
		}
		default: {
			Animation* animation = (Animation*)self->animation;
			finished             = animation->keys[self->field68].frame <= self->frame;
			break;
		}
	}
	if (finished) {
		self->mode    = self->field60;
		self->field6C = 0;
	}
}

extern "C" void fn_800A823C(EasySelect* self)
{
	if (self->animation == NULL)
		return;
	Animation* animation = (Animation*)self->animation;
	self->frame          = animation->keys[self->field64].frame;
}

extern "C" void fn_800A8264(EasySelect* self)
{
	if (self->animation != NULL)
		fn_8012CC20(self->animation);
}

#pragma opt_dead_code off
#pragma opt_propagation off
extern "C" void fn_800A8290(EasySelect* self)
{
	if (self->mode != self->previousMode) {
		self->previousMode = self->mode;

		if (self->child != NULL)
			fn_8001867C(self->child);

		if (self->field50 != NULL) {
			*(u16*)((u8*)self->field50 + 4) |= 1;
			self->field50 = NULL;
		}

		((EasyCall*)self)->slot8(self->mode);

		switch (self->mode) {
			case 1:
				if (self->animation != NULL) {
					Animation* animation = (Animation*)self->animation;
					self->frame          = animation->keys[self->field64].frame;
				}
				break;
			case 4:
				void* created;
				SelectionCallback* callback = lbl_80303EC8.callback;
				if (callback != NULL) {
					created = callback->create(self, &self->field58, callback);
				} else {
					created = NULL;
				}
				self->field50 = created;
				break;
			case 3:
				self->alpha = 0xFF;
				break;
		}
	}

	switch (self->previousMode) {
		case 0:
			break;
		case 1:
			if (self->animation != NULL) {
				f32 frame   = self->frame;
				f32 one     = *(volatile const f32*)&lbl_8042DB4C;
				self->frame = frame + one;
				s32 finished;
				switch (self->field6C) {
					case 1: {
						Animation* animation = (Animation*)self->animation;
						finished = animation->keys[self->field68].frame <= one + self->frame;
						break;
					}
					default: {
						Animation* animation = (Animation*)self->animation;
						finished             = animation->keys[self->field68].frame <= self->frame;
						break;
					}
				}
				if (finished) {
					self->mode    = self->field60;
					self->field6C = 0;
				}
			}
			break;
		case 3:
			if (self->timer <= 0) {
				s32 alpha = self->alpha;
				alpha -= 8;
				if (alpha > 0) {
					self->alpha = alpha;
				} else {
					self->alpha = 0;
					self->mode  = 2;
				}
				lbl_80303EC8.selectedStage = self->alpha;
				lbl_80303EC8.flags |= 0x200;
			} else {
				self->timer--;
			}
			break;
		case 2:
			if (self->alpha != 0xFF) {
				lbl_80303EC8.selectedStage = self->alpha;
				lbl_80303EC8.flags |= 0x200;
			}
			self->flags |= 1;
			return;
		case 4:
			executeController(self);
			break;
	}

	{
		((EasyCall*)self)->slot9();
	}
	if (self->animation != NULL)
		fn_8012CEF0(self->animation, self->frame);
done:;
}
#pragma opt_propagation reset
#pragma opt_dead_code reset

#pragma opt_propagation off
#pragma opt_lifetimes off
inline void updateSelection(int stage)
{
	lbl_80303EC8.previousStage = lbl_80303EC8.stage;
	lbl_80303EC8.stage         = stage;
	if (stage == 13)
		lbl_80303EC8.flags |= 0x20;
	if (stage == 9)
		lbl_80303EC8.flags |= 0x20;
	if (lbl_80303EC8.previousStage != 3 && lbl_80303EC8.previousStage != 8)
		return;
	int difference;
	const SelectionState* selection = &lbl_80303EC8;
	difference = selectionValuesDiffer(selection->character, lbl_8042C180->character);
	if (difference == 0)
		difference = selectionValuesDiffer(selection->team, lbl_8042C180->team);
	if (difference != 0)
		lbl_80303EC8.flags |= 0x10;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

extern "C" EasySelect* fn_800A8620(EasySelect* self, s16 shouldDelete)
{
	if (self != NULL) {
		self->vtable = &lbl_80253124;
		if (self->field48 == 0)
			updateSelection(self->field44);
		else
			updateSelection(self->field40);
		__dt__7TObjectFv(self, 0);
		if (shouldDelete > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

EasySelect::EasySelect(TObject* parent)
    : TObject(parent)
{
	vtable       = &lbl_80253124;
	previousMode = 0;
	mode         = 0;
	nextMode     = 0;
	frame        = *(volatile const f32*)&lbl_8042DB50;
	animation    = NULL;
	field3C      = NULL;
	field48      = 1;
	field40      = 15;
	field44      = 15;
	field60      = 0;
	field64      = 0;
	field68      = 0;
	field6C      = 0;

	child   = new ConstructedChild(this);
	field50 = NULL;
	field54 = 0;
	field58 = 0;
	alpha   = 0xFF;
	timer   = 0;
}

extern "C" void fn_800A88F0(void*, s32 alpha)
{
	if ((u8)alpha == 0)
		return;

	f32 half = 0.5f;
	u32 state8;
	u32 state6;
	u32 state7;
	u32 state9;
	u32 state12;
	u32 state20;
	u32 state3;
	u32 state4;
	u32 state14;
	u32 state10;
	u32 state11;
	fn_80194294(8, &state8);
	fn_80194294(6, &state6);
	fn_80194294(7, &state7);
	fn_80194294(9, &state9);
	fn_80194294(12, &state12);
	fn_80194294(20, &state20);
	fn_80194294(3, &state3);
	fn_80194294(4, &state4);
	fn_80194294(14, &state14);
	fn_80194294(10, &state10);
	fn_80194294(11, &state11);

	fn_80194234(8, 0);
	fn_80194234(6, 0);
	fn_80194234(7, 2);
	fn_80194234(9, 2);
	fn_80194234(12, 1);
	fn_80194234(20, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(14, 0);
	fn_80194234(10, 5);
	fn_80194234(11, 6);
	fn_80194234(1, 0);

	f32 width  = RsGlobal.width;
	f32 height = RsGlobal.height;
	fn_8019421C();
	fn_800A7658();

	ScreenVertex vertices[4];
	f32 zero      = *(volatile const f32*)&lbl_8042DB50;
	vertices[0].x = zero;
	vertices[0].y = zero;
	vertices[1].x = zero;
	vertices[1].y = height;
	vertices[2].x = width;
	vertices[2].y = zero;
	vertices[3].x = width;
	vertices[3].y = height;

	vertices[0].red   = 0;
	vertices[0].green = 0;
	vertices[0].blue  = 0;
	u8 drawAlpha      = 0xFF - (u8)alpha;
	vertices[0].alpha = drawAlpha;
	vertices[0].z     = half;
	vertices[1].red   = 0;
	vertices[1].green = 0;
	vertices[1].blue  = 0;
	vertices[1].alpha = drawAlpha;
	vertices[1].z     = half;
	vertices[2].red   = 0;
	vertices[2].green = 0;
	vertices[2].blue  = 0;
	vertices[2].alpha = drawAlpha;
	vertices[2].z     = half;
	vertices[3].red   = 0;
	vertices[3].green = 0;
	vertices[3].blue  = 0;
	vertices[3].alpha = drawAlpha;
	vertices[3].z     = half;
	fn_801942C0(4, vertices, 4);

	fn_80194234(8, state8);
	fn_80194234(6, state6);
	fn_80194234(7, state7);
	fn_80194234(9, state9);
	fn_80194234(12, state12);
	fn_80194234(20, state20);
	fn_80194234(3, state3);
	fn_80194234(4, state4);
	fn_80194234(14, state14);
	fn_80194234(10, state10);
	fn_80194234(11, state11);
}

extern "C" s32 fn_800A8BBC(EasySelect* self)
{
	if (self->animation == NULL)
		return 0;
	return (s32)fn_8011EFB0(self->animation);
}

extern "C" void* fn_800A8BF0(void* self)
{
	return (u8*)self + 0xC;
}

extern "C" EasySelect* fn_800A8BF8()
{
	return lbl_8042C348;
}

extern "C" void fn_800A8C00(EasySelect*, EasySelect* value)
{
	lbl_8042C348 = value;
}

extern "C" void fn_800A8C08(EasySelectCollision*) { }

extern "C" s32 fn_800A8C0C(EasySelectCollision* self)
{
#pragma cplusplus off
	return (self->flags & 3) == 0;
#pragma cplusplus reset
}

extern "C" void fn_800A8C20(EasySelectCollision* self)
{
	lbl_8042C0C0 = 0;
	self->flags |= 4;
}

extern "C" void fn_800A8C38(EasySelectCollision* self)
{
	lbl_8042C0C0 = 1;
	self->flags |= 4;
}

extern "C" void fn_800A8C50(EasySelectCollision* self, s32 enabled)
{
	if (enabled != 0)
		self->flags |= 0x400;
	else
		self->flags &= ~0x400;
}

extern "C" void fn_800A8C78(EasySelectCollision*) { }

extern "C" void fn_800A8C7C(EasySelectCollision* self)
{
	self->flags |= 2;
}

extern "C" void fn_800A8C8C(EasySelectCollision* self)
{
	self->flags |= 1;
}

#pragma dont_inline on
extern "C" void fn_800A8C9C(EasySelectCollision* self, const Vec3* position)
{
	self->position.x = position->x;
	self->position.y = position->y;
	self->position.z = position->z;
}
#pragma dont_inline reset

extern "C" void* fn_800A8CEC(void*, void*);

extern "C" void fn_800A8CB8(void* value)
{
	if (value != NULL)
		fn_80204144(value, (void*)fn_800A8CEC, 0);
}

extern "C" void* fn_800A8CEC(void* result, void* value)
{
	fn_8020139C(value, 1);
	return result;
}

extern "C" void fn_800A8D24(void* object)
{
	if (object == NULL)
		return;

	f32 values2[2];
	f32 values1[2];
	f32 values0[2];
	fn_8016EBC0(values2, values1, values0);
	RenderCamera* camera = (RenderCamera*)fn_802043AC(object);
	u8* raster           = (u8*)fn_80204918(object);
	f32 scaleY;
	f32 scaleX;
	f32 height = RsGlobal.height;
	f32 width  = RsGlobal.width;
	scaleY     = (height * values1[1] + height * values1[0]) / *(f32*)(raster + 0xC);
	scaleX     = (width * values2[0] + width * values2[1]) / *(f32*)(raster + 8);
	fn_80173614(camera, 1);
	fn_8017349C(camera, scaleX, scaleY);
	setCameraOffset(camera, width, values2, scaleX, raster, height, values1, scaleY);
	fn_8017442C(camera);
	fn_802043B4(object, *(volatile const f32*)&lbl_8042DB50);
	fn_802041EC(object);
	fn_802033F4(object);
}
extern "C" void fn_800A8EC4(void* object)
{
	if (*(void**)((u8*)&lbl_80303EC8 + 0x38) == NULL) {
		fn_800A7658();
		if (object == NULL)
			return;

		f32 values2[2];
		f32 values1[2];
		f32 values0[2];
		fn_8016EBC0(values0, values1, values2);
		RenderCamera* camera = (RenderCamera*)fn_802043AC(object);
		u8* raster           = (u8*)fn_80204918(object);
		f32 height           = RsGlobal.height;
		f32 width            = RsGlobal.width;
		f32 scaleX;
		f32 scaleY;
		scaleY   = (height * values1[1] + height * values1[0]) / *(f32*)(raster + 0xC);
		f32 xSum = width * values0[0] + width * values0[1];
		xSum     = xSum;
		scaleX   = xSum / *(f32*)(raster + 8);
		fn_80173614(camera, 1);
		fn_8017349C(camera, scaleX, scaleY);
		setCameraOffset(camera, width, values0, scaleX, raster, height, values1, scaleY);
		fn_8017442C(camera);
		fn_802043B4(object, *(volatile const f32*)&lbl_8042DB50);
		fn_802041EC(object);
		fn_802033F4(object);
		return;
	}

	fn_8011EFB0(*(void**)((u8*)&lbl_80303EC8 + 0x38));
	if (object == NULL)
		return;

	f32 values2[2];
	f32 values1[2];
	f32 values0[2];
	fn_8016EBC0(values0, values1, values2);
	RenderCamera* camera = (RenderCamera*)fn_802043AC(object);
	u8* raster           = (u8*)fn_80204918(object);
	f32 height           = RsGlobal.height;
	f32 width            = RsGlobal.width;
	f32 scaleX;
	f32 scaleY;
	scaleY = (height * values1[1] + height * values1[0]) / *(f32*)(raster + 0xC);
	scaleX = (width * values0[0] + width * values0[1]) / *(f32*)(raster + 8);
	fn_80173614(camera, 1);
	fn_8017349C(camera, scaleX, scaleY);
	setCameraOffset(camera, width, values0, scaleX, raster, height, values1, scaleY);
	fn_8017442C(camera);
	fn_802043B4(object, *(volatile const f32*)&lbl_8042DB50);
	fn_802041EC(object);
	fn_802033F4(object);
}
extern volatile const f32 lbl_8042DB60 = -80.0f;
extern volatile const f32 lbl_8042DB64 = 5.0f;
extern volatile const f32 lbl_8042DB68 = -100.0f;
extern volatile const f32 lbl_8042DB6C = 100.0f;

extern "C" void* fn_800A91AC()
{
	void* result = NULL;
	void* object = fn_80041FF4();
	if (object != NULL && fn_80192F38(object, 0x1B1, 0, 0) != 0)
		result = fn_80203B74(0, object);
	fn_80197ED8(object, 0);
	return result;
}

extern "C" void fn_800A9224(EasySelectCollision* self)
{
	self->flags |= 0x10;
}

extern "C" Vec3* fn_800A9234(EasySelectCollision* self)
{
	return &self->position;
}

extern "C" void fn_800A96D4(SelectionState*);

extern "C" s32 fn_800A923C()
{
	if (*(void**)((u8*)&lbl_80303EC8 + 0x34) != NULL && lbl_8042C34C != NULL
	    && ((s32 (*)())lbl_8042C34C)() != 0) {
		void* value = *(void**)((u8*)&lbl_80303EC8 + 0x68);
		if (value != NULL)
			fn_80018368(value);
		fn_80016BBC(lbl_8029C2E4);
		*(s32*)((u8*)lbl_8042C180 + 0x30) += 1;
		fn_800A96D4(&lbl_80303EC8);
	}
	return 0;
}

extern "C" void fn_800A92CC(void* self, s32 value1, s32 value2)
{
	*(s32*)((u8*)self + 0x1C) = 1;
	*(s32*)((u8*)self + 0x20) = value1;
	*(s32*)((u8*)self + 0x24) = value2;
}

#pragma opt_propagation off
extern "C" u32 fn_800A92E0(EasySelectCollision* self, s32 buttons, s32 port)
{
	if ((self->flags & 0x800) != 0)
		return 0;
	if (port == -1)
		port = 0;
	if ((buttons & 0x1F00) != 0) {
		u8* rows      = lbl_8029BBD0;
		s32 mapOffset = (u16)port * sizeof(s32);
		s32* mapping  = lbl_802408F8;
		s32 mapped    = *(s32*)((u8*)mapping + mapOffset);
		u8* row       = rows + mapped * 0x4C;
		return *(u32*)(row + 0x50) & (u16)buttons;
	}
	s32 mapped = lbl_802408F8[(u16)port];
	u8* row    = lbl_8029BBD0 + mapped * 0x4C;
	return repCheck(row + 0x48, (u16)buttons, 12, 1);
}

extern "C" s32 fn_800A9398(void*, s32 port)
{
	if (port == -1)
		port = 0;
	u32 buttons   = 0;
	u8* rows      = lbl_8029BBD0;
	s32 mapOffset = port * sizeof(s32);
	s32* mapping  = lbl_802408F8;
	s32 mapped    = *(s32*)((u8*)mapping + mapOffset);
	u8* row       = rows + mapped * 0x4C;
	buttons       = *(u32*)(row + 0x50);
	if ((buttons & lbl_8042CFA4) != 0)
		return 1;
	if ((buttons & lbl_8042CFA0) != 0)
		return 2;
	if ((buttons & lbl_8042CFA8) != 0)
		return 3;
	return 0;
}
#pragma opt_propagation reset

extern "C" void fn_800A9418(void* self, const u32* values)
{
	*(u32*)((u8*)self + 0x40) = values[0];
	*(u32*)((u8*)self + 0x44) = values[1];
	*(u32*)((u8*)self + 0x48) = values[2];
	lbl_8042C34C              = (void*)values[3];
}

extern "C" void* fn_800A943C(void* self)
{
	return *(void**)((u8*)self + 0x34);
}

extern "C" void fn_800A9444(void* self)
{
	EasyCall*& child = *(EasyCall**)((u8*)self + 0x28);
	if (child != NULL) {
		delete child;
		child = NULL;
	}
	EasyCall* created = (EasyCall*)new ConstructedChild(*(TObject**)((u8*)self + 0x68));
	child             = created;
}

extern "C" void fn_800A94C4()
{
	fn_8020577C();
	fn_8016F084();
}

extern "C" void fn_800A94E8(void* self)
{
	fn_8011EFB0(*(void**)((u8*)self + 0x38));
	fn_8016EF70();
	fn_80205624();
	fn_8016EE28(*(volatile const f32*)&lbl_8042DB64);
	void* value = RsPathnameCreate(&lbl_8042B330);
	fn_8016E054();
	RsPathnameDestroy(value);
}

extern "C" void fn_800A953C(void* self)
{
	*(void**)((u8*)self + 0x38) = NULL;
	void*& value                = *(void**)((u8*)self + 0x34);
	if (value != NULL) {
		fn_80159798(value);
		value = NULL;
	}
}

struct EasyRenderState {
	u8 pad00[0x2C];
	void* resource;
	u8 pad30[4];
	void* scene;
	void* animation;
	u8 pad3C[0x10];
	Vec3 position;
};

extern "C" void fn_800A9584(EasyRenderState* self)
{
	f32 values[6];
	f32 minimum     = *(volatile const f32*)&lbl_8042DB68;
	values[5]       = minimum;
	values[4]       = minimum;
	values[3]       = minimum;
	f32 maximum     = *(volatile const f32*)&lbl_8042DB6C;
	values[2]       = maximum;
	values[1]       = maximum;
	values[0]       = maximum;
	self->scene     = fn_80159920(values);
	self->animation = fn_8011F17C(self->resource);
	if (self->animation != NULL)
		fn_8011EF2C(self->animation, self->scene);
	f32 zero         = *(volatile const f32*)&lbl_8042DB50;
	self->position.x = zero;
	self->position.y = zero;
	self->position.z = *(volatile const f32*)&lbl_8042DB60;
}

#pragma opt_propagation off
#pragma opt_lifetimes off
extern "C" void fn_800A960C(SelectionState* self, s32 stage)
{
	self->previousStage = self->stage;
	self->stage         = stage;
	if (stage == 13)
		self->flags |= 0x20;
	if (stage == 9)
		self->flags |= 0x20;
	if (self->previousStage != 3 && self->previousStage != 8)
		return;
	s32 character   = self->character;
	MainState* main = lbl_8042C180;
	s32 difference  = valuesDiffer(main->character, character);
	if (difference == 0)
		difference = valuesDiffer(main->team, self->team);
	if (difference != 0)
		self->flags |= 0x10;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

extern "C" void fn_800A96B0()
{
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180);
}
#pragma dont_inline on
extern "C" void fn_800A96D4(SelectionState* self)
{
	u32 color = *(volatile const u32*)&lbl_8042DB48;
	if (*(void**)((u8*)self + 0x38) == NULL)
		return;
	if (fn_8011EFB0(*(void**)((u8*)self + 0x38)) == NULL)
		return;
	if (*(void**)((u8*)self + 0x68) == NULL)
		return;

	if (self->stage == 15 || self->selectedStage == 0) {
		void* object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
		fn_8019CF28(object, &color, 3);
		fn_8011EFB0(*(void**)((u8*)self + 0x38));
		RsCameraShowRaster();
		return;
	}

	void* object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	fn_8019CF28(object, &color, 3);
	object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (*(void**)((u8*)object + 4) != NULL)
		fn_8019EB94(*(void**)((u8*)object + 4), lbl_80253118, 0);
	fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (fn_8019CC28() != NULL) {
		fn_801AFFB0(7, 0, 0, 7, 0);
		fn_801AF914(1);
		fn_80018064(*(void**)((u8*)self + 0x68));
		u32 state;
		fn_80194294(8, &state);
		fn_80194234(8, 0);
		if (lbl_8042C610 != NULL)
			fn_801115A0(lbl_8042C610);
		fn_80194234(8, state);
		fn_8011EFB0(*(void**)((u8*)self + 0x38));
		fn_8019CC00();
	}

	object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	fn_8019CF28(object, &color, 2);
	object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (*(void**)((u8*)object + 4) != NULL)
		fn_8019EB94(*(void**)((u8*)object + 4), (u8*)self + 0x4C, 0);
	fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (fn_8019CC28() != NULL) {
		fn_801AFFB0(7, 0, 0, 7, 0);
		fn_801AF914(1);
		fn_80017DF0(*(void**)((u8*)self + 0x68));
		fn_8011EFB0(*(void**)((u8*)self + 0x38));
		fn_8019CC00();
	}

	object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	fn_8019CF28(object, &color, 2);
	object = fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (*(void**)((u8*)object + 4) != NULL)
		fn_8019EB94(*(void**)((u8*)object + 4), lbl_80239F50, 0);
	fn_8011EFB0(*(void**)((u8*)self + 0x38));
	if (fn_8019CC28() != NULL) {
		fn_801AFFB0(7, 0, 0, 7, 0);
		fn_801AF914(1);
		fn_80017AEC(*(void**)((u8*)self + 0x68));
		fn_80177C50();
		if ((self->flags & 0x200) != 0)
			fn_800A88F0((EasySelect*)self, self->selectedStage);
		fn_8011EFB0(*(void**)((u8*)self + 0x38));
		fn_8019CC00();
	}

	fn_8011EFB0(*(void**)((u8*)self + 0x38));
	RsCameraShowRaster();
	if ((self->flags & 1) != 0) {
		fn_801AD3C0(&GXNtsc480Prog, 0);
		self->flags &= ~1;
	}
	if ((self->flags & 2) != 0) {
		f32 value = GXGetYScaleFactor(GXEurgb60Hz480IntDf.field06, GXEurgb60Hz480IntDf.field08);
		fn_801AD3C0(&GXEurgb60Hz480IntDf, 0);
		GXSetDispCopyYScale(value);
		self->flags &= ~2;
	}
	if ((self->flags & 4) != 0) {
		fn_800A7614();
		self->flags &= ~4;
	}
	if ((self->flags & 8) != 0)
		self->flags &= ~8;
}
#pragma dont_inline reset
