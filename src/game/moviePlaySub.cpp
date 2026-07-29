typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct FunctionHeap {
	u8 pad[0x134];
	void* (*allocate)(u32);
	void (*release)(void*);
};

class MovieSubtitleResource
{
	u8 storage[0x1b4];

public:
	MovieSubtitleResource(const char*);
};

struct SubtitleScale {
	float x;
	float y;
};

class SEQUENCE
{
public:
	virtual void Init();
	virtual void Loop();
	virtual void End();
};

class MOVIE_PLAY : public SEQUENCE
{
	int state[3];

public:
	virtual void Init();
	virtual void Loop();
	virtual void End();
};

extern "C" u8 MoviePlay[16];

extern "C" void* MovieSubBuffer;
extern "C" int MovieSubEvent;
extern "C" void* MovieSubRaster;
extern "C" void* MovieSubResource;
extern "C" FunctionHeap* lbl_8042C9A4;
extern "C" void fn_80139188();
extern "C" void fn_801390F0();
extern "C" void fn_80139120();
extern "C" void* __vt__8SEQUENCE[6];
extern "C" void* __vt__10MOVIE_PLAY[5];
struct GameSettings {
	u8 pad[0x11];
	s8 displayMode;
	u8 pad12;
	s8 language;
	u8 pad14[0x24];
	int screenMode;
};
extern "C" GameSettings* lbl_8042C180;
extern "C" void* lbl_8042C478;

extern "C" char lbl_8042BC88[] = "_j";
extern "C" char lbl_8042BC8C[] = "_e";
extern "C" char lbl_8042BC90[] = "_f";
extern "C" char lbl_8042BC94[] = "_s";
extern "C" char lbl_8042BC98[] = "_g";
extern "C" char lbl_8042BC9C[] = "_i";
extern "C" char lbl_8042BCA0[] = "_k";
extern "C" const char* const lbl_8028CF28[7];
extern "C" u8 lbl_8028CF44[48];
extern "C" char lbl_8028CF74[14];
extern "C" char lbl_8028CF84[12];
extern "C" char lbl_8042BCA4[8] = "ssss";
extern "C" const float lbl_8042F158;
extern "C" const float lbl_8042F15C;
extern "C" const float lbl_8042F160;
extern "C" const float lbl_8042F164;

extern "C" __declspec(align(4)) __declspec(section ".data") void* moviePlaySubVtableData[5]
    = { 0, 0, (void*)fn_80139188, (void*)fn_801390F0, (void*)fn_80139120 };
extern "C" const __declspec(section ".data") u8 moviePlaySubScaleData[16]
    = { 0x3d, 0xf1, 0xa9, 0xfc, 0, 0, 0, 0, 0x3d, 0xf1, 0xa9, 0xfc, 0x3e, 0x23, 0xd7, 0x0a };
extern "C" const __declspec(section ".data") char* const moviePlaySubLanguageData[7] = {
	lbl_8042BC88,
	lbl_8042BC8C,
	lbl_8042BC90,
	lbl_8042BC94,
	lbl_8042BC98,
	lbl_8042BC9C,
	lbl_8042BCA0,
};
extern "C" __declspec(section ".data") u8 moviePlaySubReportData[48] = {
	0x91,
	0xb6,
	0x8d,
	0xdd,
	0x82,
	0xb5,
	0x82,
	0xc8,
	0x82,
	0xa2,
	0x83,
	0x81,
	0x83,
	0x62,
	0x83,
	0x5a,
	0x81,
	0x5b,
	0x83,
	0x57,
	0x82,
	0xf0,
	0x95,
	0x5c,
	0x8e,
	0xa6,
	0x82,
	0xb5,
	0x82,
	0xe6,
	0x82,
	0xa4,
	0x82,
	0xc6,
	0x82,
	0xb5,
	0x82,
	0xc4,
	0x82,
	0xa2,
	0x82,
	0xe9,
	0x81,
	0x42,
	0x0a,
	0x00,
};
extern "C" __declspec(section ".data") char moviePlaySubScriptFormatData[14] = "event%04d.scr";
extern "C" __declspec(section ".data") char moviePlaySubEventFormatData[12]  = "event%04d%s";

extern "C" void fn_800CED64(void*, int);
extern "C" void fn_80042048(const char*, void*);
extern "C" void fn_8004BEE0(void*, const char*, int);
extern "C" void* memset(void*, int, u32);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void fn_80194294(int, int*);
extern "C" void fn_80194234(int, int);
extern "C" void fn_800CE5F0(void*, void*, float, float, int, float, float);
extern "C" void OSReport(const char*, ...);
#pragma bool off
#pragma opt_propagation off
static inline int IsEqual(const volatile s8& left, int right)
{
	return left == right;
}
#pragma opt_propagation on
#pragma bool on

struct SubtitleRecord {
	s16 enabled;
	s16 start;
	s16 duration;
	s16 image;
};

struct SubtitleRaster {
	int event;
	int image;
	void* raster;
};

extern "C" const SubtitleScale lbl_8028CF18[2];

extern "C" void __sinit_moviePlaySub_cpp()
{
	*(void**)MoviePlay = __vt__8SEQUENCE;
	*(void**)MoviePlay = __vt__10MOVIE_PLAY;
}
extern "C" __declspec(section ".ctors") void (*const moviePlaySubCtor)() = __sinit_moviePlaySub_cpp;

