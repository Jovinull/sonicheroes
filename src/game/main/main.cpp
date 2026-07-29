typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;

/*
 * RenderWare event handling and the game's top-level mode loop.
 *
 * Local PS2 beta DWARF identifies the corresponding original unit as
 * main.cpp and names the two MAIN methods below.  The GameCube code and
 * section boundaries remain authoritative for this reconstruction.
 *
 * The source lives one directory deeper than the original basename because
 * the project also contains the unrelated GameCube platform entry point
 * game/main.c; both otherwise map to the same build-object path.
 */

struct DVDFileInfo {
	u8 pad[0x34];
	u32 length;
};

struct Module {
	virtual void Init();
	virtual int Loop();
	virtual void End();
};

struct TMainTask {
	u8 pad00[0x1E];
	s8 field1E;
	u8 pad1F[7];
	s8 field26;
	s8 field27;
	s8 field28;
	u8 field29;
	s8 field2A;
	u8 pad2B[0xD];
	int mode;
	int nextMode;
	u8 pad40[4];

	TMainTask();
	static void* operator new(unsigned long);
};

struct MAIN {
	int field0;

	void Init();
	int Loop();
};

struct RsGlobal {
	const char* appName;
	int maximumWidth;
	int maximumHeight;
	int maximumFPS;
	int quit;
};

extern "C" {
void InitPeripheral();
void fn_80112DAC();
void fn_80112F3C();
void fn_801EB458();
void fn_80112F80();
void fn_800B654C();
void fn_8001D70C();
void fn_8001F4D8();
void fn_8011253C();
int DVDOpen(const char*, DVDFileInfo*);
void* fn_80012994(u32);
int DVDReadPrio(DVDFileInfo*, void*, int, int, int);
void OSSetStringTable(void*);
void DVDClose(DVDFileInfo*);
void fn_800D7B18();
void fn_80116D30(void*);
void fn_80040198(void*);
void fn_80066ED8(void*, int);
void fn_800D0AA8();
void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(TMainTask*, int, int);
void fn_800A7614();
void fn_80112F10();
int fn_80011D64();
int fn_80011DD8(void*);
void fn_800122E8(const char*);
int CheckRestHeap__4PERFFv(void*);
void fn_800B6C64();
void* fn_801784C8(void*, void*);
void fn_8022CEB0();
void fn_80016E88(void*);
void fn_800CE010();
void fn_800D09C4();
void fn_8004014C(void*);
void __dt__10MODESWITCHFv(void*, int);
void fn_800B6418();
void fn_80112D98();
void fn_80016CA0(void*);
void fn_801A173C(void*);
void fn_800B6C14();
void fn_80011EFC();
int fn_80159FB8();
int fn_8013ECE0();
int fn_80226338();
int fn_80149018();
int fn_8005F710();
int fn_8014DB38();
int fn_801FC470();
int fn_8013D78C();
int fn_8020C044();
int fn_8014A90C();
int fn_8023944C();
int fn_8022D8EC();
void fn_800A7A44();
void fn_80112F74();
void fn_800A92CC(void*, int, int);
void fn_800B429C(void*);
void fn_800CD528();
void fn_800A74BC(int);
int fn_801386C4(void*);
int fn_80138664(void*);
extern TMainTask* lbl_8042C180;
extern char lbl_803E774C[];
extern char lbl_8042C1BC;
extern char lbl_8042C308;
extern char lbl_803A6690[];
extern char lbl_8029C2E4[];
extern char lbl_80303EC8[];
extern char lbl_803EC340[];
extern char lbl_8029C310[];
extern Module* lbl_80253068[];
extern int lbl_8042B320;
extern Module* lbl_8042C338;
extern void* lbl_8042C388;
extern char lbl_8042C7E0;
extern RsGlobal lbl_8029BB80;
extern char lbl_802409C8[];
extern char lbl_802409F4[];
extern char lbl_80240A14[];
extern char lbl_80240A80[];
}

extern "C" u32 lbl_8042AD90    = 0xC8C8C8FF;
extern "C" char lbl_8042AD94[] = "@@@";
extern "C" {
void* lbl_8042C0F0;
MAIN lbl_8042C0F4;
}

/*
 * These staging names are restored to their retail labels after compilation.
 * Defining the strings under the retail names before AppEventHandler makes
 * CodeWarrior combine their addresses into a local base and changes register
 * allocation.  See tools/fix_game_main_symbols.py.
 */
