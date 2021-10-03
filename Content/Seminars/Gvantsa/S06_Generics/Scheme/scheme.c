#include "scheme.h"

char *ConcatStrings(const char *first, const char *second)
{
    // S05/Strings/concat_strings.c
}

char *ConcatAll(nodeType *list)
{
    nodeType current = *list;

    switch (current)
    {
    case Nil:
    case Integer:
        return strdup("");
    case String:
        return strdup((char *)(list + 1));
    }

    nodeType **ptr = list + 1;

    nodeType *first = ptr[0]; // *(ptr + 0) // *((char *)ptr + 0 * sizeof(nodeType *))
    nodeType *second = ptr[1];

    char *firstStr = ConcatAll(first);
    char *secondStr = ConcatAll(second);

    char *result = ConcatStrings(firstStr, secondStr);

    free(firstStr);
    free(secondStr);

    return result;
}
