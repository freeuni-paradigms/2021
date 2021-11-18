#include <pthread.h>
#define N 10;

typedef struct
{
    int id;
    int amount;
    // საჭირო ველები დაამატეთ აქ
} Account;

void AmountIn(Account *fromAccount, Account *myAccount, int amount)
{
}

void AmountOut(Account *myAccount, Account *toAccount, int amount)
{
}