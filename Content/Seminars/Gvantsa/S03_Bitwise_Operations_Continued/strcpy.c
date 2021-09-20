#include <stdio.h>

void strcpy1(char dest[], const char source[])
{
    int i;
    for (i = 0; source[i] != '\0'; i++)
        dest[i] = source[i];
    dest[i] = '\0';
}

int main()
{

    char example[50];
    char *name = "John Doe";

    strcpy1(example, name);

    return 0;
}