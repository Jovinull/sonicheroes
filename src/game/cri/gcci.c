#include "types.h"

// CRI GCCI for GameCube: the file layer the stream controller sits on, wrapping
// the Dolphin DVD calls behind CRI's handle and error conventions.
//
// The unit runs from fn_8021E3D8 at 0x8021E3D8 to the end of fn_8021F404 at
// 0x8021F410, fifteen functions, and owns .rodata 0x8023FBC0 to 0x8023FDF8,
// .data 0x8029B7B8 to 0x8029B828 and .bss 0x8041F6B8 to 0x80420770. The disc
// ships no map, so the bounds are argued. Four lines agree:
//
//   The .rodata opens with the module's own version banner, "\nGCCI Ver.1.09
//   Build:May  9 2003 17:09:53\n", and every other string in the block is one
//   of this module's messages. CRI writes the banner into the library's main
//   source file.
//
//   Every .rodata, .data and .bss label the run touches has all of its users
//   inside the run. That was checked one label at a time, eleven of them, and
//   not one leaks: the error hook pair at 0x8041F6C4 and 0x8041F6C8 is reached
//   by eight functions here and by nothing else in the binary.
//
//   All three data sections are contiguous and abut their neighbours exactly.
//   The .rodata ends at 0x8023FDF8, which is where game/cri/lsc.c's begins.
//
//   The lower bound is the first cut where no data crosses; below it
//   fn_8021E118 and fn_8021E3D8 share nothing. The upper bound is fn_8021F410,
//   the shared error reporter that lsc.c also calls, so it belongs to neither.
//
// Nothing is named yet. The messages here carry no function names -- unlike
// MFCI and LSC, whose "(mfCiOpen)" and "(LSC_Create)" suffixes gave the naming
// away -- so every function keeps its dtk name until something anchors it.

typedef void (*GcciErrFunc)(void* obj, const char* msg, void* arg);
typedef void (*GcciFunc)(void);

typedef void (*DVDCBCallback)(s32 result, void* block);
typedef void (*DVDCallback)(s32 result, void* info);

typedef struct DVDCommandBlock {
	void* next;
	void* prev;
	u32 command;
	s32 state;
	u32 offset;
	u32 length;
	void* buffer;
	u32 currentTransferSize;
	u32 transferredSize;
	void* diskId;
	DVDCBCallback callback;
	void* userData;
} DVDCommandBlock;

typedef struct DVDFileInfo {
	DVDCommandBlock block;
	u32 startAddress;
	u32 length;
	DVDCallback callback;
} DVDFileInfo;

typedef struct GcciObj {
	/* 0x00 */ s8 stat;
	/* 0x01 */ s8 pad01;
	/* 0x02 */ s8 busy;
	/* 0x03 */ s8 pad03[5];
	/* 0x08 */ void* buffer;
	/* 0x0C */ s32 dvdStatus;
	/* 0x10 */ s32 sctsize;
	/* 0x14 */ s32 size;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s32 pos;
	/* 0x20 */ s32 total;
	/* 0x24 */ s32 rdsct;
	/* 0x28 */ DVDFileInfo fileInfo;
} GcciObj;

#define GCCI_OBJ_MAX  40
#define GCCI_SCT_SIZE 2048

extern void* memset(void* p, int c, u32 n);
extern char* strcpy(char* dst, const char* src);
extern char* strcat(char* dst, const char* src);
extern u32 strlen(const char* str);
extern s32 DVDOpen(const char* path, DVDFileInfo* fileInfo);
extern s32 DVDClose(DVDFileInfo* fileInfo);
extern s32 DVDGetCommandBlockStatus(void* block);
extern s32 DVDGetTransferredSize(void* block);
extern s32 DVDGetDriveStatus(void);
extern s32 DVDCancel(void* block);
extern u32 OSGetTick(void);
extern s32 DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* buffer, s32 length, s32 offset,
    DVDCallback callback, s32 priority);
extern s32 DVDReadPrio(DVDFileInfo* fileInfo, void* buffer, s32 length, s32 offset, s32 priority);
extern void fn_8021E3D4(s32 result, void* fileInfo);
extern void DCInvalidateRange(void* ptr, u32 size);
extern void DCStoreRange(void* ptr, u32 size);

