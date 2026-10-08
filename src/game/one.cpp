#include "game/one.h"
#include "game/expasm.h"
#include "MSL_C/string.h"

// Layout and method names are corroborated by symbolic metadata; behavior and
// platform-specific methods follow the GameCube target. See one-unit-evidence.md.
struct RwStreamMemory {
	u32 position;
	u32 nSize;
	u8* memBlock;
};
struct RwStream {
	s32 type, accessType, position;
	union {
		RwStreamMemory memory;
		u8 custom[20];
	} Type;
	s32 rwOwned;
};
struct RwChunkHeaderInfo {
	u32 type, length, version, buildNum;
	s32 isComplex;
};
struct OneMemoryFunctions {
	u8 preceding[0x134];
	void* (*allocate)(u32);
	void (*release)(void*);
};
extern "C" {
s32 strcmp(const char*, const char*);
char* strcpy(char*, const char*);
extern OneMemoryFunctions* lbl_8042C9A4;
char lbl_80253C00[] = "memoryOneFileNoRel.xxx";
char lbl_80253C18[] = "memoryOneFileRel.xxx";
RwStream* fn_80198000(s32, s32, const void*);
s32 fn_80197ED8(RwStream*, void*);
RwStream* fn_80193968(RwStream*, RwChunkHeaderInfo*);
s32 fn_80192F38(RwStream*, u32, u32*, u32*);
u32 fn_801979AC(RwStream*, void*, u32);
RwStream* fn_80041FF4(char*);
void* fn_80012994(u32);
void fn_800126C8(void*);
u32 fn_800D082C(u32);
void fn_800D06C0(void*, u32, u32);
void fn_80132770(NJS_MOTION*);
Rt2dMaestro* fn_80203B74(Rt2dMaestro*, RwStream*);
RpUVAnimAnimation* objRpUVAnimAnimationStreamRead__FP8RwStream(RwStream*);
RtAnimAnimation* fn_8020C398(RwStream*);
RpWorld* fn_8014E868(RwStream*);
RpDMorphAnimation* fn_8013BE18(RwStream*);
RpSpline* fn_8014D05C(RwStream*);
RpClump* fn_80150B88(RwStream*);
RwTexDictionary* fn_8019B744(RwStream*);
}

inline u32 ONEFILE::OpenData(u32 id, void* buffer)
{
	RwStream* stream;
	RwChunkHeaderInfo chunkInfo;
	u32 retVal = 0;
	if (!Exist())
		return 0;
	stream = fn_80198000(3, 1, &memInfo);
	if (fn_80192F38(stream, id, 0, 0)) {
		fn_80193968(stream, &chunkInfo);
		retVal = Expand2(stream->Type.memory.memBlock + stream->Type.memory.position - 12, buffer);
	}
	fn_80197ED8(stream, 0);
	return retVal;
}

ONEFILE::ONEFILE(char* filename, s32 flag)
{
	fname[0]  = 0;
	exBuffer  = 0;
	showError = 0;
	if (filename)
		flagBW = 1;
	else
		flagBW = flag;
	if (filename)
		LoadOneFile(filename);
}

ONEFILE::~ONEFILE()
{
	ReleaseOneFile();
}

s32 ONEFILE::LoadOneFile(char* filename)
{
	RwStream* stream;
	RwChunkHeaderInfo chunkInfo;
	s32* tmpBuffer;
	if (!filename) {
		if (Exist())
			return 1;
		ReleaseOneFile();
		return 0;
	}
	if (!strcmp(fname, filename))
		return 1;
	ReleaseOneFile();
	stream = fn_80041FF4(filename);
	if (!stream)
		return 0;
	fn_80193968(stream, &chunkInfo);
	tmpBuffer = !flagBW ? (s32*)lbl_8042C9A4->allocate(chunkInfo.length)
	                    : (s32*)fn_80012994(chunkInfo.length);
	if (!tmpBuffer)
		return 0;
	chunkInfo.length = fn_801979AC(stream, tmpBuffer, chunkInfo.length);
	fn_80197ED8(stream, 0);
	memInfo.start  = (u8*)tmpBuffer;
	memInfo.length = chunkInfo.length;
	oneFileInfo    = (ONE_FILEINFO*)(memInfo.start + 12);
	strcpy(fname, filename);
	return 1;
}

