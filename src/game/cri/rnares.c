#include "MSL_C/string.h"
#include "cri/adapter.h"
#include "cri/rnares.h"
#include "dolphin/ar.h"

extern "C" {

// CRI RNARES for GameCube: the contiguous resource-handle API and the
// destroy expansion in Finish support .text 0x80224CD0-0x80225100.
// The following ranges exclude trailing linker alignment: .rodata
// 0x802405F8-0x80240647 and .bss 0x8042A9D0-0x8042AB64.

// Descriptive names inferred from the GameCube accesses, not recovered symbols.
// Separate scalars preserve CodeWarrior's native pooled BSS addressing.
static u32 rnares_reference_count;
static u32 rnares_externally_allocated;
static u32 rnares_handle_count;
static u32 rnares_aram_size;
static u32 rnares_aram_address;
static RnaResHandle rnares_handles[32];

extern const char lbl_802405F8[] = "E1070313:Not enough RNARES handle.\n";
extern const char lbl_8024061C[] = "E1090601:Free area other than ADX buffer.\n";

u32 fn_80224CD0(RnaResHandle* handle)
{
	if (handle == NULL) {
		return 0;
	}
	return handle->size;
}

u32 fn_80224CE8(RnaResHandle* handle)
{
	if (handle == NULL) {
		return 0;
	}
	return handle->address;
}

void fn_80224D00(RnaResHandle* handle)
{
	if (handle == NULL) {
		return;
	}
	handle->used = 0;
}

RnaResHandle* fn_80224D14(void)
{
	s32 count;
	RnaResHandle* handle;
	for (count = 0; count < 32; count++) {
		if (rnares_handles[count].used == 0) {
			break;
		}
	}
	if (count == 32) {
		fn_80223424(lbl_802405F8);
		return NULL;
	}
	handle       = &rnares_handles[count];
	handle->used = 1;
	return handle;
}

void fn_80224E1C(void)
{
	s32 i;
	u32 freeSize;
	RnaResHandle* handles;
	if (--rnares_reference_count != 0) {
		return;
	}
	handles = rnares_handles;
	for (i = 0; i < 32; i++) {
		if (handles[i].used == 1) {
			fn_80224D00(&handles[i]);
		}
	}
	memset(rnares_handles, 0, sizeof(rnares_handles));
	if (rnares_externally_allocated == 0) {
		ARFree(&freeSize);
		if (freeSize != rnares_aram_size) {
			fn_80223424(lbl_8024061C);
		}
		rnares_handle_count = 0;
		rnares_aram_size    = 0;
		rnares_aram_address = 0;
	}
}

void fn_80224F88(void)
{
	u32 count;
	s32 i;
	u32 address;
	RnaResHandle* handle;
	if (rnares_reference_count == 0) {
		if (rnares_externally_allocated == 0) {
			rnares_handle_count = 32;
			rnares_aram_size    = 0x40000;
			rnares_aram_address = ARAlloc(0x40000);
		}
		memset(rnares_handles, 0, sizeof(rnares_handles));
		count   = rnares_handle_count;
		handle  = rnares_handles;
		address = rnares_aram_address;
		for (i = 0; i < count; i++, handle++) {
			handle->address = (address + i * 0x2000U) >> 1;
			handle->size    = 0x1000;
		}
	}
	rnares_reference_count++;
}
}