const char gcci_Ver[]              = "\nGCCI Ver.1.09 Build:May  9 2003 17:09:53\n";
const char gcci_ErrHandl[]         = "E0092912:handl is null.";
const char gcci_ErrHandl2[]        = "E0040302:handl is null.";
const char gcci_ErrSize[]          = "E0040303:invalidate size.";
const char gcci_ErrHandl3[]        = "E0040301:handl is null.";
const char gcci_ErrCancel[]        = "E0092917:DVDCancel failed.";
const char gcci_ErrCancelTimeout[] = "E0092918:DVDCancel time out.";
const char gcci_ErrReqCount[]      = "E0092913:nsct < 0.(gcCiReqRd)";
const char gcci_ErrReqBuffer[]     = "E0092914:buf is null.(gcCiReqRd)";
const char gcci_ErrOpenName[]      = "E0092908:fname is null.(gcCiOpen)";
const char gcci_ErrOpenRw[]        = "E0092909:rw is illigal.(gcCiOpen)";
const char gcci_ErrOpenResource[]  = "E0092910:not enough handle resource.(gcCiOpen)";
const char gcci_ErrOpenDvd[]       = "E0092911:DVDOpen fail.(gcCiOpen)";
const char gcci_ErrFileName[]      = "E0092901:fname is null.(gcCiGetFileSize)";
const char gcci_ErrFileOpen[]      = "E0040201:can't open a file.(gcCiGetFileSize)";
const char gcci_ErrFileClose[]     = "E0040202:can't close a file.(gcCiGetFileSize)";

static s32 gcci_DvdStatus;
static s8 gcci_Busy;
static s32 gcci_Canceling;
static void* gcci_ErrObj;
static GcciErrFunc gcci_ErrFunc;
static GcciObj gcci_ObjTbl[GCCI_OBJ_MAX];
static s32 gcci_Unknown;
static char gcci_WorkStr[0x100];

s32 fn_8021E3D8(GcciObj* p);
void fn_8021E438(GcciObj* p, s32 sctsize);
s32 fn_8021E51C(GcciObj* p);
s32 fn_8021E57C(GcciObj* p);
void fn_8021E5E0(GcciObj* p);
s32 fn_8021E780(GcciObj* p, s32 nsct, void* buffer);
s32 fn_8021EBA8(GcciObj* p);
s32 fn_8021EC08(GcciObj* p, s32 off, s32 whence);
void fn_8021ECD4(GcciObj* p);
GcciObj* fn_8021EE98(const char* fname, s32 mode, s32 rw);
u32 fn_8021F0A8(const char* fname);
void fn_8021F20C(GcciErrFunc func, void* obj);
void fn_8021F220(void);

GcciFunc gcci_IfTbl[26] = {
	(GcciFunc)fn_8021F220,
	(GcciFunc)fn_8021F20C,
	(GcciFunc)fn_8021F0A8,
	NULL,
	(GcciFunc)fn_8021EE98,
	(GcciFunc)fn_8021ECD4,
	(GcciFunc)fn_8021EC08,
	(GcciFunc)fn_8021EBA8,
	(GcciFunc)fn_8021E780,
	NULL,
	(GcciFunc)fn_8021E5E0,
	(GcciFunc)fn_8021E57C,
	(GcciFunc)fn_8021E51C,
	(GcciFunc)fn_8021E438,
	(GcciFunc)fn_8021E3D8,
};

static s32 gcci_ReadMode;
static s32 gcci_DataPad;

static void gcci_Error(const char* msg)
{
	if (gcci_ErrFunc != NULL) {
		gcci_ErrFunc(gcci_ErrObj, msg, NULL);
	}
}

static void gcci_ErrorArg(const char* msg, void* arg)
{
	if (gcci_ErrFunc != NULL) {
		gcci_ErrFunc(gcci_ErrObj, msg, arg);
	}
}

static u32 gcci_GetMilliseconds(void)
{
	return OSGetTick() / ((*(u32*)0x800000F8 >> 2) / 1000);
}

static inline void gcci_Stop(GcciObj* p)
{
	u32 start;
	u32 now;
	u32 elapsed;
	s32 done;
	s32 result;

	if (p->busy == 1) {
		return;
	}
	if (p->busy == 0) {
		return;
	}
	DVDGetCommandBlockStatus(&p->fileInfo);
	DVDGetDriveStatus();
	gcci_Canceling = 1;
	result         = DVDCancel(&p->fileInfo);
	gcci_Canceling = 0;
	if (result < 0) {
		gcci_ErrorArg(gcci_ErrCancel, p);
		return;
	}
	start = gcci_GetMilliseconds();
	for (;;) {
		p->dvdStatus   = DVDGetCommandBlockStatus(&p->fileInfo);
		gcci_DvdStatus = p->dvdStatus;
		now            = gcci_GetMilliseconds();
		elapsed        = now < start ? now + (-1U - start) : now - start;
		if (elapsed > 2000) {
			gcci_ErrorArg(gcci_ErrCancelTimeout, p);
			break;
		}
		done = p->dvdStatus == 0 || p->dvdStatus == 10;
		if (done) {
			break;
		}
	}
	p->busy   = 0;
	gcci_Busy = 0;
	DVDGetCommandBlockStatus(&p->fileInfo);
	DVDGetDriveStatus();
}