char mainAppName[]            = "RW3 Static Geometry Construction Example";
char mainRenderWareError[]    = "Error initializing RenderWare.";
char mainRasterCharsetError[] = "Cannot create raster charset.";

enum MainBool { MAIN_FALSE = 0, MAIN_TRUE = 1 };

static inline int AttachPlugins()
{
	if (!fn_80159FB8())
		return MAIN_FALSE;
	if (!fn_8013ECE0())
		return MAIN_FALSE;
	if (!fn_80226338())
		return MAIN_FALSE;
	if (!fn_80149018())
		return MAIN_FALSE;
	if (!fn_8005F710())
		return MAIN_FALSE;
	if (!fn_8014DB38())
		return MAIN_FALSE;
	if (!fn_801FC470())
		return MAIN_FALSE;
	if (!fn_8013D78C())
		return MAIN_FALSE;
	if (!fn_8020C044())
		return MAIN_FALSE;
	if (!fn_8014A90C())
		return MAIN_FALSE;
	if (!fn_8023944C())
		return MAIN_FALSE;
	if (!fn_8022D8EC())
		return MAIN_FALSE;
	return MAIN_TRUE;
}

static inline int InitializeApp()
{
	if (fn_80011D64()) {
		if (lbl_8029BB80.maximumWidth == 0)
			lbl_8029BB80.maximumWidth = 640;
		if (lbl_8029BB80.maximumHeight == 0)
			lbl_8029BB80.maximumHeight = 480;
		lbl_8029BB80.appName    = lbl_802409C8;
		lbl_8029BB80.maximumFPS = 60;
		return 1;
	}
	return 0;
}

static inline int Initialize3D(void* param)
{
	int memory        = CheckRestHeap__4PERFFv(lbl_803A6690);
	int* globals      = (int*)lbl_803A6690;
	globals[0x48 / 4] = memory;
	if (memory > 0x1800000)
		globals[0x208 / 4] = 0x3000000 - memory;
	else
		globals[0x208 / 4] = 0x1800000 - memory;
	if (!fn_80011DD8(param)) {
		fn_800122E8(lbl_802409F4);
		return false;
	}
	fn_800B6C64();
	lbl_8042C0F0 = fn_801784C8(&lbl_8042AD90, lbl_8042AD94);
	if (!lbl_8042C0F0) {
		fn_800122E8(lbl_80240A14);
		return false;
	}
	fn_8022CEB0();
	fn_80016E88(lbl_8029C2E4);
	lbl_8042C0F4.Init();
	return true;
}

enum RsEventStatus { rsEVENTERROR = 0, rsEVENTPROCESSED = 1, rsEVENTNOTPROCESSED = 2 };

extern "C" RsEventStatus AppEventHandler(unsigned event, void* param)
{
	switch (event) {
		case 16:
			return InitializeApp() ? rsEVENTPROCESSED : rsEVENTERROR;
		case 0:
			return rsEVENTPROCESSED;
		case 13:
			return Initialize3D(param) ? rsEVENTPROCESSED : rsEVENTERROR;
		case 14:
			fn_800CE010();
			fn_800D09C4();
			fn_8004014C(&lbl_8042C1BC);
			while (lbl_8042C180) {
				__dt__10MODESWITCHFv(lbl_8042C180, 1);
			}
			fn_800B6418();
			fn_80112D98();
			fn_80016CA0(lbl_8029C2E4);
			if (lbl_8042C0F0)
				fn_801A173C(lbl_8042C0F0);
			fn_800B6C14();
			fn_80011EFC();
			return rsEVENTPROCESSED;
		case 9: {
			RsEventStatus status;
			if (AttachPlugins())
				status = rsEVENTPROCESSED;
			else
				status = rsEVENTERROR;
			return status;
		}
		case 4:
			return rsEVENTPROCESSED;
		case 18:
			if (!lbl_8042C0F4.Loop()) {
				lbl_8029BB80.quit = 1;
				return rsEVENTPROCESSED;
			}
			break;
		default:
			break;
	}
	return rsEVENTNOTPROCESSED;
}

char mainStringTableName[] = "Tsonic.str";

