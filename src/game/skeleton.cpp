typedef unsigned int u32;

struct RwRect {
	u32 w;
	u32 h;
	unsigned char pad[24];
};

struct RwVideoMode {
	unsigned char pad0[0xC];
	u32 width;
	u32 height;
};

struct RsGlobalType {
	const char* appName;
	int maximumWidth;
	int maximumHeight;
	int maximumFPS;
	int quit;
	int field14;
	int field18;
	int field1C;
	int field20;
	int field24;
	int field28;
	int field2C;
	int field30;
	int field34;
	int field38;
	int field3C;
};

struct RwEngineFunctions {
	unsigned char pad0[0x120];
	int (*getVideoMode)(int);
};

struct RwGlobals {
	unsigned char pad0[0x60];
	RwVideoMode* mode;
};

enum RsEventStatus { rsEVENTERROR = 0, rsEVENTPROCESSED = 1, rsEVENTNOTPROCESSED = 2 };

extern "C" {
extern RwEngineFunctions* lbl_8042C9A4;

int RsInitialize();
int RsRwInitialize(void*);
void RsRwTerminate();
RsEventStatus RsEventHandler(int, void*);
void* RsTerminate(void*);
void RsErrorMessage(void*);
void fn_80178220(void*, RwRect*);
void fn_80177DC8(void*, void*, int, int, int);
int fn_80012C50();
void* fn_80012E50();
int fn_8019DB5C(void*, int, int);
void fn_80012E2C();
int fn_8019D86C(void*);
void fn_8019DB0C();
void fn_8019D79C();
int fn_8019D644();
void fn_80012E24();
int fn_8017867C();
void fn_80178608();
void fn_801A47EC(void*, int);
void fn_801A46D0();
char* fn_80012EA0(const char*);
void fn_80012E5C(void*);
RsEventStatus AppEventHandler(int, void*);
int fn_80012C08(int);
int fn_801C3C04(void*, const char*);
int fn_801A0470(const char*, void*, int);
void fn_80176DC8();
void fn_801922D8();
void fn_80012C10();
void fn_8019D558();
void EndianConversionNoop__Fv(void*);
void fn_80013010(void*);
void _skyChgDir(void*);
}

extern "C" {
RsGlobalType RsGlobal;
int sUseVideoMode = 1;
char rsAppName[]  = "RenderWare Application";
}

#pragma force_active on

extern "C" void RsCameraSize(void* camera, void* rect, int viewWindow, int aspectRatio, int flags)
{
	RwRect size;
	RwVideoMode* currentMode;
	int width;
	int height;
	int selectedMode;

	currentMode = (*(RwGlobals**)lbl_8042C9A4)->mode;
	width       = currentMode->width;
	height      = currentMode->height;

	fn_80178220(camera, &size);
	selectedMode = lbl_8042C9A4->getVideoMode((int)rect);

	viewWindow *= size.w;
	aspectRatio *= size.h;

	if (flags & 1) {
		viewWindow += size.w * 5;
	} else if (flags & 2) {
		viewWindow += width - size.w * (selectedMode + 5);
	}

	if ((u32)(flags - 1) <= 1 || flags == 0) {
		aspectRatio += (height - size.h) >> 1;
	}

	if (flags & 4) {
		aspectRatio += size.h * 2;
	} else if (flags & 8) {
		aspectRatio += height - size.h * 5;
	}

	if (flags == 4 || flags == 8 || flags == 0) {
		viewWindow += (width - size.w * selectedMode) >> 1;
	}

	fn_80177DC8(camera, rect, viewWindow, aspectRatio, 1);
}

static inline int RsInitializeImpl()
{
	RsGlobal.appName       = rsAppName;
	RsGlobal.maximumWidth  = 0;
	RsGlobal.maximumHeight = 0;
	RsGlobal.maximumFPS    = 0;
	RsGlobal.quit          = 0;
	RsGlobal.field18       = 0;
	RsGlobal.field20       = 0;
	RsGlobal.field1C       = 0;
	RsGlobal.field24       = 1;
	RsGlobal.field2C       = 0;
	RsGlobal.field28       = 0;
	RsGlobal.field30       = 2;
	RsGlobal.field38       = 0;
	RsGlobal.field34       = 0;
	return fn_80012C50();
}

