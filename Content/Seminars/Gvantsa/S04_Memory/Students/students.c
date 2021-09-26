typedef struct
{
    char *name;
    char suid[8];
    int numUnits;
} student;

int main()
{
    student friends[4];
    friends[0].name = friends[2].suid + 3;
    friends[5].numUnits = 21;
    strcpy(friends[1].suid, "4041554");
    strcpy(friends->name, "Tiger Woods");
    strcpy((char *)&friends[0].numUnits, (const char *)&friends[2].numUnits);
}
