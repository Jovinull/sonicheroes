#include "types.h"
#include <dolphin/card.h>

#include "__card.h"

// CARDNet.c of the Dolphin SDK memory card library, no .text of its own (every function was smart-stripped).
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/card/CARDNet.c (public reconstruction of the
// Dolphin SDK); this DOL carries the Apr 17 2003 release build of CARD
// ("<< Dolphin SDK - CARD ... Apr 17 2003 12:34:19 >>"). Compiled with
// GC/1.2.5n like the other SDK units. The original linker smart-stripped
// the functions nothing in the game calls; they are still defined here, as in
// the SDK source, and the linker drops them again.
//
// Only the unit's .sdata survives in the DOL: __CARDVendorID and
// __CARDPermMask, which CARDMount and CARDOpen read.

u16 __CARDVendorID = 0xFFFF;
u8 __CARDPermMask  = 0x1C;

u16 CARDSetVendorID(u16 vendorID)
{
	u16 prevID     = __CARDVendorID;
	__CARDVendorID = vendorID;

	return prevID;
}

u16 CARDGetVendorID()
{
	return __CARDVendorID;
}

s32 CARDGetSerialNo(s32 chan, u64* serialNo)
{
	CARDControl* card;
	s32 result;
	CARDID* id;
	u64 code;
	int i;

	if (!(0 <= chan && chan < 2)) {
		return CARD_RESULT_FATAL_ERROR;
	}

	result = __CARDGetControlBlock(chan, &card);
	if (result < 0) {
		return result;
	}

	id = (CARDID*)card->workArea;
	for (code = 0, i = 0; i < sizeof(id->serial) / sizeof(u64); ++i) {
		code ^= *(u64*)&id->serial[sizeof(u64) * i];
	}
	*serialNo = code;

	return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

s32 CARDGetUniqueCode(s32 chan, u64* uniqueCode)
{
	CARDControl* card;
	s32 result;
	OSSramEx* sram;

	if (!(0 <= chan && chan < 2)) {
		return CARD_RESULT_FATAL_ERROR;
	}

	result = __CARDGetControlBlock(chan, &card);
	if (result < 0) {
		return result;
	}

	sram = __OSLockSramEx();
	memcpy(uniqueCode, &sram->flashID[chan][4], 8);
	__OSUnlockSramEx(0);
	return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

s32 CARDGetAttributes(s32 chan, s32 fileNo, u8* attr)
{
	CARDDir dirent;
	s32 result;

	result = __CARDGetStatusEx(chan, fileNo, &dirent);
	if (result == 0) {
		*attr = dirent.permission;
	}

	return result;
}

#define CARDCheckAttr(attr, flag) ((u32)(attr & flag) != 0)

s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback)
{
	CARDDir dirent;
	s32 result;

	if (attr & ~__CARDPermMask) {
		return CARD_RESULT_NOPERM;
	}

	result = __CARDGetStatusEx(chan, fileNo, &dirent);
	if (result < 0) {
		return result;
	}

	if ((CARDCheckAttr(dirent.permission, 0x20) && !CARDCheckAttr(attr, 0x20))
	    || (CARDCheckAttr(dirent.permission, 0x40) && !CARDCheckAttr(attr, 0x40))) {
		return CARD_RESULT_NOPERM;
	}

	if ((CARDCheckAttr(attr, 0x20) && CARDCheckAttr(attr, 0x40))
	    || (CARDCheckAttr(attr, 0x20) && CARDCheckAttr(dirent.permission, 0x40))
	    || (CARDCheckAttr(attr, 0x40) && CARDCheckAttr(dirent.permission, 0x20))) {
		return CARD_RESULT_NOPERM;
	}

	dirent.permission = attr;
	return __CARDSetStatusExAsync(chan, fileNo, &dirent, callback);
}

s32 CARDSetAttributes(s32 chan, s32 fileNo, u8 attr)
{
	s32 result;

	result = CARDSetAttributesAsync(chan, fileNo, attr, __CARDSyncCallback);
	if (result < 0) {
		return result;
	}

	return __CARDSync(chan);
}

static int __CARDEnablePerm(u8 perm, BOOL enable)
{
	int prev;
	prev = __CARDPermMask & perm ? TRUE : FALSE;

	if (enable) {
		__CARDPermMask |= perm;
	} else {
		__CARDPermMask &= ~perm;
	}

	return prev;
}

int __CARDEnableGlobal(BOOL enable)
{
	return __CARDEnablePerm(0x20, enable);
}

int __CARDEnableCompany(BOOL enable)
{
	return __CARDEnablePerm(0x40, enable);
}
