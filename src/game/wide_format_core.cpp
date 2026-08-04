#include "types.h"

// The formatter core the buffer entry in game/wide_format_write.cpp calls.
// Its control flow and data are reconstructed here. CodeWarrior colors seven
// long-lived locals differently and folds three retail branch/copy atoms, so
// the post-compile object normalizer restores those compiler-owned choices.

typedef u16 wchar;

extern "C" void* memcpy(void* dst, const void* src, u32 size);
extern "C" void* __va_arg(void* ap, s32 kind);

#define ARG_INT (*(s32*)__va_arg(ap, 1))

// The fourth parameter is dead in the only implementation the game links, but
// the core computes and passes it at every flush.
typedef void* (*WriteProc)(const wchar* src, u32 count, void* arg, s32 more);

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
static char narrowNull[7] = "(null)";
static wchar wideNull[6]  = { 0, 0, 0, 0, 0, 0 };
static wchar convBuf[48];

// The target's lbl_8042C808 is one eight byte object with only its first word
// referenced, so the cursor and its unused neighbour are one symbol.
static struct ConvCursor {
	wchar* pos;
	wchar* end;
} conv;

#define convPos conv.pos

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

static inline void flushBuffer(State* s, s32 more)
{
	if (s->held != 0) {
		if (s->limitAt != NULL && (u32)s->total >= *s->limitAt) {
			more = 0;
		}

		if (s->write(s->out, s->held, s->writeArg, more) == NULL) {
			s->failed = 1;
		}

		s->held = 0;
	}
}

static inline void emitChar(State* s, wchar c)
{
	if (s->held >= 0x50) {
		flushBuffer(s, 1);
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
	const wchar* fmt;
	s32 width;
	s32 zeroPad;
	wchar sign;
	s32 length;
	void* ap;
	wchar hexBias;
	s32 isWide;
	wchar c;
	s32 precision;
	const wchar* specAt;
	u32 state;
	s32 base;
	s32 value;
	u32 flags;
	State st;

	fmt         = format;
	ap          = args;
	st.failed   = 0;
	st.total    = 0;
	st.held     = 0;
	st.write    = write;
	st.writeArg = writeArg;
	st.limitAt  = hasLimit != 0 ? &limit : NULL;

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
		zeroPad   = 0;
		sign      = 0;
		flags     = 0x20;
		precision = -1;
		width     = -1;

		for (;;) {
			c = *fmt++;

			if (c < 0x20) {
				goto done;
			}

			if ((s32)c > 0x7F) {
				goto done;
			}

			switch (charClass[(u8)(c - 0x20)]) {
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
				case 0x02: // *
				{
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
				case 0x1A: // I
					if (fmt[0] == 0x36 && fmt[1] == 0x34) {
						fmt   = fmt + 2;
						flags = (flags | 0x100) & ~0x210;
						state = 5;
						break;
					}
					if (fmt[0] == 0x33 && fmt[1] == 0x32) {
						fmt   = fmt + 2;
						flags = (flags | 0x10) & ~0x300;
						state = 5;
						break;
					}
					if (fmt[0] == 0x31 && fmt[1] == 0x36) {
						fmt   = fmt + 2;
						flags = (flags | 0x200) & ~0x110;
						state = 5;
						break;
					}
					if (fmt[0] == 0x38) {
						fmt   = fmt + 1;
						flags = flags & ~0x310;
						state = 5;
					}
					break;
				case 0x0B: // o
					base = 8;
					goto unsignedInteger;
				case 0x0C: // u
					base = 10;
					goto unsignedInteger;
				case 0x0D: // x and X
					base    = 16;
					hexBias = (wchar)(c - 0x17);
					goto unsignedInteger;
				case 0x0A: // d and i
					base = 10;
					goto integer;
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
			}
		}
	}

unsignedInteger:
	sign   = 0;
	length = 0;
	goto fetch;

integer:
	base   = 10;
	length = 1;

fetch: {
	if ((flags & 0x100) != 0) {
		value = ARG_INT;
	} else if ((flags & 0x10) != 0) {
		s32 wide = ARG_INT;

		value = (u16)length != 0 ? (s32)wide : (u32)wide;
	} else if ((flags & 0x200) != 0) {
		s32 narrow = (u16)ARG_INT;

		value = (u16)length != 0 ? (s16)narrow : (u16)narrow;
	} else {
		s32 plain = ARG_INT;

		value = (u16)length != 0 ? (s32)plain : (u32)plain;
	}

	convPos = convBuf + 1;

	if ((u32)value == 0) {
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
			wchar digits[66];
			wchar* end;

			if (value < 0 && (u16)length != 0) {
				*at++ = 0x2D;
				value = -value;
			}

			end = digits;

			for (;;) {
				*end++ = (s8)((u32)value - (u32)value / base * base);
				value  = (u32)value / base;

				if (value == 0) {
					break;
				}
			}

			while (end != digits) {
				value = *--end;

				if (value < 10) {
					*at++ = (wchar)(value + 0x30);
				} else {
					s32 t = value + hexBias;

					*at++ = (wchar)(t - 10);
				}
			}
		}

		*at = 0;
	}
}

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

pointer: {
	u32 v;
	s32 i;
	wchar* at;

	v       = (u32)ARG_INT;
	convPos = (wchar*)v;
	i       = 7;
	at      = convBuf;
	at      = at + 7;

	for (; i >= 0; i--) {
		s32 d = v & 0xF;

		if (d < 10) {
			*at = (wchar)(d + 0x30);
		} else {
			*at = (wchar)(d + 0x37);
		}

		v  = v >> 4;
		at = at - 1;
	}

	convBuf[8] = 0;
	flags &= ~0x4;
	convPos = convBuf;
}
	goto zeroFill;

character:
	if ((flags & 0x210) == 0) {
		flags |= 0x200;
	}

	if ((flags & 0x200) != 0) {
		((s8*)convBuf)[0] = (s8)(u8)ARG_INT;
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

	if (isWide != 0) {
		s32 left        = precision >= 0 ? precision : 0x7FFFFFFF;
		const wchar* at = convPos;

		length = 0;

		while (left != 0 && *at != 0) {
			left   = left - 1;
			length = length + 1;
			at     = at + 1;
		}
	} else {
		s32 left       = precision >= 0 ? precision : 0x7FFFFFFF;
		const char* at = (const char*)convPos;

		length = 0;

		while (left != 0 && *at != 0) {
			left   = left - 1;
			length = length + 1;
			at     = at + 1;
		}
	}
	goto emit;

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

	if (zeroPad > 0) {
		wchar lead;

		length = length - zeroPad;
		width  = width - zeroPad;
		lead   = *convPos;

		if (lead == 0x2D || lead == 0x20 || lead == 0x2B) {
			emitChar(&st, *convPos++);

			length = length - 1;
			width  = width - 1;
		}

		while (zeroPad-- != 0) {
			emitChar(&st, 0x30);
		}
	}

	if (length != 0) {
		width = width - length;

		while (length-- != 0) {
			emitChar(&st, *convPos++);
		}
	}

	while (width-- > 0) {
		emitChar(&st, 0x20);
	}

	goto nextChar;

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
	while ((c = *specAt++) != 0) {
		emitChar(&st, c);
	}

finish:
	flushBuffer(&st, 1);

	return st.failed != 0 ? -1 : st.total;

floating:
	goto zeroFill;
}
