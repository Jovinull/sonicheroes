#include "types.h"

// The formatter core the buffer entry in game/wide_format_write.cpp calls.
// See notes/wide-formatter-core.md for the section map and the decoded class
// table.

typedef u16 wchar;

extern "C" void* memcpy(void* dst, const void* src, u32 size);
extern "C" void* __va_arg(void* ap, s32 kind);

#define ARG_INT (*(s32*)__va_arg(args, 1))

typedef void* (*WriteProc)(const wchar* src, u32 count, void* arg);

// Character classes, indexed by the format character less 0x20. Anything above
// 0x1A leaves the character alone.
static const u8 charClass[96] = {
	0x00,
	0x16,
	0x16,
	0x01,
	0x16,
	0x17,
	0x16,
	0x16, // 0x20
	0x16,
	0x16,
	0x02,
	0x00,
	0x16,
	0x03,
	0x04,
	0x16, // 0x28
	0x09,
	0x05,
	0x05,
	0x05,
	0x05,
	0x05,
	0x05,
	0x05, // 0x30
	0x05,
	0x05,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16, // 0x38
	0x16,
	0x16,
	0x16,
	0x12,
	0x16,
	0x0F,
	0x19,
	0x0F, // 0x40
	0x08,
	0x1A,
	0x16,
	0x16,
	0x07,
	0x16,
	0x18,
	0x16, // 0x48
	0x16,
	0x16,
	0x16,
	0x13,
	0x16,
	0x16,
	0x16,
	0x16, // 0x50
	0x0D,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16, // 0x58
	0x16,
	0x16,
	0x16,
	0x10,
	0x0A,
	0x0F,
	0x0F,
	0x0F, // 0x60
	0x08,
	0x0A,
	0x16,
	0x16,
	0x06,
	0x16,
	0x14,
	0x0B, // 0x68
	0x0E,
	0x16,
	0x16,
	0x11,
	0x16,
	0x0C,
	0x16,
	0x16, // 0x70
	0x0D,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16,
	0x16, // 0x78
};

// The conversion buffer and the cursor into it, both file scope.
static char narrowNull[] = "(null)";
static wchar wideNull[6] = { 0, 0, 0, 0, 0, 0 };
static wchar convBuf[48];
static wchar* convPos;

// Inlined at every site that emits one character. The flush computes a flag the
// call never reads, which is this helper's dead parameter on that path.
struct State {
	wchar out[80]; // 0x90
	s32 held;      // 0x130
	WriteProc write;
	void* writeArg;
	s32 total;    // 0x13C
	s32 failed;   // 0x140
	u32* limitAt; // 0x144
};

static void emitChar(State* s, wchar c)
{
	if (s->held >= 0x50 && s->held != 0) {
		if (s->write(s->out, s->held, s->writeArg) == NULL) {
			s->failed = 1;
		}

		s->held = 0;
	}

	if (s->limitAt == NULL || s->total < (s32)*s->limitAt) {
		s->out[s->held] = c;
		s->held         = s->held + 1;
	}

	s->total = s->total + 1;
}

