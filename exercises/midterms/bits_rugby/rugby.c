#include "rugby.h"

#include <string.h>

int GamesFn(char *pt, int i)
{
    return 1;
}

int PointsFn(char *pt, int i)
{
    return *(unsigned char *)(pt + i);
}

int WonFn(char *pt, int i)
{
    return *(unsigned char *)(pt + i) > *(unsigned char *)(pt + 1 - i);
}

int Count(char *r, char *team_name, int (*fn)(char *, int i))
{
    int ret = 0;
    int len = strlen(r);
    for (int i = 0; i < len;)
    {
        int j = i;
        while (j < len && r[j] != ' ' && r[j] != ';')
        {
            j++;
        }
        int l = j - i;
        if (l == strlen(team_name) && strncmp(team_name, r + i, l) == 0)
        {
            ret += fn(r + j + 1, 0);
        }
        j += 4;
        i = j;
        while (j < len && r[j] != ' ' && r[j] != ';')
        {
            j++;
        }
        l = j - i;
        if (l == strlen(team_name) && strncmp(team_name, r + i, l) == 0)
        {
            ret += fn(r + i - 3, 1);
        }
        i = j + 1;
    }
    return ret;
}

int TotalGamesPlayed(void *results, char *team_name)
{
    return Count(results, team_name, GamesFn);
}

int TotalPointsScored(void *results, char *team_name)
{
    return Count(results, team_name, PointsFn);
}

int NumWins(void *results, char *team_name)
{
    return Count(results, team_name, WonFn);
}
