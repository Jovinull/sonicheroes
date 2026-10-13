#include "types.h"

// effSparkDestroy's out-of-line copy (rel/eff_spark_class.inc has the body;
// the name is ours): frees one spark, its model and its RwMalloc block,
// returning whether there was one.

#define EFF_SPARK_DESTROY_INLINE
#include "src/rel/eff_spark_class.inc"
