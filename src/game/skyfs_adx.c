#include "types.h"

/*
 * GameCube adaptation of RenderWare's PS2 skyfs_adx.c translation unit.
 *
 * The public PS2 source and beta DWARF establish the skyFile/RwFileFunctions
 * types, callback signatures, function names, and source order.  The
 * GameCube fields and DVD implementation below come from the target code.
 * CodeWarrior compiles this as C++ with C linkage and deferred code emission.
 *
 * The original-file boundary is established by the PS2 beta DWARF path
 * D:\Tsonic\Tsonic\skel\sky\skyfs_adx.c.  On GameCube it owns the complete
 * private file state and callback tables from _skyChgDir through
 * skyTransMode: .text 0x80013038-0x80014154, extab
 * 0x80005788-0x800057D8, extabindex 0x8000BD4C-0x8000BDC4, .data
 * 0x802406F0-0x802408F8, .sdata 0x8042AD78-0x8042AD7E, and .sbss
 * 0x8042C0C8-0x8042C0E0.
 *
 * The complete translation unit matches the original object byte-for-byte.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Callback)(s32);
typedef Callback StateCallback;

typedef struct DVDFileInfo {
	u8 block[0x30];
	u32 startAddress;
	u32 length;
	Callback callback;
} DVDFileInfo;

typedef union FileHandle {
	DVDFileInfo fileInfo;
	void* fioHandle;
} FileHandle;

typedef struct skyFile {
	u8 buffer[0x2800];
	FileHandle fileHandle;
	u32 position;
	u32 length;
	u32 bufferPosition;
	s32 readable;
} skyFile;

typedef struct RwFileFunctions {
	void* entries[11];
} RwFileFunctions;

typedef struct RwModuleInfo {
	s32 globalsOffset;
	s32 numInstances;
} RwModuleInfo;

typedef void* (*RwPluginObjectConstructor)(void*, s32, s32);
typedef void* (*RwPluginObjectDestructor)(void*, s32, s32);

extern s32 DVDReadAsyncPrio(DVDFileInfo*, void*, s32, s32, Callback, s32);
extern s32 DVDGetDriveStatus(void);
extern s32 DVDGetCommandBlockStatus(void*);
extern s32 DVDOpen(const char*, DVDFileInfo*);
extern s32 DVDClose(DVDFileInfo*);
extern void DVDInit(void);
extern void* memcpy(void*, const void*, u32);

extern RwFileFunctions* RwOsGetFileInterface(void);
extern s32 RwEngineRegisterPlugin(s32, u32, RwPluginObjectConstructor, RwPluginObjectDestructor);
extern void* RwFreeListCreate(s32, s32, s32);
extern void RwFreeListDestroy(void*);
extern u8* lbl_8042C9A4;

s32 skyTransMode(const char*);
char* skyFgets(char*, s32, void*);
s32 skyFseek(void*, long, s32);
u32 skyFwrite(const void*, u32, u32, void*);
u32 skyFread(void*, u32, u32, void*);
void* _rwSkyFSClose(void*, s32, s32);
void* _rwSkyFSOpen(void*, s32, s32);

/* C++ preserves these definitions in source order, matching the
 * original ascending .sbss layout. */
s32 lbl_8042C0C8;
RwModuleInfo lbl_8042C0CC;
void* lbl_8042C0D4;
Callback lbl_8042C0D8;
Callback lbl_8042C0DC;

u32 lbl_8042AD78     = 0x430;
char lbl_8042AD7C[2] = "r";

#pragma force_active on
#pragma inline_depth(10)
#pragma inline_max_size(10000)
#pragma defer_codegen off
void _skyChgDir(char* path) { }

void SetDvdreadingCallBackFunction(StateCallback callback)
{
	lbl_8042C0D8 = callback;
}

s32 GetDvdreadingStatus(void)
{
	switch (DVDGetDriveStatus()) {
		case 0:
			return 7;
		case 5:
			return 0;
		case 4:
			return 1;
		case 6:
			return 2;
		case -1:
			return 3;
		case 11:
			return 4;
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
			break;
	}

	if (lbl_8042C0D4 == NULL) {
		return 6;
	}

	switch (DVDGetCommandBlockStatus(lbl_8042C0D4)) {
		case 0:
			return 7;
		case 5:
			return 0;
		case 4:
			return 1;
		case 6:
			return 2;
		case -1:
			return 3;
		case 11:
			return 4;
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
			break;
	}

	return 6;
}

s32 skyfsGetLength(void* fptr)
{
	return ((skyFile*)fptr)->length;
}

#pragma defer_codegen reset

