#include "game/rw_stream_chunk.h"

extern "C" {
ChunkHdr lbl_80290400 = { 0, 0, 0, 0, 0 };

s32 fn_80192CCC(ChunkHdr* hdr)
{
	switch (hdr->type) {
		case 1:
			return 0;
		case 2:
			return 0;
		case 3:
			return 0;
		case 5:
			return 1;
		case 6:
			return 1;
		case 7:
			return 1;
		case 8:
			return 1;
		case 9:
			return 1;
		case 10:
			return 1;
		case 11:
			return 1;
		case 13:
			return 0;
		case 14:
			return 1;
		case 15:
			return 1;
		case 16:
			return 1;
		case 18:
			return 1;
		case 19:
			return 0;
		case 20:
			return 1;
		case 26:
			return 1;
	}
	return 0;
}
}