void MAIN::Init()
{
	InitPeripheral();
	fn_80112DAC();
	fn_80112F3C();
	fn_801EB458();

	while (lbl_8042C180 == 0) {
		new TMainTask;
	}

	fn_80112F80();
	fn_800B654C();
	fn_8001D70C();
	fn_8001F4D8();
	fn_8011253C();

	DVDFileInfo file;
	if (DVDOpen(lbl_80240A80, &file)) {
		u32 size    = (file.length + 0x1F) & ~0x1F;
		void* table = fn_80012994(size);
		if (DVDReadPrio(&file, table, size, 0, 2) > 0)
			OSSetStringTable(table);
		DVDClose(&file);
	}

	fn_800D7B18();
	fn_80116D30(lbl_803E774C);
	fn_80040198(&lbl_8042C1BC);
	fn_80066ED8(&lbl_8042C308, 0);
	fn_800D0AA8();
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x13, ((s8*)lbl_8042C180)[0x13]);
	fn_800A7614();
	fn_8011253C();
	fn_80112F10();
}

enum MOBJECT_TYPE { MOBJECT_0, MOBJECT_1, MOBJECT_2, MOBJECT_3 };

static inline void runModule(Module* module, int& result, bool withExtraService)
{
	lbl_8042C338 = module;
	lbl_8042C338->Init();
	do {
		result = lbl_8042C338->Loop();
		if (lbl_8042C388 != 0)
			fn_800B429C(lbl_8042C388);
		fn_800CD528();
		if (withExtraService)
			fn_8011253C();
	} while (result == 0);
}

static inline void setSpecialMode()
{
	switch (fn_801386C4(&lbl_8042C7E0)) {
		case 0:
			SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 2);
			break;
		case 1:
			if (lbl_8042C180->field26 == 0) {
				SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 2);
				SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x26, 1);
			} else {
				*(int*)(lbl_803EC340 + 4) = fn_80138664(&lbl_8042C7E0);
				SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 5);
			}
			break;
		case 2:
			break;
		default:
			SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 1);
			break;
	}
}

int MAIN::Loop()
{
	field0                       = 0;
	*(int*)(lbl_803A6690 + 0x4C) = CheckRestHeap__4PERFFv(lbl_803A6690);
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 0);
	fn_800A7A44();
	fn_8011253C();
	fn_80112F74();

	for (;;) {
		int result;
		MOBJECT_TYPE moduleIndex;

		switch (lbl_8042C180->mode) {
			case 0:
			case 1:
			case 4:
				if (lbl_8042C180->mode == 1) {
					int player = lbl_8042C180->field2A;
					if (player >= 0)
						fn_800A92CC(lbl_80303EC8, player, 0);
				}
				lbl_8042B320 = 1;
				runModule(lbl_80253068[1], result, true);
				if (result == 3)
					fn_800A74BC(0);
				lbl_8042C338->End();
				if (lbl_8042C180->field27 != 0)
					setSpecialMode();
				break;

			case 2:
				moduleIndex  = MOBJECT_0;
				lbl_8042B320 = moduleIndex;
				runModule(lbl_80253068[moduleIndex], result, false);
				lbl_8042C338->End();
				if (lbl_8042C180->field27 != 0) {
					if (result == 1)
						setSpecialMode();
					else
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 1);
				} else if (result == 1) {
					int playerMode = lbl_8042C180->field28;
					if ((playerMode == 2 || lbl_8042C180->field1E == 2)
					    && *(int*)(lbl_8029C310 + 0x3C) > 0) {
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 2);
					} else if (playerMode == 2 && *(int*)(lbl_8029C310 + 0x3C) <= 0) {
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 5);
					} else if (lbl_8042C180->field26 == 0) {
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 2);
					} else if (*(int*)(lbl_8029C310 + 0x3C) == 0x18) {
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 2);
					} else {
						SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 1);
					}
				} else {
					SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 0x30, 1);
				}
				if (result == 3)
					fn_800A74BC(0);
				break;

			case 3:
				moduleIndex  = MOBJECT_2;
				lbl_8042B320 = moduleIndex;
				runModule(lbl_80253068[moduleIndex], result, true);
				lbl_8042C338->End();
				SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(
				    lbl_8042C180, 0x30, lbl_8042C180->nextMode);
				break;

			case 5:
				moduleIndex  = MOBJECT_3;
				lbl_8042B320 = moduleIndex;
				runModule(lbl_80253068[moduleIndex], result, true);
				lbl_8042C338->End();
				if (lbl_8042C180->field27 != 0)
					setSpecialMode();
				else
					SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(
					    lbl_8042C180, 0x30, lbl_8042C180->nextMode);
				if (result == 3)
					fn_800A74BC(0);
				break;
		}
	}
}
