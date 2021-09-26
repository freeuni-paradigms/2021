#include <stdio.h>

typedef struct
{
    char *name;
    char suid[20];
    int numUnits;
} student;

int main()
{

    printf("%ld\n", sizeof(char *));
    printf("%ld\n", sizeof(int));
    printf("%ld\n", sizeof(size_t));

    printf("%ld\n", sizeof(student));

    int a[10];
    printf("%lu\n", a);
    printf("%lu\n", &a);
    printf("%lu\n", &a[0]);
}