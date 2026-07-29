#include "types.h"

#define NEXT_BIT(bit)                                                                              \
	do {                                                                                           \
		if (--mask == 0) {                                                                         \
			filterAddressing = *source++;                                                          \
			mask             = 8;                                                                  \
		}                                                                                          \
		(bit) = filterAddressing & 1;                                                              \
		filterAddressing >>= 1;                                                                    \
	} while (0)

u32 Expand2(void* sourceAddress, void* destinationAddress)
{
	u8* destinationStart;
	u8* source;
	u8* destination;
	u8* copy;
	u32 filterAddressing;
	u32 mask;
	u32 bit;
	u32 length;
	u32 tbit;
	u32 delay;
	u32 firstByte;

	firstByte        = *(u8*)sourceAddress;
	source           = (u8*)sourceAddress + 1;
	filterAddressing = firstByte;
	mask             = 9;
	destination      = (u8*)destinationAddress;
	destinationStart = destination;

	for (;;) {
		NEXT_BIT(bit);
		if (bit == 1) {
			*destination++ = *source++;
		}
		if (bit == 1) {
			continue;
		}

		NEXT_BIT(bit);
		if (bit == 1) {
			tbit  = *source++;
			delay = *source++;
			delay = tbit | (delay << 8);
			if (delay == 0) {
				return destination - destinationStart;
			}

			copy   = (u8*)((delay >> 3) | 0xFFFFE000);
			length = tbit & 7;
			if (length == 0) {
				length = *source++ + 1;
			} else {
				length += 2;
			}
			copy += (u32)destination;
		} else {
			u32 shortBit;

			length = 0;
			NEXT_BIT(shortBit);
			length = (length << 1) | shortBit;
			NEXT_BIT(shortBit);
			length = (length << 1) | shortBit;
			length += 2;
			copy = (u8*)((*source++ | 0xFFFFFF00) + (u32)destination);
		}

		while (length != 0) {
			*destination = *copy;
			destination++;
			copy++;
			length--;
		}
	}
}

#undef NEXT_BIT
