#include "types.h"

// The buffer half of a wide-character formatter: the entry point that formats
// into a caller's buffer, and the write callback that entry point hands to the
// formatter core at 0x8013A6B8.
//
// The claim is .text 0x8013A5F0 to 0x8013A6B8, extab 0x8000BA90 to 0x8000BAA0
// and extabindex 0x80011AB8 to 0x80011AD0. Nothing else: neither function names
// a constant, so the unit owns no rodata, and neither touches a static, so it
// owns no data or bss.
//
// The bounds are read rather than argued. game/enemy_voice.cpp ends at
// 0x80139FC4 and game/SpAdvStgFailed.cpp begins at 0x8013B76C, and every
// section of both neighbours abuts this run exactly. The core at 0x8013A6B8 is
// left in the automatic split for now; it is the other half of the same
// original file, so this path is a fragment rather than a translation unit.
//
// The character type is two bytes. Every string access in the pair is lhz/sth
// and the callback doubles its count before the copy, so the unit is the wide
// build of the formatter rather than the narrow one.
//
// The entry point takes the address of its own buffer parameter rather than of
// a separate local. That is what puts the parameter in the frame before either
// of the argument moves, and it is the shape the narrow vsprintf has in MSL.
//
// The callback returns its own count where the core tests a pointer. That is
// the core's success convention, not an accident: it only ever compares the
// result against zero, so returning the count reports "wrote something" and a
// zero-length write reports failure. The return type below is the pointer the
// core expects, which is why the count is cast on the way out.
//
// The callback advances the cursor inside the expression it terminates through,
// which is denser than splitting it and is what the original does. The
// terminator is emitted before the address it is written to: C evaluates the
// trivial right side first when the left side is a compound assignment, so the
// zero is materialised ahead of the reload and the add. Splitting the two into
// separate statements moves it after them, and no arrangement of separate
// statements, compiler version between GC/1.3 and GC/2.7, or optimisation flag
// puts it back.

typedef u16 wchar;

extern "C" void* memcpy(void* dst, const void* src, u32 size);

// Defined below, declared here because the entry point is emitted first.
extern "C" void* wideFormatWrite(const wchar* src, u32 count, wchar** position);

// The formatter core. The fourth and fifth parameters are the length limit: the
// core keeps a pointer to the limit only when the flag is set, which is how the
// counted variants reach the same code. This entry point is uncounted and
// passes zero for both.
extern "C" s32 fn_8013A6B8(void* (*write)(const wchar*, u32, wchar**), wchar** writeArg,
    const wchar* format, s32 hasLimit, u32 limit, void* args);

extern "C" s32 wideFormatToBuffer(wchar* buffer, const wchar* format, void* args)
{
	if (buffer != NULL) {
		*buffer = 0;

		return fn_8013A6B8(wideFormatWrite, &buffer, format, 0, 0, args);
	}

	return 0;
}

// Appends to the caller's buffer and keeps it terminated after every chunk, so
// an abandoned format still leaves a valid string behind.
extern "C" void* wideFormatWrite(const wchar* src, u32 count, wchar** position)
{
	memcpy(*position, src, count * sizeof(wchar));

	*(*position = (wchar*)((u8*)*position + count * sizeof(wchar))) = 0;

	return (void*)count;
}