s32 ONEFILE::SetOneFile(void* buffer, s32 size, s32 releaseFlag)
{
	ReleaseOneFile();
	memInfo.start  = (u8*)buffer;
	memInfo.length = size;
	oneFileInfo    = (ONE_FILEINFO*)(memInfo.start + 12);
	if (releaseFlag)
		strcpy(fname, lbl_80253C18);
	else
		strcpy(fname, lbl_80253C00);
	return 1;
}

s32 ONEFILE::ReleaseOneFile()
{
	if (Exist()) {
		if (strcmp(fname, lbl_80253C00)) {
			if (!flagBW)
				lbl_8042C9A4->release(memInfo.start);
			else
				fn_800126C8(memInfo.start);
		}
		memInfo.start = 0;
		fname[0]      = 0;
		return 1;
	}
	return 0;
}

s32 ONEFILE::CheckFileID(char* filename)
{
	char _filetmp[64];
	s32 _tmp;
	if (!Exist())
		return -1;
	if (!filename)
		return -1;
	for (_tmp = 0; _tmp < 64; _tmp++) {
		if (filename[_tmp] >= 'a' && filename[_tmp] <= 'z')
			_filetmp[_tmp] = filename[_tmp] - 32;
		else
			_filetmp[_tmp] = filename[_tmp];
		if (!_filetmp[_tmp])
			break;
	}
	for (s32 i = 2; i < 256; i++) {
		if (!strcmp(oneFileInfo->filename[i], _filetmp))
			return i;
	}
	return -1;
}

char* ONEFILE::CheckFileName(s32 id)
{
	if (!Exist())
		return 0;
	if (id < 2)
		return 0;
	return oneFileInfo->filename[id];
}

RwTexDictionary* ONEFILE::OneFileLoadTextureDictionay(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RwTexDictionary* _texdict = 0;
	_mem.length               = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 22, 0, 0))
		_texdict = fn_8019B744(stream);
	fn_80197ED8(stream, 0);
	return _texdict;
}

RpClump* ONEFILE::OneFileLoadClump(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RpClump* _clump = 0;
	_mem.length     = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 16, 0, 0))
		_clump = fn_80150B88(stream);
	fn_80197ED8(stream, 0);
	return _clump;
}

extern "C" u32 fn_800BC370(ONEFILE* archive, u32 id, void*, u32* size)
{
	u32 alignedSize;
	RwStream* stream;
	RwChunkHeaderInfo chunkInfo;
	u32 address;
	void* buffer;
	if (!archive->Exist())
		return 0;
	stream = fn_80198000(3, 1, &archive->memInfo);
	if (fn_80192F38(stream, id, size, 0)) {
		fn_80193968(stream, &chunkInfo);
		*size += 12;
		alignedSize = (*size + 31) & ~31;
		address     = fn_800D082C(alignedSize);
		buffer      = fn_80012994(*size);
		memcpy(buffer, stream->Type.memory.memBlock + stream->Type.memory.position - 12, *size);
		fn_800D06C0(buffer, address, alignedSize);
		*size = alignedSize;
		fn_800126C8(buffer);
	}
	fn_80197ED8(stream, 0);
	// The retail failure path also returns an uninitialized address.
	return address;
}

RpSpline* ONEFILE::OneFileLoadSpline(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RpSpline* _spline = 0;
	_mem.length       = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 12, 0, 0))
		_spline = fn_8014D05C(stream);
	fn_80197ED8(stream, 0);
	return _spline;
}

