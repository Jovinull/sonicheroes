// Runs memory card command `command` (0-14) on the card controller: one handler per command,
// dispatched through a jump table (owned .data). The handlers' roles are UNKNOWN.
#include "types.h"

struct Card801279C8;

extern "C" {
void fn_801275E8(Card801279C8* card);
void fn_80127540(Card801279C8* card);
void fn_80127498(Card801279C8* card);
void fn_801273C4(Card801279C8* card);
void fn_8012729C(Card801279C8* card);
void fn_801271AC(Card801279C8* card);
void fn_80127078(Card801279C8* card);
void fn_80126FF4(Card801279C8* card);
void fn_80126F14(Card801279C8* card);
void fn_80126E90(Card801279C8* card);
void fn_80126E0C(Card801279C8* card);
void fn_80126C88(Card801279C8* card);
void fn_80126BEC(Card801279C8* card);
void fn_80126B68(Card801279C8* card);
void fn_80126A44(Card801279C8* card);

void fn_801279C8(Card801279C8* card, u32 command)
{
	switch (command) {
		case 0:
			fn_801275E8(card);
			break;
		case 1:
			fn_80127540(card);
			break;
		case 2:
			fn_80127498(card);
			break;
		case 3:
			fn_801273C4(card);
			break;
		case 4:
			fn_8012729C(card);
			break;
		case 5:
			fn_801271AC(card);
			break;
		case 6:
			fn_80127078(card);
			break;
		case 7:
			fn_80126FF4(card);
			break;
		case 8:
			fn_80126F14(card);
			break;
		case 9:
			fn_80126E90(card);
			break;
		case 10:
			fn_80126E0C(card);
			break;
		case 11:
			fn_80126C88(card);
			break;
		case 12:
			fn_80126BEC(card);
			break;
		case 13:
			fn_80126B68(card);
			break;
		case 14:
			fn_80126A44(card);
			break;
	}
}
}
