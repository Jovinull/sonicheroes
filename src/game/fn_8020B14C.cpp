// Loads the entries of the bank image attached to a pool handle (see game/audio_system.h). The
// image starts with the tags "gcaxMLT " and, at 0x10, "gcaxMLTM"; the word at 0x1C is the size of
// the table of 16-byte entries that follows at 0x20. Entries with word 4 == 0xFFFFFFFF are skipped
// (without advancing, as in retail); kinds 1 and 4 (bits 24-27 of word 0) go to fn_80205F9C and
// fn_80205EA4. Returns 0, 0x09000001 for a bad header, 0x09000101 when a loader fails, the handle
// validation error, or 0x0D000001 when the system is absent.
// NonMatching: 19 word diffs, all saved-register coloring (retail keeps h in r27, e in r28, n in
// r29, base in r30 and err in r31); instructions, branches and relocations otherwise agree. The
// retail prologue uses stmw, so the unit is compiled with -use_lmw_stmw on.
#include "game/audio_system.h"

struct BankEntry8020B14C {
	unsigned int kind;   // 0x00: kind in bits 24-27
	unsigned int id;     // 0x04: bits 24-27 passed to the loader, 0xFFFFFFFF = unused
	unsigned int offset; // 0x08: from the start of the table
	unsigned int padC;
};

struct BankHeader8020B14C {
	unsigned int tag0; // "gcax"
	unsigned int tag1; // "MLT "
	unsigned char pad8[0x8];
	unsigned int tag2; // "gcax"
	unsigned int tag3; // "MLTM"
	unsigned char pad18[0x4];
	unsigned int tableSize;
	BankEntry8020B14C entries[1];
};

extern "C" {
int fn_80205F9C(int id, void* data, int a, int b, int c);
int fn_80205EA4(int id, void* data, int a, int b, int c);

int fn_8020B14C(PoolHandle* h)
{
	int n;
	int err;
	unsigned char* base;
	BankEntry8020B14C* e;
	PoolSystem* sys = lbl_8042CF6C;
	BankHeader8020B14C* hdr;
	int id;
	int res;
	if (sys == 0) {
		return 0x0D000001;
	}
	err = CheckPoolHandle(sys, h);
	if (err != 0) {
		return err;
	}
	hdr  = (BankHeader8020B14C*)h->param4;
	e    = hdr->entries;
	base = (unsigned char*)e;
	if (hdr->tag0 != 0x67636178 || hdr->tag1 != 0x4D4C5420 || hdr->tag2 != 0x67636178
	    || hdr->tag3 != 0x4D4C544D) {
		return 0x09000001;
	}
	err = 0;
	n   = hdr->tableSize >> 4;
	while (n-- > 0) {
		if (e->id == 0xFFFFFFFF) {
			continue;
		}
		id  = (e->id >> 24) & 0xF;
		res = -1;
		switch ((e->kind >> 24) & 0xF) {
			case 1:
				res = fn_80205F9C(
				    id, base + e->offset, h->paramC, h->param10, lbl_8042CF6C->f1446C);
				break;
			case 4:
				res = fn_80205EA4(
				    id, base + e->offset, h->paramC, h->param10, lbl_8042CF6C->f1446C);
				break;
		}
		if (res < 0) {
			err = 0x09000101;
			break;
		}
		e++;
	}
	return err;
}
}
