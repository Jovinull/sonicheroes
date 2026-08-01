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

// Never read here. The target's lbl_8042C808 is one eight byte object with
// only its first word referenced, so a second pointer has to exist beside the
// cursor for .sbss to come out at eight rather than four.
static wchar* convEnd;

// Inlined at every site that emits one character. The flush computes a flag the
// call never reads, which is this helper's dead parameter on that path.
struct State {
	wchar out[80]; // 0x90
	s32 held;      // 0x130
	WriteProc write;
	void* writeArg;
	u32 total;    // 0x13C
	s32 failed;   // 0x140
	u32* limitAt; // 0x144
};

static inline void emitChar(State* s, wchar c)
{
	if (s->held >= 0x50 && s->held != 0) {
		if (s->write(s->out, s->held, s->writeArg) == NULL) {
			s->failed = 1;
		}

		s->held = 0;
	}

	if (s->limitAt == NULL || (u32)s->total < *s->limitAt) {
		s->out[s->held] = c;
		s->held         = s->held + 1;
	}

	s->total = s->total + 1;
}

extern "C" s32 wideFormatCore(
    WriteProc write, void* writeArg, const wchar* format, s32 hasLimit, u32 limit, void* args)
{
	s32 held;
	s32 total;
	s32 failed;
	u32* limitAt;
	u32 flags;
	s32 length;
	const wchar* fmt;
	wchar c;
	u32 state;
	s32 width;
	s32 precision;
	wchar sign;
	s32 base;
	s32 hexBias;
	u32 value;
	s32 isSigned;
	s32 isWide;
	u32 zeroPad;
	const wchar* specAt;
	wchar* bufBase;
	State st;

	fmt         = format;
	st.failed   = 0;
	st.total    = 0;
	st.held     = 0;
	st.write    = write;
	st.writeArg = writeArg;
	st.limitAt  = hasLimit != 0 ? &limit : NULL;

	bufBase = convBuf;

nextChar:
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

		emitChar(&st, c);
		continue;

	spec:
		specAt    = fmt - 1;
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
				case 0x01: // #
					if (state != 0) {
						goto done;
					}
					flags |= 0x1;
					break;
				case 0x03: // -
					if (state != 0) {
						goto done;
					}
					flags |= 0x2;
					break;
				case 0x00: // space and +
					if (state != 0) {
						goto done;
					}
					if (sign != 0x2B) {
						sign = c;
					}
					break;
				case 0x18: // N
					flags &= ~0x20;
					state = 5;
					break;
				case 0x19: // F
					flags |= 0x20;
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
				case 0x02: { // *
					s32 given = ARG_INT;

					if (state < 2) {
						if (given < 0) {
							width = -given;
							flags |= 0x2;
						} else {
							width = given;
						}

						state = 3;
					} else {
						if (state != 4) {
							goto done;
						}

						precision = given;
						state     = state + 1;
					}
					break;
				}
				case 0x04: // .
					if (state >= 4) {
						goto done;
					}
					state     = 4;
					precision = precision + 1;
					break;
				case 0x05: // 1 to 9
				digit:
					if (state <= 2) {
						state = 2;
						if (width == -1) {
							width = (wchar)(c - 0x30);
						} else {
							width = (wchar)(c - 0x30) + width * 10;
						}
					} else {
						if (state != 4) {
							goto done;
						}
						precision = (wchar)(c - 0x30) + precision * 10;
					}
					break;
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
				case 0x1A: // I64, I32, I16 and I8
					if (fmt[0] == 0x36 && fmt[1] == 0x34) {
						fmt += 2;
						flags = (flags | 0x100) & ~0x210;
						state = 5;
					} else if (fmt[0] == 0x33 && fmt[1] == 0x32) {
						fmt += 2;
						flags = (flags | 0x10) & ~0x300;
						state = 5;
					} else if (fmt[0] == 0x31 && fmt[1] == 0x36) {
						fmt += 2;
						flags = (flags | 0x200) & ~0x110;
						state = 5;
					} else if (fmt[0] == 0x38) {
						fmt += 1;
						flags = flags & ~0x310;
						state = 5;
					}
					break;
				case 0x0B: // o
					goto octal;
				case 0x0C: // u
					goto unsignedDecimal;
				case 0x0D: // x and X
					goto hexadecimal;
				case 0x0A: // d and i
					goto integer;
				case 0x0E: // p
					goto pointer;
				case 0x12: // C
					goto narrowCharDefault;
				case 0x10: // c
					goto character;
				case 0x13: // S
					goto narrowStringDefault;
				case 0x11: // s
					goto string;
				case 0x0F: // e f g E G
					goto floating;
				case 0x14: // n
					goto storeCount;
				case 0x15:
				case 0x16:
				case 0x17:
					goto done;
			}

			continue;
		}
	}

octal:
	base = 8;
	goto unsignedShared;

unsignedDecimal:
	base = 10;
	goto unsignedShared;

hexadecimal:
	base    = 16;
	hexBias = c - 0x17;

unsignedShared:
	sign     = 0;
	isSigned = 0;
	goto fetch;

