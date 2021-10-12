#include "multitable.h"

void MultiTableNew(multitable *mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, MultiTableHashFunction hash, MultiTableCompareFunction compare){
    mt->keySize = keySizeInBytes;
    mt->valueSize = valueSizeInBytes;
    HashSetNew(&mt->mappings, keySizeInBytes + sizeof(vector), numBuckets, hash, compare, NULL);
}


void MultiTableEnter(multitable *mt, const void *keyAddr, const void *valueAddr) {
    void * found = HashSetLookup(&mt->mappings, keyAddr);
    vector * values;

    if (found == NULL) {
        char buffer[mt->keySize + sizeof(vector)];
        memcpy(buffer, keyAddr, mt->keySize);
        values = (vector *)(buffer + mt->keySize);
        VectorNew(values, mt->valueSize, NULL, 1);
        VectorAppend(values, valueAddr);
        HashSetEnter(&mt->mappings, buffer);
    } else {
        values = (vector *)((char *)found + mt->keySize);
        VectorAppend(values, valueAddr);
    }
}

typedef struct {
    MultiTableMapFunction map;
    void *auxData;
    int keySize;
} maphelper;

static void HashSetMapFunc(void *elemAddr, void *auxData) {
    maphelper *helper = auxData;
    vector * values = (vector *)((char *)elemAddr + helper->keySize);

    for (int i = 0; i < VectorLength(values); i++) {
        helper->map(elemAddr, VectorNth(values, i), helper->auxData);
    }
}

void MultiTableMap(multitable *mt, MultiTableMapFunction map, void *auxData) {
    maphelper helper = {map, auxData, mt->keySize};
    HashSetMap(&mt->mappings, HashSetMapFunc, &helper);
}