RpDMorphAnimation* ONEFILE::OneFileLoadDeltaMorph(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RpDMorphAnimation* _dmorph = 0;
	_mem.length                = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 30, 0, 0))
		_dmorph = fn_8013BE18(stream);
	fn_80197ED8(stream, 0);
	return _dmorph;
}

RpWorld* ONEFILE::OneFileLoadWorld(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RpWorld* _world = 0;
	_mem.length     = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 11, 0, 0))
		_world = fn_8014E868(stream);
	fn_80197ED8(stream, 0);
	return _world;
}

RtAnimAnimation* ONEFILE::OneFileLoadHAnimation(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RtAnimAnimation* _anim = 0;
	_mem.length            = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 27, 0, 0))
		_anim = fn_8020C398(stream);
	fn_80197ED8(stream, 0);
	return _anim;
}

RpUVAnimAnimation* ONEFILE::OneFileLoadUVAnim(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	RpUVAnimAnimation* _uvanim = 0;
	_mem.length                = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 27, 0, 0))
		_uvanim = objRpUVAnimAnimationStreamRead__FP8RwStream(stream);
	fn_80197ED8(stream, 0);
	return _uvanim;
}

Rt2dMaestro* ONEFILE::OneFileLoadMaestro(u32 id, void* buffer)
{
	RwMemory _mem;
	RwStream* stream;
	Rt2dMaestro* _maestro = 0;
	_mem.length           = OpenData(id, buffer);
	if (!_mem.length)
		return 0;
	_mem.start = (u8*)buffer;
	stream     = fn_80198000(3, 1, &_mem);
	if (fn_80192F38(stream, 433, 0, 0))
		_maestro = fn_80203B74(0, stream);
	fn_80197ED8(stream, 0);
	return _maestro;
}

NJS_MOTION* ONEFILE::OneFileLoadCameraTmb(u32 id, void* buffer)
{
	u32 size = OpenData(id, buffer);
	if (!size)
		return 0;
	NJS_MOTION* _motion = (NJS_MOTION*)lbl_8042C9A4->allocate(size);
	memcpy(_motion, buffer, size);
	fn_80132770(_motion);
	return _motion;
}

RpClump* ONEFILE::LoadClumpEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadClump(id, exBuffer);
	return 0;
}

RpSpline* ONEFILE::LoadSplineEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadSpline(id, exBuffer);
	return 0;
}

RpDMorphAnimation* ONEFILE::LoadDeltaMorphEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadDeltaMorph(id, exBuffer);
	return 0;
}

RtAnimAnimation* ONEFILE::LoadHAnimationEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadHAnimation(id, exBuffer);
	return 0;
}

RpUVAnimAnimation* ONEFILE::LoadUVAnimationEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadUVAnim(id, exBuffer);
	return 0;
}

NJS_MOTION* ONEFILE::LoadCameraTmbEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadCameraTmb(id, exBuffer);
	return 0;
}

Rt2dMaestro* ONEFILE::LoadMaestroEx(u32 id, char* oneFilename)
{
	if (LoadOneFile(oneFilename))
		return OneFileLoadMaestro(id, exBuffer);
	return 0;
}

extern "C" void fn_800BA7F8(ONEFILE* archive, void* buffer, u32 size)
{
	RwMemory mem;
	RwChunkHeaderInfo chunkInfo;
	mem.start        = (u8*)buffer;
	mem.length       = size;
	RwStream* stream = fn_80198000(3, 1, &mem);
	if (stream) {
		RwStream* header = fn_80193968(stream, &chunkInfo);
		if (header) {
			archive->memInfo.start  = header->Type.memory.memBlock + header->Type.memory.position;
			archive->memInfo.length = chunkInfo.length;
			archive->oneFileInfo    = (ONE_FILEINFO*)(archive->memInfo.start + 12);
			strcpy(archive->fname, lbl_80253C00);
		}
		fn_80197ED8(stream, 0);
	}
}