extern "C" int RsInitialize()
{
	return RsInitializeImpl();
}

static inline int RsRwInitializeImpl(void* displayID)
{
	void* memoryFunctions = fn_80012E50();
	if (!fn_8019DB5C(memoryFunctions, 1, 0x100000)) {
		return 0;
	}

	fn_80012E2C();
	RsEventHandler(3, 0);
	if (!RsEventHandler(9, 0)) {
		return 0;
	}
	if (!RsEventHandler(4, 0)) {
		return 0;
	}

	void* parameter = displayID;
	if (!fn_8019D86C(&parameter)) {
		fn_8019DB0C();
		return 0;
	}
	if (!RsEventHandler(15, displayID)) {
		fn_8019D79C();
		fn_8019DB0C();
		return 0;
	}
	if (!fn_8019D644()) {
		fn_8019D79C();
		fn_8019DB0C();
		return 0;
	}

	RsEventHandler(10, 0);
	fn_80012E24();
	if (!fn_8017867C()) {
		fn_8019D558();
		fn_8019D79C();
		fn_8019DB0C();
		return 0;
	}
	return 1;
}

extern "C" int RsRwInitialize(void* displayID)
{
	return RsRwInitializeImpl(displayID);
}

static inline void RsRwTerminateImpl()
{
	fn_80178608();
	fn_801A47EC((void*)RsTerminate, 0);
	fn_8019D558();
	fn_8019D79C();
	fn_8019DB0C();
}

extern "C" void RsRwTerminate()
{
	RsRwTerminateImpl();
}

#pragma force_active reset

extern "C" void* RsTerminate(void* param)
{
	fn_801A46D0();
	return param;
}

extern "C" char* RsPathnameCreate(const char* path)
{
	return fn_80012EA0(path);
}

extern "C" void RsPathnameDestroy(void* path)
{
	fn_80012E5C(path);
}

extern "C" RsEventStatus RsEventHandler(int event, void* param)
{
	RsEventStatus result = AppEventHandler(event, param);

	if (event == 21) {
		RsGlobal.quit = 1;
	}

	if (result == rsEVENTNOTPROCESSED) {
		switch (event) {
			case 15:
				if (fn_80012C08(sUseVideoMode) != 0) {
					result = rsEVENTPROCESSED;
				} else {
					result = rsEVENTERROR;
				}
				break;
			case 1:
				AppEventHandler(2, param);
				result = rsEVENTPROCESSED;
				break;
			case 28:
				int found;
				if (fn_801C3C04(param, "-vms") == 0) {
					sUseVideoMode = 0;
					found         = 1;
				} else {
					found = 0;
				}
				if (found != 0) {
					result = rsEVENTPROCESSED;
				} else {
					result = rsEVENTERROR;
				}
				break;
			case 3:
				result = rsEVENTPROCESSED;
				break;
			case 10:
				int registered;
				if (fn_801A0470("bmp", (void*)fn_80176DC8, 0) == 0) {
					registered = 0;
				} else if (fn_801A0470("png", (void*)fn_801922D8, 0) == 0) {
					registered = 0;
				} else {
					registered = 1;
				}
				if (registered != 0) {
					result = rsEVENTPROCESSED;
				} else {
					result = rsEVENTERROR;
				}
				break;
			case 14:
				RsRwTerminateImpl();
				result = rsEVENTPROCESSED;
				break;
			case 13:
				int initialized;
				initialized = RsRwInitializeImpl(param);
				if (initialized != 0) {
					result = rsEVENTPROCESSED;
				} else {
					result = rsEVENTERROR;
				}
				break;
			case 17:
				fn_80012C10();
				result = rsEVENTPROCESSED;
				break;
			case 16:
				if (RsInitializeImpl() != 0) {
					result = rsEVENTPROCESSED;
				} else {
					result = rsEVENTERROR;
				}
				break;
			default:
				break;
		}
	}

	return result;
}

extern "C" void RsCameraShowRaster(void* camera)
{
	EndianConversionNoop__Fv(camera);
	fn_80013010(camera);
}

extern "C" void RsErrorMessage(void* param)
{
	int values[2];
	values[0] = 255;
	values[1] = 255;

	if (RsGlobal.field1C != 0) {
		((void (*)(int, int*))RsGlobal.field20)(20, values);
	}
	_skyChgDir(param);
}
