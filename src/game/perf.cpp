#include "types.h"

// Game performance and memory diagnostics. The retail TU owns text
// 0x800CD6A0..0x800CE010 together with its ctor, exception metadata,
// performance-label table and 0x950-byte global state. The preceding function
// initializes unrelated memory arenas; the following TU begins the font/text
// subsystem. Correlated PS2 debug symbols provide the PERF method names and
// confirm perf.cpp as C++, but the GameCube boundaries and code are verified
// independently.

extern "C" {
void* memset(void*, int, u32);
int sprintf(char*, const char*, ...);
void OSInitStopwatch(void*, const char*);
void fn_80012654(u32*, u32*);
void RsCameraSize(void*, const char*, int, int, int);
int repCheck_D(void*, int, int, int);
void fn_80051D44(void*, void*, void*);

extern void* lbl_8042C0F0;
extern void* lbl_8042B088;
extern u8 lbl_802408F8[];
}

struct OSStopwatch {
	const char* name;
	u32 hits;
	s64 total;
	s64 min;
	s64 max;
	s64 last;
	s32 running;
	u8 pad[0x14];
};

struct PerfEntry {
	u8 stopwatch[0x30];
	u32 value;
	u32 pad34;
	u32 capacity;
	u32 pad3c;
};

struct PerfInfo {
	const char* name;
	s32 limit;
	s32 flag;
};

struct Controller {
	u8 pad[0x4c];
};

extern Controller lbl_8029BBD0[];

enum P_PERFORMANCE_ELE {
	P_PERFORMANCE_ELE_FIRST = 0,
};

struct PERF {
	s32 page;
	s32 mode;
	OSStopwatch temporary;
	s32 heapSize;
	s32 continuousHeapSize;
	PerfEntry elements[36];

	void clearParameter(int dest)
	{
		elements[dest].value    = 0;
		elements[dest].capacity = 0;
	}

	void addParameter2(int dest, int source)
	{
		elements[dest].value += elements[source].value;
		elements[dest].capacity += elements[source].capacity;
	}

	void addParameter(int dest, int first, int second)
	{
		clearParameter(dest);
		addParameter2(dest, first);
		addParameter2(dest, second);
	}

	void DisplayInfo();
	void InitPerfomanceMember(P_PERFORMANCE_ELE);
	void InitPerfomance();

	u32 CheckRestHeap()
	{
		u32 result;
		if (mode) {
			fn_80012654(&result, 0);
			return result;
		}
		return 0;
	}

	u32 CheckRestContinuousHeap()
	{
		u32 result;
		if (mode == 1) {
			fn_80012654(0, &result);
			return result;
		}
		return 0;
	}
};

extern "C" {
extern u32 lbl_802555A0[];
extern char lbl_802555B0[];
extern char lbl_802555CC[];
extern char lbl_802555EC[];
extern char lbl_80255604[];
extern char lbl_80255624[];
extern char lbl_80255640[];
extern char lbl_8025565C[];
extern char lbl_80255678[];
extern char lbl_80255694[];
extern char lbl_802556D8[];
extern char lbl_802556EC[];
extern char lbl_802556FC[];
extern char lbl_80255708[];
extern char lbl_80255728[];
extern char lbl_8042B64C[4];
extern u32 lbl_8042B648;
extern PerfInfo lbl_802553F0[36];
extern PERF lbl_803A6690;
}