static inline void waitForRead()
{
	s32 status;
	goto poll;
again:
	if (status <= 5) {
		if (lbl_8042C0DC != 0)
			lbl_8042C0DC(0);
	} else if (lbl_8042C0D8 != 0) {
		lbl_8042C0D8(0);
	}
poll:
	status = GetDvdreadingStatus();
	if (status != 7)
		goto again;
	lbl_8042C0D4 = 0;
}

s32 skyTransMode(const char* mode)
{
	s32 result = 0;
	if (mode == 0) {
		return 0;
	}
	if (mode[0] == 'r' && (mode[1] == 0 || (mode[1] == 'b' && mode[2] == 0))) {
		result = 1;
	} else if (mode[0] == 'w' && (mode[1] == 0 || (mode[1] == 'b' && mode[2] == 0))) {
		result = 14;
	} else if (mode[0] == 'a' && (mode[1] == 0 || (mode[1] == 'b' && mode[2] == 0))) {
		result = 6;
	} else if (mode[0] == 'r' && mode[1] == '+'
	    && (mode[2] == 0 || (mode[2] == 'b' && mode[3] == 0))) {
		result = 3;
	} else if (mode[0] == 'w' && mode[1] == '+'
	    && (mode[2] == 0 || (mode[2] == 'b' && mode[3] == 0))) {
		result = 15;
	} else if (mode[0] == 'a' && mode[1] == '+'
	    && (mode[2] == 0 || (mode[2] == 'b' && mode[3] == 0))) {
		result = 7;
	}
	return result;
}

void* skyFopen(const char* path, const char* mode)
{
	u32 parsedMode = skyTransMode(mode);
	u8* table;
	void* heap;
	skyFile* file;
	if (parsedMode == 0) {
		return 0;
	}
	table = lbl_8042C9A4;
	heap  = *(void**)(table + lbl_8042C0CC.globalsOffset + 0x2C);
	file  = ((skyFile * (*)(void*))(*(void**)(table + 0x144)))(heap);
	if (file == 0) {
		return 0;
	}
	file->readable = 0;
	if (parsedMode == 1) {
		file->readable = 1;
	}
	if (file->readable == 0) {
		table = lbl_8042C9A4;
		heap  = *(void**)(table + lbl_8042C0CC.globalsOffset + 0x2C);
		((void (*)(void*, void*))(*(void**)(table + 0x148)))(heap, file);
		return 0;
	}
	if (!DVDOpen(path, &file->fileHandle.fileInfo)) {
		table = lbl_8042C9A4;
		heap  = *(void**)(table + lbl_8042C0CC.globalsOffset + 0x2C);
		((void (*)(void*, void*))(*(void**)(table + 0x148)))(heap, file);
		return 0;
	}
	file->length         = file->fileHandle.fileInfo.length;
	file->position       = 0;
	file->bufferPosition = sizeof(file->buffer);
	lbl_8042C0C8++;
	return file;
}

s32 skyFclose(void* fptr)
{
	skyFile* file = (skyFile*)fptr;
	s32 result;
	if (file == 0)
		goto error;
	if (lbl_8042C0C8 == 0)
		goto error;
	if (!DVDClose(&file->fileHandle.fileInfo))
		goto error;
	{
		u8* table  = lbl_8042C9A4;
		void* heap = *(void**)(table + lbl_8042C0CC.globalsOffset + 0x2C);
		((void (*)(void*, void*))(*(void**)(table + 0x148)))(heap, file);
		lbl_8042C0C8--;
		result = 0;
		goto done;
	}
error:
	result = -1;
done:
	return result;
}

BOOL skyFexist(const char* path)
{
	void* handle = ((void* (*)(const char*, const char*))RwOsGetFileInterface()->entries[1])(
	    path, lbl_8042AD7C);
	if (handle != 0) {
		((void (*)(void*))RwOsGetFileInterface()->entries[2])(handle);
		return TRUE;
	}
	return FALSE;
}

