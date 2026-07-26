#include "types.h"

extern char* strncpy(char* dst, const char* src, unsigned long count);
extern s32 wctomb(char* string, u16 wide_char);

static s32 is_utf8_complete(const char* string, u32 count);
static s32 utf8_to_unicode(u16* wide_char, const char* string, u32 count);

unsigned long wcstombs(char* s, const u16* pwcs, unsigned int n)
{
	char decoded[4];
	u16 wide_char;
	unsigned long number_of_bytes;
	s32 chars_written = 0;
	const u16* source;

	if (s == 0 || pwcs == 0)
		return 0;

	source = pwcs;
	while (chars_written <= n) {
		wide_char = *source;
		if (wide_char == 0) {
			s[chars_written] = '\0';
			break;
		}

		++source;
		number_of_bytes = wctomb(decoded, wide_char);
		if (chars_written + number_of_bytes > n)
			break;

		strncpy(s + chars_written, decoded, number_of_bytes);
		chars_written += number_of_bytes;
	}

	return chars_written;
}

inline s32 wctomb(char* string, u16 wide_char)
{
	s32 number_of_bytes;
	u16 character;
	char* target;
	char first_byte_mark[4] = { 0x00, 0x00, 0xC0, 0xE0 };

	if (!string)
		return (0);

	character = wide_char;
	if (character < 0x80)
		number_of_bytes = 1;
	else if (character < 0x800)
		number_of_bytes = 2;
	else
		number_of_bytes = 3;

	target = string + number_of_bytes;

	switch (number_of_bytes) {
		case 3:
			*--target = (character & 0x3F) | 0x80;
			character >>= 6;
		case 2:
			*--target = (character & 0x3F) | 0x80;
			character >>= 6;
		case 1:
			*--target = character | first_byte_mark[number_of_bytes];
	}

	return number_of_bytes;
}

s32 mbtowc(u16* wide_char, const char* string, u32 count)
{
	return utf8_to_unicode(wide_char, string, count);
}

static s32 utf8_to_unicode(u16* wide_char, const char* string, u32 count)
{
	s32 number_of_bytes;
	s32 is_utf8;
	char* source;
	u16* destination  = wide_char;
	u16 result        = 0;
	const char* input = string;

	if (input == 0)
		return 0;

	if (count <= 0)
		return -1;

	number_of_bytes = is_utf8_complete(input, count);
	if (number_of_bytes < 0)
		return -1;

	source = (char*)input;
	switch (number_of_bytes) {
		case 3:
			result |= *source++ & 0x0F;
			result <<= 6;
		case 2:
			result |= *source++ & 0x3F;
			result <<= 6;
		case 1:
			result |= *source++ & 0x7F;
	}

	if (result == 0)
		is_utf8 = 0;
	else if (result < 0x80)
		is_utf8 = 1;
	else if (result < 0x800)
		is_utf8 = 2;
	else
		is_utf8 = 3;

	if (is_utf8 != number_of_bytes)
		return -1;

	if (destination != 0)
		*destination = result;

	return number_of_bytes;
}

static s32 is_utf8_complete(const char* string, u32 count)
{
	if (count == 0)
		return -1;

	if (string[0] == 0)
		return 0;

	if ((string[0] & 0x80) == 0) {
		return 1;
	} else if ((string[0] & 0xE0) == 0xC0) {
		if (count >= 2) {
			if ((string[1] & 0x80) == 0x80)
				return 2;
			return -1;
		}
		return -2;
	} else if ((string[0] & 0xF0) == 0xE0) {
		if (count >= 3) {
			if ((string[1] & 0x80) == 0x80) {
				if ((string[2] & 0x80) == 0x80)
					return 3;
			}
			return -1;
		} else if ((count == 2 && (string[1] & 0x80) == 0x80) || count == 1) {
			return -2;
		}
		return -1;
	}

	return -1;
}
