#include "types.h"

// The first translation unit written inside a REL module rather than the DOL.
//
// It sits at the end of autosaveD's .text, from 0x476C to the end of the
// section at 0x47F0, which is why it is the one that was carved first: the end
// of a section is the one translation unit boundary in a module that does not
// have to be argued for. Everything before it is still one undivided run.
//
// The names are dtk's. What the four functions do is legible, but nothing in
// the module spells the type they operate on, so the file name and the field
// names below are descriptions rather than evidence.
//
// The object they share is a fixed table: a run of words from offset 0x0 with
// a count at 0x80, which puts the capacity at thirty two entries, and two more
// words at 0x84 and 0x88 that the reset paths clear alongside the count.
//
// fn_2_4798 is the shape Metrowerks emits for a C++ destructor that may also
// free: it takes the object and a short flag, calls the real destructor only
// when the flag is positive, and hands the object back. The destructor it
// calls, dtor_800575F4, lives in the DOL, so this is also the first written
// call from a module out to the main binary. That shape is worth recording
// because it means the module code is C++ rather than C, even though writing
// it as C reproduces it exactly: this arrives in r3 either way, and the
// module's symbol table is unmangled.

typedef struct Table {
	/* 0x00 */ u32 items[32];
	/* 0x80 */ u32 count;
	/* 0x84 */ u32 unk_0x84;
	/* 0x88 */ u32 unk_0x88;
} Table; // 0x8C

// In the DOL, at 0x800575F4.
extern void dtor_800575F4(Table* table);

void fn_2_476C(Table* table)
{
	table->count = table->unk_0x84 = 0;
}

void fn_2_477C(Table* table, u32 value)
{
	table->items[table->count] = value;
	table->count++;
}

Table* fn_2_4798(Table* table, s16 free)
{
	if (table != NULL) {
		if (free > 0) {
			dtor_800575F4(table);
		}
	}

	return table;
}

void fn_2_47DC(Table* table)
{
	table->count    = 0;
	table->unk_0x84 = 0;
	table->unk_0x88 = 0;
}
