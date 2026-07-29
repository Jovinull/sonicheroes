#include "types.h"

struct ObjectRecord {
	u32 word00[4];
	u16 half10[2];
	s16 half14[4];
	u32 word1C;
	f32 float20;
	u32 word24;
	f32 float28;

	void copyFrom(const ObjectRecord&);
	void copyTo(ObjectRecord&) const;
};

#pragma options align = packed
struct ControllerRecord {
	f32 float00;
	u32 word04;
	u8 byte08;
	u8 byte09;
	u8 byte0A;
	u8 byte0B;
	u8 byte0C;
	u8 byte0D;

	void copyFrom(const ControllerRecord&);
};
#pragma options align = reset

struct DemoInput {
	ObjectRecord object;
	ControllerRecord controller;
	u8 pad3A[2];
};

struct ObjectSlot {
	ObjectRecord object;
	u8 pad2C[32];
};

struct ObjectPool {
	u8 pad000[528];
	ObjectSlot slots[1];
};

struct ObjectBase {
	u8 pad000[528];
	ObjectRecord object;
};

struct ControllerCopy {
	ControllerRecord controller;
	u8 pad0E[2];
};

struct ControllerSlot {
	ControllerCopy copies[3];
};

struct ControllerPool {
	ControllerSlot slots[1];
};

struct DemoData {
	s32 playerCount;
	s32 frameCount;
	u32 startFrame;
	u32 endFrame;
	u32 currentFrame;
	u8 saveData[112];
	DemoInput inputs[1];
};

struct MainState {
	u8 pad00[0x18];
	s8 mode;
	u8 pad19[0x17];
	u32 frame;
};

struct PlatformAPI {
	u8 pad00[0x134];
	void* (*allocate)(u32);
	void (*free)(void*);
};

extern "C" {
extern MainState* lbl_8042C180;
extern PlatformAPI* lbl_8042C9A4;
extern u8 lbl_8029BBD0[];
extern u8 lbl_802B0310[];
extern u8 lbl_8029C214[];
extern u8 lbl_8029C254[];
extern u8 lbl_8029C294[];
extern u8 lbl_8029C310[];
extern u8 lbl_80303E48[];

#pragma explicit_zero_data
void* lbl_8042AD80[2] = { NULL, NULL };
char lbl_8042AD88[]   = "%s.dmo";
extern char lbl_80240930[];
extern char lbl_80240944[];
extern char lbl_80240960[];
extern char lbl_8024097C[];
extern char lbl_80240994[];
extern char lbl_802409A8[];

int sprintf(char*, const char*, ...);
void* memcpy(void*, const void*, u32);
void* memset(void*, s32, u32);
s32 fn_80042048(const char*, void*);
void fn_80019540(void*);
}

#define DEMO_DATA ((DemoData*)lbl_8042AD80[0])

extern "C" void fn_80014154() { }
extern "C" void fn_80014158() { }

inline void ObjectRecord::copyFrom(const ObjectRecord& source)
{
	word00[0] = source.word00[0];
	word00[1] = source.word00[1];
	word00[2] = source.word00[2];
	word00[3] = source.word00[3];
	half10[0] = source.half10[0];
	half10[1] = source.half10[1];
	half14[0] = source.half14[0];
	half14[1] = source.half14[1];
	half14[2] = source.half14[2];
	half14[3] = source.half14[3];
	word1C    = source.word1C;
	float20   = source.float20;
	word24    = source.word24;
	float28   = source.float28;
}

inline void ObjectRecord::copyTo(ObjectRecord& destination) const
{
	destination.copyFrom(*this);
}

inline void ControllerRecord::copyFrom(const ControllerRecord& source)
{
	float00 = source.float00;
	word04  = source.word04;
	byte08  = source.byte08;
	byte09  = source.byte09;
	byte0A  = source.byte0A;
	byte0B  = source.byte0B;
	byte0C  = source.byte0C;
	byte0D  = source.byte0D;
}

inline void copyObject(ObjectRecord& destination, const ObjectRecord& source)
{
	destination.copyFrom(source);
}