void PERF::DisplayInfo()
{
	PERF* perf = this;
	switch (perf->mode) {
		case 1:
			RsCameraSize(lbl_8042C0F0, lbl_802555B0, 35, 0, 5);
			break;
		case 2:
			RsCameraSize(lbl_8042C0F0, lbl_802555CC, 35, 0, 5);
			break;
		case 0:
			RsCameraSize(lbl_8042C0F0, lbl_802555EC, 35, 0, 5);
			break;
	}
	RsCameraSize(lbl_8042C0F0, lbl_80255604, 35, 1, 5);

	u8* controller = (u8*)lbl_8029BBD0;
	controller += *(u32*)lbl_802408F8 * sizeof(Controller);
	u32 controllerIndex;
	if (*(u32*)(controller + 0x50) & 1) {
		switch (perf->mode) {
			case 0:
				perf->mode = 2;
				break;
			case 2:
				perf->mode = 1;
				break;
			case 1:
				perf->mode = 0;
				break;
		}
	}
	controllerIndex = *(u32*)lbl_802408F8;
	controller      = (u8*)&lbl_8029BBD0[controllerIndex];
	if (repCheck_D(controller + 0x48, 8, 12, 1)) {
		perf->page--;
		if (perf->page < 0)
			perf->page = 0;
	}
	controllerIndex = *(u32*)lbl_802408F8;
	controller      = (u8*)&lbl_8029BBD0[controllerIndex];
	if (repCheck_D(controller + 0x48, 4, 12, 1))
		perf->page++;

	fn_80051D44(lbl_8042B088, lbl_802555A0, &lbl_8042B648);
	perf->addParameter(9, 10, 11);
	perf->addParameter(12, 13, 14);
	perf->addParameter2(12, 15);
	perf->clearParameter(20);
	perf->addParameter2(20, 21);
	perf->addParameter2(20, 22);
	perf->addParameter2(20, 23);
	perf->addParameter2(20, 24);
	perf->clearParameter(16);
	perf->addParameter2(16, 17);
	perf->addParameter2(16, 18);
	perf->addParameter2(16, 19);
	perf->clearParameter(26);
	perf->addParameter2(26, 0);
	perf->addParameter2(26, 1);
	perf->addParameter2(26, 2);
	perf->addParameter2(26, 3);
	perf->addParameter2(26, 4);
	perf->addParameter2(26, 6);
	perf->addParameter2(26, 7);
	perf->addParameter2(26, 8);
	perf->addParameter2(26, 9);
	perf->addParameter2(26, 12);
	perf->addParameter2(26, 16);
	perf->addParameter2(26, 20);

	char text[64];
	if (perf->heapSize > 0x1800000)
		sprintf(text, lbl_80255624, 0x3000000);
	else
		sprintf(text, lbl_80255640, 0x1800000);
	RsCameraSize(lbl_8042C0F0, text, 0, 0, 5);
	sprintf(text, lbl_8025565C, perf->heapSize);
	RsCameraSize(lbl_8042C0F0, text, 0, 1, 5);
	sprintf(text, lbl_80255678, perf->continuousHeapSize);
	RsCameraSize(lbl_8042C0F0, text, 0, 2, 5);
	RsCameraSize(lbl_8042C0F0, lbl_80255694, 0, 3, 5);

	u8* element;
	int i;
	i       = 0;
	element = (u8*)perf;
	for (; i < 36; element += 0x40, i++) {
		u8* info = (u8*)&lbl_802553F0[i];
		if (i >= perf->page && i <= perf->page + 22) {
			const char* name = *(const char**)info;
			if (*name == '-')
				sprintf(text, lbl_8042B64C, name);
			else if (*(s32*)(info + 4))
				sprintf(text, lbl_802556D8, name, *(u32*)(element + 0x80), *(u32*)(element + 0x88),
				    *(s32*)(info + 4) - *(u32*)(element + 0x88));
			else if (i == 26)
				sprintf(text, lbl_802556EC, name, *(u32*)(element + 0x80), *(u32*)(element + 0x88));
			else
				sprintf(text, lbl_802556FC, name, *(u32*)(element + 0x80), *(u32*)(element + 0x88));
			RsCameraSize(lbl_8042C0F0, text, 0, i + 4 - perf->page, 5);
		}
	}

	u32 rest       = perf->CheckRestHeap();
	u32 continuous = perf->CheckRestContinuousHeap();
	sprintf(text, lbl_80255708, rest, continuous);
	RsCameraSize(lbl_8042C0F0, text, 0, 28, 5);
}

// MWCC inlines the class method above into DisplayInfo. This out-of-line
// emission surrogate preserves the independently addressable retail method
// without disabling that original inline decision.
extern "C" u32 CheckRestHeap__4PERFFv(PERF* perf)
{
	return perf->CheckRestHeap();
}

void PERF::InitPerfomanceMember(P_PERFORMANCE_ELE element)
{
	s32 index              = element;
	OSStopwatch* stopwatch = (OSStopwatch*)&elements[index];
	memset(stopwatch, 0, sizeof(OSStopwatch));
	OSInitStopwatch(stopwatch, lbl_802553F0[index].name);
}

#pragma opt_strength_reduction off
void PERF::InitPerfomance()
{
	PERF* perf = this;
	perf->page = 0;
	OSInitStopwatch(&perf->temporary, lbl_80255728);
	for (s32 index = 7; index < 36; ++index)
		lbl_803A6690.InitPerfomanceMember((P_PERFORMANCE_ELE)index);
}

extern "C" void __sinit_perf_cpp()
{
	memset(lbl_803A6690.elements, 0, sizeof(lbl_803A6690.elements));
	lbl_803A6690.mode = 0;
	lbl_803A6690.page = 0;
	OSInitStopwatch(&lbl_803A6690.temporary, lbl_80255728);
	for (s32 index = 7; index < 36; ++index) {
		OSStopwatch* stopwatch = (OSStopwatch*)&lbl_803A6690.elements[index];
		memset(stopwatch, 0, sizeof(OSStopwatch));
		OSInitStopwatch(stopwatch, lbl_802553F0[index].name);
	}
}
__declspec(section ".ctors") void (*const perfCtorEntry)(void) = __sinit_perf_cpp;
#pragma opt_strength_reduction reset