extern "C" s32 wideFormatCore(
    WriteProc write, void* writeArg, const wchar* format, s32 hasLimit, u32 limit, void* args)
{
	wchar out[80];
	s32 held;
	s32 total;
	s32 failed;
	u32* limitAt;
	const wchar* fmt;
	wchar c;
	s32 state;
	s32 flags;
	s32 width;
	s32 precision;
	wchar sign;
	s32 base;
	s32 hexBias;
	s32 value;
	s32 isSigned;
	s32 length;
	s32 isWide;

	fmt     = format;
	held    = 0;
	total   = 0;
	failed  = 0;
	limitAt = hasLimit != 0 ? &limit : NULL;

	for (;;) {
		c = *fmt++;

		if (c == 0) {
			goto finish;
		}

		if (c == 0x25) {
			c = *fmt;

			if (c != 0x25) {
				goto spec;
			}

			fmt++;
		}

		if (held >= 0x50 && held != 0) {
			if (write(out, held, writeArg) == NULL) {
				failed = 1;
			}

			held = 0;
		}

		if (limitAt == NULL || total < (s32)*limitAt) {
			out[held] = c;
			held      = held + 1;
		}

		total = total + 1;
		continue;

	spec:
		state     = 0;
		flags     = 0;
		width     = -1;
		precision = -1;
		sign      = 0;
		base      = 10;
		hexBias   = 0;

		for (;;) {
			c = *fmt++;

			if (c < 0x20) {
				goto done;
			}

			if ((s32)c > 0x7F) {
				goto done;
			}

			switch (charClass[c - 0x20]) {
				case 0x00: // space and +
					if (state != 0) {
						goto done;
					}
					if (sign != 0x2B) {
						sign = c;
					}
					break;
				case 0x01: // #
					if (state != 0) {
						goto done;
					}
					flags |= 0x1;
					break;
				case 0x02: // *
					break;
				case 0x03: // -
					if (state != 0) {
						goto done;
					}
					flags |= 0x2;
					break;
				case 0x04: // .
					if (state >= 4) {
						goto done;
					}
					state     = 4;
					precision = precision + 1;
					break;
				case 0x05: // 1 to 9
					goto digit;
				case 0x06: // l
					flags |= 0x10;
					state = 5;
					break;
				case 0x07: // L
					flags = (flags | 0x100) & ~0x10;
					state = 5;
					break;
				case 0x08: // h and H
					flags = (flags | 0x200) & ~0x10;
					state = 5;
					break;
				case 0x09: // 0
					if (state != 0) {
						goto digit;
					}
					if ((flags & 0x2) != 0) {
						break;
					}
					flags |= 0x8;
					state = 1;
					break;
				case 0x0A: // d and i
					base = 10;
					goto integer;
				case 0x0B: // o
					base = 8;
					goto unsignedInteger;
				case 0x0C: // u
					base = 10;
					goto unsignedInteger;
				case 0x0D: // x and X
					base    = 16;
					hexBias = c - 0x17;
					goto unsignedInteger;
				case 0x0E: // p
					goto pointer;
				case 0x0F: // e f g E G
					goto floating;
				case 0x10: // c
					goto character;
				case 0x11: // s
					goto string;
				case 0x12: // C
					goto character;
				case 0x13: // S
					goto string;
				case 0x14: // n
					goto storeCount;
				case 0x15:
				case 0x16:
				case 0x17:
					goto done;
				case 0x18: // N
					flags &= ~0x20;
					state = 5;
					break;
				case 0x19: // F
					flags |= 0x20;
					state = 5;
					break;
				case 0x1A: // I
					break;
			}

			continue;

		digit:
			if (state <= 2) {
				state = 2;
				if (width == -1) {
					width = c - 0x30;
				} else {
					width = (c - 0x30) + width * 10;
				}
			} else {
				if (state != 4) {
					goto done;
				}
				precision = (c - 0x30) + precision * 10;
			}
		}
	}

integer:
	base     = 10;
	isSigned = 1;
	goto fetch;

unsignedInteger:
	sign     = 0;
	isSigned = 0;

fetch:
	if ((flags & 0x100) != 0) {
		value = ARG_INT;
	} else if ((flags & 0x10) != 0) {
		value = ARG_INT;
	} else if ((flags & 0x200) != 0) {
		s32 narrow = (u16)ARG_INT;

		value = isSigned != 0 ? (s16)narrow : narrow;
	} else {
		value = ARG_INT;
	}

	convPos = convBuf + 1;

	if (value == 0) {
		if (precision == 0) {
			convBuf[1] = 0;
			goto padded;
		}
	} else {
		flags |= 0x4;
	}

	{
		wchar* at = convPos;

		if (base >= 2 && base <= 0x24) {
			wchar digits[48];
			wchar* end;

			if (value < 0 && isSigned != 0) {
				*at++ = 0x2D;
				value = -value;
			}

			end = digits;

			do {
				*end++ = (wchar)(value - value / base * base);
				value  = value / base;
			} while (value != 0);

			while (end != digits) {
				wchar d = *--end;

				if (d < 10) {
					*at++ = (wchar)(d + 0x30);
				} else {
					*at++ = (wchar)(d + hexBias - 10);
				}
			}
		}

		*at = 0;
	}

padded:
	goto emit;

pointer: {
	u32 v = (u32)ARG_INT;
	wchar* at;
	s32 n;

	convPos = convBuf;
	at      = convBuf + 7;

	for (n = 2; n != 0; n--) {
		s32 i;

		for (i = 0; i < 4; i++) {
			s32 d = v & 0xF;

			*at-- = (wchar)(d < 10 ? d + 0x30 : d + 0x37);
			v >>= 4;
		}
	}

	convBuf[8] = 0;
	flags &= ~0x4;
	convPos = convBuf;
}
	goto emit;

character:
	if ((flags & 0x210) == 0) {
		flags |= 0x200;
	}

	if ((flags & 0x200) != 0) {
		((s8*)convBuf)[0] = (s8)ARG_INT;
		((s8*)convBuf)[1] = 0;
		convPos           = convBuf;
		length            = 1;
	} else {
		convBuf[0] = (wchar)ARG_INT;
		convBuf[1] = 0;
		convPos    = convBuf;
		length     = 1;
	}
	goto emit;

string:
	if ((flags & 0x210) == 0) {
		flags |= 0x200;
	}

	if ((flags & 0x200) != 0) {
		convPos = (wchar*)ARG_INT;
		isWide  = 0;

		if (convPos == NULL) {
			convPos = (wchar*)narrowNull;
		}
	} else {
		convPos = (wchar*)ARG_INT;
		isWide  = 1;

		if (convPos == NULL) {
			convPos = wideNull;
		}
	}
	goto emit;

floating:
storeCount:
emit:
finish:
done:
	if (held != 0) {
		write(out, held, writeArg);
	}

	return failed != 0 ? -1 : total;
}
