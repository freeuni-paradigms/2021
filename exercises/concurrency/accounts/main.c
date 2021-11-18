#include <pthread.h>
#define N 10;

typedef struct
{
    int id;
    int amount;
    // საჭირო ველები დაამატეთ აქ
} Account;

void tryTransfer(Account *fromAccount, Account *toAccount, int amount)
{
}

void transfer(Account *fromAccount, Account *toAccount, int amount)
{
}