extern "C" {
char lbl_80255098[] = "SYSTEM RWINIT       : ";
char lbl_802550B0[] = "SYSTEM CHARASET     : ";
char lbl_802550C8[] = "SYSTEM MAININIT     : ";
char lbl_802550E0[] = "SYSTEM MAINTASKINIT : ";
char lbl_802550F8[] = "SYSTEM INITMODULES  : ";
char lbl_80255110[] = "---------------------";
char lbl_80255128[] = "MAIN PROGRAM+       : ";
char lbl_80255140[] = "SUB PROGRAM         : ";
char lbl_80255158[] = "PLAYER              : ";
char lbl_80255170[] = "LAND                : ";
char lbl_80255188[] = "    (DISP MODELS )  : ";
char lbl_802551A0[] = "    (OCTREE      )  : ";
char lbl_802551B8[] = "STAGE TEXTURE       : ";
char lbl_802551D0[] = "    (SHARE       )  : ";
char lbl_802551E8[] = "    (NATIVE+LAND )  : ";
char lbl_80255200[] = "    (GDISP       )  : ";
char lbl_80255218[] = "SOUND               : ";
char lbl_80255230[] = "    (INIT     )     : ";
char lbl_80255248[] = "    (ADXCREATE   )  : ";
char lbl_80255260[] = "    (LOADMLT     )  : ";
char lbl_80255278[] = "ETC                 : ";
char lbl_80255290[] = "    (STAGE INIT  )  : ";
char lbl_802552A8[] = "    (SET SHARE   )  : ";
char lbl_802552C0[] = "    (SET NATIVE  )  : ";
char lbl_802552D8[] = "    (PARTICLE    )  : ";
char lbl_802552F0[] = "TOTAL(about)        : ";
char lbl_80255308[] = "-------------------------------------------------------------";
char lbl_80255348[] = "DISPLAY OPEQ        : ";
char lbl_80255360[] = "DISPLAY PUNCH       : ";
char lbl_80255378[] = "DISPLAY ALPHA       : ";
char lbl_80255390[] = "DISPLAY 2D          : ";
char lbl_802553A8[] = "SYNC WAIT           : ";
char lbl_802553C0[] = "DISPLAY BEFORE REND : ";
char lbl_802553D8[] = "ALL                 : ";

PerfInfo lbl_802553F0[36] = {
	{ lbl_80255098, 0, 0 },
	{ lbl_802550B0, 0, 0 },
	{ lbl_802550C8, 0, 0 },
	{ lbl_802550E0, 0, 0 },
	{ lbl_802550F8, 0, 0 },
	{ lbl_80255110, 0, 0 },
	{ lbl_80255128, 0x300000, 0 },
	{ lbl_80255140, 0x133333, 0 },
	{ lbl_80255158, 0x200000, 0 },
	{ lbl_80255170, 0x533333, 0 },
	{ lbl_80255188, 0x366666, 0 },
	{ lbl_802551A0, 0x1ccccc, 0 },
	{ lbl_802551B8, 0x2b3333, 0 },
	{ lbl_802551D0, 0x80000, 0 },
	{ lbl_802551E8, 0x200000, 0 },
	{ lbl_80255200, 0x33333, 0 },
	{ lbl_80255218, 0x1b3333, 0 },
	{ lbl_80255230, 0xe6666, 0 },
	{ lbl_80255248, 0xccccc, 0 },
	{ lbl_80255260, 0, 0 },
	{ lbl_80255278, 0, 0 },
	{ lbl_80255290, 0, 0 },
	{ lbl_802552A8, 0x133333, 0 },
	{ lbl_802552C0, 0x99999, 0 },
	{ lbl_802552D8, 1, 0 },
	{ lbl_80255110, 0, 0 },
	{ lbl_802552F0, 0, 0 },
	{ lbl_80255308, 0, 0 },
	{ lbl_80255348, 0, 1 },
	{ lbl_80255360, 0, 1 },
	{ lbl_80255378, 0, 1 },
	{ lbl_80255390, 0, 1 },
	{ lbl_802553A8, 0, 1 },
	{ lbl_802553C0, 0, 1 },
	{ lbl_80255110, 0, 0 },
	{ lbl_802553D8, 0, 1 },
};

u32 lbl_802555A0[4]     = { 0, 0, 0x280, 0x1e0 };
char lbl_802555B0[]     = "MEMORY CHECK : REALTIME  ";
char lbl_802555CC[]     = "MEMORY CHECK : NO CHECK CONT  ";
char lbl_802555EC[]     = "MEMORY CHECK : FALSE  ";
char lbl_80255604[]     = "Memory check mode change -> K_L";
char lbl_80255624[]     = "MEMORY(48M setting) %10d";
char lbl_80255640[]     = "MEMORY(24M setting) %10d";
char lbl_8025565C[]     = "ALL HEAP            %10d";
char lbl_80255678[]     = "TSonic HEAP         %10d";
char lbl_80255694[]     = "                      load(perf) time /  used memory   /   capacity";
char lbl_802556D8[]     = "%s %8d %16d %16d";
char lbl_802556EC[]     = "%s %8d+%16d+";
char lbl_802556FC[]     = "%s %8d %16d";
char lbl_80255708[]     = "REST HEAP %16d  / cont. %16d";
char lbl_80255728[0x10] = "tmpStopWatch";

u32 lbl_8042B648     = 0xb480;
char lbl_8042B64C[4] = "%s";
PERF lbl_803A6690;
}
