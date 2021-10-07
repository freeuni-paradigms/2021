#include "sparsestringarray.h"

static void StringFree(void *elem) { free(*(char **)elem); }
void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize)
{
}

void SSADispose(sparsestringarray *ssa)
{
}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str)
{
}

void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData)
{
}