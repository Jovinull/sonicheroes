#include "types.h"

// The module's entry points, and the two tables it registers on the way in.
//
// The translation unit runs from _unresolved at 0x1EF0 to the end of _prolog
// at 0x1FB4, and owns .data 0x2A8 to 0x2F0. Both bounds are read rather than
// argued: task_callback_setters.c ends at 0x1EF0 and task_object.c starts at
// 0x1FB4, so the run between them is whatever is left, and the two tables are
// touched by _prolog and by nothing else in the module.
//
// The names are not guesses either. A REL header carries the offsets of its
// prolog, epilog and unresolved handler, so dtk reads all three straight out
// of the module rather than inventing them.
//
// What the tables hold is not established. The second is a list of records
// ending in -1, three function pointers to a small integer, and the first is
// one such pair, so they are written as the shapes the data has rather than
// named for a purpose that is not evidenced.

typedef struct ModuleEntry {
	s32 id;
	void (*fn)(void);
} ModuleEntry;

typedef struct TaskEntry {
	s32 id;
	void (*fn0)(void);
	void (*fn1)(void);
	void (*fn2)(void);
} TaskEntry;

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

extern void fn_2_1EEC(void);
extern void fn_2_1CE4(void);
extern void fn_2_1B7C(void);
extern void fn_2_1BE4(void);
extern void fn_2_233C(void);
extern void fn_2_2294(void);
extern void fn_2_22FC(void);
extern void fn_2_139C(void);
extern void fn_2_1324(void);
extern void fn_2_136C(void);

extern u8 lbl_8042C1C0[];
extern void fn_800421B4(void* arg0, ModuleEntry* arg1);
extern void fn_80130478(TaskEntry** arg0);

ModuleEntry lbl_2_data_2A8[] = {
	{ 0, fn_2_1EEC },
};

TaskEntry lbl_2_data_2B0[] = {
	{ 0, fn_2_1CE4, fn_2_1B7C, fn_2_1BE4 },
	{ 1, fn_2_233C, fn_2_2294, fn_2_22FC },
	{ 2, fn_2_139C, fn_2_1324, fn_2_136C },
	{ -1, NULL, NULL, NULL },
};

void _unresolved(void) { }

void _epilog(void)
{
	void (**dtor)(void);

	dtor = _dtors;
	while (*dtor != NULL) {
		(*dtor)();
		dtor++;
	}
}

void _prolog(void)
{
	void (**ctor)(void);
	TaskEntry* table;

	ctor = _ctors;
	while (*ctor != NULL) {
		(*ctor)();
		ctor++;
	}
	fn_800421B4(lbl_8042C1C0, lbl_2_data_2A8);
	table = lbl_2_data_2B0;
	fn_80130478(&table);
}
