// C programming in Linux - ch3_3

#include <stdio.h>
#include <string.h>

struct player
{
    char name[255];
    char role[255];
    int ranking;
};

void rank(struct player *p)
{
    switch(p->name[0])
    {
        case 'P': p->ranking = 4; break;
        case 'H': p->ranking = 1; break;
        case 'R': p->ranking = 2; break;
        case 'J': p->ranking = 5; break;
        case 'B': p->ranking = 3; break;
    }
}

void show(struct player *p)
{
    printf("Name: %s Role: %s Ranking: %d<br>\n", p->name, p->role, p->ranking);
}

int main(void)
{
    struct player myteam[5] = {
        {"Pele", "striker", 0},
        {"Beckham", "male model", 0},
        {"Roddick", "tennis man", 0},
        {"Haskins", "swimmer", 0},
        {"Jagger", "singer", 0}
    };

    int i = 0;
    printf("Content-type:text/html\n\n");
    for (i = 0; i < 5; i++)
        rank(&myteam[i]);
    for (i = 0; i < 5; i++)
        show(&myteam[i]);
    
    return 0;
}