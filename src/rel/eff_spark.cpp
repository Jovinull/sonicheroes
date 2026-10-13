#include "types.h"

// The EffSpark instance's housekeeping (rel/eff_spark_class.inc has the
// class). This unit has, in order:
// - effSparkClearAll: frees every spark (effSparkDestroy, inlined) and clears
//   the table;
// - effSparkLoad: on first use clears the table and loads the spark model
//   (obj0708_sparks.dff) from the stage's resources;
// - EffSpark's destructor and constructor;
// - effSparkEnd and effSparkInit: delete the instance / create it (the
//   constructor, load and clear are inlined) when there is none.
// The names other than the class's own are ours.

#include "src/rel/eff_spark_class.inc"

extern "C" void effSparkClearAll(EffSpark* spark)
{
	int i;

	for (i = 0; i < 0x200; i++) {
		effSparkDestroy(spark, spark->sparks[i]);
	}
	memset(spark->sparks, 0, sizeof(spark->sparks));
}

extern "C" void effSparkLoad(EffSpark* spark)
{
	if (spark->clump == NULL) {
		memset(spark->sparks, 0, sizeof(spark->sparks));
		spark->clump = fn_8004A774(lbl_8042C1D0, effSparkModelName);
	}
}

EffSpark::~EffSpark()
{
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}

EffSpark::EffSpark(TObject* parent)
    : TObject(parent)
    , clump(NULL)
{
	ClassName = CL_EffSpark;
	DispTime  = sizeof(EffSpark);
}

extern "C" void effSparkEnd(void)
{
	if (EffSparkTp != NULL) {
		delete EffSparkTp;
		EffSparkTp = NULL;
	}
}

extern "C" void effSparkInit(void)
{
	if (EffSparkTp == NULL) {
		EffSparkTp = new EffSpark(lbl_8042C110);
		effSparkLoad(EffSparkTp);
		effSparkClearAll(EffSparkTp);
	}
}
