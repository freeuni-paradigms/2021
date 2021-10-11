#include "sparsestringarray.h"

static void StringFree(void *elem) { free(*(char **)elem); }
void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize)
{
    ssa->arrayLength = arrayLength;
    ssa->groupSize = groupSize;

    ssa->numGroups = ((arrayLength - 1) / groupSize) + 1;

    ssa->groups = malloc(ssa->numGroups * sizeof(group));

    for (int i = 0; i < ssa->numGroups; i++)
    {
        ssa->groups[i].bitmap = malloc(groupSize * sizeof(bool));
        bzero(ssa->groups[i].bitmap, groupSize * sizeof(bool));
        VectorNew(&ssa->groups[i].strings, sizeof(char *), StringFree, 1);
    }
}

void SSADispose(sparsestringarray *ssa)
{
    for (int i = 0; i < ssa->numGroups; i++)
    {
        free(ssa->groups[i].bitmap);
        VectorDispose(&ssa->groups[i].strings);
    }

    free(ssa->groups);
}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str)
{
    int groupIndex = index / ssa->groupSize;
    int bitmapIndex = index % ssa->groupSize;

    group *grp = &ssa->groups[groupIndex];
    bool hasElement = grp->bitmap[bitmapIndex];

    int vectorIndex = 0;

    for (int i = 0; i < bitmapIndex; i++)
    {
        if (grp->bitmap[i])
            vectorIndex++;
    }

    char *copy = strdup(str);

    if (hasElement)
    {
        VectorReplace(&grp->strings, &copy, vectorIndex);
    }
    else
    {
        VectorInsert(&grp->strings, &copy, vectorIndex);
        grp->bitmap[bitmapIndex] = true;
    }

    return !hasElement;
}

void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData)
{
    char *elem = strdup("");
    for (int i = 0; i < ssa->numGroups; i++)
    {
        int end = ssa->groupSize;
        if (i == ssa->numGroups - 1 && ssa->arrayLength % ssa->groupSize != 0)
        {
            end = ssa->arrayLength % ssa->groupSize;
        }

        int vectorIndex = 0;

        for (int j = 0; j < end; j++)
        {
            if (ssa->groups[i].bitmap[j])
            {
                char **currElemPtr = VectorNth(&ssa->groups[i].strings, vectorIndex);
                mapfn(i * ssa->groupSize + j, *currElemPtr, auxData);
                vectorIndex++;
            }
            else
            {
                mapfn(i * ssa->groupSize + j, elem, auxData);
            }
        }
    }
    free(elem);
}