#pragma bool off
extern "C" void RenderMovieSubtitles(void*, int frame)
{
	int recordIndex;
	SubtitleRaster* entry;
	int event;
	SubtitleRaster* rasters;
	SubtitleRecord* record;
	void* raster;
	int saved10;
	int saved11;
	int saved20;
	float scaleX;
	float scaleY;
	SubtitleRecord* selected = 0;

	switch (lbl_8042C180->language) {
		case 0:
		case 6:
			record = (SubtitleRecord*)MovieSubBuffer;
			break;
		default:
			record = (SubtitleRecord*)((u8*)MovieSubBuffer + 0x100);
			break;
	}

	for (recordIndex = 0; recordIndex < 32; record++, recordIndex++) {
		if (record->enabled != 0 && frame >= record->start
		    && frame < record->start + record->duration
		    && (selected == 0 || record->start > selected->start)) {
			selected = record;
		}
	}

	if (selected == 0) {
		return;
	}

	recordIndex = 0;
	rasters     = (SubtitleRaster*)MovieSubRaster;
	entry       = rasters;
	event       = MovieSubEvent;
	for (; entry->event >= 0; entry++, recordIndex++) {
		if (event == entry->event && selected->image == entry->image) {
			raster = rasters[recordIndex].raster;
			goto found_raster;
		}
	}
	raster = 0;
found_raster:

	fn_80194294(10, &saved10);
	fn_80194294(11, &saved11);
	fn_80194294(20, &saved20);
	fn_80194234(20, 1);
	fn_80194234(10, 1);
	fn_80194234(11, 4);

	if (lbl_8042C180->screenMode != 5) {
		int index = IsEqual(lbl_8042C180->displayMode, 2);
		scaleX    = lbl_8028CF18[index].x;
		scaleY    = lbl_8028CF18[index].y;
	} else {
		scaleX = lbl_8042F158;
		scaleY = scaleX;
	}

	if (raster != 0) {
		if (MovieSubResource != 0) {
			fn_800CE5F0(MovieSubResource, raster, lbl_8042F15C, lbl_8042F160, 1, scaleX, scaleY);
		} else {
			fn_800CE5F0(lbl_8042C478, raster, lbl_8042F15C, lbl_8042F160, 1, scaleX, scaleY);
		}
	} else {
		OSReport((const char*)lbl_8028CF44);
	}

	fn_80194234(10, 5);
	fn_80194234(11, 4);

	if (raster != 0) {
		if (MovieSubResource != 0) {
			fn_800CE5F0(MovieSubResource, raster, lbl_8042F158, lbl_8042F164, 1, scaleX, scaleY);
		} else {
			fn_800CE5F0(lbl_8042C478, raster, lbl_8042F158, lbl_8042F164, 1, scaleX, scaleY);
		}
	} else {
		OSReport((const char*)lbl_8028CF44);
	}

	fn_80194234(10, saved10);
	fn_80194234(11, saved11);
	fn_80194234(20, saved20);
}
#pragma bool on

extern "C" void FinalizeMoviePlaySub()
{
	if (MovieSubResource != 0) {
		fn_800CED64(MovieSubResource, 1);
		MovieSubResource = 0;
	}

	if (MovieSubBuffer != 0) {
		lbl_8042C9A4->release(MovieSubBuffer);
		MovieSubBuffer = 0;
	}
}

extern "C" void InitializeMoviePlaySub(void*, int event, void** rasters)
{
	char path[256];

	FinalizeMoviePlaySub();
	MovieSubEvent  = event;
	MovieSubBuffer = lbl_8042C9A4->allocate(0x700);
	memset(MovieSubBuffer, 0, 0x700);

	if (event >= 0) {
		sprintf(path, lbl_8028CF74, event);
		fn_80042048(path, MovieSubBuffer);
		fn_8004BEE0(MovieSubBuffer, lbl_8042BCA4, 0xe0);
		sprintf(path, lbl_8028CF84, event, lbl_8028CF28[lbl_8042C180->language]);

		switch (lbl_8042C180->language) {
			case 0: {
				MovieSubtitleResource* resource = new MovieSubtitleResource(path);
				MovieSubResource                = resource;
				MovieSubRaster                  = rasters[0];
				break;
			}
			case 1:
				MovieSubRaster = rasters[1];
				break;
			case 2:
				MovieSubRaster = rasters[2];
				break;
			case 3:
				MovieSubRaster = rasters[3];
				break;
			case 4:
				MovieSubRaster = rasters[4];
				break;
			case 5:
				MovieSubRaster = rasters[5];
				break;
			case 6: {
				MovieSubtitleResource* resource = new MovieSubtitleResource(path);
				MovieSubResource                = resource;
				MovieSubRaster                  = rasters[6];
				break;
			}
		}
	} else {
		MovieSubResource = 0;
		MovieSubRaster   = 0;
	}
}
extern "C" void* movieSubBufferData   = 0;
extern "C" int movieSubEventData      = 0;
extern "C" void* movieSubRasterData   = 0;
extern "C" void* movieSubResourceData = 0;
extern "C" {
u8 MoviePlay[16];
}
extern "C" const __declspec(section ".sdata2") float lbl_8042F158 = 0.0f;
extern "C" const __declspec(section ".sdata2") float lbl_8042F15C = 0.005f;
extern "C" const __declspec(section ".sdata2") float lbl_8042F160 = 0.155f;
extern "C" const __declspec(section ".sdata2") float lbl_8042F164 = 0.16f;