static void gcci_SetNsct(GcciObj* p)
{
	s32 n;

	n       = p->sctsize + p->size;
	n       = n - 1;
	p->nsct = n / p->sctsize;
}

s32 fn_8021E3D8(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->total;
}

void fn_8021E438(GcciObj* p, s32 sctsize)
{
	s32 total;

	if (p == NULL) {
		gcci_Error(gcci_ErrHandl2);
		return;
	}
	if (p->sctsize % 32 != 0) {
		gcci_Error(gcci_ErrSize);
		return;
	}
	total      = p->pos * p->sctsize;
	p->sctsize = sctsize;
	gcci_SetNsct(p);
	p->pos   = total / p->sctsize;
	p->total = p->rdsct * sctsize;
}

s32 fn_8021E51C(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl3);
		return 0;
	}
	return p->sctsize;
}

s32 fn_8021E57C(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->busy;
}

void fn_8021E5E0(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return;
	}
	gcci_Stop(p);
}

s32 fn_8021E780(GcciObj* p, s32 nsct, void* buffer)
{
	GcciObj* q;
	s32 i;
	s32 ready;
	s32 offset;
	s32 length;
	s32 result;

	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	if (nsct < 0) {
		gcci_ErrorArg(gcci_ErrReqCount, p);
		return 0;
	}
	if (buffer == NULL) {
		gcci_ErrorArg(gcci_ErrReqBuffer, p);
		return 0;
	}
	ready = p->busy == 1 || p->busy == 0;
	if (!ready) {
		return 0;
	}
	ready = p->dvdStatus == 0 || p->dvdStatus == 10;
	if (!ready) {
		return 0;
	}
	q = gcci_ObjTbl;
	for (i = 0; i < GCCI_OBJ_MAX; i++, q++) {
		if (q->stat == 1 && q->busy == 2) {
			return 0;
		}
	}
	if (nsct == 0) {
		p->busy   = 1;
		gcci_Busy = 1;
		return 0;
	}
	p->total  = 0;
	p->buffer = buffer;
	p->rdsct  = nsct;
	fn_8021F220();
	offset = p->pos * p->sctsize;
	length = p->rdsct * p->sctsize;
	if (offset + length > p->size) {
		length = p->size - offset;
		if (length < 0) {
			p->busy   = 1;
			gcci_Busy = 1;
			return nsct;
		}
	}
	length = (length + 31) & ~31;
	DCInvalidateRange(buffer, length);
	if (gcci_ReadMode == 0) {
		result = DVDReadAsyncPrio(&p->fileInfo, buffer, length, offset, fn_8021E3D4, 2);
	} else {
		result = DVDReadPrio(&p->fileInfo, buffer, length, offset, 2);
	}
	if (result == 0) {
		return 0;
	}
	p->busy   = 2;
	gcci_Busy = 2;
	return p->rdsct;
}

s32 fn_8021EBA8(GcciObj* p)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	return p->pos;
}

s32 fn_8021EC08(GcciObj* p, s32 off, s32 whence)
{
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
		return 0;
	}
	if (whence == 0) {
		p->pos = off;
	} else if (whence == 2) {
		p->pos = p->nsct + off;
	} else if (whence == 1) {
		p->pos = p->pos + off;
	}
	p->pos = p->pos < p->nsct ? p->pos : p->nsct;
	if (p->pos > 0) {
		if (p->pos && p->pos) {
		}
	} else {
		p->pos = 0;
	}
	return p->pos;
}

void fn_8021ECD4(GcciObj* p)
{
	if (p == NULL) {
		return;
	}
	if (p == NULL) {
		gcci_Error(gcci_ErrHandl);
	} else {
		gcci_Stop(p);
	}
	DVDClose(&p->fileInfo);
	p->stat = 0;
	memset(p, 0, sizeof(GcciObj));
}

