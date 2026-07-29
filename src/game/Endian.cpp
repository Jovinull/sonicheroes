typedef signed char s8;
typedef unsigned char u8;
typedef int s32;

// The retail object keeps fixed-size, 32-byte records behind a separately
// allocated base pointer. The accessor is also used by the neighboring
// recursive parameter walker.
struct InputRecord {
	u8 bytes[32];
};

struct InputRecordArray {
	InputRecord* records;

	InputRecord* Get(s32 index);
};

InputRecord* InputRecordArray::Get(s32 index)
{
	return &records[index];
}

void EndianConversionNoop() { }

void ConvertAnyParameter(u8* data, const char* format, s32 count)
{
	while (count-- > 0) {
		const char* cursor = format;

		while (*cursor != '\0') {
			switch (*cursor) {
				case 'c':
					data += 1;
					break;
				case 's': {
					u8 value = data[0];
					data[0]  = data[1];
					data[1]  = value;
					data += 2;
					break;
				}
				case 'i': {
					u8 value = data[0];
					data[0]  = data[3];
					// The signed lvalue preserves the retail extsb/stb pair.
					((s8*)data)[3] = (s8)value;
					value          = data[1];
					data[1]        = data[2];
					((s8*)data)[2] = (s8)value;
					data += 4;
					break;
				}
			}
			++cursor;
		}
	}
}

#pragma opt_lifetimes off
void ConvertU16Array(u8* data, s32 byteCount)
{
	// Counting down bytes is significant: CodeWarrior derives the trip count,
	// unrolls eight swaps, and emits the same CTR/remainder loops as retail.
	while (byteCount > 0) {
		u8 value = data[0];
		data[0]  = data[1];
		data[1]  = value;
		data += 2;
		byteCount -= 2;
	}
}

void ConvertU32Array(u8* data, s32 byteCount)
{
	// As above, retaining the byte countdown produces the four-word unroll.
	while (byteCount > 0) {
		u8 value       = data[0];
		data[0]        = data[3];
		((s8*)data)[3] = (s8)value;
		value          = data[1];
		data[1]        = data[2];
		((s8*)data)[2] = (s8)value;
		data += 4;
		byteCount -= 4;
	}
}
#pragma opt_lifetimes reset

static void EndianStaticInitializer() { }

__declspec(section ".ctors") void (*const endianCtorEntry)(void) = EndianStaticInitializer;
