#include <assert.h>
#include <string.h>
#include <stdlib.h>

void Decompress(char **data)
{
    char *src = *data;
    char *str = "";
    while (*src != '\0')
    {
        // realloc(src, size)
        int byte = ...;
        int length = ...;
        int count  = ...;
        src++;
        char* sub_str = (src, src+length);
        for (int i = 0; i < count; i++){
            str += sub_str;
        }
        src += length;
    }
    str += "\0";
    free(*data);
    *data = str;
}