extern "C" void fn_8001415C(void*)
{
	MainState* main = lbl_8042C180;
	u32 frame       = main->frame;
	DemoData* data  = DEMO_DATA;
	if (data == NULL)
		return;
	s32 mode = main->mode;
	s32 i;

	if (mode == 3) {
		if (frame >= (u32)DEMO_DATA->playerCount) {
			sprintf((char*)lbl_8029C214, lbl_80240930);
			sprintf((char*)lbl_8029C254, lbl_80240944, DEMO_DATA->startFrame);
			sprintf((char*)lbl_8029C294, lbl_80240960, DEMO_DATA->endFrame);
			return;
		}
		sprintf((char*)lbl_8029C214, lbl_8024097C, frame, DEMO_DATA->playerCount);
		for (i = 0; i < DEMO_DATA->frameCount; i++) {
			ObjectBase* object         = (ObjectBase*)(lbl_8029BBD0 + i * 76);
			ObjectRecord* objectRecord = &object->object;
			DemoInput* output
			    = (DemoInput*)((u8*)DEMO_DATA + 0x84 + DEMO_DATA->frameCount * frame * 60 + i * 60);
			copyObject(output->object, *objectRecord);
			output->controller.copyFrom(*(ControllerRecord*)(lbl_802B0310 + i * 48));
		}
		DEMO_DATA->currentFrame = frame;
	} else if (mode == 1 || mode == 2) {
		if (mode == 1) {
			if (frame > data->currentFrame) {
				sprintf((char*)lbl_8029C214, lbl_80240994);
				sprintf((char*)lbl_8029C254, lbl_80240944, DEMO_DATA->startFrame);
				sprintf((char*)lbl_8029C294, lbl_80240960, DEMO_DATA->endFrame);
				return;
			}
			sprintf((char*)lbl_8029C214, lbl_802409A8, frame, data->currentFrame);
		} else if (frame < data->currentFrame && frame == data->endFrame) {
			fn_80019540(lbl_8029C310);
		}
		for (i = 0; i < DEMO_DATA->frameCount; i++) {
			ObjectBase* object         = (ObjectBase*)(lbl_8029BBD0 + i * 76);
			ObjectRecord* objectRecord = &object->object;
			DemoInput* input
			    = (DemoInput*)((u8*)DEMO_DATA + 0x84 + DEMO_DATA->frameCount * frame * 60 + i * 60);
			copyObject(*objectRecord, input->object);
			((ControllerRecord*)(lbl_802B0310 + i * 48))->copyFrom(input->controller);
			((ControllerRecord*)(lbl_802B0310 + i * 48 + 16))->copyFrom(input->controller);
			((ControllerRecord*)(lbl_802B0310 + i * 48 + 32))->copyFrom(input->controller);
		}
	}
	sprintf((char*)lbl_8029C254, lbl_80240944, DEMO_DATA->startFrame);
	sprintf((char*)lbl_8029C294, lbl_80240960, DEMO_DATA->endFrame);
}
extern "C" s32 fn_800145BC(const char* name)
{
	if (DEMO_DATA == NULL)
		return 0;
	char path[64];
	sprintf(path, lbl_8042AD88, name);
	if (fn_80042048(path, DEMO_DATA)) {
		memcpy(lbl_80303E48, &DEMO_DATA->saveData, 112);
		return 1;
	}
	return 0;
}

extern "C" u32 fn_80014638()
{
	return DEMO_DATA->startFrame;
}

extern "C" void fn_80014644()
{
	void** globals = lbl_8042AD80;
	lbl_8042C9A4->free(globals[1]);
	globals[0] = NULL;
	globals[1] = NULL;
}

extern "C" void fn_8001468C(s32 frameCount, s32 playerCount)
{
	lbl_8042C9A4->free(lbl_8042AD80[1]);
	lbl_8042AD80[0] = NULL;
	lbl_8042AD80[1] = NULL;
	if (frameCount > 0 && playerCount > 0) {
		void* allocation        = lbl_8042C9A4->allocate(playerCount * 60 + 164);
		lbl_8042AD80[1]         = allocation;
		lbl_8042AD80[0]         = (void*)(((u32)allocation + 31) & ~31);
		DEMO_DATA->playerCount  = playerCount;
		DEMO_DATA->frameCount   = frameCount;
		DEMO_DATA->currentFrame = 0;
		memset(DEMO_DATA->saveData, 0, 112);
		DEMO_DATA->startFrame = 0;
		DEMO_DATA->endFrame   = 0;
	}
}

extern "C" {
char lbl_80240930[] = "RECORDING ... over";
char lbl_80240944[] = "(start flame) ...       %5d";
char lbl_80240960[] = "(end   flame) ...       %5d";
char lbl_8024097C[] = "RECORDING ... %5d / %5d";
char lbl_80240994[] = "SHOWING ... over";
char lbl_802409A8[] = "TEST SHOW     ... %5d / %5d";
}
