#include <pthread.h>
#define N 10;

typedef struct
{
    int id;
    int amount;
    pthread_mutex_t *lock;
    pthread_cond_t *cond;
} Account;

void tryTransfer(Account *fromAccount, Account *toAccount, int amount)
{
    pthread_mutex_t *first, *second;

    if (fromAccount->id < toAccount->id)
    {
        first = fromAccount->lock;
        second = toAccount->lock;
    }
    else
    {
        first = toAccount->lock;
        second = fromAccount->lock;
    }

    pthread_mutex_lock(first);
    pthread_mutex_lock(second);
    if (fromAccount->amount < amount)
    {
        pthread_mutex_unlock(first);
        pthread_mutex_unlock(second);
        return;
    }

    fromAccount->amount -= amount;
    toAccount->amount += amount;
    pthread_mutex_unlock(first);
    pthread_mutex_unlock(second);
    pthread_cond_broadcast(toAccount->cond);
}

void transfer(Account *fromAccount, Account *toAccount, int amount)
{

    pthread_mutex_lock(fromAccount->lock);
    while (fromAccount->amount < amount)
    {
        pthread_cond_wait(fromAccount->cond, fromAccount->lock);
    }

    fromAccount->amount -= amount;
    pthread_mutex_unlock(fromAccount->lock);

    pthread_mutex_lock(toAccount->lock);
    toAccount->amount += amount;
    pthread_mutex_unlock(toAccount->lock);
    pthread_cond_broadcast(toAccount->cond);
}