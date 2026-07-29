#include "types.h"

/*
 * Original translation unit: Peripheral.cpp.
 *
 * The PS2 beta DWARF establishes the filename, C++ language, controller/demo
 * types, function names, and source order.  The GameCube implementation owns
 * .text 0x80014154-0x80015AC0, extab 0x800057D8-0x80005828, extabindex
 * 0x8000BDC4-0x8000BE3C, .rodata 0x80239940-0x80239978, .data
 * 0x802408F8-0x802409C8, .bss 0x8029BBD0-0x8029C5A8, .sdata
 * 0x8042AD80-0x8042AD90, .sbss 0x8042C0E0-0x8042C0F0, and the generated
 * .sdata2 conversion literal at 0x8042CFD0-0x8042CFD8.
 */

extern "C" {

struct MenuNode {
	u8 pad[4];
	u16 flags;
};

extern MenuNode* lbl_8042C104;
extern MenuNode* lbl_8042C108;
extern MenuNode* lbl_8042C10C;
extern MenuNode* lbl_8042C110;
extern MenuNode* lbl_8042C114;
extern MenuNode* lbl_8042C118;
extern MenuNode* lbl_8042C11C;
extern const u32 peripheral_repeat_bits[11];

void fn_8005751C(void);
void fn_80057574(void);
void fn_800A7548(void);
int OSGetResetSwitchState(void);
void PADRecalibrate(u32);
void PADRead(void*);
void PADClamp(void*);
void PADReset(u32);
void OSSetResetCallback(void (*)(void));
int fn_80124858(void);
float sqrtf(float);
double sqrt(double);
double __frsqrte(double);
double fn_801C9330(float, float);
int sprintf(char*, const char*, ...);
void* memcpy(void*, const void*, unsigned long);
int fn_80042048(const char*, void*);

extern u8* lbl_8042C180;
extern s8 lbl_8042C0E0;
extern s8 lbl_8042C0E1;
extern s16 lbl_8042C0E2;
extern s8 lbl_8042C0E4;
extern u8 lbl_8029C1D4[48];
extern u32 lbl_80240910[4];
extern u32 lbl_80240920[4];
extern char lbl_8042AD88[7];
extern u8 lbl_80303E48[112];
extern const float lbl_8042CFAC;
extern const float lbl_8042CFB0;
extern const double lbl_8042CFB8;
extern const double lbl_8042CFC0;
extern const float lbl_8042CFC8;
extern const float lbl_8042CFCC;

struct SKYPAD {
	u16 button;
	s8 stickX;
	s8 stickY;
	s8 substickX;
	s8 substickY;
	u8 triggerLeft;
	u8 triggerRight;
	u8 analogA;
	u8 analogB;
	s8 error;
	u8 padding;
};

struct sGamePeri {
	u32 on;
	u32 off;
	u32 press;
	u32 release;
	u16 triggerL;
	u16 triggerR;
	s16 analogX;
	s16 analogY;
	s16 analogDX;
	s16 analogDY;
	u32 angle;
	float stroke;
	u32 angleD;
	float strokeD;
	s16 repeat[10];
	u32 unknown40;
	u32 analogOn;
	u32 analogPress;
};

extern const SKYPAD peripheral_rodata_pad;
extern sGamePeri lbl_8029C188;
extern SKYPAD* lbl_8029C204[4];
void periConvertPadData(sGamePeri*, const SKYPAD*);

void fn_80014154(void) { }
void fn_80014158(void) { }

extern s16 lbl_8042C0E6;
extern s8 lbl_8042C0E8;
extern u32 lbl_802408F8[6];
extern u8 lbl_8029BBD0[0x5B8];
struct DemoStorage {
	u8* aligned;
	void* raw;
};
extern DemoStorage lbl_8042AD80;

struct MemoryFunctions {
	u8 pad[308];
	void* (*alloc)(u32);
	void (*free)(void*);
};
extern MemoryFunctions* lbl_8042C9A4;

extern char lbl_8029C214[64];
extern char lbl_8029C254[64];
extern char lbl_8029C294[68];
extern char lbl_80240930[];
extern char lbl_80240944[];
extern char lbl_80240960[];
extern char lbl_8024097C[];
extern char lbl_80240994[];
extern char lbl_802409A8[];
extern u8 lbl_802B0310[];
extern u8 lbl_8029C310[0x298];
void fn_80019540(void*);

struct DemoPeriInput {
	u32 on;
	u32 off;
	u32 press;
	u32 release;
	u16 r;
	u16 l;
	s16 x1;
	s16 y1;
	s16 x2;
	s16 y2;
	s32 angle;
	float stroke;
	s32 angle2;
	float stroke2;
};

struct DemoPlayerInput {
	float stroke;
	s32 angle;
	s8 leverGotcha;
	s8 jump;
	s8 action;
	s8 sfa;
	s8 changeLeader;
	s8 changeLeaderR;
};

struct DemoInput {
	DemoPeriInput inputPeri;
	DemoPlayerInput inputPlayer;
};

struct DemoParam {
	int maxFlame;
	int demoPlayers;
	int startFlame;
	int endFlame;
	unsigned int demoPoint;
	u8 starts[112];
	DemoInput inputs[1];
};

void SetAndGetDemoData(void)
{
	int player;
	unsigned int curPoint = *(unsigned int*)(lbl_8042C180 + 48);
	if (lbl_8042AD80.aligned == 0)
		return;

	int demoMode = *(s8*)(lbl_8042C180 + 24);
	if (demoMode == 3) {
		if (curPoint >= (unsigned int)((DemoParam*)lbl_8042AD80.aligned)->maxFlame) {
			sprintf(lbl_8029C214, lbl_80240930);
			sprintf(lbl_8029C254, lbl_80240944, ((DemoParam*)lbl_8042AD80.aligned)->startFlame);
			sprintf(lbl_8029C294, lbl_80240960, ((DemoParam*)lbl_8042AD80.aligned)->endFlame);
			return;
		}
		sprintf(lbl_8029C214, lbl_8024097C, curPoint, ((DemoParam*)lbl_8042AD80.aligned)->maxFlame);
		for (player = 0; player < ((DemoParam*)lbl_8042AD80.aligned)->demoPlayers; player++) {
			sGamePeri* periG         = (sGamePeri*)(lbl_8029BBD0 + 528 + player * 76);
			DemoInput* input         = (DemoInput*)((u8*)lbl_8042AD80.aligned + 132
			    + ((DemoParam*)lbl_8042AD80.aligned)->demoPlayers * curPoint * 60 + player * 60);
			input->inputPeri.on      = periG->on;
			input->inputPeri.off     = periG->off;
			input->inputPeri.press   = periG->press;
			input->inputPeri.release = periG->release;
			input->inputPeri.r       = periG->triggerL;
			input->inputPeri.l       = periG->triggerR;
			input->inputPeri.x1      = periG->analogX;
			input->inputPeri.y1      = periG->analogY;
			input->inputPeri.x2      = periG->analogDX;
			input->inputPeri.y2      = periG->analogDY;
			input->inputPeri.angle   = periG->angle;
			input->inputPeri.stroke  = periG->stroke;
			input->inputPeri.angle2  = periG->angleD;
			input->inputPeri.stroke2 = periG->strokeD;
			input->inputPlayer       = *(DemoPlayerInput*)(lbl_802B0310 + player * 48);
		}
		((DemoParam*)lbl_8042AD80.aligned)->demoPoint = curPoint;
	} else if (demoMode == 1 || demoMode == 2) {
		if (demoMode == 1) {
			if (curPoint > ((DemoParam*)lbl_8042AD80.aligned)->demoPoint) {
				sprintf(lbl_8029C214, lbl_80240994);
				sprintf(lbl_8029C254, lbl_80240944, ((DemoParam*)lbl_8042AD80.aligned)->startFlame);
				sprintf(lbl_8029C294, lbl_80240960, ((DemoParam*)lbl_8042AD80.aligned)->endFlame);
				return;
			}
			sprintf(lbl_8029C214, lbl_802409A8, curPoint,
			    ((DemoParam*)lbl_8042AD80.aligned)->demoPoint);
		} else if (curPoint < ((DemoParam*)lbl_8042AD80.aligned)->demoPoint
		    && curPoint == (unsigned int)((DemoParam*)lbl_8042AD80.aligned)->endFlame) {
			fn_80019540(lbl_8029C310);
		}

		for (player = 0; player < ((DemoParam*)lbl_8042AD80.aligned)->demoPlayers; player++) {
			sGamePeri* periG = (sGamePeri*)(lbl_8029BBD0 + 528 + player * 76);
			DemoInput* input = (DemoInput*)((u8*)lbl_8042AD80.aligned + 132
			    + ((DemoParam*)lbl_8042AD80.aligned)->demoPlayers * curPoint * 60 + player * 60);
			periG->on        = input->inputPeri.on;
			periG->off       = input->inputPeri.off;
			periG->press     = input->inputPeri.press;
			periG->release   = input->inputPeri.release;
			periG->triggerL  = input->inputPeri.r;
			periG->triggerR  = input->inputPeri.l;
			periG->analogX   = input->inputPeri.x1;
			periG->analogY   = input->inputPeri.y1;
			periG->analogDX  = input->inputPeri.x2;
			periG->analogDY  = input->inputPeri.y2;
			periG->angle     = input->inputPeri.angle;
			periG->stroke    = input->inputPeri.stroke;
			periG->angleD    = input->inputPeri.angle2;
			periG->strokeD   = input->inputPeri.stroke2;
			*(DemoPlayerInput*)(lbl_802B0310 + player * 48 + 0)  = input->inputPlayer;
			*(DemoPlayerInput*)(lbl_802B0310 + player * 48 + 16) = input->inputPlayer;
			*(DemoPlayerInput*)(lbl_802B0310 + player * 48 + 32) = input->inputPlayer;
		}
	}
	sprintf(lbl_8029C254, lbl_80240944, ((DemoParam*)lbl_8042AD80.aligned)->startFlame);
	sprintf(lbl_8029C294, lbl_80240960, ((DemoParam*)lbl_8042AD80.aligned)->endFlame);
}

s32 LoadDemoData(const char* filename)
{
	char path[64];
	if (lbl_8042AD80.aligned == 0)
		return 0;
	sprintf(path, lbl_8042AD88, filename);
	s32 result;
	if (fn_80042048(path, lbl_8042AD80.aligned) != 0) {
		memcpy(lbl_80303E48, lbl_8042AD80.aligned + 20, 112);
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

u32 GetStartFlame(void)
{
	return *(u32*)(lbl_8042AD80.aligned + 8);
}

void EndDemoData(void)
{
	lbl_8042C9A4->free(lbl_8042AD80.raw);
	lbl_8042AD80.aligned = 0;
	lbl_8042AD80.raw     = 0;
}

void InitDemoData(s32 players, s32 maxFlame)
{
	lbl_8042C9A4->free(lbl_8042AD80.raw);
	lbl_8042AD80.aligned = 0;
	lbl_8042AD80.raw     = 0;

	if (players > 0 && maxFlame > 0) {
		lbl_8042AD80.raw                   = lbl_8042C9A4->alloc(maxFlame * 60 + 164);
		lbl_8042AD80.aligned               = (u8*)(((u32)lbl_8042AD80.raw + 31) & ~31);
		*(s32*)(lbl_8042AD80.aligned + 0)  = maxFlame;
		*(s32*)(lbl_8042AD80.aligned + 4)  = players;
		*(s32*)(lbl_8042AD80.aligned + 16) = 0;
		extern void* memset(void*, int, unsigned long);
		memset(lbl_8042AD80.aligned + 20, 0, 112);
		*(s32*)(lbl_8042AD80.aligned + 8)  = 0;
		*(s32*)(lbl_8042AD80.aligned + 12) = 0;
	}
}

void CheckSoftResetTiming(void)
{
	if (lbl_8042C180 != 0) {
		fn_800A7548();
		lbl_8042C0E1 = 0;

		s8 flag  = 0;
		s32 port = lbl_802408F8[0];
		if ((((u32*)(lbl_8029BBD0 + 72))[port * 19] & 0x1600) == 0x1600
		    && ((((u32*)(lbl_8029BBD0 + 80))[port * 19] & 0x1600) != 0 || lbl_8042C0E2 > 0))
			flag = 1;

		if (*(s8*)(lbl_8042C180 + 30) != 0) {
			port = lbl_802408F8[1];
			if ((((u32*)(lbl_8029BBD0 + 72))[port * 19] & 0x1600) == 0x1600
			    && ((((u32*)(lbl_8029BBD0 + 80))[port * 19] & 0x1600) != 0 || lbl_8042C0E2 > 0))
				flag = 1;
		}

		if (flag == 1) {
			if (lbl_8042C0E2 < 4096)
				lbl_8042C0E2++;
		} else {
			lbl_8042C0E2 = 0;
		}
		if (lbl_8042C0E2 >= 30) {
			lbl_8042C0E0 = 1;
			lbl_8042C0E2 = 0;
		}

		s8 reset = 0;
		if (OSGetResetSwitchState() != 0)
			reset = 1;
		if (reset == 1) {
			if (lbl_8042C0E6 < 4096)
				lbl_8042C0E6++;
		} else {
			if (lbl_8042C0E6 >= 1) {
				lbl_8042C0E4 = 1;
				lbl_8042C0E6 = 0;
				PADRecalibrate(0xC0000000);
			}
			lbl_8042C0E6 = 0;
		}
	}
}

s32 CheckSoftReset(void)
{
	if (fn_80124858() == 0) {
		if (lbl_8042C0E1 == 0)
			goto success;
	}
	return 0;
success:
	return lbl_8042C0E0 | lbl_8042C0E4;
}

void inputSetResetCallback(void)
{
	lbl_8042C0E6++;
	lbl_8042C0E8 = 0;
}

u8* GetGamePeriPtr(s32 port)
{
	return lbl_8029BBD0 + lbl_802408F8[port] * 76 + 528;
}

static inline void ChkControllerLocal(void)
{
	SKYPAD** peri = lbl_8029C204;
	u32* port_num = lbl_80240920;
	s32* flag     = (s32*)lbl_8029BBD0;
	s32 cnt       = 0;
	SKYPAD* peri_temp;
	while (cnt < 4) {
		s32 port  = *port_num++;
		peri_temp = (SKYPAD*)(lbl_8029C1D4 + port * sizeof(SKYPAD));
		if (peri_temp->error == 0) {
			*peri++ = peri_temp;
			*flag++ = 1;
		} else {
			*peri++ = (SKYPAD*)&peripheral_rodata_pad;
			*flag++ = 0;
		}
		cnt++;
	}
}

void MakeGameKeyData(void)
{
	SKYPAD* pad;
	SKYPAD** pads;
	sGamePeri* work;
	sGamePeri* primary;
	sGamePeri* secondary;
	s32 i;
	s32* flags;
	u32* mapping;
	SKYPAD** out;
	u32* nextMapping;
	s32 port;
	SKYPAD* fallback;
	s32 good;
	s32 bad;
	u8* padBase;

	pads      = lbl_8029C204;
	work      = (sGamePeri*)(lbl_8029BBD0 + 1008);
	primary   = (sGamePeri*)(lbl_8029BBD0 + 72);
	secondary = (sGamePeri*)(lbl_8029BBD0 + 528);
	ChkControllerLocal();

	i = 0;
	while (i < 4) {
		pad = *pads++;
		if (((s32*)lbl_8029BBD0)[i] == 1)
			periConvertPadData(work, pad);
		else
			*work = lbl_8029C188;

		if (((s32*)lbl_8029BBD0)[i] == 1 && ((s32*)lbl_8029BBD0)[i + 246] == 0)
			*primary = *work;
		else
			*primary = lbl_8029C188;

		if (((s32*)lbl_8029BBD0)[i + 6] == 1 && ((s32*)lbl_8029BBD0)[i + 12] == 0)
			*secondary = *primary;
		else
			*secondary = lbl_8029C188;

		((s32*)lbl_8029BBD0)[i + 12] = 0;

		if (primary->on != 0 || primary->analogX != 0 || primary->analogY != 0
		    || primary->analogDX != 0 || primary->analogDY != 0)
			primary->unknown40 = 0;
		else
			primary->unknown40++;

		if (secondary->on != 0 || secondary->analogX != 0 || secondary->analogY != 0
		    || secondary->analogDX != 0 || secondary->analogDY != 0)
			secondary->unknown40 = 0;
		else
			secondary->unknown40++;

		work++;
		primary++;
		secondary++;
		i++;
	}
	CheckSoftResetTiming();
}

void ChkController(void)
{
	PADRead(lbl_8029C1D4);
	PADClamp(lbl_8029C1D4);
	for (s32 i = 0; i < 4; i++) {
		s8 error = *(s8*)(lbl_8029C1D4 + i * 12 + 10);
		if (error != 0 && error == -1)
			PADReset(lbl_80240910[i]);
	}
}

static inline void ClampAnalogPad(s16& x, s16& y)
{
	if (x > 64)
		x = 64;
	else if (x < -64)
		x = -64;
	if (y > 64)
		y = 64;
	else if (y < -64)
		y = -64;
	if (x > -6 && x < 6)
		x = 0;
	if (y > -6 && y < 6)
		y = 0;
}

static inline s32 CalcAnalogAngle(float x, float y)
{
	if (lbl_8042CFAC == x) {
		if (y > lbl_8042CFAC)
			return 0x4000;
		return 0xC000;
	}
	if (lbl_8042CFAC == y) {
		if (x > lbl_8042CFAC)
			return 0;
		return 0x8000;
	}
	return (s32)(lbl_8042CFB0 * (float)fn_801C9330(y, x));
}

#pragma fp_contract off
static inline float CalcAnalogStroke(float x, float y)
{
	float stroke;
	double half;
	double three;
	double estimate;
	float ySquared = y * y;
	float xSquared = x * x;
	stroke         = xSquared + ySquared;
	if (stroke > lbl_8042CFAC) {
		estimate                 = __frsqrte(stroke);
		half                     = lbl_8042CFB8;
		double part              = half * estimate;
		three                    = lbl_8042CFC0;
		estimate                 = part * (three - stroke * (estimate * estimate));
		part                     = half * estimate;
		estimate                 = part * (three - stroke * (estimate * estimate));
		part                     = half * estimate;
		estimate                 = part * (three - stroke * (estimate * estimate));
		volatile float converted = (float)(stroke * estimate);
		stroke                   = converted;
	}
	float result = stroke;
	if (lbl_8042CFAC != result)
		result *= lbl_8042CFC8;
	if (result > lbl_8042CFCC)
		result = lbl_8042CFCC;
	return result;
}

static inline void UpdateRepeat(s16& value, u32 on, u32 mask)
{
	s16 next = value;
	if (on & mask)
		next++;
	else
		next = 0;
	value = next;
}

#pragma opt_propagation off
void InitPeripheral(void)
{
	lbl_8029C204[0] = (SKYPAD*)(lbl_8029C1D4 + 0);
	lbl_8029C204[1] = (SKYPAD*)(lbl_8029C1D4 + 12);
	lbl_8029C204[2] = (SKYPAD*)(lbl_8029C1D4 + 24);
	lbl_8029C204[3] = (SKYPAD*)(lbl_8029C1D4 + 36);

	if (lbl_8042C0E0 != 0)
		lbl_8042C0E0 = 0;
	if (lbl_8042C0E2 != 0)
		lbl_8042C0E2 = 0;
	if (lbl_8042C0E4 != 0)
		lbl_8042C0E4 = 0;
	if (lbl_8042C0E6 != 0)
		lbl_8042C0E6 = 0;
	if (lbl_8042C0E8 == 0) {
		OSSetResetCallback(inputSetResetCallback);
		lbl_8042C0E8 = 1;
	}

	sGamePeri* periG = &lbl_8029C188;
	periConvertPadData(periG, &peripheral_rodata_pad);
	s32 cnt = 0;
	if (cnt < 10) {
		sGamePeri* p = periG;
		for (s32 j = 0; j < 10; j += 5) {
			p->repeat[0] = 0;
			p->repeat[1] = 0;
			p->repeat[2] = 0;
			p->repeat[3] = 0;
			p->repeat[4] = 0;
			p            = (sGamePeri*)((u8*)p + 10);
		}
	}
	periG->analogOn    = 0;
	periG->analogPress = 0;

	*(u32*)(lbl_8029BBD0 + 24)   = 0;
	*(u32*)(lbl_8029BBD0 + 48)   = 0;
	*(u32*)(lbl_8029BBD0 + 984)  = 0;
	*(u32*)(lbl_8029BBD0 + 28)   = 0;
	*(u32*)(lbl_8029BBD0 + 52)   = 0;
	*(u32*)(lbl_8029BBD0 + 988)  = 0;
	*(u32*)(lbl_8029BBD0 + 32)   = 0;
	*(u32*)(lbl_8029BBD0 + 56)   = 0;
	*(u32*)(lbl_8029BBD0 + 992)  = 0;
	*(u32*)(lbl_8029BBD0 + 36)   = 0;
	*(u32*)(lbl_8029BBD0 + 60)   = 0;
	*(u32*)(lbl_8029BBD0 + 996)  = 0;
	*(u32*)(lbl_8029BBD0 + 40)   = 0;
	*(u32*)(lbl_8029BBD0 + 64)   = 0;
	*(u32*)(lbl_8029BBD0 + 1000) = 0;
	*(u32*)(lbl_8029BBD0 + 44)   = 0;
	*(u32*)(lbl_8029BBD0 + 68)   = 0;
	*(u32*)(lbl_8029BBD0 + 1004) = 0;
}
#pragma opt_propagation reset
void periConvertPadData(sGamePeri* general, const SKYPAD* original)
{
	general->press    = original->button & (general->on ^ original->button) & 0xFFFF;
	general->release  = general->on & (general->on ^ original->button) & 0xFFFF;
	general->on       = original->button;
	general->off      = ~original->button;
	general->triggerL = original->triggerRight;
	general->triggerR = original->triggerLeft;

	s16 analogX = original->substickX;
	s16 analogY = -original->substickY;
	ClampAnalogPad(analogX, analogY);
	general->analogDX = analogX;
	general->analogDY = analogY;

	analogX = original->stickX;
	analogY = -original->stickY;
	ClampAnalogPad(analogX, analogY);
	general->analogX = analogX;
	general->analogY = analogY;

	general->stroke  = CalcAnalogStroke(general->analogX, general->analogY);
	general->strokeD = CalcAnalogStroke(general->analogDX, general->analogDY);

	u32 oldAnalog;
	s16 analogValueX;
	s16 analogValueY;
	analogValueY         = general->analogY;
	analogValueX         = general->analogX;
	oldAnalog            = general->analogOn;
	general->analogOn    = (general->on &= 0xFFF0FFFF);
	general->analogPress = (general->press &= 0xFFF0FFFF);

	if (analogValueY > 32) {
		general->analogOn |= 0x40000;
		if (oldAnalog & 0x40000)
			general->analogPress &= ~0x40000;
		else
			general->analogPress |= 0x40000;
	} else if (analogValueY < -32) {
		general->analogOn |= 0x80000;
		if (oldAnalog & 0x80000)
			general->analogPress &= ~0x80000;
		else
			general->analogPress |= 0x80000;
	}
	if (analogValueX > 32) {
		general->analogOn |= 0x20000;
		if (oldAnalog & 0x20000)
			general->analogPress &= ~0x20000;
		else
			general->analogPress |= 0x20000;
	} else if (analogValueX < -32) {
		general->analogOn |= 0x10000;
		if (oldAnalog & 0x10000)
			general->analogPress &= ~0x10000;
		else
			general->analogPress |= 0x10000;
	}

	general->angle  = CalcAnalogAngle((float)general->analogX, (float)general->analogY) & 0xFFFF;
	general->angleD = CalcAnalogAngle((float)general->analogDX, (float)general->analogDY) & 0xFFFF;

	UpdateRepeat(general->repeat[0], general->analogOn, 8);
	UpdateRepeat(general->repeat[1], general->analogOn, 4);
	UpdateRepeat(general->repeat[2], general->analogOn, 1);
	UpdateRepeat(general->repeat[3], general->analogOn, 2);
	UpdateRepeat(general->repeat[4], general->analogOn, 0x80000);
	UpdateRepeat(general->repeat[5], general->analogOn, 0x40000);
	UpdateRepeat(general->repeat[6], general->analogOn, 0x10000);
	UpdateRepeat(general->repeat[7], general->analogOn, 0x20000);
	UpdateRepeat(general->repeat[8], general->analogOn, 0x40);
	UpdateRepeat(general->repeat[9], general->analogOn, 0x20);
}
#pragma fp_contract reset

u32 ConvertBit_AD(const u8* self, u32 keyBit)
{
	keyBit |= (keyBit & 0xF) << 16;
	return (*(const u32*)(self + 0x48) & keyBit) != 0;
}

u32 ConvertBit_A(const u8* self, u32 keyBit)
{
	u32 bit = (keyBit & 0xFFFFFFF0) | ((keyBit & 0xF) << 16);
	return (*(const u32*)(self + 0x48) & bit) != 0;
}

u32 edgeCheck(const u8* self, u32 keyBit)
{
	keyBit |= (keyBit & 0xF) << 16;
	return (*(const u32*)(self + 0x44) & keyBit) != 0;
}

static inline u32 repCheckSub(const u8* self, u32 keyBit, s32 repTime, s32 repInt)
{
	u32 key = keyBit;
	if (key == 0)
		return 0;
	if ((*(const u32*)(self + 0x48) & key) != 0)
		return 1;
	u32 result = 0;
	for (s32 i = 0; i < 10; i++) {
		if ((key & peripheral_repeat_bits[i]) != 0) {
			s32 count = *(const s16*)(self + 0x2C + i * 2) - (repTime + 1);
			if (count >= 0 && count % repInt == 0)
				result |= 1;
		}
	}
	return result;
}

static inline u32 ConvertBitAD(u32 keyBit)
{
	return keyBit | ((keyBit & 0xF) << 16);
}

u32 repCheck(const u8* self, u32 keyBit, s32 repTime, s32 repInt)
{
	return repCheckSub(self, ConvertBitAD(keyBit), repTime, repInt);
}

u32 repCheck_D(const u8* self, u32 keyBit, s32 repTime, s32 repInt)
{
	keyBit &= 0xFFF0FFFF;
	return repCheckSub(self, keyBit, repTime, repInt);
}

__declspec(section ".rodata") const SKYPAD peripheral_rodata_pad   = { 0 };
__declspec(section ".rodata") const u32 peripheral_repeat_bits[11] = {
	0x00000008,
	0x00000004,
	0x00000001,
	0x00000002,
	0x00080000,
	0x00040000,
	0x00010000,
	0x00020000,
	0x00000040,
	0x00000020,
	0x00000000,
};

u32 lbl_802408F8[6] = { 0, 1, 2, 3, 4, 5 };
u32 lbl_80240910[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };
u32 lbl_80240920[4] = { 0, 1, 2, 3 };
char lbl_80240930[] = "RECORDING ... over";
char lbl_80240944[] = "(start flame) ...       %5d";
char lbl_80240960[] = "(end   flame) ...       %5d";
char lbl_8024097C[] = "RECORDING ... %5d / %5d";
char lbl_80240994[] = "SHOWING ... over";
char lbl_802409A8[] = "TEST SHOW     ... %5d / %5d";

u8 lbl_8029BBD0[0x5B8];
sGamePeri lbl_8029C188;
u8 lbl_8029C1D4[48];
SKYPAD* lbl_8029C204[4];
char lbl_8029C214[64];
char lbl_8029C254[64];
char lbl_8029C294[68];
u8 lbl_8029C2D8[12];
u8 lbl_8029C2E4[44];
u8 lbl_8029C310[0x298];

DemoStorage lbl_8042AD80 = { 0, 0 };
char lbl_8042AD88[7]     = "%s.dmo";

s8 lbl_8042C0E0;
s8 lbl_8042C0E1;
s16 lbl_8042C0E2;
s8 lbl_8042C0E4;
s16 lbl_8042C0E6;
s8 lbl_8042C0E8;
}
