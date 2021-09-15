#include <stdio.h>
#include <stdlib.h>

int main()
{
    // gcc memory_leak.c -Wall -ggdb3

    // valgrind --leak-check=full \
    //      --show-leak-kinds=all \
    //      --track-origins=yes \
    //      --verbose \
    //      --log-file=valgrind-out.txt \
    //      ./a.out

    // gcc memory_leak.c -fsanitize=leak

    void *elem = malloc(25);
    return 0;
}