GcciObj* fn_8021EE98(const char* fname, s32 mode, s32 rw)
{
	GcciObj* p;
	char path[0x100];
	s32 i;
	char* q;

	if (fname == NULL) {
		gcci_Error(gcci_ErrOpenName);
		return NULL;
	}
	if (rw != 0) {
		gcci_Error(gcci_ErrOpenRw);
		return NULL;
	}
	p = NULL;
	for (i = 0; i < GCCI_OBJ_MAX; i++) {
		if (gcci_ObjTbl[i].stat == 0) {
			p = &gcci_ObjTbl[i];
			break;
		}
	}
	if (p == NULL) {
		gcci_Error(gcci_ErrOpenResource);
		return NULL;
	}
	strcpy(path, gcci_WorkStr);
	strcat(path, fname);
	q = path;
	i = strlen(path);
	while (i != 0) {
		if (*q == '\\') {
			*q = '/';
		}
		q++;
		i--;
	}
	if (DVDOpen(path, &p->fileInfo) == 0) {
		gcci_Error(gcci_ErrOpenDvd);
		memset(p, 0, sizeof(GcciObj));
		return NULL;
	}
	p->sctsize = GCCI_SCT_SIZE;
	p->size    = p->fileInfo.length;
	if (p->size & 0x80000000) {
		p->size = 0x7FFFFFFF;
	}
	gcci_SetNsct(p);
	p->pos    = 0;
	p->buffer = NULL;
	p->rdsct  = 0;
	p->total  = 0;
	p->busy   = 0;
	p->stat   = 1;
	return p;
}

u32 fn_8021F0A8(const char* fname)
{
	DVDFileInfo fileInfo;
	char path[0x100];
	u32 size;
	s32 i;
	char* p;

	if (fname == NULL) {
		gcci_Error(gcci_ErrFileName);
		return 0;
	}
	strcpy(path, gcci_WorkStr);
	strcat(path, fname);
	p = path;
	i = strlen(path);
	while (i != 0) {
		if (*p == '\\') {
			*p = '/';
		}
		p++;
		i--;
	}
	if (DVDOpen(path, &fileInfo) == 0) {
		gcci_Error(gcci_ErrFileOpen);
		return 0;
	}
	size = fileInfo.length;
	if (size & 0x80000000) {
		size = 0x7FFFFFFF;
	}
	if (DVDClose(&fileInfo) == 0) {
		gcci_Error(gcci_ErrFileClose);
		return 0;
	}
	return size;
}

void fn_8021F20C(GcciErrFunc func, void* obj)
{
	gcci_ErrFunc = func;
	gcci_ErrObj  = obj;
}

void fn_8021F220(void)
{
	GcciObj* p;
	s32 i;
	s32 transferred;
	s32 total;
	s32 over;
	void* end;

	p = gcci_ObjTbl;
	for (i = 0; i < GCCI_OBJ_MAX; i++, p++) {
		if (p->stat == 1 && p->busy == 2) {
			p->dvdStatus   = DVDGetCommandBlockStatus(&p->fileInfo);
			gcci_DvdStatus = p->dvdStatus;
			switch (p->dvdStatus) {
				case -1:
					p->busy   = 3;
					gcci_Busy = 3;
					break;
				case 0:
					total = p->rdsct * p->sctsize;
					DCInvalidateRange(p->buffer, total);
					p->total = total;
					p->pos += p->rdsct;
					if (p->pos * p->sctsize > p->size) {
						over = p->pos * p->sctsize - p->size;
						end  = (char*)p->buffer + p->total - over;
						memset(end, 0, over);
						DCStoreRange(end, over);
					}
					p->busy   = 1;
					gcci_Busy = 1;
					break;
				case 10:
					transferred = DVDGetTransferredSize(&p->fileInfo);
					DCInvalidateRange(p->buffer, transferred);
					gcci_Busy = 0;
					p->total  = p->sctsize * (transferred / p->sctsize);
					p->pos += transferred / p->sctsize;
					p->busy = 0;
					break;
			}
		}
	}
}

void* fn_8021F398(void)
{
	gcci_Unknown = gcci_Unknown;
	memset(gcci_WorkStr, 0, sizeof(gcci_WorkStr));
	gcci_ErrFunc = NULL;
	gcci_ErrObj  = NULL;
	memset(&gcci_DvdStatus, 0, 12);
	return gcci_IfTbl;
}

void fn_8021F404(void* arg0, void* arg1, void* arg2, s32 mode)
{
	gcci_ReadMode = mode;
}