#pragma opt_propagation off
u32 skyFread(void* destination, u32 size, u32 count, void* filePointer)
{
	skyFile* file = (skyFile*)filePointer;
	u32 requested = size * count;
	s32 copied;
	copied = 0;
	if (file->position + requested > file->length) {
		requested = file->length - file->position;
	}

	if (file->bufferPosition < sizeof(file->buffer)) {
		if ((s32)requested > 0) {
			if (requested < (sizeof(file->buffer) - file->bufferPosition)) {
				copied = requested;
			} else {
				copied = sizeof(file->buffer) - file->bufferPosition;
			}
			memcpy(destination, file->buffer + file->bufferPosition, copied);
			destination = (u8*)destination + copied;
			file->bufferPosition += copied;
			file->position += copied;
		}
	}

	s32 amount;
	s32 readLength;
	s32 snapshot;
	s32 transferred;
	snapshot = copied;
	amount   = requested - copied;
	if ((u32)amount > 0) {
		if (amount >= sizeof(file->buffer)) {
			if ((((u32)destination & 0x1F) == 0) && (((u32)amount & 0x1F) == 0)) {
				u32 readOffset = file->position;
				lbl_8042C0D4   = &file->fileHandle.fileInfo;
				DVDReadAsyncPrio(&file->fileHandle.fileInfo, destination, amount, readOffset, 0, 2);
				waitForRead();
				transferred = amount;
				if (transferred < 0) {
					transferred = 0;
				}
			} else {
				s32 chunks;
				s32 bytesLeft;
				s32 readOffset;
				transferred = 0;
				bytesLeft   = amount;
				readOffset  = file->position;
				chunks      = bytesLeft / 0x2800 + 1;
				while (chunks-- != 0) {
					s32 available = file->length - (file->position + transferred);
					if (available > (s32)sizeof(file->buffer)) {
						amount = sizeof(file->buffer);
					} else {
						amount = available;
					}
					lbl_8042C0D4 = &file->fileHandle.fileInfo;
					DVDReadAsyncPrio(&file->fileHandle.fileInfo, file->buffer,
					    readLength = (amount + 0x1F) & ~0x1F, readOffset, 0, 2);
					waitForRead();
					if (readLength == -1) {
						return copied + transferred;
					}
					if (bytesLeft >= amount) {
						memcpy(destination, file->buffer, amount);
						bytesLeft -= amount;
						transferred += amount;
						readOffset += amount;
						destination = (u8*)destination + amount;
					} else {
						memcpy(destination, file->buffer, bytesLeft);
						transferred += bytesLeft;
						readOffset += bytesLeft;
						file->bufferPosition = bytesLeft;
					}
				}
			}
		} else {
			s32 bytes;
			s32 read;
			s32 readOffset;
			readOffset = file->position;
			bytes      = (file->length - readOffset + 0x1F) & ~0x1F;
			if (bytes > (s32)sizeof(file->buffer)) {
				bytes = sizeof(file->buffer);
			}
			lbl_8042C0D4 = &file->fileHandle.fileInfo;
			DVDReadAsyncPrio(&file->fileHandle.fileInfo, file->buffer, bytes, readOffset, 0, 2);
			waitForRead();
			read = bytes;
			if (read == -1) {
				return snapshot;
			}
			transferred = amount;
			memcpy(destination, file->buffer, transferred);
			file->bufferPosition = transferred;
		}
		file->position += transferred;
		copied += transferred;
	}
	return copied / size;
}
#pragma opt_propagation reset

u32 skyFwrite(const void* addr, u32 size, u32 count, void* fptr)
{
	return 0;
}

#pragma opt_propagation off
s32 skyFseek(void* fptr, long offset, s32 origin)
{
#define file ((skyFile*)fptr)
	u32 oldPosition = file->position;
	s32 newBufferPosition;

	switch (origin) {
		case 1:
			file->position    = oldPosition + offset;
			newBufferPosition = file->bufferPosition + offset;
			if (newBufferPosition >= 0 && (u32)newBufferPosition <= sizeof(file->buffer)
			    && file->position <= file->length) {
				file->bufferPosition = newBufferPosition;
				return 0;
			}
			break;
		case 2: {
			u32 position      = file->length + offset;
			s32 delta         = position - oldPosition;
			file->position    = position;
			newBufferPosition = file->bufferPosition + delta;
			if (newBufferPosition >= 0 && (u32)newBufferPosition <= sizeof(file->buffer)
			    && file->position <= file->length) {
				file->bufferPosition = newBufferPosition;
				return 0;
			}
			break;
		}
		case 0: {
			s32 delta         = offset - oldPosition;
			file->position    = offset;
			newBufferPosition = file->bufferPosition + delta;
			if (newBufferPosition >= 0 && (u32)newBufferPosition <= sizeof(file->buffer)
			    && file->position <= file->length) {
				file->bufferPosition = newBufferPosition;
				return 0;
			}
			break;
		}
		default:
			return -1;
	}

	if (file->position > file->length) {
		file->position = oldPosition;
		return -1;
	}

	{
		u32 readOffset = (file->position / sizeof(file->buffer)) * sizeof(file->buffer);
		s32 readLength = file->length - readOffset;
		if (readLength > sizeof(file->buffer)) {
			readLength = sizeof(file->buffer);
		} else {
			readLength = (readLength + 0x1F) & ~0x1F;
		}
		lbl_8042C0D4 = &file->fileHandle.fileInfo;
		DVDReadAsyncPrio(&file->fileHandle.fileInfo, file->buffer, readLength, readOffset, 0, 2);
		waitForRead();
		if (readLength == -1) {
			file->position = oldPosition;
			return -1;
		}
		file->bufferPosition = file->position - readOffset;
	}
	return 0;
#undef file
}
#pragma opt_propagation reset

