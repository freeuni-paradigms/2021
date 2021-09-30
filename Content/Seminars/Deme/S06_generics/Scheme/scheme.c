#include "scheme.h"

char *ConcatStrings(const char *first, const char *second) {
    size_t newSize = strlen(first) + strlen(second) + 1;
	char * result = malloc(newSize);
	strcpy(result, first);
	strcat(result, second);
	return result;
}

char *ConcatAll(nodeType *list) {
    nodeType currentType = *list;

    switch (currentType)
    {
    case Integer:
    case Nil:
        return strdup("");
    case String:
        return strdup((char*)(list + 1));
    }

    nodeType ** arr = (nodeType **)(list + 1);
    nodeType * first = arr[0];
    nodeType * second = arr[1];

    char * firstStr = ConcatAll(first);
    char * secondStr = ConcatAll(second);
    char * result = ConcatStrings(firstStr, secondStr);

    free(firstStr);
    free(secondStr);
    return result;
}