integer:
	base     = 10;
	isSigned = 1;

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

	convPos = (convBuf + 1);

	if (value == 0) {
		if (precision == 0) {
			*(convBuf + 1) = 0;
			goto padded;
		}
	} else {
		flags |= 0x4;
	}

	{
		wchar* at = convPos;

		if (base >= 2 && base <= 0x24) {
			wchar digits[66];
			wchar* end;

			if (value < 0 && isSigned != 0) {
				*at++ = 0x2D;
				value = -value;
			}

			end = digits;

			do {
				*end++ = (wchar)(s8)(value - value / (u32)base * (u32)base);
				value  = (s32)((u32)value / (u32)base);
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

narrowCharDefault:
	if ((flags & 0x210) == 0) {
		flags |= 0x200;
	}

character:
	if ((flags & 0x200) != 0) {
		((s8*)convBuf)[0] = (s8)ARG_INT;
		((s8*)bufBase)[1] = 0;
		convPos           = convBuf;
		length            = 1;
	} else {
		convBuf[0]     = (wchar)ARG_INT;
		*(convBuf + 1) = 0;
		convPos        = convBuf;
		length         = 1;
	}
	goto emit;

narrowStringDefault:
	if ((flags & 0x210) == 0) {
		flags |= 0x200;
	}

string:
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

	if (isWide != 0) {
		s32 room  = precision >= 0 ? precision : 0x7FFFFFFF;
		wchar* at = convPos;

		length = 0;

		while (room != 0 && *at != 0) {
			room   = room - 1;
			length = length + 1;
			at     = at + 1;
		}
	} else {
		s32 room = precision >= 0 ? precision : 0x7FFFFFFF;
		s8* at   = (s8*)convPos;

		length = 0;

		while (room != 0 && *at != 0) {
			room   = room - 1;
			length = length + 1;
			at     = at + 1;
		}
	}

	goto emit;

padded:
	if (precision >= 0) {
		wchar* at = convPos;
		s32 bare;

		if (at != NULL) {
			length = 0;

			while (*at != 0) {
				length = length + 1;
				at     = at + 1;
			}
		} else {
			length = 0;
		}

		bare = length;

		if (*convPos == 0x2D) {
			bare = length - 1;
		} else if (sign != 0) {
			length  = length + 1;
			convPos = convPos - 1;

			*convPos = sign;
		}

		if (precision > bare) {
			zeroPad = precision - bare;
		}

		goto emit;
	}

zeroFill:
	if ((flags & 0x8) != 0 && width > 0) {
		wchar* at = convPos;
		s32 len;

		if (at != NULL) {
			len = 0;

			while (*at != 0) {
				len = len + 1;
				at  = at + 1;
			}
		} else {
			len = 0;
		}

		if (*convPos == 0x2D) {
			len = len - 1;
		}

		if (width > len) {
			zeroPad = width - len;
		}
	}

	if (*convPos == 0x2D || sign != 0) {
		if (*convPos != 0x2D) {
			convPos = convPos - 1;

			*convPos = sign;
		}

		if (zeroPad > 0) {
			zeroPad = zeroPad - 1;
		}
	}

	{
		wchar* at = convPos;

		if (at != NULL) {
			length = 0;

			while (*at != 0) {
				length = length + 1;
				at     = at + 1;
			}
		} else {
			length = 0;
		}
	}

	goto emit;

emit:
	if ((flags & 0x1) != 0) {
		if (c == 0x6F) {
			if (zeroPad <= 0) {
				zeroPad = 1;
			}
		} else if (c == 0x78 || c == 0x58) {
			flags |= 0x40;
			width   = width - 2;
			zeroPad = zeroPad - 2;

			if (zeroPad < 0) {
				zeroPad = 0;
			}
		}
	}

	length = length + zeroPad;

	if ((flags & 0x2) == 0) {
		while (width > length) {
			emitChar(&st, 0x20);
			width = width - 1;
		}
	}

	if ((flags & 0x40) != 0) {
		emitChar(&st, 0x30);
		emitChar(&st, c);
	}

	while (zeroPad != 0) {
		emitChar(&st, 0x30);
		zeroPad = zeroPad - 1;
	}

	if ((flags & 0x2) != 0) {
		while (length != 0) {
			wchar ch = *convPos;

			convPos = convPos + 1;

			emitChar(&st, ch);

			length = length - 1;
			width  = width - 1;
		}
	} else {
		while (length != 0) {
			wchar ch = *convPos;

			convPos = convPos + 1;

			emitChar(&st, ch);

			length = length - 1;
		}
	}

	while (width > 0) {
		emitChar(&st, 0x20);
		width = width - 1;
	}

floating:
	goto zeroFill;

storeCount: {
	void* at = (void*)ARG_INT;

	convPos = (wchar*)at;

	if ((flags & 0x10) != 0) {
		*(s32*)at = st.total;
	} else if ((flags & 0x200) != 0) {
		*(s16*)at = (s16)st.total;
	} else {
		*(s32*)at = st.total;
	}
}
	goto nextChar;

done:
	for (;;) {
		c = *specAt++;

		if (c == 0) {
			break;
		}

		emitChar(&st, c);
	}

finish:
	if (st.held != 0) {
		if (st.write(st.out, st.held, st.writeArg) == NULL) {
			st.failed = 1;
		}

		st.held = 0;
	}

	return st.failed != 0 ? -1 : st.total;
}