char* skyFgets(char* result, s32 count, void* stream)
{
	skyFile* file = (skyFile*)stream;
	s32 offset;
	s32 length;
	offset = 0;
	length = skyFread(result, 1, count - 1, file);
	if (length == 0) {
		return 0;
	}
	while (offset < length) {
		if (result[offset] == '\n') {
			offset++;
			result[offset] = 0;
			offset -= length;
			skyFseek(file, offset, 1);
			return result;
		} else if (result[offset] == '\r') {
			if (offset < length - 1 && result[offset + 1] == '\n') {
				memcpy(&result[offset], &result[offset + 1], length - offset - 1);
				length--;
			} else {
				offset++;
			}
		} else {
			offset++;
		}
	}
	if (length < count && file->position == file->length) {
		result[length] = 0;
	}
	return result;
}

s32 skyFputs(const char* buffer, void* fptr)
{
	return -1;
}

s32 skyFeof(void* fptr)
{
	skyFile* file = (skyFile*)fptr;
	return file->position >= file->length;
}

s32 skyFflush(void* fptr)
{
	return 0;
}

s32 skyFtell(void* fptr)
{
	skyFile* file = (skyFile*)fptr;
	return file->position;
}

void* _rwSkyFSOpen(void* instance, s32 offset, s32 size)
{
	RwFileFunctions* callbacks;

	lbl_8042C0CC.globalsOffset                                  = offset;
	*(void**)(lbl_8042C9A4 + lbl_8042C0CC.globalsOffset + 0x2C) = RwFreeListCreate(0x284C, 5, 0x20);
	if (*(void**)(lbl_8042C9A4 + lbl_8042C0CC.globalsOffset + 0x2C) == 0) {
		return 0;
	}

	callbacks              = RwOsGetFileInterface();
	RwFileFunctions* saved = (RwFileFunctions*)(lbl_8042C9A4 + lbl_8042C0CC.globalsOffset);
	saved->entries[0]      = callbacks->entries[0];
	saved->entries[1]      = callbacks->entries[1];
	saved->entries[2]      = callbacks->entries[2];
	saved->entries[3]      = callbacks->entries[3];
	saved->entries[4]      = callbacks->entries[4];
	saved->entries[5]      = callbacks->entries[5];
	saved->entries[6]      = callbacks->entries[6];
	saved->entries[7]      = callbacks->entries[7];
	saved->entries[8]      = callbacks->entries[8];
	saved->entries[9]      = callbacks->entries[9];
	saved->entries[10]     = callbacks->entries[10];
	callbacks->entries[0]  = (void*)skyFexist;
	callbacks->entries[1]  = (void*)skyFopen;
	callbacks->entries[2]  = (void*)skyFclose;
	callbacks->entries[3]  = (void*)skyFread;
	callbacks->entries[4]  = (void*)skyFwrite;
	callbacks->entries[5]  = (void*)skyFgets;
	callbacks->entries[6]  = (void*)skyFputs;
	callbacks->entries[7]  = (void*)skyFeof;
	callbacks->entries[8]  = (void*)skyFseek;
	callbacks->entries[9]  = (void*)skyFflush;
	callbacks->entries[10] = (void*)skyFtell;
	lbl_8042C0CC.numInstances++;
	return instance;
}

void* _rwSkyFSClose(void* instance, s32 offset, s32 size)
{
	RwFileFunctions* callbacks = RwOsGetFileInterface();
	RwFileFunctions* saved     = (RwFileFunctions*)(lbl_8042C9A4 + lbl_8042C0CC.globalsOffset);
	callbacks->entries[0]      = saved->entries[0];
	callbacks->entries[1]      = saved->entries[1];
	callbacks->entries[2]      = saved->entries[2];
	callbacks->entries[3]      = saved->entries[3];
	callbacks->entries[4]      = saved->entries[4];
	callbacks->entries[5]      = saved->entries[5];
	callbacks->entries[6]      = saved->entries[6];
	callbacks->entries[7]      = saved->entries[7];
	callbacks->entries[8]      = saved->entries[8];
	callbacks->entries[9]      = saved->entries[9];
	callbacks->entries[10]     = saved->entries[10];
	RwFreeListDestroy(*(void**)(lbl_8042C9A4 + lbl_8042C0CC.globalsOffset + 0x2C));
	lbl_8042C0CC.numInstances--;
	return instance;
}

s32 SkyInstallFileSystem(char* subdir)
{
	DVDInit();
	return ((u32)RwEngineRegisterPlugin(0x30, lbl_8042AD78, _rwSkyFSOpen, _rwSkyFSClose) >> 31) ^ 1;
}

#ifdef __cplusplus
}
#endif
